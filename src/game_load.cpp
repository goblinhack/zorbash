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
#include "my_game_error.h"
#include "my_game_status.h"
#include "my_thing.h"

static timestamp_t old_timestamp_dungeon_created;
static timestamp_t new_timestamp_dungeon_created;
static timestamp_t ts_tmp;
static std::string game_load_error;
bool game_load_headers_only;

//
// Save timestamps as a delta we can restore.
//
static timestamp_t load_timestamp (timestamp_t ts)
{
    if (!ts) {
        return (0);
    }
    return (ts - old_timestamp_dungeon_created +
            new_timestamp_dungeon_created);
}

std::istream& operator>>(std::istream &in, Bits<AgeMapp &> my)
{
    in >> bits(my.t->val);
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<Dmapp &> my)
{
    in >> bits(my.t->val);
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<Monstp & > my)
{
    bool age_map;
    in >> bits(age_map);
    if (age_map) {
        my.t->age_map = new AgeMap();
        newptr(my.t->age_map, "Dmap age loaded");
        in >> bits(my.t->age_map);
    }

    bool dmap_scent;
    in >> bits(dmap_scent);
    if (dmap_scent) {
        my.t->dmap_scent = new Dmap();
        newptr(my.t->dmap_scent, "Dmap scent loaded");
        in >> bits(my.t->dmap_scent);
    }

    in >> bits(my.t->tick);
    in >> bits(my.t->bounce_count);
    in >> bits(my.t->bounce_fade);
    in >> bits(my.t->bounce_height);
    in >> bits(my.t->lunge_to);
    in >> bits(my.t->carrying);
    in >> bits(my.t->gold);
    in >> bits(my.t->interpolated_mid_at);
    in >> bits(my.t->light_col);
    in >> bits(my.t->light_quality);
    in >> bits(my.t->light_strength);
    in >> bits(my.t->owned_count);
    in >> bits(my.t->owner_id);
    in >> bits(my.t->rot);
    in >> bits(my.t->stats_attack);
    in >> bits(my.t->stats_attack_max);
    in >> bits(my.t->stats_attack_rate_tenths);
    in >> bits(my.t->stats_attacked_rate_tenths);
    in >> bits(my.t->stats_defence);
    in >> bits(my.t->stats_defence_max);
    in >> bits(my.t->stats_health);
    in >> bits(my.t->stats_health_max);
    in >> bits(my.t->submerged_offset);
    in >> bits(my.t->weapon_id);
    in >> bits(my.t->weapon_id_carry_anim);
    in >> bits(my.t->weapon_id_use_anim);

    in >> bits(ts_tmp); my.t->timestamp_lunge_begin    = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_lunge_end      = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_bounce_begin   = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_bounce_end     = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_last_attacked  = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_last_attack    = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_flip_start     = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_move_begin     = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_move_end       = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_born           = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_hunger_tick    = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_ai_next        = load_timestamp(ts_tmp);
    in >> bits(ts_tmp); my.t->timestamp_collision      = load_timestamp(ts_tmp);

    return (in);
}

std::istream& operator>> (std::istream &in, Bits<Thingp &> my)
{
    std::string name;
    in >> bits(name);
    auto tpp = tp_find(name);
    if (!tpp) {
        DIE("could not find thing template [%s]", name.c_str());
    }

    my.t->tp_id = tpp->id;

    uint32_t bits32;
    bool monst = (my.t->monst != nullptr);
    in >> bits(monst);
    if (monst) {
        my.t->new_monst();
        in >> bits(my.t->monst);
    }

    in >> bits(my.t->last_attached);
    in >> bits(my.t->br);
    in >> bits(my.t->last_blit_br);
    in >> bits(my.t->last_blit_tl);
    in >> bits(my.t->last_mid_at);
    in >> bits(my.t->mid_at);
    in >> bits(my.t->tl);
    in >> bits(my.t->id); if (!my.t->id) { DIE("loaded a thing with no ID"); }
    in >> bits(my.t->tile_curr);
    in >> bits(ts_tmp); my.t->timestamp_next_frame = load_timestamp(ts_tmp);

    uint8_t dir; in >> dir; my.t->dir = dir;

    in >> bits(bits32);
    int shift = 0;
    my.t->has_ever_moved     = (bits32 >> shift) & 1; shift++;
    my.t->has_light          = (bits32 >> shift) & 1; shift++;
    my.t->is_attached        = (bits32 >> shift) & 1; shift++;
    my.t->is_being_destroyed = (bits32 >> shift) & 1; shift++;
    my.t->is_bloodied        = (bits32 >> shift) & 1; shift++;
    my.t->is_bouncing        = (bits32 >> shift) & 1; shift++;
    my.t->is_dead            = (bits32 >> shift) & 1; shift++;
    my.t->is_facing_left     = (bits32 >> shift) & 1; shift++;
    my.t->is_hidden          = (bits32 >> shift) & 1; shift++;
    my.t->is_hungry          = (bits32 >> shift) & 1; shift++;
    my.t->is_moving          = (bits32 >> shift) & 1; shift++;
    my.t->is_open            = (bits32 >> shift) & 1; shift++;
    my.t->is_sleeping        = (bits32 >> shift) & 1; shift++;
    my.t->is_starving        = (bits32 >> shift) & 1; shift++;
    my.t->is_submerged       = (bits32 >> shift) & 1; shift++;
    my.t->is_waiting_to_move = (bits32 >> shift) & 1; shift++;
    my.t->is_pending_gc      = (bits32 >> shift) & 1; shift++;
    my.t->is_blitted         = (bits32 >> shift) & 1; shift++;

    if (my.t->has_light) {
        my.t->new_light(my.t->mid_at,
                        my.t->monst->light_strength,
                        (LightQuality)my.t->monst->light_quality,
                        my.t->monst->light_col);
    }

    return (in);
}

std::istream& operator>>(std::istream &in, Bits<class World &> my)
{_
    my.t.player = nullptr;
    my.t.cursor = nullptr;
    my.t.all_thing_ptrs = {};
    my.t.all_thing_ids_at = {};

    in >> bits(my.t.timestamp_dungeon_created); old_timestamp_dungeon_created = my.t.timestamp_dungeon_created;
    in >> bits(my.t.timestamp_dungeon_saved);
    auto dungeon_age = game->world.timestamp_dungeon_saved -
                       game->world.timestamp_dungeon_created;
    new_timestamp_dungeon_created = time_get_time_ms() - dungeon_age;
    my.t.timestamp_dungeon_created = new_timestamp_dungeon_created;
    my.t.timestamp_dungeon_saved = new_timestamp_dungeon_created + dungeon_age;

    in >> bits(my.t._is_blood);
    in >> bits(my.t._is_corridor);
    in >> bits(my.t._is_deep_water);
    in >> bits(my.t._is_dirt);
    in >> bits(my.t._is_floor);
    in >> bits(my.t._is_gfx_large_shadow_caster);
    in >> bits(my.t._is_lava);
    in >> bits(my.t._is_rock);
    in >> bits(my.t._is_visited);
    in >> bits(my.t._is_dungeon);
    in >> bits(my.t._is_wall);
    in >> bits(my.t._is_water);
    in >> bits(my.t.all_thing_ids_at);
    in >> bits(my.t.cursor_at);
    in >> bits(my.t.cursor_at_old);
    in >> bits(my.t.cursor_needs_update);
    in >> bits(my.t.cursor_found);
    in >> bits(my.t.map_at);
    in >> bits(my.t.map_follow_player);
    in >> bits(my.t.map_wanted_at);
    in >> bits(my.t.minimap_valid);
    in >> bits(my.t.mouse);
    in >> bits(my.t.mouse_old);
    in >> bits(my.t.next_thing_id);

    my.t.minimap_valid = false;
    my.t.cursor_needs_update = true;
    my.t.map_follow_player = true;

    for (auto x = 0; x < MAP_WIDTH; ++x) {
        for (auto y = 0; y < MAP_WIDTH; ++y) {
            for (auto z = 0; z < MAP_SLOTS; ++z) {
                auto id = get(my.t.all_thing_ids_at, x, y, z);
                if (id) {
#ifdef ENABLE_THING_ID_LOGS
                    auto o = my.t.test_thing_ptr(id);
                    if (o) {
                        o->die("thing already exists for ID %08X", id);
                    }
#endif
                    auto t = new Thing();
                    in >> bits(t);
#ifdef ENABLE_THING_ID_LOGS
                    t->log("load");
#endif
                    t->reinit();
                }
            }
        }
    }
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<Config &> my)
{_
    in >> bits(my.t.fps_counter);
    in >> bits(my.t.gfx_inverted);
    in >> bits(my.t.gfx_minimap);
    in >> bits(my.t.gfx_show_hidden);
    in >> bits(my.t.gfx_lights);
    in >> bits(my.t.gfx_zoom);
    in >> bits(my.t.debug_mode);
    in >> bits(my.t.arcade_mode);
    in >> bits(my.t.sound_volume);
    in >> bits(my.t.music_volume);
    in >> bits(my.t.vsync_enable);
    in >> bits(my.t.fullscreen);
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

std::istream& operator>>(std::istream &in, Bits<class Game &> my)
{_
    in >> bits(my.t.version);

    if (my.t.version != VERSION) {
        game_load_error = 
          "bad version '" VERSION "' v '" + my.t.version + "'";
        return (in);
    }

    in >> bits(my.t.save_slot);
    in >> bits(my.t.save_meta);
    in >> bits(my.t.save_file);
    if (game_load_headers_only) {
        return (in);
    }

    in >> bits(my.t.appdata);
    in >> bits(my.t.saved_dir);
    in >> bits(my.t.seed);
    in >> bits(my.t.fps_value);
    in >> bits(my.t.tick_current);
    in >> bits(my.t.tick_completed);
    in >> bits(my.t.things_are_moving);
    in >> bits(my.t.started);
    in >> bits(my.t.config);
    in >> bits(my.t.world);
    std::vector<std::wstring> s; in >> bits(s); wid_minicon_deserialize(s);
                                 in >> bits(s); wid_console_deserialize(s);
    return (in);
}

// binary mode is only for switching off newline translation
// ios::ate, open at end
std::vector<char> read_file (const std::string filename)
{_
    std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
    ifs.unsetf(std::ios::skipws);

    std::ifstream::pos_type sz = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> bytes(sz);
    ifs.read(bytes.data(), sz);

    return bytes;
}

static std::vector<char> read_lzo_file (const std::string filename,
                                        lzo_uint *uncompressed_sz)
{_
    std::ifstream ifs(filename,
                      std::ios::in | std::ios::binary | std::ios::ate);
    // tellg is not ideal, look into <filesystem> post mojave
    std::ifstream::pos_type sz = ifs.tellg();
    if (sz < 0) {
        return (std::vector<char> ());
    }

    ifs.seekg(0, std::ios::beg);
    ifs.unsetf(std::ios::skipws);
    ifs.read((char*) uncompressed_sz, sizeof(lzo_uint));

    sz -= (int) sizeof(lzo_uint);
    std::vector<char> bytes(sz);
    ifs.read(bytes.data(), sz);

    return (bytes);
}

bool
Game::load (std::string file_to_load, class Game &target)
{_
    //
    // Read to a vector and then copy to a C buffer for LZO to use
    //
    lzo_uint uncompressed_len;
    auto vec = read_lzo_file(file_to_load, &uncompressed_len);
    if (vec.size() <= 0) {
        if (!game_load_headers_only) {
            wid_error("load error, empty file?");
        }
        return (false);
    }
    auto data = vec.data();
    lzo_uint compressed_len = vec.size();

    HEAP_ALLOC(compressed, compressed_len);
    HEAP_ALLOC(uncompressed, uncompressed_len);
    memcpy(compressed, data, compressed_len);

    lzo_uint new_len = 0;
    int r = lzo1x_decompress((lzo_bytep)compressed, compressed_len, 
                             (lzo_bytep)uncompressed, &new_len, NULL);
    if (r == LZO_E_OK && new_len == uncompressed_len) {
        if (!game_load_headers_only) {
            CON("DUNGEON: loading %s, decompressed from %lu to %lu bytes",
                file_to_load.c_str(),
                (unsigned long) compressed_len,
                (unsigned long) uncompressed_len);
        }
    } else {
        /* this should NEVER happen */
        DIE("LZO internal error - decompression failed: %d", r);
    }

//    std::cout << "decompressed as ";
//    hexdump((const unsigned char *)uncompressed, uncompressed_len);

    std::string s((const char*)uncompressed, (size_t)uncompressed_len);
    std::istringstream in(s);

    if (!game_load_headers_only) {
        wid_minicon_fini();
        wid_minicon_init();
    }

    game_load_error = "";
    in >> bits(target);
//    this->dump("", std::cout);
    if (game_load_error != "") {
        if (!game_load_headers_only) {
            wid_error("load error, " + game_load_error);
        }
        return (false);
    }

    if (!game_load_headers_only) {
        wid_visible(wid_minicon_window);
        game_status_fini();
        game_status_init();
    }
//
    free(uncompressed);
    free(compressed);
    return (true);
}

void
Game::load_config (void)
{_
    auto filename = saved_dir + "config";
    std::ifstream in(filename);
    in >> bits(*(&game->config));
    game->config.log("READ:");
}

void
Game::load (void)
{_
    LOG("-");
    CON("DUNGEON: loading %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    load(save_file, *this);

    config_update_all();

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: loaded %s, seed %d", save_file.c_str(), seed);
    LOG("-");
}

void
Game::load (int slot)
{_
    if (slot < 0) {
        return;
    }

    if (slot >= MAX_SAVE_SLOTS) {
        return;
    }

    game->fini();

    auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

    LOG("-");
    CON("DUNGEON: loading %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    load(save_file, *this);

    config_update_all();

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: loaded %s, seed %d", save_file.c_str(), seed);
    LOG("-");
}

static WidPopup *wid_load;

static void wid_load_destroy (void)
{
    if (wid_load) {
        delete wid_load;
        wid_load = nullptr;
    }
    game->hard_unpause();
}

uint8_t wid_load_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                        game->load(slot);
                        wid_load_destroy();
                        return (true);
                    }
                    case SDLK_ESCAPE: {
                        CON("PLAYER: load game cancelled");
                        wid_load_destroy();
                        return (true);
                    }
                }
            }
        }
    }

    return (true);
}

uint8_t wid_load_key_down (Widp w, const struct SDL_KEYSYM *key)
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

uint8_t wid_load_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{
    auto slot = wid_get_int_context(w);
    game->load(slot);
    wid_load_destroy();
    return (true);
}

void Game::load_select (void)
{_
    MINICON("Loading a saved game");
    CON("USERCFG: loading a saved game, destroy old");

    if (wid_load) {
        return;
    }
    game->hard_pause();

    auto m = ASCII_WIDTH / 2;
    point tl = {m - WID_POPUP_WIDTH_WIDE / 2, MINICON_VIS_HEIGHT + 2};
    point br = {m + WID_POPUP_WIDTH_WIDE / 2, ITEMBAR_TL_Y - 2};
    auto width = br.x - tl.x;

    wid_load = new WidPopup(tl, br, tile_find_mand("load"), "ui_popup_wide");
    wid_set_on_key_up(wid_load->wid_popup_container, wid_load_key_up);
    wid_set_on_key_down(wid_load->wid_popup_container, wid_load_key_down);

    game_load_headers_only = true;

    wid_load->log("Choose a save slot. %%fg=red$ESC%%fg=reset$ to cancel");

    int y_at = 2;
    for (auto slot = 0; slot < MAX_SAVE_SLOTS; slot++) {
        Game tmp;
        auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);
        auto p = wid_load->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save slot");
        point tl = {0, y_at};
        point br = {width - 2, y_at + 2};

        std::string s = std::to_string(slot) + ": ";
        if (!load(tmp_file, tmp)) {
            if (game_load_error != "") {
                s += game_load_error;
            } else {
                s += "<empty>";
            }
            wid_set_style(w, WID_STYLE_RED);
        } else {
            s += tmp.save_meta;
            wid_set_style(w, WID_STYLE_GREEN);
        }
        wid_set_on_mouse_up(w, wid_load_mouse_up);
        wid_set_int_context(w, slot);

        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        y_at += 3;
    }
    game_load_headers_only = false;
    wid_update(wid_load->wid_text_area->wid_text_area);
    CON("USERCFG: loaded a saved game");
}
