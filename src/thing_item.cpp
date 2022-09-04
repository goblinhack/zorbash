//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::item_count_including_charges(Tpp tp)
{
  TRACE_NO_INDENT();
  auto count = 0;
  for (const auto o : item_vector()) {
    if (o->tp() == tp) {
      if (o->is_bag_item_not_stackable()) {
        count = 1;
      } else {
        if (o->charge_count()) {
          count += o->charge_count();
        } else {
          count++;
        }
      }
    }
  }

  return count;
}

int Thing::item_count_excluding_charges(Tpp tp)
{
  TRACE_NO_INDENT();
  auto count = 0;
  for (const auto o : item_vector()) {
    if (o->tp() == tp) {
      if (o->is_bag_item_not_stackable()) {
        count = 1;
      } else {
        count++;
      }
    }
  }

  return count;
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
  FOR_ALL_EQUIP(e)
  {
    if (equip_id_carry_anim(e).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(e));
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
      if (equip_id_use_anim(e).ok()) {
        auto w = level->thing_find(equip_id_use_anim(e));
        if (w) {
          w->move_to(curr_at);
          w->dir = dir;
        }
      }
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  if (maybe_itemsp()) {
    for (const auto o : item_vector()) {
      o->move_to(curr_at);
      o->dir = dir;
    }
  }

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating() && ! is_flying() && ! is_offscreen) {
      if (level->is_shallow_water((int) curr_at.x, (int) curr_at.y) &&
          ! level->is_ripple((int) curr_at.x, (int) curr_at.y)) {
        point at(curr_at.x, curr_at.y);
        if (game->tick_current_is_too_slow || game->prev_tick_was_too_slow) {
          //
          // No ripples
          //
        } else {
          if (pcg_random_range(0, 1000) > 500) {
            level->thing_new(tp_random_ripple()->name(), at);
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
    TRACE_NO_INDENT();
    auto w = level->thing_find(id);
    if (w) {
      w->move_to(curr_at);
      w->dir = dir;
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
  FOR_ALL_EQUIP(e)
  {
    if (equip_id_carry_anim(e).ok()) {
      auto w = level->thing_find(equip_id_carry_anim(e));
      if (w) {
        w->move_to_immediately(curr_at);
        w->dir = dir;
      }
    }

    if (equip_id_use_anim(e).ok()) {
      auto w = level->thing_find(equip_id_use_anim(e));
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
    for (const auto o : item_vector()) {
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
