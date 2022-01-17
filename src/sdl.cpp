//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"
#include "my_wid_rightbar.hpp"
#include "stb_image_write.hpp"

uint8_t  sdl_shift_held;
uint8_t  sdl_init_video;
uint32_t mouse_down;
uint32_t mouse_down_when;

ts_t sdl_last_time_for_key;

int mouse_x;
int mouse_y;
int wheel_x;
int wheel_y;
int mouse_tick;

int sdl_key_repeat_count;

int sdl_left_fire;
int sdl_right_fire;

int sdl_joy1_right;
int sdl_joy1_left;
int sdl_joy1_down;
int sdl_joy1_up;

int sdl_joy2_right;
int sdl_joy2_left;
int sdl_joy2_down;
int sdl_joy2_up;

std::array< uint8_t, SDL_MAX_BUTTONS > sdl_joy_buttons;

static SDL_Joystick *joy;
static SDL_Haptic   *haptic;

int *sdl_joy_axes;
int  sdl_joy_deadzone = 8000;
int  joy_index;
int  joy_naxes;
int  joy_buttons;
int  joy_balls;

SDL_Window   *window;  // Our window handle
SDL_GLContext context; // Our opengl context handle

SDL_Scancode      sdl_grabbed_scancode;
on_sdl_key_grab_t on_sdl_key_grab;

void sdl_fini(void)
{
  LOG("SDL fini");
  TRACE_AND_INDENT();

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(0);
  SDL_ShowCursor(1);
#endif

  if (sdl_init_video) {
    CON("SDL video quit");
    sdl_init_video = 0;
    SDL_VideoQuit();
  }

  CON("SDL delete GL context");
  SDL_GL_DeleteContext(context);

  CON("SDL destroy window");
  SDL_DestroyWindow(window);

  CON("SDL quit");
  SDL_Quit();

  CON("SDL fini done");
}

static inline void sdl_list_video_size(void)
{
  TRACE_NO_INDENT();
  int i;

  for (i = 0; i < SDL_GetNumDisplayModes(0); ++i) {
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, i, &mode);
    LOG("+ SDL video            : %dx%d available, ratio %f", mode.w, mode.h, (float) mode.w / (float) mode.h);
  }
}

void sdl_joy_rumble(float strength, ts_t ms)
{
  TRACE_NO_INDENT();
  if (! haptic) {
    return;
  }

  SDL_HapticRumblePlay(haptic, strength, ms);
}

static void sdl_init_rumble(void)
{
  LOG("SDL: init rumble:");
  TRACE_AND_INDENT();

  if (! haptic) {
    haptic = SDL_HapticOpenFromJoystick(joy);
    if (! haptic) {
      LOG("- Couldn't initialize SDL rumble: %s", SDL_GetError());
      SDL_ClearError();
      return;
    }
  }

  if (! SDL_HapticRumbleSupported(haptic)) {
    LOG("- No SDL rumble support: %s", SDL_GetError());
    SDL_ClearError();
    return;
  }

  if (SDL_HapticRumbleInit(haptic) != 0) {
    LOG("- SDL rumble nit failed: %s", SDL_GetError());
    SDL_ClearError();
    return;
  }

  LOG("- Opened Haptic for joy index %d", joy_index);
}

static void sdl_init_joystick(void)
{
  LOG("SDL: init input:");
  TRACE_NO_INDENT();

  SDL_GameController *controller = nullptr;

  LOG("- Init game controleer");
  SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

  LOG("- Init haptic");
  SDL_InitSubSystem(SDL_INIT_HAPTIC);

  LOG("- Init joystick");
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);

  joy_index = 0;
  for (joy_index = 0; joy_index < SDL_NumJoysticks(); ++joy_index) {

    if (SDL_IsGameController(joy_index)) {
      controller = SDL_GameControllerOpen(joy_index);
      if (controller) {
        LOG("- Found gamecontroller");
        break;
      } else {
        WARN("Could not open gamecontroller %i: %s", joy_index, SDL_GetError());
        SDL_ClearError();
      }
    }
  }

  if (! controller) {
    LOG("- No found gamecontroller");
    return;
  }

  joy = SDL_JoystickOpen(joy_index);
  if (joy) {
    LOG("- Opened Joystick  : %d", joy_index);
    LOG("- Name             : %s", SDL_JoystickNameForIndex(0));
    LOG("- Number of Axes   : %d", SDL_JoystickNumAxes(joy));
    LOG("- Number of Buttons: %d", SDL_JoystickNumButtons(joy));
    LOG("- Number of Balls  : %d", SDL_JoystickNumBalls(joy));

    joy_naxes   = SDL_JoystickNumAxes(joy);
    joy_buttons = SDL_JoystickNumButtons(joy);
    joy_balls   = SDL_JoystickNumBalls(joy);
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

  LOG("SDL: SDL init, version: %u.%u", SDL_MAJOR_VERSION, SDL_MINOR_VERSION);
  TRACE_AND_INDENT();

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    SDL_MSG_BOX("SDL_Init failed %s", SDL_GetError());
    DIE("SDL_Init failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: SDL_VideoInit");
  if (SDL_VideoInit(0) != 0) {
    SDL_MSG_BOX("SDL_VideoInit failed %s", SDL_GetError());
    DIE("SDL_VideoInit failed %s", SDL_GetError());
    return false;
  }

  int x = 0;
  if (x) {
    sdl_init_joystick();
    sdl_init_rumble();
  }

  sdl_init_video = 1;

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

    LOG("SDL: SDL_GetCurrentDisplayMode");
    if (SDL_GetCurrentDisplayMode(0, &mode) < 0) {
      SDL_MSG_BOX("Couldn't set windowed display: %s", SDL_GetError());
      DIE("Couldn't set windowed display: %s", SDL_GetError());
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

#ifdef ENABLE_GENERATE_TTF
  return true;
#endif

  uint32_t video_unused_flags;

  LOG("SDL: Set SDL_WINDOW_OPENGL");
  video_unused_flags = SDL_WINDOW_OPENGL;

  if (game->config.gfx_borderless) {
    LOG("SDL: Set SDL_WINDOW_BORDERLESS");
    video_unused_flags |= SDL_WINDOW_BORDERLESS;
  }

  if (game->config.gfx_fullscreen) {
    LOG("SDL: Set SDL_WINDOW_FULLSCREEN");
    video_unused_flags |= SDL_WINDOW_FULLSCREEN;
  }

  if (game->config.gfx_fullscreen_desktop) {
    LOG("SDL: Set SDL_WINDOW_FULLSCREEN_DESKTOP");
    video_unused_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if (game->config.gfx_allow_highdpi) {
    //
    // For a lo pixel game this makes no sense as the frame
    // buffers are really large and slows things down.
    //
    LOG("SDL: Calling SDL_GetDisplayDPI");
    float dpi;
    if (SDL_GetDisplayDPI(0, 0, &dpi, 0) == 0) {
      video_unused_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
      LOG("SDL: SDL_WINDOW_ALLOW_HIGHDPI");
    } else {
      ERR("SDL: Cannot enable high DPI");
    }
  }

  LOG("SDL: SDL_CreateWindow");
  window = SDL_CreateWindow("zorbash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, video_width, video_height,
                            video_unused_flags);
  if (! window) {
    ERR("Couldn't set windowed display %ux%u: %s", video_width, video_height, SDL_GetError());

    SDL_MSG_BOX("Couldn't set windowed display %ux%u: %s", video_width, video_height, SDL_GetError());

    game->config.reset();
    game->save_config();
    return false;
  }

  if (video_unused_flags & SDL_WINDOW_ALLOW_HIGHDPI) {
    SDL_GL_GetDrawableSize(window, &game->config.window_pix_width, &game->config.window_pix_height);
  } else {
    SDL_GetWindowSize(window, &game->config.window_pix_width, &game->config.window_pix_height);
  }

  LOG("SDL: Call SDL_GL_CreateContext(%dx%d)", game->config.window_pix_width, game->config.window_pix_height);

  context = SDL_GL_CreateContext(window);
  if (! context) {
    SDL_ClearError();
    ERR("SDL_GL_CreateContext failed %s", SDL_GetError());
    SDL_MSG_BOX("SDL_GL_CreateContext failed %s", SDL_GetError());
    return false;
  }

  LOG("SDL: Call SDL_GL_CreateContext(%dx%d) done", game->config.window_pix_width, game->config.window_pix_height);

  if (SDL_GL_MakeCurrent(window, context) < 0) {
    SDL_ClearError();
    ERR("SDL_GL_MakeCurrent failed %s", SDL_GetError());
    SDL_MSG_BOX("SDL_GL_MakeCurrent failed %s", SDL_GetError());
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  SDL_GL_SwapWindow(window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  SDL_GL_SwapWindow(window);

  config_game_pix_zoom_update();

  LOG("SDL: Call SDL_SetWindowTitle");
  SDL_SetWindowTitle(window, "zorbash");

  LOG("SDL: GL Vendor   : %s", glGetString(GL_VENDOR));
  LOG("SDL: GL Renderer : %s", glGetString(GL_RENDERER));
  LOG("SDL: GL Version  : %s", glGetString(GL_VERSION));
  LOG("SDL: GL Exts     : %s", glGetString(GL_EXTENSIONS));

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

int sdl_filter_events(void *userdata, SDL_Event *event)
{
  TRACE_NO_INDENT();

  switch (event->type) {
    // This is important!  Queue it if we want to quit. */
    case SDL_QUIT : return 1;

    // Mouse and keyboard events go to threads */
    case SDL_MOUSEMOTION :
    case SDL_MOUSEBUTTONDOWN :
    case SDL_MOUSEBUTTONUP :
    case SDL_MOUSEWHEEL :
    case SDL_KEYDOWN :
    case SDL_KEYUP :
    case SDL_CONTROLLERDEVICEADDED :
    case SDL_CONTROLLERBUTTONDOWN :
    case SDL_CONTROLLERBUTTONUP :
    case SDL_CONTROLLERAXISMOTION :
    case SDL_JOYAXISMOTION : // Joystick axis motion
    case SDL_JOYBALLMOTION : // Joystick trackball motion
    case SDL_JOYHATMOTION :  // Joystick hat position change
    case SDL_JOYBUTTONDOWN : // Joystick button pressed
    case SDL_JOYBUTTONUP :   // Joystick button released
      return 1;

    // Drop all other events
    default : return 0;
  }
}

void sdl_event(SDL_Event *event)
{
  TRACE_NO_INDENT();
  SDL_Keysym *key;

  wid_mouse_two_clicks = false;

  static struct SDL_Keysym last_key_pressed;

  switch (event->type) {
    case SDL_KEYDOWN :
      {
        if (g_grab_next_key) {
          DBG("SDL: Keyboard: Grabbed 0x%08" PRIX32 " = %s / %s", event->key.keysym.sym,
              SDL_GetKeyName(event->key.keysym.sym), SDL_GetScancodeName(event->key.keysym.scancode));

          g_grab_next_key      = false;
          sdl_grabbed_scancode = event->key.keysym.scancode;
          if (on_sdl_key_grab) {
            (*on_sdl_key_grab)(sdl_grabbed_scancode);
          }
          return;
        }

        key = &event->key.keysym;

        DBG("SDL: Keyboard: Key pressed keycode 0x%08" PRIX32 " = %s %d", event->key.keysym.sym,
            SDL_GetKeyName(event->key.keysym.sym), key->mod);

        {
          //
          // SDL2 has no auto repeat.
          //
          if (! memcmp(&last_key_pressed, key, sizeof(*key))) {
            //
            // Pressing the same key
            //
            sdl_key_repeat_count++;
            if (sdl_key_repeat_count > 1) {
              //
              // Fast repeat
              //
              if (! time_have_x_hundredths_passed_since(5, sdl_last_time_for_key)) {
                return;
              }
            } else {
              //
              // First press
              //
              if (! time_have_x_hundredths_passed_since(5000, sdl_last_time_for_key)) {
                return;
              }
            }
            sdl_last_time_for_key = time_get_time_ms_cached();
          } else {
            //
            // Pressing a different key
            //
            sdl_key_repeat_count = 0;
          }
          last_key_pressed = *key;
        }

        wid_key_down(key, mouse_x, mouse_y);

        sdl_shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
        break;
      }
    case SDL_KEYUP :
      {
        sdl_key_repeat_count  = 0;
        sdl_last_time_for_key = 0;
        memset(&last_key_pressed, 0, sizeof(*key));

        DBG("SDL: Keyboard: Key released keycode 0x%08" PRIX32 " = %s", event->key.keysym.sym,
            SDL_GetKeyName(event->key.keysym.sym));

        key = &event->key.keysym;

        wid_key_up(key, mouse_x, mouse_y);

        sdl_shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
        break;
      }
    case SDL_TEXTINPUT :
      {
        DBG("SDL: Keyboard: Text input \"%s\" in window %d", event->text.text, event->text.windowID);
        break;
      }
    case SDL_MOUSEWHEEL :
      {
        DBG("SDL: Mouse: Wheel scrolled %d in x and %d in y in window %d", event->wheel.x, event->wheel.y,
            event->wheel.windowID);

        sdl_get_mouse();

        static double accel = 1.0;

        {
          static ts_t ts;

          if (time_have_x_tenths_passed_since(5, ts)) {
            accel = 1.0;
          } else {
            accel *= UI_MOUSE_WHEEL_SCALE;

            if (accel > UI_MOUSE_WHEEL_SCALE_MAX) {
              accel = UI_MOUSE_WHEEL_SCALE_MAX;
            }
          }

          ts = time_get_time_ms_cached();
        }

        wheel_x = event->wheel.x;
        wheel_y = event->wheel.y;

        wheel_x *= accel;
        wheel_y *= accel;

        //
        // Negative wheel x so side scrolls seem natural. Could just be
        // a dumb macos thing to ifdef?
        //
        wid_mouse_visible = 1;
        mouse_tick++;
        wid_mouse_motion(mouse_x, mouse_y, 0, 0, -wheel_x, wheel_y);
        break;
      }
    case SDL_MOUSEMOTION :
      {
        mouse_down = sdl_get_mouse();

        DBG2("SDL: Mouse: Moved to %d,%d (%d,%d) state %d", event->motion.x, event->motion.y, event->motion.xrel,
             event->motion.yrel, mouse_down);

        wid_mouse_visible = 1;
        mouse_tick++;
        wid_mouse_motion(mouse_x, mouse_y, event->motion.xrel, event->motion.yrel, 0, 0);
        break;
      }
    case SDL_MOUSEBUTTONDOWN :
      {
        mouse_down = sdl_get_mouse();

        DBG("SDL: Mouse DOWN: button %d pressed at %d,%d state %X", event->button.button, event->button.x,
            event->button.y, mouse_down);

        auto now             = time_get_time_ms_cached();
        wid_mouse_visible    = 1;
        wid_mouse_two_clicks = (now - mouse_down_when < UI_MOUSE_DOUBLE_CLICK);

        wid_mouse_down(event->button.button, mouse_x, mouse_y);
        mouse_down_when = now;
        break;
      }
    case SDL_MOUSEBUTTONUP :
      {
        mouse_down = sdl_get_mouse();

        DBG("SDL: Mouse UP: button %d released at %d,%d state %d", event->button.button, event->button.x,
            event->button.y, mouse_down);

        wid_mouse_up(event->button.button, mouse_x, mouse_y);
        break;
      }
    case SDL_JOYAXISMOTION :
      {
        DBG("SDL: Joystick %d: Axis %d moved by %d", event->jaxis.which, event->jaxis.axis, event->jaxis.value);

        int axis  = event->jaxis.axis;
        int value = event->jaxis.value;

        if (! sdl_joy_axes) {
          sdl_joy_axes = (int *) myzalloc(sizeof(int) * joy_naxes, "joy axes");
        }

        sdl_joy_axes[ axis ] = value;

        sdl_left_fire  = false;
        sdl_right_fire = false;

        if (sdl_joy_axes[ 2 ] > sdl_joy_deadzone) {
          DBG("SDL: left fire");
          sdl_left_fire = true;
          set(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t) 1);
        } else {
          set(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t) 0);
        }

        if (sdl_joy_axes[ 5 ] > sdl_joy_deadzone) {
          DBG("SDL: right fire");
          sdl_right_fire = true;
          set(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t) 1);
        } else {
          set(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t) 0);
        }

        if (sdl_right_fire || sdl_left_fire) {
          sdl_get_mouse();
          wid_joy_button(mouse_x, mouse_y);
        }

        break;
      }
    case SDL_JOYBALLMOTION :
      {
        DBG("SDL: Joystick %d: Ball %d moved by %d,%d", event->jball.which, event->jball.ball, event->jball.xrel,
            event->jball.yrel);
        break;
      }
    case SDL_JOYHATMOTION :
      {
        DBG("SDL: Joystick %d: Hat %d moved to ", event->jhat.which, event->jhat.hat);

        switch (event->jhat.value) {
          case SDL_HAT_CENTERED : break;
          case SDL_HAT_UP :
            {
              DBG("SDL: UP");
              sdl_joy2_up = true;
              break;
            }
          case SDL_HAT_RIGHTUP :
            {
              DBG("SDL: RIGHTUP");
              sdl_joy2_right = true;
              sdl_joy2_up    = true;
              break;
            }
          case SDL_HAT_RIGHT :
            {
              DBG("SDL: RIGHT");
              sdl_joy2_right = true;
              break;
            }
          case SDL_HAT_RIGHTDOWN :
            {
              DBG("SDL: RIGHTDOWN");
              sdl_joy2_right = true;
              sdl_joy2_down  = true;
              break;
            }
          case SDL_HAT_DOWN :
            {
              DBG("SDL: DOWN");
              sdl_joy2_down = true;
              break;
            }
          case SDL_HAT_LEFTDOWN :
            {
              DBG("SDL: LEFTDOWN");
              sdl_joy2_left = true;
              sdl_joy2_down = true;
              break;
            }
          case SDL_HAT_LEFT :
            {
              DBG("SDL: LEFT");
              sdl_joy2_left = true;
              break;
            }
          case SDL_HAT_LEFTUP :
            {
              sdl_joy2_left = true;
              sdl_joy2_up   = true;
              DBG("SDL: LEFTUP");
              break;
            }
          default : DBG("SDL: UNKNOWN"); break;
        }
        break;
      }
    case SDL_JOYBUTTONDOWN :
      {
        DBG("SDL: Joystick %d: Button %d pressed", event->jbutton.which, event->jbutton.button);
        set(sdl_joy_buttons, event->jbutton.button, (uint8_t) 1);
        sdl_get_mouse();
        wid_joy_button(mouse_x, mouse_y);
        break;
      }
    case SDL_JOYBUTTONUP :
      {
        DBG("SDL: Joystick %d: Button %d released", event->jbutton.which, event->jbutton.button);
        set(sdl_joy_buttons, event->jbutton.button, (uint8_t) 0);
        break;
      }
    case SDL_CLIPBOARDUPDATE :
      {
        DBG("SDL: Clipboard updated");
        break;
      }
    case SDL_QUIT :
      {
#ifdef ENABLE_UI_ASCII_MOUSE
        SDL_ShowCursor(1);
#endif
        DIE("Quit requested");
        break;
      }
    case SDL_USEREVENT :
      {
        DBG("SDL: User event %d", event->user.code);
        break;
      }
    default :
      {
        DBG("SDL: Unknown event %d", event->type);
        break;
      }
  }
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
    return (button);
  }

  x *= game->config.window_pix_width / game->config.config_pix_width;
  y *= game->config.window_pix_height / game->config.config_pix_height;

  mouse_x = x;
  mouse_y = y;

  return (button);
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

  SDL_WarpMouseInWindow(window, x, y);

  mouse_x = x;
  mouse_y = y;
}

void sdl_tick(void)
{
  TRACE_NO_INDENT();
  sdl_left_fire = false;
  sdl_left_fire = true;

  sdl_joy1_right = false;
  sdl_joy1_left  = false;
  sdl_joy1_down  = false;
  sdl_joy1_up    = false;

  sdl_joy2_right = false;
  sdl_joy2_left  = false;
  sdl_joy2_down  = false;
  sdl_joy2_up    = false;

  sdl_get_mouse();

  //
  // Right stick
  //
  if (sdl_joy_axes[ 3 ] > sdl_joy_deadzone) {
    DBG("SDL: right stick, right");
    sdl_joy1_right = true;

    incr(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT);
    wid_joy_button(mouse_x, mouse_y);
    decr(sdl_joy_buttons, SDL_JOY_BUTTON_RIGHT);
  }

  if (sdl_joy_axes[ 3 ] < -sdl_joy_deadzone) {
    DBG("SDL: right stick, left");
    sdl_joy1_left = true;

    incr(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT);
    wid_joy_button(mouse_x, mouse_y);
    decr(sdl_joy_buttons, SDL_JOY_BUTTON_LEFT);
  }

  if (sdl_joy_axes[ 4 ] > sdl_joy_deadzone) {
    DBG("SDL: right stick, down");
    sdl_joy1_down = true;

    incr(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN);
    wid_joy_button(mouse_x, mouse_y);
    decr(sdl_joy_buttons, SDL_JOY_BUTTON_DOWN);
  }

  if (sdl_joy_axes[ 4 ] < -sdl_joy_deadzone) {
    DBG("SDL: right stick, up");
    sdl_joy1_up = true;

    incr(sdl_joy_buttons, SDL_JOY_BUTTON_UP);
    wid_joy_button(mouse_x, mouse_y);
    decr(sdl_joy_buttons, SDL_JOY_BUTTON_UP);
  }

  //
  // Left stick
  //
  int mx = 0;
  int my = 0;

  if (sdl_joy_axes[ 0 ] > sdl_joy_deadzone) {
    DBG("SDL: left stick, right");
    sdl_joy2_right = true;
    mx             = 1;
  }

  if (sdl_joy_axes[ 0 ] < -sdl_joy_deadzone) {
    DBG("SDL: left stick, left");
    sdl_joy2_left = true;
    mx            = -1;
  }

  if (sdl_joy_axes[ 1 ] > sdl_joy_deadzone) {
    DBG("SDL: left stick, down");
    sdl_joy2_down = true;
    my            = 1;
  }

  if (sdl_joy_axes[ 1 ] < -sdl_joy_deadzone) {
    DBG("SDL: left stick, up");
    sdl_joy2_up = true;
    my          = -1;
  }

  static double accel = 1.0;
  static ts_t   ts;

  if (time_have_x_tenths_passed_since(5, ts)) {
    accel = 1.0;
  }

  if ((mx != 0) || (my != 0)) {
    ts = time_get_time_ms_cached();

    accel *= UI_SCROLL_JOY_SCALE;

    if (accel > UI_SCROLL_JOY_SCALE_MAX) {
      accel = UI_SCROLL_JOY_SCALE_MAX;
    }

    double x = mouse_x + ((double) mx * accel);
    double y = mouse_y + ((double) my * accel);

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
uint8_t config_fps_counter_set(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    game->config.fps_counter = true;
    CON("FPS counter enabled (default)");
  } else {
    game->config.fps_counter = strtol(s, 0, 10) ? 1 : 0;
    if (game->config.fps_counter) {
      CON("FPS counter enabled");
    } else {
      CON("FPS counter disabled");
    }
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
    CON("GFX inverted enabled");
  } else {
    game->config.gfx_inverted = false;
    CON("GFX inverted disabled");
  }
}

//
// User has entered a command, run it
//
uint8_t config_gfx_inverted_set(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 3 ];

  if (! s || (*s == '\0')) {
    game->config.gfx_inverted = true;
    CON("GFX inverted enabled (default)");
  } else {
    int val                   = strtol(s, 0, 10) ? 1 : 0;
    game->config.gfx_inverted = val;
    if (game->config.gfx_inverted) {
      CON("GFX inverted enabled");
    } else {
      CON("GFX inverted disabled");
    }
  }

  return true;
}

//
// User has entered a command, run it
//
void config_gfx_map_mini_toggle(void)
{
  TRACE_NO_INDENT();

  if (! game->config.gfx_map_mini) {
    game->config.gfx_map_mini = true;
    CON("GFX map enabled");
  } else {
    game->config.gfx_map_mini = false;
    CON("GFX map disabled");
  }
}

//
// User has entered a command, run it
//
uint8_t config_gfx_map_mini_set(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 3 ];

  if (! s || (*s == '\0')) {
    game->config.gfx_map_mini = true;
    CON("GFX map enabled (default)");
  } else {
    int val                  = strtol(s, 0, 10) ? 1 : 0;
    game->config.gfx_map_mini = val;
    if (game->config.gfx_map_mini) {
      CON("GFX map enabled");
    } else {
      CON("GFX map disabled");
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
uint8_t config_game_pix_zoom_set(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();

  char *s = tokens->args[ 3 ];

  if (! s || (*s == '\0')) {
    game->config.game_pix_zoom = GAME_DEFAULT_PIX_ZOOM;
    CON("GFX: gfx zoom enabled (default)");
  } else {
    int val                    = strtol(s, 0, 10);
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
uint8_t config_gfx_vsync_enable(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();
  if (game->config.gfx_vsync_locked) {
    return true;
  }

  char *s = tokens->args[ 2 ];

  if (! s || (*s == '\0')) {
    game->config.gfx_vsync_enable = true;
  } else {
    game->config.gfx_vsync_enable = strtol(s, 0, 10) ? 1 : 0;
  }

  if (game->config.gfx_vsync_enable) {
    CON("PLAYER: Vsync enabled");
    SDL_GL_SetSwapInterval(1);
  } else {
    CON("PLAYER: Vsync disabled");
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
uint8_t config_errored(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();
  g_errored = false;
  CON("PLAYER: Errored mode cleared");
  wid_hide(wid_console_window);
  return true;
}

void sdl_config_update_all(void)
{
  TRACE_NO_INDENT();
  CON("SDL: OpenGL leave 2D mode");
  config_game_pix_zoom_update();
  config_gfx_vsync_update();
  CON("SDL: OpenGL enter 2D mode");
  gl_init_2d_mode();

  if (game->level) {
    game->level->update_same_level_immediately();
  }
}

//
// User has entered a command, run it
//
uint8_t sdl_user_exit(tokens_t *tokens, void *context)
{
  TRACE_NO_INDENT();
  sdl_exit();

  return true;
}

void sdl_flush_display(void)
{
  TRACE_NO_INDENT();
  if (g_opt_no_slow_log_flush) {
    return;
  }

  glEnable(GL_TEXTURE_2D);
  gl_enter_2d_mode();
  wid_display_all();
  if (game->config.gfx_inverted) {
    glLogicOp(GL_COPY_INVERTED);
    glEnable(GL_COLOR_LOGIC_OP);
  }
  blit_fbo_ui_pix(FBO_WID);
  if (game->config.gfx_inverted) {
    glLogicOp(GL_COPY);
    glDisable(GL_COLOR_LOGIC_OP);
  }
  SDL_GL_SwapWindow(window);
  GL_ERROR_CHECK();
}

void config_game_pix_zoom_update(void)
{
  TRACE_NO_INDENT();
  game->config.tile_width  = TILE_WIDTH_LORES;
  game->config.tile_height = TILE_HEIGHT_LORES;

  game->config.one_pixel_width  = 1;
  game->config.one_pixel_height = 1;

  if (! game->config.game_pix_zoom) {
    ERR("Game->config.game_pix_zoom is zero");
    game->config.game_pix_zoom = GAME_DEFAULT_PIX_ZOOM;
    return;
  }

  if (! game->config.ui_pix_zoom) {
    ERR("Game->config.ui_pix_zoom is zero");
    game->config.ui_pix_zoom = GAME_DEFAULT_UI_ZOOM;
    return;
  }

  game->config.game_pix_scale_width  = game->config.game_pix_zoom;
  game->config.game_pix_scale_height = game->config.game_pix_zoom;

  if (! game->config.game_pix_scale_width) {
    ERR("Game->config.game_pix_scale_width is zero");
    return;
  }

  game->config.ui_pix_scale_width  = game->config.ui_pix_zoom;
  game->config.ui_pix_scale_height = game->config.ui_pix_zoom;
  if (! game->config.ui_pix_scale_width) {
    ERR("Game->config.ui_pix_scale_width is zero");
    return;
  }

  game->config.game_pix_width  = game->config.window_pix_width / game->config.game_pix_scale_width;
  game->config.game_pix_height = game->config.window_pix_height / game->config.game_pix_scale_height;

  game->config.ui_pix_width  = game->config.window_pix_width / game->config.ui_pix_scale_width;
  game->config.ui_pix_height = game->config.window_pix_height / game->config.ui_pix_scale_height;

  float tiles_across = game->config.game_pix_width / TILE_WIDTH;
  float tiles_down   = game->config.game_pix_height / TILE_HEIGHT;

  TILES_ACROSS = (int) tiles_across;
  TILES_DOWN   = (int) tiles_down;

  game->config.tile_pix_width  = game->config.one_pixel_width * TILE_WIDTH;
  game->config.tile_pix_height = game->config.one_pixel_height * TILE_HEIGHT;

  game->config.video_w_h_ratio = (double) game->config.game_pix_width / (double) game->config.game_pix_height;

  game->config.tile_pixel_width  = game->config.game_pix_width / TILES_ACROSS;
  game->config.tile_pixel_height = game->config.game_pix_height / TILES_DOWN;

  CON("SDL: Window:");
  CON("SDL: - config pixel size    : %dx%d", game->config.config_pix_width, game->config.config_pix_height);
  CON("SDL: - window pixel size    : %dx%d", game->config.window_pix_width, game->config.window_pix_height);
  CON("SDL: Game graphics zoom     : %f", game->config.game_pix_zoom);
  CON("SDL: - game pixel size      : %dx%d", game->config.game_pix_width, game->config.game_pix_height);
  CON("SDL: UI zoom                : %f", game->config.ui_pix_zoom);
  CON("SDL: - UI pixel size        : %dx%d", game->config.ui_pix_width, game->config.ui_pix_height);

  TERM_WIDTH                   = TERM_WIDTH_DEF;
  TERM_HEIGHT                  = TERM_HEIGHT_DEF;
  game->config.ascii_gl_width  = UI_FONT_LARGE_WIDTH;
  game->config.ascii_gl_height = UI_FONT_LARGE_HEIGHT;

  TERM_WIDTH  = game->config.ui_pix_width / game->config.ascii_gl_width;
  TERM_HEIGHT = game->config.ui_pix_height / game->config.ascii_gl_height;

  if (TERM_WIDTH >= TERM_WIDTH_MAX) {
    LOG("SDL: Exceeded console hit max width  : %d", TERM_WIDTH);
    TERM_WIDTH                  = TERM_WIDTH_MAX;
    game->config.ascii_gl_width = (float) game->config.ui_pix_width / (float) TERM_WIDTH;
  }

  if (TERM_HEIGHT >= TERM_HEIGHT_MAX) {
    LOG("SDL: Exceeded console hit max height : %d", TERM_HEIGHT);
    TERM_HEIGHT                  = TERM_HEIGHT_MAX;
    game->config.ascii_gl_height = (float) game->config.ui_pix_height / (float) TERM_HEIGHT;
  }

  CON("SDL: - ascii gl size        : %ux%u", game->config.ascii_gl_width, game->config.ascii_gl_height);
  CON("SDL: - ascii size           : %dx%d", TERM_WIDTH, TERM_HEIGHT);
  CON("SDL: - width to height ratio: %f", game->config.video_w_h_ratio);
}
