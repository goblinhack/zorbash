//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dice.hpp"
#include "my_sys.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Dice
//
const Dice        &Tp::on_idle_tick_frequency_dice(void) const { return _on_idle_tick_frequency_dice; }
const int          Tp::on_idle_tick_frequency_get(void) const { return _on_idle_tick_frequency_dice.roll(); }
const std::string &Tp::on_idle_tick_frequency_dice_str(void) const { return _on_idle_tick_frequency_dice_str; }
void               Tp::on_idle_tick_frequency_dice_set(const std::string &v)
{
  _on_idle_tick_frequency_dice     = v;
  _on_idle_tick_frequency_dice_str = v;
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

const Dice        &Tp::damage_future2_dice(void) const { return _damage_future2_dice; }
const int          Tp::damage_future2(void) const { return _damage_future2_dice.roll(); }
const std::string &Tp::damage_future2_dice_str(void) const { return _damage_future2_dice_str; }
void               Tp::damage_future2_dice_set(const std::string &v)
{
  _damage_future2_dice     = v;
  _damage_future2_dice_str = v;
}

const Dice        &Tp::damage_future3_dice(void) const { return _damage_future3_dice; }
const int          Tp::damage_future3(void) const { return _damage_future3_dice.roll(); }
const std::string &Tp::damage_future3_dice_str(void) const { return _damage_future3_dice_str; }
void               Tp::damage_future3_dice_set(const std::string &v)
{
  _damage_future3_dice     = v;
  _damage_future3_dice_str = v;
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

const Dice        &Tp::damage_natural_dice(void) const { return _damage_natural_dice; }
const int          Tp::damage_natural_attack(void) const { return _damage_natural_dice.roll(); }
const std::string &Tp::damage_natural_dice_str(void) const { return _damage_natural_dice_str; }
void               Tp::damage_natural_dice_set(const std::string &v)
{
  _damage_natural_dice     = v;
  _damage_natural_dice_str = v;
}

const Dice        &Tp::health_initial_dice(void) const { return _health_initial_dice; }
const int          Tp::health_initial(void) const { return _health_initial_dice.roll(); }
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
std::string Tp::short_text_capitalise(void) const
{
  TRACE_NO_INDENT();
  std::string out        = text_name();
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
