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

const Dice &Thing::damage_crush_dice_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->damage_crush_dice_get());
}

const std::string Thing::damage_crush_dice_str_get(void)
{
  TRACE_NO_INDENT();

  if (enchant_get()) {
    return tp()->damage_crush_dice_str_get() + modifier_to_string(enchant_get());
  }

  return (tp()->damage_crush_dice_str_get());
}

int Thing::damage_crush_get(void)
{
  TRACE_NO_INDENT();
  auto roll = tp()->damage_crush_dice_get().roll();

  if (roll) {
    return roll + enchant_get();
  }
  return roll;
}

int Thing::on_owner_damage_crush(Thingp owner, Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, owner);
  if (! owner) {
    err("Cannot owner_damage_crush null thing");
    return damage;
  }

  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot owner_damage_crush null thing");
    return damage;
  }

  auto on_owner_damage_crush = on_owner_damage_crush_do();
  if (std::empty(on_owner_damage_crush)) {
    return damage;
  }

  auto t = split_tokens(on_owner_damage_crush, '.');
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

  ERR("Bad on_owner_damage_crush call [%s] expected mod:function, got %d elems", on_owner_damage_crush.c_str(),
      (int) on_owner_damage_crush.size());

  return damage;
}

int Thing::on_damage_crush(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, hitter);
  if (! hitter) {
    err("Cannot damage_crush null thing");
    return damage;
  }

  auto on_damage_crush = on_damage_crush_do();
  if (std::empty(on_damage_crush)) {
    return damage;
  }

  auto t = split_tokens(on_damage_crush, '.');
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

  ERR("Bad on_damage_crush call [%s] expected mod:function, got %d elems", on_damage_crush.c_str(),
      (int) on_damage_crush.size());

  return damage;
}
