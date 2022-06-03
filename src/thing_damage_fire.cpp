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

const Dice &Thing::damage_fire_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_fire_dice());
}

const std::string Thing::damage_fire_dice_str(void)
{
  TRACE_NO_INDENT();

  if (enchant_get()) {
    return tp()->damage_fire_dice_str() + modifier_to_string(enchant_get());
  }

  return (tp()->damage_fire_dice_str());
}

int Thing::damage_fire(void)
{
  TRACE_NO_INDENT();
  auto roll    = tp()->damage_fire_dice().roll();
  roll         = weapon_damage_modify(roll);
  auto enchant = enchant_get();
  dbg("Damage fire roll %d + enchant %d", roll, enchant);
  return roll + enchant;
}

int Thing::on_owner_receiving_dmg_fire(Thingp owner, Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_fire null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_fire null thing");
    return damage;
  }

  auto on_owner_receiving_dmg_fire = on_owner_receiving_dmg_fire_do();
  if (std::empty(on_owner_receiving_dmg_fire)) {
    return damage;
  }

  auto t = split_tokens(on_owner_receiving_dmg_fire, '.');
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

  ERR("Bad on_owner_receiving_dmg_fire call [%s] expected mod:function, got %d elems",
      on_owner_receiving_dmg_fire.c_str(), (int) on_owner_receiving_dmg_fire.size());

  return damage;
}

int Thing::on_receiving_dmg_fire(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot damage_fire null thing");
    return damage;
  }

  auto on_receiving_dmg_fire = on_receiving_dmg_fire_do();
  if (std::empty(on_receiving_dmg_fire)) {
    return damage;
  }

  auto t = split_tokens(on_receiving_dmg_fire, '.');
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

  ERR("Bad on_receiving_dmg_fire call [%s] expected mod:function, got %d elems", on_receiving_dmg_fire.c_str(),
      (int) on_receiving_dmg_fire.size());

  return damage;
}

int Thing::get_total_damage_for_on_receiving_dmg_fire(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receiving_dmg_fire(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receiving_dmg_fire(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_receiving_dmg_fire(this, hitter, real_hitter, damage);
    }
  }

  damage = on_receiving_dmg_fire(hitter, real_hitter, damage);

  return damage;
}

int Thing::on_attacking_dmg_fire(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot damage_fire null thing");
    return damage;
  }

  auto on_attacking_dmg_fire = on_attacking_dmg_fire_do();
  if (std::empty(on_attacking_dmg_fire)) {
    return damage;
  }

  auto t = split_tokens(on_attacking_dmg_fire, '.');
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
        victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_attacking_dmg_fire call [%s] expected mod:function, got %d elems", on_attacking_dmg_fire.c_str(),
      (int) on_attacking_dmg_fire.size());

  return damage;
}

int Thing::on_owner_attacking_dmg_fire(Thingp owner, Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_fire null thing");
    return damage;
  }

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot owner_damage_fire null thing");
    return damage;
  }

  auto on_owner_attacking_dmg_fire = on_owner_attacking_dmg_fire_do();
  if (std::empty(on_owner_attacking_dmg_fire)) {
    return damage;
  }

  auto t = split_tokens(on_owner_attacking_dmg_fire, '.');
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
        victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_attacking_dmg_fire call [%s] expected mod:function, got %d elems",
      on_owner_attacking_dmg_fire.c_str(), (int) on_owner_attacking_dmg_fire.size());

  return damage;
}

int Thing::get_total_damage_for_on_attacking_dmg_fire(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attacking_dmg_fire(this, victim, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attacking_dmg_fire(this, victim, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_attacking_dmg_fire(this, victim, damage);
    }
  }

  damage = on_attacking_dmg_fire(victim, damage);

  return damage;
}
