//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_world.hpp"

//
// push/pop are for things moving on the same level
//
void Thing::level_push(void)
{
  TRACE_NO_INDENT();
  level_pop();

  int group = get_group();
  level->put_thing((int) curr_at.x, (int) curr_at.y, id, group);
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

  if (is_acid()) {
    i_set_is_acid = true;
    level->set_is_acid(mx, my);
  }
  if (is_red_blood()) {
    i_set_is_red_blood = true;
    level->set_is_red_blood(mx, my);
  }
  if (is_green_blood()) {
    i_set_is_green_blood = true;
    level->set_is_green_blood(mx, my);
  }
  if (is_chasm()) {
    i_set_is_chasm = true;
    level->set_is_chasm(mx, my);
  }
  if (is_corpse()) {
    i_set_is_corpse = true;
    level->set_is_corpse(mx, my);
  }
  if (is_corridor()) {
    i_set_is_corridor = true;
    level->set_is_corridor(mx, my);
  }
  if (is_bridge()) {
    i_set_is_bridge = true;
    level->set_is_bridge(mx, my);
  }
  if (is_dirt()) {
    i_set_is_dirt = true;
    level->set_is_dirt(mx, my);
  }
  if (is_dry_grass()) {
    i_set_is_dry_grass = true;
    level->set_is_dry_grass(mx, my);
  }
  if (is_wet_grass()) {
    i_set_is_wet_grass = true;
    level->set_is_wet_grass(mx, my);
  }
  if (is_enchantstone()) {
    i_set_is_enchantstone = true;
    level->set_is_enchantstone(mx, my);
  }
  if (is_skillstone()) {
    i_set_is_skillstone = true;
    level->set_is_skillstone(mx, my);
  }
  if (is_foilage()) {
    i_set_is_foilage = true;
    level->set_is_foilage(mx, my);
  }
  if (is_spiderweb()) {
    i_set_is_spiderweb = true;
    level->set_is_spiderweb(mx, my);
  }
  if (is_sticky()) {
    i_set_is_sticky = true;
    level->set_is_sticky(mx, my);
  }
  if (is_shovable()) {
    i_set_is_shovable = true;
    level->set_is_shovable(mx, my);
  }
  if (is_door() && ! is_open) {
    i_set_is_door = true;
    level->set_is_door(mx, my);
  }
  if (is_ascend_dungeon()) {
    i_set_is_ascend_dungeon = true;
    level->set_is_ascend_dungeon(mx, my);
  }
  if (is_descend_dungeon()) {
    i_set_is_descend_dungeon = true;
    level->set_is_descend_dungeon(mx, my);
  }
  if (is_ascend_sewer()) {
    i_set_is_ascend_sewer = true;
    level->set_is_ascend_sewer(mx, my);
  }
  if (is_descend_sewer()) {
    i_set_is_descend_sewer = true;
    level->set_is_descend_sewer(mx, my);
  }
  if (is_fire() && ! is_dead) {
    i_set_is_fire = true;
    level->set_is_fire(mx, my);
  }
  if (is_floor()) {
    i_set_is_floor = true;
    level->set_is_floor(mx, my);
  }
  if (is_food()) {
    i_set_is_food = true;
    level->set_is_food(mx, my);
  }
  if (is_mob()) {
    i_set_is_mob = true;
    level->set_is_mob(mx, my);
  }
  if (is_gold()) {
    i_set_is_gold = true;
    level->set_is_gold(mx, my);
  }
  if (is_hazard()) {
    i_set_is_hazard = true;
    level->set_is_hazard(mx, my);
  }
  if (is_cursor_path_hazard_for_player()) {
    i_set_is_cursor_path_hazard_for_player = true;
    level->set_is_cursor_path_hazard_for_player(mx, my);
  }
  if (is_heavy()) {
    i_set_is_heavy = true;
    level->set_is_heavy(mx, my);
  }
  if (is_key()) {
    i_set_is_key = true;
    level->set_is_key(mx, my);
  }
  if (is_lava()) {
    i_set_is_lava = true;
    level->set_is_lava(mx, my);
  }
  if (is_light_blocker() && ! is_open && ! is_dead) {
    i_set_is_light_blocker = true;
    level->set_is_light_blocker(mx, my);
  }
  if (is_monst()) {
    i_set_is_monst = true;
    level->set_is_monst(mx, my);
  }
  if (is_obs_wall_or_door() && ! is_open && ! is_dead) {
    i_set_is_obs_wall_or_door = true;
    level->set_is_obs_wall_or_door(mx, my);
  }
  if (is_obs_destructable() && ! is_open && ! is_dead) {
    i_set_is_obs_destructable = true;
    level->set_is_obs_destructable(mx, my);
  }
  if (is_potion()) {
    i_set_is_potion = true;
    level->set_is_potion(mx, my);
  }
  if (is_wand()) {
    i_set_is_wand = true;
    level->set_is_wand(mx, my);
  }
  if (is_ring()) {
    i_set_is_ring = true;
    level->set_is_ring(mx, my);
  }
  if (is_ripple()) {
    i_set_is_ripple = true;
    level->set_is_ripple(mx, my);
  }
  if (is_rock()) {
    i_set_is_rock = true;
    level->set_is_rock(mx, my);
  }
  if (is_secret_door()) {
    i_set_is_secret_door = true;
    level->set_is_secret_door(mx, my);
  }
  if (is_smoke()) {
    i_set_is_smoke = true;
    level->set_is_smoke(mx, my);
  }
  if (is_brazier()) {
    i_set_is_brazier = true;
    level->set_is_brazier(mx, my);
  }
  if (is_barrel()) {
    i_set_is_barrel = true;
    level->set_is_barrel(mx, my);
  }
  if (is_treasure_type()) {
    i_set_is_treasure_type = true;
    level->set_is_treasure_type(mx, my);
  }
  if (is_wall()) {
    i_set_is_wall = true;
    level->set_is_wall(mx, my);
  }
  if (is_shallow_water() || is_deep_water()) {
    i_set_water = true;
    level->set_gfx_water(mx, my);
  }

  if (is_shallow_water()) {
    if (! is_falling) {
      i_set_is_shallow_water = true;
      level->set_is_shallow_water(mx, my);
    }
  }

  if (is_deep_water()) {
    if (! is_falling) {
      i_set_is_deep_water = true;
      level->set_is_deep_water(mx, my);
    }
  }

  if (is_lava() || is_fire()) {
    level->is_heatmap_valid = false;
  }

  if (! is_hidden) {
    if (gfx_shown_in_bg()) {
      level->ts_redraw_bg = time_get_time_ms_cached() + 1000;
    }
  }

  if (gfx_shown_in_bg()) {
    level->ts_redraw_bg = time_get_time_ms_cached() + 500;
  }

  // dbg("Is_monst count %d (after push) at %d,%d", level->is_monst(mx, my), mx, my);
}
