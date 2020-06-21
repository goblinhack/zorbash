//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "minilzo.h"
#include "my_game.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_thing.h"
#include "my_alloc.h"

extern bool game_load_headers_only;
bool game_save_config_only;
int GAME_SAVE_MARKER_EOL = 123456;

std::ostream& operator<<(std::ostream &out, Bits<AgeMapp & > const my)
{_
    out << bits(my.t->val);
    return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<Dmapp & > const my)
{_
    out << bits(my.t->val);
    return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<Monstp & > const my)
{_
    bool age_map = (my.t->age_map != nullptr);
    out << bits(age_map);
    if (age_map) {
        out << bits(my.t->age_map);
    }

    bool dmap_scent = (my.t->dmap_scent != nullptr);
    out << bits(dmap_scent);
    if (dmap_scent) {
        out << bits(my.t->dmap_scent);
    }

    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    /* color       */ out << bits(my.t->light_col);
    /* float       */ out << bits(my.t->bounce_fade);
    /* float       */ out << bits(my.t->bounce_height);
    /* float       */ out << bits(my.t->fadeup_fade);
    /* float       */ out << bits(my.t->fadeup_height);
    /* float       */ out << bits(my.t->fall_height);
    /* float       */ out << bits(my.t->wobble);
    /* fpoint      */ out << bits(my.t->lunge_to);
    /* int         */ out << bits(my.t->bounce_count);
    /* int         */ out << bits(my.t->gold);
    /* int         */ out << bits(my.t->lifespan);
    /* int         */ out << bits(my.t->light_quality);
    /* int         */ out << bits(my.t->light_strength);
    /* int         */ out << bits(my.t->owned_count);
    /* int         */ out << bits(my.t->stats01);
    /* int         */ out << bits(my.t->stats02);
    /* int         */ out << bits(my.t->stats03);
    /* int         */ out << bits(my.t->stats04);
    /* int         */ out << bits(my.t->stats05);
    /* int         */ out << bits(my.t->stats06);
    /* int         */ out << bits(my.t->stats07);
    /* int         */ out << bits(my.t->stats08);
    /* int         */ out << bits(my.t->stats09);
    /* int         */ out << bits(my.t->stats10);
    /* int         */ out << bits(my.t->stats11);
    /* int         */ out << bits(my.t->stats12);
    /* int         */ out << bits(my.t->stats13);
    /* int         */ out << bits(my.t->stats14);
    /* int         */ out << bits(my.t->stats15);
    /* int         */ out << bits(my.t->stats16);
    /* int         */ out << bits(my.t->stats17);
    /* int         */ out << bits(my.t->stats18);
    /* int         */ out << bits(my.t->stats19);
    /* int         */ out << bits(my.t->stats_defence);
    /* int         */ out << bits(my.t->stats_defence_max);
    /* int         */ out << bits(my.t->stats_health);
    /* int         */ out << bits(my.t->stats_health_max);
    /* int         */ out << bits(my.t->stats_strength);
    /* int         */ out << bits(my.t->tick_rate_tenths);
    /* point       */ out << bits(my.t->level_changed_at);
    /* point       */ out << bits(my.t->wander_target);
    /* std::list<uint32_t> */   out << bits(my.t->carrying);
    /* std::array<uint32_t> */  out << bits(my.t->actionbar_id);
    /* std::vector<point> */    out << bits(my.t->move_path);
    /* std::vector<uint32_t> */ out << bits(my.t->enemies);
    /* std::string */ out << bits(my.t->msg);
    /* timestamp_t */ out << bits(my.t->tick_last_did_something);
    /* timestamp_t */ out << bits(my.t->timestamp_fall_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_born);
    /* timestamp_t */ out << bits(my.t->timestamp_bounce_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_bounce_end);
    /* timestamp_t */ out << bits(my.t->timestamp_fall_end);
    /* timestamp_t */ out << bits(my.t->timestamp_fadeup_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_fadeup_end);
    /* timestamp_t */ out << bits(my.t->timestamp_flip_start);
    /* timestamp_t */ out << bits(my.t->timestamp_hunger_tick);
    /* timestamp_t */ out << bits(my.t->timestamp_last_tick);
    /* timestamp_t */ out << bits(my.t->timestamp_last_ticked);
    /* timestamp_t */ out << bits(my.t->timestamp_lunge_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_lunge_end);
    /* timestamp_t */ out << bits(my.t->timestamp_move_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_move_end);
    /* uint32_t    */ out << bits(my.t->owner_id);
    /* uint32_t    */ out << bits(my.t->tick);
    /* uint32_t    */ out << bits(my.t->weapon_id);
    /* uint32_t    */ out << bits(my.t->weapon_id_carry_anim);
    /* uint32_t    */ out << bits(my.t->weapon_id_use_anim);
    /* uint32_t    */ out << bits(my.t->on_fire_id_anim);
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    return (out);
}

std::ostream& operator<< (std::ostream &out, Bits<const Thingp & > const my)
{_
    const std::string name(tp_id_map[my.t->tp_id - 1]->name());
    out << bits(name);

    bool monst = (my.t->monstp != nullptr);
    out << bits(monst);
    if (monst) {
        out << bits(my.t->monstp);
    }

    out << bits(my.t->last_attached);
    out << bits(my.t->mid_at);
    out << bits(my.t->last_mid_at);
    out << bits(my.t->id);
    out << bits(my.t->tile_curr);
    out << bits(my.t->timestamp_next_frame);

    uint8_t dir = my.t->dir; out << bits(dir);

    uint32_t bits32 = 0;
    int shift = 0;
    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    /* uint32_t */ bits32 |= my.t->has_ever_moved     << shift; shift++;
    /* uint32_t */ bits32 |= my.t->has_light          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_attached        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_being_destroyed << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_blitted         << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_bouncing        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_falling         << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_dead            << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_facing_left     << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_fadeup          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_hidden          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_hungry          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_in_lava         << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_moving          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_open            << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_resurrected     << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_resurrecting    << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_sleeping        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_starving        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_tick_done       << shift; shift++;
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////
    if (shift >= (int)(sizeof(bits32) * 8)) {
        ERR("ran out of bits in serialization");
    }
    out << bits(bits32);

    return (out);
}

std::ostream& operator<<(std::ostream &out,
                         Bits<Level* & > const my)
{_
    my.t->log("save");
    out << bits(my.t->timestamp_dungeon_created);
    timestamp_t timestamp_dungeon_saved = time_get_time_ms();
    out << bits(timestamp_dungeon_saved);

    /* _fade_in_map */         out << bits(my.t->_fade_in_map);
    /* _heatmap */             out << bits(my.t->_heatmap);
    /* _is_blood */            out << bits(my.t->_is_blood);
    /* _is_corpse */           out << bits(my.t->_is_corpse);
    /* _is_corridor */         out << bits(my.t->_is_corridor);
    /* _is_deep_water */       out << bits(my.t->_is_deep_water);
    /* _is_dirt */             out << bits(my.t->_is_dirt);
    /* _is_door */             out << bits(my.t->_is_door);
    /* _is_dungeon */          out << bits(my.t->_is_dungeon);
    /* _is_entrance */         out << bits(my.t->_is_entrance);
    /* _is_exit */             out << bits(my.t->_is_exit);
    /* _is_fire */             out << bits(my.t->_is_fire);
    /* _is_floor */            out << bits(my.t->_is_floor);
    /* _is_food */             out << bits(my.t->_is_food);
    /* _is_gold */             out << bits(my.t->_is_gold);
    /* _is_hazard */           out << bits(my.t->_is_hazard);
    /* _is_key */              out << bits(my.t->_is_key);
    /* _is_lava */             out << bits(my.t->_is_lava);
    /* _is_light_blocker */    out << bits(my.t->_is_light_blocker);
    /* _is_monst */            out << bits(my.t->_is_monst);
    /* _is_rock */             out << bits(my.t->_is_rock);
    /* _is_secret_door */      out << bits(my.t->_is_secret_door);
    /* _is_smoke */            out << bits(my.t->_is_smoke);
    /* _is_treasure */         out << bits(my.t->_is_treasure);
    /* _is_visited */          out << bits(my.t->_is_visited);
    /* _is_wall */             out << bits(my.t->_is_wall);
    /* _is_water */            out << bits(my.t->_is_water);
    /* all_thing_ids_at */     out << bits(my.t->all_thing_ids_at);
    /* cursor_at */            out << bits(my.t->cursor_at);
    /* cursor_at_old */        out << bits(my.t->cursor_at_old);
    /* cursor_found */         out << bits(my.t->cursor_found);
    /* cursor_needs_update */  out << bits(my.t->cursor_needs_update);
    /* map_at */               out << bits(my.t->map_at);
    /* map_follow_player */    out << bits(my.t->map_follow_player);
    /* map_wanted_at */        out << bits(my.t->map_wanted_at);
    /* minimap_valid */        out << bits(my.t->minimap_valid);
    /* heatmap_valid */        out << bits(my.t->heatmap_valid);
    /* mouse */                out << bits(my.t->mouse);
    /* mouse_old */            out << bits(my.t->mouse_old);
    /* seed */                 out << bits(my.t->seed);
    /* world_at */             out << bits(my.t->world_at);

    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_HEIGHT; ++y) {
            for (auto slot = 0; slot < MAP_SLOTS; ++slot) {
                auto id = get(my.t->all_thing_ids_at, x, y, slot);
                if (id.ok()) {
                    const Thingp t = my.t->thing_find(id);
#ifdef ENABLE_THING_ID_LOGS
                    t->log("save");
#endif
                    out << bits(t);
                }
            }
        }
    }
    return (out);
}

std::ostream& operator<<(std::ostream &out,
                         Bits<const class World & > const my)
{_
    for (auto x = 0; x < LEVELS_ACROSS; ++x) {
        for (auto y = 0; y < LEVELS_DOWN; ++y) {
            for (auto z = 0; z < LEVELS_DEEP; ++z) {
                point3d p(x, y, z);
                bool exists;
                auto l = get(my.t.levels, x, y, z);
                if (l) {
                    exists = true;
                    CON("DUNGEON: save level %d,%d,%d", p.x, p.y, p.z);
                    out << bits(p);
                    out << bits(exists);
                    out << bits(l);
                    auto eol = GAME_SAVE_MARKER_EOL;
                    out << bits(eol);
                    CON("DUNGEON: saved level %d,%d,%d", p.x, p.y, p.z);
                } else {
                    exists = false;
                    out << bits(p);
                    out << bits(exists);
                }
            }
        }
    }
    return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<const Config & > const my)
{_
    out << bits(my.t.fps_counter);
    out << bits(my.t.gfx_inverted);
    out << bits(my.t.gfx_minimap);
    out << bits(my.t.gfx_show_hidden);
    out << bits(my.t.gfx_lights);
    out << bits(my.t.gfx_zoom);
    out << bits(my.t.gfx_vsync_enable);
    out << bits(my.t.debug_mode);
    out << bits(my.t.sound_volume);
    out << bits(my.t.music_volume);
    out << bits(my.t.fullscreen);
    out << bits(my.t.allow_highdpi);
    out << bits(my.t.inner_pix_width);
    out << bits(my.t.inner_pix_height);
    out << bits(my.t.outer_pix_width);
    out << bits(my.t.outer_pix_height);
    out << bits(my.t.scale_pix_width);
    out << bits(my.t.scale_pix_height);
    out << bits(my.t.video_w_h_ratio);
    out << bits(my.t.tile_pix_width);
    out << bits(my.t.tile_pix_height);
    out << bits(my.t.one_pixel_width);
    out << bits(my.t.one_pixel_height);
    out << bits(my.t.ascii_gl_width);
    out << bits(my.t.ascii_gl_height);
    out << bits(my.t.tile_pixel_width);
    out << bits(my.t.tile_pixel_height);
    out << bits(my.t.sdl_delay);
    out << bits(my.t.key_move_up);
    out << bits(my.t.key_move_down);
    out << bits(my.t.key_move_left);
    out << bits(my.t.key_move_right);
    out << bits(my.t.key_map_up);
    out << bits(my.t.key_map_down);
    out << bits(my.t.key_map_left);
    out << bits(my.t.key_map_right);
    out << bits(my.t.key_attack);
    out << bits(my.t.key_wait);
    out << bits(my.t.key_load);
    out << bits(my.t.key_save);
    out << bits(my.t.key_zoom_in);
    out << bits(my.t.key_zoom_out);
    out << bits(my.t.key_pause);
    out << bits(my.t.key_help);
    out << bits(my.t.key_quit);
    return (out);
}

std::ostream& operator<<(std::ostream &out,
                         Bits<const class Game & > const my)
{_
    out << bits(my.t.version);
    out << bits(my.t.save_slot);
    out << bits(my.t.save_meta);
    out << bits(my.t.save_file);
    out << bits(my.t.appdata);
    out << bits(my.t.saved_dir);
    out << bits(my.t.config);
    out << bits(my.t.world);

    out << bits(my.t.current_level);
    out << bits(my.t.fps_value);
    out << bits(my.t.hard_paused);
    out << bits(my.t.last_pause);
    out << bits(my.t.seed);
    out << bits(my.t.soft_paused);
    out << bits(my.t.started);
    out << bits(my.t.things_are_moving);
    out << bits(my.t.tick_completed);
    out << bits(my.t.tick_current);

    out << bits(wid_minicon_serialize());
    out << bits(wid_console_serialize());

    return (out);
}

bool Game::save (std::string file_to_save)
{_
    std::stringstream s(std::ios::in | std::ios::out | std::ios::binary);

    const class Game &c = *this;
    s << bits(c);

    //
    // Get the pre compress buffer
    //
    auto data = s.str();
    s.seekg(0, std::ios::end);
    lzo_uint uncompressed_len = s.tellg();
    s.seekg(0, std::ios::beg);

    HEAP_ALLOC(uncompressed, uncompressed_len);
    HEAP_ALLOC(compressed, uncompressed_len);
    memcpy(uncompressed, data.c_str(), uncompressed_len);

//    std::cout << "before compression ";
//    (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);

    if (lzo_init() != LZO_E_OK) {
        ERR("LZO init fail: enable '-DLZO_DEBUG' for diagnostics)");
    }

    HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

    lzo_uint compressed_len = 0;
    int r = lzo1x_1_compress((lzo_bytep)uncompressed, uncompressed_len,
                             (lzo_bytep)compressed, &compressed_len, wrkmem);
    if (r == LZO_E_OK) {
        CON("DUNGEON: saved as %s, compress %luMb -> %luMb",
            file_to_save.c_str(),
            (unsigned long) uncompressed_len / (1024 * 1024),
            (unsigned long) compressed_len / (1024 * 1024));
    } else {
        ERR("LZO internal error - compression failed: %d", r);
        return (false);
    }

    //
    // Dump the post compress buffer
    //
//    std::cout << "after compression ";
//    (void) hexdump((const unsigned char *)compressed, compressed_len);

    //
    // Save the post compress buffer
    //
    auto ofile = fopen(file_to_save.c_str(), "wb");
    fwrite((char*) &uncompressed_len, sizeof(uncompressed_len), 1, ofile);
    fwrite(compressed, compressed_len, 1, ofile);
    fclose(ofile);

    free(uncompressed);
    free(compressed);
    free(wrkmem);

    return (true);
}

void
Game::save (void)
{_
    LOG("-");
    CON("DUNGEON: saving %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    save(save_file);

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: saved %s, seed %d", save_file.c_str(), seed);
    LOG("-");
}

void
Game::save (int slot)
{_
    if (slot < 0) {
        return;
    }

    if (slot >= UI_WID_SAVE_SLOTS) {
        return;
    }

    auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

    LOG("-");
    CON("DUNGEON: saving %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    save(save_file);

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: saved %s, seed %d", save_file.c_str(), seed);
    LOG("-");
}

void
Game::save_config (void)
{_
    auto filename = saved_dir + "config";
    std::ofstream out(filename, std::ios::binary);
    const Config &c = game->config;
    out << bits(c);
    game->config.log("WROTE:");
}

static WidPopup *wid_save;

static void wid_save_destroy (void)
{_
    delete wid_save;
    wid_save = nullptr;
    game->hard_unpause();
}

uint8_t wid_save_key_up (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case UI_CONSOLE_KEY1:
                    case UI_CONSOLE_KEY2:
                    case UI_CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9': {_
                        int slot = c - '0';
                        game->save(slot);
                        wid_save_destroy();
                        return (true);
                    }
                    case SDLK_ESCAPE: {_
                        CON("PLAYER: save game cancelled");
                        wid_save_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t wid_save_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {_
                auto c = wid_event_to_char(key);
                switch (c) {
                    case UI_CONSOLE_KEY1:
                    case UI_CONSOLE_KEY2:
                    case UI_CONSOLE_KEY3:
                        //
                        // Magic keys we use to toggle the console.
                        //
                        return (false);
                }
            }
        }
    }

    return (true);
}

uint8_t wid_save_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    auto slot = wid_get_int_context(w);
    game->save(slot);
    wid_save_destroy();
    return (true);
}

void Game::save_select (void)
{_
    if (wid_save) {
        return;
    }
    game->hard_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = make_point(m - UI_WID_POPUP_WIDTH_WIDE / 2, UI_MINICON_VIS_HEIGHT + 2);
    point br = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2, UI_ACTIONBAR_TL_Y - 2);
    auto width = br.x - tl.x;

    wid_save = new WidPopup(tl, br, tile_find_mand("save"), "ui_popup_wide");
    wid_set_on_key_up(wid_save->wid_popup_container, wid_save_key_up);
    wid_set_on_key_down(wid_save->wid_popup_container, wid_save_key_down);

    game_load_headers_only = true;

    wid_save->log("Choose a save slot. %%fg=red$ESC%%fg=reset$ to cancel");

    int y_at = 2;
    for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
        Game tmp;
        auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);
        auto p = wid_save->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 2, y_at + 2);

        std::string s = std::to_string(slot) + " ";
        if (!load(tmp_file, tmp)) {
            s += "<empty>";
            wid_set_style(w, UI_WID_STYLE_RED);
        } else {
            s += tmp.save_meta;
            wid_set_style(w, UI_WID_STYLE_GREEN);
        }
        wid_set_on_mouse_up(w, wid_save_mouse_up);
        wid_set_int_context(w, slot);

        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        y_at += 3;
    }
    game_load_headers_only = false;
    wid_update(wid_save->wid_text_area->wid_text_area);
}
