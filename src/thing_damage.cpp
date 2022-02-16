//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>

#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

int Thing::damage_max(void)
{
  TRACE_NO_INDENT();
  auto max_damage = damage_natural_dice().max_roll();
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future1_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future2_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future3_dice().max_roll());
  max_damage      = std::max(max_damage, damage_cold_dice().max_roll());
  max_damage      = std::max(max_damage, damage_fire_dice().max_roll());
  max_damage      = std::max(max_damage, damage_crush_dice().max_roll());
  max_damage      = std::max(max_damage, damage_lightning_dice().max_roll());
  max_damage      = std::max(max_damage, damage_energy_dice().max_roll());
  max_damage      = std::max(max_damage, damage_acid_dice().max_roll());
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_necrosis_dice().max_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    max_damage = std::max(max_damage, curr_weapon->damage_max());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + enchant_get();
}

int Thing::damage_min(void)
{
  TRACE_NO_INDENT();
  auto min_damage = damage_natural_dice().min_roll();
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future1_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future2_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future3_dice().min_roll());
  min_damage      = std::min(min_damage, damage_cold_dice().min_roll());
  min_damage      = std::min(min_damage, damage_fire_dice().min_roll());
  min_damage      = std::min(min_damage, damage_crush_dice().min_roll());
  min_damage      = std::min(min_damage, damage_lightning_dice().min_roll());
  min_damage      = std::min(min_damage, damage_energy_dice().min_roll());
  min_damage      = std::min(min_damage, damage_acid_dice().min_roll());
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_necrosis_dice().min_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    min_damage = std::min(min_damage, curr_weapon->damage_min());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + enchant_get();
}

int Thing::on_damage_stat_str(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot damage_stat_str null thing");
    return damage;
  }

  auto on_damage_stat_str = on_damage_stat_str_do();
  if (std::empty(on_damage_stat_str)) {
    return damage;
  }

  auto t = split_tokens(on_damage_stat_str, '.');
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

  ERR("Bad on_damage_stat_str call [%s] expected mod:function, got %d elems", on_damage_stat_str.c_str(),
      (int) on_damage_stat_str.size());

  return damage;
}

int Thing::on_damage_stat_att(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot damage_stat_att null thing");
    return damage;
  }

  auto on_damage_stat_att = on_damage_stat_att_do();
  if (std::empty(on_damage_stat_att)) {
    return damage;
  }

  auto t = split_tokens(on_damage_stat_att, '.');
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

  ERR("Bad on_damage_stat_att call [%s] expected mod:function, got %d elems", on_damage_stat_att.c_str(),
      (int) on_damage_stat_att.size());

  return damage;
}

int Thing::on_owner_damage_stat_con(Thingp owner, Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_stat_con null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_stat_con null thing");
    return damage;
  }

  auto on_owner_damage_stat_con = on_owner_damage_stat_con_do();
  if (std::empty(on_owner_damage_stat_con)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_stat_con, '.');
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

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_stat_con call [%s] expected mod:function, got %d elems", on_owner_damage_stat_con.c_str(),
      (int) on_owner_damage_stat_con.size());

  return damage;
}
