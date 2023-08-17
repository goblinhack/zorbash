//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::stat_psi_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_psi();
  prev = stat;
  if (stat) {
    dbg3("Psi: %d", stat);
  }

  stat += stat_psi_bonus();
  if (stat != prev) {
    prev = stat;
    dbg3("Psi: with mod (%s): %d", bonus_to_string(stat_psi_bonus()).c_str(), stat);
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_psi_bonus();
      if (stat != prev) {
        prev = stat;
        dbg3("Psi: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_psi_total(), stat);
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
        stat += iter->stat_psi_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Psi: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_psi_total(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_psi_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Psi: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_psi_total(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_psi_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Psi: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_psi_total(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->stat_psi_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Psi: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_psi_total(), stat);
        }
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        stat += iter->stat_psi_bonus();
        if (stat != prev) {
          prev = stat;
          dbg3("Psi: with (%s %d): %d", iter->to_short_string().c_str(), iter->stat_psi_total(), stat);
        }
      }
    }
  }

  if (stat_psi_bonus()) {
    auto enchant = enchant_count_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg3("Psi: with enchant %d: %d", enchant, stat);
    }
  }

  return stat;
}

int Thing::stat_psi(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_psi);
  }
  return 0;
}

int Thing::stat_psi_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi = v);
  return n;
}

int Thing::stat_psi_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi -= v);
  return n;
}

int Thing::stat_psi_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi += v);
  return n;
}

int Thing::stat_psi_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi--);
  return n;
}

int Thing::stat_psi_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stat_psi_bonus
////////////////////////////////////////////////////////////////////////////
int Thing::stat_psi_bonus(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_psi_bonus);
  }
  return 0;
}

int Thing::stat_psi_bonus_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi_bonus = v);
  return n;
}

int Thing::stat_psi_bonus_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi_bonus -= v);
  return n;
}

int Thing::stat_psi_bonus_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi_bonus += v);
  return n;
}

int Thing::stat_psi_bonus_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi_bonus--);
  return n;
}

int Thing::stat_psi_bonus_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stat_psi_bonus++);
  return n;
}
