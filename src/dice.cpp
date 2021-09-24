//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dice.h"
#include "my_main.h"
#include "my_random.h"
#include "my_string.h"
#include "my_sys.h"

int stat_to_bonus(int stat)
{
  switch (stat) {
    case 0 : return 0; // Acts like not set
    case 1 : return -5;
    case 2 : return -4;
    case 3 : return -4;
    case 4 : return -3;
    case 5 : return -3;
    case 6 : return -2;
    case 7 : return -2;
    case 8 : return -1;
    case 9 : return -1;
    case 10 : return 0;
    case 11 : return 0;
    case 12 : return 1;
    case 13 : return 1;
    case 14 : return 2;
    case 15 : return 2;
    case 16 : return 3;
    case 17 : return 3;
    case 18 : return 4;
    case 19 : return 4;
    case 20 : return 5;
    case 21 : return 5;
    case 22 : return 6;
    case 23 : return 6;
    case 24 : return 7;
    case 25 : return 7;
    case 26 : return 8;
    case 27 : return 8;
    case 28 : return 9;
    case 29 : return 9;
    case 30 : return 9;
    default : return 9;
  }
}

const std::string stat_to_bonus_str(int stat)
{
  switch (stat) {
    case 0 : return "0"; // Acts like not set
    case 1 : return "-5";
    case 2 : return "-4";
    case 3 : return "-4";
    case 4 : return "-3";
    case 5 : return "-3";
    case 6 : return "-2";
    case 7 : return "-2";
    case 8 : return "-1";
    case 9 : return "-1";
    case 10 : return "+0";
    case 11 : return "+0";
    case 12 : return "+1";
    case 13 : return "+1";
    case 14 : return "+2";
    case 15 : return "+2";
    case 16 : return "+3";
    case 17 : return "+3";
    case 18 : return "+4";
    case 19 : return "+4";
    case 20 : return "+5";
    case 21 : return "+5";
    case 22 : return "+6";
    case 23 : return "+6";
    case 24 : return "+7";
    case 25 : return "+7";
    case 26 : return "+8";
    case 27 : return "+8";
    case 28 : return "+9";
    case 29 : return "+9";
    case 30 : return "+9";
    default : return "+9";
  }
}

const std::string stat_to_bonus_slash_str(int stat)
{
  switch (stat) {
    case 0 : return "/na"; // Acts like not set
    case 1 : return "/-5";
    case 2 : return "/-4";
    case 3 : return "/-4";
    case 4 : return "/-3";
    case 5 : return "/-3";
    case 6 : return "/-2";
    case 7 : return "/-2";
    case 8 : return "/-1";
    case 9 : return "/-1";
    case 10 : return "/+0";
    case 11 : return "/+0";
    case 12 : return "/+1";
    case 13 : return "/+1";
    case 14 : return "/+2";
    case 15 : return "/+2";
    case 16 : return "/+3";
    case 17 : return "/+3";
    case 18 : return "/+4";
    case 19 : return "/+4";
    case 20 : return "/+5";
    case 21 : return "/+5";
    case 22 : return "/+6";
    case 23 : return "/+6";
    case 24 : return "/+7";
    case 25 : return "/+7";
    case 26 : return "/+8";
    case 27 : return "/+8";
    case 28 : return "/+9";
    case 29 : return "/+9";
    case 30 : return "/+9";
    default : return "/+9";
  }
}

//
// Roll "a" to see if it beats "b"
//
bool d20roll(int stat_a, int stat_b, bool &fumble, bool &critical)
{
  auto roll_a = pcg_random_range_inclusive(1, 20);

  critical = false;
  fumble   = false;

  if (roll_a == 20) {
    critical = true;
    return true;
  }

  if (roll_a == 1) {
    fumble = true;
    return false;
  }

  auto roll_b = pcg_random_range_inclusive(1, 20);
  // TOPCON("a %d b %d", roll_a, roll_b);

  return roll_a + stat_to_bonus(stat_a) >= roll_b + stat_to_bonus(stat_b);
}

//
// Roll "a" to see if it beats "b"
//
bool d20roll(int stat_a, int stat_b)
{
  auto roll_a = pcg_random_range_inclusive(1, 20);

  if (roll_a == 20) {
    return true;
  }

  if (roll_a == 1) {
    return false;
  }

  auto roll_b = pcg_random_range_inclusive(1, 20);

  roll_a += stat_to_bonus(stat_a);
  roll_b += stat_to_bonus(stat_b);
  // TOPCON("A %d(+%d) B %d(%d)", roll_a, stat_a, roll_b, stat_b);

  return roll_a >= roll_b;
}

Dice::Dice(void) {}

std::string Dice::to_string(void) const { return (hd); }

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
  // LOG("roll %dd%d+%d => %d", ndice, sides, stat, tot);
  while (n-- > 0) {
    tot += pcg_random_range(0, sides) + 1;
  }
  tot += stat;
  return (tot);
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
