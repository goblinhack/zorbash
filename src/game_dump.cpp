/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

void Monst::dump (std::string pfx, std::ostream &out)
{
    out << pfx << "Monst {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    if (age_map) {
        out << pfx << "has age_map" << std::endl;
    }
    if (dmap_scent) {
        out << pfx << "has dmap_scent" << std::endl;
    }

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

void Thing::dump (std::string pfx, std::ostream &out)
{
    out << pfx << "Thing {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    out << pfx << "id                  " << std::hex             << id << std::endl;
    auto tp = tp_find(tp_id);
    out << pfx << "tp_id               " << tp_id                << " " << tp_name(tp) << std::endl;

    if (monst) {
        monst->dump(pfx + "  ", out);
    }

    out << pfx << "last_attached       " << last_attached        << std::endl;
    out << pfx << "br                  " << br                   << std::endl;
    out << pfx << "last_blit_br        " << last_blit_br         << std::endl;
    out << pfx << "last_blit_tl        " << last_blit_tl         << std::endl;
    out << pfx << "last_mid_at         " << last_mid_at          << std::endl;
    out << pfx << "mid_at              " << mid_at               << std::endl;
    out << pfx << "tl                  " << tl                   << std::endl;
    out << pfx << "tile_curr           " << tile_curr            << std::endl;
    out << pfx << "timestamp_next_frame" << timestamp_next_frame << std::endl;
    out << pfx << "dir                 " << dir                  << std::endl;
    out << pfx << "is_player           " << is_player()          << std::endl;
    out << pfx << "has_ever_moved      " << has_ever_moved       << std::endl;
    out << pfx << "has_light           " << has_light            << std::endl;
    out << pfx << "is_attached         " << is_attached          << std::endl;
    out << pfx << "is_being_destroyed  " << is_being_destroyed   << std::endl;
    out << pfx << "is_bloodied         " << is_bloodied          << std::endl;
    out << pfx << "is_bouncing         " << is_bouncing          << std::endl;
    out << pfx << "is_dead             " << is_dead              << std::endl;
    out << pfx << "is_facing_left      " << is_facing_left       << std::endl;
    out << pfx << "is_hidden           " << is_hidden            << std::endl;
    out << pfx << "is_hungry           " << is_hungry            << std::endl;
    out << pfx << "is_moving           " << is_moving            << std::endl;
    out << pfx << "is_open             " << is_open              << std::endl;
    out << pfx << "is_sleeping         " << is_sleeping          << std::endl;
    out << pfx << "is_starving         " << is_starving          << std::endl;
    out << pfx << "is_submerged        " << is_submerged         << std::endl;
    out << pfx << "is_waiting_for_ai   " << is_waiting_for_ai    << std::endl;
    out << pfx << "is_pending_gc       " << is_pending_gc        << std::endl;
    out << pfx << "is_blitted          " << is_blitted           << std::endl;

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

void World::dump (std::string pfx, std::ostream &out)
{
    out << pfx << "World {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    out << pfx << "cursor_at                 " << cursor_at << std::endl;
    out << pfx << "cursor_at_old             " << cursor_at_old << std::endl;
    out << pfx << "map_at                    " << map_at << std::endl;
    out << pfx << "map_follow_player         " << map_follow_player << std::endl;
    out << pfx << "map_wanted_at             " << map_wanted_at << std::endl;
    out << pfx << "timestamp_dungeon_created " << timestamp_dungeon_created << std::endl;
    out << pfx << "next_thing_id             " << next_thing_id << std::endl;

    out << pfx << "all_things" << std::endl;
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y, z);
                if (id) {
                    auto t = thing_find(id);
                    t->log("dump");
                    t->dump(pfx + "  ", out);
                }
            }
        }
    }

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

void Config::dump (std::string pfx, std::ostream &out)
{_
    out << pfx << "Config {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    out << pfx << "fps_counter        " << fps_counter << std::endl;
    out << pfx << "gfx_inverted       " << gfx_inverted << std::endl;
    out << pfx << "gfx_minimap        " << gfx_minimap << std::endl;
    out << pfx << "gfx_show_hidden    " << gfx_show_hidden << std::endl;
    out << pfx << "gfx_lights         " << gfx_lights << std::endl;
    out << pfx << "gfx_zoom           " << gfx_zoom << std::endl;
    out << pfx << "sound_volume       " << sound_volume << std::endl;
    out << pfx << "music_volume       " << music_volume << std::endl;
    out << pfx << "vsync_enable       " << vsync_enable << std::endl;
    out << pfx << "full_screen        " << full_screen << std::endl;
    out << pfx << "video_pix_width    " << video_pix_width << std::endl;
    out << pfx << "video_pix_height   " << video_pix_height << std::endl;
    out << pfx << "video_gl_width     " << video_gl_width << std::endl;
    out << pfx << "video_gl_height    " << video_gl_height << std::endl;
    out << pfx << "video_w_h_ratio    " << video_w_h_ratio << std::endl;
    out << pfx << "drawable_gl_width  " << drawable_gl_width << std::endl;
    out << pfx << "drawable_gl_height " << drawable_gl_height << std::endl;
    out << pfx << "tile_gl_width      " << tile_gl_width << std::endl;
    out << pfx << "tile_gl_height     " << tile_gl_height << std::endl;
    out << pfx << "one_pixel_gl_width " << one_pixel_gl_width << std::endl;
    out << pfx << "one_pixel_gl_height" << one_pixel_gl_height << std::endl;
    out << pfx << "ascii_gl_width     " << ascii_gl_width << std::endl;
    out << pfx << "ascii_gl_height    " << ascii_gl_height << std::endl;
    out << pfx << "tile_pixel_width   " << tile_pixel_width << std::endl;
    out << pfx << "tile_pixel_height  " << tile_pixel_height << std::endl;
    out << pfx << "sdl_delay          " << sdl_delay << std::endl;

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

void Game::dump (std::string pfx, std::ostream &out)
{
    out << pfx << "Game {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    out << pfx << "appdata    " << appdata << std::endl;
    out << pfx << "saved_dir  " << saved_dir << std::endl;
    out << pfx << "saved_file " << saved_file << std::endl;
    out << pfx << "seed       " << seed << std::endl;
    out << pfx << "fps_count  " << fps_count << std::endl;
    config.dump(pfx, out);
    world.dump(pfx, out);

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}
