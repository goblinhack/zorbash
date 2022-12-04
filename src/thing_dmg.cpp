//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::attacks_per_round(void)
{
  TRACE_NO_INDENT();
  return (std::max(1, tp()->attacks_per_round()));
}

int Thing::weapon_dmg(void)
{
  TRACE_NO_INDENT();
  return (tp()->weapon_dmg());
}

int Thing::dmg_current(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->dmg_current;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->dmg_current();
  }
  return v;
}

int Thing::dmg_current_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->dmg_current = v);
  return n;
}

int Thing::dmg_current_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->dmg_current -= v);
  return n;
}

int Thing::dmg_current_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->dmg_current += v);
  return n;
}

int Thing::dmg_current_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->dmg_current--);
  return n;
}

int Thing::dmg_current_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->dmg_current++);
  return n;
}
int Thing::dmg_max(void)
{
  TRACE_NO_INDENT();
  auto max_dmg = dmg_nat_att_dice().max_roll();
  max_dmg      = std::max(max_dmg, dmg_digest_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_melee_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_poison_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_drown_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_bite_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_claw_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_cold_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_fire_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_crush_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_lightning_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_energy_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_negation_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_acid_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_water_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_digest_dice().max_roll());
  max_dmg      = std::max(max_dmg, dmg_necrosis_dice().max_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    max_dmg = std::max(max_dmg, curr_weapon->dmg_max());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return max_dmg + enchant_count_get();
}

int Thing::dmg_min(void)
{
  TRACE_NO_INDENT();
  auto min_dmg = dmg_nat_att_dice().min_roll();
  min_dmg      = std::min(min_dmg, dmg_digest_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_melee_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_poison_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_drown_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_bite_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_claw_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_cold_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_fire_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_crush_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_lightning_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_energy_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_negation_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_acid_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_water_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_digest_dice().min_roll());
  min_dmg      = std::min(min_dmg, dmg_necrosis_dice().min_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    min_dmg = std::min(min_dmg, curr_weapon->dmg_min());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return min_dmg + enchant_count_get();
}

////////////////////////////////////////////////////////////////////////////
// damaged_count
////////////////////////////////////////////////////////////////////////////
int Thing::damaged_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->damaged_count);
  }
  return 0;
}

int Thing::damaged_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count = v);
}

int Thing::damaged_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count -= v);
}

int Thing::damaged_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count += v);
}

int Thing::damaged_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count--);
}

int Thing::damaged_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->damaged_count++);
}
