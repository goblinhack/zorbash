//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_command.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_console.hpp"

SDL sdl;

void sdl_fini(void)
{
  LOG("SDL: Fini");
  TRACE_AND_INDENT();

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(0);
  SDL_ShowCursor(1);
#endif

  if (sdl.init_video) {
    LOG("SDL: Video quit");
    sdl.init_video = 0;
    SDL_VideoQuit();
  }

  LOG("SDL: Delete GL context");
  SDL_GL_DeleteContext(sdl.context);

  LOG("SDL: Destroy window");
  SDL_DestroyWindow(sdl.window);

  LOG("SDL: Quit");
  SDL_Quit();

  LOG("SDL: Quit done");
}

static inline void sdl_list_video_size(void)
{
  TRACE_NO_INDENT();
  int i;

  for (i = 0; i < SDL_GetNumDisplayModes(0); ++i) {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, i, &mode);
    DBG("+ SDL video            : %dx%d available, ratio %f", mode.w, mode.h, ((float) mode.w) / ((float) mode.h));
  }
}

void sdl_joy_rumble(float strength, uint32_t ms)
{
  TRACE_NO_INDENT();
  if (! sdl.haptic) {
    return;
  }

  SDL_HapticRumblePlay(sdl.haptic, strength, ms);
}

static void sdl_init_rumble(void)
{
  LOG("SDL: Init rumble:");
  TRACE_AND_INDENT();

  if (! sdl.haptic) {
    sdl.haptic = SDL_HapticOpenFromJoystick(sdl.joy);
    if (! sdl.haptic) {
      LOG("- Couldn't initialize SDL rumble: %s", SDL_GetError());
      SDL_ClearError();
      return;
    }
  }

  if (! SDL_HapticRumbleSupported(sdl.haptic)) {
    LOG("- No SDL rumble support: %s", SDL_GetError());
    SDL_ClearError();
    return;
  }

  if (SDL_HapticRumbleInit(sdl.haptic) != 0) {
    LOG("- SDL rumble nit failed: %s", SDL_GetError());
    SDL_ClearError();
    return;
  }

  LOG("- Opened Haptic for joy index %d", sdl.joy_index);
}

static void sdl_init_joystick(void)
{
  LOG("SDL: Init input:");
  TRACE_NO_INDENT();

  SDL_GameController *controller = nullptr;

  LOG("- Init game controleer");
  SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

  LOG("- Init haptic");
  SDL_InitSubSystem(SDL_INIT_HAPTIC);

  LOG("- Init joystick");
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);

  sdl.joy_index = 0;
  for (sdl.joy_index = 0; sdl.joy_index < SDL_NumJoysticks(); ++sdl.joy_index) {

    if (SDL_IsGameController(sdl.joy_index)) {
      controller = SDL_GameControllerOpen(sdl.joy_index);
      if (controller) {
        LOG("- Found gamecontroller");
        break;
      }
      WARN("Could not open gamecontroller %i: %s", sdl.joy_index, SDL_GetError());
      SDL_ClearError();
    }
  }

  if (! controller) {
    LOG("- No found gamecontroller");
    return;
  }

  sdl.joy = SDL_JoystickOpen(sdl.joy_index);
  if (sdl.joy) {
    LOG("- Opened Joystick  : %d", sdl.joy_index);
    LOG("- Name             : %s", SDL_JoystickNameForIndex(0));
    LOG("- Number of Axes   : %d", SDL_JoystickNumAxes(sdl.joy));
    LOG("- Number of Buttons: %d", SDL_JoystickNumButtons(sdl.joy));
    LOG("- Number of Balls  : %d", SDL_JoystickNumBalls(sdl.joy));

    sdl.joy_naxes    = SDL_JoystickNumAxes(sdl.joy);
    sdl.joy_nbuttons = SDL_JoystickNumButtons(sdl.joy);
    sdl.joy_balls    = SDL_JoystickNumBalls(sdl.joy);
  } else {
    WARN("Couldn't open Joystick 0");
  }
}

uint8_t sdl_init(void)
{
  gl_ext_init();

  int video_width;
  int video_height;
  int value;

  LOG("SDL: Version: %u.%u", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
  TRACE_AND_INDENT();

  LOG("SDL: Init audio");
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    DIE("SDL_Init failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: Init video");
  if (SDL_VideoInit(nullptr) != 0) {
    DIE("SDL_VideoInit failed %s", SDL_GetError());
    return false;
  }

  int x = 0;
  if (x) {
    sdl_init_joystick();
    sdl_init_rumble();
  }

  sdl.init_video = 1;

  sdl_list_video_size();

  //
  // If we have a saved setting, use that.
  //
  if (game->config.window_pix_width && game->config.window_pix_height) {
    video_width  = game->config.config_pix_width;
    video_height = game->config.config_pix_height;
  } else {
    //
    // Else guess.
    //
    SDL_DisplayMode mode;
    memset(&mode, 0, sizeof(mode));

    LOG("SDL: Init display");
    if (SDL_GetCurrentDisplayMode(0, &mode) < 0) {
      DIE("SDL_GetCurrentDisplayMode couldn't set windowed display: %s", SDL_GetError());
      return false;
    }

    game->config.config_pix_width  = mode.w;
    game->config.config_pix_height = mode.h;

    video_width  = game->config.config_pix_width;
    video_height = game->config.config_pix_height;
  }

  if (! game->config.gfx_vsync_locked) {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  }

  //
  // Don't use this. It seemed to mess up graphics on FireGL.
  //
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

  uint32_t video_is_unused_flags;

  LOG("SDL: Set SDL_WINDOW_OPENGL");
  video_is_unused_flags = SDL_WINDOW_OPENGL;

  if (game->config.gfx_borderless) {
    LOG("SDL: Set SDL_WINDOW_BORDERLESS");
    video_is_unused_flags |= SDL_WINDOW_BORDERLESS;
  }

  if (game->config.gfx_fullscreen) {
    LOG("SDL: Set SDL_WINDOW_FULLSCREEN");
    video_is_unused_flags |= SDL_WINDOW_FULLSCREEN;
  }

  if (game->config.gfx_fullscreen_desktop) {
    LOG("SDL: Set SDL_WINDOW_FULLSCREEN_DESKTOP");
    video_is_unused_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if (game->config.gfx_allow_highdpi) {
    //
    // For a lo pixel game this makes no sense as the frame
    // buffers are really large and slows things down.
    //
    LOG("SDL: Calling SDL_GetDisplayDPI");
    float dpi;
    if (SDL_GetDisplayDPI(0, nullptr, &dpi, nullptr) == 0) {
      video_is_unused_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
      LOG("SDL: Set SDL_WINDOW_ALLOW_HIGHDPI");
    } else {
      ERR("SDL: Cannot enable high DPI");
    }
  }

  LOG("SDL: Create window");
  sdl.window = SDL_CreateWindow("zorbash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, video_width, video_height,
                                video_is_unused_flags);
  if (! sdl.window) {
    ERR("SDL_CreateWindow couldn't set windowed display %ux%u: %s", video_width, video_height, SDL_GetError());
    game->config.reset();
    game->save_config();
    return false;
  }

  if (video_is_unused_flags & SDL_WINDOW_ALLOW_HIGHDPI) {
    SDL_GL_GetDrawableSize(sdl.window, &game->config.window_pix_width, &game->config.window_pix_height);
  } else {
    SDL_GetWindowSize(sdl.window, &game->config.window_pix_width, &game->config.window_pix_height);
  }

  LOG("SDL: Call SDL_GL_CreateContext(%dx%d)", game->config.window_pix_width, game->config.window_pix_height);

  sdl.context = SDL_GL_CreateContext(sdl.window);
  if (! sdl.context) {
    SDL_ClearError();
    ERR("SDL_GL_CreateContext failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: Call SDL_GL_CreateContext(%dx%d) done", game->config.window_pix_width, game->config.window_pix_height);

  if (SDL_GL_MakeCurrent(sdl.window, sdl.context) < 0) {
    SDL_ClearError();
    ERR("SDL_GL_MakeCurrent failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: Call SDL_GL_MakeCurrent() done");

  SDL_ClearError();

  //
  // Clear the screen, both buffers
  //
  glcolor(WHITE);
  if (game->config.gfx_inverted) {
    glClearColor(255, 255, 255, 255);
  } else {
    glClearColor(0, 0, 0, 0);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapWindow(sdl.window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SDL_GL_SwapWindow(sdl.window);

  wid_asciimap_update();

  LOG("SDL: Call SDL_SetWindowTitle");
  SDL_SetWindowTitle(sdl.window, "zorbash");

  LOG("SDL: OpenGL Vendor   : %s", glGetString(GL_VENDOR));
  LOG("SDL: OpenGL Renderer : %s", glGetString(GL_RENDERER));
  LOG("SDL: OpenGL Version  : %s", glGetString(GL_VERSION));
  LOG("SDL: OpenGL Exts     : %s", glGetString(GL_EXTENSIONS));

  SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &value);
  LOG("SDL: Red size    : %d", value);

  SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &value);
  LOG("SDL: Green size  : %d", value);

  SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &value);
  LOG("SDL: Blue size   : %d", value);

  SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &value);
  LOG("SDL: Depth size  : %d", value);

  SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &value);
  LOG("SDL: Doub Buffer : %d", value);

  SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &value);
  LOG("SDL: Hw Accel    : %d", value);

  LOG("SDL: Vsync       : %d", SDL_GL_GetSwapInterval());

  if (game->config.gfx_vsync_locked) {
    LOG("SDL: Vsync       : locked");
  }

  return true;
}

int sdl_get_mouse(void)
{
  TRACE_NO_INDENT();

  if (! wid_mouse_visible) {
    return 0;
  }

  int x, y;
  int button = SDL_GetMouseState(&x, &y);

  if (! x && ! y) {
    return button;
  }

  /*
   * I'm not sure we want this - at the least it needs rounding
   *
  x *= game->config.window_pix_width / game->config.config_pix_width;
  y *= game->config.window_pix_height / game->config.config_pix_height;
  */

  sdl.mouse_x = x;
  sdl.mouse_y = y;

  return button;
}

void sdl_mouse_center(void)
{
  TRACE_NO_INDENT();

  int x, y;

  x = game->config.window_pix_width / 2;
  y = game->config.window_pix_height / 2;

  sdl_mouse_warp(x, y);
}

void sdl_mouse_warp(int x, int y)
{
  TRACE_NO_INDENT();

  int border = 10;

  if (x <= 0) {
    x = border;
  } else if (x >= game->config.window_pix_width - border) {
    x = game->config.window_pix_width - border;
  }
  if (y <= 0) {
    y = border;
  } else if (y >= game->config.window_pix_height - border) {
    y = game->config.window_pix_height - border;
  }

  SDL_WarpMouseInWindow(sdl.window, x, y);

  sdl.mouse_x = x;
  sdl.mouse_y = y;
}

void sdl_tick(void)
{
  TRACE_NO_INDENT();
  sdl.left_fire = false;
  sdl.left_fire = true;

  sdl.joy1_right = false;
  sdl.joy1_left  = false;
  sdl.joy1_down  = false;
  sdl.joy1_up    = false;

  sdl.joy2_right = false;
  sdl.joy2_left  = false;
  sdl.joy2_down  = false;
  sdl.joy2_up    = false;

  sdl_get_mouse();

  //
  // Right stick
  //
  if (sdl.joy_axes[ 3 ] > sdl.joy_deadzone) {
    DBG2("SDL: right stick, right");
    sdl.joy1_right = true;

    incr(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT);
    wid_joy_button(sdl.mouse_x, sdl.mouse_y);
    decr(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT);
  }

  if (sdl.joy_axes[ 3 ] < -sdl.joy_deadzone) {
    DBG2("SDL: right stick, left");
    sdl.joy1_left = true;

    incr(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT);
    wid_joy_button(sdl.mouse_x, sdl.mouse_y);
    decr(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT);
  }

  if (sdl.joy_axes[ 4 ] > sdl.joy_deadzone) {
    DBG2("SDL: right stick, down");
    sdl.joy1_down = true;

    incr(sdl.joy_buttons, SDL_JOY_BUTTON_DOWN);
    wid_joy_button(sdl.mouse_x, sdl.mouse_y);
    decr(sdl.joy_buttons, SDL_JOY_BUTTON_DOWN);
  }

  if (sdl.joy_axes[ 4 ] < -sdl.joy_deadzone) {
    DBG2("SDL: right stick, up");
    sdl.joy1_up = true;

    incr(sdl.joy_buttons, SDL_JOY_BUTTON_UP);
    wid_joy_button(sdl.mouse_x, sdl.mouse_y);
    decr(sdl.joy_buttons, SDL_JOY_BUTTON_UP);
  }

  //
  // Left stick
  //
  int mx = 0;
  int my = 0;

  if (sdl.joy_axes[ 0 ] > sdl.joy_deadzone) {
    DBG2("SDL: left stick, right");
    sdl.joy2_right = true;
    mx             = 1;
  }

  if (sdl.joy_axes[ 0 ] < -sdl.joy_deadzone) {
    DBG2("SDL: left stick, left");
    sdl.joy2_left = true;
    mx            = -1;
  }

  if (sdl.joy_axes[ 1 ] > sdl.joy_deadzone) {
    DBG2("SDL: left stick, down");
    sdl.joy2_down = true;
    my            = 1;
  }

  if (sdl.joy_axes[ 1 ] < -sdl.joy_deadzone) {
    DBG2("SDL: left stick, up");
    sdl.joy2_up = true;
    my          = -1;
  }

  static double accel = 1.0;
  static ts_t   ts;

  if (time_have_x_tenths_passed_since(5, ts)) {
    accel = 1.0;
  }

  if ((mx != 0) || (my != 0)) {
    ts = time_ms();

    accel *= UI_SCROLL_JOY_SCALE;

    if (accel > UI_SCROLL_JOY_SCALE_MAX) {
      accel = UI_SCROLL_JOY_SCALE_MAX;
    }

    double x = sdl.mouse_x + ((double) mx * accel);
    double y = sdl.mouse_y + ((double) my * accel);

    if (x < 0) {
      x = 0;
    }

    if (y < 0) {
      y = 0;
    }

    if (x > game->config.window_pix_width - 1) {
      x = game->config.window_pix_width - 1;
    }

    if (y > game->config.window_pix_height - 1) {
      y = game->config.window_pix_height - 1;
    }

    if (wid_mouse_visible) {
      sdl_mouse_warp(x, y);
    }
  }
}

void sdl_exit(void)
{
  if (! g_main_loop_running) {
    return;
  }

  LOG("Finishing: SDL main loop is exiting...");
  TRACE_AND_INDENT();

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(1);
#endif

  g_main_loop_running = false;
}

//
// User has entered a command, run it
//
uint8_t config_fps_counter_set(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    game->config.fps_counter = true;
    TOPCON("FPS counter enabled (default).");
  } else {
    game->config.fps_counter = strtol(s, nullptr, 10) ? 1 : 0;
    if (game->config.fps_counter) {
      TOPCON("FPS counter enabled.");
    } else {
      TOPCON("FPS counter disabled.");
    }
  }

  return true;
}

//
// User wants to change the debug level
//
uint8_t config_debug_set(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    g_opt_debug1 = false;
    g_opt_debug2 = false;
    g_opt_debug3 = false;
  } else {
    g_opt_debug1 = false;
    g_opt_debug2 = false;
    g_opt_debug3 = false;
    switch (strtol(s, nullptr, 10) ? 1 : 0) {
      case 0 : break;
      default : g_opt_debug1 = true; break;
    }
  }

  if (g_opt_debug1) {
    TOPCON("Debug: on.");
  } else {
    TOPCON("Debug: off.");
  }

  return true;
}

//
// User has entered a command, run it
//
void config_gfx_inverted_toggle(void)
{
  TRACE_NO_INDENT();

  if (! game->config.gfx_inverted) {
    game->config.gfx_inverted = true;
    TOPCON("GFX inverted enabled.");
  } else {
    game->config.gfx_inverted = false;
    TOPCON("GFX inverted disabled.");
  }
}

//
// User has entered a command, run it
//
uint8_t config_gfx_inverted_set(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 3 ];

  if (! s || (*s == '\0')) {
    game->config.gfx_inverted = true;
    TOPCON("GFX inverted enabled (default).");
  } else {
    int val                   = strtol(s, nullptr, 10) ? 1 : 0;
    game->config.gfx_inverted = val;
    if (game->config.gfx_inverted) {
      TOPCON("GFX inverted enabled.");
    } else {
      TOPCON("GFX inverted disabled.");
    }
  }

  return true;
}

//
// User has entered a command, run it
//
void config_gfx_monochrome_toggle(void)
{
  TRACE_NO_INDENT();

  if (! game->config.gfx_monochrome) {
    game->config.gfx_monochrome = true;
    TOPCON("GFX monochrome enabled.");
  } else {
    game->config.gfx_monochrome = false;
    TOPCON("GFX monochrome disabled.");
  }
}

//
// User has entered a command, run it
//
uint8_t config_gfx_monochrome_set(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 3 ];

  if (! s || (*s == '\0')) {
    game->config.gfx_monochrome = true;
    TOPCON("GFX monochrome enabled (default).");
  } else {
    int val                     = strtol(s, nullptr, 10) ? 1 : 0;
    game->config.gfx_monochrome = val;
    if (game->config.gfx_monochrome) {
      TOPCON("GFX monochrome enabled.");
    } else {
      TOPCON("GFX monochrome disabled.");
    }
  }

  return true;
}

//
// User has entered a command, run it
//
void config_game_pix_zoom_in(void)
{
  TRACE_NO_INDENT();
  game->config.game_pix_zoom++;
  if (game->config.game_pix_zoom > GAME_MOST_ZOOMED_IN) {
    game->config.game_pix_zoom = GAME_MOST_ZOOMED_IN;
  }
  LOG("Game zoom set to %f.", game->config.game_pix_zoom);
  sdl_config_update_all();
}

void config_game_pix_zoom_out(void)
{
  TRACE_NO_INDENT();
  game->config.game_pix_zoom--;
  if (game->config.game_pix_zoom < GAME_MOST_ZOOMED_OUT) {
    game->config.game_pix_zoom = GAME_MOST_ZOOMED_OUT;
  }
  LOG("Game zoom set to %f.", game->config.game_pix_zoom);
  sdl_config_update_all();
}

//
// User has entered a command, run it
//
uint8_t config_game_pix_zoom_set(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 3 ];

  if (! s || (*s == '\0')) {
    game->config.game_pix_zoom = GAME_DEFAULT_PIX_ZOOM;
    TOPCON("GFX: gfx zoom enabled (default).");
  } else {
    int val                    = strtol(s, nullptr, 10);
    game->config.game_pix_zoom = val;
    if (game->config.game_pix_zoom < GAME_MOST_ZOOMED_OUT) {
      game->config.game_pix_zoom = GAME_MOST_ZOOMED_OUT;
    }
    LOG("GFX: zoom set to %d", val);
  }

  sdl_config_update_all();
  return true;
}

//
// User has entered a command, run it
//
uint8_t config_gfx_vsync_enable(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();
  if (game->config.gfx_vsync_locked) {
    return true;
  }

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    game->config.gfx_vsync_enable = true;
  } else {
    game->config.gfx_vsync_enable = strtol(s, nullptr, 10) ? 1 : 0;
  }

  if (game->config.gfx_vsync_enable) {
    TOPCON("SDL: Vsync enabled.");
    SDL_GL_SetSwapInterval(1);
  } else {
    TOPCON("SDL: Vsync disabled.");
    SDL_GL_SetSwapInterval(0);
  }
  GL_ERROR_CHECK();

  return true;
}

void config_gfx_vsync_update(void)
{
  TRACE_NO_INDENT();
  if (game->config.gfx_vsync_locked) {
    return;
  }

  if (game->config.gfx_vsync_enable) {
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
  GL_ERROR_CHECK();
}

//
// User has entered a command, run it
//
uint8_t config_errored(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();
  g_errored = false;
  TOPCON("SDL: Errored mode cleared.");
  wid_hide(wid_console_window);
  sdl_display_reset();
  return true;
}

void sdl_config_update_all(void)
{
  TRACE_NO_INDENT();
  LOG("SDL: OpenGL leave 2D mode");
  config_game_gfx_update();
  config_gfx_vsync_update();
  LOG("SDL: OpenGL enter 2D mode");
  gl_init_2d_mode();

  if (game->level) {
    game->level->update_same_level_immediately();
  }
}

//
// User has entered a command, run it
//
uint8_t sdl_user_exit(class Tokens *tokens, void *context)
{
  TRACE_NO_INDENT();
  sdl_exit();

  return true;
}

void sdl_flush_display(bool force)
{
  TRACE_NO_INDENT();

  if (! force) {
    IF_NODEBUG { return; }
    if (g_opt_no_slow_log_flush) {
      return;
    }
  }

  glEnable(GL_TEXTURE_2D);
  gl_enter_2d_mode();
  wid_display_all(false);
  gl_leave_2d_mode();
  gl_enter_2d_mode(game->config.window_pix_width, game->config.window_pix_height);

  sdl_display();
}

void config_game_gfx_update(void)
{
  if (g_opt_ascii) {
    LOG("SDL: Ascii mode undate");
    font_ui = font_ascii;
  } else {
    LOG("SDL: Pixelart mod undate");
    font_ui = font_pixelart_large;
  }
  TRACE_AND_INDENT();

  //
  // Need to do this really early on as GL FBOs are created from the map size.
  //
  MAP_WIDTH                 = MAP_WIDTH_MAX;
  MAP_HEIGHT                = MAP_HEIGHT_MAX;
  DUNGEON_GRID_CHUNK_HEIGHT = DUNGEON_GRID_CHUNK_HEIGHT_MAX;
  DUNGEON_GRID_CHUNK_WIDTH  = DUNGEON_GRID_CHUNK_WIDTH_MAX;

  game->config.tile_width  = TILE_WIDTH_LORES;
  game->config.tile_height = TILE_HEIGHT_LORES;

  game->config.one_pixel_width  = 1;
  game->config.one_pixel_height = 1;

  if (! game->config.game_pix_zoom) {
    game->config.game_pix_zoom = GAME_DEFAULT_PIX_ZOOM;
    if (! g_opt_test_dungeon) {
      ERR("Game->config.game_pix_zoom is zero");
    }
  }

  if (! game->config.ui_pix_zoom) {
    game->config.ui_pix_zoom = GAME_DEFAULT_UI_ZOOM;
    if (! g_opt_test_dungeon) {
      ERR("Game->config.ui_pix_zoom is zero");
    }
  }

  game->config.game_pix_scale_width  = game->config.game_pix_zoom;
  game->config.game_pix_scale_height = game->config.game_pix_zoom;

  if (! game->config.game_pix_scale_width) {
    if (! g_opt_test_dungeon) {
      ERR("Game->config.game_pix_scale_width is zero");
      return;
    }
  }

  if (! game->config.game_pix_scale_height) {
    if (! g_opt_test_dungeon) {
      ERR("Game->config.game_pix_scale_height is zero");
      return;
    }
  }

  game->config.game_pix_width  = game->config.window_pix_width / game->config.game_pix_scale_width;
  game->config.game_pix_height = game->config.window_pix_height / game->config.game_pix_scale_height;
  if (! game->config.game_pix_width) {
    if (! g_opt_test_dungeon) {
      ERR("game->config.game_pix_width is zero");
      return;
    }
  }
  if (! game->config.game_pix_height) {
    if (! g_opt_test_dungeon) {
      ERR("game->config.game_pix_height is zero");
      return;
    }
  }

  game->config.ui_pix_width  = game->config.window_pix_width;
  game->config.ui_pix_height = game->config.window_pix_height;

  if (! MAP_WIDTH) {
    ERR("MAP_WIDTH zero");
    return;
  }

  if (! MAP_HEIGHT) {
    ERR("MAP_HEIGHT zero");
    return;
  }

  if (! TILE_WIDTH) {
    ERR("TILE_WIDTH zero");
    return;
  }

  if (! TILE_HEIGHT) {
    ERR("TILE_HEIGHT zero");
    return;
  }

  float tiles_across = game->config.game_pix_width / TILE_WIDTH;
  float tiles_down   = game->config.game_pix_height / TILE_HEIGHT;

  if (g_opt_ascii) {
    if (wid_asciimap) {
      int tlx;
      int tly;
      int brx;
      int bry;
      wid_get_tl_x_tl_y_br_x_br_y(wid_asciimap, &tlx, &tly, &brx, &bry);
      TILES_VISIBLE_ACROSS = brx - tlx + 1;
      TILES_VISIBLE_DOWN   = bry - tly + 1;
    } else {
      TILES_VISIBLE_ACROSS = MAP_WIDTH;
      TILES_VISIBLE_DOWN   = MAP_HEIGHT;
    }
  } else {
    TILES_VISIBLE_ACROSS = (int) tiles_across;
    TILES_VISIBLE_DOWN   = (int) tiles_down;
  }

  game->config.tile_pix_width  = game->config.one_pixel_width * TILE_WIDTH;
  game->config.tile_pix_height = game->config.one_pixel_height * TILE_HEIGHT;

  game->config.video_w_h_ratio = (double) game->config.game_pix_width / (double) game->config.game_pix_height;

  if (! TILES_VISIBLE_ACROSS) {
    if (! g_opt_test_dungeon) {
      ERR("TILES_VISIBLE_ACROSS is zero");
      return;
    }
  }

  if (! TILES_VISIBLE_DOWN) {
    if (! g_opt_test_dungeon) {
      ERR("TILES_VISIBLE_DOWN is zero");
      return;
    }
  }

  if (! g_opt_test_dungeon) {
    game->config.tile_pixel_width  = game->config.game_pix_width / TILES_VISIBLE_ACROSS;
    game->config.tile_pixel_height = game->config.game_pix_height / TILES_VISIBLE_DOWN;
  }

  LOG("SDL: Window:");
  LOG("SDL: - config pixel size    : %dx%d", game->config.config_pix_width, game->config.config_pix_height);
  LOG("SDL: - window pixel size    : %dx%d", game->config.window_pix_width, game->config.window_pix_height);
  LOG("SDL: Game graphics zoom     : %f", game->config.game_pix_zoom);
  LOG("SDL: - game pixel size      : %dx%d", game->config.game_pix_width, game->config.game_pix_height);
  LOG("SDL: UI zoom                : %f", game->config.ui_pix_zoom);
  LOG("SDL: - UI pixel size        : %dx%d", game->config.ui_pix_width, game->config.ui_pix_height);

  if (g_opt_ascii) {
    TERM_WIDTH  = game->config.ui_ascii_term_width;
    TERM_HEIGHT = game->config.ui_ascii_term_height;
  } else {
    TERM_WIDTH  = game->config.ui_gfx_term_width;
    TERM_HEIGHT = game->config.ui_gfx_term_height;
  }

  LOG("SDL: Terminal");
  LOG("SDL: - ascii gl size        : %ux%u", game->config.ascii_gl_width, game->config.ascii_gl_height);
  LOG("SDL: - term size            : %dx%d", TERM_WIDTH, TERM_HEIGHT);

  if (! TERM_WIDTH) {
    ERR("TERM_WIDTH is zero");
    return;
  }
  if (! TERM_HEIGHT) {
    ERR("TERM_HEIGHT is zero");
    return;
  }

  if (TERM_WIDTH >= TERM_WIDTH_MAX) {
    LOG("SDL: - exceeded console max width: %d", TERM_WIDTH);
    TERM_WIDTH                  = TERM_WIDTH_MAX;
    game->config.ascii_gl_width = ceil(((float) game->config.ui_pix_height) / ((float) TERM_WIDTH));
  }

  if (TERM_HEIGHT >= TERM_HEIGHT_MAX) {
    LOG("SDL: - exceeded console max height: %d", TERM_HEIGHT);
    TERM_HEIGHT                  = TERM_HEIGHT_MAX;
    game->config.ascii_gl_height = ceil(((float) game->config.ui_pix_height) / ((float) TERM_HEIGHT));
  }

  if (g_opt_ascii) {
    font_ui = font_ascii;
  } else {
    font_ui = font_pixelart_large;
  }

  //
  // Account for rounding errors, so the tiles look smoother.
  //
  game->config.ascii_gl_width  = ceil(((float) game->config.ui_pix_width) / ((float) TERM_WIDTH));
  game->config.ascii_gl_height = ceil(((float) game->config.ui_pix_height) / ((float) TERM_HEIGHT));

  //
  // If we overflow the screen, try to cut a few rows and columns off
  //
  while (game->config.ascii_gl_width * TERM_WIDTH > game->config.ui_pix_width) {
    TERM_WIDTH--;
    LOG("SDL: - exceeded pixel width, try width: %d", TERM_WIDTH);
  }
  while (game->config.ascii_gl_height * TERM_HEIGHT > game->config.ui_pix_height) {
    TERM_HEIGHT--;
    LOG("SDL: - exceeded pixel height, try height: %d", TERM_HEIGHT);
  }

  LOG("SDL: Updated terminal");
  LOG("SDL: - term size            : %dx%d", TERM_WIDTH, TERM_HEIGHT);
  LOG("SDL: - width to height ratio: %f", game->config.video_w_h_ratio);
  LOG("SDL: Map");
  LOG("SDL: - map size             : %dx%d", MAP_WIDTH, MAP_HEIGHT);
}
