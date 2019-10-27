/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

std::ostream& operator<<(std::ostream &out, 
                         Bits<const AgeMap & > const my)
{
    out << bits(my.t.val);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<AgeMap &> my)
{
    in >> bits(my.t.val);
    return (in);
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<const Dmap & > const my)
{
    out << bits(my.t.val);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<Dmap &> my)
{
    in >> bits(my.t.val);
    return (in);
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<const Monst & > const my)
{
    bool age_map = (my.t.age_map != nullptr);
    out << bits(age_map);
    if (age_map) {
        out << bits(my.t.age_map);
    }

    bool dmap_goals = (my.t.dmap_goals != nullptr);
    out << bits(dmap_goals);
    if (dmap_goals) {
        out << bits(my.t.dmap_goals);
    }

    bool dmap_scent = (my.t.dmap_scent != nullptr);
    out << bits(dmap_scent);
    if (dmap_scent) {
        out << bits(my.t.dmap_scent);
    }

    out << bits(my.t.light_strength);
    out << bits(my.t.light_quality);
    out << bits(my.t.light_col);
    out << bits(my.t.interpolated_mid_at);
    out << bits(my.t.bounce_height);
    out << bits(my.t.bounce_fade);
    out << bits(my.t.rot);
    out << bits(my.t.submerged_offset);
    out << bits(my.t.bounce_count);
    out << bits(my.t.gold);
    out << bits(my.t.health);
    out << bits(my.t.health_max);
    out << bits(my.t.owned_count);
    out << bits(my.t.timestamp_bounce_begin);
    out << bits(my.t.timestamp_bounce_end);
    out << bits(my.t.timestamp_last_i_was_hit);
    out << bits(my.t.timestamp_flip_start);
    out << bits(my.t.timestamp_move_begin);
    out << bits(my.t.timestamp_move_end);
    out << bits(my.t.timestamp_born);
    out << bits(my.t.timestamp_hunger_tick);
    out << bits(my.t.timestamp_ai_next);
    out << bits(my.t.timestamp_collision);
    out << bits(my.t.owner_id);
    out << bits(my.t.weapon_id_carry_anim);
    out << bits(my.t.weapon_id_use_anim);
    out << bits(my.t.weapon_id);
    out << bits(my.t.carrying);

    return (out);
}

std::istream& operator>>(std::istream &in, Bits<Monst &> my)
{
    bool age_map;
    in >> bits(age_map);
    if (age_map) {
        my.t.age_map = new AgeMap();
        in >> bits(my.t.age_map);
    }

    bool dmap_goals;
    in >> bits(dmap_goals);
    if (dmap_goals) {
        my.t.dmap_goals = new Dmap();
        in >> bits(my.t.dmap_goals);
    }

    bool dmap_scent;
    in >> bits(dmap_scent);
    if (dmap_scent) {
        my.t.dmap_scent = new Dmap();
        in >> bits(my.t.dmap_scent);
    }

    in >> bits(my.t.light_strength);
    in >> bits(my.t.light_quality);
    in >> bits(my.t.light_col);
    in >> bits(my.t.interpolated_mid_at);
    in >> bits(my.t.bounce_height);
    in >> bits(my.t.bounce_fade);
    in >> bits(my.t.rot);
    in >> bits(my.t.submerged_offset);
    in >> bits(my.t.bounce_count);
    in >> bits(my.t.gold);
    in >> bits(my.t.health);
    in >> bits(my.t.health_max);
    in >> bits(my.t.owned_count);
    in >> bits(my.t.timestamp_bounce_begin);
    in >> bits(my.t.timestamp_bounce_end);
    in >> bits(my.t.timestamp_last_i_was_hit);
    in >> bits(my.t.timestamp_flip_start);
    in >> bits(my.t.timestamp_move_begin);
    in >> bits(my.t.timestamp_move_end);
    in >> bits(my.t.timestamp_born);
    in >> bits(my.t.timestamp_hunger_tick);
    in >> bits(my.t.timestamp_ai_next);
    in >> bits(my.t.timestamp_collision);
    in >> bits(my.t.owner_id);
    in >> bits(my.t.weapon_id_carry_anim);
    in >> bits(my.t.weapon_id_use_anim);
    in >> bits(my.t.weapon_id);
    in >> bits(my.t.carrying);

    return (in);
}

void Monst::dump (std::string pfx, std::ostream &out)
{
    out << pfx << "Monst {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    if (age_map) {
        out << pfx << "has age_map" << std::endl;
    }
    if (dmap_goals) {
        out << pfx << "has dmap_goals" << std::endl;
    }
    if (dmap_scent) {
        out << pfx << "has dmap_scent" << std::endl;
    }

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<const Thing & > const my)
{
    bool monst = (my.t.monst != nullptr);
    out << bits(monst);
    if (monst) {
        out << bits(my.t.monst);
    }

    out << bits(my.t.last_attached);
    out << bits(my.t.br);
    out << bits(my.t.last_blit_br);
    out << bits(my.t.last_blit_tl);
    out << bits(my.t.last_mid_at);
    out << bits(my.t.mid_at);
    out << bits(my.t.tl);
    out << bits(my.t.id);
    out << bits(my.t.tp_id);
    out << bits(my.t.tile_curr);
    out << bits(my.t.timestamp_next_frame);
    uint8_t dir = my.t.dir;
    out << bits(dir);

    uint32_t bits32 = 0;
    int shift = 0;
    bits32 |= my.t.has_ever_moved     << shift; shift++;
    bits32 |= my.t.has_light          << shift; shift++;
    bits32 |= my.t.is_attached        << shift; shift++;
    bits32 |= my.t.is_being_destroyed << shift; shift++;
    bits32 |= my.t.is_bloodied        << shift; shift++;
    bits32 |= my.t.is_bouncing        << shift; shift++;
    bits32 |= my.t.is_dead            << shift; shift++;
    bits32 |= my.t.is_facing_left     << shift; shift++;
    bits32 |= my.t.is_hidden          << shift; shift++;
    bits32 |= my.t.is_hungry          << shift; shift++;
    bits32 |= my.t.is_moving          << shift; shift++;
    bits32 |= my.t.is_open            << shift; shift++;
    bits32 |= my.t.is_sleeping        << shift; shift++;
    bits32 |= my.t.is_starving        << shift; shift++;
    bits32 |= my.t.is_submerged       << shift; shift++;
    bits32 |= my.t.is_waiting_for_ai  << shift; shift++;
    bits32 |= my.t.is_pending_gc      << shift; shift++;
    if (shift >= (int)(sizeof(bits32) * 8)) {
        DIE("ran out of bits in serialization");
    }
    out << bits(bits32);

    return (out);
}

std::istream& operator>>(std::istream &in, Bits<Thing &> my)
{
    bool monst = (my.t.monst != nullptr);
    in >> bits(monst);
    if (monst) {
        my.t.new_monst();
        in >> bits(my.t.monst);
    }

    in >> bits(my.t.last_attached);
    in >> bits(my.t.br);
    in >> bits(my.t.last_blit_br);
    in >> bits(my.t.last_blit_tl);
    in >> bits(my.t.last_mid_at);
    in >> bits(my.t.mid_at);
    in >> bits(my.t.tl);
    in >> bits(my.t.id);
    in >> bits(my.t.tp_id);
    in >> bits(my.t.tile_curr);
    in >> bits(my.t.timestamp_next_frame);
    uint8_t dir;
    in >> dir;
    my.t.dir = dir;

    uint32_t bits32;
    in >> bits(bits32);
    int shift = 0;
    my.t.has_ever_moved     = (bits32 >> shift) & 1; shift++;
    my.t.has_light          = (bits32 >> shift) & 1; shift++;
    my.t.is_attached        = (bits32 >> shift) & 1; shift++;
    my.t.is_being_destroyed = (bits32 >> shift) & 1; shift++;
    my.t.is_bloodied        = (bits32 >> shift) & 1; shift++;
    my.t.is_bouncing        = (bits32 >> shift) & 1; shift++;
    my.t.is_dead            = (bits32 >> shift) & 1; shift++;
    my.t.is_facing_left     = (bits32 >> shift) & 1; shift++;
    my.t.is_hidden          = (bits32 >> shift) & 1; shift++;
    my.t.is_hungry          = (bits32 >> shift) & 1; shift++;
    my.t.is_moving          = (bits32 >> shift) & 1; shift++;
    my.t.is_open            = (bits32 >> shift) & 1; shift++;
    my.t.is_sleeping        = (bits32 >> shift) & 1; shift++;
    my.t.is_starving        = (bits32 >> shift) & 1; shift++;
    my.t.is_submerged       = (bits32 >> shift) & 1; shift++;
    my.t.is_waiting_for_ai  = (bits32 >> shift) & 1; shift++;
    my.t.is_pending_gc      = (bits32 >> shift) & 1; shift++;

    world->put_thing_ptr((int)my.t.last_attached.x, 
                         (int)my.t.last_attached.y, &my.t);

    if (my.t.has_light) {
        my.t.new_light(my.t.mid_at,
                       my.t.monst->light_strength,
                       (LightQuality)my.t.monst->light_quality,
                       my.t.monst->light_col);
    }

    return (in);
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

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<const class World & > const my)
{_
    out << bits(my.t._is_wall);
    out << bits(my.t._is_gfx_large_shadow_caster);
    out << bits(my.t._is_light);
    out << bits(my.t._is_floor);
    out << bits(my.t._is_lava);
    out << bits(my.t._is_blood);
    out << bits(my.t._is_water);
    out << bits(my.t._is_deep_water);
    out << bits(my.t._is_corridor);
    out << bits(my.t._is_dirt);
    out << bits(my.t._is_grass);
    out << bits(my.t._is_soil);
    out << bits(my.t._is_gravel);
    out << bits(my.t._is_snow);
    out << bits(my.t._is_rock);
    out << bits(my.t._is_visited);
    out << bits(my.t.map_at);
    out << bits(my.t.map_wanted_at);
    out << bits(my.t.map_tile_over);
    out << bits(my.t.all_thing_ids_at);

    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(my.t.all_thing_ids_at, x, y)[z];
                if (id) {
                    auto t = thing_find(id);
                    verify(t);
                    out << bits(t);
                }
            }
        }
    }
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<class World &> my)
{_
    in >> bits(my.t._is_wall);
    in >> bits(my.t._is_gfx_large_shadow_caster);
    in >> bits(my.t._is_light);
    in >> bits(my.t._is_floor);
    in >> bits(my.t._is_lava);
    in >> bits(my.t._is_blood);
    in >> bits(my.t._is_water);
    in >> bits(my.t._is_deep_water);
    in >> bits(my.t._is_corridor);
    in >> bits(my.t._is_dirt);
    in >> bits(my.t._is_grass);
    in >> bits(my.t._is_soil);
    in >> bits(my.t._is_gravel);
    in >> bits(my.t._is_snow);
    in >> bits(my.t._is_rock);
    in >> bits(my.t._is_visited);
    in >> bits(my.t.map_at);
    in >> bits(my.t.map_wanted_at);
    in >> bits(my.t.map_tile_over);
    in >> bits(my.t.all_thing_ids_at);

    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(my.t.all_thing_ids_at, x, y)[z];
                if (id) {
                    auto t = new Thing();
                    in >> bits(t);
                    t->attach();
                }
            }
        }
    }
    return (in);
}

void World::dump (std::string pfx, std::ostream &out)
{
    out << pfx << "World {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    out << pfx << "map_at          " << map_at << std::endl;
    out << pfx << "map_wanted_at   " << map_wanted_at << std::endl;
    out << pfx << "map_tile_over   " << map_tile_over << std::endl;

    out << pfx << "all_things" << std::endl;
    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(all_thing_ids_at, x, y)[z];
                if (id) {
                    auto t = thing_find(id);
                    verify(t);
                    t->dump(pfx + "  ", out);
                }
            }
        }
    }

    pfx = old_pfx;
    out << pfx << "}" << std::endl;
}

std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my)
{_
    out << bits(my.t.fps_counter);
    out << bits(my.t.sound_volume);
    out << bits(my.t.music_volume);
    out << bits(my.t.vsync_enable);
    out << bits(my.t.full_screen);
    out << bits(my.t.video_pix_width);
    out << bits(my.t.video_pix_height);
    out << bits(my.t.video_gl_width);
    out << bits(my.t.video_gl_height);
    out << bits(my.t.video_w_h_ratio);
    out << bits(my.t.drawable_gl_width);
    out << bits(my.t.drawable_gl_height);
    out << bits(my.t.tile_gl_width);
    out << bits(my.t.tile_gl_height);
    out << bits(my.t.one_pixel_gl_width);
    out << bits(my.t.one_pixel_gl_height);
    out << bits(my.t.ascii_gl_width);
    out << bits(my.t.ascii_gl_height);
    out << bits(my.t.tile_pixel_width);
    out << bits(my.t.tile_pixel_height);
    out << bits(my.t.sdl_delay);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<Config &> my)
{_
    in >> bits(my.t.fps_counter);
    in >> bits(my.t.sound_volume);
    in >> bits(my.t.music_volume);
    in >> bits(my.t.vsync_enable);
    in >> bits(my.t.full_screen);
    in >> bits(my.t.video_pix_width);
    in >> bits(my.t.video_pix_height);
    in >> bits(my.t.video_gl_width);
    in >> bits(my.t.video_gl_height);
    in >> bits(my.t.video_w_h_ratio);
    in >> bits(my.t.drawable_gl_width);
    in >> bits(my.t.drawable_gl_height);
    in >> bits(my.t.tile_gl_width);
    in >> bits(my.t.tile_gl_height);
    in >> bits(my.t.one_pixel_gl_width);
    in >> bits(my.t.one_pixel_gl_height);
    in >> bits(my.t.ascii_gl_width);
    in >> bits(my.t.ascii_gl_height);
    in >> bits(my.t.tile_pixel_width);
    in >> bits(my.t.tile_pixel_height);
    in >> bits(my.t.sdl_delay);
    return (in);
}

void Config::dump (std::string pfx, std::ostream &out)
{_
    out << pfx << "Config {" << std::endl;
    auto old_pfx = pfx;
    pfx += "  ";

    out << pfx << "fps_counter        " << fps_counter << std::endl;
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

std::ostream& operator<<(std::ostream &out, 
                         Bits<const class Game & > const my)
{_
    out << bits(my.t.appdata);
    out << bits(my.t.saved_dir);
    out << bits(my.t.saved_file);
    out << bits(my.t.seed);
    out << bits(my.t.fps_count);
    out << bits(my.t.config);
    out << bits(my.t.world);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<class Game &> my)
{_
    in >> bits(my.t.appdata);
    in >> bits(my.t.saved_dir);
    in >> bits(my.t.saved_file);
    in >> bits(my.t.seed);
    in >> bits(my.t.fps_count);
    in >> bits(my.t.config);
    in >> bits(my.t.world);
    return (in);
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
