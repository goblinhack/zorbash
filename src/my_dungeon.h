/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_game.h"
#include "my_point.h"
#include "my_tile.h"
#include "my_room.h"
#include "my_charmap.h"
#include "my_dmap.h"
#include "my_range.h"
#include "my_dungeon_grid.h"
#include "my_ascii.h"
#include <stack>
#include <list>
#include <algorithm>

static bool dungeon_debug = true;

class Grid {
public:
    Roomp node_rooms[GRID_WIDTH][GRID_HEIGHT] = {};

    Grid()
    {
        for (auto dy = 0; dy < GRID_HEIGHT; dy++) {
            for (auto dx = 0; dx < GRID_WIDTH; dx++) {
                node_rooms[dx][dy] = nullptr;
            }
        }
    }
};

class Dungeon {
public:
    //
    // The. Map.
    //
    std::vector<char>                         cells;

    int map_width                             {MAP_WIDTH};
    int map_height                            {MAP_HEIGHT};
    int map_depth                             {MAP_DEPTH};

    //
    // High level view of the map.
    //
    int grid_width                           {0};
    int grid_height                          {0};
    Nodes                                    *nodes;

    //
    // Root seed for the dungeon
    //
    uint32_t                                 seed;
    
    //
    // Room pointers on the above nodes map
    //
    Grid                                     grid {};

    void make_dungeon (void)
    {_
        //
        // Create the high level blueprint of the level layout
        //
        create_node_map();

        //
        // Reset the list of rooms we can place. We only place one of
        // each possible room once per level
        //
        reset_possible_rooms();

        solve(&grid);
        debug("created dungeon");
    }

    void debug (std::string s)
    {_
        //return;
        //dump();
        //LOG("dungeon (%u): %s", seed, s.c_str());
        LOG("dungeon (%u) %s", seed, s.c_str());
    }

    Dungeon (int map_width,
             int map_height,
             int grid_width,
             int grid_height,
             int seed) :
        map_width                  (map_width),
        map_height                 (map_height),
        grid_width                 (grid_width),
        grid_height                (grid_height),
        seed                       (seed)
    {_
        make_dungeon();
    }

    Dungeon ()
    {_
        make_dungeon();
    }

    int offset (const int x, const int y, const int z)
    {
        auto offset = (map_width * map_height) * z;
        offset += (map_width) * y;
        offset += x;

        return (offset);
    }

    int offset (const int x, const int y)
    {
        auto offset = (map_width) * y;
        offset += x;

        return (offset);
    }

    bool is_oob (const int x, const int y, const int z)
    {
        return ((x < 0) || (x >= map_width) ||
                (y < 0) || (y >= map_height) ||
                (z < 0) || (z >= map_depth));
    }

    bool is_oob (const int x, const int y)
    {
        return ((x < 0) || (x >= map_width) ||
                (y < 0) || (y >= map_height));
    }

    char *cell_addr (const int x, const int y, const int z)
    {
        if (is_oob(x, y, z)) {
            return (nullptr);
        }

        return (&cells[offset(x, y, z)]);
    }

    char *cell_addr_fast (const int x, const int y, const int z)
    {
        return (&cells[offset(x, y, z)]);
    }

    /*
     * Puts a tile on the map
     */
    void putc (const int x, const int y, const int z, const char c)
    {
        if (!c) {
            DIE("putting nul char at %d,%d,%d", x, y, z);
        }
        auto p = cell_addr(x, y, z);
        if (p != nullptr) {
            *p = c;
        }
    }
    
    /*
     * Puts a tile on the map
     */
    void putc_fast (const int x, const int y, const int z, const char c)
    {
        auto p = cell_addr_fast(x, y, z);
        if (p != nullptr) {
            *p = c;
        }
    }

    /*
     * Gets a tile of the map or None
     */
    char getc (const int x, const int y, const int z)
    {
        auto p = cell_addr(x, y, z);
        if (p != nullptr) {
            return (*p);
        }
        return (Charmap::NONE);
    }

    /*
     * Gets a tile of the map or None
     */
    char getc_fast (const int x, const int y, const int z)
    {
        auto p = cell_addr_fast(x, y, z);
        if (p != nullptr) {
            return (*p);
        }
        return (Charmap::NONE);
    }
    
    bool is_anything_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
                return true;
            }
        }
        return false;
    }

    bool is_anything_at (const int x, const int y, const int z)
    {
        auto c = getc(x, y, z);
        if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
            return true;
        }
        return false;
    }

    bool is_floor_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_floor) {
                return true;
            }
        }
        return false;
    }

    bool is_dusty_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_dusty) {
                return true;
            }
        }
        return false;
    }

    bool is_wall_at (const int x, const int y)
    {
        auto d = MAP_DEPTH_WALLS;
        auto c = getc(x, y, d);
        auto v = Charmap::all_charmaps[c];
        return (v.is_wall);
    }

    bool is_monst_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_monst) {
                return true;
            }
        }
        return false;
    }

    bool is_door_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_door) {
                return true;
            }
        }
        return false;
    }

    bool is_entrance_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_entrance) {
                return true;
            }
        }
        return false;
    }

    bool is_exit_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_exit) {
                return true;
            }
        }
        return false;
    }

    bool is_lava_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_lava) {
                return true;
            }
        }
        return false;
    }

    bool is_water_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_water) {
                return true;
            }
        }
        return false;
    }

    bool is_treasure_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_treasure) {
                return true;
            }
        }
        return false;
    }

    bool is_key_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_key) {
                return true;
            }
        }
        return false;
    }

    bool is_anything_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
                return true;
            }
        }
        return false;
    }

    bool is_anything_at_fast (const int x, const int y, const int z)
    {
        auto c = getc_fast(x, y, z);
        if ((c != Charmap::NONE) && (c != Charmap::SPACE)) {
            return true;
        }
        return false;
    }

    bool is_floor_at_fast (const int x, const int y)
    {
        const auto d = MAP_DEPTH_FLOOR;
        auto c = getc_fast(x, y, d);
        auto v = Charmap::all_charmaps[c];

        return (v.is_floor);
    }

    bool is_wall_at_fast (const int x, const int y)
    {
        auto d = MAP_DEPTH_WALLS;
        auto c = getc_fast(x, y, d);
        auto v = Charmap::all_charmaps[c];
        return (v.is_wall);
    }

    bool is_door_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_door) {
                return true;
            }
        }
        return false;
    }

    bool is_entrance_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_entrance) {
                return true;
            }
        }
        return false;
    }

    bool is_exit_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_exit) {
                return true;
            }
        }
        return false;
    }

    bool is_lava_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_lava) {
                return true;
            }
        }
        return false;
    }

    bool is_water_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_water) {
                return true;
            }
        }
        return false;
    }

    bool is_treasure_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_treasure) {
                return true;
            }
        }
        return false;
    }

    bool is_key_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_key) {
                return true;
            }
        }
        return false;
    }

    void create_node_map (void)
    {
        if (grid_width > GRID_WIDTH) {
            DIE("nodes width overflow. got %d, max %d",
                grid_width, GRID_WIDTH);
        }

        if (grid_height > GRID_HEIGHT) {
            DIE("nodes height overflow. got %d, max %d",
                grid_height, GRID_HEIGHT);
        }

        nodes = new Nodes(grid_width, grid_height);
    }

    void dump (void)
    {_
        if (!dungeon_debug) {
            return;
        }

        LOG("dungeon: seed %u", seed);
        for (auto y = 0; y < map_height; y++) {
            std::string s;
            for (auto x = 0; x < map_width; x++) {
                bool got_one = false;
                for (auto d = map_depth - 1; d >= 0; d--) {
                    if (!is_anything_at(x, y, d)) {
                        continue;
                    }

                    auto m = getc(x, y, d);
                    auto cr = Charmap::all_charmaps[m];
                    auto c = cr.c;

                    if (!c) {
                        DIE("unknown map char %c at %d,%d,%d", m, x, y, d);
                    }

                    if (!(x % 2) && !(y % 2)) {
                        if (!is_wall_at(x, y) && is_floor_at(x, y)) {
                            auto X = (x - MAP_BORDER) / ROOM_WIDTH;
                            auto Y = (y - MAP_BORDER) / ROOM_HEIGHT;
                            auto n = nodes->getn(X, Y);
                            if (n) {
                                c = '0' + n->depth;
                            }
                        }
                    }

                    if (!((x-MAP_BORDER) % ROOM_WIDTH) || 
                        !((y-MAP_BORDER) % ROOM_HEIGHT)) {
                        if (is_wall_at(x, y)) {
                            c = 'X';
                        }
                    }
                    
                    s += c;
                    got_one = true;
                    break;
                }
                if (!got_one) {
                    s += " ";
                }
            }
            if (s != "") {
                LOG("[%s]", s.c_str());
            }
        }
    }

    void reset_possible_rooms (void)
    {
        cells.resize(map_width * map_height * MAP_DEPTH,
                     Charmap::SPACE);

        std::fill(cells.begin(), cells.end(), Charmap::SPACE);
        
        for (auto r : Room::all_rooms) {
            r->placed = false;
        }
    }

    void room_print_at (Roomp r, int x, int y)
    {
        for (auto z = 0 ; z < MAP_DEPTH; z++) {
            for (auto dy = 0; dy < r->height; dy++) {
                for (auto dx = 0; dx < r->width; dx++) {
                    auto c = r->data[dx][dy][z];
                    if (c && (c != Charmap::SPACE)) {
                        putc(x + dx, y + dy, z, c);
                    }
                }
            }
        }
    }

    void rooms_print_all (Grid *g)
    {
        std::fill(cells.begin(), cells.end(), Charmap::SPACE);

        for (auto x = 0; x < grid_width; x++) {
            for (auto y = 0; y < grid_height; y++) {
                Roomp r = g->node_rooms[x][y];
                if (r) {
                    room_print_at(r, 
                                  x * ROOM_WIDTH + MAP_BORDER, 
                                  y * ROOM_HEIGHT + MAP_BORDER);
                }
            }
        }
        dump();
    }

    bool room_is_a_candidate (const Node *n, Roomp r)
    {
        if (n->has_exit_up != r->has_exit_up) { 
            return (false); 
        }
        if (n->has_exit_down != r->has_exit_down) { 
            return (false); 
        }
        if (n->has_exit_left != r->has_exit_left) { 
            return (false); 
        }
        if (n->has_exit_right != r->has_exit_right) { 
            return (false); 
        }
        if (n->dir_left != r->dir_left) {
            return (false);
        }
        if (n->dir_right != r->dir_right) {
            return (false);
        }
        if (n->dir_up != r->dir_up) {
            return (false);
        }
        if (n->dir_down != r->dir_down) {
            return (false);
        }
        if (n->is_exit != r->is_exit) {
            return (false);
        }
        if (n->is_entrance != r->is_entrance) {
            return (false);
        }
        if (n->is_lock != r->is_lock) {
            return (false);
        }
        if (n->is_key != r->is_key) {
            return (false);
        }
        if (n->is_secret != r->is_secret) {
            return (false);
        }
        if (n->depth != r->depth) {
            return (false);
        }
        return (true);
    }

    bool room_is_a_candidate_less_restrictive (const Node *n, Roomp r)
    {
        if (n->has_exit_up != r->has_exit_up) { 
            return (false); 
        }
        if (n->has_exit_down != r->has_exit_down) { 
            return (false); 
        }
        if (n->has_exit_left != r->has_exit_left) { 
            return (false); 
        }
        if (n->has_exit_right != r->has_exit_right) { 
            return (false); 
        }
        if (r->dir_left) {
            return (false);
        }
        if (r->dir_right) {
            return (false);
        }
        if (r->dir_up) {
            return (false);
        }
        if (r->dir_down) {
            return (false);
        }
        if (n->is_exit != r->is_exit) {
            return (false);
        }
        if (n->is_entrance != r->is_entrance) {
            return (false);
        }
        if (n->is_lock != r->is_lock) {
            return (false);
        }
        if (n->is_key != r->is_key) {
            return (false);
        }
        return (true);
    }

    bool room_is_a_candidate_less_restrictive2 (const Node *n, Roomp r)
    {
        if (n->has_exit_up != r->has_exit_up) { 
            return (false); 
        }
        if (n->has_exit_down != r->has_exit_down) { 
            return (false); 
        }
        if (n->has_exit_left != r->has_exit_left) { 
            return (false); 
        }
        if (n->has_exit_right != r->has_exit_right) { 
            return (false); 
        }
        if (r->dir_left) {
            return (false);
        }
        if (r->dir_right) {
            return (false);
        }
        if (r->dir_up) {
            return (false);
        }
        if (r->dir_down) {
            return (false);
        }
        if (n->is_exit != r->is_exit) {
            return (false);
        }
        if (n->is_entrance != r->is_entrance) {
            return (false);
        }
        if (n->is_lock != r->is_lock) {
            return (false);
        }
        if (n->is_key != r->is_key) {
            return (false);
        }
        return (true);
    }

    bool room_fits_existing_rooms (Grid *g, Node *n, Roomp r, int x, int y)
    {
        if (n->has_exit_down) {
            auto o = g->node_rooms[x][y+1];
            if (o && !(r->down_exits & o->up_exits)) {
                return (false);
            }
        }
        if (n->has_exit_up) {
            auto o = g->node_rooms[x][y-1];
            if (o && !(r->up_exits & o->down_exits)) {
                return (false);
            }
        }
        if (n->has_exit_right) {
            auto o = g->node_rooms[x+1][y];
            if (o && !(r->right_exits & o->left_exits)) {
                return (false);
            }
        }
        if (n->has_exit_left) {
            auto o = g->node_rooms[x-1][y];
            if (o && !(r->left_exits & o->right_exits)) {
                return (false);
            }
        }
        return (true);
    }

    bool solve (int x, int y, Grid *g)
    {
        auto n = nodes->getn(x, y);

        if (!nodes->node_is_a_room(n)) {
            return (true);
        }

        if (g->node_rooms[x][y]) {
            return (true);
        }

        std::vector<Roomp> candidates;

        for (auto r : Room::all_rooms) {
            if (!room_is_a_candidate(n, r)) {
                continue;
            }

            if (!room_fits_existing_rooms(g, n, r, x, y)) {
                continue;
            }
            candidates.push_back(r);
        }

        auto ncandidates = candidates.size();
	if (!ncandidates) {
            for (auto r : Room::all_rooms) {
                if (!room_is_a_candidate_less_restrictive(n, r)) {
                    continue;
                }

                if (!room_fits_existing_rooms(g, n, r, x, y)) {
                    continue;
                }
                candidates.push_back(r);
            }

            ncandidates = candidates.size();
            if (!ncandidates) {
                for (auto r : Room::all_rooms) {
                    if (!room_is_a_candidate_less_restrictive2(n, r)) {
                        continue;
                    }

                    if (!room_fits_existing_rooms(g, n, r, x, y)) {
                        continue;
                    }
                    candidates.push_back(r);
                }

                ncandidates = candidates.size();
                if (!ncandidates) {
                    rooms_print_all(g);
                    DIE("no grid room candidates at %d %d",x, y);
                    return (false);
                }
            }
	}

        auto r = candidates[random_range(0, ncandidates)];
        g->node_rooms[x][y] = r;
        
        if (n->has_exit_down) {
            Grid old = *g;
            if (!solve(x, y+1, g)) {
                *g = old;
            }
        }
        if (n->has_exit_up) {
            Grid old = *g;
            if (!solve(x, y-1, g)) {
                *g = old;
            }
        }
        if (n->has_exit_right) {
            Grid old = *g;
            if (!solve(x+1, y, g)) {
                *g = old;
            }
        }
        if (n->has_exit_left) {
            Grid old = *g;
            if (!solve(x-1, y, g)) {
                *g = old;
            }
        }
        return (true);
    }

    bool solve (Grid *g)
    {
        for (auto x = 0; x < grid_width; x++) {
            for (auto y = 0; y < grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (!n->is_entrance) {
                    continue;
                }
                if (!solve(x, y, g)) {
                    dump();
                    DIE("could not solve level at %d,%d", x, y);
                }
                break;
            }
        }

        for (auto x = 0; x < grid_width; x++) {
            for (auto y = 0; y < grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (!n->is_secret) {
                    continue;
                }
                solve(x, y, g);
            }
        }

        rooms_print_all(g);

        return (true);
    }
};
