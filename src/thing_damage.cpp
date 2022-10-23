//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::attacks_per_round(void)
{
  TRACE_NO_INDENT();
  return (tp()->attacks_per_round());
}

int Thing::weapon_damage(void)
{
  TRACE_NO_INDENT();
  return (tp()->weapon_damage());
}

int Thing::damage_current(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->damage_current;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->damage_current();
  }
  return v;
}

int Thing::damage_current_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->damage_current = v);
  return n;
}

int Thing::damage_current_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->damage_current -= v);
  return n;
}

int Thing::damage_current_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->damage_current += v);
  return n;
}

int Thing::damage_current_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->damage_current--);
  return n;
}

int Thing::damage_current_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->damage_current++);
  return n;
}
int Thing::damage_max(void)
{
  TRACE_NO_INDENT();
  auto max_damage = damage_nat_att_dice().max_roll();
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, damage_drown_dice().max_roll());
  max_damage      = std::max(max_damage, damage_bite_dice().max_roll());
  max_damage      = std::max(max_damage, damage_claw_dice().max_roll());
  max_damage      = std::max(max_damage, damage_cold_dice().max_roll());
  max_damage      = std::max(max_damage, damage_fire_dice().max_roll());
  max_damage      = std::max(max_damage, damage_crush_dice().max_roll());
  max_damage      = std::max(max_damage, damage_lightning_dice().max_roll());
  max_damage      = std::max(max_damage, damage_energy_dice().max_roll());
  max_damage      = std::max(max_damage, damage_acid_dice().max_roll());
  max_damage      = std::max(max_damage, damage_water_dice().max_roll());
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_necrosis_dice().max_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    max_damage = std::max(max_damage, curr_weapon->damage_max());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return max_damage + enchant_get();
}

int Thing::damage_min(void)
{
  TRACE_NO_INDENT();
  auto min_damage = damage_nat_att_dice().min_roll();
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, damage_drown_dice().min_roll());
  min_damage      = std::min(min_damage, damage_bite_dice().min_roll());
  min_damage      = std::min(min_damage, damage_claw_dice().min_roll());
  min_damage      = std::min(min_damage, damage_cold_dice().min_roll());
  min_damage      = std::min(min_damage, damage_fire_dice().min_roll());
  min_damage      = std::min(min_damage, damage_crush_dice().min_roll());
  min_damage      = std::min(min_damage, damage_lightning_dice().min_roll());
  min_damage      = std::min(min_damage, damage_energy_dice().min_roll());
  min_damage      = std::min(min_damage, damage_acid_dice().min_roll());
  min_damage      = std::min(min_damage, damage_water_dice().min_roll());
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_necrosis_dice().min_roll());

  //
  // Add in weapons
  //
  Thingp curr_weapon = equip_get(MONST_EQUIP_WEAPON);
  if (curr_weapon) {
    min_damage = std::min(min_damage, curr_weapon->damage_min());
  }

  //
  // Don't include crush damage as it is non typical
  //
  return min_damage + enchant_get();
}
