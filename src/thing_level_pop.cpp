//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_gl.h"

void Thing::level_pop(void) {
  TRACE_AND_INDENT();
  if (! is_attached) {
    return;
  }
  is_attached = false;

  auto mx = (int16_t) (int) last_attached.x;
  auto my = (int16_t) (int) last_attached.y;

  if (i_set_is_acid) {
    i_set_is_acid = false;
    level->unset_is_acid(mx, my);
  }
  if (i_set_is_poison) {
    i_set_is_poison = false;
    level->unset_is_poison(mx, my);
  }
  if (i_set_is_blood) {
    i_set_is_blood = false;
    level->unset_is_blood(mx, my);
  }
  if (i_set_is_chasm) {
    i_set_is_chasm = false;
    level->unset_is_chasm(mx, my);
  }
  if (i_set_is_corpse) {
    i_set_is_corpse = false;
    level->unset_is_corpse(mx, my);
  }
  if (i_set_is_corridor) {
    i_set_is_corridor = false;
    level->unset_is_corridor(mx, my);
  }
  if (i_set_is_bridge) {
    i_set_is_bridge = false;
    level->unset_is_bridge(mx, my);
  }
  if (i_set_is_shallow_water) {
    i_set_is_shallow_water = false;
    level->unset_is_shallow_water(mx, my);
  }
  if (i_set_is_deep_water) {
    i_set_is_deep_water = false;
    level->unset_is_deep_water(mx, my);
  }
  if (i_set_is_dirt) {
    i_set_is_dirt = false;
    level->unset_is_dirt(mx, my);
  }
  if (i_set_is_dry_grass) {
    i_set_is_dry_grass = false;
    level->unset_is_dry_grass(mx, my);
  }
  if (i_set_is_enchantstone) {
    i_set_is_enchantstone = false;
    level->unset_is_enchantstone(mx, my);
  }
  if (i_set_is_skillstone) {
    i_set_is_skillstone = false;
    level->unset_is_skillstone(mx, my);
  }
  if (i_set_is_foilage) {
    i_set_is_foilage = false;
    level->unset_is_foilage(mx, my);
  }
  if (i_set_is_spiderweb) {
    i_set_is_spiderweb = false;
    level->unset_is_spiderweb(mx, my);
  }
  if (i_set_is_sticky) {
    i_set_is_sticky = false;
    level->unset_is_sticky(mx, my);
  }
  if (i_set_is_shovable) {
    i_set_is_shovable = false;
    level->unset_is_shovable(mx, my);
  }
  if (i_set_is_door) {
    i_set_is_door = false;
    level->unset_is_door(mx, my);
  }
  if (i_set_is_ascend_dungeon) {
    i_set_is_ascend_dungeon = false;
    level->unset_is_ascend_dungeon(mx, my);
  }
  if (i_set_is_descend_dungeon) {
    i_set_is_descend_dungeon = false;
    level->unset_is_descend_dungeon(mx, my);
  }
  if (i_set_is_ascend_sewer) {
    i_set_is_ascend_sewer = false;
    level->unset_is_ascend_sewer(mx, my);
  }
  if (i_set_is_descend_sewer) {
    i_set_is_descend_sewer = false;
    level->unset_is_descend_sewer(mx, my);
  }
  if (i_set_is_fire) {
    i_set_is_fire = false;
    level->unset_is_fire(mx, my);
  }
  if (i_set_is_floor) {
    i_set_is_floor = false;
    level->unset_is_floor(mx, my);
  }
  if (i_set_is_food) {
    i_set_is_food = false;
    level->unset_is_food(mx, my);
  }
  if (i_set_is_minion_generator) {
    i_set_is_minion_generator = false;
    level->unset_is_minion_generator(mx, my);
  }
  if (i_set_is_gold) {
    i_set_is_gold = false;
    level->unset_is_gold(mx, my);
  }
  if (i_set_is_hazard) {
    i_set_is_hazard = false;
    level->unset_is_hazard(mx, my);
  }
  if (i_set_is_extreme_hazard) {
    i_set_is_extreme_hazard = false;
    level->unset_is_extreme_hazard(mx, my);
  }
  if (i_set_is_treasure_class_a) {
    i_set_is_treasure_class_a = false;
    level->unset_is_treasure_class_a(mx, my);
  }
  if (i_set_is_treasure_class_b) {
    i_set_is_treasure_class_b = false;
    level->unset_is_treasure_class_b(mx, my);
  }
  if (i_set_is_treasure_class_c) {
    i_set_is_treasure_class_c = false;
    level->unset_is_treasure_class_c(mx, my);
  }
  if (i_set_is_key) {
    i_set_is_key = false;
    level->unset_is_key(mx, my);
  }
  if (i_set_is_lava) {
    i_set_is_lava = false;
    level->unset_is_lava(mx, my);
  }
  if (i_set_is_light_blocker) {
    i_set_is_light_blocker = false;
    level->unset_is_light_blocker(mx, my);
  }
  if (i_set_is_monst) {
    i_set_is_monst = false;
    level->unset_is_monst(mx, my);
  }
  if (i_set_is_obs_wall_or_door) {
    i_set_is_obs_wall_or_door = false;
    level->unset_is_obs_wall_or_door(mx, my);
  }
  if (i_set_is_obs_destructable) {
    i_set_is_obs_destructable = false;
    level->unset_is_obs_destructable(mx, my);
  }
  if (i_set_is_potion) {
    i_set_is_potion = false;
    level->unset_is_potion(mx, my);
  }
  if (i_set_is_wand) {
    i_set_is_wand = false;
    level->unset_is_wand(mx, my);
  }
  if (i_set_is_ripple) {
    i_set_is_ripple = false;
    level->unset_is_ripple(mx, my);
  }
  if (i_set_is_rock) {
    i_set_is_rock = false;
    level->unset_is_rock(mx, my);
  }
  if (i_set_is_secret_door) {
    i_set_is_secret_door = false;
    level->unset_is_secret_door(mx, my);
  }
  if (i_set_is_smoke) {
    i_set_is_smoke = false;
    level->unset_is_smoke(mx, my);
  }
  if (i_set_is_brazier) {
    i_set_is_brazier = false;
    level->unset_is_brazier(mx, my);
  }
  if (i_set_is_barrel) {
    i_set_is_barrel = false;
    level->unset_is_barrel(mx, my);
  }
  if (i_set_is_treasure_type) {
    i_set_is_treasure_type = false;
    level->unset_is_treasure_type(mx, my);
  }
  if (i_set_is_wall) {
    i_set_is_wall = false;
    level->unset_is_wall(mx, my);
  }
  if (i_set_gfx_water) {
    i_set_gfx_water = false;
    level->unset_gfx_water(mx, my);
  }
  int group = get_group();
  level->remove_thing(last_attached.x, last_attached.y, id, group);

  if (is_lava() || is_fire()) {
    level->is_heatmap_valid = false;
  }

  if (gfx_shown_in_bg()) {
    level->ts_redraw_bg = time_get_time_ms_cached() + 500;
  }

#if 0
  if (is_torch()) {
    con("pop at %d,%d", last_attached.x, last_attached.y);
  }
#endif

  // dbg("Is_monst count %d (after pop) at %d,%d", level->is_monst(mx, my), mx, my);
}
