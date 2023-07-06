//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"

static struct SDL_Keysym last_key_pressed;

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

static void __attribute__((noinline)) sdl_event_keydown_repeat(SDL_Keysym *key, SDL_Event *event)
{
  //
  // Pressing the same key
  //
  if (sdl.key_repeat_count > 0) {
    //
    // Fast repeat
    //
    if (! time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_NEXT, sdl.key_repeat_this_key)) {
      return;
    }
  } else {
    //
    // First press
    //
    if (! time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_FIRST, sdl.key_repeat_this_key)) {
      return;
    }
    sdl.key_repeat_count++;
  }

  sdl.key_repeat_this_key = time_ms();
}

static bool __attribute__((noinline)) sdl_event_keydown_same_key(SDL_Keysym *key)
{
  //
  // SDL2 has no auto repeat.
  //
  // Do not use memcmp; SDL_Keysym has an unused field and this will trigger valgrind.
  //
  if (key->scancode != last_key_pressed.scancode)
    return false;

  if (key->sym != last_key_pressed.sym)
    return false;

  if (key->mod != last_key_pressed.mod)
    return false;

  return true;
}

static void __attribute__((noinline)) sdl_event_keydown_handler(SDL_Keysym *key, SDL_Event *event)
{
  last_key_pressed.scancode = key->scancode;
  last_key_pressed.sym      = key->sym;
  last_key_pressed.mod      = key->mod;

  pcg_random_allowed++;
  wid_key_down(key, sdl.mouse_x, sdl.mouse_y);
  pcg_random_allowed--;

  sdl.shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
}

static void __attribute__((noinline)) sdl_event_keydown(SDL_Keysym *key, SDL_Event *event)
{
  sdl.event_count++;

  CON("SDL: Keyboard: Key pressed keycode 0x%08" PRIX32 " = %s %d", event->key.keysym.sym,
      to_string(event->key.keysym).c_str(), key->mod);

  //
  // SDL2 has no auto repeat.
  //
  if (sdl_event_keydown_same_key(key)) {
    sdl_event_keydown_repeat(key, event);
  } else {
    //
    // Pressing a different key
    //
    sdl.key_repeat_count = 0;
  }

  sdl_event_keydown_handler(key, event);
}

static void __attribute__((noinline)) sdl_event_keyup(SDL_Keysym *key, SDL_Event *event)
{
  sdl.event_count++;
  if (g_grab_next_key) {
    CON("SDL: Keyboard: Grabbed 0x%08" PRIX32 " = %s / %s", event->key.keysym.sym,
        to_string(event->key.keysym).c_str(), SDL_GetScancodeName(event->key.keysym.scancode));

    g_grab_next_key = false;
    sdl.grabbed_key = sdlk_normalize(event->key.keysym);
    if (sdl.on_sdl_key_grab) {
      (*sdl.on_sdl_key_grab)(sdl.grabbed_key);
    }
    return;
  }

  sdl.key_repeat_count    = 0;
  sdl.key_repeat_this_key = 0;

  memset(&last_key_pressed, 0, sizeof(last_key_pressed));

  CON("SDL: Keyboard: Key released keycode 0x%08" PRIX32 " = %s", event->key.keysym.sym,
      to_string(event->key.keysym).c_str());

  key = &event->key.keysym;

  pcg_random_allowed++;
  wid_key_up(key, sdl.mouse_x, sdl.mouse_y);
  pcg_random_allowed--;

  sdl.shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
}

static void __attribute__((noinline))
sdl_event_mousemotion(SDL_Keysym *key, SDL_Event *event, bool &processed_mouse_motion_event)
{
  sdl.event_count++;
  sdl.mouse_down = sdl_get_mouse();
  int        mx;
  int        my;
  static int last_mx;
  static int last_my;

  //
  // Catch up with the latest mouse position; and dampen identical events.
  //
  SDL_GetMouseState(&mx, &my);
  if ((mx == last_mx) && (my == last_my)) {
    return;
  }

  last_mx = mx;
  last_my = my;

  DBG("SDL: Mouse: Moved to %d,%d (rel %d,%d) state %d (actually at %d,%d)", event->motion.x, event->motion.y,
      event->motion.xrel, event->motion.yrel, sdl.mouse_down, mx, my);

  wid_mouse_visible = 1;
  sdl.mouse_tick++;
  if (! processed_mouse_motion_event) {
    pcg_random_allowed++;
    wid_mouse_motion(mx, my, event->motion.xrel, event->motion.yrel, 0, 0);
    pcg_random_allowed--;
    processed_mouse_motion_event = true;
  }
}

static void __attribute__((noinline)) sdl_event_mousedown(SDL_Keysym *key, SDL_Event *event)
{
  sdl.event_count++;
  sdl.mouse_down                = sdl_get_mouse();
  sdl.last_mouse_held_down_when = time_ms();
  sdl.held_mouse_x              = sdl.mouse_x;
  sdl.held_mouse_y              = sdl.mouse_y;

  DBG("SDL: Mouse DOWN: button %d pressed at %d,%d state %X", event->button.button, event->button.x, event->button.y,
      sdl.mouse_down);

  auto now             = time_ms();
  wid_mouse_visible    = 1;
  wid_mouse_two_clicks = (now - sdl.mouse_down_when < UI_MOUSE_DOUBLE_CLICK);

  pcg_random_allowed++;
  wid_mouse_down(event->button.button, sdl.mouse_x, sdl.mouse_y);
  pcg_random_allowed--;
  sdl.mouse_down_when = now;
}

static void __attribute__((noinline)) sdl_event_mouseup(SDL_Keysym *key, SDL_Event *event)
{
  sdl.event_count++;
  sdl.mouse_down                = sdl_get_mouse();
  sdl.last_mouse_held_down_when = 0;
  sdl.held_mouse_x              = 0;
  sdl.held_mouse_y              = 0;

  DBG("SDL: Mouse UP: button %d released at %d,%d state %d", event->button.button, event->button.x, event->button.y,
      sdl.mouse_down);

  pcg_random_allowed++;
  wid_mouse_up(event->button.button, sdl.mouse_x, sdl.mouse_y);
  pcg_random_allowed--;
}

void sdl_event(SDL_Event *event, bool &processed_mouse_motion_event)
{
  TRACE_NO_INDENT();
  SDL_Keysym *key = &event->key.keysym;

  wid_mouse_two_clicks = false;

  switch (event->type) {
    case SDL_KEYDOWN : sdl_event_keydown(key, event); break;
    case SDL_KEYUP : sdl_event_keyup(key, event); break;
    case SDL_MOUSEMOTION : sdl_event_mousemotion(key, event, processed_mouse_motion_event); break;
    case SDL_MOUSEBUTTONDOWN : sdl_event_mousedown(key, event); break;
    case SDL_MOUSEBUTTONUP : sdl_event_mouseup(key, event); break;
    case SDL_TEXTINPUT :
      {
        sdl.event_count++;
        CON("SDL: Keyboard: Text input \"%s\" in window %d", event->text.text, event->text.windowID);
        break;
      }
    case SDL_MOUSEWHEEL :
      {
        sdl.event_count++;
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

          ts = time_ms();
        }

        sdl.wheel_x = event->wheel.x;
        sdl.wheel_y = event->wheel.y;

        //
        // Handle "natural" scrolling direction.
        //
        if (! game->config.mouse_wheel_lr_negated) {
          sdl.wheel_x = -sdl.wheel_x;
        }

        if (game->config.mouse_wheel_ud_negated) {
          sdl.wheel_y = -sdl.wheel_y;
        }

        sdl.wheel_x *= accel;
        sdl.wheel_y *= accel;

        wid_mouse_visible = 1;
        sdl.mouse_tick++;
        if (! processed_mouse_motion_event) {
          pcg_random_allowed++;
          wid_mouse_motion(sdl.mouse_x, sdl.mouse_y, 0, 0, -sdl.wheel_x, sdl.wheel_y);
          pcg_random_allowed--;
          processed_mouse_motion_event = true;
        }
        break;
      }
    case SDL_JOYAXISMOTION :
      {
        sdl.event_count++;
        DBG("SDL: Joystick %d: Axis %d moved by %d", event->jaxis.which, event->jaxis.axis, event->jaxis.value);

        int axis  = event->jaxis.axis;
        int value = event->jaxis.value;

        if (! sdl.joy_axes) {
          sdl.joy_axes = (int *) myzalloc(sizeof(int) * sdl.joy_naxes, "joy axes");
        }

        sdl.joy_axes[ axis ] = value;

        sdl.left_fire  = false;
        sdl.right_fire = false;

        if (sdl.joy_axes[ 2 ] > sdl.joy_deadzone) {
          DBG("SDL: left fire");
          sdl.left_fire = true;
          set(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t) 1);
        } else {
          set(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t) 0);
        }

        if (sdl.joy_axes[ 5 ] > sdl.joy_deadzone) {
          DBG("SDL: right fire");
          sdl.right_fire = true;
          set(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t) 1);
        } else {
          set(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t) 0);
        }

        if (sdl.right_fire || sdl.left_fire) {
          sdl_get_mouse();
          pcg_random_allowed++;
          wid_joy_button(sdl.mouse_x, sdl.mouse_y);
          pcg_random_allowed--;
        }

        break;
      }
    case SDL_JOYBALLMOTION :
      {
        sdl.event_count++;
        DBG("SDL: Joystick %d: Ball %d moved by %d,%d", event->jball.which, event->jball.ball, event->jball.xrel,
            event->jball.yrel);
        break;
      }
    case SDL_JOYHATMOTION :
      {
        sdl.event_count++;
        DBG("SDL: Joystick %d: Hat %d moved to ", event->jhat.which, event->jhat.hat);

        switch (event->jhat.value) {
          case SDL_HAT_CENTERED : break;
          case SDL_HAT_UP :
            {
              DBG("SDL: UP");
              sdl.joy2_up = true;
              break;
            }
          case SDL_HAT_RIGHTUP :
            {
              DBG("SDL: RIGHTUP");
              sdl.joy2_right = true;
              sdl.joy2_up    = true;
              break;
            }
          case SDL_HAT_RIGHT :
            {
              DBG("SDL: RIGHT");
              sdl.joy2_right = true;
              break;
            }
          case SDL_HAT_RIGHTDOWN :
            {
              DBG("SDL: RIGHTDOWN");
              sdl.joy2_right = true;
              sdl.joy2_down  = true;
              break;
            }
          case SDL_HAT_DOWN :
            {
              DBG("SDL: DOWN");
              sdl.joy2_down = true;
              break;
            }
          case SDL_HAT_LEFTDOWN :
            {
              DBG("SDL: LEFTDOWN");
              sdl.joy2_left = true;
              sdl.joy2_down = true;
              break;
            }
          case SDL_HAT_LEFT :
            {
              DBG("SDL: LEFT");
              sdl.joy2_left = true;
              break;
            }
          case SDL_HAT_LEFTUP :
            {
              sdl.joy2_left = true;
              sdl.joy2_up   = true;
              DBG("SDL: LEFTUP");
              break;
            }
          default : DBG("SDL: UNKNOWN"); break;
        }
        break;
      }
    case SDL_JOYBUTTONDOWN :
      {
        sdl.event_count++;
        DBG("SDL: Joystick %d: Button %d pressed", event->jbutton.which, event->jbutton.button);
        set(sdl.joy_buttons, event->jbutton.button, (uint8_t) 1);
        sdl_get_mouse();
        pcg_random_allowed++;
        wid_joy_button(sdl.mouse_x, sdl.mouse_y);
        pcg_random_allowed--;
        break;
      }
    case SDL_JOYBUTTONUP :
      {
        sdl.event_count++;
        DBG("SDL: Joystick %d: Button %d released", event->jbutton.which, event->jbutton.button);
        set(sdl.joy_buttons, event->jbutton.button, (uint8_t) 0);
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

static void sdl_key_repeat_events_(void)
{
  TRACE_NO_INDENT();

  if (! game) {
    return;
  }

  if (! game->level) {
    return;
  }

  const uint8_t *state = SDL_GetKeyboardState(nullptr);

  bool up    = state[ sdlk_to_scancode(game->config.key_move_up) ];
  bool down  = state[ sdlk_to_scancode(game->config.key_move_down) ];
  bool left  = state[ sdlk_to_scancode(game->config.key_move_left) ];
  bool right = state[ sdlk_to_scancode(game->config.key_move_right) ];
  bool wait  = state[ sdlk_to_scancode(game->config.key_wait_or_collect) ];

  //
  // Keypad stuff is hardcoded.
  //
  if (state[ SDL_SCANCODE_KP_PERIOD ]) {
    wait = true;
  }
  if (state[ SDL_SCANCODE_KP_1 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    left = true;
    down = true;
  }
  if (state[ SDL_SCANCODE_KP_2 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    down = true;
  }
  if (state[ SDL_SCANCODE_KP_3 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    right = true;
    down  = true;
  }
  if (state[ SDL_SCANCODE_KP_4 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    left = true;
  }
  if (state[ SDL_SCANCODE_KP_6 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    right = true;
  }
  if (state[ SDL_SCANCODE_KP_7 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    left = true;
    up   = true;
  }
  if (state[ SDL_SCANCODE_KP_8 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    up = true;
  }
  if (state[ SDL_SCANCODE_KP_9 ]) {
    // 7 8 9
    // 4   6
    // 1 2 3
    right = true;
    up    = true;
  }

  bool        movement               = wait || up || down || left || right;
  static ts_t last_movement_keypress = 0;
  static int  repeat_count;

  if (! movement) {
    repeat_count = 0;
  } else {
    if (repeat_count > 0) {
      //
      // Fast repeat
      //
      if (time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_NEXT, last_movement_keypress)) {
        last_movement_keypress                  = time_ms();
        game->request_player_move_up            = up;
        game->request_player_move_down          = down;
        game->request_player_move_left          = left;
        game->request_player_move_right         = right;
        game->request_player_to_wait_or_collect = wait;

        if (! game->request_player_move) {
          game->request_player_move = time_ms();
        }
      }
    } else {
      //
      // First press
      //
      if (time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_FIRST, last_movement_keypress)) {
        repeat_count++;
        last_movement_keypress                  = time_ms();
        game->request_player_move_up            = up;
        game->request_player_move_down          = down;
        game->request_player_move_left          = left;
        game->request_player_move_right         = right;
        game->request_player_to_wait_or_collect = wait;

        if (! game->request_player_move) {
          game->request_player_move = time_ms();
        }
      }
    }
  }

  if (game->level) {
    game->level->handle_input_events();
  }
}

void sdl_key_repeat_events(void)
{
  pcg_random_allowed++;
  sdl_key_repeat_events_();
  pcg_random_allowed--;
}
