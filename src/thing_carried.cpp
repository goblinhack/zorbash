//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_level.hpp"
#include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
#include "my_thing.hpp"

//
// Including items in bags
//
std::list< Thingp > Thing::carried_item_only_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemsp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  TRACE_NO_INDENT();
  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      TRACE_NO_INDENT();
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        out.push_back(t);
      }
    }
    out.push_back(t);
  }
  return out;
}

std::vector< Thingp > Thing::carried_item_only_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemsp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  TRACE_NO_INDENT();
  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      TRACE_NO_INDENT();
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        out.push_back(t);
      }
    }
    out.push_back(t);
  }

  return out;
}

//
// Including items in bags
//
std::list< Thingp > Thing::carried_and_equipped_item_list(void)
{
  TRACE_NO_INDENT();

  std::list< Thingp > out;

  if (! maybe_itemsp()) {
    static std::list< Thingp > empty;
    return empty;
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    auto t = equip_get(iter);
    if (t) {
      verify(MTYPE_THING, t);
      out.push_back(t);
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      TRACE_NO_INDENT();
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        out.push_back(t);
      }
    }
    out.push_back(t);
  }
  return out;
}

std::vector< Thingp > Thing::carried_and_equipped_item_vector(void)
{
  TRACE_NO_INDENT();

  std::vector< Thingp > out;

  if (! maybe_itemsp()) {
    static std::vector< Thingp > empty;
    return empty;
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    auto t = equip_get(iter);
    if (t) {
      verify(MTYPE_THING, t);
      out.push_back(t);
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_CARRYING(item)
  {
    auto t = level->thing_find(item.id);
    if (unlikely(! t)) {
      continue;
    }
    if (t->is_bag()) {
      TRACE_NO_INDENT();
      FOR_ALL_CARRIED_BY(t, item)
      {
        auto t = level->thing_find(item.id);
        if (unlikely(! t)) {
          continue;
        }
        out.push_back(t);
      }
    }
    out.push_back(t);
  }

  return out;
}

void Thing::move_carried_items(void)
{
  TRACE_NO_INDENT();

  //
  // Light source follows the thing.
  //
  update_light();

  //
  // Weapons follow also.
  //
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    auto w = equip_get(iter);
    if (w) {
      verify(MTYPE_THING, w);
      w->move_to_immediately(curr_at);
      w->dir = dir;
    }

    if (equip_id_carry_anim(iter).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(iter));
      if (w) {
        w->move_to(curr_at);
        w->dir = dir;
      }
    }

    //
    // Don't move the swing animation. This messes up when we have multiple
    // swings for things like axes, such that this moving animation means
    // we're not sure where the first swing was.
    //
    if (0) {
      if (equip_id_use_anim(iter).ok()) {
        auto w = level->thing_find(equip_id_use_anim(iter));
        if (w) {
          w->move_to(curr_at);
          w->dir = dir;
        }
      }
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BUFFS_FOR(this, id)
  {
    auto iter = level->thing_find(id);
    if (iter) {
      iter->move_to_immediately(curr_at);
      iter->dir = dir;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_DEBUFFS_FOR(this, id)
  {
    auto iter = level->thing_find(id);
    if (iter) {
      iter->move_to_immediately(curr_at);
      iter->dir = dir;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_SKILLS_FOR(this, id)
  {
    auto iter = level->thing_find(id);
    if (iter) {
      iter->move_to_immediately(curr_at);
      iter->dir = dir;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_SPELLS_FOR(this, id)
  {
    auto iter = level->thing_find(id);
    if (iter) {
      iter->move_to_immediately(curr_at);
      iter->dir = dir;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    if (bodypart_id_get(iter).ok()) {
      auto bodypart = level->thing_find(bodypart_id_get(iter));
      if (bodypart) {
        bodypart->move_to(curr_at);
        bodypart->dir = dir;
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  if (maybe_itemsp()) {
    for (const auto o : carried_item_only_vector()) {
      verify(MTYPE_THING, o);
      o->move_to(curr_at);
      o->dir = dir;
    }
  }

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating_currently() && ! is_flying() && is_visible_to_player) {
      if (level->is_shallow_water((int) curr_at.x, (int) curr_at.y)
          && ! level->is_ripple((int) curr_at.x, (int) curr_at.y)) {
        point at(curr_at.x, curr_at.y);
        if (game->tick_current_is_too_slow || game->prev_tick_was_too_slow) {
          //
          // No ripples
          //
        } else {
          if (pcg_random_range(0, 1000) > 500) {
            if (thing_size() < (int) THING_SIZE_NORMAL) {
              level->thing_new(tp_random_small_ripple()->name(), at);
            } else {
              level->thing_new(tp_random_large_ripple()->name(), at);
            }
          }
        }
      }
    }
  }

  //
  // If we're on fire, let the flames follow!
  //
  auto id = on_fire_anim_id();
  if (id.ok()) {
    auto iter = level->thing_find(id);
    if (iter) {
      iter->move_to(curr_at);
      iter->dir = dir;
    }
  }

  if (follower_count()) {
    for (auto follower : all_followers_get()) {
      if (follower->is_spell_of_protection_barrier()) {
        follower->move_to(curr_at);
        follower->dir = dir;
      }
    }
  }
}

void Thing::move_carried_items_immediately(void)
{
  TRACE_NO_INDENT();

  //
  // Light source follows the thing.
  //
  update_light();

  //
  // Weapons follow also.
  //
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(iter)
  {
    auto w = equip_get(iter);
    if (w) {
      w->move_to_immediately(curr_at);
      w->dir = dir;
    }

    if (equip_id_carry_anim(iter).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(iter));
      if (w) {
        w->move_to_immediately(curr_at);
        w->dir = dir;
      }
    }

    if (equip_id_use_anim(iter).ok()) {
      auto w = level->thing_find(equip_id_use_anim(iter));
      if (w) {
        w->move_to_immediately(curr_at);
        w->dir = dir;
      }
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BODYPART(iter)
  {
    if (bodypart_id_get(iter).ok()) {
      auto w = level->thing_find(bodypart_id_get(iter));
      if (w) {
        w->move_to_immediately(curr_at);
        w->dir = dir;
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  if (maybe_itemsp()) {
    for (const auto o : carried_item_only_vector()) {
      o->move_to_immediately(curr_at);
      o->dir = dir;
    }
  }

  auto id = on_fire_anim_id();
  if (id.ok()) {
    TRACE_NO_INDENT();
    auto w = level->thing_find(id);
    if (w) {
      w->move_to_immediately(curr_at);
      w->dir = dir;
    }
  }

  if (follower_count()) {
    for (auto follower : all_followers_get()) {
      if (follower->is_spell_of_protection_barrier()) {
        follower->move_to_immediately(curr_at);
        follower->dir = dir;
      }
    }
  }
}

bool Thing::is_carrying_an_item(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return false;
  }

  if (itemsp()->carrying.size()) {
    return true;
  }

  auto owner = top_owner();
  if (owner) {
    return owner->is_carrying_an_item();
  }

  return false;
}
