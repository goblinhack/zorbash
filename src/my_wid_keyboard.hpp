//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

#include "my_string.hpp"
#include "my_wid.hpp"

typedef void (*wid_keyboard_event_t)(Widp, const std::wstring &text);

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
  std::wstring text;

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
  Widp buttons[ WID_KEYBOARD_DOWN ][ WID_KEYBOARD_ACROSS ];

  /*
   * What to call on events
   */
  wid_keyboard_event_t selected;
  wid_keyboard_event_t cancelled;

  /*
   * Just created?
   */
  int is_new;

  size_t max_len;

} wid_keyboard_ctx;

Widp wid_keyboard(const std::wstring &text, const std::wstring &title, wid_keyboard_event_t selected,
                  wid_keyboard_event_t cancelled, size_t max_len);

extern int wid_keyboard_visible;
