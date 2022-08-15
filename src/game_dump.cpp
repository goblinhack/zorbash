//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::dump(std::string pfx, std::ostream &out)
{
  TRACE_AND_INDENT();
  out << pfx << "World {" << std::endl;
  auto old_pfx = pfx;
  pfx += "  ";

  out << pfx << "cursor_at          " << cursor_at << std::endl;
  out << pfx << "cursor_old         " << cursor_old << std::endl;
  out << pfx << "map_at             " << map_at << std::endl;
  out << pfx << "map_wanted_at      " << map_wanted_at << std::endl;

  out << pfx << "all_things" << std::endl;
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
            t->log("Dump");
          }
        }
      }
    }
  }

  pfx = old_pfx;
  out << pfx << "}" << std::endl;
}

void World::dump(std::string pfx, std::ostream &out)
{
  TRACE_AND_INDENT();
  out << pfx << "Level {" << std::endl;
  auto old_pfx = pfx;
  pfx += "  ";

  out << pfx << "levels" << std::endl;
  for (auto x = 0; x < LEVELS_ACROSS; ++x) {
    for (auto y = 0; y < LEVELS_DOWN; ++y) {
      for (auto z = 0; z < LEVELS_DEEP; ++z) {
        auto l = get(levels, x, y, z);
        if (l) {
          l->dump(pfx + "  ", out);
        }
      }
    }
  }

  pfx = old_pfx;
  out << pfx << "}" << std::endl;
}

void Config::dump(std::string pfx, std::ostream &out)
{
  TRACE_AND_INDENT();
  out << pfx << "Config {" << std::endl;
  auto old_pfx = pfx;
  pfx += "  ";

  out << pfx << "ascii_gl_height        " << ascii_gl_height << std::endl;
  out << pfx << "ascii_gl_width         " << ascii_gl_width << std::endl;
  out << pfx << "debug_mode             " << debug_mode << std::endl;
  out << pfx << "fps_counter            " << fps_counter << std::endl;
  out << pfx << "game_pix_height        " << game_pix_height << std::endl;
  out << pfx << "game_pix_scale_height  " << game_pix_scale_height << std::endl;
  out << pfx << "game_pix_scale_width   " << game_pix_scale_width << std::endl;
  out << pfx << "game_pix_width         " << game_pix_width << std::endl;
  out << pfx << "game_pix_zoom          " << game_pix_zoom << std::endl;
  out << pfx << "gfx_allow_highdpi      " << gfx_allow_highdpi << std::endl;
  out << pfx << "gfx_borderless         " << gfx_borderless << std::endl;
  out << pfx << "gfx_fullscreen_desktop " << gfx_fullscreen_desktop << std::endl;
  out << pfx << "gfx_fullscreen         " << gfx_fullscreen << std::endl;
  out << pfx << "gfx_inverted           " << gfx_inverted << std::endl;
  out << pfx << "gfx_show_hidden        " << gfx_show_hidden << std::endl;
  out << pfx << "gfx_vsync_enable       " << gfx_vsync_enable << std::endl;
  out << pfx << "music_volume           " << music_volume << std::endl;
  out << pfx << "one_pixel_height       " << one_pixel_height << std::endl;
  out << pfx << "one_pixel_width        " << one_pixel_width << std::endl;
  out << pfx << "sdl_delay              " << sdl_delay << std::endl;
  out << pfx << "snapshot_freq          " << snapshot_freq << std::endl;
  out << pfx << "sound_volume           " << sound_volume << std::endl;
  out << pfx << "tile_height            " << tile_height << std::endl;
  out << pfx << "tile_pixel_height      " << tile_pixel_height << std::endl;
  out << pfx << "tile_pixel_width       " << tile_pixel_width << std::endl;
  out << pfx << "tile_pix_height        " << tile_pix_height << std::endl;
  out << pfx << "tile_pix_width         " << tile_pix_width << std::endl;
  out << pfx << "tile_width             " << tile_width << std::endl;
  out << pfx << "ui_pix_height          " << ui_pix_height << std::endl;
  out << pfx << "ui_pix_width           " << ui_pix_width << std::endl;
  out << pfx << "ui_pix_zoom            " << ui_pix_zoom << std::endl;
  out << pfx << "ui_ascii_term_height   " << ui_ascii_term_height << std::endl;
  out << pfx << "ui_ascii_term_width    " << ui_ascii_term_width << std::endl;
  out << pfx << "ui_gfx_term_height     " << ui_gfx_term_height << std::endl;
  out << pfx << "ui_gfx_term_width      " << ui_gfx_term_width << std::endl;
  out << pfx << "video_w_h_ratio        " << video_w_h_ratio << std::endl;
  out << pfx << "window_pix_height      " << window_pix_height << std::endl;
  out << pfx << "window_pix_width       " << window_pix_width << std::endl;
  pfx = old_pfx;
  out << pfx << "}" << std::endl;
}

void Game::dump(std::string pfx, std::ostream &out)
{
  TRACE_AND_INDENT();
  out << pfx << "Game {" << std::endl;
  auto old_pfx = pfx;
  pfx += "  ";

  out << pfx << "save_slot  " << save_slot << std::endl;
  out << pfx << "save_meta  " << save_meta << std::endl;
  out << pfx << "save_file  " << save_file << std::endl;
  out << pfx << "appdata    " << appdata << std::endl;
  out << pfx << "saved_dir  " << saved_dir << std::endl;
  out << pfx << "seed       " << seed << std::endl;
  config.dump(pfx, out);
  world.dump(pfx, out);

  pfx = old_pfx;
  out << pfx << "}" << std::endl;
}
