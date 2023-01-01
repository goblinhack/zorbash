//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

//
// push/pop are for things moving on the same level
//
void Thing::level_push(void)
{
  TRACE_NO_INDENT();
  level_pop();

  auto x = curr_at.x;
  auto y = curr_at.y;

  level->put_thing(x, y, id);
  is_attached   = true;
  last_attached = point(x, y);

#if 0
  if (is_torch()) {
    con("push at %d,%d", last_attached.x, last_attached.y);
  }
#endif

  if (is_the_grid) {
    return;
  }

  //
  // Don't have things like lasers or projectiles briefly setting fire on a tile
  // as that will cause interactions. And they really are brief, not long lived
  // like actual fire.
  //
  if (is_tmp_thing()) {
    return;
  }

  //
  // We don't want torches for example to act as if they are on the level/
  //
  if (is_hidden) {
    return;
  }

  if (is_acid()) {
    i_set_is_acid = true;
    level->is_acid_set(x, y);
  }
  if (is_red_blood()) {
    i_set_is_red_blood = true;
    level->is_red_blood_set(x, y);
  }
  if (is_green_blood()) {
    i_set_is_green_blood = true;
    level->is_green_blood_set(x, y);
  }
  if (is_chasm()) {
    i_set_is_chasm = true;
    level->is_chasm_set(x, y);
  }
  if (is_corpse()) {
    i_set_is_corpse = true;
    level->is_corpse_set(x, y);
  }
  if (is_corridor()) {
    i_set_is_corridor = true;
    level->is_corridor_set(x, y);
  }
  if (is_bridge()) {
    i_set_is_bridge = true;
    level->is_bridge_set(x, y);
  }
  if (is_dirt()) {
    i_set_is_dirt = true;
    level->is_dirt_set(x, y);
  }
  if (is_dry_grass()) {
    i_set_is_dry_grass = true;
    level->is_dry_grass_set(x, y);
  }
  if (is_wet_grass()) {
    i_set_is_wet_grass = true;
    level->is_wet_grass_set(x, y);
  }
  if (is_enchantstone()) {
    i_set_is_enchantstone = true;
    level->is_enchantstone_set(x, y);
  }
  if (is_skillstone()) {
    i_set_is_skillstone = true;
    level->is_skillstone_set(x, y);
  }
  if (is_foliage()) {
    i_set_is_foliage = true;
    level->is_foliage_set(x, y);
  }
  if (is_carnivorous_plant()) {
    i_set_is_carnivorous_plant = true;
    level->is_carnivorous_plant_set(x, y);
  }
  if (is_spiderweb()) {
    i_set_is_spiderweb = true;
    level->is_spiderweb_set(x, y);
  }
  if (is_block_of_ice()) {
    i_set_is_block_of_ice = true;
    level->is_block_of_ice_set(x, y);
  }
  if (is_sticky()) {
    i_set_is_sticky = true;
    level->is_sticky_set(x, y);
  }
  if (is_shovable()) {
    i_set_is_shovable = true;
    level->is_shovable_set(x, y);
  }
  if (is_door() && ! is_open) {
    i_set_is_door = true;
    level->is_door_set(x, y);
  }
  if (is_ascend_dungeon()) {
    i_set_is_ascend_dungeon = true;
    level->is_ascend_dungeon_set(x, y);
  }
  if (is_descend_dungeon()) {
    i_set_is_descend_dungeon = true;
    level->is_descend_dungeon_set(x, y);
  }
  if (is_ascend_sewer()) {
    i_set_is_ascend_sewer = true;
    level->is_ascend_sewer_set(x, y);
  }
  if (is_descend_sewer()) {
    i_set_is_descend_sewer = true;
    level->is_descend_sewer_set(x, y);
  }
  if (is_floor() || is_corridor()) {
    i_set_is_floor = true;
    level->is_floor_set(x, y);
  }
  if (is_food()) {
    i_set_is_food = true;
    level->is_food_set(x, y);
  }
  if (is_mob()) {
    i_set_is_mob = true;
    level->is_mob_set(x, y);
  }
  if (is_gold()) {
    i_set_is_gold = true;
    level->is_gold_set(x, y);
  }
  if (is_combustible()) {
    i_set_is_combustible = true;
    level->is_combustible_set(x, y);
  }
  if (is_torch()) {
    i_set_is_torch = true;
    level->is_torch_set(x, y);
  }
  if (is_able_to_burn()) {
    i_set_is_able_to_burn = true;
    level->is_able_to_burn_set(x, y);
  }
  if (is_heavy()) {
    i_set_is_heavy = true;
    level->is_heavy_set(x, y);
  }
  if (is_key()) {
    i_set_is_key = true;
    level->is_key_set(x, y);
  }
  if (is_lava()) {
    i_set_is_lava = true;
    level->is_lava_set(x, y);
  }
  if (is_basalt()) {
    i_set_is_basalt = true;
    level->is_basalt_set(x, y);
  }
  if (is_potion()) {
    i_set_is_potion = true;
    level->is_potion_set(x, y);
  }
  if (is_staff()) {
    i_set_is_staff = true;
    level->is_staff_set(x, y);
  }
  if (is_ring()) {
    i_set_is_ring = true;
    level->is_ring_set(x, y);
  }
  if (is_ripple()) {
    i_set_is_ripple = true;
    level->is_ripple_set(x, y);
  }
  if (is_rock()) {
    i_set_is_rock = true;
    level->is_rock_set(x, y);
  }
  if (is_smoke()) {
    i_set_is_smoke = true;
    level->is_smoke_set(x, y);
  }
  if (is_steam()) {
    i_set_is_steam = true;
    level->is_steam_set(x, y);
  }
  if (is_treasure_type()) {
    i_set_is_treasure_type = true;
    level->is_treasure_type_set(x, y);
  }
  if (is_wall()) {
    i_set_is_wall = true;
    level->is_wall_set(x, y);
  }
  if (is_shallow_water() || is_deep_water()) {
    i_set_water = true;
    level->gfx_water_set(x, y);
  }
  if (is_shallow_water()) {
    if (! is_falling) {
      i_set_is_shallow_water = true;
      level->is_shallow_water_set(x, y);
    }
  }
  if (is_deep_water()) {
    if (! is_falling) {
      i_set_is_deep_water = true;
      level->is_deep_water_set(x, y);
    }
  }

  if (! is_dead && ! is_open) {
    if (is_fire()) {
      i_set_is_fire = true;
      level->is_fire_set(x, y);
    }
    if (is_secret_door()) {
      i_set_is_secret_door = true;
      level->is_secret_door_set(x, y);
    }
    if (is_hazard()) {
      i_set_is_hazard = true;
      level->is_hazard_set(x, y);
    }
    if (is_cursor_path_hazard()) {
      i_set_is_cursor_path_hazard = true;
      level->is_cursor_path_hazard_set(x, y);
    }
    if (is_cursor_path_blocker()) {
      i_set_is_cursor_path_blocker = true;
      level->is_cursor_path_blocker_set(x, y);
    }
    if (is_light_blocker() && ! is_open && ! is_currently_invisible) {
      i_set_is_light_blocker = true;
      level->is_light_blocker_set(x, y);
    }
    if (is_light_blocker_for_monst() && ! is_open && ! is_currently_invisible) {
      i_set_is_light_blocker_for_monst = true;
      level->is_light_blocker_for_monst_set(x, y);
    }
    if (is_gas_blocker() && ! is_open) {
      i_set_is_gas_blocker = true;
      level->is_gas_blocker_set(x, y);
    }
    if (noise_blocker() && ! is_open) {
      i_set_noise_blocker = true;
      level->noise_blocker_set(x, y);
    }
    if (is_obs_wall_or_door() && ! is_open) {
      i_set_is_obs_wall_or_door = true;
      level->is_obs_wall_or_door_set(x, y);
    }
    if (is_obs_for_jump_landing() && ! is_open) {
      i_set_is_obs_for_jump_landing = true;
      level->is_obs_for_jump_landing_set(x, y);
    }
    if (is_obs_destructable() && ! is_open) {
      i_set_is_obs_destructable = true;
      level->is_obs_destructable_set(x, y);
    }
    if (is_monst()) {
      i_set_is_monst = true;
      level->monst_count++;
      level->is_monst_set(x, y);
    }
    if (is_brazier()) {
      //
      // Dead/extinguished braziers are not an obstacle
      //
      i_set_is_brazier = true;
      level->is_brazier_set(x, y);
    }
    if (is_barrel()) {
      i_set_is_barrel = true;
      level->is_barrel_set(x, y);
    }
    if (is_tentacle()) {
      i_set_is_tentacle = true;
      level->is_tentacle_set(x, y);
    }
  }

  if (gfx_pixelart_shown_in_bg()) {
    level->ts_redraw_bg = time_ms_cached() + 1000;
  }

  if (is_lava() || is_fire()) {
    level->is_heatmap_valid = false;
  }

  if (gfx_pixelart_shown_in_bg()) {
    level->ts_redraw_bg = time_ms_cached() + 500;
  }

  //
  // Keep track of what we are submerged in (or our owner).
  //
  auto o_top = top_owner();

  if (! is_water()) {
    is_in_water = level->is_water(curr_at);
    if (o_top && o_top->is_in_water) {
      is_in_water = true;
    }
  }

  if (! is_lava()) {
    is_in_lava = level->is_lava(curr_at);
    if (o_top && o_top->is_in_lava) {
      is_in_lava = true;
    }
  }

  //
  // Update submerged status
  //
  if (gfx_pixelart_submergable()) {
    auto map_loc = curr_at;
    if (o_top) {
      map_loc = o_top->curr_at;
    }

    submerged_offset_set(0);

    if (is_always_submerged()) {
      //
      // Krakens are pre submerged.
      //
    } else if (level->is_deep_water((int) map_loc.x, (int) map_loc.y)) {
      submerged_offset_set(8);
    } else if (level->is_lava((int) map_loc.x, (int) map_loc.y)) {
      submerged_offset_set(TILE_HEIGHT / 2);
    } else if (level->is_shallow_water((int) map_loc.x, (int) map_loc.y)) {
      submerged_offset_set(4);
    }

    if (! is_dead && (is_floating() || is_flying())) {
      //
      // Ghosts do not sink into lava
      //
      submerged_offset_set(0);
    }
  }

  //
  // If loading, then the animations may not be loaded yet, so take care.
  //
  if (! g_loading) {
    //
    // Need to push all animations also; so if we are changing state, like being
    // submerged, then when we push again, the animations are also suitably submerged.
    //
    FOR_ALL_EQUIP(e)
    {
      if (equip_id_carry_anim(e).ok()) {
        auto w = level->thing_find(equip_id_carry_anim(e));
        if (w) {
          w->level_push();
        }
      }

      if (equip_id_use_anim(e).ok()) {
        auto w = level->thing_find(equip_id_use_anim(e));
        if (w) {
          w->level_push();
        }
      }
    }

    auto on_fire_id = on_fire_anim_id();
    if (on_fire_id.ok()) {
      TRACE_NO_INDENT();
      auto w = level->thing_find(on_fire_id);
      if (w) {
        w->level_push();
      }
    }
  }

  // dbg("Is_monst count %d (after push) at %d,%d", level->is_monst(x, y), x, y);
}
