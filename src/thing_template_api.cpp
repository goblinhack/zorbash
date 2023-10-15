//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing_template.hpp"

//
// Dice
//
const Dice        &Tp::on_idle_tick_freq_dice(void) const { return _on_idle_tick_freq_dice; }
const int          Tp::on_idle_tick_freq(void) const { return _on_idle_tick_freq_dice.roll(); }
const std::string &Tp::on_idle_tick_freq_dice_str(void) const { return _on_idle_tick_freq_dice_str; }
void               Tp::on_idle_tick_freq_dice_set(const std::string &v)
{
  _on_idle_tick_freq_dice     = v;
  _on_idle_tick_freq_dice_str = v;
}

const Dice        &Tp::spawn_group_size_dice(void) const { return _spawn_group_size_dice; }
const int          Tp::spawn_group_size(void) const { return _spawn_group_size_dice.roll(); }
const std::string &Tp::spawn_group_size_dice_str(void) const { return _spawn_group_size_dice_str; }
void               Tp::spawn_group_size_dice_set(const std::string &v)
{
  _spawn_group_size_dice     = v;
  _spawn_group_size_dice_str = v;
}

const Dice        &Tp::lifespan_dice(void) const { return _lifespan_dice; }
const int          Tp::lifespan(void) const { return _lifespan_dice.roll(); }
const std::string &Tp::lifespan_dice_str(void) const { return _lifespan_dice_str; }
void               Tp::lifespan_dice_set(const std::string &v)
{
  _lifespan_dice     = v;
  _lifespan_dice_str = v;
}

const Dice        &Tp::nutrition_dice(void) const { return _nutrition_dice; }
const int          Tp::nutrition(void) const { return _nutrition_dice.roll(); }
const std::string &Tp::nutrition_dice_str(void) const { return _nutrition_dice_str; }
void               Tp::nutrition_dice_set(const std::string &v)
{
  _nutrition_dice     = v;
  _nutrition_dice_str = v;
}

const Dice        &Tp::dmg_melee_dice(void) const { return _dmg_melee_dice; }
const int          Tp::dmg_melee(void) const { return _dmg_melee_dice.roll(); }
const std::string &Tp::dmg_melee_dice_str(void) const { return _dmg_melee_dice_str; }
void               Tp::dmg_melee_dice_set(const std::string &v)
{
  _dmg_melee_dice     = v;
  _dmg_melee_dice_str = v;
}

const Dice        &Tp::dmg_poison_dice(void) const { return _dmg_poison_dice; }
const int          Tp::dmg_poison(void) const { return _dmg_poison_dice.roll(); }
const std::string &Tp::dmg_poison_dice_str(void) const { return _dmg_poison_dice_str; }
void               Tp::dmg_poison_dice_set(const std::string &v)
{
  _dmg_poison_dice     = v;
  _dmg_poison_dice_str = v;
}

const Dice        &Tp::dmg_drown_dice(void) const { return _dmg_drown_dice; }
const int          Tp::dmg_drown(void) const { return _dmg_drown_dice.roll(); }
const std::string &Tp::dmg_drown_dice_str(void) const { return _dmg_drown_dice_str; }
void               Tp::dmg_drown_dice_set(const std::string &v)
{
  _dmg_drown_dice     = v;
  _dmg_drown_dice_str = v;
}

const Dice        &Tp::dmg_bite_dice(void) const { return _dmg_bite_dice; }
const int          Tp::dmg_bite(void) const { return _dmg_bite_dice.roll(); }
const std::string &Tp::dmg_bite_dice_str(void) const { return _dmg_bite_dice_str; }
void               Tp::dmg_bite_dice_set(const std::string &v)
{
  _dmg_bite_dice     = v;
  _dmg_bite_dice_str = v;
}

const Dice        &Tp::dmg_claw_dice(void) const { return _dmg_claw_dice; }
const int          Tp::dmg_claw(void) const { return _dmg_claw_dice.roll(); }
const std::string &Tp::dmg_claw_dice_str(void) const { return _dmg_claw_dice_str; }
void               Tp::dmg_claw_dice_set(const std::string &v)
{
  _dmg_claw_dice     = v;
  _dmg_claw_dice_str = v;
}

const Dice        &Tp::dmg_cold_dice(void) const { return _dmg_cold_dice; }
const int          Tp::dmg_cold(void) const { return _dmg_cold_dice.roll(); }
const std::string &Tp::dmg_cold_dice_str(void) const { return _dmg_cold_dice_str; }
void               Tp::dmg_cold_dice_set(const std::string &v)
{
  _dmg_cold_dice     = v;
  _dmg_cold_dice_str = v;
}

const Dice        &Tp::dmg_fire_dice(void) const { return _dmg_fire_dice; }
const int          Tp::dmg_fire(void) const { return _dmg_fire_dice.roll(); }
const std::string &Tp::dmg_fire_dice_str(void) const { return _dmg_fire_dice_str; }
void               Tp::dmg_fire_dice_set(const std::string &v)
{
  _dmg_fire_dice     = v;
  _dmg_fire_dice_str = v;
}

const Dice        &Tp::dmg_heat_dice(void) const { return _dmg_heat_dice; }
const int          Tp::dmg_heat(void) const { return _dmg_heat_dice.roll(); }
const std::string &Tp::dmg_heat_dice_str(void) const { return _dmg_heat_dice_str; }
void               Tp::dmg_heat_dice_set(const std::string &v)
{
  _dmg_heat_dice     = v;
  _dmg_heat_dice_str = v;
}

const Dice        &Tp::dmg_crush_dice(void) const { return _dmg_crush_dice; }
const int          Tp::dmg_crush(void) const { return _dmg_crush_dice.roll(); }
const std::string &Tp::dmg_crush_dice_str(void) const { return _dmg_crush_dice_str; }
void               Tp::dmg_crush_dice_set(const std::string &v)
{
  _dmg_crush_dice     = v;
  _dmg_crush_dice_str = v;
}

const Dice        &Tp::dmg_impact_dice(void) const { return _dmg_impact_dice; }
const int          Tp::dmg_impact(void) const { return _dmg_impact_dice.roll(); }
const std::string &Tp::dmg_impact_dice_str(void) const { return _dmg_impact_dice_str; }
void               Tp::dmg_impact_dice_set(const std::string &v)
{
  _dmg_impact_dice     = v;
  _dmg_impact_dice_str = v;
}

const Dice        &Tp::dmg_missile_dice(void) const { return _dmg_missile_dice; }
const int          Tp::dmg_missile(void) const { return _dmg_missile_dice.roll(); }
const std::string &Tp::dmg_missile_dice_str(void) const { return _dmg_missile_dice_str; }
void               Tp::dmg_missile_dice_set(const std::string &v)
{
  _dmg_missile_dice     = v;
  _dmg_missile_dice_str = v;
}

const Dice        &Tp::dmg_lightning_dice(void) const { return _dmg_lightning_dice; }
const int          Tp::dmg_lightning(void) const { return _dmg_lightning_dice.roll(); }
const std::string &Tp::dmg_lightning_dice_str(void) const { return _dmg_lightning_dice_str; }
void               Tp::dmg_lightning_dice_set(const std::string &v)
{
  _dmg_lightning_dice     = v;
  _dmg_lightning_dice_str = v;
}

const Dice        &Tp::dmg_energy_dice(void) const { return _dmg_energy_dice; }
const int          Tp::dmg_energy(void) const { return _dmg_energy_dice.roll(); }
const std::string &Tp::dmg_energy_dice_str(void) const { return _dmg_energy_dice_str; }
void               Tp::dmg_energy_dice_set(const std::string &v)
{
  _dmg_energy_dice     = v;
  _dmg_energy_dice_str = v;
}

const Dice        &Tp::dmg_negation_dice(void) const { return _dmg_negation_dice; }
const int          Tp::dmg_negation(void) const { return _dmg_negation_dice.roll(); }
const std::string &Tp::dmg_negation_dice_str(void) const { return _dmg_negation_dice_str; }
void               Tp::dmg_negation_dice_set(const std::string &v)
{
  _dmg_negation_dice     = v;
  _dmg_negation_dice_str = v;
}

const Dice        &Tp::dmg_acid_dice(void) const { return _dmg_acid_dice; }
const int          Tp::dmg_acid(void) const { return _dmg_acid_dice.roll(); }
const std::string &Tp::dmg_acid_dice_str(void) const { return _dmg_acid_dice_str; }
void               Tp::dmg_acid_dice_set(const std::string &v)
{
  _dmg_acid_dice     = v;
  _dmg_acid_dice_str = v;
}

const Dice        &Tp::dmg_water_dice(void) const { return _dmg_water_dice; }
const int          Tp::dmg_water(void) const { return _dmg_water_dice.roll(); }
const std::string &Tp::dmg_water_dice_str(void) const { return _dmg_water_dice_str; }
void               Tp::dmg_water_dice_set(const std::string &v)
{
  _dmg_water_dice     = v;
  _dmg_water_dice_str = v;
}

const Dice        &Tp::dmg_digest_dice(void) const { return _dmg_digest_dice; }
const int          Tp::dmg_digest(void) const { return _dmg_digest_dice.roll(); }
const std::string &Tp::dmg_digest_dice_str(void) const { return _dmg_digest_dice_str; }
void               Tp::dmg_digest_dice_set(const std::string &v)
{
  _dmg_digest_dice     = v;
  _dmg_digest_dice_str = v;
}

const Dice        &Tp::dmg_necrosis_dice(void) const { return _dmg_necrosis_dice; }
const int          Tp::dmg_necrosis(void) const { return _dmg_necrosis_dice.roll(); }
const std::string &Tp::dmg_necrosis_dice_str(void) const { return _dmg_necrosis_dice_str; }
void               Tp::dmg_necrosis_dice_set(const std::string &v)
{
  _dmg_necrosis_dice     = v;
  _dmg_necrosis_dice_str = v;
}

const Dice        &Tp::dmg_stamina_dice(void) const { return _dmg_stamina_dice; }
const int          Tp::dmg_stamina(void) const { return _dmg_stamina_dice.roll(); }
const std::string &Tp::dmg_stamina_dice_str(void) const { return _dmg_stamina_dice_str; }
void               Tp::dmg_stamina_dice_set(const std::string &v)
{
  _dmg_stamina_dice     = v;
  _dmg_stamina_dice_str = v;
}

const Dice        &Tp::dmg_magic_drain_dice(void) const { return _dmg_magic_drain_dice; }
const int          Tp::dmg_magic_drain(void) const { return _dmg_magic_drain_dice.roll(); }
const std::string &Tp::dmg_magic_drain_dice_str(void) const { return _dmg_magic_drain_dice_str; }
void               Tp::dmg_magic_drain_dice_set(const std::string &v)
{
  _dmg_magic_drain_dice     = v;
  _dmg_magic_drain_dice_str = v;
}

const Dice        &Tp::dmg_nat_att_dice(void) const { return _dmg_nat_att_dice; }
const int          Tp::dmg_nat_att(void) const { return _dmg_nat_att_dice.roll(); }
const std::string &Tp::dmg_nat_att_dice_str(void) const { return _dmg_nat_att_dice_str; }
void               Tp::dmg_nat_att_dice_set(const std::string &v)
{
  _dmg_nat_att_dice     = v;
  _dmg_nat_att_dice_str = v;
}

const Dice        &Tp::health_initial_dice(void) const { return _health_initial_dice; }
const int          Tp::health_initial(void) const { return _health_initial_dice.roll(); }
const int          Tp::health_initial_max_roll(void) const { return _health_initial_dice.max_roll(); }
const std::string &Tp::health_initial_dice_str(void) const { return _health_initial_dice_str; }
void               Tp::health_initial_dice_set(const std::string &v)
{
  _health_initial_dice     = v;
  _health_initial_dice_str = v;
}

const Dice &Tp::health_regenerate_amount_dice(void) const { return _health_regenerate_amount_dice; }
const int   Tp::health_regenerate_amount(void) const { return _health_regenerate_amount_dice.roll(); }
const int   Tp::health_regenerate_amount_max_roll(void) const { return _health_regenerate_amount_dice.max_roll(); }
const std::string &Tp::health_regenerate_amount_dice_str(void) const { return _health_regenerate_amount_dice_str; }
void               Tp::health_regenerate_amount_dice_set(const std::string &v)
{
  _health_regenerate_amount_dice     = v;
  _health_regenerate_amount_dice_str = v;
}

const Dice        &Tp::gold_value_dice(void) const { return _gold_value_dice; }
const int          Tp::cash(void) const { return _gold_value_dice.roll(); }
const std::string &Tp::gold_value_dice_str(void) const { return _gold_value_dice_str; }
void               Tp::gold_value_dice_set(const std::string &v)
{
  _gold_value_dice     = v;
  _gold_value_dice_str = v;
}

const Dice        &Tp::resurrect_dice(void) const { return _resurrect_dice; }
const int          Tp::resurrect(void) const { return _resurrect_dice.roll(); }
const std::string &Tp::resurrect_dice_str(void) const { return _resurrect_dice_str; }
void               Tp::resurrect_dice_set(const std::string &v)
{
  _resurrect_dice     = v;
  _resurrect_dice_str = v;
}
