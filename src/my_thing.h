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
#include "my_time_util.h"
#include "my_light.h"

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
        archive(cereal::make_nvp("id",               id),
                cereal::make_nvp("at",               at),
                cereal::make_nvp("last_at",          last_at));
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
    fpoint             at;

    /*
     * On screen coordinates, taking account for size of the current frame.
     */
    fpoint             tl;
    fpoint             br;

    /*
     * Previous hop where we were. We use this to interpolate the real
     * position when moving.
     */
    fpoint             last_at;

    /*
     * Pointer to common settings for this thing.
     */
    Tpp                tp {nullptr};

    /*
     * Does this thing have a light source?
     */
    Lightp             light {nullptr};

    /*
     * Used for animating the steps.
     */
    uint32_t           flip_start_ms {};
    uint32_t           begin_move_ms {};
    uint32_t           end_move_ms {};
    uint32_t           next_frame_ms {};

    /*
     * Timestamps
     */
    uint32_t           timestamp_born {};
    uint32_t           timestamp_last_i_was_hit {};
    uint32_t           timestamp_last_attacked {};
    uint32_t           timestamp_move_start {};
    uint32_t           timestamp_move_end {};

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
    uint16_t           gold {0};
    uint16_t           hp {0};

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
     * Update thing_new when adding new bitfields.
     */
    unsigned int       is_dead:1;          /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_bloodied:1;      /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_player:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_hidden:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_sleeping:1;      /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_moving:1;        /* until -std=c++2a remember to update thing.cpp */
    unsigned int       has_ever_moved:1;   /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_open:1;          /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_bouncing:1;      /* until -std=c++2a remember to update thing.cpp */
    unsigned int       is_attached:1;      /* until -std=c++2a remember to update thing.cpp */
    
    std::string logname(void);
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
    void update(void);
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
    void tick();

    /*
     * thing_display.cpp
     */
    fpoint last_attached;
    void attach(void);
    void detach(void);
    void blit_wall_cladding(fpoint &tl, fpoint &br);
    void blit_shadow(const Tpp &tp, const Tilep &tile, 
                     const fpoint &tl, const fpoint &br);
    void blit(double offset_x, double offset_y, int x, int y, int z);

    /*
     * thing_hit.cpp
     */
    int hit_actual(Thingp orig_hitter, Thingp real_hitter, Thingp hitter, 
                   int damage);
    int hit_possible(Thingp hitter, int damage);
    int hit_possible(Thingp hitter);

    /*
     * thing_move.cpp
     */
    void update_coordinates(void);
    bool move(fpoint future_pos,
              const uint8_t up,
              const uint8_t down,
              const uint8_t left,
              const uint8_t right,
              const uint8_t fire);
    void bounce(double bounce_height,
                double bounce_fade,
                uint32_t ms,
                uint32_t bounce_count);
    double get_bounce(void);

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
    void to_coords(fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3);

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

extern Thingp thing_new(std::string tp_name, fpoint at);
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
void thing_update_all_coordinates(void);

/*
 * thing_collision.cpp
 */
bool things_overlap(Thingp t, Thingp o);
bool things_overlap(Thingp t, fpoint t_at, Thingp o);

/*
 * thing_tick.cpp
 */
void thing_tick_all(void);

#endif /* THING_H */
