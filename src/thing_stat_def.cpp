//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

int Thing::get_stat_def_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_stat_def_total();
  }

  int stat_def      = 0;
  int last_stat_def = 0;

  stat_def = get_stat_def();
  dbg("Def: %d", stat_def);

  int dex_total = get_stat_dex_total();
  stat_def += stat_to_bonus(dex_total);
  last_stat_def = stat_def;
  if (stat_def != last_stat_def) {
    last_stat_def = stat_def;
    dbg("Def: with: (dex %d): %d", dex_total, stat_def);
  }

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      stat_def += stat_to_bonus(equip->get_stat_def());

      if (stat_def != last_stat_def) {
        last_stat_def = stat_def;
        dbg("Def: with (%s def %d/%d): %d", equip->to_short_string().c_str(), equip->get_stat_def(),
            stat_to_bonus(equip->get_stat_def()), stat_def);

        //
        // Add enchanted stat_def
        //
        stat_def += equip->get_enchant();
        if (stat_def != last_stat_def) {
          last_stat_def = stat_def;
          dbg("Def: with (enchant %d): %d", equip->get_enchant(), stat_def);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_def += stat_to_bonus(buff->get_stat_def());

        if (stat_def != last_stat_def) {
          last_stat_def = stat_def;
          dbg("Def: with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_def(),
              stat_to_bonus(buff->get_stat_def()), stat_def);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_def += stat_to_bonus(buff->get_stat_def());

        if (stat_def != last_stat_def) {
          last_stat_def = stat_def;
          dbg("Def: with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_def(),
              stat_to_bonus(buff->get_stat_def()), stat_def);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_def += stat_to_bonus(buff->get_stat_def());

        if (stat_def != last_stat_def) {
          last_stat_def = stat_def;
          dbg("Def: with skill (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_def(),
              stat_to_bonus(buff->get_stat_def()), stat_def);
        }
      }
    }
  }

  //
  // Penalties
  //
  stat_def -= get_stuck_count();
  if (stat_def != last_stat_def) {
    last_stat_def = stat_def;
    dbg("Def: with (stuck count %d): %d", get_stuck_count(), stat_def);
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      stat_def /= 2;
      if (stat_def != last_stat_def) {
        last_stat_def = stat_def;
        dbg("Def: with (water penalty): %d", stat_def);
      }
    }
    if (level->is_deep_water(curr_at)) {
      stat_def /= 2;
      if (stat_def != last_stat_def) {
        last_stat_def = stat_def;
        dbg("Def: with (deep water penalty): %d", stat_def);
      }
    }
  }

  dbg("Def: final: %d", stat_def);
  return stat_def;
}

int Thing::get_stat_def(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = get_infop()->stat_def;
  }
  return v;
}

int Thing::set_stat_def(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def = v);
  return (n);
}

int Thing::decr_stat_def(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def -= v);
  if (get_infop()->stat_def < 0) {
    get_infop()->stat_def = 0;
  }
  return (n);
}

int Thing::incr_stat_def(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def += v);
  return (n);
}

int Thing::decr_stat_def(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def--);
  if (get_infop()->stat_def < 0) {
    get_infop()->stat_def = 0;
  }
  return (n);
}

int Thing::incr_stat_def(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_def++);
  return (n);
}
