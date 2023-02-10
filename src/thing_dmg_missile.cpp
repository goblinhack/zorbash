//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

const Dice &Thing::dmg_missile_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_missile_dice());
}

const std::string Thing::dmg_missile_dice_str(void)
{
  TRACE_NO_INDENT();

  if (enchant_count_get()) {
    return tp()->dmg_missile_dice_str() + modifier_to_string(enchant_count_get());
  }

  return (tp()->dmg_missile_dice_str());
}

int Thing::dmg_missile(void)
{
  TRACE_NO_INDENT();
  auto roll    = tp()->dmg_missile_dice().roll();
  roll         = weapon_dmg_modify(roll);
  auto enchant = enchant_count_get();
  dbg("Damage impact roll %d + enchant %d", roll, enchant);
  return roll + enchant;
}

int Thing::on_owner_receive_dmg_missile(Thingp owner, Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_dmg_missile null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call owner_dmg_missile null thing");
    return damage;
  }

  auto on_owner_receive_dmg_missile = on_owner_receive_dmg_missile_do();
  if (std::empty(on_owner_receive_dmg_missile)) {
    return damage;
  }

  auto t = split_tokens(on_owner_receive_dmg_missile, '.');
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

    dbg2("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
         owner->to_short_string().c_str(), hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, real_hitter->id.id,
                          (unsigned int) curr_at.x, (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_receive_dmg_missile call [%s] expected mod:function, got %d elems",
      on_owner_receive_dmg_missile.c_str(), (int) on_owner_receive_dmg_missile.size());

  return damage;
}

int Thing::on_receiving_dmg_missile(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call dmg_missile null thing");
    return damage;
  }

  auto on_receiving_dmg_missile = on_receiving_dmg_missile_do();
  if (std::empty(on_receiving_dmg_missile)) {
    return damage;
  }

  auto t = split_tokens(on_receiving_dmg_missile, '.');
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

    dbg2("Call %s.%s(%s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
         hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_receiving_dmg_missile call [%s] expected mod:function, got %d elems", on_receiving_dmg_missile.c_str(),
      (int) on_receiving_dmg_missile.size());

  return damage;
}

int Thing::total_dmg_for_on_receiving_dmg_missile(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receive_dmg_missile(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_receive_dmg_missile(this, hitter, real_hitter, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_receive_dmg_missile(this, hitter, real_hitter, damage);
    }
  }

  damage = on_receiving_dmg_missile(hitter, real_hitter, damage);

  return damage;
}

int Thing::on_attacking_dmg_missile(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call dmg_missile null thing");
    return damage;
  }

  auto on_attacking_dmg_missile = on_attacking_dmg_missile_do();
  if (std::empty(on_attacking_dmg_missile)) {
    return damage;
  }

  auto t = split_tokens(on_attacking_dmg_missile, '.');
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

    dbg2("Call %s.%s(%s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
         victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_attacking_dmg_missile call [%s] expected mod:function, got %d elems", on_attacking_dmg_missile.c_str(),
      (int) on_attacking_dmg_missile.size());

  return damage;
}

int Thing::on_owner_attack_dmg_missile(Thingp owner, Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_dmg_missile null thing");
    return damage;
  }

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call owner_dmg_missile null thing");
    return damage;
  }

  auto on_owner_attack_dmg_missile = on_owner_attack_dmg_missile_do();
  if (std::empty(on_owner_attack_dmg_missile)) {
    return damage;
  }

  auto t = split_tokens(on_owner_attack_dmg_missile, '.');
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

    dbg2("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
         owner->to_short_string().c_str(), victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_attack_dmg_missile call [%s] expected mod:function, got %d elems",
      on_owner_attack_dmg_missile.c_str(), (int) on_owner_attack_dmg_missile.size());

  return damage;
}

int Thing::total_dmg_for_on_attacking_dmg_missile(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return damage;
  }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_missile(this, victim, damage);
    }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) {
      damage = iter->on_owner_attack_dmg_missile(this, victim, damage);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      damage = iter->on_owner_attack_dmg_missile(this, victim, damage);
    }
  }

  damage = on_attacking_dmg_missile(victim, damage);

  return damage;
}

int Thing::chance_d1000_dmg_missile(int index)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_dmg_missile(index));
}

const std::string &Thing::on_receiving_dmg_missile_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_receiving_dmg_missile_do());
}

const std::string &Thing::on_attacking_dmg_missile_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_attacking_dmg_missile_do());
}

const std::string &Thing::on_owner_attack_dmg_missile_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_attack_dmg_missile_do());
}

const std::string &Thing::on_owner_receive_dmg_missile_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_receive_dmg_missile_do());
}

int Tp::chance_d1000_dmg_missile(int index) const
{
  if (index >= (int) _chance_d1000_dmg_missile.size()) {
    return 0;
  }
  return _chance_d1000_dmg_missile[ index ];
}

void Tp::chance_d1000_dmg_missile_set(int index, int v)
{
  _chance_d1000_dmg_missile.resize(index + 1);
  _chance_d1000_dmg_missile[ index ] = v;
}
