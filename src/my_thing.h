
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#ifndef _MY_THING_H
#define _MY_THING_H

#include <unordered_map>
#include <memory>

typedef class Thing* Thingp;
typedef std::unordered_map< uint32_t, Thingp > Things;

#include "my_thing_template.h"
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

class Path {
public:
    Path () {}
    Path (std::vector<point> &p, int c) : path(p), cost(c) { }

    std::vector<point> path;
    int                cost {};
};

extern Path astar_solve(point start, std::multiset<Goal> &goals, Dmap *dmap);

typedef class AgeMap {
public:
    uint32_t val[CHUNK_WIDTH][CHUNK_HEIGHT] = {{0}};
    AgeMap(void) {}

    template <class Archive>
    void serialize (Archive & archive)
    {
        archive(cereal::make_nvp("val", val));
    }
} AgeMap;

class Monst
{
public:
    AgeMap       *age_map;                   // How old a cell is
    Dmap         *dmap_goals;
    Dmap         *dmap_scent;
    Lightp       light;                      // Have a light source?
    Tpp          tp;                         // Common settings
    Worldp       world;
};

class Thing
{
private:
public:
    Thing (void)
    {
        is_init = false;
        newptr(this, "thing");
    }

    ~Thing (void)
    {
        verify(this);
        if (!is_init) {
            return;
        }
        if (is_being_destroyed) {
            die("death recursion");
        }
        is_being_destroyed = true;
        destroy();
        if (monst) {
            oldptr(monst);
            delete monst;
        }
        oldptr(this);
    }

    template <class Archive>
    void serialize (Archive & archive )
    {
        archive(cereal::make_nvp("id", id));
    }

    void new_monst (void)
    {
        if (unlikely(!monst)) { 
            monst = new Monst(); 
            newptr(monst, "Monst");
        }
    }

    AgeMap *age_map (void)
    {
        new_monst();
        return (monst->age_map);
    }

    void new_age_map (void)
    {
        new_monst();
        monst->age_map = new AgeMap();
        newptr(monst->age_map, "AgeMap");
    }

    void delete_age_map (void)
    {
        if (monst && monst->age_map) { 
            oldptr(monst->age_map);
            delete monst->age_map; monst->age_map = 0;
        }
    }

    Monst        *monst;
    Dmap         *dmap_goals;
    Dmap         *dmap_scent;
    Lightp       light;                      // Have a light source?
    Tpp          tp;                         // Common settings
    float        bounce_fade;                // 0.1; rapid, 0.9 slow
    float        bounce_height;              // Percentage of tile height.
    float        rot;                        // GL co-orids
    float        submerged_offset;           // GL co-orids
    fpoint       br;                         // On screen coordinates
    fpoint       ground_at;
    fpoint       interpolated_mid_at;
    fpoint       last_attached;
    fpoint       last_blit_br;               // GL co-orids
    fpoint       last_blit_tl;               // GL co-orids
    fpoint       last_mid_at;                // Previous hop where we were.
    fpoint       mid_at;                     // Grid coordinates.
    fpoint       old_br;
    fpoint       tl;                         // On screen coordinates
    fsize        sz;
    int16_t      gold;
    int16_t      health;
    int16_t      health_max;
    uint8_t      bounce_count;
    uint8_t      owned_count;                // How many things this thing owns.
    uint16_t     tile_bl;
    uint16_t     tile_bot;
    uint16_t     tile_br;
    uint16_t     tile_curr;
    uint16_t     tile_left;
    uint16_t     tile_right;
    uint16_t     tile_tl;
    uint16_t     tile_top;
    uint16_t     tile_tr;
    uint16_t     weapon_tp_id;               // Weapon thing template.
    uint32_t     hunger_tick_last_ms;        // Ticks every time does something. Used from memory aging
    uint32_t     id;                         // Unique per thing.
    uint32_t     id_owner;                   // Who created this thing?
    uint32_t     id_weapon_carry_anim;
    uint32_t     id_weapon_use_anim;
    uint32_t     timestamp_ai_next;
    uint32_t     timestamp_born;
    uint32_t     timestamp_bounce_begin;
    uint32_t     timestamp_bounce_end;
    uint32_t     timestamp_collision;
    uint32_t     timestamp_flip_start;       // Used for animating the steps.
    uint32_t     timestamp_last_attacked;
    uint32_t     timestamp_last_i_was_hit;
    uint32_t     timestamp_move_begin;
    uint32_t     timestamp_move_end;
    uint32_t     timestamp_move_start;
    uint32_t     timestamp_next_frame;
    uint8_t      depth;                      // Display order
    unsigned int dir:4;                      // Direction
    unsigned int has_ever_moved:1;
    unsigned int is_attached:1;
    unsigned int is_being_destroyed:1;
    unsigned int is_bloodied:1;
    unsigned int is_bouncing:1;
    unsigned int is_dead:1;
    unsigned int is_facing_left:1;
    unsigned int is_hidden:1;
    unsigned int is_hungry:1;
    unsigned int is_init:1;
    unsigned int is_lit:1;
    unsigned int is_moving:1;
    unsigned int is_open:1;
    unsigned int is_sleeping:1;
    unsigned int is_starving:1;
    unsigned int is_submerged:1;
    unsigned int is_waiting_for_ai:1;

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
    bool will_attack(const Thingp it);
    bool will_avoid(const Thingp it);
    bool will_eat(const Thingp it);
    bool will_prefer(const Thingp it);
    const char *to_cstring(void);
    double collision_radius(void)                          { return (tp_collision_radius(tp)); }
    double get_bounce(void);
    fpoint ai_get_next_hop(void);
    int ai_delay_after_moving_ms(void)                     { return (tp_ai_delay_after_moving_ms(tp)); }
    int ai_scent_distance(void)                            { return (tp_ai_scent_distance(tp)); }
    int bite_damage(void)                                  { return (tp->bite_damage()); }
    int collision_attack(void)                             { return (tp_collision_attack(tp)); }
    int collision_box(void)                                { return (tp_collision_box(tp)); }
    int collision_check(void)                              { return (tp_collision_check(tp)); }
    int collision_circle(void)                             { return (tp_collision_circle(tp)); }
    int collision_hit_priority(void)                       { return (tp_collision_hit_priority(tp)); }
    int does_nothing(void)                                 { return (tp_does_nothing(tp)); }
    int gfx_animated(void)                                 { return (tp_gfx_animated(tp)); }
    int gfx_animated_can_vflip(void)                       { return (tp_gfx_animated_can_vflip(tp)); }
    int gfx_animated_no_dir(void)                          { return (tp_gfx_animated_no_dir(tp)); }
    int gfx_bounce_on_move(void)                           { return (tp_gfx_bounce_on_move(tp)); }
    int gfx_can_hflip(void)                                { return (tp_gfx_can_hflip(tp)); }
    int gfx_is_an_animation_only(void)                     { return (tp_gfx_is_an_animation_only(tp)); }
    int gfx_is_floor_deco(void)                            { return (tp_gfx_is_floor_deco(tp)); }
    int gfx_is_wall_deco(void)                             { return (tp_gfx_is_wall_deco(tp)); }
    int gfx_is_weapon_carry_anim(void)                     { return (tp_gfx_is_weapon_carry_anim(tp)); }
    int gfx_is_weapon_use_anim(void)                       { return (tp_gfx_is_weapon_use_anim(tp)); }
    int gfx_large_shadow_caster(void)                      { return (tp_gfx_large_shadow_caster(tp)); }
    int gfx_outlined(void)                                 { return (tp_gfx_outlined(tp)); }
    int gfx_oversized_but_sitting_on_the_ground(void)      { return (tp_gfx_oversized_but_sitting_on_the_ground(tp)); }
    int gfx_small_shadow_caster(void)                      { return (tp_gfx_small_shadow_caster(tp)); }
    int ai_hit_actual(Thingp orig_hitter, Thingp real_hitter, Thingp hitter, int damage);
    int ai_ai_hit_if_possible(Thingp hitter);
    int ai_ai_hit_if_possible(Thingp hitter, int damage);
    int hunger_at_health_pct(void)                         { return (tp_hunger_at_health_pct(tp)); }
    int hunger_clock_freq_ms(void)                         { return (tp_hunger_clock_freq_ms(tp)); }
    int hunger_constant(void)                              { return (tp_hunger_constant(tp)); }
    int hunger_initial_health_at(void)                     { return (tp_hunger_initial_health_at(tp)); }
    int hunger_starving_at_health_pct(void)                { return (tp_hunger_starving_at_health_pct(tp)); }
    int is_active(void)                                    { return (tp_is_active(tp)); }
    int is_attackable(void)                                { return (tp_is_attackable(tp)); }
    int is_bleeder(void)                                   { return (tp_is_bleeder(tp)); }
    int is_blood(void)                                     { return (tp_is_blood(tp)); }
    int is_combustable(void)                               { return (tp_is_combustable(tp)); }
    int is_corpse_on_death(void)                           { return (tp_is_corpse_on_death(tp)); }
    int is_corridor(void)                                  { return (tp_is_corridor(tp)); }
    int is_deep_water(void)                                { return (tp_is_deep_water(tp)); }
    int is_dirt(void)                                      { return (tp_is_dirt(tp)); }
    int is_door(void)                                      { return (tp_is_door(tp)); }
    int is_entrance(void)                                  { return (tp_is_entrance(tp)); }
    int is_exit(void)                                      { return (tp_is_exit(tp)); }
    int is_explosion(void)                                 { return (tp_is_explosion(tp)); }
    int is_floor(void)                                     { return (tp_is_floor(tp)); }
    int is_food(void)                                      { return (tp_is_food(tp)); }
    int is_grass(void)                                     { return (tp_is_grass(tp)); }
    int is_gravel(void)                                    { return (tp_is_gravel(tp)); }
    int is_key(void)                                       { return (tp_is_key(tp)); }
    int is_lava(void)                                      { return (tp_is_lava(tp)); }
    int is_less_preferred_terrain(point p);
    int is_light_strength(void)                            { return (tp_is_light_strength(tp)); }
    int is_made_of_meat(void)                              { return (tp_is_made_of_meat(tp)); }
    int is_meat_eater(void)                                { return (tp_is_meat_eater(tp)); }
    int is_monst(void)                                     { return (tp_is_monst(tp)); }
    int is_movable(void)                                   { return (tp_is_movable(tp)); }
    int is_movement_blocking(void)                         { return (tp_is_movement_blocking(tp)); }
    int is_obstacle(void)                                  { return (tp_is_obstacle(tp)); }
    int is_player(void)                                    { return (tp_is_player(tp)); }
    int is_projectile(void)                                { return (tp_is_projectile(tp)); }
    int is_ripple(void)                                    { return (tp_is_ripple(tp)); }
    int is_rock(void)                                      { return (tp_is_rock(tp)); }
    int is_rrr1(void)                                      { return (tp_is_rrr1(tp)); }
    int is_rrr10(void)                                     { return (tp_is_rrr10(tp)); }
    int is_rrr11(void)                                     { return (tp_is_rrr11(tp)); }
    int is_rrr12(void)                                     { return (tp_is_rrr12(tp)); }
    int is_rrr13(void)                                     { return (tp_is_rrr13(tp)); }
    int is_rrr14(void)                                     { return (tp_is_rrr14(tp)); }
    int is_rrr15(void)                                     { return (tp_is_rrr15(tp)); }
    int is_rrr16(void)                                     { return (tp_is_rrr16(tp)); }
    int is_rrr17(void)                                     { return (tp_is_rrr17(tp)); }
    int is_rrr18(void)                                     { return (tp_is_rrr18(tp)); }
    int is_rrr19(void)                                     { return (tp_is_rrr19(tp)); }
    int is_rrr2(void)                                      { return (tp_is_rrr2(tp)); }
    int is_rrr20(void)                                     { return (tp_is_rrr20(tp)); }
    int is_rrr21(void)                                     { return (tp_is_rrr21(tp)); }
    int is_rrr22(void)                                     { return (tp_is_rrr22(tp)); }
    int is_rrr23(void)                                     { return (tp_is_rrr23(tp)); }
    int is_rrr24(void)                                     { return (tp_is_rrr24(tp)); }
    int is_rrr25(void)                                     { return (tp_is_rrr25(tp)); }
    int is_rrr26(void)                                     { return (tp_is_rrr26(tp)); }
    int is_rrr27(void)                                     { return (tp_is_rrr27(tp)); }
    int is_rrr28(void)                                     { return (tp_is_rrr28(tp)); }
    int is_rrr29(void)                                     { return (tp_is_rrr29(tp)); }
    int is_rrr3(void)                                      { return (tp_is_rrr3(tp)); }
    int is_rrr30(void)                                     { return (tp_is_rrr30(tp)); }
    int is_rrr31(void)                                     { return (tp_is_rrr31(tp)); }
    int is_rrr32(void)                                     { return (tp_is_rrr32(tp)); }
    int is_rrr33(void)                                     { return (tp_is_rrr33(tp)); }
    int is_rrr34(void)                                     { return (tp_is_rrr34(tp)); }
    int is_rrr35(void)                                     { return (tp_is_rrr35(tp)); }
    int is_rrr36(void)                                     { return (tp_is_rrr36(tp)); }
    int is_rrr37(void)                                     { return (tp_is_rrr37(tp)); }
    int is_rrr38(void)                                     { return (tp_is_rrr38(tp)); }
    int is_rrr39(void)                                     { return (tp_is_rrr39(tp)); }
    int is_rrr4(void)                                      { return (tp_is_rrr4(tp)); }
    int is_rrr40(void)                                     { return (tp_is_rrr40(tp)); }
    int is_rrr41(void)                                     { return (tp_is_rrr41(tp)); }
    int is_rrr42(void)                                     { return (tp_is_rrr42(tp)); }
    int is_rrr43(void)                                     { return (tp_is_rrr43(tp)); }
    int is_rrr44(void)                                     { return (tp_is_rrr44(tp)); }
    int is_rrr45(void)                                     { return (tp_is_rrr45(tp)); }
    int is_rrr46(void)                                     { return (tp_is_rrr46(tp)); }
    int is_rrr47(void)                                     { return (tp_is_rrr47(tp)); }
    int is_rrr48(void)                                     { return (tp_is_rrr48(tp)); }
    int is_rrr49(void)                                     { return (tp_is_rrr49(tp)); }
    int is_rrr5(void)                                      { return (tp_is_rrr5(tp)); }
    int is_rrr50(void)                                     { return (tp_is_rrr50(tp)); }
    int is_rrr6(void)                                      { return (tp_is_rrr6(tp)); }
    int is_rrr7(void)                                      { return (tp_is_rrr7(tp)); }
    int is_rrr8(void)                                      { return (tp_is_rrr8(tp)); }
    int is_rrr9(void)                                      { return (tp_is_rrr9(tp)); }
    int is_snow(void)                                      { return (tp_is_snow(tp)); }
    int is_soil(void)                                      { return (tp_is_soil(tp)); }
    int is_undead(void)                                    { return (tp_is_undead(tp)); }
    int is_wall(void)                                      { return (tp_is_wall(tp)); }
    int is_water(void)                                     { return (tp_is_water(tp)); }
    int is_water_dweller(void)                             { return (tp_is_water_dweller(tp)); }
    int is_water_hater(void)                               { return (tp_is_water_hater(tp)); }
    int is_weapon(void)                                    { return (tp_is_weapon(tp)); }
    int weapon_damage(void)                                { return (tp_weapon_damage(tp)); }
    int weapon_use_delay_hundredths(void)                  { return (tp_weapon_use_delay_hundredths(tp)); }
    int weapon_use_distance(void)                          { return (tp_weapon_use_distance(tp)); }
    int z_depth(void)                                      { return (tp_z_depth(tp)); }
    std::string bite_damage_hd(void)                       { return (tp_bite_damage_hd(tp)); }
    std::string is_nutrition_hd(void)                         { return (tp_is_nutrition_hd(tp)); }
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
    void blit_grass_cladding(fpoint &tl, fpoint &br);
    void blit_gravel_cladding(fpoint &tl, fpoint &br);
    void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_non_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br); void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, double x1, double y1, double x2, double y2, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, double x1, double y1, double x2, double y2, const fpoint &tl, const fpoint &br);
    void blit_rock_cladding(fpoint &tl, fpoint &br);
    void blit_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br);
    void blit_snow_cladding(fpoint &tl, fpoint &br);
    void blit_soil_cladding(fpoint &tl, fpoint &br);
    void blit_upside_down(double offset_x, double offset_y, int x, int y);
    void blit_wall_cladding(fpoint &tl, fpoint &br);
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
    void kill(void);
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void log_(const char *fmt, va_list args); // compile error without
    void move_carried_items(void);
    void move_delta(fpoint);
    void move_to(fpoint to);
    void set_owner(Thingp owner);
    void sheath(void);
    void tick();
    void to_coords(fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3);
    void unwield(const char *why);
    void update_light(void);
    void update_pos(fpoint);
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
    int is_nutrition(void)                                    { return (tp->is_nutrition()); }
};

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
