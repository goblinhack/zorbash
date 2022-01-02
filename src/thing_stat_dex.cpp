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

int Thing::get_stat_dex_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_stat_dex();
  }

  int stat_dex = 0;
  int last_dex = 0;

  stat_dex += get_stat_dex();
  last_dex = stat_dex;
  dbg("Dex: (%d/%d): %d", get_stat_dex(), stat_to_bonus(get_stat_dex()), stat_dex);

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      stat_dex += stat_to_bonus(equip->get_stat_dex());

      if (stat_dex != last_dex) {
        last_dex = stat_dex;
        dbg("Dex: with (%s stat_dex %d/%d): %d", equip->to_short_string().c_str(), equip->get_stat_dex(),
            stat_to_bonus(equip->get_stat_dex()), stat_dex);

        //
        // Add enchanted stat_dex
        //
        stat_dex += equip->get_enchant();
        if (stat_dex != last_dex) {
          last_dex = stat_dex;
          dbg("Dex: with (enchant %d): %d", equip->get_enchant(), stat_dex);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_dex += stat_to_bonus(buff->get_stat_dex());

        if (stat_dex != last_dex) {
          last_dex = stat_dex;
          dbg("Dex: with buff (%s stat_dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_dex(),
              stat_to_bonus(buff->get_stat_dex()), stat_dex);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_dex += stat_to_bonus(buff->get_stat_dex());

        if (stat_dex != last_dex) {
          last_dex = stat_dex;
          dbg("Dex: with debuff (%s stat_dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_dex(),
              stat_to_bonus(buff->get_stat_dex()), stat_dex);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_dex += stat_to_bonus(buff->get_stat_dex());

        if (stat_dex != last_dex) {
          last_dex = stat_dex;
          dbg("Dex: with skill (%s stat_dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_dex(),
              stat_to_bonus(buff->get_stat_dex()), stat_dex);
        }
      }
    }
  }

  return stat_dex;
}

int Thing::get_stat_dex(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->stat_dex);
  } else {
    return 0;
  }
}

int Thing::set_stat_dex(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_dex = v);
  return (n);
}

int Thing::decr_stat_dex(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_dex -= v);
  return (n);
}

int Thing::incr_stat_dex(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_dex += v);
  return (n);
}

int Thing::decr_stat_dex(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_dex--);
  return (n);
}

int Thing::incr_stat_dex(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_dex++);
  return (n);
}
