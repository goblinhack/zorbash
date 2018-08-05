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
 * The above is level 1 of our loop. Choose an adjacent node for level 2
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
 * Repeat for level 3
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
 * Place a key room one per level. A key need not be a real key, but
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

class Node {
public:
    /*
     * Nodes have a level number, optional key, start and exit and corridors
     * to adjoining levels.
     */
    int level                                 {0};
    int pass                                  {0};
    int x, y;
    /*
     * Not necessarily an actual key or lock, but something allowing access
     * to the other node. Only one key per node level.
     */
    bool is_key                               {false};
    bool is_lock                              {false};
    bool is_entrance                          {false};
    bool is_exit                              {false};
    bool has_exit_up                          {false};
    bool has_exit_down                        {false};
    bool has_exit_left                        {false};
    bool has_exit_right                       {false};
    bool has_exit_secret_up                   {false};
    bool has_exit_secret_down                 {false};
    bool has_exit_secret_left                 {false};
    bool has_exit_secret_right                {false};
};

class Nodes {
public:
    std::vector<Node>                         nodes;
    int nodes_width                           {5};
    int nodes_height                          {5};

    void finish_constructor (void)
    {_
        init_nodes();

        auto pass = 1;
        auto level = 1;
        while (level < 10) {
            auto placed = snake_walk(level, 10, pass);

            CON("level %d placecd %d nodes", level, placed);
            if (!placed) {
                break;
            }

            join_nodes_of_same_level(level, pass);
            level++;
        }

        for (auto join = 1; join < level - 1; join++) {
            join_level_to_next_level(join, pass);
        }
        for (auto join = 1; join < level - 2; join++) {
            join_level_secret(join, pass);
        }
        debug("done first pass of rooms");

        pass = 2;
        auto secret_level = 1;
        while (secret_level < 10) {
            auto placed = snake_walk(secret_level, 10, pass);

            CON("level %d placecd %d secret nodes", secret_level, placed);
            if (!placed) {
                break;
            }

            join_nodes_of_same_level(secret_level, pass);
            secret_level++;
        }

        for (auto join = 1; join < level; join++) {
            join_level_to_next_level(join, pass);
        }
        for (auto join = 1; join < level; join++) {
            join_level_secret(join, pass);
        }

        debug("done second pass of secret rooms");
    }

    Nodes (int nodes_width, int nodes_height) :
        nodes_width                  (nodes_width),
        nodes_height                 (nodes_height)
    {_
        finish_constructor();
    }

    Nodes ()
    {_
        finish_constructor();
    }

    void debug (std::string msg)
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

                if (node->level) {
                    out[oy][ox] = '0' + node->level;
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

    int offset (const int x, const int y)
    {_
        auto offset = nodes_width * y;
        offset += x;

        return (offset);
    }

    bool is_oob (const int x, const int y)
    {_
        return ((x < 0) || (x >= nodes_width) ||
                (y < 0) || (y >= nodes_height));
    }

    Node *node_addr (const int x, const int y)
    {_
        if (is_oob(x, y)) {
            return (nullptr);
        }

        return (&nodes[offset(x, y)]);
    }

    void putn (const int x, const int y, const Node n)
    {_
        auto p = node_addr(x, y);
        if (p != nullptr) {
            *p = n;
        }
    }

    Node *getn (const int x, const int y)
    {_
        auto p = node_addr(x, y);
        return (p);
    }

    point random_dir (void)
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

    void random_dir (int *dx, int *dy)
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
    void init_nodes (void)
    {
        nodes.resize(nodes_width * nodes_height);

        std::vector< std::pair<point, point> > s;

        for (auto x = 0; x < nodes_width; x++) {
            for (auto y = 0; y < nodes_height; y++) {

                auto n = getn(x, y);
                n->x = x;
                n->y = y;
                n->level = 0;
                n->pass = 0;
            }
        }
    }

    //
    // Walk the level randomly, ala snake until you hit your own tail,
    // forking randomly also
    //
    int snake_walk (int level, int max_placed, int pass)
    {
        std::list<point> s;

        auto dx = 0;
        auto dy = 0;
        auto x = 0;
        auto y = 0;

        if (level == 1) {
            //
            // Start anywhere
            //
            auto tries = 1000;
            while (tries--) {
                x = random_range(0, nodes_width);
                y = random_range(0, nodes_height);

                auto o = getn(x, y);
                if (o && !o->level) {
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
            // Else start adjacent next to the old level
            //
            auto tries = 1000;
            while (tries--) {
                x = random_range(0, nodes_width);
                y = random_range(0, nodes_height);
                random_dir(&dx, &dy);

                auto o = getn(x, y);
                auto n = getn(x + dx, y + dy);

                if (o && !o->level && n && (n->pass == pass) && (n->level == level - 1)) {
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
            if (!n || n->level) {
                continue;
            }

            if (n->pass && (n->pass != pass)) {
                continue;
            }

            placed++;
            n->level = level;
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

            auto o = n;

            //
            // Get the next moved, or change dir again if blocked.
            //
            n = getn(x + dx, y + dy);
            if (!n || n->level) {
                auto tries = 20;
                while (tries--) {
                    random_dir(&dx, &dy);
                    n = getn(x + dx, y + dy);
                    if (n && !n->level) {
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

    void join_nodes_of_same_level (int level, int pass)
    {
        //
        // Connect up the nodes on the same level
        //
        for (auto x = 0; x < nodes_width; x++) {
            for (auto y = 0; y < nodes_height; y++) {
                auto o = getn(x, y);
                if (o->level != level) {
                    continue;
                }

                if (o->pass && (o->pass != pass)) {
                    continue;
                }

                if (o->has_exit_right) {
                    auto n = getn(x + 1, y);
                    if (n && (n->pass == pass) && (n->level == level)) {
                        n->has_exit_left = true;
                    } else {
                        o->has_exit_right = false;
                    }
                }

                if (o->has_exit_left) {
                    auto n = getn(x - 1, y);
                    if (n && (n->pass == pass) && (n->level == level)) {
                        n->has_exit_right = true;
                    } else {
                        o->has_exit_left = false;
                    }
                }

                if (o->has_exit_down) {
                    auto n = getn(x, y + 1);
                    if (n && (n->pass == pass) && (n->level == level)) {
                        n->has_exit_up = true;
                    } else {
                        o->has_exit_down = false;
                    }
                }

                if (o->has_exit_up) {
                    auto n = getn(x, y - 1);
                    if (n && (n->pass == pass) && (n->level == level)) {
                        n->has_exit_down = true;
                    } else {
                        o->has_exit_up = false;
                    }
                }
            }
        }
    }

    //
    // Connect up the nodes to the next level. We need at least one.
    //
    void join_level_to_next_level (int level, int pass)
    {
        std::vector< std::pair<point, point> > s;

        for (auto x = 0; x < nodes_width; x++) {
            for (auto y = 0; y < nodes_height; y++) {
                auto o = getn(x, y);
                if (o->level != level) {
                    continue;
                }
                if (o->pass && (o->pass != pass)) {
                    continue;
                }

                auto n = getn(x + 1, y);
                if (n && (n->pass == pass) && (n->level == level + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x + 1 , y)));
                }

                n = getn(x - 1, y);
                if (n && (n->pass == pass) && (n->level == level + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x - 1 , y)));
                }

                n = getn(x, y + 1);
                if (n && (n->pass == pass) && (n->level == level + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x, y + 1)));
                }

                n = getn(x, y - 1);
                if (n && (n->pass == pass) && (n->level == level + 1)) {
                    s.push_back(
                        std::make_pair(point(x, y), point(x, y - 1)));
                }
            }
        }

        if (!s.size()) {
            if (pass == 1) {
                debug("error");
                DIE("no exits from %d to %d", level, level + 1);
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

    void join_level_secret (int level, int pass)
    {
        std::vector< std::pair<point, point> > s;

        for (auto x = 0; x < nodes_width; x++) {
            for (auto y = 0; y < nodes_height; y++) {
                auto o = getn(x, y);
                if (o->level != level) {
                    continue;
                }
                if (o->pass && (o->pass != pass)) {
                    continue;
                }

                if (pass == 1) {
                    auto n = getn(x + 1, y);
                    if (n && (n->pass == pass) && (n->level > level + 1)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x + 1 , y)));
                    }

                    n = getn(x - 1, y);
                    if (n && (n->pass == pass) && (n->level > level + 1)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x - 1 , y)));
                    }

                    n = getn(x, y + 1);
                    if (n && (n->pass == pass) && (n->level > level + 1)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x, y + 1)));
                    }

                    n = getn(x, y - 1);
                    if (n && (n->pass == pass) && (n->level > level + 1)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x, y - 1)));
                    }
                } else {
                    auto n = getn(x + 1, y);
                    if (n && (n->pass != pass) && (n->level >= level)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x + 1 , y)));
                    }

                    n = getn(x - 1, y);
                    if (n && (n->pass != pass) && (n->level >= level)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x - 1 , y)));
                    }

                    n = getn(x, y + 1);
                    if (n && (n->pass != pass) && (n->level >= level)) {
                        s.push_back(
                            std::make_pair(point(x, y), point(x, y + 1)));
                    }

                    n = getn(x, y - 1);
                    if (n && (n->pass != pass) && (n->level >= level)) {
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
};

class Nodes *grid_test (void)
{
    for (;;) {
        auto d = new Nodes(5, 5);

        return (d);
    }
}
