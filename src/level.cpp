//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

std::string Level::to_string(void)
{
  TRACE_NO_INDENT();

  std::string level_no_str;
  if (dungeon_walk_order_level_no) {
    level_no_str = std::to_string(dungeon_walk_order_level_no);
  } else {
    level_no_str = world_at.to_string();
  }

  if (is_level_type_sewer) {
    return ("sewer L" + level_no_str);
  } else {
    return ("dungeon L" + level_no_str);
  }
}

uint32_t Level::num(void)
{
  TRACE_NO_INDENT();
  return dungeon_walk_order_level_no;
}

uint8_t Level::is_acid(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_acid, p.x, p.y));
}

uint8_t Level::is_acid(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_acid, x, y));
}

void Level::set_is_acid(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_acid, x, y, (uint8_t) 1);
}

void Level::unset_is_acid(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_acid, x, y, (uint8_t) 1);
}

uint8_t Level::is_chasm(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_chasm, x, y));
}

uint8_t Level::is_chasm(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_chasm, p.x, p.y));
}

void Level::set_is_chasm(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_chasm, x, y, (uint8_t) 1);
}

void Level::unset_is_chasm(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_chasm, x, y, (uint8_t) 1);
}

uint8_t Level::is_hazard(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_hazard, p.x, p.y));
}

uint8_t Level::is_hazard(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_hazard, x, y));
}

void Level::set_is_hazard(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_hazard, x, y, (uint8_t) 1);
}

void Level::unset_is_hazard(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_hazard, x, y, (uint8_t) 1);
}

uint8_t Level::is_cursor_path_hazard_for_player(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_cursor_path_hazard_for_player, p.x, p.y));
}

uint8_t Level::is_cursor_path_hazard_for_player(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_cursor_path_hazard_for_player, x, y));
}

void Level::set_is_cursor_path_hazard_for_player(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_cursor_path_hazard_for_player, x, y, (uint8_t) 1);
}

void Level::unset_is_cursor_path_hazard_for_player(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_cursor_path_hazard_for_player, x, y, (uint8_t) 1);
}

uint8_t Level::is_heavy(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_heavy, p.x, p.y));
}

uint8_t Level::is_heavy(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_heavy, x, y));
}

void Level::set_is_heavy(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_heavy, x, y, (uint8_t) 1);
}

void Level::unset_is_heavy(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_heavy, x, y, (uint8_t) 1);
}

uint8_t Level::is_secret_door(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_secret_door, p.x, p.y));
}

uint8_t Level::is_secret_door(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_secret_door, x, y));
}

void Level::set_is_secret_door(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_secret_door, x, y, (uint8_t) 1);
}

void Level::unset_is_secret_door(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_secret_door, x, y, (uint8_t) 1);
}

uint8_t Level::is_ripple(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_ripple, p.x, p.y));
}

uint8_t Level::is_ripple(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_ripple, x, y));
}

void Level::set_is_ripple(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_ripple, x, y, (uint8_t) 1);
}

void Level::unset_is_ripple(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_ripple, x, y, (uint8_t) 1);
}

uint8_t Level::is_barrel(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_barrel, p.x, p.y));
}

uint8_t Level::is_barrel(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_barrel, x, y));
}

void Level::set_is_barrel(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_barrel, x, y, (uint8_t) 1);
}

void Level::unset_is_barrel(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_barrel, x, y, (uint8_t) 1);
}

uint8_t Level::is_mob(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_mob, p.x, p.y));
}

uint8_t Level::is_mob(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_mob, x, y));
}

void Level::set_is_mob(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_mob, x, y, (uint8_t) 1);
}

void Level::unset_is_mob(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_mob, x, y, (uint8_t) 1);
}

uint8_t Level::is_potion(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_potion, p.x, p.y));
}

uint8_t Level::is_potion(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_potion, x, y));
}

void Level::set_is_potion(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_potion, x, y, (uint8_t) 1);
}

void Level::unset_is_potion(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_potion, x, y, (uint8_t) 1);
}

uint8_t Level::is_wand(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_wand, p.x, p.y));
}

uint8_t Level::is_wand(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_wand, x, y));
}

void Level::set_is_wand(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wand, x, y, (uint8_t) 1);
}

void Level::unset_is_wand(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_wand, x, y, (uint8_t) 1);
}

uint8_t Level::is_ring(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_ring, p.x, p.y));
}

uint8_t Level::is_ring(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_ring, x, y));
}

void Level::set_is_ring(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_ring, x, y, (uint8_t) 1);
}

void Level::unset_is_ring(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_ring, x, y, (uint8_t) 1);
}

uint8_t Level::is_red_blood(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_red_blood, p.x, p.y));
}

uint8_t Level::is_red_blood(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_red_blood, x, y));
}

void Level::set_is_red_blood(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_red_blood, x, y, (uint8_t) 1);
}

void Level::unset_is_red_blood(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_red_blood, x, y, (uint8_t) 1);
}

uint8_t Level::is_green_blood(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_green_blood, p.x, p.y));
}

uint8_t Level::is_green_blood(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_green_blood, x, y));
}

void Level::set_is_green_blood(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_green_blood, x, y, (uint8_t) 1);
}

void Level::unset_is_green_blood(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_green_blood, x, y, (uint8_t) 1);
}

uint8_t Level::gfx_water(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_gfx_water, p.x, p.y));
}

uint8_t Level::gfx_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_gfx_water, x, y));
}

void Level::set_gfx_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_gfx_water, x, y, (uint8_t) 1);
}

void Level::unset_gfx_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_gfx_water, x, y, (uint8_t) 1);
}

uint8_t Level::is_deep_water(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_deep_water, p.x, p.y));
}

uint8_t Level::is_deep_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_deep_water, x, y));
}

void Level::set_is_deep_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_deep_water, x, y, (uint8_t) 1);
}

void Level::unset_is_deep_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_deep_water, x, y, (uint8_t) 1);
}

uint8_t Level::is_shallow_water(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_shallow_water, p.x, p.y));
}

uint8_t Level::is_shallow_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_shallow_water, x, y));
}

void Level::set_is_shallow_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_shallow_water, x, y, (uint8_t) 1);
}

void Level::unset_is_shallow_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_shallow_water, x, y, (uint8_t) 1);
}

uint8_t Level::is_water(const point p)
{
  TRACE_NO_INDENT();
  return is_shallow_water(p) || is_deep_water(p);
}

uint8_t Level::is_water(const int x, const int y)
{
  TRACE_NO_INDENT();
  return is_shallow_water(x, y) || is_deep_water(x, y);
}

uint8_t Level::is_wall(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_wall, p.x, p.y));
}

uint8_t Level::is_wall(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_wall, x, y));
}

void Level::set_is_wall(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wall, x, y, (uint8_t) 1);
}

void Level::unset_is_wall(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_wall, x, y, (uint8_t) 1);
}

uint8_t Level::is_corridor(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_corridor, p.x, p.y));
}

uint8_t Level::is_corridor(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_corridor, x, y));
}

void Level::set_is_corridor(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_corridor, x, y, (uint8_t) 1);
}

void Level::unset_is_corridor(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_corridor, x, y, (uint8_t) 1);
}

uint8_t Level::is_bridge(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_bridge, p.x, p.y));
}

uint8_t Level::is_bridge(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_bridge, x, y));
}

void Level::set_is_bridge(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_bridge, x, y, (uint8_t) 1);
}

void Level::unset_is_bridge(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_bridge, x, y, (uint8_t) 1);
}

uint8_t Level::is_dirt(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_dirt, p.x, p.y));
}

uint8_t Level::is_dirt(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_dirt, x, y));
}

void Level::set_is_dirt(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_dirt, x, y, (uint8_t) 1);
}

void Level::unset_is_dirt(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_dirt, x, y, (uint8_t) 1);
}

uint8_t Level::is_dry_grass(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_dry_grass, p.x, p.y));
}

uint8_t Level::is_dry_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_dry_grass, x, y));
}

void Level::set_is_dry_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_dry_grass, x, y, (uint8_t) 1);
}

void Level::unset_is_dry_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_dry_grass, x, y, (uint8_t) 1);
}

uint8_t Level::is_wet_grass(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_wet_grass, p.x, p.y));
}

uint8_t Level::is_wet_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_wet_grass, x, y));
}

void Level::set_is_wet_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wet_grass, x, y, (uint8_t) 1);
}

void Level::unset_is_wet_grass(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_wet_grass, x, y, (uint8_t) 1);
}

uint8_t Level::is_enchantstone(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_enchantstone, p.x, p.y));
}

uint8_t Level::is_enchantstone(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_enchantstone, x, y));
}

void Level::set_is_enchantstone(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_enchantstone, x, y, (uint8_t) 1);
}

void Level::unset_is_enchantstone(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_enchantstone, x, y, (uint8_t) 1);
}

uint8_t Level::is_skillstone(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_skillstone, p.x, p.y));
}

uint8_t Level::is_skillstone(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_skillstone, x, y));
}

void Level::set_is_skillstone(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_skillstone, x, y, (uint8_t) 1);
}

void Level::unset_is_skillstone(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_skillstone, x, y, (uint8_t) 1);
}

uint8_t Level::is_foilage(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_foilage, p.x, p.y));
}

uint8_t Level::is_foilage(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_foilage, x, y));
}

void Level::set_is_foilage(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_foilage, x, y, (uint8_t) 1);
}

void Level::unset_is_foilage(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_foilage, x, y, (uint8_t) 1);
}

uint8_t Level::is_spiderweb(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_spiderweb, p.x, p.y));
}

uint8_t Level::is_spiderweb(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_spiderweb, x, y));
}

void Level::set_is_spiderweb(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_spiderweb, x, y, (uint8_t) 1);
}

void Level::unset_is_spiderweb(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_spiderweb, x, y, (uint8_t) 1);
}

uint8_t Level::is_sticky(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_sticky, p.x, p.y));
}

uint8_t Level::is_sticky(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_sticky, x, y));
}

void Level::set_is_sticky(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_sticky, x, y, (uint8_t) 1);
}

void Level::unset_is_sticky(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_sticky, x, y, (uint8_t) 1);
}

uint8_t Level::is_shovable(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_shovable, p.x, p.y));
}

uint8_t Level::is_shovable(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_shovable, x, y));
}

void Level::set_is_shovable(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_shovable, x, y, (uint8_t) 1);
}

void Level::unset_is_shovable(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_shovable, x, y, (uint8_t) 1);
}

uint8_t Level::is_floor(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_floor, p.x, p.y));
}

uint8_t Level::is_floor(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_floor, x, y));
}

void Level::set_is_floor(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_floor, x, y, (uint8_t) 1);
}

void Level::unset_is_floor(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_floor, x, y, (uint8_t) 1);
}

uint8_t Level::is_rock(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_rock, p.x, p.y));
}

uint8_t Level::is_rock(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_rock, x, y));
}

void Level::set_is_rock(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_rock, x, y, (uint8_t) 1);
}

void Level::unset_is_rock(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_rock, x, y, (uint8_t) 1);
}

uint8_t Level::is_able_to_stand_on(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_able_to_stand_on, p.x, p.y));
}

uint8_t Level::is_able_to_stand_on(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_able_to_stand_on, x, y));
}

void Level::set_is_able_to_stand_on(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_able_to_stand_on, x, y, (uint8_t) 1);
}

void Level::unset_is_able_to_stand_on(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_able_to_stand_on, x, y, (uint8_t) 1);
}

uint8_t Level::is_corpse(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_corpse, p.x, p.y));
}

uint8_t Level::is_corpse(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_corpse, x, y));
}

void Level::set_is_corpse(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_corpse, x, y, (uint8_t) 1);
}

void Level::unset_is_corpse(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_corpse, x, y, (uint8_t) 1);
}

uint8_t Level::is_monst(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_monst, p.x, p.y));
}

uint8_t Level::is_monst_or_player(const point p)
{
  if (is_monst(p)) {
    return true;
  }
  if (player && (player->curr_at == p)) {
    return true;
  }
  return false;
}

uint8_t Level::is_monst(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_monst, x, y));
}

void Level::set_is_monst(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_monst, x, y, (uint8_t) 1);
}

void Level::unset_is_monst(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_monst, x, y, (uint8_t) 1);
}

uint8_t Level::is_door(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_door, p.x, p.y));
}

uint8_t Level::is_door(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_door, x, y));
}

void Level::set_is_door(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_door, x, y, (uint8_t) 1);
}

void Level::unset_is_door(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_door, x, y, (uint8_t) 1);
}

uint8_t Level::is_key(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_key, p.x, p.y));
}

uint8_t Level::is_key(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_key, x, y));
}

void Level::set_is_key(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_key, x, y, (uint8_t) 1);
}

void Level::unset_is_key(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_key, x, y, (uint8_t) 1);
}

uint8_t Level::is_food(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_food, p.x, p.y));
}

uint8_t Level::is_food(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_food, x, y));
}

void Level::set_is_food(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_food, x, y, (uint8_t) 1);
}

void Level::unset_is_food(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_food, x, y, (uint8_t) 1);
}

uint8_t Level::is_treasure_type(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_treasure_type, p.x, p.y));
}

uint8_t Level::is_treasure_type(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_treasure_type, x, y));
}

void Level::set_is_treasure_type(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_treasure_type, x, y, (uint8_t) 1);
}

void Level::unset_is_treasure_type(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_treasure_type, x, y, (uint8_t) 1);
}

uint8_t Level::is_gold(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_gold, p.x, p.y));
}

uint8_t Level::is_gold(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_gold, x, y));
}

void Level::set_is_gold(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_gold, x, y, (uint8_t) 1);
}

void Level::unset_is_gold(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_gold, x, y, (uint8_t) 1);
}

uint8_t Level::is_ascend_dungeon(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_ascend_dungeon, p.x, p.y));
}

uint8_t Level::is_ascend_dungeon(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_ascend_dungeon, x, y));
}

void Level::set_is_ascend_dungeon(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_ascend_dungeon, x, y, (uint8_t) 1);
}

void Level::unset_is_ascend_dungeon(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_ascend_dungeon, x, y, (uint8_t) 1);
}

uint8_t Level::is_descend_dungeon(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_descend_dungeon, p.x, p.y));
}

uint8_t Level::is_descend_dungeon(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_descend_dungeon, x, y));
}

void Level::set_is_descend_dungeon(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_descend_dungeon, x, y, (uint8_t) 1);
}

void Level::unset_is_descend_dungeon(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_descend_dungeon, x, y, (uint8_t) 1);
}

uint8_t Level::is_ascend_sewer(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_ascend_sewer, p.x, p.y));
}

uint8_t Level::is_ascend_sewer(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_ascend_sewer, x, y));
}

void Level::set_is_ascend_sewer(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_ascend_sewer, x, y, (uint8_t) 1);
}

void Level::unset_is_ascend_sewer(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_ascend_sewer, x, y, (uint8_t) 1);
}

uint8_t Level::is_descend_sewer(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_descend_sewer, p.x, p.y));
}

uint8_t Level::is_descend_sewer(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_descend_sewer, x, y));
}

void Level::set_is_descend_sewer(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_descend_sewer, x, y, (uint8_t) 1);
}

void Level::unset_is_descend_sewer(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_descend_sewer, x, y, (uint8_t) 1);
}

uint8_t Level::is_smoke(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_smoke, p.x, p.y));
}

uint8_t Level::is_smoke(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_smoke, x, y));
}

void Level::set_is_smoke(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_smoke, x, y, (uint8_t) 1);
}

void Level::unset_is_smoke(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_smoke, x, y, (uint8_t) 1);
}

//
// Used in lighting, so inlined
//
bool Level::is_oob(const int x, const int y, const int z) const
{
  return ((x < 0) || (x >= MAP_WIDTH) || (y < 0) || (y >= MAP_HEIGHT) || (z < 0) || (z >= MAP_DEPTH));
}

bool Level::is_oob(const int x, const int y) const
{
  return ((x < 0) || (x >= MAP_WIDTH) || (y < 0) || (y >= MAP_HEIGHT));
}

bool Level::is_oob(const fpoint p) const
{
  return ((p.x < 0) || (p.x >= MAP_WIDTH) || (p.y < 0) || (p.y >= MAP_HEIGHT));
}

bool Level::is_oob(const point p) const
{
  return ((p.x < 0) || (p.x >= MAP_WIDTH) || (p.y < 0) || (p.y >= MAP_HEIGHT));
}

uint8_t Level::fade_in_map(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_fade_in_map, p.x, p.y));
}

uint8_t Level::fade_in_map_no_check(const point p) { return (get_no_check(_fade_in_map, p.x, p.y)); }

uint8_t Level::fade_in_map(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_fade_in_map, x, y));
}

uint8_t Level::fade_in_map_no_check(const int x, const int y) { return (get_no_check(_fade_in_map, x, y)); }

void Level::incr_fade_in(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  auto v = get(_fade_in_map, x, y);
  if (v < 255) {
    v += 1;
    set(_fade_in_map, x, y, v);
  } else {
    set(_fade_in_map, x, y, (uint8_t) 255);
  }
}

void Level::incr_fade_in_no_check(const int x, const int y)
{
  auto v = get_no_check(_fade_in_map, x, y);
  if (v < 255) {
    v += 1;
    set_no_check(_fade_in_map, x, y, v);
  } else {
    set(_fade_in_map, x, y, (uint8_t) 255);
  }
}

void Level::unset_fade_in(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_fade_in_map, x, y, (uint8_t) 0);
}

void Level::unset_fade_in_no_check(const int x, const int y) { set_no_check(_fade_in_map, x, y, (uint8_t) 0); }

uint8_t Level::is_lit_ever(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_lit_ever, p.x, p.y));
}

uint8_t Level::is_lit_ever_no_check(const point p) { return (get_no_check(_is_lit_ever, p.x, p.y)); }

uint8_t Level::is_lit_ever(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_lit_ever, x, y));
}

uint8_t Level::is_lit_ever_no_check(const int x, const int y) { return (get_no_check(_is_lit_ever, x, y)); }

void Level::set_is_lit_ever(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }

  if (! get(_is_lit_ever, x, y)) {
    set(_fade_in_map, x, y, (uint8_t) 1);
  }
  set(_is_lit_ever, x, y, true);
}

void Level::set_is_lit_ever_no_check(const int x, const int y)
{
  if (! get_no_check(_is_lit_ever, x, y)) {
    set_no_check(_fade_in_map, x, y, (uint8_t) 1);
  }
  set_no_check(_is_lit_ever, x, y, true);
}

void Level::unset_is_lit_ever(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_lit_ever, x, y, false);
}

void Level::unset_is_lit_ever_no_check(const int x, const int y) { set_no_check(_is_lit_ever, x, y, false); }

//
// Used in lighting, so inlined
//
bool Level::is_light_blocker(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_light_blocker, p.x, p.y));
}

bool Level::is_light_blocker_no_check(const point p) const { return (get_no_check(_is_light_blocker, p.x, p.y)); }

bool Level::is_light_blocker(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_light_blocker, x, y));
}

bool Level::is_light_blocker_no_check(const int x, const int y) const
{
  return (get_no_check(_is_light_blocker, x, y));
}

void Level::set_is_light_blocker(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_light_blocker, x, y, true);
}

void Level::set_is_light_blocker_no_check(const int x, const int y) { set_no_check(_is_light_blocker, x, y, true); }

void Level::unset_is_light_blocker(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_light_blocker, x, y, false);
}

void Level::unset_is_light_blocker_no_check(const int x, const int y)
{
  set_no_check(_is_light_blocker, x, y, false);
}

//
// Used in lighting, so inlined
//
bool Level::is_obs_wall_or_door(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_wall_or_door, p.x, p.y));
}

bool Level::is_obs_wall_or_door_no_check(const point p) const
{
  return (get_no_check(_is_obs_wall_or_door, p.x, p.y));
}

bool Level::is_obs_wall_or_door(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_wall_or_door, x, y));
}

bool Level::is_obs_wall_or_door_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_wall_or_door, x, y));
}

void Level::set_is_obs_wall_or_door(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_wall_or_door, x, y, true);
}

void Level::set_is_obs_wall_or_door_no_check(const int x, const int y)
{
  set_no_check(_is_obs_wall_or_door, x, y, true);
}

void Level::unset_is_obs_wall_or_door(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_wall_or_door, x, y, false);
}

void Level::unset_is_obs_wall_or_door_no_check(const int x, const int y)
{
  set_no_check(_is_obs_wall_or_door, x, y, false);
}

//
// Used in lighting, so inlined
//
bool Level::is_obs_destructable(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_obs_destructable, p.x, p.y));
}

bool Level::is_obs_destructable_no_check(const point p) const
{
  return (get_no_check(_is_obs_destructable, p.x, p.y));
}

bool Level::is_obs_destructable(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_obs_destructable, x, y));
}

bool Level::is_obs_destructable_no_check(const int x, const int y) const
{
  return (get_no_check(_is_obs_destructable, x, y));
}

void Level::set_is_obs_destructable(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_destructable, x, y, true);
}

void Level::set_is_obs_destructable_no_check(const int x, const int y)
{
  set_no_check(_is_obs_destructable, x, y, true);
}

void Level::unset_is_obs_destructable(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_destructable, x, y, false);
}

void Level::unset_is_obs_destructable_no_check(const int x, const int y)
{
  set_no_check(_is_obs_destructable, x, y, false);
}

uint8_t Level::is_lit_currently(const point p)
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_lit_currently, p.x, p.y));
}

uint8_t Level::is_lit_currently_no_check(const point p) { return (get_no_check(_is_lit_currently, p.x, p.y)); }

//
// Note light fades
//
uint8_t Level::is_lit_recently(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  //
  // So anything older than 10 ticks we consider no lit recently
  //
  return (get(_is_lit_currently, x, y) > 250);
}

//
// Note light fades
//
uint8_t Level::is_lit_currently(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_lit_currently, x, y));
}

uint8_t Level::is_lit_currently_no_check(const int x, const int y) { return (get_no_check(_is_lit_currently, x, y)); }

void Level::set_is_lit_currently_no_check(const int x, const int y)
{
  auto l = getptr_no_check(_is_lit_currently, x, y);
  if (*l == 0) {
    *l = 255;
  } else if (*l < 255) {
    (*l)++;
  }
}

void Level::set_is_lit_currently(const int x, const int y)
{
  auto l = getptr(_is_lit_currently, x, y);
  if (*l == 0) {
    *l = 255;
  } else if (*l < 255) {
    (*l)++;
  }
}

void Level::set_is_lit_currently_no_check(const int x, const int y, uint8_t v)
{
  set_no_check(_is_lit_currently, x, y, v);
}

void Level::unset_is_lit_currently(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_lit_currently, x, y, (uint8_t) 0);
}

void Level::unset_is_lit_currently_no_check(const int x, const int y)
{
  set_no_check(_is_lit_currently, x, y, (uint8_t) 0);
}

uint32_t Level::get_is_map_changed(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_map_changed, x, y));
}

uint32_t Level::get_is_map_changed_no_check(const int x, const int y)
{
  return (get_no_check(_is_map_changed, x, y));
}

void Level::set_is_map_changed_no_check(const int x, const int y) { set(_is_map_changed, x, y, game->tick_current); }

void Level::set_is_map_changed(const int x, const int y) { set(_is_map_changed, x, y, game->tick_current); }

void Level::set_is_map_changed_no_check(const int x, const int y, uint32_t v)
{
  set_no_check(_is_map_changed, x, y, v);
}

void Level::unset_is_map_changed(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_map_changed, x, y, (uint32_t) 0);
}

void Level::unset_is_map_changed_no_check(const int x, const int y)
{
  set_no_check(_is_map_changed, x, y, (uint32_t) 0);
}
