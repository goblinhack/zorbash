//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include "my_thing.h"

void Monst::log (std::string pfx)
{_
    LOG("%s Monst {", pfx.c_str());
    auto old_pfx = pfx;
    pfx += "  ";

    if (age_map) {
        LOG("%s has age_map", pfx.c_str());
    }
    if (dmap_scent) {
        LOG("%s has dmap_scent", pfx.c_str());
    }

    pfx = old_pfx;
    LOG("%s }", pfx.c_str());
}

void Thing::log (std::string pfx)
{_
    LOG("%s Thing {", pfx.c_str());
    auto old_pfx = pfx;
    pfx += "  ";

    LOG("%s id                  %08X", pfx.c_str(), id);
    LOG("%s tp_id               %d", pfx.c_str(), tp_id);

    if (monstp) {
        monstp->log(pfx + "  ");
    }

    LOG("%s at                   %s", pfx.c_str(), at.to_string().c_str());
    LOG("%s target               %s", pfx.c_str(), target.to_string().c_str());
    LOG("%s tile_curr            %u", pfx.c_str(), tile_curr);
    LOG("%s timestamp_next_frame %u", pfx.c_str(), timestamp_next_frame);
    LOG("%s dir                  %u", pfx.c_str(), dir);
    LOG("%s is_player            %u", pfx.c_str(), is_player());
    LOG("%s has_ever_moved       %u", pfx.c_str(), has_ever_moved);
    LOG("%s has_light            %u", pfx.c_str(), has_light);
    LOG("%s is_attached          %u", pfx.c_str(), is_attached);
    LOG("%s is_being_destroyed   %u", pfx.c_str(), is_being_destroyed);
    LOG("%s is_blitted           %u", pfx.c_str(), is_blitted);
    LOG("%s is_bloodied          %u", pfx.c_str(), is_bloodied);
    LOG("%s is_bouncing          %u", pfx.c_str(), is_bouncing);
    LOG("%s is_dead              %u", pfx.c_str(), is_dead);
    LOG("%s is_facing_left       %u", pfx.c_str(), is_facing_left);
    LOG("%s is_hidden            %u", pfx.c_str(), is_hidden);
    LOG("%s is_hungry            %u", pfx.c_str(), is_hungry);
    LOG("%s is_move_done         %u", pfx.c_str(), is_move_done);
    LOG("%s is_moving            %u", pfx.c_str(), is_moving);
    LOG("%s is_open              %u", pfx.c_str(), is_open);
    LOG("%s is_sleeping          %u", pfx.c_str(), is_sleeping);
    LOG("%s is_starving          %u", pfx.c_str(), is_starving);
    LOG("%s is_in_water          %u", pfx.c_str(), is_in_water);
    LOG("%s is_in_lava           %u", pfx.c_str(), is_in_lava);
    LOG("%s is_waiting_to_move   %u", pfx.c_str(), is_waiting_to_move);

    pfx = old_pfx;
    LOG("%s }", pfx.c_str());
}

void Level::log (std::string pfx)
{_
    LOG("%s Level {", pfx.c_str());
    auto old_pfx = pfx;
    pfx += "  ";

    LOG("%s cursor_at                 %s", pfx.c_str(), cursor_at.to_string().c_str());
    LOG("%s cursor_at_old             %s", pfx.c_str(), cursor_at_old.to_string().c_str());
    LOG("%s map_at                    %s", pfx.c_str(), map_at.to_string().c_str());
    LOG("%s map_follow_player         %u", pfx.c_str(), map_follow_player);
    LOG("%s map_wanted_at             %s", pfx.c_str(), map_wanted_at.to_string().c_str());
    LOG("%s timestamp_dungeon_created %u", pfx.c_str(), timestamp_dungeon_created);
    LOG("%s next_thing_id             %08X", pfx.c_str(), next_thing_id);

    LOG("%s all_things", pfx.c_str());
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_HEIGHT; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y, z);
                if (id) {
                    auto t = thing_find(id);
                    t->log(pfx + "  ");
                }
            }
        }
    }

    pfx = old_pfx;
    LOG("%s }", pfx.c_str());
}

void World::log (std::string pfx)
{_
    LOG("%s World {", pfx.c_str());
    auto old_pfx = pfx;
    pfx += "  ";

    LOG("%s levels", pfx.c_str());
    for (auto x = 0; x < LEVELS_ACROSS; ++x) {
        for (auto y = 0; y < LEVELS_DOWN; ++y) {
            for (auto z = 0; z < LEVELS_DEEP; ++z) {
                auto l = get(levels, x, y, z);
                if (l) {
                    l->log(pfx + "  ");
                }
            }
        }
    }

    pfx = old_pfx;
    LOG("%s }", pfx.c_str());
}

void Config::log (std::string pfx)
{_
    LOG("%s Config {", pfx.c_str());
    auto old_pfx = pfx;
    pfx += "  ";

    LOG("%s fps_counter         %u", pfx.c_str(), fps_counter);
    LOG("%s gfx_inverted        %u", pfx.c_str(), gfx_inverted);
    LOG("%s gfx_minimap         %u", pfx.c_str(), gfx_minimap);
    LOG("%s gfx_show_hidden     %u", pfx.c_str(), gfx_show_hidden);
    LOG("%s gfx_lights          %u", pfx.c_str(), gfx_lights);
    LOG("%s gfx_zoom            %u", pfx.c_str(), gfx_zoom);
    LOG("%s debug_mode          %u", pfx.c_str(), debug_mode);
    LOG("%s arcade_mode         %u", pfx.c_str(), arcade_mode);
    LOG("%s sound_volume        %u", pfx.c_str(), sound_volume);
    LOG("%s music_volume        %u", pfx.c_str(), music_volume);
    LOG("%s gfx_vsync_enable    %u", pfx.c_str(), gfx_vsync_enable);
    LOG("%s fullscreen          %u", pfx.c_str(), fullscreen);
    LOG("%s allow_highdpi       %u", pfx.c_str(), allow_highdpi);
    LOG("%s video_pix_width     %u", pfx.c_str(), video_pix_width);
    LOG("%s video_pix_height    %u", pfx.c_str(), video_pix_height);
    LOG("%s video_gl_width      %f", pfx.c_str(), video_gl_width);
    LOG("%s video_gl_height     %f", pfx.c_str(), video_gl_height);
    LOG("%s video_w_h_ratio     %f", pfx.c_str(), video_w_h_ratio);
    LOG("%s drawable_gl_width   %u", pfx.c_str(), drawable_gl_width);
    LOG("%s drawable_gl_height  %u", pfx.c_str(), drawable_gl_height);
    LOG("%s tile_gl_width       %f", pfx.c_str(), tile_gl_width);
    LOG("%s tile_gl_height      %f", pfx.c_str(), tile_gl_height);
    LOG("%s one_pixel_gl_width  %f", pfx.c_str(), one_pixel_gl_width);
    LOG("%s one_pixel_gl_height %f", pfx.c_str(), one_pixel_gl_height);
    LOG("%s ascii_gl_width      %f", pfx.c_str(), ascii_gl_width);
    LOG("%s ascii_gl_height     %f", pfx.c_str(), ascii_gl_height);
    LOG("%s tile_pixel_width    %f", pfx.c_str(), tile_pixel_width);
    LOG("%s tile_pixel_height   %f", pfx.c_str(), tile_pixel_height);
    LOG("%s sdl_delay           %u", pfx.c_str(), sdl_delay);

    pfx = old_pfx;
    LOG("%s }", pfx.c_str());
}

void Game::log (std::string pfx)
{_
    LOG("%s Game {", pfx.c_str());
    auto old_pfx = pfx;
    pfx += "  ";

    LOG("%s save_slot  %u", pfx.c_str(), save_slot);
    LOG("%s save_meta  %s", pfx.c_str(), save_meta.c_str());
    LOG("%s save_file  %s", pfx.c_str(), save_file.c_str());
    LOG("%s appdata    %s", pfx.c_str(), appdata.c_str());
    LOG("%s saved_dir  %s", pfx.c_str(), saved_dir.c_str());
    LOG("%s seed       %u", pfx.c_str(), seed);
    config.log(pfx);
    world.log(pfx);

    pfx = old_pfx;
    LOG("%s }", pfx.c_str());
}
