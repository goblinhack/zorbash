//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_array_bounds_check.h"
#include "my_vector_bounds_check.h"
#include "my_dmap.h"
#include "my_monst.h"
#include "my_python.h"
#include "my_string.h"
#include "my_random.h"

//
// Python callback upon being enchant
//
void Thing::on_enchant(void)
{
  TRACE_AND_INDENT();
  auto on_enchant = tp()->on_enchant_do();
  if (std::empty(on_enchant)) {
    return;
  }

  auto t = split_tokens(on_enchant, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) mid_at.x, (unsigned int) mid_at.y);
  } else {
    ERR("Bad on_enchant call [%s] expected mod:function, got %d elems", on_enchant.c_str(), (int) on_enchant.size());
  }
}

bool Thing::enchant(Thingp what)
{
  TRACE_AND_INDENT();
  TOPCON("You enchant %s.", what->text_the().c_str());
  what->on_enchant();
  what->incr_enchant(1);

  //
  // Drop an enchantstone
  //
  auto found = false;
  for (auto id : monstp->carrying) {
    auto t = level->thing_find(id);
    if (! t) {
      continue;
    }
    if (t->is_enchantstone()) {
      t->dead("used");
      found = true;
      break;
    }
  }
  if (! found) {
    err("no enchantstone found");
  }

  return true;
}

void Thing::enchant_randomly(void)
{
  TRACE_AND_INDENT();
  if (! is_enchantable()) {
    return;
  }

  incr_enchant(1);
  while (pcg_random_range(0, 100) < 20 + level->num() * 2) {
    if (get_enchant() >= get_enchant_max()) {
      break;
    }
    incr_enchant(1);
  }
}

int Thing::get_enchantstone_count(void)
{
  TRACE_AND_INDENT();
  int v = 0;
  for (const auto &item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (! t->is_enchantstone()) {
      continue;
    }
    log("Found an enchantstone: %s", t->to_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_enchant_something(void)
{
  TRACE_AND_INDENT();
  for (const auto &item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (t->is_enchantable()) {
      log("Found something we can enchant: %s", t->to_string().c_str());
      return true;
    }
  }
  return false;
}

bool Thing::enchant_random_item(void)
{
  TRACE_AND_INDENT();
  for (const auto &item : monstp->carrying) {
    auto t = level->thing_find(item.id);
    if (! t) {
      continue;
    }
    if (! t->is_enchantable()) {
      continue;
    }
    log("Enchant this randomly: %s", t->to_string().c_str());
    return enchant(t);
  }
  return false;
}
