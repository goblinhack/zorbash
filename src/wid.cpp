/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_main.h"
#include "my_slre.h"
#include "my_wid.h"
#include "my_tex.h"
#include "my_tile.h"
#include "my_tile_info.h"
#include "my_command.h"
#include "my_time_util.h"
#include "my_wid_console.h"
#include "my_math_util.h"
#include "my_thing.h"
#include "my_wid_tiles.h"
#include "my_game.h"
#include "my_string.h"
#include "my_ascii.h"
#include "my_glapi.h"
#include "my_game.h"
#include <stdlib.h>

#define WID_FULL_LOGNAME
#undef DEBUG_WID_MOTION
#undef DEBUG_WID_FOCUS

#ifdef ENABLE_INVERTED_GFX
static bool inverted_gfx = true;
#else
static bool inverted_gfx = false;
#endif

/*
 * Display sorted.
 */
static wid_key_map_location wid_top_level;

/*
 * Creation sorted and global.
 */
static wid_key_map_int wid_global;

/*
 * Creation sorted and per wid parent.
 */
static wid_key_map_int wid_top_level2;

/*
 * For moving things.
 */
static wid_key_map_int wid_top_level3;

/*
 * For garbage collection.
 */
static wid_key_map_int wid_top_level4;

/*
 * For ticking things.
 */
static wid_key_map_int wid_top_level5;

/*
 * Mouse movement
 */
static widp wid_popup_tooltip;
static widp wid_popup_tooltip2;

std::wstring wid_tooltip_string;
std::wstring wid_tooltip2_string;

/*
 * Scope the focus to children of this widget and do not change it.
 * Good for popups.
 */
static widp wid_focus_locked;
static widp wid_focus;
static widp wid_over;

/*
 * Mouse
 */
int wid_mouse_visible = 1;

/*
 * Widget moving
 */
static widp wid_moving;
static int32_t wid_moving_last_x;
static int32_t wid_moving_last_y;

static uint32_t wid_time;

/*
 * Widget effects
 */
const int32_t wid_destroy_delay_ms = 200;

/*
 * Prototypes.
 */
static void wid_destroy_delay(widp *wp, int32_t delay);
static uint8_t wid_scroll_trough_mouse_down(widp w, int32_t x, int32_t y,
                                            uint32_t button);
static uint8_t wid_scroll_trough_mouse_motion(widp w,
                                              int32_t x, int32_t y,
                                              int32_t relx, int32_t rely,
                                              int32_t wheelx, int32_t wheely);
static void wid_find_first_focus(void);
static void wid_find_top_focus(void);
static void wid_destroy_immediate(widp w);
static void wid_destroy_immediate_internal(widp w);
static void wid_update_internal(widp w);
static void wid_tree_detach(widp w);
static void wid_tree_attach(widp w);
static void wid_tree_remove(widp w);
static void wid_tree2_unsorted_remove(widp w);
static void wid_tree3_moving_wids_remove(widp w);
static void wid_tree3_moving_wids_insert(widp w);
static void wid_tree4_wids_being_destroyed_remove(widp w);
static void wid_tree4_wids_being_destroyed_insert(widp w);
static void wid_tree5_ticking_wids_remove(widp w);
static void wid_tree5_ticking_wids_insert(widp w);
static void wid_move_dequeue(widp w);
static void wid_display(widp w,
                        uint8_t disable_scissor,
                        uint8_t *updated_scissors,
                        int clip);

/*
 * Child sort priority
 */
static int32_t wid_highest_priority = 1;
static int32_t wid_lowest_priority = -1;

/*
 * History for all text widgets.
 */
#define HISTORY_MAX 16
std::wstring history[HISTORY_MAX];
uint32_t history_at;
uint32_t history_walk;

/*
 * A tile over the mouse pointer
 */
widp wid_mouse_template;
static widp wid_on_screen_at[ASCII_WIDTH][ASCII_HEIGHT];

static uint8_t wid_init_done;
static uint8_t wid_exiting;

static int wid_refresh_overlay_count;

uint8_t wid_init (void)
{_
    wid_init_done = true;

    return (true);
}

void wid_fini (void)
{_
    if (wid_init_done) {
        wid_init_done = false;
        wid_exiting = true;

        wid_gc_all();

        {
            auto iter = wid_top_level.begin();

            while (iter != wid_top_level.end()) {
                auto child = iter->second;
                wid_destroy_immediate(child);
                iter = wid_top_level.begin();
            }
        }
    }
}

void wid_dump (widp w, int depth)
{_
    if (!w) {
        return;
    }

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    printf("\n          %*s dump: [%s] text [%S] tip [%S] [%S] %d,%d to %d,%d ", depth * 2, "", wid_name(w).c_str(), wid_get_text(w).c_str(), w->tooltip.c_str(), w->tooltip2.c_str(), tlx, tly, brx, bry);

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_dump(child, depth + 2);
    }
}

int32_t wid_get_cx (widp w)
{_
    int32_t cx = (w->key.tl.x + w->key.br.x) / 2.0;

    return (cx);
}

int32_t wid_get_cy (widp w)
{_
    int32_t cy = (w->key.tl.y + w->key.br.y) / 2.0;

    return (cy);
}

int32_t wid_get_tl_x (widp w)
{_
    int32_t cx = (w->key.tl.x + w->key.br.x) / 2.0;

    return (cx - (cx - w->key.tl.x));
}

int32_t wid_get_tl_y (widp w)
{_
    int32_t cy = (w->key.tl.y + w->key.br.y) / 2.0;

    return (cy - (cy - w->key.tl.y));
}

int32_t wid_get_br_x (widp w)
{_
    int32_t cx = (w->key.tl.x + w->key.br.x) / 2.0;

    return (cx + (w->key.br.x - cx));
}

int32_t wid_get_br_y (widp w)
{_
    int32_t cy = (w->key.tl.y + w->key.br.y) / 2.0;

    return (cy + (w->key.br.y - cy));
}

void wid_get_tl_x_tl_y_br_x_br_y (widp w,
                                  int32_t *tl_x,
                                  int32_t *tl_y,
                                  int32_t *br_x,
                                  int32_t *br_y)
{_
    const int32_t tlx = w->key.tl.x;
    const int32_t tly = w->key.tl.y;
    const int32_t brx = w->key.br.x;
    const int32_t bry = w->key.br.y;

    const int32_t cx = (tlx + brx) / 2.0;
    const int32_t cy = (tly + bry) / 2.0;

    *tl_x = cx - (cx - tlx);
    *tl_y = cy - (cy - tly);
    *br_x = cx + (brx - cx);
    *br_y = cy + (bry - cy);
}

/*
 * Set the wid new co-ords. Returns true if there is a change.
 */
void wid_set_pos (widp w, point tl, point br)
{_
    verify(w.get());

    widp p;

    wid_tree_detach(w);

    w->key.tl = tl;
    w->key.br = br;

    /*
     * Child postion is relative from the parent.
     */
    p = w->parent;
    if (p) {
        w->key.tl.x += wid_get_tl_x(p);
        w->key.tl.y += wid_get_tl_y(p);
        w->key.br.x += wid_get_tl_x(p);
        w->key.br.y += wid_get_tl_y(p);
    }

    w->can_be_attached_now = true;
    wid_tree_attach(w);
}

/*
 * Set the wid new co-ords. Returns true if there is a change.
 */
void wid_set_pos_pct (widp w, fpoint tl, fpoint br)
{_
    verify(w.get());

    widp p;

    wid_tree_detach(w);

    if (!w->parent) {
        tl.x *= ASCII_WIDTH;
        tl.y *= ASCII_HEIGHT;
        br.x *= ASCII_WIDTH;
        br.y *= ASCII_HEIGHT;
    } else {
        tl.x *= wid_get_width(w->parent);
        tl.y *= wid_get_height(w->parent);
        br.x *= wid_get_width(w->parent);
        br.y *= wid_get_height(w->parent);
    }

    int32_t key_tl_x = tl.x;
    int32_t key_tl_y = tl.y;
    int32_t key_br_x = br.x;
    int32_t key_br_y = br.y;

    /*
     * Child postion is relative from the parent.
     */
    p = w->parent;
    if (p) {
        key_tl_x += wid_get_tl_x(p);
        key_tl_y += wid_get_tl_y(p);
        key_br_x += wid_get_tl_x(p);
        key_br_y += wid_get_tl_y(p);
    }

    w->key.tl.x = (int)round(key_tl_x);
    w->key.tl.y = (int)round(key_tl_y);
    w->key.br.x = (int)round(key_br_x);
    w->key.br.y = (int)round(key_br_y);

    w->can_be_attached_now = true;
    wid_tree_attach(w);
}

/*
 * Set the wid new co-ords. Returns true if there is a change.
 */
void wid_setx_tl_br_pct (widp w, fpoint tl, fpoint br)
{_
    verify(w.get());

    widp p;

    wid_tree_detach(w);

    if (!w->parent) {
        tl.x *= (double)ASCII_WIDTH;
        br.x *= (double)ASCII_WIDTH;
    } else {
        tl.x *= wid_get_width(w->parent);
        br.x *= wid_get_width(w->parent);
    }

    w->key.tl.x = round(tl.x);
    w->key.br.x = round(br.x);

    /*
     * Child postion is relative from the parent.
     */
    p = w->parent;
    if (p) {
        w->key.tl.x += wid_get_tl_x(p);
        w->key.br.x += wid_get_tl_x(p);
    }

    w->can_be_attached_now = true;
    wid_tree_attach(w);
}

/*
 * Set the wid new co-ords. Returns true if there is a change.
 */
void wid_sety_tl_br_pct (widp w, fpoint tl, fpoint br)
{_
    verify(w.get());

    widp p;

    wid_tree_detach(w);

    if (!w->parent) {
        tl.y *= (double)ASCII_HEIGHT;
        br.y *= (double)ASCII_HEIGHT;
    } else {
        tl.y *= wid_get_height(w->parent);
        br.y *= wid_get_height(w->parent);
    }

    w->key.tl.y = round(tl.y);
    w->key.br.y = round(br.y);

    /*
     * Child postion is relative from the parent.
     */
    p = w->parent;
    if (p) {
        w->key.tl.y += wid_get_tl_y(p);
        w->key.br.y += wid_get_tl_y(p);
    }

    w->can_be_attached_now = true;
    wid_tree_attach(w);
}

void wid_get_tl_br (widp w, point *tl, point *br)
{_
    verify(w.get());

    *tl = w->key.tl;
    *br = w->key.br;
}

void wid_set_pos_no_relative_offset (widp w, point tl, point br)
{_
    wid_tree_detach(w);

    w->key.tl = tl;
    w->key.br = br;

    w->can_be_attached_now = true;
    wid_tree_attach(w);
}

void wid_set_context (widp w, void *context)
{_
    verify(w.get());

    w->context = context;
}

void *wid_get_context (widp w)
{_
    return (w->context);
}

void wid_set_prev (widp w, widp prev)
{_
    verify(w.get());

    if (w == prev) {
        ERR("wid list loop");
    }

    w->prev = prev;

    if (prev) {
        prev->next = w;
    }
}

widp wid_get_prev (widp w)
{_

    if (w->prev == w) {
        ERR("wid list get prev loop");
    }

    return (w->prev);
}

widp wid_get_next (widp w)
{_
    if (w->next == w) {
        ERR("wid list get next loop");
    }

    return (w->next);
}

static widp wid_get_head (widp w)
{_
    widp prev;

    while (w) {

        prev = wid_get_prev(w);
        if (!prev) {
            break;
        }

        w = prev;
    }

    return (w);
}

static widp wid_get_tail (widp w)
{_
    widp next;

    while (w) {

        next = wid_get_next(w);
        if (!next) {
            break;
        }

        w = next;
    }

    return (w);
}

widp wid_get_top_parent (widp w)
{_
    if (!w) {
        return (0);
    }

    if (!w->parent) {
        return (w);
    }

    while (w->parent) {
        w = w->parent;
    }

    return (w);
}

widp wid_get_parent (widp w)
{_
    if (!w) {
        return (0);
    }

    return (w->parent);
}

widp wid_get_scrollbar_vert (widp w)
{_
    if (!w) {
        return (0);
    }

    return (w->scrollbar_vert);
}

widp wid_get_scrollbar_horiz (widp w)
{_
    if (!w) {
        return (0);
    }

    return (w->scrollbar_horiz);
}

static void wid_mouse_motion_end (void)
{_
    wid_moving = 0;
}

void wid_set_ignore_events (widp w, uint8_t val)
{_
    w->ignore_events = val;
}

static void wid_set_scissors (int tlx, int tly, int brx, int bry)
{_
    ascii_set_scissors(point(tlx, tly), point(brx, bry));
}

/*
 * Should this widget be ignored for events?
 */
uint8_t wid_ignore_events (widp w)
{_
    widp top;

    if (!w) {
        return (true);
    }

    verify(w.get());

    if (w->ignore_events || w->moving || w->hidden || w->being_destroyed) {
        return (true);
    }

    if (w->parent) {
        top = wid_get_top_parent(w);

        if (top->moving || top->hidden || top->being_destroyed) {
            return (true);
        }
    }

    return (false);
}

uint8_t wid_ignore_for_focus (widp w)
{_
    widp top;

    if (w->hidden ||
        w->being_destroyed) {
        return (true);
    }

    if (w->parent) {
        top = wid_get_top_parent(w);

        if (top->hidden ||
            top->being_destroyed) {
            return (true);
        }
    }

    return (false);
}

/*
 * Should this widget be ignored for events?
 */
uint8_t wid_ignore_being_destroyed (widp w)
{_
    widp top;

    if (w->being_destroyed) {
        return (true);
    }

    if (w->parent) {
        top = wid_get_top_parent(w);

        if (top->being_destroyed) {
            return (true);
        }
    }

    return (false);
}

static void wid_mouse_motion_begin (widp w, int32_t x, int32_t y)
{_
    wid_mouse_motion_end();

    if (wid_ignore_being_destroyed(w)) {
        return;
    }

    wid_moving = w;
    wid_moving_last_x = x;
    wid_moving_last_y = y;
}

static void wid_mfocus_e (void)
{_
    widp w;

    w = wid_focus;
    wid_focus = 0;
    wid_focus_locked = 0;

    if (!w) {
        return;
    }

    if (w.get()->on_m_focus_e) {
        w.get()->on_m_focus_e(w);
    }
}

widp wid_get_current_focus (void)
{_
    return (wid_focus);
}

static void wid_mfocus_b (widp w)
{_
    widp top;

    if (!w) {
        wid_mfocus_e();
        wid_focus = 0;

        wid_find_top_focus();
        return;
    }

    if (wid_focus == w) {
        return;
    }

    wid_mfocus_e();

    if (wid_ignore_for_focus(w)) {
        return;
    }

    top = wid_get_top_parent(w);

    wid_focus = w;
    top->focus_last = w->focus_order;

    if (w.get()->on_m_focus_b) {
        w.get()->on_m_focus_b(w);
    }
}

static void wid_m_over_e (void)
{_
    widp w;

    if (!wid_mouse_visible) {
        return;
    }

    w = wid_over;
    wid_over = 0;

    if (!w) {
        return;
    }

    wid_set_mode(w, WID_MODE_NORMAL);

    /*
     * Python can try and do cleanup - and if we're exiting already, no point.
     */
    if (wid_exiting) {
        return;
    }

    if (w.get()->on_m_over_e) {
        w.get()->on_m_over_e(w);
    }
}

void wid_tooltip_set (std::wstring text)
{_
    if (!wid_tooltip_string.empty()) {
        if (wid_tooltip_string == text) {
            return;
        }

        wid_destroy(&wid_popup_tooltip);
    }

    wid_tooltip_string = text;
}

void wid_tooltip2_set (std::wstring text)
{_
    if (!wid_tooltip2_string.empty()) {
        if (wid_tooltip2_string == text) {
            return;
        }

        wid_destroy(&wid_popup_tooltip2);
    }

    wid_tooltip2_string = text;
}

static uint8_t wid_m_over_b (widp w, uint32_t x, uint32_t y,
                             int32_t relx, int32_t rely,
                             int32_t wheelx, int32_t wheely)
{_
    if (!wid_mouse_visible) {
        return (false);
    }

    if (wid_over == w) {
        return (true);
    }

    verify(w.get());

    if (!(w.get()->on_m_over_b)) {
        if (w->cfg[WID_MODE_OVER].color_set[WID_COLOR_BG] ||
            w->cfg[WID_MODE_OVER].color_set[WID_COLOR_TEXT]) {
            /*
             * Changes appearance on mouse over, so choose this wid even
             * if it has no over callback.
             */
        } else {
            /*
             * Can ignore. It doesn't really do anything when the mouse
             * is over.
             */
            return (false);
        }
    }

    if (wid_ignore_being_destroyed(w)) {
        return (false);
    }

    wid_m_over_e();

    wid_over = w;

    wid_set_mode(w, WID_MODE_OVER);

    if (w.get()->on_m_over_b) {
        (w.get()->on_m_over_b)(w, relx, rely, wheelx, wheely);
    }

    if (!w->tooltip.empty()) {
        if (!wid_tooltip_string.empty()) {
            if (wid_tooltip_string == w->tooltip) {
                return (true);
            }

            wid_destroy(&wid_popup_tooltip);
        }

        wid_tooltip_string = w->tooltip;
    }

    if (!w->tooltip2.empty()) {
        if (!wid_tooltip2_string.empty()) {
            if (wid_tooltip2_string == w->tooltip2) {
                return (true);
            }

            wid_destroy(&wid_popup_tooltip2);
        }
        wid_tooltip2_string = w->tooltip2;
    }

    return (true);
}

/*
 * Map an SDL key event to the char the user typed
 */
static char wid_event_to_char (const struct SDL_KEYSYM *evt)
{_
    switch (evt->mod) {
        case KMOD_LSHIFT:
        case KMOD_RSHIFT:
            switch (evt->sym) {
                case SDLK_a: return ('A');
                case SDLK_b: return ('B');
                case SDLK_c: return ('C');
                case SDLK_d: return ('D');
                case SDLK_e: return ('E');
                case SDLK_f: return ('F');
                case SDLK_g: return ('G');
                case SDLK_h: return ('H');
                case SDLK_i: return ('I');
                case SDLK_j: return ('J');
                case SDLK_k: return ('K');
                case SDLK_l: return ('L');
                case SDLK_m: return ('M');
                case SDLK_n: return ('N');
                case SDLK_o: return ('O');
                case SDLK_p: return ('P');
                case SDLK_q: return ('Q');
                case SDLK_r: return ('R');
                case SDLK_s: return ('S');
                case SDLK_t: return ('T');
                case SDLK_u: return ('U');
                case SDLK_v: return ('V');
                case SDLK_w: return ('W');
                case SDLK_x: return ('X');
                case SDLK_y: return ('Y');
                case SDLK_z: return ('Z');
                case SDLK_QUOTE: return ('\'');
                case SDLK_COMMA: return ('<');
                case SDLK_MINUS: return ('_');
                case SDLK_PERIOD: return ('>');
                case SDLK_SLASH: return ('?');
                case SDLK_EQUALS: return ('+');
                case SDLK_0: return (')');
                case SDLK_1: return ('!');
                case SDLK_2: return ('"');
                case SDLK_3: return ('#');
                case SDLK_4: return ('$');
                case SDLK_5: return ('%');
                case SDLK_6: return ('^');
                case SDLK_7: return ('&');
                case SDLK_8: return ('*');
                case SDLK_9: return ('(');
                case SDLK_SEMICOLON: return (':');
                case SDLK_LEFTBRACKET: return ('{');
                case SDLK_BACKSLASH: return ('|');
                case SDLK_RIGHTBRACKET: return ('}');
                case SDLK_HASH: return ('~');

            default:
                break;
            }

        case KMOD_LALT:
        case KMOD_RALT:
            switch (evt->sym) {
                default:
                break;
            }

        case KMOD_LCTRL:
        case KMOD_RCTRL:
            switch (evt->sym) {
                default:
                break;
            }

        default:
            break;
    }

    switch (evt->sym) {
        case SDLK_BACKSPACE: return ('');
        case SDLK_TAB: return ('\t');
        case SDLK_RETURN: return ('\n');
        case SDLK_ESCAPE: return ('');
        case SDLK_SPACE: return (' ');
        case SDLK_EXCLAIM: return ('!');
        case SDLK_QUOTEDBL: return ('"');
        case SDLK_HASH: return ('#');
        case SDLK_DOLLAR: return ('$');
        case SDLK_AMPERSAND: return ('%');
        case SDLK_QUOTE: return ('\'');
        case SDLK_LEFTPAREN: return ('(');
        case SDLK_RIGHTPAREN: return (')');
        case SDLK_ASTERISK: return ('*');
        case SDLK_PLUS: return ('+');
        case SDLK_COMMA: return (',');
        case SDLK_MINUS: return ('-');
        case SDLK_PERIOD: return ('.');
        case SDLK_SLASH: return ('/');
        case SDLK_0: return ('0');
        case SDLK_1: return ('1');
        case SDLK_2: return ('2');
        case SDLK_3: return ('3');
        case SDLK_4: return ('4');
        case SDLK_5: return ('5');
        case SDLK_6: return ('6');
        case SDLK_7: return ('7');
        case SDLK_8: return ('8');
        case SDLK_9: return ('9');
        case SDLK_COLON: return (':');
        case SDLK_SEMICOLON: return (';');
        case SDLK_LESS: return ('<');
        case SDLK_EQUALS: return ('=');
        case SDLK_GREATER: return ('>');
        case SDLK_QUESTION: return ('?');
        case SDLK_AT: return ('@');
        case SDLK_LEFTBRACKET: return ('[');
        case SDLK_BACKSLASH: return ('\\');
        case SDLK_RIGHTBRACKET: return (']');
        case SDLK_CARET: return ('^');
        case SDLK_UNDERSCORE: return ('_');
        case SDLK_BACKQUOTE: return ('`');
        case SDLK_a: return ('a');
        case SDLK_b: return ('b');
        case SDLK_c: return ('c');
        case SDLK_d: return ('d');
        case SDLK_e: return ('e');
        case SDLK_f: return ('f');
        case SDLK_g: return ('g');
        case SDLK_h: return ('h');
        case SDLK_i: return ('i');
        case SDLK_j: return ('j');
        case SDLK_k: return ('k');
        case SDLK_l: return ('l');
        case SDLK_m: return ('m');
        case SDLK_n: return ('n');
        case SDLK_o: return ('o');
        case SDLK_p: return ('p');
        case SDLK_q: return ('q');
        case SDLK_r: return ('r');
        case SDLK_s: return ('s');
        case SDLK_t: return ('t');
        case SDLK_u: return ('u');
        case SDLK_v: return ('v');
        case SDLK_w: return ('w');
        case SDLK_x: return ('x');
        case SDLK_y: return ('y');
        case SDLK_z: return ('z');
        case SDLK_DELETE: return ('');
#if SDL_MAJOR_VERSION == 1 /* { */
        case SDLK_KP0: return ('0');
        case SDLK_KP1: return ('1');
        case SDLK_KP2: return ('2');
        case SDLK_KP3: return ('3');
        case SDLK_KP4: return ('4');
        case SDLK_KP5: return ('5');
        case SDLK_KP6: return ('6');
        case SDLK_KP7: return ('7');
        case SDLK_KP8: return ('8');
        case SDLK_KP9: return ('9');
#else
        case SDLK_KP_0: return ('0');
        case SDLK_KP_1: return ('1');
        case SDLK_KP_2: return ('2');
        case SDLK_KP_3: return ('3');
        case SDLK_KP_4: return ('4');
        case SDLK_KP_5: return ('5');
        case SDLK_KP_6: return ('6');
        case SDLK_KP_7: return ('7');
        case SDLK_KP_8: return ('8');
        case SDLK_KP_9: return ('9');
#endif /* } */
        case SDLK_KP_PERIOD: return ('.');
        case SDLK_KP_DIVIDE: return ('/');
        case SDLK_KP_MULTIPLY: return ('*');
        case SDLK_KP_MINUS: return ('-');
        case SDLK_KP_PLUS: return ('+');
        case SDLK_KP_ENTER: return ('\0');
        case SDLK_KP_EQUALS: return ('=');
        case SDLK_UP: return ('\0');
        case SDLK_DOWN: return ('\0');
        case SDLK_RIGHT: return ('\0');
        case SDLK_LEFT: return ('\0');
        case SDLK_INSERT: return ('\0');
        case SDLK_HOME: return ('\0');
        case SDLK_END: return ('\0');
        case SDLK_PAGEUP: return ('\0');
        case SDLK_PAGEDOWN: return ('\0');
        case SDLK_F1: return ('\0');
        case SDLK_F2: return ('\0');
        case SDLK_F3: return ('\0');
        case SDLK_F4: return ('\0');
        case SDLK_F5: return ('\0');
        case SDLK_F6: return ('\0');
        case SDLK_F7: return ('\0');
        case SDLK_F8: return ('\0');
        case SDLK_F9: return ('\0');
        case SDLK_F10: return ('\0');
        case SDLK_F11: return ('\0');
        case SDLK_F12: return ('\0');
        case SDLK_F13: return ('\0');
        case SDLK_F14: return ('\0');
        case SDLK_F15: return ('\0');
        case SDLK_CAPSLOCK: return ('\0');
        case SDLK_RSHIFT: return ('\0');
        case SDLK_LSHIFT: return ('\0');
        case SDLK_RCTRL: return ('\0');
        case SDLK_LCTRL: return ('\0');
        case SDLK_RALT: return ('\0');
        case SDLK_LALT: return ('\0');
        case SDLK_MODE: return ('\0');
        case SDLK_HELP: return ('!');
        case SDLK_SYSREQ: return ('\0');
        case SDLK_MENU: return ('\0');
        case SDLK_POWER: return ('\0');
        case SDLK_UNDO: return ('\0');
        default: return ('\0');
    }
    return ('\0');
}

/*
 * Widget mode, whether it is active, inactive etc...
 */
void wid_set_mode (widp w, wid_mode mode)
{_
    verify(w.get());

    w->timestamp_last_mode_change = wid_time;
    w->mode = mode;
}

/*
 * Widget mode, whether it is active, inactive etc...
 */
wid_mode wid_get_mode (widp w)
{_
    /*
     * Allow focus to override less important modes.
     */
    if (w == wid_focus) {
        if ((w->mode == WID_MODE_NORMAL) || (w->mode == WID_MODE_OVER)) {
            return (WID_MODE_FOCUS);
        }
    }

    return (w->mode);
}

std::string wid_logname (widp w)
{_
    verify(w.get());

    return (w->logname);
}

std::string wid_name (widp w)
{_
    verify(w.get());

    return (w->name);
}

std::wstring wid_get_text (widp w)
{_
    verify(w.get());

    return (w->text);
}

std::string wid_get_name (widp w)
{_
    verify(w.get());

    return (w->name);
}

std::wstring wid_get_tooltip (widp w)
{_
    verify(w.get());

    return (w->tooltip);
}

std::wstring wid_get_text_with_cursor (widp w)
{_
    if (!w->received_input) {
        w->cursor = (uint32_t)w->text.length();
    }

    std::wstring t = w->text;
    std::wstring o = t.substr(0, w->cursor) + ASCII_CURSOR_UCHAR + 
                    t.substr(w->cursor);

    return (o);
}

void wid_set_name (widp w, std::string name)
{_
    verify(w.get());

    w->name = name;
}

void wid_set_debug (widp w, uint8_t val)
{_
    w->debug = val;
}

void wid_set_text (widp w, std::wstring text)
{_
    verify(w.get());

    if (text == L"") {
        w->text = L"";
    } else {
        if (text == w->text) {
            return;
        }

        w->text = text;
    }

    auto len = w->text.size();
    if (w->cursor > len) {
        w->cursor = len;
    }
}

void wid_set_tooltip (widp w, std::wstring name)
{_
    verify(w.get());

    w->tooltip = name;
}

void wid_set_tooltip2 (widp w, std::wstring name)
{_
    verify(w.get());

    w->tooltip2 = name;
}

uint8_t wid_get_received_input (widp w)
{_
    return (w->received_input);
}

void wid_set_received_input (widp w, uint8_t val)
{_
    verify(w.get());

    w->received_input = val;
}

uint32_t wid_get_cursor (widp w)
{_
    return (w->cursor);
}

void wid_set_cursor (widp w, uint32_t val)
{_
    verify(w.get());

    w->cursor = val;
}

int32_t wid_get_width (widp w)
{_
    return (wid_get_br_x(w) - wid_get_tl_x(w));
}

int32_t wid_get_height (widp w)
{_
    int32_t h = (wid_get_br_y(w) - wid_get_tl_y(w));
    if (!h) {
        return (1);
    }
    return (h);
}

void wid_get_mxy (widp w, int32_t *x, int32_t *y)
{_
    *x = (wid_get_br_x(w) + wid_get_tl_x(w)) / 2.0;
    *y = (wid_get_br_y(w) + wid_get_tl_y(w)) / 2.0;
}

uint8_t wid_get_focusable (widp w)
{_
    return (w->focus_order);
}

void wid_set_focusable (widp w, uint8_t val)
{_
    verify(w.get());

    w->focus_order = val;
}

uint8_t wid_get_show_cursor (widp w)
{_
    return (w->show_cursor);
}

void wid_set_show_cursor (widp w, uint8_t val)
{_
    verify(w.get());

    w->show_cursor = val;
}

uint8_t wid_get_do_not_raise (widp w)
{_
    return (w->do_not_raise);
}

void wid_set_do_not_raise (widp w, uint8_t val)
{_
    verify(w.get());

    w->do_not_raise = val;
}

uint8_t wid_get_do_not_lower (widp w)
{_
    return (w->do_not_lower);
}

void wid_set_do_not_lower (widp w, uint8_t val)
{_
    verify(w.get());

    w->do_not_lower = val;
}

uint8_t wid_get_movable (widp w)
{_
    if (w->movable_set) {
        return (w->movable);
    }

    return (false);
}

void wid_set_movable (widp w, uint8_t val)
{_
    verify(w.get());

    w->movable = val;
    w->movable_set = true;

    wid_set_movable_horiz(w, val);
    wid_set_movable_vert(w, val);
}

uint8_t wid_get_movable_horiz (widp w)
{_
    if (w->movable_horiz_set) {
        return (w->movable_horiz);
    }

    return (false);
}

void wid_set_movable_horiz (widp w, uint8_t val)
{_
    verify(w.get());

    w->movable_horiz = val;
    w->movable_horiz_set = true;
}

uint8_t wid_get_movable_vert (widp w)
{_
    if (w->movable_vert_set) {
        return (w->movable_vert);
    }

    return (false);
}

void wid_set_movable_vert (widp w, uint8_t val)
{_
    verify(w.get());

    w->movable_vert = val;
    w->movable_vert_set = true;
}

uint8_t wid_get_movable_bounded (widp w)
{_
    if (w->movable_bounded_set) {
        return (w->movable_bounded);
    }

    return (false);
}

void wid_set_movable_bounded (widp w, uint8_t val)
{_
    verify(w.get());

    w->movable_bounded = val;
    w->movable_bounded_set = true;
}

uint8_t wid_get_movable_no_user_scroll (widp w)
{_
    if (w->movable_no_user_scroll_set) {
        return (w->movable_no_user_scroll);
    }

    return (false);
}

void wid_set_movable_no_user_scroll (widp w, uint8_t val)
{_
    verify(w.get());

    w->movable_no_user_scroll = val;
    w->movable_no_user_scroll_set = true;
}

uint8_t wid_get_text_lhs (widp w)
{_
    return (w->text_lhs);
}

void wid_set_text_lhs (widp w, uint8_t val)
{_
    verify(w.get());

    w->text_lhs = val;
}

uint8_t wid_get_text_rhs (widp w)
{_
    return (w->text_rhs);
}

void wid_set_text_rhs (widp w, uint8_t val)
{_
    verify(w.get());

    w->text_rhs = true;
}

uint8_t wid_get_text_centerx (widp w)
{_
    return (w->text_centerx);
}

void wid_set_text_centerx (widp w, uint8_t val)
{_
    verify(w.get());

    w->text_centerx = val;
}

uint8_t wid_get_text_top (widp w)
{_
    return (w->text_top);
}

void wid_set_text_top (widp w, uint8_t val)
{_
    verify(w.get());

    w->text_top = val;
}

uint8_t wid_get_text_bot (widp w)
{_
    return (w->text_bot);
}

void wid_set_text_bot (widp w, uint8_t val)
{_
    verify(w.get());

    w->text_bot = val;
}

uint8_t wid_get_text_centery (widp w)
{_
    return (w->text_centery);
}

void wid_set_text_centery (widp w, uint8_t val)
{_
    verify(w.get());

    w->text_centery = val;
}

uint8_t wid_get_text_pos (widp w, int32_t *x, int32_t *y)
{_
    if (w->text_pos_set) {
        *x = w->text_pos.x;
        *y = w->text_pos.y;

        return (true);
    }

    return (false);
}

void wid_set_text_pos (widp w, uint8_t val, int32_t x, int32_t y)
{_
    verify(w.get());

    w->text_pos.x = x;
    w->text_pos.y = y;
    w->text_pos_set = val;
}

Texp wid_get_tex (widp w, fsize *size)
{_
    if (size) {
        *size = w->texuv;
    }

    return (w->tex);
}

void wid_set_tex (widp w, std::string tex, std::string name)
{_
    verify(w.get());

    if ((tex == "") && (name == "")) {
        w->tex = 0;
        return;
    }

    Texp t = tex_load(tex, name, GL_NEAREST);
    if (!t) {
        ERR("failed to set wid tex %s", tex.c_str());
    }

    w->tex = t;

    fsize sz = {
        (double) tex_get_width(t),
        (double) tex_get_height(t)
    };

    wid_set_tex_sz(w, sz);
}

void wid_set_tex_sz (widp w, fsize uv)
{_
    verify(w.get());

    w->texuv = uv;
}

Tilep wid_get_tile (widp w)
{_
    return (w->tile);
}

Tpp wid_get_thing_template (widp w)
{_
    verify(w.get());

    return (w->tp);
}

void wid_set_tilename (widp w, std::string name)
{_
    verify(w.get());

    Tilep tile = tile_find(name);
    if (!tile) {
        ERR("failed to find wid tile %s", name.c_str());
    }

    if (!w) {
        DIE("widget does not exist to set tile %s", name.c_str());
    }

    w->tile = tile;
    if (!w->first_tile) {
        w->first_tile = tile;
    }
}

void wid_set_thing_template (widp w, Tpp t)
{_
    verify(w.get());

    w->tp = t;

    if (!t) {
        wid_set_tile(w, 0);
        return;
    }

    auto tiles = tp_get_tiles(t);
    auto tile = tile_info_first(tiles);
    if (!tile) {
        return;
    }

    wid_set_tilename(w, tile_info_name(tile));

    wid_set_name(w, tp_name(t));
}

fsize wid_get_tex_tl (widp w)
{_
    if (w->tex_tl_set) {
        return (w->tex_tl);
    }

    fsize nosize = {0, 0};
    return (nosize);
}

void wid_set_tex_tl (widp w, fsize val)
{_
    verify(w.get());

    w->tex_tl_set = true;
    w->tex_tl = val;
}

fsize wid_get_tex_br (widp w)
{_
    if (w->tex_br_set) {
        return (w->tex_br);
    }

    fsize size = {1, 1};
    return (size);
}

void wid_set_tex_br (widp w, fsize val)
{_
    verify(w.get());

    w->tex_br_set = true;
    w->tex_br = val;
}

/*
 * Look at all the wid modes and return the most relevent setting
 */
color wid_get_color (widp w, wid_color which)
{_
    uint32_t mode = (__typeof__(mode)) wid_get_mode(w); // for c++, no enum walk
    wid_cfg *cfg = &w->cfg[mode];

    if (cfg->color_set[which]) {
        return (cfg->colors[which]);
    }

    if ((wid_focus == w) && (wid_over == w)) {
        mode = WID_MODE_OVER;
        cfg = &w->cfg[mode];
        if (cfg->color_set[which]) {
            return (cfg->colors[which]);
        }
    }

    mode = WID_MODE_NORMAL;
    cfg = &w->cfg[mode];
    if (cfg->color_set[which]) {
        return (cfg->colors[which]);
    }

    return (WHITE);
}

/*
 * Look at all the wid modes and return the most relevent setting
 */
color wid_get_mode_color (widp w, wid_color which)
{_
    uint32_t mode = (__typeof__(mode)) wid_get_mode(w); // for c++, no enum walk
    wid_cfg *cfg = &w->cfg[mode];

    return (cfg->colors[which]);
}

/*
 * Look at all the widset modes and return the most relevent setting
 */
void wid_set_color (widp w, wid_color col, color val)
{_
    verify(w.get());

    w->cfg[wid_get_mode(w)].colors[col] = val;
    w->cfg[wid_get_mode(w)].color_set[col] = true;
}

void wid_set_offset (widp w, point offset)
{_
    verify(w.get());

    w->offset = offset;
}

void wid_get_offset (widp w, point *offset)
{_
    verify(w.get());

    *offset = w->offset;
}

void wid_set_focus (widp w)
{_
    /*
     * Don't allow focus override if hard focus is set.
     */
    if (w) {
        if (wid_focus_locked) {
            if (wid_get_top_parent(w) != wid_focus_locked) {
                return;
            }
        }

        if (!w->focus_order) {
            return;
        }
    }

    wid_mfocus_b(w);
}

void wid_set_shape_square (widp w)
{
    w->square = true;
    w->box = false;
}

void wid_set_shape_none (widp w)
{
    w->square = false;
    w->box = false;
}

void wid_set_shape_box (widp w)
{
    w->square = false;
    w->box = true;
}

void wid_set_active (widp w)
{_
    wid_set_mode(w, WID_MODE_ACTIVE);
}

void wid_focus_lock (widp w)
{_
    if (w.get()) {
        WID_DBG(w, "focus locked");
    }

    wid_focus_locked = w;
}

void wid_set_on_key_down (widp w, on_key_down_t fn)
{_
    verify(w.get());

    w.get()->on_key_down = fn;
}

void wid_set_on_key_up (widp w, on_key_up_t fn)
{_
    verify(w.get());

    w.get()->on_key_up = fn;
}

void wid_set_on_joy_button (widp w, on_joy_button_t fn)
{_
    verify(w.get());

    w.get()->on_joy_button = fn;
}

void wid_set_on_m_down (widp w, on_m_down_t fn)
{_
    verify(w.get());

    w.get()->on_m_down = fn;
}

void wid_set_on_m_up (widp w, on_m_up_t fn)
{_
    verify(w.get());

    w.get()->on_m_up = fn;
}

void wid_set_on_m_motion (widp w, on_m_motion_t fn)
{_
    verify(w.get());

    w.get()->on_m_motion = fn;
}

void wid_set_on_m_focus_b (widp w, on_m_focus_b_t fn)
{_
    verify(w.get());

    w.get()->on_m_focus_b = fn;
}

void wid_set_on_m_focus_e (widp w, on_m_focus_e_t fn)
{_
    verify(w.get());

    w.get()->on_m_focus_e = fn;
}

void wid_set_on_m_over_b (widp w, on_m_over_b_t fn)
{_
    verify(w.get());

    w.get()->on_m_over_b = fn;
}

void wid_set_on_m_over_e (widp w, on_m_over_e_t fn)
{_
    verify(w.get());

    w.get()->on_m_over_e = fn;
}

void wid_set_on_destroy (widp w, on_destroy_t fn)
{_
    verify(w.get());

    w.get()->on_destroy = fn;
}

void wid_set_on_destroy_b (widp w, on_destroy_t fn)
{_
    verify(w.get());

    w.get()->on_destroy_b = fn;
}

void wid_set_on_tick (widp w, on_tick_t fn)
{_
    verify(w.get());

    if (!fn) {
        ERR("no ticker function set");
    }

    w.get()->on_tick = fn;

    wid_tree5_ticking_wids_insert(w);
}

/*
 * Remove this wid from any trees it is in.
 */
static void wid_tree_detach (widp w)
{_
    verify(w.get());

    wid_tree_remove(w);
}

/*
 * Add back to all trees.
 */
static void wid_tree_attach (widp w)
{_
    verify(w.get());

    wid_key_map_location *root;

    if (w->in_tree_root) {
        DIE("wid is already attached");
    }

    if (!w->parent) {
        root = &wid_top_level;
    } else {
        root = &w->parent->children_display_sorted;
    }

    auto result = root->insert(std::make_pair(w->key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] failed", wid_get_name(w).c_str());
    }

    w->in_tree_root = root;
}

static void wid_tree_insert (widp w)
{_
    verify(w.get());

    static uint64_t key;

    if (w->in_tree_root) {
        DIE("wid is already inserted");
    }

    wid_key_map_location *root;

    /*
     * Get a wid sort ID.
     */
    w->key.key = ++key;

    if (!w->parent) {
        root = &wid_top_level;
    } else {
        root = &w->parent->children_display_sorted;
    }

    auto result = root->insert(std::make_pair(w->key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] failed", wid_get_name(w).c_str());
    }

    w->in_tree_root = root;
}

static void wid_tree_global_unsorted_insert (widp w)
{_
    verify(w.get());

    static wid_key_type key;

    if (w->in_tree_global_unsorted_root) {
        DIE("wid is already in the global tree");
    }

    auto root = &wid_global;

    key.val++;

    w->tree_global_key = key;
    auto result = root->insert(std::make_pair(w->tree_global_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree_global failed", wid_get_name(w).c_str());
    }

    w->in_tree_global_unsorted_root = root;
}

static void wid_tree2_unsorted_insert (widp w)
{_
    verify(w.get());

    static uint64_t key;

    if (w->in_tree2_unsorted_root) {
        DIE("wid is already in the in_tree2_unsorted_root");
    }

    wid_key_map_int *root;

    if (!w->parent) {
        root = &wid_top_level2;
    } else {
        root = &w->parent->tree2_children_unsorted;
    }

    w->tree2_key = ++key;
    auto result = root->insert(std::make_pair(w->tree2_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree2 failed", wid_get_name(w).c_str());
    }

    w->in_tree2_unsorted_root = root;
}

static void wid_tree3_moving_wids_insert (widp w)
{_
    verify(w.get());

    if (w->in_tree3_moving_wids) {
        return;
    }

    if (wid_exiting) {
        return;
    }

    static uint64_t key;
    wid_key_map_int *root = &wid_top_level3;

    w->tree3_key = ++key;
    auto result = root->insert(std::make_pair(w->tree3_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree3 failed", wid_get_name(w).c_str());
    }

    w->in_tree3_moving_wids = root;
}

static void wid_tree4_wids_being_destroyed_insert (widp w)
{_
    verify(w.get());

    if (w->in_tree4_wids_being_destroyed) {
        return;
    }

    if (wid_exiting) {
        return;
    }

    static uint64_t key;

    wid_key_map_int *root;

    root = &wid_top_level4;

    w->tree4_key = ++key;
    auto result = root->insert(std::make_pair(w->tree4_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree4 failed", wid_get_name(w).c_str());
    }

    w->in_tree4_wids_being_destroyed = root;
}

static void wid_tree5_ticking_wids_insert (widp w)
{_
    verify(w.get());

    if (w->in_tree5_ticking_wids) {
        return;
    }

    if (wid_exiting) {
        return;
    }

    static uint64_t key;

    wid_key_map_int *root;

    root = &wid_top_level5;

    w->tree5_key = ++key;
    auto result = root->insert(std::make_pair(w->tree5_key, w));
    if (result.second == false) {
        DIE("wid insert name [%s] tree5 failed", wid_get_name(w).c_str());
    }

    w->in_tree5_ticking_wids = root;
}

static void wid_tree_remove (widp w)
{_
    verify(w.get());

    wid_key_map_location *root;

    root = w->in_tree_root;
    if (!root) {
        return;
    }

    auto result = root->find(w->key);
    if (result == root->end()) {
        DIE("wid tree did not find wid hence cannot remove it");
    }

    root->erase(w->key);

    w->in_tree_root = nullptr;
}

static void wid_tree2_unsorted_remove (widp w)
{_
    verify(w.get());

    auto root = w->in_tree2_unsorted_root;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree2_key);
    if (result == root->end()) {
        DIE("wid tree2 did not find wid");
    }
    root->erase(w->tree2_key);

    w->in_tree2_unsorted_root = nullptr;
}

static void wid_tree_global_unsorted_remove (widp w)
{_
    verify(w.get());

    auto root = w->in_tree_global_unsorted_root;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree_global_key);
    if (result == root->end()) {
        DIE("wid tree_global did not find wid");
    }
    root->erase(w->tree_global_key);

    w->in_tree_global_unsorted_root = nullptr;
}

widp wid_unsorted_find (wid_key_type key)
{_
    auto root = &wid_global;

    if (!key.val) {
        return (nullptr);
    }

    auto result = root->find(key.val);
    if (result == root->end()) {
        ERR("wid unsorted find did not find wid, %" PRIu64, key.val);
        return (0);
    }

    auto w = result->second;

    verify(w.get());

    return (w);
}

wid_key_type wid_unsorted_get_key (widp w)
{_
    verify(w.get());

    auto root = &wid_global;

    auto result = root->find(w->tree_global_key);
    if (result == root->end()) {
        DIE("wid unsorted did not find wid");
    }

    w = result->second;

    verify(w.get());

    return (w->tree_global_key);
}

static void wid_tree3_moving_wids_remove (widp w)
{_
    verify(w.get());

    auto root = w->in_tree3_moving_wids;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree3_key);
    if (result == root->end()) {
        DIE("wid tree3 did not find wid");
    }
    root->erase(w->tree3_key);

    w->in_tree3_moving_wids = nullptr;
}

static void wid_tree4_wids_being_destroyed_remove (widp w)
{_
    verify(w.get());

    auto root = w->in_tree4_wids_being_destroyed;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree4_key);
    if (result == root->end()) {
        DIE("wid tree4 did not find wid");
    }
    root->erase(w->tree4_key);

    w->in_tree4_wids_being_destroyed = nullptr;
}

static void wid_tree5_ticking_wids_remove (widp w)
{_
    verify(w.get());

    auto root = w->in_tree5_ticking_wids;
    if (!root) {
        return;
    }

    auto result = root->find(w->tree5_key);
    if (result == root->end()) {
        DIE("wid tree5 did not find wid");
    }
    root->erase(w->tree5_key);

    w->in_tree5_ticking_wids = nullptr;
    w->on_tick = 0;
}

/*
 * Initialize a wid with basic settings
 */
static widp wid_new (widp parent)
{_
    auto w = std::make_shared< class wid >();

    w->parent = parent;
    w->timestamp_created = wid_time;

    WID_DBG(w, "new");

    wid_tree_insert(w);
    wid_tree2_unsorted_insert(w);
    wid_tree_global_unsorted_insert(w);

    /*
     * Give some lame 3d to the wid
     */
    wid_set_mode(w, WID_MODE_NORMAL);

    fsize sz = {0.0f, 0.0f};
    wid_set_tex_tl(w, sz);

    fsize sz2 = {1.0f, 1.0f};
    wid_set_tex_br(w, sz2);

    w->visible = true;

    return (w);
}

static void wid_destroy_immediate_internal (widp w)
{_
    verify(w.get());

    wid_tree3_moving_wids_remove(w);
    wid_tree4_wids_being_destroyed_remove(w);
    wid_tree5_ticking_wids_remove(w);

    if (w.get()->on_destroy) {
        (w.get()->on_destroy)(w);
    }

    if (wid_focus == w) {
        wid_mfocus_e();
    }

    if (wid_focus_locked == w) {
        wid_focus_locked = 0;
    }

    if (wid_over == w) {
        wid_m_over_e();
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    if (w->scrollbar_vert) {
        w->scrollbar_vert->scrollbar_owner = 0;
    }

    if (w->scrollbar_horiz) {
        w->scrollbar_horiz->scrollbar_owner = 0;
    }

    if (w->scrollbar_owner) {
        if (w->scrollbar_owner->scrollbar_vert == w) {
            w->scrollbar_owner->scrollbar_vert = 0;
        }

        if (w->scrollbar_owner->scrollbar_horiz == w) {
            w->scrollbar_owner->scrollbar_horiz = 0;
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

    w->parent = 0;
}

static void wid_destroy_immediate (widp w)
{_
    verify(w.get());

    /*
     * If removing a top level widget, choose a new focus.
     */
    if (!w->parent) {
        wid_find_top_focus();
    }

    wid_tree_detach(w);

    wid_tree2_unsorted_remove(w);
    wid_tree_global_unsorted_remove(w);

    wid_destroy_immediate_internal(w);

    if (w == wid_popup_tooltip) {
        wid_popup_tooltip = 0;
    }

    if (w == wid_popup_tooltip2) {
        wid_popup_tooltip2 = 0;
    }

    if (w == wid_focus_locked) {
        wid_focus_locked = 0;
    }

    if (w == wid_focus) {
        wid_focus = 0;
    }

    if (w == wid_over) {
        wid_over = 0;
    }

    if (w == wid_moving) {
        wid_moving = 0;
    }
}

static void wid_destroy_delay (widp *wp, int32_t delay)
{_
    widp w;
    widp child;
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    if (!wp) {
        return;
    }

    w = *wp;

    if (!w) {
        return;
    }

    verify(w.get());

    WID_DBG(w, "destroy");

    *wp = 0;

    if (w->being_destroyed) {
        if (delay) {
            return;
        }
    }

    w->being_destroyed = true;
    wid_tree4_wids_being_destroyed_insert(w);

    if (wid_focus == w) {
        wid_mfocus_e();
    }

    if (wid_over == w) {
        wid_m_over_e();
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    for (auto iter : w->tree2_children_unsorted) {
        auto child = iter.second;
        verify(child.get());
        wid_destroy(&child);
    }

    if (!w->parent) {
        wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);
    }

    if (w.get()->on_destroy_b) {
        (w.get()->on_destroy_b)(w);
    }

    /*
     * Make sure it stops ticking right now as client pointers this widget
     * might use in the ticker may no longer be valid.
     */
    wid_tree5_ticking_wids_remove(w);
}

void wid_destroy (widp *wp)
{_
    wid_destroy_delay(wp, wid_destroy_delay_ms);
}

void wid_destroy_nodelay (widp *wp)
{_
    wid_destroy_delay(wp, 0);
}

void wid_destroy_in (widp w, uint32_t ms)
{_
    verify(w.get());

    w->destroy_when = wid_time + ms;

    wid_tree4_wids_being_destroyed_insert(w);
}

void wid_destroy_ptr_in (widp *w, uint32_t ms)
{_
    verify((*w).get());

    (*w)->destroy_when = wid_time + ms;
    (*w)->destroy_ptr = w;

    wid_tree4_wids_being_destroyed_insert(*w);
}

/*
 * Initialize a top level wid with basic settings
 */
widp wid_new_window (std::string name)
{_
    widp w = wid_new(0);

    w->logname = string_sprintf("%s[%p]", name.c_str(), w.get());

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);

    color col = WHITE;
    col.a = 255;
    glcolor(col);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, col);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);
    wid_set_movable(w, false);
    wid_set_shape_box(w);

    return (w);
}

/*
 * Initialize a top level wid with basic settings
 */
widp wid_new_container (widp parent, std::string name)
{_
    widp w = wid_new(parent);

#ifdef WID_FULL_LOGNAME
    w->logname = string_sprintf("%s[%p] (parent %s[%p])", 
                                name.c_str(), w.get(), 
                                parent->logname.c_str(), parent.get());
#else
    w->logname = string_sprintf("%s[%p]", name.c_str(), w.get());
#endif

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);

    color col = BLACK;
    col.a = 0;
    glcolor(col);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, col);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);
    wid_set_shape_square(w);

    return (w);
}

/*
 * Initialize a top level wid with basic settings
 */
widp wid_new_plain (widp parent, std::string name)
{_
    if (!parent) {
        ERR("no parent");
    }

    widp w = wid_new(parent);

#ifdef WID_FULL_LOGNAME
    w->logname = string_sprintf("%s[%p] (parent %s[%p])", 
                                name.c_str(), w.get(), 
                                parent->logname.c_str(), parent.get());
#else
    w->logname = string_sprintf("%s[%p]", name.c_str(), w.get());
#endif

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);
    wid_set_shape_square(w);

    return (w);
}

/*
 * Initialize a top level wid with basic settings
 */
widp wid_new_square_window (std::string name)
{_
    widp w = wid_new(0);

    w->logname = string_sprintf("%s[%p]", name.c_str(), w.get());

    WID_DBG(w, "%s", __FUNCTION__);

    color c;
    color tl;
    color br;

    c = WHITE;
    tl = GRAY80;
    br = GRAY90;

    c.a = 255;
    tl.a = 200;
    br.a = 200;

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_color(w, WID_COLOR_BG, c);
    wid_set_color(w, WID_COLOR_TEXT, WHITE);
    wid_set_movable(w, false);
    wid_set_name(w, name);
    wid_set_shape_box(w);

    wid_raise(w);

    return (w);
}

widp wid_new_square_button (widp parent, std::string name)
{_
    if (!parent) {
        ERR("no parent");
    }

    widp w = wid_new(parent);

#ifdef WID_FULL_LOGNAME
    w->logname = string_sprintf("%s[%p] (parent %s[%p])", 
                                name.c_str(), w.get(), 
                                parent->logname.c_str(), parent.get());
#else
    w->logname = string_sprintf("%s[%p]", name.c_str(), w.get());
#endif

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);
    wid_set_shape_box(w);

    return (w);
}

/*
 * Initialize a wid with basic settings
 */
static widp wid_new_scroll_trough (widp parent)
{_
    if (!parent) {
        ERR("no parent");
    }

    widp w = wid_new(parent);

    w->logname = string_sprintf("%s[%p]", "scroll trough", w.get());

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_mode(w, WID_MODE_NORMAL); {
        wid_set_color(w, WID_COLOR_BG, GRAY60);
    }

    wid_set_on_m_down(w, wid_scroll_trough_mouse_down);
    wid_set_on_m_motion(w, wid_scroll_trough_mouse_motion);
    wid_set_shape_square(w);

    return (w);
}

/*
 * Initialize a wid with basic settings
 */
static widp wid_new_scroll_bar (widp parent,
                                std::string name,
                                widp scrollbar_owner,
                                uint8_t vertical)
{_
    if (!parent) {
        ERR("no parent");
    }

    color c;
    color tl;
    color br;

    widp w = wid_new(parent);

    if (vertical) {
        w->logname = string_sprintf("%s, %s[%p]", name.c_str(), "vert scroll bar", w.get());
    } else {
        w->logname = string_sprintf("%s, %s[%p]", name.c_str(), "horiz scroll bar", w.get());
    }

    WID_DBG(w, "%s", __FUNCTION__);

    wid_set_name(w, name);

    wid_set_mode(w, WID_MODE_ACTIVE); {
        c = RED;
        wid_set_color(w, WID_COLOR_BG, c);
    }

    wid_set_mode(w, WID_MODE_NORMAL); {
        c = ORANGE;
        wid_set_color(w, WID_COLOR_BG, c);
    }

    wid_set_movable(w, true);
    wid_set_movable_bounded(w, true);
    wid_set_shape_square(w);

    if (vertical) {
        wid_set_movable_vert(w, true);
        wid_set_movable_horiz(w, false);
        scrollbar_owner->scrollbar_vert = w;
    } else {
        wid_set_movable_horiz(w, true);
        wid_set_movable_vert(w, false);
        scrollbar_owner->scrollbar_horiz = w;
    }

    w->scrollbar_owner = scrollbar_owner;

    wid_hide(w);

    return (w);
}

widp wid_new_vert_scroll_bar (widp parent,
                              std::string name,
                              widp scrollbar_owner)
{_
    if (!parent) {
        ERR("no parent");
    }

    point tl;
    point br;

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    int32_t ptlx;
    int32_t ptly;
    int32_t pbrx;
    int32_t pbry;

    /*
     * Make the trough line up with the scrolling window.
     */
    wid_get_abs_coords(parent, &ptlx, &ptly, &pbrx, &pbry);
    wid_get_abs_coords(scrollbar_owner, &tlx, &tly, &brx, &bry);

    tl.x = pbrx;
    tl.y = tly - ptly;
    br.x = pbrx;
    br.y = tl.y + wid_get_br_y(scrollbar_owner) - wid_get_tl_y(scrollbar_owner);

    widp trough = wid_new_scroll_trough(parent);
    wid_set_pos(trough, tl, br);
    wid_set_shape_square(trough);

    {
        fpoint tl;
        fpoint br;

        tl.x = 0.0f;
        tl.y = 0.0f;
        br.x = 1.0f;
        br.y = 1.0f;

        widp scrollbar = wid_new_scroll_bar(trough, name, scrollbar_owner, true);
        wid_set_pos_pct(scrollbar, tl, br);

        wid_update_internal(scrollbar);
        wid_visible(wid_get_parent(scrollbar));
        wid_visible(scrollbar);

        return (scrollbar);
    }
}

widp wid_new_horiz_scroll_bar (widp parent, std::string name,
                               widp scrollbar_owner)
{_
    if (!parent) {
        ERR("no parent");
    }

    point tl;
    point br;

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    int32_t ptlx;
    int32_t ptly;
    int32_t pbrx;
    int32_t pbry;

    /*
     * Make the trough line up with the scrolling window.
     */
    wid_get_abs_coords(parent, &ptlx, &ptly, &pbrx, &pbry);
    wid_get_abs_coords(scrollbar_owner, &tlx, &tly, &brx, &bry);

    tl.x = tlx - ptlx;
    tl.y = tly;
    br.x = tl.x + wid_get_br_x(scrollbar_owner) - wid_get_tl_x(scrollbar_owner);
    br.y = tly;

    widp trough = wid_new_scroll_trough(parent);
    wid_set_pos(trough, tl, br);
    wid_set_shape_square(trough);

    {
        fpoint tl;
        fpoint br;

        tl.x = 0.0f;
        tl.y = 0.0f;
        br.x = 1.0f;
        br.y = 1.0f;

        widp scrollbar = wid_new_scroll_bar(trough, name, scrollbar_owner, false);
        wid_set_pos_pct(scrollbar, tl, br);

        wid_update_internal(scrollbar);
        wid_hide(scrollbar->parent);

        return (scrollbar);
    }
}

static void wid_raise_internal (widp w)
{_
    verify(w.get());
_
    if (w->do_not_raise) {
        return;
    }
_
    if (wid_moving != w) {
        wid_mouse_motion_end();
    }
_
    if (wid_get_top_parent(wid_moving) != w) {
        wid_mouse_motion_end();
    }
_
    wid_tree_detach(w);
    w->key.priority = ++wid_highest_priority;
    wid_tree_attach(w);
}

static void wid_raise_override (widp parent)
{_
    /*
     * If some widget wants to be on top, let it.
     */
    widp w;

    verify(parent.get());

    if (parent->do_not_lower) {
        wid_raise_internal(parent);
    }

    for (auto iter : parent->children_display_sorted) {
        auto w = iter.second;

        verify(w.get());

        if (w->do_not_lower) {
            wid_raise_internal(w);
            break;
        }

        wid_raise_override(w);
    }
}

void wid_raise (widp w_in)
{_
    if (!w_in.get()) {
        return;
    }
_
    verify(w_in.get());
_
    wid_raise_internal(w_in);
_
    /*
     * If some widget wants to be on top, let it.
     */
    std::vector<widp> worklist;
    for (auto iter : wid_top_level) {
        auto w = iter.second;
        worklist.push_back(w);
    }

    for (auto w : worklist) {
        wid_raise_override(w);
    }

    verify(w_in.get());
_
    wid_find_top_focus();
_
    /*
     * If we were hovering over a window and it was replaced, we need to fake
     * a mouse movement so we know we are still over it.
     */
    if (!w_in->parent.get()) {
        wid_update_mouse();
    }
}

static void wid_lower_internal (widp w)
{_
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

void wid_lower (widp w_in)
{_
    if (!w_in) {
        return;
    }

    wid_lower_internal(w_in);

    /*
     * If some widget wants to be on top, let it.
     */
    for (auto iter : wid_top_level) {
        auto w = iter.second;
        if (w->do_not_raise) {
            wid_lower_internal(w);
            break;
        }
    }

    wid_find_top_focus();

    /*
     * If we were hovering over a window and it was replaced, we need to fake
     * a mouse movement so we know we are still over it.
     */
    if (!w_in->parent && !w_in->children_display_sorted.empty()) {
        wid_update_mouse();
    }
}

void wid_toggle_hidden (widp w)
{_
    if (w->hidden) {
        wid_visible(w);
    } else {
        wid_hide(w);
    }
}

static void wid_find_first_child_focus (widp w, widp *best)
{_
    if (w->focus_order) {
        if (!*best) {
            *best = w;
        } else if (w->focus_order < (*best)->focus_order) {
            *best = w;
        }
    }

    widp child;

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        wid_find_first_child_focus(child, best);
    }
}

static void wid_find_first_focus (void)
{_
    widp best;

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        best = 0;
        wid_find_first_child_focus(w, &best);
        if (best) {
            wid_set_focus(best);
            return;
        }
    }
}

static void wid_find_specific_child_focus (widp w, widp *best,
                                           uint8_t focus_order)
{_
    if (w->focus_order) {
        if (w->focus_order == focus_order) {
            *best = w;
            return;
        }
    }

    widp child;

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        wid_find_specific_child_focus(child, best, focus_order);
    }
}

static widp wid_find_top_wid_focus (widp w)
{_
    widp best;

    best = 0;

    if (wid_ignore_for_focus(w)) {
        return (best);
    }

    /*
     * First time we've looked at this widget, hunt for the first focus.
     */
    if (!w->focus_last) {
        wid_find_first_child_focus(w, &best);
        if (best) {
            return (best);
        }
    }

    wid_find_specific_child_focus(w, &best, w->focus_last);
    if (best) {
        return (best);
    }

    return (best);
}

static void wid_find_top_focus (void)
{_
    widp best;

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        best = 0;

        /*
         * First time we've looked at this widget, hunt for the first focus.
         */
        if (!w->focus_last) {
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

static void wid_find_last_child_focus (widp w, widp *best)
{_
    if (w->focus_order) {
        if (!*best) {
            *best = w;
        } else if (w->focus_order > (*best)->focus_order) {
            *best = w;
        }
    }

    widp child;

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_last_child_focus(child, best);
    }
}

widp wid_get_focus (widp w)
{_
    widp best;

    best = 0;

    if (wid_focus) {
        if (wid_get_top_parent(wid_focus) == wid_get_top_parent(w)) {
            return (wid_focus);
        }
    }

    if (!w->focus_last) {
        best = wid_find_top_wid_focus(wid_get_top_parent(w));
        if (best) {
            return (best);
        }
    }

    wid_find_specific_child_focus(w, &best, w->focus_last);

    return (best);
}

static void wid_find_last_focus (void)
{_
    widp best;

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        best = 0;
        wid_find_last_child_focus(w, &best);
        if (best) {
            wid_set_focus(best);
            return;
        }
    }
}

static void wid_find_next_child_focus (widp w, widp *best)
{_
    if (w->focus_order) {
        if (*best) {
            if ((w->focus_order < (*best)->focus_order) &&
                (w->focus_order > wid_focus->focus_order)) {
                *best = w;
            }
        } else if (w->focus_order > wid_focus->focus_order) {
            *best = w;
        }
    }

    widp child;

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        wid_find_next_child_focus(child, best);
    }
}

static void wid_find_next_focus (void)
{_
    widp best;

    if (!wid_focus) {
        wid_find_first_focus();
        return;
    }

    best = 0;
    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        if (!w->focus_last) {
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

static void wid_find_prev_child_focus (widp w, widp *best)
{_
    if (w->focus_order) {
        if (*best) {
            if ((w->focus_order > (*best)->focus_order) &&
                (w->focus_order < wid_focus->focus_order)) {
                *best = w;
            }
        } else if (w->focus_order < wid_focus->focus_order) {
            *best = w;
        }
    }

    widp child;

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        wid_find_prev_child_focus(child, best);
    }
}

static void wid_find_prev_focus (void)
{_
    widp best;

    if (!wid_focus) {
        wid_find_first_focus();
        return;
    }

    best = 0;
    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_ignore_for_focus(w)) {
            continue;
        }

        if (!w->focus_last) {
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

widp wid_find (widp w, std::string name)
{_
    verify(w.get());

    if (w->name == "") {
        return (0);
    }

    if (strcasestr_(w->name.c_str(), name.c_str())) {
        return (w);
    }

    widp child;

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        widp ret;

        ret = wid_find(child, name);
        if (ret) {
            return (ret);
        }
    }

    return (0);
}

void wid_always_hidden (widp w, uint8_t value)
{_
    verify(w.get());

    w->always_hidden = value;
}

void wid_visible (widp w)
{_
    if (!w.get()) {
        return;
    }

    verify(w.get());

    w->visible = true;

    w->hidden = false;

    wid_find_top_focus();
}

void wid_this_visible (widp w)
{_
    if (!w.get()) {
        return;
    }

    verify(w.get());

    w->visible = true;

    w->hidden = false;
}

void wid_hide (widp w)
{_
    verify(w.get());

    if (!w) {
        return;
    }

    w->hidden = true;

    w->visible = false;

    if (wid_over == w) {
        wid_m_over_e();
    }

    if (wid_moving == w) {
        wid_mouse_motion_end();
    }

    if (wid_get_top_parent(wid_over) == w) {
        wid_m_over_e();
    }

    if (wid_get_top_parent(wid_moving) == w) {
        wid_mouse_motion_end();
    }

    if (w == wid_focus) {
        wid_find_top_focus();
    }
}

static uint8_t wid_scroll_trough_mouse_down (widp w,
                                             int32_t x,
                                             int32_t y,
                                             uint32_t button)
{_
    int32_t dx;
    int32_t dy;
    widp child;

    verify(w.get());

    std::vector<widp> worklist;
    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;
        worklist.push_back(child);
    }

    for (auto child : worklist) {
        verify(child.get());

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

        if (!wid_get_movable_horiz(child)) {
            dx = 0;
        }

        if (!wid_get_movable_vert(child)) {
            dy = 0;
        }

        wid_move_delta(child, dx, dy);
    }

    return (true);
}

static uint8_t wid_scroll_trough_mouse_motion (widp w,
                                               int32_t x, int32_t y,
                                               int32_t relx, int32_t rely,
                                               int32_t wheelx, int32_t wheely)
{_
    int32_t dx;
    int32_t dy;
    widp child;

    if ((SDL_BUTTON(SDL_BUTTON_LEFT) & SDL_GetMouseState(0, 0)) ||
        wheely || wheelx) {

        dy = rely ? rely : -wheely;

        dx = relx ? relx : -wheelx;

        dx = ((int)(dx / ASCII_WIDTH)) * ASCII_WIDTH;
        dy = ((int)(dy / ASCII_HEIGHT)) * ASCII_HEIGHT;

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
        return (false);
    }

    std::vector<widp> worklist;
    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;
        worklist.push_back(child);
    }

    for (auto child : worklist) {
        verify(child.get());

        if (dx || dy) {
            wid_set_mode(child, WID_MODE_ACTIVE);
        }

        if (!wid_get_movable_horiz(child)) {
            dx = 0;
        }

        if (!wid_get_movable_vert(child)) {
            dy = 0;
        }

        wid_move_delta(child, dx, dy);
    }

    return (true);
}

static void wid_adjust_scrollbar (widp scrollbar, widp owner)
{_
    double height = wid_get_height(owner);
    double width = wid_get_width(owner);
    double child_height = 0;
    double child_width = 0;
    double scrollbar_width;
    double scrollbar_height;
    double trough_height;
    double trough_width;
    double miny = 0;
    double maxy = 0;
    double minx = 0;
    double maxx = 0;
    double pct;
    uint8_t first = true;
    widp child;

    /*
     * Find out the space that the children take up then use this to
     * adjust the scrollbar dimensions.
     */
    {
        for (auto iter : owner->tree2_children_unsorted) {
            auto child = iter.second;

            int32_t tl_x, tl_y, br_x, br_y;

            wid_get_tl_x_tl_y_br_x_br_y(child, &tl_x, &tl_y, &br_x, &br_y);

            if (first) {
                minx = tl_x;
                miny = tl_y;
                maxx = br_x;
                maxy = br_y;
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

    int32_t ptl_x, ptl_y, pbr_x, pbr_y;
    wid_get_tl_x_tl_y_br_x_br_y(owner, &ptl_x, &ptl_y, &pbr_x, &pbr_y);

    minx -= ptl_x;
    miny -= ptl_y;
    maxx -= ptl_x;
    maxy -= ptl_y;

    child_width = maxx - minx;
    child_height = maxy - miny;

    if (child_width < width) {
        maxx = minx + width;
        child_width = maxx - minx;
    }

    if (child_height < height) {
        maxy = miny + height;
        child_height = maxy - miny;
    }

    if (owner->scrollbar_vert) {
        if (wid_get_movable_vert(scrollbar)) {
            trough_height = wid_get_height(owner->scrollbar_vert->parent);
            scrollbar_height = (int)(trough_height * (height / child_height));

            if (trough_height - scrollbar_height == 0.0f) {
                pct = 0.0f;
            } else {
                pct = (wid_get_tl_y(scrollbar) - 
                       wid_get_tl_y(scrollbar->parent)) /
                        (trough_height - scrollbar_height);
            }

            owner->offset.y = -miny;
            owner->offset.y -= (pct * (child_height - height));

            scrollbar->key.tl.y =
                wid_get_tl_y(scrollbar->parent) +
                pct * (trough_height - scrollbar_height);

            wid_tree_detach(scrollbar);
            scrollbar->key.br.y = wid_get_tl_y(scrollbar) + scrollbar_height;
            wid_tree_attach(scrollbar);

            wid_set_mode(scrollbar, WID_MODE_ACTIVE);
        }
    }

    if (owner->scrollbar_horiz) {
        if (wid_get_movable_horiz(scrollbar)) {
            trough_width = wid_get_width(owner->scrollbar_horiz->parent);
            scrollbar_width = (int)(trough_width * (width / child_width));

            if (trough_width - scrollbar_width == 0.0f) {
                pct = 0.0f;
            } else {
                pct = (wid_get_tl_x(scrollbar) -
                       wid_get_tl_x(scrollbar->parent)) /
                        (trough_width - scrollbar_width);
            }

            owner->offset.x = -minx;
            owner->offset.x -= (pct * (child_width - width));

            scrollbar->key.tl.x =
                wid_get_tl_x(scrollbar->parent) +
                pct * (trough_width - scrollbar_width);

            wid_tree_detach(scrollbar);
            scrollbar->key.br.x = wid_get_tl_x(scrollbar) + scrollbar_width;
            wid_tree_attach(scrollbar);

            wid_set_mode(scrollbar, WID_MODE_ACTIVE);
        }
    }
}

void wid_get_children_size (widp owner, int32_t *w, int32_t *h)
{_
    double height = wid_get_height(owner);
    double width = wid_get_width(owner);
    double child_height = 0;
    double child_width = 0;
    double miny = 0;
    double maxy = 0;
    double minx = 0;
    double maxx = 0;
    uint8_t first = true;
    widp child;

    /*
     * Find out the space that the children take up then use this to
     * adjust the scrollbar dimensions.
     */
    for (auto iter : owner->children_display_sorted) {

        auto child = iter.second;

        verify(child.get());

        int32_t tminx = wid_get_tl_x(child) - wid_get_tl_x(child->parent);
        int32_t tminy = wid_get_tl_y(child) - wid_get_tl_y(child->parent);
        int32_t tmaxx = wid_get_br_x(child) - wid_get_tl_x(child->parent);
        int32_t tmaxy = wid_get_br_y(child) - wid_get_tl_y(child->parent);

        if (first) {
            minx = tminx;
            miny = tminy;
            maxx = tmaxx;
            maxy = tmaxy;
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

    child_width = maxx - minx;
    child_height = maxy - miny;

    if (child_width < width) {
        maxx = minx + width;
        child_width = maxx - minx;
    }

    if (child_height < height) {
        maxy = miny + height;
        child_height = maxy - miny;
    }

    if (w) {
        *w = child_width;
    }

    if (h) {
        *h = child_height;
    }
}

static void wid_update_internal (widp w)
{_
    verify(w.get());

    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    /*
     * First time around, initialize the wid.
     */
    if (!w->first_update) {
        w->first_update = true;

        if (!w->parent) {
            /*
             * Find the focus.
             */
            wid_find_top_focus();
        }

        /*
         * Set back to normal to undo any settings when creating.
         *
         * No, make the clients fix their code.
         */
//        wid_set_mode(w, WID_MODE_NORMAL);
    }

    widp child;

    /*
     * Clip all the children. Avoid this for speed for the main game window.
     */
    std::vector<widp> worklist;
    for (auto iter : w->tree2_children_unsorted) {
        auto w = iter.second;
        worklist.push_back(w);
    }

    for (auto child : worklist) {
        wid_update_internal(child);
    }

    /*
     * If the source of the event is the scrollbars themselves...
     */
    if (w->scrollbar_owner) {
        verify(w.get());
        wid_adjust_scrollbar(w, w->scrollbar_owner);

        wid_update_internal(w->scrollbar_owner);
    } else {
        /*
         * If the source of the event is the owner of the scrollbars...
         */
        if (w->scrollbar_vert) {
            verify(w.get());
            wid_adjust_scrollbar(w->scrollbar_vert, w);
        }

        if (w->scrollbar_horiz) {
            verify(w.get());
            wid_adjust_scrollbar(w->scrollbar_horiz, w);
        }
    }
}

void wid_update (widp w)
{_
    verify(w.get());

    wid_update_internal(w);

    /*
     * If we were hovering over a window and it was replaced, we need to fake
     * a mouse movement so we know we are still over it.
     */
    if (!w->parent && !w->children_display_sorted.empty()) {
        wid_update_mouse();
    }
}

void wid_update_mouse (void)
{_
    /*
     * So if we are now over a new widget that was created on top of the
     * mouse, we activate it.
     */
    int32_t x;
    int32_t y;

    SDL_GetMouseState(&x, &y);

    wid_mouse_motion(x, y, 0, 0, 0, 0);
}

void wid_scroll_text (widp w)
{_
    std::wstring s;
    widp prev;
    widp tmp;

    /*
     * Get the wid on the top of the list/screen.
     */
    tmp = wid_get_tail(w);

    /*
     * Now copy the text up to the parent widgets.
     */
    while (tmp) {
        prev = wid_get_prev(tmp);

        if (prev) {
            s = wid_get_text(prev);

            wid_set_text(tmp, s);
        }

        tmp = prev;
    }
}

/*
 * Replace the 2nd last line of text and scroll. The assumption is the last
 * line is the input line.
 */
void wid_scroll_with_input (widp w, std::wstring str)
{_
    widp tmp;

    wid_scroll_text(w);

    /*
     * Get the wid on the bottom of the list/screen.
     */
    tmp = wid_get_head(w);

    /*
     * Now get the 2nd last line. The last line is the input. The 2nd last
     * line is where new output goes.
     */
    if (tmp) {
        tmp = wid_get_next(tmp);
        if (tmp) {
            wid_set_text(tmp, str);
        }
    }
}

uint8_t wid_receive_input (widp w, const SDL_KEYSYM *key)
{_
    std::wstring beforecursor;
    std::wstring aftercursor;
    std::wstring tmp;
    std::wstring origtext;
    std::wstring updatedtext;
    std::wstring newchar;
    uint32_t origlen;
    uint32_t cnt;

    newchar += wid_event_to_char(key);
    origtext = wid_get_text(w);
    origlen = (uint32_t)origtext.length();

    if (!w->received_input) {
        wid_set_received_input(w, true);
        w->cursor = (uint32_t)origtext.length();
    }

    if (origtext.empty()) {
        aftercursor = beforecursor = L"";
    } else {
        beforecursor = origtext.substr(0, w->cursor);
        aftercursor = origtext.substr(w->cursor);
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
            switch (wid_event_to_char(key)) {
            case 'i':
                CON("Screen inverted");
                inverted_gfx = !inverted_gfx;
                break;

            case 'p':
                if (!history_walk) {
                    history_walk = HISTORY_MAX - 1;
                } else {
                    history_walk--;
                }

                wid_set_text(w, history[history_walk]);
                w->cursor = (uint32_t)wid_get_text(w).length();
                break;

            case 'n':
                history_walk++;
                if (history_walk >= HISTORY_MAX) {
                    history_walk = 0;
                }

                wid_set_text(w, history[history_walk]);
                w->cursor = (uint32_t)wid_get_text(w).length();
                break;

            case 'a':
                w->cursor = 0;
                break;

            case 'e':
                w->cursor = origlen;
                break;
            }
            break;

        default:

        switch (key->sym) {
            case SDLK_BACKSPACE:
                if (beforecursor.size()) {
                    w->cursor--;

                    beforecursor.erase(beforecursor.end() - 1);
                    auto result = beforecursor + aftercursor;
                    wid_set_text(w, result);
                }
                break;

            case SDLK_TAB:
                if (w != wid_console_input_line) {
                    return (true);
                }

                command_handle(wid_get_text(w),
                               &updatedtext,
                               false /* show ambiguous */,
                               true /* show complete */,
                               false /* execute command */,
                               0 /* context */);

                if (!updatedtext.empty()) {
                    wid_set_text(w, updatedtext);
                    w->cursor = updatedtext.length();
                }
                return (true);

            case SDLK_RETURN:
                if (w != wid_console_input_line) {
                    return (false);
                }

                if (origlen && (w == wid_console_input_line)) {
                    static std::wstring entered;
                    static std::wstring entered2;

                    entered = wid_get_text(w);
                    entered2 = L"> " + wid_get_text(w);

                    wid_scroll_text(w);
                    wid_set_text(w->next, entered2);

                    if (!command_handle(entered, 
                                        &updatedtext,
                                        true /* show ambiguous */,
                                        false /* show complete */,
                                        true /* execute command */,
                                        0 /* context */)) {
                         return (true);
                    }

                    if (!updatedtext.empty()) {
                        wid_set_text(w, updatedtext);
                        w->cursor = updatedtext.length();
                    }

                    history[history_at] = updatedtext;

                    history_at++;
                    if (history_at >= HISTORY_MAX) {
                        history_at = 0;
                    }
                    history_walk = history_at;

                    wid_set_text(w, L"");
                    w->cursor = 0;
                } else if (w == wid_console_input_line) {
                    wid_scroll_text(w);
                }
                return (true);

            case SDLK_LEFT:
                if (w->cursor > 0) {
                    w->cursor--;
                }
                break;

            case SDLK_RIGHT:
                if (w->cursor < origlen) {
                    w->cursor++;
                }
                break;

            case SDLK_UP:
                cnt = 0;
                while (cnt < HISTORY_MAX) {
                    cnt++;
                    if (!history_walk) {
                        history_walk = HISTORY_MAX - 1;
                    } else {
                        history_walk--;
                    }

                    wid_set_text(w, history[history_walk]);
                    if (history[history_walk] == L"") {
                        continue;
                    }

                    w->cursor = (uint32_t)wid_get_text(w).length();
                    break;
                }
                break;

            case SDLK_DOWN:
                cnt = 0;
                while (cnt < HISTORY_MAX) {
                    cnt++;

                    history_walk++;
                    if (history_walk >= HISTORY_MAX) {
                        history_walk = 0;
                    }

                    wid_set_text(w, history[history_walk]);
                    if (history[history_walk] == L"") {
                        continue;
                    }

                    w->cursor = (uint32_t)wid_get_text(w).length();
                    break;
                }
                break;

            case SDLK_HOME:
                w->cursor = 0;
                break;

            case SDLK_END:
                w->cursor = origlen;
                break;

            default: {
                auto c = wid_event_to_char(key);

                switch (c) {
                case SDLK_ESCAPE:
                    if (w != wid_console_input_line) {
                        break;
                    }

                case '`':
                case '~':
                case '\\':
                    /*
                     * Magic keys we use to toggle the console.
                     */
                    return (false);

                case '?':
                    if (w != wid_console_input_line) {
                        break;
                    }

                    command_handle(wid_get_text(w),
                                   &updatedtext,
                                   true /* show ambiguous */,
                                   false /* show complete */,
                                   false /* execute command */,
                                   0 /* context */);

                    if (!updatedtext.empty()) {
                        wid_set_text(w, updatedtext);
                        w->cursor = updatedtext.length();
                    }
                    return (true);
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

    return (true);
}

/*
 * Handle keys no one grabbed.
 */
static uint8_t wid_receive_unhandled_input (const SDL_KEYSYM *key)
{_
    if (game_key_down(key)) {
        return (true);
    }

    widp w;

    w = wid_get_top_parent(wid_console_input_line);

    switch (key->mod) {
        default:

        switch ((int32_t)key->sym) {
            case '\\':
                sdl_screenshot();
                CON("Screenshot taken");
                break;

            case '`':
            case '~':
                wid_toggle_hidden(wid_console_window);
                wid_raise(wid_console_window);

                /*
                 * Need this so the console gets focus over the menu.
                 */
                if (w->visible) {
                    wid_set_focus(w);
                    wid_focus_lock(w);
                } else {
                    wid_set_focus(0);
                    wid_focus_lock(0);
                }
                break;

            case SDLK_ESCAPE:
                if (w->visible) {
                    wid_hide(w);
                }

                /*
                 * Need this so the console gets focus over the menu.
                 */
                if (w->visible) {
                    wid_set_focus(w);
                    wid_focus_lock(w);
                } else {
                    wid_set_focus(0);
                    wid_focus_lock(0);
                }
                break;

            case SDLK_TAB:
            case SDLK_RETURN:
            case SDLK_DOWN:
            case SDLK_RIGHT:
                wid_find_next_focus();
                break;

            case SDLK_UP:
            case SDLK_LEFT:
                wid_find_prev_focus();
                break;

            default: {
                wid_console_receive_input(wid_console_input_line, key);
                break;
            }
        }
    }

    return (true);
}

static widp wid_find_at (widp w, int32_t x, int32_t y)
{_
    w = wid_on_screen_at[x][y];
    if (!w) {
        return (0);
    }

    if (wid_ignore_being_destroyed(w)) {
        return (0);
    }

    verify(w.get());

    return (w);
}

static widp wid_key_down_handler_at (widp w, int32_t x, int32_t y,
                                     uint8_t strict)
{_
    widp child;

    if (!w) {
        return (0);
    }

    if (wid_ignore_events(w)) {
        return (0);
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return (0);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_key_down_handler_at(child, x, y,
                                                    true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_key_down_handler_at(child, x, y,
                                                    false /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w.get()->on_key_down) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    w = wid_get_top_parent(w);
    if (w.get()->on_key_down) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    return (0);
}

static widp wid_key_up_handler_at (widp w, int32_t x, int32_t y,
                                     uint8_t strict)
{_
    widp child;

    if (!w) {
        return (0);
    }

    if (wid_ignore_events(w)) {
        return (0);
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return (0);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_key_up_handler_at(child, x, y,
                                                    true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_key_up_handler_at(child, x, y,
                                                    false /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w.get()->on_key_up) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    return (0);
}

static widp wid_joy_button_handler_at (widp w, int32_t x, int32_t y,
                                       uint8_t strict)
{_
    widp child;

    if (!w) {
        return (0);
    }

    if (wid_ignore_events(w)) {
        return (0);
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return (0);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_joy_button_handler_at(child, x, y,
                                                    true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w.get()->on_joy_button) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    return (0);
}

static widp wid_mouse_down_handler_at (widp w, int32_t x, int32_t y,
                                       uint8_t strict)
{_
    widp child;

    if (!w) {
        return (0);
    }

    if (w->ignore_for_mouse_down) {
        return (0);
    }

    if (wid_ignore_events(w)) {
        return (0);
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return (0);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_mouse_down_handler_at(child, x, y,
                                                      true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w.get()->on_m_down) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    if (wid_get_movable(w)) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    /*
     * Prevent mouse events that occur in the bounds of one window, leaking
     * into lower levels.
     */
    if (!w->parent) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    return (0);
}

static widp wid_mouse_up_handler_at (widp w, int32_t x, int32_t y, uint8_t strict)
{_
    widp child;

    if (!w) {
        return (0);
    }

    if (wid_ignore_events(w)) {
        return (0);
    }

    if (strict) {
        if ((x < w->abs_tl.x) ||
            (y < w->abs_tl.y) ||
            (x > w->abs_br.x) ||
            (y > w->abs_br.y)) {
            return (0);
        }
    }

    for (auto iter : w->children_display_sorted) {
        auto child = iter.second;

        verify(child.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(child) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        widp closer_match = wid_mouse_up_handler_at(child, x, y,
                                                      true /* strict */);
        if (closer_match) {
            return (closer_match);
        }
    }

    if (w.get()->on_m_up) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    if (wid_get_movable(w)) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    /*
     * Prevent mouse events that occur in the bounds of one window, leaking
     * into lower levels.
     */
    if (!w->parent) {
        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            return (0);
        }

        return (w);
    }

    return (0);
}

static void wid_children_move_delta_internal (widp w, int32_t dx, int32_t dy)
{_
    /*
     * Make sure you can't move a wid outside the parents box.
     */
    widp p = w->parent;
    if (p) {
        if (wid_get_movable_bounded(w)) {
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

    widp child;

    for (auto iter : w->tree2_children_unsorted) {
        auto child = iter.second;

        wid_children_move_delta_internal(child, dx, dy);
    }
}

static void wid_move_delta_internal (widp w, int32_t dx, int32_t dy)
{_
    wid_tree_detach(w);

    /*
     * Make sure you can't move a wid outside the parents box.
     */
    widp p = w->parent;
    if (p) {
        if (wid_get_movable_bounded(w)) {
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

    widp child;

    std::vector<widp> worklist;
    for (auto iter : w->tree2_children_unsorted) {
        auto w = iter.second;
        worklist.push_back(w);
    }

    for (auto child : worklist) {
        wid_children_move_delta_internal(child, dx, dy);
    }

    w->can_be_attached_now = true;
}

void wid_move_delta (widp w, int32_t dx, int32_t dy)
{_
    verify(w.get());

    wid_move_delta_internal(w, dx, dy);

    wid_update_internal(w);
}

void wid_move_delta_pct (widp w, double dx, double dy)
{_
    if (!w->parent) {
        dx *= (double)ASCII_WIDTH;
        dy *= (double)ASCII_HEIGHT;
    } else {
        dx *= wid_get_width(w->parent);
        dy *= wid_get_height(w->parent);
    }

    verify(w.get());

    wid_move_delta_internal(w, dx, dy);

    wid_update_internal(w);
}

void wid_move_to_bottom (widp w)
{_
    if (w->parent) {
        wid_move_delta(w, 0, wid_get_br_y(w->parent) - wid_get_br_y(w));
    } else {
        wid_move_delta(w, 0, ASCII_HEIGHT - wid_get_br_y(w));
    }
}

void wid_move_to_left (widp w)
{_
    if (w->parent) {
        wid_move_delta(w, wid_get_tl_x(w->parent) - wid_get_tl_x(w), 0);
    } else {
        wid_move_delta(w, - wid_get_tl_x(w), 0);
    }
}

void wid_move_to_right (widp w)
{_
    if (w->parent) {
        wid_move_delta(w, wid_get_br_x(w->parent) - wid_get_br_x(w), 0);
    } else {
        wid_move_delta(w, ASCII_WIDTH - wid_get_br_x(w), 0);
    }
}

void wid_move_to_vert_pct (widp w, double pct)
{_
    double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
    double at = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
    double delta = (pct - at) * pheight;

    wid_move_delta(w, 0, delta);
}

void wid_move_to_horiz_pct (widp w, double pct)
{_
    double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
    double at = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
    double delta = (pct - at) * pwidth;

    wid_move_delta(w, delta, 0);
}

void wid_move_to_vert_pct_in (widp w, double pct, double in)
{_
    if (pct < 0.0) {
        pct = 0.0;
    }

    if (pct > 1.0) {
        pct = 1.0;
    }

    double pheight = wid_get_br_y(w->parent) - wid_get_tl_y(w->parent);
    double at = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
    double delta = (pct - at) * pheight;

    wid_move_to_abs_in(w, wid_get_tl_x(w), wid_get_tl_y(w) + delta, in);
}

void wid_move_to_horiz_pct_in (widp w, double pct, double in)
{_
    if (pct < 0.0) {
        pct = 0.0;
    }

    if (pct > 1.0) {
        pct = 1.0;
    }

    double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
    double at = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
    double delta = (pct - at) * pwidth;

    wid_move_to_abs_in(w, wid_get_tl_x(w) + delta, wid_get_tl_y(w), in);
}

void wid_move_to_horiz_vert_pct_in (widp w, double x, double y, double in)
{_
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
    double aty = (wid_get_tl_y(w) - wid_get_tl_y(w->parent)) / pheight;
    double dy = (y - aty) * pheight;

    double pwidth = wid_get_br_x(w->parent) - wid_get_tl_x(w->parent);
    double atx = (wid_get_tl_x(w) - wid_get_tl_x(w->parent)) / pwidth;
    double dx = (x - atx) * pwidth;

    wid_move_to_abs_in(w, wid_get_tl_x(w) + dx, wid_get_tl_y(w) + dy, in);
}

void wid_move_to_top (widp w)
{_
    if (w->parent) {
        wid_move_delta(w, 0, wid_get_tl_y(w->parent) - wid_get_tl_y(w));
    } else {
        wid_move_delta(w, 0, - wid_get_tl_y(w));
    }
}

static widp wid_joy_button_handler (int32_t x, int32_t y)
{_
    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_joy_button_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return (0);
}

static widp wid_mouse_down_handler (int32_t x, int32_t y)
{_
    widp w;

    w = wid_mouse_down_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_mouse_down_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_down_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_down_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return (0);
}

static widp wid_mouse_up_handler (int32_t x, int32_t y)
{_
    widp w;

    w = wid_mouse_up_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_mouse_up_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
//        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_up_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_up_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return (0);
}

static widp wid_mouse_motion_handler (int32_t x, int32_t y,
                                      int32_t relx, int32_t rely,
                                      int32_t wheelx, int32_t wheely)
{_
    widp w;

#if 0
#ifdef DEBUG_WID_MOTION
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
    printf("\n ");
static int count;
count++;
printf("\nmouse at %d, %d  (%d, %d) count %d", x, y, mouse_x, mouse_y, count);
#endif

    w = wid_mouse_motion_handler_at(wid_focus, x, y,
                                    relx, rely,
                                    wheelx, wheely,
                                    true /* strict */,
                                    0 /* depth */,
                                    0 /* debug */);
    if (w) {
#ifdef DEBUG_WID_MOTION
    printf("\ngot focus wid %s",wid_name(w).c_str());
#endif
        return (w);
    }

    w = wid_mouse_motion_handler_at(wid_over, x, y,
                                    relx, rely,
                                    wheelx, wheely,
                                    true /* strict */,
                                    0 /* depth */,
                                    0 /* debug */);
    if (w) {
#ifdef DEBUG_WID_MOTION
    printf("\ngot over wid %s",wid_name(w).c_str());
#endif
        return (w);
    }

#ifdef DEBUG_WID_MOTION
    printf("\n  walk top level:");
#endif
    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;

        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
#ifdef DEBUG_WID_MOTION
    printf("\n   focus locked");
#endif
            continue;
        }

        w = wid_mouse_motion_handler_at(w, x, y,
                                        relx, rely,
                                        wheelx, wheely,
                                        true /* strict */,
                                        0 /* depth */,
                                        0 /* debug */);
        if (!w) {
            continue;
        }

        return (w);
    }
#endif

    w = wid_on_screen_at[x][y];
    if (w) {
        return (w);
    }

    if (!wheelx && !wheely) {
        return (0);
    }

#if 0
#ifdef DEBUG_WID_MOTION
    printf("\n  walk top level non strict:");
#endif
    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_mouse_motion_handler_at(w, x, y,
                                        relx, rely,
                                        wheelx, wheely,
                                        false /* strict */,
                                        0 /* depth */,
                                        0 /* debug */);
        if (!w) {
            continue;
        }

        return (w);
    }

#endif
    return (0);
}

/*
 * Catch recursive cases like this:
 *
 * #42 0x00000001180a1233 in wid_update (w=0x11f0c0c00) at wid.c:5353
 *
 * #43 0x00000001180bf45d in map_editor_map_thing_replace_template
 *
 * #44 0x00000001180c1509 in map_editor_map_thing_replace (w=0x11f1dca00, x=5,
 *
 * #45 0x00000001180c0275 in map_editor_map_tile_mouse_motion (w=0x11f1dca00,
 *
 * #46 0x00000001180a170f in wid_mouse_motion (x=338, y=357, relx=0, rely=0,
 *
 * #47 0x000000011809ff26 in wid_update_mouse () at wid.c:5371
 *
 * #48 0x00000001180a1233 in wid_update (w=0x11f0c0c00) at wid.c:5353
 *
 * #49 0x00000001180bf45d in map_editor_map_thing_replace_template
 *
 * #50 0x00000001180c1509 in map_editor_map_thing_replace (w=0x11f1dca00, x=5,
 *
 * #51 0x00000001180c0275 in map_editor_map_tile_mouse_motion (w=0x11f1dca00,
 *
 * #52 0x00000001180a170f in wid_mouse_motion (x=338, y=357, relx=0, rely=0,
 *
 */
static int wid_mouse_motion_recursion;

void wid_mouse_motion (int32_t x, int32_t y,
                       int32_t relx, int32_t rely,
                       int32_t wheelx, int32_t wheely)
{_
    int got_one = false;

    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    wid_refresh_overlay_count += 1;

    if (wid_mouse_motion_recursion) {
        return;
    }

    wid_mouse_motion_recursion = 1;

    widp w;

    if (wid_mouse_template) {
        wid_move_to_abs_centered_in(wid_mouse_template, x, y, 10);
        wid_raise(wid_mouse_template);
    }

    uint8_t over = false;

    for (auto iter : wid_top_level) {
        auto w = iter.second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        /*
         * Allow wheel events to go everywhere
         */
        if (!wheelx && !wheely) {
            w = wid_find_at(w, x, y);
            if (!w) {
                continue;
            }
        }

        if (wid_ignore_events(w)) {
            /*
             * This wid is ignoring events, but what about the parent?
             */
            w = w->parent;
            while (w) {
                if (!wid_ignore_events(w)) {
                    break;
                }
                w = w->parent;
            }

            if (!w) {
                continue;
            }
        }

        /*
         * Over a new wid.
         */
_
        while (w &&
               !wid_m_over_b(w, x, y, relx, rely, wheelx, wheely)) {
            w = w->parent;
        }

        uint8_t done = false;

        if (!w) {
            /*
             * Allow scrollbar to grab.
             */
        } else {
            /*
             * This widget reacted somehow when we went over it. i.e. popup ot
             * function.
             */
            over = true;
        }

        w = wid_mouse_motion_handler(x, y, relx, rely, wheelx, wheely);
        if (w) {
_
            if (wid_m_over_b(w, x, y, relx, rely, wheelx, wheely)) {
                over = true;
            }

            /*
             * If the mouse event is fully processed then do not pass onto
             * scrollbars.
             */
            if (w.get()->on_m_motion) {
                verify(w.get());
                if ((w.get()->on_m_motion)(w, x, y, relx, rely, wheelx, wheely)) {
                    got_one = true;
                    break;
                }
            }

            if (wid_over == w) {
                if (!wheelx && !wheely) {
                    break;
                }
            }

            while (w) {
                /*
                 * If there are scrollbars and the wid did not grab the event
                 * then scroll for it.
                 */
                if (wheely) {
                    if (w->scrollbar_vert &&
                        !wid_get_movable_no_user_scroll(w->scrollbar_vert)) {

                        got_one = true;
                        wid_move_delta(w->scrollbar_vert, 0, -wheely);
                        done = true;
                    }
                }

                if (wheelx) {
                    if (w->scrollbar_horiz &&
                        !wid_get_movable_no_user_scroll(w->scrollbar_horiz)) {

                        got_one = true;
                        wid_move_delta(w->scrollbar_horiz, -wheelx, 0);
                        done = true;
                    }
                }

                if (done) {
                    break;
                }

                /*
                 * Maybe the container has a scrollbar. Try it.
                 */
                w = w->parent;
            }
        }

        if (done) {
            break;
        }
    }

    if (!over) {
        wid_m_over_e();
    }

    /*
     * If nothing then pass the event to the console to allow scrolling
     * of the console.
     */
    if (!got_one){
        if (wid_console_container && (wheelx || wheely)) {
            widp w = wid_console_container->scrollbar_vert;
            if (w) {
                w = w->parent;
            }

            if (w && w.get()->on_m_motion) {
                (w.get()->on_m_motion)(w, x, y, relx, rely, wheelx, wheely);
            }
        }
    }

    wid_mouse_motion_recursion = 0;
}

/*
 * If no handler for this button, fake a mouse event.
 */
void wid_fake_joy_button (int32_t x, int32_t y)
{_
    if (sdl_joy_buttons[SDL_JOY_BUTTON_A]) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_B]) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_X]) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_Y]) {
        wid_mouse_down(2, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_TOP_LEFT]) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_TOP_RIGHT]) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_LEFT_STICK_DOWN]) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_RIGHT_STICK_DOWN]) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_START]) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_XBOX]) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_BACK]) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_UP]) {
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_DOWN]) {
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_LEFT]) {
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_RIGHT]) {
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_LEFT_FIRE]) {
        wid_mouse_down(SDL_BUTTON_LEFT, x, y);
        return;
    }
    if (sdl_joy_buttons[SDL_JOY_BUTTON_RIGHT_FIRE]) {
        wid_mouse_down(SDL_BUTTON_RIGHT, x, y);
        return;
    }
}

void wid_joy_button (int32_t x, int32_t y)
{_
    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    /*
     * Only if there is a change in status, send an event.
     */
    static uint32_t ts[SDL_MAX_BUTTONS];
    int changed = false;
    int b;

    for (b = 0; b < SDL_MAX_BUTTONS; b++) {
        if (sdl_joy_buttons[b]) {
            if (time_have_x_tenths_passed_since(2, ts[b])) {
                changed = true;
                ts[b] = time_get_time_ms_cached();
            }
        }
    }

    if (!changed) {
        return;
    }

    widp w;

    w = wid_joy_button_handler(x, y);
    if (!w) {
        wid_fake_joy_button(x, y);
        return;
    }

    /*
     * Raise on mouse.
     */
    if (w.get()->on_joy_button) {
        /*
         * If the button doesn't eat the event, try the parent.
         */
        while (!(w.get()->on_joy_button)(w, x, y)) {
            w = w->parent;

            while (w && !w.get()->on_joy_button) {
                w = w->parent;
            }

            if (!w) {
                wid_fake_joy_button(x, y);
                return;
            }
        }

        verify(w.get());

        wid_set_focus(w);
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);

        /*
         * Move on mouse.
         */
        if (wid_get_movable(w)) {
            wid_mouse_motion_begin(w, x, y);
            return;
        }

        return;
    } else {
        wid_fake_joy_button(x, y);
    }

    if (wid_get_movable(w)) {
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);
        wid_mouse_motion_begin(w, x, y);
        return;
    }
}

void wid_mouse_down (uint32_t button, int32_t x, int32_t y)
{_
    widp w;

    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    w = wid_mouse_down_handler(x, y);
    if (!w) {
        if (game_mouse_down(x, y, button)) {
            return;
        }
        return;
    }

    /*
     * Raise on mouse.
     */
    if ((w.get()->on_m_down && (w.get()->on_m_down)(w, x, y, button)) ||
        wid_get_movable(w)) {
        //CON("grabbed by %s",wid_name(w).c_str());

        verify(w.get());

        wid_set_focus(w);
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);

        /*
         * Move on mouse.
         */
        if (wid_get_movable(w)) {
            wid_mouse_motion_begin(w, x, y);
            return;
        }

        return;
    }

    if (wid_get_movable(w)) {
        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);
        wid_mouse_motion_begin(w, x, y);
        return;
    }
}

void wid_mouse_up (uint32_t button, int32_t x, int32_t y)
{_
    widp w;

    pixel_to_ascii(&x, &y);
    if (!ascii_ok(x, y)) {
        return;
    }

    wid_mouse_motion_end();

    w = wid_mouse_up_handler(x, y);
    if (!w) {
        return;
    }

    if ((w.get()->on_m_up && (w.get()->on_m_up)(w, x, y, button)) ||
        wid_get_movable(w)) {

        verify(w.get());

        wid_set_mode(w, WID_MODE_ACTIVE);
        wid_raise(w);
    }
}

static widp wid_key_down_handler (int32_t x, int32_t y)
{_
    widp w;

//CON("key down");
    w = wid_key_down_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
//CON("%s %d",wid_logname(w),__LINE__);
        return (w);
    }

    w = wid_key_down_handler_at(
                wid_get_top_parent(wid_focus), x, y, false /* strict */);
    if (w) {
//CON("%s %d",wid_logname(w),__LINE__);
        return (w);
    }

    w = wid_key_down_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
//CON("%s %d",wid_logname(w),__LINE__);
        return (w);
    }

    w = wid_key_down_handler_at(
                wid_get_top_parent(wid_over), x, y, false /* strict */);
    if (w) {
//CON("%s %d",wid_logname(w),__LINE__);
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
//CON("  focus is locked");
            continue;
        }

        w = wid_key_down_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }
//CON("     got top level strict handler%s",wid_logname(w));

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
//CON("  focus is locked");
            continue;
        }

        w = wid_key_down_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

//CON("     got top level loose handler%s",wid_logname(w));
        return (w);
    }

    return (0);
}

static widp wid_key_up_handler (int32_t x, int32_t y)
{_
    widp w;

    w = wid_key_up_handler_at(wid_focus, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_key_up_handler_at(
                wid_get_top_parent(wid_focus), x, y, false /* strict */);
    if (w) {
        return (w);
    }

    w = wid_key_up_handler_at(wid_over, x, y, true /* strict */);
    if (w) {
        return (w);
    }

    w = wid_key_up_handler_at(
                wid_get_top_parent(wid_over), x, y, false /* strict */);
    if (w) {
        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_key_up_handler_at(w, x, y, true /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    for (auto iter = wid_top_level.rbegin();
         iter != wid_top_level.rend(); ++iter) {
        auto w = iter->second;
        verify(w.get());

        if (wid_focus_locked &&
            (wid_get_top_parent(w) != wid_get_top_parent(wid_focus_locked))) {
            continue;
        }

        w = wid_key_up_handler_at(w, x, y, false /* strict */);
        if (!w) {
            continue;
        }

        return (w);
    }

    return (0);
}

#ifdef DEBUG_GL_BLEND
TIP2("%d %d %s %s", i1, i2, vals_str[i1], vals_str[i2]);
glBlendFunc(vals[i1], vals[i2]);
#endif

#ifdef DEBUG_GL_BLEND
static int vals[] = {

/* GL_ZERO                           */ 0,
/* GL_ONE                            */ 1,
/* GL_SRC_COLOR                      */ 0x0300,
/* GL_ONE_MINUS_SRC_COLOR            */ 0x0301,
/* GL_SRC_ALPHA                      */ 0x0302,
/* GL_ONE_MINUS_SRC_ALPHA            */ 0x0303,
/* GL_DST_ALPHA                      */ 0x0304,
/* GL_ONE_MINUS_DST_ALPHA            */ 0x0305,
/* GL_DST_COLOR                      */ 0x0306,
/* GL_ONE_MINUS_DST_COLOR            */ 0x0307,
/* GL_SRC_ALPHA_SATURATE             */ 0x0308,
/* GL_FUNC_ADD                       */ 0x8006,
/* GL_BLEND_EQUATION                 */ 0x8009,
/* GL_BLEND_EQUATION_RGB             */ 0x8009    /* same as BLEND_EQUATION */,
/* GL_BLEND_EQUATION_ALPHA           */ 0x883D,
/* GL_FUNC_SUBTRACT                  */ 0x800A,
/* GL_FUNC_REVERSE_SUBTRACT          */ 0x800B,
/* GL_BLEND_DST_RGB                  */ 0x80C8,
/* GL_BLEND_SRC_RGB                  */ 0x80C9,
/* GL_BLEND_DST_ALPHA                */ 0x80CA,
/* GL_BLEND_SRC_ALPHA                */ 0x80CB,
/* GL_CONSTANT_COLOR                 */ 0x8001,
/* GL_ONE_MINUS_CONSTANT_COLOR       */ 0x8002,
/* GL_CONSTANT_ALPHA                 */ 0x8003,
/* GL_ONE_MINUS_CONSTANT_ALPHA       */ 0x8004,
/* GL_BLEND_COLOR */ 0x8005,
};
static std::string  vals_str[] = {

"GL_ZERO                           ",
"GL_ONE                            ",
"GL_SRC_COLOR                      ",
"GL_ONE_MINUS_SRC_COLOR            ",
"GL_SRC_ALPHA                      ",
"GL_ONE_MINUS_SRC_ALPHA            ",
"GL_DST_ALPHA                      ",
"GL_ONE_MINUS_DST_ALPHA            ",
"GL_DST_COLOR                      ",
"GL_ONE_MINUS_DST_COLOR            ",
"GL_SRC_ALPHA_SATURATE             ",
"GL_FUNC_ADD                       ",
"GL_BLEND_EQUATION                 ",
"GL_BLEND_EQUATION_RGB             ",
"GL_BLEND_EQUATION_ALPHA           ",
"GL_FUNC_SUBTRACT                  ",
"GL_FUNC_REVERSE_SUBTRACT          ",
"GL_BLEND_DST_RGB                  ",
"GL_BLEND_SRC_RGB                  ",
"GL_BLEND_DST_ALPHA                ",
"GL_BLEND_SRC_ALPHA                ",
"GL_CONSTANT_COLOR                 ",
"GL_ONE_MINUS_CONSTANT_COLOR       ",
"GL_CONSTANT_ALPHA                 ",
"GL_ONE_MINUS_CONSTANT_ALPHA       ",
"GL_BLEND_COLOR ",
};


static int i1;
static int i2;
#endif

void wid_key_down (const struct SDL_KEYSYM *key, int32_t x, int32_t y)
{_
    widp w;

#ifdef DEBUG_GL_BLEND
if (wid_event_to_char(key) == '+') {
    usleep(100000);
    i1 ++;
    if (i1 >= (int)ARRAY_SIZE(vals)) {
	i1 = 0;
	i2 ++;
	if (i2 >= (int)ARRAY_SIZE(vals)) {
	    i2 = 0;
	}
    }
    return;
}

if (wid_event_to_char(key) == '-') {
    usleep(100000);
    i1 --;
    if (i1 < 0) {
	i1 = (int)ARRAY_SIZE(vals);
	i2 --;
	if (i2 < 0) {
	    i2 = (int)ARRAY_SIZE(vals);
	}
    }
    return;
}
#endif

    if (wid_focus &&
        !wid_is_hidden(wid_focus) &&
        (wid_focus->on_key_down)) {

        verify(wid_focus.get());

        if ((wid_focus->on_key_down)(wid_focus, key)) {
            /*
             * Do not raise, gets in the way of popups the callback creates.
             */
            return;
        }

        w = wid_focus;

        goto try_parent;
    }

    w = wid_key_down_handler(x, y);
    if (!w) {
        /*
         * If no-one handles it, feed it to the default handler, the console.
         */
        wid_receive_unhandled_input(key);
        return;
    }

    if ((w.get()->on_key_down)(w, key)) {
        /*
         * Do not raise, gets in the way of popups the callback creates.
         */
//CON("wid did not handle");
        return;
    }

try_parent:
    w = w->parent;

    /*
     * Ripple the key event to the parent so global things like pressing
     * escape can do things.
     */
    while (w) {
        if (w.get()->on_key_down) {
            if ((w.get()->on_key_down)(w, key)) {
                /*
                 * Do not raise, gets in the way of popups the callback
                 * creates.
                 */
                return;
            }
        }

        w = w->parent;
    }

    /*
     * If no-one handles it, feed it to the default handler, the console.
     */
    wid_receive_unhandled_input(key);
}

void wid_key_up (const struct SDL_KEYSYM *key, int32_t x, int32_t y)
{_
    widp w;

    if (wid_focus &&
        !wid_is_hidden(wid_focus) &&
        (wid_focus->on_key_up)) {

        verify(wid_focus.get());

        if ((wid_focus->on_key_up)(wid_focus, key)) {
            wid_set_mode(wid_focus, WID_MODE_ACTIVE);

            /*
             * Do not raise, gets in the way of popups the callback creates.
             */
            return;
        }

        w = wid_focus;

        goto try_parent;
    }

    w = wid_key_up_handler(x, y);
    if (!w) {
        /*
         * If no-one handles it, drop it. We only hand key down to the
         * console.
         */
        return;
    }

    if ((w.get()->on_key_up)(w, key)) {
        verify(w.get());

        wid_set_mode(w, WID_MODE_ACTIVE);

        /*
         * Do not raise, gets in the way of popups the callback creates.
         */
        return;
    }

try_parent:
    w = w->parent;

    /*
     * Ripple the key event to the parent so global things like pressing
     * escape can do things.
     */
    while (w) {
        if (w.get()->on_key_up) {
            if ((w.get()->on_key_up)(w, key)) {
                verify(w.get());

                wid_set_mode(w, WID_MODE_ACTIVE);

                /*
                 * Do not raise, gets in the way of popups the callback
                 * creates.
                 */
                return;
            }
        }

        w = w->parent;
    }
}

/*
 * Get the onscreen co-ords of the widget, clipped to the parent.
 */
void wid_get_abs_coords (widp w,
                         int32_t *tlx,
                         int32_t *tly,
                         int32_t *brx,
                         int32_t *bry)
{_
    widp p;

    *tlx = wid_get_tl_x(w);
    *tly = wid_get_tl_y(w);
    *brx = wid_get_br_x(w);
    *bry = wid_get_br_y(w);

    p = w->parent;
    if (p) {
        *tlx += p->offset.x;
        *tly += p->offset.y;
        *brx += p->offset.x;
        *bry += p->offset.y;
    }

    while (p) {
        int32_t ptlx = wid_get_tl_x(p);
        int32_t ptly = wid_get_tl_y(p);
        int32_t pbrx = wid_get_br_x(p);
        int32_t pbry = wid_get_br_y(p);

        if (p->parent) {
            ptlx += p->parent->offset.x;
            ptly += p->parent->offset.y;
            pbrx += p->parent->offset.x;
            pbry += p->parent->offset.y;
        }

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

        p = p->parent;
    }

    w->abs_tl.x = *tlx;
    w->abs_tl.y = *tly;
    w->abs_br.x = *brx;
    w->abs_br.y = *bry;
}

/*
 * Get the onscreen co-ords of the widget, no clipping
 */
void wid_get_abs_coords_unclipped (widp w,
                                   int32_t *tlx,
                                   int32_t *tly,
                                   int32_t *brx,
                                   int32_t *bry)
{_
    widp p;

    *tlx = wid_get_tl_x(w);
    *tly = wid_get_tl_y(w);
    *brx = wid_get_br_x(w);
    *bry = wid_get_br_y(w);

    p = w->parent;
    if (p) {
        *tlx += p->offset.x;
        *tly += p->offset.y;
        *brx += p->offset.x;
        *bry += p->offset.y;
    }

    while (p) {
        int32_t ptlx = wid_get_tl_x(p);
        int32_t ptly = wid_get_tl_y(p);
        int32_t pbrx = wid_get_br_x(p);
        int32_t pbry = wid_get_br_y(p);

        if (p->parent) {
            ptlx += p->parent->offset.x;
            ptly += p->parent->offset.y;
            pbrx += p->parent->offset.x;
            pbry += p->parent->offset.y;
        }

        p = p->parent;
    }

    w->abs_tl.x = *tlx;
    w->abs_tl.y = *tly;
    w->abs_br.x = *brx;
    w->abs_br.y = *bry;
}

/*
 * Get the onscreen co-ords of the widget, clipped to the parent.
 */
void wid_get_abs (widp w,
                  int32_t *x,
                  int32_t *y)
{_
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    *x = (tlx + brx) / 2;
    *y = (tly + bry) / 2;
}

void wid_get_pct (widp w,
                  double *px,
                  double *py)
{_
    int32_t x;
    int32_t y;

    wid_get_abs(w, &x, &y);

    *px = (double)x / (double)ASCII_WIDTH;
    *py = (double)y / (double)ASCII_HEIGHT;
}

/*
 * Finish off a widgets move.
 */
void wid_move_end (widp w)
{_
    while (w->moving) {
        wid_move_dequeue(w);
    }
}

/*
 * Do stuff for widgets once per frame.
 */
static void wid_gc (widp w)
{_
    verify(w.get());

    if (w->being_destroyed) {
        wid_destroy_immediate(w);
        return;
    }

    /*
     * Delayed destroy?
     */
    if (w->destroy_when && (wid_time >= w->destroy_when)) {
        verify(w.get());

        if (w->destroy_ptr) {
            *(w->destroy_ptr) = 0;
            w->destroy_ptr = 0;
        }

        wid_destroy(&w);
    }
}

/*
 * Display one wid and its children
 */
static void wid_display (widp w,
                         uint8_t disable_scissor,
                         uint8_t *updated_scissors,
                         int clip)
{_
    int32_t clip_height = 0;
    int32_t clip_width = 0;
    uint8_t hidden;
    uint8_t always_hidden;
    int32_t owidth;
    int32_t oheight;
    int32_t otlx;
    int32_t otly;
    int32_t obrx;
    int32_t obry;
    int32_t tlx;
    int32_t tly;
    int32_t brx;
    int32_t bry;
    widp p;

    /*
     * Bounding box for drawing the wid. Co-ords are negative as we
     * flipped the screen
     */
    tlx = w->abs_tl.x;
    tly = w->abs_tl.y;
    brx = w->abs_br.x;
    bry = w->abs_br.y;

    /*
     * If we're clipped out of existence! then nothing to draw. This can
     * be outside the bounds of a widget or if at the top level, off screeen.
     */
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

    hidden = wid_is_hidden(w);
    always_hidden = wid_is_always_hidden(w);

    if (always_hidden) {
        /*
         * Always render. Not hidden yet.
         */
        return;
    } else if (hidden) {
        /*
         * Hidden or parent is hidden.
         */
        return;
    }

    /*
     * Record the original pre clip sizes for text centering.
     */
    otlx = wid_get_tl_x(w);
    otly = wid_get_tl_y(w);
    obrx = wid_get_br_x(w);
    obry = wid_get_br_y(w);

    p = w->parent;
    if (p) {
        otlx += p->offset.x;
        otly += p->offset.y;
        obrx += p->offset.x;
        obry += p->offset.y;
    }

    owidth = obrx - otlx;
    oheight = obry - otly;

    /*
     * If this widget was active and the time has elapsed, make it normal.
     */
    if (wid_get_mode(w) == WID_MODE_ACTIVE) {
        if ((wid_time - w->timestamp_last_mode_change) > 250) {
            wid_set_mode(w, WID_MODE_NORMAL);
        }
    }

    /*
     * Draw the wid frame
     */
    color col_border_text = wid_get_color(w, WID_COLOR_TEXT);

    /*
     * If inputting text, show a cursor.
     */
    std::wstring text;

    if (wid_get_show_cursor(w)) {
        text = wid_get_text_with_cursor(w);
    } else {
        text = wid_get_text(w);
    }

    if (w->disable_scissors) {
        disable_scissor = true;
    }

    /*
     * Should be no need for scissors if you do not have any children
     * or are not the top level wid.
     */
    if (!disable_scissor) {
        /*
         * Text box needs clipping when the text gets too wide.
         */
       if (!w->children_display_sorted.empty() || !w->parent || w->show_cursor) {
            /*
             * Tell the parent we are doing scissors so they can re-do
             * their own scissors.
             */
            if (updated_scissors) {
                *updated_scissors = true;
            }

            wid_set_scissors(
                tlx,
                tly,
                brx,
                bry);
        }
    }

    Tilep tile = wid_get_tile(w);

    auto width = wid_get_width(w);
    auto height = wid_get_height(w);

    /*
     * Add the texture tile at a time
     */
    Texp tex;

    if (!tile) {
        tex = wid_get_tex(w, 0);

        double dx = 1.0 / (double)width;
        double dy = 1.0 / (double)height;
        int x, y;
        double tx, ty;
        for (x = 0, tx = 0.0; x < width; x++, tx += dx) {
            for (y = 0, ty = 0.0; y < height; y++, ty += dy) {
                ascii_set_bg(tlx + x, tly + y, tex, tx, ty, dx, dy);
            }
        }
    } else {
        tex = 0;
    }

    fsize texuv;
    (void) wid_get_tex(w, &texuv);

    point tl;
    point br;

    tl.x = otlx;
    tl.y = otly;
    br.x = otlx + width;
    br.y = otly + height;

    box_args w_box_args = {
        .x              = tl.x,
        .y              = tl.y,
        .width          = (br.x - tl.x) + 1,
        .height         = (br.y - tl.y) + 1,
    };

    button_args w_button_args = {
        .x              = tl.x,
        .y              = tl.y,
        .width          = (br.x - tl.x) + 1,
    };

#if 0
    color col = wid_get_color(w, WID_COLOR_BG);
    w_box_args.col_tl = col;
    w_box_args.c1_active = col;
    w_box_args.col_mid = col;
    w_box_args.c2_active = col;
    w_box_args.col_br = col;
    w_box_args.c3_active = col;
#endif

    bool is_button = (bry == tly) && w->square;

    if (w == wid_over) {
        w_box_args.over = true;
        w_button_args.over = true;

        if (w->cfg[WID_MODE_OVER].color_set[WID_COLOR_BG]) {
            auto c = w->cfg[WID_MODE_OVER].colors[WID_COLOR_TEXT];
            w_box_args.col_border_text = c;
            w_button_args.col_border_text = c;

            c = w->cfg[WID_MODE_OVER].colors[WID_COLOR_BG];
            w_button_args.col_tl = c;
            w_button_args.col_mid = c;
            w_button_args.col_br = c;
        }
    } else {
        if (w->cfg[WID_MODE_NORMAL].color_set[WID_COLOR_BG]) {
            w_box_args.col_border_text = COLOR_NONE;
            w_button_args.col_border_text = COLOR_NONE;

            auto c = w->cfg[WID_MODE_NORMAL].colors[WID_COLOR_BG];
            w_box_args.col_tl = c;
            w_box_args.col_mid = color(c.r * 0.8, c.g * 0.8, c.b * 0.8, 255);
            w_box_args.col_br = color(c.r * 0.5, c.g * 0.5, c.b * 0.5, 255);

            w_button_args.col_tl = c;
            w_button_args.col_mid = c;
            w_button_args.col_br = c;
        }
    }

    if (is_button) {
        ascii_put_button(w_button_args, text.c_str());
    } else if (w->square) {
        /*
         * Flat square
         */
        if (bry == tly) {
            auto c = L'▋';
            auto color = w->cfg[WID_MODE_NORMAL].colors[WID_COLOR_BG];

            ascii_put_solid_line(tlx, tlx + w_box_args.width, tly,
                                 c, color, w_box_args.context);
        } else {
            w_box_args.col_tl = w_box_args.col_mid;
            w_box_args.col_br = w_box_args.col_mid;

            ascii_put_box(w_box_args, L"");
        }
    } else if (w->box) {
        /*
         * Bevelled box
         */
        ascii_put_box(w_box_args, L"");
    } else {
        /* shape none */
    }

    {
        for (auto x = tl.x; x < br.x; x++) {
            for (auto y = tl.y; y < br.y; y++) {
                if (!ascii_ok(x, y)) {
                    continue;
                }
                wid_on_screen_at[x][y] = w;
            }
        }
    }

    if (!is_button && !text.empty()) {
        int32_t x, y;
        int32_t xpc, ypc;
        int32_t width, height;

        /*
         * Manually specified text position.
         */
        width = ascii_strlen(text);
        height = 0;

        if (wid_get_text_pos(w, &xpc, &ypc)) {
            x = (owidth * xpc) - ((int32_t)width / 2) + otlx;
            y = (oheight * ypc) - ((int32_t)height / 2) + otly;
        } else {
            /*
             * Position the text
             */
            if (((int)width > owidth) && w->show_cursor) {
                /*
                 * If the text is too big, center it on the cursor.
                 */
                x = ((owidth - (int32_t)width) / 2) + otlx;

                uint32_t c_width = (width / (double)text.length());

                x -= (w->cursor - (text.length() / 2)) * c_width;
            } else if (wid_get_text_lhs(w)) {
                x = otlx;
            } else if (wid_get_text_centerx(w)) {
                x = ((owidth - (int32_t)width) / 2) + otlx;
            } else if (wid_get_text_rhs(w)) {
                x = obrx - (int32_t)width;
            } else {
                x = ((owidth - (int32_t)width) / 2) + otlx;
            }

            if (wid_get_text_top(w)) {
                y = otly;
            } else if (wid_get_text_centery(w)) {
                y = ((oheight - (int32_t)height) / 2) + otly;
            } else if (wid_get_text_bot(w)) {
                y = obry - (int32_t)height;
            } else {
                y = ((oheight - (int32_t)height) / 2) + otly;
            }
        }

        ascii_putf__(x, y, col_border_text, COLOR_NONE, text);
    }


    widp child;

    for (auto iter = w->children_display_sorted.begin();
         iter != w->children_display_sorted.end(); ++iter) {

        auto child = iter->second;

        uint8_t child_updated_scissors = false;

        wid_display(child, disable_scissor, &child_updated_scissors, clip);

        /*
         * Need to re-enforce the parent's scissors if the child did
         * their own bit of scissoring?
         */
        if (!disable_scissor && child_updated_scissors) {
            wid_set_scissors(
                tlx,
                tly,
                brx,
                bry);
        }
    }
}

/*
 * Do stuff for all widgets.
 */
void wid_move_all (void)
{_
    if (wid_top_level3.empty()) {
        return;
    }

    uint32_t N = wid_top_level3.size();
    widp w;
    widp wids[N];
    uint32_t n = 0;

    for (auto iter : wid_top_level3) {
        auto w = iter.second;
        wids[n] = w;
        n++;
    }

    while (n--) {
        w = wids[n];

        double x;
        double y;

        if (wid_time >= w->timestamp_moving_end) {

            wid_move_dequeue(w);

            /*
             * If nothing else in the move queue, we're dine.
             */
            if (!w->moving) {
                continue;
            }
        }

        double time_step =
            (double)(wid_time - w->timestamp_moving_begin) /
            (double)(w->timestamp_moving_end - w->timestamp_moving_begin);

        x = (time_step * (double)(w->moving_end.x - w->moving_start.x)) +
            w->moving_start.x;
        y = (time_step * (double)(w->moving_end.y - w->moving_start.y)) +
            w->moving_start.y;

        wid_move_to_abs(w, x, y);
    }
}

/*
 * Do stuff for all widgets.
 */
void wid_gc_all (void)
{_
    widp w;

    std::vector<widp> to_gc;

    for (auto iter : wid_top_level4) {
        auto w = iter.second;
        to_gc.push_back(w);
    }

    for (auto w : to_gc) {
        wid_gc(w);
    }
}

/*
 * Do stuff for all widgets.
 */
void wid_tick_all (void)
{_
//    wid_time = time_get_time_ms_cached();
    if (!game.config.sdl_delay) {
        wid_time += 100/1;
    } else {
        wid_time += 100/game.config.sdl_delay;
    }

    widp w;

    for (auto iter : wid_top_level5) {
        auto w = iter.second;

        verify(w.get());

        if (!w.get()->on_tick) {
            ERR("wid on ticker tree, but no callback set");
        }

        (w.get()->on_tick)(w);
    }
}

static int saved_mouse_x;
static int saved_mouse_y;

void wid_mouse_hide (int value)
{_
    int visible = !value;

    if (visible != wid_mouse_visible) {
        wid_mouse_visible = visible;
        if (visible) {
            sdl_mouse_warp(saved_mouse_x, saved_mouse_y);
        } else {
            saved_mouse_x = mouse_x;
            saved_mouse_y = mouse_y;
        }
    }
}

void wid_mouse_warp (widp w)
{_
    int32_t tlx, tly, brx, bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    int32_t x = (tlx + brx) / 2.0;
    int32_t y = (tly + bry) / 2.0;

    sdl_mouse_warp(x, y);
}

void wid_mouse_move (widp w)
{_
    int32_t tlx, tly, brx, bry;

    wid_get_abs_coords(w, &tlx, &tly, &brx, &bry);

    int32_t x = (tlx + brx) / 2.0;
    int32_t y = (tly + bry) / 2.0;

    saved_mouse_x = mouse_x;
    saved_mouse_y = mouse_y;

    mouse_x = x;
    mouse_y = y;
}

/*
 * Display all widgets
 */
void wid_display_all (void)
{_
    wid_tick_all();
    wid_move_all();

    blit_fbo_bind(FBO_WID);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    game_display();

    glBindTexture(GL_TEXTURE_2D, 0);

    {
        for (auto x = 0; x < ASCII_WIDTH; x++) {
            for (auto y = 0; y < ASCII_HEIGHT; y++) {
                wid_on_screen_at[x][y] = nullptr;
            }
        }
    }

    for (auto iter = wid_top_level.begin();
         iter != wid_top_level.end(); ++iter) {

        auto w = iter->second;

        if (wid_is_hidden(w)) {
            continue;
        }

        wid_display(w,
                    false /* disable_scissors */,
                    0 /* updated_scissors */,
                    true);
    }

    ascii_clear_scissors();

#ifdef DEBUG_WID_FOCUS
    if (wid_focus) {
        ascii_putf(0, ASCII_HEIGHT-4, WHITE, GRAY, L"focus %s", wid_logname(wid_focus).c_str());
    }
    if (wid_over) {
        ascii_putf(0, ASCII_HEIGHT-3, WHITE, GRAY, L"over  %s", wid_logname(wid_over).c_str());
    }
#endif
    {
        color c = ASCII_UI_BOX_INACTIVE_RIGHT_COLOR;
        ascii_putf(0, ASCII_HEIGHT-1, WHITE, c, wid_tooltip_string.c_str());
    }
    {
        color c = ASCII_UI_BOX_INACTIVE_MID_COLOR;
        ascii_putf(0, ASCII_HEIGHT-2, WHITE, c, wid_tooltip2_string.c_str());
    }

    /*
     * FPS counter.
     */
    if (game.config.fps_counter) {
        ascii_putf(0, 1, 
                   GREEN, ASCII_UI_BOX_INACTIVE_MID_COLOR, 
                   L"%u FPS", game.state.fps_count);
    }

    ascii_display();

    if (inverted_gfx) {
        glLogicOp(GL_COPY_INVERTED);
        glEnable(GL_COLOR_LOGIC_OP);
    }

    blit_fbo_unbind();

    glBlendFunc(GL_BLEND_SRC_ALPHA, GL_ZERO);
    glcolor(WHITE);
    blit_fbo(FBO_WID);

    if (inverted_gfx) {
        glLogicOp(GL_COPY);
        glDisable(GL_COLOR_LOGIC_OP);
    }
}

uint8_t wid_is_hidden (widp w)
{_
    verify(w.get());

    if (!w) {
        return (false);
    }

    if (w->hidden) {
        return (true);
    }

    while (w->parent) {
        w = w->parent;

        if (w->hidden) {
            return (true);
        }
    }

    return (false);
}

uint8_t inline wid_this_hidden (widp w)
{_
    return (w->hidden);
}

uint8_t wid_is_always_hidden (widp w)
{_
    verify(w.get());

    if (w->always_hidden) {
        return (true);
    }

    return (false);
}

void wid_move_to_pct (widp w, double x, double y)
{_
    verify(w.get());

    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    double dx = x - wid_get_tl_x(w);
    double dy = y - wid_get_tl_y(w);

    wid_move_delta(w, dx, dy);
}

void wid_move_to_abs (widp w, int32_t x, int32_t y)
{_
    verify(w.get());

    int32_t dx = x - wid_get_tl_x(w);
    int32_t dy = y - wid_get_tl_y(w);

    wid_move_delta(w, dx, dy);
}

void wid_move_to_pct_centered (widp w, double x, double y)
{_
    verify(w.get());

    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    double dx = x - wid_get_tl_x(w);
    double dy = y - wid_get_tl_y(w);

    dx -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    dy -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_delta(w, dx, dy);
}

void wid_move_to_abs_centered (widp w, int32_t x, int32_t y)
{_
    verify(w.get());

    int32_t dx = x - wid_get_tl_x(w);
    int32_t dy = y - wid_get_tl_y(w);

    dx -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    dy -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_delta(w, dx, dy);
}

static void wid_move_enqueue (widp w,
                              int32_t moving_start_x,
                              int32_t moving_start_y,
                              int32_t moving_end_x,
                              int32_t moving_end_y,
                              uint32_t ms)
{_
    verify(w.get());

    if (w->moving) {
        /*
         * Smoother character moves with this.
         */
#if 1
        w->moving_start.x = moving_start_x;
        w->moving_start.y = moving_start_y;
        w->moving_end.x = moving_end_x;
        w->moving_end.y = moving_end_y;
        w->timestamp_moving_begin = wid_time;
        w->timestamp_moving_end = wid_time + ms;
        return;
#else
        /*
         * If this is not a widget with a thing, then just zoom it to the
         * destination. We don't need queues.
         */
        Thingp t = wid_get_thing(w);
        if (!t) {
            w->moving_end.x = moving_end_x;
            w->moving_end.y = moving_end_y;
            w->timestamp_moving_begin = wid_time;
            w->timestamp_moving_end = wid_time + ms;
            return;
        }

        if (w->moving == WID_MAX_MOVE_QUEUE) {
            Thingp t = wid_get_thing(w);

            ERR("too many moves queued up for widget %s",
                wid_logname(w));

            if (t) {
                log(t, "Too many moves queued up");
            }

#ifdef DEBUG_WID_MOVE
            int i;
            CON("    [-] to %f,%f in %d",
                w->moving_end.x, w->moving_end.y,
                w->timestamp_moving_end - wid_time);

            for (i = 0; i < w->moving - 1; i++) {
                wid_move_t *c = &w->move[i];

                CON("    [%d] to %f,%f in %d", i,
                    c->moving_end.x, c->moving_end.y,
                    c->timestamp_moving_end - wid_time);
            }
#endif
        }

        wid_move_t *c = &w->move[w->moving - 1];

        c->timestamp_moving_end = wid_time + ms;
        c->moving_end.x = moving_end_x;
        c->moving_end.y = moving_end_y;
#endif
    } else {
        w->moving_start.x = moving_start_x;
        w->moving_start.y = moving_start_y;
        w->moving_end.x = moving_end_x;
        w->moving_end.y = moving_end_y;
        w->timestamp_moving_begin = wid_time;
        w->timestamp_moving_end = wid_time + ms;

        wid_tree3_moving_wids_insert(w);
    }

    w->moving++;
}

static void wid_move_dequeue (widp w)
{_
    verify(w.get());

    if (!w->moving) {
        return;
    }

    wid_move_to_abs(w, w->moving_end.x, w->moving_end.y);

    w->moving--;
    if (!w->moving) {
        wid_tree3_moving_wids_remove(w);
        return;
    }

    wid_move_t *c = &w->move[0];

    w->moving_start.x = w->moving_end.x;
    w->moving_start.y = w->moving_end.y;
    w->moving_end.x = c->moving_end.x;
    w->moving_end.y = c->moving_end.y;
    w->timestamp_moving_begin = wid_time;
    w->timestamp_moving_end = c->timestamp_moving_end;

    uint8_t i;
    for (i = 0; i < w->moving; i++) {
        if (i < WID_MAX_MOVE_QUEUE - 1) {
            wid_move_t *c = &w->move[i];
            memcpy(c, c+1, sizeof(*c));
        }
    }

    {
        wid_move_t *c = &w->move[i];
        memset(c, 0, sizeof(*c));
    }
}

void wid_move_to_pct_in (widp w, double x, double y, uint32_t ms)
{_
    verify(w.get());

    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    /*
     * Child postion is relative from the parent.
     */
    widp p = w->parent;
    if (p) {
        x += wid_get_tl_x(p);
        y += wid_get_tl_y(p);
    }

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

/*
 * Return numbers in the 0 to 1 range indicating how far the move has
 * progressed from start to end.
 */
void wid_get_move_interpolated_progress (widp w, double *dx, double *dy)
{_
    verify(w.get());

    if (!wid_is_moving(w)) {
        *dx = 0.0;
        *dy = 0.0;
        return;
    }

    double x = wid_get_tl_x(w);
    double y = wid_get_tl_y(w);

    double mx = (double)(x - w->moving_start.x);
    double my = (double)(y - w->moving_start.y);
    double wx = (double)(w->moving_end.x - w->moving_start.x);
    double wy = (double)(w->moving_end.y - w->moving_start.y);

    if (fabs(wx) <= 0.0001) {
        *dx = 0;
    } else {
        *dx = mx / wx;
    }

    if (fabs(wy) <= 0.0001) {
        *dy = 0;
    } else {
        *dy = my / wy;
    }
}

void wid_move_to_abs_in (widp w, int32_t x, int32_t y, uint32_t ms)
{_
    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_abs_poffset_in (widp w, int32_t x, int32_t y, uint32_t ms)
{_
    verify(w.get());

    /*
     * Child postion is relative from the parent.
     */
    widp p = w->parent;
    if (p) {
        x += wid_get_tl_x(p);
        y += wid_get_tl_y(p);
    }

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_delta_in (widp w, int32_t dx, int32_t dy, uint32_t ms)
{_
    int32_t x = wid_get_tl_x(w);
    int32_t y = wid_get_tl_y(w);

    wid_move_enqueue(w, x, y, x + dx, y + dy, ms);
}

void wid_move_to_pct_centered_in (widp w, double x, double y, uint32_t ms)
{_
    verify(w.get());

    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    /*
     * Child postion is relative from the parent.
     */
    widp p = w->parent;
    if (p) {
        x += wid_get_tl_x(p);
        y += wid_get_tl_y(p);
    }

    x -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    y -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_delta_pct_in (widp w, double x, double y, uint32_t ms)
{_
    verify(w.get());

    if (!w->parent) {
        x *= (double)ASCII_WIDTH;
        y *= (double)ASCII_HEIGHT;
    } else {
        x *= wid_get_width(w->parent);
        y *= wid_get_height(w->parent);
    }

    /*
     * Child postion is relative from the parent.
     */
    widp p = w->parent;
    if (p) {
        x += wid_get_tl_x(p);
        y += wid_get_tl_y(p);
    }

    wid_move_enqueue(w,
                     wid_get_tl_x(w),
                     wid_get_tl_y(w),
                     wid_get_tl_x(w) + x,
                     wid_get_tl_y(w) + y,
                     ms);
}

void wid_move_to_abs_centered_in (widp w, int32_t x, int32_t y, uint32_t ms)
{_
    verify(w.get());

    x -= (wid_get_br_x(w) - wid_get_tl_x(w))/2;
    y -= (wid_get_br_y(w) - wid_get_tl_y(w))/2;

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}

void wid_move_to_centered_in (widp w, int32_t x, int32_t y, uint32_t ms)
{_
    verify(w.get());

    wid_move_enqueue(w, wid_get_tl_x(w), wid_get_tl_y(w), x, y, ms);
}
