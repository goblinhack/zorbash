//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

const Dice &Thing::dmg_cold_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_cold_dice());
}

const std::string Thing::dmg_cold_dice_str(void)
{
  TRACE_NO_INDENT();

  if (enchant_count_get()) {
    return tp()->dmg_cold_dice_str() + bonus_to_string(enchant_count_get());
  }

  return (tp()->dmg_cold_dice_str());
}

int Thing::dmg_cold(Thingp victim)
{
  TRACE_NO_INDENT();
  auto roll    = tp()->dmg_cold_dice().roll();
  roll         = weapon_dmg_modify(roll, victim);
  auto enchant = enchant_count_get();
  dbg("Damage cold roll %d + enchant %d", roll, enchant);
  return roll + enchant;
}

int Thing::on_owner_rcv_dmg_cold(Thingp owner, Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_dmg_cold null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call owner_dmg_cold null thing");
    return damage;
  }

  auto on_owner_rcv_dmg_cold = on_owner_rcv_dmg_cold_do();
  if (std::empty(on_owner_rcv_dmg_cold)) {
    return damage;
  }

  auto t = split_tokens(on_owner_rcv_dmg_cold, '.');
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

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        owner->to_short_string().c_str(), hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, real_hitter->id.id,
                          (unsigned int) curr_at.x, (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_rcv_dmg_cold call [%s] expected mod:function, got %d elems", on_owner_rcv_dmg_cold.c_str(),
      (int) on_owner_rcv_dmg_cold.size());

  return damage;
}

int Thing::on_rcv_dmg_cold(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call dmg_cold null thing");
    return damage;
  }

  auto on_rcv_dmg_cold = on_rcv_dmg_cold_do();
  if (std::empty(on_rcv_dmg_cold)) {
    return damage;
  }

  auto t = split_tokens(on_rcv_dmg_cold, '.');
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

    dbg("Call %s.%s(%s %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), real_hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_rcv_dmg_cold call [%s] expected mod:function, got %d elems", on_rcv_dmg_cold.c_str(),
      (int) on_rcv_dmg_cold.size());

  return damage;
}

int Thing::total_dmg_for_on_rcv_dmg_cold(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_rcv_dmg_cold(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_rcv_dmg_cold(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_SKILLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter && iter->is_activated) {
      damage = iter->on_owner_rcv_dmg_cold(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_SPELLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter && iter->is_activated) {
      damage = iter->on_owner_rcv_dmg_cold(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_rcv_dmg_cold(this, hitter, real_hitter, damage);
    }
  }

  damage = on_rcv_dmg_cold(hitter, real_hitter, damage);

  return damage;
}

int Thing::on_attacking_dmg_cold(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call dmg_cold null thing");
    return damage;
  }

  auto on_attacking_dmg_cold = on_attacking_dmg_cold_do();
  if (std::empty(on_attacking_dmg_cold)) {
    return damage;
  }

  auto t = split_tokens(on_attacking_dmg_cold, '.');
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

  ERR("Bad on_attacking_dmg_cold call [%s] expected mod:function, got %d elems", on_attacking_dmg_cold.c_str(),
      (int) on_attacking_dmg_cold.size());

  return damage;
}

int Thing::on_owner_attack_dmg_cold(Thingp owner, Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_dmg_cold null thing");
    return damage;
  }

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call owner_dmg_cold null thing");
    return damage;
  }

  auto on_owner_attack_dmg_cold = on_owner_attack_dmg_cold_do();
  if (std::empty(on_owner_attack_dmg_cold)) {
    return damage;
  }

  auto t = split_tokens(on_owner_attack_dmg_cold, '.');
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

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        owner->to_short_string().c_str(), victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_attack_dmg_cold call [%s] expected mod:function, got %d elems", on_owner_attack_dmg_cold.c_str(),
      (int) on_owner_attack_dmg_cold.size());

  return damage;
}

int Thing::total_dmg_for_on_attacking_dmg_cold(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_cold(this, victim, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_cold(this, victim, damage);
    }
  }

  FOR_ALL_SKILLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_cold(this, victim, damage);
    }
  }

  FOR_ALL_SPELLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_cold(this, victim, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_attack_dmg_cold(this, victim, damage);
    }
  }

  damage = on_attacking_dmg_cold(victim, damage);

  return damage;
}

int Thing::dmg_chance_d1000_cold(int index)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_chance_d1000_cold(index));
}

const std::string &Thing::on_rcv_dmg_cold_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_rcv_dmg_cold_do());
}

const std::string &Thing::on_attacking_dmg_cold_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_attacking_dmg_cold_do());
}

const std::string &Thing::on_owner_attack_dmg_cold_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_attack_dmg_cold_do());
}

const std::string &Thing::on_owner_rcv_dmg_cold_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_rcv_dmg_cold_do());
}

int Thing::dmg_rcv_doubled_from_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_rcv_doubled_from_cold());
}

int Tp::dmg_chance_d1000_cold(int index) const
{
  if (index >= (int) _dmg_chance_d1000_cold.size()) {
    return 0;
  }
  return _dmg_chance_d1000_cold[ index ];
}

void Tp::dmg_chance_d1000_cold_set(int index, int v)
{
  _dmg_chance_d1000_cold.resize(index + 1);
  _dmg_chance_d1000_cold[ index ] = v;
}
