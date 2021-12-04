//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_depth.hpp"
#include "my_dice.hpp"
#include "my_level.hpp"
#include "my_sys.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Dice
//
const Dice        &Tp::on_idle_dice(void) const { return _on_idle_dice; }
const int          Tp::idle_tick(void) const { return _on_idle_dice.roll(); }
const std::string &Tp::on_idle_dice_str(void) const { return _on_idle_dice_str; }
void               Tp::set_on_idle_dice(const std::string &v)
{
  _on_idle_dice     = v;
  _on_idle_dice_str = v;
}

const Dice        &Tp::lifespan_dice(void) const { return _lifespan_dice; }
const int          Tp::lifespan(void) const { return _lifespan_dice.roll(); }
const std::string &Tp::lifespan_dice_str(void) const { return _lifespan_dice_str; }
void               Tp::set_lifespan_dice(const std::string &v)
{
  _lifespan_dice     = v;
  _lifespan_dice_str = v;
}

const Dice        &Tp::nutrition_dice(void) const { return _nutrition_dice; }
const int          Tp::nutrition(void) const { return _nutrition_dice.roll(); }
const std::string &Tp::nutrition_dice_str(void) const { return _nutrition_dice_str; }
void               Tp::set_nutrition_dice(const std::string &v)
{
  _nutrition_dice     = v;
  _nutrition_dice_str = v;
}

const Dice        &Tp::get_damage_melee_dice(void) const { return _damage_melee_dice; }
const int          Tp::get_damage_melee(void) const { return _damage_melee_dice.roll(); }
const std::string &Tp::get_damage_melee_dice_str(void) const { return _damage_melee_dice_str; }
void               Tp::set_damage_melee_dice(const std::string &v)
{
  _damage_melee_dice     = v;
  _damage_melee_dice_str = v;
}

const Dice        &Tp::get_damage_poison_dice(void) const { return _damage_poison_dice; }
const int          Tp::get_damage_poison(void) const { return _damage_poison_dice.roll(); }
const std::string &Tp::get_damage_poison_dice_str(void) const { return _damage_poison_dice_str; }
void               Tp::set_damage_poison_dice(const std::string &v)
{
  _damage_poison_dice     = v;
  _damage_poison_dice_str = v;
}

const Dice        &Tp::get_damage_future1_dice(void) const { return _damage_future1_dice; }
const int          Tp::get_damage_future1(void) const { return _damage_future1_dice.roll(); }
const std::string &Tp::get_damage_future1_dice_str(void) const { return _damage_future1_dice_str; }
void               Tp::set_damage_future1_dice(const std::string &v)
{
  _damage_future1_dice     = v;
  _damage_future1_dice_str = v;
}

const Dice        &Tp::get_damage_future2_dice(void) const { return _damage_future2_dice; }
const int          Tp::get_damage_future2(void) const { return _damage_future2_dice.roll(); }
const std::string &Tp::get_damage_future2_dice_str(void) const { return _damage_future2_dice_str; }
void               Tp::set_damage_future2_dice(const std::string &v)
{
  _damage_future2_dice     = v;
  _damage_future2_dice_str = v;
}

const Dice        &Tp::get_damage_future3_dice(void) const { return _damage_future3_dice; }
const int          Tp::get_damage_future3(void) const { return _damage_future3_dice.roll(); }
const std::string &Tp::get_damage_future3_dice_str(void) const { return _damage_future3_dice_str; }
void               Tp::set_damage_future3_dice(const std::string &v)
{
  _damage_future3_dice     = v;
  _damage_future3_dice_str = v;
}

const Dice        &Tp::get_damage_future4_dice(void) const { return _damage_future4_dice; }
const int          Tp::get_damage_future4(void) const { return _damage_future4_dice.roll(); }
const std::string &Tp::get_damage_future4_dice_str(void) const { return _damage_future4_dice_str; }
void               Tp::set_damage_future4_dice(const std::string &v)
{
  _damage_future4_dice     = v;
  _damage_future4_dice_str = v;
}

const Dice        &Tp::get_damage_future5_dice(void) const { return _damage_future1_dice; }
const int          Tp::get_damage_future5(void) const { return _damage_future1_dice.roll(); }
const std::string &Tp::get_damage_future5_dice_str(void) const { return _damage_future1_dice_str; }
void               Tp::set_damage_future5_dice(const std::string &v)
{
  _damage_future5_dice     = v;
  _damage_future5_dice_str = v;
}

const Dice        &Tp::get_damage_future6_dice(void) const { return _damage_future6_dice; }
const int          Tp::get_damage_future6(void) const { return _damage_future6_dice.roll(); }
const std::string &Tp::get_damage_future6_dice_str(void) const { return _damage_future6_dice_str; }
void               Tp::set_damage_future6_dice(const std::string &v)
{
  _damage_future6_dice     = v;
  _damage_future6_dice_str = v;
}

const Dice        &Tp::get_damage_future7_dice(void) const { return _damage_future7_dice; }
const int          Tp::get_damage_future7(void) const { return _damage_future7_dice.roll(); }
const std::string &Tp::get_damage_future7_dice_str(void) const { return _damage_future7_dice_str; }
void               Tp::set_damage_future7_dice(const std::string &v)
{
  _damage_future7_dice     = v;
  _damage_future7_dice_str = v;
}

const Dice        &Tp::get_damage_energy_dice(void) const { return _damage_energy_dice; }
const int          Tp::get_damage_energy(void) const { return _damage_energy_dice.roll(); }
const std::string &Tp::get_damage_energy_dice_str(void) const { return _damage_energy_dice_str; }
void               Tp::set_damage_energy_dice(const std::string &v)
{
  _damage_energy_dice     = v;
  _damage_energy_dice_str = v;
}

const Dice        &Tp::get_damage_acid_dice(void) const { return _damage_acid_dice; }
const int          Tp::get_damage_acid(void) const { return _damage_acid_dice.roll(); }
const std::string &Tp::get_damage_acid_dice_str(void) const { return _damage_acid_dice_str; }
void               Tp::set_damage_acid_dice(const std::string &v)
{
  _damage_acid_dice     = v;
  _damage_acid_dice_str = v;
}

const Dice        &Tp::get_damage_digest_dice(void) const { return _damage_digest_dice; }
const int          Tp::get_damage_digest(void) const { return _damage_digest_dice.roll(); }
const std::string &Tp::get_damage_digest_dice_str(void) const { return _damage_digest_dice_str; }
void               Tp::set_damage_digest_dice(const std::string &v)
{
  _damage_digest_dice     = v;
  _damage_digest_dice_str = v;
}

const Dice        &Tp::get_damage_necrosis_dice(void) const { return _damage_necrosis_dice; }
const int          Tp::get_damage_necrosis(void) const { return _damage_necrosis_dice.roll(); }
const std::string &Tp::get_damage_necrosis_dice_str(void) const { return _damage_necrosis_dice_str; }
void               Tp::set_damage_necrosis_dice(const std::string &v)
{
  _damage_necrosis_dice     = v;
  _damage_necrosis_dice_str = v;
}

const Dice        &Tp::get_damage_crush_dice(void) const { return _damage_crush_dice; }
const int          Tp::get_damage_crush(void) const { return _damage_crush_dice.roll(); }
const std::string &Tp::get_damage_crush_dice_str(void) const { return _damage_crush_dice_str; }
void               Tp::set_damage_crush_dice(const std::string &v)
{
  _damage_crush_dice     = v;
  _damage_crush_dice_str = v;
}

const Dice        &Tp::get_damage_bite_dice(void) const { return _damage_bite_dice; }
const int          Tp::get_damage_bite(void) const { return _damage_bite_dice.roll(); }
const std::string &Tp::get_damage_bite_dice_str(void) const { return _damage_bite_dice_str; }
void               Tp::set_damage_bite_dice(const std::string &v)
{
  _damage_bite_dice     = v;
  _damage_bite_dice_str = v;
}

const Dice        &Tp::get_health_initial_dice(void) const { return _health_initial_dice; }
const int          Tp::get_health_initial(void) const { return _health_initial_dice.roll(); }
const std::string &Tp::get_health_initial_dice_str(void) const { return _health_initial_dice_str; }
void               Tp::set_health_initial_dice(const std::string &v)
{
  _health_initial_dice     = v;
  _health_initial_dice_str = v;
}

const Dice        &Tp::gold_value_dice(void) const { return _gold_value_dice; }
const int          Tp::cash(void) const { return _gold_value_dice.roll(); }
const std::string &Tp::gold_value_dice_str(void) const { return _gold_value_dice_str; }
void               Tp::set_gold_value_dice(const std::string &v)
{
  _gold_value_dice     = v;
  _gold_value_dice_str = v;
}

const Dice        &Tp::resurrect_dice(void) const { return _resurrect_dice; }
const int          Tp::resurrect(void) const { return _resurrect_dice.roll(); }
const std::string &Tp::resurrect_dice_str(void) const { return _resurrect_dice_str; }
void               Tp::set_resurrect_dice(const std::string &v)
{
  _resurrect_dice     = v;
  _resurrect_dice_str = v;
}

std::string Tp::text_a_or_an(void) const { return _text_a_or_an; }

//
// foo bar -> Foo Bar
//
std::string Tp::short_text_capitalized(void) const
{
  TRACE_AND_INDENT();
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
