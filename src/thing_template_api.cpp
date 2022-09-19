//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_sys.hpp"
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

const Dice        &Tp::damage_melee_dice(void) const { return _damage_melee_dice; }
const int          Tp::damage_melee(void) const { return _damage_melee_dice.roll(); }
const std::string &Tp::damage_melee_dice_str(void) const { return _damage_melee_dice_str; }
void               Tp::damage_melee_dice_set(const std::string &v)
{
  _damage_melee_dice     = v;
  _damage_melee_dice_str = v;
}

const Dice        &Tp::damage_poison_dice(void) const { return _damage_poison_dice; }
const int          Tp::damage_poison(void) const { return _damage_poison_dice.roll(); }
const std::string &Tp::damage_poison_dice_str(void) const { return _damage_poison_dice_str; }
void               Tp::damage_poison_dice_set(const std::string &v)
{
  _damage_poison_dice     = v;
  _damage_poison_dice_str = v;
}

const Dice        &Tp::damage_future1_dice(void) const { return _damage_future1_dice; }
const int          Tp::damage_future1(void) const { return _damage_future1_dice.roll(); }
const std::string &Tp::damage_future1_dice_str(void) const { return _damage_future1_dice_str; }
void               Tp::damage_future1_dice_set(const std::string &v)
{
  _damage_future1_dice     = v;
  _damage_future1_dice_str = v;
}

const Dice        &Tp::damage_bite_dice(void) const { return _damage_bite_dice; }
const int          Tp::damage_bite(void) const { return _damage_bite_dice.roll(); }
const std::string &Tp::damage_bite_dice_str(void) const { return _damage_bite_dice_str; }
void               Tp::damage_bite_dice_set(const std::string &v)
{
  _damage_bite_dice     = v;
  _damage_bite_dice_str = v;
}

const Dice        &Tp::damage_claw_dice(void) const { return _damage_claw_dice; }
const int          Tp::damage_claw(void) const { return _damage_claw_dice.roll(); }
const std::string &Tp::damage_claw_dice_str(void) const { return _damage_claw_dice_str; }
void               Tp::damage_claw_dice_set(const std::string &v)
{
  _damage_claw_dice     = v;
  _damage_claw_dice_str = v;
}

const Dice        &Tp::damage_cold_dice(void) const { return _damage_cold_dice; }
const int          Tp::damage_cold(void) const { return _damage_cold_dice.roll(); }
const std::string &Tp::damage_cold_dice_str(void) const { return _damage_cold_dice_str; }
void               Tp::damage_cold_dice_set(const std::string &v)
{
  _damage_cold_dice     = v;
  _damage_cold_dice_str = v;
}

const Dice        &Tp::damage_fire_dice(void) const { return _damage_fire_dice; }
const int          Tp::damage_fire(void) const { return _damage_fire_dice.roll(); }
const std::string &Tp::damage_fire_dice_str(void) const { return _damage_fire_dice_str; }
void               Tp::damage_fire_dice_set(const std::string &v)
{
  _damage_fire_dice     = v;
  _damage_fire_dice_str = v;
}

const Dice        &Tp::damage_crush_dice(void) const { return _damage_crush_dice; }
const int          Tp::damage_crush(void) const { return _damage_crush_dice.roll(); }
const std::string &Tp::damage_crush_dice_str(void) const { return _damage_crush_dice_str; }
void               Tp::damage_crush_dice_set(const std::string &v)
{
  _damage_crush_dice     = v;
  _damage_crush_dice_str = v;
}

const Dice        &Tp::damage_lightning_dice(void) const { return _damage_lightning_dice; }
const int          Tp::damage_lightning(void) const { return _damage_lightning_dice.roll(); }
const std::string &Tp::damage_lightning_dice_str(void) const { return _damage_lightning_dice_str; }
void               Tp::damage_lightning_dice_set(const std::string &v)
{
  _damage_lightning_dice     = v;
  _damage_lightning_dice_str = v;
}

const Dice        &Tp::damage_energy_dice(void) const { return _damage_energy_dice; }
const int          Tp::damage_energy(void) const { return _damage_energy_dice.roll(); }
const std::string &Tp::damage_energy_dice_str(void) const { return _damage_energy_dice_str; }
void               Tp::damage_energy_dice_set(const std::string &v)
{
  _damage_energy_dice     = v;
  _damage_energy_dice_str = v;
}

const Dice        &Tp::damage_acid_dice(void) const { return _damage_acid_dice; }
const int          Tp::damage_acid(void) const { return _damage_acid_dice.roll(); }
const std::string &Tp::damage_acid_dice_str(void) const { return _damage_acid_dice_str; }
void               Tp::damage_acid_dice_set(const std::string &v)
{
  _damage_acid_dice     = v;
  _damage_acid_dice_str = v;
}

const Dice        &Tp::damage_water_dice(void) const { return _damage_water_dice; }
const int          Tp::damage_water(void) const { return _damage_water_dice.roll(); }
const std::string &Tp::damage_water_dice_str(void) const { return _damage_water_dice_str; }
void               Tp::damage_water_dice_set(const std::string &v)
{
  _damage_water_dice     = v;
  _damage_water_dice_str = v;
}

const Dice        &Tp::damage_digest_dice(void) const { return _damage_digest_dice; }
const int          Tp::damage_digest(void) const { return _damage_digest_dice.roll(); }
const std::string &Tp::damage_digest_dice_str(void) const { return _damage_digest_dice_str; }
void               Tp::damage_digest_dice_set(const std::string &v)
{
  _damage_digest_dice     = v;
  _damage_digest_dice_str = v;
}

const Dice        &Tp::damage_necrosis_dice(void) const { return _damage_necrosis_dice; }
const int          Tp::damage_necrosis(void) const { return _damage_necrosis_dice.roll(); }
const std::string &Tp::damage_necrosis_dice_str(void) const { return _damage_necrosis_dice_str; }
void               Tp::damage_necrosis_dice_set(const std::string &v)
{
  _damage_necrosis_dice     = v;
  _damage_necrosis_dice_str = v;
}

const Dice        &Tp::damage_draining_dice(void) const { return _damage_draining_dice; }
const int          Tp::damage_draining(void) const { return _damage_draining_dice.roll(); }
const std::string &Tp::damage_draining_dice_str(void) const { return _damage_draining_dice_str; }
void               Tp::damage_draining_dice_set(const std::string &v)
{
  _damage_draining_dice     = v;
  _damage_draining_dice_str = v;
}

const Dice        &Tp::damage_nat_att_dice(void) const { return _damage_nat_att_dice; }
const int          Tp::damage_nat_att(void) const { return _damage_nat_att_dice.roll(); }
const std::string &Tp::damage_nat_att_dice_str(void) const { return _damage_nat_att_dice_str; }
void               Tp::damage_nat_att_dice_set(const std::string &v)
{
  _damage_nat_att_dice     = v;
  _damage_nat_att_dice_str = v;
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

std::string Tp::text_a_or_an(void) const { return _text_a_or_an; }

//
// foo bar -> Foo Bar
//
std::string Tp::text_short_capitalised(void) const
{
  TRACE_NO_INDENT();
  std::string out        = text_long_name();
  char       *b          = (char *) out.c_str();
  char       *e          = b + out.size();
  char       *c          = b;
  bool        word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}
