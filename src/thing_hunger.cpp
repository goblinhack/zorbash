//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::hunger_clock_tick(void)
{
  TRACE_NO_INDENT();

  if (is_lifeless() || is_undead() || is_ethereal()) {
    return;
  }

  if (is_dead || ! hunger_clock_tick_freq()) {
    return;
  }

  //
  // Hunger clock fires rarely
  //
  if (game->tick_current % hunger_clock_tick_freq()) {
    return;
  }

  //
  // Hunger only ticks on con fail
  //
  if (d20roll_under(stat_con_total())) {
    return;
  }

  dbg("Hunger tick");
  TRACE_AND_INDENT();

  auto my_hunger_level = hunger();
  if (my_hunger_level > 1) {
    hunger_decr(1);
    if (my_hunger_level == 1) {
      if (is_player()) {
        msg("You are starving!");
      }
      return;
    }
  } else {
    //
    // starvation is just annoying for players
    //
    return;
  }
}

void Thing::hunger_update(void)
{
  TRACE_NO_INDENT();

  if (is_lifeless() || is_undead() || is_ethereal()) {
    return;
  }

  if (is_dead || ! hunger_clock_tick_freq()) {
    return;
  }

  if (hunger_is_insatiable()) {
    is_starving = true;
    return;
  }

  dbg("Hunger update");
  TRACE_AND_INDENT();

  auto tpp             = tp();
  auto my_hunger_level = hunger();

  int hungry_at = (int) ((double) 100 * ((double) tpp->hunger_is_hungry_at_pct() / 100.0));
  is_hungry     = my_hunger_level <= hungry_at;

  int starving_at = (int) ((double) 100 * ((double) tpp->hunger_is_starving_at_pct() / 100.0));
  is_starving     = my_hunger_level <= starving_at;

  is_satiated = my_hunger_level > 80;
  is_gorged   = my_hunger_level > 110;

  if (is_player()) {
    if (is_gorged || is_satiated) {
      buff_add_if_not_found(tp_find("buff_full"));
      debuff_remove(tp_find("debuff_hungry"));
      debuff_remove(tp_find("debuff_starving"));
    } else if (is_starving) {
      buff_remove(tp_find("buff_full"));
      debuff_remove(tp_find("debuff_hungry"));
      debuff_add_if_not_found(tp_find("debuff_starving"));
    } else if (is_hungry) {
      buff_remove(tp_find("buff_full"));
      debuff_remove(tp_find("debuff_starving"));
      debuff_add_if_not_found(tp_find("debuff_hungry"));
    }
  }
}

int Thing::hunger_is_insatiable(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_insatiable());
}

int Thing::hunger_clock_tick_freq(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_clock_tick_freq());
}

int Thing::hunger_is_hungry_at_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_hungry_at_pct());
}

int Thing::hunger_is_starving_at_pct(void)
{
  TRACE_NO_INDENT();
  return (tp()->hunger_is_starving_at_pct());
}

int Thing::hunger_boost(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return false;
  }

  auto old_hunger = hunger();
  auto new_hunger = old_hunger + v;
  auto max_hunger = THING_HUNGER_MAX;

  if (old_hunger >= max_hunger) {
    dbg("Hunger boost not possible, maxxed out already");
    return false;
  }

  new_hunger = std::min(new_hunger, max_hunger);
  hunger_set(new_hunger);

  if (new_hunger >= max_hunger) {
    dbg("Hunger boost not possible, maxxed at %d", new_hunger);
  } else {
    dbg("Hunger boost by %d from %d to %d", v, old_hunger, new_hunger);
  }
  return new_hunger - old_hunger;
}

bool Thing::hunger_boost_would_occur(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return false;
  }

  auto old_hunger = hunger();
  auto max_hunger = THING_HUNGER_MAX;

  if (old_hunger >= max_hunger) {
    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////////////
// hunger
////////////////////////////////////////////////////////////////////////////
int Thing::hunger(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->hunger;
  }
  return v;
}

int Thing::hunger_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger = v);
  return n;
}

int Thing::hunger_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger -= v);
  return n;
}

int Thing::hunger_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger += v);
  return n;
}

int Thing::hunger_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger--);
  return n;
}

int Thing::hunger_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->hunger++);
  return n;
}
