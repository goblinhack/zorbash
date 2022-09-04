//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_player.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"
#include "stb_image_write.hpp"

//
// Main loop
//
void sdl_loop(void)
{
  TRACE_NO_INDENT();
  LOG("SDL: main loop");

  //
  // Keep this lowish to avoid too much lag when processing mouse motion events, that redraw the cursor path.
  //
  // 2 - seems too slow as it adds a noticeable lag when you do a wheel mouse event after a lot of mouse moves.
  // 3 - still some lag
  // 4 - seems ok
  // 10 - too much lag now due to cursor redraws
  //
  SDL_Event events[ 4 ];
  int       found;
  int       i;
  int       frames = 0;

  sdl_mouse_center();
  SDL_SetEventFilter(sdl_filter_events, 0);

  glEnable(GL_TEXTURE_2D);

  //
  // Wait for events
  //
  int ui_ts_fast_last      = time_ms();
  int ui_ts_slow_last      = ui_ts_fast_last;
  int ui_ts_very_slow_last = ui_ts_fast_last;

  g_main_loop_running = true;

  game->config.gfx_vsync_locked = SDL_GL_GetSwapInterval();

  if (! game->config.gfx_vsync_locked) {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    GL_ERROR_CHECK();

    if (game->config.gfx_vsync_enable) {
      SDL_GL_SetSwapInterval(1);
    } else {
      SDL_GL_SetSwapInterval(0);
    }
    GL_ERROR_CHECK();
  }

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  GL_ERROR_CHECK();

  gl_enter_2d_mode();

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(0);
#endif

  //
  // Causes a 0.3 sec delay first time it seems to run
  //
  SDL_PumpEvents();

  for (; /*ever*/;) {
    // LOG("SDL: tick");

    frames++;
    game->frame_count++;

    //
    // Reset joystick handling before we poll and update.
    //
    if (unlikely(sdl.joy_axes != nullptr)) {
      sdl_tick();
    }

    static bool old_g_errored;
    if (unlikely(g_errored)) {
      if (g_errored != old_g_errored) {
        CON("%%fg=red$An error occurred. Check the logs above.%%fg=reset$");
        CON("To dismiss this console, press TAB.");
        CON("To continue playing at your own risk, try 'clear errored'");
        if (wid_console_window && ! (wid_console_window->visible)) {
          wid_visible(wid_console_window);
          wid_raise(wid_console_window);
          wid_lower(wid_topcon_window);
        }
      }
    }
    old_g_errored = g_errored;

    {
      gl_leave_2d_mode();
      gl_enter_2d_mode(game->config.game_pix_width, game->config.game_pix_height);

      glcolor(WHITE);
      game->display();
      blit_fbo_unbind();

      gl_leave_2d_mode();
      gl_enter_2d_mode(game->config.window_pix_width, game->config.window_pix_height);
    }

    //
    // Less frequent updates
    //
    int  ts_now           = time_ms();
    bool update_very_slow = (ts_now - ui_ts_very_slow_last >= UI_UPDATE_VERY_SLOW_MS);
    bool update_slow      = (ts_now - ui_ts_slow_last >= UI_UPDATE_SLOW_MS);
    bool update_fast      = (ts_now - ui_ts_fast_last >= UI_UPDATE_FAST_MS);

    //
    // In ascii mode update the screen more slowly to save CPU
    //
    if (unlikely(update_very_slow)) {
      ui_ts_very_slow_last = ts_now;

      //
      // This tick is for either
      // a) ascii mode
      // b) when in pixeal art mode and between levels and waiting for level fade in
      //
      if (likely(! g_errored)) {
        if (likely(game->level != nullptr)) {
          game->level->tick();
        }
      }

      wid_display_all();
    }

    //
    // Less frequent updates
    //
    if (unlikely(update_slow)) {
      ui_ts_slow_last = ts_now;

      //
      // Update status and rightbars
      //
      if (game) {
        //
        // Start the game if needed.
        //
        if (game->start_requested) {
          game->start_requested = false;
          game->start();
        }
      }

      //
      // Update FPS counter. Used for damping AI even if not shown.
      //
      game->fps_value = (1000 / UI_UPDATE_SLOW_MS) * frames;
      frames          = 0;
    }

    //
    // Do processing of some things, like reading the keyboard or doing
    // stuff with widgets only occasionally if we do not need to.
    //
    if (unlikely(update_fast)) {
      ui_ts_fast_last = ts_now;

      //
      // Clean up dead widgets.
      //
      wid_gc_all();

      //
      // Read events
      //
      SDL_PumpEvents();

      sdl.wheel_x = 0;
      sdl.wheel_y = 0;

      found = SDL_PeepEvents(events, ARRAY_SIZE(events), SDL_GETEVENT, SDL_QUIT, SDL_LASTEVENT);

      //
      // Only process one mouse motion event; and when we do we only look at the latest
      // mouse position, to avoid perception of lag. Mouse motion events can be expensive
      // as we redraw the cursor path.
      //
      bool processed_mouse_motion_event = false;
      for (i = 0; i < found; ++i) {
        sdl_event(&events[ i ], processed_mouse_motion_event);
      }

      //
      // Handle key auto repeat
      //
      sdl_key_repeat_events();

      //
      // Mouse held?
      //
      if (unlikely(! found)) {
        auto mouse_down = sdl_get_mouse();
        if (mouse_down) {
          if (sdl.last_mouse_held_down_when) {
            if (time_have_x_hundredths_passed_since(10, sdl.last_mouse_held_down_when)) {
              if (sdl.held_mouse_x && sdl.held_mouse_y) {
                DBG2("SDL: Mouse DOWN: held: Button %d now at %d,%d initially at %d,%d", mouse_down, sdl.mouse_x,
                     sdl.mouse_y, sdl.held_mouse_x, sdl.held_mouse_y);
                wid_mouse_held(sdl.mouse_down, sdl.held_mouse_x, sdl.held_mouse_y);
                sdl.held_mouse_x = 0;
                sdl.held_mouse_y = 0;
              } else {
                DBG2("SDL: Mouse DOWN: held: Button %d now at %d,%d", sdl.mouse_down, sdl.mouse_x, sdl.mouse_y);
                wid_mouse_held(sdl.mouse_down, sdl.mouse_x, sdl.mouse_y);
              }
            }
          }
        }
      }

      //
      // Screenshot?
      //
      if (unlikely(! g_do_screenshot)) {
        if (unlikely(! g_main_loop_running)) {
          LOG("Exit main loop");
          break;
        }
      }

      //
      // If the user has moved the mouse, tick to allow the cursor to move.
      // Or if a tick has started, tick quickly.
      //
      if (likely(! g_errored)) {
        if (likely(game->level != nullptr)) {
          if (found || game->tick_begin_ms) {
            game->level->tick();
          }
        }
      }

      //
      // If the user has moved the mouse or we're in the intro, update the widgets.
      //
      if (processed_mouse_motion_event || ! game->level) {
        wid_display_all();
      }
    }

    sdl_display();

    //
    // Config change?
    //
    if (unlikely(g_need_restart)) {
      break;
    }

#if 0
    if (unlikely(g_saved_snapshot)) {
      g_saved_snapshot = false;
      game->load_snapshot();
      game->tick_begin("Resume after snapshot");
    }
#endif
  }

  LOG("Exited main loop");

  gl_leave_2d_mode();

#ifdef ENABLE_UI_ASCII_MOUSE
  SDL_ShowCursor(1);
#endif
}
