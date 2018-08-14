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

#define MAX_NODES_WIDTH 10
#define MAX_NODES_HEIGHT 10

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
    // This is the target minimum room size given the map size and the number
    // of nodes in the level
    //
    int room_width                            {0};
    int room_height                           {0};

    //
    // High level view of the map.
    //
    int nodes_width                           {0};
    int nodes_height                          {0};
    Nodes                                     *nodes;

    //
    // Room pointers on the above nodes map
    //
    Roomp                                     node_rooms[MAX_NODES_WIDTH]
                                                        [MAX_NODES_HEIGHT];

    //
    // All possible rooms we will choose from. Initially these are fixed
    // rooms and we add more random ones onto this list.
    //
    std::vector<Roomp>                        all_possible_rooms;
    int                                       how_many_possible_rooms;

    //
    // Placed rooms
    //
    std::vector<Roomp>                        all_placed_rooms;

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
            // Create the simplest level so we have something possible to 
            // build off of. Place only the smaller rooms here.
            //
            if (!place_initial_small_rooms()) {
                continue;
            }

            //
            // Now try and replace some of the small rooms with larger ones
            //
            if (!replace_small_rooms_randomly_with_larger_rooms()) {
                continue;
            }

            //
            // Drag rooms to the center of the map
            //
            if (!compress_room_layout()) {
                continue;
            }

            //
            // Join the corridors of each room, including secret ones
            //
            if (!create_room_corridors()) {
                continue;
            }

            break;
        }
    }

    void debug (std::string s)
    {_
        //return;
        dump();
        CON("%s", s.c_str());
    }

    Dungeon (int map_width,
             int map_height,
             int nodes_width,
             int nodes_height) :
        map_width                  (map_width),
        map_height                 (map_height),
        nodes_width                (nodes_width),
        nodes_height               (nodes_height)
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

    bool is_floor_or_corridor_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_floor ||
                v.is_corridor) {
                return true;
            }
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

    bool is_wall_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_wall) {
                return true;
            }
        }
        return false;
    }

    bool is_cwall_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_cwall) {
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

    bool is_dungeon_way_up_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_dungeon_way_up) {
                return true;
            }
        }
        return false;
    }

    bool is_dungeon_way_down_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_dungeon_way_down) {
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

    bool is_chasm_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_chasm) {
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

    bool is_dissolves_walls_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto v = Charmap::all_charmaps[c];

            if (v.is_dissolves_walls) {
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
                v.is_dungeon_way_down ||
                v.is_dungeon_way_up   ||
                v.is_door) {
                return true;
            }
        }
        return false;
    }

    void create_node_map (void)
    {
        if (nodes_width >= MAX_NODES_WIDTH) {
            DIE("nodes width overflow");
        }

        if (nodes_height >= MAX_NODES_HEIGHT) {
            DIE("nodes height overflow");
        }

        nodes = new Nodes(nodes_width, nodes_height);
        room_width  = map_width / nodes_width;
        room_height  = map_height / nodes_height;
    }

#if 0
    std::vector<point> get_line_ (point a, point b, int flag)
    {_
        int temp, dx, dy, tdy, dydx, p, x, y, i;

        if (a.x > b.x) {
            temp = a.x; a.x = b.x; b.x = temp;
            temp = a.y; a.y = b.y; b.y = temp;
        }

        dx = b.x - a.x;
        dy = b.y - a.y;
        tdy = 2 * dy;
        dydx = tdy - 2 * dx;
        p = tdy - dx;   /* p0 = 2dy - dx */
        x = a.x;
        y = a.y;

        std::vector<point> r;

        switch (flag) {
            case 0: r.push_back(point(x, y)); break;
            case 1: r.push_back(point(y, x)); break;
            case 2: r.push_back(point(y, -x)); break;
            case 3: r.push_back(point(x, -y)); break;
        }

        for (i = 1; i <= dx; i++){
            x++;

	    if (p < 0) {
		p += tdy;
	    } else {
		p += dydx;
		y++;
	    }

            switch (flag) {
                case 0: r.push_back(point(x, y)); break;
                case 1: r.push_back(point(y, x)); break;
                case 2: r.push_back(point(y, -x)); break;
                case 3: r.push_back(point(x, -y)); break;
            }
        }

        return (r);
    }

    std::vector<point> get_line (point a, point b)
    {_
        int x0 = a.x;
        int x1 = b.x;
        int y0 = a.y;
        int y1 = b.y;

        float slope = 100;

        if (x0 != x1) slope = (y1 - y0) * 1.0 / (x1 - x0);

        /* call helper function depending on the line slope */
        if ((0 <= slope) && (slope <= 1))
            return get_line_(point(x0, y0), point(x1, y1), 0);
        else if ((-1 <= slope) && (slope <= 0))
            return get_line_(point(x0, -y0), point(x1, -y1), 3);
        else if (slope > 1)
            return get_line_(point(y0, x0), point(y1, x1), 1);
        else
            return get_line_(point(-y0, x0), point(-y1, x1), 2);
    }

    /*
     * Line between points
     */
    void line_draw (point start, point end, int depth, char rchar)
    {_
        auto points = get_line(start, end);
        for (auto p : points) {
            putc(p.x, p.y, depth, rchar);
        }
    }

    /*
     * Flood fill empty space.
     */
    void flood_fill(int x, int y, int depth, char rchar)
    {_
        std::stack<point> s;

        s.push(point(x, y));
        while (s.size() > 0) {

            point p = s.top();
            auto x = p.x;
            auto y = p.y;
            s.pop();

            if (is_oob(x, y)) {
                continue;
            }

            if (is_floor_or_corridor_at(x, y)) {
                continue;
            }

            putc(x, y, depth, rchar);

            s.push(point(x + 1, y));
            s.push(point(x - 1, y));
            s.push(point(x, y + 1));
            s.push(point(x, y - 1));
        }
    }

    /*
     * Flood fill empty space and return the points.
     * Used to get all the tiles in a room.
     */
    std::vector<point> flood_erase (const int x, const int y,
                                    const size_t max_size)
    {_
        bool walked[map_width][map_height];
        std::vector<point> r;
        std::stack<point> s;

        for (auto i = 0; i < map_width; i++) {
            for (auto j = 0; j < map_height; j++) {
                walked[i][j] = false;
            }
        }

        s.push(point(x, y));

        while (s.size() > 0) {
            point p = s.top();
            auto x = p.x;
            auto y = p.y;
            s.pop();

            if ((x >= map_width) || (y >= map_height) || (x < 0) || (y < 0)) {
                continue;
            }

            if (walked[x][y]) {
                continue;
            }

            walked[x][y] = true;

            auto c = getc(x, y, Charmap::DEPTH_FLOOR);
            if (c != Charmap::FLOOR) {
                continue;
            }

            putc(x, y, Charmap::DEPTH_FLOOR, Charmap::SPACE);
            r.push_back(point(x, y));

            // To limit room size
            if (r.size() > max_size) {
                break;
            }

            if ((x < map_width - 1) and not walked[x + 1][y]) {
                s.push(point(x + 1, y));
            }
            if ((x > 1) and not walked[x - 1][y]) {
                s.push(point(x - 1, y));
            }
            if ((y < map_height - 1) and !walked[x][y + 1]) {
                s.push(point(x, y + 1));
            }
            if ((y > 1) and not walked[x][y - 1]) {
                s.push(point(x, y - 1));
            }
        }
        return (r);
    }

    /*
     * Flood fill empty space and return the points.
     * Used to get all the tiles in a room.
     */
    std::vector<point> flood_find (const int x, const int y,
                                   std::function<bool (char)> callback)
    {_
        bool walked[map_width][map_height];
        std::vector<point> r;
        std::stack<point> s;

        for (auto i = 0; i < map_width; i++) {
            for (auto j = 0; j < map_height; j++) {
                walked[i][j] = false;
            }
        }

        s.push(point(x, y));

        while (s.size() > 0) {
            point p = s.top();
            auto x = p.x;
            auto y = p.y;
            s.pop();

            if ((x >= map_width) || (y >= map_height) || (x < 0) || (y < 0)) {
                continue;
            }

            if (walked[x][y]) {
                continue;
            }

            walked[x][y] = true;

            auto c = getc(x, y, Charmap::DEPTH_FLOOR);
            if (!callback(c)) {
                continue;
            }

            r.push_back(point(x, y));

            if ((x < map_width - 1) and not walked[x + 1][y]) {
                s.push(point(x + 1, y));
            }
            if ((x > 1) and not walked[x - 1][y]) {
                s.push(point(x - 1, y));
            }
            if ((y < map_height - 1) and !walked[x][y + 1]) {
                s.push(point(x, y + 1));
            }
            if ((y > 1) and not walked[x][y - 1]) {
                s.push(point(x, y - 1));
            }
        }
        return (r);
    }

    bool Callback(char c);
    void t (void)
    {_
        auto f = std::bind(&Dungeon::Callback, this, std::placeholders::_1);
        flood_find (0, 0, f);
        flood_find (0, 0, [](char c) { return true; });
    }

    /*
     * Find all adjacent characters of the same type.
     */
    void flood_replace (const int x, const int y, const int z,
                        const char old,
                        const char with)
    {_
        bool walked[map_width][map_height];
        std::stack<point> s;

        for (auto i = 0; i < map_width; i++) {
            for (auto j = 0; j < map_height; j++) {
                walked[i][j] = false;
            }
        }

        s.push(point(x, y));

        while (s.size() > 0) {
            point p = s.top();
            auto x = p.x;
            auto y = p.y;
            s.pop();

            if ((x >= map_width) || (y >= map_height) || (x < 0) || (y < 0)) {
                continue;
            }

            if (walked[x][y]) {
                continue;
            }

            walked[x][y] = true;

            auto c = getc(x, y, z);
            if (c != old) {
                continue;
            }

            putc(x, y, z, with);

            if ((x < map_width - 1) and not walked[x + 1][y]) {
                s.push(point(x + 1, y));
            }
            if ((x > 1) and not walked[x - 1][y]) {
                s.push(point(x - 1, y));
            }
            if ((y < map_height - 1) and !walked[x][y + 1]) {
                s.push(point(x, y + 1));
            }
            if ((y > 1) and not walked[x][y - 1]) {
                s.push(point(x, y - 1));
            }
        }
    }
#endif

    void dump (void)
    {_
        if (!dungeon_debug) {
            return;
        }

        CON("map debug:");
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

    //
    // Check for room overlaps
    //
    bool room_can_be_placed (Roomp room, int x, int y)
    {_
        if (x < 0) {
            return false;
        }
        if (x + room->width >= map_width) {
            return false;
        }

        if (y < 0) {
            return false;
        }
        if (y + room->height >= map_height) {
            return false;
        }

        for (auto d = 0 ; d < Charmap::DEPTH_MAX; d++) {
            if (not room->data[d].size()) {
                continue;
            }

            auto dy = 0;
            for (auto s : room->data[d]) {
                auto dx = 0;
                for (auto c : s) {
                    if (c != Charmap::SPACE) {
                        if (is_anything_at(x + dx,     y + dy)) {
                            return false;
                        }
                    }
                    dx++;
                }
                dy++;
            }

            dy = 0;
            for (auto s : room->data[d]) {
                auto dx = 0;
                for (auto c : s) {
                    if (c != Charmap::SPACE) {
                        if (is_anything_at(x + dx - 1, y + dy) ||
                            is_anything_at(x + dx + 1, y + dy) ||
                            is_anything_at(x + dx, y + dy - 1) ||
                            is_anything_at(x + dx, y + dy + 1)) {
                            return false;
                        }
                    }
                    dx++;
                }
                dy++;
            }
        }

        return true;
    }

    //
    // Dump a room onto the level. No checks
    //
    void room_place (Roomp room, int x, int y)
    {_
        for (auto d = 0 ; d < Charmap::DEPTH_MAX; d++) {
            if (not room->data[d].size()) {
                continue;
            }

            auto dy = 0;
            for (auto s : room->data[d]) {
                auto dx = 0;
                for (auto c : s) {
                    if (c != Charmap::SPACE) {
                        putc(x + dx, y + dy, d, c);
                    }
                    dx++;
                }
                dy++;
            }
        }
    }

    //
    // Try to push a room on the level
    //
    bool room_place_if_no_overlaps (Roomp room, int x, int y)
    {_
        if (not room_can_be_placed(room, x, y)) {
            return false;
        }

        room_place(room, x, y);
        return true;
    }

    //
    // From a fixed list of random roomnos, return the next one. This
    // ensures no room will ever appear more than once.
    //
    Roomp get_next_room (void)
    {_
        Roomp r;

        if (!all_possible_rooms.size()) {
            all_possible_rooms = Room::all_rooms;
            std::shuffle(all_possible_rooms.begin(), all_possible_rooms.end(), rng);
        }

        r = all_possible_rooms.back();
        all_possible_rooms.pop_back();

        if (!r) {
            all_possible_rooms = Room::all_rooms;
            std::shuffle(all_possible_rooms.begin(), all_possible_rooms.end(), rng);
        }

        if (r->placed) {
            return (get_next_room());
        }
        return (r);
    }

    bool draw_corridor (point start, point end, char w)
    {
        dmap d;

        if (w == Charmap::CORRIDOR) {
            LOG("create corridor, between %d,%d and %d,%d ^^^",
                start.x, start.y,
                end.x, end.y);
        } else {
            LOG("create secret corridor, between %d,%d and %d,%d ^^^",
                start.x, start.y,
                end.x, end.y);
        }

        for (auto x = 0; x < map_width; x++) {
            for (auto y = 0; y < map_height; y++) {
                if (is_anything_at(x, y)) {
                    d.val[x][y] = DMAP_IS_WALL;
                } else {
                    d.val[x][y] = DMAP_IS_PASSABLE;
                }
            }
        }

        d.val[end.x][end.y] = DMAP_IS_GOAL;
        d.val[start.x][start.y] = DMAP_IS_PASSABLE;

        dmap_process(&d);
        //dmap_print(&d);
        auto p = dmap_solve(&d, start, end);

        //
        // Too long a corridor?
        //
        if (p.size() > 25) {
            for (auto c : p) {
                putc(c.x, c.y, Charmap::DEPTH_FLOOR, Charmap::DEBUG);
            }
            debug("^^^ failed to create corridor, too long a corridor ^^^");
            return (false);
        }

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
                putc(c.x, c.y, Charmap::DEPTH_FLOOR, Charmap::DEBUG);
            }

            debug("^^^ failed to create corridor, end not found ^^^");
            LOG("^^^ failed to create corridor, end not found between %d,%d and %d,%d ^^^",
                start.x, start.y,
                end.x, end.y);
            return (false);
        }

        for (auto c : p) {
            auto o = getc(c.x - 1, c.y, Charmap::DEPTH_FLOOR);
            if ((o == Charmap::CORRIDOR) || (o == Charmap::SECRET_CORRIDOR)) {
                debug("^^^ failed to create corridor, adjoins another corridor ^^^");
                return (false);
            }
            o = getc(c.x + 1, c.y, Charmap::DEPTH_FLOOR);
            if ((o == Charmap::CORRIDOR) || (o == Charmap::SECRET_CORRIDOR)) {
                debug("^^^ failed to create corridor, adjoins another corridor ^^^");
                return (false);
            }
            o = getc(c.x, c.y + 1, Charmap::DEPTH_FLOOR);
            if ((o == Charmap::CORRIDOR) || (o == Charmap::SECRET_CORRIDOR)) {
                debug("^^^ failed to create corridor, adjoins another corridor ^^^");
                return (false);
            }
            o = getc(c.x, c.y - 1, Charmap::DEPTH_FLOOR);
            if ((o == Charmap::CORRIDOR) || (o == Charmap::SECRET_CORRIDOR)) {
                debug("^^^ failed to create corridor, adjoins another corridor ^^^");
                return (false);
            }
            o = getc(c.x, c.y, Charmap::DEPTH_FLOOR);
            if ((o == Charmap::CORRIDOR) || (o == Charmap::SECRET_CORRIDOR)) {
                debug("^^^ failed to create corridor, overlaps another corridor ^^^");
                return (false);
            }
        }

        for (auto c : p) {
            putc(c.x, c.y, Charmap::DEPTH_FLOOR, w);
        }

        putc(start.x, start.y, Charmap::DEPTH_WALLS, Charmap::DOOR);
        putc(end.x, end.y, Charmap::DEPTH_WALLS, Charmap::DOOR);

        //debug("^^^ placed corridor ^^^");
        return (true);
    }

    void reset_possible_rooms (void)
    {
        cells.resize(map_width * map_height * Charmap::DEPTH_MAX,
                     Charmap::SPACE);

        std::fill(cells.begin(), cells.end(), Charmap::SPACE);

        all_placed_rooms.resize(0);

        memset(node_rooms, 0, sizeof(node_rooms));

        how_many_possible_rooms = (int) Room::all_rooms.size();
        for (auto r : Room::all_rooms) {
            r->placed = false;
        }
    }

    //
    // Place the initial rooms. Choose only small ones we know will
    // fit.
    //
    bool place_initial_small_rooms (void)
    {
        for (auto x = 0; x < nodes->nodes_width; x++) {
            for (auto y = 0; y < nodes->nodes_height; y++) {

                auto n = nodes->getn(x, y);
                if (!n->depth) {
                    continue;
                }

                if (n->depth == nodes->depth_obstacle) {
                    continue;
                }

                auto placed = false;
                for (auto roomi = 0; roomi < how_many_possible_rooms; roomi++) {

                    auto r = get_next_room();

                    if (r->width >= room_width) {
                        continue;
                    }

                    if (r->height >= room_height) {
                        continue;
                    }

                    if ((n->has_exit_down || n->has_secret_exit_down) &&
                        !r->down_exits.size()) {
                        continue;
                    }
                    if ((n->has_exit_up || n->has_secret_exit_up) &&
                        !r->up_exits.size()) {
                        continue;
                    }
                    if ((n->has_exit_left || n->has_secret_exit_left) &&
                        !r->left_exits.size()) {
                        continue;
                    }
                    if ((n->has_exit_right || n->has_secret_exit_right) &&
                        !r->right_exits.size()) {
                        continue;
                    }

                    r->at.x = x * room_width + 
                                    random_range(-room_width/2, room_width/2);
                    r->at.y = y * room_height + 
                                    random_range(-room_width/2, room_height/2);

                    node_rooms[x][y] = r;
                    r->placed = true;

                    if (room_place_if_no_overlaps(r, r->at.x, r->at.y)) {
                        placed = true;
                        break;
                    }
                }

                if (!placed) {
                    // debug("^^^ failed to place initial small rooms ^^^");
                    LOG("failed to place initial small rooms");
                    return (false);
                }
            }
        }

        debug("^^^ placed initial small rooms ^^^");
        return (true);
    }

    //
    // Repeatedly try to place larger rooms
    //
    bool replace_small_rooms_randomly_with_larger_rooms (void)
    {
        auto place_large_room_tries = 10;
        while (place_large_room_tries--) {
            std::fill(cells.begin(), cells.end(), Charmap::SPACE);

            Roomp replace_this_room_with_a_larger_one = nullptr;

            //
            // Choose a room to skip
            //
            for (auto x = 0; x < nodes->nodes_width; x++) {
                for (auto y = 0; y < nodes->nodes_height; y++) {
                    auto r = node_rooms[x][y];
                    if (!r) {
                        continue;
                    }

                    //
                    // Already larger
                    //
                    if ((r->width > room_width) ||
                        (r->height > room_height)) {
                        continue;
                    }

                    if (random_range(0, 100) < 10) {
                        replace_this_room_with_a_larger_one = r;
                    }
                }
            }

            if (!replace_this_room_with_a_larger_one) {
                continue;
            }

            //
            // Place all rooms bar the skip room
            //
            for (auto x = 0; x < nodes->nodes_width; x++) {
                for (auto y = 0; y < nodes->nodes_height; y++) {
                    auto r = node_rooms[x][y];
                    if (!r) {
                        continue;
                    }

                    if (r == replace_this_room_with_a_larger_one) {
                        continue;
                    }

                    auto rx = r->at.x;
                    auto ry = r->at.y;
                    if (!room_place_if_no_overlaps(r, rx, ry)) {
                        DIE("could not place base room when trying to find larger rooms");
                        break;
                    }
                }
            }

            //
            // Now place a larger room where the skip room is
            //
            for (auto x = 0; x < nodes->nodes_width; x++) {
                for (auto y = 0; y < nodes->nodes_height; y++) {
                    auto r = node_rooms[x][y];
                    if (!r) {
                        continue;
                    }

                    if (r != replace_this_room_with_a_larger_one) {
                        continue;
                    }

                    auto n = nodes->getn(x, y);
                    for (auto roomi = 0; roomi < how_many_possible_rooms; roomi++) {

                        auto r = get_next_room();

                        //
                        // Filter out small rooms
                        //
                        if (r->width < room_width) {
                            continue;
                        }

                        if (r->height < room_height) {
                            continue;
                        }

                        //
                        // Filter to only rooms that match the node 
                        // requirements
                        //
                        if ((n->has_exit_down || n->has_secret_exit_down) &&
                            !r->down_exits.size()) {
                            continue;
                        }
                        if ((n->has_exit_up || n->has_secret_exit_up) &&
                            !r->up_exits.size()) {
                            continue;
                        }
                        if ((n->has_exit_left || n->has_secret_exit_left) &&
                            !r->left_exits.size()) {
                            continue;
                        }
                        if ((n->has_exit_right || n->has_secret_exit_right) &&
                            !r->right_exits.size()) {
                            continue;
                        }

                        auto offsets = 3;
                        for (auto dx = -offsets; dx < offsets; dx++) {
                            for (auto dy = -offsets; dy < offsets; dy++) {
                                auto rx = dx + x * room_width;
                                auto ry = dy + y * room_height;

                                if (room_place_if_no_overlaps(r, rx, ry)) {
                                    node_rooms[x][y]->placed = false;
                                    r->placed = true;
                                    node_rooms[x][y] = r;
                                    r->at.x = rx;
                                    r->at.y = ry;
                                    goto next;
                                }
                            }
                        }
                    }
                }
            }
next:
            continue;
        }

        //
        // Remake the dungeon with the larger rooms
        //
        std::fill(cells.begin(), cells.end(), Charmap::SPACE);

        for (auto x = 0; x < nodes->nodes_width; x++) {
            for (auto y = 0; y < nodes->nodes_height; y++) {
                auto r = node_rooms[x][y];
                if (!r) {
                    continue;
                }

                auto rx = r->at.x;
                auto ry = r->at.y;
                if (!room_place_if_no_overlaps(r, rx, ry)) {
                    DIE("could not place base room(2) when trying to find larger rooms");
                    break;
                }

                //
                // We are sticking with this room, so keep track of it
                //
                all_placed_rooms.push_back(r);
            }
        }

        debug("^^^ placed larger rooms ^^^");

        return (true);
    }

    //
    // Repeat placing all rooms bar one random one. Try to move
    // that random one closer to the center. Repeat.
    //
    bool compress_room_layout (void)
    {
        auto mx = map_width / 2;
        auto my = map_height / 2;
        auto delta = 2;

        auto attempts_to_move_rooms_closer = 50;
        while (attempts_to_move_rooms_closer--) {
            for (unsigned int rs = 0;
                 rs < (unsigned int) all_placed_rooms.size();
                 rs++) {

                auto r = all_placed_rooms[rs];
                auto skip_roomno = r->roomno;

                std::fill(cells.begin(), cells.end(), Charmap::SPACE);

                /*
                 * Place all except one room
                 */
                auto ri = 0;
                for (auto x = 0; x < nodes->nodes_width; x++) {
                    for (auto y = 0; y < nodes->nodes_height; y++) {

                        auto n = nodes->getn(x, y);
                        if (n->depth <= 0 ) {
                            continue;
                        }

                        auto r = all_placed_rooms[ri++];
                        if (r->roomno == skip_roomno) {
                            continue;
                        }

                        room_place(r, r->at.x, r->at.y);
                    }
                }

                /*
                 * Place the room we want to move
                 */
                ri = 0;
                for (auto x = 0; x < nodes->nodes_width; x++) {
                    for (auto y = 0; y < nodes->nodes_height; y++) {

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
                            if (room_can_be_placed(r, r->at.x - delta, r->at.y)) {
                                r->at.x--;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        if (r->at.x < mx) {
                            if (room_can_be_placed(r, r->at.x + delta, r->at.y)) {
                                r->at.x++;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        if (r->at.y + r->height > my) {
                            if (room_can_be_placed(r, r->at.x, r->at.y - delta)) {
                                r->at.y--;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        if (r->at.y < my) {
                            if (room_can_be_placed(r, r->at.x, r->at.y + delta)) {
                                r->at.y++;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        room_place(r, r->at.x, r->at.y);
                        break;
                    }
                }
            }
        }
        debug("^^^ placed compressed layout ^^^");

        return (true);
    }

    //
    // Join the corridors of each room
    //
    bool create_room_corridors (void)
    {
        for (auto x = 0; x < map_width; x++) {
            for (auto y = 0; y < map_height; y++) {
                if (getc(x, y, Charmap::DEPTH_WALLS) == Charmap::DOOR) {
                    putc(x, y, Charmap::DEPTH_WALLS, Charmap::WALL);
                }
            }
        }

        for (auto x = 0; x < nodes->nodes_width; x++) {
            for (auto y = 0; y < nodes->nodes_height; y++) {

                auto n = nodes->getn(x, y);
                if (!n->depth) {
                    continue;
                }

                if (n->depth == nodes->depth_obstacle) {
                    continue;
                }

                auto r = node_rooms[x][y];

                if (n->has_exit_down) {
                    auto o = node_rooms[x][y+1];
                    if (!o) {
                        debug("^^^ bug ^^^");
                        DIE("had exit down at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->down_exits.size());
                    auto odoori = random_range(0, o->up_exits.size());
                    if (odoori >= o->up_exits.size()) {
                        debug("^^^ bug ^^^");
                        DIE("no left exit [%d] at %d,%d, but only have %ld exits",
                            odoori, x, y, o->up_exits.size());
                    }

                    auto rdoor = r->down_exits[rdoori];
                    auto odoor = o->up_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    if (!draw_corridor(start, end, Charmap::CORRIDOR)) {
                        return (false);
                    }
                }

                if (n->has_exit_right) {
                    auto o = node_rooms[x+1][y];
                    if (!o) {
                        debug("^^^ bug ^^^");
                        DIE("had exit right at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->right_exits.size());
                    auto odoori = random_range(0, o->left_exits.size());
                    if (odoori >= o->left_exits.size()) {
                        debug("^^^ bug ^^^");
                        DIE("no left exit [%d] at %d,%d, but only have %ld exits",
                            odoori, x, y, o->left_exits.size());
                    }

                    auto rdoor = r->right_exits[rdoori];
                    auto odoor = o->left_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    if (!draw_corridor(start, end, Charmap::CORRIDOR)) {
                        return (false);
                    }
                }

                if (n->has_secret_exit_down) {
                    auto o = node_rooms[x][y+1];
                    if (!o) {
                        debug("^^^ bug ^^^");
                        DIE("had secret exit down at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->down_exits.size());
                    auto odoori = random_range(0, o->up_exits.size());
                    if (odoori >= o->up_exits.size()) {
                        debug("^^^ bug ^^^");
                        DIE("no left exit [%d] at %d,%d, but only have %ld exits",
                            odoori, x, y, o->up_exits.size());
                    }

                    auto rdoor = r->down_exits[rdoori];
                    auto odoor = o->up_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    if (!draw_corridor(start, end, Charmap::SECRET_CORRIDOR)) {
                        return (false);
                    }
                }

                if (n->has_secret_exit_right) {
                    auto o = node_rooms[x+1][y];
                    if (!o) {
                        debug("^^^ bug ^^^");
                        DIE("had secret exit right at %d,%d, but no node exists", x, y);
                    }
                    auto rdoori = random_range(0, r->right_exits.size());
                    auto odoori = random_range(0, o->left_exits.size());
                    if (odoori >= o->left_exits.size()) {
                        debug("^^^ bug ^^^");
                        DIE("no left exit [%d] at %d,%d, but only have %ld exits",
                            odoori, x, y, o->left_exits.size());
                    }

                    auto rdoor = r->right_exits[rdoori];
                    auto odoor = o->left_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    if (!draw_corridor(start, end, Charmap::SECRET_CORRIDOR)) {
                        return (false);
                    }
                }
            }
        }

        debug("^^^ placed corridors ^^^");
        return (true);
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
        /* auto d = new */ Dungeon(MAP_WIDTH, MAP_HEIGHT, 6, 3);
    }

    return (nullptr);
#else
    auto d = new Dungeon(MAP_WIDTH, MAP_HEIGHT, 6, 3);

    return (d);
#endif
}
