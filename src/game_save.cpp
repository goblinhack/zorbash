//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_dungeon.h"
#include <sstream>
#include "minilzo.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_thing.h"
#include "my_alloc.h"

extern bool game_load_headers_only;
bool game_save_config_only;

std::ostream& operator<<(std::ostream &out, Bits<AgeMapp & > const my)
{
    out << bits(my.t->val);
    return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<Dmapp & > const my)
{
    out << bits(my.t->val);
    return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<Monstp & > const my)
{
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
    /* float       */ out << bits(my.t->rot);
    /* float       */ out << bits(my.t->submerged_offset);
    /* fpoint      */ out << bits(my.t->interpolated_mid_at);
    /* fpoint      */ out << bits(my.t->lunge_to);
    /* int         */ out << bits(my.t->bounce_count);
    /* int         */ out << bits(my.t->gold);
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
    /* int         */ out << bits(my.t->stats20);
    /* int         */ out << bits(my.t->stats_attack);
    /* int         */ out << bits(my.t->stats_attack_max);
    /* int         */ out << bits(my.t->stats_attack_rate_tenths);
    /* int         */ out << bits(my.t->stats_attacked_rate_tenths);
    /* int         */ out << bits(my.t->stats_defence);
    /* int         */ out << bits(my.t->stats_defence_max);
    /* int         */ out << bits(my.t->stats_health);
    /* int         */ out << bits(my.t->stats_health_max);
    /* std::list<uint32_t> */ out << bits(my.t->carrying);
    /* std::string */ out << bits(my.t->msg);
    /* timestamp_t */ out << bits(my.t->timestamp_ai_next);
    /* timestamp_t */ out << bits(my.t->timestamp_born);
    /* timestamp_t */ out << bits(my.t->timestamp_bounce_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_bounce_end);
    /* timestamp_t */ out << bits(my.t->timestamp_collision);
    /* timestamp_t */ out << bits(my.t->timestamp_fadeup_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_fadeup_end);
    /* timestamp_t */ out << bits(my.t->timestamp_flip_start);
    /* timestamp_t */ out << bits(my.t->timestamp_hunger_tick);
    /* timestamp_t */ out << bits(my.t->timestamp_last_attack);
    /* timestamp_t */ out << bits(my.t->timestamp_last_attacked);
    /* timestamp_t */ out << bits(my.t->timestamp_lunge_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_lunge_end);
    /* timestamp_t */ out << bits(my.t->timestamp_move_begin);
    /* timestamp_t */ out << bits(my.t->timestamp_move_end);
    /* uint32_t    */ out << bits(my.t->owner_id);
    /* uint32_t    */ out << bits(my.t->tick);
    /* uint32_t    */ out << bits(my.t->weapon_id);
    /* uint32_t    */ out << bits(my.t->weapon_id_carry_anim);
    /* uint32_t    */ out << bits(my.t->weapon_id_use_anim);
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
{
    std::string name(tp_id_map[my.t->tp_id - 1]->name);
    out << bits(name);

    bool monst = (my.t->monst != nullptr);
    out << bits(monst);
    if (monst) {
        out << bits(my.t->monst);
    }

    out << bits(my.t->last_attached);
    out << bits(my.t->br);
    out << bits(my.t->last_blit_br);
    out << bits(my.t->last_blit_tl);
    out << bits(my.t->last_mid_at);
    out << bits(my.t->mid_at);
    out << bits(my.t->tl);
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
    /* uint32_t */ bits32 |= my.t->is_bloodied        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_bouncing        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_dead            << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_facing_left     << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_fadeup          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_hidden          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_hungry          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_move_done       << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_moving          << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_open            << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_pending_gc      << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_sleeping        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_starving        << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_submerged       << shift; shift++;
    /* uint32_t */ bits32 |= my.t->is_waiting_to_move << shift; shift++;
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
                         Bits<const class World & > const my)
{_
    out << bits(my.t.timestamp_dungeon_created);
    out << bits(my.t.timestamp_dungeon_saved);
    out << bits(my.t._is_blood);
    out << bits(my.t._is_corridor);
    out << bits(my.t._is_deep_water);
    out << bits(my.t._is_dirt);
    out << bits(my.t._is_floor);
    out << bits(my.t._is_gfx_large_shadow_caster);
    out << bits(my.t._is_lava);
    out << bits(my.t._is_rock);
    out << bits(my.t._is_visited);
    out << bits(my.t._is_dungeon);
    out << bits(my.t._is_wall);
    out << bits(my.t._is_water);
    out << bits(my.t.all_thing_ids_at);
    out << bits(my.t.cursor_at);
    out << bits(my.t.cursor_at_old);
    out << bits(my.t.cursor_needs_update);
    out << bits(my.t.cursor_found);
    out << bits(my.t.map_at);
    out << bits(my.t.map_follow_player);
    out << bits(my.t.map_wanted_at);
    out << bits(my.t.minimap_valid);
    out << bits(my.t.mouse);
    out << bits(my.t.mouse_old);
    out << bits(my.t.next_thing_id);

    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(my.t.all_thing_ids_at, x, y, z);
                if (id) {
                    const Thingp t = thing_find(id);
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
    out << bits(my.t.arcade_mode);
    out << bits(my.t.sound_volume);
    out << bits(my.t.music_volume);
    out << bits(my.t.fullscreen);
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
    out << bits(my.t.key_up);
    out << bits(my.t.key_down);
    out << bits(my.t.key_left);
    out << bits(my.t.key_right);
    out << bits(my.t.key_attack);
    out << bits(my.t.key_wait);
    out << bits(my.t.key_load);
    out << bits(my.t.key_save);
    out << bits(my.t.key_zoom_in);
    out << bits(my.t.key_zoom_out);
    out << bits(my.t.key_pause);
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
    out << bits(my.t.seed);
    out << bits(my.t.fps_value);
    out << bits(my.t.tick_current);
    out << bits(my.t.tick_completed);
    out << bits(my.t.things_are_moving);
    out << bits(my.t.started);
    out << bits(my.t.config);
    out << bits(my.t.world);
    out << bits(wid_minicon_serialize());
    out << bits(wid_console_serialize());

    return (out);
}

bool Game::save (std::string file_to_save)
{_
    std::stringstream s(std::ios::in | std::ios::out | std::ios::binary);

    game->world.timestamp_dungeon_saved = time_get_time_ms();
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
        CON("DUNGEON: saved as %s, compressed from %lu to %lu bytes",
            file_to_save.c_str(),
            (unsigned long) uncompressed_len,
            (unsigned long) compressed_len);
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

    if (slot >= MAX_SAVE_SLOTS) {
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
{
    if (wid_save) {
        delete wid_save;
        wid_save = nullptr;
    }
    game->hard_unpause();
}

uint8_t wid_save_key_up (Widp w, const struct SDL_KEYSYM *key)
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
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
                    case '9': {
                        int slot = c - '0';
                        game->save(slot);
                        wid_save_destroy();
                        return (true);
                    }
                    case SDLK_ESCAPE: {
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
{
    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
                    case CONSOLE_KEY1:
                    case CONSOLE_KEY2:
                    case CONSOLE_KEY3:
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
{
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
    point tl = {m - WID_POPUP_WIDTH_WIDE / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDE / 2, ITEMBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    wid_save = new WidPopup(tl, br, tile_find_mand("save"), "ui_popup_wide");
    wid_set_on_key_up(wid_save->wid_popup_container, wid_save_key_up);
    wid_set_on_key_down(wid_save->wid_popup_container, wid_save_key_down);

    game_load_headers_only = true;

    wid_save->log("Choose a save slot. %%fg=red$ESC%%fg=reset$ to cancel");

    int y_at = 2;
    for (auto slot = 0; slot < MAX_SAVE_SLOTS; slot++) {
        Game tmp;
        auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);
        auto p = wid_save->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save slot");
        point tl = {0, y_at};
        point br = {width - 2, y_at + 2};

        std::string s = std::to_string(slot) + " ";
        if (!load(tmp_file, tmp)) {
            s += "<empty>";
            wid_set_style(w, WID_STYLE_RED);
        } else {
            s += tmp.save_meta;
            wid_set_style(w, WID_STYLE_GREEN);
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
