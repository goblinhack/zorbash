//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::stat_luck_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_luck();
  prev = stat;
  if (stat) {
    dbg3("Luck: %d", stat);
  }

  stat += stat_luck_bonus();
  if (stat != prev) {
    prev = stat;
    dbg3("Luck: with mod (%s): %d", bonus_to_string(stat_luck_bonus()).c_str(), stat);
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_luck_bonus();
      if (stat != prev) {
        prev = stat;
        dbg3("Luck: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_luck_total(), stat);
      }
    }
  }

  if (maybe_itemsp()) {
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
        stat += iter->stat_luck_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Luck: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_luck_total(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_luck_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Luck: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_luck_total(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_luck_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Luck: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_luck_total(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->stat_luck_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Luck: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_luck_total(), stat);
        }
      }
    }
  }

  if (stat_luck_bonus()) {
    auto enchant = enchant_count_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg3("Luck: with enchant %d: %d", enchant, stat);
    }
  }

  return stat;
}

int Thing::stat_luck(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_luck);
  }
  return 0;
}

int Thing::stat_luck_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck = v);
  return n;
}

int Thing::stat_luck_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck -= v);
  return n;
}

int Thing::stat_luck_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck += v);
  return n;
}

int Thing::stat_luck_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck--);
  return n;
}

int Thing::stat_luck_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stat_luck_bonus
////////////////////////////////////////////////////////////////////////////
int Thing::stat_luck_bonus(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_luck_bonus);
  }
  return 0;
}

int Thing::stat_luck_bonus_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck_bonus = v);
  return n;
}

int Thing::stat_luck_bonus_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck_bonus -= v);
  return n;
}

int Thing::stat_luck_bonus_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck_bonus += v);
  return n;
}

int Thing::stat_luck_bonus_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck_bonus--);
  return n;
}

int Thing::stat_luck_bonus_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_luck_bonus++);
  return n;
}
