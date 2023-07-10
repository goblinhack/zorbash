//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dice.hpp"
#include "my_main.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

//
// True if the a >= b
//
bool d20_ge(int stat_total, const int dice_roll_to_exceed, bool &fumble, bool &critical)
{
  auto dice_roll = pcg_random_range_inclusive(1, 20);

  critical = false;
  fumble   = false;

  if (dice_roll == 20) {
    critical = true;
    return true;
  }

  if (dice_roll == 1) {
    fumble = true;
    return false;
  }

  return dice_roll + stat_to_bonus(stat_total) >= dice_roll_to_exceed;
}

//
// Roll for stat modifier "a" to see if it beats "b"
//
bool d20_ge(int stat_total, const int dice_roll_to_exceed)
{
  auto dice_roll = pcg_random_range_inclusive(1, 20);

  if (dice_roll == 20) {
    DBG("d20: rolled a 20 => success");
    return true;
  }

  if (dice_roll == 1) {
    DBG("d20: fumble");
    return false;
  }

  DBG("d20: %d(rolled %d+%d) >= %d", dice_roll + stat_to_bonus(stat_total), dice_roll, stat_to_bonus(stat_total),
      dice_roll_to_exceed);

  dice_roll += stat_to_bonus(stat_total);

  return dice_roll >= dice_roll_to_exceed;
}

bool Thing::d20_ge(int stat_total, const int dice_roll_to_exceed)
{
  auto dice_roll = pcg_random_range_inclusive(1, 20);

  if (dice_roll == 20) {
    dbg("d20: rolled a 20 => success");
    return true;
  }

  if (dice_roll == 1) {
    dbg("d20: fumble");
    return false;
  }

  dbg("d20: %d(rolled %d+%d) >= %d", dice_roll + stat_to_bonus(stat_total), dice_roll, stat_to_bonus(stat_total),
      dice_roll_to_exceed);

  dice_roll += stat_to_bonus(stat_total);

  return dice_roll >= dice_roll_to_exceed;
}

Dice::Dice(void) = default;

std::string Dice::to_string(void) const { return hd; }

Dice::Dice(std::string s)
{
  hd = s;

  //
  // Allow python function after ":" so "1d1+1:fire.call_me()" is allowed
  //
  for (auto d : split_tokens(s, ':')) {
    std::size_t found = d.find("()");
    if (found != std::string::npos) {
      //
      // Parse the python function call
      //
      auto bare_func = d.replace(found, 2, "");
      auto sp        = split_tokens(bare_func, '.');
      if (sp.size() == 2) {
        //
        // <module>.<func>()
        //
        python_mod  = sp[ 0 ];
        python_func = sp[ 1 ];
      } else {
        //
        // <func>()
        //
        python_func = sp[ 0 ];
      }
    } else {
      //
      // 1d6+1
      //
      for (auto x : split_tokens(d, '+')) {
        auto sp = split_tokens(x, 'd');
        if (sp.size() == 2) {
          ndice = std::stoi(sp[ 0 ]);
          sides = std::stoi(sp[ 1 ]);
        } else {
          stat += std::stoi(sp[ 0 ]);
        }
        // CON("new dice %dd%d+%d", ndice, sides, stat);
      }
    }
  }
}

int Dice::roll(void) const
{
  int n   = ndice;
  int tot = 0;
  // CON("roll %dd%d+%d", ndice, sides, stat);
  while (n-- > 0) {
    tot += pcg_random_range(0, sides) + 1;
  }
  tot += stat;
  // CON("roll %dd%d+%d => %d", ndice, sides, stat, tot);
  return tot;
}

int Dice::max_roll(void) const { return ndice * sides + stat; }

int Dice::min_roll(void) const { return ndice * 1 + stat; }

bool Dice::crit_roll(void) const
{
  auto r = roll();
  return r >= (ndice * sides);
}

bool Dice::crit_roll_minus_stat(void) const
{
  auto r = roll();
  return r - stat >= (ndice * sides);
}

int Dice::operator()() const { return (roll()); }
