/*
 * Copyright(C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

#ifndef _MY_WID_H_
#define _MY_WID_H_

typedef std::shared_ptr< class wid > widp;

#include <SDL.h>
#include "my_sdl.h"
#include "my_enum.h"
#include "my_size.h"
#include "my_wid_tiles.h"

#ifdef ENABLE_WID_DEBUG
void WID_LOG(widp, const char *fmt, ...) \
                     __attribute__ ((format (printf, 2, 3)));

void WID_DBG(widp, const char *fmt, ...) \
                     __attribute__ ((format (printf, 2, 3)));
#else
#define WID_DBG(...)
#define WID_LOG(...)
#endif

typedef enum {
    WID_COLOR_BG,
    WID_COLOR_TEXT,
    WID_COLOR_MAX,
} wid_color;

typedef enum {
    WID_MODE_NORMAL,
    WID_MODE_OVER,
    WID_MODE_FOCUS,
    WID_MODE_ACTIVE,
    WID_MODE_LAST,
} wid_mode;

#define WID_MODE_FIRST WID_MODE_NORMAL

color wid_get_color(widp, wid_color which);
color wid_get_mode_color(widp, wid_color which);
int32_t wid_get_br_x(widp);
int32_t wid_get_br_y(widp);
int32_t wid_get_cx(widp);
int32_t wid_get_cy(widp);
int32_t wid_get_height(widp);
int32_t wid_get_tl_x(widp);
int32_t wid_get_tl_y(widp);
int32_t wid_get_width(widp);
extern int wid_mouse_visible;
fsize wid_get_tex_br(widp);
fsize wid_get_tex_tl(widp);
std::string wid_get_name(widp);
std::wstring wid_get_text(widp);
std::wstring wid_get_text_with_cursor(widp);
std::wstring wid_get_tooltip(widp);
std::string wid_logname(widp);
std::string wid_name(widp);
texp wid_get_tex(widp, fsize *size);
tilep wid_get_tile(widp);
tilep wid_get_tile2(widp);
tpp wid_get_thing_template(widp);
typedef uint8_t(*on_joy_button_t)(widp, int32_t x, int32_t y);
typedef uint8_t(*on_key_down_t)(widp, const struct SDL_KEYSYM *);
typedef uint8_t(*on_key_up_t)(widp, const struct SDL_KEYSYM *);
typedef uint8_t(*on_m_down_t)(widp, int32_t x, int32_t y, uint32_t button);
typedef uint8_t(*on_m_motion_t)(widp, int32_t x, int32_t y, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
typedef uint8_t(*on_m_up_t)(widp, int32_t x, int32_t y, uint32_t button);
typedef void(*on_destroy_b_t)(widp);
typedef void(*on_destroy_t)(widp);
typedef void(*on_m_focus_b_t)(widp);
typedef void(*on_m_focus_e_t)(widp);
typedef void(*on_m_over_b_t)(widp, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
typedef void(*on_m_over_e_t)(widp);
typedef void(*on_tick_t)(widp);
uint32_t wid_get_cursor(widp);
uint32_t wid_get_gllist(widp);
uint32_t wid_get_mode_gllist(widp);
uint8_t wid_get_do_not_lower(widp);
uint8_t wid_get_do_not_raise(widp);
uint8_t wid_get_focusable(widp);
uint8_t wid_get_mode_top(widp);
uint8_t wid_get_movable(widp);
uint8_t wid_get_movable_bounded(widp);
uint8_t wid_get_movable_horiz(widp);
uint8_t wid_get_movable_no_user_scroll(widp);
uint8_t wid_get_movable_vert(widp);
uint8_t wid_get_received_input(widp);
uint8_t wid_get_show_cursor(widp);
uint8_t wid_get_text_bot(widp);
uint8_t wid_get_text_centerx(widp);
uint8_t wid_get_text_centery(widp);
uint8_t wid_get_text_lhs(widp);
uint8_t wid_get_text_pos(widp, int32_t *x, int32_t *y);
uint8_t wid_get_text_rhs(widp);
uint8_t wid_get_text_top(widp);
uint8_t wid_ignore_being_destroyed(widp);
uint8_t wid_ignore_events(widp);
uint8_t wid_ignore_for_focus(widp);
uint8_t wid_init(void);
uint8_t wid_is_always_hidden(widp w);
uint8_t wid_is_hidden(widp w);
uint8_t wid_receive_input(widp, const SDL_KEYSYM *key);
uint8_t wid_this_hidden(widp w);
void *wid_get_context(widp);
void wid_always_hidden(widp, uint8_t value);
void wid_animate(widp);
void wid_destroy(widp *);
void wid_destroy_in(widp w, uint32_t ms);
void wid_destroy_nodelay(widp *);
void wid_destroy_ptr_in(widp *w, uint32_t ms);
void wid_display_all(void);
void wid_fake_joy_button(int32_t x, int32_t y);
void wid_fini(void);
void wid_focus_lock(widp);
void wid_gc_all(void);
void wid_gc_all_force(void);
void wid_get_abs(widp w, int32_t *x, int32_t *y);
void wid_get_abs_coords(widp w, int32_t *tlx, int32_t *tly, int32_t *brx, int32_t *bry);
void wid_get_abs_coords_unclipped(widp w, int32_t *tlx, int32_t *tly, int32_t *brx, int32_t *bry);
void wid_get_children_size(widp, int32_t *width, int32_t *height);
void wid_get_move_interpolated_progress(widp w, double *dx, double *dy);
void wid_get_mxy(widp w, int32_t *x, int32_t *y);
void wid_get_offset(widp, point *offset);
void wid_get_pct(widp w, double *x, double *y);
void wid_get_tl_br(widp, point *tl, point *br);
void wid_get_tl_x_tl_y_br_x_br_y(widp w, int32_t *tl_x, int32_t *tl_y, int32_t *br_x, int32_t *br_y);
void wid_hide(widp);
void wid_joy_button(int32_t x, int32_t y);
void wid_key_down(const struct SDL_KEYSYM *, int32_t x, int32_t y);
void wid_key_up(const struct SDL_KEYSYM *, int32_t x, int32_t y);
void wid_lower(widp);
void wid_mouse_down(uint32_t button, int32_t x, int32_t y);
void wid_mouse_hide(int);
void wid_mouse_motion(int32_t x, int32_t y, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
void wid_mouse_move(widp w);
void wid_mouse_up(uint32_t button, int32_t x, int32_t y);
void wid_mouse_warp(widp w);
void wid_move_all(void);
void wid_move_delta(widp, int32_t dx, int32_t dy);
void wid_move_delta_in(widp w, int32_t dx, int32_t dy, uint32_t ms);
void wid_move_delta_pct(widp, double dx, double dy);
void wid_move_delta_pct_in(widp, double dx, double dy, uint32_t delay);
void wid_move_end(widp);
void wid_move_to_abs(widp, int32_t dx, int32_t dy);
void wid_move_to_abs_centered(widp, int32_t dx, int32_t dy);
void wid_move_to_abs_centered_in(widp, int32_t dx, int32_t dy, uint32_t delay);
void wid_move_to_abs_in(widp, int32_t dx, int32_t dy, uint32_t delay);
void wid_move_to_abs_poffset_in(widp w, int32_t x, int32_t y, uint32_t delay);
void wid_move_to_bottom(widp);
void wid_move_to_centered_in(widp, int32_t dx, int32_t dy, uint32_t delay);
void wid_move_to_horiz_pct(widp w, double pct);
void wid_move_to_horiz_pct_in(widp w, double pct, double in);
void wid_move_to_horiz_vert_pct_in(widp w, double x, double y, double in);
void wid_move_to_left(widp);
void wid_move_to_pct(widp, double dx, double dy);
void wid_move_to_pct_centered(widp, double dx, double dy);
void wid_move_to_pct_centered_in(widp, double dx, double dy, uint32_t delay);
void wid_move_to_pct_in(widp, double dx, double dy, uint32_t delay);
void wid_move_to_right(widp);
void wid_move_to_top(widp);
void wid_move_to_vert_pct(widp w, double pct);
void wid_move_to_vert_pct_in(widp w, double pct, double in);
void wid_raise(widp);
void wid_scroll_text(widp);
void wid_scroll_with_input(widp, std::wstring str);
void wid_set_active(widp);
void wid_set_animate(widp, uint8_t);
void wid_set_color(widp, wid_color col, color val);
void wid_set_context(widp w, void *context);
void wid_set_cursor(widp, uint32_t val);
void wid_set_debug(widp, uint8_t);
void wid_set_do_not_lower(widp, uint8_t val);
void wid_set_do_not_raise(widp, uint8_t val);
void wid_set_shape_square(widp);
void wid_set_shape_none(widp);
void wid_set_shape_box(widp);
void wid_set_focus(widp);
void wid_set_focusable(widp, uint8_t val);
void wid_set_ignore_events(widp, uint8_t);
void wid_set_mode(widp, wid_mode mode);
void wid_set_movable(widp, uint8_t val);
void wid_set_movable_bounded(widp, uint8_t val);
void wid_set_movable_horiz(widp, uint8_t val);
void wid_set_movable_no_user_scroll(widp, uint8_t val);
void wid_set_movable_vert(widp, uint8_t val);
void wid_set_name(widp, std::string);
void wid_set_offset(widp, point offset);
void wid_set_on_destroy(widp, on_destroy_t fn);
void wid_set_on_destroy_b(widp, on_destroy_b_t fn);
void wid_set_on_joy_button(widp, on_joy_button_t fn);
void wid_set_on_key_down(widp, on_key_down_t fn);
void wid_set_on_key_up(widp, on_key_up_t fn);
void wid_set_on_m_down(widp, on_m_down_t fn);
void wid_set_on_m_focus_b(widp, on_m_focus_b_t fn);
void wid_set_on_m_focus_e(widp, on_m_focus_e_t fn);
void wid_set_on_m_motion(widp, on_m_motion_t fn);
void wid_set_on_m_over_b(widp, on_m_over_b_t fn);
void wid_set_on_m_over_e(widp, on_m_over_e_t fn);
void wid_set_on_m_up(widp, on_m_up_t fn);
void wid_set_on_tick(widp, on_tick_t fn);
void wid_set_pos(widp, point tl, point br);
void wid_set_pos_no_relative_offset(widp w, point tl, point br);
void wid_set_pos_pct(widp, fpoint tl, fpoint br);
void wid_set_prev(widp w, widp);
void wid_set_received_input(widp, uint8_t val);
void wid_set_show_cursor(widp, uint8_t val);
void wid_set_tex(widp, std::string file, std::string name);
void wid_set_tex_br(widp, fsize val);
void wid_set_tex_sz(widp, fsize uv);
void wid_set_tex_tl(widp, fsize val);
void wid_set_text(widp, std::wstring);
void wid_set_text_bot(widp, uint8_t val);
void wid_set_text_centerx(widp, uint8_t val);
void wid_set_text_centery(widp, uint8_t val);
void wid_set_text_lhs(widp, uint8_t val);
void wid_set_text_pos(widp, uint8_t val, int32_t x, int32_t y);
void wid_set_text_rhs(widp, uint8_t val);
void wid_set_text_top(widp, uint8_t val);
void wid_set_thing_template(widp, tpp);
void wid_set_tilename(widp, std::string name);
void wid_set_tooltip(widp, std::wstring string);
void wid_set_tooltip2(widp, std::wstring string);
void wid_set_top(widp, uint8_t val);
void wid_setx_tl_br_pct(widp, fpoint tl, fpoint br);
void wid_sety_tl_br_pct(widp, fpoint tl, fpoint br);
void wid_this_hide(widp, uint32_t delay);
void wid_this_visible(widp);
void wid_tick_all(void);
void wid_toggle_hidden(widp);
void wid_tooltip2_set(std::wstring text);
void wid_tooltip_set(std::wstring text);
void wid_update(widp);
void wid_update_mouse(void);
void wid_visible(widp);
wid_mode wid_get_mode(widp);
widp wid_find(widp, std::string name);
widp wid_get_current_focus(void);
widp wid_get_focus(widp);
widp wid_get_next(widp);
widp wid_get_parent(widp);
widp wid_get_prev(widp);
widp wid_get_scrollbar_horiz(widp);
widp wid_get_scrollbar_vert(widp);
widp wid_get_top_parent(widp);
widp wid_new_container(widp, std::string name);
widp wid_new_horiz_scroll_bar(widp parent, std::string name, widp scrollbar_owner);
widp wid_new_plain(widp, std::string name);
widp wid_new_square_button(widp parent, std::string name);
widp wid_new_square_window(std::string name);
widp wid_new_tooltip(std::string tooltip);
widp wid_new_vert_scroll_bar(widp parent, std::string name, widp scrollbar_owner);
widp wid_new_window(std::string name);
void wid_dump(widp w, int depth);

/*
 * History for all text widgets.
 */
#define HISTORY_MAX 16
extern std::wstring history[HISTORY_MAX];
extern uint32_t history_at;
extern uint32_t history_walk;

typedef struct {
    /*
     * Colors
     */
    color colors[WID_COLOR_MAX];
    uint8_t color_set [WID_COLOR_MAX];
} wid_cfg;

class tree_wid_key {
public:
    tree_wid_key (void)
    {
    }

    tree_wid_key (int priority, point tl, point br, uint64_t key) :
                  priority(priority), tl(tl), br(br), key(key)
    {
    }

    ~tree_wid_key (void)
    {
    }

    int priority {};

    /*
     * The real position on the screen initially.
     */
    point tl {};
    point br {};

    /*
     * Unique wid ID.
     */
    uint64_t key {};
};

struct tree_wid_key_cmp : public std::binary_function<class tree_wid_key, class tree_wid_key, bool>
{
    bool operator()(const tree_wid_key& lhs, const tree_wid_key& rhs) const
    {
        if (lhs.priority < rhs.priority) {
            return (true);
        } else if (lhs.priority > rhs.priority) {
            return (false);
        }

        if (lhs.br.y < rhs.br.y) {
            return (true);
        } else if (lhs.br.y > rhs.br.y) {
            return (false);
        }

        if (lhs.key < rhs.key) {
            return (true);
        } else if (lhs.key > rhs.key) {
            return (false);
        }

        return (false);
    }
};

class wid_key_type {
public:
    wid_key_type (void)
    {
    }

    wid_key_type (uint64_t val) : val(val)
    {
    }

    bool operator <(const wid_key_type& rhs) const
    {
        return (val < rhs.val);
    }

    uint64_t val {};
};

typedef std::map< tree_wid_key, widp, tree_wid_key_cmp > wid_key_map_location;
typedef std::map< wid_key_type, widp > wid_key_map_int;

widp wid_unsorted_find(wid_key_type key);
wid_key_type wid_unsorted_get_key(widp w);

typedef struct wid_move_ {
    point moving_end;
    uint32_t timestamp_moving_end;
} wid_move_t;

class wid {

public:
    wid (void)
    {
        newptr(this, "wid");
    }

    ~wid (void)
    {
        oldptr(this);
    }

    wid_key_type tree_global_key {};

    /*
     * Sorted for display order.
     */
    tree_wid_key key                                    {};
    wid_key_type tree2_key                              {};
    wid_key_type tree3_key                              {};
    wid_key_type tree4_key                              {};
    wid_key_type tree5_key                              {};

    wid_key_map_location *in_tree_root                  {};
    wid_key_map_int *in_tree2_unsorted_root             {};
    wid_key_map_int *in_tree3_moving_wids               {};
    wid_key_map_int *in_tree4_wids_being_destroyed      {};
    wid_key_map_int *in_tree5_ticking_wids              {};
    wid_key_map_int *in_tree_global_unsorted_root       {};

    /*
     * Sorted for display onto the screen.
     */
    wid_key_map_location children_display_sorted {};

    /*
     * No particular sort order.
     */
    wid_key_map_int tree2_children_unsorted {};

    /*
     * A tree for moving things
     */
    wid_key_map_int tree3_moving_wids {};

    /*
     * A tree for things being destroyed.
     */
    wid_key_map_int tree4_wids_being_destroyed {};

    /*
     * A tree for ticking things
     */
    wid_key_map_int tree5_ticking_wids {};

    /*
     * Tiles widget
     */
    wid_tilesp wid_tiles {};

    uint8_t hidden                      {};
    uint8_t debug                       {};
    uint8_t tex_tl_set                  {};
    uint8_t tex_br_set                  {};
    uint8_t always_hidden               {};
    uint8_t visible                     {};
    uint8_t received_input              {};
    uint8_t movable                     {};
    uint8_t movable_set                 {};
    uint8_t movable_horiz               {};
    uint8_t movable_horiz_set           {};
    uint8_t movable_vert                {};
    uint8_t movable_vert_set            {};
    uint8_t movable_bounded             {};
    uint8_t movable_bounded_set         {};
    uint8_t movable_no_user_scroll      {};
    uint8_t movable_no_user_scroll_set  {};
    uint8_t ignore_events               {};
    uint8_t ignore_for_mouse_down       {};
    uint8_t first_update                {};
    uint8_t show_cursor                 {};
    uint8_t text_pos_set                {};
    uint8_t text_lhs                    {};
    uint8_t text_rhs                    {};
    uint8_t text_centerx                {};
    uint8_t text_top                    {};
    uint8_t text_bot                    {};
    uint8_t text_centery                {};
    uint8_t being_destroyed             {};
    uint8_t do_not_raise                {};
    uint8_t do_not_lower                {};
    uint8_t can_be_attached_now         {};
    uint8_t disable_scissors            {};
    uint8_t animate                     {};
    uint8_t square                      {};
    uint8_t box                         {};

    /*
     * Optionally set to the previous wid in a list
     */
    widp prev {};
    widp next {};
    widp scrollbar_horiz {};
    widp scrollbar_vert {};
    widp scrollbar_owner {};

    tpp tp {};

    /*
     * The real position after scrollbar adjustments.
     */
    point abs_tl {};
    point abs_br {};

    texp tex {};
    tilep tile {};
    tilep first_tile {};
    thing_tilep current_tile {};

    fsize texuv {};

    fsize tex_tl {};
    fsize tex_br {};

    /*
     * WID_MODE_NORMAL ...
     */
    wid_mode mode {};

    /*
     * Offset of child widgets in the parent window.
     */
    point offset {};

    /*
     * Config layers:
     */
    wid_cfg cfg[WID_MODE_LAST] {};

    /*
     * Client context
     */
    void *context {};

    /*
     * Text placement.
     */
    point text_pos {};

    uint32_t destroy_when {};
    uint32_t timestamp_created {};
    uint32_t timestamp_last_mode_change {};

    /*
     * When to change frame for animation.
     */
    uint32_t timestamp_change_to_next_frame {};

    widp *destroy_ptr {};

    /*
     * Queue of wid move requests.
     */
#define WID_MAX_MOVE_QUEUE 4
    wid_move_t move[WID_MAX_MOVE_QUEUE] {};
    point moving_start {};
    point moving_end {};
    uint32_t timestamp_moving_begin {};
    uint32_t timestamp_moving_end {};
    uint8_t moving {};

    /*
     * Text input
     */
    uint16_t cursor {};

    /*
     * Order of this wid amongst other focusable widgets.
     */
    uint8_t focus_order {};

    /*
     * Who had it last ? Used when raising this wid again.
     */
    uint8_t focus_last {};

    /*
     * The wids children
     */
    widp parent {};

    /*
     * Widget internal name.
     */
    std::string name {};

    /*
     * For debugging.
     */
    std::string logname {};

    /*
     * Text that appears on the wid.
     */
    std::wstring text {};

    /*
     * Text that appears as a tooltip.
     */
    std::wstring tooltip {};
    std::wstring tooltip2 {};

    /*
     * Action handlers
     */
    on_key_down_t on_key_down         {};
    on_key_up_t on_key_up             {};
    on_joy_button_t on_joy_button     {};
    on_m_down_t on_m_down             {};
    on_m_up_t on_m_up                 {};
    on_m_motion_t on_m_motion         {};
    on_m_focus_b_t on_m_focus_b       {};
    on_m_focus_e_t on_m_focus_e       {};
    on_m_over_b_t on_m_over_b         {};
    on_m_over_e_t on_m_over_e         {};
    on_destroy_t on_destroy           {};
    on_destroy_b_t on_destroy_b       {};
    on_tick_t on_tick                 {};
};

static inline uint8_t wid_is_moving (widp w)
{
    verify(w.get());

    if (w->moving) {
        return (true);
    }

    return (false);
}

extern widp wid_mouse_template;

extern const int32_t wid_destroy_delay_ms;
extern std::wstring wid_tooltip_string;
extern std::wstring wid_tooltip2_string;

static inline
void wid_set_tile (widp w, tilep tile)
{
    verify(w.get());

    w->tile = tile;
    if (!w->first_tile) {
        w->first_tile = tile;
    }
}
#endif
