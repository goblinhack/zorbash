//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_ui.hpp"
#include "my_wid.hpp"
#include "my_wid_keyboard.hpp"

/*
 * How keys appear on screen
 */
static const char *keys[ WID_KEYBOARD_DOWN ][ WID_KEYBOARD_ACROSS ] = {
    {
        "!",
        "@",
        "#",
        "$",
        "%",
        "^",
        "*",
        "(",
        ")",
        "_",
        "+",
        "DEL",
    },
    {
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "0",
        "-",
        "CLEAR",
    },
    {
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        ";",
        "CANCL",
    },
    {
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        ":",
        "OK",
    },
    {
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "<",
        ">",
        "k",
        ",",
        ".",
        "SPACE",
    },
};

/*
 * The real key behind the scenes
 */
static const char key_char[ WID_KEYBOARD_DOWN ][ WID_KEYBOARD_ACROSS ] = {
    {'!', '@', '#', '$', '%', '^', '*', '(', ')', '_', '+', ''},
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', ''},
    {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        ';',
        '',
    },
    {
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        ':',
        '\n',
    },
    {
        'u',
        'v',
        'w',
        'x',
        'y',
        'z',
        '<',
        '>',
        'k',
        ',',
        '.',
        ' ',
    },
};

int wid_keyboard_visible;

static void    wid_keyboard_destroy(Widp w);
static void    wid_keyboard_set_focus(wid_keyboard_ctx *ctx, int focusx, int focusy);
static uint8_t wid_keyboard_text_input_key_event(Widp w, const SDL_Keysym *key);

static void wid_keyboard_update_buttons(Widp w)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  int width  = 7;
  int height = 5;

  int x, y;

  ctx->b = 0;

  for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
    for (y = 0; y < WID_KEYBOARD_DOWN; y++) {

      Widp b = ctx->buttons[ y ][ x ];

      point tl;
      point br;
      color c;

      tl.x = x * width;
      tl.y = y * height;

      br.x = tl.x;
      br.y = tl.y;
      br.x += 6;
      br.y += 4;

      if ((x == ctx->focusx) && (y == ctx->focusy)) {
        c      = GREEN;
        ctx->b = b;
        wid_raise(b);
      } else {
        wid_lower(b);

        c = GRAY70;
      }

      if (ctx->is_new) {
        wid_set_pos(b, tl, br);
      }

      wid_set_color(b, WID_COLOR_TEXT_FG, c);
    }
  }
  wid_update(w);
}

static void wid_keyboard_event(Widp w, int focusx, int focusy, const SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  const char *add;
  if ((focusx == -1) && (focusy == -1)) {
    add = 0;
  } else {
    add = keys[ focusy ][ focusx ];
  }

  if (key) {
    wid_receive_input(ctx->input, key);
  } else if (! strcasecmp(add, "OK")) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
  } else if (! strcasecmp(add, "CANCL")) {
    (ctx->cancelled)(ctx->w, wid_get_text(ctx->input));
  } else if (! strcasecmp(add, "CLEAR")) {
    for (;;) {
      SDL_Keysym key = {};
      key.sym        = SDLK_BACKSPACE;

      std::wstring tmp = wid_get_text(ctx->input);
      if (tmp.empty()) {
        break;
      }
      wid_receive_input(ctx->input, &key);
    }

  } else if (! strcasecmp(add, "DEL")) {
    SDL_Keysym key = {};
    key.sym        = SDLK_BACKSPACE;
    wid_receive_input(ctx->input, &key);
  } else if (! strcasecmp(add, "SPACE")) {
    SDL_Keysym key = {};
    key.sym        = ' ';
    wid_receive_input(ctx->input, &key);
  } else {
    SDL_Keysym key = {};
    key.sym        = add[ 0 ];
    wid_receive_input(ctx->input, &key);
  }

  if (key && (focusx == -1) && (focusy == -1)) {
    int x, y;

    for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
      for (y = 0; y < WID_KEYBOARD_DOWN; y++) {
        char c = key_char[ y ][ x ];
        if (c == key->sym) {
          focusx = x;
          focusy = y;
          break;
        }
      }

      if ((focusx != -1) && (focusy != -1)) {
        break;
      }
    }
  }

  if ((focusx != -1) && (focusy != -1)) {
    wid_keyboard_set_focus(ctx, focusx, focusy);
  }
}

static uint8_t wid_keyboard_mouse_event(Widp w, int focusx, int focusy)
{
  TRACE_AND_INDENT();
  wid_keyboard_event(w, focusx, focusy, 0 /* key */);

  return true;
}

static uint8_t wid_keyboard_button_mouse_event(Widp w, int x, int y, uint32_t button)
{
  TRACE_AND_INDENT();
  int focus  = wid_get_int_context(w);
  int focusx = (focus & 0xff);
  int focusy = (focus & 0xff00) >> 8;

  return (wid_keyboard_mouse_event(w, focusx, focusy));
}

static void wid_keyboard_focus_right(wid_keyboard_ctx *ctx)
{
  TRACE_AND_INDENT();
  ctx->focusx++;
  if (ctx->focusx > WID_KEYBOARD_ACROSS - 1) {
    ctx->focusx = 0;
  }

  wid_keyboard_update_buttons(ctx->w);
}

static void wid_keyboard_focus_left(wid_keyboard_ctx *ctx)
{
  TRACE_AND_INDENT();
  ctx->focusx--;
  if (ctx->focusx < 0) {
    ctx->focusx = WID_KEYBOARD_ACROSS - 1;
  }

  wid_keyboard_update_buttons(ctx->w);
}

static void wid_keyboard_focus_down(wid_keyboard_ctx *ctx)
{
  TRACE_AND_INDENT();
  ctx->focusy++;
  if (ctx->focusy > WID_KEYBOARD_DOWN - 1) {
    ctx->focusy = 0;
  }

  wid_keyboard_update_buttons(ctx->w);
}

static void wid_keyboard_focus_up(wid_keyboard_ctx *ctx)
{
  TRACE_AND_INDENT();
  ctx->focusy--;
  if (ctx->focusy < 0) {
    ctx->focusy = WID_KEYBOARD_DOWN - 1;
  }

  wid_keyboard_update_buttons(ctx->w);
}

static void wid_keyboard_last_focus(wid_keyboard_ctx *ctx)
{
  TRACE_AND_INDENT();
  ctx->focusx = WID_KEYBOARD_ACROSS - 1;
  ctx->focusy = WID_KEYBOARD_DOWN - 1;

  wid_keyboard_update_buttons(ctx->w);
}

static void wid_keyboard_first_focus(wid_keyboard_ctx *ctx)
{
  TRACE_AND_INDENT();
  ctx->focusx = 0;
  ctx->focusy = 0;

  wid_keyboard_update_buttons(ctx->w);
}

static void wid_keyboard_set_focus(wid_keyboard_ctx *ctx, int focusx, int focusy)
{
  TRACE_AND_INDENT();
  ctx->focusx = focusx;
  ctx->focusy = focusy;

  wid_keyboard_update_buttons(ctx->w);
}

static uint8_t wid_keyboard_parent_key_down(Widp w, const SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  switch (key->sym) {
    case '`' : return false;

    case SDLK_ESCAPE : (ctx->cancelled)(ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_RETURN :
      {
        (ctx->selected)(ctx->w, wid_get_text(ctx->input));
        return true;

        case SDLK_LEFT : wid_keyboard_focus_left(ctx); break;

        case SDLK_RIGHT : wid_keyboard_focus_right(ctx); break;

        case SDLK_UP : wid_keyboard_focus_up(ctx); break;

        case SDLK_DOWN : wid_keyboard_focus_down(ctx); break;

        case SDLK_HOME : wid_keyboard_first_focus(ctx); break;

        case SDLK_END : wid_keyboard_last_focus(ctx); break;

        default : wid_keyboard_event(ctx->w, -1, -1, key); return true;
      }
  }

  return true;
}

static uint8_t wid_keyboard_parent_joy_button(Widp w, int x, int y)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);
  int ret = false;

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  if (sdl.joy_buttons[ SDL_JOY_BUTTON_A ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_B ]) {
    (ctx->cancelled)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_X ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_Y ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_LEFT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_RIGHT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_STICK_DOWN ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_STICK_DOWN ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_START ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_XBOX ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_BACK ]) {
    (ctx->cancelled)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_UP ]) {
    wid_keyboard_focus_up(ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_DOWN ]) {
    wid_keyboard_focus_down(ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT ]) {
    wid_keyboard_focus_left(ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT ]) {
    wid_keyboard_focus_right(ctx);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_FIRE ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_FIRE ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }

  wid_keyboard_update_buttons(ctx->w);
  if (ctx->b) {
    wid_mouse_warp(ctx->b);
  }

  return ret;
}

static uint8_t wid_keyboard_button_key_event(Widp w, const SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  switch (key->sym) {
    case '`' : return false;

    case SDLK_ESCAPE : (ctx->cancelled)(ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_RETURN : (ctx->selected)(ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_BACKSPACE :
    case SDLK_DELETE :
    case SDLK_LEFT :
    case SDLK_RIGHT :
    case SDLK_UP :
    case SDLK_DOWN :
    case SDLK_HOME :
    case SDLK_END : break;

    default : wid_keyboard_event(w, -1, -1, key); return true;
  }

  return false;
}

static uint8_t wid_keyboard_button_joy_button_event(Widp w, int x, int y)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);
  int ret = false;

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  if (sdl.joy_buttons[ SDL_JOY_BUTTON_A ]) {
    ret = wid_keyboard_mouse_event(w, ctx->focusx, ctx->focusy);
  }

  if (sdl.joy_buttons[ SDL_JOY_BUTTON_B ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_X ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_BACKSPACE;
    wid_keyboard_text_input_key_event(ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_Y ]) {
    (ctx->selected)(ctx->w, wid_get_text(ctx->input));
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_LEFT ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_LEFT;
    wid_keyboard_text_input_key_event(ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_TOP_RIGHT ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_RIGHT;
    wid_keyboard_text_input_key_event(ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_STICK_DOWN ]) {
    wid_keyboard_mouse_event(w, ctx->focusx, ctx->focusy);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_STICK_DOWN ]) {
    wid_keyboard_mouse_event(w, ctx->focusx, ctx->focusy);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_START ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_XBOX ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_BACK ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_UP ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_DOWN ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT ]) {}
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_LEFT_FIRE ]) {
    SDL_Keysym key = {};
    key.sym        = SDLK_BACKSPACE;
    wid_receive_input(ctx->input, &key);
    ret = true;
  }
  if (sdl.joy_buttons[ SDL_JOY_BUTTON_RIGHT_FIRE ]) {
    wid_keyboard_mouse_event(w, ctx->focusx, ctx->focusy);
    ret = true;
  }

  wid_keyboard_update_buttons(ctx->w);
  if (ctx->b) {
    wid_mouse_warp(ctx->b);
  }

  return ret;
}

static uint8_t wid_keyboard_text_input_key_event(Widp w, const SDL_Keysym *key)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  /*
   * Don't process events too soon. Else the menu might not even have
   * appeared.
   */
  if (time_ms() - ctx->created < 100) {
    return false;
  }

  switch (key->sym) {
    case SDLK_ESCAPE : (ctx->cancelled)(ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_RETURN : (ctx->selected)(ctx->w, wid_get_text(ctx->input)); return true;

    case SDLK_BACKSPACE :
    case SDLK_DELETE :
    case SDLK_LEFT :
    case SDLK_RIGHT :
    case SDLK_UP :
    case SDLK_DOWN :
    case SDLK_HOME :
    case SDLK_END : wid_receive_input(ctx->input, key); return true;

    default : wid_keyboard_event(w, -1, -1, key); return true;
  }

  return false;
}

static void wid_keyboard_mouse_over(Widp w, int relx, int rely, int wheelx, int wheely)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  if (! relx && ! rely && ! wheelx && ! wheely) {
    return;
  }

  /*
   * If we recreate the keyboard with a fixed focus we will be told about
   * a mouse over event immediately which may not be over the focus item
   * and will cause us to move. Annoying.
   */
  if (time_ms() - ctx->created < 100) {
    return;
  }

  int focus  = wid_get_int_context(w);
  int focusx = (focus & 0xff);
  int focusy = (focus & 0xff00) >> 8;

  wid_keyboard_set_focus(ctx, focusx, focusy);
}

static void wid_keyboard_destroy(Widp w)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  wid_set_void_context(w, 0);
  oldptr(MTYPE_MISC, ctx);

  wid_keyboard_visible = false;
}

static void wid_keyboard_tick(Widp w)
{
  TRACE_AND_INDENT();
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) wid_get_void_context(w);
  verify(MTYPE_MISC, ctx);

  static int val;
  static int delta = 1;
  static int step  = 2;

  val += delta * step;

  if (val > 255) {
    val   = 255;
    delta = -1;
  }

  if (val < 200) {
    val   = 200;
    delta = 1;
  }

  int x, y;

  for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
    for (y = 0; y < WID_KEYBOARD_DOWN; y++) {

      if ((x != ctx->focusx) || (y != ctx->focusy)) {
        continue;
      }

      Widp b = ctx->buttons[ y ][ x ];

      color c;
      c   = GREEN;
      c.g = val;

      /*
       * Make sure the other widgets look plain in all modes.
       */
      int mode;
      for (mode = WID_MODE_NORMAL; mode < WID_MODE_LAST; mode++) {
        wid_set_mode(b, (wid_mode) mode);
        wid_set_color(b, WID_COLOR_TEXT_FG, c);
      }

      wid_set_mode(w, (wid_mode) WID_MODE_NORMAL);
    }
  }
}

static void wid_keyboard_bg_tick(Widp w)
{
  TRACE_AND_INDENT();
  if (g_opt_ascii) {
    return;
  }

  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  std::string t = "grid";
  blit_init();
  tile_blit(tile_find_mand(t.c_str()), point(0, 0), point(game->config.ui_pix_width, game->config.ui_pix_height));
  blit_flush();
}

Widp wid_keyboard(const std::wstring &text, const std::wstring &title, wid_keyboard_event_t selected,
                  wid_keyboard_event_t cancelled, size_t max_len)
{
  TRACE_AND_INDENT();
  wid_keyboard_visible = true;

  /*
   * Create a context to hold button info so we can update it when the focus
   * changes
   */
  wid_keyboard_ctx *ctx = (wid_keyboard_ctx *) myzalloc(sizeof(*ctx), "wid keyboard");
  ctx->focusx           = -1;
  ctx->focusy           = -1;
  ctx->cancelled        = cancelled;
  ctx->selected         = selected;

  Widp window  = wid_new_square_window("wid keyboard");
  ctx->w       = window;
  ctx->is_new  = true;
  ctx->max_len = max_len;

  /*
   * Main window
   */
  const auto width  = WID_KEYBOARD_ACROSS * 7 + 1;
  const auto height = WID_KEYBOARD_DOWN * 5 + 8;

  int left_half  = width / 2;
  int right_half = width - left_half;
  int top_half   = height / 2;
  int bot_half   = height - top_half;

  {
    point tl = make_point(TERM_WIDTH / 2 - left_half, TERM_HEIGHT / 2 - top_half);
    point br = make_point(TERM_WIDTH / 2 + right_half, TERM_HEIGHT / 2 + bot_half);

    wid_set_pos(window, tl, br);
    wid_set_style(window, UI_WID_STYLE_NORMAL);
    wid_set_on_key_down(window, wid_keyboard_parent_key_down);
    wid_set_on_joy_button(window, wid_keyboard_parent_joy_button);
    wid_set_on_destroy(window, wid_keyboard_destroy);
    wid_set_void_context(window, ctx);
  }

  /*
   * Create the title
   */
  {
    Widp w = wid_new_square_button(window, "wid keyboard title");

    point tl = {5, 1};
    point br = {width - 5, 1};

    wid_set_pos(w, tl, br);
    wid_set_text(w, title);
    wid_set_shape_none(w);
    wid_set_color(w, WID_COLOR_TEXT_FG, YELLOW);
  }

  /*
   * Create the text input container
   */
  {
    Widp w = wid_new_square_button(window, "wid keyboard input");

    ctx->input = w;

    point tl = {10, 3};
    point br = {width - 10, 5};

    wid_set_pos(w, tl, br);
    wid_set_text(w, text);
    wid_set_show_cursor(w, true);
    wid_set_on_key_down(w, wid_keyboard_text_input_key_event);
    wid_set_void_context(w, ctx);
    wid_set_style(w, UI_WID_STYLE_RED);

    if (max_len) {
      wid_set_text_max_len(w, max_len);
    }

    wid_set_color(w, WID_COLOR_BG, GRAY20);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);

    wid_set_mode(w, WID_MODE_OVER);

    wid_set_color(w, WID_COLOR_BG, GRAY20);
    wid_set_color(w, WID_COLOR_TEXT_FG, GREEN);

    wid_set_mode(w, WID_MODE_NORMAL);
    wid_set_on_tick(w, wid_keyboard_bg_tick);
  }

  /*
   * Create the button container
   */
  {
    Widp button_container = wid_new_square_button(window, "wid keyboard buttons");
    wid_set_shape_none(button_container);
    wid_set_on_tick(button_container, wid_keyboard_tick);

    point tl = {1, 7};
    point br = {width - 1, height - 2};

    wid_set_pos(button_container, tl, br);
    wid_set_void_context(button_container, ctx);

    /*
     * Create the buttons
     */
    int x, y;

    for (x = 0; x < WID_KEYBOARD_ACROSS; x++) {
      for (y = 0; y < WID_KEYBOARD_DOWN; y++) {
        Widp b                 = wid_new_square_button(button_container, "wid keyboard button");
        ctx->buttons[ y ][ x ] = b;

        wid_set_text(b, keys[ y ][ x ]);

        wid_set_on_mouse_over_begin(b, wid_keyboard_mouse_over);
        wid_set_on_key_down(b, wid_keyboard_button_key_event);
        wid_set_on_joy_button(b, wid_keyboard_button_joy_button_event);
        wid_set_on_mouse_down(b, wid_keyboard_button_mouse_event);
        wid_set_style(b, UI_WID_STYLE_DARK);

        wid_set_color(b, WID_COLOR_TEXT_FG, GREEN);

        wid_set_mode(b, WID_MODE_OVER);

        wid_set_color(b, WID_COLOR_TEXT_FG, GREEN);

        wid_set_mode(b, WID_MODE_NORMAL);

        wid_set_void_context(b, ctx);
        int focus = (y << 8) | x;
        wid_set_int_context(b, focus);

        if (! strcasecmp(keys[ y ][ x ], "CANCL")) {
          wid_set_style(b, UI_WID_STYLE_RED);
        }

        if (! strcasecmp(keys[ y ][ x ], "OK")) {
          wid_set_style(b, UI_WID_STYLE_GREEN);
        }
      }
    }
  }

  wid_keyboard_update_buttons(window);
  wid_set_do_not_lower(window, 1);
  wid_update(window);
  wid_raise(window);
  wid_set_focus(window);

  ctx->created = time_ms();

  return window;
}
