//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_command.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_sound.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_unicode.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_console.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_tp_info.hpp"

#undef ENABLE_DEBUG_GFX_GL_BLEND

//
// Unique key for each tree
//
static uint64_t key;

//
// Display sorted.
//
static wid_key_map_location wid_top_level;

//
// Creation sorted and global.
//
static wid_key_map_int wid_global;

//
// Creation sorted and per wid parent.
//
static wid_key_map_int wid_top_level2;

//
// For moving things.
//
static wid_key_map_int wid_top_level3;

//
// For garbage collection.
//
static wid_key_map_int wid_top_level4;

//
// For tick things.
//
static wid_key_map_int wid_tick_top_level;
static wid_key_map_int wid_tick_post_display_top_level;

//
// Ignore events to avoid processing the same event twice if we
// look at scancodes and bypass wid events
//
ts_t wid_ignore_events_briefly_ts;

//
// Last time we changed what we were over.
//
ts_t wid_last_over_event;

//
// Scope the focus to children of this widget and do not change it.
// Good for popups.
//
static Widp wid_focus_locked {};
Widp        wid_focus {};
Widp        wid_over {};

//
// Mouse
//
int  wid_mouse_visible = 1;
bool wid_mouse_two_clicks;
ts_t wid_last_mouse_motion;

//
// Widget moving
//
static Widp wid_moving {};
static int  wid_moving_last_x;
static int  wid_moving_last_y;

static ts_t wid_time;

//
// Widget effects
//
const ts_t wid_destroy_delay_ms = 200;

//
// Prototypes.
//
static void    wid_destroy_delay(Widp *wp, int delay);
static uint8_t wid_scroll_trough_mouse_down(Widp w, int x, int y, uint32_t button);
static uint8_t wid_scroll_trough_mouse_motion(Widp w, int x, int y, int relx, int rely, int wheelx, int wheely);
static void    wid_find_first_focus(void);
static void    wid_find_top_focus(void);
static void    wid_destroy_immediate(Widp w);
static void    wid_destroy_immediate_internal(Widp w);
static void    wid_update_internal(Widp w);
static void    wid_tree_detach(Widp w);
static void    wid_tree_attach(Widp w);
static void    wid_tree_remove(Widp w);
static void    wid_tree2_unsorted_remove(Widp w);
static void    wid_tree3_moving_wids_remove(Widp w);
static void    wid_tree3_moving_wids_insert(Widp w);
static void    wid_tree4_wids_being_destroyed_remove(Widp w);
static void    wid_tree4_wids_being_destroyed_insert(Widp w);
static void    wid_tree5_tick_wids_remove(Widp w);
static void    wid_tree5_tick_wids_insert(Widp w);
static void    wid_tree6_tick_post_display_wids_remove(Widp w);
static void    wid_tree6_tick_post_display_wids_insert(Widp w);
static void    wid_move_dequeue(Widp w);
static void    wid_display(Widp w, uint8_t disable_scissor, uint8_t *updated_scissors, int clip);

//
// Child sort priority
//
static int wid_highest_priority = 1;
static int wid_lowest_priority  = -1;

//
// History for all text widgets.
//
#define HISTORY_MAX 16
std::array< std::wstring, HISTORY_MAX > history;
uint32_t                                g_history_at;
uint32_t                                g_history_walk;

//
// A tile over the mouse pointer
//
Widp                                                              wid_mouse_template {};
std::array< std::array< Widp, TERM_HEIGHT_MAX >, TERM_WIDTH_MAX > wid_on_screen_at {};

static uint8_t wid_init_done;
static uint8_t wid_exiting;

static int wid_refresh_overlay_count;

Wid::Wid(void) { newptr(MTYPE_WID, this, "wid"); }

Wid::~Wid(void) { oldptr(MTYPE_WID, this); }

uint8_t wid_init(void)
{
  TRACE_NO_INDENT();
  wid_init_done = true;

  return true;
}

void wid_fini(void)
{
  TRACE_NO_INDENT();
  wid_init_done = false;
  wid_exiting   = true;

  wid_on_screen_at = {};

  wid_gc_all();

  for (;;) {
    if (! wid_top_level.size()) {
      break;
    }

    auto iter  = wid_top_level.begin();
    auto child = iter->second;
    wid_destroy_immediate(child);
  }
}

void wid_dump(Widp w, int depth)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return;
  }

  int tlx;
  int tly;
  int brx;
  int bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  printf("\n          %*s dump: [%s] text [%S] %d,%d to @%d,%d %d children", depth * 2, "", wid_name(w).c_str(),
         wid_get_text(w).c_str(), tlx, tly, brx, bry, wid_count(w, depth));

#if 1
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    wid_dump(child, depth + 2);
  }
#endif
}

int wid_count(Widp w, int depth)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return 0;
  }

  int count = 1;

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    count += wid_count(child, depth + 2);
  }

  return count;
}

int wid_get_tl_x(Widp w)
{
  TRACE_NO_INDENT();
  int cx = (w->key.tl.x + w->key.br.x) / 2.0;

  return (cx - (cx - w->key.tl.x));
}

int wid_get_tl_y(Widp w)
{
  TRACE_NO_INDENT();
  int cy = (w->key.tl.y + w->key.br.y) / 2.0;

  return (cy - (cy - w->key.tl.y));
}

int wid_get_br_x(Widp w)
{
  TRACE_NO_INDENT();
  int cx = (w->key.tl.x + w->key.br.x) / 2.0;

  return (cx + (w->key.br.x - cx));
}

int wid_get_br_y(Widp w)
{
  TRACE_NO_INDENT();
  int cy = (w->key.tl.y + w->key.br.y) / 2.0;

  return (cy + (w->key.br.y - cy));
}

void wid_get_tl_x_tl_y_br_x_br_y(Widp w, int *tl_x, int *tl_y, int *br_x, int *br_y)
{
  TRACE_NO_INDENT();

  if (! w) {
    *tl_x = 0;
    *tl_y = 0;
    *br_x = 0;
    *br_y = 0;
    ERR("NULL wid");
    return;
  }

  const int tlx = w->key.tl.x;
  const int tly = w->key.tl.y;
  const int brx = w->key.br.x;
  const int bry = w->key.br.y;

  const int cx = (tlx + brx) / 2.0;
  const int cy = (tly + bry) / 2.0;

  *tl_x = cx - (cx - tlx);
  *tl_y = cy - (cy - tly);
  *br_x = cx + (brx - cx);
  *br_y = cy + (bry - cy);
}

//
// Set the wid new co-ords. Returns true if there is a change.
//
void wid_set_pos(Widp w, point tl, point br)
{
  TRACE_NO_INDENT();
  Widp p {};

  wid_tree_detach(w);

  w->key.tl = tl;
  w->key.br = br;

  //
  // Child postion is relative from the parent.
  //
  p = w->parent;
  if (p) {
    w->key.tl.x += wid_get_tl_x(p);
    w->key.tl.y += wid_get_tl_y(p);
    w->key.br.x += wid_get_tl_x(p);
    w->key.br.y += wid_get_tl_y(p);

    w->key.tl.x -= p->offset.x;
    w->key.tl.y -= p->offset.y;
    w->key.br.x -= p->offset.x;
    w->key.br.y -= p->offset.y;
  }

  wid_tree_attach(w);
}

//
// Set the wid new co-ords. Returns true if there is a change.
//
void wid_set_pos_pct(Widp w, fpoint tl, fpoint br)
{
  TRACE_NO_INDENT();
  Widp p {};

  wid_tree_detach(w);

  if (! w->parent) {
    tl.x *= TERM_WIDTH;
    tl.y *= TERM_HEIGHT;
    br.x *= TERM_WIDTH;
    br.y *= TERM_HEIGHT;
  } else {
    tl.x *= wid_get_width(w->parent);
    tl.y *= wid_get_height(w->parent);
    br.x *= wid_get_width(w->parent);
    br.y *= wid_get_height(w->parent);
  }

  if (tl.x < 0) {
    tl.x = 0;
  }
  if (tl.y < 0) {
    tl.y = 0;
  }
  if (br.x >= wid_get_width(w->parent)) {
    br.x = wid_get_width(w->parent) - 1;
  }
  if (br.y >= wid_get_height(w->parent)) {
    br.y = wid_get_height(w->parent) - 1;
  }

  int key_tl_x = tl.x;
  int key_tl_y = tl.y;
  int key_br_x = br.x;
  int key_br_y = br.y;

  //
  // Child postion is relative from the parent.
  //
  p = w->parent;
  if (p) {
    key_tl_x += wid_get_tl_x(p);
    key_tl_y += wid_get_tl_y(p);
    key_br_x += wid_get_tl_x(p);
    key_br_y += wid_get_tl_y(p);
  }

  w->key.tl.x = (int) round(key_tl_x);
  w->key.tl.y = (int) round(key_tl_y);
  w->key.br.x = (int) round(key_br_x);
  w->key.br.y = (int) round(key_br_y);

  wid_tree_attach(w);
}

void wid_set_string_context(Widp w, std::string string_context)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL postringer");
    return;
  }
  w->string_context = string_context;
}

std::string wid_get_string_context(Widp w)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL postringer");
    return 0;
  }
  return (w->string_context);
}

void wid_set_int_context(Widp w, int int_context)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return;
  }
  w->int_context = int_context;
}

int wid_get_int_context(Widp w)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return 0;
  }
  return (w->int_context);
}

void wid_set_void_context(Widp w, void *void_context)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return;
  }
  w->void_context = void_context;
}

void *wid_get_void_context(Widp w)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return nullptr;
  }
  return (w->void_context);
}

void wid_unset_thing_id_context(Widp w, int which)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return;
  }

  auto id = w->thing_id_context[ which ];
  if (id != NoThingId) {
    auto t                       = game->thing_find(id);
    w->thing_id_context[ which ] = NoThingId;
    if (t) {
      auto items = t->maybe_itemsp();
      if (items) {
        WID_DBG(w, "unset thing reference %" PRIX32, id.id);
        IF_DEBUG2 { t->log("unset thing reference %s", wid_get_name(w).c_str()); }
        items->thing_wid.erase(w);
      }
    }
  }
}

void wid_clear_thing_id_context(Widp w, int which)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return;
  }

  auto id = w->thing_id_context[ which ];
  if (id != NoThingId) {
    WID_DBG(w, "clear thing reference wid[%d] %p -> %" PRIX32, which, w, id.id);
    w->thing_id_context[ which ] = NoThingId;
  }
}

void wid_set_thing_context(Widp w, Thingp t, int which)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return;
  }

  wid_unset_thing_id_context(w, which);
  w->thing_id_context[ which ] = t->id;

  t->new_itemsp();
  auto items = t->maybe_itemsp();
  if (items) {
    WID_DBG(w, "set thing reference wid %" PRIX32, t->id.id);
    IF_DEBUG2 { t->log("set thing reference %s", wid_get_name(w).c_str()); }
    items->thing_wid.insert(w);
  }
}

ThingId wid_get_thing_id_context(Widp w, int which)
{
  TRACE_NO_INDENT();
  if (! w) {
    ERR("NULL pointer");
    return NoThingId;
  }

  auto id = w->thing_id_context[ which ];
  if (id != NoThingId) {
    WID_DBG(w, "get thing reference wid[%d] %p -> %" PRIX32, which, w, id.id);
  }
  return id;
}

void wid_set_prev(Widp w, Widp prev)
{
  TRACE_NO_INDENT();

  IF_DEBUG3
  {
    verify(MTYPE_WID, w);
    if (prev) {
      verify(MTYPE_WID, prev);
    }
  }

  if (unlikely(! w)) {
    DIE("No wid");
  }

  if (w == prev) {
    DIE("Wid list loop");
  }

  w->prev = prev;

  if (prev) {
    prev->next = w;
  }
}

Widp wid_get_prev(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    DIE("No wid");
  }

  if (w->prev == w) {
    DIE("Wid list get prev loop");
  }

  return (w->prev);
}

Widp wid_get_next(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    DIE("No wid");
  }

  if (w->next == w) {
    ERR("Wid list get next loop");
  }

  return (w->next);
}

Widp wid_get_head(Widp w)
{
  TRACE_NO_INDENT();
  Widp prev {};

  while (w) {
    prev = wid_get_prev(w);
    if (! prev) {
      break;
    }

    w = prev;
  }

  return w;
}

Widp wid_get_tail(Widp w)
{
  TRACE_NO_INDENT();
  Widp next {};

  while (w) {
    next = wid_get_next(w);
    if (! next) {
      break;
    }

    w = next;
  }

  return w;
}

Widp wid_get_top_parent(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return w;
  }

  IF_DEBUG3 { verify(MTYPE_WID, w); }

  if (! w->parent) {
    return w;
  }

  while (w->parent) {
    IF_DEBUG3 { verify(MTYPE_WID, w); }
    w = w->parent;
  }

  return w;
}

Widp wid_get_parent(Widp w)
{
  TRACE_NO_INDENT();
  return (w->parent);
}

Widp wid_get_scrollbar_vert(Widp w)
{
  TRACE_NO_INDENT();
  return (w->scrollbar_vert);
}

Widp wid_get_scrollbar_horiz(Widp w)
{
  TRACE_NO_INDENT();
  return (w->scrollbar_horiz);
}

static void wid_mouse_motion_end(void)
{
  TRACE_NO_INDENT();
  wid_moving = nullptr;
}

void wid_set_ignore_events(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  w->ignore_events = val;
}

void wid_set_ignore_scroll_events(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  w->ignore_scroll_events = val;
}

static void wid_set_scissors(int tlx, int tly, int brx, int bry)
{
  TRACE_NO_INDENT();
  ascii_set_scissors(point(tlx, tly), point(brx, bry));
}

//
// Should this widget be ignored for events?
//
uint8_t wid_ignore_events(Widp w)
{
  TRACE_NO_INDENT();
  Widp top {};

  if (unlikely(! w)) {
    return true;
  }

  if (w->ignore_events || w->moving || w->hidden || w->being_destroyed) {
    return true;
  }

  if (w->parent) {
    top = wid_get_top_parent(w);

    if (top->moving || top->hidden || top->being_destroyed) {
      return true;
    }
  }

  return false;
}

uint8_t wid_ignore_events_only(Widp w)
{
  TRACE_NO_INDENT();
  Widp top {};

  if (unlikely(! w)) {
    return true;
  }

  if (w->ignore_events) {
    return true;
  }

  if (w->parent) {
    top = wid_get_top_parent(w);

    if (top->moving) {
      return true;
    }
  }

  return false;
}

uint8_t wid_ignore_scroll_events(Widp w)
{
  TRACE_NO_INDENT();
  Widp top {};

  if (unlikely(! w)) {
    return true;
  }

  if (w->ignore_scroll_events || w->moving || w->hidden || w->being_destroyed) {
    return true;
  }

  if (w->parent) {
    top = wid_get_top_parent(w);

    if (top->moving || top->hidden || top->being_destroyed) {
      return true;
    }
  }

  return false;
}

uint8_t wid_ignore_for_focus(Widp w)
{
  TRACE_NO_INDENT();
  Widp top {};

  if (w->hidden || w->being_destroyed) {
    return true;
  }

  if (w->parent) {
    top = wid_get_top_parent(w);

    if (top->hidden || top->being_destroyed) {
      return true;
    }
  }

  return false;
}

//
// Should this widget be ignored for events?
//
uint8_t wid_ignore_being_destroyed(Widp w)
{
  TRACE_NO_INDENT();
  Widp top {};

  if (w->being_destroyed) {
    return true;
  }

  if (w->parent) {
    top = wid_get_top_parent(w);

    if (top->being_destroyed) {
      return true;
    }
  }

  return false;
}

static void wid_mouse_motion_begin(Widp w, int x, int y)
{
  TRACE_NO_INDENT();
  wid_mouse_motion_end();

  if (wid_ignore_being_destroyed(w)) {
    return;
  }

  wid_moving        = w;
  wid_moving_last_x = x;
  wid_moving_last_y = y;
}

static void wid_mfocus_end(void)
{
  TRACE_NO_INDENT();
  Widp w {};

  w                = wid_focus;
  wid_focus        = nullptr;
  wid_focus_locked = nullptr;

  if (unlikely(! w)) {
    return;
  }

  if (w->on_mouse_focus_end) {
    w->on_mouse_focus_end(w);
  }
}

Widp wid_get_current_focus(void)
{
  TRACE_NO_INDENT();
  return wid_focus;
}

static void wid_mfocus_begin(Widp w)
{
  TRACE_NO_INDENT();
  Widp top {};

  if (unlikely(! w)) {
    wid_mfocus_end();
    wid_focus = nullptr;

    wid_find_top_focus();
    return;
  }

  if (wid_focus == w) {
    return;
  }

  wid_mfocus_end();

  if (wid_ignore_for_focus(w)) {
    return;
  }

  top = wid_get_top_parent(w);

  wid_focus       = w;
  top->focus_last = w->focus_order;

  if (w->on_mouse_focus_begin) {
    w->on_mouse_focus_begin(w);
  }
}

static void wid_mouse_over_end(void)
{
  TRACE_NO_INDENT();
  Widp w {};

  if (! wid_mouse_visible) {
    return;
  }

  w = wid_over;
  if (wid_over) {
    if (! wid_ignore_events(wid_over)) {
      wid_last_over_event = time_ms_cached();
      // DBG("mouse over end %s mouse %d,%d.", wid_over->name.c_str(), ascii_mouse_x, ascii_mouse_y);
    }
  }
  wid_over = nullptr;

  if (unlikely(! w)) {
    return;
  }

  wid_set_mode(w, WID_MODE_NORMAL);

  //
  // Python can try and do cleanup - and if we're exiting already, no point.
  //
  if (wid_exiting) {
    return;
  }

  if (w->on_mouse_over_end) {
    w->on_mouse_over_end(w);
  }
}

static uint8_t wid_mouse_over_begin(Widp w, uint32_t x, uint32_t y, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  if (! wid_mouse_visible) {
    return false;
  }

  if (wid_over == w) {
    return true;
  }

  if (wid_ignore_events(w)) {
    return false;
  }

  if (wheelx || wheely) {
    if (wid_ignore_scroll_events(w)) {
      return false;
    }
  }

  if (! w->on_mouse_over_begin && ! w->on_mouse_down) {
    if (get(w->cfg, WID_MODE_OVER).color_set[ WID_COLOR_BG ]
        || get(w->cfg, WID_MODE_OVER).color_set[ WID_COLOR_TEXT_FG ]) {
      //
      // Changes appearance on mouse over, so choose this wid even
      // if it has no over callback.
      //
    } else {
      //
      // Can ignore. It doesn't really do anything when the mouse
      // is over.
      //
      if (! wid_over && get(wid_on_screen_at, x, y)) {
        //
        // But if we have nothing else, use this
        //
      } else {
        return false;
      }
    }
  }

  if (wid_ignore_being_destroyed(w)) {
    return false;
  }

  wid_mouse_over_end();

  wid_over = w;
  if (! wid_ignore_events(wid_over)) {
    wid_last_over_event = time_ms_cached();
    // DBG("mouse over %s mouse %d,%d.", wid_over->name.c_str(), ascii_mouse_x, ascii_mouse_y);
  }

  wid_set_mode(w, WID_MODE_OVER);

  if (w->on_mouse_over_begin) {
    (w->on_mouse_over_begin)(w, relx, rely, wheelx, wheely);
  }

  return true;
}

//
// Map an SDL key event to the char the user typed
//
char wid_event_to_char(const struct SDL_Keysym *evt)
{
  TRACE_NO_INDENT();
  if ((evt->mod & KMOD_LSHIFT) || (evt->mod & KMOD_RSHIFT)) {
    switch (evt->sym) {
      case SDLK_a : return ('A');
      case SDLK_b : return ('B');
      case SDLK_c : return ('C');
      case SDLK_d : return ('D');
      case SDLK_e : return ('E');
      case SDLK_f : return ('F');
      case SDLK_g : return ('G');
      case SDLK_h : return ('H');
      case SDLK_i : return ('I');
      case SDLK_j : return ('J');
      case SDLK_k : return ('K');
      case SDLK_l : return ('L');
      case SDLK_m : return ('M');
      case SDLK_n : return ('N');
      case SDLK_o : return ('O');
      case SDLK_p : return ('P');
      case SDLK_q : return ('Q');
      case SDLK_r : return ('R');
      case SDLK_s : return ('S');
      case SDLK_t : return ('T');
      case SDLK_u : return ('U');
      case SDLK_v : return ('V');
      case SDLK_w : return ('W');
      case SDLK_x : return ('X');
      case SDLK_y : return ('Y');
      case SDLK_z : return ('Z');
      case SDLK_QUOTE : return ('"');
      case SDLK_COMMA : return ('<');
      case SDLK_MINUS : return ('_');
      case SDLK_PERIOD : return ('>');
      case SDLK_SLASH : return ('?');
      case SDLK_EQUALS : return ('+');
      case SDLK_0 : return (')');
      case SDLK_1 : return ('!');
      case SDLK_2 : return ('@');
      case SDLK_3 : return ('#');
      case SDLK_4 : return ('$');
      case SDLK_5 : return ('%');
      case SDLK_6 : return ('^');
      case SDLK_7 : return ('&');
      case SDLK_8 : return ('*');
      case SDLK_9 : return ('(');
      case SDLK_SEMICOLON : return (':');
      case SDLK_LEFTBRACKET : return ('{');
      case SDLK_BACKSLASH : return ('|');
      case SDLK_RIGHTBRACKET : return ('}');
      case SDLK_HASH : return ('~');
    }
  }

  switch (evt->sym) {
    case SDLK_BACKSPACE : return ('');
    case SDLK_TAB : return ('\t');
    case SDLK_RETURN : return ('\n');
    case SDLK_ESCAPE : return ('');
    case SDLK_SPACE : return (' ');
    case SDLK_EXCLAIM : return ('!');
    case SDLK_QUOTEDBL : return ('"');
    case SDLK_HASH : return ('#');
    case SDLK_DOLLAR : return ('$');
    case SDLK_AMPERSAND : return ('%');
    case SDLK_QUOTE : return ('\'');
    case SDLK_LEFTPAREN : return ('(');
    case SDLK_RIGHTPAREN : return (')');
    case SDLK_ASTERISK : return ('*');
    case SDLK_PLUS : return ('+');
    case SDLK_COMMA : return (',');
    case SDLK_MINUS : return ('-');
    case SDLK_PERIOD : return ('.');
    case SDLK_SLASH : return ('/');
    case SDLK_0 : return ('0');
    case SDLK_1 : return ('1');
    case SDLK_2 : return ('2');
    case SDLK_3 : return ('3');
    case SDLK_4 : return ('4');
    case SDLK_5 : return ('5');
    case SDLK_6 : return ('6');
    case SDLK_7 : return ('7');
    case SDLK_8 : return ('8');
    case SDLK_9 : return ('9');
    case SDLK_COLON : return (':');
    case SDLK_SEMICOLON : return (';');
    case SDLK_LESS : return ('<');
    case SDLK_EQUALS : return ('=');
    case SDLK_GREATER : return ('>');
    case SDLK_QUESTION : return ('?');
    case SDLK_AT : return ('@');
    case SDLK_LEFTBRACKET : return ('[');
    case SDLK_BACKSLASH : return ('\\');
    case SDLK_RIGHTBRACKET : return (']');
    case SDLK_CARET : return ('^');
    case SDLK_UNDERSCORE : return ('_');
    case SDLK_BACKQUOTE : return ('`');
    case SDLK_a : return ('a');
    case SDLK_b : return ('b');
    case SDLK_c : return ('c');
    case SDLK_d : return ('d');
    case SDLK_e : return ('e');
    case SDLK_f : return ('f');
    case SDLK_g : return ('g');
    case SDLK_h : return ('h');
    case SDLK_i : return ('i');
    case SDLK_j : return ('j');
    case SDLK_k : return ('k');
    case SDLK_l : return ('l');
    case SDLK_m : return ('m');
    case SDLK_n : return ('n');
    case SDLK_o : return ('o');
    case SDLK_p : return ('p');
    case SDLK_q : return ('q');
    case SDLK_r : return ('r');
    case SDLK_s : return ('s');
    case SDLK_t : return ('t');
    case SDLK_u : return ('u');
    case SDLK_v : return ('v');
    case SDLK_w : return ('w');
    case SDLK_x : return ('x');
    case SDLK_y : return ('y');
    case SDLK_z : return ('z');
    case SDLK_DELETE : return ('');
#if SDL_MAJOR_VERSION == 1 // {
    case SDLK_KP0 : return ('0');
    case SDLK_KP1 : return ('1');
    case SDLK_KP2 : return ('2');
    case SDLK_KP3 : return ('3');
    case SDLK_KP4 : return ('4');
    case SDLK_KP5 : return ('5');
    case SDLK_KP6 : return ('6');
    case SDLK_KP7 : return ('7');
    case SDLK_KP8 : return ('8');
    case SDLK_KP9 : return ('9');
#else
    case SDLK_KP_0 : return ('0');
    case SDLK_KP_1 : return ('1');
    case SDLK_KP_2 : return ('2');
    case SDLK_KP_3 : return ('3');
    case SDLK_KP_4 : return ('4');
    case SDLK_KP_5 : return ('5');
    case SDLK_KP_6 : return ('6');
    case SDLK_KP_7 : return ('7');
    case SDLK_KP_8 : return ('8');
    case SDLK_KP_9 : return ('9');
#endif // }
    case SDLK_KP_PERIOD : return ('.');
    case SDLK_KP_DIVIDE : return ('/');
    case SDLK_KP_MULTIPLY : return ('*');
    case SDLK_KP_MINUS : return ('-');
    case SDLK_KP_PLUS : return ('+');
    case SDLK_KP_ENTER : return ('\0');
    case SDLK_KP_EQUALS : return ('=');
    case SDLK_UP : return ('\0');
    case SDLK_DOWN : return ('\0');
    case SDLK_RIGHT : return ('\0');
    case SDLK_LEFT : return ('\0');
    case SDLK_INSERT : return ('\0');
    case SDLK_HOME : return ('\0');
    case SDLK_END : return ('\0');
    case SDLK_PAGEUP : return ('\0');
    case SDLK_PAGEDOWN : return ('\0');
    case SDLK_F1 : return ('\0');
    case SDLK_F2 : return ('\0');
    case SDLK_F3 : return ('\0');
    case SDLK_F4 : return ('\0');
    case SDLK_F5 : return ('\0');
    case SDLK_F6 : return ('\0');
    case SDLK_F7 : return ('\0');
    case SDLK_F8 : return ('\0');
    case SDLK_F9 : return ('\0');
    case SDLK_F10 : return ('\0');
    case SDLK_F11 : return ('\0');
    case SDLK_F12 : return ('\0');
    case SDLK_F13 : return ('\0');
    case SDLK_F14 : return ('\0');
    case SDLK_F15 : return ('\0');
    case SDLK_CAPSLOCK : return ('\0');
    case SDLK_RSHIFT : return ('\0');
    case SDLK_LSHIFT : return ('\0');
    case SDLK_RCTRL : return ('\0');
    case SDLK_LCTRL : return ('\0');
    case SDLK_RALT : return ('\0');
    case SDLK_LALT : return ('\0');
    case SDLK_MODE : return ('\0');
    case SDLK_HELP : return ('!');
    case SDLK_SYSREQ : return ('\0');
    case SDLK_MENU : return ('\0');
    case SDLK_POWER : return ('\0');
    case SDLK_UNDO : return ('\0');
    default : return ('\0');
  }
  return ('\0');
}

//
// Widget mode, whether it is active, inactive etc...
//
void wid_set_mode(Widp w, wid_mode mode)
{
  TRACE_NO_INDENT();
  w->ts_last_mode_change = wid_time;
  w->mode                = mode;
}

//
// Widget mode, whether it is active, inactive etc...
//
wid_mode wid_get_mode(Widp w)
{
  TRACE_NO_INDENT();
  //
  // Allow focus to override less important modes.
  //
  if (w == wid_focus) {
    if ((w->mode == WID_MODE_NORMAL) || (w->mode == WID_MODE_OVER)) {
      return (WID_MODE_FOCUS);
    }
  }

  return (w->mode);
}

std::string to_string(Widp w)
{
  TRACE_NO_INDENT();
  return (w->to_string);
}

std::string wid_name(Widp w)
{
  TRACE_NO_INDENT();
  return (w->name);
}

std::wstring wid_get_text(Widp w)
{
  TRACE_NO_INDENT();
  return (w->text);
}

std::string wid_get_name(Widp w)
{
  TRACE_NO_INDENT();
  return (w->name);
}

static std::wstring wid_get_text_with_cursor(Widp w)
{
  TRACE_NO_INDENT();
  if (! w->received_input) {
    w->cursor = (uint32_t) w->text.length();
  }

  std::wstring t = w->text;
  std::wstring o = t.substr(0, w->cursor) + UNICODE_ALIAS_FOR_CURSOR + t.substr(w->cursor);

  return o;
}

void wid_set_name(Widp w, std::string name)
{
  TRACE_NO_INDENT();
  if (name != "") {
    oldptr(MTYPE_WID, w);
    w->name = name;
    newptr(MTYPE_WID, w, "wid");
  } else {
    w->name = name;
  }

#ifdef ENABLE_DEBUG_UI
#ifdef ENABLE_DEBUG_UI2
  if (w->parent) {
    w->to_string = string_sprintf("%s[%p] (parent %s[%p])", name.c_str(), w, w->parent->to_string.c_str(), w->parent);
  } else {
    w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
  }
#else
  w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif
}

void wid_set_debug(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();

  IF_DEBUG3 { verify(MTYPE_WID, w); }

  w->debug = val;
}

void wid_set_text_max_len(Widp w, size_t max_len) { w->max_len = max_len; }

void wid_set_text(Widp w, std::wstring text)
{
  TRACE_NO_INDENT();

  IF_DEBUG3 { verify(MTYPE_WID, w); }

  if (text == L"") {
    w->text = L"";
  } else {
    if (text == w->text) {
      return;
    }

    w->text = text;
  }

  if (w->max_len) {
    if (w->text.size() > w->max_len) {
      w->text.resize(w->max_len);
    }
  }

  auto len = w->text.size();
  if (w->cursor > len) {
    w->cursor = len;
  }
}

void wid_set_text(Widp w, std::string text)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  wid_set_text(w, string_to_wstring(text));
}

void wid_set_text(Widp w, int v)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  wid_set_text(w, std::to_string(v));
}

uint8_t wid_get_received_input(Widp w)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  return (w->received_input);
}

void wid_set_received_input(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  w->received_input = val;
}

uint32_t wid_get_cursor(Widp w)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  return (w->cursor);
}

void wid_set_cursor(Widp w, uint32_t val)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  w->cursor = val;
}

int wid_get_width(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (wid_get_br_x(w) - wid_get_tl_x(w)) + 1;
}

int wid_get_height(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (wid_get_br_y(w) - wid_get_tl_y(w)) + 1;
}

uint8_t wid_get_focusable(Widp w)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  return (w->focus_order);
}

void wid_set_focusable(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  w->focus_order = val;
}

uint8_t wid_get_show_cursor(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->show_cursor);
}

void wid_set_show_cursor(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->show_cursor = val;
}

uint8_t wid_get_do_not_raise(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->do_not_raise);
}

void wid_set_do_not_raise(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->do_not_raise = val;
}

uint8_t wid_get_do_not_lower(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->do_not_lower);
}

void wid_set_do_not_lower(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->do_not_lower = val;
}

uint8_t wid_get_moveable(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  if (w->moveable_set) {
    return (w->moveable);
  }

  return false;
}

void wid_set_moveable(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->moveable     = val;
  w->moveable_set = true;

  wid_set_moveable_horiz(w, val);
  wid_set_moveable_vert(w, val);
}

uint8_t wid_get_moveable_horiz(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  if (w->moveable_horiz_set) {
    return (w->moveable_horiz);
  }

  return false;
}

void wid_set_moveable_horiz(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->moveable_horiz     = val;
  w->moveable_horiz_set = true;
}

uint8_t wid_get_moveable_vert(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  if (w->moveable_vert_set) {
    return (w->moveable_vert);
  }

  return false;
}

void wid_set_moveable_vert(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->moveable_vert     = val;
  w->moveable_vert_set = true;
}

uint8_t wid_get_moveable_bounded(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  if (w->moveable_bounded_set) {
    return (w->moveable_bounded);
  }

  return false;
}

void wid_set_moveable_bounded(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->moveable_bounded     = val;
  w->moveable_bounded_set = true;
}

uint8_t wid_get_moveable_no_user_scroll(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  if (w->moveable_no_user_scroll_set) {
    return (w->moveable_no_user_scroll);
  }

  return false;
}

void wid_set_moveable_no_user_scroll(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->moveable_no_user_scroll     = val;
  w->moveable_no_user_scroll_set = true;
}

uint8_t wid_get_text_lhs(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->text_lhs);
}

void wid_set_text_lhs(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->text_lhs = val;
}

uint8_t wid_get_text_rhs(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->text_rhs);
}

void wid_set_text_rhs(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->text_rhs = true;
}

uint8_t wid_get_text_centerx(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->text_centerx);
}

void wid_set_text_centerx(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->text_centerx = val;
}

uint8_t wid_get_text_top(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->text_top);
}

void wid_set_text_top(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  w->text_top = val;
}

uint8_t wid_get_text_bot(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  return (w->text_bot);
}

void wid_set_text_bot(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  w->text_bot = val;
}

uint8_t wid_get_text_centery(Widp w)
{
  TRACE_NO_INDENT();
  return (w->text_centery);
}

void wid_set_text_centery(Widp w, uint8_t val)
{
  TRACE_NO_INDENT();
  w->text_centery = val;
}

uint8_t wid_get_text_pos(Widp w, int *x, int *y)
{
  TRACE_NO_INDENT();
  if (w->text_pos_set) {
    *x = w->text_pos.x;
    *y = w->text_pos.y;

    return true;
  }

  return false;
}

void wid_set_text_pos(Widp w, uint8_t val, int x, int y)
{
  TRACE_NO_INDENT();
  w->text_pos.x   = x;
  w->text_pos.y   = y;
  w->text_pos_set = val;
}

void wid_set_tile(int depth, Widp w, Tilep tile)
{
  set(w->tiles, depth, tile);
  TRACE_NO_INDENT();
}

void wid_set_tilename(int depth, Widp w, std::string name)
{
  TRACE_NO_INDENT();
  Tilep tile = tile_find(name);
  if (unlikely(! tile)) {
    ERR("Failed to find wid tile [%s]", name.c_str());
  }

  if (unlikely(! w)) {
    DIE("Widget does not exist to set tile %s", name.c_str());
  }

  set(w->tiles, depth, tile);
}

void wid_set_tile(int depth, Widp w, Thingp t)
{
  auto tpp   = t->tp();
  auto tiles = &tpp->tiles;

  auto tile = tile_first(tiles);
  if (tile) {
    if (g_opt_ascii) {
      auto tile = tile_index_to_tile(t->tile_curr);
      if (tile) {
        wid_set_style(w, UI_WID_STYLE_DARK);
        std::wstring text;
        text += tile->ascii_fg_char;
        wid_set_text(w, text);
        wid_set_color(w, WID_COLOR_TEXT_FG, tile->ascii_fg_col_value);
      }
    } else {
      set(w->tiles, depth, tile);
    }
  }
}

//
// Look at all the wid modes and return the most relevent setting
//
color wid_get_color(Widp w, wid_color which)
{
  TRACE_NO_INDENT();
  uint32_t mode = (__typeof__(mode)) wid_get_mode(w); // for c++, no enum walk
  wid_cfg *cfg  = &getref(w->cfg, mode);

  if (cfg->color_set[ which ]) {
    return (cfg->colors[ which ]);
  }

  if ((wid_focus == w) && (wid_over == w)) {
    mode = WID_MODE_OVER;
    cfg  = &getref(w->cfg, mode);
    if (cfg->color_set[ which ]) {
      return (cfg->colors[ which ]);
    }
  }

  mode = WID_MODE_NORMAL;
  cfg  = &getref(w->cfg, mode);
  if (cfg->color_set[ which ]) {
    return (cfg->colors[ which ]);
  }

  return WHITE;
}

int wid_get_style(Widp w)
{
  TRACE_NO_INDENT();
  uint32_t mode = (__typeof__(mode)) wid_get_mode(w); // for c++, no enum walk
  wid_cfg *cfg  = &getref(w->cfg, mode);

  if (cfg->style_set) {
    return (cfg->style);
  }

  if ((wid_focus == w) && (wid_over == w)) {
    mode = WID_MODE_OVER;
    cfg  = &getref(w->cfg, mode);
    if (cfg->style_set) {
      return (cfg->style);
    }
  }

  mode = WID_MODE_NORMAL;
  cfg  = &getref(w->cfg, mode);
  if (cfg->style_set) {
    return (cfg->style);
  }

  return UI_WID_STYLE_NORMAL;
}

void wid_set_style(Widp w, int style)
{
  w->cfg[ wid_get_mode(w) ].style     = style;
  w->cfg[ wid_get_mode(w) ].style_set = true;
}

//
// Look at all the widset modes and return the most relevent setting
//
void wid_set_color(Widp w, wid_color col, color val)
{
  TRACE_NO_INDENT();
  w->cfg[ wid_get_mode(w) ].colors[ col ]    = val;
  w->cfg[ wid_get_mode(w) ].color_set[ col ] = true;
}

void wid_set_focus(Widp w)
{
  TRACE_NO_INDENT();
  //
  // Don't allow focus override if hard focus is set.
  //
  if (w) {
    if (wid_focus_locked) {
      if (wid_get_top_parent(w) != wid_focus_locked) {
        return;
      }
    }

    if (! w->focus_order) {
      return;
    }
  }

  wid_mfocus_begin(w);
}

void wid_unset_focus(void)
{
  TRACE_NO_INDENT();
  wid_mfocus_end();
}

void wid_set_shape_square(Widp w) { w->square = true; }

void wid_set_shape_none(Widp w) { w->square = false; }

void wid_set_active(Widp w)
{
  TRACE_NO_INDENT();
  wid_set_mode(w, WID_MODE_ACTIVE);
}

void wid_focus_lock(Widp w)
{
  TRACE_NO_INDENT();
  if (w) {
    WID_DBG(w, "focus locked");
  }

  wid_focus_locked = w;
}

void wid_unset_focus_lock(void)
{
  TRACE_NO_INDENT();
  wid_focus_locked = nullptr;
}

void wid_set_on_key_down(Widp w, on_key_down_t fn)
{
  TRACE_NO_INDENT();
  w->on_key_down = fn;
}

void wid_set_on_key_up(Widp w, on_key_up_t fn)
{
  TRACE_NO_INDENT();
  w->on_key_up = fn;
}

void wid_set_on_joy_button(Widp w, on_joy_button_t fn)
{
  TRACE_NO_INDENT();
  w->on_joy_button = fn;
}

void wid_set_on_mouse_down(Widp w, on_mouse_down_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_down = fn;
}

void wid_set_on_mouse_held(Widp w, on_mouse_down_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_held = fn;
}

void wid_set_on_mouse_up(Widp w, on_mouse_up_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_up = fn;
}

void wid_set_on_mouse_motion(Widp w, on_mouse_motion_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_motion = fn;
}

void wid_set_on_mouse_focus_begin(Widp w, on_mouse_focus_begin_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_focus_begin = fn;
}

void wid_set_on_mouse_focus_end(Widp w, on_mouse_focus_end_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_focus_end = fn;
}

void wid_set_on_mouse_over_begin(Widp w, on_mouse_over_begin_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_over_begin = fn;
}

void wid_set_on_mouse_over_end(Widp w, on_mouse_over_end_t fn)
{
  TRACE_NO_INDENT();
  w->on_mouse_over_end = fn;
}

void wid_set_on_destroy(Widp w, on_destroy_t fn)
{
  TRACE_NO_INDENT();
  w->on_destroy = fn;
}

void wid_set_on_destroy_begin(Widp w, on_destroy_t fn)
{
  TRACE_NO_INDENT();
  w->on_destroy_begin = fn;
}

void wid_set_on_display(Widp w, on_display_t fn)
{
  TRACE_NO_INDENT();
  w->on_display = fn;
}

void wid_set_on_tick(Widp w, on_tick_t fn)
{
  TRACE_NO_INDENT();
  w->on_tick = fn;
  wid_tree5_tick_wids_insert(w);
}

void wid_set_on_tick_post_display(Widp w, on_tick_post_display_t fn)
{
  TRACE_NO_INDENT();
  w->on_tick_post_display = fn;
  wid_tree6_tick_post_display_wids_insert(w);
}

//
// Remove this wid from any trees it is in.
//
static void wid_tree_detach(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  wid_tree_remove(w);
}

//
// Add back to all trees.
//
static void wid_tree_attach(Widp w)
{
  TRACE_NO_INDENT();
  IF_DEBUG3 { verify(MTYPE_WID, w); }
  wid_key_map_location *root;

  if (w->in_tree_root) {
    DIE("Wid is already attached");
  }

  if (! w->parent) {
    root = &wid_top_level;
  } else {
    IF_DEBUG3 { verify(MTYPE_WID, w->parent); }
    root = &w->parent->children_display_sorted;
  }

  if (! root) {
    DIE("No root");
  }

  auto result = root->insert(std::make_pair(w->key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] failed", wid_get_name(w).c_str());
  }

  w->in_tree_root = root;
}

static void wid_tree_insert(Widp w)
{
  TRACE_NO_INDENT();

  if (w->in_tree_root) {
    DIE("Wid is already inserted");
  }

  wid_key_map_location *root;

  //
  // Get a wid sort ID.
  //
  w->key.key = ++key;

  if (! w->parent) {
    root = &wid_top_level;
  } else {
    verify(MTYPE_WID, w->parent);
    root = &w->parent->children_display_sorted;
  }

  if (! root) {
    DIE("No root");
  }

  auto result = root->insert(std::make_pair(w->key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] failed", wid_get_name(w).c_str());
  }

  w->in_tree_root = root;
}

static void wid_tree_global_unsorted_insert(Widp w)
{
  TRACE_NO_INDENT();
  static WidKeyType key;

  if (w->in_tree_global_unsorted_root) {
    DIE("Wid is already in the global tree");
  }

  auto root = &wid_global;

  key.val++;

  w->tree_global_key = key;
  auto result        = root->insert(std::make_pair(w->tree_global_key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] tree_global failed", wid_get_name(w).c_str());
  }

  w->in_tree_global_unsorted_root = root;
}

static void wid_tree2_unsorted_insert(Widp w)
{
  TRACE_NO_INDENT();

  if (w->in_tree2_unsorted_root) {
    DIE("Wid is already in the in_tree2_unsorted_root");
  }

  wid_key_map_int *root;

  if (! w->parent) {
    root = &wid_top_level2;
  } else {
    root = &w->parent->tree2_children_unsorted;
  }

  w->tree2_key = ++key;
  auto result  = root->insert(std::make_pair(w->tree2_key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] tree2 failed", wid_get_name(w).c_str());
  }

  w->in_tree2_unsorted_root = root;
}

static void wid_tree3_moving_wids_insert(Widp w)
{
  TRACE_NO_INDENT();
  if (w->in_tree3_moving_wids) {
    return;
  }

  if (wid_exiting) {
    return;
  }

  static uint64_t  key;
  wid_key_map_int *root = &wid_top_level3;

  w->tree3_key = ++key;
  auto result  = root->insert(std::make_pair(w->tree3_key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] tree3 failed", wid_get_name(w).c_str());
  }

  w->in_tree3_moving_wids = root;
}

static void wid_tree4_wids_being_destroyed_insert(Widp w)
{
  TRACE_NO_INDENT();
  if (w->in_tree4_wids_being_destroyed) {
    return;
  }

  if (wid_exiting) {
    return;
  }

  wid_key_map_int *root;

  root = &wid_top_level4;

  w->tree4_key = ++key;
  auto result  = root->insert(std::make_pair(w->tree4_key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] tree4 failed", wid_get_name(w).c_str());
  }

  w->in_tree4_wids_being_destroyed = root;
}

static void wid_tree5_tick_wids_insert(Widp w)
{
  TRACE_NO_INDENT();
  if (w->in_tree5_tick_wids) {
    return;
  }

  if (wid_exiting) {
    return;
  }

  wid_key_map_int *root;

  root = &wid_tick_top_level;

  w->tree5_key = ++key;
  auto result  = root->insert(std::make_pair(w->tree5_key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] tree5 failed", wid_get_name(w).c_str());
  }

  w->in_tree5_tick_wids = root;
}

static void wid_tree6_tick_post_display_wids_insert(Widp w)
{
  TRACE_NO_INDENT();
  if (w->in_tree6_tick_wids_post_display) {
    return;
  }

  if (wid_exiting) {
    return;
  }

  wid_key_map_int *root;

  root = &wid_tick_post_display_top_level;

  w->tree6_key = ++key;
  auto result  = root->insert(std::make_pair(w->tree6_key, w));
  if (result.second == false) {
    DIE("Wid insert name [%s] tree6 failed", wid_get_name(w).c_str());
  }

  w->in_tree6_tick_wids_post_display = root;
}

static void wid_tree_remove(Widp w)
{
  TRACE_NO_INDENT();
  wid_key_map_location *root;

  IF_DEBUG3 { verify(MTYPE_WID, w); }

  root = w->in_tree_root;
  if (! root) {
    return;
  }

  auto result = root->find(w->key);
  if (result == root->end()) {
    DIE("Wid tree did not find wid %s hence cannot remove it", wid_get_name(w).c_str());
  }

  root->erase(w->key);

  w->in_tree_root = nullptr;
}

static void wid_tree2_unsorted_remove(Widp w)
{
  TRACE_NO_INDENT();
  auto root = w->in_tree2_unsorted_root;
  if (! root) {
    return;
  }

  auto result = root->find(w->tree2_key);
  if (result == root->end()) {
    DIE("Wid tree2 did not find wid");
  }
  root->erase(w->tree2_key);

  w->in_tree2_unsorted_root = nullptr;
}

static void wid_tree_global_unsorted_remove(Widp w)
{
  TRACE_NO_INDENT();
  auto root = w->in_tree_global_unsorted_root;
  if (! root) {
    return;
  }

  auto result = root->find(w->tree_global_key);
  if (result == root->end()) {
    DIE("Wid tree_global did not find wid");
  }
  root->erase(w->tree_global_key);

  w->in_tree_global_unsorted_root = nullptr;
}

WidKeyType wid_unsorted_get_key(Widp w)
{
  TRACE_NO_INDENT();
  auto root = &wid_global;

  auto result = root->find(w->tree_global_key);
  if (result == root->end()) {
    DIE("Wid unsorted did not find wid");
  }

  w = result->second;

  return (w->tree_global_key);
}

static void wid_tree3_moving_wids_remove(Widp w)
{
  TRACE_NO_INDENT();
  auto root = w->in_tree3_moving_wids;
  if (! root) {
    return;
  }

  auto result = root->find(w->tree3_key);
  if (result == root->end()) {
    DIE("Wid tree3 did not find wid");
  }
  root->erase(w->tree3_key);

  w->in_tree3_moving_wids = nullptr;
}

static void wid_tree4_wids_being_destroyed_remove(Widp w)
{
  TRACE_NO_INDENT();
  auto root = w->in_tree4_wids_being_destroyed;
  if (! root) {
    return;
  }

  auto result = root->find(w->tree4_key);
  if (result == root->end()) {
    DIE("Wid tree4 did not find wid");
  }
  root->erase(w->tree4_key);

  w->in_tree4_wids_being_destroyed = nullptr;
}

static void wid_tree5_tick_wids_remove(Widp w)
{
  TRACE_NO_INDENT();
  auto root = w->in_tree5_tick_wids;
  if (! root) {
    return;
  }

  auto result = root->find(w->tree5_key);
  if (result == root->end()) {
    DIE("Wid tree5 did not find wid");
  }
  root->erase(w->tree5_key);

  w->in_tree5_tick_wids = nullptr;
  w->on_tick            = 0;
}

static void wid_tree6_tick_post_display_wids_remove(Widp w)
{
  TRACE_NO_INDENT();
  auto root = w->in_tree6_tick_wids_post_display;
  if (! root) {
    return;
  }

  auto result = root->find(w->tree6_key);
  if (result == root->end()) {
    DIE("Wid tree6 did not find wid");
  }
  root->erase(w->tree6_key);

  w->in_tree6_tick_wids_post_display = nullptr;
  w->on_tick_post_display            = 0;
}

//
// Initialize a wid with basic settings
//
static Widp wid_new(Widp parent)
{
  TRACE_NO_INDENT();
  auto w = new Wid();

  w->parent     = parent;
  w->ts_created = wid_time;

  wid_tree_insert(w);
  wid_tree2_unsorted_insert(w);
  wid_tree_global_unsorted_insert(w);

  //
  // Give some lame 3d to the wid
  //
  wid_set_mode(w, WID_MODE_NORMAL);

  w->visible = true;
  wid_set_style(w, UI_WID_STYLE_SOLID_NONE);
  WID_DBG(w, "new");

  return w;
}

static Widp wid_new(void)
{
  TRACE_NO_INDENT();
  auto w = new Wid();

  w->ts_created = wid_time;

  wid_tree_insert(w);
  wid_tree2_unsorted_insert(w);
  wid_tree_global_unsorted_insert(w);

  //
  // Give some lame 3d to the wid
  //
  wid_set_mode(w, WID_MODE_NORMAL);

  w->visible = true;
  wid_set_style(w, UI_WID_STYLE_SOLID_NONE);
  WID_DBG(w, "new");

  return w;
}

static void wid_destroy_immediate_internal(Widp w)
{
  TRACE_NO_INDENT();
  wid_tree3_moving_wids_remove(w);
  wid_tree4_wids_being_destroyed_remove(w);
  wid_tree5_tick_wids_remove(w);
  wid_tree6_tick_post_display_wids_remove(w);

  if (w->on_destroy) {
    (w->on_destroy)(w);
  }

  if (wid_focus == w) {
    wid_mfocus_end();
  }

  if (wid_focus_locked == w) {
    wid_focus_locked = nullptr;
  }

  //
  // This can easily lead to recursion. Do we need it?
  //
  // if (wid_over == w) {
  //     wid_mouse_over_end();
  // }

  if (wid_moving == w) {
    wid_mouse_motion_end();
  }

  if (w->scrollbar_vert) {
    w->scrollbar_vert->scrollbar_owner = nullptr;
  }

  if (w->scrollbar_horiz) {
    w->scrollbar_horiz->scrollbar_owner = nullptr;
  }

  if (w->scrollbar_owner) {
    if (w->scrollbar_owner->scrollbar_vert == w) {
      w->scrollbar_owner->scrollbar_vert = nullptr;
    }

    if (w->scrollbar_owner->scrollbar_horiz == w) {
      w->scrollbar_owner->scrollbar_horiz = nullptr;
    }
  }

  {
    auto iter = w->children_display_sorted.begin();

    while (iter != w->children_display_sorted.end()) {
      auto child = iter->second;
      wid_destroy_immediate(child);
      iter = w->children_display_sorted.begin();
    }
  }

  {
    auto iter = w->tree2_children_unsorted.begin();

    while (iter != w->tree2_children_unsorted.end()) {
      auto child = iter->second;
      wid_destroy_immediate(child);
      iter = w->tree2_children_unsorted.begin();
    }
  }
}

static void wid_destroy_immediate(Widp w)
{
  TRACE_NO_INDENT();
  verify(MTYPE_WID, w);
  WID_DBG(w, "destroy immediate");

  //
  // If removing a top level widget, choose a new focus.
  //
  if (! w->parent) {
    wid_find_top_focus();
  } else {
    verify(MTYPE_WID, w->parent);
  }

  wid_tree_detach(w);

  wid_tree2_unsorted_remove(w);
  wid_tree_global_unsorted_remove(w);

  wid_destroy_immediate_internal(w);

  if (w == wid_focus_locked) {
    wid_focus_locked = nullptr;
  }

  if (w == wid_focus) {
    wid_focus = nullptr;
  }

  if (w == wid_over) {
    wid_over = nullptr;
    if (! wid_ignore_events(w)) {
      wid_last_over_event = time_ms_cached();
    }
  }

  if (w == wid_moving) {
    wid_moving = nullptr;
  }

  for (auto which = 0; which < WID_THING_ID_MAX_CONTEXT; which++) {
    WID_DBG(w, "destroy thing reference");
    wid_unset_thing_id_context(w, which);
  }

  for (auto x = 0; x < TERM_WIDTH; x++) {
    for (auto y = 0; y < TERM_HEIGHT; y++) {
      if (get(wid_on_screen_at, x, y) == w) {
        set(wid_on_screen_at, x, y, static_cast< Widp >(0));
      }
    }
  }

  delete w;
}

static void wid_destroy_delay(Widp *wp, int delay)
{
  TRACE_NO_INDENT();
  int tlx;
  int tly;
  int brx;
  int bry;

  if (! wp) {
    return;
  }

  auto w = *wp;

  if (unlikely(! w)) {
    return;
  }

  WID_DBG(w, "destroy delay");

  (*wp) = nullptr;

  if (w->being_destroyed) {
    if (delay) {
      return;
    }
  }

  w->being_destroyed = true;
  wid_tree4_wids_being_destroyed_insert(w);

  if (wid_focus == w) {
    wid_mfocus_end();
  }

  //
  // This can easily lead to recursion. Do we need it?
  //
  // if (wid_over == w) {
  //     wid_mouse_over_end();
  // }

  if (wid_moving == w) {
    wid_mouse_motion_end();
  }

  for (auto &iter : w->tree2_children_unsorted) {
    auto child = iter.second;
    wid_destroy(&child);
  }

  if (! w->parent) {
    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);
  }

  if (w->on_destroy_begin) {
    (w->on_destroy_begin)(w);
  }

  //
  // Make sure it stops tick right now as client pointers this widget
  // might use in the ticker may no longer be valid.
  //
  wid_tree5_tick_wids_remove(w);
  wid_tree6_tick_post_display_wids_remove(w);
}

void wid_destroy(Widp *wp)
{
  TRACE_NO_INDENT();
  wid_destroy_delay(wp, wid_destroy_delay_ms);
}

void wid_destroy_nodelay(Widp *wp)
{
  TRACE_NO_INDENT();
  wid_destroy_delay(wp, 0);
}

void wid_destroy_in(Widp w, uint32_t ms)
{
  TRACE_NO_INDENT();
  w->destroy_when = wid_time + ms;

  wid_tree4_wids_being_destroyed_insert(w);
}

//
// Initialize a top level wid with basic settings
//
Widp wid_new_window(std::string name)
{
  TRACE_NO_INDENT();
  Widp w = wid_new();

  w->to_string = string_sprintf("%s[%p]", name.c_str(), w);

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_name(w, name);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_shape_square(w);

  //
  // Raise it so if there were other widgets with the same parent
  // then this will be in front
  //
  wid_raise(w);
  WID_DBG(w, "new");

  return w;
}

//
// Initialize a top level wid with basic settings
//
Widp wid_new_container(Widp parent, std::string name)
{
  TRACE_NO_INDENT();
  Widp w = wid_new(parent);

#ifdef ENABLE_DEBUG_UI
#ifdef ENABLE_DEBUG_UI2
  w->to_string = string_sprintf("%s[%p] (parent %s[%p])", name.c_str(), w, parent->to_string.c_str(), parent);
#else
  w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_name(w, name);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);
  wid_set_shape_square(w);

  //
  // Raise it so if there were other widgets with the same parent
  // then this will be in front
  //
  wid_raise(w);
  WID_DBG(w, "new");

  return w;
}

//
// Initialize a top level wid with basic settings
//
Widp wid_new_square_window(std::string name)
{
  TRACE_NO_INDENT();
  Widp w = wid_new();

  w->to_string = string_sprintf("%s[%p]", name.c_str(), w);

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_name(w, name);
  wid_set_shape_square(w);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  //
  // Raise it so if there were other widgets with the same parent
  // then this will be in front
  //
  wid_raise(w);
  WID_DBG(w, "new");

  return w;
}

Widp wid_new_square_button(Widp parent, std::string name)
{
  TRACE_NO_INDENT();
  if (! parent) {
    ERR("No parent");
  }

  Widp w = wid_new(parent);

#ifdef ENABLE_DEBUG_UI
#ifdef ENABLE_DEBUG_UI2
  w->to_string = string_sprintf("%s[%p] (parent %s[%p])", name.c_str(), w, parent->to_string.c_str(), parent);
#else
  w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_name(w, name);
  wid_set_shape_square(w);

  wid_set_mode(w, WID_MODE_OVER);
  wid_set_color(w, WID_COLOR_BG, GRAY90);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  //
  // Raise it so if there were other widgets with the same parent
  // then this will be in front
  //
  wid_raise(w);
  WID_DBG(w, "new");

  return w;
}

Widp wid_new_plain(Widp parent, std::string name)
{
  TRACE_NO_INDENT();
  if (! parent) {
    ERR("No parent");
  }

  Widp w = wid_new(parent);

#ifdef ENABLE_DEBUG_UI
#ifdef ENABLE_DEBUG_UI2
  w->to_string = string_sprintf("%s[%p] (parent %s[%p])", name.c_str(), w, parent->to_string.c_str(), parent);
#else
  w->to_string = string_sprintf("%s[%p]", name.c_str(), w);
#endif
#endif

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_name(w, name);
  wid_set_shape_square(w);

  wid_set_mode(w, WID_MODE_OVER);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  //
  // Raise it so if there were other widgets with the same parent
  // then this will be in front
  //
  wid_raise(w);
  WID_DBG(w, "new");

  return w;
}

//
// Initialize a wid with basic settings
//
static Widp wid_new_scroll_trough(Widp parent)
{
  TRACE_NO_INDENT();
  if (! parent) {
    ERR("No parent");
  }

  Widp w = wid_new(parent);

  w->to_string = string_sprintf("[%p] scroll trough (parent %s[%p])", w, parent->to_string.c_str(), parent);

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_mode(w, WID_MODE_NORMAL);
  {
    color c = GRAY90;
    wid_set_color(w, WID_COLOR_BG, c);
  }

  wid_set_on_mouse_down(w, wid_scroll_trough_mouse_down);
  wid_set_on_mouse_motion(w, wid_scroll_trough_mouse_motion);
  wid_set_shape_square(w);

  wid_set_mode(w, WID_MODE_OVER);
  wid_set_color(w, WID_COLOR_BG, GRAY90);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  wid_set_style(w, UI_WID_STYLE_DARK);
  WID_DBG(w, "new");

  return w;
}

//
// Initialize a wid with basic settings
//
static Widp wid_new_scroll_bar(Widp parent, std::string name, Widp scrollbar_owner, uint8_t vertical)
{
  TRACE_NO_INDENT();
  if (! parent) {
    ERR("No parent");
  }

  Widp w = wid_new(parent);

  if (vertical) {
    w->to_string = string_sprintf("%s, %s[%p]", name.c_str(), "vert scroll bar", w);
  } else {
    w->to_string = string_sprintf("%s, %s[%p]", name.c_str(), "horiz scroll bar", w);
  }

  WID_DBG(w, "%s", __FUNCTION__);

  wid_set_name(w, name);

  wid_set_mode(w, WID_MODE_ACTIVE);
  {
    color c = GREEN;
    wid_set_color(w, WID_COLOR_BG, c);
  }

  wid_set_mode(w, WID_MODE_NORMAL);
  {
    color c = GRAY50;
    wid_set_color(w, WID_COLOR_BG, c);
  }

  wid_set_moveable(w, true);
  wid_set_moveable_bounded(w, true);

  if (vertical) {
    wid_set_moveable_vert(w, true);
    wid_set_moveable_horiz(w, false);
    scrollbar_owner->scrollbar_vert = w;
  } else {
    wid_set_moveable_horiz(w, true);
    wid_set_moveable_vert(w, false);
    scrollbar_owner->scrollbar_horiz = w;
  }

  w->scrollbar_owner = scrollbar_owner;

  wid_set_shape_square(w);

  wid_set_mode(w, WID_MODE_OVER);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  wid_set_mode(w, WID_MODE_NORMAL);
  wid_set_color(w, WID_COLOR_BG, WHITE);
  wid_set_color(w, WID_COLOR_TEXT_FG, WHITE);

  wid_set_style(w, UI_WID_STYLE_DARK);
  WID_DBG(w, "new");

  return w;
}

Widp wid_new_vert_scroll_bar(Widp parent, std::string name, Widp scrollbar_owner)
{
  TRACE_NO_INDENT();
  if (! parent) {
    ERR("No parent");
  }

  point tl;
  point br;

  int tlx;
  int tly;
  int brx;
  int bry;
  int ptlx;
  int ptly;
  int pbrx;
  int pbry;

  //
  // Make the trough line up with the scrolling window.
  //
  wid_get_abs_coords(parent, &ptlx, &ptly, &pbrx, &pbry);
  wid_get_abs_coords(scrollbar_owner, &tlx, &tly, &brx, &bry);

  tl.x = tlx - ptlx + wid_get_width(scrollbar_owner);
  br.x = tl.x;

  tl.y = tly - ptly;
  br.y = tly - ptly + wid_get_height(scrollbar_owner) - 1;

  Widp trough = wid_new_scroll_trough(parent);
  wid_set_pos(trough, tl, br);
  wid_set_shape_square(trough);
  wid_set_style(trough, UI_WID_STYLE_VERT_SCROLL_DARK);

  {
    fpoint tl(0, 0);
    fpoint br(1, 1);
    Widp   scrollbar = wid_new_scroll_bar(trough, name, scrollbar_owner, true);
    wid_set_pos_pct(scrollbar, tl, br);

    wid_update_internal(scrollbar);
    wid_visible(wid_get_parent(scrollbar));
    wid_visible(scrollbar);
    wid_set_mode(scrollbar, WID_MODE_ACTIVE);
    wid_set_style(scrollbar, UI_WID_STYLE_VERT_LIGHT);
    wid_set_mode(scrollbar, WID_MODE_NORMAL);
    wid_set_style(scrollbar, UI_WID_STYLE_VERT_DARK);

    trough->is_scrollbar_vert_trough = true;
    scrollbar->is_scrollbar_vert     = true;

    return scrollbar;
  }
}

Widp wid_new_horiz_scroll_bar(Widp parent, std::string name, Widp scrollbar_owner)
{
  TRACE_NO_INDENT();
  if (! parent) {
    ERR("No parent");
  }

  point tl;
  point br;

  int tlx;
  int tly;
  int brx;
  int bry;
  int ptlx;
  int ptly;
  int pbrx;
  int pbry;

  //
  // Make the trough line up with the scrolling window.
  //
  wid_get_abs_coords(parent, &ptlx, &ptly, &pbrx, &pbry);
  wid_get_abs_coords(scrollbar_owner, &tlx, &tly, &brx, &bry);

  tl.x = tlx - ptlx;
  br.x = tlx - ptlx + wid_get_width(scrollbar_owner) - 1;

  tl.y = tly - ptly + wid_get_height(scrollbar_owner);
  br.y = tl.y;

  Widp trough = wid_new_scroll_trough(parent);
  wid_set_pos(trough, tl, br);
  wid_set_shape_square(trough);
  wid_set_style(trough, UI_WID_STYLE_HORIZ_SCROLL_DARK);

  {
    fpoint tl(0, 0);
    fpoint br(1, 1);
    Widp   scrollbar = wid_new_scroll_bar(trough, name, scrollbar_owner, false);
    wid_set_pos_pct(scrollbar, tl, br);

    wid_update_internal(scrollbar);
    wid_visible(wid_get_parent(scrollbar));
    wid_visible(scrollbar);
    wid_set_style(scrollbar, UI_WID_STYLE_HORIZ_SCROLL_LIGHT);

    trough->is_scrollbar_horiz_trough = true;
    scrollbar->is_scrollbar_horiz     = true;

    return scrollbar;
  }
}

static void wid_raise_internal(Widp w)
{
  TRACE_NO_INDENT();

  verify(MTYPE_WID, w);
  if (w->do_not_raise) {
    return;
  }

  if (wid_moving != w) {
    wid_mouse_motion_end();
  }

  if (wid_get_top_parent(wid_moving) != w) {
    wid_mouse_motion_end();
  }

  wid_tree_detach(w);
  w->key.priority = ++wid_highest_priority;
  wid_tree_attach(w);
}

static void wid_raise_override(Widp parent)
{
  TRACE_NO_INDENT();
  //
  // If some widget wants to be on top, let it.
  //
  if (parent->do_not_lower) {
    wid_raise_internal(parent);
  }

  for (auto &iter : parent->children_display_sorted) {
    auto w = iter.second;

    if (w->do_not_lower) {
      wid_raise_internal(w);
      break;
    }

    wid_raise_override(w);
  }
}

void wid_raise(Widp w_in)
{
  TRACE_NO_INDENT();
  if (! w_in) {
    return;
  }

  wid_raise_internal(w_in);

  //
  // If some widget wants to be on top, let it.
  //
  std::vector< Widp > worklist;
  for (auto &iter : wid_top_level) {
    auto w = iter.second;
    worklist.push_back(w);
  }

  for (auto &w : worklist) {
    wid_raise_override(w);
  }

  wid_find_top_focus();

  //
  // If we were hovering over a window and it was replaced, we need to fake
  // a mouse movement so we know we are still over it.
  //
  if (! w_in->parent) {
    wid_update_mouse();
  }
}

static void wid_lower_internal(Widp w)
{
  TRACE_NO_INDENT();

  verify(MTYPE_WID, w);

  if (w->do_not_lower) {
    return;
  }

  if (wid_moving == w) {
    wid_mouse_motion_end();
  }

  if (wid_get_top_parent(wid_moving) == w) {
    wid_mouse_motion_end();
  }

  wid_tree_detach(w);
  w->key.priority = --wid_lowest_priority;
  wid_tree_attach(w);
}

void wid_lower(Widp w_in)
{
  TRACE_NO_INDENT();
  if (! w_in) {
    return;
  }

  wid_lower_internal(w_in);

  //
  // If some widget wants to be on top, let it.
  //
  for (auto &iter : wid_top_level) {
    auto w = iter.second;
    if (w->do_not_raise) {
      wid_lower_internal(w);
      break;
    }
  }

  wid_find_top_focus();

  //
  // If we were hovering over a window and it was replaced, we need to fake
  // a mouse movement so we know we are still over it.
  //
  if (! w_in->parent && ! w_in->children_display_sorted.empty()) {
    wid_update_mouse();
  }
}

void wid_toggle_hidden(Widp w)
{
  TRACE_NO_INDENT();
  if (w->hidden) {
    wid_visible(w);
  } else {
    wid_hide(w);
  }
}

static void wid_find_first_child_focus(Widp w, Widp *best)
{
  TRACE_NO_INDENT();
  if (w->focus_order) {
    if (! *best) {
      *best = w;
    } else if (w->focus_order < (*best)->focus_order) {
      *best = w;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    wid_find_first_child_focus(child, best);
  }
}

static void wid_find_first_focus(void)
{
  TRACE_NO_INDENT();
  Widp best {};

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;
    if (wid_ignore_for_focus(w)) {
      continue;
    }

    best = nullptr;
    wid_find_first_child_focus(w, &best);
    if (best) {
      wid_set_focus(best);
      return;
    }
  }
}

static void wid_find_specific_child_focus(Widp w, Widp *best, uint8_t focus_order)
{
  TRACE_NO_INDENT();
  if (w->focus_order) {
    if (w->focus_order == focus_order) {
      *best = w;
      return;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    wid_find_specific_child_focus(child, best, focus_order);
  }
}

static Widp wid_find_top_wid_focus(Widp w)
{
  TRACE_NO_INDENT();
  Widp best {};

  if (wid_ignore_for_focus(w)) {
    return best;
  }

  //
  // First time we've looked at this widget, hunt for the first focus.
  //
  if (! w->focus_last) {
    wid_find_first_child_focus(w, &best);
    if (best) {
      return best;
    }
  }

  wid_find_specific_child_focus(w, &best, w->focus_last);
  if (best) {
    return best;
  }

  return best;
}

static void wid_find_top_focus(void)
{
  TRACE_NO_INDENT();
  Widp best {};

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;
    if (wid_ignore_for_focus(w)) {
      continue;
    }

    best = nullptr;

    //
    // First time we've looked at this widget, hunt for the first focus.
    //
    if (! w->focus_last) {
      wid_find_first_child_focus(w, &best);
      if (best) {
        wid_set_focus(best);
        return;
      }
    }

    wid_find_specific_child_focus(w, &best, w->focus_last);
    if (best) {
      wid_set_focus(best);
      return;
    }
  }

  wid_find_first_focus();
}

static void wid_find_last_child_focus(Widp w, Widp *best)
{
  TRACE_NO_INDENT();
  if (w->focus_order) {
    if (! *best) {
      *best = w;
    } else if (w->focus_order > (*best)->focus_order) {
      *best = w;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    wid_find_last_child_focus(child, best);
  }
}

Widp wid_get_focus(Widp w)
{
  TRACE_NO_INDENT();
  Widp best {};

  if (wid_focus) {
    if (wid_get_top_parent(wid_focus) == wid_get_top_parent(w)) {
      return wid_focus;
    }
  }

  if (! w->focus_last) {
    best = wid_find_top_wid_focus(wid_get_top_parent(w));
    if (best) {
      return best;
    }
  }

  wid_find_specific_child_focus(w, &best, w->focus_last);

  return best;
}

static void wid_find_last_focus(void)
{
  TRACE_NO_INDENT();
  Widp best {};

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;
    if (wid_ignore_for_focus(w)) {
      continue;
    }

    best = nullptr;
    wid_find_last_child_focus(w, &best);
    if (best) {
      wid_set_focus(best);
      return;
    }
  }
}

static void wid_find_next_child_focus(Widp w, Widp *best)
{
  TRACE_NO_INDENT();
  if (w->focus_order) {
    if (*best) {
      if ((w->focus_order < (*best)->focus_order) && (w->focus_order > wid_focus->focus_order)) {
        *best = w;
      }
    } else if (w->focus_order > wid_focus->focus_order) {
      *best = w;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    wid_find_next_child_focus(child, best);
  }
}

static void wid_find_next_focus(void)
{
  TRACE_NO_INDENT();
  Widp best {};

  if (! wid_focus) {
    wid_find_first_focus();
    return;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_ignore_for_focus(w)) {
      continue;
    }

    if (! w->focus_last) {
      continue;
    }

    wid_find_next_child_focus(w, &best);
    if (best) {
      wid_set_focus(best);
      return;
    }

    wid_find_first_focus();
    break;
  }
}

static void wid_find_prev_child_focus(Widp w, Widp *best)
{
  TRACE_NO_INDENT();
  if (w->focus_order) {
    if (*best) {
      if ((w->focus_order > (*best)->focus_order) && (w->focus_order < wid_focus->focus_order)) {
        *best = w;
      }
    } else if (w->focus_order < wid_focus->focus_order) {
      *best = w;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    wid_find_prev_child_focus(child, best);
  }
}

static void wid_find_prev_focus(void)
{
  TRACE_NO_INDENT();
  Widp best {};

  if (! wid_focus) {
    wid_find_first_focus();
    return;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_ignore_for_focus(w)) {
      continue;
    }

    if (! w->focus_last) {
      continue;
    }

    wid_find_prev_child_focus(w, &best);
    if (best) {
      wid_set_focus(best);
      return;
    }

    wid_find_last_focus();
    break;
  }
}

Widp wid_find(Widp w, const std::string &name)
{
  TRACE_NO_INDENT();
  if (! strcasecmp(w->name.c_str(), name.c_str())) {
    return w;
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    Widp ret {};

    ret = wid_find(child, name);
    if (ret) {
      return ret;
    }
  }
  return nullptr;
}

static void wid_find_all_(Widp w, const std::string &name, std::list< Widp > &out)
{
  TRACE_NO_INDENT();
  if (! strcasecmp(w->name.c_str(), name.c_str())) {
    out.push_back(w);
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    wid_find_all_(child, name, out);
  }
}

std::list< Widp > wid_find_all(Widp w, const std::string &name)
{
  std::list< Widp > out;
  wid_find_all_(w, name, out);
  return out;
}

static void wid_find_all_containing_(Widp w, const std::string &name, std::list< Widp > &out)
{
  TRACE_NO_INDENT();
  if (strstr(w->name.c_str(), name.c_str())) {
    out.push_back(w);
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    wid_find_all_containing_(child, name, out);
  }
}

std::list< Widp > wid_find_all_containing(Widp w, const std::string &name)
{
  std::list< Widp > out;
  wid_find_all_containing_(w, name, out);
  return out;
}

std::list< Widp > wid_find_all_containing(const std::string &name)
{
  std::list< Widp > out;
  TRACE_NO_INDENT();
  for (auto &iter : wid_top_level) {
    auto w = iter.second;
    auto r = wid_find(w, name);
    if (r) {
      wid_find_all_containing_(r, name, out);
    }
  }
  return out;
}

Widp wid_find(const std::string &name)
{
  TRACE_NO_INDENT();
  for (auto &iter : wid_top_level) {
    auto w = iter.second;
    auto r = wid_find(w, name);
    if (r) {
      return r;
    }
  }
  // DBG3("Wid [%s] not found", name.c_str());
  return nullptr;
}

static void wid_find_all_at(Widp w, std::list< Widp > &out, const point p)
{
  TRACE_NO_INDENT();

  for (auto &iter : w->children_display_sorted) {
    auto c = iter.second;
    wid_find_all_at(c, out, p);
    if ((p.x < c->abs_tl.x) || (p.y < c->abs_tl.y) || (p.x > c->abs_br.x) || (p.y > c->abs_br.y)) {
      continue;
    }
    out.push_back(c);
  }
}

std::list< Widp > wid_find_all_at(const point p)
{
  std::list< Widp > out;

  TRACE_NO_INDENT();
  for (auto &iter : wid_top_level) {
    auto w = iter.second;
    if ((p.x < w->abs_tl.x) || (p.y < w->abs_tl.y) || (p.x > w->abs_br.x) || (p.y > w->abs_br.y)) {
      continue;
    }

    wid_find_all_at(w, out, p);
    out.push_back(w);
  }
  return out;
}

void wid_always_hidden(Widp w, uint8_t value)
{
  TRACE_NO_INDENT();
  w->always_hidden = value;
}

void wid_visible(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return;
  }

  w->visible = true;
  w->hidden  = false;

  std::vector< Widp > worklist;
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    wid_visible(child);
  }

  wid_find_top_focus();
}

void wid_this_visible(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return;
  }

  w->visible = true;
  w->hidden  = false;
}

void wid_hide(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return;
  }

  w->hidden  = true;
  w->visible = false;

  if (wid_over == w) {
    wid_mouse_over_end();
  }

  if (wid_moving == w) {
    wid_mouse_motion_end();
  }

  if (wid_get_top_parent(wid_over) == w) {
    wid_mouse_over_end();
  }

  if (wid_get_top_parent(wid_moving) == w) {
    wid_mouse_motion_end();
  }

  if (w == wid_focus) {
    wid_find_top_focus();
  }

  std::vector< Widp > worklist;
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    wid_hide(child);
  }
}

static uint8_t wid_scroll_trough_mouse_down(Widp w, int x, int y, uint32_t button)
{
  TRACE_NO_INDENT();
  int dx;
  int dy;

  std::vector< Widp > worklist;
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    worklist.push_back(child);
  }

  for (auto &child : worklist) {
    dx = 0;
    dy = 0;

    if (x < wid_get_tl_x(child)) {
      dx = -1;
    }

    if (x > wid_get_tl_x(child)) {
      dx = 1;
    }

    if (y < wid_get_tl_y(child)) {
      dy = -1;
    }

    if (y > wid_get_tl_y(child)) {
      dy = 1;
    }

    if (dx || dy) {
      wid_set_mode(child, WID_MODE_ACTIVE);
    }

    if (! wid_get_moveable_horiz(child)) {
      dx = 0;
    }

    if (! wid_get_moveable_vert(child)) {
      dy = 0;
    }

    wid_move_delta(child, dx, dy);
  }

  return true;
}

static uint8_t wid_scroll_trough_mouse_motion(Widp w, int x, int y, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  int dx;
  int dy;

  if ((SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(0, 0)) || wheely || wheelx) {

    dy = rely ? rely : -wheely;

    dx = relx ? relx : -wheelx;

    if (dx < 0) {
      dx = -1;
    }
    if (dy < 0) {
      dy = -1;
    }
    if (dx > 0) {
      dx = 1;
    }
    if (dy > 0) {
      dy = 1;
    }
  } else {
    return false;
  }

  std::vector< Widp > worklist;
  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;
    worklist.push_back(child);
  }

  for (auto &child : worklist) {
    if (dx || dy) {
      wid_set_mode(child, WID_MODE_ACTIVE);
    }

    if (! wid_get_moveable_horiz(child)) {
      dx = 0;
    }

    if (! wid_get_moveable_vert(child)) {
      dy = 0;
    }

    wid_move_delta(child, dx, dy);
  }

  return true;
}

static void wid_adjust_scrollbar(Widp scrollbar, Widp owner)
{
  TRACE_NO_INDENT();

  double  height       = wid_get_height(owner);
  double  width        = wid_get_width(owner);
  double  child_height = 0;
  double  child_width  = 0;
  double  scrollbar_width;
  double  scrollbar_height;
  double  trough_height;
  double  trough_width;
  double  miny = 0;
  double  maxy = 0;
  double  minx = 0;
  double  maxx = 0;
  double  pct;
  uint8_t first = true;

  //
  // Find out the space that the children take up then use this to
  // adjust the scrollbar dimensions.
  //
  {
    for (auto &iter : owner->tree2_children_unsorted) {
      auto child = iter.second;

      int tl_x, tl_y, br_x, br_y;

      wid_get_tl_x_tl_y_br_x_br_y(child, &tl_x, &tl_y, &br_x, &br_y);

      if (first) {
        minx  = tl_x;
        miny  = tl_y;
        maxx  = br_x;
        maxy  = br_y;
        first = false;
        continue;
      }

      if (tl_x < minx) {
        minx = tl_x;
      }

      if (tl_y < miny) {
        miny = tl_y;
      }

      if (br_x > maxx) {
        maxx = br_x;
      }

      if (br_y > maxy) {
        maxy = br_y;
      }
    }
  }

  TRACE_NO_INDENT();
  int ptl_x, ptl_y, pbr_x, pbr_y;
  wid_get_tl_x_tl_y_br_x_br_y(owner, &ptl_x, &ptl_y, &pbr_x, &pbr_y);

  minx -= ptl_x;
  miny -= ptl_y;
  maxx -= ptl_x;
  maxy -= ptl_y;

  child_width  = maxx - minx + 1;
  child_height = maxy - miny + 1;

  if (child_width < width) {
    maxx        = minx + width - 1;
    child_width = maxx - minx + 1;
  }

  if (child_height < height) {
    maxy         = miny + height - 1;
    child_height = maxy - miny + 1;
  }

  TRACE_NO_INDENT();
  if (owner->scrollbar_vert) {
    if (wid_get_moveable_vert(scrollbar)) {
      trough_height    = wid_get_height(owner->scrollbar_vert->parent);
      scrollbar_height = (int) (trough_height * (height / child_height));

      if (trough_height - scrollbar_height == 0.0f) {
        pct = 0.0f;
      } else {
        pct = (((float) wid_get_tl_y(scrollbar)) - ((float) wid_get_tl_y(scrollbar->parent)))
            / ((float) (trough_height - scrollbar_height));
      }

      owner->offset.y = -miny;
      owner->offset.y -= (pct * (child_height - height));

      float n = ((float) wid_get_tl_y(scrollbar->parent)) + pct * ((float) (trough_height - scrollbar_height));
      scrollbar->key.tl.y = (int) ceil(n);

      wid_tree_detach(scrollbar);
      scrollbar->key.br.y = wid_get_tl_y(scrollbar) + scrollbar_height - 1;
      wid_tree_attach(scrollbar);

      wid_set_mode(scrollbar, WID_MODE_ACTIVE);
    }
  }

  TRACE_NO_INDENT();
  if (owner->scrollbar_horiz) {
    if (wid_get_moveable_horiz(scrollbar)) {
      trough_width    = wid_get_width(owner->scrollbar_horiz->parent);
      scrollbar_width = (int) (trough_width * (width / child_width));

      if (trough_width - scrollbar_width == 0.0f) {
        pct = 0.0f;
      } else {
        pct = (wid_get_tl_x(scrollbar) - wid_get_tl_x(scrollbar->parent)) / (trough_width - scrollbar_width);
      }

      owner->offset.x = -minx;
      owner->offset.x -= (pct * (child_width - width));

      float n = ((float) wid_get_tl_x(scrollbar->parent)) + pct * ((float) (trough_width - scrollbar_width));
      scrollbar->key.tl.x = (int) ceil(n);

      wid_tree_detach(scrollbar);
      scrollbar->key.br.x = wid_get_tl_x(scrollbar) + scrollbar_width - 1;
      wid_tree_attach(scrollbar);

      wid_set_mode(scrollbar, WID_MODE_ACTIVE);
    }
  }
}

void wid_get_children_size(Widp owner, int *w, int *h)
{
  TRACE_NO_INDENT();
  double  height       = wid_get_height(owner);
  double  width        = wid_get_width(owner);
  double  child_height = 0;
  double  child_width  = 0;
  double  miny         = 0;
  double  maxy         = 0;
  double  minx         = 0;
  double  maxx         = 0;
  uint8_t first        = true;

  //
  // Find out the space that the children take up then use this to
  // adjust the scrollbar dimensions.
  //
  for (auto &iter : owner->children_display_sorted) {

    auto child = iter.second;

    int tminx = wid_get_tl_x(child) - wid_get_tl_x(child->parent);
    int tminy = wid_get_tl_y(child) - wid_get_tl_y(child->parent);
    int tmaxx = wid_get_br_x(child) - wid_get_tl_x(child->parent);
    int tmaxy = wid_get_br_y(child) - wid_get_tl_y(child->parent);

    if (first) {
      minx  = tminx;
      miny  = tminy;
      maxx  = tmaxx;
      maxy  = tmaxy;
      first = false;
      continue;
    }

    if (tminx < minx) {
      minx = tminx;
    }

    if (tminy < miny) {
      miny = tminy;
    }

    if (tmaxx > maxx) {
      maxx = tmaxx;
    }

    if (tmaxy > maxy) {
      maxy = tmaxy;
    }
  }

  child_width  = maxx - minx;
  child_height = maxy - miny;

  if (child_width < width) {
    maxx        = minx + width;
    child_width = maxx - minx;
  }

  if (child_height < height) {
    maxy         = miny + height;
    child_height = maxy - miny;
  }

  if (w) {
    *w = child_width;
  }

  if (h) {
    *h = child_height;
  }
}

static void wid_update_internal(Widp w)
{
  TRACE_NO_INDENT();
  int tlx;
  int tly;
  int brx;
  int bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  //
  // First time around, initialize the wid.
  //
  if (! w->first_update) {
    w->first_update = true;

    if (! w->parent) {
      //
      // Find the focus.
      //
      wid_find_top_focus();
    }

    //
    // Set back to normal to undo any settings when creating.
    //
    // No, make the clients fix their code.
    //
    //        wid_set_mode(w, WID_MODE_NORMAL);
  }

  //
  // Clip all the children. Avoid this for speed for the main game window.
  //
  std::vector< Widp > worklist;
  for (auto &iter : w->tree2_children_unsorted) {
    auto w = iter.second;
    worklist.push_back(w);
  }

  for (auto &child : worklist) {
    wid_update_internal(child);
  }

  //
  // If the source of the event is the scrollbars themselves...
  //
  if (w->scrollbar_owner) {
    wid_adjust_scrollbar(w, w->scrollbar_owner);
    wid_update_internal(w->scrollbar_owner);
  } else {
    //
    // If the source of the event is the owner of the scrollbars...
    //
    if (w->scrollbar_vert) {
      wid_adjust_scrollbar(w->scrollbar_vert, w);
    }

    if (w->scrollbar_horiz) {
      wid_adjust_scrollbar(w->scrollbar_horiz, w);
    }
  }
}

void wid_update(Widp w)
{
  TRACE_NO_INDENT();
  wid_update_internal(w);

  //
  // If we were hovering over a window and it was replaced, we need to fake
  // a mouse movement so we know we are still over it.
  //
  if (! w->parent && ! w->children_display_sorted.empty()) {
    wid_update_mouse();
  }
}

void wid_update_mouse(void)
{
  TRACE_NO_INDENT();
  //
  // So if we are now over a new widget that was created on top of the
  // mouse, we activate it.
  //
  int x;
  int y;

  SDL_GetMouseState(&x, &y);

  wid_mouse_motion(x, y, 0, 0, 0, 0);
}

void wid_scroll_text(Widp w)
{
  TRACE_NO_INDENT();
  std::wstring s;
  Widp         prev {};
  Widp         tmp {};

  //
  // Get the wid on the top of the list/screen.
  //
  tmp = wid_get_tail(w);

  //
  // Now copy the text up to the parent widgets.
  //
  while (tmp) {
    prev = wid_get_prev(tmp);

    if (prev) {
      s = wid_get_text(prev);

      wid_set_text(tmp, s);
    }

    tmp = prev;
  }
}

//
// Replace the 2nd last line of text and scroll. The assumption is the last
// line is the input line.
//
void wid_scroll_with_input(Widp w, std::wstring str)
{
  TRACE_NO_INDENT();
  Widp tmp {};

  wid_scroll_text(w);

  //
  // Get the wid on the bottom of the list/screen.
  //
  tmp = wid_get_head(w);

  //
  // Now get the 2nd last line. The last line is the input. The 2nd last
  // line is where new output goes.
  //
  if (tmp) {
    tmp = wid_get_next(tmp);
    if (tmp) {
      wid_set_text(tmp, str);
    }
  }
}

uint8_t wid_receive_input(Widp w, const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  std::wstring beforecursor;
  std::wstring aftercursor;
  std::wstring tmp;
  std::wstring origtext;
  std::wstring updatedtext;
  std::wstring newchar;
  uint32_t     origlen;
  uint32_t     cnt;

  if (sdlk_eq(*key, game->config.key_console)) {
    return false;
  }

  newchar += wid_event_to_char(key);
  origtext = wid_get_text(w);
  origlen  = (uint32_t) origtext.length();

  if (! w->received_input) {
    wid_set_received_input(w, true);
    w->cursor = (uint32_t) origtext.length();
  }

  if (origtext.empty()) {
    aftercursor = beforecursor = L"";
  } else {
    beforecursor = origtext.substr(0, w->cursor);
    aftercursor  = origtext.substr(w->cursor);
  }

  switch (key->mod) {
    case KMOD_LCTRL :
    case KMOD_RCTRL :
      switch (wid_event_to_char(key)) {
        case 'p' :
          if (! g_history_walk) {
            g_history_walk = HISTORY_MAX - 1;
          } else {
            g_history_walk--;
          }

          wid_set_text(w, get(history, g_history_walk));
          w->cursor = (uint32_t) wid_get_text(w).length();
          break;

        case 'n' :
          g_history_walk++;
          if (g_history_walk >= HISTORY_MAX) {
            g_history_walk = 0;
          }

          wid_set_text(w, get(history, g_history_walk));
          w->cursor = (uint32_t) wid_get_text(w).length();
          break;

        case 'a' : w->cursor = 0; break;

        case 'e' : w->cursor = origlen; break;
      }
      break;

    default :

      switch (key->sym) {
        case SDLK_BACKSPACE :
          if (beforecursor.size()) {
            w->cursor--;

            beforecursor.erase(beforecursor.end() - 1);
            auto result = beforecursor + aftercursor;
            wid_set_text(w, result);
          }
          break;

        case SDLK_TAB :
          if (w != wid_console_input_line) {
            return true;
          }

          command_handle(wid_get_text(w), &updatedtext, false /* show ambiguous */, true /* show complete */,
                         false /* execute command */, 0 /* context */);

          if (! updatedtext.empty()) {
            wid_set_text(w, updatedtext);
            w->cursor = updatedtext.length();
          }
          return true;

        case SDLK_RETURN :
          if (w != wid_console_input_line) {
            return false;
          }

          if (origlen && (w == wid_console_input_line)) {
            static std::wstring entered;
            static std::wstring entered2;

            entered  = wid_get_text(w);
            entered2 = L"\u0084 %%fg=green$" + wid_get_text(w);

            wid_scroll_text(w);
            wid_set_text(w->next, entered2);

            if (! command_handle(entered, &updatedtext, true /* show ambiguous */, false /* show complete */,
                                 true /* execute command */, 0 /* context */)) {
              return true;
            }

            updatedtext = trim(updatedtext);

            if (! updatedtext.empty()) {
              wid_set_text(w, updatedtext);
              w->cursor = updatedtext.length();
            }

            set(history, g_history_at, updatedtext);

            g_history_at++;
            if (g_history_at >= HISTORY_MAX) {
              g_history_at = 0;
            }
            g_history_walk = g_history_at;

            wid_set_text(w, L"");
            w->cursor = 0;
          } else if (w == wid_console_input_line) {
            wid_scroll_text(w);
          }
          return true;

        case SDLK_LEFT :
          if (w->cursor > 0) {
            w->cursor--;
          }
          break;

        case SDLK_RIGHT :
          if (w->cursor < origlen) {
            w->cursor++;
          }
          break;

        case SDLK_UP :
          cnt = 0;
          while (cnt < HISTORY_MAX) {
            cnt++;
            if (! g_history_walk) {
              g_history_walk = HISTORY_MAX - 1;
            } else {
              g_history_walk--;
            }

            wid_set_text(w, get(history, g_history_walk));
            if (get(history, g_history_walk) == L"") {
              continue;
            }

            w->cursor = (uint32_t) wid_get_text(w).length();
            break;
          }
          break;

        case SDLK_DOWN :
          cnt = 0;
          while (cnt < HISTORY_MAX) {
            cnt++;

            g_history_walk++;
            if (g_history_walk >= HISTORY_MAX) {
              g_history_walk = 0;
            }

            wid_set_text(w, get(history, g_history_walk));
            if (get(history, g_history_walk) == L"") {
              continue;
            }

            w->cursor = (uint32_t) wid_get_text(w).length();
            break;
          }
          break;

        case SDLK_HOME : w->cursor = 0; break;

        case SDLK_END : w->cursor = origlen; break;

        default :
          {
            auto c = wid_event_to_char(key);

            switch (c) {
              case SDLK_ESCAPE :
                if (w != wid_console_input_line) {
                  break;
                }

              case '?' :
                if (w != wid_console_input_line) {
                  break;
                }

                command_handle(wid_get_text(w), &updatedtext, true /* show ambiguous */, false /* show complete */,
                               false /* execute command */, 0 /* context */);

                if (! updatedtext.empty()) {
                  wid_set_text(w, updatedtext);
                  w->cursor = updatedtext.length();
                }
                return true;
            }

            if (c != '\0') {
              std::wstring tmp = L"";
              tmp += c;
              updatedtext = beforecursor;
              updatedtext += c;
              updatedtext += aftercursor;

              w->cursor++;

              wid_set_text(w, updatedtext);
            }
          }
      }
  }

  return true;
}

//
// Handle keys no one grabbed.
//
static uint8_t wid_receive_unhandled_input(const SDL_Keysym *key)
{
  TRACE_NO_INDENT();
  Widp w {};

  w = wid_get_top_parent(wid_console_input_line);

  if (sdlk_eq(*key, game->config.key_console)) {
    wid_toggle_hidden(wid_console_window);
    wid_raise(wid_console_window);

    //
    // Need this so the console gets focus over the menu.
    //
    if (w->visible) {
      wid_set_focus(w);
      wid_focus_lock(w);
    } else {
      wid_unset_focus();
      wid_unset_focus_lock();
    }
    return true;
  }

  if (sdlk_eq(*key, game->config.key_screenshot)) {
    sdl_screenshot();
    TOPCON("Screenshot taken.");
    CON("INF: Screenshot taken");
    return true;
  }

  switch ((int) key->sym) {
    case '?' : game->wid_config_keyboard_select(); break;

    case SDLK_ESCAPE :
      if (w->visible) {
        wid_hide(w);
      }

      //
      // Need this so the console gets focus over the menu.
      //
      if (w->visible) {
        wid_set_focus(w);
        wid_focus_lock(w);
      } else {
        wid_unset_focus();
        wid_unset_focus_lock();
      }
      break;

    case SDLK_TAB :
    case SDLK_RETURN :
    case SDLK_DOWN :
    case SDLK_RIGHT : wid_find_next_focus(); break;

    case SDLK_UP :
    case SDLK_LEFT : wid_find_prev_focus(); break;

    default :
      {
        if (wid_console_window && wid_console_window->visible) {
          wid_console_receive_input(wid_console_input_line, key);
        }
        break;
      }
  }

  return true;
}

Widp wid_find_at(int x, int y)
{
  TRACE_NO_INDENT();
  auto w = get(wid_on_screen_at, x, y);
  if (unlikely(! w)) {
    return nullptr;
  }

  verify(MTYPE_WID, w);
  if (wid_ignore_being_destroyed(w)) {
    return nullptr;
  }

  return w;
}

Widp wid_find_under_mouse(void)
{
  TRACE_NO_INDENT();
  if (ascii_is_empty(ascii_mouse_x, ascii_mouse_y)) {
    return nullptr;
  }

  auto w = wid_find_at(ascii_mouse_x, ascii_mouse_y);
  if (w) {
    w = wid_get_top_parent(w);
    // CON("mouse %d,%d over %s %p", ascii_mouse_x, ascii_mouse_y, w->name.c_str(), w);
    if (wid_ignore_events_only(w)) {
      return nullptr;
    }
    return w;
  }
  return nullptr;
}

Widp wid_find_under_mouse_when_scrolling(void)
{
  TRACE_NO_INDENT();
  if (ascii_is_empty(ascii_mouse_x, ascii_mouse_y)) {
    return nullptr;
  }
  auto w = wid_find_at(ascii_mouse_x, ascii_mouse_y);
  if (w) {
    w = wid_get_top_parent(w);
    if (wid_ignore_scroll_events(w)) {
      // TOPCON("ign2 %s.", wid_name(w).c_str());
      return nullptr;
    } else {
      // TOPCON("over2 %s.", wid_name(w).c_str());
      return w;
    }
  }
  return w;
}

static Widp wid_key_down_handler_at(Widp w, int x, int y, uint8_t strict)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_key_down_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_key_down_handler_at(child, x, y, false /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_key_down) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  w = wid_get_top_parent(w);
  if (w->on_key_down) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_key_up_handler_at(Widp w, int x, int y, uint8_t strict)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_key_up_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_key_up_handler_at(child, x, y, false /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_key_up) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_joy_button_handler_at(Widp w, int x, int y, uint8_t strict)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_joy_button_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_joy_button) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_down_handler_at(Widp w, int x, int y, uint8_t strict)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (w->ignore_for_mouse_down) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_mouse_down_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_mouse_down) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  if (wid_get_moveable(w)) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  //
  // Prevent mouse events that occur in the bounds of one window, leaking
  // into lower levels.
  //
  if (! w->parent) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_held_handler_at(Widp w, int x, int y, uint8_t strict)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_mouse_held_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_mouse_held) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  if (wid_get_moveable(w)) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  //
  // Prevent mouse events that occur in the bounds of one window, leaking
  // into lower levels.
  //
  if (! w->parent) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_up_handler_at(Widp w, int x, int y, uint8_t strict)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return nullptr;
  }

  if (! w->visible) {
    return nullptr;
  }

  if (wid_ignore_events(w)) {
    return nullptr;
  }

  //
  // Prevent newly created widgets grabbing events too soon; like
  // for example a scancode causes a widget to be created but the
  // same keypress is taken by the widget.
  //
  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    return nullptr;
  }

  if (strict) {
    if ((x < w->abs_tl.x) || (y < w->abs_tl.y) || (x > w->abs_br.x) || (y > w->abs_br.y)) {
      return nullptr;
    }
  }

  for (auto &iter : w->children_display_sorted) {
    auto child = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    Widp closer_match = wid_mouse_up_handler_at(child, x, y, true /* strict */);
    if (closer_match) {
      return closer_match;
    }
  }

  if (w->on_mouse_up) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  if (wid_get_moveable(w)) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  //
  // Prevent mouse events that occur in the bounds of one window, leaking
  // into lower levels.
  //
  if (! w->parent) {
    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      return nullptr;
    }

    return w;
  }

  return nullptr;
}

static void wid_children_move_delta_internal(Widp w, int dx, int dy)
{
  TRACE_NO_INDENT();
  //
  // Make sure you can't move a wid outside the parents box.
  //
  Widp p = w->parent;
  if (p) {
    if (wid_get_moveable_bounded(w)) {
      if (wid_get_tl_x(w) + dx < wid_get_tl_x(p)) {
        dx = wid_get_tl_x(p) - wid_get_tl_x(w);
      }

      if (wid_get_tl_y(w) + dy < wid_get_tl_y(p)) {
        dy = wid_get_tl_y(p) - wid_get_tl_y(w);
      }

      if (wid_get_br_x(w) + dx > wid_get_br_x(p)) {
        dx = wid_get_br_x(p) - wid_get_br_x(w);
      }

      if (wid_get_br_y(w) + dy > wid_get_br_y(p)) {
        dy = wid_get_br_y(p) - wid_get_br_y(w);
      }
    }
  }

  w->key.tl.x += dx;
  w->key.tl.y += dy;
  w->key.br.x += dx;
  wid_tree_detach(w);
  w->key.br.y += dy;
  wid_tree_attach(w);

  for (auto &iter : w->tree2_children_unsorted) {
    auto child = iter.second;

    wid_children_move_delta_internal(child, dx, dy);
  }
}

static void wid_move_delta_internal(Widp w, int dx, int dy)
{
  TRACE_NO_INDENT();
  wid_tree_detach(w);

  //
  // Make sure you can't move a wid outside the parents box.
  //
  Widp p = w->parent;
  if (p) {
    if (wid_get_moveable_bounded(w)) {
      if (wid_get_tl_x(w) + dx < wid_get_tl_x(p)) {
        dx = wid_get_tl_x(p) - wid_get_tl_x(w);
      }

      if (wid_get_tl_y(w) + dy < wid_get_tl_y(p)) {
        dy = wid_get_tl_y(p) - wid_get_tl_y(w);
      }

      if (wid_get_br_x(w) + dx > wid_get_br_x(p)) {
        dx = wid_get_br_x(p) - wid_get_br_x(w);
      }

      if (wid_get_br_y(w) + dy > wid_get_br_y(p)) {
        dy = wid_get_br_y(p) - wid_get_br_y(w);
      }
    }
  }

  w->key.tl.x += dx;
  w->key.tl.y += dy;
  w->key.br.x += dx;
  w->key.br.y += dy;
  wid_tree_attach(w);

  std::vector< Widp > worklist;
  for (auto &iter : w->tree2_children_unsorted) {
    auto w = iter.second;
    worklist.push_back(w);
  }

  for (auto &child : worklist) {
    wid_children_move_delta_internal(child, dx, dy);
  }
}

void wid_move_delta(Widp w, int dx, int dy)
{
  TRACE_NO_INDENT();
  wid_move_delta_internal(w, dx, dy);

  wid_update_internal(w);
}

void wid_resize(Widp w, int width, int height)
{
  TRACE_NO_INDENT();
  wid_tree_detach(w);

  if (width != -1) {
    w->key.br.x = w->key.tl.x + width;
  }
  if (height != -1) {
    w->key.br.y = w->key.tl.y + height;
  }

  wid_tree_attach(w);
}

void wid_move_delta_pct(Widp w, double dx, double dy)
{
  TRACE_NO_INDENT();
  if (! w->parent) {
    dx *= (double) TERM_WIDTH;
    dy *= (double) TERM_HEIGHT;
  } else {
    dx *= wid_get_width(w->parent);
    dy *= wid_get_height(w->parent);
  }

  wid_move_delta_internal(w, dx, dy);

  wid_update_internal(w);
}

void wid_move_to(Widp w, int x, int y)
{
  TRACE_NO_INDENT();
  if (w->parent) {
    wid_move_delta(w, x - wid_get_tl_x(w->parent), y - wid_get_tl_y(w->parent));
  } else {
    wid_move_delta(w, x - wid_get_tl_x(w), y - wid_get_tl_y(w));
  }
}

void wid_move_to_bottom(Widp w)
{
  TRACE_NO_INDENT();
  if (w->parent) {
    wid_move_delta(w, 0, wid_get_br_y(w->parent) - wid_get_br_y(w));
  } else {
    wid_move_delta(w, 0, TERM_HEIGHT - wid_get_br_y(w));
  }
}

void wid_move_to_y_off(Widp w, int off)
{
  TRACE_NO_INDENT();
  wid_move_delta(w, 0, off);
}

void wid_move_to_left(Widp w)
{
  TRACE_NO_INDENT();
  if (w->parent) {
    wid_move_delta(w, wid_get_tl_x(w->parent) - wid_get_tl_x(w), 0);
  } else {
    wid_move_delta(w, -wid_get_tl_x(w), 0);
  }
}

void wid_move_to_right(Widp w)
{
  TRACE_NO_INDENT();
  if (w->parent) {
    wid_move_delta(w, wid_get_br_x(w->parent) - wid_get_br_x(w), 0);
  } else {
    wid_move_delta(w, TERM_WIDTH - wid_get_br_x(w), 0);
  }
}

void wid_move_to_vert_pct(Widp w, double pct)
{
  TRACE_NO_INDENT();
  double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
  double at      = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
  double delta   = (pct - at) * pheight;

  wid_move_delta(w, 0, delta);
}

void wid_move_to_horiz_pct(Widp w, double pct)
{
  TRACE_NO_INDENT();
  double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
  double at     = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
  double delta  = (pct - at) * pwidth;

  wid_move_delta(w, delta, 0);
}

void wid_move_to_vert_pct_in(Widp w, double pct, double in)
{
  TRACE_NO_INDENT();
  if (pct < 0.0) {
    pct = 0.0;
  }

  if (pct > 1.0) {
    pct = 1.0;
  }

  double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
  double at      = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
  double delta   = (pct - at) * pheight;

  wid_move_to_abs_in(w, wid_get_tl_x(w), wid_get_tl_y(w) + delta, in);
}

void wid_move_to_horiz_pct_in(Widp w, double pct, double in)
{
  TRACE_NO_INDENT();
  if (pct < 0.0) {
    pct = 0.0;
  }

  if (pct > 1.0) {
    pct = 1.0;
  }

  double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
  double at     = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
  double delta  = (pct - at) * pwidth;

  wid_move_to_abs_in(w, wid_get_tl_x(w) + delta, wid_get_tl_y(w), in);
}

void wid_move_to_horiz_vert_pct_in(Widp w, double x, double y, double in)
{
  TRACE_NO_INDENT();
  if (x < 0.0) {
    x = 0.0;
  }

  if (x > 1.0) {
    x = 1.0;
  }

  if (y < 0.0) {
    y = 0.0;
  }

  if (y > 1.0) {
    y = 1.0;
  }

  double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
  double aty     = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
  double dy      = (y - aty) * pheight;

  double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
  double atx    = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
  double dx     = (x - atx) * pwidth;

  wid_move_to_abs_in(w, wid_get_tl_x(w) + dx, wid_get_tl_y(w) + dy, in);
}

void wid_move_to_top(Widp w)
{
  TRACE_NO_INDENT();
  if (w->parent) {
    wid_move_delta(w, 0, wid_get_tl_y(w->parent) - wid_get_tl_y(w));
  } else {
    wid_move_delta(w, 0, -wid_get_tl_y(w));
  }
}

static Widp wid_joy_button_handler(int x, int y)
{
  TRACE_NO_INDENT();
  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_joy_button_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_down_handler(int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  w = wid_mouse_down_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_mouse_down_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_down_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_down_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_held_handler(int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  w = wid_mouse_held_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_mouse_held_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_held_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_held_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

static Widp wid_mouse_up_handler(int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  w = wid_mouse_up_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    verify(MTYPE_WID, w);
    return w;
  }

  w = wid_mouse_up_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    verify(MTYPE_WID, w);
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_up_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    verify(MTYPE_WID, w);
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_mouse_up_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    verify(MTYPE_WID, w);
    return w;
  }

  return nullptr;
}

static Widp wid_mouse_motion_handler(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  Widp w {};

  w = get(wid_on_screen_at, x, y);
  if (w) {
    verify(MTYPE_WID, w);
    if (w->hidden) {
      return nullptr;
    }
    return w;
  }

  return nullptr;
}

//
// Catch recursive cases:
//
static int wid_mouse_motion_recursion;

void wid_mouse_motion(int x, int y, int relx, int rely, int wheelx, int wheely)
{
  TRACE_NO_INDENT();
  int got_one = false;

  //
  // To avoid lag, just grab the current mouse position.
  //
  SDL_GetMouseState(&x, &y);

  //
  // Map to ascii
  //
  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  if (relx || rely) {
    wid_last_mouse_motion = time_ms_cached();
  }

  wid_refresh_overlay_count++;

  if (wid_mouse_motion_recursion) {
    return;
  }

  wid_mouse_motion_recursion = 1;

  if (wid_mouse_template) {
    wid_move_to_abs_centered_in(wid_mouse_template, x, y, 10);
    wid_raise(wid_mouse_template);
  }

  uint8_t over = false;

  for (auto &iter : wid_top_level) {
    auto w = iter.second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    //
    // Allow wheel events to go everywhere
    //
    if (! wheelx && ! wheely) {
      w = wid_find_at(x, y);
      if (unlikely(! w)) {
        continue;
      }
    }

    if (wid_ignore_events(w)) {
      //
      // This wid is ignoring events, but what about the parent?
      //
      w = w->parent;
      while (w) {
        if (! wid_ignore_events(w)) {
          break;
        }
        w = w->parent;
      }

      if (unlikely(! w)) {
        continue;
      }
    }

    //
    // Over a new wid.
    //

    while (w && ! wid_mouse_over_begin(w, x, y, relx, rely, wheelx, wheely)) {
      w = w->parent;
    }

    uint8_t done = false;

    if (unlikely(! w)) {
      //
      // Allow scrollbar to grab.
      //
    } else {
      //
      // This widget reacted somehow when we went over it. i.e. popup ot
      // function.
      //
      over = true;
    }

    w = wid_mouse_motion_handler(x, y, relx, rely, wheelx, wheely);
    if (w) {
      if (wid_mouse_over_begin(w, x, y, relx, rely, wheelx, wheely)) {
        over = true;
      }

      //
      // If the mouse event is fully processed then do not pass onto
      // scrollbars.
      //
      if (w->on_mouse_motion) {
        if ((w->on_mouse_motion)(w, x, y, relx, rely, wheelx, wheely)) {
          verify(MTYPE_WID, w);
          got_one = true;
          break;
        }
      }

      if (wid_over == w) {
        if (! wheelx && ! wheely) {
          break;
        }
      }

      while (w) {
        //
        // If there are scrollbars and the wid did not grab the event
        // then scroll for it.
        //
        if (wheely) {
          if (w->scrollbar_vert && ! wid_get_moveable_no_user_scroll(w->scrollbar_vert)) {

            got_one = true;
            wid_move_delta(w->scrollbar_vert, 0, -wheely);
            done = true;
          }
        }

        if (wheelx) {
          if (w->scrollbar_horiz && ! wid_get_moveable_no_user_scroll(w->scrollbar_horiz)) {

            got_one = true;
            wid_move_delta(w->scrollbar_horiz, -wheelx, 0);
            done = true;
          }
        }

        if (done) {
          break;
        }

        //
        // Maybe the container has a scrollbar. Try it.
        //
        w = w->parent;
      }
    }

    if (done) {
      break;
    }
  }

  if (! over) {
    wid_mouse_over_end();
  }

  //
  // If nothing then pass the event to the console to allow scrolling
  // of the console.
  //
  if (! got_one) {
    if (wid_console_window && wid_console_window->visible) {
      if (wid_console_container && (wheelx || wheely)) {
        Widp w = wid_console_container->scrollbar_vert;
        if (w) {
          w = w->parent;
        }

        if (w && w->on_mouse_motion) {
          (w->on_mouse_motion)(w, x, y, relx, rely, wheelx, wheely);
        }
      }
    }
  }

  wid_mouse_motion_recursion = 0;

  if (relx || rely || wheelx || wheely) {
    game_mouse_motion(x, y, relx, rely, wheelx, wheely);
  }
}

//
// If no handler for this button, fake a mouse event.
//
void wid_fake_joy_button(int x, int y)
{
  TRACE_NO_INDENT();
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_A)) {
    wid_mouse_down(SDL_BUTTON_LEFT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_B)) {
    wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_X)) {
    wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_Y)) {
    wid_mouse_down(2, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_TOP_LEFT)) {
    wid_mouse_down(SDL_BUTTON_LEFT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_TOP_RIGHT)) {
    wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT_STICK_DOWN)) {
    wid_mouse_down(SDL_BUTTON_LEFT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT_STICK_DOWN)) {
    wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_START)) {
    wid_mouse_down(SDL_BUTTON_LEFT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_XBOX)) {
    wid_mouse_down(SDL_BUTTON_LEFT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_BACK)) {
    wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_UP)) {}
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_DOWN)) {}
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT)) {}
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT)) {}
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE)) {
    wid_mouse_down(SDL_BUTTON_LEFT, x, y);
    return;
  }
  if (get(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE)) {
    wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
    return;
  }
}

void wid_joy_button(int x, int y)
{
  TRACE_NO_INDENT();
  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  //
  // Only if there is a change in status, send an event.
  //
  static std::array< ts_t, SDL_MAX_BUTTONS > ts;
  int                                        changed = false;
  int                                        b;

  for (b = 0; b < SDL_MAX_BUTTONS; b++) {
    if (get(sdl.joy_buttons, b)) {
      if (time_have_x_tenths_passed_since(2, get(ts, b))) {
        changed = true;
        set(ts, b, time_ms_cached());
      }
    }
  }

  if (! changed) {
    return;
  }

  Widp w {};

  w = wid_joy_button_handler(x, y);
  if (unlikely(! w)) {
    wid_fake_joy_button(x, y);
    return;
  }

  //
  // Raise on mouse.
  //
  if (w->on_joy_button) {
    //
    // If the button doesn't eat the event, try the parent.
    //
    while (! (w->on_joy_button)(w, x, y)) {
      w = w->parent;

      while (w && ! w->on_joy_button) {
        w = w->parent;
      }

      if (unlikely(! w)) {
        wid_fake_joy_button(x, y);
        return;
      }
    }

    wid_set_focus(w);
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);

    //
    // Move on mouse.
    //
    if (wid_get_moveable(w)) {
      wid_mouse_motion_begin(w, x, y);
      return;
    }

    return;
  } else {
    wid_fake_joy_button(x, y);
  }

  if (wid_get_moveable(w)) {
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    wid_mouse_motion_begin(w, x, y);
    return;
  }
}

void wid_mouse_down(uint32_t button, int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  w = wid_mouse_down_handler(x, y);
  if (unlikely(! w)) {
    return;
  }

  //
  // Raise on mouse.
  //
  if ((w->on_mouse_down && (w->on_mouse_down)(w, x, y, button)) || wid_get_moveable(w)) {
    verify(MTYPE_WID, w);
    sound_play("click");

    wid_set_focus(w);
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);

    //
    // Move on mouse.
    //
    if (wid_get_moveable(w)) {
      wid_mouse_motion_begin(w, x, y);
      return;
    }

    if (game) {
      game->last_mouse_down = time_ms_cached();
    }

    return;
  }

  if (wid_get_moveable(w)) {
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    wid_mouse_motion_begin(w, x, y);
    return;
  }

  if (game_mouse_down(x, y, button)) {
    sound_play("click");
    if (game) {
      game->last_mouse_down = time_ms_cached();
    }
  }
}

void wid_mouse_held(uint32_t button, int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  w = wid_mouse_held_handler(x, y);
  if (unlikely(! w)) {
    return;
  }

  //
  // Raise on mouse.
  //
  if ((w->on_mouse_held && (w->on_mouse_held)(w, x, y, button)) || wid_get_moveable(w)) {
    verify(MTYPE_WID, w);

    wid_set_focus(w);
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);

    //
    // Move on mouse.
    //
    if (wid_get_moveable(w)) {
      wid_mouse_motion_begin(w, x, y);
      return;
    }

    return;
  }

  if (wid_get_moveable(w)) {
    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    wid_mouse_motion_begin(w, x, y);
    return;
  }
}

void wid_mouse_up(uint32_t button, int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  wid_mouse_motion_end();

  w = wid_mouse_up_handler(x, y);
  if (unlikely(! w)) {
    return;
  }
  verify(MTYPE_WID, w);

  if ((w->on_mouse_up && (w->on_mouse_up)(w, x, y, button)) || wid_get_moveable(w)) {
    verify(MTYPE_WID, w);
    sound_play("click");

    wid_set_mode(w, WID_MODE_ACTIVE);
    wid_raise(w);
    return;
  }

  game_mouse_up(x, y, button);
}

static Widp wid_key_down_handler(int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  // TOPCON("key down.");
  w = wid_key_down_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    // TOPCON("%s %d.",to_cstring(w).c_str(),__LINE__);
    return w;
  }

  w = wid_key_down_handler_at(wid_get_top_parent(wid_focus), x, y, false /* strict */);
  if (w) {
    // TOPCON("%s %d.",to_string(w).c_str(),__LINE__);
    return w;
  }

  w = wid_key_down_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    // TOPCON("%s %d.",to_string(w).c_str(),__LINE__);
    return w;
  }

  w = wid_key_down_handler_at(wid_get_top_parent(wid_over), x, y, false /* strict */);
  if (w) {
    // TOPCON("%s %d.",to_string(w).c_str(),__LINE__);
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      // TOPCON("  focus is locked.");
      continue;
    }

    w = wid_key_down_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }
    // TOPCON("     got top level strict handler%s.",to_string(w).c_str());

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      // TOPCON("  focus is locked.");
      continue;
    }

    w = wid_key_down_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    // TOPCON("     got top level loose handler%s.",to_string(w));
    return w;
  }

  return nullptr;
}

static Widp wid_key_up_handler(int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  w = wid_key_up_handler_at(wid_focus, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_key_up_handler_at(wid_get_top_parent(wid_focus), x, y, false /* strict */);
  if (w) {
    return w;
  }

  w = wid_key_up_handler_at(wid_over, x, y, true /* strict */);
  if (w) {
    return w;
  }

  w = wid_key_up_handler_at(wid_get_top_parent(wid_over), x, y, false /* strict */);
  if (w) {
    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_key_up_handler_at(w, x, y, true /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  for (auto iter = wid_top_level.rbegin(); iter != wid_top_level.rend(); ++iter) {
    auto w = iter->second;

    if (wid_focus_locked && (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
      continue;
    }

    w = wid_key_up_handler_at(w, x, y, false /* strict */);
    if (unlikely(! w)) {
      continue;
    }

    return w;
  }

  return nullptr;
}

#ifdef ENABLE_DEBUG_GFX_GL_BLEND
int vals[] = {
    GL_ZERO,
    GL_ONE,
    GL_CONSTANT_ALPHA,
    GL_CONSTANT_COLOR,
    GL_DST_ALPHA,
    GL_DST_COLOR,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_COLOR,
    GL_ONE_MINUS_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_ONE_MINUS_DST_COLOR,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_ONE_MINUS_SRC_COLOR,
    GL_SRC_ALPHA,
    GL_SRC_ALPHA_SATURATE,
    GL_SRC_COLOR,
};

std::string vals_str[] = {
    "GL_ZERO",
    "GL_ONE",
    "GL_CONSTANT_ALPHA",
    "GL_CONSTANT_COLOR",
    "GL_DST_ALPHA",
    "GL_DST_COLOR",
    "GL_ONE_MINUS_CONSTANT_ALPHA",
    "GL_ONE_MINUS_CONSTANT_ALPHA",
    "GL_ONE_MINUS_CONSTANT_COLOR",
    "GL_ONE_MINUS_DST_ALPHA",
    "GL_ONE_MINUS_DST_ALPHA",
    "GL_ONE_MINUS_DST_COLOR",
    "GL_ONE_MINUS_SRC_ALPHA",
    "GL_ONE_MINUS_SRC_COLOR",
    "GL_SRC_ALPHA",
    "GL_SRC_ALPHA_SATURATE",
    "GL_SRC_COLOR",
};

int g_blend_a;
int g_blend_b;
#endif

#if 0
  //
  // Paste this code prior to the blend in question
  //
  extern int vals[];
  extern std::string vals_str[];
  extern int g_blend_a;
  extern int g_blend_b;
  CON("glBlendFunc(%s, %s)", vals_str[g_blend_a].c_str(), vals_str[g_blend_b].c_str());
  glBlendFunc(vals[g_blend_a], vals[g_blend_b]);
#endif

void wid_key_down(const struct SDL_Keysym *key, int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    DBG("SDL: Keyboard: bad coord %d,%d", x, y);
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

#ifdef ENABLE_DEBUG_GFX_GL_BLEND
  if (wid_event_to_char(key) == '+') {
    CON("ENABLE_DEBUG_GFX_GL_BLEND +");
    usleep(50);
    g_blend_a++;
    if (g_blend_a >= (int) ARRAY_SIZE(vals)) {
      g_blend_a = 0;
      g_blend_b++;
      if (g_blend_b >= (int) ARRAY_SIZE(vals)) {
        g_blend_b = 0;
        ERR("Wrapped");
      }
    }
    return;
  }

  if (wid_event_to_char(key) == '-') {
    CON("ENABLE_DEBUG_GFX_GL_BLEND -");
    usleep(50);
    g_blend_a--;
    if (g_blend_a < 0) {
      g_blend_a = (int) ARRAY_SIZE(vals) - 1;
      g_blend_b--;
      if (g_blend_b < 0) {
        g_blend_b = (int) ARRAY_SIZE(vals) - 1;
      }
    }
    return;
  }
#endif
  if (wid_focus && ! wid_is_hidden(wid_focus) && (wid_focus->on_key_down)) {
    if ((wid_focus->on_key_down)(wid_focus, key)) {
      DBG("WID: key grabbed by focused wid: %s at (%d,%d)", wid_focus->name.c_str(), ascii_mouse_x, ascii_mouse_y);
      //
      // Do not raise, gets in the way of popups the callback creates.
      //
      return;
    }

    w = wid_focus;

    goto try_parent;
  }

  w = wid_key_down_handler(x, y);
  if (unlikely(! w)) {
    //
    // If no-one handles it, feed it to the default handler, the console.
    //
    DBG("SDL: Keyboard: no one handled the event");
    wid_receive_unhandled_input(key);
    return;
  }

  {
    DBG("WID: Key over by wid: %s for (%d,%d)", w->name.c_str(), ascii_mouse_x, ascii_mouse_y);
    if ((w->on_key_down)(w, key)) {
      DBG("WID: Key grabbed by wid: %s for (%d,%d)", w->name.c_str(), ascii_mouse_x, ascii_mouse_y);
      sound_play("click");
      //
      // Do not raise, gets in the way of popups the callback creates.
      //
      // CON("wid did not handle");
      return;
    }
  }

try_parent:
  w = w->parent;

  //
  // Ripple the key event to the parent so global things like pressing
  // escape can do things.
  //
  while (w) {
    if (w->on_key_down) {
      if ((w->on_key_down)(w, key)) {
        DBG("WID: key grabbed by wid: %s for (%d,%d)", w->name.c_str(), ascii_mouse_x, ascii_mouse_y);
        sound_play("click");
        //
        // Do not raise, gets in the way of popups the callback
        // creates.
        //
        return;
      }
    }

    w = w->parent;
  }

  //
  // If no-one handles it, feed it to the default handler, the console.
  //
  {
    DBG("WID: key is unhandled");
    wid_receive_unhandled_input(key);
  }
}

void wid_key_up(const struct SDL_Keysym *key, int x, int y)
{
  TRACE_NO_INDENT();
  Widp w {};

  pixel_to_ascii(&x, &y);
  if (! ascii_ok(x, y)) {
    return;
  }
  ascii_mouse_x = x;
  ascii_mouse_y = y;

  if (wid_focus && ! wid_is_hidden(wid_focus) && (wid_focus->on_key_up)) {

    if ((wid_focus->on_key_up)(wid_focus, key)) {
      wid_set_mode(wid_focus, WID_MODE_ACTIVE);

      //
      // Do not raise, gets in the way of popups the callback creates.
      //
      return;
    }

    w = wid_focus;

    goto try_parent;
  }

  w = wid_key_up_handler(x, y);
  if (unlikely(! w)) {
    //
    // If no-one handles it, drop it. We only hand key down to the
    // console.
    //
    return;
  }

  if ((w->on_key_up)(w, key)) {
    wid_set_mode(w, WID_MODE_ACTIVE);

    //
    // Do not raise, gets in the way of popups the callback creates.
    //
    return;
  }

try_parent:
  w = w->parent;

  //
  // Ripple the key event to the parent so global things like pressing
  // escape can do things.
  //
  while (w) {
    if (w->on_key_up) {
      if ((w->on_key_up)(w, key)) {
        wid_set_mode(w, WID_MODE_ACTIVE);

        //
        // Do not raise, gets in the way of popups the callback
        // creates.
        //
        return;
      }
    }

    w = w->parent;
  }
}

//
// Get the onscreen co-ords of the widget, clipped to the parent.
//
void wid_get_abs_coords(Widp w, int *tlx, int *tly, int *brx, int *bry)
{
  TRACE_NO_INDENT();
  Widp p {};

  *tlx = wid_get_tl_x(w);
  *tly = wid_get_tl_y(w);
  *brx = wid_get_br_x(w);
  *bry = wid_get_br_y(w);

  p = w->parent;
  while (p) {
    *tlx += p->offset.x;
    *tly += p->offset.y;
    *brx += p->offset.x;
    *bry += p->offset.y;
    p = p->parent;
  }

#if 0
  int ptlx;
  int ptly;
  int pbrx;
  int pbry;

  if (w->parent) {
    wid_get_abs_coords(w->parent, &ptlx, &ptly, &pbrx, &pbry);

    if (ptlx > *tlx) {
      *tlx = ptlx;
    }

    if (ptly > *tly) {
      *tly = ptly;
    }

    if (pbrx < *brx) {
      *brx = pbrx;
    }

    if (pbry < *bry) {
      *bry = pbry;
    }
  }
#endif

  w->abs_tl.x = *tlx;
  w->abs_tl.y = *tly;
  w->abs_br.x = *brx;
  w->abs_br.y = *bry;
}

//
// Get the onscreen co-ords of the widget, clipped to the parent.
//
void wid_get_abs(Widp w, int *x, int *y)
{
  TRACE_NO_INDENT();
  int tlx;
  int tly;
  int brx;
  int bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  *x = (tlx + brx) / 2;
  *y = (tly + bry) / 2;
}

void wid_get_pct(Widp w, double *px, double *py)
{
  TRACE_NO_INDENT();
  int x;
  int y;

  wid_get_abs(w, &x, &y);

  *px = (double) x / (double) TERM_WIDTH;
  *py = (double) y / (double) TERM_HEIGHT;
}

//
// Finish off a widgets move.
//
void wid_move_end(Widp w)
{
  TRACE_NO_INDENT();
  while (w->moving) {
    wid_move_dequeue(w);
  }
}

//
// Display one wid and its children
//
static int  wid_total_count;
static void wid_display(Widp w, uint8_t disable_scissor, uint8_t *updated_scissors, int clip)
{
  TRACE_NO_INDENT();
  wid_total_count++;
  int     clip_height = 0;
  int     clip_width  = 0;
  uint8_t hidden;
  uint8_t always_hidden;
  int     owidth;
  int     oheight;
  int     otlx;
  int     otly;
  int     obrx;
  int     obry;
  int     tlx;
  int     tly;
  int     brx;
  int     bry;
#if 0
  Widp p {};
#endif

  IF_DEBUG3 { verify(MTYPE_WID, w); }

#if 0
  if (!w->parent) {
    wid_dump(w, 0);
  }
#endif

  //
  // Bounding box for drawing the wid. Co-ords are negative as we
  // flipped the screen
  //
  tlx = w->abs_tl.x;
  tly = w->abs_tl.y;
  brx = w->abs_br.x;
  bry = w->abs_br.y;

  //
  // If we're clipped out of existence! then nothing to draw. This can
  // be outside the bounds of a widget or if at the top level, off screeen.
  //
  if (clip) {
    clip_width = brx - tlx;
    if (clip_width < 0) {
      return;
    }

    clip_height = bry - tly;
    if (clip_height < 0) {
      return;
    }
  }

  hidden        = wid_is_hidden(w);
  always_hidden = wid_is_always_hidden(w);

  if (always_hidden) {
    //
    // Always render. Not hidden yet.
    //
    return;
  } else if (hidden) {
    //
    // Hidden or parent is hidden.
    //
    return;
  }

  //
  // Record the original pre clip sizes for text centering.
  //
  otlx = wid_get_tl_x(w);
  otly = wid_get_tl_y(w);
  obrx = wid_get_br_x(w);
  obry = wid_get_br_y(w);

  wid_get_abs_coords(w, &otlx, &otly, &obrx, &obry);
#if 0
  p = w->parent;
  while (p) {
    otlx += p->offset.x;
    otly += p->offset.y;
    obrx += p->offset.x;
    obry += p->offset.y;
    p = p->parent;
  }
#endif

  //
  // Inclusive width
  //
  owidth  = obrx - otlx + 1;
  oheight = obry - otly + 1;

  //
  // If this widget was active and the time has elapsed, make it normal.
  //
  auto mode = wid_get_mode(w);
  if (mode == WID_MODE_ACTIVE) {
    if ((wid_time - w->ts_last_mode_change) > 250) {
      wid_set_mode(w, WID_MODE_NORMAL);
    }
  }

  //
  // If inputting text, show a cursor.
  //
  std::wstring text;

  if (wid_get_show_cursor(w)) {
    text = wid_get_text_with_cursor(w);
  } else {
    text = wid_get_text(w);
  }

  if (w->disable_scissors) {
    disable_scissor = true;
  }

  //
  // Should be no need for scissors if you do not have any children
  // or are not the top level wid.
  //
  if (! disable_scissor) {
#if 0
  //
  // Why would we not always want scissors on?
  //
  if (!w->children_display_sorted.empty() || !w->parent || w->show_cursor) {
#endif
    //
    // Tell the parent we are doing scissors so they can re-do
    // their own scissors.
    //
    if (updated_scissors) {
      *updated_scissors = true;
    }
#if 0

  if (w->parent) {

    if (ptlx > *tlx) {
      *tlx = ptlx;
    }

    if (ptly > *tly) {
      *tly = ptly;
    }

    if (pbrx < *brx) {
      *brx = pbrx;
    }

    if (pbry < *bry) {
      *bry = pbry;
    }
  }
#endif

    auto sciss_tlx = tlx;
    auto sciss_tly = tly;
    auto sciss_brx = brx;
    auto sciss_bry = bry;

    auto p = w->parent;
    while (p) {
      int ptlx;
      int ptly;
      int pbrx;
      int pbry;
      wid_get_abs_coords(p, &ptlx, &ptly, &pbrx, &pbry);

      if (ptlx > sciss_tlx) {
        sciss_tlx = ptlx;
      }
      if (pbrx < sciss_brx) {
        sciss_brx = pbrx;
      }
      if (ptly > sciss_tly) {
        sciss_tly = ptly;
      }
      if (pbry < sciss_bry) {
        sciss_bry = pbry;
      }

      p = p->parent;
    }

    wid_set_scissors(sciss_tlx, sciss_tly, sciss_brx, sciss_bry);
#if 0
    }
#endif
  }

  auto width  = wid_get_width(w);
  auto height = wid_get_height(w);

  point tl;
  point br;

  tl.x = otlx;
  tl.y = otly;
  br.x = otlx + width;
  br.y = otly + height;

  box_args w_box_args = {
      .x      = tl.x,
      .y      = tl.y,
      .width  = (br.x - tl.x),
      .height = (br.y - tl.y),
  };

  if (w == wid_over) {
    w_box_args.over = true;

    if (w->cfg[ WID_MODE_OVER ].color_set[ WID_COLOR_TEXT_FG ]) {
      w_box_args.col_text = get(w->cfg, WID_MODE_OVER).colors[ WID_COLOR_TEXT_FG ];
    } else {
      w_box_args.col_text = get(w->cfg, WID_MODE_NORMAL).colors[ WID_COLOR_TEXT_FG ];
    }

    if (w->cfg[ WID_MODE_OVER ].color_set[ WID_COLOR_BG ]) {
      w_box_args.col_bg = get(w->cfg, WID_MODE_OVER).colors[ WID_COLOR_BG ];
    } else {
      w_box_args.col_bg = get(w->cfg, WID_MODE_NORMAL).colors[ WID_COLOR_BG ];
    }
  } else {
    w_box_args.col_text = get(w->cfg, WID_MODE_NORMAL).colors[ WID_COLOR_TEXT_FG ];
    w_box_args.col_bg   = get(w->cfg, WID_MODE_NORMAL).colors[ WID_COLOR_BG ];
  }

  if (w->square) {
    ascii_put_box(w_box_args, wid_get_style(w), w->tiles, L"");
  } else {
    // shape none
  }

  {
    //
    // Set the tiles this widget is over, taking into account the scissors
    // if the parent is resized.
    //
    // CON("%d,%d to @%d,%d %s %p", tl.x, tl.y, br.x, br.y, w->name.c_str(), w);
    for (auto x = tl.x; x < br.x; x++) {
      if (unlikely(! ascii_x_ok(x))) {
        continue;
      }
      for (auto y = tl.y; y < br.y; y++) {
        if (unlikely(! ascii_y_ok(y))) {
          continue;
        }

        if (ascii_ok_for_scissors(x, y)) {
          set(wid_on_screen_at, x, y, w);
        }
      }
    }
  }

  if (w->on_display) {
    (w->on_display)(w, tl, br);
  }

  if (! text.empty()) {
    int x, y;
    int xpc, ypc;
    int width, height;

    //
    // Manually specified text position.
    //
    width  = ascii_strlen(text);
    height = 0;

    if (wid_get_text_pos(w, &xpc, &ypc)) {
      x = (owidth * xpc) - ((int) width / 2) + otlx;
      y = (oheight * ypc) - ((int) height / 2) + otly;
    } else {
      //
      // Position the text
      //
      if (((int) width > owidth) && w->show_cursor) {
        //
        // If the text is too big, center it on the cursor.
        //
        x = ((owidth - (int) width) / 2) + otlx;

        uint32_t c_width = (width / (double) text.length());

        x -= (w->cursor - (text.length() / 2)) * c_width;
      } else if (wid_get_text_lhs(w)) {
        x = otlx;
      } else if (wid_get_text_centerx(w)) {
        x = ((owidth - (int) width) / 2) + otlx;
      } else if (wid_get_text_rhs(w)) {
        x = obrx - (int) width + 1;
      } else {
        x = ((owidth - (int) width) / 2) + otlx;
      }

      if (wid_get_text_top(w)) {
        y = otly;
      } else if (wid_get_text_centery(w)) {
        y = ((oheight - (int) height) / 2) + otly;
      } else if (wid_get_text_bot(w)) {
        y = obry - (int) height + 1;
      } else {
        y = ((oheight - (int) height) / 2) + otly;
      }
    }

    if (w->cfg[ mode ].color_set[ WID_COLOR_TEXT_FG ] && w->cfg[ mode ].color_set[ WID_COLOR_TEXT_BG ]) {
      ascii_putf__(x, y, w_box_args.col_text, w_box_args.col_bg, text);
    } else if (w->cfg[ mode ].color_set[ WID_COLOR_TEXT_FG ]) {
      ascii_putf__(x, y, w_box_args.col_text, COLOR_NONE, text);
    } else if (w->cfg[ mode ].color_set[ WID_COLOR_TEXT_BG ]) {
      ascii_putf__(x, y, WHITE, w_box_args.col_bg, text);
    } else {
      ascii_putf__(x, y, w_box_args.col_text, COLOR_NONE, text);
    }
  }

  for (auto iter = w->children_display_sorted.begin(); iter != w->children_display_sorted.end(); ++iter) {

    auto child = iter->second;

    uint8_t child_updated_scissors = false;

    wid_display(child, disable_scissor, &child_updated_scissors, clip);

    //
    // Need to re-enforce the parent's scissors if the child did
    // their own bit of scissoring?
    //
    if (! disable_scissor && child_updated_scissors) {
      wid_set_scissors(tlx, tly, brx, bry);
    }
  }
}

//
// Do stuff for all widgets.
//
void wid_move_all(void)
{
  TRACE_NO_INDENT();
  if (wid_top_level3.empty()) {
    return;
  }

  uint32_t N = wid_top_level3.size();
  Widp     w {};
  Widp     wids[ N ];
  uint32_t n = 0;

  for (auto &iter : wid_top_level3) {
    auto w    = iter.second;
    wids[ n ] = w;
    n++;
  }

  while (n--) {
    w = wids[ n ];

    double x;
    double y;

    if (wid_time >= w->ts_moving_end) {
      wid_move_dequeue(w);

      //
      // If nothing else in the move queue, we're dine.
      //
      if (! w->moving) {
        continue;
      }
    }

    double time_step = (double) (wid_time - w->ts_moving_begin) / (double) (w->ts_moving_end - w->ts_moving_begin);

    x = (time_step * (double) (w->moving_end.x - w->moving_start.x)) + w->moving_start.x;
    y = (time_step * (double) (w->moving_end.y - w->moving_start.y)) + w->moving_start.y;

    wid_move_to_abs(w, x, y);
  }
}

//
// Delayed destroy?
//
static void wid_gc(Widp w)
{
  TRACE_NO_INDENT();
  WID_DBG(w, "gc");

  if (w->being_destroyed) {
    wid_destroy_immediate(w);
    return;
  }

  if (w->destroy_when && (wid_time >= w->destroy_when)) {
    wid_destroy(&w);
  }
}

//
// Do stuff for all widgets.
//
void wid_gc_all(void)
{
  TRACE_NO_INDENT();
  std::vector< Widp > to_gc;

  for (;;) {
    if (! wid_top_level4.size()) {
      return;
    }
    auto i = wid_top_level4.begin();
    auto w = i->second;

    wid_gc(w);
  }
}

//
// Do stuff for all widgets.
//
static void wid_tick_all(void)
{
  TRACE_NO_INDENT();
  wid_time = time_ms_cached();

  std::list< Widp > work;
  for (auto &iter : wid_tick_top_level) {
    auto w = iter.second;
    work.push_back(w);
  }

  for (auto &w : work) {
    if (! w->on_tick) {
      ERR("Wid on ticker tree, but no callback set");
    }

    (w->on_tick)(w);
  }
}

//
// Do stuff for all widgets.
//
static void wid_handle_requests(void)
{
  TRACE_NO_INDENT();

  //
  // If the console is visible, don't create any new windows
  //
  if (wid_console_window && wid_console_window->visible) {
    return;
  }

  //
  // Allow updating the rightbar even if things are moving. Else we end up never
  // updating it if the player is waiting.
  //
  switch (game->state) {
    case Game::STATE_CHOOSING_TARGET :
      //
      // Allow to remake the skillbox when choosing a target, so that we can highlight
      // the skill or spell as active whilst choosing.
      // /
    case Game::STATE_NORMAL :
      //
      // If we need to remake the rightbar, do so
      //
      if (game->request_to_remake_rightbar || game->request_to_remake_skillbox || game->request_to_remake_spellbox) {
        DBG("Handle request to remake rightbar");
        wid_leftbar_init();
        if (wid_rightbar_init()) {
          game->unset_request_to_remake_rightbar();
          game->unset_request_to_remake_skillbox();
          game->unset_request_to_remake_spellbox();
        }
        wid_actionbar_init();
        game->unset_request_to_remake_actionbar();
      }
      break;

    case Game::STATE_INVENTORY :
    case Game::STATE_COLLECTING_ITEMS :
    case Game::STATE_ENCHANTING_ITEMS :
    case Game::STATE_CHOOSING_SKILLS :
    case Game::STATE_CHOOSING_SPELLS :
    case Game::STATE_CHOOSING_LEVEL :
    case Game::STATE_LOAD_MENU :
    case Game::STATE_KEYBOARD_MENU :
    case Game::STATE_SAVE_MENU :
    case Game::STATE_QUIT_MENU : break;
    default : ERR("Unhandled game state"); break;
  }

  //
  // Wait until everything stops moving, or we can get into tricky situations like when changing
  // graphics modes with things that had not finished moving to their tile.
  //
  if (game->things_are_moving) {
    return;
  }

  //
  // If we need to destroy the thing info, do so
  //
  if (game->request_destroy_thing_info) {
    if (time_have_x_tenths_passed_since(1, game->request_destroy_thing_info)) {
      DBG("Handle request to destroy thing info");
      game->request_destroy_thing_info = false;
      wid_thing_info_fini("wid request destroy info");
    }
  }

  //
  // If we need to destroy the thing info, do so
  //
  if (game->request_destroy_tp_info) {
    if (time_have_x_tenths_passed_since(1, game->request_destroy_tp_info)) {
      DBG("Handle request to destroy thing info");
      game->request_destroy_tp_info = false;
      wid_tp_info_fini("wid request destroy info");
    }
  }

  //
  // Update the inventory if needed. This is valid in both normal and inventory states.
  //
  if (game->request_to_update_inventory_thing_select) {
    DBG("Inventory: handle over selected thing");
    wid_inventory_select(game->request_inventory_thing_select);
    game->request_inventory_thing_select = nullptr;
    game->unset_request_to_update_inventory_thing_select();
  }

  switch (game->state) {
    case Game::STATE_NORMAL :
      //
      // Update the actionbar
      //
      if (game->request_to_remake_actionbar) {
        DBG("Handle request to remake actionhar");
        wid_actionbar_init();
        game->unset_request_to_remake_actionbar();
      }

      //
      // Switch between graphics modes.
      //
      if (game->request_to_toggle_gfx) {
        game->request_to_toggle_gfx = false;
        g_opt_ascii                 = ! g_opt_ascii;

        //
        // We lose the console as it is resized. However I don't want to lose the logs
        // if we change mode, so save and then restore them.
        //
        auto old_logs = wid_console_serialize();

        sdl_display_reset();

        //
        // Now back with the old logs!
        //
        wid_console_deserialize(old_logs);

        if (g_opt_ascii) {
          BOTCON("ASCII mode");
        } else {
          BOTCON("Pixel art mode");
        }
      }

      if (game->request_recreate_cursor_path) {
        game->request_recreate_cursor_path = false;
        if (game->level && game->level->player) {
          //
          // cursor_recreate seems to cause a flicker here where the cursor briefly
          // appears back over the player.
          //
          pcg_random_allowed++;
          game->level->cursor_path_create(game->level->player);
          pcg_random_allowed--;
        }
      }

      //
      // Drive closure of the inventory if we're waiting on it.
      //
      if (wid_inventory_window) {
        if (game->robot_mode) {
          if (game->tick_requested.empty()) {
            game->tick_begin("Robot close inventory");
          }
        }
      }

      break;

    case Game::STATE_INVENTORY :
      //
      // Update the inventory if needed
      //
      if (game->request_to_update_inventory_thing_over) {
        DBG2("Inventory: handle over thing");
        wid_inventory_over(game->request_inventory_thing_over);
        game->request_inventory_thing_over = nullptr;
        game->unset_request_to_update_inventory_thing_over();
      }

      if (game->request_to_remake_inventory) {
        DBG2("Handle request to remake inventory");
        wid_inventory_init();
        game->unset_request_to_remake_inventory();
      }
      break;
    case Game::STATE_COLLECTING_ITEMS :
    case Game::STATE_ENCHANTING_ITEMS :
    case Game::STATE_CHOOSING_SKILLS :
    case Game::STATE_CHOOSING_SPELLS :
    case Game::STATE_CHOOSING_TARGET :
    case Game::STATE_CHOOSING_LEVEL :
    case Game::STATE_LOAD_MENU :
    case Game::STATE_KEYBOARD_MENU :
    case Game::STATE_SAVE_MENU :
    case Game::STATE_QUIT_MENU : break;
    default : ERR("Unhandled game state"); break;
  }
}

static void wid_tick_all_post_display(void)
{
  TRACE_NO_INDENT();
  wid_time = time_ms_cached();

  if (wid_console_window->visible) {
    return;
  }

  std::list< Widp > work;
  for (auto &iter : wid_tick_post_display_top_level) {
    auto w = iter.second;
    work.push_back(w);
  }

  for (auto &w : work) {
    if (! w->on_tick_post_display) {
      ERR("Wid on tick_post_displayer tree, but no callback set");
    }

    (w->on_tick_post_display)(w);
  }
}

static int saved_mouse_x;
static int saved_mouse_y;

void wid_mouse_hide(int value)
{
  TRACE_NO_INDENT();
  int visible = ! value;

  if (visible != wid_mouse_visible) {
    wid_mouse_visible = visible;
    if (visible) {
      sdl_mouse_warp(saved_mouse_x, saved_mouse_y);
    } else {
      saved_mouse_x = sdl.mouse_x;
      saved_mouse_y = sdl.mouse_y;
    }
  }
}

void wid_mouse_warp(Widp w)
{
  TRACE_NO_INDENT();
  int tlx, tly, brx, bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int x = (tlx + brx) / 2.0;
  int y = (tly + bry) / 2.0;

  sdl_mouse_warp(x, y);
}

void wid_mouse_move(Widp w)
{
  TRACE_NO_INDENT();
  int tlx, tly, brx, bry;

  wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

  int x = (tlx + brx) / 2.0;
  int y = (tly + bry) / 2.0;

  saved_mouse_x = sdl.mouse_x;
  saved_mouse_y = sdl.mouse_y;

  sdl.mouse_x = x;
  sdl.mouse_y = y;
}

//
// Display all widgets
//
void wid_display_all(bool ok_to_handle_requests)
{
  TRACE_NO_INDENT();
  ascii_clear_display();

  //
  // A bit faster to avoid this when flushing the display
  //
  if (ok_to_handle_requests) {
    TRACE_NO_INDENT();
    wid_handle_requests();
  }

  TRACE_NO_INDENT();
  gl_leave_2d_mode();
  gl_enter_2d_mode(game->config.ui_pix_width, game->config.ui_pix_height);
  blit_fbo_bind_locked(FBO_WID);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClear(GL_COLOR_BUFFER_BIT);
  glcolor(WHITE);

  TRACE_NO_INDENT();
  wid_tick_all();

  TRACE_NO_INDENT();
  wid_move_all();

  // CON("---------------------------------");

  wid_on_screen_at = {};

  wid_total_count = 0;

  auto wid_top_level_copy = wid_top_level;
  for (auto iter = wid_top_level_copy.begin(); iter != wid_top_level_copy.end(); ++iter) {
    auto w = iter->second;
    verify(MTYPE_WID, w);

    if (w->parent) {
      verify(MTYPE_WID, w->parent);
    }

    if (wid_is_hidden(w)) {
      continue;
    }

#if 0
auto last = wid_total_count;
#endif
    wid_display(w, false /* disable_scissors */, 0 /* updated_scissors */, true);
    verify(MTYPE_WID, w);
#if 0
printf("%s %d\n", wid_name(w).c_str(), wid_total_count - last);
#endif
  }

#if 0
printf("========================================= %d\n", wid_total_count);
#endif

  if (wid_total_count > 5000) {
    ERR("Too many widgets %d", wid_total_count);
  }

#if 0
  for (auto y = 0; y < TERM_HEIGHT; y++) {
    for (auto x = 0; x < TERM_WIDTH; x++) {
      if (get_no_check(wid_on_screen_at, x, y)) {
        putchar('W');
      } else {
        putchar(' ');
      }
    }
    putchar('\n');
  }
#endif

  ascii_clear_scissors();

#ifdef ENABLE_DEBUG_UI_FOCUS
  if (wid_focus) {
    ascii_putf(0, TERM_HEIGHT - 4, WHITE, GRAY, L"focus %s", to_string(wid_focus).c_str());
  }
  if (wid_over) {
    ascii_putf(0, TERM_HEIGHT - 3, WHITE, GRAY, L"over  %s", to_string(wid_over).c_str());
  }
#endif

  //
  // FPS counter.
  //
  if (game->config.fps_counter) {
    ascii_putf(TERM_WIDTH - 7, TERM_HEIGHT - 1, GREEN, BLACK, L"%u FPS", game->fps_value);
  }

  TRACE_NO_INDENT();
  ascii_display();

  TRACE_NO_INDENT();
  blit_fbo_unbind_locked();

  TRACE_NO_INDENT();
  wid_tick_all_post_display();

  //
  // Need this to reset wid_over after display
  //
  wid_update_mouse();

  gl_leave_2d_mode();
  gl_enter_2d_mode(game->config.window_pix_width, game->config.window_pix_height);
}

uint8_t wid_is_hidden(Widp w)
{
  TRACE_NO_INDENT();
  if (unlikely(! w)) {
    return false;
  }

  IF_DEBUG3 { verify(MTYPE_WID, w); }

  if (w->hidden) {
    return true;
  }

  while (w->parent) {
    w = w->parent;

    if (w->hidden) {
      return true;
    }
  }

  return false;
}

uint8_t wid_is_always_hidden(Widp w)
{
  TRACE_NO_INDENT();
  if (w->always_hidden) {
    return true;
  }

  return false;
}

void wid_move_to_pct(Widp w, double x, double y)
{
  TRACE_NO_INDENT();
  if (! w->parent) {
    x *= (double) TERM_WIDTH;
    y *= (double) TERM_HEIGHT;
  } else {
    x *= wid_get_width(w->parent);
    y *= wid_get_height(w->parent);
  }

  double dx = x - wid_get_tl_x(w);
  double dy = y - wid_get_tl_y(w);

  wid_move_delta(w, dx, dy);
}

void wid_move_to_abs(Widp w, int x, int y)
{
  TRACE_NO_INDENT();
  int dx = x - wid_get_tl_x(w);
  int dy = y - wid_get_tl_y(w);

  wid_move_delta(w, dx, dy);
}

void wid_move_to_pct_centered(Widp w, double ox, double oy)
{
  TRACE_NO_INDENT();

  double x = ox;
  double y = oy;

  if (! w->parent) {
    x *= (double) TERM_WIDTH;
    y *= (double) TERM_HEIGHT;
  } else {
    x *= wid_get_width(w->parent);
    y *= wid_get_height(w->parent);
  }

  double dx = x - wid_get_tl_x(w);
  double dy = y - wid_get_tl_y(w);

  dx -= ceil(wid_get_br_x(w) - wid_get_tl_x(w)) / 2;
  dy -= ceil(wid_get_br_y(w) - wid_get_tl_y(w)) / 2;

  wid_move_delta(w, dx, dy);

  //
  // Account for rounding errors if we can fit the window in the screen and it is
  // now one character offscreen.
  //
  if ((ox == 0.5) && (oy == 0.5)) {
    int tlx;
    int tly;
    int brx;
    int bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    if ((bry >= TERM_HEIGHT - 1) && (tly > 0)) {
      wid_move_delta(w, 0, -1);
    } else if ((tly < 0) && (bry < TERM_HEIGHT - 1)) {
      wid_move_delta(w, 0, 1);
    }

    if ((brx >= TERM_WIDTH - 1) && (tlx > 0)) {
      wid_move_delta(w, -1, 0);
    } else if ((tlx < 0) && (brx < TERM_WIDTH - 1)) {
      wid_move_delta(w, 1, 0);
    }
  }
}

void wid_move_to_abs_centered(Widp w, int x, int y)
{
  TRACE_NO_INDENT();
  int dx = x - wid_get_tl_x(w);
  int dy = y - wid_get_tl_y(w);

  dx -= ceil((wid_get_br_x(w) - wid_get_tl_x(w)) / 2);
  dy -= ceil((wid_get_br_y(w) - wid_get_tl_y(w)) / 2);

  wid_move_delta(w, dx, dy);
}

static void wid_move_enqueue(Widp w, int moving_start_x, int moving_start_y, int moving_end_x, int moving_end_y,
                             uint32_t ms)
{
  TRACE_NO_INDENT();
  w->moving_start.x  = moving_start_x;
  w->moving_start.y  = moving_start_y;
  w->moving_end.x    = moving_end_x;
  w->moving_end.y    = moving_end_y;
  w->ts_moving_begin = wid_time;
  w->ts_moving_end   = wid_time + ms;

  wid_tree3_moving_wids_insert(w);

  w->moving++;
}

static void wid_move_dequeue(Widp w)
{
  TRACE_NO_INDENT();
  if (! w->moving) {
    return;
  }

  wid_move_to_abs(w, w->moving_end.x, w->moving_end.y);

  w->moving--;
  if (! w->moving) {
    wid_tree3_moving_wids_remove(w);
    return;
  }

  wid_move_t *c = &getref(w->move, 0);

  w->moving_start.x  = w->moving_end.x;
  w->moving_start.y  = w->moving_end.y;
  w->moving_end.x    = c->moving_endx;
  w->moving_end.y    = c->moving_endy;
  w->ts_moving_begin = wid_time;
  w->ts_moving_end   = c->ts_moving_end;

  uint8_t i;
  for (i = 0; i < w->moving; i++) {
    if (i < WID_MAX_MOVE_QUEUE - 1) {
      wid_move_t *c = &getref(w->move, i);
      memcpy(c, c + 1, SIZEOF(*c));
    }
  }

  {
    wid_move_t *c = &getref(w->move, i);
    memset(c, 0, SIZEOF(*c));
  }
}

void wid_move_to_pct_in(Widp w, double x, double y, uint32_t ms)
{
  TRACE_NO_INDENT();
  if (! w->parent) {
    x *= (double) TERM_WIDTH;
    y *= (double) TERM_HEIGHT;
  } else {
    x *= wid_get_width(w->parent);
    y *= wid_get_height(w->parent);
  }

  //
  // Child postion is relative from the parent.
  //
  Widp p = w->parent;
  if (p) {
    x += wid_get_tl_x(p);
    y += wid_get_tl_y(p);
  }

  wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_abs_in(Widp w, int x, int y, uint32_t ms)
{
  TRACE_NO_INDENT();
  wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_delta_in(Widp w, int dx, int dy, uint32_t ms)
{
  TRACE_NO_INDENT();
  int x = wid_get_tl_x(w);
  int y = wid_get_tl_y(w);

  wid_move_enqueue(w, x, y, x + dx, y + dy, ms);
}

void wid_move_to_pct_centered_in(Widp w, double x, double y, uint32_t ms)
{
  TRACE_NO_INDENT();
  if (! w->parent) {
    x *= (double) TERM_WIDTH;
    y *= (double) TERM_HEIGHT;
  } else {
    x *= wid_get_width(w->parent);
    y *= wid_get_height(w->parent);
  }

  //
  // Child postion is relative from the parent.
  //
  Widp p = w->parent;
  if (p) {
    x += wid_get_tl_x(p);
    y += wid_get_tl_y(p);
  }

  x -= (wid_get_br_x(w) - wid_get_tl_x(w)) / 2;
  y -= (wid_get_br_y(w) - wid_get_tl_y(w)) / 2;

  wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_abs_centered_in(Widp w, int x, int y, uint32_t ms)
{
  TRACE_NO_INDENT();
  x -= (wid_get_br_x(w) - wid_get_tl_x(w)) / 2;
  y -= (wid_get_br_y(w) - wid_get_tl_y(w)) / 2;

  wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_centered_in(Widp w, int x, int y, uint32_t ms)
{
  TRACE_NO_INDENT();
  wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

uint8_t wid_is_moving(Widp w)
{
  if (w->moving) {
    return true;
  }

  return false;
}

void wid_ignore_events_briefly(void)
{
  if (! time_have_x_tenths_passed_since(10, wid_ignore_events_briefly_ts)) {
    return;
  }

  wid_ignore_events_briefly_ts = time_ms_cached();
}

bool wid_some_recent_event_occurred(void)
{
  //
  // If a widget has just closed for example or been recreated, don't
  // immediately allow a double click on a chasm that was behind the
  // widget for example.
  //
  if (! time_have_x_tenths_passed_since(2, wid_last_over_event)) {
    // DBG("wid_some_recent_event_occurred: Too soon since last wid over event");
    return true;
  }

  if (! time_have_x_tenths_passed_since(1, wid_ignore_events_briefly_ts)) {
    // DBG("wid_some_recent_event_occurred: Too soon since last ignore event");
    return true;
  }

  //
  // If over the map_mini allows clicks to move us
  //
  // Else, ignore clicks as they should go to a widget
  //
  if (game->map_mini_over == point(-1, -1)) {
    auto w = wid_find_under_mouse();
    if (w) {
      if (w->name != "wid topcon window") {
        // DBG("wid_some_recent_event_occurred: Over wid ignore event: %s %p", w->name.c_str(), w);
        return true;
      }
    }
  }

  return false;
}
