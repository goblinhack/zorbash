//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_main.h"
#include "my_monst.h"
#include "my_random.h"
#include "my_sprintf.h"
#include "my_sys.h"
#include "my_thing.h"

int Thing::item_count_including_charges(Tpp tp)
{
  TRACE_AND_INDENT();
  auto count = 0;
  for (auto oid : monst_infop->carrying) {
    auto o = level->thing_find(oid);
    if (! o) {
      continue;
    }

    if (o->tp() == tp) {
      if (o->is_bag_item_not_stackable()) {
        count = 1;
      } else {
        if (o->get_charge_count()) {
          count += o->get_charge_count();
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
  TRACE_AND_INDENT();
  auto count = 0;
  for (auto oid : monst_infop->carrying) {
    auto o = level->thing_find(oid);
    if (! o) {
      continue;
    }

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
  TRACE_AND_INDENT();
  //
  // Light source follows the thing.
  //
  update_light();

  //
  // Weapons follow also.
  //
  if (get_weapon_id_carry_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_carry_anim());
    if (w) {
      w->move_to(mid_at);
      w->dir = dir;
    }
  }

  if (get_weapon_id_use_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_use_anim());
    if (w) {
      w->move_to(mid_at);
      w->dir = dir;
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  if (monst_infop) {
    for (auto oid : monst_infop->carrying) {
      auto o = level->thing_find(oid);
      if (o) {
        o->move_to(mid_at);
        o->dir = dir;
      }
    }
  }

  //
  // If something moves on the water, make a ripple
  //
  if (is_monst() || is_player()) {
    if (! is_floating()) {
      if (level->is_shallow_water((int) mid_at.x, (int) mid_at.y) &&
          ! level->is_ripple((int) mid_at.x, (int) mid_at.y)) {
        point at(mid_at.x, mid_at.y);
        dbg("Causes ripples");
        if (game->robot_mode) {
          //
          // Faster
          //
          if (pcg_random_range(0, 1000) > 900) {
            level->thing_new(tp_random_ripple()->name(), at);
          }
        } else {
          if (pcg_random_range(0, 1000) > 500) {
            level->thing_new(tp_random_ripple()->name(), at);
          }
        }
      }
    }
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {
    TRACE_AND_INDENT();
    auto w = level->thing_find(on_fire_anim_id);
    if (w) {
      w->move_to(mid_at);
      w->dir = dir;
    }
  }
}

void Thing::move_carried_items_immediately(void)
{
  TRACE_AND_INDENT();
  //
  // Light source follows the thing.
  //
  update_light();

  //
  // Weapons follow also.
  //
  if (get_weapon_id_carry_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_carry_anim());
    if (w) {
      w->move_to_immediately(mid_at);
      w->dir = dir;
    }
  }

  if (get_weapon_id_use_anim().ok()) {
    auto w = level->thing_find(get_weapon_id_use_anim());
    if (w) {
      w->move_to_immediately(mid_at);
      w->dir = dir;
    }
  }

  //
  // Move carried items too as when we attack, we will use say the
  // carried sword and so it had better be in the same location.
  //
  if (monst_infop) {
    for (auto oid : monst_infop->carrying) {
      auto o = level->thing_find(oid);
      if (o) {
        o->move_to_immediately(mid_at);
        o->dir = dir;
      }
    }
  }

  auto on_fire_anim_id = get_on_fire_anim_id();
  if (on_fire_anim_id.ok()) {
    TRACE_AND_INDENT();
    auto w = level->thing_find(on_fire_anim_id);
    if (w) {
      w->move_to_immediately(mid_at);
      w->dir = dir;
    }
  }
}

bool Thing::is_carrying_item(void)
{
  TRACE_AND_INDENT();
  if (! monst_infop) {
    return false;
  }

  if (monst_infop->carrying.size()) {
    return true;
  }

  auto owner = get_top_owner();
  if (owner) {
    return owner->is_carrying_item();
  }

  return false;
}

std::vector< Thingp > Thing::get_item_list(void)
{
  TRACE_AND_INDENT();
  std::vector< Thingp > tr;
  dbg("Carried items:");
  TRACE_AND_INDENT();
  if (! monst_infop) {
    dbg("Not carrying");
    return tr;
  }

  for (const auto &item : monst_infop->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }

    dbg("Item %s", t->to_string().c_str());
    if (t->monst_infop && t->monst_infop->carrying.size()) {
      auto tr2 = t->get_item_list();
      std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
    }

    if (t->is_bag_item()) {
      tr.push_back(t);
    }
  }

  auto owner = get_immediate_owner();
  if (owner) {
    auto tr2 = owner->get_item_list();
    std::move(tr2.begin(), tr2.end(), std::back_inserter(tr));
  }

  return tr;
}
