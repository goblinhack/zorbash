//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
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

  auto mx = (int16_t) (int) last_attached.x;
  auto my = (int16_t) (int) last_attached.y;

  if (i_set_is_acid) {
    i_set_is_acid = false;
    level->is_acid_unset(mx, my);
  }
  if (i_set_is_red_blood) {
    i_set_is_red_blood = false;
    level->is_red_blood_unset(mx, my);
  }
  if (i_set_is_green_blood) {
    i_set_is_green_blood = false;
    level->is_green_blood_unset(mx, my);
  }
  if (i_set_is_chasm) {
    i_set_is_chasm = false;
    level->is_chasm_unset(mx, my);
  }
  if (i_set_is_corpse) {
    i_set_is_corpse = false;
    level->is_corpse_unset(mx, my);
  }
  if (i_set_is_corridor) {
    i_set_is_corridor = false;
    level->is_corridor_unset(mx, my);
  }
  if (i_set_is_bridge) {
    i_set_is_bridge = false;
    level->is_bridge_unset(mx, my);
  }
  if (i_set_is_shallow_water) {
    i_set_is_shallow_water = false;
    level->is_shallow_water_unset(mx, my);
  }
  if (i_set_is_deep_water) {
    i_set_is_deep_water = false;
    level->is_deep_water_unset(mx, my);
  }
  if (i_set_is_dirt) {
    i_set_is_dirt = false;
    level->is_dirt_unset(mx, my);
  }
  if (i_set_is_dry_grass) {
    i_set_is_dry_grass = false;
    level->is_dry_grass_unset(mx, my);
  }
  if (i_set_is_wet_grass) {
    i_set_is_wet_grass = false;
    level->is_wet_grass_unset(mx, my);
  }
  if (i_set_is_enchantstone) {
    i_set_is_enchantstone = false;
    level->is_enchantstone_unset(mx, my);
  }
  if (i_set_is_skillstone) {
    i_set_is_skillstone = false;
    level->is_skillstone_unset(mx, my);
  }
  if (i_set_is_foilage) {
    i_set_is_foilage = false;
    level->is_foilage_unset(mx, my);
  }
  if (i_set_is_carnivorous_plant) {
    i_set_is_carnivorous_plant = false;
    level->is_carnivorous_plant_unset(mx, my);
  }
  if (i_set_is_spiderweb) {
    i_set_is_spiderweb = false;
    level->is_spiderweb_unset(mx, my);
  }
  if (i_set_is_block_of_ice) {
    i_set_is_block_of_ice = false;
    level->is_block_of_ice_unset(mx, my);
  }
  if (i_set_is_sticky) {
    i_set_is_sticky = false;
    level->is_sticky_unset(mx, my);
  }
  if (i_set_is_shovable) {
    i_set_is_shovable = false;
    level->is_shovable_unset(mx, my);
  }
  if (i_set_is_door) {
    i_set_is_door = false;
    level->is_door_unset(mx, my);
  }
  if (i_set_is_ascend_dungeon) {
    i_set_is_ascend_dungeon = false;
    level->is_ascend_dungeon_unset(mx, my);
  }
  if (i_set_is_descend_dungeon) {
    i_set_is_descend_dungeon = false;
    level->is_descend_dungeon_unset(mx, my);
  }
  if (i_set_is_ascend_sewer) {
    i_set_is_ascend_sewer = false;
    level->is_ascend_sewer_unset(mx, my);
  }
  if (i_set_is_descend_sewer) {
    i_set_is_descend_sewer = false;
    level->is_descend_sewer_unset(mx, my);
  }
  if (i_set_is_fire) {
    i_set_is_fire = false;
    level->is_fire_unset(mx, my);
  }
  if (i_set_is_floor) {
    i_set_is_floor = false;
    level->is_floor_unset(mx, my);
  }
  if (i_set_is_food) {
    i_set_is_food = false;
    level->is_food_unset(mx, my);
  }
  if (i_set_is_mob) {
    i_set_is_mob = false;
    level->is_mob_unset(mx, my);
  }
  if (i_set_is_gold) {
    i_set_is_gold = false;
    level->is_gold_unset(mx, my);
  }
  if (i_set_is_hazard) {
    i_set_is_hazard = false;
    level->is_hazard_unset(mx, my);
  }
  if (i_set_is_cursor_path_hazard) {
    i_set_is_cursor_path_hazard = false;
    level->is_cursor_path_hazard_unset(mx, my);
  }
  if (i_set_is_cursor_path_blocker) {
    i_set_is_cursor_path_blocker = false;
    level->is_cursor_path_blocker_unset(mx, my);
  }
  if (i_set_is_combustible) {
    i_set_is_combustible = false;
    level->is_combustible_unset(mx, my);
  }
  if (i_set_is_torch) {
    i_set_is_torch = false;
    level->is_torch_unset(mx, my);
  }
  if (i_set_is_able_to_burn) {
    i_set_is_able_to_burn = false;
    level->is_able_to_burn_unset(mx, my);
  }
  if (i_set_is_heavy) {
    i_set_is_heavy = false;
    level->is_heavy_unset(mx, my);
  }
  if (i_set_is_key) {
    i_set_is_key = false;
    level->is_key_unset(mx, my);
  }
  if (i_set_is_lava) {
    i_set_is_lava = false;
    level->is_lava_unset(mx, my);
  }
  if (i_set_is_basalt) {
    i_set_is_basalt = false;
    level->is_basalt_unset(mx, my);
  }
  if (i_set_is_light_blocker) {
    i_set_is_light_blocker = false;
    level->is_light_blocker_unset(mx, my);
  }
  if (i_set_is_light_blocker_for_monst) {
    i_set_is_light_blocker_for_monst = false;
    level->is_light_blocker_for_monst_unset(mx, my);
  }
  if (i_set_is_gas_blocker) {
    i_set_is_gas_blocker = false;
    level->is_gas_blocker_unset(mx, my);
  }
  if (i_set_noise_blocker) {
    i_set_noise_blocker = false;
    level->noise_blocker_unset(mx, my);
  }
  if (i_set_is_monst) {
    i_set_is_monst = false;
    level->monst_count--;
    level->is_monst_unset(mx, my);
  }
  if (i_set_is_obs_wall_or_door) {
    i_set_is_obs_wall_or_door = false;
    level->is_obs_wall_or_door_unset(mx, my);
  }
  if (i_set_is_obs_for_jump_landing) {
    i_set_is_obs_for_jump_landing = false;
    level->is_obs_for_jump_landing_unset(mx, my);
  }
  if (i_set_is_obs_destructable) {
    i_set_is_obs_destructable = false;
    level->is_obs_destructable_unset(mx, my);
  }
  if (i_set_is_potion) {
    i_set_is_potion = false;
    level->is_potion_unset(mx, my);
  }
  if (i_set_is_wand) {
    i_set_is_wand = false;
    level->is_wand_or_staff_unset(mx, my);
  }
  if (i_set_is_staff) {
    i_set_is_staff = false;
    level->is_wand_or_staff_unset(mx, my);
  }
  if (i_set_is_ring) {
    i_set_is_ring = false;
    level->is_ring_unset(mx, my);
  }
  if (i_set_is_ripple) {
    i_set_is_ripple = false;
    level->is_ripple_unset(mx, my);
  }
  if (i_set_is_rock) {
    i_set_is_rock = false;
    level->is_rock_unset(mx, my);
  }
  if (i_set_is_secret_door) {
    i_set_is_secret_door = false;
    level->is_secret_door_unset(mx, my);
  }
  if (i_set_is_smoke) {
    i_set_is_smoke = false;
    level->is_smoke_unset(mx, my);
  }
  if (i_set_is_brazier) {
    i_set_is_brazier = false;
    level->is_brazier_unset(mx, my);
  }
  if (i_set_is_barrel) {
    i_set_is_barrel = false;
    level->is_barrel_unset(mx, my);
  }
  if (i_set_is_treasure_type) {
    i_set_is_treasure_type = false;
    level->is_treasure_type_unset(mx, my);
  }
  if (i_set_is_wall) {
    i_set_is_wall = false;
    level->is_wall_unset(mx, my);
  }
  if (i_set_water) {
    i_set_water = false;
    level->gfx_water_unset(mx, my);
  }

  level->remove_thing(last_attached.x, last_attached.y, id);

  if (is_lava() || is_fire()) {
    level->is_heatmap_valid = false;
  }

  if (gfx_pixelart_shown_in_bg()) {
    level->ts_redraw_bg = time_ms_cached() + 500;
  }

#if 0
  if (is_torch()) {
    con("pop at %d,%d", last_attached.x, last_attached.y);
  }
#endif

  // dbg("Is_monst count %d (after pop) at %d,%d", level->is_monst(mx, my), mx, my);
}
