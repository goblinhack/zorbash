//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::noise(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->noise);
  }
  return 0;
}

int Thing::noise_total(void)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return 0;
  }

  auto decibels = noise();
  // con("NOISE %d", decibels);

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      decibels += iter->noise();
      // iter->con("NOISE %d", decibels);
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
        decibels += iter->noise();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        decibels += iter->noise();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        decibels += iter->noise();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        decibels += iter->noise();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        decibels += iter->noise();
        // iter->con("NOISE %d", decibels);
      }
    }
  }
  // con("NOISE %d", decibels);

  if (is_player() || is_monst()) {
    decibels -= stat_dex_bonus() * 10;

    if (level->is_able_to_dampen_footsteps(curr_at)) {
      decibels /= 2;
    }

    if (level->is_able_to_amplify_footsteps(curr_at)) {
      decibels += 10;
    }

    //
    // If creeping along wall edges then dampen noise. Any of the following
    // will dampen.
    //
    uint64_t which = (level->is_obs_wall_or_door(curr_at.x - 1, curr_at.y - 1) ? 0xf00000000LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x - 0, curr_at.y - 1) ? 0x0f0000000LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x + 1, curr_at.y - 1) ? 0x00f000000LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x - 1, curr_at.y - 0) ? 0x000f00000LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x - 0, curr_at.y - 0) ? 0x0000f0000LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x + 1, curr_at.y - 0) ? 0x00000f000LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x - 1, curr_at.y + 1) ? 0x000000f00LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x - 0, curr_at.y + 1) ? 0x0000000f0LLU : 0)
                   | (level->is_obs_wall_or_door(curr_at.x + 1, curr_at.y + 1) ? 0x00000000fLLU : 0);
    switch (which) {
        // x.. ..x xxx ...
        // x@. .@x .@. .@.
        // x.. ..x ... xxx
      case 0xf00f00f00LLU :
      case 0x00f00f00fLLU :
      case 0xfff000000LLU :
      case 0x000000fffLLU :
        // xxx xxx x.. ..x
        // x@. .@x x@. .@x
        // x.. ..x xxx xxx
      case 0xffff00f00LLU :
      case 0xfff00f00fLLU :
      case 0xf00f00fffLLU :
      case 0x00f00ffffLLU :
        // xxx xxx x.x x.x
        // x@. .@x x@. .@x
        // x.x x.x xxx xxx
      case 0xffff00f0fLLU :
      case 0xfff00ff0fLLU :
      case 0xf0ff00fffLLU :
      case 0xf0f00ffffLLU :
        // xxx xxx x.x xxx
        // x@. .@x x@x x@x
        // xxx xxx xxx x.x
      case 0xffff00fffLLU :
      case 0xfff00ffffLLU :
      case 0xf0ff0ffffLLU :
      case 0xffff0ff0fLLU :
        // xx. .xx ... ...
        // x@. .@x x@. .@x
        // ... ... xx. .xx
      case 0xff0f00000LLU :
      case 0x0ff00f000LLU :
      case 0x000f00ff0LLU :
      case 0x00000f0ffLLU : decibels /= 2; break;
    }
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

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      decibels += iter->noise_additional_on_jump_end();
      // iter->con("NOISE %d", decibels);
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
        decibels += iter->noise_additional_on_jump_end();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        decibels += iter->noise_additional_on_jump_end();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        decibels += iter->noise_additional_on_jump_end();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        decibels += iter->noise_additional_on_jump_end();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        decibels += iter->noise_additional_on_jump_end();
        // iter->con("NOISE %d", decibels);
      }
    }
  }

  if (is_player() || is_monst()) {
    decibels -= stat_dex_bonus() * 10;
  }

  if (level->is_able_to_dampen_footsteps(curr_at)) {
    decibels /= 2;
  }
  if (level->is_able_to_amplify_footsteps(curr_at)) {
    decibels *= 2;
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

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      decibels += iter->noise_additional_on_teleporting();
      // iter->con("NOISE %d", decibels);
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
        decibels += iter->noise_additional_on_teleporting();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        decibels += iter->noise_additional_on_teleporting();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        decibels += iter->noise_additional_on_teleporting();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        decibels += iter->noise_additional_on_teleporting();
        // iter->con("NOISE %d", decibels);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS_FOR(this, id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        decibels += iter->noise_additional_on_teleporting();
        // iter->con("NOISE %d", decibels);
      }
    }
  }

  if (is_player() || is_monst()) {
    decibels -= stat_dex_bonus() * 10;
  }

  if (level->is_able_to_dampen_footsteps(curr_at)) {
    decibels /= 2;
  }
  if (level->is_able_to_amplify_footsteps(curr_at)) {
    decibels *= 2;
  }

  return decibels;
}

int Thing::noise_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->noise = v);
  return n;
}

int Thing::noise_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->noise -= v);
  return n;
}

int Thing::noise_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->noise += v);
  return n;
}

int Thing::noise_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->noise--);
  return n;
}

int Thing::noise_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->noise++);
  return n;
}

uint8_t Level::is_able_to_dampen_footsteps(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_able_to_dampen_footsteps, p.x, p.y));
}

uint8_t Level::is_able_to_dampen_footsteps(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_able_to_dampen_footsteps, x, y));
}

void Level::is_able_to_dampen_footsteps_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_able_to_dampen_footsteps, x, y, (uint8_t) 1);
}

void Level::is_able_to_dampen_footsteps_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_able_to_dampen_footsteps, x, y, (uint8_t) 1);
}

uint8_t Level::is_able_to_amplify_footsteps(const point p)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(p.x, p.y))) {
    return false;
  }
  return (get(_is_able_to_amplify_footsteps, p.x, p.y));
}

uint8_t Level::is_able_to_amplify_footsteps(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return false;
  }
  return (get(_is_able_to_amplify_footsteps, x, y));
}

void Level::is_able_to_amplify_footsteps_set(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  incr(_is_able_to_amplify_footsteps, x, y, (uint8_t) 1);
}

void Level::is_able_to_amplify_footsteps_unset(const int x, const int y)
{
  TRACE_NO_INDENT();
  if (unlikely(is_oob(x, y))) {
    return;
  }
  is_map_changed = true;
  decr(_is_able_to_amplify_footsteps, x, y, (uint8_t) 1);
}

int Thing::is_able_to_dampen_footsteps(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_dampen_footsteps());
}

int Thing::is_able_to_amplify_footsteps(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_amplify_footsteps());
}

int Thing::noise_on_moving(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_moving());
}

int Thing::noise_additional_on_teleporting(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_additional_on_teleporting());
}

int Thing::noise_additional_on_jump_end(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_additional_on_jump_end());
}

int Thing::noise_on_born(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_born());
}

int Thing::noise_on_open_or_close(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_open_or_close());
}

int Thing::noise_on_hit_and_now_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_hit_and_now_dead());
}

int Thing::noise_on_hit_and_still_alive(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_hit_and_still_alive());
}

int Thing::noise_decibels_hearing(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_decibels_hearing());
}

int Thing::noise_on_dropping(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_on_dropping());
}

int Thing::noise_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->noise_blocker());
}
