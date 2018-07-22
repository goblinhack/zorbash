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
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

static bool debug = false;

class Dungeon {
public:
    std::vector<char>                         cells;
    std::vector<char>                         tmp;
    std::vector<int>                          roomno_cells;
    int map_width                             {MAP_WIDTH};
    int map_height                            {MAP_HEIGHT};
    int map_depth                             {Charmap::DEPTH_MAX};

    uint32_t map_cellular_automata_fill_chance = 50;
    int map_cellular_automata_r1               = 5;
    int map_cellular_automata_r2               = 2;
    int map_cellular_automata_generations      = 8;

    //
    // After the cellular stage we erase portions of the map with
    // lines to makes isolated islands we then pull out as "rooms"
    //
    int map_carve_lines_cnt                    = 50;

    //
    // All possible rooms we will choose from. Initially these are fixed
    // rooms and we add more random ones onto this list.
    //
    Rooms                                     fixed_rooms;
    Rooms                                     random_rooms;

    int fixed_room_count                      {};
    int random_room_count                     {};

    //
    // Set if we fail to generate
    //
    bool generate_failed                      {false};

    //
    // How many rooms on the level currently.
    //
    int rooms_on_level                        {};
    int rooms_on_level_target                 {};

    //
    // What chance for fixed versus random rooms
    //
    int fixed_room_chance                     {20};

    //
    // Chance of a corridor splitting
    //
    int corridor_fork_chance                  {35};
    int tunnel_fork_chance                    {95};

    //
    // Lower, longer corridors
    //
    int corridor_grow_chance                  {2};
    int tunnel_grow_chance                    {1};

    //
    // How often a random room is locked
    //
    int room_locked_chance                    {5};

    //
    // How close corridors should be to each other
    //
    int corridor_spacing                      {3};

    //
    // For random shape rooms, how large?
    //
    size_t min_room_size                      {10};
    size_t max_room_size                      {100};

    //
    // Dmap for z depths of the level
    //
    dmap *depth_map                           {};

    //
    // Random lists of rooms to try and place
    //
    std::vector<int>                          fixed_roomno_list;
    std::vector<int>                          random_roomno_list;

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

    void finish_constructor (void)
    {
        Charmap::init_charmaps();

        cells.resize(map_width * map_height * Charmap::DEPTH_MAX);
        tmp.resize(map_width * map_height * Charmap::DEPTH_MAX);

        std::fill(cells.begin(), cells.end(), Charmap::NONE);
        roomno_cells.resize(map_width * map_height);

        //
        // Create all randomly shaped rooms.
        //
        for (auto c : range<int>(0, 2)) {
            rooms_all_create_random_shapes(c);
        }

        //
        // Total of fixed and random room
        //
        fixed_rooms = Room::all_fixed_rooms;
        fixed_room_count = fixed_rooms.size();

        random_rooms = Room::all_random_rooms;
        random_room_count = random_rooms.size();

        fixed_roomno_list = make_shuffled_range<int>(fixed_room_count);
        random_roomno_list = make_shuffled_range<int>(random_room_count);
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
        offset += (map_width) * y;
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
            LOG("out of bounds on cell map %d,%d,%d vs %d,%d,%d", 
                x, y, z, map_width, map_height, map_depth);
            return (nullptr);
        }

        return (&cells[cell_offset(x, y, z)]);
    }

    char *tmp_addr (const int x, const int y, const int z)
    {
        if (is_oob(x, y, z)) {
            LOG("out of bounds on tmp map %d,%d,%d vs %d,%d,%d", 
                x, y, z, map_width, map_height, map_depth);
            return (nullptr);
        }

        return (&tmp[cell_offset(x, y, z)]);
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
     * Puts a tile on the map
     */
    void puttmp (const int x, const int y, const int z, const char c)
    {
        char *p = tmp_addr(x, y, z);
        if (p != nullptr) {
            *p = c;
        }
    }

    /*
     * Gets a tile of the map or None
     */
    char gettmp (const int x, const int y, const int z)
    {
        char *p = tmp_addr(x, y, z);
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

    void dump (void)
    {
        if (!debug) {
            return;
        }

        printf("-------------------------------------------------------------\n");
        for (auto y = 0; y < map_height; y++) {
            for (auto x = 0; x < map_width; x++) {
                if (is_floor_at(x, y)) {
                    printf(".");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }

    /*
     * Cellular Automata Method for Generating Random Cave-Like Levels
     */
    char map_cellular_automata_random_tile (void)
    {
        if (random_range(0, 100) < map_cellular_automata_fill_chance) {
            return (Charmap::WALL);
        } else {
            return (Charmap::FLOOR);
        }
    }

    //
    // Grow our cells
    //
    void cave_generation (void)
    {
        int x, y, i, j;

        for (y=1; y < map_height-1; y++) {
            for (x=1; x < map_width-1; x++) {

                int adjcount_r1 = 0,
                adjcount_r2 = 0;

                //
                // Count adjacent room tiles.
                //
                for (i=-1; i <= 1; i++) {
                    for (j=-1; j <= 1; j++) {
                        if (getc(x+j, y+i, Charmap::DEPTH_FLOOR) != 
                              Charmap::FLOOR) {
                            adjcount_r1++;
                        }
                    }
                }

                for (i=y-2; i <= y+2; i++) {
                    for (j=x-2; j <= x+2; j++) {

                        if ((abs(i-y) == 2) && (abs(j-x)==2)) {
                            //
                            // Too close to the edge.
                            //
                            continue;
                        }

                        if (i < 0 || j < 0 || i>=map_height || j>=map_width) {
                            //
                            // Out of bounds.
                            //
                            continue;
                        }

                        if (getc(j, i, Charmap::DEPTH_FLOOR) != Charmap::FLOOR) {
                            adjcount_r2++;
                        }
                    }
                }

                //
                // Adjust for the grow threshold for rock or flow.
                //
                if ((adjcount_r1 >= map_cellular_automata_r1) ||
                    (adjcount_r2 <= map_cellular_automata_r2)) {
                    puttmp(x, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
                } else {
                    puttmp(x, y, Charmap::DEPTH_FLOOR, Charmap::FLOOR);
                }
            }
        }

        for (y=1; y < map_height-1; y++) {
            for (x=1; x < map_width-1; x++) {
                putc(x, y, 
                     Charmap::DEPTH_FLOOR,
                     gettmp(x, y, Charmap::DEPTH_FLOOR));
            }
        }
    }

    //
    // Generate a cave!
    //
    void make_cave (void)
    {
        int x, y, i;

        for (y=1; y < map_height-1; y++) {
            for (x=1; x < map_width-1; x++) {
                putc(x, y, Charmap::DEPTH_FLOOR,
                     map_cellular_automata_random_tile());
            }
        }

        for (y=0; y < map_height; y++) {
            for (x=0; x < map_width; x++) {
                puttmp(x, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            }
        }

        for (y=0; y < map_height; y++) {
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-1, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-2, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-3, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-4, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-5, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(1, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(2, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(3, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(0, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(4, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
        }

        for (x=0; x < map_width; x++) {
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-1, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-2, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-3, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-4, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-5, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 1, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 2, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 3, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 4, Charmap::DEPTH_FLOOR, Charmap::WALL);
        }

        map_cellular_automata_generations = 3 + (rand() % 10);

        for (i=0; i < map_cellular_automata_generations; i++) {
            cave_generation();
        }
    }

    //
    // Generate the cave
    //
    void cave_gen (void)
    {_
        std::fill(cells.begin(), cells.end(), Charmap::NONE);
        std::fill(tmp.begin(), tmp.end(), Charmap::NONE);
        make_cave();

        //
        // We only want the floor in the end to make rooms
        //
        for (int y=1; y < map_height-1; y++) {
            for (int x=1; x < map_width-1; x++) {
                if (getc(x, y, Charmap::DEPTH_FLOOR) == Charmap::WALL) {
                    putc(x, y, Charmap::DEPTH_FLOOR, Charmap::SPACE);
                }
            }
        }
    }

    //
    // Make randomly shaped rooms
    //
    // We use the map as a scratchpad for creating the room.
    //
    void rooms_all_create_random_shapes (int which)
    {
        //
        // Create a cellular automata like cave first
        //
        cave_gen();
        dump();

        //
        // Now carve out some empty regions in the cave
        //
        auto cnt = 0;
        while (cnt < map_carve_lines_cnt) {
            auto x1 = random_range(-10, map_width + 10);
            auto y1 = random_range(-10, map_height + 10);
            auto x2 = random_range(-10, map_width + 10);
            auto y2 = random_range(-10, map_height + 10);
            line_draw(point(x1, y1), 
                      point(x1, y2), 
                      Charmap::DEPTH_FLOOR,
                      Charmap::SPACE);
            line_draw(point(x1, y1), 
                      point(x2, y1), 
                      Charmap::DEPTH_FLOOR,
                      Charmap::SPACE);
            cnt ++;
        }
        dump();

        //
        // Now pull each room out of the level with a kind of inverse
        // flood fill.
        //
        for (auto y = 0; y < map_height; y++) {
            for (auto x = 0; x < map_width; x++) {
                if (!is_floor_at(x, y)) {
                    continue;
                }

                auto room_points = flood_erase(x, y, max_room_size);

                //
                // Filter to rooms of a certain size.
                //
                if (room_points.size() < min_room_size) {
                    continue;
                }

                //
                // Find the size of this random room.
                //
                auto minx = 9999;
                auto maxx = -9999;
                auto miny = 9999;
                auto maxy = -9999;
                for (auto p : room_points) {
                    auto rx = p.x;
                    auto ry = p.y;

                    if (rx < minx) {
                        minx = rx;
                    }
                    if (ry < miny) {
                        miny = ry;
                    }
                    if (rx > maxx) {
                        maxx = rx;
                    }
                    if (ry > maxy) {
                        maxy = ry;
                    }
                }

                auto rw = maxx - minx + 1;
                auto rh = maxy - miny + 1;
                rw += 2;
                rh += 2;

                //
                // Now we need to create the floor and wall vertical
                // room slices.
                //
                char rcells[rw][rh];
                memset(rcells, Charmap::NONE, sizeof(rcells));

                //
                // Copy the room points into the new array
                //
                for (auto p : room_points) {
                    auto rx = p.x;
                    auto ry = p.y;

                    rx -= minx;
                    ry -= miny;
                    rx ++;
                    ry ++;
                    rcells[rx][ry] = Charmap::FLOOR;
                }

                for (auto ry = 0; ry < rh; ry++) {
                    for (auto rx = 0; rx < rw; rx++) {
                        if (rcells[rx][ry] != Charmap::FLOOR) {
                            continue;
                        }

                        if (rcells[rx-1][ry] == Charmap::NONE) {
                            rcells[rx-1][ry] = Charmap::WALL;
                        }
                        if (rcells[rx+1][ry] == Charmap::NONE) {
                            rcells[rx+1][ry] = Charmap::WALL;
                        }
                        if (rcells[rx][ry-1] == Charmap::NONE) {
                            rcells[rx][ry-1] = Charmap::WALL;
                        }
                        if (rcells[rx][ry+1] == Charmap::NONE) {
                            rcells[rx][ry+1] = Charmap::WALL;
                        }
                    }
                }

                auto r = Room::random_room_new();
                for (auto rx = 0; rx < rw; rx++) {
                    std::string walls;
                    for (auto ry = 0; ry < rh; ry++) {
                        auto c = rcells[rx][ry+1];
                        if (c == Charmap::WALL) {
                            /*
                             * Random holes in the walls of rooms
                             */
                            if (!(rx % 2) and !(ry % 2)) {
                                if (random_range(0, 100) < 10) {
                                    walls += c;
                                } else {
                                    walls += ' ';
                                }
                            } else {
                                walls += c;
                            }
                        } else {
                            walls += ' ';
                        }
                    }
                    r->walls_data.push_back(walls);
                }

                for (auto rx = 0; rx < rw; rx++) {
                    std::string floor;
                    for (auto ry = 0; ry < rh; ry++) {
                        auto c = rcells[rx][ry+1];
                        if (c == Charmap::FLOOR) {
                            floor += c;
                        } else {
                            floor += ' ';
                        }
                    }
                    r->floor_data.push_back(floor);
                }

                for (auto rx = 0; rx < rw; rx++) {
                    std::string items;
                    for (auto ry = 0; ry < rh; ry++) {
                        items += ' ';
                    }
                    r->items_data.push_back(items);
                }

                r->finalize();
            }
        }

        //
        // Zero out the map as we were lazy and used it for a scratchpad
        // when creating rooms.
        //
        std::fill(cells.begin(), cells.end(), Charmap::NONE);
    }
};

class Dungeon *dungeon_test (void)
{
    auto d = new Dungeon(80, 80, 20);

    return (d);
}
