//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::stat_dex_total(void)
{
  TRACE_AND_INDENT();

  int stat = 0;
  int prev = 0;

  stat = stat_dex();
  prev = stat;
  if (stat) {
    dbg3("Dex: %d", stat);
  }

  stat += stat_dex_mod();
  if (stat != prev) {
    prev = stat;
    dbg3("Dex: with mod (%s): %d", modifier_to_string(stat_dex_mod()).c_str(), stat);
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      stat += iter->stat_dex_total();
      if (stat != prev) {
        prev = stat;
        dbg3("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
             modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
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
        stat += iter->stat_dex_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_dex_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_dex_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        stat += iter->stat_dex_total();
        if (stat != prev) {
          prev = stat;
          dbg3("Dex: with (%s %s): %d", iter->to_short_string().c_str(),
               modifier_to_string(iter->stat_dex_mod()).c_str(), stat);
        }
      }
    }
  }

  if (stat) {
    auto enchant = enchant_get();
    stat += enchant;
    if (stat != prev) {
      prev = stat;
      dbg3("Dex: with enchant %d: %d", enchant, stat);
    }
  }

  return stat;
}

int Thing::stat_dex(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stat_dex);
  } else {
    return 0;
  }
}

int Thing::stat_dex_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->stat_dex = v);
  return n;
}

int Thing::stat_dex_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->stat_dex -= v);
  return n;
}

int Thing::stat_dex_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->stat_dex += v);
  return n;
}

int Thing::stat_dex_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->stat_dex--);
  return n;
}

int Thing::stat_dex_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->stat_dex++);
  return n;
}
