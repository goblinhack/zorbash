//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_english.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
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

void Thing::enchant_common(Thingp what)
{
  if (is_player()) {
    if (what->is_enchantable_as_a_group()) {
      msg("You enchant all of %s.", pluralise(what->text_the()).c_str());
    } else {
      msg("You enchant %s.", what->text_the().c_str());
    }
  }
}

bool Thing::enchant_with_stone(Thingp what)
{
  enchant_common(what);
  TRACE_AND_INDENT();

  //
  // Enchant one dart, you enchant them all
  //
  if (what->is_enchantable_as_a_group()) {
    for (const auto t : carried_and_equipped_item_vector()) {
      if (t->tp() == what->tp()) {
        t->on_enchant();
        t->enchant_count_incr(1);
        t->damaged_count_set(0);
      }
    }
  } else {
    //
    // Single item enchant.
    //
    what->on_enchant();
    what->enchant_count_incr(1);
    what->damaged_count_set(0);
  }

  if (is_player()) {
    sound_play("powerup");
  }

  //
  // Drop a enchantstone
  //
  auto found = false;
  for (const auto enchantstone : carried_item_only_vector()) {
    if (enchantstone->is_enchantstone()) {
      if (enchantstone->charge_count()) {
        enchantstone->charge_count_decr();
      }
      if (! enchantstone->charge_count()) {
        enchantstone->is_drained = true;
        enchantstone->dead("drained and used");
      }
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
  enchant_common(what);
  TRACE_AND_INDENT();

  //
  // Enchant one dart, you enchant them all
  //
  if (what->is_enchantable_as_a_group()) {
    for (const auto t : carried_and_equipped_item_vector()) {
      if (t->tp() == what->tp()) {
        t->on_enchant();
        t->enchant_count_incr(1);
        t->damaged_count_set(0);
      }
    }
  } else {
    //
    // Single item enchant.
    //
    what->on_enchant();
    what->enchant_count_incr(1);
    what->damaged_count_set(0);
  }

  if (is_player()) {
    sound_play("powerup");
  }

  return true;
}

void Thing::enchant_randomly(void)
{
  TRACE_NO_INDENT();

  if (! is_enchantable()) {
    return;
  }

  enchant_count_incr(1);
  while (pcg_random_range(0, 100) < 20 + level->num() * 2) {
    if (enchant_count_get() >= enchant_max_current_get()) {
      break;
    }
    enchant_count_incr(1);
  }
  damaged_count_set(0);
}

int Thing::enchantstone_count(void)
{
  TRACE_NO_INDENT();

  int v = 0;
  for (const auto t : carried_item_only_vector()) {
    if (! t->is_enchantstone()) {
      continue;
    }
    dbg("Found an enchantstone: %s", t->to_short_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_enchant_something(void)
{
  TRACE_NO_INDENT();
  for (const auto t : carried_and_equipped_item_vector()) {
    if (t->is_enchantable()) {
      dbg("Found something we can enchant: %s", t->to_short_string().c_str());
      return true;
    }
  }
  return false;
}

bool Thing::enchant_random_item_with_stone(void)
{
  TRACE_NO_INDENT();
  std::vector< Thingp > cands;
  for (const auto t : carried_and_equipped_item_vector()) {
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

int Thing::enchant_count_get(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->enchant;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->enchant_count_get();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->enchant_count_get();
    }
  }
  return v;
}

int Thing::enchant_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant = v);
  return n;
}

int Thing::enchant_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant -= v);
  if (infop()->enchant < 0) {
    infop()->enchant = 0;
  }
  return n;
}

int Thing::enchant_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant += v);
  return n;
}

int Thing::enchant_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant--);
  if (infop()->enchant < 0) {
    infop()->enchant = 0;
  }
  return n;
}

int Thing::enchant_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->enchant++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// enchant_max
////////////////////////////////////////////////////////////////////////////
int Thing::enchant_max_current_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->enchant_max);
  }
  return 0;
}

int Thing::enchant_max_current_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->enchant_max = v);
  return n;
}

int Thing::enchant_max_current_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->enchant_max -= v);
  return n;
}

int Thing::enchant_max_current_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->enchant_max += v);
  return n;
}

int Thing::enchant_max_current_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->enchant_max--);
  return n;
}

int Thing::enchant_max_current_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->enchant_max++);
  return n;
}

int Thing::enchant_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->enchant_max());
}
