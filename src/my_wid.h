//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_WID_H_
#define _MY_WID_H_

#include "my_main.h"
#include "my_point.h"
#include "my_size.h"
#include "my_ascii.h"
typedef class Wid* Widp;
#include "my_sdl.h"
#include "my_wid_tiles.h"

#ifdef ENABLE_UI_DEBUG
void WID_LOG(Widp, const char *fmt, ...) \
                     __attribute__ ((format (printf, 2, 3)));

void WID_DBG(Widp, const char *fmt, ...) \
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

Widp wid_find(Widp, std::string name);
Widp wid_get_current_focus(void);
Widp wid_get_focus(Widp);
Widp wid_get_head(Widp);
Widp wid_get_next(Widp);
Widp wid_get_parent(Widp);
Widp wid_get_prev(Widp);
Widp wid_get_scrollbar_horiz(Widp);
Widp wid_get_scrollbar_vert(Widp);
Widp wid_get_tail(Widp);
Widp wid_get_top_parent(Widp);
Widp wid_new_container(Widp, std::string name);
Widp wid_new_horiz_scroll_bar(Widp parent, std::string name, Widp scrollbar_owner);
Widp wid_new_square_button(Widp parent, std::string name);
Widp wid_new_square_window(std::string name);
Widp wid_new_vert_scroll_bar(Widp parent, std::string name, Widp scrollbar_owner);
Widp wid_new_window(std::string name);
char wid_event_to_char(const struct SDL_KEYSYM *evt);
color wid_get_color(Widp, wid_color which);
int32_t wid_get_height(Widp);
int32_t wid_get_tl_x(Widp);
int32_t wid_get_tl_y(Widp);
int32_t wid_get_width(Widp);
std::string to_string(Widp);
std::string wid_get_name(Widp);
std::string wid_name(Widp);
std::wstring wid_get_text(Widp);
std::wstring wid_get_tooltip(Widp);
typedef uint8_t(*on_joy_button_t)(Widp, int32_t x, int32_t y);
typedef uint8_t(*on_key_down_t)(Widp, const struct SDL_KEYSYM *);
typedef uint8_t(*on_key_up_t)(Widp, const struct SDL_KEYSYM *);
typedef uint8_t(*on_mouse_down_t)(Widp, int32_t x, int32_t y, uint32_t button);
typedef uint8_t(*on_mouse_motion_t)(Widp, int32_t x, int32_t y, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
typedef uint8_t(*on_mouse_up_t)(Widp, int32_t x, int32_t y, uint32_t button);
typedef void(*on_destroy_begin_t)(Widp);
typedef void(*on_destroy_t)(Widp);
typedef void(*on_mouse_focus_begin_t)(Widp);
typedef void(*on_mouse_focus_end_t)(Widp);
typedef void(*on_mouse_over_b_t)(Widp, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
typedef void(*on_mouse_over_e_t)(Widp);
typedef void(*on_tick_t)(Widp);
uint32_t wid_get_cursor(Widp);
uint32_t wid_get_gllist(Widp);
uint32_t wid_get_mode_gllist(Widp);
uint8_t wid_get_do_not_lower(Widp);
uint8_t wid_get_do_not_raise(Widp);
uint8_t wid_get_focusable(Widp);
uint8_t wid_get_mode_top(Widp);
uint8_t wid_get_movable(Widp);
uint8_t wid_get_movable_bounded(Widp);
uint8_t wid_get_movable_horiz(Widp);
uint8_t wid_get_movable_no_user_scroll(Widp);
uint8_t wid_get_movable_vert(Widp);
uint8_t wid_get_received_input(Widp);
uint8_t wid_get_show_cursor(Widp);
uint8_t wid_get_text_bot(Widp);
uint8_t wid_get_text_centerx(Widp);
uint8_t wid_get_text_centery(Widp);
uint8_t wid_get_text_lhs(Widp);
uint8_t wid_get_text_pos(Widp, int32_t *x, int32_t *y);
uint8_t wid_get_text_rhs(Widp);
uint8_t wid_get_text_top(Widp);
uint8_t wid_ignore_being_destroyed(Widp);
uint8_t wid_ignore_events(Widp);
uint8_t wid_ignore_for_focus(Widp);
uint8_t wid_init(void);
uint8_t wid_is_always_hidden(Widp w);
uint8_t wid_is_hidden(Widp w);
uint8_t wid_receive_input(Widp, const SDL_KEYSYM *key);
int wid_get_int_context(Widp);
void wid_always_hidden(Widp, uint8_t value);
void wid_destroy(Widp *);
void wid_destroy_in(Widp w, uint32_t ms);
void wid_destroy_nodelay(Widp *);
void wid_destroy_ptr_in(Widp *w, uint32_t ms);
void wid_display_all(void);
void wid_dump(Widp w, int depth);
void wid_fake_joy_button(int32_t x, int32_t y);
void wid_fini(void);
void wid_focus_lock(Widp);
void wid_gc_all(void);
void wid_gc_all_force(void);
void wid_get_abs(Widp w, int32_t *x, int32_t *y);
void wid_get_abs_coords(Widp w, int32_t *tlx, int32_t *tly, int32_t *brx, int32_t *bry);
void wid_get_abs_coords_unclipped(Widp w, int32_t *tlx, int32_t *tly, int32_t *brx, int32_t *bry);
void wid_get_children_size(Widp, int32_t *width, int32_t *height);
void wid_get_pct(Widp w, double *x, double *y);
void wid_get_tl_x_tl_y_br_x_br_y(Widp w, int32_t *tl_x, int32_t *tl_y, int32_t *br_x, int32_t *br_y);
void wid_hide(Widp);
void wid_joy_button(int32_t x, int32_t y);
void wid_key_down(const struct SDL_KEYSYM *, int32_t x, int32_t y);
void wid_key_up(const struct SDL_KEYSYM *, int32_t x, int32_t y);
void wid_lower(Widp);
void wid_mouse_down(uint32_t button, int32_t x, int32_t y);
void wid_mouse_hide(int);
void wid_mouse_motion(int32_t x, int32_t y, int32_t relx, int32_t rely, int32_t wheelx, int32_t wheely);
void wid_mouse_move(Widp w);
void wid_mouse_up(uint32_t button, int32_t x, int32_t y);
void wid_mouse_warp(Widp w);
void wid_move_all(void);
void wid_move_delta(Widp, int32_t dx, int32_t dy);
void wid_move_delta_in(Widp w, int32_t dx, int32_t dy, uint32_t ms);
void wid_move_delta_pct(Widp, double dx, double dy);
void wid_move_end(Widp);
void wid_move_to_abs(Widp, int32_t dx, int32_t dy);
void wid_move_to_abs_centered(Widp, int32_t dx, int32_t dy);
void wid_move_to_abs_centered_in(Widp, int32_t dx, int32_t dy, uint32_t delay);
void wid_move_to_abs_in(Widp, int32_t dx, int32_t dy, uint32_t delay);
void wid_move_to_bottom(Widp);
void wid_move_to_centered_in(Widp, int32_t dx, int32_t dy, uint32_t delay);
void wid_move_to_horiz_pct(Widp w, double pct);
void wid_move_to_horiz_pct_in(Widp w, double pct, double in);
void wid_move_to_horiz_vert_pct_in(Widp w, double x, double y, double in);
void wid_move_to_left(Widp);
void wid_move_to_pct(Widp, double dx, double dy);
void wid_move_to_pct_centered(Widp, double dx, double dy);
void wid_move_to_pct_centered_in(Widp, double dx, double dy, uint32_t delay);
void wid_move_to_pct_in(Widp, double dx, double dy, uint32_t delay);
void wid_move_to_right(Widp);
void wid_move_to_top(Widp);
void wid_move_to_vert_pct(Widp w, double pct);
void wid_move_to_vert_pct_in(Widp w, double pct, double in);
void wid_raise(Widp);
void wid_scroll_text(Widp);
void wid_scroll_with_input(Widp, std::wstring str);
void wid_set_active(Widp);
void wid_set_bg_tilename(Widp, std::string name);
void wid_set_color(Widp, wid_color col, color val);
void wid_set_int_context(Widp w, int);
void wid_set_cursor(Widp, uint32_t val);
void wid_set_debug(Widp, uint8_t);
void wid_set_do_not_lower(Widp, uint8_t val);
void wid_set_do_not_raise(Widp, uint8_t val);
void wid_set_fg_tilename(Widp, std::string name);
void wid_set_focus(Widp);
void wid_set_focusable(Widp, uint8_t val);
void wid_set_ignore_events(Widp, uint8_t);
void wid_set_mode(Widp, wid_mode mode);
void wid_set_movable(Widp, uint8_t val);
void wid_set_movable_bounded(Widp, uint8_t val);
void wid_set_movable_horiz(Widp, uint8_t val);
void wid_set_movable_no_user_scroll(Widp, uint8_t val);
void wid_set_movable_vert(Widp, uint8_t val);
void wid_set_name(Widp, std::string);
void wid_set_on_destroy(Widp, on_destroy_t fn);
void wid_set_on_destroy_begin(Widp, on_destroy_begin_t fn);
void wid_set_on_joy_button(Widp, on_joy_button_t fn);
void wid_set_on_key_down(Widp, on_key_down_t fn);
void wid_set_on_key_up(Widp, on_key_up_t fn);
void wid_set_on_mouse_down(Widp, on_mouse_down_t fn);
void wid_set_on_mouse_focus_begin(Widp, on_mouse_focus_begin_t fn);
void wid_set_on_mouse_focus_end(Widp, on_mouse_focus_end_t fn);
void wid_set_on_mouse_motion(Widp, on_mouse_motion_t fn);
void wid_set_on_mouse_over_b(Widp, on_mouse_over_b_t fn);
void wid_set_on_mouse_over_e(Widp, on_mouse_over_e_t fn);
void wid_set_on_mouse_up(Widp, on_mouse_up_t fn);
void wid_set_on_tick(Widp, on_tick_t fn);
void wid_set_pos(Widp, point tl, point br);
void wid_set_pos_pct(Widp, fpoint tl, fpoint br);
void wid_set_prev(Widp w, Widp);
void wid_set_received_input(Widp, uint8_t val);
void wid_set_shape_none(Widp);
void wid_set_shape_square(Widp);
void wid_set_show_cursor(Widp, uint8_t val);
void wid_set_tex_br(Widp, fsize val);
void wid_set_tex_tl(Widp, fsize val);
void wid_set_text(Widp, int);
void wid_set_text(Widp, std::string);
void wid_set_text(Widp, std::wstring);
void wid_set_text_bot(Widp, uint8_t val);
void wid_set_text_centerx(Widp, uint8_t val);
void wid_set_text_centery(Widp, uint8_t val);
void wid_set_text_lhs(Widp, uint8_t val);
void wid_set_text_pos(Widp, uint8_t val, int32_t x, int32_t y);
void wid_set_text_rhs(Widp, uint8_t val);
void wid_set_text_top(Widp, uint8_t val);
void wid_set_top(Widp, uint8_t val);
void wid_this_visible(Widp);
void wid_tick_all(void);
void wid_toggle_hidden(Widp);
void wid_unset_focus();
void wid_unset_focus_lock(void);
void wid_update(Widp);
void wid_update_mouse(void);
void wid_visible(Widp);
wid_mode wid_get_mode(Widp);

typedef struct {
    //
    // Colors
    //
    std::array<color, WID_COLOR_MAX> colors;
    std::array<uint8_t, WID_COLOR_MAX> color_set;
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

    //
    // The real position on the screen initially.
    //
    point tl {};
    point br {};

    //
    // Unique wid ID.
    //
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

class WidKeyType {
public:
    WidKeyType (void)
    {
    }

    WidKeyType (uint64_t val) : val(val)
    {
    }

    bool operator <(const WidKeyType& rhs) const
    {
        return (val < rhs.val);
    }

    uint64_t val {};
};

typedef std::map< tree_wid_key, Widp, tree_wid_key_cmp > wid_key_map_location;
typedef std::map< WidKeyType, Widp > wid_key_map_int;

WidKeyType wid_unsorted_get_key(Widp w);

typedef struct wid_move_ {
    int moving_endx;
    int moving_endy;
    timestamp_t timestamp_moving_end;
} wid_move_t;

class Wid {
public:
    Wid (void)
    {
        newptr(this, "wid");
    }

    ~Wid (void)
    {
        oldptr(this);
    }

    WidKeyType tree_global_key {};

    //
    // Sorted for display order.
    //
    tree_wid_key key                                    {};
    WidKeyType tree2_key                                {};
    WidKeyType tree3_key                                {};
    WidKeyType tree4_key                                {};
    WidKeyType tree5_key                                {};

    wid_key_map_location *in_tree_root                  {};
    wid_key_map_int *in_tree2_unsorted_root             {};
    wid_key_map_int *in_tree3_moving_wids               {};
    wid_key_map_int *in_tree4_wids_being_destroyed      {};
    wid_key_map_int *in_tree5_ticking_wids              {};
    wid_key_map_int *in_tree_global_unsorted_root       {};

    //
    // Sorted for display onto the screen.
    //
    wid_key_map_location children_display_sorted {};

    //
    // No particular sort order.
    //
    wid_key_map_int tree2_children_unsorted {};

    //
    // A tree for moving things
    //
    wid_key_map_int tree3_moving_wids {};

    //
    // A tree for things being destroyed.
    //
    wid_key_map_int tree4_wids_being_destroyed {};

    //
    // A tree for ticking things
    //
    wid_key_map_int tree5_ticking_wids {};

    //
    // Tiles widget
    //
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
    uint8_t disable_scissors            {};
    uint8_t square                      {};

    //
    // Optionally set to the previous wid in a list
    //
    Widp prev {};
    Widp next {};
    Widp scrollbar_horiz {};
    Widp scrollbar_vert {};
    Widp scrollbar_owner {};

    int style {};

    //
    // The real position after scrollbar adjustments.
    //
    point abs_tl {};
    point abs_br {};

#if 0
    Texp tex {};
#endif
    Tilep bg_tile {};
    Tilep fg_tile {};
#if 0
    Tilep first_tile {};
    Tilep tile_curr {};
#endif

    fsize texuv {};

    fsize tex_tl {};
    fsize tex_br {};

    //
    // WID_MODE_NORMAL ...
    //
    wid_mode mode {};

    //
    // Offset of child widgets in the parent window.
    //
    point offset {};

    //
    // Config layers:
    //
    std::array<wid_cfg, WID_MODE_LAST> cfg {};

    //
    // Client context
    //
    int int_context {-1};

    //
    // Text placement.
    //
    point text_pos {};

    timestamp_t destroy_when {};
    timestamp_t timestamp_created {};
    timestamp_t timestamp_last_mode_change {};

    //
    // Queue of wid move requests.
    //
#define WID_MAX_MOVE_QUEUE 4
    std::array<wid_move_t, WID_MAX_MOVE_QUEUE> move {};
    point moving_start {};
    point moving_end {};
    timestamp_t timestamp_moving_begin {};
    timestamp_t timestamp_moving_end {};
    uint8_t moving {};

    //
    // Text input
    //
    uint16_t cursor {};

    //
    // Order of this wid amongst other focusable widgets.
    //
    uint8_t focus_order {};

    //
    // Who had it last ? Used when raising this wid again.
    //
    uint8_t focus_last {};

    //
    // The wids children
    //
    Widp parent {};

    //
    // Widget internal name.
    //
    std::string name {};

    //
    // For debugging.
    //
    std::string to_string {};

    //
    // Text that appears on the wid.
    //
    std::wstring text {};

    //
    // Action handlers
    //
    on_key_down_t on_key_down                   {};
    on_key_up_t on_key_up                       {};
    on_joy_button_t on_joy_button               {};
    on_mouse_down_t on_mouse_down               {};
    on_mouse_up_t on_mouse_up                   {};
    on_mouse_motion_t on_mouse_motion           {};
    on_mouse_focus_begin_t on_mouse_focus_begin {};
    on_mouse_focus_end_t on_mouse_focus_end     {};
    on_mouse_over_b_t on_mouse_over_b           {};
    on_mouse_over_e_t on_mouse_over_e           {};
    on_destroy_t on_destroy                     {};
    on_destroy_begin_t on_destroy_begin         {};
    on_tick_t on_tick                           {};
};

uint8_t wid_is_moving(Widp w);
void wid_set_style(Widp w, int style);
void wid_set_bg_tile(Widp w, Tilep tile);
void wid_set_fg_tile(Widp w, Tilep tile);

extern int wid_mouse_visible;
extern Widp wid_mouse_template;
extern Widp wid_over;
extern Widp wid_focus;

extern const int32_t wid_destroy_delay_ms;
extern std::array<
         std::array<Widp, ASCII_HEIGHT_MAX>,
            ASCII_WIDTH_MAX> wid_on_screen_at;
#endif
