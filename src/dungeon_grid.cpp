/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

//
// Implements layered cycles that can be used to then create a dungeon
//

#include "my_main.h"
#include "my_point.h"
#include "my_tile.h"
#include "my_room.h"
#include "my_charmap.h"
#include "my_dmap.h"
#include "my_range.h"
#include "my_dungeon_grid.h"
#include <stack>
#include <list>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

/*
 * Start with a grid of nodes and a start point.
 *
 *    x x x x x
 *
 *    x x S x x
 *
 *    x x x x x
 *
 *    x x x x x
 *
 *    x x x x x
 *
 * Recursize snake walk from a random start. Stop once you have a loop.
 *
 *    1-1-1-1 x
 *          |
 *    x 1-1-1 x
 *      |   |
 *    x 1-1-1-1
 *
 *    x x x x x
 *
 *    x x x x x
 *
 * The above is depth 1 of our loop. Choose an adjacent node for depth 2
 *
 *    1-1-1-1 x
 *          |
 *    x 1-1-1 x
 *      |   |
 *    x 1-1-1-1
 *      .   .
 *    x D-2-D x
 *      |   |
 *    x 2-2-2 x
 *
 * Again stop when a loop. Choose random 1 - 2 connections and make those doors.
 *
 * Repeat for depth 3
 *
 *    1-1-1-1 x
 *          |
 *    x 1-1-1 x
 *      |   |
 *    x 1-1-1-1
 *      .   .
 *    x D-2-D.D
 *      |   | |
 *    x 2-2-2 3
 *    
 * Remove disconnected nodes. 
 *
 *    - 1-1-1 -
 *          |
 *    - 1-1-1 -
 *      |   |
 *    - 1-1-1-1
 *      .   .
 *    - D-2-D.D
 *      |   | |
 *    - 2-2-2 3
 *    
 * Do a djkstra flood from a random end point in 3
 *
 *    - 1-2-3 -
 *          |
 *    - 2-4-4 -
 *      |   |
 *    - 3-4-6-4
 *      .   .
 *    - 4-5-7=8
 *      |   | |
 *    - 4-5-6 9
 *    
 * Choose the furthest point as the start.
 *
 *      S-1-1  
 *          |
 *      1-1-1  
 *      |   |
 *      1-1-1-1
 *      .   .
 *      2-2-2=3
 *      |   | |
 *      2-2-2 E
 *
 * Place a key room one per depth. A key need not be a real key, but
 * something that unlocks an node between 1 and 2
 *
 *      S-1-1  
 *          |
 *      1-1-*  
 *      |   |
 *      1-1-1-1
 *      .   .
 *      2-2-2=3
 *      |   | |
 *      2-2-* E
 */

static bool debug_enabled = true;

void Nodes::finish_constructor (void)
{_
redo:
    init_nodes();

    //
    // Place the depth and join up the nodes. Add occasional
    // secret jumps between nodes in the depth
    //
    auto pass = 1;
    auto depth = 1;
    while (depth < 10) {
        set_max_depth();

        auto placed = snake_walk(depth, 10, pass);

        CON("node-grid: level depth %d placed %d nodes", depth, placed);
        if (!placed) {
            break;
        }

        //
        // We need at least 2 nodes per depth as one can be a lock
        // and the other a key per depth
        //
        if (depth == 1) {
            //
            // Need an extra one on level one for the entrance
            //
            if (placed < 3) {
                debug("failed initial level, did not place enough nodes");
                CON("node-grid: failed level depth %d placed only %d nodes, redo", depth, placed);
                goto redo;
            }
        } else {
            if (placed < 2) {
                debug("failed level, did not place enough nodes at depth");
                CON("node-grid: failed level depth %d placed only %d nodes, redo", depth, placed);
                goto redo;
            }
        }

        join_nodes_of_same_depth(depth, pass);
        depth++;
    }

    debug("done first pass of rooms at same depth");

    for (auto join = 1; join < depth - 1; join++) {
        join_depth_to_next_depth(join, pass);
    }
    debug("done first pass of rooms and joined rooms to next depth");

    remove_stubs();
    debug("removed stubs");

    for (auto join = 1; join < depth - 2; join++) {
        join_depth_secret(join, pass);
    }
    debug("done first pass of rooms and joined secret rooms");

    //
    // Now place secret rooms and join them to the main
    // depth via secret doors
    //
    pass = 2;
    auto secret_depth = 1;
    while (secret_depth < 10) {
        auto placed = snake_walk(secret_depth, 10, pass);

        CON("node-grid: level depth %d placed %d secret nodes", secret_depth, placed);
        if (!placed) {
            break;
        }

        join_nodes_of_same_depth(secret_depth, pass);
        secret_depth++;
    }
    debug("done snake walk of secret rooms");

    for (auto join = 1; join < depth; join++) {
        join_depth_to_next_depth(join, pass);
    }
    debug("done first pass of secret rooms and joined rooms to next depth");

    for (auto join = 1; join < depth; join++) {
        join_depth_secret(join, pass);
    }
    debug("done second pass of secret rooms and joined secret rooms to next depth");

    remove_stubs();
    debug("removed stubs");

    set_max_depth();

    //
    // Add start and exit
    //
    place_entrance();
    place_exit();
    
    //
    // First time we consider secret exitsd
    //
    create_path_to_exit(1);
    debug("created path to exit");

    //
    // Second time we ignore them to ensure they are not considered
    // as on the main path
    //
    create_path_to_exit(2);
    debug("created path to exit, ignoring secret paths");

    //
    // Make nodes not on the direct path to the exit, bi directional
    // so you cannot get stuck
    //
    make_paths_off_critical_path_reachable();
    debug("made critical paths reachable");

    //
    // Ensure each key can reach each lock
    //
    for (auto depth = 1; depth < max_depth; depth++) {
        create_path_lock_to_key(depth);
    }
    debug("created path from keys to locks");

    //
    // Add keys for moving between levels
    //
    for (auto depth = 2; depth <= max_depth; depth++) {
        place_lock(depth, 1);
    }
    for (auto depth = 2; depth <= max_depth; depth++) {
        hide_other_locks(depth, 1);
    }
    for (auto depth = 1; depth < max_depth; depth++) {
        if (!place_key(depth, 1)) {
            goto redo;
        }
    }
    debug("placed locks");

    debug("final map");
}

void Nodes::debug (std::string msg)
{_
    if (!debug_enabled) {
        return;
    }

    auto step = 5;
    auto center = 3;

    char out[(nodes_height+1) * step][(nodes_width+1) * step];

    memset(out, ' ', sizeof(out));

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto ox = (x * step) + center;
            auto oy = (y * step) + center;
            auto node = getn(x, y);
            if (node->has_exit_down) {
                out[oy+1][ox] = '|';
                out[oy+2][ox] = '|';
            }
            if (node->has_exit_up) {
                out[oy-1][ox] = '|';
                out[oy-2][ox] = '|';
            }
            if (node->has_exit_left) {
                out[oy][ox-1] = '-';
                out[oy][ox-2] = '-';
            }
            if (node->has_exit_right) {
                out[oy][ox+1] = '-';
                out[oy][ox+2] = '-';
            }
            if (node->has_secret_exit_down) {
                out[oy+1][ox] = '?';
                out[oy+2][ox] = '?';
            }
            if (node->has_secret_exit_up) {
                out[oy-1][ox] = '?';
                out[oy-2][ox] = '?';
            }
            if (node->has_secret_exit_left) {
                out[oy][ox-1] = '?';
                out[oy][ox-2] = '?';
            }
            if (node->has_secret_exit_right) {
                out[oy][ox+1] = '?';
                out[oy][ox+2] = '?';
            }
            if (node->dir_up) {
                out[oy-1][ox-1] = '^';
            }
            if (node->dir_down) {
                out[oy-1][ox+1] = 'v';
            }
            if (node->dir_left) {
                out[oy+1][ox-1] = '<';
            }
            if (node->dir_right) {
                out[oy+1][ox+1] = '>';
            }
            if (node->is_entrance) {
                out[oy][ox-1] = 'S';
            }
            if (node->is_exit) {
                out[oy][ox-1] = 'E';
            }
            if (node->is_lock) {
                out[oy][ox-1] = 'D';
            }
            if (node->is_key) {
                out[oy][ox-1] = 'K';
            }

            if (node->depth == depth_obstacle) {
                out[oy][ox] = 'O';
            } else if (node->depth) {
                out[oy][ox] = '0' + node->depth;
            } else {
                out[oy][ox] = '.';
            }
        }
    }

    for (auto y = 0; y < nodes_height * step; y++) {
        std::string s;
        for (auto x = 0; x < nodes_width * step; x++) {
            s += out[y][x];
        }
        CON("node-grid: %s", s.c_str());
    }
    CON("node-grid: ^^^^^ %s ^^^^^", msg.c_str());

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto node = getn(x, y);
            if (node->has_exit_down) {
                if (y == nodes_height - 1) {
                    DIE("node %d,%d has exit down off end of map", x, y);
                }
            }
            if (node->has_exit_right) {
                if (x == nodes_width - 1) {
                    DIE("node %d,%d has exit right off end of map", x, y);
                }
            }
            if (node->has_exit_left) {
                if (x == 0) {
                    DIE("node %d,%d has exit left off end of map", x, y);
                }
            }
            if (node->has_exit_up) {
                if (y == 0) {
                    DIE("node %d,%d has exit up off end of map", x, y);
                }
            }
            if (node->has_secret_exit_down) {
                if (y == nodes_height - 1) {
                    DIE("node %d,%d has secret exit down off end of map", x, y);
                }
            }
            if (node->has_secret_exit_right) {
                if (x == nodes_width - 1) {
                    DIE("node %d,%d has secret exit right off end of map", x, y);
                }
            }
            if (node->has_secret_exit_left) {
                if (x == 0) {
                    DIE("node %d,%d has secret exit left off end of map", x, y);
                }
            }
            if (node->has_secret_exit_up) {
                if (y == 0) {
                    DIE("node %d,%d has secret exit up off end of map", x, y);
                }
            }
        }
    }

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto node = getn(x, y);
            if (node->has_exit_down) {
                auto o = getn(x, y + 1);
                if (!o || !o->depth) {
                    DIE("node %d,%d has exit down but no node exists", x, y);
                }
            }
            if (node->has_exit_right) {
                auto o = getn(x + 1, y);
                if (!o || !o->depth) {
                    DIE("node %d,%d has exit right but no node exists", x, y);
                }
            }
            if (node->has_exit_left) {
                auto o = getn(x - 1, y);
                if (!o || !o->depth) {
                    DIE("node %d,%d has exit left but no node exists", x, y);
                }
            }
            if (node->has_exit_up) {
                auto o = getn(x, y - 1);
                if (!o || !o->depth) {
                    DIE("node %d,%d has exit up but no node exists", x, y);
                }
            }
            if (node->has_secret_exit_down) {
                auto o = getn(x, y + 1);
                if (!o || !o->depth) {
                    DIE("node %d,%d has secret exit down but no node exists", x, y);
                }
            }
            if (node->has_secret_exit_right) {
                auto o = getn(x + 1, y);
                if (!o || !o->depth) {
                    DIE("node %d,%d has secret exit right but no node exists", x, y);
                }
            }
            if (node->has_secret_exit_left) {
                auto o = getn(x - 1, y);
                if (!o || !o->depth) {
                    DIE("node %d,%d has secret exit left but no node exists", x, y);
                }
            }
            if (node->has_secret_exit_up) {
                auto o = getn(x, y - 1);
                if (!o || !o->depth) {
                    DIE("node %d,%d has secret exit up but no node exists", x, y);
                }
            }
        }
    }

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto node = getn(x, y);
            if (node->has_exit_down) {
                auto o = getn(x, y + 1);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has exit down but that node is an obstacle", x, y);
                }
            }
            if (node->has_exit_right) {
                auto o = getn(x + 1, y);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has exit right but that node is an obstacle", x, y);
                }
            }
            if (node->has_exit_left) {
                auto o = getn(x - 1, y);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has exit left but that node is an obstacle", x, y);
                }
            }
            if (node->has_exit_up) {
                auto o = getn(x, y - 1);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has exit up but that node is an obstacle", x, y);
                }
            }
            if (node->has_secret_exit_down) {
                auto o = getn(x, y + 1);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has secret exit down but that node is an obstacle", x, y);
                }
            }
            if (node->has_secret_exit_right) {
                auto o = getn(x + 1, y);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has secret exit right but that node is an obstacle", x, y);
                }
            }
            if (node->has_secret_exit_left) {
                auto o = getn(x - 1, y);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has secret exit left but that node is an obstacle", x, y);
                }
            }
            if (node->has_secret_exit_up) {
                auto o = getn(x, y - 1);
                if (o->depth == depth_obstacle) {
                    DIE("node %d,%d has secret exit up but that node is an obstacle", x, y);
                }
            }
        }
    }

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto node = getn(x, y);
            if (node->has_exit_down) {
                if (node->has_secret_exit_down) {
                    DIE("node %d,%d has both normal and secret exits down", x, y);
                }
            }
            if (node->has_exit_right) {
                if (node->has_secret_exit_right) {
                    DIE("node %d,%d has both normal and secret exits right", x, y);
                }
            }
            if (node->has_exit_left) {
                if (node->has_secret_exit_left) {
                    DIE("node %d,%d has both normal and secret exits left", x, y);
                }
            }
            if (node->has_exit_up) {
                if (node->has_secret_exit_up) {
                    DIE("node %d,%d has both normal and secret exits up", x, y);
                }
            }
        }
    }
}

int Nodes::offset (const int x, const int y)
{_
    auto offset = nodes_width * y;
    offset += x;

    return (offset);
}

bool Nodes::is_oob (const int x, const int y)
{_
    return ((x < 0) || (x >= nodes_width) ||
            (y < 0) || (y >= nodes_height));
}

Node *Nodes::node_addr (const int x, const int y)
{_
    if (is_oob(x, y)) {
        return (nullptr);
    }

    return (&nodes[offset(x, y)]);
}

void Nodes::putn (const int x, const int y, const Node n)
{_
    auto p = node_addr(x, y);
    if (p != nullptr) {
        *p = n;
    }
}

Node *Nodes::getn (const int x, const int y)
{_
    auto p = node_addr(x, y);
    return (p);
}

point Nodes::random_dir (void)
{
    auto dx = 0, dy = 0;

    switch (random_range(0, 4)) {
        case 0: dx = -1; dy =  0; break;
        case 1: dx =  1; dy =  0; break;
        case 2: dx =  0; dy = -1; break;
        case 3: dx =  0; dy =  1; break;
    }
    return (point(dx, dy));
}

void Nodes::random_dir (int *dx, int *dy)
{
    switch (random_range(0, 4)) {
        case 0: *dx = -1; *dy =  0; break;
        case 1: *dx =  1; *dy =  0; break;
        case 2: *dx =  0; *dy = -1; break;
        case 3: *dx =  0; *dy =  1; break;
    }
}

//
// Set up nodes so they know their coords
//
void Nodes::init_nodes (void)
{
    nodes.resize(nodes_width * nodes_height);

    std::vector< std::pair<point, point> > s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto n = getn(x, y);
            n->depth                                 = 0;
            n->pass                                  = 0;
            n->x                                     = 0;
            n->y                                     = 0;
            n->is_key                                = false;
            n->is_lock                               = false;
            n->is_entrance                           = false;
            n->is_exit                               = false;
            n->on_critical_path                      = false;
            n->dir_up                                = false;
            n->dir_down                              = false;
            n->dir_left                              = false;
            n->dir_right                             = false;
            n->set_has_exit_up(false);
            n->set_has_exit_down(false);
            n->set_has_exit_left(false);
            n->set_has_exit_right(false);
            n->set_has_secret_exit_up(false);
            n->set_has_secret_exit_down(false);
            n->set_has_secret_exit_left(false);
            n->set_has_secret_exit_right(false);
        }
    }

#if 0
    auto obstacles = random_range(0, (nodes_width * nodes_height) / 4);
    if (obstacles < 3) {
        obstacles = 3;
    }

    while (obstacles--) {
        auto x = random_range(0, nodes_width);
        auto y = random_range(1, nodes_height);

        auto o = getn(x, y);
        o->depth = depth_obstacle;
    }
#endif

    max_depth = 0;
    max_vdepth = 0;
}

//
// Walk the depth randomly, ala snake until you hit your own tail,
// forking randomly also
//
bool Nodes::node_is_free (Node *n)
{
    return (n && !n->depth);
}

bool Nodes::node_is_a_room (Node *n)
{
    return (n && n->depth && (n->depth != depth_obstacle));
}

int Nodes::snake_walk (int depth, int max_placed, int pass)
{
    std::list<point> s;

    auto dx = 0;
    auto dy = 0;
    auto x = 0;
    auto y = 0;

    if (depth == 1) {
        if (pass == 1) {
            //
            // Start anywhere
            //
            auto tries = 1000;
            while (tries--) {
                x = random_range(0, nodes_width);
                y = 0;

                auto o = getn(x, y);
                if (node_is_free(o)) {
                    s.push_back(point(x, y));
                    random_dir(&dx, &dy);
                    dy = 0;
                    break;
                }
            }

            if (tries < 0) {
                return (0);
            }
        } else {
            //
            // Start adjacent to a non hidden level node and connect to it
            //
            auto tries = 1000;
            while (tries--) {
                x = random_range(0, nodes_width);
                y = random_range(0, nodes_height);
                random_dir(&dx, &dy);

                auto o = getn(x, y);
                auto n = getn(x + dx, y + dy);

                if (node_is_free(o) && node_is_a_room(n) && (n->pass != pass)) {
                    s.push_back(point(x, y));

                    if (dx == 1) {
                        o->set_has_secret_exit_right(true);
                        n->set_has_secret_exit_left(true);
                    }

                    if (dx == -1) {
                        o->set_has_secret_exit_left(true);
                        n->set_has_secret_exit_right(true);
                    }

                    if (dy == 1) {
                        o->set_has_secret_exit_down(true);
                        n->set_has_secret_exit_up(true);
                    }

                    if (dy == -1) {
                        o->set_has_secret_exit_up(true);
                        n->set_has_secret_exit_down(true);
                    }
                    break;
                }
            }

            if (tries < 0) {
                return (0);
            }
        }
    } else {
        if (pass == 1) {
            //
            // Else start adjacent next to the old max depth
            //
            auto tries = 1000;
            while (tries--) {
                x = random_range(0, nodes_width);
                y = max_vdepth;

                random_dir(&dx, &dy);

                auto o = getn(x, y);
                auto n = getn(x + dx, y + dy);

                if (node_is_free(o) && node_is_a_room(n) && 
                    (n->pass == pass) && (n->depth == depth - 1)) {
                    s.push_back(point(x, y));

                    if (dx == 1) {
                        o->set_has_exit_right(true);
                        n->set_has_exit_left(true);
                    }

                    if (dx == -1) {
                        o->set_has_exit_left(true);
                        n->set_has_exit_right(true);
                    }

                    if (dy == 1) {
                        o->set_has_exit_down(true);
                        n->set_has_exit_up(true);
                    }

                    if (dy == -1) {
                        o->set_has_exit_up(true);
                        n->set_has_exit_down(true);
                    }
                    break;
                }
            }

            if (tries < 0) {
                return (0);
            }
        } else {
            //
            // Else start adjacent next to the old secret depth
            //
            auto tries = 1000;
            while (tries--) {
                x = random_range(0, nodes_width);
                y = random_range(0, nodes_height);
                random_dir(&dx, &dy);

                auto o = getn(x, y);
                auto n = getn(x + dx, y + dy);

                if (node_is_free(o) && node_is_a_room(n) && 
                    (n->pass == pass) && (n->depth == depth - 1)) {
                    s.push_back(point(x, y));

                    if (dx == 1) {
                        o->set_has_secret_exit_right(true);
                        n->set_has_secret_exit_left(true);
                    }

                    if (dx == -1) {
                        o->set_has_secret_exit_left(true);
                        n->set_has_secret_exit_right(true);
                    }

                    if (dy == 1) {
                        o->set_has_secret_exit_down(true);
                        n->set_has_secret_exit_up(true);
                    }

                    if (dy == -1) {
                        o->set_has_secret_exit_up(true);
                        n->set_has_secret_exit_down(true);
                    }
                    break;
                }
            }

            if (tries < 0) {
                return (0);
            }
        }
    }

    auto placed = 0;
    dy = 0;

    do {
        auto p = s.front();
        s.pop_front();

        auto x = p.x;
        auto y = p.y;

        //
        // Get next empty cell
        //
        auto n = getn(x, y);
        if (!n || n->depth) {
            continue;
        }

        if (n->pass && (n->pass != pass)) {
            continue;
        }

        placed++;
        n->depth = depth;
        n->pass = pass;

        //
        // Change dir
        //
        random_dir(&dx, &dy);
        if (dy < 0) {
            if (random_range(0, 1000) < 990) {
                dy = 0;
            }
        }
        if (dy > 0) {
            if (random_range(0, 100) < 20) {
                dy = 0;
            }
        }

        auto old = n;

        //
        // Create forks but make sure the old corridor knows
        // where the fork corridor is
        //
        if (placed < max_placed) {
            if (random_range(0, 100) < 90) {
                switch (random_range(0, 2)) {
                case 0: 
                    if (x < nodes_width - 1) {
                        auto f = getn(x + 1, y);
                        if (node_is_free(f)) {
                            s.push_back(point(x + 1, y    )); 
                            n->set_has_exit_right(true);
                        }
                    }
                    break;
                case 1: 
                    if (x > 0){
                        auto f = getn(x - 1, y);
                        if (node_is_free(f)) {
                            s.push_back(point(x - 1, y    ));
                            n->set_has_exit_left(true);
                        }
                    }
                    break;
                }
            }

            if (random_range(0, 100) < 10) {
                if (y < nodes_height - 1) {
                    auto f = getn(x, y + 1);
                    if (node_is_free(f)) {
                        s.push_back(point(x, y + 1));
                        n->set_has_exit_down(true);
                    }
                }
            }

            if (y < depth + 2) {
                if (random_range(0, 100) < 5) {
                    if (y > 0){
                        auto f = getn(x, y - 1);
                        if (node_is_free(f)) {
                            s.push_back(point(x, y - 1));
                            n->set_has_exit_up(true);
                        }
                    }
                }
            }
            if (dy < 0) {
                dy = 0;
            }

            //
            // Get the next move, or change dir again if blocked.
            //
            n = getn(x + dx, y + dy);
            if (!node_is_free(n)) {
                auto tries = 5;
                while (tries--) {
                    random_dir(&dx, &dy);
                    dy = 0;
                    n = getn(x + dx, y + dy);
                    if (node_is_free(n)) {
                        break;
                    }
                }

                if (tries < 0) {
                    continue;
                }
            }

            s.push_back(point(x + dx, y + dy));

            if (dx == 1) {
                old->set_has_exit_right(true);
            }
            if (dx == -1) {
                old->set_has_exit_left(true);
            }
            if (dy == 1) {
                old->set_has_exit_down(true);
            }
            if (dy == -1) {
                old->set_has_exit_up(true);
            }
        }

    } while (s.size());

    return (placed);
}

void Nodes::join_nodes_of_same_depth (int depth, int pass)
{
    //
    // Connect up the nodes on the same depth
    //
    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->depth != depth) {
                continue;
            }

            if (o->pass && (o->pass != pass)) {
                continue;
            }

            if (o->has_exit_right) {
                auto n = getn(x + 1, y);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->set_has_exit_left(true);
                } else {
                    o->set_has_exit_right(false);
                }
            }

            if (o->has_exit_left) {
                auto n = getn(x - 1, y);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->set_has_exit_right(true);
                } else {
                    o->set_has_exit_left(false);
                }
            }

            if (o->has_exit_down) {
                auto n = getn(x, y + 1);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->set_has_exit_up(true);
                } else {
                    o->set_has_exit_down(false);
                }
            }

            if (o->has_exit_up) {
                auto n = getn(x, y - 1);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->set_has_exit_down(true);
                } else {
                    o->set_has_exit_up(false);
                }
            }
        }
    }
}

//
// Connect up the nodes to the next depth. We need at least one.
//
void Nodes::join_depth_to_next_depth (int depth, int pass)
{
    std::vector< std::pair<point, point> > s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->depth != depth) {
                continue;
            }
            if (o->pass && (o->pass != pass)) {
                continue;
            }

            auto n = getn(x + 1, y);
            if (n && (n->pass == pass) && (n->depth == depth + 1)) {
                s.push_back(
                    std::make_pair(point(x, y), point(x + 1, y)));
            }

            n = getn(x - 1, y);
            if (n && (n->pass == pass) && (n->depth == depth + 1)) {
                s.push_back(
                    std::make_pair(point(x, y), point(x - 1, y)));
            }

            n = getn(x, y + 1);
            if (n && (n->pass == pass) && (n->depth == depth + 1)) {
                s.push_back(
                    std::make_pair(point(x, y), point(x, y + 1)));
            }

            n = getn(x, y - 1);
            if (n && (n->pass == pass) && (n->depth == depth + 1)) {
                s.push_back(
                    std::make_pair(point(x, y), point(x, y - 1)));
            }
        }
    }

    if (!s.size()) {
        if (pass == 1) {
            debug("error");
            DIE("no exits from %d to %d", depth, depth + 1);
        }
        return;
    }

    auto r = random_range(0, s.size());

    if (!r) {
        r = 1;
    }

    while (r--) {
        auto i = random_range(0, s.size());
        auto p = s[i];
        auto a = p.first;
        auto b = p.second;

        auto dx = b.x - a.x;
        auto dy = b.y - a.y;

        auto n = getn(b.x, b.y);
        if (!n) {
            DIE("no new pos");
        }
        auto o = getn(a.x, a.y);
        if (!o) {
            DIE("no old pos");
        }

        if (dx == 1) {
            o->set_has_exit_right(true);
            n->set_has_exit_left(true);
        }

        if (dx == -1) {
            o->set_has_exit_left(true);
            n->set_has_exit_right(true);
        }

        if (dy == 1) {
            o->set_has_exit_down(true);
            n->set_has_exit_up(true);
        }

        if (dy == -1) {
            o->set_has_exit_up(true);
            n->set_has_exit_down(true);
        }
    }
}

void Nodes::join_depth_secret (int depth, int pass)
{
    std::vector< std::pair<point, point> > s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->depth != depth) {
                continue;
            }
            if (o->pass && (o->pass != pass)) {
                continue;
            }

            if (pass == 1) {
                auto n = getn(x + 1, y);
                if (n && (n->pass == pass) && (n->depth > depth + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x + 1, y)));
                }

                n = getn(x - 1, y);
                if (n && (n->pass == pass) && (n->depth > depth + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x - 1, y)));
                }

                n = getn(x, y + 1);
                if (n && (n->pass == pass) && (n->depth > depth + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x, y + 1)));
                }

                n = getn(x, y - 1);
                if (n && (n->pass == pass) && (n->depth > depth + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x, y - 1)));
                }
            } else {
                auto n = getn(x + 1, y);
                if (n && (n->pass != pass) && (n->depth >= depth)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x + 1, y)));
                }

                n = getn(x - 1, y);
                if (n && (n->pass != pass) && (n->depth >= depth)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x - 1, y)));
                }

                n = getn(x, y + 1);
                if (n && (n->pass != pass) && (n->depth >= depth)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x, y + 1)));
                }

                n = getn(x, y - 1);
                if (n && (n->pass != pass) && (n->depth >= depth)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x, y - 1)));
                }
            }
        }
    }

    if (!s.size()) {
        return;
    }

    auto r = random_range(0, s.size());
    if (!r) {
        r = 1;
    }

    if (pass == 2) {
        r = s.size() / 2;
    }

    while (r--) {
        auto i = random_range(0, s.size());
        auto p = s[i];
        auto a = p.first;
        auto b = p.second;

        auto dx = b.x - a.x;
        auto dy = b.y - a.y;

        auto n = getn(b.x, b.y);
        if (!n) {
            DIE("no new pos");
        }
        auto o = getn(a.x, a.y);
        if (!o) {
            DIE("no old pos");
        }

        if (dx == 1) {
            o->set_has_secret_exit_right(true);
            n->set_has_secret_exit_left(true);
        }

        if (dx == -1) {
            o->set_has_secret_exit_left(true);
            n->set_has_secret_exit_right(true);
        }

        if (dy == 1) {
            o->set_has_secret_exit_down(true);
            n->set_has_secret_exit_up(true);
        }

        if (dy == -1) {
            o->set_has_secret_exit_up(true);
            n->set_has_secret_exit_down(true);
        }
    }
}

void Nodes::place_lock (int depth, int pass)
{
    std::vector<point> s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->pass != pass) {
                continue;
            }
            if (o->depth != depth) {
                continue;
            }

            auto n = getn(x + 1, y);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_right) {
                s.push_back(point(x, y));
            }
            n = getn(x - 1, y);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_left) {
                s.push_back(point(x, y));
            }
            n = getn(x, y - 1);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_up) {
                s.push_back(point(x, y));
            }
            n = getn(x, y + 1);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_down) {
                s.push_back(point(x, y));
            }
        }
    }

    if (!s.size()) {
        DIE("no lock placed for depth %d", depth);
        return;
    }

    auto i = random_range(0, s.size());
    auto p = s[i];
    auto n = getn(p.x, p.y);
    n->is_lock = true;
}

void Nodes::hide_other_locks (int depth, int pass)
{
    std::vector<point> s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->pass != pass) {
                continue;
            }
            if (o->depth != depth) {
                continue;
            }
            if (o->is_lock) {
                continue;
            }

            auto n = getn(x + 1, y);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_right) {
                o->set_has_exit_right(false);
                o->set_has_secret_exit_right(true);
                n->set_has_exit_left(false);
                n->set_has_secret_exit_left(true);
            }
            n = getn(x - 1, y);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_left) {
                o->set_has_exit_left(false);
                o->set_has_secret_exit_left(true);
                n->set_has_exit_right(false);
                n->set_has_secret_exit_right(true);
            }
            n = getn(x, y - 1);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_up) {
                o->set_has_exit_up(false);
                o->set_has_secret_exit_up(true);
                n->set_has_exit_down(false);
                n->set_has_secret_exit_down(true);
            }
            n = getn(x, y + 1);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_down) {
                o->set_has_exit_down(false);
                o->set_has_secret_exit_down(true);
                n->set_has_exit_up(false);
                n->set_has_secret_exit_up(true);
            }
        }
    }
}

bool Nodes::place_key (int depth, int pass)
{
    std::vector<point> s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->pass != pass) {
                continue;
            }
            if (o->depth != depth) {
                continue;
            }
            if (o->is_lock) {
                continue;
            }
            if (o->is_entrance) {
                continue;
            }
            if (o->is_exit) {
                continue;
            }
            if (!o->on_critical_path) {
                continue;
            }

            s.push_back(point(x, y));
        }
    }

    if (!s.size()) {
        debug("no key placed");
        CON("no key placed for depth %d", depth);
        return (false);
    }

    auto i = random_range(0, s.size());
    auto p = s[i];
    auto n = getn(p.x, p.y);
    n->is_key = true;
    return (true);
}

void Nodes::place_entrance (void)
{
    std::vector<point> s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < 1; y++) {
            auto o = getn(x, y);
            if (o->pass != 1) {
                continue;
            }
            if (o->depth != 1) {
                continue;
            }
            if (o->is_key) {
                continue;
            }
            if (o->is_lock) {
                continue;
            }
            if (o->is_entrance) {
                continue;
            }
            if (o->is_exit) {
                continue;
            }

            s.push_back(point(x, y));
        }
    }

    if (!s.size()) {
        DIE("no entrance");
        return;
    }

    auto i = random_range(0, s.size());
    auto p = s[i];
    auto n = getn(p.x, p.y);
    n->is_entrance = true;
}

void Nodes::place_exit (void)
{
    std::vector<point> s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->pass != 1) {
                continue;
            }

            if (o->is_key) {
                continue;
            }
            if (o->is_lock) {
                continue;
            }
            if (o->is_entrance) {
                continue;
            }
            if (o->is_exit) {
                continue;
            }

            if (o->depth == max_depth) {
                s.push_back(point(x, y));
            }
        }
    }

    if (!s.size()) {
        DIE("no exit");
        return;
    }

    auto i = random_range(0, s.size());
    auto p = s[i];
    auto n = getn(p.x, p.y);
    n->is_exit = true;
}

void Nodes::remove_stubs (void)
{
    std::vector<point> s;

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto node = getn(x, y);

            if (node->has_exit_down) {
                auto o = getn(x, y + 1);
                if (!o->has_exit_up) {
                    node->set_has_exit_down(false);
                }
            }
            if (node->has_exit_up) {
                auto o = getn(x, y - 1);
                if (!o->has_exit_down) {
                    node->set_has_exit_up(false);
                }
            }
            if (node->has_exit_right) {
                auto o = getn(x + 1, y);
                if (!o->has_exit_left) {
                    node->set_has_exit_right(false);
                }
            }
            if (node->has_exit_left) {
                auto o = getn(x - 1, y);
                if (!o->has_exit_right) {
                    node->set_has_exit_left(false);
                }
            }
            if (node->has_secret_exit_down) {
                auto o = getn(x, y + 1);
                if (!o->has_secret_exit_up) {
                    node->set_has_secret_exit_down(false);
                }
            }
            if (node->has_secret_exit_up) {
                auto o = getn(x, y - 1);
                if (!o->has_secret_exit_down) {
                    node->set_has_secret_exit_up(false);
                }
            }
            if (node->has_secret_exit_right) {
                auto o = getn(x + 1, y);
                if (!o->has_secret_exit_left) {
                    node->set_has_secret_exit_right(false);
                }
            }
            if (node->has_secret_exit_left) {
                auto o = getn(x - 1, y);
                if (!o->has_secret_exit_right) {
                    node->set_has_secret_exit_left(false);
                }
            }
        }
    }
}

void Nodes::dmap_print_walls (dmap *d)
{
    for (auto y = 0; y < nodes_height * 2 + 1; y++) {
        for (auto x = 0; x < nodes_width * 2 + 1; x++) {
            int16_t e = d->val[x][y];
            if (e == DMAP_IS_WALL) {
                printf("#");
                continue;
            }
            if (e == DMAP_IS_PASSABLE) {
                printf(".");
                continue;
            }

            if (e > 0) {
                printf("%d", e % 10);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void Nodes::create_path_to_exit (int pass)
{
    //
    // Choose start and end of the dmap
    //
    point start;
    point end;
    
    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            if (!n) {
                continue;
            }
            if (n->is_entrance) {
                start = point(x, y);
            }
            if (n->is_exit) {
                end = point(x, y);
            }
        }
    }
    
    dmap d;

    memset(&d, 0, sizeof(d));

    int minx, miny, maxx, maxy;
    
    minx = 0;
    miny = 0;
    maxx = nodes_width * 2 + 1;
    maxy = nodes_height * 2 + 1;
    
    //
    // Set up obstacles for the exit search
    //
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            d.val[x][y] = DMAP_IS_WALL;
        }
    }

    if (pass == 1) {
        for (auto y = 0; y < nodes_height; y++) {
            for (auto x = 0; x < nodes_width; x++) {
                auto n = getn(x, y);
                auto X = (x * 2) + 1;
                auto Y = (y * 2) + 1;
                if (n && node_is_a_room(n)) {
                    if (n->has_exit_up || n->has_secret_exit_up) {
                        d.val[X][Y-1] = DMAP_IS_PASSABLE;
                    }
                    if (n->has_exit_down || n->has_secret_exit_down) {
                        d.val[X][Y+1] = DMAP_IS_PASSABLE;
                    }
                    if (n->has_exit_right || n->has_secret_exit_right) {
                        d.val[X+1][Y] = DMAP_IS_PASSABLE;
                    }
                    if (n->has_exit_left || n->has_secret_exit_left) {
                        d.val[X-1][Y] = DMAP_IS_PASSABLE;
                    }
                    d.val[X][Y] = DMAP_IS_PASSABLE;
                } else {
                    d.val[X][Y] = DMAP_IS_WALL;
                }
            }
        }
    } else {
        for (auto y = 0; y < nodes_height; y++) {
            for (auto x = 0; x < nodes_width; x++) {
                auto n = getn(x, y);
                auto X = (x * 2) + 1;
                auto Y = (y * 2) + 1;
                if (n && node_is_a_room(n)) {
                    if (n->has_exit_up) {
                        d.val[X][Y-1] = DMAP_IS_PASSABLE;
                    }
                    if (n->has_exit_down) {
                        d.val[X][Y+1] = DMAP_IS_PASSABLE;
                    }
                    if (n->has_exit_right) {
                        d.val[X+1][Y] = DMAP_IS_PASSABLE;
                    }
                    if (n->has_exit_left) {
                        d.val[X-1][Y] = DMAP_IS_PASSABLE;
                    }
                    d.val[X][Y] = DMAP_IS_PASSABLE;
                } else {
                    d.val[X][Y] = DMAP_IS_WALL;
                }
            }
        }

    }
        
    d.val[end.x*2+1][end.y*2+1] = DMAP_IS_GOAL;
    d.val[start.x*2+1][start.y*2+1] = DMAP_IS_PASSABLE;

    point dmap_start(minx, miny);
    point dmap_end(maxx, maxy);
    dmap_process(&d, dmap_start, dmap_end);
    //dmap_print_walls(&d);

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            auto X = x*2 + 1;
            auto Y = y*2 + 1;
            
            if (n && node_is_a_room(n)) {
                if (d.val[X+1][Y] < d.val[X][Y]) {
                    auto o = getn(x+1, y);
                    if (o && node_is_a_room(o)) {
                        n->dir_up = false;
                        n->dir_down = false;
                        n->dir_left = false;
                        n->dir_right = false;
                        n->dir_right = true;
                    }
                }
                if (d.val[X-1][Y] < d.val[X][Y]) {
                    auto o = getn(x-1, y);
                    if (o && node_is_a_room(o)) {
                        n->dir_up = false;
                        n->dir_down = false;
                        n->dir_left = false;
                        n->dir_right = false;
                        n->dir_left = true;
                    }
                }
                if (d.val[X][Y+1] < d.val[X][Y]) {
                    auto o = getn(x, y+1);
                    if (o && node_is_a_room(o)) {
                        n->dir_up = false;
                        n->dir_down = false;
                        n->dir_left = false;
                        n->dir_right = false;
                        n->dir_down = true;
                    }
                }
                if (d.val[X][Y-1] < d.val[X][Y]) {
                    auto o = getn(x, y-1);
                    if (o && node_is_a_room(o)) {
                        n->dir_up = false;
                        n->dir_down = false;
                        n->dir_left = false;
                        n->dir_right = false;
                        n->dir_up = true;
                    }
                }
            }
        }
    }
}

void Nodes::create_path_lock_to_key (int depth)
{
    //
    // Choose start and end of the dmap
    //
    point start;
    point end;
    
    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            if (!n) {
                continue;
            }
            if (n->depth != depth) {
                continue;
            }
            if (n->is_key) {
                end = point(x, y);
            }
            if (n->is_lock) {
                start = point(x, y);
            }
        }
    }
    
    dmap d;

    memset(&d, 0, sizeof(d));

    int minx, miny, maxx, maxy;
    
    minx = 0;
    miny = 0;
    maxx = nodes_width * 2 + 1;
    maxy = nodes_height * 2 + 1;
    
    //
    // Set up obstacles for the exit search
    //
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            d.val[x][y] = DMAP_IS_WALL;
        }
    }

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            auto X = (x * 2) + 1;
            auto Y = (y * 2) + 1;
            if (n && (n->pass == 1) && 
                (n->depth == depth) && node_is_a_room(n)) {
                if (n->has_exit_up) {
                    d.val[X][Y-1] = DMAP_IS_PASSABLE;
                }
                if (n->has_exit_down) {
                    d.val[X][Y+1] = DMAP_IS_PASSABLE;
                }
                if (n->has_exit_right) {
                    d.val[X+1][Y] = DMAP_IS_PASSABLE;
                }
                if (n->has_exit_left) {
                    d.val[X-1][Y] = DMAP_IS_PASSABLE;
                }
                d.val[X][Y] = DMAP_IS_PASSABLE;
            } else {
                d.val[X][Y] = DMAP_IS_WALL;
            }
        }
    }
        
    d.val[end.x*2+1][end.y*2+1] = DMAP_IS_GOAL;
    d.val[start.x*2+1][start.y*2+1] = DMAP_IS_PASSABLE;

    point dmap_start(minx, miny);
    point dmap_end(maxx, maxy);
    dmap_process(&d, dmap_start, dmap_end);
    dmap_print_walls(&d);

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            auto X = x*2 + 1;
            auto Y = y*2 + 1;
            
            if (n && (n->depth == depth) && node_is_a_room(n)) {
                if (d.val[X+1][Y] < d.val[X][Y]) {
                    auto o = getn(x+1, y);
                    if (o && (o->depth == depth) && node_is_a_room(o)) {
                        n->dir_right = true;
                    }
                }
                if (d.val[X-1][Y] < d.val[X][Y]) {
                    auto o = getn(x-1, y);
                    if (o && (o->depth == depth) && node_is_a_room(o)) {
                        n->dir_left = true;
                    }
                }
                if (d.val[X][Y+1] < d.val[X][Y]) {
                    auto o = getn(x, y+1);
                    if (o && (o->depth == depth) && node_is_a_room(o)) {
                        n->dir_down = true;
                    }
                }
                if (d.val[X][Y-1] < d.val[X][Y]) {
                    auto o = getn(x, y-1);
                    if (o && (o->depth == depth) && node_is_a_room(o)) {
                        n->dir_up = true;
                    }
                }
            }
        }
    }
}

void Nodes::make_paths_off_critical_path_reachable (void)
{
    //
    // Choose start and end of the dmap
    //
    point start;
    point end;
    
    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            if (!n) {
                continue;
            }
            if (n->is_entrance) {
                start = point(x, y);
            }
            if (n->is_exit) {
                end = point(x, y);
            }
        }
    }
    
    int minx, miny, maxx, maxy;
    
    minx = 0;
    miny = 0;
    maxx = nodes_width * 2 + 1;
    maxy = nodes_height * 2 + 1;
    
    dmap d;
    memset(&d, 0, sizeof(d));

    //
    // Set up obstacles for the exit search
    //
    for (auto y = miny; y < maxy; y++) {
        for (auto x = minx; x < maxx; x++) {
            d.val[x][y] = DMAP_IS_WALL;
        }
    }

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);
            auto X = (x * 2) + 1;
            auto Y = (y * 2) + 1;

            if (node_is_a_room(n)) {
                if (n->has_exit_up) {
                    d.val[X][Y-1] = DMAP_IS_PASSABLE;
                }
                if (n->has_exit_down) {
                    d.val[X][Y+1] = DMAP_IS_PASSABLE;
                }
                if (n->has_exit_right) {
                    d.val[X+1][Y] = DMAP_IS_PASSABLE;
                }
                if (n->has_exit_left) {
                    d.val[X-1][Y] = DMAP_IS_PASSABLE;
                }
                d.val[X][Y] = DMAP_IS_PASSABLE;
            }
        }
    }

    point dmap_start(minx, miny);
    point dmap_end(maxx, maxy);

    start.x = (start.x * 2) + 1;
    start.y = (start.y * 2) + 1;
    end.x = (end.x * 2) + 1;
    end.y = (end.y * 2) + 1;

    d.val[end.x][end.y] = DMAP_IS_GOAL;
    d.val[start.x][start.y] = DMAP_IS_PASSABLE;

    dmap_process(&d, dmap_start, dmap_end);
    //dmap_print_walls(&d);

    bool on_critical_path[nodes_width][nodes_height];
    memset(on_critical_path, 0, sizeof(on_critical_path));

    auto p = dmap_solve(&d, start, end);
    for (auto c : p) {
        auto X = (c.x - 1) / 2;
        auto Y = (c.y - 1) / 2;

        if (X >= nodes_width) {
            DIE("bug");
        }
        if (Y >= nodes_height) {
            DIE("bug");
        }
        if (X < 0) {
            DIE("bug");
        }
        if (Y < 0) {
            DIE("bug");
        }

        on_critical_path[X][Y] = true;
        auto n = getn(X, Y);

        n->on_critical_path = true;
    }

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto n = getn(x, y);

            if (on_critical_path[x][y]) {
                continue;
            }

            if (!node_is_a_room(n)) {
                continue;
            }

            if (n->has_exit_up) {
                auto o = getn(x, y-1);
                if (o && (o->pass == n->pass)) {
                    n->dir_up = true;
                    o->dir_down = true;
                }
            }
            if (n->has_exit_down) {
                auto o = getn(x, y+1);
                if (o && (o->pass == n->pass)) {
                    n->dir_down = true;
                    o->dir_up = true;
                }
            }
            if (n->has_exit_right) {
                auto o = getn(x+1, y);
                if (o && (o->pass == n->pass)) {
                    n->dir_right = true;
                    o->dir_left = true;
                }
            }
            if (n->has_exit_left) {
                auto o = getn(x-1, y);
                if (o && (o->pass == n->pass)) {
                    n->dir_left = true;
                    o->dir_right = true;
                }
            }
        }
    }
}

void Nodes::set_max_depth (void)
{
    std::vector<point> s;
    auto max_depth_ = 0;
    auto max_vdepth_ = 0;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->pass != 1) {
                continue;
            }

            if (o->depth > max_depth_) {
                max_depth_ = o->depth;
            }
            if (y > max_vdepth_) {
                max_vdepth_ = y;
            }
        }
    }

    max_depth = max_depth_;
    max_vdepth = max_depth_;
}

class Nodes *grid_test (void)
{
    auto x = 1000 ;
    while (x--) {
        /* auto d = */ new Nodes(5, 5);

        continue;
//        return (d);
    }
        return (nullptr);
}
