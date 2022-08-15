//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::dump(std::string pfx)
{
  TRACE_AND_INDENT();
  LOG("%s Level {", pfx.c_str());
  auto old_pfx = pfx;
  pfx += "  ";

  LOG("%s cursor_at          %s", pfx.c_str(), cursor_at.to_string().c_str());
  LOG("%s cursor_old         %s", pfx.c_str(), cursor_old.to_string().c_str());
  LOG("%s map_at             %s", pfx.c_str(), map_at.to_string().c_str());
  LOG("%s map_wanted_at      %s", pfx.c_str(), map_wanted_at.to_string().c_str());

  LOG("%s all_things", pfx.c_str());
  {
    for (auto x = 0; x < MAP_WIDTH; ++x) {
      for (auto y = 0; y < MAP_HEIGHT; ++y) {
        for (auto z = 0; z < MAP_SLOTS; ++z) {
          auto id = get(all_things_id_at, x, y, z);
          if (id.ok()) {
            auto t = thing_find(id);
            if (unlikely(! t)) {
              continue;
            }
            t->log("dump");
          }
        }
      }
    }
  }

  pfx = old_pfx;
  LOG("%s }", pfx.c_str());
}

void World::dump(std::string pfx)
{
  TRACE_AND_INDENT();
  LOG("%s World {", pfx.c_str());
  auto old_pfx = pfx;
  pfx += "  ";

  LOG("%s levels", pfx.c_str());
  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          l->dump(pfx + "  ");
        }
      }
    }
  }

  pfx = old_pfx;
  LOG("%s }", pfx.c_str());
}

void Config::dump(std::string pfx)
{
  TRACE_AND_INDENT();
  LOG("%s Config {", pfx.c_str());
  auto old_pfx = pfx;
  pfx += "  ";

  LOG("%s ascii_gl_height        %u", pfx.c_str(), ascii_gl_height);
  LOG("%s ascii_gl_width         %u", pfx.c_str(), ascii_gl_width);
  LOG("%s debug_mode             %u", pfx.c_str(), debug_mode);
  LOG("%s fps_counter            %u", pfx.c_str(), fps_counter);
  LOG("%s game_pix_height        %u", pfx.c_str(), game_pix_height);
  LOG("%s game_pix_scale_height  %f", pfx.c_str(), game_pix_scale_height);
  LOG("%s game_pix_scale_width   %f", pfx.c_str(), game_pix_scale_width);
  LOG("%s game_pix_width         %u", pfx.c_str(), game_pix_width);
  LOG("%s game_pix_zoom          %f", pfx.c_str(), game_pix_zoom);
  LOG("%s gfx_allow_highdpi      %u", pfx.c_str(), gfx_allow_highdpi);
  LOG("%s gfx_borderless         %u", pfx.c_str(), gfx_borderless);
  LOG("%s gfx_fullscreen_desktop %u", pfx.c_str(), gfx_fullscreen_desktop);
  LOG("%s gfx_fullscreen         %u", pfx.c_str(), gfx_fullscreen);
  LOG("%s gfx_inverted           %u", pfx.c_str(), gfx_inverted);
  LOG("%s gfx_show_hidden        %u", pfx.c_str(), gfx_show_hidden);
  LOG("%s gfx_vsync_enable       %u", pfx.c_str(), gfx_vsync_enable);
  LOG("%s music_volume           %u", pfx.c_str(), music_volume);
  LOG("%s one_pixel_height       %f", pfx.c_str(), one_pixel_height);
  LOG("%s one_pixel_width        %f", pfx.c_str(), one_pixel_width);
  LOG("%s sdl_delay              %u", pfx.c_str(), sdl_delay);
  LOG("%s snapshot_freq          %u", pfx.c_str(), snapshot_freq);
  LOG("%s sound_volume           %u", pfx.c_str(), sound_volume);
  LOG("%s tile_pixel_height      %f", pfx.c_str(), tile_pixel_height);
  LOG("%s tile_pixel_width       %f", pfx.c_str(), tile_pixel_width);
  LOG("%s tile_pix_height        %f", pfx.c_str(), tile_pix_height);
  LOG("%s tile_pix_width         %f", pfx.c_str(), tile_pix_width);
  LOG("%s ui_pix_height          %u", pfx.c_str(), ui_pix_height);
  LOG("%s ui_pix_width           %u", pfx.c_str(), ui_pix_width);
  LOG("%s ui_pix_zoom            %f", pfx.c_str(), ui_pix_zoom);
  LOG("%s ui_ascii_term_height   %u", pfx.c_str(), ui_ascii_term_height);
  LOG("%s ui_ascii_term_width    %u", pfx.c_str(), ui_ascii_term_width);
  LOG("%s ui_gfx_term_height     %u", pfx.c_str(), ui_gfx_term_height);
  LOG("%s ui_gfx_term_width      %u", pfx.c_str(), ui_gfx_term_width);
  LOG("%s video_w_h_ratio        %f", pfx.c_str(), video_w_h_ratio);
  LOG("%s window_pix_height      %u", pfx.c_str(), window_pix_height);
  LOG("%s window_pix_width       %u", pfx.c_str(), window_pix_width);
  pfx = old_pfx;
  LOG("%s }", pfx.c_str());
}

void Game::dump(std::string pfx)
{
  TRACE_AND_INDENT();
  LOG("%s Game {", pfx.c_str());
  auto old_pfx = pfx;
  pfx += "  ";

  LOG("%s save_slot  %u", pfx.c_str(), save_slot);
  LOG("%s save_meta  %s", pfx.c_str(), save_meta.c_str());
  LOG("%s save_file  %s", pfx.c_str(), save_file.c_str());
  LOG("%s appdata    %s", pfx.c_str(), appdata.c_str());
  LOG("%s saved_dir  %s", pfx.c_str(), saved_dir.c_str());
  LOG("%s seed       %u", pfx.c_str(), seed);
  config.dump(pfx);
  world.dump(pfx);

  pfx = old_pfx;
  LOG("%s }", pfx.c_str());
}
