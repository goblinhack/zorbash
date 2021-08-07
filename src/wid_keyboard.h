/*
 * Copyright (C) 2011-2015 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

typedef void(*wid_keyboard_event_t)(Widp, const char *text);

#define WID_KEYBOARD_ACROSS 12
#define WID_KEYBOARD_DOWN   5

typedef struct {
    /*
     * Parent widget
     */
    Widp w;

    /*
     * Current button
     */
    Widp b;

    /*
     * Text input widget
     */
    Widp input;

    /*
     * Entered text.
     */
    char text[MAXLONGSTR];

    /*
     * Item currently in focus
     */
    int focusx;
    int focusy;

    /*
     * When the keyboard was made.
     */
    uint32_t created;

    /*
     * Items in the keyboard
     */
    Widp buttons[WID_KEYBOARD_DOWN][WID_KEYBOARD_ACROSS];

    /*
     * What to call on events
     */
    wid_keyboard_event_t selected;
    wid_keyboard_event_t cancelled;

    /*
     * Just created?
     */
    int is_new;

} wid_keyboard_ctx;

Widp wid_keyboard (const char *text,
                   const char *title,
                   wid_keyboard_event_t selected,
                   wid_keyboard_event_t cancelled);

extern int wid_keyboard_visible;
