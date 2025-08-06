//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_ui.hpp"
#include <SDL_mixer.h>

void Config::fini(void) { TRACE_AND_INDENT(); }

void Config::reset(void)
{
  TRACE_AND_INDENT();
  version                 = "" MYVER "";
  debug_mode              = false;
  disable_player_warnings = false;
  fps_counter             = false;
  game_pix_scale_height   = {};
  game_pix_scale_width    = {};
  game_pix_zoom           = GAME_DEFAULT_PIX_ZOOM;
  gfx_allow_highdpi       = false;
  gfx_borderless          = true;
  gfx_fullscreen          = false;
  one_pixel_height        = {};
  one_pixel_width         = {};
  tile_pixel_height       = {};
  tile_pixel_width        = {};
  tile_pix_height         = {};
  tile_pix_width          = {};
  ui_pix_zoom             = GAME_DEFAULT_UI_ZOOM;
  ui_ascii_term_height    = {TERM_ASCII_HEIGHT_DEF};
  ui_ascii_term_width     = {TERM_ASCII_WIDTH_DEF};
  ui_gfx_term_height      = {TERM_GFX_HEIGHT_DEF};
  ui_gfx_term_width       = {TERM_GFX_WIDTH_DEF};
  video_w_h_ratio         = {};
  gfx_fullscreen_desktop  = true;
  gfx_inverted            = false;
  gfx_monochrome          = g_opt_gfx_monochrome;
  gfx_show_hidden         = false;
  gfx_vsync_enable        = true;
  gfx_vsync_locked        = false;
  mouse_wheel_lr_negated  = false;
  mouse_wheel_ud_negated  = false;
  config_pix_height       = {};
  config_pix_width        = {};
  game_pix_height         = {};
  game_pix_width          = {};
  ui_pix_height           = {};
  ui_pix_width            = {};
  window_pix_height       = {};
  window_pix_width        = {};
  ascii_gl_height         = {};
  ascii_gl_width          = {};

  key_action0.sym         = SDLK_0;
  key_action1.sym         = SDLK_1;
  key_action2.sym         = SDLK_2;
  key_action3.sym         = SDLK_3;
  key_action4.sym         = SDLK_4;
  key_action5.sym         = SDLK_5;
  key_action6.sym         = SDLK_6;
  key_action7.sym         = SDLK_7;
  key_action8.sym         = SDLK_8;
  key_action9.sym         = SDLK_9;
  key_skill0.sym          = SDLK_0;
  key_skill0.mod          = KMOD_SHIFT;
  key_skill1.sym          = SDLK_1;
  key_skill1.mod          = KMOD_SHIFT;
  key_skill2.sym          = SDLK_2;
  key_skill2.mod          = KMOD_SHIFT;
  key_skill3.sym          = SDLK_3;
  key_skill3.mod          = KMOD_SHIFT;
  key_skill4.sym          = SDLK_4;
  key_skill4.mod          = KMOD_SHIFT;
  key_skill5.sym          = SDLK_5;
  key_skill5.mod          = KMOD_SHIFT;
  key_skill6.sym          = SDLK_6;
  key_skill6.mod          = KMOD_SHIFT;
  key_skill7.sym          = SDLK_7;
  key_skill7.mod          = KMOD_SHIFT;
  key_skill8.sym          = SDLK_8;
  key_skill8.mod          = KMOD_SHIFT;
  key_skill9.sym          = SDLK_9;
  key_skill9.mod          = KMOD_SHIFT;
  key_spell0.sym          = SDLK_0;
  key_spell0.mod          = KMOD_CTRL;
  key_spell1.sym          = SDLK_1;
  key_spell1.mod          = KMOD_CTRL;
  key_spell2.sym          = SDLK_2;
  key_spell2.mod          = KMOD_CTRL;
  key_spell3.sym          = SDLK_3;
  key_spell3.mod          = KMOD_CTRL;
  key_spell4.sym          = SDLK_4;
  key_spell4.mod          = KMOD_CTRL;
  key_spell5.sym          = SDLK_5;
  key_spell5.mod          = KMOD_CTRL;
  key_spell6.sym          = SDLK_6;
  key_spell6.mod          = KMOD_CTRL;
  key_spell7.sym          = SDLK_7;
  key_spell7.mod          = KMOD_CTRL;
  key_spell8.sym          = SDLK_8;
  key_spell8.mod          = KMOD_CTRL;
  key_spell9.sym          = SDLK_9;
  key_spell9.mod          = KMOD_CTRL;
  key_attack.sym          = SDLK_SPACE;
  key_drop.sym            = SDLK_BACKSPACE;
  key_eat.sym             = SDLK_e;
  key_help.sym            = SDLK_h;
  key_jump.sym            = SDLK_j;
  key_load.sym            = SDLK_F11;
  key_map_down.sym        = SDLK_DOWN;
  key_map_left.sym        = SDLK_LEFT;
  key_map_right.sym       = SDLK_RIGHT;
  key_map_up.sym          = SDLK_UP;
  key_move_down.sym       = SDLK_s;
  key_move_left.sym       = SDLK_a;
  key_move_right.sym      = SDLK_d;
  key_move_up.sym         = SDLK_w;
  key_quit.sym            = SDLK_q;
  key_save.sym            = SDLK_F12;
  key_screenshot.sym      = SDLK_F10;
  key_throw.sym           = SDLK_t;
  key_inventory.sym       = SDLK_i;
  key_console.sym         = SDLK_TAB;
  key_console.mod         = KMOD_SHIFT;
  key_robot_mode.sym      = SDLK_r;
  key_gfx_toggle.sym      = SDLK_TAB;
  key_descend.sym         = SDLK_GREATER;
  key_ascend.sym          = SDLK_LESS;
  key_use.sym             = SDLK_u;
  key_wait_or_collect.sym = SDLK_PERIOD;
  key_zoom_in.sym         = SDLK_z;
  key_zoom_out.sym        = SDLK_x;
  music_volume            = {MIX_MAX_VOLUME / 3};
  sdl_delay               = 1;
  snapshot_freq           = ENABLE_SAVE_SNAPSHOT_FREQ;
  sound_volume            = {MIX_MAX_VOLUME / 2};

  // key_unused1.sym  = SDLK_TAB;
  // key_unused1.mod  = KMOD_NUM;
  // key_unused2.sym  = SDLK_TAB;
  // key_unused2.mod  = KMOD_NUM;
  // key_unused3.sym  = SDLK_TAB;
  // key_unused3.mod  = KMOD_NUM;
  // key_unused4.sym  = SDLK_TAB;
  // key_unused4.mod  = KMOD_NUM;
  // key_unused5.sym  = SDLK_TAB;
  // key_unused5.mod  = KMOD_NUM;
  // key_unused6.sym  = SDLK_TAB;
  // key_unused6.mod  = KMOD_NUM;
  // key_unused7.sym  = SDLK_TAB;
  // key_unused7.mod  = KMOD_NUM;
  // key_unused8.sym  = SDLK_TAB;
  // key_unused8.mod  = KMOD_NUM;
  // key_unused9.sym  = SDLK_TAB;
  // key_unused9.mod  = KMOD_NUM;
  // key_unused10.sym  = SDLK_TAB;
  // key_unused10.mod  = KMOD_NUM;
  // key_unused11.sym  = SDLK_TAB;
  // key_unused11.mod  = KMOD_NUM;
  // key_unused12.sym  = SDLK_TAB;
  // key_unused12.mod  = KMOD_NUM;
  // key_unused13.sym  = SDLK_TAB;
  // key_unused13.mod  = KMOD_NUM;
  // key_unused14.sym  = SDLK_TAB;
  // key_unused14.mod  = KMOD_NUM;
  // key_unused15.sym  = SDLK_TAB;
  // key_unused15.mod  = KMOD_NUM;
  // key_unused16.sym  = SDLK_TAB;
  // key_unused16.mod  = KMOD_NUM;
  // key_unused17.sym  = SDLK_TAB;
  // key_unused17.mod  = KMOD_NUM;
  // key_unused18.sym  = SDLK_TAB;
  // key_unused18.mod  = KMOD_NUM;
  // key_unused19.sym  = SDLK_TAB;
  // key_unused19.mod  = KMOD_NUM;
  // key_unused20.sym  = SDLK_TAB;
  // key_unused20.mod  = KMOD_NUM;
  //
  player_bodyparts[ BODYPART_EYES ]  = "bodypart_eyes1";
  player_bodyparts[ BODYPART_FACE ]  = "bodypart_face1";
  player_bodyparts[ BODYPART_TORSO ] = "bodypart_torso1";
  player_bodyparts[ BODYPART_LEGS ]  = "bodypart_legs1";
  player_bodyparts[ BODYPART_HAT ]   = "bodypart_hat1";
}

//
// Now all templates are loaded, make sure we have some default config.
// for example, for bodyparts.
//
void Config::final_init(void)
{
  TRACE_AND_INDENT();

  //
  // Initialize with random bodyparts if not set
  //
  FOR_ALL_BODYPART(iter)
  {
    TRACE_NO_INDENT();
    auto curr_bodypart = get(player_bodyparts, iter);
    if (curr_bodypart.empty()) {
      auto tp_bodypart = tp_random_bodypart(iter);
      set(player_bodyparts, iter, tp_bodypart->name());
    }
  }
}
