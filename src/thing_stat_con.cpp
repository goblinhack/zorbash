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

int Thing::get_stat_con_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_stat_con();
  }

  int stat_con = 0;
  int last_con = 0;

  stat_con += get_stat_con();
  last_con = stat_con;
  dbg("Constitution: (%d/%d): %d", get_stat_con(), stat_to_bonus(get_stat_con()), stat_con);

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      stat_con += stat_to_bonus(equip->get_stat_con());

      if (stat_con != last_con) {
        last_con = stat_con;
        dbg("Constitution with (%s stat_con %d/%d): %d", equip->to_short_string().c_str(), equip->get_stat_con(),
            stat_to_bonus(equip->get_stat_con()), stat_con);

        //
        // Add enchanted stat_con
        //
        stat_con += equip->get_enchant();
        if (stat_con != last_con) {
          last_con = stat_con;
          dbg("Constitution with (enchant %d): %d", equip->get_enchant(), stat_con);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_con += stat_to_bonus(buff->get_stat_con());

        if (stat_con != last_con) {
          last_con = stat_con;
          dbg("Constitution with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_con(),
              stat_to_bonus(buff->get_stat_con()), stat_con);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_con += stat_to_bonus(buff->get_stat_con());

        if (stat_con != last_con) {
          last_con = stat_con;
          dbg("Constitution with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_con(),
              stat_to_bonus(buff->get_stat_con()), stat_con);
        }
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        stat_con += stat_to_bonus(buff->get_stat_con());

        if (stat_con != last_con) {
          last_con = stat_con;
          dbg("Constitution with skill (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_con(),
              stat_to_bonus(buff->get_stat_con()), stat_con);
        }
      }
    }
  }

  return stat_con;
}

int Thing::get_stat_con(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (get_infop()->stat_con);
  } else {
    return 0;
  }
}

int Thing::set_stat_con(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_con = v);
  return (n);
}

int Thing::decr_stat_con(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_con -= v);
  return (n);
}

int Thing::incr_stat_con(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_con += v);
  return (n);
}

int Thing::decr_stat_con(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_con--);
  return (n);
}

int Thing::incr_stat_con(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->stat_con++);
  return (n);
}
