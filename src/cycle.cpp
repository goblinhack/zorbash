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
    /*
     * Not necessarily an actual key or lock, but something allowing access
     * to the other node. Only one key per node level.
     */
    bool is_key                               {false};
    bool is_lock                              {false};
    bool is_entrance                          {false};
    bool is_exit                              {false};
    bool is_up                                {false};
    bool is_down                              {false};
    bool is_left                              {false};
    bool is_right                             {false};
};

class Nodes {
public:
    std::vector<Node>                         nodes;
    int nodes_width                           {5};
    int nodes_height                          {5};

    void finish_constructor (void)
    {_
        nodes.resize(nodes_width * nodes_height);

        auto n = getn(1, 1);
        n->level = 1;
        n->is_exit = true;
        n->is_down = true;

        n = getn(3, 3);
        n->level = 2;
        n->is_exit = true;
        n->is_up = true;
        n->is_right = true;

        n = getn(3, 4);
        n->level = 3;
        n->is_exit = true;
        n->is_up = true;
        n->is_right = true;

        debug("test");
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
                if (node->is_down) {
                    out[oy+1][ox] = '|';
                    out[oy+2][ox] = '|';
                    out[oy+3][ox] = '|';
                }
                if (node->is_up) {
                    out[oy-1][ox] = '|';
                    out[oy-2][ox] = '|';
                    out[oy-3][ox] = '|';
                }
                if (node->is_left) {
                    out[oy][ox-1] = '_';
                    out[oy][ox-2] = '_';
                    out[oy][ox-3] = '_';
                }
                if (node->is_right) {
                    out[oy][ox+1] = '_';
                    out[oy][ox+2] = '_';
                    out[oy][ox+3] = '_';
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
            DIE("out of bounds on node map %d,%d vs size %d,%d", 
                x, y, nodes_width, nodes_height);
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
};

class Nodes *grid_test (void)
{
    for (;;) {
        auto d = new Nodes(5, 5);

        return (d);
    }
}
