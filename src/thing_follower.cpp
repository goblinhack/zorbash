//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_follower_set(Thingp leader)
{
  verify(MTYPE_THING, leader);
  if (! leader) {
    err("Cannot follower_set null thing");
    return;
  }

  auto on_follower_set = on_follower_set_do();
  if (std::empty(on_follower_set)) {
    return;
  }

  auto t = split_tokens(on_follower_set, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), leader->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, leader->id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_follower_set call [%s] expected mod:function, got %d elems", on_follower_set.c_str(),
        (int) on_follower_set.size());
  }
}

void Thing::on_follower_unset(Thingp leader)
{
  verify(MTYPE_THING, leader);
  if (! leader) {
    err("Cannot follower_unset null thing");
    return;
  }

  auto on_follower_unset = on_follower_unset_do();
  if (std::empty(on_follower_unset)) {
    return;
  }

  //
  // Don't call this on death of the follower to avoid spurious post RIP messages
  //
  if (level->is_being_destroyed) {
    dbg("Do not call unset, level being destroyed");
    return;
  }

  auto t = split_tokens(on_follower_unset, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_string().c_str(), leader->to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, leader->id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_follower_unset call [%s] expected mod:function, got %d elems", on_follower_unset.c_str(),
        (int) on_follower_unset.size());
  }
}
