//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::stat_str_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_str();
  prev = stat;
  if (stat) {
    dbg("Str: %d", stat);
  }

  stat += stat_str_bonus();
  if (stat != prev) {
    prev = stat;
    dbg("Str: with mod (%s): %d", bonus_to_string(stat_str_bonus()).c_str(), stat);
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_str_bonus();
      if (stat != prev) {
        prev = stat;
        dbg3("Str: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_str_total(), stat);
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
        stat += iter->stat_str_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Str: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_str_total(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_str_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Str: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_str_total(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_str_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Str: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_str_total(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->stat_str_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Str: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_str_total(), stat);
        }
      }
    }
  }

  if (stat_str_bonus()) {
    auto enchant = enchant_count_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg("Str: with enchant %d: %d", enchant, stat);
    }
  }

  return stat;
}

int Thing::stat_str(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_str);
  }
  return 0;
}

int Thing::stat_str_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str = v);
  return n;
}

int Thing::stat_str_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str -= v);
  return n;
}

int Thing::stat_str_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str += v);
  return n;
}

int Thing::stat_str_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str--);
  return n;
}

int Thing::stat_str_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stat_str_bonus
////////////////////////////////////////////////////////////////////////////
int Thing::stat_str_bonus(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_str_bonus);
  }
  return 0;
}

int Thing::stat_str_bonus_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_bonus = v);
  return n;
}

int Thing::stat_str_bonus_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_bonus -= v);
  return n;
}

int Thing::stat_str_bonus_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_bonus += v);
  return n;
}

int Thing::stat_str_bonus_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_bonus--);
  return n;
}

int Thing::stat_str_bonus_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_str_bonus++);
  return n;
}
