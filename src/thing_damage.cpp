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

int Thing::on_owner_melee_damage(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_melee_damage null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_melee_damage null thing");
    return damage;
  }

  auto on_owner_melee_damage = on_owner_melee_damage_do();
  if (std::empty(on_owner_melee_damage)) {
    return damage;
  }

  auto t = split_tokens(on_owner_melee_damage, '.');
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

  ERR("Bad on_owner_melee_damage call [%s] expected mod:function, got %d elems", on_owner_melee_damage.c_str(),
      (int) on_owner_melee_damage.size());

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

int Thing::on_owner_poison_damage(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_poison_damage null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_poison_damage null thing");
    return damage;
  }

  auto on_owner_poison_damage = on_owner_poison_damage_do();
  if (std::empty(on_owner_poison_damage)) {
    return damage;
  }

  auto t = split_tokens(on_owner_poison_damage, '.');
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

  ERR("Bad on_owner_poison_damage call [%s] expected mod:function, got %d elems", on_owner_poison_damage.c_str(),
      (int) on_owner_poison_damage.size());

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

int Thing::on_owner_necrosis_damage(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_necrosis_damage null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_necrosis_damage null thing");
    return damage;
  }

  auto on_owner_necrosis_damage = on_owner_necrosis_damage_do();
  if (std::empty(on_owner_necrosis_damage)) {
    return damage;
  }

  auto t = split_tokens(on_owner_necrosis_damage, '.');
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

  ERR("Bad on_owner_necrosis_damage call [%s] expected mod:function, got %d elems", on_owner_necrosis_damage.c_str(),
      (int) on_owner_necrosis_damage.size());

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

int Thing::on_owner_bite_damage(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_bite_damage null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_bite_damage null thing");
    return damage;
  }

  auto on_owner_bite_damage = on_owner_bite_damage_do();
  if (std::empty(on_owner_bite_damage)) {
    return damage;
  }

  auto t = split_tokens(on_owner_bite_damage, '.');
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

  ERR("Bad on_owner_bite_damage call [%s] expected mod:function, got %d elems", on_owner_bite_damage.c_str(),
      (int) on_owner_bite_damage.size());

  return damage;
}

///////////////////////////////////////////////////////////////////////////
// swallow
///////////////////////////////////////////////////////////////////////////
const Dice &Thing::get_damage_swallow_dice(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_swallow_dice());
}

const std::string &Thing::get_damage_swallow_dice_str(void)
{
  TRACE_AND_INDENT();
  return (tp()->get_damage_swallow_dice_str());
}

int Thing::get_damage_swallow(void)
{
  TRACE_AND_INDENT();
  auto roll = tp()->get_damage_swallow_dice().roll();
  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

///////////////////////////////////////////////////////////////////////////
// misc
///////////////////////////////////////////////////////////////////////////
int Thing::get_damage_max(void)
{
  TRACE_AND_INDENT();
  auto max_damage = get_damage_bite_dice().max_roll();
  max_damage      = std::max(max_damage, get_damage_swallow_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, get_damage_poison_dice().max_roll());
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
  min_damage      = std::min(min_damage, get_damage_swallow_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, get_damage_necrosis_dice().min_roll());
  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + get_enchant();
}

int Thing::on_owner_strength_damage(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_strength_damage null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_strength_damage null thing");
    return damage;
  }

  auto on_owner_strength_damage = on_owner_strength_damage_do();
  if (std::empty(on_owner_strength_damage)) {
    return damage;
  }

  auto t = split_tokens(on_owner_strength_damage, '.');
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

  ERR("Bad on_owner_strength_damage call [%s] expected mod:function, got %d elems", on_owner_strength_damage.c_str(),
      (int) on_owner_strength_damage.size());

  return damage;
}

int Thing::on_owner_constitution_damage(Thingp owner, Thingp hitter, int damage)
{
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_constitution_damage null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_constitution_damage null thing");
    return damage;
  }

  auto on_owner_constitution_damage = on_owner_constitution_damage_do();
  if (std::empty(on_owner_constitution_damage)) {
    return damage;
  }

  auto t = split_tokens(on_owner_constitution_damage, '.');
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

  ERR("Bad on_owner_constitution_damage call [%s] expected mod:function, got %d elems",
      on_owner_constitution_damage.c_str(), (int) on_owner_constitution_damage.size());

  return damage;
}
