//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::level_pop(void)
{
  TRACE_NO_INDENT();

  if (! is_attached) {
    return;
  }
  is_attached = false;

#if 0
  if (is_torch()) {
    con("pop at %d,%d", last_attached.x, last_attached.y);
  }
#endif

  auto x = last_attached.x;
  auto y = last_attached.y;

  if (! is_the_grid) {
    if (i_set_is_acid) {
      i_set_is_acid = false;
      level->is_acid_unset(x, y);
    }
    if (i_set_is_red_blood) {
      i_set_is_red_blood = false;
      level->is_red_blood_unset(x, y);
    }
    if (i_set_is_green_blood) {
      i_set_is_green_blood = false;
      level->is_green_blood_unset(x, y);
    }
    if (i_set_is_chasm) {
      i_set_is_chasm = false;
      level->is_chasm_unset(x, y);
    }
    if (i_set_is_corpse) {
      i_set_is_corpse = false;
      level->is_corpse_unset(x, y);
    }
    if (i_set_is_corridor) {
      i_set_is_corridor = false;
      level->is_corridor_unset(x, y);
    }
    if (i_set_is_bridge) {
      i_set_is_bridge = false;
      level->is_bridge_unset(x, y);
    }
    if (i_set_is_shallow_water) {
      i_set_is_shallow_water = false;
      level->is_shallow_water_unset(x, y);
    }
    if (i_set_is_deep_water) {
      i_set_is_deep_water = false;
      level->is_deep_water_unset(x, y);
    }
    if (i_set_is_dirt) {
      i_set_is_dirt = false;
      level->is_dirt_unset(x, y);
    }
    if (i_set_is_dry_grass) {
      i_set_is_dry_grass = false;
      level->is_dry_grass_unset(x, y);
    }
    if (i_set_is_wet_grass) {
      i_set_is_wet_grass = false;
      level->is_wet_grass_unset(x, y);
    }
    if (i_set_is_dry_grass) {
      i_set_is_dry_grass = false;
      level->is_dry_grass_unset(x, y);
    }
    if (i_set_is_enchantstone) {
      i_set_is_enchantstone = false;
      level->is_enchantstone_unset(x, y);
    }
    if (i_set_is_skillstone) {
      i_set_is_skillstone = false;
      level->is_skillstone_unset(x, y);
    }
    if (i_set_is_foliage) {
      i_set_is_foliage = false;
      level->is_foliage_unset(x, y);
    }
    if (i_set_is_carnivorous_plant) {
      i_set_is_carnivorous_plant = false;
      level->is_carnivorous_plant_unset(x, y);
    }
    if (i_set_is_spiderweb) {
      i_set_is_spiderweb = false;
      level->is_spiderweb_unset(x, y);
    }
    if (i_set_is_block_of_ice) {
      i_set_is_block_of_ice = false;
      level->is_block_of_ice_unset(x, y);
    }
    if (i_set_is_able_to_dampen_footsteps) {
      i_set_is_able_to_dampen_footsteps = false;
      level->is_able_to_dampen_footsteps_unset(x, y);
    }
    if (i_set_is_able_to_amplify_footsteps) {
      i_set_is_able_to_amplify_footsteps = false;
      level->is_able_to_amplify_footsteps_unset(x, y);
    }
    if (i_set_is_attackable_by_monst) {
      i_set_is_attackable_by_monst = false;
      level->is_attackable_by_monst_unset(x, y);
    }
    if (i_set_is_attackable_by_player) {
      i_set_is_attackable_by_player = false;
      level->is_attackable_by_player_unset(x, y);
    }
    if (i_set_is_sticky) {
      i_set_is_sticky = false;
      level->is_sticky_unset(x, y);
    }
    if (i_set_is_tentacle) {
      i_set_is_tentacle = false;
      level->is_tentacle_unset(x, y);
    }
    if (i_set_is_shovable) {
      i_set_is_shovable = false;
      level->is_shovable_unset(x, y);
    }
    if (i_set_is_door) {
      i_set_is_door = false;
      level->is_door_unset(x, y);
    }
    if (i_set_is_ascend_dungeon) {
      i_set_is_ascend_dungeon = false;
      level->is_ascend_dungeon_unset(x, y);
    }
    if (i_set_is_descend_dungeon) {
      i_set_is_descend_dungeon = false;
      level->is_descend_dungeon_unset(x, y);
    }
    if (i_set_is_ascend_sewer) {
      i_set_is_ascend_sewer = false;
      level->is_ascend_sewer_unset(x, y);
    }
    if (i_set_is_portal) {
      i_set_is_portal = false;
      level->is_portal_unset(x, y);
    }
    if (i_set_is_portal) {
      i_set_is_portal = false;
      level->is_portal_unset(x, y);
    }
    if (i_set_is_descend_sewer) {
      i_set_is_descend_sewer = false;
      level->is_descend_sewer_unset(x, y);
    }
    if (i_set_is_fire) {
      i_set_is_fire = false;
      level->is_fire_unset(x, y);
    }
    if (i_set_is_floor) {
      i_set_is_floor = false;
      level->is_floor_unset(x, y);
    }
    if (i_set_is_food) {
      i_set_is_food = false;
      level->is_food_unset(x, y);
    }
    if (i_set_is_mob) {
      i_set_is_mob = false;
      level->is_mob_unset(x, y);
    }
    if (i_set_is_gold) {
      i_set_is_gold = false;
      level->is_gold_unset(x, y);
    }
    if (i_set_is_hazard) {
      i_set_is_hazard = false;
      level->is_hazard_unset(x, y);
    }
    if (i_set_is_cursor_path_hazard) {
      i_set_is_cursor_path_hazard = false;
      level->is_cursor_path_hazard_unset(x, y);
    }
    if (i_set_is_cursor_path_blocker) {
      i_set_is_cursor_path_blocker = false;
      level->is_cursor_path_blocker_unset(x, y);
    }
    if (i_set_is_combustible) {
      i_set_is_combustible = false;
      level->is_combustible_unset(x, y);
    }
    if (i_set_is_torch) {
      i_set_is_torch = false;
      level->is_torch_unset(x, y);
    }
    if (i_set_is_burnable) {
      i_set_is_burnable = false;
      level->is_burnable_unset(x, y);
    }
    if (i_set_is_heavy) {
      i_set_is_heavy = false;
      level->is_heavy_unset(x, y);
    }
    if (i_set_is_key) {
      i_set_is_key = false;
      level->is_key_unset(x, y);
    }
    if (i_set_is_lava) {
      i_set_is_lava = false;
      level->is_lava_unset(x, y);
    }
    if (i_set_is_basalt) {
      i_set_is_basalt = false;
      level->is_basalt_unset(x, y);
    }
    if (i_set_is_light_blocker) {
      i_set_is_light_blocker = false;
      level->is_light_blocker_unset(x, y);
    }
    if (i_set_is_light_blocker_for_monst) {
      i_set_is_light_blocker_for_monst = false;
      level->is_light_blocker_for_monst_unset(x, y);
    }
    if (i_set_is_gas_blocker) {
      i_set_is_gas_blocker = false;
      level->is_gas_blocker_unset(x, y);
    }
    if (i_set_noise_blocker) {
      i_set_noise_blocker = false;
      level->noise_blocker_unset(x, y);
    }
    if (i_set_is_monst) {
      i_set_is_monst = false;
      level->monst_count--;
      level->is_monst_unset(x, y);
    }
    if (i_set_is_obs_wall_or_door) {
      i_set_is_obs_wall_or_door = false;
      level->is_obs_wall_or_door_unset(x, y);
    }
    if (is_obs_when_dead() && is_dead) {
      i_set_is_obs_when_dead = false;
      level->is_obs_when_dead_unset(x, y);
    }
    if (i_set_is_obs_for_jump_landing) {
      i_set_is_obs_for_jump_landing = false;
      level->is_obs_for_jump_landing_unset(x, y);
    }
    if (i_set_is_obs_destructable) {
      i_set_is_obs_destructable = false;
      level->is_obs_destructable_unset(x, y);
    }
    if (i_set_is_potion) {
      i_set_is_potion = false;
      level->is_potion_unset(x, y);
    }
    if (i_set_is_staff) {
      i_set_is_staff = false;
      level->is_staff_unset(x, y);
    }
    if (i_set_is_ring) {
      i_set_is_ring = false;
      level->is_ring_unset(x, y);
    }
    if (i_set_is_ripple) {
      i_set_is_ripple = false;
      level->is_ripple_unset(x, y);
    }
    if (i_set_is_rock) {
      i_set_is_rock = false;
      level->is_rock_unset(x, y);
    }
    if (i_set_is_secret_door) {
      i_set_is_secret_door = false;
      level->is_secret_door_unset(x, y);
    }
    if (i_set_is_smoke) {
      i_set_is_smoke = false;
      level->is_smoke_unset(x, y);
    }
    if (i_set_is_steam) {
      i_set_is_steam = false;
      level->is_steam_unset(x, y);
    }
    if (i_set_is_brazier) {
      i_set_is_brazier = false;
      level->is_brazier_unset(x, y);
    }
    if (i_set_is_barrel) {
      i_set_is_barrel = false;
      level->is_barrel_unset(x, y);
    }
    if (i_set_is_trap) {
      i_set_is_trap = false;
      level->is_trap_unset(x, y);
    }
    if (i_set_is_treasure_type) {
      i_set_is_treasure_type = false;
      level->is_treasure_type_unset(x, y);
    }
    if (i_set_is_wall) {
      i_set_is_wall = false;
      level->is_wall_unset(x, y);
    }
    if (i_set_water) {
      i_set_water = false;
      level->gfx_water_unset(x, y);
    }

    if (is_lava() || is_fire()) {
      level->is_heatmap_valid = false;
    }

    if (gfx_pixelart_shown_in_bg()) {
      level->ts_redraw_bg = time_ms_cached() + 500;
    }

    //
    // If loading, then the animations may not be loaded yet, so take care.
    //
    if (! g_loading) {
      //
      // Need to pop all animations also; so if we are changing state, like being
      // submerged, then when we push again, the animations are also suitably submerged.
      //
      FOR_ALL_EQUIP(e)
      {
        if (equip_id_carry_anim(e).ok()) {
          auto w = level->thing_find(equip_id_carry_anim(e));
          if (w) {
            w->level_pop();
          }
        }

        if (equip_id_use_anim(e).ok()) {
          auto w = level->thing_find(equip_id_use_anim(e));
          if (w) {
            w->level_pop();
          }
        }
      }

      auto on_fire_id = on_fire_anim_id();
      if (on_fire_id.ok()) {
        TRACE_NO_INDENT();
        auto w = level->thing_find(on_fire_id);
        if (w) {
          w->level_pop();
        }
      }
    }
  }

  level->remove_thing(x, y, id);

  // dbg("Is_monst count %d (after pop) at %d,%d", level->is_monst(x, y), x, y);
}
