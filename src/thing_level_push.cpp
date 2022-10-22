//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

//
// push/pop are for things moving on the same level
//
void Thing::level_push(void)
{
  TRACE_NO_INDENT();
  level_pop();

  level->put_thing((int) curr_at.x, (int) curr_at.y, id);
  auto mx       = (int16_t) (int) curr_at.x;
  auto my       = (int16_t) (int) curr_at.y;
  is_attached   = true;
  last_attached = point(mx, my);

#if 0
  if (is_torch()) {
    con("push at %d,%d", last_attached.x, last_attached.y);
  }
#endif

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
    level->is_acid_set(mx, my);
  }
  if (is_red_blood()) {
    i_set_is_red_blood = true;
    level->is_red_blood_set(mx, my);
  }
  if (is_green_blood()) {
    i_set_is_green_blood = true;
    level->is_green_blood_set(mx, my);
  }
  if (is_chasm()) {
    i_set_is_chasm = true;
    level->is_chasm_set(mx, my);
  }
  if (is_corpse()) {
    i_set_is_corpse = true;
    level->is_corpse_set(mx, my);
  }
  if (is_corridor()) {
    i_set_is_corridor = true;
    level->is_corridor_set(mx, my);
  }
  if (is_bridge()) {
    i_set_is_bridge = true;
    level->is_bridge_set(mx, my);
  }
  if (is_dirt()) {
    i_set_is_dirt = true;
    level->is_dirt_set(mx, my);
  }
  if (is_dry_grass()) {
    i_set_is_dry_grass = true;
    level->is_dry_grass_set(mx, my);
  }
  if (is_wet_grass()) {
    i_set_is_wet_grass = true;
    level->is_wet_grass_set(mx, my);
  }
  if (is_enchantstone()) {
    i_set_is_enchantstone = true;
    level->is_enchantstone_set(mx, my);
  }
  if (is_skillstone()) {
    i_set_is_skillstone = true;
    level->is_skillstone_set(mx, my);
  }
  if (is_foilage()) {
    i_set_is_foilage = true;
    level->is_foilage_set(mx, my);
  }
  if (is_carnivorous_plant()) {
    i_set_is_carnivorous_plant = true;
    level->is_carnivorous_plant_set(mx, my);
  }
  if (is_spiderweb()) {
    i_set_is_spiderweb = true;
    level->is_spiderweb_set(mx, my);
  }
  if (is_block_of_ice()) {
    i_set_is_block_of_ice = true;
    level->is_block_of_ice_set(mx, my);
  }
  if (is_sticky()) {
    i_set_is_sticky = true;
    level->is_sticky_set(mx, my);
  }
  if (is_shovable()) {
    i_set_is_shovable = true;
    level->is_shovable_set(mx, my);
  }
  if (is_door() && ! is_open) {
    i_set_is_door = true;
    level->is_door_set(mx, my);
  }
  if (is_ascend_dungeon()) {
    i_set_is_ascend_dungeon = true;
    level->is_ascend_dungeon_set(mx, my);
  }
  if (is_descend_dungeon()) {
    i_set_is_descend_dungeon = true;
    level->is_descend_dungeon_set(mx, my);
  }
  if (is_ascend_sewer()) {
    i_set_is_ascend_sewer = true;
    level->is_ascend_sewer_set(mx, my);
  }
  if (is_descend_sewer()) {
    i_set_is_descend_sewer = true;
    level->is_descend_sewer_set(mx, my);
  }
  if (is_floor()) {
    i_set_is_floor = true;
    level->is_floor_set(mx, my);
  }
  if (is_food()) {
    i_set_is_food = true;
    level->is_food_set(mx, my);
  }
  if (is_mob()) {
    i_set_is_mob = true;
    level->is_mob_set(mx, my);
  }
  if (is_gold()) {
    i_set_is_gold = true;
    level->is_gold_set(mx, my);
  }
  if (is_hazard()) {
    i_set_is_hazard = true;
    level->is_hazard_set(mx, my);
  }
  if (is_cursor_path_hazard()) {
    i_set_is_cursor_path_hazard = true;
    level->is_cursor_path_hazard_set(mx, my);
  }
  if (is_cursor_path_blocker()) {
    i_set_is_cursor_path_blocker = true;
    level->is_cursor_path_blocker_set(mx, my);
  }
  if (is_combustible()) {
    i_set_is_combustible = true;
    level->is_combustible_set(mx, my);
  }
  if (is_torch()) {
    i_set_is_torch = true;
    level->is_torch_set(mx, my);
  }
  if (is_able_to_burn()) {
    i_set_is_able_to_burn = true;
    level->is_able_to_burn_set(mx, my);
  }
  if (is_heavy()) {
    i_set_is_heavy = true;
    level->is_heavy_set(mx, my);
  }
  if (is_key()) {
    i_set_is_key = true;
    level->is_key_set(mx, my);
  }
  if (is_lava()) {
    i_set_is_lava = true;
    level->is_lava_set(mx, my);
  }
  if (is_basalt()) {
    i_set_is_basalt = true;
    level->is_basalt_set(mx, my);
  }
  if (is_potion()) {
    i_set_is_potion = true;
    level->is_potion_set(mx, my);
  }
  if (is_wand()) {
    i_set_is_wand = true;
    level->is_wand_or_staff_set(mx, my);
  }
  if (is_staff()) {
    i_set_is_staff = true;
    level->is_wand_or_staff_set(mx, my);
  }
  if (is_ring()) {
    i_set_is_ring = true;
    level->is_ring_set(mx, my);
  }
  if (is_ripple()) {
    i_set_is_ripple = true;
    level->is_ripple_set(mx, my);
  }
  if (is_rock()) {
    i_set_is_rock = true;
    level->is_rock_set(mx, my);
  }
  if (is_secret_door()) {
    i_set_is_secret_door = true;
    level->is_secret_door_set(mx, my);
  }
  if (is_smoke()) {
    i_set_is_smoke = true;
    level->is_smoke_set(mx, my);
  }
  if (is_treasure_type()) {
    i_set_is_treasure_type = true;
    level->is_treasure_type_set(mx, my);
  }
  if (is_wall()) {
    i_set_is_wall = true;
    level->is_wall_set(mx, my);
  }
  if (is_shallow_water() || is_deep_water()) {
    i_set_water = true;
    level->gfx_water_set(mx, my);
  }
  if (is_shallow_water()) {
    if (! is_falling) {
      i_set_is_shallow_water = true;
      level->is_shallow_water_set(mx, my);
    }
  }
  if (is_deep_water()) {
    if (! is_falling) {
      i_set_is_deep_water = true;
      level->is_deep_water_set(mx, my);
    }
  }

  if (! is_dead) {
    if (is_fire()) {
      i_set_is_fire = true;
      level->is_fire_set(mx, my);
    }
    if (is_light_blocker() && ! is_open) {
      i_set_is_light_blocker = true;
      level->is_light_blocker_set(mx, my);
    }
    if (is_light_blocker_for_monst() && ! is_open) {
      i_set_is_light_blocker_for_monst = true;
      level->is_light_blocker_for_monst_set(mx, my);
    }
    if (is_gas_blocker() && ! is_open) {
      i_set_is_gas_blocker = true;
      level->is_gas_blocker_set(mx, my);
    }
    if (noise_blocker() && ! is_open) {
      i_set_noise_blocker = true;
      level->noise_blocker_set(mx, my);
    }
    if (is_obs_wall_or_door() && ! is_open) {
      i_set_is_obs_wall_or_door = true;
      level->is_obs_wall_or_door_set(mx, my);
    }
    if (is_obs_destructable() && ! is_open) {
      i_set_is_obs_destructable = true;
      level->is_obs_destructable_set(mx, my);
    }
    if (is_monst()) {
      i_set_is_monst = true;
      level->is_monst_set(mx, my);
    }
    if (is_brazier()) {
      //
      // Dead/extinguished braziers are not an obstacle
      //
      i_set_is_brazier = true;
      level->is_brazier_set(mx, my);
    }
    if (is_barrel()) {
      i_set_is_barrel = true;
      level->is_barrel_set(mx, my);
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

  // dbg("Is_monst count %d (after push) at %d,%d", level->is_monst(mx, my), mx, my);
}
