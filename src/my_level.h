//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_LEVEL_H_
#define _MY_LEVEL_H_

#include <map>
#include <deque>
#include <functional>

#include "my_time.h"
#include "my_thing_defs.h"
#include "my_particle.h"
#include "my_laser.h"
#include "my_projectile.h"
#include "my_dungeon.h"
#include "my_fwd.h"
#include "my_dmap.h"
#include "my_point3d.h"

class Level {
public:
    //
    // These are caches for fast lookup in display code
    //
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_light_blocker {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking_hard {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking_soft {};
    std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_lit_ever {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _fade_in_map {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _heatmap {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_acid {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_poison {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_chasm {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_bridge {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_shallow_water {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dry_grass {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_enchantstone {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_skillstone {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_foilage {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_spiderweb {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_sticky {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_door {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ascend_dungeon {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_descend_dungeon {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ascend_sewer {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_descend_sewer {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_fire {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_food {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_minion_generator {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_gold {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_extreme_hazard {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_a {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_b {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_c {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_key {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lit_currently {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_monst {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_potion {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wand {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ripple {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_smoke {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_brazier {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_barrel {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};
    std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _gfx_water {};

    //
    // When this Level was made. Used to restore timestamps relative to this.
    //
    timestamp_t                timestamp_dungeon_created {};
    timestamp_t                timestamp_dungeon_saved {};
    timestamp_t                timestamp_fade_out_begin {};
    timestamp_t                timestamp_fade_in_begin {};

    //
    // Where we are in the world
    //
    point3d                    world_at;

    //
    // Current on screen map limits in tile coords
    //
    int                        minx;
    int                        maxx;
    int                        miny;
    int                        maxy;
    //
    // All randomness jumps off of this as the root
    //
    bool                       cursor_found {};
    bool                       heatmap_valid {};
    bool                       is_starting {}; // Loading level
    bool                       map_changed {}; // Something moved on the map
    bool                       map_follow_player {};
    bool                       minimap_valid {};
    bool                       is_sewer_level {};
    bool                       is_dungeon_level {};
    fpoint                     cursor_at;
    fpoint                     cursor_at_old;
    fpoint                     map_at;        // map tile location
    fpoint                     map_wanted_at; // map scroll desired at
    float                      wobble = {};   // Fades when set
    int                        mouse {-1};    // ticks for every move
    int                        mouse_old {-1};
    int                        seed {};
    int                        monst_count {};
    point                      map_br;        // visible map br
    point                      map_tl;        // visible map tl
    point                      pixel_map_at;  // map pixel location

    //
    // Everything thing on the level. Not all in the game, just this level.
    //
    std::map<ThingId, Thingp> all_things {};

    //
    // For all things that move, like monsters, or those that do not, like
    // wands, and even those that do not move but can be destroyed, like
    // walls. Omits things like floors, corridors, the grid; those that
    // generally do nothing or are hidden.
    //
    std::map<ThingId, Thingp> all_interesting_things {};
    //
    // These are used to add/remove to all_interesting_things when walking
    // is done; aboids the map becoming invalidated due to changes.
    //
    bool all_interesting_things_walk_in_progress {};
    std::map<ThingId, Thingp> pending_add_all_interesting_things {};
    std::map<ThingId, Thingp> pending_remove_all_interesting_things {};

    //
    // All things that are to be destroyed
    //
    std::map<ThingId, Thingp> all_gc_things {};

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

    //
    // This is what we've lit on this level, so we can restore it
    // when we return
    //
    std::vector<uint8_t> fbo_light;

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////

    //
    // Update thing_fini.cpp when adding more references to Thingp
    //
    Thingp                     player = {};
    Thingp                     cursor = {};
    Thingp                     highlight = {};
    Thingp                     hover_over = {};

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

    bool                       is_being_destroyed {};
    bool                       cursor_update_needed {};

    //
    // Animation loop counters for surface effects
    //
    int                        water_step1 {};
    float                      water_step2 {};
    int                        deep_water_step1 {};
    float                      deep_water_step2 {};
    int                        lava_step1 {};
    float                      lava_step2 {};

    //
    // If set, redraw the background; allows for dampening
    //
    timestamp_t                timestamp_redraw_bg {};

    //
    // For thing effects, like jumping
    //
    std::vector<Particle>      all_internal_particles;
    std::vector<Particle>      new_internal_particles;

    //
    // For things like move of items into inventory
    //
    std::vector<Particle>      all_external_particles;
    std::vector<Particle>      new_external_particles;

    std::vector<Projectile>    all_projectiles;
    std::vector<Projectile>    new_projectiles;

    std::vector<Laser>         all_lasers;
    std::vector<Laser>         new_lasers;

    //
    // Where the minimap widget ois
    //
    point                      minimap_tl;
    point                      minimap_br;

    //
    // We regenerate this map every player move, and indicates the shortest
    // path to the player. Used for sound effects and lighting checks.
    //
    Dmap                       dmap_to_player;

    /////////////////////////////////////////////////////////////////////////
    // not worth saving
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    /////////////////////////////////////////////////////////////////////////

    Level(void);
    ~Level(void);

    void remove_thing(int x, int y, ThingId id);
    void remove_thing(point p, ThingId id);

    void put_thing(int x, int y, ThingId id);
    void put_thing(point p, ThingId id);

    #define JOIN1(X,Y) X##Y
    #define JOIN(X,Y) JOIN1(X,Y)

    #define FOR_ALL_THINGS_WALKER(level, t, x, y)                   \
        if (!(level)->is_oob(x, y)) {                               \
            static Thingp things_to_walk[MAP_SLOTS];                \
            auto _vec_ = getptr(level->all_thing_ptrs_at, x, y);    \
            auto things_to_walk_size = _vec_->size();               \
            for(size_t idx = 0; idx < things_to_walk_size; idx++)   \
                things_to_walk[idx] = (*_vec_)[idx];                \
            for(size_t idx = 0; idx < things_to_walk_size; idx++) { \
                Thingp t;                                           \
                t = things_to_walk[idx];                            \
                verify(t);                                          \

    #define FOR_ALL_THINGS(level, t, x, y)                          \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \

    #define FOR_ALL_THINGS_END() } }

    #define FOR_ALL_INTERESTING_THINGS_ON_LEVEL(level, t) {         \
        level->all_interesting_things_walk_in_progress = true;      \
        auto c = level->all_interesting_things;                     \
        auto i = level->all_interesting_things.begin();             \
        while (i != level->all_interesting_things.end()) {          \
            auto t = i->second;                                     \
            i++;                                                    \
            if (t->is_hidden) { continue; }                         \
                                                                    \
            verify(t);                                              \

    #define FOR_ALL_INTERESTING_THINGS_ON_LEVEL_END(level)          \
            if (i == level->all_interesting_things.end()) {         \
                break;                                              \
            }                                                       \
        }                                                           \
        level->all_interesting_things_walk_in_progress = false;     \
    }

#if 0
            {                                                       \
                bool got = false;                                   \
                for (auto p : level->all_interesting_things) {      \
                    if (p.second == t) {                            \
                        got = true;                                 \
                        break;                                      \
                    }                                               \
                }                                                   \
                if (!got) {                                         \
                    t->die("Found thing not on list");              \
                }                                                   \
            }                                                       \

#endif

    #define FOR_ALL_TICKABLE_THINGS_ON_LEVEL(level, t) {            \
        level->all_interesting_things_walk_in_progress = true;      \
        auto c = level->all_interesting_things;                     \
        auto i = level->all_interesting_things.begin();             \
        while (i != level->all_interesting_things.end()) {          \
            auto t = i->second;                                     \
            i++;                                                    \
            if (t->is_hidden) {                                     \
                if (!t->is_active()) { /* e.g. carried wand */      \
                    continue;                                       \
                }                                                   \
            }                                                       \
                                                                    \
            verify(t);                                              \

    #define FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(level)             \
            if (i == level->all_interesting_things.end()) {         \
                break;                                              \
            }                                                       \
        }                                                           \
        level->all_interesting_things_walk_in_progress = false;     \
    }

    //
    // NOTE: get is a lot safer than getptr, if the vector gets resized somehow
    // during walks
    //
    #define FOR_ALL_GRID_THINGS(level, t, x, y)              	    \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
                if (!t->is_the_grid) { continue; }                  \

    #define FOR_ALL_THINGS_AT_DEPTH(level, t, x, y, z)              \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
                if (t->z_depth != z) {                              \
                    continue;                                       \
                }                                                   \
                if (t->is_hidden) { continue; }                     \

    #define FOR_ALL_LIGHTS_AT_DEPTH(level, t, x, y)                 \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
            if (likely(!t->has_light)) { continue; }                \
            if (t->is_hidden) { continue; }                         \

    //
    // Things that move around
    //
    #define FOR_ALL_ACTIVE_THINGS(level, t, x, y)                   \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
                if (t->is_the_grid) { continue; }                   \
                if (t->is_hidden) { continue; }                     \
                if (!t->is_active()) {                              \
                    continue;                                       \
                }                                                   \

    //
    // Things that move around and things that do not, but are interesting
    // like food or walls that can be destroyed
    //
    #define FOR_ALL_INTERESTING_THINGS(level, t, x, y)              \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
                if (t->is_the_grid) { continue; }                   \
                if (t->is_hidden) { continue; }                     \
                if (!t->is_interesting()) {                         \
                    continue;                                       \
                }                                                   \

    //
    // Things you can bump into
    //
    #define FOR_ALL_COLLISION_THINGS(level, t, x, y)                \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
                if (t->is_the_grid) { continue; }                   \
                if (t->is_hidden) { continue; }                     \
                if (t->is_interesting() ||                          \
                    t->is_attackable_by_monst() ||                  \
                    t->is_attackable_by_player() ||                 \
                    t->ai_obstacle()) {                             \
                } else {                                            \
                    continue;                                       \
                }

    //
    // Cursor path is the highlighted path the player follows.
    //
    #define FOR_ALL_CURSOR_PATH_THINGS(level, t, x, y)              \
        FOR_ALL_THINGS_WALKER(level, t, x, y)                       \
                if (!t->is_cursor_path()) {                         \
                    continue;                                       \
                }                                                   \

    Thingp inventory_get(const uint32_t slot);
    Thingp inventory_get(void);
    Thingp skillbox_get(const uint32_t slot);
    Thingp skillbox_get(void);
    Thingp thing_find(const ThingId id);
    Thingp thing_new(Tpp, const point at);
    Thingp thing_new(Tpp, const fpoint at);
    Thingp thing_new(Tpp, const fpoint at, const fpoint jitter);
    Thingp thing_new(const std::string& tp_name, Thingp owner);
    Thingp thing_new(const std::string& tp_name, const fpoint at, const fpoint jitter);
    Thingp thing_new(const std::string& tp_name, const fpoint at);
    Thingp thing_new(const std::string& tp_name, const point at);
    bool create_dungeon(point3d at, int seed);
    bool create_sewer(point3d at, int seed);
    bool create_sewer_pipes(point3d at);
    bool create_sewer_pools(void);
    bool inventory_chosen(const uint32_t slot);
    bool inventory_assign(const uint32_t slot, Thingp);
    int inventory_get_slot(Thingp item);
    bool inventory_over(const uint32_t slot);
    bool skillbox_chosen(const uint32_t slot);
    bool skillbox_over(const uint32_t slot);
    bool is_light_blocker(const int x, const int y) const;
    bool is_light_blocker(const point &p) const;
    bool is_light_blocker_no_check(const int x, const int y) const;
    bool is_light_blocker_no_check(const point &p) const;
    bool is_movement_blocking_hard(const int x, const int y) const;
    bool is_movement_blocking_hard(const point &p) const;
    bool is_movement_blocking_hard_no_check(const int x, const int y) const;
    bool is_movement_blocking_hard_no_check(const point &p) const;
    bool is_movement_blocking_soft(const int x, const int y) const;
    bool is_movement_blocking_soft(const point &p) const;
    bool is_movement_blocking_soft_no_check(const int x, const int y) const;
    bool is_movement_blocking_soft_no_check(const point &p) const;
    bool is_oob(const fpoint p) const;
    bool is_oob(const int x, const int y) const;
    bool is_oob(const int x, const int y, const int z) const;
    bool is_oob(const point p) const;
    bool screen_shake_begin(void);
    float get_wobble(void) const;
    float update_wobble(void);
    std::string to_string(void);
    uint8_t fade_in_map(const int x, const int y);
    uint8_t fade_in_map(const point &p);
    uint8_t fade_in_map_no_check(const int x, const int y);
    uint8_t fade_in_map_no_check(const point &p);
    uint8_t heatmap(const int x, const int y);
    uint8_t heatmap(const point &p);
    uint8_t heatmap_no_check(const int x, const int y);
    uint8_t heatmap_no_check(const point &p);
    uint8_t is_acid(const int x, const int y);
    uint8_t is_acid(const point &p);
    uint8_t is_ascend_dungeon(const int x, const int y);
    uint8_t is_ascend_dungeon(const point &p);
    uint8_t is_ascend_sewer(const int x, const int y);
    uint8_t is_ascend_sewer(const point &p);
    uint8_t is_blood(const int x, const int y);
    uint8_t is_blood(const point &p);
    uint8_t is_chasm(const int x, const int y);
    uint8_t is_chasm(const point &p);
    uint8_t is_corpse(const int x, const int y);
    uint8_t is_corpse(const point &p);
    uint8_t is_corridor(const int x, const int y);
    uint8_t is_corridor(const point &p);
    uint8_t is_bridge(const int x, const int y);
    uint8_t is_bridge(const point &p);
    uint8_t is_deep_water(const int x, const int y);
    uint8_t is_deep_water(const point &p);
    uint8_t is_descend_dungeon(const int x, const int y);
    uint8_t is_descend_dungeon(const point &p);
    uint8_t is_descend_sewer(const int x, const int y);
    uint8_t is_descend_sewer(const point &p);
    uint8_t is_dirt(const int x, const int y);
    uint8_t is_dirt(const point &p);
    uint8_t is_dry_grass(const int x, const int y);
    uint8_t is_dry_grass(const point &p);
    uint8_t is_enchantstone(const int x, const int y);
    uint8_t is_enchantstone(const point &p);
    uint8_t is_skillstone(const int x, const int y);
    uint8_t is_skillstone(const point &p);
    uint8_t is_foilage(const int x, const int y);
    uint8_t is_foilage(const point &p);
    uint8_t is_spiderweb(const int x, const int y);
    uint8_t is_spiderweb(const point &p);
    uint8_t is_sticky(const int x, const int y);
    uint8_t is_sticky(const point &p);
    uint8_t is_door(const int x, const int y);
    uint8_t is_door(const point &p);
    uint8_t is_dungeon(const int x, const int y);
    uint8_t is_dungeon(const point &p);
    uint8_t is_extreme_hazard(const int x, const int y);
    uint8_t is_extreme_hazard(const point &p);
    uint8_t is_fire(const int x, const int y);
    uint8_t is_fire(const point &p);
    uint8_t is_floor(const point &p);
    uint8_t is_floor(const int x, const int y);
    uint8_t is_food(const int x, const int y);
    uint8_t is_food(const point &p);
    uint8_t gfx_water(const int x, const int y);
    uint8_t gfx_water(const point &p);
    uint8_t is_gold(const int x, const int y);
    uint8_t is_gold(const point &p);
    uint8_t is_hazard(const int x, const int y);
    uint8_t is_hazard(const point &p);
    uint8_t is_key(const int x, const int y);
    uint8_t is_key(const point &p);
    uint8_t is_lava(const int x, const int y);
    uint8_t is_lava(const point &p);
    uint8_t is_lit_currently(const int x, const int y);
    uint8_t is_lit_currently(const point &p);
    uint8_t is_lit_currently_no_check(const int x, const int y);
    uint8_t is_lit_currently_no_check(const point &p);
    uint8_t is_minion_generator(const int x, const int y);
    uint8_t is_minion_generator(const point &p);
    uint8_t is_monst(const int x, const int y);
    uint8_t is_monst(const point &p);
    uint8_t is_poison(const int x, const int y);
    uint8_t is_poison(const point &p);
    uint8_t is_potion(const int x, const int y);
    uint8_t is_potion(const point &p);
    uint8_t is_wand(const int x, const int y);
    uint8_t is_wand(const point &p);
    uint8_t is_ripple(const int x, const int y);
    uint8_t is_ripple(const point &p);
    uint8_t is_rock(const int x, const int y);
    uint8_t is_rock(const point &p);
    uint8_t is_secret_door(const int x, const int y);
    uint8_t is_secret_door(const point &p);
    uint8_t is_shallow_water(const int x, const int y);
    uint8_t is_shallow_water(const point &p);
    uint8_t is_water(const int x, const int y);
    uint8_t is_water(const point &p);
    uint8_t is_smoke(const int x, const int y);
    uint8_t is_smoke(const point &p);
    uint8_t is_brazier(const int x, const int y);
    uint8_t is_brazier(const point &p);
    uint8_t is_barrel(const int x, const int y);
    uint8_t is_barrel(const point &p);
    uint8_t is_treasure(const int x, const int y);
    Thingp inventory_describe(const uint32_t slot);
    Thingp skillbox_describe(const uint32_t slot);
    Tpp tp_random_minion_generator(const point &p);
    Tpp tp_random_minion_generator_easy(const point &p);
    Tpp tp_random_minion_generator_hard(const point &p);
    Tpp tp_random_monst(const point &p);
    Tpp tp_random_monst_easy(const point &p);
    Tpp tp_random_monst_hard(const point &p);
    friend std::istream& operator>>(std::istream &in, Bits<Levelp &> my);
    friend std::ostream& operator<<(std::ostream &out, Bits<Levelp & > const my);
    uint8_t is_treasure(const point &p);
    uint8_t is_treasure_class_a(const int x, const int y);
    uint8_t is_treasure_class_a(const point &p);
    uint8_t is_treasure_class_b(const int x, const int y);
    uint8_t is_treasure_class_b(const point &p);
    uint8_t is_treasure_class_c(const int x, const int y);
    uint8_t is_treasure_class_c(const point &p);
    uint8_t is_lit_ever(const int x, const int y);
    uint8_t is_lit_ever(const point &p);
    uint8_t is_lit_ever_no_check(const int x, const int y);
    uint8_t is_lit_ever_no_check(const point &p);
    uint8_t is_wall(const int x, const int y);
    uint8_t is_wall(const point &p);
    void clear(void);
    void con(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void create(point3d at, int seed);
    void create_dungeon_game_mark_dungeon_tiles(Dungeonp d);
    void create_dungeon_place_chasm(Dungeonp d, const std::string &what);
    void create_dungeon_place_corridor(Dungeonp d, const std::string what, int depth);
    void create_dungeon_place_bridge(Dungeonp d);
    void create_dungeon_place_deep_water(Dungeonp d, const std::string &what);
    void create_dungeon_place_floors(Dungeonp d, const std::string what, int depth, int variant, int block_width, int block_height, int tries);
    void create_dungeon_place_lava(Dungeonp d, const std::string &what);
    void create_dungeon_place_braziers(Dungeonp d, const std::string &what);
    void create_dungeon_place_lava_smoke(Dungeonp d);
    void create_dungeon_place_objects_with_normal_placement_rules(Dungeonp d);
    void create_dungeon_place_place_shallow_water(Dungeonp d, const std::string &what);
    void create_dungeon_place_random_blood(Dungeonp d);
    void create_dungeon_place_random_floor_deco(Dungeonp d);
    void create_dungeon_place_remaining_floor(Dungeonp d, const std::string &what);
    void create_dungeon_place_remaining_rocks(Dungeonp d, const std::string &what);
    void create_dungeon_place_remaining_walls(Dungeonp d, const std::string &what);
    void create_dungeon_place_rocks(Dungeonp d, int variant, int block_width, int block_height, int tries);
    void create_dungeon_place_sewer_pipes(Dungeonp d);
    void create_dungeon_place_walls(Dungeonp d, Tpp tp, int variant, int block_width, int block_height, int tries);
    void create_sewer_place_remaining_walls(const std::string &what);
    void create_sewer_place_walls(int variant, int block_width, int block_height, int tries);
    void cursor_check_if_scroll_needed(void);
    void cursor_describe(void);
    void cursor_find_on_visible_things(const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void cursor_move(void);
    void cursor_path_clear(void);
    void cursor_path_create(const std::vector<point> &move_path);
    void cursor_path_create(void);
    void cursor_path_draw(point start, point end);
    void cursor_path_draw(const std::vector<point> &move_path);
    void cursor_path_draw(void);
    void cursor_path_draw_circle(void);
    void cursor_path_draw_line(point start, point end);
    void cursor_path_draw_line(const std::vector<point> &move_path);
    void cursor_recreate(void);
    void describe(Thingp);
    void describe(fpoint at);
    void display(void);
    void display_anim(void);
    void display_blood(void);
    void display_deep_water(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void display_external_particles(void);
    void display_fade_in(void);
    void display_fade_out(void);
    void display_internal_particles(void);
    void display_lasers(void);
    void display_projectiles(void);
    void display_lava(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void display_map(void);
    void display_map_bg_things(void);
    void display_map_fg2_things(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void display_map_fg_things(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void display_map_things(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void display_minimap(void);
    void display_target(void);
    void display_water(const int fbo, const int16_t minx, const int16_t miny, const int16_t maxx, const int16_t maxy);
    void dump(std::string prefix);
    void dump(std::string prefix, std::ostream &out);
    void err(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void fini(void);
    void get_tiles(void);
    void incr_fade_in(const int x, const int y);
    void incr_fade_in_no_check(const int x, const int y);
    void incr_heatmap(const int x, const int y);
    void incr_heatmap_no_check(const int x, const int y);
    void lights_fade(void);
    void lights_render(int minx, int miny, int maxx, int maxy, int fbo);
    void lights_render_small_lights(int minx, int miny, int maxx, int maxy, int fbo, bool include_player_lights);
    void lights_update_new_level(void);
    void lights_update_same_level(void);
    void log(const char *fmt, ...) __attribute__((format(printf, 2, 3)));
    void log_(const char *fmt, va_list args); // compile error without
    void new_external_particle(ThingId, point start, point end, isize sz, uint32_t dur, Tilep tile, bool hflip, bool make_visible_at_end);
    void new_external_particle(point start, point end, isize sz, uint32_t dur, Tilep tile, bool hflip, bool make_visible_at_end);
    void new_internal_particle(ThingId, point start, point end, isize sz, uint32_t dur, Tilep tile, bool hflip, bool make_visible_at_end);
    void new_internal_particle(point start, point end, isize sz, uint32_t dur, Tilep tile, bool hflip, bool make_visible_at_end);
    void new_laser(ThingId id, point start, point stop, uint32_t dur);
    void new_projectile(ThingId id, point start, point stop, uint32_t dur);
    void place_dirt(Dungeonp d);
    void place_random_treasure(Dungeonp d);
    void place_dry_grass(Dungeonp d);
    void place_foilage(Dungeonp d);
    void place_spiderweb(Dungeonp d);
    void place_floor_deco(Dungeonp d);
    void place_the_grid(void);
    void dmap_to_player_update(void);
    void sanity_check(void);
    void screen_shake_end(void);
    void scroll_map(void);
    void scroll_map_do(bool fast);
    void scroll_map_set_target(void);
    void scroll_map_to_player(void);
    void scroll_map_to_player_immediately(void);
    void set_is_dungeon(const int x, const int y);
    void set_is_acid(const int x, const int y);
    void set_is_ascend_dungeon(const int x, const int y);
    void set_is_ascend_sewer(const int x, const int y);
    void set_is_blood(const int x, const int y);
    void set_is_brazier(const int x, const int y);
    void set_is_chasm(const int x, const int y);
    void set_is_corpse(const int x, const int y);
    void set_is_corridor(const int x, const int y);
    void set_is_bridge(const int x, const int y);
    void set_is_deep_water(const int x, const int y);
    void set_is_descend_dungeon(const int x, const int y);
    void set_is_descend_sewer(const int x, const int y);
    void set_is_dirt(const int x, const int y);
    void set_is_dry_grass(const int x, const int y);
    void set_is_enchantstone(const int x, const int y);
    void set_is_skillstone(const int x, const int y);
    void set_is_foilage(const int x, const int y);
    void set_is_spiderweb(const int x, const int y);
    void set_is_sticky(const int x, const int y);
    void set_is_door(const int x, const int y);
    void set_is_extreme_hazard(const int x, const int y);
    void set_is_fire(const int x, const int y);
    void set_is_floor(const int x, const int y);
    void set_is_food(const int x, const int y);
    void set_gfx_water(const int x, const int y);
    void set_is_gold(const int x, const int y);
    void set_is_hazard(const int x, const int y);
    void set_is_key(const int x, const int y);
    void set_is_lava(const int x, const int y);
    void set_is_light_blocker(const int x, const int y);
    void set_is_light_blocker_no_check(const int x, const int y);
    void set_is_lit_currently(const int x, const int y);
    void set_is_lit_currently_no_check(const int x, const int y);
    void set_is_lit_currently_no_check(const int x, const int y, uint8_t v);
    void set_is_minion_generator(const int x, const int y);
    void set_is_monst(const int x, const int y);
    void set_is_movement_blocking_hard(const int x, const int y);
    void set_is_movement_blocking_hard_no_check(const int x, const int y);
    void set_is_movement_blocking_soft(const int x, const int y);
    void set_is_movement_blocking_soft_no_check(const int x, const int y);
    void set_is_poison(const int x, const int y);
    void set_is_potion(const int x, const int y);
    void set_is_wand(const int x, const int y);
    void set_is_ripple(const int x, const int y);
    void set_is_rock(const int x, const int y);
    void set_is_secret_door(const int x, const int y);
    void set_is_shallow_water(const int x, const int y);
    void set_is_smoke(const int x, const int y);
    void set_is_treasure(const int x, const int y);
    void set_is_treasure_class_a(const int x, const int y);
    void set_is_treasure_class_b(const int x, const int y);
    void set_is_treasure_class_c(const int x, const int y);
    void set_is_wall(const int x, const int y);
    void set_visited(const int x, const int y);
    void set_visited_no_check(const int x, const int y);
    void set_wobble(float);
    void things_gc(bool force);
    void things_gc_force(void);
    void things_gc_if_possible(void);
    void things_tick(void);
    void tick(void);
    void unset_is_dungeon(const int x, const int y);
    void unset_fade_in(const int x, const int y);
    void unset_fade_in_no_check(const int x, const int y);
    void unset_heatmap(const int x, const int y);
    void unset_heatmap_no_check(const int x, const int y);
    void unset_is_acid(const int x, const int y);
    void unset_is_ascend_dungeon(const int x, const int y);
    void unset_is_ascend_sewer(const int x, const int y);
    void unset_is_blood(const int x, const int y);
    void unset_is_brazier(const int x, const int y);
    void unset_is_barrel(const int x, const int y);
    void set_is_barrel(const int x, const int y);
    void unset_is_chasm(const int x, const int y);
    void unset_is_corpse(const int x, const int y);
    void unset_is_corridor(const int x, const int y);
    void unset_is_bridge(const int x, const int y);
    void unset_is_deep_water(const int x, const int y);
    void unset_is_descend_dungeon(const int x, const int y);
    void unset_is_descend_sewer(const int x, const int y);
    void unset_is_dirt(const int x, const int y);
    void unset_is_dry_grass(const int x, const int y);
    void unset_is_enchantstone(const int x, const int y);
    void unset_is_skillstone(const int x, const int y);
    void unset_is_foilage(const int x, const int y);
    void unset_is_spiderweb(const int x, const int y);
    void unset_is_sticky(const int x, const int y);
    void unset_is_door(const int x, const int y);
    void unset_is_extreme_hazard(const int x, const int y);
    void unset_is_fire(const int x, const int y);
    void unset_is_floor(const int x, const int y);
    void unset_is_food(const int x, const int y);
    void unset_gfx_water(const int x, const int y);
    void unset_is_gold(const int x, const int y);
    void unset_is_hazard(const int x, const int y);
    void unset_is_key(const int x, const int y);
    void unset_is_lava(const int x, const int y);
    void unset_is_light_blocker(const int x, const int y);
    void unset_is_light_blocker_no_check(const int x, const int y);
    void unset_is_lit_currently(const int x, const int y);
    void unset_is_lit_currently_no_check(const int x, const int y);
    void unset_is_minion_generator(const int x, const int y);
    void unset_is_monst(const int x, const int y);
    void unset_is_movement_blocking_hard(const int x, const int y);
    void unset_is_movement_blocking_hard_no_check(const int x, const int y);
    void unset_is_movement_blocking_soft(const int x, const int y);
    void unset_is_movement_blocking_soft_no_check(const int x, const int y);
    void unset_is_poison(const int x, const int y);
    void unset_is_potion(const int x, const int y);
    void unset_is_wand(const int x, const int y);
    void unset_is_ripple(const int x, const int y);
    void unset_is_rock(const int x, const int y);
    void unset_is_secret_door(const int x, const int y);
    void unset_is_shallow_water(const int x, const int y);
    void unset_is_smoke(const int x, const int y);
    void unset_is_treasure(const int x, const int y);
    void unset_is_treasure_class_a(const int x, const int y);
    void unset_is_treasure_class_b(const int x, const int y);
    void unset_is_treasure_class_c(const int x, const int y);
    void unset_is_wall(const int x, const int y);
    void unset_visited(const int x, const int y);
    void unset_visited_no_check(const int x, const int y);
    void update_all_ticks(void);
    void update_deep_water(void);
    void update_hazard_tile_map(void);
    void update_heatmap(void);
    void update_map(void);
    void update_minimap(bool showing_two_levels, bool show_faded);
    void update_new_level(void);
    void update_same_level(void);
    void update_same_level_immediately(void);
    void update_things_next_to_a_chasm(void);
    void update_water_next_to_lava(void);
    bool can_see_obstacle(int x, int y);
    bool can_see_(int x0_in, int y0_in, int x1_in, int y1_in, int flag);
    bool can_see(int x0, int y0, int x1, int y1);
    std::deque<point> flood_fill(point) const;
    std::deque<point> flood_fill_points(point, std::function<int(Thingp)> filter);
    std::deque<Thingp> flood_fill_things(point, std::function<int(Thingp)> filter);
};

#endif
