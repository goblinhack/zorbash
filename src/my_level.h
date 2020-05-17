//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_LEVEL_H_
#define _MY_LEVEL_H_

#include "my_point.h"
#include "my_time.h"
#include "my_depth.h"

class Level {
public:
    //
    // These are caches for fast lookup in display code
    //
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_chasm {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_gfx_large_shadow {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_visited {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_water {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_fade_in {};

    //
    // When this Level was made. Used to restore timestamps relative to this.
    //
    timestamp_t                timestamp_dungeon_created {};
    timestamp_t                timestamp_dungeon_saved {};

    //
    // Where we are in the world
    //
    point3d                    world_at;

    //
    // All randomness jumps off of this as the root
    //
    int                        seed {};

    //
    // Something moved on the map; update caches
    //
    bool                       map_changed {};

    bool                       cursor_needs_update {};
    bool                       cursor_found {};
    fpoint                     cursor_at;
    fpoint                     cursor_at_old;
    bool                       map_follow_player {};
    fpoint                     map_at;        // map tile location
    fpoint                     map_wanted_at; // map scroll desired at
    point                      pixel_map_at;  // map pixel location
    point                      map_tl;        // visible map tl
    point                      map_br;        // visible map br
    bool                       minimap_valid {};
    int                        mouse {-1};    // ticks for every move
    int                        mouse_old {-1};

    Thingp                     player = {};
    Thingp                     cursor = {};

    //
    // All things. The array index is part of the thing ID
    //
    class Thing_entropy {
    public:
        Thingp   ptr {};
        uint32_t id {};
    };
    std::array<class Thing_entropy, MAX_THINGS> all_thing_ptrs {};

    std::map<uint32_t, Thingp> all_things {};
    std::map<uint32_t, Thingp> all_active_things {};
    std::map<uint32_t, Thingp> all_gc_things {};

    //
    // Tile maps for rendering solid blocks of water etc...
    //
    std::array<std::array<bool, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    water_tile_map = {};
    std::array<std::array<bool, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    deep_water_tile_map = {};
    std::array<std::array<bool, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    lava_tile_map = {};
    std::array<std::array<bool, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    chasm_tile_map = {};

    //
    // All thing IDs
    //
    std::array<
      std::array<
        std::array<uint32_t, MAP_SLOTS>, MAP_HEIGHT>, MAP_WIDTH>
          all_thing_ids_at {};

    std::array<
      std::array<
        std::vector<Thingp>, MAP_HEIGHT>, MAP_WIDTH>
          all_thing_ptrs_at {};

    //
    // Animation loop counters for surface effects
    //
    int   water_step1 {};
    float water_step2 {};
    int   deep_water_step1 {};
    float deep_water_step2 {};
    int   lava_step1 {};
    float lava_step2 {};

    Level (void)
    {_
        newptr(this, "level");
    }

    ~Level (void)
    {_
        oldptr(this);
    }

    void alloc_thing_id(Thingp t);
    void realloc_thing_id(Thingp t);
    void free_thing_id(Thingp t);
    Thingp test_thing_ptr(uint32_t id);
    Thingp find_thing_ptr(uint32_t id);

    void remove_thing(int x, int y, uint32_t id);
    void remove_thing(point p, uint32_t id);

    void put_thing(int x, int y, uint32_t id);
    void put_thing(point p, uint32_t id);

    #define JOIN1(X,Y) X##Y
    #define JOIN(X,Y) JOIN1(X,Y)

    #define FOR_ALL_THINGS(level, t, x, y)                          \
        if (!(level)->is_oob(x, y)) {                               \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) { \
                verify(t);                                          \

    #define FOR_ALL_THINGS_END() } }

    #define FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z)              \
        if (!(level)->is_oob(x, y)) {                               \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) { \
                verify(t);                                          \
                auto tpp = t->tp();                                 \
                if (tpp->z_depth != z) {                            \
                    continue;                                       \
                }

    #define FOR_ALL_LIGHTS_AT_DEPTH(level, t, x, y)                 \
        if (!(level)->is_oob(x, y)) {                               \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) { \
                verify(t);                                          \
                if (!t->get_light_count()) {                        \
                    continue;                                       \
                }

    //
    // Things that move around and things that do not, but are interesting,
    // like food
    //
    #define FOR_ALL_INTERESTING_THINGS(level, t, x, y)                    \
        if (!(level)->is_oob(x, y)) {                                     \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) {       \
                verify(t);                                                \
                if (!t->is_interesting()) {                               \
                    continue;                                             \
                }                                                         \

    //
    // Things that move around and things that do not, but are interesting,
    // like food
    //
    #define FOR_ALL_COLLISION_THINGS(level, t, x, y)                      \
        if (!(level)->is_oob(x, y)) {                                     \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) {       \
                verify(t);                                                \
                if (!t->is_interesting() && !t->is_obstacle()) {          \
                    continue;                                             \
                }                                                         \

    //
    // Cursor path is the highlighted path the player follows.
    //
    #define FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y)                    \
        if (!(level)->is_oob(x, y)) {                                     \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) {       \
                verify(t);                                                \
                if (!t->is_cursor_path()) {                               \
                    continue;                                             \
                }                                                         \

    void display(void);
    void display_lava(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_chasm(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_water(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_deep_water(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void scroll_map(void);
    void display_anim(void);
    void scroll_map_to_player(void);
    void scroll_map_set_target(void);
    void display_map_things(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_map(void);
    void update_map(void);
    void update_minimap(void);
    void update_hazard_map(void);
    void cursor_check_if_scroll_needed(void);
    void cursor_find_on_visible_things(const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void cursor_move(void);
    void cursor_path_draw(point start, point end);
    void cursor_path_create(void);
    void cursor_path_clear(void);
    void clear(void);
    bool is_anything_at(const int x, const int y);
    bool is_anything_at(const point &p);
    bool is_door(const int x, const int y);
    bool is_door(const point &p);
    bool is_food(const int x, const int y);
    bool is_food(const point &p);
    bool is_key(const int x, const int y);
    bool is_key(const point &p);
    bool is_monst(const int x, const int y);
    bool is_monst(const point &p);

    bool is_floor(const int x, const int y);
    bool is_floor(const point &p);
    void set_floor(const int x, const int y);
    void unset_floor(const int x, const int y);

    bool is_corridor(const int x, const int y);
    bool is_corridor(const point &p);
    void set_corridor(const int x, const int y);
    void unset_corridor(const int x, const int y);

    bool is_blood(const int x, const int y);
    bool is_blood(const point &p);
    void set_blood(const int x, const int y);
    void unset_blood(const int x, const int y);

    bool is_wall(const int x, const int y);
    bool is_wall(const point &p);
    void set_wall(const int x, const int y);
    void unset_wall(const int x, const int y);

    bool is_water(const int x, const int y);
    bool is_water(const point &p);
    void set_water(const int x, const int y);
    void unset_water(const int x, const int y);

    bool is_lava(const int x, const int y);
    bool is_lava(const point &p);
    void set_lava(const int x, const int y);
    void unset_lava(const int x, const int y);

    bool is_chasm(const int x, const int y);
    bool is_chasm(const point &p);
    void set_chasm(const int x, const int y);
    void unset_chasm(const int x, const int y);

    bool is_hazard(const int x, const int y);
    bool is_hazard(const point &p);
    void set_hazard(const int x, const int y);
    void unset_hazard(const int x, const int y);

    bool is_secret_door(const int x, const int y);
    bool is_secret_door(const point &p);
    void set_secret_door(const int x, const int y);
    void unset_secret_door(const int x, const int y);

    bool is_corpse(const int x, const int y);
    bool is_corpse(const point &p);
    void set_corpse(const int x, const int y);
    void unset_corpse(const int x, const int y);

    bool is_deep_water(const int x, const int y);
    bool is_deep_water(const point &p);
    void set_deep_water(const int x, const int y);
    void unset_deep_water(const int x, const int y);

    bool is_dirt(const int x, const int y);
    bool is_dirt(const point &p);
    void set_dirt(const int x, const int y);
    void unset_dirt(const int x, const int y);

    bool is_rock(const int x, const int y);
    bool is_rock(const point &p);
    void set_rock(const int x, const int y);
    void unset_rock(const int x, const int y);

    bool is_dungeon(const int x, const int y);
    bool is_dungeon(const point &p);
    void set_dungeon(const int x, const int y);
    void unset_dungeon(const int x, const int y);

    //
    // Used in lighting, so inlined
    //
    inline bool is_oob (const int x, const int y, const int z)
    {_
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT) ||
                (z < 0) || (z >= MAP_DEPTH));
    }

    inline bool is_oob (const int x, const int y)
    {_
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT));
    }

    inline bool is_oob (const fpoint p)
    {_
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline bool is_oob (const point p)
    {_
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline bool is_oob (const spoint p)
    {_
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline uint8_t is_fade_in (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_fade_in, p.x, p.y));
    }

    inline uint8_t is_fade_in_unsafe (const point &p)
    {_
        return (get_unsafe(_is_fade_in, p.x, p.y));
    }

    inline uint8_t is_fade_in (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_fade_in, x, y));
    }

    inline uint8_t is_fade_in_unsafe (const int x, const int y)
    {_
        return (get_unsafe(_is_fade_in, x, y));
    }

    inline void incr_fade_in (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        auto v = get(_is_fade_in, x, y);
        if (v < 200) {
            v+=5;
            set(_is_fade_in, x, y, v);
        } else {
            set(_is_fade_in, x, y, (uint8_t)255);
        }
    }

    inline void incr_fade_in_unsafe (const int x, const int y)
    {_
        auto v = get_unsafe(_is_fade_in, x, y);
        if (v < 200) {
            v+=5;
            set_unsafe(_is_fade_in, x, y, v);
        } else {
            set(_is_fade_in, x, y, (uint8_t)255);
        }
    }

    inline void unset_fade_in (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_fade_in, x, y, (uint8_t)0);
    }

    inline void unset_fade_in_unsafe (const int x, const int y)
    {_
        set_unsafe(_is_fade_in, x, y, (uint8_t)0);
    }

    inline uint8_t is_visited (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_visited, p.x, p.y));
    }

    inline uint8_t is_visited_unsafe (const point &p)
    {_
        return (get_unsafe(_is_visited, p.x, p.y));
    }

    inline uint8_t is_visited (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_visited, x, y));
    }

    inline uint8_t is_visited_unsafe (const int x, const int y)
    {_
        return (get_unsafe(_is_visited, x, y));
    }

    inline void set_visited (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }

        if (!get(_is_visited, x, y)) {
            set(_is_fade_in, x, y, (uint8_t)1);
        }
    }

    inline void set_visited_unsafe (const int x, const int y)
    {_
        if (!get_unsafe(_is_visited, x, y)) {
            set_unsafe(_is_fade_in, x, y, (uint8_t)1);
        }
        set_unsafe(_is_visited, x, y, true);
    }

    inline void unset_visited (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_visited, x, y, false);
    }

    inline void unset_visited_unsafe (const int x, const int y)
    {_
        set_unsafe(_is_visited, x, y, false);
    }

    //
    // Used in lighting, so inlined
    //
    inline bool is_gfx_large_shadow (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_gfx_large_shadow, p.x, p.y));
    }

    inline bool is_gfx_large_shadow_unsafe (const point &p)
    {_
        return (get_unsafe(_is_gfx_large_shadow, p.x, p.y));
    }

    inline bool is_gfx_large_shadow (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_gfx_large_shadow, x, y));
    }

    inline bool is_gfx_large_shadow_unsafe (const int x, const int y)
    {_
        return (get_unsafe(_is_gfx_large_shadow, x, y));
    }

    inline void set_gfx_large_shadow (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_gfx_large_shadow, x, y, true);
    }

    inline void set_gfx_large_shadow_unsafe (const int x, const int y)
    {_
        set_unsafe(_is_gfx_large_shadow, x, y, true);
    }

    inline void unset_gfx_large_shadow (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_gfx_large_shadow, x, y, false);
    }

    inline void unset_gfx_large_shadow_unsafe (const int x, const int y)
    {_
        set_unsafe(_is_gfx_large_shadow, x, y, false);
    }

    void init(point3d at, int seed);
    const char *to_cstring(void);
    std::string to_string(void);
    void fini(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void log_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg_(const char *fmt, va_list args); // compile error without
    friend std::ostream& operator<<(std::ostream &out, Bits<const Level & > const my);
    friend std::istream& operator>>(std::istream &in, Bits<Level &> my);
};

#endif
