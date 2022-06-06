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
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "stb_image_write.hpp"

void sdl_display(void)
{
  pcg_random_allowed = false;
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
  pcg_random_allowed = true;
}

void sdl_display_reset(void)
{
  CON("SDL: Video reset");

  wid_rightbar_fini();
  wid_leftbar_fini();
  wid_actionbar_fini();
  wid_botcon_fini();
  wid_thing_info_fini("gfx toggle"); // To remove bag or other info

  config_game_gfx_update();

  game->request_remake_rightbar  = true;
  game->request_remake_inventory = true;
  game->request_remake_actionbar = true;
  game->request_remake_skillbox  = true;
  game->request_remake_debuffbox = true;
  game->request_remake_buffbox   = true;

  if (game->level) {
    game->level->scroll_map_to_player_immediately();
  }

  wid_botcon_fini();
  wid_botcon_init();
  wid_visible(wid_botcon_window);

  wid_gc_all();
  wid_display_all();
}
