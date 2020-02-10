//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_THING_H
#define _MY_THING_H

#include <unordered_map>
#include <memory>
#include <set>

typedef struct Thing_* Thingp;
typedef struct Monst_* Monstp;
typedef struct AgeMap_* AgeMapp;
typedef struct Dmap_* Dmapp;
typedef std::unordered_map< uint32_t, Thingp > Things;

#include "my_time.h"
#include "my_light.h"

class Goal
{
public:
    float score = {0};
    point  at;
    std::string why;

    Goal () {}
    Goal (float score) : score(score) { }

    friend bool operator<(const class Goal & lhs, const class Goal & rhs) {
        //
        // Reverse sorted
        //
        return lhs.score > rhs.score;
    }
};

class Path {
public:
    Path () {}
    Path (std::vector<point> &p, int c) : path(p), cost(c) { }

    std::vector<point> path;
    int                cost {};
};

extern Path astar_solve(const point &at, std::multiset<Goal> &goals, Dmap *dmap, const point &start, const point &end);

typedef struct AgeMap_ {
    std::array<std::array<timestamp_t, MAP_HEIGHT>, MAP_WIDTH> val {};
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
    Dmap         *dmap_scent = {};
    Lightp       light = {};                 // Have a light source?

    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    color        light_col {};
    float        bounce_fade = {};           // 0.1; rapid, 0.9 slow
    float        bounce_height = {};         // Percentage of tile height.
    float        fadeup_fade = {};           // 0.1; rapid, 0.9 slow
    float        fadeup_height = {};         // Percentage of tile height.
    float        rot = {};                   // GL co-orids
    float        submerged_offset = {};      // GL co-orids
    fpoint       interpolated_mid_at;
    fpoint       lunge_to = {};              // When a monst attacks something
    int          bounce_count = {};
    int          gold = {};
    int          light_quality {};
    int          light_strength {};
    int          owned_count = {};           // How many things this thing owns.
    int          stats01 = {};
    int          stats02 = {};
    int          stats03 = {};
    int          stats04 = {};
    int          stats05 = {};
    int          stats06 = {};
    int          stats07 = {};
    int          stats08 = {};
    int          stats09 = {};
    int          stats10 = {};
    int          stats11 = {};
    int          stats12 = {};
    int          stats13 = {};
    int          stats14 = {};
    int          stats15 = {};
    int          stats16 = {};
    int          stats17 = {};
    int          stats18 = {};
    int          stats19 = {};
    int          stats20 = {};
    int          stats_attack = {};
    int          stats_attack_max = {};
    int          stats_attack_rate_tenths = {};
    int          stats_attacked_rate_tenths = {};
    int          stats_defence = {};
    int          stats_defence_max = {};
    int          stats_health = {};
    int          stats_health_max = {};
    std::list<uint32_t> carrying;
    std::vector<point>  move_path;
    std::string  msg;                        // Text that floats on screen
    timestamp_t  timestamp_ai_next {};
    timestamp_t  timestamp_born {};
    timestamp_t  timestamp_bounce_begin {};
    timestamp_t  timestamp_bounce_end {};
    timestamp_t  timestamp_collision {};
    timestamp_t  timestamp_fadeup_begin {};
    timestamp_t  timestamp_fadeup_end {};
    timestamp_t  timestamp_flip_start {};    // Used for animating the steps.
    timestamp_t  timestamp_hunger_tick {};   // Ticks every time does something. Used from memory aging
    timestamp_t  timestamp_last_attack {};
    timestamp_t  timestamp_last_attacked {};
    timestamp_t  timestamp_lunge_begin {};
    timestamp_t  timestamp_lunge_end {};
    timestamp_t  timestamp_move_begin {};
    timestamp_t  timestamp_move_end {};
    uint32_t     owner_id {};                // Who created this thing?
    uint32_t     tick = {};                  // Increments on completion of move
    uint32_t     weapon_id {};               // Current weapon
    uint32_t     weapon_id_carry_anim {};
    uint32_t     weapon_id_use_anim {};
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
} Monst;
std::ostream& operator<<(std::ostream &out, Bits<const Monst & > const my);
std::istream& operator>>(std::istream &in, Bits<Monst &> my);

typedef struct Thing_ {
public:
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
    int16_t tp_id                 {-1};  // Common settings
    uint16_t tile_curr            {};
    timestamp_t timestamp_next_frame {};
    uint32_t dir:4                {}; // Direction

    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    uint32_t has_ever_moved:1     {};
    uint32_t has_light:1          {};
    uint32_t is_attached:1        {};
    uint32_t is_being_destroyed:1 {};
    uint32_t is_blitted:1         {};
    uint32_t is_bloodied:1        {};
    uint32_t is_bouncing:1        {};
    uint32_t is_dead:1            {};
    uint32_t is_facing_left:1     {};
    uint32_t is_fadeup:1          {};
    uint32_t is_hidden:1          {};
    uint32_t is_hungry:1          {};
    uint32_t is_move_done:1       {}; // has moved/hit and finished its move
    uint32_t is_moving:1          {};
    uint32_t is_open:1            {};
    uint32_t is_pending_gc:1      {};
    uint32_t is_sleeping:1        {};
    uint32_t is_starving:1        {};
    uint32_t is_submerged:1       {};
    uint32_t is_waiting_to_move:1 {};
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

private:
    //
    // As this is called a lot, probably worth the memory
    //
    Tpp      mytp                 {};
public:
    const Tpp tp(void)
    {
        if (likely(mytp != nullptr)) {
            return (mytp);
        }
        if (unlikely(tp_id == -1)) {
            return (nullptr);
        }
        mytp = tp_id_map[tp_id - 1];
        return (mytp);
    }

    static void update_all(void);

    void new_monst(void);
    void get_tiles(ThingTiles *tiles);

    AgeMap *get_age_map(void);
    void new_age_map(void);
    void delete_age_map(void);

    Dmap *get_dmap_scent(void);
    void new_dmap_scent(void);
    void delete_dmap_scent(void);

    Lightp get_light(void);
    void new_light(fpoint at,
                   double strength,
                   LightQuality quality = LIGHT_QUALITY_POINT,
                   color col = WHITE);
    void delete_light(void);

    void set_lunge_to(fpoint);
    fpoint get_lunge_to(void);

    void set_bounce_height(float);
    float get_bounce_height(void);

    void set_bounce_fade(float);
    float get_bounce_fade(void);

    void set_bounce_count(int);
    int get_bounce_count(void);

    void set_fadeup_height(float);
    float get_fadeup_height(void);

    void set_fadeup_fade(float);
    float get_fadeup_fade(void);

    void set_rot(float);
    float get_rot(void);

    void set_msg(std::string);
    std::string get_msg(void);

    void set_submerged_offset(float);
    float get_submerged_offset(void);

    uint32_t set_tick(uint32_t);
    uint32_t get_tick(void);
    uint32_t decr_tick(uint32_t);
    uint32_t incr_tick(uint32_t);
    uint32_t decr_tick(void);
    uint32_t incr_tick(void);

    int set_gold(int);
    int get_gold(void);
    int decr_gold(int);
    int incr_gold(int);
    int decr_gold(void);
    int incr_gold(void);

    int set_stats_health(int);
    int get_stats_health(void);
    int decr_stats_health(int);
    int incr_stats_health(int);
    int decr_stats_health(void);
    int incr_stats_health(void);

    int set_stats_health_max(int);
    int get_stats_health_max(void);
    int decr_stats_health_max(int);
    int incr_stats_health_max(int);
    int decr_stats_health_max(void);
    int incr_stats_health_max(void);

    int set_stats_defence(int);
    int get_stats_defence(void);
    int decr_stats_defence(int);
    int incr_stats_defence(int);
    int decr_stats_defence(void);
    int incr_stats_defence(void);

    int set_stats_defence_max(int);
    int get_stats_defence_max(void);
    int decr_stats_defence_max(int);
    int incr_stats_defence_max(int);
    int decr_stats_defence_max(void);
    int incr_stats_defence_max(void);

    int set_stats_attack(int);
    int get_stats_attack(void);
    int decr_stats_attack(int);
    int incr_stats_attack(int);
    int decr_stats_attack(void);
    int incr_stats_attack(void);

    int set_stats_attack_max(int);
    int get_stats_attack_max(void);
    int decr_stats_attack_max(int);
    int incr_stats_attack_max(int);
    int decr_stats_attack_max(void);
    int incr_stats_attack_max(void);

    int set_stats_attack_rate_tenths(int);
    int get_stats_attack_rate_tenths(void);
    int decr_stats_attack_rate_tenths(int);
    int incr_stats_attack_rate_tenths(int);
    int decr_stats_attack_rate_tenths(void);
    int incr_stats_attack_rate_tenths(void);

    int set_stats_attacked_rate_tenths(int);
    int get_stats_attacked_rate_tenths(void);
    int decr_stats_attacked_rate_tenths(int);
    int incr_stats_attacked_rate_tenths(int);
    int decr_stats_attacked_rate_tenths(void);
    int incr_stats_attacked_rate_tenths(void);

    int set_stats01(int);
    int get_stats01(void);
    int decr_stats01(int);
    int incr_stats01(int);
    int decr_stats01(void);
    int incr_stats01(void);

    int set_stats02(int);
    int get_stats02(void);
    int decr_stats02(int);
    int incr_stats02(int);
    int decr_stats02(void);
    int incr_stats02(void);

    int set_stats03(int);
    int get_stats03(void);
    int decr_stats03(int);
    int incr_stats03(int);
    int decr_stats03(void);
    int incr_stats03(void);

    int set_stats04(int);
    int get_stats04(void);
    int decr_stats04(int);
    int incr_stats04(int);
    int decr_stats04(void);
    int incr_stats04(void);

    int set_stats05(int);
    int get_stats05(void);
    int decr_stats05(int);
    int incr_stats05(int);
    int decr_stats05(void);
    int incr_stats05(void);

    int set_stats06(int);
    int get_stats06(void);
    int decr_stats06(int);
    int incr_stats06(int);
    int decr_stats06(void);
    int incr_stats06(void);

    int set_stats07(int);
    int get_stats07(void);
    int decr_stats07(int);
    int incr_stats07(int);
    int decr_stats07(void);
    int incr_stats07(void);

    int set_stats08(int);
    int get_stats08(void);
    int decr_stats08(int);
    int incr_stats08(int);
    int decr_stats08(void);
    int incr_stats08(void);

    int set_stats09(int);
    int get_stats09(void);
    int decr_stats09(int);
    int incr_stats09(int);
    int decr_stats09(void);
    int incr_stats09(void);

    int set_stats10(int);
    int get_stats10(void);
    int decr_stats10(int);
    int incr_stats10(int);
    int decr_stats10(void);
    int incr_stats10(void);

    int set_stats11(int);
    int get_stats11(void);
    int decr_stats11(int);
    int incr_stats11(int);
    int decr_stats11(void);
    int incr_stats11(void);

    int set_stats12(int);
    int get_stats12(void);
    int decr_stats12(int);
    int incr_stats12(int);
    int decr_stats12(void);
    int incr_stats12(void);

    int set_stats13(int);
    int get_stats13(void);
    int decr_stats13(int);
    int incr_stats13(int);
    int decr_stats13(void);
    int incr_stats13(void);

    int set_stats14(int);
    int get_stats14(void);
    int decr_stats14(int);
    int incr_stats14(int);
    int decr_stats14(void);
    int incr_stats14(void);

    int set_stats15(int);
    int get_stats15(void);
    int decr_stats15(int);
    int incr_stats15(int);
    int decr_stats15(void);
    int incr_stats15(void);

    int set_stats16(int);
    int get_stats16(void);
    int decr_stats16(int);
    int incr_stats16(int);
    int decr_stats16(void);
    int incr_stats16(void);

    int set_stats17(int);
    int get_stats17(void);
    int decr_stats17(int);
    int incr_stats17(int);
    int decr_stats17(void);
    int incr_stats17(void);

    int set_stats18(int);
    int get_stats18(void);
    int decr_stats18(int);
    int incr_stats18(int);
    int decr_stats18(void);
    int incr_stats18(void);

    int set_stats19(int);
    int get_stats19(void);
    int decr_stats19(int);
    int incr_stats19(int);
    int decr_stats19(void);
    int incr_stats19(void);

    int set_stats20(int);
    int get_stats20(void);
    int decr_stats20(int);
    int incr_stats20(int);
    int decr_stats20(void);
    int incr_stats20(void);

    int set_owned_count(int);
    int get_owned_count(void);
    int decr_owned_count(int);
    int incr_owned_count(int);
    int decr_owned_count(void);
    int incr_owned_count(void);

    timestamp_t set_timestamp_lunge_begin(timestamp_t);
    timestamp_t get_timestamp_lunge_begin(void);
    timestamp_t decr_timestamp_lunge_begin(timestamp_t);
    timestamp_t incr_timestamp_lunge_begin(timestamp_t);
    timestamp_t decr_timestamp_lunge_begin(void);
    timestamp_t incr_timestamp_lunge_begin(void);

    timestamp_t set_timestamp_lunge_end(timestamp_t);
    timestamp_t get_timestamp_lunge_end(void);
    timestamp_t decr_timestamp_lunge_end(timestamp_t);
    timestamp_t incr_timestamp_lunge_end(timestamp_t);
    timestamp_t decr_timestamp_lunge_end(void);
    timestamp_t incr_timestamp_lunge_end(void);

    timestamp_t set_timestamp_bounce_begin(timestamp_t);
    timestamp_t get_timestamp_bounce_begin(void);
    timestamp_t decr_timestamp_bounce_begin(timestamp_t);
    timestamp_t incr_timestamp_bounce_begin(timestamp_t);
    timestamp_t decr_timestamp_bounce_begin(void);
    timestamp_t incr_timestamp_bounce_begin(void);

    timestamp_t set_timestamp_bounce_end(timestamp_t);
    timestamp_t get_timestamp_bounce_end(void);
    timestamp_t decr_timestamp_bounce_end(timestamp_t);
    timestamp_t incr_timestamp_bounce_end(timestamp_t);
    timestamp_t decr_timestamp_bounce_end(void);
    timestamp_t incr_timestamp_bounce_end(void);

    timestamp_t set_timestamp_fadeup_begin(timestamp_t);
    timestamp_t get_timestamp_fadeup_begin(void);
    timestamp_t decr_timestamp_fadeup_begin(timestamp_t);
    timestamp_t incr_timestamp_fadeup_begin(timestamp_t);
    timestamp_t decr_timestamp_fadeup_begin(void);
    timestamp_t incr_timestamp_fadeup_begin(void);

    timestamp_t set_timestamp_fadeup_end(timestamp_t);
    timestamp_t get_timestamp_fadeup_end(void);
    timestamp_t decr_timestamp_fadeup_end(timestamp_t);
    timestamp_t incr_timestamp_fadeup_end(timestamp_t);
    timestamp_t decr_timestamp_fadeup_end(void);
    timestamp_t incr_timestamp_fadeup_end(void);

    timestamp_t set_timestamp_last_attacked(timestamp_t);
    timestamp_t get_timestamp_last_attacked(void);
    timestamp_t decr_timestamp_last_attacked(timestamp_t);
    timestamp_t incr_timestamp_last_attacked(timestamp_t);
    timestamp_t decr_timestamp_last_attacked(void);
    timestamp_t incr_timestamp_last_attacked(void);

    timestamp_t set_timestamp_last_attack(timestamp_t);
    timestamp_t get_timestamp_last_attack(void);
    timestamp_t decr_timestamp_last_attack(timestamp_t);
    timestamp_t incr_timestamp_last_attack(timestamp_t);
    timestamp_t decr_timestamp_last_attack(void);
    timestamp_t incr_timestamp_last_attack(void);

    timestamp_t set_timestamp_flip_start(timestamp_t);
    timestamp_t get_timestamp_flip_start(void);
    timestamp_t decr_timestamp_flip_start(timestamp_t);
    timestamp_t incr_timestamp_flip_start(timestamp_t);
    timestamp_t decr_timestamp_flip_start(void);
    timestamp_t incr_timestamp_flip_start(void);

    timestamp_t set_timestamp_move_begin(timestamp_t);
    timestamp_t get_timestamp_move_begin(void);
    timestamp_t decr_timestamp_move_begin(timestamp_t);
    timestamp_t incr_timestamp_move_begin(timestamp_t);
    timestamp_t decr_timestamp_move_begin(void);
    timestamp_t incr_timestamp_move_begin(void);

    timestamp_t set_timestamp_move_end(timestamp_t);
    timestamp_t get_timestamp_move_end(void);
    timestamp_t decr_timestamp_move_end(timestamp_t);
    timestamp_t incr_timestamp_move_end(timestamp_t);
    timestamp_t decr_timestamp_move_end(void);
    timestamp_t incr_timestamp_move_end(void);

    timestamp_t set_timestamp_born(timestamp_t);
    timestamp_t get_timestamp_born(void);
    timestamp_t decr_timestamp_born(timestamp_t);
    timestamp_t incr_timestamp_born(timestamp_t);
    timestamp_t decr_timestamp_born(void);
    timestamp_t incr_timestamp_born(void);

    timestamp_t set_timestamp_hunger_tick(timestamp_t);
    timestamp_t get_timestamp_hunger_tick(void);
    timestamp_t decr_timestamp_hunger_tick(timestamp_t);
    timestamp_t incr_timestamp_hunger_tick(timestamp_t);
    timestamp_t decr_timestamp_hunger_tick(void);
    timestamp_t incr_timestamp_hunger_tick(void);

    timestamp_t set_timestamp_ai_next(timestamp_t);
    timestamp_t get_timestamp_ai_next(void);
    timestamp_t decr_timestamp_ai_next(timestamp_t);
    timestamp_t incr_timestamp_ai_next(timestamp_t);
    timestamp_t decr_timestamp_ai_next(void);
    timestamp_t incr_timestamp_ai_next(void);

    timestamp_t set_timestamp_collision(timestamp_t);
    timestamp_t get_timestamp_collision(void);
    timestamp_t decr_timestamp_collision(timestamp_t);
    timestamp_t incr_timestamp_collision(timestamp_t);
    timestamp_t decr_timestamp_collision(void);
    timestamp_t incr_timestamp_collision(void);

    uint32_t set_owner_id(uint32_t);
    uint32_t get_owner_id(void);

    uint32_t set_weapon_id_carry_anim(uint32_t);
    uint32_t get_weapon_id_carry_anim(void);

    uint32_t set_weapon_id_use_anim(uint32_t);
    uint32_t get_weapon_id_use_anim(void);

    uint32_t set_weapon_id(uint32_t);
    uint32_t get_weapon_id(void);

    Thingp owner_get();
    Thingp weapon_get();
    Thingp weapon_get_carry_anim(void);
    Thingp weapon_get_use_anim(void);
    bool collision_check_and_handle(Thingp it, fpoint future_pos, int x, int y, int dx, int dy);
    bool collision_check_and_handle(fpoint, bool *, bool *, float radius);
    bool collision_check_and_handle_at(bool *, bool *);
    bool collision_check_and_handle_at(fpoint, bool *, bool *);
    bool collision_check_and_handle_nearby(fpoint, bool *, bool *);
    bool collision_check_only(Thingp it, int x, int y, int dx, int dy);
    bool collision_check_only(Thingp it, fpoint future_pos, int x, int y, int dx, int dy);
    bool collision_check_only(void);
    bool collision_check_only(fpoint);
    bool collision_obstacle(fpoint);
    bool collision_obstacle(Thingp);
    bool ai_is_goal_for_me(point p, int priority, float *score, std::string &why);
    bool ai_is_obstacle_for_me(point p);
    void stop(void);
    bool move(fpoint future_pos);
    bool move(fpoint future_pos, uint8_t up, uint8_t down, uint8_t left, uint8_t right, uint8_t fire, uint8_t idle);
    bool follow_path(void);
    bool update_coordinates(void);
    void update_cursor(void);
    bool possible_to_attack(const Thingp it);
    bool will_avoid(const Thingp it);
    bool will_eat(const Thingp it);
    bool will_prefer(const Thingp it);
    const char *to_cstring(void);
    double get_bounce(void);
    double get_fadeup(void);
    double get_lunge(void);
    fpoint ai_get_next_hop(void);
    fpoint set_interpolated_mid_at(fpoint);
    fpoint get_interpolated_mid_at(void);
    int ai_hit_if_possible(Thingp hitter);
    int ai_hit_if_possible(Thingp hitter, int damage);
    int ai_delay_after_moving_ms(void);
    int ai_hit_actual(Thingp orig_hitter, Thingp real_hitter, Thingp hitter, int damage);
    int ai_scent_distance(void);
    int collision_attack(void);
    int collision_box(void);
    int collision_check(void);
    int collision_circle(void);
    int collision_hit_priority(void);
    int gfx_animated(void);
    int gfx_animated_can_vflip(void);
    int gfx_animated_no_dir(void);
    int gfx_bounce_on_move(void);
    int gfx_animated_can_hflip(void);
    int gfx_is_an_animation_only(void);
    int gfx_is_floor_deco(void);
    int gfx_is_wall_deco(void);
    int gfx_is_weapon_carry_anim(void);
    int gfx_is_attack_anim(void);
    int gfx_large_shadow_caster(void);
    int gfx_show_outlined(void);
    int gfx_oversized_but_sitting_on_the_ground(void);
    int gfx_small_shadow_caster(void);
    int health_hunger_pct(void);
    int hunger_clock_freq_ms(void);
    int is_hunger_insatiable(void);
    int health_initial(void);
    int health_starving_pct(void);
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
    int is_interesting(void);
    int is_key(void);
    int is_lava(void);
    int is_light_strength(void);
    int is_loggable(void);
    int is_made_of_meat(void);
    int is_meat_eater(void);
    int is_monst(void);
    int is_alive_monst(void);
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
    int is_cursor_path(void);
    int is_rrr4(void);
    int is_blood_splatter(void);
    int is_no_tile(void);
    int is_msg(void);
    int is_attack_lunge(void);
    int defence(void);
    int attack(void);
    int is_secret_door(void);
    int is_cursor_can_hover_over(void);
    int is_cursor(void);
    int is_rrr5(void);
    int gfx_dead_anim(void);
    int is_rrr6(void);
    int is_rrr7(void);
    int is_rrr8(void);
    int is_rrr9(void);
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
    std::string stats_attack_hd(void);
    std::string is_nutrition_hd(void);
    std::string to_name(void);
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
    uint8_t is_less_preferred_terrain(point p);
    uint8_t is_visible();
    void achieve_goals_in_life();
    bool collision_find_best_target(bool *, bool *);
    void animate();
    void attach(void);
    void blit(double offset_x, double offset_y, int x, int y);
    void blit_text(std::string const&, fpoint &tl, fpoint &br);
    void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_non_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br); void blit_non_player_owned_shadow(const Tpp &tp, const Tilep &tile, double x1, double y1, double x2, double y2, const fpoint &tl, const fpoint &br);
    void blit_player_owned_shadow_section(const Tpp &tp, const Tilep &tile, double x1, double y1, double x2, double y2, const fpoint &tl, const fpoint &br);
    void blit_rock_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void blit_shadow(const Tpp &tp, const Tilep &tile, const fpoint &tl, const fpoint &br);
    void blit_shadow_section(const Tpp &tp, const Tilep &tile, const fpoint &tile_tl, const fpoint &tile_br, const fpoint &tl, const fpoint &br);
    void blit_upside_down(double offset_x, double offset_y, int x, int y);
    void blit_wall_cladding(fpoint &tl, fpoint &br, const ThingTiles *tiles);
    void lunge(fpoint tt);
    void bounce(double bounce_height, double bounce_fade, timestamp_t ms, int bounce_count);
    void fadeup(double fadeup_height, double fadeup_fade, timestamp_t ms);
    void carry(Thingp w);
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
    void drop(Thingp w);
    void drop_all(void);
    void dump(std::string prefix, std::ostream &out);
    void log(std::string prefix);
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void health_boost(int v);
    void hide();
    void hooks_remove();
    void hunger_clock();
    void init(std::string name, fpoint at, fpoint jitter);
    void reinit(void);
    void kill(void);
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void log_(const char *fmt, va_list args); // compile error without
    void move_carried_items(void);
    void move_set_dir_from_delta(fpoint);
    void move_delta(fpoint);
    void move_to(fpoint to);
    void move_to_immediately(fpoint to);
    void remove_owner(void);
    void set_owner(Thingp owner);
    void sheath(void);
    void tick();
    void to_coords(fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3);
    void unwield(const char *why);
    void update_interpolated_position(void);
    void update_light(void);
    void update_pos(fpoint, bool immediately);
    void use(void);
    void visible();
    void weapon_get_use_offset(float *dx, float *dy);
    void weapon_set_carry_anim(Thingp weapon_carry_anim);
    void weapon_set_carry_anim_id(uint32_t weapon_carry_anim_id);
    void weapon_set_placement(void);
    void weapon_set_use_anim(Thingp weapon_use_anim);
    void weapon_set_use_anim_id(uint32_t weapon_use_anim_id);
    void weapon_sheath(void);
    void wield(Thingp w);
} Thing;

//std::ostream& operator<<(std::ostream &out, Bits<const Thing & > const my);
//std::istream& operator>>(std::istream &in, Bits<Thing &> my);

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

Thingp thing_new(std::string tp_name, Thingp owner);
Thingp thing_new(std::string tp_name, fpoint at, fpoint jitter = fpoint(0, 0));
bool things_overlap(Thingp t, Thingp o);
bool things_overlap(Thingp t, fpoint t_at, Thingp o);
void thing_gc(void);
void thing_map_scroll_to_player(void);
void thing_render_all(void);
void thing_render_minimap(void);
void things_tick(void);
void thing_cursor_move(void);
void thing_cursor_find_path(void);
void thing_cursor_map_follow(void);
void thing_cursor_find(uint16_t minx, uint16_t miny, uint16_t maxx, uint16_t maxy);
void thing_cursor_reset_if_needed(void);

#endif // THING_H
