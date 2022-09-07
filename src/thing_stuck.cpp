//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_stuck(void)
{
  TRACE_NO_INDENT();

  auto on_stuck = tp()->on_stuck_do();
  if (std::empty(on_stuck)) {
    return;
  }

  auto t = split_tokens(on_stuck, '.');
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

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_stuck call [%s] expected mod:function, got %d elems", on_stuck.c_str(), (int) on_stuck.size());
  }
}

void Thing::stuck(const std::string &why)
{
  dbg("Stuck: %s", why.c_str());
  TRACE_AND_INDENT();

  stuck_count_incr();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_stuck_do().empty()) {
        iter->stuck(why);
      }
    }
  }
}

bool Thing::is_stuck(void)
{
  if (is_sticky()) {
    return false;
  }

  if (! is_monst() && ! is_player()) {
    return false;
  }

  if (! level->is_sticky(curr_at.x, curr_at.y)) {
    return false;
  }

  if (buff_find_is_slippery()) {
    return false;
  }

  if (is_immune_to_spiderwebs() && level->is_spiderweb(curr_at.x, curr_at.y)) {
    return false;
  }

  //
  // Makes sure ghosts (or the cursor!) do not get stuck in webs.
  //
  if (is_ethereal()) {
    return false;
  }
  return true;
}

int Thing::stuck_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->stuck_count);
  } else {
    return 0;
  }
}

int Thing::stuck_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count = v);
}

int Thing::stuck_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count -= v);
}

int Thing::stuck_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count += v);
}

int Thing::stuck_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count--);
}

int Thing::stuck_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count++);
}
