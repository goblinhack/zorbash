//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::move_speed_total(void)
{
  TRACE_NO_INDENT();

  int stat = 0;
  int prev = 0;

  stat = move_speed();
  prev = stat;

  stat += move_speed_bonus();
  if (stat != prev) {
    prev = stat;
    dbg2("Move speed: with mod (%s): %d", bonus_to_string(move_speed_bonus()).c_str(), stat);
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->move_speed_total();
      if (stat != prev) {
        prev = stat;
        dbg2("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
             bonus_to_string(iter->move_speed_bonus()).c_str(), stat);
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
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->move_speed_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->move_speed_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->move_speed_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->move_speed_bonus()).c_str(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->move_speed_total();
        if (stat != prev) {
          prev = stat;
          dbg2("Move speed: with (%s %s): %d", iter->to_short_string().c_str(),
               bonus_to_string(iter->move_speed_bonus()).c_str(), stat);
        }
      }
    }
  }

  //
  // Slow the thing down if it's not native to deep water.
  //
  if (is_monst() || is_player()) {
    if (! is_swimmer() && ! is_floating_currently() && ! is_flying() && ! is_ethereal()) {
      if (! environ_likes_deep_water()) {
        if (level->is_deep_water(curr_at)) {
          stat /= 4;
          if (stat != prev) {
            prev = stat;
            dbg2("Move speed: with deep water penalty: %d", stat);
          }
        }
      } else if (! environ_likes_shallow_water()) {
        if (level->is_water(curr_at)) {
          stat /= 2;
          if (stat != prev) {
            prev = stat;
            dbg2("Move speed: with water penalty: %d", stat);
          }
        }
      }
    }
  }

  return stat;
}

int Thing::move_speed(void)
{
  TRACE_NO_INDENT();
  return (tp()->move_speed());
}

////////////////////////////////////////////////////////////////////////////
// move_speed_bonus
////////////////////////////////////////////////////////////////////////////
int Thing::move_speed_bonus(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->move_speed_bonus);
  }
  return 0;
}

int Thing::move_speed_bonus_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_speed_bonus = v);
  return n;
}

int Thing::move_speed_bonus_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_speed_bonus -= v);
  return n;
}

int Thing::move_speed_bonus_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_speed_bonus += v);
  return n;
}

int Thing::move_speed_bonus_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_speed_bonus--);
  return n;
}

int Thing::move_speed_bonus_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_speed_bonus++);
  return n;
}

int Thing::move_speed_curr(void)
{
  TRACE_NO_INDENT();

  auto n = infop();

  if (! n->move_speed_curr) {
    n->move_speed_curr = move_speed_total();
  }

  return n->move_speed_curr;
}

void Thing::move_speed_curr_set(int speed)
{
  TRACE_NO_INDENT();
  auto n             = infop();
  n->move_speed_curr = speed;
}
