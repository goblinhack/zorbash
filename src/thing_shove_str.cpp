//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::shove_strength_total(void)
{
  int stat = 0;
  int prev = 0;

  stat = shove_strength();
  prev = stat;
  if (stat) {
    dbg3("Shove strength: %d", stat);
  }
  TRACE_AND_INDENT();

  stat += shove_bonus();
  if (stat != prev) {
    prev = stat;
    dbg3("Shove strength: with mod (%s): %d", bonus_to_string(shove_bonus()).c_str(), stat);
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->shove_strength_total();
      if (stat != prev) {
        prev = stat;
        dbg3("Shove strength: with (%s %s): %d", iter->to_short_string().c_str(),
             bonus_to_string(iter->shove_bonus()).c_str(), stat);
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
        stat += iter->shove_strength_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Shove strength: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->shove_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->shove_strength_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Shove strength: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->shove_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->shove_strength_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Shove strength: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->shove_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->shove_strength_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Shove strength: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->shove_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->shove_strength_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Shove strength: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->shove_bonus()).c_str(), stat);
        }
      }
    }
  }

  return stat;
}

int Thing::shove_strength(void)
{
  TRACE_NO_INDENT();
  return (tp()->shove_strength());
}

////////////////////////////////////////////////////////////////////////////
// shove_bonus
////////////////////////////////////////////////////////////////////////////
int Thing::shove_bonus(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->shove_bonus);
  }
  return 0;
}

int Thing::shove_bonus_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->shove_bonus = v);
  return n;
}

int Thing::shove_bonus_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->shove_bonus -= v);
  return n;
}

int Thing::shove_bonus_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->shove_bonus += v);
  return n;
}

int Thing::shove_bonus_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->shove_bonus--);
  return n;
}

int Thing::shove_bonus_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->shove_bonus++);
  return n;
}
