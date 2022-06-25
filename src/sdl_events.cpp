//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_font.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_ui.hpp"
#include "my_wid_console.hpp"
#include "stb_image_write.hpp"

int sdl_filter_events(void *userdata, SDL_Event *event)
{
  TRACE_NO_INDENT();

  switch (event->type) {
    // This is important!  Queue it if we want to quit. */
    case SDL_QUIT: return 1;

    // Mouse and keyboard events go to threads */
    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEWHEEL:
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    case SDL_CONTROLLERDEVICEADDED:
    case SDL_CONTROLLERBUTTONDOWN:
    case SDL_CONTROLLERBUTTONUP:
    case SDL_CONTROLLERAXISMOTION:
    case SDL_JOYAXISMOTION: // Joystick axis motion
    case SDL_JOYBALLMOTION: // Joystick trackball motion
    case SDL_JOYHATMOTION:  // Joystick hat position change
    case SDL_JOYBUTTONDOWN: // Joystick button pressed
    case SDL_JOYBUTTONUP:   // Joystick button released
      return 1;

    // Drop all other events
    default: return 0;
  }
}

void sdl_event(SDL_Event *event, bool &processed_mouse_motion_event)
{
  TRACE_NO_INDENT();
  SDL_Keysym *key;

  wid_mouse_two_clicks = false;

  static struct SDL_Keysym last_key_pressed;

  switch (event->type) {
    case SDL_KEYDOWN:
      {
        sdl.event_count++;
        key = &event->key.keysym;

        DBG2("SDL: Keyboard: Key pressed keycode 0x%08" PRIX32 " = %s %d", event->key.keysym.sym,
             SDL_GetKeyName(event->key.keysym.sym), key->mod);

        {
          //
          // SDL2 has no auto repeat.
          //
          if (! memcmp(&last_key_pressed, key, sizeof(*key))) {
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
          } else {
            //
            // Pressing a different key
            //
            sdl.key_repeat_count = 0;
          }
          last_key_pressed = *key;
        }

        wid_key_down(key, sdl.mouse_x, sdl.mouse_y);

        sdl.shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;

        break;
      }
    case SDL_KEYUP:
      {
        sdl.event_count++;
        if (g_grab_next_key) {
          DBG2("SDL: Keyboard: Grabbed 0x%08" PRIX32 " = %s / %s", event->key.keysym.sym,
               SDL_GetKeyName(event->key.keysym.sym), SDL_GetScancodeName(event->key.keysym.scancode));

          g_grab_next_key = false;
          sdl.grabbed_key = sdlk_normalize(event->key.keysym);
          if (sdl.on_sdl_key_grab) {
            (*sdl.on_sdl_key_grab)(sdl.grabbed_key);
          }
          return;
        }

        sdl.key_repeat_count    = 0;
        sdl.key_repeat_this_key = 0;
        memset(&last_key_pressed, 0, sizeof(*key));

        DBG2("SDL: Keyboard: Key released keycode 0x%08" PRIX32 " = %s", event->key.keysym.sym,
             SDL_GetKeyName(event->key.keysym.sym));

        key = &event->key.keysym;

        wid_key_up(key, sdl.mouse_x, sdl.mouse_y);

        sdl.shift_held = (key->mod & KMOD_SHIFT) ? 1 : 0;
        break;
      }
    case SDL_TEXTINPUT:
      {
        sdl.event_count++;
        sdl.event_count++;
        DBG2("SDL: Keyboard: Text input \"%s\" in window %d", event->text.text, event->text.windowID);
        break;
      }
    case SDL_MOUSEWHEEL:
      {
        sdl.event_count++;
        DBG2("SDL: Mouse: Wheel scrolled %d in x and %d in y in window %d", event->wheel.x, event->wheel.y,
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
        // Negative wheel x so side scrolls seem natural. Could just be a dumb macos thing to ifdef?
        //
#ifdef __APPLE__
        sdl.wheel_x = -sdl.wheel_x;
#endif

        sdl.wheel_x *= accel;
        sdl.wheel_y *= accel;

        wid_mouse_visible = 1;
        sdl.mouse_tick++;
        if (! processed_mouse_motion_event) {
          wid_mouse_motion(sdl.mouse_x, sdl.mouse_y, 0, 0, -sdl.wheel_x, sdl.wheel_y);
          processed_mouse_motion_event = true;
        }
        break;
      }
    case SDL_MOUSEMOTION:
      {
        sdl.event_count++;
        sdl.mouse_down = sdl_get_mouse();

        DBG2("SDL: Mouse: Moved to %d,%d (%d,%d) state %d", event->motion.x, event->motion.y, event->motion.xrel,
             event->motion.yrel, sdl.mouse_down);

        wid_mouse_visible = 1;
        sdl.mouse_tick++;
        if (! processed_mouse_motion_event) {
          wid_mouse_motion(sdl.mouse_x, sdl.mouse_y, event->motion.xrel, event->motion.yrel, 0, 0);
          processed_mouse_motion_event = true;
        }
        break;
      }
    case SDL_MOUSEBUTTONDOWN:
      {
        sdl.event_count++;
        sdl.mouse_down                = sdl_get_mouse();
        sdl.last_mouse_held_down_when = time_ms();
        sdl.held_mouse_x              = sdl.mouse_x;
        sdl.held_mouse_y              = sdl.mouse_y;

        DBG2("SDL: Mouse DOWN: button %d pressed at %d,%d state %X", event->button.button, event->button.x,
             event->button.y, sdl.mouse_down);

        auto now             = time_ms();
        wid_mouse_visible    = 1;
        wid_mouse_two_clicks = (now - sdl.mouse_down_when < UI_MOUSE_DOUBLE_CLICK);

        wid_mouse_down(event->button.button, sdl.mouse_x, sdl.mouse_y);
        sdl.mouse_down_when = now;
        break;
      }
    case SDL_MOUSEBUTTONUP:
      {
        sdl.event_count++;
        sdl.mouse_down                = sdl_get_mouse();
        sdl.last_mouse_held_down_when = 0;
        sdl.held_mouse_x              = 0;
        sdl.held_mouse_y              = 0;

        DBG2("SDL: Mouse UP: button %d released at %d,%d state %d", event->button.button, event->button.x,
             event->button.y, sdl.mouse_down);

        wid_mouse_up(event->button.button, sdl.mouse_x, sdl.mouse_y);
        break;
      }
    case SDL_JOYAXISMOTION:
      {
        sdl.event_count++;
        DBG2("SDL: Joystick %d: Axis %d moved by %d", event->jaxis.which, event->jaxis.axis, event->jaxis.value);

        int axis  = event->jaxis.axis;
        int value = event->jaxis.value;

        if (! sdl.joy_axes) {
          sdl.joy_axes = (int *) myzalloc(sizeof(int) * sdl.joy_naxes, "joy axes");
        }

        sdl.joy_axes[ axis ] = value;

        sdl.left_fire  = false;
        sdl.right_fire = false;

        if (sdl.joy_axes[ 2 ] > sdl.joy_deadzone) {
          DBG2("SDL: left fire");
          sdl.left_fire = true;
          set(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t) 1);
        } else {
          set(sdl.joy_buttons, SDL_JOY_BUTTON_LEFT_FIRE, (uint8_t) 0);
        }

        if (sdl.joy_axes[ 5 ] > sdl.joy_deadzone) {
          DBG2("SDL: right fire");
          sdl.right_fire = true;
          set(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t) 1);
        } else {
          set(sdl.joy_buttons, SDL_JOY_BUTTON_RIGHT_FIRE, (uint8_t) 0);
        }

        if (sdl.right_fire || sdl.left_fire) {
          sdl_get_mouse();
          wid_joy_button(sdl.mouse_x, sdl.mouse_y);
        }

        break;
      }
    case SDL_JOYBALLMOTION:
      {
        sdl.event_count++;
        DBG2("SDL: Joystick %d: Ball %d moved by %d,%d", event->jball.which, event->jball.ball, event->jball.xrel,
             event->jball.yrel);
        break;
      }
    case SDL_JOYHATMOTION:
      {
        sdl.event_count++;
        DBG2("SDL: Joystick %d: Hat %d moved to ", event->jhat.which, event->jhat.hat);

        switch (event->jhat.value) {
          case SDL_HAT_CENTERED: break;
          case SDL_HAT_UP:
            {
              DBG2("SDL: UP");
              sdl.joy2_up = true;
              break;
            }
          case SDL_HAT_RIGHTUP:
            {
              DBG2("SDL: RIGHTUP");
              sdl.joy2_right = true;
              sdl.joy2_up    = true;
              break;
            }
          case SDL_HAT_RIGHT:
            {
              DBG2("SDL: RIGHT");
              sdl.joy2_right = true;
              break;
            }
          case SDL_HAT_RIGHTDOWN:
            {
              DBG2("SDL: RIGHTDOWN");
              sdl.joy2_right = true;
              sdl.joy2_down  = true;
              break;
            }
          case SDL_HAT_DOWN:
            {
              DBG2("SDL: DOWN");
              sdl.joy2_down = true;
              break;
            }
          case SDL_HAT_LEFTDOWN:
            {
              DBG2("SDL: LEFTDOWN");
              sdl.joy2_left = true;
              sdl.joy2_down = true;
              break;
            }
          case SDL_HAT_LEFT:
            {
              DBG2("SDL: LEFT");
              sdl.joy2_left = true;
              break;
            }
          case SDL_HAT_LEFTUP:
            {
              sdl.joy2_left = true;
              sdl.joy2_up   = true;
              DBG2("SDL: LEFTUP");
              break;
            }
          default: DBG2("SDL: UNKNOWN"); break;
        }
        break;
      }
    case SDL_JOYBUTTONDOWN:
      {
        sdl.event_count++;
        DBG2("SDL: Joystick %d: Button %d pressed", event->jbutton.which, event->jbutton.button);
        set(sdl.joy_buttons, event->jbutton.button, (uint8_t) 1);
        sdl_get_mouse();
        wid_joy_button(sdl.mouse_x, sdl.mouse_y);
        break;
      }
    case SDL_JOYBUTTONUP:
      {
        sdl.event_count++;
        DBG2("SDL: Joystick %d: Button %d released", event->jbutton.which, event->jbutton.button);
        set(sdl.joy_buttons, event->jbutton.button, (uint8_t) 0);
        break;
      }
    case SDL_CLIPBOARDUPDATE:
      {
        DBG2("SDL: Clipboard updated");
        break;
      }
    case SDL_QUIT:
      {
#ifdef ENABLE_UI_ASCII_MOUSE
        SDL_ShowCursor(1);
#endif
        DIE("Quit requested");
        break;
      }
    case SDL_USEREVENT:
      {
        DBG2("SDL: User event %d", event->user.code);
        break;
      }
    default:
      {
        DBG2("SDL: Unknown event %d", event->type);
        break;
      }
  }
}

void sdl_key_repeat_events(void)
{
  TRACE_NO_INDENT();

  if (! game) {
    return;
  }

  if (! game->level) {
    return;
  }

  const uint8_t *state = SDL_GetKeyboardState(0);

  bool        up    = state[ sdlk_to_scancode(game->config.key_move_up) ];
  bool        down  = state[ sdlk_to_scancode(game->config.key_move_down) ];
  bool        left  = state[ sdlk_to_scancode(game->config.key_move_left) ];
  bool        right = state[ sdlk_to_scancode(game->config.key_move_right) ];
  bool        wait  = state[ sdlk_to_scancode(game->config.key_wait_or_collect) ];
  static bool old_up;
  static bool old_down;
  static bool old_left;
  static bool old_right;
  static bool old_wait;

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

  bool        movement = wait || up || down || left || right;
  static bool old_movement;
  static ts_t last_movement_keypress = 0;
  static int  repeat_count;

  if (! movement || ! last_movement_keypress) {
    last_movement_keypress = time_ms();
    repeat_count           = 0;

    if (old_movement) {
      game->request_player_up              = old_up;
      game->request_player_down            = old_down;
      game->request_player_left            = old_left;
      game->request_player_right           = old_right;
      game->request_player_wait_or_collect = old_wait;

      if (! game->request_player_move) {
        game->request_player_move = time_ms();
      }
    }
  } else {
    if (repeat_count > 0) {
      //
      // Fast repeat
      //
      if (time_have_x_hundredths_passed_since(SDL_KEY_REPEAT_HUNDREDTHS_NEXT, last_movement_keypress)) {
        last_movement_keypress               = time_ms();
        game->request_player_up              = up;
        game->request_player_down            = down;
        game->request_player_left            = left;
        game->request_player_right           = right;
        game->request_player_wait_or_collect = wait;

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
        last_movement_keypress               = time_ms();
        game->request_player_up              = up;
        game->request_player_down            = down;
        game->request_player_left            = left;
        game->request_player_right           = right;
        game->request_player_wait_or_collect = wait;

        if (! game->request_player_move) {
          game->request_player_move = time_ms();
        }
      }
    }
  }

  if (game->level) {
    game->level->handle_input_events();
  }

  old_up       = up;
  old_down     = down;
  old_left     = left;
  old_right    = right;
  old_wait     = wait;
  old_movement = movement;
}
