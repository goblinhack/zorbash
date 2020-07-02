//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "minilzo.h"
#include "my_wid_minicon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_game_error.h"
#include "my_game_status.h"
#include "my_thing.h"
#include "my_alloc.h"
#include "my_sprintf.h"

static timestamp_t old_timestamp_dungeon_created;
static timestamp_t new_timestamp_dungeon_created;
static timestamp_t T;
static std::string game_load_error;
bool game_load_headers_only;
extern int GAME_SAVE_MARKER_EOL;

#define READ_MAGIC(m) { \
    uint32_t magic; \
    in >> bits(magic); \
    if (magic != m) { \
        game_load_error = \
          "bad final thing magic expected: " + std::to_string(m) + " got " + std::to_string(magic); \
        return (in); \
    } \
}

//
// Save timestamps as a delta we can restore.
//
static timestamp_t load (timestamp_t T)
{_
    if (!T) {
        return (0);
    }
    return (T - old_timestamp_dungeon_created +
            new_timestamp_dungeon_created);
}

std::istream& operator>>(std::istream &in, Bits<Monstp & > my)
{_
    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    /* ThingId      on_fire_id_anim           */ in >> bits(my.t->on_fire_id_anim);
    /* ThingId      owner_id                  */ in >> bits(my.t->owner_id);
    /* ThingId      weapon_id                 */ in >> bits(my.t->weapon_id);
    /* ThingId      weapon_id_carry_anim      */ in >> bits(my.t->weapon_id_carry_anim);
    /* ThingId      weapon_id_use_anim        */ in >> bits(my.t->weapon_id_use_anim);
    /* color        light_col                 */ in >> bits(my.t->light_col);
    /* float        bounce_fade               */ in >> bits(my.t->bounce_fade);
    /* float        bounce_height             */ in >> bits(my.t->bounce_height);
    /* float        fadeup_fade               */ in >> bits(my.t->fadeup_fade);
    /* float        fadeup_height             */ in >> bits(my.t->fadeup_height);
    /* float        fall_height               */ in >> bits(my.t->fall_height);
    /* float        wobble                    */ in >> bits(my.t->wobble);
    /* fpoint       interpolated_mid_at       */ in >> bits(my.t->interpolated_mid_at);
    /* fpoint       lunge_to                  */ in >> bits(my.t->lunge_to);
    /* int          bounce_count              */ in >> bits(my.t->bounce_count);
    /* int          gold                      */ in >> bits(my.t->gold);
    /* int          lifespan                  */ in >> bits(my.t->lifespan);
    /* int          light_quality             */ in >> bits(my.t->light_quality);
    /* int          light_strength            */ in >> bits(my.t->light_strength);
    /* int          owned_count               */ in >> bits(my.t->owned_count);
    /* int          stats01                   */ in >> bits(my.t->stats01);
    /* int          stats02                   */ in >> bits(my.t->stats02);
    /* int          stats03                   */ in >> bits(my.t->stats03);
    /* int          stats04                   */ in >> bits(my.t->stats04);
    /* int          stats05                   */ in >> bits(my.t->stats05);
    /* int          stats06                   */ in >> bits(my.t->stats06);
    /* int          stats07                   */ in >> bits(my.t->stats07);
    /* int          stats08                   */ in >> bits(my.t->stats08);
    /* int          stats09                   */ in >> bits(my.t->stats09);
    /* int          stats10                   */ in >> bits(my.t->stats10);
    /* int          stats11                   */ in >> bits(my.t->stats11);
    /* int          stats12                   */ in >> bits(my.t->stats12);
    /* int          stats13                   */ in >> bits(my.t->stats13);
    /* int          stats14                   */ in >> bits(my.t->stats14);
    /* int          stats15                   */ in >> bits(my.t->stats15);
    /* int          stats16                   */ in >> bits(my.t->stats16);
    /* int          stats17                   */ in >> bits(my.t->stats17);
    /* int          stats18                   */ in >> bits(my.t->stats18);
    /* int          stats19                   */ in >> bits(my.t->stats19);
    /* int          stats_defence             */ in >> bits(my.t->stats_defence);
    /* int          stats_defence_max         */ in >> bits(my.t->stats_defence_max);
    /* int          stats_health              */ in >> bits(my.t->stats_health);
    /* int          stats_health_max          */ in >> bits(my.t->stats_health_max);
    /* int          stats_strength            */ in >> bits(my.t->stats_strength);
    /* int          submerged_offset          */ in >> bits(my.t->submerged_offset);
    /* int          tick_rate_tenths          */ in >> bits(my.t->tick_rate_tenths);
    /* int          tick_resurrect_when       */ in >> bits(my.t->tick_resurrect_when);
    /* point        level_changed_at          */ in >> bits(my.t->level_changed_at);
    /* point        wander_target             */ in >> bits(my.t->wander_target);
    /* std::list<ThingId>   carrying          */ in >> bits(my.t->carrying);
    /* std::string          msg               */ in >> bits(my.t->msg);
    /* std::vector<ThingId> actionbar_id      */ in >> bits(my.t->actionbar_id);
    /* std::vector<ThingId> enemies           */ in >> bits(my.t->enemies);
    /* std::vector<point>   move_path         */ in >> bits(my.t->move_path);
    /* timestamp_t  timestamp_born            */ in >> bits(T); my.t->timestamp_born = load(T);
    /* timestamp_t  timestamp_bounce_begin    */ in >> bits(T); my.t->timestamp_bounce_begin = load(T);
    /* timestamp_t  timestamp_bounce_end      */ in >> bits(T); my.t->timestamp_bounce_end = load(T);
    /* timestamp_t  timestamp_fadeup_begin    */ in >> bits(T); my.t->timestamp_fadeup_begin = load(T);
    /* timestamp_t  timestamp_fadeup_end      */ in >> bits(T); my.t->timestamp_fadeup_end = load(T);
    /* timestamp_t  timestamp_fall_begin      */ in >> bits(T); my.t->timestamp_fall_begin = load(T);
    /* timestamp_t  timestamp_fall_end        */ in >> bits(T); my.t->timestamp_fall_end = load(T);
    /* timestamp_t  timestamp_flip_start      */ in >> bits(T); my.t->timestamp_flip_start = load(T);
    /* timestamp_t  timestamp_hunger_tick     */ in >> bits(T); my.t->timestamp_hunger_tick = load(T);
    /* timestamp_t  timestamp_last_tick       */ in >> bits(T); my.t->timestamp_last_tick = load(T);
    /* timestamp_t  timestamp_last_ticked     */ in >> bits(T); my.t->timestamp_last_ticked = load(T);
    /* timestamp_t  timestamp_last_wander_try */ in >> bits(T); my.t->timestamp_last_wander_try = load(T);
    /* timestamp_t  timestamp_lunge_begin     */ in >> bits(T); my.t->timestamp_lunge_begin = load(T);
    /* timestamp_t  timestamp_lunge_end       */ in >> bits(T); my.t->timestamp_lunge_end = load(T);
    /* timestamp_t  timestamp_move_begin      */ in >> bits(T); my.t->timestamp_move_begin = load(T);
    /* timestamp_t  timestamp_move_end        */ in >> bits(T); my.t->timestamp_move_end = load(T);
    /* uint32_t     tick                      */ in >> bits(my.t->tick);
    /* uint32_t     tick_last_did_something   */ in >> bits(my.t->tick_last_did_something);
    /* uint32_t     tick_last_escape          */ in >> bits(my.t->tick_last_escape);
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    return (in);
}

std::istream& operator>> (std::istream &in, Bits<Thingp &> my)
{_
#ifdef ENABLE_DEBUG_SAVE_LOAD
    auto start = in.tellg();
#endif

    READ_MAGIC(THING_MAGIC_BEGIN);

    std::string name;
    in >> bits(name);
    auto tpp = tp_find(name);
    if (!tpp) {
        game_load_error = "unknown thing name '" + name;
        return (in);
    }

    my.t->id = tpp->id;

    uint32_t bits32;
    bool monst = (my.t->monstp != nullptr);
    in >> bits(monst);
    if (monst) {
        my.t->new_monst();
        in >> bits(my.t->monstp);
    }

    /////////////////////////////////////////////////////////////////////////
    // Keep these in the same order as my_thing.h and save/load
    /////////////////////////////////////////////////////////////////////////
    in >> bits(my.t->tp_id); if (my.t->tp_id <= 0) {
        game_load_error = "loaded a thing with no TP ID";
        return in;
    }
    in >> bits(my.t->id.id); if (!my.t->id.id) {
        game_load_error = "loaded a thing with no ID";
        return in;
    }
    in >> bits(my.t->last_mid_at);
    in >> bits(my.t->mid_at);
    in >> bits(my.t->last_attached);
    in >> bits(my.t->last_blit_br);
    in >> bits(my.t->last_blit_tl);
    in >> bits(T); my.t->timestamp_next_frame = load(T);
    in >> bits(my.t->tile_curr);
    in >> bits(my.t->alpha);
    uint8_t dir; in >> dir; my.t->dir = dir;

    in >> bits(bits32);
    int shift = 0;
    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    /* uint32_t */ my.t->has_ever_moved     = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->has_light          = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->inited_tiles       = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_attached        = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_being_destroyed = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_blitted         = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_bouncing        = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_dead            = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_facing_left     = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_fadeup          = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_falling         = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_hidden          = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_hungry          = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_in_lava         = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_in_water        = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_jumping         = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_moving          = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_open            = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_resurrected     = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_resurrecting    = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_sleeping        = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_starving        = (bits32 >> shift) & 1; shift++;
    /* uint32_t */ my.t->is_tick_done       = (bits32 >> shift) & 1; shift++;
    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    READ_MAGIC(THING_MAGIC_END);

#ifdef ENABLE_DEBUG_SAVE_LOAD
    auto diff = in.tellg() - start;
    LOG("LOAD %dbytes %s TP %d ID %x last_mid_at %f,%f monstp %p", 
        (int)diff, name.c_str(), my.t->tp_id, my.t->id.id, my.t->last_mid_at.x, my.t->last_mid_at.y, my.t->monstp);
#endif
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<Level * &> my)
{_
    auto l = my.t;

    l->player = nullptr;
    l->cursor = nullptr;
    l->all_thing_ids_at = {};
    l->all_thing_ptrs_at = {};
    l->all_things = {};
    l->all_active_things = {};
    l->all_gc_things = {};

    in >> bits(l->timestamp_dungeon_created); old_timestamp_dungeon_created = l->timestamp_dungeon_created;
    in >> bits(l->timestamp_dungeon_saved);
    auto dungeon_age = l->timestamp_dungeon_saved -
                       l->timestamp_dungeon_created;
    new_timestamp_dungeon_created = time_get_time_ms() - dungeon_age;
    l->timestamp_dungeon_created = new_timestamp_dungeon_created;
    l->timestamp_dungeon_saved = new_timestamp_dungeon_created + dungeon_age;

    /* _fade_in_map */          in >> bits(l->_fade_in_map);
    /* _heatmap */              in >> bits(l->_heatmap);
    /* _is_acid */              in >> bits(l->_is_acid);
    /* _is_blood */             in >> bits(l->_is_blood);
    /* _is_corpse */            in >> bits(l->_is_corpse);
    /* _is_corridor */          in >> bits(l->_is_corridor);
    /* _is_deep_water */        in >> bits(l->_is_deep_water);
    /* _is_dirt */              in >> bits(l->_is_dirt);
    /* _is_door */              in >> bits(l->_is_door);
    /* _is_dungeon */           in >> bits(l->_is_dungeon);
    /* _is_entrance */          in >> bits(l->_is_entrance);
    /* _is_exit */              in >> bits(l->_is_exit);
    /* _is_fire */              in >> bits(l->_is_fire);
    /* _is_floor */             in >> bits(l->_is_floor);
    /* _is_food */              in >> bits(l->_is_food);
    /* _is_generator */         in >> bits(l->_is_generator);
    /* _is_gold */              in >> bits(l->_is_gold);
    /* _is_hazard */            in >> bits(l->_is_hazard);
    /* _is_key */               in >> bits(l->_is_key);
    /* _is_lava */              in >> bits(l->_is_lava);
    /* _is_light_blocker */     in >> bits(l->_is_light_blocker);
    /* _is_lit */               in >> bits(l->_is_lit);
    /* _is_monst */             in >> bits(l->_is_monst);
    /* _is_movement_blocking */ in >> bits(l->_is_movement_blocking);
    /* _is_rock */              in >> bits(l->_is_rock);
    /* _is_secret_door */       in >> bits(l->_is_secret_door);
    /* _is_smoke */             in >> bits(l->_is_smoke);
    /* _is_treasure */          in >> bits(l->_is_treasure);
    /* _is_visited */           in >> bits(l->_is_visited);
    /* _is_wall */              in >> bits(l->_is_wall);
    /* _is_water */             in >> bits(l->_is_water);
    /* all_thing_ids_at */      in >> bits(l->all_thing_ids_at);
    /* cursor_at */             in >> bits(l->cursor_at);
    /* cursor_at_old */         in >> bits(l->cursor_at_old);
    /* cursor_found */          in >> bits(l->cursor_found);
    /* cursor_needs_update */   in >> bits(l->cursor_needs_update);
    /* heatmap_valid */         in >> bits(l->heatmap_valid);
    /* is_starting */           in >> bits(l->is_starting);
    /* map_at */                in >> bits(l->map_at);
    /* map_br */                in >> bits(l->map_br);
    /* map_changed */           in >> bits(l->map_changed);
    /* map_follow_player */     in >> bits(l->map_follow_player);
    /* map_tl */                in >> bits(l->map_tl);
    /* map_wanted_at */         in >> bits(l->map_wanted_at);
    /* minimap_valid */         in >> bits(l->minimap_valid);
    /* mouse */                 in >> bits(l->mouse);
    /* mouse_old */             in >> bits(l->mouse_old);
    /* pixel_map_at */          in >> bits(l->pixel_map_at);
    /* seed */                  in >> bits(l->seed);
    /* world_at */              in >> bits(l->world_at);

    l->minimap_valid = false;
    l->heatmap_valid = false;
    l->map_changed = true;
    l->cursor_needs_update = true;
    l->map_follow_player = true;

    auto p = l->world_at;
    LOG("DUNGEON: loading things for level %d,%d,%d", p.x, p.y, p.z);
_
    //
    // Operate on a copy, not live data that might change as we add things
    //
    auto ids = my.t->all_thing_ids_at;

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto slot = 0; slot < MAP_SLOTS; slot++) {
                auto id = get(ids, x, y, slot);
                if (id.ok()) {
                    auto t = new Thing();
                    in >> bits(t);

                    if (game_load_error != "") {
                        return in;
                    }

                    //
                    // Cannot use t->log here as thing is no inited yet
                    //
                    t->level = l;
                    if (t->id != id) {
                        game_load_error =
                          string_sprintf("found different thing than expected at map position %d,%d slot %d: %x expected %x",
                             x, y, slot, t->id.id, id.id);
                        return in;
                    }

                    t->reinit();
                    t->log("loaded");
                    if (t->has_light) {
                        t->new_light(t->mid_at,
                                     fpoint(0, 0),
                                     t->monstp->light_strength,
                                     t->monstp->light_col);
                        t->log("added light");
                    }
                }
            }
        }
    }

    READ_MAGIC(THING_MAGIC_FINAL);
    LOG("DUNGEON: loaded things for level %d,%d,%d", p.x, p.y, p.z);

    my.t->update_map();
    LOG("DUNGEON: updated map for level %d,%d,%d", p.x, p.y, p.z);
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<class World &> my)
{_
    my.t.levels = {};
    my.t.all_thing_ptrs = {};

    for (auto x = 0; x < LEVELS_ACROSS; ++x) {
        for (auto y = 0; y < LEVELS_DOWN; ++y) {
            for (auto z = 0; z < LEVELS_DEEP; ++z) {
                point3d p;
                bool exists;
                in >> bits(p);
                in >> bits(exists);
                if (p != point3d(x, y, z)) {
                    game_load_error =
                        string_sprintf("level mismatch expected %d,%d,%d vs found %d,%d,%d",
                                       x, y, z, p.x, p.y, p.z);
                    return (in);
                }

                if (exists) {_
                    CON("DUNGEON: loading level %d,%d,%d", p.x, p.y, p.z);
                    auto l = new Level();
                    set(my.t.levels, x, y, z, l);
                    in >> bits(l);
                    if (game_load_error != "") {
                        return in;
                    }

                    int eol;
                    in >> bits(eol);
                    if (eol != GAME_SAVE_MARKER_EOL) {
                        game_load_error =
                            string_sprintf("end of level %d,%d,%d not found",
                                           x, y, z);
                        return (in);
                    }
                    CON("DUNGEON: loaded level %d,%d,%d", p.x, p.y, p.z);
                }
            }
        }
    }
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<Config &> my)
{_
    /* bool               allow_highdpi                */ in >> bits(my.t.allow_highdpi                );
    /* bool               ascii_mode                   */ in >> bits(my.t.ascii_mode                   );
    /* bool               debug_mode                   */ in >> bits(my.t.debug_mode                   );
    /* bool               fps_counter                  */ in >> bits(my.t.fps_counter                  );
    /* bool               fullscreen                   */ in >> bits(my.t.fullscreen                   );
    /* bool               gfx_inverted                 */ in >> bits(my.t.gfx_inverted                 );
    /* bool               gfx_lights                   */ in >> bits(my.t.gfx_lights                   );
    /* bool               gfx_minimap                  */ in >> bits(my.t.gfx_minimap                  );
    /* bool               gfx_show_hidden              */ in >> bits(my.t.gfx_show_hidden              );
    /* bool               gfx_vsync_enable             */ in >> bits(my.t.gfx_vsync_enable             );
    /* double             ascii_gl_height              */ in >> bits(my.t.ascii_gl_height              );
    /* double             ascii_gl_width               */ in >> bits(my.t.ascii_gl_width               );
    /* double             one_pixel_height             */ in >> bits(my.t.one_pixel_height             );
    /* double             one_pixel_width              */ in >> bits(my.t.one_pixel_width              );
    /* double             tile_pix_height              */ in >> bits(my.t.tile_pix_height              );
    /* double             tile_pix_width               */ in >> bits(my.t.tile_pix_width               );
    /* double             tile_pixel_height            */ in >> bits(my.t.tile_pixel_height            );
    /* double             tile_pixel_width             */ in >> bits(my.t.tile_pixel_width             );
    /* double             video_w_h_ratio              */ in >> bits(my.t.video_w_h_ratio              );
    /* int32_t            inner_pix_height             */ in >> bits(my.t.inner_pix_height             );
    /* int32_t            inner_pix_width              */ in >> bits(my.t.inner_pix_width              );
    /* int32_t            outer_pix_height             */ in >> bits(my.t.outer_pix_height             );
    /* int32_t            outer_pix_width              */ in >> bits(my.t.outer_pix_width              );
    /* int32_t            scale_pix_height             */ in >> bits(my.t.scale_pix_height             );
    /* int32_t            scale_pix_width              */ in >> bits(my.t.scale_pix_width              );
    /* uint32_t           gfx_zoom                     */ in >> bits(my.t.gfx_zoom                     );
    /* uint32_t           key_attack                   */ in >> bits(my.t.key_attack                   );
    /* uint32_t           key_help                     */ in >> bits(my.t.key_help                     );
    /* uint32_t           key_load                     */ in >> bits(my.t.key_load                     );
    /* uint32_t           key_map_down                 */ in >> bits(my.t.key_map_down                 );
    /* uint32_t           key_map_left                 */ in >> bits(my.t.key_map_left                 );
    /* uint32_t           key_map_right                */ in >> bits(my.t.key_map_right                );
    /* uint32_t           key_map_up                   */ in >> bits(my.t.key_map_up                   );
    /* uint32_t           key_move_down                */ in >> bits(my.t.key_move_down                );
    /* uint32_t           key_move_left                */ in >> bits(my.t.key_move_left                );
    /* uint32_t           key_move_right               */ in >> bits(my.t.key_move_right               );
    /* uint32_t           key_move_up                  */ in >> bits(my.t.key_move_up                  );
    /* uint32_t           key_pause                    */ in >> bits(my.t.key_pause                    );
    /* uint32_t           key_quit                     */ in >> bits(my.t.key_quit                     );
    /* uint32_t           key_save                     */ in >> bits(my.t.key_save                     );
    /* uint32_t           key_screenshot               */ in >> bits(my.t.key_screenshot               );
    /* uint32_t           key_unused1                  */ in >> bits(my.t.key_unused1                  );
    /* uint32_t           key_unused10                 */ in >> bits(my.t.key_unused10                 );
    /* uint32_t           key_unused11                 */ in >> bits(my.t.key_unused11                 );
    /* uint32_t           key_unused12                 */ in >> bits(my.t.key_unused12                 );
    /* uint32_t           key_unused13                 */ in >> bits(my.t.key_unused13                 );
    /* uint32_t           key_unused14                 */ in >> bits(my.t.key_unused14                 );
    /* uint32_t           key_unused15                 */ in >> bits(my.t.key_unused15                 );
    /* uint32_t           key_unused16                 */ in >> bits(my.t.key_unused16                 );
    /* uint32_t           key_unused17                 */ in >> bits(my.t.key_unused17                 );
    /* uint32_t           key_unused18                 */ in >> bits(my.t.key_unused18                 );
    /* uint32_t           key_unused19                 */ in >> bits(my.t.key_unused19                 );
    /* uint32_t           key_unused2                  */ in >> bits(my.t.key_unused2                  );
    /* uint32_t           key_unused20                 */ in >> bits(my.t.key_unused20                 );
    /* uint32_t           key_unused3                  */ in >> bits(my.t.key_unused3                  );
    /* uint32_t           key_unused4                  */ in >> bits(my.t.key_unused4                  );
    /* uint32_t           key_unused5                  */ in >> bits(my.t.key_unused5                  );
    /* uint32_t           key_unused6                  */ in >> bits(my.t.key_unused6                  );
    /* uint32_t           key_unused7                  */ in >> bits(my.t.key_unused7                  );
    /* uint32_t           key_unused8                  */ in >> bits(my.t.key_unused8                  );
    /* uint32_t           key_unused9                  */ in >> bits(my.t.key_unused9                  );
    /* uint32_t           key_wait                     */ in >> bits(my.t.key_wait                     );
    /* uint32_t           key_zoom_in                  */ in >> bits(my.t.key_zoom_in                  );
    /* uint32_t           key_zoom_out                 */ in >> bits(my.t.key_zoom_out                 );
    /* uint32_t           music_volume                 */ in >> bits(my.t.music_volume                 );
    /* uint32_t           sdl_delay                    */ in >> bits(my.t.sdl_delay                    );
    /* uint32_t           sound_volume                 */ in >> bits(my.t.sound_volume                 );
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
    in >> bits(my.t.save_file); if (game_load_headers_only) { return (in); }
    in >> bits(my.t.appdata);
    in >> bits(my.t.saved_dir);
    in >> bits(my.t.config);
    if (game_load_error != "") {
        return in;
    }
    in >> bits(my.t.world);
    if (game_load_error != "") {
        return in;
    }

    /* bool               hard_paused       */ in >> bits(my.t.hard_paused);
    /* bool               soft_paused       */ in >> bits(my.t.soft_paused);
    /* bool               started           */ in >> bits(my.t.started);
    /* fpoint             mouse_over        */ in >> bits(my.t.mouse_over);
    /* int                seed              */ in >> bits(my.t.seed);
    /* point3d            current_level     */ in >> bits(my.t.current_level);
    /* timestamp_t        last_pause        */ in >> bits(my.t.last_pause);
    /* uint32_t           fps_value         */ in >> bits(my.t.fps_value);
    /* uint32_t           things_are_moving */ in >> bits(my.t.things_are_moving);
    /* uint32_t           tick_completed    */ in >> bits(my.t.tick_completed);
    /* uint32_t           tick_current      */ in >> bits(my.t.tick_current);
_
    std::vector<std::wstring> s; in >> bits(s); wid_minicon_deserialize(s);
                                 in >> bits(s); wid_console_deserialize(s);
    my.t.level = get(my.t.world.levels,
                     my.t.current_level.x,
                     my.t.current_level.y,
                     my.t.current_level.z);
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
                                        lzo_uint *uncompressed_sz,
                                        uint32_t *cs)
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
    ifs.read((char*) uncompressed_sz, sizeof(*uncompressed_sz));
    ifs.read((char*) cs, sizeof(*cs));

    sz -= (int) sizeof(*uncompressed_sz);
    sz -= (int) sizeof(*cs);
    std::vector<char> bytes(sz);
    ifs.read(bytes.data(), sz);

    return (bytes);
}

uint32_t csum (char *mem, uint32_t len)
{
    uint32_t ret = 0;
    while (len--) {
        ret <<= 1;
        ret ^= *mem;
        mem++;
    }
    return ret;
}

bool
Game::load (std::string file_to_load, class Game &target)
{_
    //
    // Read to a vector and then copy to a C buffer for LZO to use
    //
    lzo_uint uncompressed_len;
    uint32_t cs;
    auto vec = read_lzo_file(file_to_load, &uncompressed_len, &cs);
    if (vec.size() <= 0) {
        if (!game_load_headers_only) {
            game_error("load error, empty file?");
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
            CON("DUNGEON: loading %s, decompress %luMb -> %luMb",
                file_to_load.c_str(),
                (unsigned long) compressed_len / (1024 * 1024),
                (unsigned long) uncompressed_len / (1024 * 1024));
        }
    } else {
        /* this should NEVER happen */
        ERR("LZO internal error - decompression failed: %d", r);
        return (false);
    }

    uint32_t csin = csum((char*)uncompressed, (uint32_t)uncompressed_len);
    if (cs != csin) {
        ERR("Corrupt file, checksum mismatch");
        return (false);
    }

#ifdef ENABLE_DEBUG_SAVE_LOAD_HEX
    std::cout << "decompressed as ";
    hexdump((const unsigned char *)uncompressed, uncompressed_len);
#endif

    std::string s((const char*)uncompressed, (size_t)uncompressed_len);
    std::istringstream in(s);

    if (!game_load_headers_only) {
        wid_minicon_fini();
        wid_minicon_init();
    }

    game_load_error = "";
    in >> bits(target);
    if (game_load_error != "") {
        if (!game_load_headers_only) {
            game_error("load error, " + game_load_error);
        }
        return (false);
    }

    if (!game_load_headers_only) {
        wid_visible(wid_minicon_window);
        game_status_wid_fini();
        game_status_wid_init();
    }

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

    if (slot >= UI_WID_SAVE_SLOTS) {
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

    MINICON("Loaded the game from %s", save_file.c_str());
}

static WidPopup *wid_load;

static void wid_load_destroy (void)
{_
    delete wid_load;
    wid_load = nullptr;
    game->hard_unpause();
}

uint8_t wid_load_key_up (Widp w, const struct SDL_KEYSYM *key)
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
                        game->load(slot);
                        wid_load_destroy();
                        return (true);
                    }
                    case SDLK_ESCAPE: {_
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

uint8_t wid_load_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
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
    point tl = make_point(m - UI_WID_POPUP_WIDTH_WIDE / 2, UI_MINICON_VIS_HEIGHT + 2);
    point br = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2, UI_ACTIONBAR_TL_Y - 2);
    auto width = br.x - tl.x;

    wid_load = new WidPopup(tl, br, tile_find_mand("load"), "ui_popup_wide");
    wid_set_on_key_up(wid_load->wid_popup_container, wid_load_key_up);
    wid_set_on_key_down(wid_load->wid_popup_container, wid_load_key_down);

    game_load_headers_only = true;

    wid_load->log("Choose a load slot. %%fg=red$ESC%%fg=reset$ to cancel");

    int y_at = 2;
    for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
        Game tmp;
        auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);
        auto p = wid_load->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "LOAD slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 2, y_at + 2);

        std::string s = std::to_string(slot) + ": ";
        if (!load(tmp_file, tmp)) {
            if (game_load_error != "") {
                s += game_load_error;
            } else {
                s += "<empty>";
            }
            wid_set_style(w, UI_WID_STYLE_RED);
        } else {
            s += tmp.save_meta;
            wid_set_style(w, UI_WID_STYLE_GREEN);
        }
        wid_set_on_mouse_up(w, wid_load_mouse_up);
        wid_set_int_context(w, slot);

        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        y_at += 3;
    }
    game_load_headers_only = false;
    wid_update(wid_load->wid_text_area->wid_text_area);
}
