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
        auto placed = snake_walk(depth, 10, pass);

        CON("depth %d placed %d nodes", depth, placed);
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
            if (placed < 3) {
                debug("failed initial level");
                LOG("depth %d placed only %d nodes, redo", depth, placed);
                goto redo;
            }
        } else {
            if (placed < 2) {
                debug("failed level");
                LOG("depth %d placed only %d nodes, redo", depth, placed);
                goto redo;
            }
        }

        join_nodes_of_same_depth(depth, pass);
        depth++;
    }

    for (auto join = 1; join < depth - 1; join++) {
        join_depth_to_next_depth(join, pass);
    }
    for (auto join = 1; join < depth - 2; join++) {
        join_depth_secret(join, pass);
    }
    debug("done first pass of rooms");

    //
    // Now place secret rooms and join them to the main
    // depth via secret doors
    //
    pass = 2;
    auto secret_depth = 1;
    while (secret_depth < 10) {
        auto placed = snake_walk(secret_depth, 10, pass);

        CON("depth %d placecd %d secret nodes", secret_depth, placed);
        if (!placed) {
            break;
        }

        join_nodes_of_same_depth(secret_depth, pass);
        secret_depth++;
    }

    for (auto join = 1; join < depth; join++) {
        join_depth_to_next_depth(join, pass);
    }
    for (auto join = 1; join < depth; join++) {
        join_depth_secret(join, pass);
    }

    debug("done second pass of secret rooms");

    set_max_depth();

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
        place_key(depth, 1);
    }

    //
    // Add start and exit
    //
    place_entrance();
    place_exit();

    debug("placed exits");
}

void Nodes::debug (std::string msg)
{_
    if (!debug_enabled) {
        return;
    }

    auto step = 7;
    auto center = 3;

    char out[nodes_height * step][nodes_width * step];

    memset(out, ' ', sizeof(out));

    for (auto y = 0; y < nodes_height; y++) {
        for (auto x = 0; x < nodes_width; x++) {
            auto ox = (x * step) + center;
            auto oy = (y * step) + center;
            auto node = getn(x, y);
            if (node->has_exit_down) {
                out[oy+1][ox] = '|';
                out[oy+2][ox] = '|';
                out[oy+3][ox] = '|';
            }
            if (node->has_exit_up) {
                out[oy-1][ox] = '|';
                out[oy-2][ox] = '|';
                out[oy-3][ox] = '|';
            }
            if (node->has_exit_left) {
                out[oy][ox-1] = '_';
                out[oy][ox-2] = '_';
                out[oy][ox-3] = '_';
            }
            if (node->has_exit_right) {
                out[oy][ox+1] = '_';
                out[oy][ox+2] = '_';
                out[oy][ox+3] = '_';
            }
            if (node->has_exit_secret_down) {
                out[oy+1][ox] = '?';
                out[oy+2][ox] = ' ';
                out[oy+3][ox] = '?';
            }
            if (node->has_exit_secret_up) {
                out[oy-1][ox] = '?';
                out[oy-2][ox] = ' ';
                out[oy-3][ox] = '?';
            }
            if (node->has_exit_secret_left) {
                out[oy][ox-1] = '?';
                out[oy][ox-2] = ' ';
                out[oy][ox-3] = '?';
            }
            if (node->has_exit_secret_right) {
                out[oy][ox+1] = '?';
                out[oy][ox+2] = ' ';
                out[oy][ox+3] = '?';
            }
            if (node->is_entrance) {
                out[oy-1][ox-1] = 'S';
            }
            if (node->is_exit) {
                out[oy-1][ox-1] = 'E';
            }
            if (node->is_lock) {
                out[oy-1][ox-1] = 'D';
            }
            if (node->is_key) {
                out[oy-1][ox-1] = 'K';
            }

            if (node->depth == depth_obstacle) {
                out[oy][ox] = '-';
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
        CON("cyclic-dungeon: %s", s.c_str());
    }
    CON("cyclic-dungeon: ^^^^^ %s ^^^^^", msg.c_str());
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
            memset(n, 0, sizeof(*n));
        }
    }

    auto obstacles = random_range(0, (nodes_width * nodes_height) / 2);
    if (obstacles < 3) {
        obstacles = 3;
    }

    while (obstacles--) {
        auto x = random_range(0, nodes_width);
        auto y = random_range(0, nodes_height);

        auto o = getn(x, y);
        o->depth = depth_obstacle;
    }
}

//
// Walk the depth randomly, ala snake until you hit your own tail,
// forking randomly also
//
int Nodes::snake_walk (int depth, int max_placed, int pass)
{
    std::list<point> s;

    auto dx = 0;
    auto dy = 0;
    auto x = 0;
    auto y = 0;

    if (depth == 1) {
        //
        // Start anywhere
        //
        auto tries = 1000;
        while (tries--) {
            x = random_range(0, nodes_width);
            y = random_range(0, nodes_height);

            auto o = getn(x, y);
            if (o && !o->depth) {
                s.push_back(point(x, y));
                random_dir(&dx, &dy);
                break;
            }
        }

        if (tries < 0) {
            return (0);
        }
    } else {
        //
        // Else start adjacent next to the old depth
        //
        auto tries = 1000;
        while (tries--) {
            x = random_range(0, nodes_width);
            y = random_range(0, nodes_height);
            random_dir(&dx, &dy);

            auto o = getn(x, y);
            auto n = getn(x + dx, y + dy);

            if (o && !o->depth && n && (n->pass == pass) && (n->depth == depth - 1)) {
                s.push_back(point(x, y));
                break;
            }
        }

        if (tries < 0) {
            return (0);
        }
    }

    auto placed = 0;

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
        if (random_range(0, 100) < 30) {
            switch (random_range(0, 4)) {
                random_dir(&dx, &dy);
            }
        }

        //
        // Create forks but make sure the old corridor knows
        // where the fork corridor is
        //
        if (random_range(0, 100) < 10) {
            switch (random_range(0, 4)) {
                case 0: 
                    s.push_back(point(x + 1, y    )); 
                    n->has_exit_right = true;
                    break;
                case 1: 
                    s.push_back(point(x - 1, y    ));
                    n->has_exit_left = true;
                    break;
                case 2: 
                    s.push_back(point(x    , y + 1));
                    n->has_exit_down = true;
                    break;
                case 3: 
                    s.push_back(point(x    , y - 1));
                    n->has_exit_up = true;
                    break;
            }
        }

        auto o = n;

        //
        // Get the next moved, or change dir again if blocked.
        //
        n = getn(x + dx, y + dy);
        if (!n || n->depth) {
            auto tries = 5;
            while (tries--) {
                random_dir(&dx, &dy);
                n = getn(x + dx, y + dy);
                if (n && !n->depth) {
                    break;
                }
            }

            if (tries < 0) {
                continue;
            }
        }

        s.push_back(point(x + dx, y + dy));

        if (dx == 1) {
            o->has_exit_right = true;
        }
        if (dx == -1) {
            o->has_exit_left = true;
        }
        if (dy == 1) {
            o->has_exit_down = true;
        }
        if (dy == -1) {
            o->has_exit_up = true;
        }

    } while (s.size() && (placed < max_placed));

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
                    n->has_exit_left = true;
                } else {
                    o->has_exit_right = false;
                }
            }

            if (o->has_exit_left) {
                auto n = getn(x - 1, y);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->has_exit_right = true;
                } else {
                    o->has_exit_left = false;
                }
            }

            if (o->has_exit_down) {
                auto n = getn(x, y + 1);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->has_exit_up = true;
                } else {
                    o->has_exit_down = false;
                }
            }

            if (o->has_exit_up) {
                auto n = getn(x, y - 1);
                if (n && (n->pass == pass) && (n->depth == depth)) {
                    n->has_exit_down = true;
                } else {
                    o->has_exit_up = false;
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
                    std::make_pair(point(x, y), point(x + 1 , y)));
            }

            n = getn(x - 1, y);
            if (n && (n->pass == pass) && (n->depth == depth + 1)) {
                s.push_back(
                    std::make_pair(point(x, y), point(x - 1 , y)));
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
            o->has_exit_right = true;
            n->has_exit_left = true;
        }

        if (dx == -1) {
            o->has_exit_left = true;
            n->has_exit_right = true;
        }

        if (dy == 1) {
            o->has_exit_down = true;
            n->has_exit_up = true;
        }

        if (dy == -1) {
            o->has_exit_up = true;
            n->has_exit_down = true;
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
                        std::make_pair(point(x, y), point(x + 1 , y)));
                }

                n = getn(x - 1, y);
                if (n && (n->pass == pass) && (n->depth > depth + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x - 1 , y)));
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
                        std::make_pair(point(x, y), point(x + 1 , y)));
                }

                n = getn(x - 1, y);
                if (n && (n->pass != pass) && (n->depth >= depth)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x - 1 , y)));
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
            o->has_exit_secret_right = true;
            n->has_exit_secret_left = true;
        }

        if (dx == -1) {
            o->has_exit_secret_left = true;
            n->has_exit_secret_right = true;
        }

        if (dy == 1) {
            o->has_exit_secret_down = true;
            n->has_exit_secret_up = true;
        }

        if (dy == -1) {
            o->has_exit_secret_up = true;
            n->has_exit_secret_down = true;
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
                o->has_exit_right = false;
                o->has_exit_secret_right = true;
                n->has_exit_left = false;
                n->has_exit_secret_left = true;
            }
            n = getn(x - 1, y);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_left) {
                o->has_exit_left = false;
                o->has_exit_secret_left = true;
                n->has_exit_right = false;
                n->has_exit_secret_right = true;
            }
            n = getn(x, y - 1);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_up) {
                o->has_exit_up = false;
                o->has_exit_secret_up = true;
                n->has_exit_down = false;
                n->has_exit_secret_down = true;
            }
            n = getn(x, y + 1);
            if (n && (n->pass == pass) && (n->depth == depth - 1) &&
                o->has_exit_down) {
                o->has_exit_down = false;
                o->has_exit_secret_down = true;
                n->has_exit_up = false;
                n->has_exit_secret_up = true;
            }
        }
    }
}

void Nodes::place_key (int depth, int pass)
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

            s.push_back(point(x, y));
        }
    }

    if (!s.size()) {
        DIE("no key placed for depth %d", depth);
        return;
    }

    auto i = random_range(0, s.size());
    auto p = s[i];
    auto n = getn(p.x, p.y);
    n->is_key = true;
}

void Nodes::place_entrance (void)
{
    std::vector<point> s;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
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

void Nodes::set_max_depth (void)
{
    std::vector<point> s;
    auto max_depth_ = 0;

    for (auto x = 0; x < nodes_width; x++) {
        for (auto y = 0; y < nodes_height; y++) {
            auto o = getn(x, y);
            if (o->pass != 1) {
                continue;
            }

            if (o->depth > max_depth_) {
                max_depth_ = o->depth;
            }
        }
    }
    max_depth = max_depth_;
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
