//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_LEVEL_H_
#define _MY_LEVEL_H_

#include "my_point.h"
#include "my_time.h"
#include "my_depth.h"
#include "my_particle.h"
#include "my_dungeon.h"
#include "my_thing_id.h"

class Level {
public:
    //
    // These are caches for fast lookup in display code
    //
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_light_blocker {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_lit {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_visited {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _fade_in_map {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _heatmap {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_acid {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_chasm {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_door {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_entrance {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_exit {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_fire {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_food {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_generator {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_gold {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_key {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_monst {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_mundane_item {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_potion {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_smoke {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_water {};

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
    bool                       cursor_found {};
    bool                       cursor_needs_update {};
    bool                       heatmap_valid {};
    bool                       is_starting {}; // Loading level
    bool                       map_changed {}; // Something moved on the map
    bool                       map_follow_player {};
    bool                       minimap_valid {};
    fpoint                     cursor_at;
    fpoint                     cursor_at_old;
    fpoint                     map_at;        // map tile location
    fpoint                     map_wanted_at; // map scroll desired at
    float                      wobble = {};   // Fades when set
    int                        mouse {-1};    // ticks for every move
    int                        mouse_old {-1};
    int                        seed {};
    point                      map_br;        // visible map br
    point                      map_tl;        // visible map tl
    point                      pixel_map_at;  // map pixel location
    Thingp                     player = {};
    Thingp                     cursor = {};
    std::map<ThingId, Thingp> all_things {};
    std::map<ThingId, Thingp> all_active_things {};
    std::map<ThingId, Thingp> all_gc_things {};

    //
    // Tile maps for rendering solid blocks of water etc...
    //
    std::array<std::array<uint8_t, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    water_tile_map = {};
    std::array<std::array<uint8_t, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    deep_water_tile_map = {};
    std::array<std::array<uint8_t, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    lava_tile_map = {};
    std::array<std::array<uint8_t, MAP_HEIGHT + 8>, MAP_WIDTH + 8>
                    chasm_tile_map = {};
    //
    // All thing IDs
    //
    std::array<
      std::array<
        std::array<ThingId, MAP_SLOTS>, MAP_HEIGHT>, MAP_WIDTH>
          all_thing_ids_at {};

    std::array<
      std::array<
        std::vector<Thingp>, MAP_HEIGHT>, MAP_WIDTH>
          all_thing_ptrs_at {};

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////

    //
    // Animation loop counters for surface effects
    //
    int   water_step1 {};
    float water_step2 {};
    int   deep_water_step1 {};
    float deep_water_step2 {};
    int   lava_step1 {};
    float lava_step2 {};

    //
    // For thing effects, like jumping
    //
    std::vector<Particle> all_internal_particles;

    //
    // For things like move of items into inventory
    //
    std::vector<Particle> all_external_particles;

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    /////////////////////////////////////////////////////////////////////////

    Level (void);
    ~Level (void);

    void remove_thing(int x, int y, ThingId id);
    void remove_thing(point p, ThingId id);

    void put_thing(int x, int y, ThingId id);
    void put_thing(point p, ThingId id);

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
                if (t->z_depth() != z) {                            \
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
    // Things you can bump into
    //
    #define FOR_ALL_COLLISION_THINGS(level, t, x, y)                      \
        if (!(level)->is_oob(x, y)) {                                     \
            for (auto t : getref(level->all_thing_ptrs_at, x, y)) {       \
                verify(t);                                                \
                if (!t->is_interesting() &&                               \
                    !t->is_attackable() &&                                \
                    !t->ai_obstacle()) {                                  \
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

    void clear(void);
    void cursor_check_if_scroll_needed(void);
    void cursor_find_on_visible_things(const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void cursor_move(void);
    void cursor_path_clear(void);
    void cursor_path_create(void);
    void cursor_path_draw(point start, point end);
    void display(void);
    void display_anim(void);
    void display_blood(void);
    void display_chasm(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_deep_water(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_lava(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_map(void);
    void display_map_things(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void display_water(const int fbo, const uint16_t minx, const uint16_t miny, const uint16_t maxx, const uint16_t maxy);
    void scroll_map(void);
    void scroll_map_set_target(void);
    void scroll_map_to_player(void);
    void tick(void);
    void update_all_ticks(void);
    void update_hazard_tile_map(void);
    void update_map(void);
    void update_minimap(void);

    void set_wobble(float);
    float get_wobble(void) const;
    float update_wobble(void);
    bool screen_shake_begin(void);
    void screen_shake_end(void);

    bool is_anything_at (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }

        for (auto& t : get(all_thing_ptrs_at, x, y)) {
            if (t) {
                verify(t);
                return (true);
            }
        }
        return (false);
    }

    bool is_anything_at (const point &p)
    {_
        return (is_anything_at(p.x, p.y));
    }

    uint8_t is_lava (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_lava, p.x, p.y));
    }

    uint8_t is_lava (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_lava, x, y));
    }

    void set_is_lava (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_lava, x, y, (uint8_t)1);
    }

    void unset_is_lava (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_lava, x, y, (uint8_t)1);
    }

    uint8_t is_acid (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_acid, p.x, p.y));
    }

    uint8_t is_acid (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_acid, x, y));
    }

    void set_is_acid (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_acid, x, y, (uint8_t)1);
    }

    void unset_is_acid (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_acid, x, y, (uint8_t)1);
    }

    uint8_t is_chasm (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_chasm, x, y));
    }

    uint8_t is_chasm (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_chasm, p.x, p.y));
    }

    void set_is_chasm (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_chasm, x, y, (uint8_t)1);
    }

    void unset_is_chasm (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_chasm, x, y, (uint8_t)1);
    }

    uint8_t is_hazard (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_hazard, p.x, p.y));
    }

    uint8_t is_hazard (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_hazard, x, y));
    }

    void set_is_hazard (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_hazard, x, y, (uint8_t)1);
    }

    void unset_is_hazard (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_hazard, x, y, (uint8_t)1);
    }

    uint8_t is_secret_door (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_secret_door, p.x, p.y));
    }

    uint8_t is_secret_door (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_secret_door, x, y));
    }

    void set_is_secret_door (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_secret_door, x, y, (uint8_t)1);
    }

    void unset_is_secret_door (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_secret_door, x, y, (uint8_t)1);
    }

    uint8_t is_generator (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_generator, p.x, p.y));
    }

    uint8_t is_generator (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_generator, x, y));
    }

    void set_is_generator (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_generator, x, y, (uint8_t)1);
    }

    void unset_is_generator (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_generator, x, y, (uint8_t)1);
    }

    uint8_t is_potion (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_potion, p.x, p.y));
    }

    uint8_t is_potion (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_potion, x, y));
    }

    void set_is_potion (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_potion, x, y, (uint8_t)1);
    }

    void unset_is_potion (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_potion, x, y, (uint8_t)1);
    }

    uint8_t is_blood (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_blood, p.x, p.y));
    }

    uint8_t is_blood (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_blood, x, y));
    }

    void set_is_blood (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_blood, x, y, (uint8_t)1);
    }

    void unset_is_blood (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_blood, x, y, (uint8_t)1);
    }

    uint8_t is_water (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_water, p.x, p.y));
    }

    uint8_t is_water (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_water, x, y));
    }

    void set_is_water (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_water, x, y, (uint8_t)1);
    }

    void unset_is_water (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_water, x, y, (uint8_t)1);
    }

    uint8_t is_deep_water (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_deep_water, p.x, p.y));
    }

    uint8_t is_deep_water (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_deep_water, x, y));
    }

    void set_is_deep_water (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_deep_water, x, y, (uint8_t)1);
    }

    void unset_is_deep_water (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_deep_water, x, y, (uint8_t)1);
    }

    uint8_t is_wall (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_wall, p.x, p.y));
    }

    uint8_t is_wall (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_wall, x, y));
    }

    void set_is_wall (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_wall, x, y, (uint8_t)1);
    }

    void unset_is_wall (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_wall, x, y, (uint8_t)1);
    }

    uint8_t is_corridor (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_corridor, p.x, p.y));
    }

    uint8_t is_corridor (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_corridor, x, y));
    }

    void set_is_corridor (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_corridor, x, y, (uint8_t)1);
    }

    void unset_is_corridor (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_corridor, x, y, (uint8_t)1);
    }

    uint8_t is_dirt (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_dirt, p.x, p.y));
    }

    uint8_t is_dirt (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_dirt, x, y));
    }

    void set_is_dirt (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_dirt, x, y, (uint8_t)1);
    }

    void unset_is_dirt (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_dirt, x, y, (uint8_t)1);
    }

    uint8_t is_floor (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_floor, x, y));
    }

    void set_is_floor (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_floor, x, y, (uint8_t)1);
    }

    void unset_is_floor (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_floor, x, y, (uint8_t)1);
    }

    uint8_t is_rock (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_rock, p.x, p.y));
    }

    uint8_t is_rock (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_rock, x, y));
    }

    void set_is_rock (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_rock, x, y, (uint8_t)1);
    }

    void unset_is_rock (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_rock, x, y, (uint8_t)1);
    }

    uint8_t is_dungeon (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_dungeon, p.x, p.y));
    }

    uint8_t is_dungeon (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_dungeon, x, y));
    }

    void set_dungeon (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        incr(_is_dungeon, x, y, (uint8_t)1);
    }

    void unset_dungeon (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        map_changed = true;
        decr(_is_dungeon, x, y, (uint8_t)1);
    }

    uint8_t is_corpse (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_corpse, p.x, p.y));
    }

    uint8_t is_corpse (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_corpse, x, y));
    }

    void set_is_corpse (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_corpse, x, y, (uint8_t)1);
    }

    void unset_is_corpse (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_corpse, x, y, (uint8_t)1);
    }

    uint8_t is_fire (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_fire, p.x, p.y));
    }

    uint8_t is_fire (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_fire, x, y));
    }

    void set_is_fire (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_fire, x, y, (uint8_t)1);
    }

    void unset_is_fire (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_fire, x, y, (uint8_t)1);
    }

    uint8_t is_monst (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_monst, p.x, p.y));
    }

    uint8_t is_monst (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_monst, x, y));
    }

    void set_is_monst (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_monst, x, y, (uint8_t)1);
    }

    void unset_is_monst (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_monst, x, y, (uint8_t)1);
    }

    uint8_t is_door (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_door, p.x, p.y));
    }

    uint8_t is_door (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_door, x, y));
    }

    void set_is_door (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_door, x, y, (uint8_t)1);
    }

    void unset_is_door (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_door, x, y, (uint8_t)1);
    }

    uint8_t is_key (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_key, p.x, p.y));
    }

    uint8_t is_key (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_key, x, y));
    }

    void set_is_key (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_key, x, y, (uint8_t)1);
    }

    void unset_is_key (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_key, x, y, (uint8_t)1);
    }

    uint8_t is_food (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_food, p.x, p.y));
    }

    uint8_t is_food (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_food, x, y));
    }

    void set_is_food (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_food, x, y, (uint8_t)1);
    }

    void unset_is_food (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_food, x, y, (uint8_t)1);
    }

    uint8_t is_treasure (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_treasure, p.x, p.y));
    }

    uint8_t is_treasure (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_treasure, x, y));
    }

    void set_is_treasure (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_treasure, x, y, (uint8_t)1);
    }

    void unset_is_treasure (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_treasure, x, y, (uint8_t)1);
    }

    uint8_t is_mundane_item (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_mundane_item, p.x, p.y));
    }

    uint8_t is_mundane_item (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_mundane_item, x, y));
    }

    void set_is_mundane_item (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_mundane_item, x, y, (uint8_t)1);
    }

    void unset_is_mundane_item (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_mundane_item, x, y, (uint8_t)1);
    }

    uint8_t is_gold (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_gold, p.x, p.y));
    }

    uint8_t is_gold (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_gold, x, y));
    }

    void set_is_gold (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_gold, x, y, (uint8_t)1);
    }

    void unset_is_gold (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_gold, x, y, (uint8_t)1);
    }

    uint8_t is_entrance (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_entrance, p.x, p.y));
    }

    uint8_t is_entrance (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_entrance, x, y));
    }

    void set_is_entrance (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_entrance, x, y, (uint8_t)1);
    }

    void unset_is_entrance (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_entrance, x, y, (uint8_t)1);
    }

    uint8_t is_exit (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_exit, p.x, p.y));
    }

    uint8_t is_exit (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_exit, x, y));
    }

    void set_is_exit (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_exit, x, y, (uint8_t)1);
    }

    void unset_is_exit (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_exit, x, y, (uint8_t)1);
    }

    uint8_t is_smoke (const point &p)
    {_
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_smoke, p.x, p.y));
    }

    uint8_t is_smoke (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_smoke, x, y));
    }

    void set_is_smoke (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        incr(_is_smoke, x, y, (uint8_t)1);
    }

    void unset_is_smoke (const int x, const int y)
    {_
        if (unlikely(is_oob(x, y))) {
            return;
        }
        decr(_is_smoke, x, y, (uint8_t)1);
    }

    uint8_t heatmap(const point &p);
    uint8_t heatmap_no_check(const point &p);
    uint8_t heatmap(const int x, const int y);
    uint8_t heatmap_no_check(const int x, const int y);
    void incr_heatmap(const int x, const int y);
    void incr_heatmap_no_check(const int x, const int y);
    void unset_heatmap(const int x, const int y);
    void unset_heatmap_no_check(const int x, const int y);
    void update_heatmap(void);

    //
    // Used in lighting, so inlined
    //
    inline bool is_oob (const int x, const int y, const int z)
    {
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT) ||
                (z < 0) || (z >= MAP_DEPTH));
    }

    inline bool is_oob (const int x, const int y)
    {
        return ((x < 0) || (x >= MAP_WIDTH) ||
                (y < 0) || (y >= MAP_HEIGHT));
    }

    inline bool is_oob (const fpoint p)
    {
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline bool is_oob (const point p)
    {
        return ((p.x < 0) || (p.x >= MAP_WIDTH) ||
                (p.y < 0) || (p.y >= MAP_HEIGHT));
    }

    inline uint8_t fade_in_map (const point &p)
    {
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_fade_in_map, p.x, p.y));
    }

    inline uint8_t fade_in_map_no_check (const point &p)
    {
        return (get_no_check(_fade_in_map, p.x, p.y));
    }

    inline uint8_t fade_in_map (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_fade_in_map, x, y));
    }

    inline uint8_t fade_in_map_no_check (const int x, const int y)
    {
        return (get_no_check(_fade_in_map, x, y));
    }

    inline void incr_fade_in (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        auto v = get(_fade_in_map, x, y);
        if (v < 200) {
            v+=5;
            set(_fade_in_map, x, y, v);
        } else {
            set(_fade_in_map, x, y, (uint8_t)255);
        }
    }

    inline void incr_fade_in_no_check (const int x, const int y)
    {
        auto v = get_no_check(_fade_in_map, x, y);
        if (v < 200) {
            v+=5;
            set_no_check(_fade_in_map, x, y, v);
        } else {
            set(_fade_in_map, x, y, (uint8_t)255);
        }
    }

    inline void unset_fade_in (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_fade_in_map, x, y, (uint8_t)0);
    }

    inline void unset_fade_in_no_check (const int x, const int y)
    {
        set_no_check(_fade_in_map, x, y, (uint8_t)0);
    }

    inline uint8_t is_visited (const point &p)
    {
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_visited, p.x, p.y));
    }

    inline uint8_t is_visited_no_check (const point &p)
    {
        return (get_no_check(_is_visited, p.x, p.y));
    }

    inline uint8_t is_visited (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_visited, x, y));
    }

    inline uint8_t is_visited_no_check (const int x, const int y)
    {
        return (get_no_check(_is_visited, x, y));
    }

    inline void set_visited (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }

        if (!get(_is_visited, x, y)) {
            set(_fade_in_map, x, y, (uint8_t)1);
        }
    }

    inline void set_visited_no_check (const int x, const int y)
    {
        if (!get_no_check(_is_visited, x, y)) {
            set_no_check(_fade_in_map, x, y, (uint8_t)1);
        }
        set_no_check(_is_visited, x, y, true);
    }

    inline void unset_visited (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_visited, x, y, false);
    }

    inline void unset_visited_no_check (const int x, const int y)
    {
        set_no_check(_is_visited, x, y, false);
    }

    //
    // Used in lighting, so inlined
    //
    inline bool is_light_blocker (const point &p)
    {
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_light_blocker, p.x, p.y));
    }

    inline bool is_light_blocker_no_check (const point &p)
    {
        return (get_no_check(_is_light_blocker, p.x, p.y));
    }

    inline bool is_light_blocker (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_light_blocker, x, y));
    }

    inline bool is_light_blocker_no_check (const int x, const int y)
    {
        return (get_no_check(_is_light_blocker, x, y));
    }

    inline void set_is_light_blocker (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_light_blocker, x, y, true);
    }

    inline void set_is_light_blocker_no_check (const int x, const int y)
    {
        set_no_check(_is_light_blocker, x, y, true);
    }

    inline void unset_is_light_blocker (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_light_blocker, x, y, false);
    }

    inline void unset_is_light_blocker_no_check (const int x, const int y)
    {
        set_no_check(_is_light_blocker, x, y, false);
    }

    //
    // Used in lighting, so inlined
    //
    inline bool is_movement_blocking (const point &p)
    {
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_movement_blocking, p.x, p.y));
    }

    inline bool is_movement_blocking_no_check (const point &p)
    {
        return (get_no_check(_is_movement_blocking, p.x, p.y));
    }

    inline bool is_movement_blocking (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_movement_blocking, x, y));
    }

    inline bool is_movement_blocking_no_check (const int x, const int y)
    {
        return (get_no_check(_is_movement_blocking, x, y));
    }

    inline void set_is_movement_blocking (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_movement_blocking, x, y, true);
    }

    inline void set_is_movement_blocking_no_check (const int x, const int y)
    {
        set_no_check(_is_movement_blocking, x, y, true);
    }

    inline void unset_is_movement_blocking (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_movement_blocking, x, y, false);
    }

    inline void unset_is_movement_blocking_no_check (const int x, const int y)
    {
        set_no_check(_is_movement_blocking, x, y, false);
    }

    inline bool is_lit (const point &p)
    {
        if (unlikely(is_oob(p.x, p.y))) {
            return (false);
        }
        return (get(_is_lit, p.x, p.y));
    }

    inline bool is_lit_no_check (const point &p)
    {
        return (get_no_check(_is_lit, p.x, p.y));
    }

    inline bool is_lit (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return (false);
        }
        return (get(_is_lit, x, y));
    }

    inline bool is_lit_no_check (const int x, const int y)
    {
        return (get_no_check(_is_lit, x, y));
    }

    inline void set_is_lit (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_lit, x, y, true);
    }

    inline void set_is_lit_no_check (const int x, const int y)
    {
        set_no_check(_is_lit, x, y, true);
    }

    inline void unset_is_lit (const int x, const int y)
    {
        if (unlikely(is_oob(x, y))) {
            return;
        }
        set(_is_lit, x, y, false);
    }

    inline void unset_is_lit_no_check (const int x, const int y)
    {
        set_no_check(_is_lit, x, y, false);
    }

    void new_internal_particle(point start, point end, size sz, uint32_t dur, Tilep tile);
    void new_internal_particle(ThingId, point start, point end, size sz, uint32_t dur, Tilep tile);
    void new_external_particle(point start, point end, size sz, uint32_t dur, Tilep tile);
    void new_external_particle(ThingId, point start, point end, size sz, uint32_t dur, Tilep tile);
    void display_internal_particles(void);
    void display_external_particles(void);

    void game_mark_dungeon_tiles(Dungeonp d);
    void place_chasm(Dungeonp d, const std::string &what);
    void place_corridor(Dungeonp d, const std::string what, int depth);
    void place_deep_water(Dungeonp d, const std::string &what);
    void place_dirt(Dungeonp d);
    void place_floor_deco(Dungeonp d);
    void place_floor_under_objects(Dungeonp d, const std::string what, int depth);
    void place_floors(Dungeonp d, const std::string what, int depth, int variant, int block_width, int block_height, int tries);
    void place_lava(Dungeonp d, const std::string &what);
    void place_normal_placement_rules(Dungeonp d);
    void place_random_blood(Dungeonp d);
    void place_random_floor_deco(Dungeonp d);
    void place_remaining_floor(Dungeonp d, const std::string &what);
    void place_remaining_rocks(Dungeonp d, const std::string &what);
    void place_remaining_walls(Dungeonp d, const std::string &what);
    void place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries);
    void place_wall_deco(Dungeonp d);
    void place_walls(Dungeonp d, int variant, int block_width, int block_height, int tries);
    void place_water(Dungeonp d, const std::string &what);
    void lights_render(int minx, int miny, int maxx, int maxy, int fbo);
    Thingp actionbar_get(const uint32_t slot);
    Thingp actionbar_get(void);
    Thingp thing_find(const ThingId id);
    Thingp thing_new(const std::string& tp_name, Thingp owner);
    Thingp thing_new(const std::string& tp_name, const point at);
    Thingp thing_new(const std::string& tp_name, const fpoint at, const fpoint jitter = fpoint(0, 0));
    bool actionbar_select(const uint32_t slot);
    bool actionbar_describe(const uint32_t slot);
    void things_gc(void);
    void things_tick(void);

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
