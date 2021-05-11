//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "minilzo.h"
#include "my_sys.h"
#include "my_game.h"
#include "my_wid_topcon.h"
#include "my_wid_console.h"
#include "my_wid_popup.h"
#include "my_alloc.h"
#include "my_array_bounds_check.h"
#include "my_monst.h"
#include "my_string.h"
#include "my_thing.h"
#include "my_ui.h"
#include "my_sdl.h"

extern bool game_load_headers_only;
bool game_save_config_only;
int GAME_SAVE_MARKER_EOL = 123456;
extern uint32_t csum(char *mem, uint32_t len);

#define WRITE_MAGIC(m) { uint32_t magic = m; out << bits(magic); }

std::ostream& operator<<(std::ostream &out, Bits<Monstp & > const my)
{_
    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    /* ThingId      on_fire_id_anim           */ out << bits(my.t->on_fire_id_anim);
    /* ThingId      owner_id                  */ out << bits(my.t->owner_id);
    /* ThingId      minion_owner_id           */ out << bits(my.t->minion_owner_id);
    /* ThingId      spawner_owner_id          */ out << bits(my.t->spawner_owner_id);
    /* ThingId      weapon_id                 */ out << bits(my.t->weapon_id);
    /* ThingId      weapon_id_carry_anim      */ out << bits(my.t->weapon_id_carry_anim);
    /* ThingId      weapon_id_use_anim        */ out << bits(my.t->weapon_id_use_anim);
    /* color        light_col                 */ out << bits(my.t->light_col);
    /* float        bounce_fade               */ out << bits(my.t->bounce_fade);
    /* float        bounce_height             */ out << bits(my.t->bounce_height);
    /* float        fadeup_fade               */ out << bits(my.t->fadeup_fade);
    /* float        fadeup_height             */ out << bits(my.t->fadeup_height);
    /* float        fall_height               */ out << bits(my.t->fall_height);
    /* float        wobble                    */ out << bits(my.t->wobble);
    /* fpoint       lunge_to                  */ out << bits(my.t->lunge_to);
    /* int          bag_height                */ out << bits(my.t->bag_height);
    /* int          bag_width                 */ out << bits(my.t->bag_width);
    /* int          bounce_count              */ out << bits(my.t->bounce_count);
    /* int          gold                      */ out << bits(my.t->gold);
    /* int          health                    */ out << bits(my.t->health);
    /* int          health_max                */ out << bits(my.t->health_max);
    /* int          keys                      */ out << bits(my.t->keys);
    /* int          lifespan                  */ out << bits(my.t->lifespan);
    /* int          light_quality             */ out << bits(my.t->light_quality);
    /* int          light_strength            */ out << bits(my.t->light_strength);
    /* int          stat_attack               */ out << bits(my.t->stat_attack);
    /* int          stat_constitution         */ out << bits(my.t->stat_constitution);
    /* int          stat_defence              */ out << bits(my.t->stat_defence);
    /* int          stat_strength             */ out << bits(my.t->stat_strength);
    /* int          owned_count               */ out << bits(my.t->owned_count);
    /* int          minion_count              */ out << bits(my.t->minion_count);
    /* int          charge_count              */ out << bits(my.t->charge_count);
    /* int          stamina                   */ out << bits(my.t->stamina);
    /* int          stamina_max               */ out << bits(my.t->stamina_max);
    /* int          enchant                   */ out << bits(my.t->enchant);
    /* int          enchant_max               */ out << bits(my.t->enchant_max);
    /* int          poison                    */ out << bits(my.t->poison);
    /* int          stats01                   */ out << bits(my.t->stats01);
    /* int          stats02                   */ out << bits(my.t->stats02);
    /* int          stats03                   */ out << bits(my.t->stats03);
    /* int          stats04                   */ out << bits(my.t->stats04);
    /* int          stats05                   */ out << bits(my.t->stats05);
    /* int          stats06                   */ out << bits(my.t->stats06);
    /* int          stats07                   */ out << bits(my.t->stats07);
    /* int          stats08                   */ out << bits(my.t->stats08);
    /* int          stats09                   */ out << bits(my.t->stats09);
    /* int          stats10                   */ out << bits(my.t->stats10);
    /* int          stats11                   */ out << bits(my.t->stats11);
    /* int          stats12                   */ out << bits(my.t->stats12);
    /* int          stats17                   */ out << bits(my.t->stats17);
    /* int          stats_stats19             */ out << bits(my.t->stats_stats19);
    /* int          submerged_offset          */ out << bits(my.t->submerged_offset);
    /* int          throw_distance            */ out << bits(my.t->throw_distance);
    /* int          tick_rate_tenths          */ out << bits(my.t->tick_rate_tenths);
    /* int          tick_resurrect_when       */ out << bits(my.t->tick_resurrect_when);
    /* point        bag_position              */ out << bits(my.t->bag_position);
    /* point        wander_target             */ out << bits(my.t->wander_target);
    /* point     where_i_dropped_an_item_last */ out << bits(my.t->where_i_dropped_an_item_last);
    /* point   where_i_failed_to_collect_last */ out << bits(my.t->where_i_failed_to_collect_last);
    /* std::array<std::array<ThingId > >      */ out << bits(my.t->bag);
    /* std::list<ThingId>   carrying          */ out << bits(my.t->carrying);
    /* std::list<ThingId>   skills            */ out << bits(my.t->skills);
    /* std::string          msg               */ out << bits(my.t->msg);
    /* std::vector<ThingId> enemies           */ out << bits(my.t->enemies);
    /* std::vector<point>   move_path         */ out << bits(my.t->move_path);
    /* std::vector<uint16_t> inventory_id     */ out << bits(my.t->inventory_id);
    /* std::vector<uint16_t> skillbox_id      */ out << bits(my.t->skillbox_id);
    /* timestamp_t  timestamp_born            */ out << bits(my.t->timestamp_born);
    /* timestamp_t  timestamp_bounce_begin    */ out << bits(my.t->timestamp_bounce_begin);
    /* timestamp_t  timestamp_bounce_end      */ out << bits(my.t->timestamp_bounce_end);
    /* timestamp_t  timestamp_fadeup_begin    */ out << bits(my.t->timestamp_fadeup_begin);
    /* timestamp_t  timestamp_fadeup_end      */ out << bits(my.t->timestamp_fadeup_end);
    /* timestamp_t  timestamp_fall_begin      */ out << bits(my.t->timestamp_fall_begin);
    /* timestamp_t  timestamp_fall_end        */ out << bits(my.t->timestamp_fall_end);
    /* timestamp_t  timestamp_flip_start      */ out << bits(my.t->timestamp_flip_start);
    /* timestamp_t  timestamp_hunger_tick     */ out << bits(my.t->timestamp_hunger_tick);
    /* timestamp_t  timestamp_jump_begin      */ out << bits(my.t->timestamp_jump_begin);
    /* timestamp_t  timestamp_jump_end        */ out << bits(my.t->timestamp_jump_end);
    /* timestamp_t  timestamp_unused2         */ out << bits(my.t->timestamp_unused2);
    /* timestamp_t  timestamp_unused1         */ out << bits(my.t->timestamp_unused1);
    /* timestamp_t  timestamp_last_wander_try */ out << bits(my.t->timestamp_last_wander_try);
    /* timestamp_t  timestamp_lunge_begin     */ out << bits(my.t->timestamp_lunge_begin);
    /* timestamp_t  timestamp_lunge_end       */ out << bits(my.t->timestamp_lunge_end);
    /* timestamp_t  timestamp_move_begin      */ out << bits(my.t->timestamp_move_begin);
    /* timestamp_t  timestamp_move_end        */ out << bits(my.t->timestamp_move_end);
    /* timestamp_t  timestamp_sleep_end       */ out << bits(my.t->timestamp_sleep_end);
    /* uint32_t     tick                      */ out << bits(my.t->tick);
    /* uint32_t     tick_last_did_something   */ out << bits(my.t->tick_last_did_something);
    /* uint32_t     tick_last_location_check  */ out << bits(my.t->tick_last_location_check);
    /* uint32_t     tick_last_escape          */ out << bits(my.t->tick_last_escape);
    /* uint32_t     tick_last_level_change    */ out << bits(my.t->tick_last_level_change);
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
    auto start = out.tellp();
    WRITE_MAGIC(THING_MAGIC_BEGIN + (int) sizeof(Thing));

    const std::string name(tp_id_map[my.t->tp_id - 1]->name());
    out << bits(name);

    bool monst = (my.t->monstp != nullptr);
    out << bits(monst);
    if (monst) {
        out << bits(my.t->monstp);
    }

    /////////////////////////////////////////////////////////////////////////
    // Keep these in the same order as my_thing.h and save/load
    /////////////////////////////////////////////////////////////////////////
    out << bits(my.t->tp_id);
    out << bits(my.t->id);
    out << bits(my.t->interpolated_mid_at);
    out << bits(my.t->last_mid_at);
    out << bits(my.t->mid_at);
    out << bits(my.t->last_attached);
    out << bits(my.t->last_blit_br);
    out << bits(my.t->last_blit_tl);
    out << bits(my.t->last_blit_at);
    out << bits(my.t->timestamp_next_frame);
    out << bits(my.t->tile_curr);
    out << bits(my.t->alpha);
    out << bits(my.t->z_depth);
    uint8_t dir = my.t->dir; out << bits(dir);

    /////////////////////////////////////////////////////////////////////////
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    //
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    // v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
    /////////////////////////////////////////////////////////////////////////
    uint64_t bits64 = 0;
    int shift = 0;
    /* uint64_t */ bits64 |= my.t->has_ever_moved                << shift; shift++;
    /* uint64_t */ bits64 |= my.t->has_light                     << shift; shift++;
    /* uint64_t */ bits64 |= my.t->inited_tiles                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_activated                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_attached                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_being_destroyed            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_blitted                    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_bouncing                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_changing_level             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_dead                       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_dying                      << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_facing_left                << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_fadeup                     << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_falling                    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_hidden                     << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_hungry                     << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_in_lava                    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_in_water                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_jumping                    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_moving                     << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_open                       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_resurrected                << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_resurrecting               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_resurrection_blocked       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_sleeping                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_starving                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_the_grid                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_ascend_dungeon  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_ascend_sewer    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_descend_dungeon << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_descend_sewer   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_fall            << shift; shift++;
    if (shift >= (int)(sizeof(bits64) * 8)) {
        ERR("Ran out of bits in serialization");
    }
    out << bits(bits64);

    bits64 = 0;
    shift = 0;
    /* uint64_t */ bits64 |= my.t->i_set_is_acid                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_poison                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_blood                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_chasm                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_corpse                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_bridge                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_corridor               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_deep_water             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_shallow_water          << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_dirt                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_dry_fungus             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_enchantstone           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_skillstone             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_foilage                << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_spiderweb              << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_door                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_ascend_dungeon         << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_descend_dungeon        << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_ascend_sewer           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_descend_sewer          << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_fire                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_floor                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_food                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_minion_generator       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_gold                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_hazard                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_extreme_hazard         << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_treasure_class_a       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_treasure_class_b       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_treasure_class_c       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_key                    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_lava                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_light_blocker          << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_monst                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_movement_blocking_hard << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_movement_blocking_soft << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_potion                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_wand                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_ripple                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_rock                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_secret_door            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_smoke                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_brazier                << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_barrel                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_treasure               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_wall                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_gfx_water                 << shift; shift++;
    if (shift >= (int)(sizeof(bits64) * 8)) {
        ERR("Ran out of bits in serialization");
    }
    out << bits(bits64);

    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    //
    // Not worth saving as temporary
    //
    // /* uint64_t */ bits64 |= my.t->has_external_particle << shift; shift++;
    // /* uint64_t */ bits64 |= my.t->has_internal_particle << shift; shift++;
    // /* uint64_t */ bits64 |= my.t->has_laser << shift; shift++;
    // /* uint64_t */ bits64 |= my.t->has_projectile << shift; shift++;

    WRITE_MAGIC(THING_MAGIC_END);

    if (g_opt_debug4) {
        auto diff = out.tellp() - start;
        LOG("SAVE %dbytes %s TP %d ID %x last_mid_at %f,%f monstp %p", 
            (int)diff, name.c_str(), my.t->tp_id, my.t->id.id, 
            my.t->last_mid_at.x, my.t->last_mid_at.y, my.t->monstp);
    }
    return (out);
}

std::ostream& operator<<(std::ostream &out, Bits<Levelp & > const my)
{_
    if (g_opt_debug4) {
        my.t->log("Save");
    }

    out << bits(my.t->timestamp_dungeon_created);
    timestamp_t timestamp_dungeon_saved = time_get_time_ms();
    out << bits(timestamp_dungeon_saved);
    out << bits(my.t->timestamp_fade_out_begin);
    out << bits(my.t->timestamp_fade_in_begin);

    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_light_blocker {};          */ out << bits(my.t->_is_light_blocker);
    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking_hard {}; */ out << bits(my.t->_is_movement_blocking_hard);
    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_movement_blocking_soft {}; */ out << bits(my.t->_is_movement_blocking_soft);
    /* std::array<std::array<bool, MAP_HEIGHT>, MAP_WIDTH> _is_visited {};                */ out << bits(my.t->_is_visited);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _fade_in_map {};            */ out << bits(my.t->_fade_in_map);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _heatmap {};                */ out << bits(my.t->_heatmap);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_acid {};                */ out << bits(my.t->_is_acid);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_poison {};              */ out << bits(my.t->_is_poison);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};               */ out << bits(my.t->_is_blood);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_chasm {};               */ out << bits(my.t->_is_chasm);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};              */ out << bits(my.t->_is_corpse);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_bridge {};              */ out << bits(my.t->_is_bridge);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};            */ out << bits(my.t->_is_corridor);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};          */ out << bits(my.t->_is_deep_water);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_shallow_water {};       */ out << bits(my.t->_is_shallow_water);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};                */ out << bits(my.t->_is_dirt);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dry_fungus {};          */ out << bits(my.t->_is_dry_fungus);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_enchantstone {};        */ out << bits(my.t->_is_enchantstone);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_skillstone {};          */ out << bits(my.t->_is_skillstone);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_foilage {};             */ out << bits(my.t->_is_foilage);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_spiderweb {};           */ out << bits(my.t->_is_spiderweb);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_door {};                */ out << bits(my.t->_is_door);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};             */ out << bits(my.t->_is_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ascend_dungeon {};      */ out << bits(my.t->_is_ascend_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_descend_dungeon {};     */ out << bits(my.t->_is_descend_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ascend_sewer {};        */ out << bits(my.t->_is_ascend_sewer);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_descend_sewer {};       */ out << bits(my.t->_is_descend_sewer);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_fire {};                */ out << bits(my.t->_is_fire);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};               */ out << bits(my.t->_is_floor);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_food {};                */ out << bits(my.t->_is_food);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_minion_generator {};    */ out << bits(my.t->_is_minion_generator);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_gold {};                */ out << bits(my.t->_is_gold);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};              */ out << bits(my.t->_is_hazard);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_extreme_hazard {};      */ out << bits(my.t->_is_extreme_hazard);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_a {};    */ out << bits(my.t->_is_treasure_class_a);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_b {};    */ out << bits(my.t->_is_treasure_class_b);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_c {};    */ out << bits(my.t->_is_treasure_class_c);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_key {};                 */ out << bits(my.t->_is_key);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};                */ out << bits(my.t->_is_lava);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lit {};                 */ out << bits(my.t->_is_lit);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_monst {};               */ out << bits(my.t->_is_monst);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_potion {};              */ out << bits(my.t->_is_potion);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wand {};                */ out << bits(my.t->_is_wand);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ripple {};              */ out << bits(my.t->_is_ripple);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};                */ out << bits(my.t->_is_rock);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};         */ out << bits(my.t->_is_secret_door);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_smoke {};               */ out << bits(my.t->_is_smoke);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_brazier {};             */ out << bits(my.t->_is_brazier);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_barrel {};              */ out << bits(my.t->_is_barrel);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure {};            */ out << bits(my.t->_is_treasure);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};                */ out << bits(my.t->_is_wall);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _gfx_water {};              */ out << bits(my.t->_gfx_water);

    /* all_thing_ids_at */      out << bits(my.t->all_thing_ids_at);
    /* cursor_at */             out << bits(my.t->cursor_at);
    /* cursor_at_old */         out << bits(my.t->cursor_at_old);
    /* cursor_found */          out << bits(my.t->cursor_found);
    /* cursor_needs_update */   out << bits(my.t->cursor_needs_update);
    /* heatmap_valid */         out << bits(my.t->heatmap_valid);
    /* is_starting */           out << bits(my.t->is_starting);
    /* map_at */                out << bits(my.t->map_at);
    /* map_br */                out << bits(my.t->map_br);
    /* map_changed */           out << bits(my.t->map_changed);
    /* map_follow_player */     out << bits(my.t->map_follow_player);
    /* map_tl */                out << bits(my.t->map_tl);
    /* map_wanted_at */         out << bits(my.t->map_wanted_at);
    /* minimap_valid */         out << bits(my.t->minimap_valid);
    /* is_dungeon_level */      out << bits(my.t->is_dungeon_level);
    /* is_sewer_level */        out << bits(my.t->is_sewer_level);
    /* monst_count */           out << bits(my.t->monst_count);
    /* mouse */                 out << bits(my.t->mouse);
    /* mouse_old */             out << bits(my.t->mouse_old);
    /* pixel_map_at */          out << bits(my.t->pixel_map_at);
    /* seed */                  out << bits(my.t->seed);
    /* world_at */              out << bits(my.t->world_at);
    /* minx */                  out << bits(my.t->minx);
    /* maxx */                  out << bits(my.t->maxx);
    /* miny */                  out << bits(my.t->miny);
    /* maxy */                  out << bits(my.t->maxy);

    for (auto x = 0; x < MAP_WIDTH; x++) {
        for (auto y = 0; y < MAP_HEIGHT; y++) {
            for (auto slot = 0; slot < MAP_SLOTS; slot++) {
                auto id = get(my.t->all_thing_ids_at, x, y, slot);
                if (id.ok()) {
                    const Thingp t = my.t->thing_find(id);
                    if (!t) {
                        continue;
                    }
                    if (g_opt_debug4) {
                        t->log("Save");
                    }
                    out << bits(t);
                }
            }
        }
    }
    WRITE_MAGIC(THING_MAGIC_FINAL);

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
                    CON("DUNGEON: Save level %d,%d,%d", p.x, p.y, p.z);
                    out << bits(p);
                    out << bits(exists);
                    out << bits(l);
                    auto eol = GAME_SAVE_MARKER_EOL;
                    out << bits(eol);
                    CON("DUNGEON: Saved level %d,%d,%d", p.x, p.y, p.z);
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
    uint32_t header_size = sizeof(Config);
    /* uint32_t           header_size                  */ out << bits(header_size                       );

    /* float              game_pix_scale_height        */ out << bits(my.t.game_pix_scale_height        );
    /* float              game_pix_scale_width         */ out << bits(my.t.game_pix_scale_width         );
    /* float              game_pix_zoom                */ out << bits(my.t.game_pix_zoom                );
    /* float              one_pixel_height             */ out << bits(my.t.one_pixel_height             );
    /* float              one_pixel_width              */ out << bits(my.t.one_pixel_width              );
    /* float              tile_pix_height              */ out << bits(my.t.tile_pix_height              );
    /* float              tile_pix_width               */ out << bits(my.t.tile_pix_width               );
    /* float              tile_pixel_height            */ out << bits(my.t.tile_pixel_height            );
    /* float              tile_pixel_width             */ out << bits(my.t.tile_pixel_width             );
    /* float              ui_pix_scale_height          */ out << bits(my.t.ui_pix_scale_height          );
    /* float              ui_pix_scale_width           */ out << bits(my.t.ui_pix_scale_width           );
    /* float              ui_pix_zoom                  */ out << bits(my.t.ui_pix_zoom                  );
    /* float              video_w_h_ratio              */ out << bits(my.t.video_w_h_ratio              );
    /* int                debug_mode                   */ out << bits(my.t.debug_mode                   );
    /* int                fps_counter                  */ out << bits(my.t.fps_counter                  );
    /* int                gfx_allow_highdpi            */ out << bits(my.t.gfx_allow_highdpi            );
    /* int                gfx_borderless               */ out << bits(my.t.gfx_borderless               );
    /* int                gfx_fullscreen               */ out << bits(my.t.gfx_fullscreen               );
    /* int                gfx_fullscreen_desktop       */ out << bits(my.t.gfx_fullscreen_desktop       );
    /* int                gfx_inverted                 */ out << bits(my.t.gfx_inverted                 );
    /* int                gfx_minimap                  */ out << bits(my.t.gfx_minimap                  );
    /* int                gfx_show_hidden              */ out << bits(my.t.gfx_show_hidden              );
    /* int                gfx_vsync_enable             */ out << bits(my.t.gfx_vsync_enable             );
    /* int                tile_height                  */ out << bits(my.t.tile_height                  );
    /* int                tile_width                   */ out << bits(my.t.tile_width                   );
    /* int32_t            config_pix_height            */ out << bits(my.t.config_pix_height            );
    /* int32_t            config_pix_width             */ out << bits(my.t.config_pix_width             );
    /* int32_t            game_pix_height              */ out << bits(my.t.game_pix_height              );
    /* int32_t            game_pix_width               */ out << bits(my.t.game_pix_width               );
    /* int32_t            ui_pix_height                */ out << bits(my.t.ui_pix_height                );
    /* int32_t            ui_pix_width                 */ out << bits(my.t.ui_pix_width                 );
    /* int32_t            window_pix_height            */ out << bits(my.t.window_pix_height            );
    /* int32_t            window_pix_width             */ out << bits(my.t.window_pix_width             );
    /* uint16_y           ascii_gl_height              */ out << bits(my.t.ascii_gl_height              );
    /* uint16_y           ascii_gl_width               */ out << bits(my.t.ascii_gl_width               );
    /* uint32_t           key_action0                  */ out << bits(my.t.key_action0                  );
    /* uint32_t           key_action1                  */ out << bits(my.t.key_action1                  );
    /* uint32_t           key_action2                  */ out << bits(my.t.key_action2                  );
    /* uint32_t           key_action3                  */ out << bits(my.t.key_action3                  );
    /* uint32_t           key_action4                  */ out << bits(my.t.key_action4                  );
    /* uint32_t           key_action5                  */ out << bits(my.t.key_action5                  );
    /* uint32_t           key_action6                  */ out << bits(my.t.key_action6                  );
    /* uint32_t           key_action7                  */ out << bits(my.t.key_action7                  );
    /* uint32_t           key_action8                  */ out << bits(my.t.key_action8                  );
    /* uint32_t           key_action9                  */ out << bits(my.t.key_action9                  );
    /* uint32_t           key_attack                   */ out << bits(my.t.key_attack                   );
    /* uint32_t           key_console                  */ out << bits(my.t.key_console                  );
    /* uint32_t           key_drop                     */ out << bits(my.t.key_drop                     );
    /* uint32_t           key_eat                      */ out << bits(my.t.key_eat                      );
    /* uint32_t           key_help                     */ out << bits(my.t.key_help                     );
    /* uint32_t           key_inventory                */ out << bits(my.t.key_inventory                );
    /* uint32_t           key_jump                     */ out << bits(my.t.key_jump                     );
    /* uint32_t           key_load                     */ out << bits(my.t.key_load                     );
    /* uint32_t           key_map_down                 */ out << bits(my.t.key_map_down                 );
    /* uint32_t           key_map_left                 */ out << bits(my.t.key_map_left                 );
    /* uint32_t           key_map_right                */ out << bits(my.t.key_map_right                );
    /* uint32_t           key_map_up                   */ out << bits(my.t.key_map_up                   );
    /* uint32_t           key_move_down                */ out << bits(my.t.key_move_down                );
    /* uint32_t           key_move_left                */ out << bits(my.t.key_move_left                );
    /* uint32_t           key_move_right               */ out << bits(my.t.key_move_right               );
    /* uint32_t           key_move_up                  */ out << bits(my.t.key_move_up                  );
    /* uint32_t           key_pause                    */ out << bits(my.t.key_pause                    );
    /* uint32_t           key_quit                     */ out << bits(my.t.key_quit                     );
    /* uint32_t           key_save                     */ out << bits(my.t.key_save                     );
    /* uint32_t           key_screenshot               */ out << bits(my.t.key_screenshot               );
    /* uint32_t           key_throw                    */ out << bits(my.t.key_throw                    );
    /* uint32_t           key_unused3                  */ out << bits(my.t.key_unused3                  );
    /* uint32_t           key_unused4                  */ out << bits(my.t.key_unused4                  );
    /* uint32_t           key_unused5                  */ out << bits(my.t.key_unused5                  );
    /* uint32_t           key_use                      */ out << bits(my.t.key_use                      );
    /* uint32_t           key_wait_or_collect          */ out << bits(my.t.key_wait_or_collect          );
    /* uint32_t           key_zoom_in                  */ out << bits(my.t.key_zoom_in                  );
    /* uint32_t           key_zoom_out                 */ out << bits(my.t.key_zoom_out                 );
    /* uint32_t           music_volume                 */ out << bits(my.t.music_volume                 );
    /* uint32_t           sdl_delay                    */ out << bits(my.t.sdl_delay                    );
    /* uint32_t           sound_volume                 */ out << bits(my.t.sound_volume                 );
    /* std::string        player name                  */ out << bits(g_opt_player_name);
    /* std::string        seed name                    */ out << bits(g_opt_seed_name);

    out << bits(my.t.hiscores);

    return (out);
}

std::ostream& operator<<(std::ostream &out,
                         Bits<const class Game & > const my)
{_
    uint32_t header_size = sizeof(Game);
    out << bits(my.t.version);
    out << bits(header_size);
    out << bits(my.t.save_slot);
    out << bits(my.t.save_meta);
    out << bits(my.t.save_file);
    out << bits(my.t.appdata);
    out << bits(my.t.saved_dir);
    out << bits(my.t.config);
    out << bits(my.t.world);

    /* bool               hard_paused                  */ out << bits(my.t.hard_paused);
    /* bool               soft_paused                  */ out << bits(my.t.soft_paused);
    /* bool               started                      */ out << bits(my.t.started);
    /* bool               things_are_moving            */ out << bits(my.t.things_are_moving);
    /* fpoint             mouse_over                   */ out << bits(my.t.mouse_over);
    /* point              minimap_over                 */ out << bits(my.t.minimap_over);
    /* int                seed                         */ out << bits(my.t.seed);
    /* std::string        seed_name                    */ out << bits(my.t.seed_name);
    /* point3d            current_level                */ out << bits(my.t.current_level);
    /* uint32_t           inventory_highlight_slot     */ out << bits(my.t.inventory_highlight_slot);
    /* uint32_t           skillbox_highlight_slot      */ out << bits(my.t.skillbox_highlight_slot);
    /* uint32_t           previous_slot                */ out << bits(my.t.previous_slot);
    /* uint32_t           fps_value                    */ out << bits(my.t.fps_value);
    /* uint32_t           tick_completed               */ out << bits(my.t.tick_completed);
    /* uint32_t           tick_current                 */ out << bits(my.t.tick_current);

    out << bits(wid_topcon_serialize());
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

#if 0
    if (g_opt_debug4) {
        std::cout << "before compression ";
        (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);
    }
#endif

    if (lzo_init() != LZO_E_OK) {
        ERR("LZO init fail: enable '-DLZO_DEBUG' for diagnostics)");
    }

    HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

    lzo_uint compressed_len = 0;
    int r = lzo1x_1_compress((lzo_bytep)uncompressed, uncompressed_len,
                             (lzo_bytep)compressed, &compressed_len, wrkmem);
    if (r == LZO_E_OK) {
        CON("DUNGEON: Saved as %s, compress %luMb -> %luMb",
            file_to_save.c_str(),
            (unsigned long) uncompressed_len / (1024 * 1024),
            (unsigned long) compressed_len / (1024 * 1024));
    } else {
        ERR("LZO internal error - compression failed: %d", r);
        return false;
    }

    //
    // Uncompress and check the data matches
    //
    if (g_opt_debug4) {
        HEAP_ALLOC(tmp_compressed, compressed_len);
        HEAP_ALLOC(tmp_uncompressed, uncompressed_len);
        memcpy(tmp_compressed, compressed, compressed_len);

        lzo_uint new_len = 0;
        int r = lzo1x_decompress((lzo_bytep)tmp_compressed, compressed_len,
                                 (lzo_bytep)tmp_uncompressed, &new_len, NULL);
        if (r == LZO_E_OK && new_len == uncompressed_len) {
            if (memcmp(tmp_uncompressed, uncompressed, uncompressed_len)) {
                ERR("LZO compress-decompress failed");
            }
        } else {
            /* this should NEVER happen */
            ERR("LZO internal error - decompression failed: %d", r);
            return false;
        }
    }

    //
    // Dump the post compress buffer
    //
#if 0
    if (g_opt_debug4) {
        std::cout << "after compression ";
        (void) hexdump((const unsigned char *)compressed, compressed_len);
    }
#endif

    //
    // Save the post compress buffer
    //
    uint32_t cs = csum((char*)uncompressed, uncompressed_len);

    auto ofile = fopen(file_to_save.c_str(), "wb");
    fwrite((char*) &uncompressed_len, sizeof(uncompressed_len), 1, ofile);
    fwrite((char*) &cs, sizeof(cs), 1, ofile);
    fwrite(compressed, compressed_len, 1, ofile);
    fclose(ofile);

    free(uncompressed);
    free(compressed);
    free(wrkmem);

    return true;
}

void
Game::save (void)
{_
    LOG("-");
    CON("DUNGEON: Saving %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    save(save_file);

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: Saved %s, seed %u", save_file.c_str(), seed);
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
    CON("DUNGEON: Saving %s", save_file.c_str());
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    LOG("v v v v v v v v v v v v v v v v v v v v v v v v v v v ");

    save(save_file);

    LOG("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ");
    LOG("| | | | | | | | | | | | | | | | | | | | | | | | | | | ");
    CON("DUNGEON: Saved %s, seed %u", save_file.c_str(), seed);
    LOG("-");

    TOPCON("Saved the game to %s.", save_file.c_str());
}

void
Game::save_config (void)
{_
    auto filename = saved_dir + "config";
    std::ofstream out(filename, std::ios::binary);
    const Config &c = game->config;
    out << bits(c);
    game->config.dump("WROTE:");
}

static WidPopup *wid_save;

static void wid_save_destroy (void)
{_
    delete wid_save;
    wid_save = nullptr;
    game->hard_unpause();
}

static uint8_t wid_save_key_up (Widp w, const struct SDL_Keysym *key)
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
            default: {_
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
                    case '9': {_
                        int slot = c - '0';
                        game->save(slot);
                        wid_save_destroy();
                        return true;
                    }
                    case 'b':
                    case SDLK_ESCAPE: {_
                        CON("PLAYER: Save game cancelled");
                        wid_save_destroy();
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

static uint8_t wid_save_key_down (Widp w, const struct SDL_Keysym *key)
{_
    if (sdl_shift_held) {
        if (key->scancode == (SDL_Scancode)game->config.key_console) {
            return false;
        }
    }

    return true;
}

static uint8_t wid_save_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
{_
    auto slot = wid_get_int_context(w);
    game->save(slot);
    wid_save_destroy();
    return true;
}

void Game::save_select (void)
{_
    if (wid_save) {
        return;
    }
    game->hard_pause();

    auto m = TERM_WIDTH / 2;
    point tl = make_point(m - UI_WID_POPUP_WIDTH_WIDE / 2,
                          UI_TOPCON_VIS_HEIGHT + 10);
    point br = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2,
                          tl.y + 29);
    auto width = br.x - tl.x;

    wid_save = new WidPopup("Game save", tl, br, 
                            tile_find_mand("save"), "",
                            false, false);
    wid_set_on_key_up(wid_save->wid_popup_container, wid_save_key_up);
    wid_set_on_key_down(wid_save->wid_popup_container, wid_save_key_down);

    game_load_headers_only = true;

    wid_save->log(" ");
    wid_save->log("Choose a save slot. %%fg=red$ESC%%fg=reset$ to cancel");

    int y_at = 3;
    for (auto slot = 0; slot < UI_WID_SAVE_SLOTS; slot++) {
        Game tmp;
        auto tmp_file = saved_dir + "saved-slot-" + std::to_string(slot);
        auto p = wid_save->wid_text_area->wid_text_area;
        auto w = wid_new_square_button(p, "save slot");
        point tl = make_point(0, y_at);
        point br = make_point(width - 2, y_at);

        std::string s = std::to_string(slot) + " ";
        if (!load(tmp_file, tmp)) {
            s += "<empty>";
            wid_set_style(w, UI_WID_STYLE_HORIZ_DARK);
        } else {
            s += tmp.save_meta;
            wid_set_style(w, UI_WID_STYLE_HORIZ_LIGHT);
        }
        wid_set_on_mouse_up(w, wid_save_mouse_up);
        wid_set_int_context(w, slot);

        wid_set_pos(w, tl, br);
        wid_set_text(w, s);
        y_at += 1;
    }
    game_load_headers_only = false;
    wid_update(wid_save->wid_text_area->wid_text_area);
}
