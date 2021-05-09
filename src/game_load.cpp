//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "minilzo.h"
#include "my_wid_topcon.h"
#include "my_wid_botcon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_game_error.h"
#include "my_wid_rightbar.h"
#include "my_alloc.h"
#include "my_sprintf.h"
#include "my_file.h"
#include "my_array_bounds_check.h"
#include "my_monst.h"
#include "my_ui.h"
#include "my_string.h"
#include "my_thing.h"
#include "my_sdl.h"

static timestamp_t old_timestamp_dungeon_created;
static timestamp_t new_timestamp_dungeon_created;
static timestamp_t T;
static std::string game_load_error;
bool game_load_headers_only;
extern int GAME_SAVE_MARKER_EOL;
std::array<bool, UI_WID_SAVE_SLOTS> slot_valid;

#define READ_MAGIC(what, m) { \
    uint32_t magic; \
    in >> bits(magic); \
    if (magic != m) { \
        game_load_error = \
          "bad " what " magic expected: " + std::to_string(m) + " got " + std::to_string(magic); \
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
    return (T - old_timestamp_dungeon_created + new_timestamp_dungeon_created);
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
    /* ThingId      minion_owner_id           */ in >> bits(my.t->minion_owner_id);
    /* ThingId      spawner_owner_id          */ in >> bits(my.t->spawner_owner_id);
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
    /* fpoint       lunge_to                  */ in >> bits(my.t->lunge_to);
    /* int          bag_height                */ in >> bits(my.t->bag_height);
    /* int          bag_width                 */ in >> bits(my.t->bag_width);
    /* int          bounce_count              */ in >> bits(my.t->bounce_count);
    /* int          gold                      */ in >> bits(my.t->gold);
    /* int          health                    */ in >> bits(my.t->health);
    /* int          health_max                */ in >> bits(my.t->health_max);
    /* int          keys                      */ in >> bits(my.t->keys);
    /* int          lifespan                  */ in >> bits(my.t->lifespan);
    /* int          light_quality             */ in >> bits(my.t->light_quality);
    /* int          light_strength            */ in >> bits(my.t->light_strength);
    /* int          stat_attack               */ in >> bits(my.t->stat_attack);
    /* int          stat_constitution         */ in >> bits(my.t->stat_constitution);
    /* int          stat_defence              */ in >> bits(my.t->stat_defence);
    /* int          stat_strength             */ in >> bits(my.t->stat_strength);
    /* int          owned_count               */ in >> bits(my.t->owned_count);
    /* int          minion_count              */ in >> bits(my.t->minion_count);
    /* int          charge_count              */ in >> bits(my.t->charge_count);
    /* int          stamina                   */ in >> bits(my.t->stamina);
    /* int          stamina_max               */ in >> bits(my.t->stamina_max);
    /* int          enchant                   */ in >> bits(my.t->enchant);
    /* int          enchant_max               */ in >> bits(my.t->enchant_max);
    /* int          poison                    */ in >> bits(my.t->poison);
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
    /* int          stats17                   */ in >> bits(my.t->stats17);
    /* int          stats_stats19             */ in >> bits(my.t->stats_stats19);
    /* int          submerged_offset          */ in >> bits(my.t->submerged_offset);
    /* int          throw_distance            */ in >> bits(my.t->throw_distance);
    /* int          tick_rate_tenths          */ in >> bits(my.t->tick_rate_tenths);
    /* int          tick_resurrect_when       */ in >> bits(my.t->tick_resurrect_when);
    /* point        bag_position              */ in >> bits(my.t->bag_position);
    /* point        wander_target             */ in >> bits(my.t->wander_target);
    /* point     where_i_dropped_an_item_last */ in >> bits(my.t->where_i_dropped_an_item_last);
    /* point   where_i_failed_to_collect_last */ in >> bits(my.t->where_i_failed_to_collect_last);
    /* std::array<std::array<ThingId > >      */ in >> bits(my.t->bag);
    /* std::list<ThingId>   carrying          */ in >> bits(my.t->carrying);
    /* std::list<ThingId>   skills            */ in >> bits(my.t->skills);
    /* std::string          msg               */ in >> bits(my.t->msg);
    /* std::vector<ThingId> enemies           */ in >> bits(my.t->enemies);
    /* std::vector<point>   move_path         */ in >> bits(my.t->move_path);
    /* std::vector<uint16_t> inventory_id     */ in >> bits(my.t->inventory_id);
    /* std::vector<uint16_t> skillbox_id      */ in >> bits(my.t->skillbox_id);
    /* timestamp_t  timestamp_born            */ in >> bits(T); my.t->timestamp_born = load(T);
    /* timestamp_t  timestamp_bounce_begin    */ in >> bits(T); my.t->timestamp_bounce_begin = load(T);
    /* timestamp_t  timestamp_bounce_end      */ in >> bits(T); my.t->timestamp_bounce_end = load(T);
    /* timestamp_t  timestamp_fadeup_begin    */ in >> bits(T); my.t->timestamp_fadeup_begin = load(T);
    /* timestamp_t  timestamp_fadeup_end      */ in >> bits(T); my.t->timestamp_fadeup_end = load(T);
    /* timestamp_t  timestamp_fall_begin      */ in >> bits(T); my.t->timestamp_fall_begin = load(T);
    /* timestamp_t  timestamp_fall_end        */ in >> bits(T); my.t->timestamp_fall_end = load(T);
    /* timestamp_t  timestamp_flip_start      */ in >> bits(T); my.t->timestamp_flip_start = load(T);
    /* timestamp_t  timestamp_hunger_tick     */ in >> bits(T); my.t->timestamp_hunger_tick = load(T);
    /* timestamp_t  timestamp_jump_begin      */ in >> bits(T); my.t->timestamp_jump_begin = load(T);
    /* timestamp_t  timestamp_jump_end        */ in >> bits(T); my.t->timestamp_jump_end = load(T);
    /* timestamp_t  timestamp_unused2         */ in >> bits(T); my.t->timestamp_unused2 = load(T);
    /* timestamp_t  timestamp_unused1         */ in >> bits(T); my.t->timestamp_unused1 = load(T);
    /* timestamp_t  timestamp_last_wander_try */ in >> bits(T); my.t->timestamp_last_wander_try = load(T);
    /* timestamp_t  timestamp_lunge_begin     */ in >> bits(T); my.t->timestamp_lunge_begin = load(T);
    /* timestamp_t  timestamp_lunge_end       */ in >> bits(T); my.t->timestamp_lunge_end = load(T);
    /* timestamp_t  timestamp_move_begin      */ in >> bits(T); my.t->timestamp_move_begin = load(T);
    /* timestamp_t  timestamp_move_end        */ in >> bits(T); my.t->timestamp_move_end = load(T);
    /* timestamp_t  timestamp_sleep_end       */ in >> bits(T); my.t->timestamp_sleep_end = load(T);
    /* uint32_t     tick                      */ in >> bits(my.t->tick);
    /* uint32_t     tick_last_did_something   */ in >> bits(my.t->tick_last_did_something);
    /* uint32_t     tick_last_location_check  */ in >> bits(my.t->tick_last_location_check);
    /* uint32_t     tick_last_escape          */ in >> bits(my.t->tick_last_escape);
    /* uint32_t     tick_last_level_change    */ in >> bits(my.t->tick_last_level_change);
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
    auto start = in.tellg();

    READ_MAGIC("thing begin", THING_MAGIC_BEGIN + (int) sizeof(Thing));

    std::string name;
    in >> bits(name);
    auto tpp = tp_find(name);
    if (!tpp) {
        game_load_error = "unknown thing name '" + name;
        return (in);
    }

    my.t->id = tpp->id;

    uint64_t bits64;
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

    if (!tp_find(my.t->tp_id)) {
        game_load_error = "loaded a thing with invalid TP ID";
        return in;
    }

    in >> bits(my.t->id.id); if (!my.t->id.id) {
        game_load_error = "loaded a thing with no ID";
        return in;
    }
    in >> bits(my.t->interpolated_mid_at);
    in >> bits(my.t->last_mid_at);
    in >> bits(my.t->mid_at);
    in >> bits(my.t->last_attached);
    in >> bits(my.t->last_blit_br);
    in >> bits(my.t->last_blit_tl);
    in >> bits(my.t->last_blit_at);
    in >> bits(T); my.t->timestamp_next_frame = load(T);
    in >> bits(my.t->tile_curr);
    in >> bits(my.t->alpha);
    in >> bits(my.t->z_depth);
    uint8_t dir; in >> dir; my.t->dir = dir;

    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    in >> bits(bits64);
    int shift = 0;
    /* uint64_t */ my.t->has_ever_moved                = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->has_light                     = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->inited_tiles                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_activated                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_attached                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_being_destroyed            = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_blitted                    = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_bouncing                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_changing_level             = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_dead                       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_dying                      = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_facing_left                = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_fadeup                     = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_falling                    = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_hidden                     = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_hungry                     = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_in_lava                    = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_in_water                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_jumping                    = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_moving                     = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_open                       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_resurrected                = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_resurrecting               = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_resurrection_blocked       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_sleeping                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_starving                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_the_grid                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_waiting_to_ascend_dungeon  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_waiting_to_ascend_sewer    = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_waiting_to_descend_dungeon = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_waiting_to_descend_sewer   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->is_waiting_to_fall            = (bits64 >> shift) & 1; shift++;

    in >> bits(bits64);
    shift = 0;

    /* uint64_t */ my.t->i_set_is_acid                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_poison                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_blood                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_chasm                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_corpse                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_bridge                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_corridor               = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_deep_water             = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_shallow_water          = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_dirt                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_dry_fungus             = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_enchantstone           = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_skillstone             = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_foilage                = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_door                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_ascend_dungeon         = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_descend_dungeon        = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_ascend_sewer           = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_descend_sewer          = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_fire                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_floor                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_food                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_minion_generator       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_gold                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_hazard                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_extreme_hazard         = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_treasure_class_a       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_treasure_class_b       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_treasure_class_c       = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_key                    = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_lava                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_light_blocker          = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_monst                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_movement_blocking_hard = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_movement_blocking_soft = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_potion                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_wand                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_ripple                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_rock                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_secret_door            = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_smoke                  = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_brazier                = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_barrel                 = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_treasure               = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_is_wall                   = (bits64 >> shift) & 1; shift++;
    /* uint64_t */ my.t->i_set_gfx_water                 = (bits64 >> shift) & 1; shift++;

    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    //
    // Need to reinit tiles
    //
    my.t->inited_tiles          = false;

    //
    // We do not save particles or lasers
    //
    my.t->has_external_particle = false;
    my.t->has_internal_particle = false;
    my.t->has_laser             = false;
    my.t->has_projectile        = false;

    READ_MAGIC("thing end", THING_MAGIC_END);

    if (g_opt_debug4) {
        auto diff = in.tellg() - start;
        LOG("LOAD %dbytes %s TP %d ID %x last_mid_at %f,%f monstp %p", 
            (int)diff, name.c_str(), my.t->tp_id, my.t->id.id, 
            my.t->last_mid_at.x, my.t->last_mid_at.y, my.t->monstp);
    }

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
    l->all_interesting_things = {};
    l->all_gc_things = {};

    in >> bits(l->timestamp_dungeon_created); old_timestamp_dungeon_created = l->timestamp_dungeon_created;
    in >> bits(l->timestamp_dungeon_saved);
    auto dungeon_age = l->timestamp_dungeon_saved -
                       l->timestamp_dungeon_created;
    new_timestamp_dungeon_created = time_get_time_ms() - dungeon_age;
    l->timestamp_dungeon_created = new_timestamp_dungeon_created;
    l->timestamp_dungeon_saved = new_timestamp_dungeon_created + dungeon_age;
    in >> bits(l->timestamp_fade_out_begin);
    in >> bits(l->timestamp_fade_in_begin);

    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_light_blocker {};          */ in >> bits(my.t->_is_light_blocker);
    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking_hard {}; */ in >> bits(my.t->_is_movement_blocking_hard);
    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking_soft {}; */ in >> bits(my.t->_is_movement_blocking_soft);
    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_visited {};                */ in >> bits(my.t->_is_visited);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _fade_in_map {};            */ in >> bits(my.t->_fade_in_map);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _heatmap {};                */ in >> bits(my.t->_heatmap);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_acid {};                */ in >> bits(my.t->_is_acid);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_poison {};              */ in >> bits(my.t->_is_poison);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};               */ in >> bits(my.t->_is_blood);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_chasm {};               */ in >> bits(my.t->_is_chasm);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};              */ in >> bits(my.t->_is_corpse);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_bridge {};              */ in >> bits(my.t->_is_bridge);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};            */ in >> bits(my.t->_is_corridor);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};          */ in >> bits(my.t->_is_deep_water);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_shallow_water {};       */ in >> bits(my.t->_is_shallow_water);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};                */ in >> bits(my.t->_is_dirt);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dry_fungus {};          */ in >> bits(my.t->_is_dry_fungus);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_enchantstone {};        */ in >> bits(my.t->_is_enchantstone);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_skillstone {};          */ in >> bits(my.t->_is_skillstone);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_foilage {};             */ in >> bits(my.t->_is_foilage);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_door {};                */ in >> bits(my.t->_is_door);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};             */ in >> bits(my.t->_is_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ascend_dungeon {};      */ in >> bits(my.t->_is_ascend_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_descend_dungeon {};     */ in >> bits(my.t->_is_descend_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ascend_sewer {};        */ in >> bits(my.t->_is_ascend_sewer);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_descend_sewer {};       */ in >> bits(my.t->_is_descend_sewer);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_fire {};                */ in >> bits(my.t->_is_fire);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};               */ in >> bits(my.t->_is_floor);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_food {};                */ in >> bits(my.t->_is_food);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_minion_generator {};    */ in >> bits(my.t->_is_minion_generator);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_gold {};                */ in >> bits(my.t->_is_gold);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};              */ in >> bits(my.t->_is_hazard);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_extreme_hazard {};      */ in >> bits(my.t->_is_extreme_hazard);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_a {};    */ in >> bits(my.t->_is_treasure_class_a);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_b {};    */ in >> bits(my.t->_is_treasure_class_b);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_c {};    */ in >> bits(my.t->_is_treasure_class_c);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_key {};                 */ in >> bits(my.t->_is_key);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};                */ in >> bits(my.t->_is_lava);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lit {};                 */ in >> bits(my.t->_is_lit);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_monst {};               */ in >> bits(my.t->_is_monst);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_potion {};              */ in >> bits(my.t->_is_potion);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wand {};                */ in >> bits(my.t->_is_wand);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ripple {};              */ in >> bits(my.t->_is_ripple);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};                */ in >> bits(my.t->_is_rock);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};         */ in >> bits(my.t->_is_secret_door);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_smoke {};               */ in >> bits(my.t->_is_smoke);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_brazier {};             */ in >> bits(my.t->_is_brazier);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_barrel {};              */ in >> bits(my.t->_is_barrel);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure {};            */ in >> bits(my.t->_is_treasure);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};                */ in >> bits(my.t->_is_wall);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _gfx_water {};              */ in >> bits(my.t->_gfx_water);

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
    /* is_dungeon_level */      in >> bits(l->is_dungeon_level);
    /* is_sewer_level */        in >> bits(l->is_sewer_level);
    /* monst_count */           in >> bits(l->monst_count);
    /* mouse */                 in >> bits(l->mouse);
    /* mouse_old */             in >> bits(l->mouse_old);
    /* pixel_map_at */          in >> bits(l->pixel_map_at);
    /* seed */                  in >> bits(l->seed);
    /* world_at */              in >> bits(l->world_at);
    /* minx */                  in >> bits(l->minx);
    /* maxx */                  in >> bits(l->maxx);
    /* miny */                  in >> bits(l->miny);
    /* maxy */                  in >> bits(l->maxy);

    l->update_new_level();
    l->timestamp_redraw_bg = 1; // Force redraw
    l->timestamp_fade_in_begin = time_get_time_ms_cached();
    l->map_changed = true;
    l->cursor_needs_update = true;
    l->map_follow_player = true;

    auto p = l->world_at;
    LOG("DUNGEON: Loading things for level %d,%d,%d", p.x, p.y, p.z);
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
                }
            }
        }
    }

    l->update_new_level();

    READ_MAGIC("level end", THING_MAGIC_FINAL);
    LOG("DUNGEON: Loaded things for level %d,%d,%d", p.x, p.y, p.z);

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

                if (exists) {
                    CON("DUNGEON: Loading level %d,%d,%d", p.x, p.y, p.z);
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
                    CON("DUNGEON: Loaded level %d,%d,%d", p.x, p.y, p.z);
                }
            }
        }
    }
    return (in);
}

std::istream& operator>>(std::istream &in, Bits<Config &> my)
{_
    /* uint32_t           header_size                  */ in >> bits(my.t.header_size                  );
    if (my.t.header_size != sizeof(Config)) {
        game_load_error = "bad save file header version";
        return in;
    }

    /* float              game_pix_scale_height        */ in >> bits(my.t.game_pix_scale_height        );
    /* float              game_pix_scale_width         */ in >> bits(my.t.game_pix_scale_width         );
    /* float              game_pix_zoom                */ in >> bits(my.t.game_pix_zoom                );
    /* float              one_pixel_height             */ in >> bits(my.t.one_pixel_height             );
    /* float              one_pixel_width              */ in >> bits(my.t.one_pixel_width              );
    /* float              tile_pix_height              */ in >> bits(my.t.tile_pix_height              );
    /* float              tile_pix_width               */ in >> bits(my.t.tile_pix_width               );
    /* float              tile_pixel_height            */ in >> bits(my.t.tile_pixel_height            );
    /* float              tile_pixel_width             */ in >> bits(my.t.tile_pixel_width             );
    /* float              ui_pix_scale_height          */ in >> bits(my.t.ui_pix_scale_height          );
    /* float              ui_pix_scale_width           */ in >> bits(my.t.ui_pix_scale_width           );
    /* float              ui_pix_zoom                  */ in >> bits(my.t.ui_pix_zoom                  );
    /* float              video_w_h_ratio              */ in >> bits(my.t.video_w_h_ratio              );
    /* int                debug_mode                   */ in >> bits(my.t.debug_mode                   );
    /* int                fps_counter                  */ in >> bits(my.t.fps_counter                  );
    /* int                gfx_allow_highdpi            */ in >> bits(my.t.gfx_allow_highdpi            );
    /* int                gfx_borderless               */ in >> bits(my.t.gfx_borderless               );
    /* int                gfx_fullscreen               */ in >> bits(my.t.gfx_fullscreen               );
    /* int                gfx_fullscreen_desktop       */ in >> bits(my.t.gfx_fullscreen_desktop       );
    /* int                gfx_inverted                 */ in >> bits(my.t.gfx_inverted                 );
    /* int                gfx_minimap                  */ in >> bits(my.t.gfx_minimap                  );
    /* int                gfx_show_hidden              */ in >> bits(my.t.gfx_show_hidden              );
    /* int                gfx_vsync_enable             */ in >> bits(my.t.gfx_vsync_enable             );
    /* int                tile_height                  */ in >> bits(my.t.tile_height                  );
    /* int                tile_width                   */ in >> bits(my.t.tile_width                   );
    /* int32_t            config_pix_height            */ in >> bits(my.t.config_pix_height            );
    /* int32_t            config_pix_width             */ in >> bits(my.t.config_pix_width             );
    /* int32_t            game_pix_height              */ in >> bits(my.t.game_pix_height              );
    /* int32_t            game_pix_width               */ in >> bits(my.t.game_pix_width               );
    /* int32_t            ui_pix_height                */ in >> bits(my.t.ui_pix_height                );
    /* int32_t            ui_pix_width                 */ in >> bits(my.t.ui_pix_width                 );
    /* int32_t            window_pix_height            */ in >> bits(my.t.window_pix_height            );
    /* int32_t            window_pix_width             */ in >> bits(my.t.window_pix_width             );
    /* uint16_t           ascii_gl_height              */ in >> bits(my.t.ascii_gl_height              );
    /* uint16_t           ascii_gl_width               */ in >> bits(my.t.ascii_gl_width               );
    /* uint32_t           key_action0                  */ in >> bits(my.t.key_action0                  );
    /* uint32_t           key_action1                  */ in >> bits(my.t.key_action1                  );
    /* uint32_t           key_action2                  */ in >> bits(my.t.key_action2                  );
    /* uint32_t           key_action3                  */ in >> bits(my.t.key_action3                  );
    /* uint32_t           key_action4                  */ in >> bits(my.t.key_action4                  );
    /* uint32_t           key_action5                  */ in >> bits(my.t.key_action5                  );
    /* uint32_t           key_action6                  */ in >> bits(my.t.key_action6                  );
    /* uint32_t           key_action7                  */ in >> bits(my.t.key_action7                  );
    /* uint32_t           key_action8                  */ in >> bits(my.t.key_action8                  );
    /* uint32_t           key_action9                  */ in >> bits(my.t.key_action9                  );
    /* uint32_t           key_attack                   */ in >> bits(my.t.key_attack                   );
    /* uint32_t           key_console                  */ in >> bits(my.t.key_console                  );
    /* uint32_t           key_drop                     */ in >> bits(my.t.key_drop                     );
    /* uint32_t           key_eat                      */ in >> bits(my.t.key_eat                      );
    /* uint32_t           key_help                     */ in >> bits(my.t.key_help                     );
    /* uint32_t           key_inventory                */ in >> bits(my.t.key_inventory                );
    /* uint32_t           key_jump                     */ in >> bits(my.t.key_jump                     );
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
    /* uint32_t           key_throw                    */ in >> bits(my.t.key_throw                    );
    /* uint32_t           key_unused3                  */ in >> bits(my.t.key_unused3                  );
    /* uint32_t           key_unused4                  */ in >> bits(my.t.key_unused4                  );
    /* uint32_t           key_unused5                  */ in >> bits(my.t.key_unused5                  );
    /* uint32_t           key_use                      */ in >> bits(my.t.key_use                      );
    /* uint32_t           key_wait_or_collect          */ in >> bits(my.t.key_wait_or_collect          );
    /* uint32_t           key_zoom_in                  */ in >> bits(my.t.key_zoom_in                  );
    /* uint32_t           key_zoom_out                 */ in >> bits(my.t.key_zoom_out                 );
    /* uint32_t           music_volume                 */ in >> bits(my.t.music_volume                 );
    /* uint32_t           sdl_delay                    */ in >> bits(my.t.sdl_delay                    );
    /* uint32_t           sound_volume                 */ in >> bits(my.t.sound_volume                 );
    /* std::string        player name                  */ in >> bits(g_opt_player_name);

    //
    // Allow the command line to override.
    //
    {
        std::string tmp;
        in >> bits(tmp);
        if (g_opt_seed_name.empty()) {
            g_opt_seed_name = tmp;
        }
    }

    in >> bits(my.t.hiscores);

    if (!my.t.game_pix_zoom) {
        ERR("Loading, game_pix_zoom is zero");
        my.t.game_pix_zoom = 3;
        my.t.ui_pix_zoom = 2;
    }

    return (in);
}

std::istream& operator>>(std::istream &in, Bits<class Game &> my)
{_
    in >> bits(my.t.version);
    if (my.t.version != VERSION) {
        game_load_error =
          "old version '" VERSION "' v '" + my.t.version + "'";
        return (in);
    }
    in >> bits(my.t.header_size);
    if (my.t.header_size != (uint32_t) sizeof(Game)) {
        game_load_error =
          "old version '" VERSION "' v '" + my.t.version + "'";
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

    /* bool               hard_paused                  */ in >> bits(my.t.hard_paused);
    /* bool               soft_paused                  */ in >> bits(my.t.soft_paused);
    /* bool               started                      */ in >> bits(my.t.started);
    /* bool               things_are_moving            */ in >> bits(my.t.things_are_moving);
    /* fpoint             mouse_over                   */ in >> bits(my.t.mouse_over);
    /* point              minimap_over                 */ in >> bits(my.t.minimap_over);
    /* int                seed                         */ in >> bits(my.t.seed);
    /* std::string        seed_name                    */ in >> bits(my.t.seed_name);
    /* point3d            current_level                */ in >> bits(my.t.current_level);
    /* uint32_t           inventory_highlight_slot     */ in >> bits(my.t.inventory_highlight_slot);
    /* uint32_t           skillbox_highlight_slot      */ in >> bits(my.t.skillbox_highlight_slot);
    /* uint32_t           previous_slot                */ in >> bits(my.t.previous_slot);
    /* uint32_t           fps_value                    */ in >> bits(my.t.fps_value);
    /* uint32_t           tick_completed               */ in >> bits(my.t.tick_completed);
    /* uint32_t           tick_current                 */ in >> bits(my.t.tick_current);

    std::vector<std::wstring> s; in >> bits(s); wid_topcon_deserialize(s);
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
    if (ifs.is_open()) {
        ifs.unsetf(std::ios::skipws);

        std::ifstream::pos_type sz = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        std::vector<char> bytes(sz);
        ifs.read(bytes.data(), sz);
        return bytes;
    } else {
        std::vector<char> bytes;
        return bytes;
    }
}

static std::vector<char> read_lzo_file (const std::string filename,
                                        lzo_uint *uncompressed_sz,
                                        uint32_t *cs)
{_
    std::ifstream ifs(filename,
                      std::ios::in | std::ios::binary | std::ios::ate);
    if (ifs.is_open()) {
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
    } else {
        std::vector<char> bytes;
        return (bytes);
    }
}

uint32_t csum (char *mem, uint32_t len)
{_
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
    game_load_error = "";

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
        return false;
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
            CON("DUNGEON: Loading %s, decompress %luMb -> %luMb",
                file_to_load.c_str(),
                (unsigned long) compressed_len / (1024 * 1024),
                (unsigned long) uncompressed_len / (1024 * 1024));
        }
    } else {
        /* this should NEVER happen */
        ERR("LZO internal error - decompression failed: %d", r);
        return false;
    }

    uint32_t csin = csum((char*)uncompressed, (uint32_t)uncompressed_len);
    if (cs != csin) {
        ERR("Corrupt file, checksum mismatch");
        return false;
    }

#if 0
    if (g_opt_debug4) {
        std::cout << "decompressed as ";
        hexdump((const unsigned char *)uncompressed, uncompressed_len);
    }
#endif

    std::string s((const char*)uncompressed, (size_t)uncompressed_len);
    std::istringstream in(s);

    if (!game_load_headers_only) {
        wid_topcon_fini();
        wid_topcon_init();
    }

    game_load_error = "";
    in >> bits(target);
    if (game_load_error != "") {
        if (!game_load_headers_only) {
            game_error("load error, " + game_load_error);
        }
        return false;
    }

    if (!game_load_headers_only) {
        wid_visible(wid_topcon_window);
        wid_visible(wid_botcon_window);
        wid_rightbar_fini();
        wid_rightbar_init();
    }

    free(uncompressed);
    free(compressed);
    return true;
}

void
Game::load_config (void)
{_
    auto filename = saved_dir + "config";
    std::ifstream in(filename);
    if (in.is_open()) {
        in >> bits(*(&game->config));
        game->config.dump("READ:");
    }
}

void
Game::load (void)
{_
    LOG("-");
    CON("DUNGEON: Loading %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    load(save_file, *this);

    sdl_config_update_all();

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: Loaded %s, seed %u", save_file.c_str(), seed);
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

    if  (!get(slot_valid, slot)) {
        TOPCON("No game at that slot.");
        return;
    }

    game->fini();

    auto save_file = saved_dir + "saved-slot-" + std::to_string(slot);

    LOG("-");
    CON("DUNGEON: Loading %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    load(save_file, *this);

    sdl_config_update_all();

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: Loaded %s, seed %d", save_file.c_str(), seed);
    LOG("-");

    TOPCON("Loaded the game from %s.", save_file.c_str());
}

static WidPopup *wid_load;

static void wid_load_destroy (void)
{_
    delete wid_load;
    wid_load = nullptr;
    game->hard_unpause();
}

static uint8_t wid_load_key_up (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    switch (key->mod) {
        case KMOD_LCTRL:
        case KMOD_RCTRL:
        default:
        switch (key->sym) {
            default: {
                auto c = wid_event_to_char(key);
                switch (c) {
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
                        if  (!get(slot_valid, slot)) {
                            TOPCON("No game at that slot.");
                        } else {
                            game->load(slot);
                            wid_load_destroy();
                        }
                        return true;
                    }
                    case 'b':
                    case SDLK_ESCAPE: {_
                        CON("PLAYER: Load game cancelled");
                        wid_load_destroy();
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

static uint8_t wid_load_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

static uint8_t wid_load_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    auto slot = wid_get_int_context(w);
    game->load(slot);
    wid_load_destroy();
    return true;
}

void Game::load_select (void)
{_
    CON("USERCFG: loading a saved game, destroy old");

    if (wid_load) {
        return;
    }
    game->hard_pause();

    auto m = TERM_WIDTH / 2;
    point tl = make_point(m - UI_WID_POPUP_WIDTH_WIDE / 2,
                          UI_TOPCON_VIS_HEIGHT + 10);
    point br = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2,
                          tl.y + 30);
    auto width = br.x - tl.x;

    wid_load = new WidPopup("Game load", tl, br, 
                            tile_find_mand("load"), "", 
                            false, false);
    wid_set_on_key_up(wid_load->wid_popup_container, wid_load_key_up);
    wid_set_on_key_down(wid_load->wid_popup_container, wid_load_key_down);

    game_load_headers_only = true;

    wid_load->log(" ");
    wid_load->log("Choose a load slot. %%fg=red$ESC%%fg=reset$ to cancel");

    int y_at = 3;
    for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
        Game tmp;
        auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);
        auto p = wid_load->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "load slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 2, y_at);

        std::string s = std::to_string(slot) + ": ";
        if (!load(tmp_file, tmp)) {
            if (game_load_error != "") {
                s += game_load_error;
            } else {
                s += "<empty>";
            }
            set(slot_valid, slot, false);
            wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        } else {
            s += tmp.save_meta;
            wid_set_style(w, UI_WID_STYLE_HORIZ_LIGHT);
            wid_set_on_mouse_up(w, wid_load_mouse_up);
            set(slot_valid, slot, true);
        }
        wid_set_int_context(w, slot);

        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        y_at += 1;
    }
    game_load_headers_only = false;
    wid_update(wid_load->wid_text_area->wid_text_area);
}
