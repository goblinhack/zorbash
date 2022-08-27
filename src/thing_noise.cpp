//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::noise(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->noise);
  } else {
    return 0;
  }
}

int Thing::noise_total(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto decibels = noise();
  // con("NOISE %d", decibels);

  FOR_ALL_EQUIP(e)
  {
    auto it = equip_get(e);
    if (it) {
      decibels += it->noise();
      // it->con("NOISE %d", decibels);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto it = level->thing_find(id);
      if (it) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(it)) {
          continue;
        }
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise();
        // it->con("NOISE %d", decibels);
      }
    }
  }
  // con("NOISE %d", decibels);

  if (is_player() || is_monst()) {
    decibels -= stat_dex_mod() * 10;
  }
  // con("NOISE %d", decibels);

  return decibels;
}

int Thing::noise_on_jumping(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto decibels = noise_total();
  // con("NOISE %d", decibels);

  FOR_ALL_EQUIP(e)
  {
    auto it = equip_get(e);
    if (it) {
      decibels += it->noise_additional_on_jump_end();
      // it->con("NOISE %d", decibels);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto it = level->thing_find(id);
      if (it) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(it)) {
          continue;
        }
        decibels += it->noise_additional_on_jump_end();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise_additional_on_jump_end();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise_additional_on_jump_end();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise_additional_on_jump_end();
        // it->con("NOISE %d", decibels);
      }
    }
  }

  if (is_player() || is_monst()) {
    decibels -= stat_dex_mod() * 10;
  }

  return decibels;
}

int Thing::noise_on_teleporting(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto decibels = noise_total();
  // con("NOISE %d", decibels);

  FOR_ALL_EQUIP(e)
  {
    auto it = equip_get(e);
    if (it) {
      decibels += it->noise_additional_on_teleporting();
      // it->con("NOISE %d", decibels);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto it = level->thing_find(id);
      if (it) {
        //
        // Don't count boots for example twice
        //
        if (is_equipped(it)) {
          continue;
        }
        decibels += it->noise_additional_on_teleporting();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise_additional_on_teleporting();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise_additional_on_teleporting();
        // it->con("NOISE %d", decibels);
      }
    }

    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto it = level->thing_find(id);
      if (it) {
        decibels += it->noise_additional_on_teleporting();
        // it->con("NOISE %d", decibels);
      }
    }
  }

  if (is_player() || is_monst()) {
    decibels -= stat_dex_mod() * 10;
  }

  return decibels;
}

int Thing::noise_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->noise = v);
  return n;
}

int Thing::noise_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->noise -= v);
  return n;
}

int Thing::noise_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->noise += v);
  return n;
}

int Thing::noise_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->noise--);
  return n;
}

int Thing::noise_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_remake_rightbar = true;
    LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
  }
  new_infop();
  auto n = (infop()->noise++);
  return n;
}
