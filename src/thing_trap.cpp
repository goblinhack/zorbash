//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::trap_tick(void)
{
  if (is_floating() || is_flying() || is_ethereal()) {
    return;
  }

  if (! level->is_trap(curr_at.x, curr_at.y)) {
    return;
  }

  dbg("Trap tick");
  TRACE_AND_INDENT();

  //
  // Find all non traps and crush them
  //
  FOR_ALL_THINGS_THAT_INTERACT(level, victim, curr_at.x, curr_at.y)
  {
    if (victim->is_trap()) {
      continue;
    }

    on_activated(victim);
  }
  FOR_ALL_THINGS_END()
}

uint8_t Level::is_trap(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_trap, p.x, p.y));
}

uint8_t Level::is_trap(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_trap, x, y));
}

void Level::is_trap_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_trap, x, y, (uint8_t) 1);
}

void Level::is_trap_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_trap, x, y, (uint8_t) 1);
}

//
// Python callback upon being stealing
//
void Thing::on_activated(Thingp victim)
{
  TRACE_NO_INDENT();
  auto on_activated = tp()->on_activated_do();
  if (std::empty(on_activated)) {
    return;
  }

  auto t = split_tokens(on_activated, '.');
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

    con("Call %s.%s(%s %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), victim->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, victim->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_activated call [%s] expected mod:function, got %d elems", on_activated.c_str(),
        (int) on_activated.size());
  }
}

const std::string &Thing::on_activated_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_activated_do());
}
