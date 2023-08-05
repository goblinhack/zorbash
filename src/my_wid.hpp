//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_WID_HPP_
#define _MY_WID_HPP_

#include <list>
#include <map>

#include "my_ascii.hpp"
#include "my_thing_id.hpp"
#include "my_time.hpp"
#include "my_wid_tiles.hpp"

void WID_LOG(Widp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);
void WID_DBG(Widp, const char *fmt, ...) CHECK_FORMAT_STR(printf, 2, 3);

typedef enum {
  WID_COLOR_BG,
  WID_COLOR_TEXT_FG,
  WID_COLOR_TEXT_BG,
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

char wid_event_to_char(const struct SDL_Keysym *evt);

color wid_get_color(Widp, wid_color which);

int wid_get_height(Widp);
int wid_get_tl_x(Widp);
int wid_get_tl_y(Widp);
int wid_get_width(Widp);

int wid_get_style(Widp);

std::list< Widp > wid_find_all_at(const point p);
std::list< Widp > wid_find_all_containing(const std::string &name);
std::list< Widp > wid_find_all_containing(Widp w, const std::string &name);
std::list< Widp > wid_find_all(Widp w, const std::string &name);

std::string to_string(Widp);
std::string wid_get_name(Widp);
std::string wid_name(Widp);

std::wstring wid_get_text(Widp);
std::wstring wid_get_tooltip(Widp);

Widp wid_find_at(int x, int y);
Widp wid_find(const std::string &name);
Widp wid_find_under_mouse(void);
Widp wid_find_under_mouse_when_scrolling(void);
Widp wid_find(Widp, const std::string &name);
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
Widp wid_new_plain(Widp parent, std::string name);
Widp wid_new_square_button(Widp parent, std::string name);
Widp wid_new_square_window(std::string name);
Widp wid_new_vert_scroll_bar(Widp parent, std::string name, Widp scrollbar_owner);
Widp wid_new_window(std::string name);

typedef uint8_t (*on_joy_button_t)(Widp, int x, int y);
typedef uint8_t (*on_key_down_t)(Widp, const struct SDL_Keysym *);
typedef uint8_t (*on_key_up_t)(Widp, const struct SDL_Keysym *);
typedef uint8_t (*on_mouse_down_t)(Widp, int x, int y, uint32_t button);
typedef uint8_t (*on_mouse_held_t)(Widp, int x, int y, uint32_t button);
typedef uint8_t (*on_mouse_motion_t)(Widp, int x, int y, int relx, int rely, int wx, int wy);
typedef uint8_t (*on_mouse_up_t)(Widp, int x, int y, uint32_t button);

typedef void (*on_destroy_begin_t)(Widp);
typedef void (*on_destroy_t)(Widp);
typedef void (*on_mouse_focus_begin_t)(Widp);
typedef void (*on_mouse_focus_end_t)(Widp);
typedef void (*on_mouse_over_begin_t)(Widp, int relx, int rely, int wheelx, int wheely);
typedef void (*on_mouse_over_end_t)(Widp);
typedef void (*on_tick_t)(Widp);
typedef void (*on_display_t)(Widp, point tl, point br);
typedef void (*on_tick_post_display_t)(Widp);

uint32_t wid_get_cursor(Widp);
uint32_t wid_get_gllist(Widp);
uint32_t wid_get_mode_gllist(Widp);

int wid_get_br_x(Widp w);
int wid_get_br_y(Widp w);
int wid_get_tl_x(Widp w);
int wid_get_tl_y(Widp w);

int         wid_count(Widp w, int depth);
int         wid_get_int_context(Widp);
std::string wid_get_string_context(Widp);

#define WID_THING_ID_MAX_CONTEXT 2
ThingId wid_get_thing_id_context(Widp, int which);
void    wid_unset_thing_id_context(Widp, int which);
void    wid_clear_thing_id_context(Widp, int which);
void    wid_set_thing_context(Widp w, Thingp, int which);

uint8_t wid_get_do_not_lower(Widp);
uint8_t wid_get_do_not_raise(Widp);
uint8_t wid_get_focusable(Widp);
uint8_t wid_get_mode_top(Widp);
uint8_t wid_get_moveable_bounded(Widp);
uint8_t wid_get_moveable_horiz(Widp);
uint8_t wid_get_moveable_no_user_scroll(Widp);
uint8_t wid_get_moveable_vert(Widp);
uint8_t wid_get_moveable(Widp);
uint8_t wid_get_received_input(Widp);
uint8_t wid_get_show_cursor(Widp);
uint8_t wid_get_text_bot(Widp);
uint8_t wid_get_text_centerx(Widp);
uint8_t wid_get_text_centery(Widp);
uint8_t wid_get_text_lhs(Widp);
uint8_t wid_get_text_pos(Widp, int *x, int *y);
uint8_t wid_get_text_rhs(Widp);
uint8_t wid_get_text_top(Widp);
uint8_t wid_ignore_being_destroyed(Widp);
uint8_t wid_ignore_events(Widp);
uint8_t wid_ignore_for_focus(Widp);
uint8_t wid_ignore_scroll_events(Widp);
uint8_t wid_init(void);
uint8_t wid_is_always_hidden(Widp w);
uint8_t wid_is_hidden(Widp w);
uint8_t wid_receive_input(Widp, const SDL_Keysym *key);

void *wid_get_void_context(Widp);

void wid_always_hidden(Widp, uint8_t value);
void wid_destroy_in(Widp w, uint32_t ms);
void wid_destroy_nodelay(Widp *);
void wid_destroy_ptr_in(Widp *w, uint32_t ms);
void wid_destroy(Widp *);
void wid_display_all(bool ok_to_handle_requests = true);
void wid_dump(Widp w, int depth);
void wid_fake_joy_button(int x, int y);
void wid_fini(void);
void wid_focus_lock(Widp);
void wid_gc_all_force(void);
void wid_gc_all(void);
void wid_get_abs_coords_unclipped(Widp w, int *tlx, int *tly, int *brx, int *bry);
void wid_get_abs_coords(Widp w, int *tlx, int *tly, int *brx, int *bry);
void wid_get_abs(Widp w, int *x, int *y);
void wid_get_children_size(Widp, int *width, int *height);
void wid_get_pct(Widp w, double *x, double *y);
void wid_get_tl_x_tl_y_br_x_br_y(Widp w, int *tl_x, int *tl_y, int *br_x, int *br_y);
void wid_hide(Widp);
void wid_ignore_events_briefly(void);
void wid_joy_button(int x, int y);
void wid_key_down(const struct SDL_Keysym *, int x, int y);
void wid_key_up(const struct SDL_Keysym *, int x, int y);
void wid_lower(Widp);
void wid_mouse_down(uint32_t button, int x, int y);
void wid_mouse_held(uint32_t button, int x, int y);
void wid_mouse_hide(int);
void wid_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely);
void wid_mouse_move(Widp w);
void wid_mouse_up(uint32_t button, int x, int y);
void wid_mouse_warp(Widp w);
void wid_move_all(void);
void wid_move_delta_in(Widp w, int dx, int dy, uint32_t ms);
void wid_move_delta_pct(Widp, double dx, double dy);
void wid_move_delta(Widp, int dx, int dy);
void wid_move_end(Widp);
void wid_move_to_abs_centered_in(Widp, int dx, int dy, uint32_t delay);
void wid_move_to_abs_centered(Widp, int dx, int dy);
void wid_move_to_abs_in(Widp, int dx, int dy, uint32_t delay);
void wid_move_to_abs(Widp, int dx, int dy);
void wid_move_to_bottom(Widp);
void wid_move_to_centered_in(Widp, int dx, int dy, uint32_t delay);
void wid_move_to_horiz_pct_in(Widp w, double pct, double in);
void wid_move_to_horiz_pct(Widp w, double pct);
void wid_move_to_horiz_vert_pct_in(Widp w, double x, double y, double in);
void wid_move_to_left(Widp);
void wid_move_to_pct_centered_in(Widp, double dx, double dy, uint32_t delay);
void wid_move_to_pct_centered(Widp, double dx, double dy);
void wid_move_to_pct_in(Widp, double dx, double dy, uint32_t delay);
void wid_move_to_pct(Widp, double dx, double dy);
void wid_move_to_right(Widp);
void wid_move_to_top(Widp);
void wid_move_to_vert_pct_in(Widp w, double pct, double in);
void wid_move_to_vert_pct(Widp w, double pct);
void wid_move_to(Widp w, int x, int y);
void wid_move_to_y_off(Widp w, int off);
void wid_raise(Widp);
void wid_resize(Widp w, int width, int height);
void wid_scroll_text(Widp);
void wid_scroll_with_input(Widp, std::wstring str);
void wid_set_active(Widp);
void wid_set_color(Widp, wid_color col, color val);
void wid_set_cursor(Widp, uint32_t val);
void wid_set_debug(Widp, uint8_t);
void wid_set_do_not_lower(Widp, uint8_t val);
void wid_set_do_not_raise(Widp, uint8_t val);
void wid_set_focusable(Widp, uint8_t val);
void wid_set_focus(Widp);
void wid_set_ignore_events(Widp, uint8_t);
void wid_set_ignore_scroll_events(Widp, uint8_t);
void wid_set_int_context(Widp w, int);
void wid_set_mode(Widp, wid_mode mode);
void wid_set_moveable_bounded(Widp, uint8_t val);
void wid_set_moveable_horiz(Widp, uint8_t val);
void wid_set_moveable_no_user_scroll(Widp, uint8_t val);
void wid_set_moveable_vert(Widp, uint8_t val);
void wid_set_moveable(Widp, uint8_t val);
void wid_set_name(Widp, std::string);
void wid_set_on_destroy_begin(Widp, on_destroy_begin_t fn);
void wid_set_on_destroy(Widp, on_destroy_t fn);
void wid_set_on_display(Widp, on_display_t fn);
void wid_set_on_joy_button(Widp, on_joy_button_t fn);
void wid_set_on_key_down(Widp, on_key_down_t fn);
void wid_set_on_key_up(Widp, on_key_up_t fn);
void wid_set_on_mouse_down(Widp, on_mouse_down_t fn);
void wid_set_on_mouse_focus_begin(Widp, on_mouse_focus_begin_t fn);
void wid_set_on_mouse_focus_end(Widp, on_mouse_focus_end_t fn);
void wid_set_on_mouse_held(Widp, on_mouse_down_t fn);
void wid_set_on_mouse_motion(Widp, on_mouse_motion_t fn);
void wid_set_on_mouse_over_begin(Widp, on_mouse_over_begin_t fn);
void wid_set_on_mouse_over_end(Widp, on_mouse_over_end_t fn);
void wid_set_on_mouse_up(Widp, on_mouse_up_t fn);
void wid_set_on_tick_post_display(Widp, on_tick_post_display_t fn);
void wid_set_on_tick(Widp, on_tick_t fn);
void wid_set_pos_pct(Widp, fpoint tl, fpoint br);
void wid_set_pos(Widp, point tl, point br);
void wid_set_prev(Widp w, Widp);
void wid_set_received_input(Widp, uint8_t val);
void wid_set_shape_none(Widp);
void wid_set_shape_square(Widp);
void wid_set_show_cursor(Widp, uint8_t val);
void wid_set_string_context(Widp w, std::string);
void wid_set_style(Widp w, int style);
void wid_set_tex_br(Widp, fsize val);
void wid_set_text_bot(Widp, uint8_t val);
void wid_set_text_centerx(Widp, uint8_t val);
void wid_set_text_centery(Widp, uint8_t val);
void wid_set_text_lhs(Widp, uint8_t val);
void wid_set_tex_tl(Widp, fsize val);
void wid_set_text_max_len(Widp, size_t);
void wid_set_text_pos(Widp, uint8_t val, int x, int y);
void wid_set_text_rhs(Widp, uint8_t val);
void wid_set_text_top(Widp, uint8_t val);
void wid_set_text(Widp, int);
void wid_set_text(Widp, std::string);
void wid_set_text(Widp, std::wstring);
void wid_set_tile(int depth, Widp w, class Thing_ *t);
void wid_set_tile(int depth, Widp w, Tilep tile);
void wid_set_tilename(int depth, Widp, std::string name);
void wid_set_top(Widp, uint8_t val);
void wid_set_void_context(Widp w, void *);
void wid_this_visible(Widp);
void wid_toggle_hidden(Widp);
void wid_unset_focus();
void wid_unset_focus_lock(void);
void wid_update_mouse(void);
void wid_update(Widp);
void wid_visible(Widp);

wid_mode wid_get_mode(Widp);

typedef struct {
  //
  // Colors
  //
  std::array< color, WID_COLOR_MAX >   colors;
  std::array< uint8_t, WID_COLOR_MAX > color_set;
  int                                  style;
  uint8_t                              style_set;
} wid_cfg;

class tree_wid_key
{
public:
  tree_wid_key(void) = default;

  tree_wid_key(int priority, point tl, point br, uint64_t key) : priority(priority), tl(tl), br(br), key(key) {}

  ~tree_wid_key(void) = default;

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

struct tree_wid_key_cmp {
  bool operator()(const tree_wid_key &lhs, const tree_wid_key &rhs) const
  {
    if (lhs.priority < rhs.priority) {
      return true;
    }
    if (lhs.priority > rhs.priority) {
      return false;
    }

    if (lhs.br.y < rhs.br.y) {
      return true;
    }
    if (lhs.br.y > rhs.br.y) {
      return false;
    }

    if (lhs.key < rhs.key) {
      return true;
    }
    if (lhs.key > rhs.key) {
      return false;
    }

    return false;
  }
};

class WidKeyType
{
public:
  WidKeyType(void) = default;

  WidKeyType(uint64_t val) : val(val) {}

  bool operator<(const WidKeyType &rhs) const { return (val < rhs.val); }

  uint64_t val {};
};

typedef std::map< tree_wid_key, Widp, tree_wid_key_cmp > wid_key_map_location;
typedef std::map< WidKeyType, Widp >                     wid_key_map_int;

WidKeyType wid_unsorted_get_key(Widp w);

typedef struct wid_move_ {
  int  moving_endx;
  int  moving_endy;
  ts_t ts_moving_end;
} wid_move_t;

class Wid
{
public:
  Wid(void);
  ~Wid(void);

  WidKeyType tree_global_key {};

  //
  // Sorted for display order.
  //
  tree_wid_key key {};
  WidKeyType   tree2_key {};
  WidKeyType   tree3_key {};
  WidKeyType   tree4_key {};
  WidKeyType   tree5_key {};
  WidKeyType   tree6_key {};

  wid_key_map_location *in_tree_root {};
  wid_key_map_int      *in_tree2_unsorted_root {};
  wid_key_map_int      *in_tree3_moving_wids {};
  wid_key_map_int      *in_tree4_wids_being_destroyed {};
  wid_key_map_int      *in_tree5_tick_wids {};
  wid_key_map_int      *in_tree6_tick_wids_post_display {};
  wid_key_map_int      *in_tree_global_unsorted_root {};

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
  // A tree for tick things
  //
  wid_key_map_int tree5_tick_wids {};
  wid_key_map_int tree6_tick_post_displaying_wids {};

  //
  // Tiles widget
  //
  wid_tilesp wid_tiles {};

  uint8_t hidden {};
  uint8_t debug {};
  uint8_t tex_tl_set {};
  uint8_t tex_br_set {};
  uint8_t always_hidden {};
  uint8_t visible {};
  uint8_t received_input {};
  uint8_t moveable {};
  uint8_t moveable_set {};
  uint8_t moveable_horiz {};
  uint8_t moveable_horiz_set {};
  uint8_t moveable_vert {};
  uint8_t moveable_vert_set {};
  uint8_t moveable_bounded {};
  uint8_t moveable_bounded_set {};
  uint8_t moveable_no_user_scroll {};
  uint8_t moveable_no_user_scroll_set {};
  uint8_t ignore_events {};
  uint8_t ignore_scroll_events {};
  uint8_t ignore_for_mouse_down {};
  uint8_t first_update {};
  uint8_t show_cursor {};
  uint8_t text_pos_set {};
  uint8_t text_lhs {};
  uint8_t text_rhs {};
  uint8_t text_centerx {};
  uint8_t text_top {};
  uint8_t text_bot {};
  uint8_t text_centery {};
  uint8_t being_destroyed {};
  uint8_t do_not_raise {};
  uint8_t do_not_lower {};
  uint8_t disable_scissors {};
  uint8_t square {};
  uint8_t is_scrollbar_vert_trough {};
  uint8_t is_scrollbar_vert {};
  uint8_t is_scrollbar_horiz_trough {};
  uint8_t is_scrollbar_horiz {};

  //
  // Optionally set to the previous wid in a list
  //
  Widp prev {};
  Widp next {};
  Widp scrollbar_horiz {};
  Widp scrollbar_vert {};
  Widp scrollbar_owner {};

  //
  // The real position after scrollbar adjustments.
  //
  point abs_tl {};
  point abs_br {};

  //
  // Lots of layers of tiles for widgets.
  //
  TileLayers tiles = {};

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
  std::array< wid_cfg, WID_MODE_LAST > cfg {};

  //
  // Client context
  //
  std::string                                     string_context;
  int                                             int_context {-1};
  void                                           *void_context {};
  std::array< ThingId, WID_THING_ID_MAX_CONTEXT > thing_id_context {NoThingId};

  //
  // Text placement.
  //
  point text_pos {};

  ts_t destroy_when {};
  ts_t ts_created {};
  ts_t ts_last_mode_change {};

//
// Queue of wid move requests.
//
#define WID_MAX_MOVE_QUEUE 4
  std::array< wid_move_t, WID_MAX_MOVE_QUEUE > move {};
  point                                        moving_start {};
  point                                        moving_end {};
  ts_t                                         ts_moving_begin {};
  ts_t                                         ts_moving_end {};
  uint8_t                                      moving {};

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
  size_t       max_len {};

  //
  // Action handlers
  //
  on_key_down_t          on_key_down {};
  on_key_up_t            on_key_up {};
  on_joy_button_t        on_joy_button {};
  on_mouse_down_t        on_mouse_down {};
  on_mouse_down_t        on_mouse_held {};
  on_mouse_up_t          on_mouse_up {};
  on_mouse_motion_t      on_mouse_motion {};
  on_mouse_focus_begin_t on_mouse_focus_begin {};
  on_mouse_focus_end_t   on_mouse_focus_end {};
  on_mouse_over_begin_t  on_mouse_over_begin {};
  on_mouse_over_end_t    on_mouse_over_end {};
  on_destroy_t           on_destroy {};
  on_destroy_begin_t     on_destroy_begin {};
  on_tick_t              on_tick {};
  on_display_t           on_display {};
  on_tick_post_display_t on_tick_post_display {};
};

uint8_t wid_is_moving(Widp w);

bool wid_some_recent_event_occurred(void);

extern bool                                                              wid_mouse_two_clicks;
extern const int                                                         wid_destroy_delay_ms;
extern int                                                               wid_mouse_visible;
extern std::array< std::array< Widp, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > wid_on_screen_at;
extern ts_t                                                              wid_ignore_events_briefly_ts;
extern ts_t                                                              wid_last_mouse_motion;
extern ts_t                                                              wid_last_over_event;
extern Widp                                                              wid_focus;
extern Widp                                                              wid_mouse_template;
extern Widp                                                              wid_over;

#endif
