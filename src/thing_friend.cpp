//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

bool Thing::is_friend(Thingp f)
{
  TRACE_NO_INDENT();
  if (unlikely(! maybe_aip())) {
    return false;
  }

  if (aip()->thing_friends.find(f->id) != aip()->thing_friends.end()) {
    return true;
  }

  if (aip()->perma_friends.find(f->tp()->id) != aip()->perma_friends.end()) {
    return true;
  }

  //
  // Don't attack your own tentacles
  //
  if (same_leader_or_owner(f)) {
    return true;
  }

  return false;
}

void Thing::add_friend(Thingp f)
{
  TRACE_NO_INDENT();

  aip()->thing_friends[ f->id ] = true;
}

void Thing::add_friend(Tpp f)
{
  TRACE_NO_INDENT();

  aip()->perma_friends[ f->id ] = true;
}
