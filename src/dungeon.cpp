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
    std::vector<char>                         cells;
    //
    // If a cell has something in it
    //
    std::vector<int>                          in_use;
    //
    // Next to a space that could be an exit
    //
    std::vector<int>                          exit_candidate;
    //
    // Used temporarily for room generation
    // 
    std::vector<char>                         tmp;
    //
    // And the end of a corridor
    //
    std::vector<point>                        corridor_ends;

    //
    // The. Map.
    //
    int map_width                             {MAP_WIDTH};
    int map_height                            {MAP_HEIGHT};
    int map_depth                             {Charmap::DEPTH_MAX};
    int room_width                            {15};
    int room_height                           {15};
    int nodes_width                           {3};
    int nodes_height                          {3};

    //
    // High level view of the map.
    //
    Nodes                                     *nodes;

    //
    // We generate a cellular automata map and then carve that into
    // room fragments so we get curvy rooms.
    //
    uint32_t map_cellular_automata_fill_chance = 50;
    int map_cellular_automata_r1               = 5;
    int map_cellular_automata_r2               = 5;
    int map_cellular_automata_generations      = 5;

    //
    // After the cellular stage we erase portions of the map with
    // lines to makes isolated islands we then pull out as "rooms"
    //
    int map_carve_lines_cnt                    = 30;

    //
    // All possible rooms we will choose from. Initially these are fixed
    // rooms and we add more random ones onto this list.
    //
    std::vector<Roomp>                        all_rooms;

    //
    // First chosen
    //
    Roomp                                     room_first;

    //
    // Random lists of rooms to try and place
    //
    std::vector<Roomp>                        all_rooms_placed;

    //
    // Set if we fail to generate
    //
    bool generate_failed                      {false};

    //
    // What chance for fixed versus random rooms
    //
    uint32_t fixed_room_chance                {20};

    //
    // Chance of a corridor splitting
    //
    uint32_t corridor_fork_chance             {80};
    uint32_t tunnel_fork_chance               {95};

    //
    // Lower, longer corridors
    //
    uint32_t corridor_stop_chance_per_step    {3};
    uint32_t tunnel_grow_chance               {1};

    //
    // How often a random room is locked
    //
    uint32_t room_locked_chance               {5};

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

    void finish_constructor (void)
    {_
        cells.resize(map_width * map_height * Charmap::DEPTH_MAX, 
                     Charmap::SPACE);
        tmp.resize(map_width * map_height * Charmap::DEPTH_MAX, 
                   Charmap::SPACE);
        in_use.resize(map_width * map_height * Charmap::DEPTH_MAX, 
                      false);
        exit_candidate.resize(map_width * map_height * Charmap::DEPTH_MAX, 
                              false);

        nodes = new Nodes(nodes_width, nodes_height);
        room_width  = map_width / nodes_width;
        room_height  = map_height / nodes_height;

        place_rooms();
    }

    void debug (std::string s)
    {_
        // return
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
        finish_constructor();
    }

    Dungeon ()
    {_
        finish_constructor();
    }

    int offset (const int x, const int y, const int z)
    {_
        auto offset = (map_width * map_height) * z;
        offset += (map_width) * y;
        offset += x;

        return (offset);
    }

    int offset (const int x, const int y)
    {_
        auto offset = (map_width) * y;
        offset += x;

        return (offset);
    }

    bool is_oob (const int x, const int y, const int z)
    {_
        return ((x < 0) || (x >= map_width) ||
                (y < 0) || (y >= map_height) ||
                (z < 0) || (z >= map_depth));
    }

    bool is_oob (const int x, const int y)
    {_
        return ((x < 0) || (x >= map_width) ||
                (y < 0) || (y >= map_height));
    }

    char *cell_addr (const int x, const int y, const int z)
    {_
        if (is_oob(x, y, z)) {
            LOG("out of bounds on cell map %d,%d,%d vs %d,%d,%d", 
                x, y, z, map_width, map_height, map_depth);
            return (nullptr);
        }

        return (&cells[offset(x, y, z)]);
    }

    char *tmp_addr (const int x, const int y, const int z)
    {_
        if (is_oob(x, y, z)) {
            LOG("out of bounds on tmp map %d,%d,%d vs %d,%d,%d", 
                x, y, z, map_width, map_height, map_depth);
            return (nullptr);
        }

        return (&tmp[offset(x, y, z)]);
    }

    int *in_use_addr (const int x, const int y)
    {_
        if (is_oob(x, y)) {
            LOG("out of bounds on in_use map %d,%d vs %d,%d", 
                x, y, map_width, map_height);
            return (nullptr);
        }

        return (&in_use[offset(x, y)]);
    }

    int *exit_candidate_addr (const int x, const int y)
    {_
        if (is_oob(x, y)) {
            LOG("out of bounds on in_use map %d,%d vs %d,%d", 
                x, y, map_width, map_height);
            return (nullptr);
        }

        return (&exit_candidate[offset(x, y)]);
    }

    /*
     * Puts a tile on the map
     */
    void putc (const int x, const int y, const int z, const char c)
    {_
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
    {_
        auto p = cell_addr(x, y, z);
        if (p != nullptr) {
            return (*p);
        }
        return (Charmap::NONE);
    }

    /*
     * Puts a tile on the map
     */
    void puttmp (const int x, const int y, const int z, const char c)
    {_
        auto p = tmp_addr(x, y, z);
        if (p != nullptr) {
            *p = c;
        }
    }

    /*
     * Gets a tile of the map or None
     */
    char gettmp (const int x, const int y, const int z)
    {_
        auto p = tmp_addr(x, y, z);
        if (p != nullptr) {
            return (*p);
        }
        return (Charmap::NONE);
    }

    /*
     * Puts a tile on the map
     */
    void put_exit_candidate (const int x, const int y, const bool v)
    {_
        auto p = exit_candidate_addr(x, y);
        if (p != nullptr) {
            *p = v;
        }
    }

    /*
     * Gets a tile of the map or None
     */
    bool get_exit_candidate (const int x, const int y)
    {_
        auto p = exit_candidate_addr(x, y);
        if (p != nullptr) {
            return (*p);
        }
        return (false);
    }

    /*
     * Puts a tile on the map
     */
    void put_in_use (const int x, const int y, const bool v)
    {_
        auto p = in_use_addr(x, y);
        if (p != nullptr) {
            *p = v;
        }
    }

    /*
     * Gets a tile of the map or None
     */
    bool get_in_use (const int x, const int y)
    {_
        auto p = in_use_addr(x, y);
        if (p != nullptr) {
            return (*p);
        }
        return (false);
    }

    bool is_anything_at (const int x, const int y)
    {_
        for (auto d = 0; d < map_depth; d++) {
            auto c = getc(x, y, d);
            if (c != Charmap::SPACE) {
                return true;
            }
        }
        return false;
    }

    bool is_anything_at (const int x, const int y, const int z)
    {_
        auto c = getc(x, y, z);
        if (c != Charmap::SPACE) {
            return true;
        }
        return false;
    }

    bool is_floor_or_corridor_at (const int x, const int y)
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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
    {_
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

    /*
     * Cellular Automata Method for Generating Random Cave-Like Levels
     */
    char map_cellular_automata_random_tile (void)
    {_
        if (random_range(0, 100) < map_cellular_automata_fill_chance) {
            return (Charmap::SPACE);
        } else {
            return (Charmap::FLOOR);
        }
    }

    //
    // Grow our cells
    //
    void cave_generation (void)
    {_
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
                    // gives smaller rooms
                    // puttmp(x, y, Charmap::DEPTH_FLOOR, Charmap::SPACE);
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
    {_
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
            putc(map_width-2, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-3, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-4, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(map_width-5, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(1, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(2, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(3, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(4, y, Charmap::DEPTH_FLOOR, Charmap::WALL);
        }

        for (x=0; x < map_width; x++) {
            putc(x, 0, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-1, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-2, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-3, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-4, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, map_height-5, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 1, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 2, Charmap::DEPTH_FLOOR, Charmap::WALL);
            putc(x, 3, Charmap::DEPTH_FLOOR, Charmap::WALL);
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
        std::fill(cells.begin(), cells.end(), Charmap::SPACE);
        std::fill(tmp.begin(), tmp.end(), Charmap::SPACE);
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
                        if (is_anything_at(x + dx, y + dy)) {
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
        all_rooms_placed.push_back(room);

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
        Roomp place;

        place = all_rooms.back();
        all_rooms.pop_back();

        return (place);
    }

    //
    // Place the first room in a level, in the center ish. First room should
    // not be a fixed room.
    //
#if 0
    bool room_place_first (void)
    {_
        auto room_place_tries = 0;
        for (;;) {
            //
            // First room should not be fixed.
            //
            auto room = get_next_random_room();

            auto x = (map_width / 2);
            auto y = (map_height / 2);
            x -= (room->width / 2);
            y -= (room->height / 2);

            if (room_place_if_no_overlaps(room, x, y)) {
                room_first = room;

                auto roomno = room->roomno;
                roomno_can_be_used_as_start[roomno] = true;
                roomno_can_be_used_as_exit[roomno] = false;
                return true;
            }

            if (room_place_tries > 10000) {
                ERR("Could not place first room");
                return false;
            }

            room_place_tries ++;
        }
    }
#endif

    //
    // Search the whole level for possible room exits
    //
    std::vector<point> rooms_find_all_exits (void)
    {_
        std::fill(in_use.begin(), in_use.end(), false);
        std::fill(exit_candidate.begin(), exit_candidate.end(), false);

        //
        // First pass find all the places we could place a corridor
        //
        for (auto y : range<int>(corridor_spacing, 
                                 map_height - corridor_spacing)) {
            for (auto x : range<int>(corridor_spacing, 
                                     map_width - corridor_spacing)) {

                if (not is_floor_or_corridor_at(x, y)) {
                    continue;
                }

                if (is_wall_at(x, y)) {
                    put_in_use(x, y, true);
                    continue;
                }

                if (not is_corridor_at(x, y)) {
                    continue;
                }

                if (not is_floor_or_corridor_at(x + 1, y) ||
                    not is_floor_or_corridor_at(x - 1, y) ||
                    not is_floor_or_corridor_at(x, y - 1) ||
                    not is_floor_or_corridor_at(x, y + 1)) {
                    put_exit_candidate(x, y, true);
                }
            }
        }

        //
        // Possible start points for corridors.
        //
        std::vector<point> possible_new_corridors;

        //
        // Next pass filter all places we could start that are too near
        // to other corridors that already exist, or are candidates to
        // create.
        //
        auto border = corridor_spacing;

        for (auto y : range<int>(border + 1, map_height - (border + 1))) {
            for (auto x : range<int>(border + 1, map_width - (border + 1))) {

                if (not get_exit_candidate(x, y)) {
                    continue;
                }

                auto c = - corridor_spacing;
                auto d = corridor_spacing + 1;

                //
                // Check no corridor adjacent to any other one nearby. Or
                // any new one we plan.
                //
                auto skip = false;
                for (auto dx : range<int>(c, d)) {
                    for (auto dy : range<int>(c, d)) {
                        if ((dx == 0) and (dy == 0)) {
                            continue;
                        }

                        if (get_exit_candidate(x + dx, y + dy)) {
                            put_in_use(x + dx, y + dy, true);
                            skip = true;
                            break;
                        }

                        if (is_corridor_at(x + dx, y + dy)) {
                            put_in_use(x + dx, y + dy, true);
                            skip = true;
                            break;
                        }
                    }
                    if (skip) {
                        break;
                    }
                }
                if (skip) {
                    continue;
                }

                possible_new_corridors.push_back(point(x, y));
            }
        }

        //
        // Return the final list of corridor starts
        //
        return possible_new_corridors;
    }

    //
    // Grow a corridor in the given direction
    //
    void room_corridor_draw (int x, int y, int dx, int dy, 
                             int clen=0, 
                             int fork_count=0,
                             char c=Charmap::CORRIDOR)
    {_
        x += dx;
        y += dy;

        if (x < 2) {
            return;
        } else if (x >= map_width - 3) {
            return;
        }

        if (y < 2) {
            return;
        } else if (y >= map_height - 3) {
            return;
        }

        if (getc(x, y, Charmap::DEPTH_FLOOR) == Charmap::NONE) {
            return;
        }

        if (is_floor_or_corridor_at(x, y)) {
            return;
        }

        clen ++;

        putc(x, y, Charmap::DEPTH_FLOOR, c);

        //
        // Reached the end of a corridor?
        //
        auto stop_chance = clen * corridor_stop_chance_per_step;
        auto r = random_range(1, 100);
        if (r < stop_chance) {
            corridor_ends.push_back(point(x, y));
            return;
        }

        //
        // Stopped growing. Fork the corridor.
        // Don't do corridors forks adjacent to each other.
        //
        if ((fork_count < 3) and ((clen % 2) == 0)) {
            if (random_range(1, 100) < corridor_fork_chance) {
                room_corridor_draw(x, y, dy, dx, clen, fork_count + 1, c);
            }

            if (random_range(1, 100) < corridor_fork_chance) {
                room_corridor_draw(x, y, -dy, -dx, clen, fork_count + 1, c);
            }
        }

        //
        // Keep on growing
        //
        room_corridor_draw(x, y, dx, dy, clen, fork_count + 1, c);
    }

    //
    // For each room exit (and we search the whole room) grow corridors
    //
    void rooms_all_grow_new_corridors (void)
    {_
        auto possible_new_corridors = rooms_find_all_exits();

        //
        // For each possible direction of a corridor, sprout one.
        //
        for (auto coord : possible_new_corridors) {
            auto x = coord.x;
            auto y = coord.y;

            // a b c
            // d * f
            // g h i
            auto b = get_in_use(x, y-1);
            auto d = get_in_use(x-1, y);
            auto f = get_in_use(x+1, y);
            auto h = get_in_use(x, y+1);

            if (not b) {
                room_corridor_draw(x, y, 0, -1, 0, 0, Charmap::CORRIDOR);
            }
            if (not d) {
                room_corridor_draw(x, y, -1, 0, 0, 0, Charmap::CORRIDOR);
            }
            if (not f) {
                room_corridor_draw(x, y, 1, 0, 0, 0, Charmap::CORRIDOR);
            }
            if (not h) {
                room_corridor_draw(x, y, 0, 1, 0, 0, Charmap::CORRIDOR);
            }
        }
    }

    //
    // Search for corridor end points and try to dump rooms there.
    //
#if 0
    bool rooms_all_try_to_place_at_end_of_corridors (void)
    {_
        auto room = get_next_room();
        auto placed_a_room = false;

        //
        // For all corridor end points.
        //
        for (auto coord : corridor_ends) {
            auto cx = coord.x;
            auto cy = coord.y;

            //
            // Try to attach room only by it's edges. This is a bit quicker
            // than searching the room for exits.
            //
            for (auto edge : room->edge_exits) {
                auto rx = edge.x;
                auto ry = edge.y;
                auto x = cx - rx;
                auto y = cy - ry;

                if (room_place_if_no_overlaps(room, x - 1, y) ||
                    room_place_if_no_overlaps(room, x + 1, y) ||
                    room_place_if_no_overlaps(room, x, y - 1) ||
                    room_place_if_no_overlaps(room, x, y + 1)) {
                    placed_a_room = true;
                }

                if (placed_a_room) {
                    debug("^^^ placed a room at the end of a corridor ^^^");
                    break;
                }
            }

            if (placed_a_room) {
                break;
            }
        }

        //
        // Placed at least one?
        //
        return placed_a_room;
    }

    //
    // Place remaining rooms hanging off of the corridors of the last.
    //
    bool rooms_place_remaining (int place)
    {_
        corridor_ends.resize(0);
        rooms_all_grow_new_corridors();
        debug("^^^ grown new corridors ^^^");

        auto room_place_tries = 0;
        while (place--) {
            room_place_tries ++;
            if (room_place_tries > rooms_on_level * 100) {
                LOG("Tried to place rooms for too long, made %d rooms",
                     rooms_on_level);
                dump();
                return false;
            }

            //
            // If we place at least one new room, we will have new corridors
            // to grow.
            //
            if (rooms_all_try_to_place_at_end_of_corridors()) {
                rooms_all_grow_new_corridors();
                debug("^^^ grown new corridors after room placing ^^^");
            }
        }

        return true;
    }
    
    //
    // Place all rooms
    //
    bool rooms_place_all (int place)
    {_
        if (not room_place_first()) {
            return false;
        }
        debug("^^^ placed first rooms ^^^");

        if (not rooms_place_remaining(place)) {
            return false;
        }

        return true;
    }
#endif

    void draw_corridor (point start, point end, char w)
    {
        dmap d;
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
        auto p = dmap_solve(&d, start, end);
        for (auto c : p) {
            putc(c.x, c.y, Charmap::DEPTH_FLOOR, w);
        }
    }

    void place_rooms (void)
    {
        auto tries = 1000;

        std::vector<Roomp> rooms;

        if (!tries--) {
            DIE("too many tries to place rooms");
        }
        std::fill(cells.begin(), cells.end(), Charmap::SPACE);

        all_rooms = Room::all_rooms;
        std::shuffle(all_rooms.begin(), all_rooms.end(), rng);

        Roomp room_node[nodes_width][nodes_height];
        memset(room_node, 0, sizeof(room_node));

        //
        // Place the initial rooms. Choose only small ones we know will
        // fit.
        //
        auto nrooms = (int) Room::all_rooms.size();
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
                for (auto place_room = 0; place_room < nrooms; place_room++) {
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

                    r->at.x = x * room_width;
                    r->at.y = y * room_height;

                    rooms.push_back(r);
                    room_node[x][y] = r;

                    if (room_place_if_no_overlaps(r, r->at.x, r->at.y)) {
                        placed = true;
                        break;
                    }
                }

                if (!placed) {
                    debug("^^^ cannot place initial rooms ^^^");
                    DIE("could not place initial rooms");
                }
            }
        }

        //
        // Join the corridors of each room
        //
        for (auto x = 0; x < nodes->nodes_width; x++) {
            for (auto y = 0; y < nodes->nodes_height; y++) {

                auto n = nodes->getn(x, y);
                if (!n->depth) {
                    continue;
                }

                if (n->depth == nodes->depth_obstacle) {
                    continue;
                }

                auto r = room_node[x][y];

                if (n->has_exit_down) {
                    auto o = room_node[x][y+1];
                    auto rdoori = random_range(0, r->down_exits.size());
                    auto odoori = random_range(0, o->up_exits.size());
                    auto rdoor = r->down_exits[rdoori];
                    auto odoor = o->up_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    draw_corridor(start, end, Charmap::CORRIDOR);
                }

                if (n->has_exit_right) {
                    auto o = room_node[x+1][y];
                    auto rdoori = random_range(0, r->right_exits.size());
                    auto odoori = random_range(0, o->left_exits.size());
                    auto rdoor = r->right_exits[rdoori];
                    auto odoor = o->left_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    draw_corridor(start, end, Charmap::CORRIDOR);
                }

                if (n->has_secret_exit_down) {
                    auto o = room_node[x][y+1];
                    auto rdoori = random_range(0, r->down_exits.size());
                    auto odoori = random_range(0, o->up_exits.size());
                    auto rdoor = r->down_exits[rdoori];
                    auto odoor = o->up_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    draw_corridor(start, end, Charmap::DUSTY);
                }

                if (n->has_secret_exit_right) {
                    auto o = room_node[x+1][y];
                    auto rdoori = random_range(0, r->right_exits.size());
                    auto odoori = random_range(0, o->left_exits.size());
                    auto rdoor = r->right_exits[rdoori];
                    auto odoor = o->left_exits[odoori];

                    auto start = r->at + rdoor;
                    auto end = o->at + odoor;
                    draw_corridor(start, end, Charmap::DUSTY);
                }
            }
        }

        debug("^^^ initial placement of rooms ^^^");

        auto mx = map_width / 2;
        auto my = map_height / 2;

        if (mx) {
            DIE("mx");
        }

        /*
         * Repeat placing all rooms bar one random one. Try to move
         * that random one closer to the center. Repeat.
         */
        tries = 50;
        while (tries--) {
            for (unsigned int rs = 0; 
                 rs < (unsigned int) rooms.size(); 
                 rs++) {

                auto r = rooms[rs];
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

                        auto r = rooms[ri++];
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

                        auto r = rooms[ri++];
                        if (r->roomno != skip_roomno) {
                            continue;
                        }

                        if (r->at.x + r->width > mx) {
                            if (room_can_be_placed(r, r->at.x - 2, r->at.y)) {
                                r->at.x--;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        if (r->at.x < mx) {
                            if (room_can_be_placed(r, r->at.x + 2, r->at.y)) {
                                r->at.x++;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        if (r->at.y + r->height > my) {
                            if (room_can_be_placed(r, r->at.x, r->at.y - 2)) {
                                r->at.y--;
                                room_place(r, r->at.x, r->at.y);
                                break;
                            }
                        }

                        if (r->at.y < my) {
                            if (room_can_be_placed(r, r->at.x, r->at.y + 2)) {
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
        debug("^^^ placed all rooms ^^^");
    }
};

class Dungeon *dungeon_test (void)
{
    for (;;) {
        auto d = new Dungeon(MAP_WIDTH, MAP_HEIGHT, 6, 3);

        if (not d->generate_failed) {
            return (d);
        }
    }
}
