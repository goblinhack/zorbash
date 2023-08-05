//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_sdl_event.hpp"
#include "my_sdl_proto.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "my_wid_tp_info.hpp"

void sdl_display(void)
{
  {
    blit_fbo_bind(FBO_FINAL);
    glClear(GL_COLOR_BUFFER_BIT);
    glcolor(WHITE);

    if (! g_opt_ascii) {
      glBlendFunc(GL_ONE, GL_ZERO);
      blit_fbo_window_pix(FBO_MAP);

      //
      // Draw the map
      //
      if (likely(game->level != nullptr)) {
        game->level->display_pixelart_map_mini();
      }
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
      SDL_GL_SwapWindow(sdl.window);
    } else {
      glFlush();
    }
  }
}

void sdl_display_reset(void)
{
  CON("SDL: Video resetting");

  auto old_topcon  = wid_topcon_serialize();
  auto old_console = wid_console_serialize();

  wid_console_fini();
  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_actionbar_fini();
  wid_botcon_fini();
  wid_topcon_fini();
  wid_asciimap_fini();
  wid_thing_info_fini("gfx toggle"); // To remove bag or other info
  wid_tp_info_fini("gfx toggle");    // To remove bag or other info

  config_game_gfx_update();

  game->set_request_to_remake_rightbar();
  game->set_request_to_remake_inventory();
  game->set_request_to_remake_actionbar();
  game->set_request_to_remake_skillbox();
  game->set_request_to_remake_spellbox();
  game->set_request_to_remake_debuffbox();
  game->set_request_to_remake_buffbox();

  if (game->level) {
    game->level->scroll_map_to_player_immediately();
  }

  wid_console_init();
  wid_hide(wid_console_window);
  sdl_flush_display();

  wid_asciimap_init();
  wid_botcon_init();
  wid_topcon_init();
  wid_visible(wid_topcon_window);
  wid_visible(wid_botcon_window);
  wid_topcon_deserialize(old_topcon);
  wid_console_deserialize(old_console);

  //
  // DO NOT CALL THIS HERE. We could be inside a widget mouse up handler.
  //
  // wid_gc_all();
  //
  wid_display_all();

  CON("SDL: Video reset");
  sdl_flush_display();
}
