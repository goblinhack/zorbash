//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

const Dice &Thing::dmg_digest_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_digest_dice());
}

const std::string Thing::dmg_digest_dice_str(void)
{
  TRACE_NO_INDENT();

  if (enchant_count_get()) { return tp()->dmg_digest_dice_str() + bonus_to_string(enchant_count_get()); }

  return (tp()->dmg_digest_dice_str());
}

int Thing::dmg_digest(Thingp victim)
{
  TRACE_NO_INDENT();
  auto roll    = tp()->dmg_digest_dice().roll();
  roll         = weapon_dmg_modify(roll, victim);
  auto enchant = enchant_count_get();
  dbg("Damage digest roll %d + enchant %d", roll, enchant);
  return roll + enchant;
}

int Thing::on_owner_receive_dmg_digest(Thingp owner, Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_dmg_digest null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call owner_dmg_digest null thing");
    return damage;
  }

  auto on_owner_receive_dmg_digest = on_owner_receive_dmg_digest_do();
  if (std::empty(on_owner_receive_dmg_digest)) { return damage; }

  auto t = split_tokens(on_owner_receive_dmg_digest, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) { fn = fn.replace(found, 2, ""); }

    if (mod == "me") { mod = name(); }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        owner->to_short_string().c_str(), hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, real_hitter->id.id,
                          (unsigned int) curr_at.x, (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_receive_dmg_digest call [%s] expected mod:function, got %d elems",
      on_owner_receive_dmg_digest.c_str(), (int) on_owner_receive_dmg_digest.size());

  return damage;
}

int Thing::on_receiving_dmg_digest(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot call dmg_digest null thing");
    return damage;
  }

  auto on_receiving_dmg_digest = on_receiving_dmg_digest_do();
  if (std::empty(on_receiving_dmg_digest)) { return damage; }

  auto t = split_tokens(on_receiving_dmg_digest, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) { fn = fn.replace(found, 2, ""); }

    if (mod == "me") { mod = name(); }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), real_hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_receiving_dmg_digest call [%s] expected mod:function, got %d elems", on_receiving_dmg_digest.c_str(),
      (int) on_receiving_dmg_digest.size());

  return damage;
}

int Thing::total_dmg_for_on_receiving_dmg_digest(Thingp hitter, Thingp real_hitter, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) { return damage; }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_receive_dmg_digest(this, hitter, real_hitter, damage); }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_receive_dmg_digest(this, hitter, real_hitter, damage); }
  }

  FOR_ALL_SKILLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_receive_dmg_digest(this, hitter, real_hitter, damage); }
  }

  FOR_ALL_SPELLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_receive_dmg_digest(this, hitter, real_hitter, damage); }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) { damage = iter->on_owner_receive_dmg_digest(this, hitter, real_hitter, damage); }
  }

  damage = on_receiving_dmg_digest(hitter, real_hitter, damage);

  return damage;
}

int Thing::on_attacking_dmg_digest(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call dmg_digest null thing");
    return damage;
  }

  auto on_attacking_dmg_digest = on_attacking_dmg_digest_do();
  if (std::empty(on_attacking_dmg_digest)) { return damage; }

  auto t = split_tokens(on_attacking_dmg_digest, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) { fn = fn.replace(found, 2, ""); }

    if (mod == "me") { mod = name(); }

    dbg("Call %s.%s(%s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_attacking_dmg_digest call [%s] expected mod:function, got %d elems", on_attacking_dmg_digest.c_str(),
      (int) on_attacking_dmg_digest.size());

  return damage;
}

int Thing::on_owner_attack_dmg_digest(Thingp owner, Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot call owner_dmg_digest null thing");
    return damage;
  }

  verify(MTYPE_THING, victim);
  if (! victim) {
    err("Cannot call owner_dmg_digest null thing");
    return damage;
  }

  auto on_owner_attack_dmg_digest = on_owner_attack_dmg_digest_do();
  if (std::empty(on_owner_attack_dmg_digest)) { return damage; }

  auto t = split_tokens(on_owner_attack_dmg_digest, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) { fn = fn.replace(found, 2, ""); }

    if (mod == "me") { mod = name(); }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        owner->to_short_string().c_str(), victim->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, victim->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_attack_dmg_digest call [%s] expected mod:function, got %d elems",
      on_owner_attack_dmg_digest.c_str(), (int) on_owner_attack_dmg_digest.size());

  return damage;
}

int Thing::total_dmg_for_on_attacking_dmg_digest(Thingp victim, int damage)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) { return damage; }

  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_attack_dmg_digest(this, victim, damage); }
  }

  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_attack_dmg_digest(this, victim, damage); }
  }

  FOR_ALL_SKILLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_attack_dmg_digest(this, victim, damage); }
  }

  FOR_ALL_SPELLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter) { damage = iter->on_owner_attack_dmg_digest(this, victim, damage); }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) { damage = iter->on_owner_attack_dmg_digest(this, victim, damage); }
  }

  damage = on_attacking_dmg_digest(victim, damage);

  return damage;
}

int Thing::dmg_chance_d1000_digest(int index)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_chance_d1000_digest(index));
}

const std::string &Thing::on_receiving_dmg_digest_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_receiving_dmg_digest_do());
}

const std::string &Thing::on_attacking_dmg_digest_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_attacking_dmg_digest_do());
}

const std::string &Thing::on_owner_attack_dmg_digest_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_attack_dmg_digest_do());
}

const std::string &Thing::on_owner_receive_dmg_digest_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_receive_dmg_digest_do());
}

int Tp::dmg_chance_d1000_digest(int index) const
{
  if (index >= (int) _dmg_chance_d1000_digest.size()) { return 0; }
  return _dmg_chance_d1000_digest[ index ];
}

void Tp::dmg_chance_d1000_digest_set(int index, int v)
{
  _dmg_chance_d1000_digest.resize(index + 1);
  _dmg_chance_d1000_digest[ index ] = v;
}
