/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
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

//
// The algorithm
//
// - Create a cyclic dungeon map. Different 'levels' of the dungeon can be
// cycles with a door of some kind to the next level.
//
//    K         S    D    K
//    1____1____1____2____2    -
//    |    |    |         |
//    |    |    |         |
//    |    |    |         |
//    |    |    |        D|   D
//    1    1____1    -    3____4
//    ?                   |    |
//    ?                   |    |
//    ?                   |    |
//    ?                  K|   E|
//    1____1____2    -    3    4
//
//  - Place initial small rooms
//
//  - Now we know we have a possible level, replace some of the small rooms
//  with larger rooms, so it looks more interesting.
//
//  xDxxxxx                                                         xDxxx
// xx.....D               xDx      xDxxDx                           D...xxx
// D......x               D.xx     x.xx.x      xxDxxx               x.....x
// x......x               x..xx    x....x      x..$.D               x.....x
// xxxxDxxx               x...x    x....x      D....x              xx..x..x
//                        x...xx   xx...x      x....x              x......D
//                        xxx..x    xxx.D      xxxDxx              x...xxxx
//                          xDxx      xDx                          xDxxx
//                                 xDx              xxxxx
//                                 x.x              D...D         xxxxx
//                                xx.xx             x...x         D...D
//   xxxxDxxxxx                  xx...xDx           x...xxxxDxxxx x...xxxxxxxxx
//   x........D                  x......x           x...........D x...........D
//   xxxx..xxxx          xDxxxx  x......xx          x...........x xxxx...xxxxxx
//      D..D             D....D  D.......x          x...........x    D...x
//   xxxx..xxxx          x....xx xDxxxxxxx          x...........x xxxx...x
//   D........x          xx....D                    xxxDxxxxxxxxx x......x
//   xxxxxDxxxx           xx...x                                  xxxDxxxx
//                         xx..x
//           xxxxDx         xxDx  xDxx
//           D....x               D..xx                             xxxxxDx
//           x....D  xxDxx        x...xx                xxxxDxx     x.xx..D
//           x...xx xx...D        x....D                x.....D     x.....x
//           D.xxx  D....x        x.xDxx                D.....x     x.....x
//           xDx    xx..xx        xDx                   x.....x     xxxxxxx
//                   xx.x                               xxxDxxx
//                    xDx
//
//
//  - Drag all the rooms to the center of the map, making sure to keep enough
//  of a gap for corridors
//
//                                                   xDxxx
//                                  xDxxDx           D...xxx
//                  xDxxxxx         x.xx.x           x.....x
//                 xx.....D  xDx    x....x  xxDxxx   x.....x
//                 D......x  D.xx   x....x  x..$.D  xx..x..x
//                 x......x  x..xx  xx...x  D....x  x......D  xxxxx
//                 xxxxDxxx  x...x   xxx.D  x....x  x...xxxx  D...D
//                           x...xx    xDx  xxxDxx  xDxxx     x...xxxxxxxxx
//                           xxx..x                           x...........D
//              xxxxDxxxxx     xDxx    xDx                    xxxx...xxxxxx
//              x........D             x.x      xxxxx            D...x
//              xxxx..xxxx            xx.xx     D...D         xxxx...x
//                 D..D     xDxxxx   xx...xDx   x...x         x......x
//              xxxx..xxxx  D....D   x......x   x...xxxxDxxxx xxxDxxxx
//              D........x  x....xx  x......xx  x...........D
//              xxxxxDxxxx  xx....D  D.......x  x...........x
//                           xx...x  xDxxxxxxx  x...........x
//                            xx..x             x...........x
//                     xxxxDx  xxDx             xxxDxxxxxxxxx
//                     D....x         xDxx
//                     x....D         D..xx            xxxxxDx
//                     x...xx  xxDxx  x...xx  xxxxDxx  x.xx..D
//                     D.xxx  xx...D  x....D  x.....D  x.....x
//                     xDx    D....x  x.xDxx  D.....x  x.....x
//                            xx..xx  xDx     x.....x  xxxxxxx
//                             xx.x           xxxDxxx
//                              xDx
//
//  - Now draw corridors, according to the original node layout. Make sure no
//  corridors overlap or touch.
//
//                                                   xxxxx
//                                  xxxxxx          #D...xxx
//                  xxxxxxx         x.xx.x         ##x.....x
//                 xx.....D# xxx    x....x  xxxxxx## x.....x
//                 x......x##D.xx   x....x  x..$.D# xx..x..x
//                 x......x  x..xx  xx...x #D....x  x......x  xxxxx
//                 xxxxDxxx  x...x   xxx.D##x....x  x...xxxx  x...x
//                   ###     x...xx    xDx  xxxxxx  xDxxx     x...xxxxxxxxx
//                  ##       xxx..x     #            #        x...........x
//              xxxxDxxxxx     xDxx    xDx           #        xxxx...xxxxxx
//              x........x    ###      x.x      xxxxx##      ####D...x
//              xxxx..xxxx   ##       xx.xx     x...x ##     #xxxx...x
//                 x..x     xDxxxx   xx...xxx   x...x  ##    #x......x
//              xxxx..xxxx  x....x   x......x   x...xxxxDxxxx#xxxDxxxx
//              x........x  x....xx  x......xx  x...........D#   #
//              xxxxxDxxxx  xx....D##D.......x  x...........x    #
//                   ??????  xx...x  xxxxxxxxx  x...........x   ##
//                        ??  xx..x             x...........x  ##
//                     xxxxDx  xxxx             xxxDxxxxxxxxx ##
//                     x....x         xxxx         #        ###
//                     x....D#       #D..xx       ##   xxxxxDx
//                     x...xx# xxxxx##x...xx  xxxxDxx  x.xx..x
//                     x.xxx #xx...D# x....x  x.....x  x.....x
//                     xxx   #D....x  x.xxxx  x.....x  x.....x
//                            xx..xx  xxx     x.....x  xxxxxxx
//                             xx.x           xxxxxxx
//                              xxx
//
//

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

    //
    // For rollback when moving rooms around.
    //
    std::vector<char>                         cells_saved;

    //
    // Pointers from map position to room
    //
    std::vector<Roomp>                        cells_room;

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

    //
    // Placed rooms
    //
    std::vector<Roomp>                       all_placed_rooms;

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

            //
            // Create a cyclic dungeon map.
            //
            create_cyclic_rooms(&grid);

            //
            // Choose how rooms are linked
            //
            choose_room_doors();

            //
            // Drag rooms to the center of the map
            //
            if (!compress_room_layout_to_center_of_map()) {
                continue;
            }

            if (compress_room_corridors()) {
                break;
            }
            
            debug("failed, redo from scratch");
        }

        //
        // Keep track of which tile has which room
        //
        assign_rooms_to_tiles();

        //
        // Remove all doors and then add them back in, but only between
        // depth changes
        //
        remove_all_doors();

        //
        // Place the rooms back on the map, so if there were any intentional
        // doors removed above then they will reappear.
        //
        room_print_only_doors(&grid);

        // 
        // Not sure we want this as rooms
        // 
        //place_doors_between_depth_changes();

        //
        // Add a perimeter to the level. Helps avoid off by one bugs.
        //
        add_corridor_walls();
        add_room_walls();
        add_border();

        debug("success, created dungeon");
    }

    void debug (std::string s)
    {_
        //return;
        LOG("dungeon (%u) %s", seed, s.c_str());
        dump();
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

    Roomp *cell_rooms_addr (const int x, const int y)
    {
        if (is_oob(x, y)) {
            return (nullptr);
        }

        return (&cells_room[offset(x, y)]);
    }

    Roomp *cell_rooms_addr_fast (const int x, const int y)
    {
        return (&cells_room[offset(x, y)]);
    }

    void putr (const int x, const int y, Roomp r)
    {
        auto p = cell_rooms_addr(x, y);
        if (p != nullptr) {
            *p = r;
        }
    }

    Roomp getr (const int x, const int y)
    {
        auto p = cell_rooms_addr(x, y);
        if (p != nullptr) {
            return (*p);
        }
        return (nullptr);
    }

    Roomp getr_fast (const int x, const int y)
    {
        auto p = cell_rooms_addr_fast(x, y);
        if (p != nullptr) {
            return (*p);
        }
        return (nullptr);
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

    int get_grid_depth_at (const int x, const int y)
    {
        auto r = getr(x, y);
        if (r) {
            return (r->depth);
        }
        return (0);
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

    bool is_corridor_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_corridor) {
                return true;
            }
        }
        return false;
    }

    bool is_corridor_at_fast (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc_fast(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_corridor) {
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

    bool is_floor_deco_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_floor_deco) {
                return true;
            }
        }
        return false;
    }

    bool is_wall_deco_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_wall_deco) {
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

        LOG("dungeon: seed %u (with room depth)", seed);
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
                        DIE("unknown map char %c at x %d, y %d, depth %d", 
                            m, x, y, d);
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

        /*
         * Pass 2 without room depths
         */
        LOG("dungeon: seed %u (more readable version)", seed);
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
                        DIE("unknown map char %c at x %d, y %d, depth %d", 
                            m, x, y, d);
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
        cells_room.resize(map_width * map_height, nullptr);

        std::fill(cells.begin(), cells.end(), Charmap::SPACE);
        std::fill(cells_room.begin(), cells_room.end(), nullptr);
        
        for (auto r : Room::all_rooms) {
            r->placed = false;

            r->which_secret_door_up = 0;
            r->which_secret_door_down = 0;
            r->which_secret_door_left = 0;
            r->which_secret_door_right = 0;
            r->which_door_up = 0;
            r->which_door_down = 0;
            r->which_door_left = 0;
            r->which_door_right = 0;

            r->left_room = nullptr;
            r->right_room = nullptr;
            r->up_room = nullptr;
            r->down_room = nullptr;
            
            r->secret_left_room = nullptr;
            r->secret_right_room = nullptr;
            r->secret_up_room = nullptr;
            r->secret_down_room = nullptr;
        }
    }

    void room_print_at (Roomp r, int x, int y)
    {_
        r->at.x = x;
        r->at.y = y;

        for (auto z = 0; z < MAP_DEPTH; z++) {
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

    void room_print_only_doors_at (Roomp r, int x, int y)
    {_
        for (auto z = 0; z < MAP_DEPTH; z++) {
            for (auto dy = 0; dy < r->height; dy++) {
                for (auto dx = 0; dx < r->width; dx++) {
                    auto c = r->data[dx][dy][z];
                    if (c == Charmap::DOOR) {
                        putc(x + dx, y + dy, z, c);
                    }
                }
            }
        }
    }

    void room_print_only_doors (Grid *g)
    {_
        for (auto x = 0; x < grid_width; x++) {
            for (auto y = 0; y < grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                Roomp r = g->node_rooms[x][y];
                if (r) {
                    room_print_only_doors_at(r, r->at.x, r->at.y);
                }
            }
        }
    }

    void rooms_print_all (Grid *g)
    {_
        std::fill(cells.begin(), cells.end(), Charmap::SPACE);

        for (auto x = 0; x < grid_width; x++) {
            for (auto y = 0; y < grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                Roomp r = g->node_rooms[x][y];
                if (r) {
                    room_print_at(r, 
                                  x * ROOM_WIDTH + MAP_BORDER, 
                                  y * ROOM_HEIGHT + MAP_BORDER);
                }
            }
        }
    }

    bool room_is_a_candidate (const Node *n, Roomp r)
    {
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto o = grid.node_rooms[x][y];
                if (o == r) {
                    return (false);
                }
            }
        }

        if ((n->has_door_down || n->has_secret_exit_down) &&
            !r->doors_down.size()) {
            return (false);
        }
        if ((n->has_door_up || n->has_secret_exit_up) &&
            !r->doors_up.size()) {
            return (false);
        }
        if ((n->has_door_left || n->has_secret_exit_left) &&
            !r->doors_left.size()) {
            return (false);
        }
        if ((n->has_door_right || n->has_secret_exit_right) &&
            !r->doors_right.size()) {
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
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto o = grid.node_rooms[x][y];
                if (o == r) {
                    return (false);
                }
            }
        }
        
        if ((n->has_door_down || n->has_secret_exit_down) &&
            !r->doors_down.size()) {
            return (false);
        }
        if ((n->has_door_up || n->has_secret_exit_up) &&
            !r->doors_up.size()) {
            return (false);
        }
        if ((n->has_door_left || n->has_secret_exit_left) &&
            !r->doors_left.size()) {
            return (false);
        }
        if ((n->has_door_right || n->has_secret_exit_right) &&
            !r->doors_right.size()) {
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

            candidates.push_back(r);
        }

        auto ncandidates = candidates.size();
	if (!ncandidates) {
            for (auto r : Room::all_rooms) {
                if (!room_is_a_candidate_less_restrictive(n, r)) {
                    continue;
                }

                candidates.push_back(r);
            }

            ncandidates = candidates.size();
            if (!ncandidates) {
                rooms_print_all(g);
                dump();
                DIE("no grid room candidates at %d %d", x, y);
                return (false);
            }
	}

        auto r = candidates[random_range(0, ncandidates)];
        g->node_rooms[x][y] = r;
        
        if (n->has_door_down) {
            Grid old = *g;
            if (!solve(x, y+1, g)) {
                *g = old;
            }
        }
        if (n->has_door_up) {
            Grid old = *g;
            if (!solve(x, y-1, g)) {
                *g = old;
            }
        }
        if (n->has_door_right) {
            Grid old = *g;
            if (!solve(x+1, y, g)) {
                *g = old;
            }
        }
        if (n->has_door_left) {
            Grid old = *g;
            if (!solve(x-1, y, g)) {
                *g = old;
            }
        }
        return (true);
    }

    bool create_cyclic_rooms (Grid *g)
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

    void add_border (void)
    {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto x = 0; x < MAP_BORDER; x++) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::WALL);
                putc(MAP_WIDTH - (x+1), y, MAP_DEPTH_WALLS, Charmap::WALL);
            }
        }
        for (auto x = 0; x < MAP_WIDTH; x++) {
            for (auto y = 0; y < MAP_BORDER; y++) {
                putc(x, y, MAP_DEPTH_WALLS, Charmap::WALL);
                putc(x, MAP_HEIGHT - (y+1), MAP_DEPTH_WALLS, Charmap::WALL);
            }
        }
    }

    void add_corridor_walls (void)
    {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                if (is_wall_at_fast(x, y)) {
                    continue;
                }
                if (is_corridor_at_fast(x, y)) {
                    if (!is_anything_at_fast(x - 1, y - 1)) {
                        putc(x - 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x, y - 1)) {
                        putc(x, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x + 1, y - 1)) {
                        putc(x + 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }

                    if (!is_anything_at_fast(x - 1, y)) {
                        putc(x - 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x + 1, y)) {
                        putc(x + 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                    }

                    if (!is_anything_at_fast(x - 1, y + 1)) {
                        putc(x - 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x, y + 1)) {
                        putc(x, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x + 1, y + 1)) {
                        putc(x + 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                }
            }
        }
    }

    void add_room_walls (void)
    {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto x = 0; x < MAP_WIDTH; x++) {
                if (is_wall_at_fast(x, y)) {
                    continue;
                }
                if (is_floor_at_fast(x, y)) {
                    if (!is_anything_at_fast(x - 1, y - 1)) {
                        putc(x - 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x, y - 1)) {
                        putc(x, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x + 1, y - 1)) {
                        putc(x + 1, y - 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }

                    if (!is_anything_at_fast(x - 1, y)) {
                        putc(x - 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x + 1, y)) {
                        putc(x + 1, y, MAP_DEPTH_WALLS, Charmap::WALL);
                    }

                    if (!is_anything_at_fast(x - 1, y + 1)) {
                        putc(x - 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x, y + 1)) {
                        putc(x, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at_fast(x + 1, y + 1)) {
                        putc(x + 1, y + 1, MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                }
            }
        }
    }

    //
    // Find which doors we want to use for a room
    //
    void choose_room_doors (void)
    {
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                if (n->depth == nodes->depth_obstacle) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];

                if (n->has_door_down) {
                    auto o = grid.node_rooms[x][y+1];
                    if (!o) {
                        debug("bug");
                        DIE("had exit down at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->doors_down.size());
                    auto odoori = random_range(0, o->doors_up.size());
                    if (rdoori >= r->doors_down.size()) {
                        debug("bug");
                        DIE("bug");
                    }
                    if (odoori >= o->doors_up.size()) {
                        debug("bug");
                        DIE("bug");
                    }

                    r->which_door_down = rdoori;
                    o->which_door_up = odoori;
                    
                    r->down_room = o;
                    o->up_room = r;
                }

                if (n->has_door_right) {
                    auto o = grid.node_rooms[x+1][y];
                    if (!o) {
                        debug("bug");
                        DIE("had exit right at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->doors_right.size());
                    auto odoori = random_range(0, o->doors_left.size());
                    if (rdoori >= r->doors_right.size()) {
                        debug("bug");
                        DIE("bug");
                    }
                    if (odoori >= o->doors_left.size()) {
                        debug("bug");
                        DIE("bug");
                    }

                    r->which_door_right = rdoori;
                    o->which_door_left = odoori;
                    
                    r->right_room = o;
                    o->left_room = r;
                }

                if (n->has_secret_exit_down) {
                    auto o = grid.node_rooms[x][y+1];
                    if (!o) {
                        debug("bug");
                        DIE("had secret exit down at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->doors_down.size());
                    auto odoori = random_range(0, o->doors_up.size());
                    if (rdoori >= r->doors_down.size()) {
                        debug("bug");
                        DIE("bug, room %d, down door index %d size %d", 
                            r->roomno, (int)rdoori, (int)r->doors_down.size());
                    }
                    if (odoori >= o->doors_up.size()) {
                        debug("bug");
                        DIE("bug, room %d, up door index %d size %d", 
                            r->roomno, (int)odoori, (int)r->doors_up.size());
                    }

                    r->which_secret_door_down = rdoori;
                    o->which_secret_door_up = odoori;
                    
                    r->secret_down_room = o;
                    o->secret_up_room = r;
                }

                if (n->has_secret_exit_right) {
                    auto o = grid.node_rooms[x+1][y];
                    if (!o) {
                        debug("bug");
                        DIE("had secret exit right at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->doors_right.size());
                    auto odoori = random_range(0, o->doors_left.size());
                    if (rdoori >= r->doors_right.size()) {
                        debug("bug");
                        DIE("bug, room %d, right door index %d size %d", 
                            r->roomno, (int)rdoori, (int)r->doors_right.size());
                    }
                    if (odoori >= o->doors_left.size()) {
                        debug("bug");
                        DIE("bug, room %d, left door index %d size %d", 
                            r->roomno, (int)odoori, (int)r->doors_left.size());
                    }

                    r->which_secret_door_right = rdoori;
                    o->which_secret_door_left = odoori;
                    
                    r->secret_right_room = o;
                    o->secret_left_room = r;
                }
            }
        }
    }

    void save_level (void)
    {
        cells_saved = cells;

        for (unsigned int rs = 0;
                rs < (unsigned int) all_placed_rooms.size(); rs++) {
            auto r = all_placed_rooms[rs];
            r->rollback_at = r->at;
        }
    }

    void restore_level (void)
    {
        cells = cells_saved;

        for (unsigned int rs = 0;
                rs < (unsigned int) all_placed_rooms.size(); rs++) {
            auto r = all_placed_rooms[rs];
            r->at = r->rollback_at;
        }
    }

    int draw_corridor (point start, point end, char w)
    {
        dmap d;

        memset(&d, 0, sizeof(d));

#if 0
        if (w == Charmap::CORRIDOR) {
            LOG("create corridor, between %d,%d and %d,%d",
                start.x, start.y,
                end.x, end.y);
        } else {
            LOG("create secret corridor, between %d,%d and %d,%d",
                start.x, start.y,
                end.x, end.y);
        }
#endif

        point dmap_start = start;
        point dmap_end = end;

        int minx, miny, maxx, maxy;
        if (dmap_start.x < dmap_end.x) {
            minx = dmap_start.x;
            maxx = dmap_end.x;
        } else {
            minx = dmap_end.x;
            maxx = dmap_start.x;
        }
        if (dmap_start.y < dmap_end.y) {
            miny = dmap_start.y;
            maxy = dmap_end.y;
        } else {
            miny = dmap_end.y;
            maxy = dmap_start.y;
        }

        auto border = 3;
        minx -= border;
        miny -= border;
        maxx += border;
        maxy += border;

        if (minx < 0) {
            minx = 0;
        }
        if (miny < 0) {
            miny = 0;
        }
        if (maxx >= map_width) {
            maxx = map_width - 1;
        }
        if (maxy >= map_height) {
            maxy = map_height - 1;
        }

        //
        // Set up obstacles for the corridor search
        //
        for (auto y = miny; y < maxy; y++) {
            for (auto x = minx; x < maxx; x++) {
                if (is_anything_at_fast(x, y)) {
                    d.val[x][y] = DMAP_IS_WALL;
                } else {
                    d.val[x][y] = DMAP_IS_PASSABLE;
                }
            }
        }

        //
        // Ensure adjoining corridors are not possible
        //
        for (auto y = miny + 1; y < maxy - 1; y++) {
            for (auto x = minx + 1; x < maxx - 1; x++) {
                if (is_corridor_at_fast(x, y)) {
                    d.val[x-1][y] = DMAP_IS_WALL;
                    d.val[x][y-1] = DMAP_IS_WALL;
                    d.val[x][y] = DMAP_IS_WALL;
                    d.val[x][y+1] = DMAP_IS_WALL;
                    d.val[x+1][y] = DMAP_IS_WALL;
                }
            }
        }

        dmap_start = point(minx, miny);
        dmap_end = point(maxx, maxy);

        d.val[end.x][end.y] = DMAP_IS_GOAL;
        d.val[start.x][start.y] = DMAP_IS_PASSABLE;

        dmap_process(&d, dmap_start, dmap_end);
        //dmap_print_walls(&d);

        //LOG("dmap hash: %llx level hash %llx", dmap_hash(&d), level_hash());
        auto p = dmap_solve(&d, start, end);

        //
        // Too long a corridor?
        //
#if 0
        if (p.size() > 25) {
            for (auto c : p) {
                putc(c.x, c.y, MAP_DEPTH_FLOOR, Charmap::DEBUG);
            }
            debug("failed to create corridor, too long a corridor");
            return (0);
        }
#endif

        //
        // Check we can reach the end point
        //
        bool got_goal = false;
        for (auto c : p) {
            if (c == end) {
                got_goal = true;
                break;
            }
        }

        if (!got_goal) {
            for (auto c : p) {
                putc(c.x, c.y, MAP_DEPTH_FLOOR, Charmap::DEBUG);
            }
            putc(start.x, start.y, MAP_DEPTH_WALLS, Charmap::DEBUG);
            putc(end.x, end.y, MAP_DEPTH_WALLS, Charmap::DEBUG);

            debug("failed to create corridor, end not found");
            LOG("dungeon: failed to create corridor, end not found between %d,%d and %d,%d",
                start.x, start.y,
                end.x, end.y);
            return (0);
        }

        for (auto c : p) {
            putc(c.x, c.y, MAP_DEPTH_FLOOR, w);
        }

        putc(start.x, start.y, MAP_DEPTH_WALLS, Charmap::DOOR);
        putc(end.x, end.y, MAP_DEPTH_WALLS, Charmap::DOOR);

        //debug("placed corridor");
        return (p.size());
    }

    //
    // Join the corridors of each room
    //
    int draw_corridors (void)
    {
        for (auto x = 0; x < map_width; x++) {
            for (auto y = 0; y < map_height; y++) {
                auto c = getc(x, y, MAP_DEPTH_WALLS);
                if ((c == Charmap::DOOR_UP) ||
                    (c == Charmap::DOOR_DOWN) ||
                    (c == Charmap::DOOR_LEFT) ||
                    (c == Charmap::DOOR_RIGHT)) {
                    putc(x, y, MAP_DEPTH_WALLS, Charmap::WALL);
                }
            }
        }

        auto corridor_count = 0;
        
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {

                auto n = nodes->getn(x, y);
                if (!n->depth) {
                    continue;
                }

                if (n->depth == nodes->depth_obstacle) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];

                if (n->has_door_down) {
                    auto o = grid.node_rooms[x][y+1];
                    
                    auto rdoori = r->which_door_down;
                    auto odoori = o->which_door_up;

                    auto rdoor = r->doors_down[rdoori];
                    auto odoor = o->doors_up[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    
                    r->down_door_at = start;
                    o->up_door_at = end;
                    
                    auto cnt = draw_corridor(start, end, Charmap::CORRIDOR);
                    if (!cnt) {
                        return (0);
                    }
                    corridor_count += cnt;
                }

                if (n->has_door_right) {
                    auto o = grid.node_rooms[x+1][y];
                    
                    auto rdoori = r->which_door_right;
                    auto odoori = o->which_door_left;

                    auto rdoor = r->doors_right[rdoori];
                    auto odoor = o->doors_left[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    
                    r->right_door_at = start;
                    o->left_door_at = end;
                    
                    auto cnt = draw_corridor(start, end, Charmap::CORRIDOR);
                    if (!cnt) {
                        return (0);
                    }
                    corridor_count += cnt;
                }

                if (n->has_secret_exit_down) {
                    auto o = grid.node_rooms[x][y+1];
                    
                    auto rdoori = r->which_secret_door_down;
                    auto odoori = o->which_secret_door_up;

                    auto rdoor = r->doors_down[rdoori];
                    auto odoor = o->doors_up[odoori];
                    
                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    
                    r->down_secret_door_at = start;
                    o->up_secret_door_at = end;
                    
                    auto cnt = draw_corridor(start, end, Charmap::SECRET_CORRIDOR);
                    if (!cnt) {
                        return (0);
                    }
                    corridor_count += cnt;
                }

                if (n->has_secret_exit_right) {
                    auto o = grid.node_rooms[x+1][y];
                    
                    auto rdoori = r->which_secret_door_right;
                    auto odoori = o->which_secret_door_left;

                    auto rdoor = r->doors_right[rdoori];
                    auto odoor = o->doors_left[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    
                    r->right_secret_door_at = start;
                    o->left_secret_door_at = end;
                    
                    auto cnt = draw_corridor(start, end, Charmap::SECRET_CORRIDOR);
                    if (!cnt) {
                        return (0);
                    }
                    corridor_count += cnt;
                }
            }
        }

        return (corridor_count);
    }

    void center_room_layout (void)
    {
        auto minx = map_width;
        auto miny = map_height;
        auto maxx = 0;
        auto maxy = 0;
        
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];
                if (!r) {
                    continue;
                }
                
                if (r->at.x < minx) {
                    minx = r->at.x;
                }
                if (r->at.y < miny) {
                    miny = r->at.y;
                }
                if (r->at.x + r->width > maxx) {
                    maxx = r->at.x + r->width;
                }
                if (r->at.y + r->height > maxy) {
                    maxy = r->at.y + r->height;
                }
            }
        }
        
        auto dx = (map_width - (maxx - minx)) / 2;
        auto dy = (map_height - (maxy - miny)) / 2;
        
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];
                if (!r) {
                    continue;
                }
                
                r->at.x -= minx;
                r->at.y -= miny;
                
                r->at.x += dx;
                r->at.y += dy;
            }
        }
    }

    //
    // Dump a room onto the level. No checks
    //
    void place_room (Roomp r, int x, int y)
    {
        for (auto dz = 0 ; dz < MAP_DEPTH; dz++) {
            for (auto dy = 0; dy < r->height; dy++) {
                for (auto dx = 0; dx < r->width; dx++) {
                    auto c = r->data[dx][dy][dz];
                    if (c != Charmap::SPACE) {
                        putc_fast(x + dx, y + dy, dz, c);
                    }
                }
            }
        }

        for (auto dy = 0; dy < r->height; dy++) {
            for (auto dx = 0; dx < r->width; dx++) {
                auto c = r->data[dx][dy][MAP_DEPTH_FLOOR];
                if (c != Charmap::SPACE) {
                    if (!is_anything_at(x + dx - 1, y + dy - 1)) {
                        putc_fast(x + dx - 1, y + dy - 1, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx, y + dy - 1)) {
                        putc_fast(x + dx, y + dy - 1, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx + 1, y + dy - 1)) {
                        putc_fast(x + dx + 1, y + dy - 1, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx - 1, y + dy)) {
                        putc_fast(x + dx - 1, y + dy, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx + 1, y + dy)) {
                        putc_fast(x + dx + 1, y + dy, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx - 1, y + dy + 1)) {
                        putc_fast(x + dx - 1, y + dy + 1, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx, y + dy + 1)) {
                        putc_fast(x + dx, y + dy + 1, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                    if (!is_anything_at(x + dx + 1, y + dy + 1)) {
                        putc_fast(x + dx + 1, y + dy + 1, 
                                  MAP_DEPTH_WALLS, Charmap::WALL);
                    }
                }
            }
        }
    }
    
    //
    // Dump a room onto the level along with its roomno. Done when we
    // have finalized positions of rooms.
    //
    void map_place_room_ptr (Roomp r, int x, int y)
    {
        if (!r) {
            DIE("no room to place");
        }
        
        for (auto dz = 0 ; dz < MAP_DEPTH; dz++) {
            for (auto dy = 0; dy < r->height; dy++) {
                for (auto dx = 0; dx < r->width; dx++) {
                    auto c = r->data[dx][dy][dz];
                    if (c != Charmap::SPACE) {
                        putr(x + dx, y + dy, r);
                    }
                }
            }
        }
    }

    //
    // Check for room overlaps
    //
    bool can_place_room (Roomp r, int x, int y)
    {
        if (x < 0) {
            return false;
        }
        if (x + r->width >= map_width) {
            return false;
        }

        if (y < 0) {
            return false;
        }
        if (y + r->height >= map_height) {
            return false;
        }

        for (auto dz = 0 ; dz < MAP_DEPTH; dz++) {
            for (auto dy = 0; dy < r->height; dy++) {
                for (auto dx = 0; dx < r->width; dx++) {
                    auto c = r->data[dx][dy][dz];
                    if (c != Charmap::SPACE) {
                        if (is_anything_at(x + dx, y + dy)) {
                            return false;
                        }

                        if (is_wall_at(x + dx - 1, y + dy) ||
                            is_wall_at(x + dx + 1, y + dy) ||
                            is_wall_at(x + dx, y + dy - 1) ||
                            is_wall_at(x + dx, y + dy + 1)) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }

    //
    // Try to push a room on the level
    //
    bool map_room_place_if_no_overlaps (Roomp r, int x, int y)
    {
        if (not can_place_room(r, x, y)) {
            return false;
        }

        place_room(r, x, y);
        return true;
    }

    //
    // Repeat placing all rooms bar one random one. Try to move
    // that random one closer to the center. Repeat.
    //
    bool compress_room_layout_to_center_of_map (void)
    {
        auto mx = map_width / 2;
        auto my = map_height / 2;
        auto delta = 1;

        all_placed_rooms.resize(0);

        for (auto r : Room::all_rooms) {
            r->placed = false;
        }

        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];
                if (!r) {
                    continue;
                }

                all_placed_rooms.push_back(r);
                r->placed = true;
            }
        }

        //
        // Make sure we start with a solvable room
        //
        save_level();
        if (!draw_corridors()) {
            debug("level before adding corridors is NOT solvable");
            return (false);
        }

        restore_level();
        debug("level before adding corridors is solvable");

        auto failed_attempts = 0;
        auto attempts_to_move_rooms_closer = 200;

        choose_room_doors();
        
        while (attempts_to_move_rooms_closer--) {

            center_room_layout();
            
            for (unsigned int rs = 0;
                 rs < (unsigned int) all_placed_rooms.size();
                 rs++) {

                auto r = all_placed_rooms[rs];
                auto skip_roomno = r->roomno;

                std::fill(cells.begin(), cells.end(), Charmap::SPACE);
                
                auto moved = false;

                /*
                 * Place all except one room
                 */
                auto ri = 0;
                for (auto x = 0; x < nodes->grid_width; x++) {
                    for (auto y = 0; y < nodes->grid_height; y++) {

                        auto n = nodes->getn(x, y);
                        if (n->depth <= 0 ) {
                            continue;
                        }

                        auto r = all_placed_rooms[ri++];
                        if (r->roomno == skip_roomno) {
                            continue;
                        }

                        place_room(r, r->at.x, r->at.y);
                    }
                }

                /*
                 * Place the room we want to move
                 */
                ri = 0;
                for (auto x = 0; x < nodes->grid_width; x++) {
                    for (auto y = 0; y < nodes->grid_height; y++) {

                        auto n = nodes->getn(x, y);
                        if (!n->depth) {
                            continue;
                        }

                        //
                        // water etc..
                        //
                        if (n->depth == nodes->depth_obstacle) {
                            continue;
                        }

                        auto r = all_placed_rooms[ri++];
                        if (r->roomno != skip_roomno) {
                            continue;
                        }

                        if (r->at.x + r->width > mx) {
                            if (can_place_room(r, r->at.x - delta, r->at.y)) {
                                r->at.x--;
                                place_room(r, r->at.x, r->at.y);
                                moved = true;
                                break;
                            }
                        }

                        if (r->at.x < mx) {
                            if (can_place_room(r, r->at.x + delta, r->at.y)) {
                                r->at.x++;
                                place_room(r, r->at.x, r->at.y);
                                moved = true;
                                break;
                            }
                        }

                        if (r->at.y + r->height > my) {
                            if (can_place_room(r, r->at.x, r->at.y - delta)) {
                                r->at.y--;
                                place_room(r, r->at.x, r->at.y);
                                moved = true;
                                break;
                            }
                        }

                        if (r->at.y < my) {
                            if (can_place_room(r, r->at.x, r->at.y + delta)) {
                                r->at.y++;
                                place_room(r, r->at.x, r->at.y);
                                moved = true;
                                break;
                            }
                        }

                        place_room(r, r->at.x, r->at.y);
                        break;
                    }
                }

                if (!moved) {
                    continue;
                }

                //
                // Ok we've moved one room. If we can still place corridors
                // then we can keep going. If not, rollback the room to the
                // last that was solvable.
                //
                std::vector<char> cells_ok = cells;

                if (!draw_corridors()) {
                    debug("failed to placing corridors, rollback");
                    restore_level();

                    if (failed_attempts++ > 20) {
                        debug("success, placed compressed layout");
                        return (true);
                    }
                } else {
                    debug("success, placed corridors");
                    failed_attempts = 0;
                    cells = cells_ok;
                    save_level();
                }
            }
        }
        
        debug("success, placed compressed layout");
        return (true);
    }

    bool compress_room_corridors (void)
    {
        auto delta = 1;

        all_placed_rooms.resize(0);

        for (auto r : Room::all_rooms) {
            r->placed = false;
        }

        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];
                if (!r) {
                    continue;
                }

                all_placed_rooms.push_back(r);
                r->placed = true;
            }
        }

        //
        // Make sure we start with a solvable room
        //
        save_level();
        auto corridor_count = draw_corridors();
        if (!corridor_count) {
            debug("level before adding corridors is NOT solvable");
            return (false);
        }

        dump();
        debug("level before adding shorter corridors is solvable");
        restore_level();

        auto failed_to_place_all_corridors = 0;
        auto failed_to_make_shorter_corridors = 0;
        auto attempts_to_move_rooms_closer = 200;

        choose_room_doors();
        
        while (attempts_to_move_rooms_closer--) {

            center_room_layout();
            
            for (unsigned int rs = 0;
                 rs < (unsigned int) all_placed_rooms.size();
                 rs++) {

                std::fill(cells.begin(), cells.end(), Charmap::SPACE);
                
                /*
                 * which rooms shall we move?
                 */
                for (auto x = 0; x < nodes->grid_width; x++) {
                    for (auto y = 0; y < nodes->grid_height; y++) {
                        auto n = nodes->getn(x, y);
                        if (n->depth <= 0 ) {
                            continue;
                        }

                        auto r = grid.node_rooms[x][y];
                        if (r) {
                            r->skip = (random_range(0, 100) < 10);
                        }
                    }
                }
                
                /*
                 * Place all rooms that are not going to move
                 */
                for (auto x = 0; x < nodes->grid_width; x++) {
                    for (auto y = 0; y < nodes->grid_height; y++) {
                        auto n = nodes->getn(x, y);
                        if (n->depth <= 0 ) {
                            continue;
                        }

                        auto r = grid.node_rooms[x][y];
                        if (!r) {
                            continue;
                        }
                        if (!r->skip) {
                            place_room(r, r->at.x, r->at.y);
                        }
                    }
                }

                /*
                 * Place the rooms we want to move
                 */
                auto moved = false;
                for (auto x = 0; x < nodes->grid_width; x++) {
                    for (auto y = 0; y < nodes->grid_height; y++) {
                        auto n = nodes->getn(x, y);
                        if (n->depth <= 0 ) {
                            continue;
                        }

                        auto r = grid.node_rooms[x][y];
                        if (!r) {
                            continue;
                        }
                        if (!r->skip) {
                            continue;
                        }

                        auto moved_one = false;
                        switch (random_range(0, 4)) {
                        case 0:
                            if (can_place_room(r, r->at.x - delta, r->at.y)) {
                                r->at.x--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x + delta, r->at.y)) {
                                r->at.x++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x, r->at.y - delta)) {
                                r->at.y--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x, r->at.y + delta)) {
                                r->at.y++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            break;

                        case 1:
                            if (can_place_room(r, r->at.x + delta, r->at.y)) {
                                r->at.x++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x - delta, r->at.y)) {
                                r->at.x--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x, r->at.y - delta)) {
                                r->at.y--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x, r->at.y + delta)) {
                                r->at.y++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            break;
                            
                        case 2:
                            if (can_place_room(r, r->at.x, r->at.y - delta)) {
                                r->at.y--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x - delta, r->at.y)) {
                                r->at.x--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x + delta, r->at.y)) {
                                r->at.x++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x, r->at.y + delta)) {
                                r->at.y++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            break;

                        case 3:
                            if (can_place_room(r, r->at.x, r->at.y + delta)) {
                                r->at.y++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x - delta, r->at.y)) {
                                r->at.x--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x + delta, r->at.y)) {
                                r->at.x++;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            if (can_place_room(r, r->at.x, r->at.y - delta)) {
                                r->at.y--;
                                place_room(r, r->at.x, r->at.y);
                                moved_one = true;
                                break;
                            }
                            break;
                        case 4:
                            DIE("wtf");
                        }
                        
                        if (moved_one) {
                            moved = true;
                        } else {
                            place_room(r, r->at.x, r->at.y);
                        }
                    }
                }

                if (!moved) {
                    continue;
                }

                //
                // Ok we've moved one room. If we can still place corridors
                // then we can keep going. If not, rollback the room to the
                // last that was solvable.
                //
                std::vector<char> cells_ok = cells;

                auto new_corridor_count = draw_corridors();
//CON("corridor_count %d new_corridor_count %d 
//failed_to_make_shorter_corridors %d ",corridor_count, new_corridor_count, 
//failed_to_make_shorter_corridors);
                if (new_corridor_count >= corridor_count) {
                    debug("failed to place shorter corridors, rollback");
                    
                    restore_level();
                    if (!draw_corridors()) {
                        DIE("rolled back level was not solvable");
                    }

                    if (failed_to_make_shorter_corridors++ > 100) {
                        debug("success, placed shorter corridor layout");
                        return (true);
                    }

                    restore_level();
                } else if (!new_corridor_count) {
                    debug("failed to place all corridors, rollback");
                    
                    restore_level();
                    if (!draw_corridors()) {
                        DIE("rolled back level was not solvable");
                    }

                    if (failed_to_place_all_corridors++ > 20) {
                        debug("success, placed shorter corridor layout");
                        return (true);
                    }

                    restore_level();
                } else {
                    corridor_count = new_corridor_count;
                    debug("success, placed corridors");
                    failed_to_place_all_corridors = 0;
                    failed_to_make_shorter_corridors = 0;
                    cells = cells_ok;
                    save_level();
                }
            }
        }
        debug("success, placed shorter corridor layout");

        return (draw_corridors());
    }

    void assign_rooms_to_tiles (void)
    {
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];
                if (r) {
                    auto n = nodes->getn(x, y);
                    r->depth = n->depth;
                    map_place_room_ptr(r, r->at.x, r->at.y);
                }
            }
        }
    }

    void remove_all_doors (void)
    {
        for (auto x = 0; x < map_width; x++) {
            for (auto y = 0; y < map_height; y++) {
                if (getc(x, y, MAP_DEPTH_WALLS) == Charmap::DOOR) {
                    putc(x, y, MAP_DEPTH_WALLS, Charmap::SPACE);
                }
            }
        }
    }

    void place_doors_between_depth_changes (void)
    {
        for (auto x = 0; x < nodes->grid_width; x++) {
            for (auto y = 0; y < nodes->grid_height; y++) {
                auto n = nodes->getn(x, y);
                if (n->depth <= 0 ) {
                    continue;
                }

                auto r = grid.node_rooms[x][y];
                if (!r) {
                    continue;
                }

                if (r->down_room) {
                    auto o = r->down_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    if (r->depth > o->depth) {
                        putc(r->down_door_at.x, r->down_door_at.y, 
                             MAP_DEPTH_WALLS, Charmap::DOOR);
                    }
                }
                
                if (r->up_room) {
                    auto o = r->up_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    if (r->depth > o->depth) {
                        putc(r->up_door_at.x, r->up_door_at.y, 
                             MAP_DEPTH_WALLS, Charmap::DOOR);
                    }
                }
                
                if (r->right_room) {
                    auto o = r->right_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    if (r->depth > o->depth) {
                        putc(r->right_door_at.x, r->right_door_at.y, 
                             MAP_DEPTH_WALLS, Charmap::DOOR);
                    }
                }
                
                if (r->left_room) {
                    auto o = r->left_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    if (r->depth > o->depth) {
                        putc(r->left_door_at.x, r->left_door_at.y, 
                             MAP_DEPTH_WALLS, Charmap::DOOR);
                    }
                }
                
                if (r->secret_down_room) {
                    auto o = r->secret_down_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    putc(r->down_secret_door_at.x, r->down_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                    putc(o->up_secret_door_at.x, o->up_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                }
                
                if (r->secret_up_room) {
                    auto o = r->secret_up_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    putc(r->up_secret_door_at.x, r->up_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                    putc(o->down_secret_door_at.x, o->down_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                }
                
                if (r->secret_right_room) {
                    auto o = r->secret_right_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    putc(r->right_secret_door_at.x, r->right_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                    putc(o->left_secret_door_at.x, o->left_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                }
                
                if (r->secret_left_room) {
                    auto o = r->secret_left_room;
                    if (!o) {
                        DIE("room linkage bug");
                    }
                    
                    putc(r->left_secret_door_at.x, r->left_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                    putc(o->right_secret_door_at.x, o->right_secret_door_at.y, 
                         MAP_DEPTH_WALLS, Charmap::SECRET_DOOR);
                }
            }
        }
    }
};
