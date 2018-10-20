/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file.
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
     * Previous hop where we were. We use this to interpolate the real
     * position when moving.
     */
    fpoint             last_at;

    /*
     * Very poor mans i.e. mine, physics.
     */
    fpoint             normal_velocity;
    fpoint             tangent_velocity;

    /*
     * For freefalling.
    float              fall_speed {0};
    float              jump_speed {0};
    float              momentum {0};
    float              rot {0};
     */

    /*
     * How close for collision detection.
     */
    float              collision_radius {0};

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
    uint32_t           last_move_ms {};
    uint32_t           end_move_ms {};
    uint32_t           next_frame_ms {};

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
    uint32_t           weapon_swing_anim_thing_id {0};

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
    unsigned int       is_dead:1;
    unsigned int       is_hidden:1;
    unsigned int       is_sleeping:1;
    unsigned int       is_moving:1;
    unsigned int       has_ever_moved:1;
    unsigned int       is_open:1;
    
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

    void pop();
    void animate();
    void dead(Thingp killer, const char *fmt, ...) __attribute__ ((format (printf, 3, 4)));
    void destroyed(void);
    void move_delta(fpoint);
    void move_to(fpoint to);
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
    void set_is_dead(uint8_t val);
    void remove_hooks();
    Thingp get_owner();
    void set_owner(Thingp owner);
    uint8_t is_visible();
    void visible();
    void hide();

    /*
     * thing_weapon.c
     */
    Tpp get_weapon();
    void wield_next_weapon();
    void unwield(const char *why);
    void sheath(void);
    void swing(void);
    void wield(Tpp tp);
    void weapon_sheath(void);
    void get_weapon_swing_offset(double *dx, double *dy);
    Thingp get_weapon_carry_anim(void);
    Thingp get_weapon_swing_anim(void);
    void set_weapon_placement(void);
    void set_weapon_carry_anim_id(uint32_t weapon_carry_anim_id);
    void set_weapon_carry_anim(Thingp weapon_carry_anim);
    void set_weapon_swing_anim_id(uint32_t weapon_swing_anim_id);
    void set_weapon_swing_anim(Thingp weapon_swing_anim);

    void log_(const char *fmt, va_list args); // compile error without
    void log(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void die_(const char *fmt, va_list args); // compile error without
    void die(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void con_(const char *fmt, va_list args); // compile error without
    void con(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void err_(const char *fmt, va_list args); // compile error without
    void err(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
    void dbg(const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));
};

extern Thingp thing_new(std::string tp_name, fpoint at);
extern Thingp thing_find(uint32_t name);
extern void thing_render_all(void);
extern void thing_map_scroll_to_player(void);
void map_light_init(void);
void map_light_add(Tpp tp, fpoint at, double strength, color c, bool hiqual);
void map_light_calculate_visible(int level);
void map_light_display(int fbo);
void map_light_ray_effect(const int light_index, const int light_level);

#endif /* THING_H */
