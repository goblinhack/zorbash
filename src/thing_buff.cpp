//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
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
  dbg("Try to add buff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
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

  FOR_ALL_BUFFS(item)
  {
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

  get_itemsp()->buffs.push_front(what->id);
  what->set_owner(this);
  what->hide();

  dbg("Add buff %s", what->to_short_string().c_str());

  if (is_player()) {
    wid_buffbox_init();
  }

  return true;
}

bool Thing::buff_remove(Thingp what)
{
  dbg("Removing buff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = what->get_immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove buff %s which is not owned", what->to_short_string().c_str());
    return false;
  }

  if (is_player()) {
    buffbox_id_remove(what);
  }

  what->remove_owner();
  get_itemsp()->buffs.remove(what->id);
  game->request_remake_buffbox = true;

  dbg("Removed %s", what->to_short_string().c_str());
  return true;
}

bool Thing::buff_find(const std::string &what)
{
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->name() == what) {
        return true;
      }
    }
  }
  return false;
}

void Thing::buff_remove_all(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return;
  }

  while (! get_itemsp()->buffs.empty()) {
    auto id = *get_itemsp()->buffs.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    buff_remove(t);
  }
}

bool Thing::buff_use(Thingp what)
{
  dbg("Try to use buff %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  used(what, this, false /* remove after use */);
  return true;
}

bool Thing::buff_add(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }

  //
  // Need to allow for duplicates, so cannot check if the tp exists
  //
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    return false;
  }

  dbg("Add buff: %s", t->to_string().c_str());
  TRACE_AND_INDENT();

  buff_add(t);

  return true;
}

bool Thing::buff_remove(Tpp what)
{
  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(item)
  {
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
  if (! maybe_itemsp()) {
    return;
  }

  if (get_itemsp()->buffs.empty()) {
    return;
  }

  dbg("Buff tick");
  TRACE_AND_INDENT();

  FOR_ALL_BUFFS(item)
  {
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
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_poison(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future1(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future1(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future2(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future2(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future3(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future3(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_future4(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_future4(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_fire(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_fire(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_crush(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_crush(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_lightning(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_lightning(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_energy(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_energy(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_acid(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_acid(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_digest(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_digest(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_stat_con(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_stat_con(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_stat_str(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_stat_str(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_melee(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_melee(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_necrosis(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_necrosis(this, hitter, damage);
    }
  }
  return damage;
}

int Thing::buff_on_damage_natural_attack(Thingp hitter, int damage)
{
  if (! maybe_itemsp()) {
    return damage;
  }
  if (get_itemsp()->buffs.empty()) {
    return damage;
  }
  FOR_ALL_BUFFS(item)
  {
    auto t = level->thing_find(item.id);
    if (t) {
      damage = t->on_owner_damage_natural_attack(this, hitter, damage);
    }
  }
  return damage;
}
