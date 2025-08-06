//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

float Thing::jump_distance_current(void)
{
  TRACE_NO_INDENT();

  auto d = (float) jump_distance_total();

  if (is_player()) {
    d += 0.5 + ((pcg_random_range(0, 100) / 100.0));
  }

  //
  // Reduce jump distance if tired
  //
  if (stamina() < stamina_max() / 2) {
    d *= 0.8;
  } else if (stamina() < stamina_max() / 4) {
    d *= 0.5;
  } else if (stamina() < stamina_max() / 8) {
    d *= 0.2;
  }

  return d;
}

float Thing::jump_distance_max_get(void)
{
  TRACE_NO_INDENT();
  auto d = ((float) jump_distance_total());
  return d;
}

int Thing::jump_distance_total(void)
{
  int stat = 0;
  int prev = 0;

  stat = jump_distance();
  prev = stat;
  if (stat) {
    dbg3("Jump distance: %d", stat);
  }
  TRACE_AND_INDENT();

  stat += jump_distance_bonus();
  if (stat != prev) {
    prev = stat;
    dbg3("Jump distance: with mod (%s): %d", bonus_to_string(jump_distance_bonus()).c_str(), stat);
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->jump_distance_total();
      if (stat != prev) {
        prev = stat;
        dbg3("Jump distance: with (%s %s): %d", iter->to_short_string().c_str(),
             bonus_to_string(iter->jump_distance_bonus()).c_str(), stat);
      }
    }
  }

  if (maybe_itemsp()) {
    TRACE_NO_INDENT();
    FOR_ALL_CARRYING(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(iter)) {
          continue;
        }
        //
        // Things that are equipped must be equipped to get the benefit.
        // Other items give the benefit by just being carried.
        //
        if (iter->is_auto_equipped()) {
          continue;
        }
        stat += iter->jump_distance_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Jump distance: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->jump_distance_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->jump_distance_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Jump distance: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->jump_distance_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->jump_distance_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Jump distance: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->jump_distance_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->jump_distance_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Jump distance: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->jump_distance_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->jump_distance_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Jump distance: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->jump_distance_bonus()).c_str(), stat);
        }
      }
    }
  }

  return stat;
}

int Thing::jump_distance(void)
{
  TRACE_NO_INDENT();
  return (tp()->jump_distance());
}

////////////////////////////////////////////////////////////////////////////
// jump_distance_bonus
////////////////////////////////////////////////////////////////////////////
int Thing::jump_distance_bonus(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->jump_distance_bonus);
  }
  return 0;
}

int Thing::jump_distance_bonus_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->jump_distance_bonus = v);
  return n;
}

int Thing::jump_distance_bonus_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->jump_distance_bonus -= v);
  return n;
}

int Thing::jump_distance_bonus_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->jump_distance_bonus += v);
  return n;
}

int Thing::jump_distance_bonus_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->jump_distance_bonus--);
  return n;
}

int Thing::jump_distance_bonus_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->jump_distance_bonus++);
  return n;
}
