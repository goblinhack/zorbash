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
#include "my_wid_topcon.hpp"
#include "stb_image_write.hpp"

//
// Main loop
//
void sdl_loop(void)
{
  TRACE_NO_INDENT();
  LOG("SDL: main loop");

  SDL_Event events[ 10 ];
  int       found;
  int       i;
  int       frames = 0;

  sdl_mouse_center();
  SDL_SetEventFilter(sdl_filter_events, 0);

  glEnable(GL_TEXTURE_2D);

  //
  // Wait for events
  //
  int ui_ts_fast_last = time_get_time_ms();
  int ui_ts_slow_last = ui_ts_fast_last;

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
    if (unlikely(sdl_joy_axes != nullptr)) {
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

    pcg_random_allowed = false;
    {
      gl_leave_2d_mode();
      gl_enter_2d_mode(game->config.game_pix_width, game->config.game_pix_height);

      glcolor(WHITE);
      game->display();
      blit_fbo_unbind();

      gl_leave_2d_mode();
      gl_enter_2d_mode(game->config.window_pix_width, game->config.window_pix_height);
    }
    pcg_random_allowed = true;

    //
    // Less frequent updates
    //
    int  ts_now      = time_get_time_ms();
    bool update_slow = (ts_now - ui_ts_slow_last >= UI_UPDATE_SLOW_MS);
    bool update_fast = (ts_now - ui_ts_fast_last >= UI_UPDATE_FAST_MS);

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

        if (wid_console_window && wid_console_window->visible) {
          pcg_random_allowed = false;
          {
            wid_display_all();
          }
          pcg_random_allowed = true;
        } else {
          pcg_random_allowed = false;
          {
            //
            // Must do this before wid_display_all so that the
            // on screen widgets are updated with the new wid
            // we are about to make.
            //
            if (game->request_update_rightbar) {
              game->request_update_rightbar = false;
              wid_rightbar_init();
            }

            wid_display_all();
          }
          pcg_random_allowed = true;
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
      pcg_random_allowed = false;
      {
        wid_gc_all();
      }
      pcg_random_allowed = true;

      //
      // Read events
      //
      SDL_PumpEvents();

      wheel_x = 0;
      wheel_y = 0;

      found = SDL_PeepEvents(events, ARRAY_SIZE(events), SDL_GETEVENT, SDL_QUIT, SDL_LASTEVENT);

      for (i = 0; i < found; ++i) {
        sdl_event(&events[ i ]);
      }

      //
      // Mouse held?
      //
      static uint32_t last_mouse_held_down = time_get_time_ms_cached();
      if (unlikely(! found)) {
        auto mouse_down = sdl_get_mouse();
        if (mouse_down) {
          if (last_mouse_held_down) {
            if (time_have_x_hundredths_passed_since(5, last_mouse_held_down)) {
              LOG("SDL: Mouse DOWN held: Button %d", mouse_down);
              wid_mouse_held(mouse_down, mouse_x, mouse_y);
            }
          } else {
            last_mouse_held_down = time_get_time_ms_cached();
          }
        } else {
          last_mouse_held_down = 0;
        }
      } else {
        last_mouse_held_down = 0;
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
    }

    if (likely(! g_errored)) {
      if (likely(game->level != nullptr)) {
        //
        // If the tick ends, start the new tick asap for smoothness.
        //
        if (game->level->tick()) {
          game->level->tick();
        }
      }
    }

    pcg_random_allowed = false;
    {
      blit_fbo_bind(FBO_FINAL);
      glClear(GL_COLOR_BUFFER_BIT);
      glcolor(WHITE);
      glBlendFunc(GL_ONE, GL_ZERO);
      blit_fbo_window_pix(FBO_MAP);

      //
      // Draw the map
      //
      if (likely(game->level != nullptr)) {
        game->level->display_map_mini();
      }

      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      blit_fbo_window_pix(FBO_WID);
      blit_fbo_unbind();

      glBlendFunc(GL_ONE, GL_ZERO);
      if (unlikely(game->config.gfx_inverted)) {
        glLogicOp(GL_COPY_INVERTED);
        glEnable(GL_COLOR_LOGIC_OP);
        blit_fbo_window_pix(FBO_FINAL);
        glLogicOp(GL_COPY);
        glDisable(GL_COLOR_LOGIC_OP);
      } else {
        blit_fbo_window_pix(FBO_FINAL);
      }

      //
      // Screenshot?
      //
      if (unlikely(g_do_screenshot)) {
        g_do_screenshot = 0;
        sdl_screenshot_do();
      }

      SDL_Delay(game->config.sdl_delay);

      //
      // Flip
      //
      if (likely(game->config.gfx_vsync_locked)) {
        SDL_GL_SwapWindow(window);
      } else {
        glFlush();
      }
    }

    pcg_random_allowed = true;

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
