//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
    /* int          bounce_count              */ out << bits(my.t->bounce_count);
    /* int          bag_width                 */ out << bits(my.t->bag_width);
    /* int          bag_height                */ out << bits(my.t->bag_height);
    /* int          gold                      */ out << bits(my.t->gold);
    /* int          lifespan                  */ out << bits(my.t->lifespan);
    /* int          light_quality             */ out << bits(my.t->light_quality);
    /* int          light_strength            */ out << bits(my.t->light_strength);
    /* int          owned_count               */ out << bits(my.t->owned_count);
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
    /* int          stats13                   */ out << bits(my.t->stats13);
    /* int          stats14                   */ out << bits(my.t->stats14);
    /* int          stats15                   */ out << bits(my.t->stats15);
    /* int          stats16                   */ out << bits(my.t->stats16);
    /* int          stats17                   */ out << bits(my.t->stats17);
    /* int          stats18                   */ out << bits(my.t->stats18);
    /* int          stats_stamina             */ out << bits(my.t->stats_stamina);
    /* int          stats_stamina_max         */ out << bits(my.t->stats_stamina_max);
    /* int          stats_defence             */ out << bits(my.t->stats_defence);
    /* int          stats_defence_max         */ out << bits(my.t->stats_defence_max);
    /* int          stats_health              */ out << bits(my.t->stats_health);
    /* int          stats_health_max          */ out << bits(my.t->stats_health_max);
    /* int          stats_strength            */ out << bits(my.t->stats_strength);
    /* int          submerged_offset          */ out << bits(my.t->submerged_offset);
    /* int          tick_rate_tenths          */ out << bits(my.t->tick_rate_tenths);
    /* int          tick_resurrect_when       */ out << bits(my.t->tick_resurrect_when);
    /* point        bag_position              */ out << bits(my.t->bag_position);
    /* point        wander_target             */ out << bits(my.t->wander_target);
    /* point     where_i_dropped_an_item_last */ out << bits(my.t->where_i_dropped_an_item_last);
    /* point   where_i_failed_to_collect_last */ out << bits(my.t->where_i_failed_to_collect_last);
    /* std::list<ThingId>   carrying          */ out << bits(my.t->carrying);
    /* std::string          msg               */ out << bits(my.t->msg);
    /* std::vector<ThingId> inventory_id      */ out << bits(my.t->inventory_id);
    /* std::vector<ThingId> enemies           */ out << bits(my.t->enemies);
    /* std::vector<point>   move_path         */ out << bits(my.t->move_path);
    /* timestamp_t  timestamp_born            */ out << bits(my.t->timestamp_born);
    /* timestamp_t  timestamp_bounce_begin    */ out << bits(my.t->timestamp_bounce_begin);
    /* timestamp_t  timestamp_bounce_end      */ out << bits(my.t->timestamp_bounce_end);
    /* timestamp_t  timestamp_fadeup_begin    */ out << bits(my.t->timestamp_fadeup_begin);
    /* timestamp_t  timestamp_fadeup_end      */ out << bits(my.t->timestamp_fadeup_end);
    /* timestamp_t  timestamp_fall_begin      */ out << bits(my.t->timestamp_fall_begin);
    /* timestamp_t  timestamp_fall_end        */ out << bits(my.t->timestamp_fall_end);
    /* timestamp_t  timestamp_jump_begin      */ out << bits(my.t->timestamp_jump_begin);
    /* timestamp_t  timestamp_jump_end        */ out << bits(my.t->timestamp_jump_end);
    /* timestamp_t  timestamp_flip_start      */ out << bits(my.t->timestamp_flip_start);
    /* timestamp_t  timestamp_hunger_tick     */ out << bits(my.t->timestamp_hunger_tick);
    /* timestamp_t  timestamp_last_tick       */ out << bits(my.t->timestamp_last_tick);
    /* timestamp_t  timestamp_last_ticked     */ out << bits(my.t->timestamp_last_ticked);
    /* timestamp_t  timestamp_last_wander_try */ out << bits(my.t->timestamp_last_wander_try);
    /* timestamp_t  timestamp_lunge_begin     */ out << bits(my.t->timestamp_lunge_begin);
    /* timestamp_t  timestamp_lunge_end       */ out << bits(my.t->timestamp_lunge_end);
    /* timestamp_t  timestamp_move_begin      */ out << bits(my.t->timestamp_move_begin);
    /* timestamp_t  timestamp_move_end        */ out << bits(my.t->timestamp_move_end);
    /* uint32_t     tick                      */ out << bits(my.t->tick);
    /* uint32_t     tick_last_did_something   */ out << bits(my.t->tick_last_did_something);
    /* uint32_t     tick_last_escape          */ out << bits(my.t->tick_last_escape);
    /* uint32_t     tick_last_level_change    */ out << bits(my.t->tick_last_level_change);
    /* bag                                    */ out << bits(my.t->bag);
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
#ifdef ENABLE_DEBUG_SAVE_LOAD
    auto start = out.tellp();
#endif
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
    /* uint64_t */ bits64 |= my.t->has_ever_moved        << shift; shift++;
    /* uint64_t */ bits64 |= my.t->has_external_particle << shift; shift++;
    /* uint64_t */ bits64 |= my.t->has_internal_particle << shift; shift++;
    /* uint64_t */ bits64 |= my.t->has_light             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->inited_tiles          << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_attached           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_being_destroyed    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_blitted            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_bouncing           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_changing_level     << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_dead               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_facing_left        << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_fadeup             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_falling            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_hidden             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_hungry             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_in_lava            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_in_water           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_jumping            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_moving             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_open               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_resurrected        << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_resurrecting       << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_sleeping           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_starving           << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_tick_done          << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_ascend  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_descend << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_waiting_to_fall    << shift; shift++;
    /* uint64_t */ bits64 |= my.t->is_the_grid           << shift; shift++;
    if (shift >= (int)(sizeof(bits64) * 8)) {
        ERR("ran out of bits in serialization");
    }
    out << bits(bits64);

    bits64 = 0;
    shift = 0;
    /* uint64_t */ bits64 |= my.t->i_set_is_acid                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_blood                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_chasm                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_corpse                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_corridor               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_deep_water             << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_dirt                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_door                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_entrance               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_exit                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_fire                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_floor                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_food                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_generator              << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_gold                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_hazard                 << shift; shift++;
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
    /* uint64_t */ bits64 |= my.t->i_set_is_ripple                 << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_rock                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_secret_door            << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_smoke                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_torch                  << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_treasure               << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_wall                   << shift; shift++;
    /* uint64_t */ bits64 |= my.t->i_set_is_water                  << shift; shift++;
    if (shift >= (int)(sizeof(bits64) * 8)) {
        ERR("ran out of bits in serialization");
    }
    out << bits(bits64);

    /////////////////////////////////////////////////////////////////////////
    // ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
    // | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    //
    // Keep these sorted alphabetically to make it easier to see additions
    // and always update game_load.cpp and game_save.cpp
    /////////////////////////////////////////////////////////////////////////

    WRITE_MAGIC(THING_MAGIC_END);

#ifdef ENABLE_DEBUG_SAVE_LOAD
    auto diff = out.tellp() - start;
    LOG("SAVE %dbytes %s TP %d ID %x last_mid_at %f,%f monstp %p", 
        (int)diff, name.c_str(), my.t->tp_id, my.t->id.id, my.t->last_mid_at.x, my.t->last_mid_at.y, my.t->monstp);
#endif
    return (out);
}

std::ostream& operator<<(std::ostream &out,
                         Bits<Level* & > const my)
{_
#ifdef ENABLE_DEBUG_SAVE_LOAD
    my.t->log("save");
#endif
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
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_blood {};               */ out << bits(my.t->_is_blood);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_chasm {};               */ out << bits(my.t->_is_chasm);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corpse {};              */ out << bits(my.t->_is_corpse);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_corridor {};            */ out << bits(my.t->_is_corridor);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_deep_water {};          */ out << bits(my.t->_is_deep_water);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dirt {};                */ out << bits(my.t->_is_dirt);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_door {};                */ out << bits(my.t->_is_door);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_dungeon {};             */ out << bits(my.t->_is_dungeon);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_entrance {};            */ out << bits(my.t->_is_entrance);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_exit {};                */ out << bits(my.t->_is_exit);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_fire {};                */ out << bits(my.t->_is_fire);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_floor {};               */ out << bits(my.t->_is_floor);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_food {};                */ out << bits(my.t->_is_food);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_generator {};           */ out << bits(my.t->_is_generator);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_gold {};                */ out << bits(my.t->_is_gold);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_hazard {};              */ out << bits(my.t->_is_hazard);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_a {};    */ out << bits(my.t->_is_treasure_class_a);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_b {};    */ out << bits(my.t->_is_treasure_class_b);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure_class_c {};    */ out << bits(my.t->_is_treasure_class_c);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_key {};                 */ out << bits(my.t->_is_key);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lava {};                */ out << bits(my.t->_is_lava);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_lit {};                 */ out << bits(my.t->_is_lit);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_monst {};               */ out << bits(my.t->_is_monst);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_potion {};              */ out << bits(my.t->_is_potion);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_ripple {};              */ out << bits(my.t->_is_ripple);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_rock {};                */ out << bits(my.t->_is_rock);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_secret_door {};         */ out << bits(my.t->_is_secret_door);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_smoke {};               */ out << bits(my.t->_is_smoke);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_torch {};               */ out << bits(my.t->_is_torch);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_treasure {};            */ out << bits(my.t->_is_treasure);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_wall {};                */ out << bits(my.t->_is_wall);
    /* std::array<std::array<uint8_t, MAP_HEIGHT>, MAP_WIDTH> _is_water {};               */ out << bits(my.t->_is_water);

    /* all_thing_ids_at */      out << bits(my.t->all_thing_ids_at);
    /* cursor_at */             out << bits(my.t->cursor_at);
    /* cursor_at_old */         out << bits(my.t->cursor_at_old);
    /* cursor_found */          out << bits(my.t->cursor_found);
    /* cursor_needs_update */   out << bits(my.t->cursor_needs_update);
    /* heatmap_valid */         out << bits(my.t->heatmap_valid);
    /* bg_valid */              out << bits(my.t->bg_valid);
    /* is_starting */           out << bits(my.t->is_starting);
    /* map_at */                out << bits(my.t->map_at);
    /* map_br */                out << bits(my.t->map_br);
    /* map_changed */           out << bits(my.t->map_changed);
    /* map_follow_player */     out << bits(my.t->map_follow_player);
    /* map_tl */                out << bits(my.t->map_tl);
    /* map_wanted_at */         out << bits(my.t->map_wanted_at);
    /* minimap_valid */         out << bits(my.t->minimap_valid);
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
#ifdef ENABLE_DEBUG_SAVE_LOAD
                    t->log("save");
#endif
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

    /* float              ascii_gl_height              */ out << bits(my.t.ascii_gl_height              );
    /* float              ascii_gl_width               */ out << bits(my.t.ascii_gl_width               );
    /* float              gfx_zoom                     */ out << bits(my.t.gfx_zoom                     );
    /* float              one_pixel_height             */ out << bits(my.t.one_pixel_height             );
    /* float              one_pixel_width              */ out << bits(my.t.one_pixel_width              );
    /* float              scale_pix_height             */ out << bits(my.t.scale_pix_height             );
    /* float              scale_pix_width              */ out << bits(my.t.scale_pix_width              );
    /* float              tile_pix_height              */ out << bits(my.t.tile_pix_height              );
    /* float              tile_pix_width               */ out << bits(my.t.tile_pix_width               );
    /* float              tile_pixel_height            */ out << bits(my.t.tile_pixel_height            );
    /* float              tile_pixel_width             */ out << bits(my.t.tile_pixel_width             );
    /* float              video_w_h_ratio              */ out << bits(my.t.video_w_h_ratio              );
    /* int                ascii_mode                   */ out << bits(my.t.ascii_mode                   );
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
    /* int32_t            inner_pix_height             */ out << bits(my.t.inner_pix_height             );
    /* int32_t            inner_pix_width              */ out << bits(my.t.inner_pix_width              );
    /* int32_t            outer_pix_height             */ out << bits(my.t.outer_pix_height             );
    /* int32_t            outer_pix_width              */ out << bits(my.t.outer_pix_width              );
    /* int32_t            config_pix_height            */ out << bits(my.t.config_pix_height            );
    /* int32_t            config_pix_width             */ out << bits(my.t.config_pix_width             );
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
    /* uint32_t           key_help                     */ out << bits(my.t.key_help                     );
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
    /* uint32_t           key_unused99                 */ out << bits(my.t.key_unused99                  );
    /* uint32_t           key_console                  */ out << bits(my.t.key_console                  );
    /* uint32_t           key_unused3                  */ out << bits(my.t.key_unused3                  );
    /* uint32_t           key_unused4                  */ out << bits(my.t.key_unused4                  );
    /* uint32_t           key_unused5                  */ out << bits(my.t.key_unused5                  );
    /* uint32_t           key_eat                      */ out << bits(my.t.key_eat                      );
    /* uint32_t           key_throw                    */ out << bits(my.t.key_throw                    );
    /* uint32_t           key_drop                     */ out << bits(my.t.key_drop                     );
    /* uint32_t           key_use                      */ out << bits(my.t.key_use                      );
    /* uint32_t           key_wait_or_collect                     */ out << bits(my.t.key_wait_or_collect                     );
    /* uint32_t           key_zoom_in                  */ out << bits(my.t.key_zoom_in                  );
    /* uint32_t           key_zoom_out                 */ out << bits(my.t.key_zoom_out                 );
    /* uint32_t           music_volume                 */ out << bits(my.t.music_volume                 );
    /* uint32_t           sdl_delay                    */ out << bits(my.t.sdl_delay                    );
    /* uint32_t           sound_volume                 */ out << bits(my.t.sound_volume                 );
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
    /* fpoint             mouse_over                   */ out << bits(my.t.mouse_over);
    /* int                seed                         */ out << bits(my.t.seed);
    /* std::string        seed_name                    */ out << bits(my.t.seed_name);
    /* point3d            current_level                */ out << bits(my.t.current_level);
    /* uint32_t           inventory_highlight_slot     */ out << bits(my.t.inventory_highlight_slot);
    /* uint32_t           previous_slot                */ out << bits(my.t.previous_slot);
    /* uint32_t           fps_value                    */ out << bits(my.t.fps_value);
    /* uint32_t           things_are_moving            */ out << bits(my.t.things_are_moving);
    /* uint32_t           tick_completed               */ out << bits(my.t.tick_completed);
    /* uint32_t           tick_current                 */ out << bits(my.t.tick_current);

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

#ifdef ENABLE_DEBUG_SAVE_LOAD_HEX
    std::cout << "before compression ";
    (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);
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

#ifdef ENABLE_DEBUG_SAVE_CHECK
    //
    // Uncompress and check the data matches
    //
    {
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
#endif

    //
    // Dump the post compress buffer
    //
#ifdef ENABLE_DEBUG_SAVE_LOAD_HEX
    std::cout << "after compression ";
    (void) hexdump((const unsigned char *)compressed, compressed_len);
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

    MINICON("Saved the game to %s", save_file.c_str());
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
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
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

uint8_t wid_save_key_down (Widp w, const struct SDL_KEYSYM *key)
{_
    if (key->scancode == (SDL_Scancode)game->config.key_console) {
        return false;
    }

    return true;
}

uint8_t wid_save_mouse_up (Widp w, int32_t x, int32_t y, uint32_t button)
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
                          UI_MINICON_VIS_HEIGHT + 2);
    point br = make_point(m + UI_WID_POPUP_WIDTH_WIDE / 2,
                          tl.y + 19);
    auto width = br.x - tl.x;

    wid_save = new WidPopup("Game save", tl, br, tile_find_mand("save"), "");
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
        point br = make_point(width - 3, y_at);

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
