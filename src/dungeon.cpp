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
#include <stack>
#include <list>

class Dungeon {
public:
    std::vector<char>              cells;
    std::vector<int>               roomno_cells;
    int map_width                  {MAP_WIDTH};
    int map_height                 {MAP_HEIGHT};
    int map_depth                  {Charmap::DEPTH_MAX};

    //
    // All possible rooms we will choose from. Initially these are fixed
    // rooms and we add more random ones onto this list.
    //
    Rooms                          rooms;

    //
    // Set if we fail to generate
    //
    bool generate_failed           {false};

    //
    // How many rooms on the level currently.
    //
    int rooms_on_level             {};
    int rooms_on_level_target      {};

    //
    // First range of rooms are fixed; rest randomly generated
    //
    int fixed_room_count           {};

    //
    // What chance for fixed versus random rooms
    //
    int fixed_room_chance          {20};

    //
    // Chance of a corridor splitting
    //
    int corridor_fork_chance       {35};
    int tunnel_fork_chance         {95};

    //
    // Lower, longer corridors
    //
    int corridor_grow_chance       {2};
    int tunnel_grow_chance         {1};

    //
    // How often a random room is locked
    //
    int room_locked_chance         {5};

    //
    // How close corridors should be to each other
    //
    int corridor_spacing           {3};

    //
    // For random shape rooms, how large?
    //
    int min_room_size              {10};

    //
    // Depth is how many rooms from the start room we are
    //
    std::map< int, int > roomno_depth;

    //
    // Rooms that have all doors locked
    //
    std::map< int, bool > roomno_locked;

    //
    // Exits from each room
    //
    std::map< int, std::list<point> > roomno_exits;

    //
    // The tiles of a each romm
    //
    std::map< int, std::list<point> > room_occupiable_tiles;

    //
    // z depths of the level
    //
    dmap *depth_map                {};

    void finish_constructor (void)
    {
        Charmap::init_charmaps();
        rooms = Room::all_rooms;
        fixed_room_count = rooms.size();

        cells.resize(map_width * map_height * Charmap::DEPTH_MAX);
        roomno_cells.resize(map_width * map_height);
    }

    Dungeon (int map_width,
             int map_height,
             int rooms_on_level_target) :
        map_width                  (map_width),
        map_height                 (map_height),
        rooms_on_level_target      (rooms_on_level_target)
    {
        finish_constructor();
    }

    Dungeon ()
    {
        finish_constructor();
    }

    int cell_offset (const int x, const int y, const int z)
    {
        auto offset = (map_width * map_height) * z;
        offset += (map_height) * y;
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
            LOG("out of bounds on %d,%d,%d vs %d,%d,%d", 
                x, y, z, map_width, map_height, map_depth);
            return (nullptr);
        }

        return (&cells[cell_offset(x, y, z)]);
    }

    int room_offset (const int x, const int y)
    {
        auto offset = (map_height) * y;
        offset += x;

        return (offset);
    }

    int *roomno_addr (const int x, const int y)
    {
        if (is_oob(x, y)) {
            LOG("out of bounds on room cells at %d,%d vs %d,%d", 
                x, y, map_width, map_height);
            return (nullptr);
        }

        return (&roomno_cells[room_offset(x, y)]);
    }

    /*
     * Puts a tile on the map
     */
    void putc (const int x, const int y, const int z, const char c)
    {
        char *p = cell_addr(x, y, z);
        if (p != nullptr) {
            *p = c;
        }
    }

    /*
     * Gets a tile of the map or None
     */
    char getc (const int x, const int y, const int z)
    {
        char *p = cell_addr(x, y, z);
        if (p != nullptr) {
            return (*p);
        }
        return (Charmap::NONE);
    }

    /*
     * Puts a roomno on the map
     */
    void putr (const int x, const int y, const int c)
    {
        int *p = roomno_addr(x, y);
        if (p != nullptr) {
            *p = 0;
        }
    }

    /*
     * Gets a roomno of the map or None
     */
    int getr (const int x, const int y)
    {
        int *p = roomno_addr(x, y);
        if (p != nullptr) {
            return (*p);
        }
        return (Charmap::NONE);
    }

    bool is_anything_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            if (c != Charmap::SPACE) {
                return true;
            }
        }
        return false;
    }

    bool is_any_floor_or_corridor_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_floor ||
                charmap.is_corridor) {
                return true;
            }
        }
        return false;
    }

    bool is_any_floor_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_floor) {
                return true;
            }
        }
        return false;
    }

    bool is_any_dusty_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_dusty) {
                return true;
            }
        }
        return false;
    }

    bool is_any_corridor_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_corridor) {
                return true;
            }
        }
        return false;
    }

    bool is_any_wall_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_wall) {
                return true;
            }
        }
        return false;
    }

    bool is_any_cwall_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_cwall) {
                return true;
            }
        }
        return false;
    }

    bool is_any_door_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_door) {
                return true;
            }
        }
        return false;
    }

    bool is_any_dungeon_way_up_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_dungeon_way_up) {
                return true;
            }
        }
        return false;
    }

    bool is_any_dungeon_way_down_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_dungeon_way_down) {
                return true;
            }
        }
        return false;
    }

    bool is_any_lava_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_lava) {
                return true;
            }
        }
        return false;
    }

    bool is_any_water_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_water) {
                return true;
            }
        }
        return false;
    }

    bool is_any_chasm_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_chasm) {
                return true;
            }
        }
        return false;
    }
    
    bool is_any_treasure_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_treasure) {
                return true;
            }
        }
        return false;
    }

    bool is_any_dissolves_walls_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_dissolves_walls) {
                return true;
            }
        }
        return false;
    }

    bool is_any_key_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_key) {
                return true;
            }
        }
        return false;
    }

    bool is_movement_blocking_at (const int x, const int y)
    {
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            auto charmap = Charmap::all_charmaps[c];

            if (charmap.is_wall             ||
                charmap.is_treasure         ||
                charmap.is_dungeon_way_down ||
                charmap.is_dungeon_way_up   ||
                charmap.is_door) {
                return true;
            }
        }
        return false;
    }

    std::vector<point> get_line_ (point a, point b, int flag)
    {
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

        const int step = 10;
        int s = 0;

        for (i = 1; i <= dx; i++){

            x++;
            if (p < 0) p += tdy;
            else { p += dydx; y++; }

            if (s++ != step) {
                continue;
            }
            s = 0;

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
    {
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
    void line_draw(point start, point end, int depth, char rchar)
    {
        auto points = get_line(start, end);
        for (auto p : points) {
            putc(p.x, p.y, depth, rchar);
        }
    }

    /*
     * Flood fill empty space.
     */
    void flood_fill(int x, int y, int depth, char rchar)
    {
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

            if (is_any_floor_or_corridor_at(x, y)) {
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
    {
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

            putc(x, y, Charmap::DEPTH_FLOOR, Charmap::NONE);
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
    {
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
    {
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
    {
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
};

class Dungeon *dungeon_test (void)
{
    auto d = new Dungeon(80, 80, 20);

    return (d);
}
