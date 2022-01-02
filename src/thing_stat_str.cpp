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

int Thing::get_stat_str_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_stat_str();
  }

  int stat_str      = 0;
  int last_strength = 0;

  stat_str      = get_stat_str();
  last_strength = stat_str;
  dbg("Str: (%d/%d): %d", get_stat_str(), stat_to_bonus(get_stat_str()), stat_str);

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      stat_str += stat_to_bonus(equip->get_stat_str());

      if (stat_str != last_strength) {
        last_strength = stat_str;
        dbg("Str: with (%s str %d/%d): %d", equip->to_short_string().c_str(), equip->get_stat_str(),
            stat_to_bonus(equip->get_stat_str()), stat_str);

        //
        // Add enchanted stat_str
        //
        stat_str += equip->get_enchant();
        if (stat_str != last_strength) {
          last_strength = stat_str;
          dbg("Str: with (enchant %d): %d", equip->get_enchant(), stat_str);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_str += stat_to_bonus(buff->get_stat_str());

        if (stat_str != last_strength) {
          last_strength = stat_str;
          dbg("Str: with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_str(),
              stat_to_bonus(buff->get_stat_str()), stat_str);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_str += stat_to_bonus(buff->get_stat_str());

        if (stat_str != last_strength) {
          last_strength = stat_str;
          dbg("Str: with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_str(),
              stat_to_bonus(buff->get_stat_str()), stat_str);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_str += stat_to_bonus(buff->get_stat_str());

        if (stat_str != last_strength) {
          last_strength = stat_str;
          dbg("Str: with skill (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_str(),
              stat_to_bonus(buff->get_stat_str()), stat_str);
        }
      }
    }
  }

  return stat_str;
}

int Thing::get_stat_str(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->stat_str);
  } else {
    return 0;
  }
}

int Thing::set_stat_str(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_str = v);
  return (n);
}

int Thing::decr_stat_str(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_str -= v);
  return (n);
}

int Thing::incr_stat_str(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_str += v);
  return (n);
}

int Thing::decr_stat_str(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_str--);
  return (n);
}

int Thing::incr_stat_str(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_str++);
  return (n);
}
