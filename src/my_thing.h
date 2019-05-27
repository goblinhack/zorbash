/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_THING_H
#define _MY_THING_H

#include <unordered_map>
#include <memory>

typedef class Thing* Thingp;
typedef std::unordered_map< uint32_t, Thingp > Things;

#include "my_game.h"
#include "my_thing_template.h"
#include "my_tile_info.h"
#include "my_time.h"
#include "my_light.h"
#include "my_dmap.h"
#include "my_size.h"

enum {
    THING_DIR_NONE,
    THING_DIR_DOWN,
    THING_DIR_UP,
    THING_DIR_LEFT,
    THING_DIR_RIGHT,
    THING_DIR_TL,
    THING_DIR_BL,
    THING_DIR_TR,
    THING_DIR_BR,
};

class Goal
{
public:
    double score = {0};
    point  at;
    Thingp thing {};

    Goal () {}
    Goal (double score) : score(score) { }
    Goal (Thingp target) : thing(target) { }
    Goal (point target) : at(target) { }

    friend bool operator<(const class Goal & lhs, const class Goal & rhs) {
        return lhs.score < rhs.score;
    }
};

typedef struct AgeMap {
    int val[MAP_WIDTH][MAP_HEIGHT];
} AgeMap;

class Thing
{
private:

public:
    Thing (void)
    {
        newptr(this, "thing");
    }

    ~Thing (void)
    {
        // log("destroyed");
        destroy();
        oldptr(this);
    }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(cereal::make_nvp("id",               id));
        // etc todo and remember to repair Tp on loading
    }

    /*
     * Unique per thing.
     */
    uint32_t           id {};

    /*
     * Display order
     */
    uint8_t            depth;

    /*
     * Grid coordinates.
     */
    fpoint             mid_at;
    fpoint             ground_at;
    fpoint             interpolated_mid_at;

    /*
     * Previous hop where we were. We use this to interpolate the real
     * position when moving.
     */
    fpoint             last_mid_at;

    /*
     * On screen coordinates, taking account for size of the current frame.
     */
    fpoint             tl;
    fpoint             br;
    fpoint             old_br;
    fsize              sz;

    /*
     * GL co-orids
     */
    fpoint             last_blit_tl;
    fpoint             last_blit_br;


    /*
     * Physics
     */
    float              fall_speed {};
    float              jump_speed {};
    float              momentum {};
    float              rot {};
    fpoint normal_velocity {};
    fpoint tangent_velocity {};

    /*
     * Pointer to common settings for this thing.
     */
    Tpp                tp {nullptr};

    /*
     * Does this thing have a light source?
     */
    Lightp             light {nullptr};

    /*
     * Use to detect things hit by a light source
     */
    uint32_t           light_iterator {};

    /*
     * Used for animating the steps.
     */
    uint32_t           flip_start_ms {};
    uint32_t           begin_move_ms {};
    uint32_t           end_move_ms {};
    uint32_t           next_frame_ms {};
    uint32_t           next_ai_ms {};

    /*
     * Ticks every time the thing does something. Used from memory aging
     * to the hunger clock.
     */
    uint32_t           hunger_tick_last_ms {0};

    /*
     * Timestamps
     */
    uint32_t           timestamp_born {};
    uint32_t           timestamp_last_i_was_hit {};
    uint32_t           timestamp_last_attacked {};
    uint32_t           timestamp_move_start {};
    uint32_t           timestamp_move_end {};
    uint32_t           timestamp_collision {};

    /*
     * Bouncing
     */
    uint32_t           timestamp_bounce_begin {};
    uint32_t           timestamp_bounce_end {};
    double             bounce_height {}; // Percentage of tile height.
    double             bounce_fade {};   // 0.1; rapid decrease, 0.9 slow
    uint16_t           bounce_count {};

    /*
     * Tileinfo may be null if this thing does not need animation.
     * Ih such a case, current_tile will be set.
     */
    Tileinfop          current_tileinfo {};
    Tilep              current_tile {};

    /*
     * For thing decorations
     */
    Tilep              top_tile {};
    Tilep              bot_tile {};
    Tilep              left_tile {};
    Tilep              right_tile {};
    Tilep              tl_tile {};
    Tilep              tr_tile {};
    Tilep              bl_tile {};
    Tilep              br_tile {};

    /*
     * Only used for display purposes.
     */
    int                gold {0};
    int                health {0};
    int                max_health {0};

    uint32_t           weapon_carry_anim_thing_id {0};
    uint32_t           weapon_use_anim_thing_id {0};

    /*
     * Weapon thing template.
     */
    uint16_t           weapon_tp_id {0};

    /*
     * Who created this thing? e.g. who cast a spell?
     */
    uint32_t           owner_thing_id {0};

    /*
     * How many things this thing owns.
     */
    uint16_t           owned_count {0};

    unsigned int       dir:4;

    /*
     * AI
     */
    Dmap               *dmap_scent;
    Dmap               *dmap_goals;

    /*
     * This is an array of how old a cell is since we last visited it with
     * "memory" below.
     */
    AgeMap             *age_map;

    /*
     * Update thing_new when adding new bitfields.
     */
    unsigned int       is_hungry:1;          /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_starving:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_dead:1;            /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_bloodied:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_hidden:1;          /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_sleeping:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_moving:1;          /* until -std=c++2a remember to update thing.cpp */
    unsigned int       has_ever_moved:1;     /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_open:1;            /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_bouncing:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_attached:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_lit:1;             /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_waiting_for_ai:1;  /* until -std=c++2a remember to update thing.cpp */

    std::string to_string(void);
    uint8_t is_dir_bl(void);
    uint8_t is_dir_br(void);
    uint8_t is_dir_down(void);
    uint8_t is_dir_left(void);
    uint8_t is_dir_none(void);
    uint8_t is_dir_right(void);
    uint8_t is_dir_tl(void);
    uint8_t is_dir_tr(void);
    uint8_t is_dir_up(void);

    void destroy();
    void animate();
    void kill(void);
    void destroyed(void);
    void update_pos(fpoint);
    void move_delta(fpoint);
    void move_to(fpoint to);
    bool slide(void);
    void move_carried_items(void);
    void update_light(void);
    void set_dir_bl(void);
    void set_dir_br(void);
    void set_dir_down(void);
    void set_dir_left(void);
    void set_dir_none(void);
    void set_dir_right(void);
    void set_dir_tl(void);
    void set_dir_tr(void);
    void set_dir_up(void);
    void remove_hooks();
    Thingp get_owner();
    void set_owner(Thingp owner);
    uint8_t is_visible();
    void visible();
    void hide();

    /*
     * thing_tick.cpp
     */
    void tick();
    void do_collision_check();
    void achieve_goals_in_life();

    /*
     * thing_display.cpp
     */
    fpoint last_attached;
    void attach(void);
    void detach(void);
    void blit_wall_cladding(fpoint &tl, fpoint &br);
    void blit_rock_cladding(fpoint &tl, fpoint &br);
    void blit_shadow(const Tpp &tp, const Tilep &tile,
                     const fpoint &tl, const fpoint &br);
    void blit_shadow_section(const Tpp &tp, const Tilep &tile,
                             const fpoint &tile_tl, const fpoint &tile_br,
                             const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow(const Tpp &tp, const Tilep &tile,
                                  const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile,
                                          double x1, double y1,
                                          double x2, double y2,
                                          const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile,
                                          const fpoint &tile_tl, const fpoint &tile_br,
                                          const fpoint &tl, const fpoint &br);
    void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile,
                                      double x1, double y1,
                                      double x2, double y2,
                                      const fpoint &tl, const fpoint &br);
    void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile,
                                      const fpoint &tl, const fpoint &br);
    void blit_non_player_owned_shadow_section(const Tpp &tp, const Tilep &tile,
                                              const fpoint &tile_tl, const fpoint &tile_br,
                                              const fpoint &tl, const fpoint &br);
    void blit(double offset_x, double offset_y, int x, int y);
    void blit_upside_down(double offset_x, double offset_y, int x, int y);

    /*
     * thing_hit.cpp
     */
    int hit_actual(Thingp orig_hitter, Thingp real_hitter, Thingp hitter,
                   int damage);
    int hit_if_possible(Thingp hitter, int damage);
    int hit_if_possible(Thingp hitter);

    /*
     * thing_move.cpp
     */
    bool update_coordinates(void);
    bool move(fpoint future_pos);
    bool move(fpoint future_pos, const uint8_t up, const uint8_t down,
              const uint8_t left, const uint8_t right, const uint8_t fire);
    void bounce(double bounce_height, double bounce_fade, uint32_t ms,
                uint32_t bounce_count);
    double get_bounce(void);
    void to_coords(fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3);

    /*
     * thing_collision.cpp
     */
    bool handle_collisions(void);
    void possible_hits_find_best(void);
    bool possible_hit(Thingp it, int x, int y, int dx, int dy);

    /*
     * thing_health.cpp
     */
    void health_boost(int v);

    /*
     * thing_hunger.cpp
     */
    void hunger_clock();

    /*
     * thing_weapon.cpp
     */
    Tpp get_weapon();
    void wield_next_weapon();
    void unwield(const char *why);
    void sheath(void);
    void use(void);
    void wield(Tpp tp);
    void weapon_sheath(void);
    void get_weapon_use_offset(double *dx, double *dy);
    Thingp get_weapon_carry_anim(void);
    Thingp get_weapon_use_anim(void);
    void set_weapon_placement(void);
    void set_weapon_carry_anim_id(uint32_t weapon_carry_anim_id);
    void set_weapon_carry_anim(Thingp weapon_carry_anim);
    void set_weapon_use_anim_id(uint32_t weapon_use_anim_id);
    void set_weapon_use_anim(Thingp weapon_use_anim);

    void log_(const char *fmt, va_list args); // compile error without
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dead_(Thingp killer, const char *fmt, va_list args); // compile error without
    void dead(Thingp killer, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));
    void dead_(const char *fmt, va_list args); // compile error without
    void dead(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void die_(const char *fmt, va_list args); // compile error without
    void die(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));

    /*
     * thing_ai.cpp
     */
    bool will_attack(const Thingp it);
    bool will_avoid(const Thingp it);
    bool will_eat(const Thingp it);
    bool will_prefer(const Thingp it);
    bool is_obstacle_for_me(point p);
    bool is_goal_for_me(point p, int priority, double *score);
    fpoint get_next_hop(void);

    int nutrition (void) const
    {
        return (tp->nutrition());
    }

    int bite_damage (void) const
    {
        return (tp->bite_damage());
    }

    int is_floor (void)
    {
        return (tp_is_floor(tp));
    }

    int is_wall (void)
    {
        return (tp_is_wall(tp));
    }

    int is_door (void)
    {
        return (tp_is_door(tp));
    }

    int is_lava (void)
    {
        return (tp_is_lava(tp));
    }

    int is_water (void)
    {
        return (tp_is_water(tp));
    }

    int is_deep_water (void)
    {
        return (tp_is_deep_water(tp));
    }

    int is_monst (void)
    {
        return (tp_is_monst(tp));
    }

    int is_player (void)
    {
        return (tp_is_player(tp));
    }

    int gfx_is_an_animation_only (void)
    {
        return (tp_gfx_is_an_animation_only(tp));
    }

    int gfx_animated (void)
    {
        return (tp_gfx_animated(tp));
    }

    int gfx_animated_no_dir (void)
    {
        return (tp_gfx_animated_no_dir(tp));
    }

    int is_rrr1 (void)
    {
        return (tp_is_rrr1(tp));
    }

    int is_rrr2 (void)
    {
        return (tp_is_rrr2(tp));
    }

    int is_rrr3 (void)
    {
        return (tp_is_rrr3(tp));
    }

    int is_rrr4 (void)
    {
        return (tp_is_rrr4(tp));
    }

    int is_rrr5 (void)
    {
        return (tp_is_rrr5(tp));
    }

    int is_rrr6 (void)
    {
        return (tp_is_rrr6(tp));
    }

    int is_rrr7 (void)
    {
        return (tp_is_rrr7(tp));
    }

    int is_rrr8 (void)
    {
        return (tp_is_rrr8(tp));
    }

    int is_rrr9 (void)
    {
        return (tp_is_rrr9(tp));
    }

    int is_rrr10 (void)
    {
        return (tp_is_rrr10(tp));
    }

    int is_rrr11 (void)
    {
        return (tp_is_rrr11(tp));
    }

    int is_rrr12 (void)
    {
        return (tp_is_rrr12(tp));
    }

    int is_rrr13 (void)
    {
        return (tp_is_rrr13(tp));
    }

    int is_rrr14 (void)
    {
        return (tp_is_rrr14(tp));
    }

    int is_rrr15 (void)
    {
        return (tp_is_rrr15(tp));
    }

    int is_rock (void)
    {
        return (tp_is_rock(tp));
    }

    int is_wall_clinger (void)
    {
        return (tp_is_wall_clinger(tp));
    }

    std::string nutrition_hd (void)
    {
        return (tp_nutrition_hd(tp));
    }

    std::string bite_damage_hd (void)
    {
        return (tp_bite_damage_hd(tp));
    }

    int collision_check (void)
    {
        return (tp_collision_check(tp));
    }

    int attack_on_collision (void)
    {
        return (tp_attack_on_collision(tp));
    }

    int is_water_dweller (void)
    {
        return (tp_is_water_dweller(tp));
    }

    int collision_hit_priority (void)
    {
        return (tp_collision_hit_priority(tp));
    }

    double collision_radius (void)
    {
        return (tp_collision_radius(tp));
    }

    int ai_delay_after_moving_ms (void)
    {
        return (tp_ai_delay_after_moving_ms(tp));
    }

    int gfx_bounce_on_move (void)
    {
        return (tp_gfx_bounce_on_move(tp));
    }

    int is_corpse_on_death (void)
    {
        return (tp_is_corpse_on_death(tp));
    }

    int is_bleeder (void)
    {
        return (tp_is_bleeder(tp));
    }

    int is_meat_eater (void)
    {
        return (tp_is_meat_eater(tp));
    }

    int is_made_of_meat (void)
    {
        return (tp_is_made_of_meat(tp));
    }

    int is_active (void)
    {
        return (tp_is_active(tp));
    }

    int hunger_starving_at_health_pct (void)
    {
        return (tp_hunger_starving_at_health_pct(tp));
    }

    int hunger_initial_health_at (void)
    {
        return (tp_hunger_initial_health_at(tp));
    }

    int hunger_at_health_pct (void)
    {
        return (tp_hunger_at_health_pct(tp));
    }

    int hunger_clock_freq_ms (void)
    {
        return (tp_hunger_clock_freq_ms(tp));
    }

    int ai_scent_distance (void)
    {
        return (tp_ai_scent_distance(tp));
    }

    int is_ripple (void)
    {
        return (tp_is_ripple(tp));
    }

    int is_light_strength (void)
    {
        return (tp_is_light_strength(tp));
    }

    int is_dirt (void)
    {
        return (tp_is_dirt(tp));
    }

    int is_blood (void)
    {
        return (tp_is_blood(tp));
    }

    int gfx_animated_can_vflip (void)
    {
        return (tp_gfx_animated_can_vflip(tp));
    }

    int gfx_small_shadow_caster (void)
    {
        return (tp_gfx_small_shadow_caster(tp));
    }

    int is_corridor (void)
    {
        return (tp_is_corridor(tp));
    }

    int gfx_oversized_but_sitting_on_the_ground (void)
    {
        return (tp_gfx_oversized_but_sitting_on_the_ground(tp));
    }

    int is_boring (void)
    {
        return (tp_is_boring(tp));
    }

    int is_exit (void)
    {
        return (tp_is_exit(tp));
    }

    int is_entrance (void)
    {
        return (tp_is_entrance(tp));
    }

    int gfx_is_floor_deco (void)
    {
        return (tp_gfx_is_floor_deco(tp));
    }

    int gfx_is_wall_deco (void)
    {
        return (tp_gfx_is_wall_deco(tp));
    }

    int move_speed_ms (void)
    {
        return (tp_move_speed_ms(tp));
    }

    int weapon_use_delay_hundredths (void)
    {
        return (tp_weapon_use_delay_hundredths(tp));
    }

    int collision_box (void)
    {
        return (tp_collision_box(tp));
    }

    int collision_circle (void)
    {
        return (tp_collision_circle(tp));
    }

    int weapon_damage (void)
    {
        return (tp_weapon_damage(tp));
    }

    int is_projectile (void)
    {
        return (tp_is_projectile(tp));
    }

    int is_explosion (void)
    {
        return (tp_is_explosion(tp));
    }

    int is_combustable (void)
    {
        return (tp_is_combustable(tp));
    }

    int weapon_use_distance (void)
    {
        return (tp_weapon_use_distance(tp));
    }

    int gfx_is_weapon_carry_anim_only (void)
    {
        return (tp_gfx_is_weapon_carry_anim_only(tp));
    }

    int gfx_is_weapon_use_anim (void)
    {
        return (tp_gfx_is_weapon_use_anim(tp));
    }

    int is_weapon (void)
    {
        return (tp_is_weapon(tp));
    }

    int gfx_outlined (void)
    {
        return (tp_gfx_outlined(tp));
    }

    int gfx_large_shadow_caster (void)
    {
        return (tp_gfx_large_shadow_caster(tp));
    }

    int gfx_can_hflip (void)
    {
        return (tp_gfx_can_hflip(tp));
    }

    int z_depth (void)
    {
        return (tp_z_depth(tp));
    }

    int is_movable (void)
    {
        return (tp_is_movable(tp));
    }

    int is_movement_blocking (void)
    {
        return (tp_is_movement_blocking(tp));
    }

    int is_key (void)
    {
        return (tp_is_key(tp));
    }
};

class ThingDisplaySortKey {
public:
    ThingDisplaySortKey (void)
    {
    }

    ThingDisplaySortKey (uint8_t depth, double y, Thingp t) :
                        depth(depth), y(y), t(t)
    {
    }

    ~ThingDisplaySortKey (void)
    {
    }

    int depth {};
    double y {};
    Thingp t {};
};

struct thing_display_sort_cmp : public std::binary_function<class ThingDisplaySortKey, class ThingDisplaySortKey, bool>
{
    bool operator()(const ThingDisplaySortKey& lhs,
                    const ThingDisplaySortKey& rhs) const
    {
        if (lhs.y < rhs.y) {
            return (true);
        } else if (lhs.y > rhs.y) {
            return (false);
        }

        if (lhs.depth < rhs.depth) {
            return (true);
        } else if (lhs.depth > rhs.depth) {
            return (false);
        }

        if (lhs.t->id < rhs.t->id) {
            return (true);
        } else if (lhs.t->id > rhs.t->id) {
            return (false);
        }

        return (false);
    }
};

extern Thingp thing_new(std::string tp_name, fpoint at, fpoint jitter = fpoint(0, 0));
extern Thingp thing_find(uint32_t name);
extern void thing_gc(void);
extern void thing_render_all(void);
extern void thing_map_scroll_to_player(void);

/*
 * thing_display.cpp
 */
typedef std::map< ThingDisplaySortKey, Thingp, thing_display_sort_cmp > ThingDisplayOrder;
extern ThingDisplayOrder thing_display_order[MAP_WIDTH][MAP_HEIGHT][MAP_DEPTH];

/*
 * thing_move.cpp
 */

/*
 * thing_collision.cpp
 */
bool things_overlap(Thingp t, Thingp o);
bool things_overlap(Thingp t, fpoint t_at, Thingp o);

/*
 * thing_tick.cpp
 */
extern void things_tick(void);

extern const double wall_clinger_scale;

#endif /* THING_H */
