
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#ifndef _MY_THING_H
#define _MY_THING_H

#include <unordered_map>
#include <memory>
#include <set>

typedef struct Thing_* Thingp;
typedef std::unordered_map< uint32_t, Thingp > Things;

#include "my_thing_template.h"
#include "my_time.h"
#include "my_light.h"
#include "my_dmap.h"

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

class Path {
public:
    Path () {}
    Path (std::vector<point> &p, int c) : path(p), cost(c) { }

    std::vector<point> path;
    int                cost {};
};

extern Path astar_solve(point start, std::multiset<Goal> &goals, Dmap *dmap);

typedef struct {
    std::array<std::array<uint32_t, CHUNK_HEIGHT>, CHUNK_WIDTH> val;
} AgeMap;
std::ostream& operator<<(std::ostream &out, Bits<const AgeMap & > const my);
std::istream& operator>>(std::istream &in, Bits<AgeMap &> my);

typedef struct {
    uint16_t tile_bl;
    uint16_t tile_bot;
    uint16_t tile_br;
    uint16_t tile_left;
    uint16_t tile_right;
    uint16_t tile_tl;
    uint16_t tile_top;
    uint16_t tile_tr;
} ThingTiles;

typedef struct Monst_ {
    AgeMap       *age_map = {};              // How old a cell is
    Dmap         *dmap_goals = {};
    Dmap         *dmap_scent = {};
    Lightp       light = {};                 // Have a light source?
    int          light_strength {};
    int          light_quality {};
    color        light_col {};
    fpoint       interpolated_mid_at;
    float        bounce_height = {};         // Percentage of tile height.
    float        bounce_fade = {};           // 0.1; rapid, 0.9 slow
    float        rot = {};                   // GL co-orids
    float        submerged_offset = {};      // GL co-orids
    int          bounce_count = {};
    int          gold = {}; 
    int          health = {}; 
    int          health_max = {}; 
    int          owned_count = {};           // How many things this thing owns.
    uint32_t     timestamp_bounce_begin {};
    uint32_t     timestamp_bounce_end {};
    uint32_t     timestamp_last_i_was_hit {};
    uint32_t     timestamp_flip_start {};    // Used for animating the steps.
    uint32_t     timestamp_move_begin {};
    uint32_t     timestamp_move_end {};
    uint32_t     timestamp_born {};
    uint32_t     timestamp_hunger_tick {};   // Ticks every time does something. Used from memory aging
    uint32_t     timestamp_ai_next {};
    uint32_t     timestamp_collision {};
    uint32_t     owner_id {};                // Who created this thing?
    uint32_t     weapon_id_carry_anim {};
    uint32_t     weapon_id_use_anim {};
    uint16_t     weapon_tp_id {};            // Weapon thing template.
    void dump(std::string prefix, std::ostream &out);
} Monst;
std::ostream& operator<<(std::ostream &out, Bits<const Monst & > const my);
std::istream& operator>>(std::istream &in, Bits<Monst &> my);

typedef struct Thing_ {
    Thing_ (void);
    ~Thing_ (void);
    Monst    *monst               {};
    spoint   last_attached;
    fpoint   br;                         // On screen coordinates
    fpoint   last_blit_br;               // GL co-orids
    fpoint   last_blit_tl;               // GL co-orids
    fpoint   last_mid_at;                // Previous hop where we were.
    fpoint   mid_at;                     // Grid coordinates.
    fpoint   tl;                         // On screen coordinates
    uint32_t id;                         // Unique per thing.
    uint16_t tp_id;                      // Common settings
    uint16_t tile_curr;
    uint32_t timestamp_next_frame {};
    uint32_t dir:4                {}; // Direction
    uint32_t has_ever_moved:1     {};
    uint32_t has_light:1          {};
    uint32_t is_attached:1        {};
    uint32_t is_being_destroyed:1 {};
    uint32_t is_bloodied:1        {};
    uint32_t is_bouncing:1        {};
    uint32_t is_dead:1            {};
    uint32_t is_facing_left:1     {};
    uint32_t is_hidden:1          {};
    uint32_t is_hungry:1          {};
    uint32_t is_moving:1          {};
    uint32_t is_open:1            {};
    uint32_t is_sleeping:1        {};
    uint32_t is_starving:1        {};
    uint32_t is_submerged:1       {};
    uint32_t is_waiting_for_ai:1  {};

    Tpp tp(void)
    {
        return (tp_id_map[tp_id - 1]);
    }

    void new_monst(void);
    void get_tiles(ThingTiles *tiles);

    AgeMap *get_age_map(void);
    void new_age_map(void);
    void delete_age_map(void);

    Dmap *get_dmap_goals(void);
    void new_dmap_goals(void);
    void delete_dmap_goals(void);

    Dmap *get_dmap_scent(void);
    void new_dmap_scent(void);
    void delete_dmap_scent(void);

    Lightp get_light(void);
    void new_light(fpoint at, 
                   double strength,
                   LightQuality quality = LIGHT_QUALITY_POINT, 
                   color col = WHITE);
    void delete_light(void);

    void set_bounce_height(float);
    float get_bounce_height(void);

    void set_bounce_fade(float);
    float get_bounce_fade(void);

    void set_bounce_count(int);
    int get_bounce_count(void);

    void set_rot(float);
    float get_rot(void);

    void set_submerged_offset(float);
    float get_submerged_offset(void);

    int set_gold(int);
    int get_gold(void);
    int decr_gold(int);
    int incr_gold(int);
    int decr_gold(void);
    int incr_gold(void);

    int set_health(int);
    int get_health(void);
    int decr_health(int);
    int incr_health(int);
    int decr_health(void);
    int incr_health(void);

    int set_health_max(int);
    int get_health_max(void);
    int decr_health_max(int);
    int incr_health_max(int);
    int decr_health_max(void);
    int incr_health_max(void);

    int set_owned_count(int);
    int get_owned_count(void);
    int decr_owned_count(int);
    int incr_owned_count(int);
    int decr_owned_count(void);
    int incr_owned_count(void);

    uint32_t set_timestamp_bounce_begin(uint32_t);
    uint32_t get_timestamp_bounce_begin(void);
    uint32_t decr_timestamp_bounce_begin(uint32_t);
    uint32_t incr_timestamp_bounce_begin(uint32_t);
    uint32_t decr_timestamp_bounce_begin(void);
    uint32_t incr_timestamp_bounce_begin(void);

    uint32_t set_timestamp_bounce_end(uint32_t);
    uint32_t get_timestamp_bounce_end(void);
    uint32_t decr_timestamp_bounce_end(uint32_t);
    uint32_t incr_timestamp_bounce_end(uint32_t);
    uint32_t decr_timestamp_bounce_end(void);
    uint32_t incr_timestamp_bounce_end(void);

    uint32_t set_timestamp_last_i_was_hit(uint32_t);
    uint32_t get_timestamp_last_i_was_hit(void);
    uint32_t decr_timestamp_last_i_was_hit(uint32_t);
    uint32_t incr_timestamp_last_i_was_hit(uint32_t);
    uint32_t decr_timestamp_last_i_was_hit(void);
    uint32_t incr_timestamp_last_i_was_hit(void);

    uint32_t set_timestamp_flip_start(uint32_t);
    uint32_t get_timestamp_flip_start(void);
    uint32_t decr_timestamp_flip_start(uint32_t);
    uint32_t incr_timestamp_flip_start(uint32_t);
    uint32_t decr_timestamp_flip_start(void);
    uint32_t incr_timestamp_flip_start(void);

    uint32_t set_timestamp_move_begin(uint32_t);
    uint32_t get_timestamp_move_begin(void);
    uint32_t decr_timestamp_move_begin(uint32_t);
    uint32_t incr_timestamp_move_begin(uint32_t);
    uint32_t decr_timestamp_move_begin(void);
    uint32_t incr_timestamp_move_begin(void);

    uint32_t set_timestamp_move_end(uint32_t);
    uint32_t get_timestamp_move_end(void);
    uint32_t decr_timestamp_move_end(uint32_t);
    uint32_t incr_timestamp_move_end(uint32_t);
    uint32_t decr_timestamp_move_end(void);
    uint32_t incr_timestamp_move_end(void);

    uint32_t set_timestamp_born(uint32_t);
    uint32_t get_timestamp_born(void);
    uint32_t decr_timestamp_born(uint32_t);
    uint32_t incr_timestamp_born(uint32_t);
    uint32_t decr_timestamp_born(void);
    uint32_t incr_timestamp_born(void);

    uint32_t set_timestamp_hunger_tick(uint32_t);
    uint32_t get_timestamp_hunger_tick(void);
    uint32_t decr_timestamp_hunger_tick(uint32_t);
    uint32_t incr_timestamp_hunger_tick(uint32_t);
    uint32_t decr_timestamp_hunger_tick(void);
    uint32_t incr_timestamp_hunger_tick(void);

    uint32_t set_timestamp_ai_next(uint32_t);
    uint32_t get_timestamp_ai_next(void);
    uint32_t decr_timestamp_ai_next(uint32_t);
    uint32_t incr_timestamp_ai_next(uint32_t);
    uint32_t decr_timestamp_ai_next(void);
    uint32_t incr_timestamp_ai_next(void);

    uint32_t set_timestamp_collision(uint32_t);
    uint32_t get_timestamp_collision(void);
    uint32_t decr_timestamp_collision(uint32_t);
    uint32_t incr_timestamp_collision(uint32_t);
    uint32_t decr_timestamp_collision(void);
    uint32_t incr_timestamp_collision(void);

    uint32_t set_owner_id(uint32_t);
    uint32_t get_owner_id(void);

    uint32_t set_weapon_id_carry_anim(uint32_t);
    uint32_t get_weapon_id_carry_anim(void);

    uint32_t set_weapon_id_use_anim(uint32_t);
    uint32_t get_weapon_id_use_anim(void);

    uint32_t set_weapon_tp_id(uint32_t);
    uint32_t get_weapon_tp_id(void);

    fpoint set_interpolated_mid_at(fpoint);
    fpoint get_interpolated_mid_at(void);

    Thingp owner_get();
    Thingp weapon_get_carry_anim(void);
    Thingp weapon_get_use_anim(void);
    Tpp weapon_get();
    bool ai_collisions_handle(void);
    bool ai_is_goal_for_me(point p, int priority, double *score);
    bool ai_is_obstacle_for_me(point p);
    bool ai_possible_hit(Thingp it, int x, int y, int dx, int dy);
    bool move(fpoint future_pos);
    bool move(fpoint future_pos, uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t fire);
    bool update_coordinates(void);
    void update_interpolated_position(void);
    bool will_attack(const Thingp it);
    bool will_avoid(const Thingp it);
    bool will_eat(const Thingp it);
    bool will_prefer(const Thingp it);
    const char *to_cstring(void);
    double collision_radius(void);
    double get_bounce(void);
    fpoint ai_get_next_hop(void);
    int ai_ai_hit_if_possible(Thingp hitter);
    int ai_ai_hit_if_possible(Thingp hitter, int damage);
    int ai_delay_after_moving_ms(void);
    int ai_hit_actual(Thingp orig_hitter, Thingp real_hitter, Thingp hitter, int damage);
    int ai_scent_distance(void);
    int bite_damage(void);
    int collision_attack(void);
    int collision_box(void);
    int collision_check(void);
    int collision_circle(void);
    int collision_hit_priority(void);
    int is_interesting(void);
    int gfx_animated(void);
    int gfx_animated_can_vflip(void);
    int gfx_animated_no_dir(void);
    int gfx_bounce_on_move(void);
    int gfx_can_hflip(void);
    int gfx_is_an_animation_only(void);
    int gfx_is_floor_deco(void);
    int gfx_is_wall_deco(void);
    int gfx_is_weapon_carry_anim(void);
    int gfx_is_weapon_use_anim(void);
    int gfx_large_shadow_caster(void);
    int gfx_outlined(void);
    int gfx_oversized_but_sitting_on_the_ground(void);
    int gfx_small_shadow_caster(void);
    int hunger_at_health_pct(void);
    int hunger_clock_freq_ms(void);
    int hunger_constant(void);
    int hunger_initial_health_at(void);
    int hunger_starving_at_health_pct(void);
    int is_active(void);
    int is_attackable(void);
    int is_bleeder(void);
    int is_blood(void);
    int is_combustable(void);
    int is_corpse_on_death(void);
    int is_corridor(void);
    int is_deep_water(void);
    int is_dirt(void);
    int is_door(void);
    int is_entrance(void);
    int is_exit(void);
    int is_explosion(void);
    int is_floor(void);
    int is_food(void);
    int is_grass(void);
    int is_gravel(void);
    int is_key(void);
    int is_lava(void);
    int is_less_preferred_terrain(point p);
    int is_light_strength(void);
    int is_made_of_meat(void);
    int is_meat_eater(void);
    int is_monst(void);
    int is_movable(void);
    int is_movement_blocking(void);
    int is_nutrition(void);
    int is_obstacle(void);
    int is_player(void);
    int is_projectile(void);
    int is_ripple(void);
    int is_rock(void);
    int is_rrr1(void);
    int is_rrr10(void);
    int is_rrr11(void);
    int is_rrr12(void);
    int is_rrr13(void);
    int is_rrr14(void);
    int is_rrr15(void);
    int is_rrr16(void);
    int is_rrr17(void);
    int is_rrr18(void);
    int is_rrr19(void);
    int is_rrr2(void);
    int is_rrr20(void);
    int is_rrr21(void);
    int is_rrr22(void);
    int is_rrr23(void);
    int is_rrr24(void);
    int is_rrr25(void);
    int is_rrr26(void);
    int is_loggable(void);
    int is_rrr28(void);
    int is_rrr29(void);
    int is_rrr3(void);
    int is_rrr30(void);
    int is_rrr31(void);
    int is_rrr32(void);
    int is_rrr33(void);
    int is_rrr34(void);
    int is_rrr35(void);
    int is_rrr36(void);
    int is_rrr37(void);
    int is_rrr38(void);
    int is_rrr39(void);
    int is_rrr4(void);
    int is_rrr40(void);
    int is_rrr41(void);
    int is_rrr42(void);
    int is_rrr43(void);
    int is_rrr44(void);
    int is_rrr45(void);
    int is_rrr46(void);
    int is_rrr47(void);
    int is_rrr48(void);
    int is_rrr49(void);
    int is_rrr5(void);
    int is_rrr50(void);
    int is_rrr6(void);
    int is_rrr7(void);
    int is_rrr8(void);
    int is_rrr9(void);
    int is_snow(void);
    int is_soil(void);
    int is_undead(void);
    int is_wall(void);
    int is_water(void);
    int is_water_dweller(void);
    int is_water_hater(void);
    int is_weapon(void);
    int weapon_damage(void);
    int weapon_use_delay_hundredths(void);
    int weapon_use_distance(void);
    int z_depth(void);
    std::string bite_damage_hd(void);
    std::string is_nutrition_hd(void);
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
    uint8_t is_visible();
    void achieve_goals_in_life();
    void ai_possible_hits_find_best(void);
    void animate();
    void attach(void);
    void blit(double offset_x, double offset_y, int x, int y);
    void blit_grass_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void blit_gravel_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_non_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br); void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, double x1, double y1, double x2, double y2, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, double x1, double y1, double x2, double y2, const fpoint &tl, const fpoint &br);
    void blit_rock_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void blit_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br);
    void blit_snow_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void blit_soil_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void blit_upside_down(double offset_x, double offset_y, int x, int y);
    void blit_wall_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void bounce(double bounce_height, double bounce_fade, uint32_t ms, uint32_t bounce_count);
    void collision_check_do();
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dead(Thingp killer, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));
    void dead(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dead_(Thingp killer, const char *fmt, va_list args); // compile error without
    void dead_(const char *fmt, va_list args); // compile error without
    void destroy();
    void destroyed(void);
    void detach(void);
    void die(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void die_(const char *fmt, va_list args); // compile error without
    void dir_set_bl(void);
    void dir_set_br(void);
    void dir_set_down(void);
    void dir_set_left(void);
    void dir_set_none(void);
    void dir_set_right(void);
    void dir_set_tl(void);
    void dir_set_tr(void);
    void dir_set_up(void);
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void health_boost(int v);
    void hide();
    void hooks_remove();
    void hunger_clock();
    void init(std::string name, fpoint at, fpoint jitter);
    void kill(void);
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void log_(const char *fmt, va_list args); // compile error without
    void move_carried_items(void);
    void move_delta(fpoint, bool immediately);
    void move_to(fpoint to);
    void move_to_immediately(fpoint to);
    void set_owner(Thingp owner);
    void sheath(void);
    void tick();
    void to_coords(fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3);
    void unwield(const char *why);
    void update_light(void);
    void update_pos(fpoint, bool immediately);
    void use(void);
    void visible();
    void weapon_get_use_offset(double *dx, double *dy);
    void weapon_set_carry_anim(Thingp weapon_carry_anim);
    void weapon_set_carry_anim_id(uint32_t weapon_carry_anim_id);
    void weapon_set_placement(void);
    void weapon_set_use_anim(Thingp weapon_use_anim);
    void weapon_set_use_anim_id(uint32_t weapon_use_anim_id);
    void weapon_sheath(void);
    void weapon_wield_next();
    void wield(Tpp tp);

    void dump(std::string prefix, std::ostream &out);
} Thing;

std::ostream& operator<<(std::ostream &out, Bits<const Thing & > const my);
std::istream& operator>>(std::istream &in, Bits<Thing &> my);

struct ThingDisplaySortKey {
    int16_t y;
    uint32_t id;
};

struct thing_display_sort_cmp : public std::binary_function<struct ThingDisplaySortKey, struct ThingDisplaySortKey, bool>
{
    bool operator()(const struct ThingDisplaySortKey& lhs,
                    const struct ThingDisplaySortKey& rhs) const
    {
        if (lhs.y < rhs.y) {
            return (true);
        } else if (lhs.y > rhs.y) {
            return (false);
        }

        if (lhs.id < rhs.id) {
            return (true);
        } else {
            return (false);
        }
    }
};

typedef std::unordered_map< struct ThingDisplaySortKey, Thingp,
                  thing_display_sort_cmp > ThingDisplayOrder;

Thingp thing_find(uint32_t name);
Thingp thing_new(std::string tp_name, Thingp owner);
Thingp thing_new(std::string tp_name, fpoint at, fpoint jitter = fpoint(0, 0));
bool things_overlap(Thingp t, Thingp o);
bool things_overlap(Thingp t, fpoint t_at, Thingp o);
void thing_gc(void);
void thing_map_scroll_to_player(void);
void thing_render_all(void);
void things_tick(void);

#endif // THING_H
