//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"

//
// Python callback upon being fire
//
void Thing::on_fire(void)
{
  TRACE_NO_INDENT();
  auto on_fire = tp()->on_you_are_on_fire_do();
  if (std::empty(on_fire)) {
    return;
  }

  auto t = split_tokens(on_fire, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg2("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_fire call [%s] expected mod:function, got %d elems", on_fire.c_str(), (int) on_fire.size());
  }
}

bool Thing::is_on_fire(void)
{
  TRACE_NO_INDENT();

  auto id = on_fire_anim_id();
  if (! id) {
    return false;
  }

  return id.ok();
}

void Thing::on_fire_unset(void)
{
  TRACE_NO_INDENT();

  if (! is_on_fire()) {
    return;
  }

  auto id = on_fire_anim_id();
  if (! id) {
    return;
  }

  auto fire_anim = level->thing_find(id);
  if (fire_anim) {
    dbg("Unset on fire");
    fire_anim->dead("by removing fire");
    on_fire_anim_id_set(NoThingId);
  }
}

bool Thing::on_fire_set(const std::string &why)
{
  TRACE_NO_INDENT();

  if (is_frozen) {
    return false;
  }

  if (level->is_block_of_ice(curr_at)) {
    return false;
  }

  if (level->is_water(curr_at)) {
    return false;
  }

  if (! is_able_to_burn() && ! is_combustible()) {
    return false;
  }

  //
  // Give some things more of a chance of catching on fire, to be less cruel
  //
  if (chance_d1000_set_on_fire()) {
    if (d10000() > chance_d1000_set_on_fire()) {
      return false;
    }
  }

  if (is_immune_to_fire()) {
    on_fire_unset();
    return false;
  }

  if (is_on_fire()) {
    return true;
  }

  if (is_dead) {
    //
    // If already dead, just spawn the fire and cleanup the corpse.
    //
    corpse_cleanup = true;
    dead("corpse cleanup");

    if (on_fire_anim_id().ok()) {
      return false;
    }

    con("Spawn fire, %s", why.c_str());
    level->thing_new("fire", this);
  } else {
    if (on_fire_anim_id().ok()) {
      return false;
    }

    dbg("Set on fire, %s", why.c_str());
    TRACE_NO_INDENT();

    auto on_fire_anim = level->thing_new("fire", this);
    on_fire_anim_id_set(on_fire_anim->id);
    on_fire_anim->owner_set(this);
    move_carried_items();

    on_fire();

    dbg("Is now on fire, %s", why.c_str());
    TRACE_NO_INDENT();

    if (is_player()) {
      msg("%%fg=red$You are literally ON FIRE!%%fg=reset$");
    }

    //
    // I mean, it's likely this will cause you to wake.
    //
    wake("on fire");
  }

  //
  // In case the fire is over a chasm. Don't call forced as we could
  // have already stepped on lava that triggered this.
  //
  location_check_me();

  return true;
}

//
// When on fire, where to run to?
//
bool Thing::ai_create_on_fire_path(point &nh, const point start, const point end)
{
  TRACE_NO_INDENT();
  Dmap  dmap {};
  point dmap_start = start;
  point dmap_end   = end;

  if (level->is_oob(start) || level->is_oob(end)) {
    err("Cannot create fire path, start %s, end %s", start.to_string().c_str(), end.to_string().c_str());
    return false;
  }

  int minx, miny, maxx, maxy;
  if (dmap_start.x < dmap_end.x) {
    minx = dmap_start.x;
    maxx = dmap_end.x;
  } else {
    minx = dmap_end.x;
    maxx = dmap_start.x;
  }
  if (dmap_start.y < dmap_end.y) {
    miny = dmap_start.y;
    maxy = dmap_end.y;
  } else {
    miny = dmap_end.y;
    maxy = dmap_start.y;
  }

  auto border = TILES_VISIBLE_ACROSS / 2;
  minx -= border;
  miny -= border;
  maxx += border;
  maxy += border;

  if (minx < 0) {
    minx = 0;
  }
  if (miny < 0) {
    miny = 0;
  }
  if (maxx >= MAP_WIDTH) {
    maxx = MAP_WIDTH - 1;
  }
  if (maxy >= MAP_HEIGHT) {
    maxy = MAP_HEIGHT - 1;
  }

  //
  // Set up obstacles for the search. Don't avoid all bad things
  // as we're on fire!
  //
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      if (collision_obstacle(point(x, y))) {
        set(dmap.val, x, y, DMAP_IS_WALL);
      } else {
        set(dmap.val, x, y, DMAP_IS_PASSABLE);
      }
    }
  }

  dmap_start = point(minx, miny);
  dmap_end   = point(maxx, maxy);

  set(dmap.val, end.x, end.y, DMAP_IS_GOAL);
  set(dmap.val, start.x, start.y, DMAP_IS_PASSABLE);

  dmap_process(&dmap, dmap_start, dmap_end, true, true);
#if 0
  dmap_print(&dmap, start, dmap_start, dmap_end);
#endif

  auto p = dmap_solve(&dmap, start);

  char path_debug           = '\0'; // astart path debug
  auto [ result, fallback ] = astar_solve(nullptr, path_debug, start, end, &dmap, true /* allow diagonals */);
#if 0
  for (auto i : result.path) {
    set(dmap.val, i.x, i.y, (uint8_t)0);
  }
  dmap_print(&dmap, start, dmap_start, dmap_end);
#endif

  auto hops     = result.path;
  auto hops_len = hops.size();

  if (hops_len >= 1) {
    auto hop0 = get(hops, hops_len - 1);
    nh        = hop0;
    return true;
  }
  return false;
}

bool Thing::ai_on_fire_choose_target(point &nh)
{
  TRACE_NO_INDENT();
  point start(curr_at.x, curr_at.y);

  //
  // Reached the target? Choose a new one.
  //
  auto target = aip()->wander_dest;

  if (target != point(0, 0)) {
    if (! level->is_shallow_water(target.x, target.y)) {
      //
      // Choose a new wander location
      //
      aip()->wander_dest = point(0, 0);
    }
  }

  if (target != point(0, 0)) {
    if (ai_create_on_fire_path(nh, start, target)) {
      return true;
    }
  }

  //
  // Choose a new wander location
  //
  aip()->wander_dest = point(0, 0);

  auto attempts = 10;
  while (attempts--) {
    auto  tries   = 10;
    auto  closest = std::numeric_limits< int >::max();
    point best;
    auto  got_one = false;

    while (tries--) {
      auto target = dest_random_get(distance_vision_get());
      if (level->is_shallow_water(target)) {
        if (distance(start, target) < closest) {
          dbg("Best (shallow water) at %d,%d", target.x, target.y);
          best    = target;
          got_one = true;
        }
      }
    }

    if (got_one) {
      target = best;
      if (ai_create_on_fire_path(nh, start, target)) {
        aip()->wander_dest = target;
        dbg("On-fire move to %d,%d nh %d,%d", target.x, target.y, nh.x, nh.y);
        if (is_player()) {
          msg("You are thinking of jumping into that cool water!");
          popup("Need water!");
        }
        return true;
      }
      closest = std::numeric_limits< int >::max();
    }
  }

  attempts = 10;
  while (attempts--) {
    auto  tries   = 10;
    auto  closest = std::numeric_limits< int >::max();
    point best;
    auto  got_one = false;

    while (tries--) {
      auto target = dest_random_get(distance_vision_get());
      if (level->is_chasm(target)) {
        if (distance(start, target) < closest) {
          dbg("Best (chasm) at %d,%d", target.x, target.y);
          best    = target;
          got_one = true;
        }
      }
    }

    if (got_one) {
      target = best;
      if (ai_create_on_fire_path(nh, start, target)) {
        aip()->wander_dest = target;
        dbg("On-fire move to %d,%d nh %d,%d", target.x, target.y, nh.x, nh.y);
        if (is_player()) {
          msg("You are thinking of jumping into a chasm!");
          popup("Need water!");
        }
        return true;
      }
      closest = std::numeric_limits< int >::max();
    }
  }

  dbg("on-fire wander failed");
  return false;
}

bool Thing::ai_on_fire(void)
{
  dbg("On fire, try to escape");
  TRACE_AND_INDENT();

  for (auto tries = 1; tries < 10; tries++) {
    point nh;
    dbg("On fire, try %d", tries);
    if (ai_on_fire_choose_target(nh)) {
      if (move_to_or_escape(nh)) {
        return true;
      }

      //
      // Set this so next time we will choose another target
      //
      aip()->wander_dest = point(0, 0);
    }
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////
// on_fire_id_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::on_fire_anim_id(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->on_fire_id_anim);
  }
  return NoThingId;
}

ThingId Thing::on_fire_anim_id_set(ThingId v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->on_fire_id_anim = v);
}
