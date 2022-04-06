//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

const Dice &Thing::damage_cold_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_cold_dice());
}

const std::string Thing::damage_cold_dice_str(void)
{
  TRACE_NO_INDENT();

  if (enchant_get()) {
    return tp()->damage_cold_dice_str() + modifier_to_string(enchant_get());
  }

  return (tp()->damage_cold_dice_str());
}

int Thing::damage_cold(void)
{
  TRACE_NO_INDENT();
  auto roll    = tp()->damage_cold_dice().roll();
  auto enchant = enchant_get();
  dbg("Damage cold roll %d + enchant %d", roll, enchant);
  return roll + enchant;
}

int Thing::on_owner_receiving_damage_cold(Thingp owner, Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_cold null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_cold null thing");
    return damage;
  }

  auto on_owner_receiving_damage_cold = on_owner_receiving_damage_cold_do();
  if (std::empty(on_owner_receiving_damage_cold)) {
    return damage;
  }

  auto t = split_tokens(on_owner_receiving_damage_cold, '.');
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

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), owner->to_string().c_str(),
        hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, real_hitter->id.id,
                          (unsigned int) curr_at.x, (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_receiving_damage_cold call [%s] expected mod:function, got %d elems", on_owner_receiving_damage_cold.c_str(),
      (int) on_owner_receiving_damage_cold.size());

  return damage;
}

int Thing::on_receiving_damage_cold(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot damage_cold null thing");
    return damage;
  }

  auto on_receiving_damage_cold = on_receiving_damage_cold_do();
  if (std::empty(on_receiving_damage_cold)) {
    return damage;
  }

  auto t = split_tokens(on_receiving_damage_cold, '.');
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

    dbg("Call %s.%s(%s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_receiving_damage_cold call [%s] expected mod:function, got %d elems", on_receiving_damage_cold.c_str(),
      (int) on_receiving_damage_cold.size());

  return damage;
}

int Thing::total_on_receiving_damage_cold(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receiving_damage_cold(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receiving_damage_cold(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_receiving_damage_cold(this, hitter, real_hitter, damage);
    }
  }

  damage = on_receiving_damage_cold(hitter, real_hitter, damage);

  return damage;
}
