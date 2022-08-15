//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_game.hpp"
#include "my_sdl.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

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

void Level::is_acid_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_acid, x, y, (uint8_t) 1);
}

void Level::is_acid_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_acid, x, y, (uint8_t) 1);
}

uint8_t Level::is_cold(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_cold, p.x, p.y));
}

uint8_t Level::is_cold(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_cold, x, y));
}

void Level::is_cold_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_cold, x, y, (uint8_t) 1);
}

void Level::is_cold_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_cold, x, y, (uint8_t) 1);
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

void Level::is_chasm_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_chasm, x, y, (uint8_t) 1);
}

void Level::is_chasm_unset(const int x, const int y)
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

void Level::is_hazard_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_hazard, x, y, (uint8_t) 1);
}

void Level::is_hazard_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_hazard, x, y, (uint8_t) 1);
}

uint8_t Level::is_combustible(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_combustible, p.x, p.y));
}

uint8_t Level::is_combustible(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_combustible, x, y));
}

void Level::is_combustible_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_combustible, x, y, (uint8_t) 1);
}

void Level::is_combustible_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_combustible, x, y, (uint8_t) 1);
}

uint8_t Level::is_torch(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_torch, p.x, p.y));
}

uint8_t Level::is_torch(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_torch, x, y));
}

void Level::is_torch_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_torch, x, y, (uint8_t) 1);
}

void Level::is_torch_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_torch, x, y, (uint8_t) 1);
}

uint8_t Level::is_burnable(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_burnable, p.x, p.y));
}

uint8_t Level::is_burnable(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_burnable, x, y));
}

void Level::is_burnable_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_burnable, x, y, (uint8_t) 1);
}

void Level::is_burnable_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_burnable, x, y, (uint8_t) 1);
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

void Level::is_heavy_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_heavy, x, y, (uint8_t) 1);
}

void Level::is_heavy_unset(const int x, const int y)
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

void Level::is_secret_door_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_secret_door, x, y, (uint8_t) 1);
}

void Level::is_secret_door_unset(const int x, const int y)
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

void Level::is_ripple_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_ripple, x, y, (uint8_t) 1);
}

void Level::is_ripple_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_ripple, x, y, (uint8_t) 1);
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

void Level::is_mob_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_mob, x, y, (uint8_t) 1);
}

void Level::is_mob_unset(const int x, const int y)
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

void Level::is_potion_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_potion, x, y, (uint8_t) 1);
}

void Level::is_potion_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_potion, x, y, (uint8_t) 1);
}

uint8_t Level::is_wand_or_staff(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_wand_or_staff, p.x, p.y));
}

uint8_t Level::is_wand_or_staff(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_wand_or_staff, x, y));
}

void Level::is_wand_or_staff_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wand_or_staff, x, y, (uint8_t) 1);
}

void Level::is_wand_or_staff_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_wand_or_staff, x, y, (uint8_t) 1);
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

void Level::is_ring_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_ring, x, y, (uint8_t) 1);
}

void Level::is_ring_unset(const int x, const int y)
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

void Level::is_red_blood_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_red_blood, x, y, (uint8_t) 1);
}

void Level::is_red_blood_unset(const int x, const int y)
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

void Level::is_green_blood_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_green_blood, x, y, (uint8_t) 1);
}

void Level::is_green_blood_unset(const int x, const int y)
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

void Level::gfx_water_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_gfx_water, x, y, (uint8_t) 1);
}

void Level::gfx_water_unset(const int x, const int y)
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

void Level::is_deep_water_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_deep_water, x, y, (uint8_t) 1);
}

void Level::is_deep_water_unset(const int x, const int y)
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

void Level::is_shallow_water_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_shallow_water, x, y, (uint8_t) 1);
}

void Level::is_shallow_water_unset(const int x, const int y)
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

void Level::is_wall_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wall, x, y, (uint8_t) 1);
}

void Level::is_wall_unset(const int x, const int y)
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

void Level::is_corridor_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_corridor, x, y, (uint8_t) 1);
}

void Level::is_corridor_unset(const int x, const int y)
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

void Level::is_bridge_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_bridge, x, y, (uint8_t) 1);
}

void Level::is_bridge_unset(const int x, const int y)
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

void Level::is_dirt_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_dirt, x, y, (uint8_t) 1);
}

void Level::is_dirt_unset(const int x, const int y)
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

void Level::is_dry_grass_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_dry_grass, x, y, (uint8_t) 1);
}

void Level::is_dry_grass_unset(const int x, const int y)
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

void Level::is_wet_grass_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_wet_grass, x, y, (uint8_t) 1);
}

void Level::is_wet_grass_unset(const int x, const int y)
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

void Level::is_enchantstone_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_enchantstone, x, y, (uint8_t) 1);
}

void Level::is_enchantstone_unset(const int x, const int y)
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

void Level::is_skillstone_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_skillstone, x, y, (uint8_t) 1);
}

void Level::is_skillstone_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_skillstone, x, y, (uint8_t) 1);
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

void Level::is_spiderweb_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_spiderweb, x, y, (uint8_t) 1);
}

void Level::is_spiderweb_unset(const int x, const int y)
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

void Level::is_sticky_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_sticky, x, y, (uint8_t) 1);
}

void Level::is_sticky_unset(const int x, const int y)
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

void Level::is_shovable_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_shovable, x, y, (uint8_t) 1);
}

void Level::is_shovable_unset(const int x, const int y)
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

void Level::is_floor_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_floor, x, y, (uint8_t) 1);
}

void Level::is_floor_unset(const int x, const int y)
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

void Level::is_rock_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_rock, x, y, (uint8_t) 1);
}

void Level::is_rock_unset(const int x, const int y)
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

void Level::is_able_to_stand_on_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_able_to_stand_on, x, y, (uint8_t) 1);
}

void Level::is_able_to_stand_on_unset(const int x, const int y)
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

void Level::is_corpse_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_corpse, x, y, (uint8_t) 1);
}

void Level::is_corpse_unset(const int x, const int y)
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

void Level::is_monst_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_monst, x, y, (uint8_t) 1);
}

void Level::is_monst_unset(const int x, const int y)
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

void Level::is_door_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_door, x, y, (uint8_t) 1);
}

void Level::is_door_unset(const int x, const int y)
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

void Level::is_key_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_key, x, y, (uint8_t) 1);
}

void Level::is_key_unset(const int x, const int y)
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

void Level::is_food_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_food, x, y, (uint8_t) 1);
}

void Level::is_food_unset(const int x, const int y)
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

void Level::is_treasure_type_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_treasure_type, x, y, (uint8_t) 1);
}

void Level::is_treasure_type_unset(const int x, const int y)
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

void Level::is_gold_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_gold, x, y, (uint8_t) 1);
}

void Level::is_gold_unset(const int x, const int y)
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

void Level::is_ascend_dungeon_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_ascend_dungeon, x, y, (uint8_t) 1);
}

void Level::is_ascend_dungeon_unset(const int x, const int y)
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

void Level::is_descend_dungeon_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_descend_dungeon, x, y, (uint8_t) 1);
}

void Level::is_descend_dungeon_unset(const int x, const int y)
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

void Level::is_ascend_sewer_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_ascend_sewer, x, y, (uint8_t) 1);
}

void Level::is_ascend_sewer_unset(const int x, const int y)
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

void Level::is_descend_sewer_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_descend_sewer, x, y, (uint8_t) 1);
}

void Level::is_descend_sewer_unset(const int x, const int y)
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

void Level::is_smoke_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_smoke, x, y, (uint8_t) 1);
}

void Level::is_smoke_unset(const int x, const int y)
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

void Level::fade_in_incr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  auto v = get(_fade_in_map, x, y);
  if (v < 255) {
    v++;
    set(_fade_in_map, x, y, v);
  } else {
    set(_fade_in_map, x, y, (uint8_t) 255);
  }
}

void Level::fade_in_no_check_incr(const int x, const int y)
{
  auto v = get_no_check(_fade_in_map, x, y);
  if (v < 255) {
    v++;
    set_no_check(_fade_in_map, x, y, v);
  } else {
    set(_fade_in_map, x, y, (uint8_t) 255);
  }
}

void Level::fade_in_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_fade_in_map, x, y, (uint8_t) 0);
}

void Level::fade_in_no_check_unset(const int x, const int y) { set_no_check(_fade_in_map, x, y, (uint8_t) 0); }

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

void Level::is_light_blocker_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_light_blocker, x, y, true);
}

void Level::is_light_blocker_no_check_set(const int x, const int y) { set_no_check(_is_light_blocker, x, y, true); }

void Level::is_light_blocker_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_light_blocker, x, y, false);
}

void Level::is_light_blocker_no_check_unset(const int x, const int y)
{
  set_no_check(_is_light_blocker, x, y, false);
}

//
// Used in lighting, so inlined
//
bool Level::is_light_blocker_for_monst(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_light_blocker_for_monst, p.x, p.y));
}

bool Level::is_light_blocker_for_monst_no_check(const point p) const
{
  return (get_no_check(_is_light_blocker_for_monst, p.x, p.y));
}

bool Level::is_light_blocker_for_monst(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_light_blocker_for_monst, x, y));
}

bool Level::is_light_blocker_for_monst_no_check(const int x, const int y) const
{
  return (get_no_check(_is_light_blocker_for_monst, x, y));
}

void Level::is_light_blocker_for_monst_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_light_blocker_for_monst, x, y, true);
}

void Level::is_light_blocker_for_monst_no_check_set(const int x, const int y)
{
  set_no_check(_is_light_blocker_for_monst, x, y, true);
}

void Level::is_light_blocker_for_monst_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_light_blocker_for_monst, x, y, false);
}

void Level::is_light_blocker_for_monst_no_check_unset(const int x, const int y)
{
  set_no_check(_is_light_blocker_for_monst, x, y, false);
}

bool Level::is_gas_blocker(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_gas_blocker, p.x, p.y));
}

bool Level::is_gas_blocker_no_check(const point p) const { return (get_no_check(_is_gas_blocker, p.x, p.y)); }

bool Level::is_gas_blocker(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_gas_blocker, x, y));
}

bool Level::is_gas_blocker_no_check(const int x, const int y) const { return (get_no_check(_is_gas_blocker, x, y)); }

void Level::is_gas_blocker_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_blocker, x, y, true);
}

void Level::is_gas_blocker_no_check_set(const int x, const int y) { set_no_check(_is_gas_blocker, x, y, true); }

void Level::is_gas_blocker_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_blocker, x, y, false);
}

void Level::is_gas_blocker_no_check_unset(const int x, const int y) { set_no_check(_is_gas_blocker, x, y, false); }

bool Level::noise_blocker(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_noise_blocker, p.x, p.y));
}

bool Level::noise_blocker_no_check(const point p) const { return (get_no_check(_noise_blocker, p.x, p.y)); }

bool Level::noise_blocker(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_noise_blocker, x, y));
}

bool Level::noise_blocker_no_check(const int x, const int y) const { return (get_no_check(_noise_blocker, x, y)); }

void Level::noise_blocker_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noise_blocker, x, y, true);
}

void Level::noise_blocker_no_check_set(const int x, const int y) { set_no_check(_noise_blocker, x, y, true); }

void Level::noise_blocker_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_noise_blocker, x, y, false);
}

void Level::noise_blocker_no_check_unset(const int x, const int y) { set_no_check(_noise_blocker, x, y, false); }

uint8_t Level::is_gas_poison(const point p) const
{
  if (unlikely(is_oob(p.x, p.y))) {
    return 0;
  }
  return (get(_is_gas_poison, p.x, p.y));
}

uint8_t Level::is_gas_poison_no_check(const point p) const { return (get_no_check(_is_gas_poison, p.x, p.y)); }

uint8_t Level::is_gas_poison(const int x, const int y) const
{
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_gas_poison, x, y));
}

uint8_t Level::is_gas_poison_no_check(const int x, const int y) const { return (get_no_check(_is_gas_poison, x, y)); }

void Level::is_gas_poison_set(const int x, const int y, uint8_t val)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_poison, x, y, val);
}

void Level::is_gas_poison_no_check_set(const int x, const int y, uint8_t val)
{
  set_no_check(_is_gas_poison, x, y, val);
}

void Level::is_gas_poison_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_gas_poison, x, y, (uint8_t) 0);
}

void Level::is_gas_poison_no_check_unset(const int x, const int y)
{
  set_no_check(_is_gas_poison, x, y, (uint8_t) 0);
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

void Level::is_obs_wall_or_door_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_wall_or_door, x, y, true);
}

void Level::is_obs_wall_or_door_no_check_set(const int x, const int y)
{
  set_no_check(_is_obs_wall_or_door, x, y, true);
}

void Level::is_obs_wall_or_door_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_wall_or_door, x, y, false);
}

void Level::is_obs_wall_or_door_no_check_unset(const int x, const int y)
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

void Level::is_obs_destructable_set(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_destructable, x, y, true);
}

void Level::is_obs_destructable_no_check_set(const int x, const int y)
{
  set_no_check(_is_obs_destructable, x, y, true);
}

void Level::is_obs_destructable_unset(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) {
    return;
  }
  set(_is_obs_destructable, x, y, false);
}

void Level::is_obs_destructable_no_check_unset(const int x, const int y)
{
  set_no_check(_is_obs_destructable, x, y, false);
}

uint8_t Level::is_brazier(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_brazier, p.x, p.y));
}

uint8_t Level::is_brazier(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_brazier, x, y));
}
uint8_t Level::is_brazier_no_check(const int x, const int y) { return (get(_is_brazier, x, y)); }

void Level::is_brazier_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_brazier, x, y, (uint8_t) 1);
}

void Level::is_brazier_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_brazier, x, y, (uint8_t) 1);
}
uint8_t Level::is_fire(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_fire, p.x, p.y));
}

uint8_t Level::is_fire(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_fire, x, y));
}

uint8_t Level::is_fire_no_check(const int x, const int y) { return (get(_is_fire, x, y)); }

void Level::is_fire_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  incr(_is_fire, x, y, (uint8_t) 1);
}

void Level::is_fire_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  decr(_is_fire, x, y, (uint8_t) 1);
}
