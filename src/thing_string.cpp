//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"

std::string Thing::to_string(void)
{
  TRACE_NO_INDENT();

  auto tpp = tp();
  verify(MTYPE_THING, this);

  if (unlikely(! level)) {
    return (string_sprintf(
        "%" PRIX32 " <not in level> <no tp>%s%s%s%s%s%s%s%s%s%s%s%s %d,%d", id.id, is_sleeping ? "/sleeping" : "",
        is_dead ? "/dead" : "", is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
        is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "", is_visible_to_player ? "/vis" : "/offscreen",
        is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "", is_jumping ? "/jumping" : "", is_moving ? "/mv" : "",
        is_falling ? "/fall" : "", curr_at.x, curr_at.y));
  }

  if (unlikely(! tpp)) {
    TRACE_NO_INDENT();
    return (string_sprintf(
        "%" PRIX32 " L%d <no tp>%s%s%s%s%s%s%s%s%s%s%s%s %d,%d", id.id, level->dungeon_walk_order_level_no,
        is_sleeping ? "/sleeping" : "", is_dead ? "/dead" : "", is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "",
        is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
        is_visible_to_player ? "/vis" : "/offscreen", is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "",
        is_jumping ? "/jumping" : "", is_moving ? "/mv" : "", is_falling ? "/fall" : "", curr_at.x, curr_at.y));
  }

  if (! g_loading) {
    auto l = leader();
    if (l && (l != this)) {
      return (string_sprintf(
          "%" PRIX32 " %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s %d,%d l:%s", id.id, tpp->name().c_str(),
          is_sleeping ? "/sleeping" : "", is_dead ? "/dead" : "", is_scheduled_for_death ? "/dead-sched" : "",
          is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "", is_resurrecting ? "/resurrecting" : "",
          is_visible_to_player ? "/vis" : "/offscreen", is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "",
          is_jumping ? "/jumping" : "", is_moving ? "/mv" : "", is_falling ? "/fall" : "",
          is_changing_level ? "/chg-level" : "", is_waiting_to_ascend_dungeon ? "/asc-dung" : "",
          is_waiting_to_descend_dungeon ? "/des-dung" : "", is_waiting_to_descend_sewer ? "/des-sewer" : "",
          is_waiting_to_ascend_sewer ? "/asc-sewer" : "", curr_at.x, curr_at.y, l->to_short_string().c_str()));
    }
  }

  /*
   * Makes debugs too long
   */

  if (! is_being_destroyed) {
    if (! g_loading && immediate_owner()) {
      auto o = immediate_owner();
      return (string_sprintf(
          "%" PRIX32 " L%d %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s o:%s", id.id, level->dungeon_walk_order_level_no,
          tpp->name().c_str(), is_sleeping ? "/sleeping" : "", is_dead ? "/dead" : "",
          is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
          is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "", is_visible_to_player ? "/vis" : "/offscreen",
          is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "", is_jumping ? "/jumping" : "",
          is_moving ? "/mv" : "", is_falling ? "/fall" : "", is_changing_level ? "/chg-level" : "",
          is_waiting_to_ascend_dungeon ? "/asc-dung" : "", is_waiting_to_descend_dungeon ? "/des-dung" : "",
          is_waiting_to_descend_sewer ? "/des-sewer" : "", is_waiting_to_ascend_sewer ? "/asc-sewer" : "",
          o->to_short_string().c_str()));
    }
  }

  return (string_sprintf(
      "%" PRIX32 " L%d %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s %d,%d", id.id, level->dungeon_walk_order_level_no,
      tpp->name().c_str(), is_sleeping ? "/sleeping" : "", is_dead ? "/dead" : "",
      is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
      is_visible_to_player ? "/vis" : "/offscreen", is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "",
      is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "", is_jumping ? "/jumping" : "", is_moving ? "/mv" : "",
      is_falling ? "/fall" : "", is_changing_level ? "/chg-level" : "",
      is_waiting_to_ascend_dungeon ? "/asc-dung" : "", is_waiting_to_descend_dungeon ? "/des-dung" : "",
      is_waiting_to_descend_sewer ? "/des-sewer" : "", is_waiting_to_ascend_sewer ? "/asc-sewer" : "", curr_at.x,
      curr_at.y));
}

//
// As above but does not show owner or leader - which gets long fast
//
std::string Thing::to_short_string(void)
{
  TRACE_NO_INDENT();

  auto tpp = tp();
  verify(MTYPE_THING, this);

  if (unlikely(! level)) {
    return (string_sprintf(
        "%" PRIX32 " <not in level> <no tp>%s%s%s%s%s%s%s%s%s%s%s%s %d,%d", id.id, is_sleeping ? "/dead" : "",
        is_dead ? "/dead" : "", is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
        is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "", is_visible_to_player ? "/vis" : "/offscreen",
        is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "", is_jumping ? "/jumping" : "", is_moving ? "/mv" : "",
        is_falling ? "/fall" : "", curr_at.x, curr_at.y));
  }

  if (unlikely(! tpp)) {
    TRACE_NO_INDENT();
    return (string_sprintf("%" PRIX32 " L%d <no tp>%s%s%s%s%s%s%s%s%s%s %d,%d", id.id,
                           level->dungeon_walk_order_level_no, is_sleeping ? "/dead" : "", is_dead ? "/dead" : "",
                           is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
                           is_visible_to_player ? "/vis" : "/offscreen", is_on_fire() ? "/onfire" : "",
                           is_hidden ? "/hid" : "", is_jumping ? "/jumping" : "", is_moving ? "/mv" : "",
                           is_falling ? "/fall" : "", curr_at.x, curr_at.y));
  }

  return (string_sprintf(
      "%" PRIX32 " L%d %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s %d,%d", id.id, level->dungeon_walk_order_level_no,
      tpp->name().c_str(), is_sleeping ? "/dead" : "", is_dead ? "/dead" : "",
      is_scheduled_for_death ? "/dead-sched" : "", is_resurrecting ? "/resurrecting" : "",
      is_visible_to_player ? "/vis" : "/offscreen", is_frozen ? "/frozen" : "", is_burnt ? "/burnt" : "",
      is_on_fire() ? "/onfire" : "", is_hidden ? "/hid" : "", is_jumping ? "/jumping" : "", is_moving ? "/mv" : "",
      is_falling ? "/fall" : "", is_changing_level ? "/chg-level" : "",
      is_waiting_to_ascend_dungeon ? "/asc-dung" : "", is_waiting_to_descend_dungeon ? "/des-dung" : "",
      is_waiting_to_descend_sewer ? "/des-sewer" : "", is_waiting_to_ascend_sewer ? "/asc-sewer" : "", curr_at.x,
      curr_at.y));
}

std::string Thing::to_dbg_string(void)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, this);

  return (string_sprintf(
      "L%d %" PRIX32
      " %s (%d,%d)%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s)",
      level->dungeon_walk_order_level_no, id.id, tp() ? tp()->name().c_str() : "notp", curr_at.x, curr_at.y,
      has_ever_moved ? ", has_ever_moved" : "", has_external_particle ? ", has_external_particle" : "",
      has_internal_particle ? ", has_internal_particle" : "", has_light ? ", has_light" : "",
      has_projectile ? ", has_projectile" : "", is_activated ? ", is_activated" : "",
      is_attached ? ", is_attached" : "", is_being_destroyed ? ", is_being_destroyed" : "",
      is_bouncing ? ", is_bouncing" : "", is_changing_level ? ", is_changing_level" : "", is_dead ? ", is_dead" : "",
      is_scheduled_for_death ? ", is_scheduled_for_death" : "", is_dying ? ", is_dying" : "",
      is_facing_left ? ", is_facing_left" : "", is_fadeup ? ", is_fadeup" : "", is_falling ? ", is_falling" : "",
      is_hidden ? ", is_hidden" : "", is_hunger_level_hungry ? ", is_hunger_level_hungry" : "",
      is_jumping ? ", is_jumping" : "", is_moving ? ", is_moving" : "",
      is_visible_to_player ? ", is_visible_to_player" : "", is_open ? ", is_open" : "",
      is_resurrected ? ", is_resurrected" : "", is_resurrecting ? ", is_resurrecting" : "",
      is_resurrection_blocked ? ", is_resurrection_blocked" : "", is_sleeping ? ", is_sleeping" : "",
      is_hunger_level_starving ? ", is_hunger_level_starving" : "", is_the_grid ? ", is_the_grid" : "",
      is_waiting_to_ascend_dungeon ? ", is_waiting_to_ascend_dungeon" : "",
      is_waiting_to_ascend_sewer ? ", is_waiting_to_ascend_sewer" : "",
      is_waiting_to_descend_dungeon ? ", is_waiting_to_descend_dungeon" : "",
      is_waiting_to_descend_sewer ? ", is_waiting_to_descend_sewer" : "",
      is_waiting_to_leave_level_has_completed_fall ? ", is_waiting_to_leave_level_has_completed_fall" : "",
      i_set_water ? ", i_set_water" : "", i_set_is_acid ? ", i_set_is_acid" : "",
      i_set_is_ascend_dungeon ? ", i_set_is_ascend_dungeon" : "",
      i_set_is_ascend_sewer ? ", i_set_is_ascend_sewer" : "", i_set_is_barrel ? ", i_set_is_barrel" : "",
      i_set_is_red_blood ? ", i_set_is_red_blood" : "", i_set_is_brazier ? ", i_set_is_brazier" : "",
      i_set_is_bridge ? ", i_set_is_bridge" : "", i_set_is_chasm ? ", i_set_is_chasm" : "",
      i_set_is_corpse ? ", i_set_is_corpse" : "", i_set_is_corridor ? ", i_set_is_corridor" : "",
      i_set_is_deep_water ? ", i_set_is_deep_water" : "",
      i_set_is_descend_dungeon ? ", i_set_is_descend_dungeon" : "",
      i_set_is_descend_sewer ? ", i_set_is_descend_sewer" : "", i_set_is_dirt ? ", i_set_is_dirt" : "",
      i_set_is_door ? ", i_set_is_door" : "", i_set_is_dry_grass ? ", i_set_is_dry_grass" : "",
      i_set_is_enchant_stone ? ", i_set_is_enchant_stone" : "",
      i_set_is_cursor_path_hazard ? ", i_set_is_cursor_path_hazard" : "", i_set_is_fire ? ", i_set_is_fire" : "",
      i_set_is_floor ? ", i_set_is_floor" : "", i_set_is_foliage ? ", i_set_is_foliage" : "",
      i_set_is_food ? ", i_set_is_food" : "", i_set_is_gold ? ", i_set_is_gold" : "",
      i_set_is_hazard ? ", i_set_is_hazard" : "", i_set_is_key ? ", i_set_is_key" : "",
      i_set_is_lava ? ", i_set_is_lava" : "", i_set_is_light_blocker ? ", i_set_is_light_blocker" : "",
      i_set_is_mob ? ", i_set_is_mob" : "", i_set_is_monst ? ", i_set_is_monst" : "",
      i_set_is_obs_wall_or_door ? ", i_set_is_obs_wall_or_door" : "",
      i_set_is_obs_destructable ? ", i_set_is_obs_destructable" : "",
      i_set_is_poisonous_danger_level ? ", i_set_is_poisonous_danger_level" : "",
      i_set_is_potion ? ", i_set_is_potion" : "", i_set_is_ripple ? ", i_set_is_ripple" : "",
      i_set_is_rock ? ", i_set_is_rock" : "", i_set_is_secret_door ? ", i_set_is_secret_door" : "",
      i_set_is_shallow_water ? ", i_set_is_shallow_water" : "", i_set_is_skill_stone ? ", i_set_is_skill_stone" : "",
      i_set_is_smoke ? ", i_set_is_smoke" : "", i_set_is_spiderweb ? ", i_set_is_spiderweb" : "",
      i_set_is_sticky ? ", i_set_is_sticky" : "", i_set_is_shovable ? ", i_set_is_shovable" : "",
      i_set_is_treasure_type ? ", i_set_is_treasure_type" : "", i_set_is_wall ? ", i_set_is_wall" : "",
      i_set_is_ring ? ", i_set_is_ring" : ""));
}

//
// Like the above, but excludes temporary flags like particles
//
std::string Thing::to_dbg_saved_string(void)
{
  TRACE_NO_INDENT();

  verify(MTYPE_THING, this);

  return (string_sprintf(
      "L%d %" PRIX32
      " %s (%d,%d)%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s"
      "%s%s%s%s%s%s%s%s%s%s%s%s%s%s)",
      level->dungeon_walk_order_level_no, id.id, tp() ? tp()->name().c_str() : "notp", curr_at.x, curr_at.y,
      has_ever_moved ? ", has_ever_moved" : "", has_light ? ", has_light" : "",
      has_projectile ? ", has_projectile" : "", is_activated ? ", is_activated" : "",
      is_attached ? ", is_attached" : "", is_being_destroyed ? ", is_being_destroyed" : "",
      is_bouncing ? ", is_bouncing" : "", is_changing_level ? ", is_changing_level" : "", is_dead ? ", is_dead" : "",
      is_scheduled_for_death ? ", is_scheduled_for_death" : "", is_dying ? ", is_dying" : "",
      is_facing_left ? ", is_facing_left" : "", is_fadeup ? ", is_fadeup" : "", is_falling ? ", is_falling" : "",
      is_hidden ? ", is_hidden" : "", is_hunger_level_hungry ? ", is_hunger_level_hungry" : "",
      is_jumping ? ", is_jumping" : "", is_moving ? ", is_moving" : "",
      is_visible_to_player ? ", is_visible_to_player" : "", is_open ? ", is_open" : "",
      is_resurrected ? ", is_resurrected" : "", is_resurrecting ? ", is_resurrecting" : "",
      is_resurrection_blocked ? ", is_resurrection_blocked" : "", is_sleeping ? ", is_sleeping" : "",
      is_hunger_level_starving ? ", is_hunger_level_starving" : "", is_the_grid ? ", is_the_grid" : "",
      is_waiting_to_ascend_dungeon ? ", is_waiting_to_ascend_dungeon" : "",
      is_waiting_to_ascend_sewer ? ", is_waiting_to_ascend_sewer" : "",
      is_waiting_to_descend_dungeon ? ", is_waiting_to_descend_dungeon" : "",
      is_waiting_to_descend_sewer ? ", is_waiting_to_descend_sewer" : "",
      is_waiting_to_leave_level_has_completed_fall ? ", is_waiting_to_leave_level_has_completed_fall" : "",
      i_set_water ? ", i_set_water" : "", i_set_is_acid ? ", i_set_is_acid" : "",
      i_set_is_ascend_dungeon ? ", i_set_is_ascend_dungeon" : "",
      i_set_is_ascend_sewer ? ", i_set_is_ascend_sewer" : "", i_set_is_barrel ? ", i_set_is_barrel" : "",
      i_set_is_red_blood ? ", i_set_is_red_blood" : "", i_set_is_brazier ? ", i_set_is_brazier" : "",
      i_set_is_bridge ? ", i_set_is_bridge" : "", i_set_is_chasm ? ", i_set_is_chasm" : "",
      i_set_is_corpse ? ", i_set_is_corpse" : "", i_set_is_corridor ? ", i_set_is_corridor" : "",
      i_set_is_deep_water ? ", i_set_is_deep_water" : "",
      i_set_is_descend_dungeon ? ", i_set_is_descend_dungeon" : "",
      i_set_is_descend_sewer ? ", i_set_is_descend_sewer" : "", i_set_is_dirt ? ", i_set_is_dirt" : "",
      i_set_is_door ? ", i_set_is_door" : "", i_set_is_dry_grass ? ", i_set_is_dry_grass" : "",
      i_set_is_enchant_stone ? ", i_set_is_enchant_stone" : "",
      i_set_is_cursor_path_hazard ? ", i_set_is_cursor_path_hazard" : "", i_set_is_fire ? ", i_set_is_fire" : "",
      i_set_is_floor ? ", i_set_is_floor" : "", i_set_is_foliage ? ", i_set_is_foliage" : "",
      i_set_is_food ? ", i_set_is_food" : "", i_set_is_gold ? ", i_set_is_gold" : "",
      i_set_is_hazard ? ", i_set_is_hazard" : "", i_set_is_key ? ", i_set_is_key" : "",
      i_set_is_lava ? ", i_set_is_lava" : "", i_set_is_light_blocker ? ", i_set_is_light_blocker" : "",
      i_set_is_mob ? ", i_set_is_mob" : "", i_set_is_monst ? ", i_set_is_monst" : "",
      i_set_is_obs_wall_or_door ? ", i_set_is_obs_wall_or_door" : "",
      i_set_is_obs_destructable ? ", i_set_is_obs_destructable" : "",
      i_set_is_poisonous_danger_level ? ", i_set_is_poisonous_danger_level" : "",
      i_set_is_potion ? ", i_set_is_potion" : "", i_set_is_ripple ? ", i_set_is_ripple" : "",
      i_set_is_rock ? ", i_set_is_rock" : "", i_set_is_secret_door ? ", i_set_is_secret_door" : "",
      i_set_is_shallow_water ? ", i_set_is_shallow_water" : "", i_set_is_skill_stone ? ", i_set_is_skill_stone" : "",
      i_set_is_smoke ? ", i_set_is_smoke" : "", i_set_is_spiderweb ? ", i_set_is_spiderweb" : "",
      i_set_is_sticky ? ", i_set_is_sticky" : "", i_set_is_shovable ? ", i_set_is_shovable" : "",
      i_set_is_treasure_type ? ", i_set_is_treasure_type" : "", i_set_is_wall ? ", i_set_is_wall" : "",
      i_set_is_ring ? ", i_set_is_ring" : ""));
}
