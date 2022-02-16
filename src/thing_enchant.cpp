//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

//
// Python callback upon being enchant
//
void Thing::on_enchant(void)
{
  TRACE_NO_INDENT();

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

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_enchant call [%s] expected mod:function, got %d elems", on_enchant.c_str(), (int) on_enchant.size());
  }
}

bool Thing::enchant_with_stone(Thingp what)
{
  msg("You enchant %s.", what->text_the().c_str());

  dbg("enchant %s", what->text_the().c_str());
  TRACE_AND_INDENT();

  what->on_enchant();
  what->enchant_incr(1);

  //
  // Drop an enchantstone
  //
  auto found = false;
  for (const auto t : item_vector()) {
    if (t->is_enchantstone()) {
      t->dead("used");
      found = true;
      break;
    }
  }
  if (! found) {
    //
    // Not really an error if the enchant is automatic
    //
    dbg("no enchantstone found");
  }

  return true;
}

bool Thing::enchant_without_stone(Thingp what)
{
  msg("You enchant %s.", what->text_the().c_str());

  dbg("Enchant %s", what->text_the().c_str());
  TRACE_AND_INDENT();

  what->on_enchant();
  what->enchant_incr(1);

  return true;
}

void Thing::enchant_randomly(void)
{
  TRACE_NO_INDENT();

  if (! is_enchantable()) {
    return;
  }

  enchant_incr(1);
  while (pcg_random_range(0, 100) < 20 + level->num() * 2) {
    if (enchant_get() >= enchant_max_current_get()) {
      break;
    }
    enchant_incr(1);
  }
}

int Thing::enchantstone_count(void)
{
  TRACE_NO_INDENT();

  int v = 0;
  for (const auto t : item_vector()) {
    if (! t->is_enchantstone()) {
      continue;
    }
    dbg("Found an enchantstone: %s", t->to_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_enchant_something(void)
{
  TRACE_NO_INDENT();
  for (const auto t : item_vector()) {
    if (t->is_enchantable()) {
      dbg("Found something we can enchant: %s", t->to_string().c_str());
      return true;
    }
  }
  return false;
}

bool Thing::enchant_random_item_with_stone(void)
{
  TRACE_NO_INDENT();
  std::vector< Thingp > cands;
  for (const auto t : item_vector()) {
    if (! t->is_enchantable()) {
      continue;
    }
    cands.push_back(t);
  }

  if (cands.empty()) {
    return false;
  }

  auto chosen = cands[ pcg_random_range(0, cands.size()) ];
  dbg("Enchant this randomly: %s", chosen->to_string().c_str());
  return enchant_with_stone(chosen);
}
