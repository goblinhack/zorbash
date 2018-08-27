/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
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
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

static bool dungeon_debug = true;

class Dungeon {
public:
    //
    // The. Map.
    //
    std::vector<char>                         cells;

    int map_width                             {MAP_WIDTH};
    int map_height                            {MAP_HEIGHT};
    int map_depth                             {Charmap::DEPTH_MAX};

    //
    // High level view of the map.
    //
    int grid_width                           {0};
    int grid_height                          {0};
    Nodes                                     *nodes;

    //
    // Root seed for the dungeon
    //
    uint32_t                                  seed;
    
    //
    // Room pointers on the above nodes map
    //
    Roomp                                     node_rooms[GRID_WIDTH]
                                                        [GRID_HEIGHT];

    void make_dungeon (void)
    {_
        //
        // Create the high level blueprint of the level layout
        //
        create_node_map();

        for (;;) {
            //
            // Reset the list of rooms we can place. We only place one of
            // each possible room once per level
            //
            reset_possible_rooms();

            DIE("x");
            debug("failed, redo from scratch");
        }
        
        debug("success, created dungeon");
    }

    void debug (std::string s)
    {_
        //return;
        //dump();
        //CON("dungeon (%u): %s", seed, s.c_str());
        CON("dungeon (%u) %s: hash %llx", seed, s.c_str(), level_hash());
    }

    Dungeon (int map_width,
             int map_height,
             int grid_width,
             int grid_height,
             int seed) :
        map_width                  (map_width),
        map_height                 (map_height),
        grid_width                (grid_width),
        grid_height               (grid_height),
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
        auto d = Charmap::DEPTH_WALLS;
        auto c = getc(x, y, d);
        auto v = Charmap::all_charmaps[c];
        return (v.is_wall);
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

    bool is_movement_blocking_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_wall             ||
                v.is_treasure         ||
                v.is_exit ||
                v.is_entrance   ||
                v.is_door) {
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
        const auto d = Charmap::DEPTH_FLOOR;
        auto c = getc_fast(x, y, d);
        auto v = Charmap::all_charmaps[c];

        return (v.is_floor);
    }

    bool is_wall_at_fast (const int x, const int y)
    {
        auto d = Charmap::DEPTH_WALLS;
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

    bool is_movement_blocking_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_wall             ||
                v.is_treasure         ||
                v.is_exit ||
                v.is_entrance   ||
                v.is_door) {
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

        CON("dungeon: seed %u", seed);
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
                            Roomp r = node_rooms[x][y];
                            if (r) {
                                c = '0' + r->depth;
                            }
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
            CON("%s", s.c_str());
        }
    }

    uint64_t level_hash (void)
    {_
        uint64_t h = 0;

        for (auto y = 0; y < map_height; y++) {
            for (auto x = 0; x < map_width; x++) {
                for (auto d = map_depth - 1; d >= 0; d--) {
                    auto m = getc(x, y, d);
                    auto cr = Charmap::all_charmaps[m];
                    auto c = cr.c;

                    h += (c - 32) * x * y;
                    h--;
                }
            }
        }
        return (h);
    }

    //
    // Dump a room onto the level. No checks
    //
    void map_place_room_chars (Roomp room, int x, int y)
    {
        for (auto z = 0 ; z < Charmap::DEPTH_MAX; z++) {
            for (auto dy = 0; dy < room->height; dy++) {
                for (auto dx = 0; dx < room->width; dx++) {
                    auto c = room->data[dx][dy][z];
                    if (c != Charmap::SPACE) {
                        putc_fast(x + dx, y + dy, z, c);
                    }
                }
            }
        }
    }
    
    //
    // From a fixed list of random roomnos, return the next one. This
    // ensures no room will ever appear more than once.
    //
    Roomp get_next_room (int node_x, int node_y)
    {
        auto n = nodes->getn(node_x, node_y);

        auto tries = 100000;
        while (tries-- > 0) {
            auto ri = random_range(0, Room::all_rooms.size());
            auto r = Room::all_rooms[ri];
            
            if (r->placed) {
                continue;
            }
#if 0
            if (n->dir_left != r->dir_left) {
                continue;
            }
            if (n->dir_right != r->dir_right) {
                continue;
            }
            if (n->dir_up != r->dir_up) {
                continue;
            }
            if (n->dir_down != r->dir_down) {
                continue;
            }
#endif
            if (n->is_exit != r->is_exit) {
                continue;
            }
            if (n->is_entrance != r->is_entrance) {
                continue;
            }
            if (n->is_lock != r->is_lock) {
                continue;
            }
            if (n->is_key != r->is_key) {
                continue;
            }
            return (r);
        }
        DIE("failed to get a room");
    }

    void dmap_print_walls (dmap *d)
    {
        int16_t x;
        int16_t y;

        for (y = 0; y < MAP_HEIGHT; y++) {
            for (x = 0; x < MAP_WIDTH; x++) {
                int16_t e = d->val[x][y];
                if (e == DMAP_IS_WALL) {
                    if (is_floor_at(x, y)) {
                        printf(".");
                    } else if (is_wall_at(x, y)) {
                        printf("x");
                    } else {
                        printf("_");
                    }
                    continue;
                }
                if (e == DMAP_IS_PASSABLE) {
                    if (is_floor_at(x, y)) {
                        printf(".");
                    } else {
                        printf(" ");
                    }
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

    void reset_possible_rooms (void)
    {
        cells.resize(map_width * map_height * Charmap::DEPTH_MAX,
                     Charmap::SPACE);

        std::fill(cells.begin(), cells.end(), Charmap::SPACE);
        
        for (auto r : Room::all_rooms) {
            r->placed = false;
        }
    }
};

class Dungeon *dungeon_test (void)
{
#if 0
    auto x = 1000 ;
    while (x--) {
        //
        // smaller node numbers mean larger rooms
        //
        /* auto d = new */ Dungeon(MAP_WIDTH, MAP_HEIGHT, 6, 3, x);
    }

    return (nullptr);
#else
int x = -577749009;
//x = myrand();
CON("seed: %d", x);
mysrand(x);
    auto d = new Dungeon(MAP_WIDTH, MAP_HEIGHT, 7, 5, x);

    return (d);
#endif
}
