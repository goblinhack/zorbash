//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_math.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

const Dice &Thing::get_damage_melee_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->get_damage_melee_dice());
}

const std::string Thing::damage_melee_dice_str_get(void)
{
  TRACE_NO_INDENT();

  if (get_enchant()) {
    return tp()->damage_melee_dice_str_get() + modifier_to_string(get_enchant());
  }

  return (tp()->damage_melee_dice_str_get());
}

int Thing::get_damage_melee(void)
{
  TRACE_NO_INDENT();
  auto roll = tp()->get_damage_melee_dice().roll();

  if (roll) {
    return roll + get_enchant();
  }
  return roll;
}

int Thing::on_owner_damage_melee(Thingp owner, Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
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

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), owner->to_string().c_str(),
        hitter->to_short_string().c_str(), damage);

    return py_call_int_fn(mod.c_str(), fn.c_str(), id.id, owner->id.id, hitter->id.id, (unsigned int) curr_at.x,
                          (unsigned int) curr_at.y, (unsigned int) damage);
  }

  ERR("Bad on_owner_damage_melee call [%s] expected mod:function, got %d elems", on_owner_damage_melee.c_str(),
      (int) on_owner_damage_melee.size());

  return damage;
}

int Thing::on_damage_melee(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot damage_melee null thing");
    return damage;
  }

  auto on_damage_melee = on_damage_melee_do();
  if (std::empty(on_damage_melee)) {
    return damage;
  }

  auto t = split_tokens(on_damage_melee, '.');
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

  ERR("Bad on_damage_melee call [%s] expected mod:function, got %d elems", on_damage_melee.c_str(),
      (int) on_damage_melee.size());

  return damage;
}
