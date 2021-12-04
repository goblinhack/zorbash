//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_buffbox.hpp"

bool Thing::buff_add(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to add buff %s", what->to_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemp()) {
    dbg("No; not a monst");
    return false;
  }

  auto existing_owner = what->get_immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      dbg("No; same owner");
      return true;
    }
    existing_owner->drop(what);
  }

  for (const auto &item : get_itemp()->buffs) {
    if (item == what->id) {
      dbg("No; already carried");
      return true;
    }
  }

  if (is_player()) {
    if (! buffbox_id_insert(what)) {
      dbg("No; no space in buffbox");
      return false;
    }
  }

  get_itemp()->buffs.push_front(what->id);
  what->set_owner(this);
  what->hide();

  dbg("Add buff %s", what->to_string().c_str());

  if (is_player()) {
    wid_buffbox_init();
  }

  return true;
}

bool Thing::buff_remove(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Removing buff %s", what->to_string().c_str());
  TRACE_AND_INDENT();
  auto existing_owner = what->get_immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove buff %s which is not owned", what->to_string().c_str());
    return false;
  }

  if (is_player()) {
    buffbox_id_remove(what);
  }

  what->remove_owner();
  get_itemp()->buffs.remove(what->id);
  game->request_remake_buffbox = true;

  dbg("Removed %s", what->to_string().c_str());
  return true;
}

void Thing::buff_remove_all(void)
{
  TRACE_AND_INDENT();
  if (! maybe_itemp()) {
    return;
  }

  while (! get_itemp()->buffs.empty()) {
    auto id = *get_itemp()->buffs.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    buff_remove(t);
  }
}

bool Thing::buff_use(Thingp what)
{
  TRACE_AND_INDENT();
  dbg("Try to use buff %s", what->to_string().c_str());
  used(what, this, false /* remove after use */);
  return true;
}

bool Thing::buff_add(Tpp what)
{
  if (! maybe_itemp()) {
    return false;
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(what, mid_at);
  if (unlikely(! t)) {
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Add buff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();
  buff_add(t);

  return true;
}

bool Thing::buff_remove(Tpp what)
{
  if (! maybe_itemp()) {
    return false;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t && (t->tp() == what)) {
      buff_remove(t);
      return true;
    }
  }
  return false;
}

void Thing::buff_tick(void)
{
  if (! maybe_itemp()) {
    return;
  }
  if (get_itemp()->buffs.empty()) {
    return;
  }

  TRACE_AND_INDENT();
  dbg("Buff tick");
  TRACE_AND_INDENT();

  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      dbg("Buff (%s)", t->to_string().c_str());
      if (! t->on_tick()) {
        return;
      }
      if (is_dead) {
        return;
      }
    }
  }
}

int Thing::buff_on_damage_poison(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_poison(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future1(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future1(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future2(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future2(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future3(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future3(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future4(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future4(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future5(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future5(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future6(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future6(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future7(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future7(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future8(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future8(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future9(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future9(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_digest(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_digest(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_constitution(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_constitution(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_strength(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_strength(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_melee(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_melee(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_necrosis(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_necrosis(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_bite(Thingp hitter, int damage)
{
  if (! maybe_itemp()) {
    return damage;
  }
  if (get_itemp()->buffs.empty()) {
    return damage;
  }
  for (const auto &item : get_itemp()->buffs) {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_bite(this, hitter, damage);
    }
  }
  return damage;
}
