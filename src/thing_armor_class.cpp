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

int Thing::get_armor_class_total(void)
{
  TRACE_NO_INDENT();

  auto owner = get_top_owner();
  if (owner) {
    return owner->get_armor_class_total();
  }

  int armor_class      = 0;
  int last_armor_class = 0;

  armor_class = get_armor_class();
  dbg("Armor class: %d", armor_class);

  armor_class += stat_to_bonus(get_stat_dexterity());
  armor_class += get_attack_bonus();
  last_armor_class = armor_class;
  if (armor_class != last_armor_class) {
    last_armor_class = armor_class;
    dbg("Armor class with: (dex %d/%d): %d", get_stat_dexterity(), stat_to_bonus(get_stat_dexterity()), armor_class);
  }

  FOR_ALL_EQUIP(e)
  {
    auto equip = get_equip(e);
    if (equip) {
      armor_class += stat_to_bonus(equip->get_stat_dexterity());
      armor_class += equip->get_attack_bonus();

      if (armor_class != last_armor_class) {
        last_armor_class = armor_class;
        dbg("Armor class with (%s dex %d/%d): %d", equip->to_short_string().c_str(), equip->get_stat_dexterity(),
            stat_to_bonus(equip->get_stat_dexterity()), armor_class);

        //
        // Add enchanted dexterity
        //
        armor_class += equip->get_enchant();
        if (armor_class != last_armor_class) {
          last_armor_class = armor_class;
          dbg("Armor class with (enchant %d): %d", equip->get_enchant(), armor_class);
        }
      }
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_BUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        armor_class += stat_to_bonus(buff->get_stat_dexterity());
        armor_class += buff->get_attack_bonus();

        if (armor_class != last_armor_class) {
          last_armor_class = armor_class;
          dbg("Armor class with buff (%s dex %d/%d): %d", buff->to_short_string().c_str(), buff->get_stat_dexterity(),
              stat_to_bonus(buff->get_stat_dexterity()), armor_class);
        }
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto buff = level->thing_find(id);
      if (buff) {
        armor_class += stat_to_bonus(buff->get_stat_dexterity());
        armor_class += buff->get_attack_bonus();

        if (armor_class != last_armor_class) {
          last_armor_class = armor_class;
          dbg("Armor class with debuff (%s dex %d/%d): %d", buff->to_short_string().c_str(),
              buff->get_stat_dexterity(), stat_to_bonus(buff->get_stat_dexterity()), armor_class);
        }
      }
    }
  }

  armor_class -= get_stuck_count();
  if (armor_class != last_armor_class) {
    last_armor_class = armor_class;
    dbg("Armor class with (stuck count %d): %d", get_stuck_count(), armor_class);
  }

  //
  // Terrain penalties
  //
  if (! is_aquatic() && ! buff_find_is_aquatic()) {
    if (level->is_water(curr_at)) {
      armor_class /= 2;
      if (armor_class != last_armor_class) {
        last_armor_class = armor_class;
        dbg("Armor class with (water penalty): %d", armor_class);
      }
    }
    if (level->is_deep_water(curr_at)) {
      armor_class /= 2;
      if (armor_class != last_armor_class) {
        last_armor_class = armor_class;
        dbg("Armor class with (deep water penalty): %d", armor_class);
      }
    }
  }

  return armor_class;
}

int Thing::get_armor_class(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = get_infop()->armor_class;
  }
  return v;
}

int Thing::set_armor_class(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->armor_class = v);
  return (n);
}

int Thing::decr_armor_class(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->armor_class -= v);
  if (get_infop()->armor_class < 0) {
    get_infop()->armor_class = 0;
  }
  return (n);
}

int Thing::incr_armor_class(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->armor_class += v);
  return (n);
}

int Thing::decr_armor_class(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->armor_class--);
  if (get_infop()->armor_class < 0) {
    get_infop()->armor_class = 0;
  }
  return (n);
}

int Thing::incr_armor_class(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (get_infop()->armor_class++);
  return (n);
}
