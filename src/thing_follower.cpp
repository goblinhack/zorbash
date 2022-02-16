//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_color.hpp"
#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
// REMOVED #include "my_sprintf.hpp"
// REMOVED #include "my_string.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"

void Thing::on_you_are_declared_a_follower(Thingp leader)
{
  verify(MTYPE_THING, leader);
  if (! leader) {
    err("Cannot you_are_declared_a_follower null thing");
    return;
  }

  auto on_you_are_declared_a_follower = on_you_are_declared_a_follower_do();
  if (std::empty(on_you_are_declared_a_follower)) {
    return;
  }

  auto t = split_tokens(on_you_are_declared_a_follower, '.');
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

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), leader->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, leader->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_you_are_declared_a_follower call [%s] expected mod:function, got %d elems",
        on_you_are_declared_a_follower.c_str(), (int) on_you_are_declared_a_follower.size());
  }
}

void Thing::on_death_of_a_follower(Thingp leader)
{
  verify(MTYPE_THING, leader);
  if (! leader) {
    err("Cannot follower_death null thing");
    return;
  }

  auto on_death_of_a_follower = on_death_of_a_follower_do();
  if (std::empty(on_death_of_a_follower)) {
    return;
  }

  //
  // Don't call this on death of the follower to avoid spurious post RIP messages
  //
  if (level->is_being_destroyed) {
    dbg("Do not call unset, level being destroyed");
    return;
  }

  auto t = split_tokens(on_death_of_a_follower, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = leader->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), leader->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, leader->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_death_of_a_follower call [%s] expected mod:function, got %d elems", on_death_of_a_follower.c_str(),
        (int) on_death_of_a_follower.size());
  }
}
