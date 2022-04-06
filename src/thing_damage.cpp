//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>

#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

int Thing::damage_max(void)
{
  TRACE_NO_INDENT();
  auto max_damage = damage_natural_dice().max_roll();
  max_damage      = std::max(max_damage, damage_digest_dice().max_roll());
  max_damage      = std::max(max_damage, damage_melee_dice().max_roll());
  max_damage      = std::max(max_damage, damage_poison_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future1_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future2_dice().max_roll());
  max_damage      = std::max(max_damage, damage_future3_dice().max_roll());
  max_damage      = std::max(max_damage, damage_cold_dice().max_roll());
  max_damage      = std::max(max_damage, damage_fire_dice().max_roll());
  max_damage      = std::max(max_damage, damage_crush_dice().max_roll());
  max_damage      = std::max(max_damage, damage_lightning_dice().max_roll());
  max_damage      = std::max(max_damage, damage_energy_dice().max_roll());
  max_damage      = std::max(max_damage, damage_acid_dice().max_roll());
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
  auto min_damage = damage_natural_dice().min_roll();
  min_damage      = std::min(min_damage, damage_digest_dice().min_roll());
  min_damage      = std::min(min_damage, damage_melee_dice().min_roll());
  min_damage      = std::min(min_damage, damage_poison_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future1_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future2_dice().min_roll());
  min_damage      = std::min(min_damage, damage_future3_dice().min_roll());
  min_damage      = std::min(min_damage, damage_cold_dice().min_roll());
  min_damage      = std::min(min_damage, damage_fire_dice().min_roll());
  min_damage      = std::min(min_damage, damage_crush_dice().min_roll());
  min_damage      = std::min(min_damage, damage_lightning_dice().min_roll());
  min_damage      = std::min(min_damage, damage_energy_dice().min_roll());
  min_damage      = std::min(min_damage, damage_acid_dice().min_roll());
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

int Thing::damage_melee_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_melee_chance_d1000(index));
}

int Thing::damage_nat_attack_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_nat_attack_chance_d1000(index));
}

int Thing::damage_poison_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_poison_chance_d1000(index));
}

int Thing::damage_future1_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_future1_chance_d1000(index));
}

int Thing::damage_future2_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_future2_chance_d1000(index));
}

int Thing::damage_future3_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_future3_chance_d1000(index));
}

int Thing::damage_cold_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_cold_chance_d1000(index));
}

int Thing::damage_fire_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_fire_chance_d1000(index));
}

int Thing::damage_crush_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_crush_chance_d1000(index));
}

int Thing::damage_lightning_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_lightning_chance_d1000(index));
}

int Thing::damage_energy_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_energy_chance_d1000(index));
}

int Thing::damage_acid_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_acid_chance_d1000(index));
}

int Thing::damage_digest_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_digest_chance_d1000(index));
}

int Thing::damage_necrosis_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_necrosis_chance_d1000(index));
}

int Thing::damage_draining_chance_d1000(int index)
{
  TRACE_NO_INDENT();
  return (tp()->damage_draining_chance_d1000(index));
}

void Tp::damage_acid_chance_d1000_set(int index, int v)
{
  _damage_acid_chance_d1000.resize(index + 1);
  _damage_acid_chance_d1000[ index ] = v;
}

void Tp::damage_cold_chance_d1000_set(int index, int v)
{
  _damage_cold_chance_d1000.resize(index + 1);
  _damage_cold_chance_d1000[ index ] = v;
}

void Tp::damage_crush_chance_d1000_set(int index, int v)
{
  _damage_crush_chance_d1000.resize(index + 1);
  _damage_crush_chance_d1000[ index ] = v;
}

void Tp::damage_digest_chance_d1000_set(int index, int v)
{
  _damage_digest_chance_d1000.resize(index + 1);
  _damage_digest_chance_d1000[ index ] = v;
}

void Tp::damage_energy_chance_d1000_set(int index, int v)
{
  _damage_energy_chance_d1000.resize(index + 1);
  _damage_energy_chance_d1000[ index ] = v;
}

void Tp::damage_fire_chance_d1000_set(int index, int v)
{
  _damage_fire_chance_d1000.resize(index + 1);
  _damage_fire_chance_d1000[ index ] = v;
}

void Tp::damage_future1_chance_d1000_set(int index, int v)
{
  _damage_future1_chance_d1000.resize(index + 1);
  _damage_future1_chance_d1000[ index ] = v;
}

void Tp::damage_future2_chance_d1000_set(int index, int v)
{
  _damage_future2_chance_d1000.resize(index + 1);
  _damage_future2_chance_d1000[ index ] = v;
}

void Tp::damage_future3_chance_d1000_set(int index, int v)
{
  _damage_future3_chance_d1000.resize(index + 1);
  _damage_future3_chance_d1000[ index ] = v;
}

void Tp::damage_lightning_chance_d1000_set(int index, int v)
{
  _damage_lightning_chance_d1000.resize(index + 1);
  _damage_lightning_chance_d1000[ index ] = v;
}

void Tp::damage_melee_chance_d1000_set(int index, int v)
{
  _damage_melee_chance_d1000.resize(index + 1);
  _damage_melee_chance_d1000[ index ] = v;
}

void Tp::damage_nat_attack_chance_d1000_set(int index, int v)
{
  _damage_nat_attack_chance_d1000.resize(index + 1);
  _damage_nat_attack_chance_d1000[ index ] = v;
}

void Tp::damage_necrosis_chance_d1000_set(int index, int v)
{
  _damage_necrosis_chance_d1000.resize(index + 1);
  _damage_necrosis_chance_d1000[ index ] = v;
}
void Tp::damage_draining_chance_d1000_set(int index, int v)
{
  _damage_draining_chance_d1000.resize(index + 1);
  _damage_draining_chance_d1000[ index ] = v;
}
void Tp::damage_poison_chance_d1000_set(int index, int v)
{
  _damage_poison_chance_d1000.resize(index + 1);
  _damage_poison_chance_d1000[ index ] = v;
}

void Tp::damage_nat_attack_type_set(const std::string &v) { _damage_nat_attack_type = v; }

int Tp::damage_acid_chance_d1000(int index) const
{
  if (index >= _damage_acid_chance_d1000.size()) {
    return 0;
  }
  return _damage_acid_chance_d1000[ index ];
}

int Tp::damage_cold_chance_d1000(int index) const
{
  if (index >= _damage_cold_chance_d1000.size()) {
    return 0;
  }
  return _damage_cold_chance_d1000[ index ];
}

int Tp::damage_crush_chance_d1000(int index) const
{
  if (index >= _damage_crush_chance_d1000.size()) {
    return 0;
  }
  return _damage_crush_chance_d1000[ index ];
}

int Tp::damage_digest_chance_d1000(int index) const
{
  if (index >= _damage_digest_chance_d1000.size()) {
    return 0;
  }
  return _damage_digest_chance_d1000[ index ];
}

int Tp::damage_energy_chance_d1000(int index) const
{
  if (index >= _damage_energy_chance_d1000.size()) {
    return 0;
  }
  return _damage_energy_chance_d1000[ index ];
}

int Tp::damage_fire_chance_d1000(int index) const
{
  if (index >= _damage_fire_chance_d1000.size()) {
    return 0;
  }
  return _damage_fire_chance_d1000[ index ];
}

int Tp::damage_future1_chance_d1000(int index) const
{
  if (index >= _damage_future1_chance_d1000.size()) {
    return 0;
  }
  return _damage_future1_chance_d1000[ index ];
}

int Tp::damage_future2_chance_d1000(int index) const
{
  if (index >= _damage_future2_chance_d1000.size()) {
    return 0;
  }
  return _damage_future2_chance_d1000[ index ];
}

int Tp::damage_future3_chance_d1000(int index) const
{
  if (index >= _damage_future3_chance_d1000.size()) {
    return 0;
  }
  return _damage_future3_chance_d1000[ index ];
}

int Tp::damage_lightning_chance_d1000(int index) const
{
  if (index >= _damage_lightning_chance_d1000.size()) {
    return 0;
  }
  return _damage_lightning_chance_d1000[ index ];
}

int Tp::damage_melee_chance_d1000(int index) const
{
  if (index >= _damage_melee_chance_d1000.size()) {
    return 0;
  }
  return _damage_melee_chance_d1000[ index ];
}

int Tp::damage_nat_attack_chance_d1000(int index) const
{
  if (index >= _damage_nat_attack_chance_d1000.size()) {
    return 0;
  }
  return _damage_nat_attack_chance_d1000[ index ];
}

int Tp::damage_necrosis_chance_d1000(int index) const
{
  if (index >= _damage_necrosis_chance_d1000.size()) {
    return 0;
  }
  return _damage_necrosis_chance_d1000[ index ];
}

int Tp::damage_draining_chance_d1000(int index) const
{
  if (index >= _damage_draining_chance_d1000.size()) {
    return 0;
  }
  return _damage_draining_chance_d1000[ index ];
}

int Tp::damage_poison_chance_d1000(int index) const
{
  if (index >= _damage_poison_chance_d1000.size()) {
    return 0;
  }
  return _damage_poison_chance_d1000[ index ];
}
