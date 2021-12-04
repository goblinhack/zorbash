//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
// damage_future1
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future1_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future1_dice());
}

const std::string &Thing::get_damage_future1_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future1_dice_str());
}

int Thing::get_damage_future1(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future1_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future1(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future1 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future1 null thing");
    return damage;
  }

  auto on_owner_damage_future1 = on_owner_damage_future1_do();
  if (std::empty(on_owner_damage_future1)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future1, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future1 call [%s] expected mod:function, got %d elems", on_owner_damage_future1.c_str(),
      (int) on_owner_damage_future1.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future2
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future2_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future2_dice());
}

const std::string &Thing::get_damage_future2_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future2_dice_str());
}

int Thing::get_damage_future2(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future2_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future2(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future2 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future2 null thing");
    return damage;
  }

  auto on_owner_damage_future2 = on_owner_damage_future2_do();
  if (std::empty(on_owner_damage_future2)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future2, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future2 call [%s] expected mod:function, got %d elems", on_owner_damage_future2.c_str(),
      (int) on_owner_damage_future2.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future3
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future3_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future3_dice());
}

const std::string &Thing::get_damage_future3_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future3_dice_str());
}

int Thing::get_damage_future3(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future3_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future3(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future3 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future3 null thing");
    return damage;
  }

  auto on_owner_damage_future3 = on_owner_damage_future3_do();
  if (std::empty(on_owner_damage_future3)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future3, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future3 call [%s] expected mod:function, got %d elems", on_owner_damage_future3.c_str(),
      (int) on_owner_damage_future3.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future4
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future4_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future4_dice());
}

const std::string &Thing::get_damage_future4_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future4_dice_str());
}

int Thing::get_damage_future4(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future4_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future4(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future4 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future4 null thing");
    return damage;
  }

  auto on_owner_damage_future4 = on_owner_damage_future4_do();
  if (std::empty(on_owner_damage_future4)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future4, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future4 call [%s] expected mod:function, got %d elems", on_owner_damage_future4.c_str(),
      (int) on_owner_damage_future4.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future5
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future5_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future5_dice());
}

const std::string &Thing::get_damage_future5_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future5_dice_str());
}

int Thing::get_damage_future5(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future5_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future5(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future5 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future5 null thing");
    return damage;
  }

  auto on_owner_damage_future5 = on_owner_damage_future5_do();
  if (std::empty(on_owner_damage_future5)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future5, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future5 call [%s] expected mod:function, got %d elems", on_owner_damage_future5.c_str(),
      (int) on_owner_damage_future5.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future6
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future6_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future6_dice());
}

const std::string &Thing::get_damage_future6_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future6_dice_str());
}

int Thing::get_damage_future6(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future6_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future6(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future6 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future6 null thing");
    return damage;
  }

  auto on_owner_damage_future6 = on_owner_damage_future6_do();
  if (std::empty(on_owner_damage_future6)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future6, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future6 call [%s] expected mod:function, got %d elems", on_owner_damage_future6.c_str(),
      (int) on_owner_damage_future6.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future7
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future7_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future7_dice());
}

const std::string &Thing::get_damage_future7_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future7_dice_str());
}

int Thing::get_damage_future7(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future7_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future7(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future7 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future7 null thing");
    return damage;
  }

  auto on_owner_damage_future7 = on_owner_damage_future7_do();
  if (std::empty(on_owner_damage_future7)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future7, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future7 call [%s] expected mod:function, got %d elems", on_owner_damage_future7.c_str(),
      (int) on_owner_damage_future7.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_future8
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_future8_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future8_dice());
}

const std::string &Thing::get_damage_future8_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_future8_dice_str());
}

int Thing::get_damage_future8(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_future8_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_future8(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_future8 null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_future8 null thing");
    return damage;
  }

  auto on_owner_damage_future8 = on_owner_damage_future8_do();
  if (std::empty(on_owner_damage_future8)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_future8, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_future8 call [%s] expected mod:function, got %d elems", on_owner_damage_future8.c_str(),
      (int) on_owner_damage_future8.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_acid
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_acid_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_acid_dice());
}

const std::string &Thing::get_damage_acid_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_acid_dice_str());
}

int Thing::get_damage_acid(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_acid_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_acid(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_acid null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_acid null thing");
    return damage;
  }

  auto on_owner_damage_acid = on_owner_damage_acid_do();
  if (std::empty(on_owner_damage_acid)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_acid, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_acid call [%s] expected mod:function, got %d elems", on_owner_damage_acid.c_str(),
      (int) on_owner_damage_acid.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// damage_digest
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_digest_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_digest_dice());
}

const std::string &Thing::get_damage_digest_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_digest_dice_str());
}

int Thing::get_damage_digest(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_digest_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_digest(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_digest null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_digest null thing");
    return damage;
  }

  auto on_owner_damage_digest = on_owner_damage_digest_do();
  if (std::empty(on_owner_damage_digest)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_digest, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_digest call [%s] expected mod:function, got %d elems", on_owner_damage_digest.c_str(),
      (int) on_owner_damage_digest.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// melee
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_melee_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_melee_dice());
}

const std::string &Thing::get_damage_melee_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_melee_dice_str());
}

int Thing::get_damage_melee(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_melee_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_melee(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_melee null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_melee null thing");
    return damage;
  }

  auto on_owner_damage_melee = on_owner_damage_melee_do();
  if (std::empty(on_owner_damage_melee)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_melee, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_melee call [%s] expected mod:function, got %d elems", on_owner_damage_melee.c_str(),
      (int) on_owner_damage_melee.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// poison
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_poison_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_poison_dice());
}

const std::string &Thing::get_damage_poison_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_poison_dice_str());
}

int Thing::get_damage_poison(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_poison_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_poison(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_poison null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_poison null thing");
    return damage;
  }

  auto on_owner_damage_poison = on_owner_damage_poison_do();
  if (std::empty(on_owner_damage_poison)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_poison, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_poison call [%s] expected mod:function, got %d elems", on_owner_damage_poison.c_str(),
      (int) on_owner_damage_poison.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// necrosis
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_necrosis_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_necrosis_dice());
}

const std::string &Thing::get_damage_necrosis_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_necrosis_dice_str());
}

int Thing::get_damage_necrosis(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_necrosis_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_necrosis(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_necrosis null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_necrosis null thing");
    return damage;
  }

  auto on_owner_damage_necrosis = on_owner_damage_necrosis_do();
  if (std::empty(on_owner_damage_necrosis)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_necrosis, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_necrosis call [%s] expected mod:function, got %d elems", on_owner_damage_necrosis.c_str(),
      (int) on_owner_damage_necrosis.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// crush
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_crush_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_crush_dice());
}

const std::string &Thing::get_damage_crush_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_crush_dice_str());
}

int Thing::get_damage_crush(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_crush_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// bite
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_bite_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_bite_dice());
}

const std::string &Thing::get_damage_bite_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_bite_dice_str());
}

int Thing::get_damage_bite(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_bite_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_bite(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_bite null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_bite null thing");
    return damage;
  }

  auto on_owner_damage_bite = on_owner_damage_bite_do();
  if (std::empty(on_owner_damage_bite)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_bite, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_bite call [%s] expected mod:function, got %d elems", on_owner_damage_bite.c_str(),
      (int) on_owner_damage_bite.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// misc
///////////////////////////////////////////////////////////////////////////
int Thing::get_damage_max(void)
{
  TRACE_AND_INDENT();
  auto max_damage = get_damage_bite_dice().max_roll();
  max_damage      = std::max(max_damage, get_damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future1_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future2_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future3_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future4_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future5_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future6_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future7_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_future8_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_acid_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_necrosis_dice().max_roll());
  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + get_enchant();
}

int Thing::get_damage_min(void)
{
  TRACE_AND_INDENT();
  auto min_damage = get_damage_bite_dice().min_roll();
  min_damage      = std::min(min_damage, get_damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future1_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future2_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future3_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future4_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future5_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future6_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future7_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_future8_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_acid_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_necrosis_dice().min_roll());
  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + get_enchant();
}

int Thing::on_owner_damage_strength(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_strength null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_strength null thing");
    return damage;
  }

  auto on_owner_damage_strength = on_owner_damage_strength_do();
  if (std::empty(on_owner_damage_strength)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_strength, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_strength call [%s] expected mod:function, got %d elems", on_owner_damage_strength.c_str(),
      (int) on_owner_damage_strength.size());

  return damage;
}

int Thing::on_owner_damage_constitution(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_constitution null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_constitution null thing");
    return damage;
  }

  auto on_owner_damage_constitution = on_owner_damage_constitution_do();
  if (std::empty(on_owner_damage_constitution)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_constitution, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), owner->to_string().c_str(),
        hitter->to_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) mid_at.x,
                          (unsigned int) mid_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_constitution call [%s] expected mod:function, got %d elems",
      on_owner_damage_constitution.c_str(), (int) on_owner_damage_constitution.size());

  return damage;
}
