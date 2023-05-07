//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DICE_HPP_
#define _MY_DICE_HPP_

#include "my_random.hpp"
#include <string>

class Dice
{
private:
  int ndice {};
  int sides {};
  int stat {};

  std::string hd;

public:
  std::string python_func;
  std::string python_mod;
  std::string to_string(void) const;

  Dice(void);
  Dice(std::string s);

  int roll(void) const;
  int max_roll(void) const;
  int min_roll(void) const;

  bool crit_roll(void) const;
  bool crit_roll_minus_stat(void) const;

  int operator()() const;
};

bool d20_ge(int stat_a, int stat_b);
bool d20_ge(int stat_a, int stat_b, bool &fumble, bool &critical);
bool d20_le(int stat_a, int stat_b);
bool d20_le(int stat_a, int stat_b, bool &fumble, bool &critical);
bool d20_le(int stat);

int stat_to_bonus(int stat);

const std::string stat_to_bonus_string(int stat);
const std::string stat_to_bonus_slash_str(int stat);
const std::string bonus_to_string(int stat);

#define d10000() ((int) pcg_random_range_inclusive(1, 10000))
#define d1000()  ((int) pcg_random_range_inclusive(1, 1000))
#define d100()   ((int) pcg_random_range_inclusive(1, 100))
#define d10()    ((int) pcg_random_range_inclusive(1, 10))
#define d11()    ((int) pcg_random_range_inclusive(1, 11))
#define d12()    ((int) pcg_random_range_inclusive(1, 12))
#define d13()    ((int) pcg_random_range_inclusive(1, 13))
#define d14()    ((int) pcg_random_range_inclusive(1, 14))
#define d15()    ((int) pcg_random_range_inclusive(1, 15))
#define d16()    ((int) pcg_random_range_inclusive(1, 16))
#define d17()    ((int) pcg_random_range_inclusive(1, 17))
#define d18()    ((int) pcg_random_range_inclusive(1, 18))
#define d19()    ((int) pcg_random_range_inclusive(1, 19))
#define d20()    ((int) pcg_random_range_inclusive(1, 20))
#define d2()     ((int) pcg_random_range_inclusive(1, 2))
#define d3()     ((int) pcg_random_range_inclusive(1, 3))
#define d4()     ((int) pcg_random_range_inclusive(1, 4))
#define d50()    ((int) pcg_random_range_inclusive(1, 50))
#define d5()     ((int) pcg_random_range_inclusive(1, 5))
#define d6()     ((int) pcg_random_range_inclusive(1, 6))
#define d7()     ((int) pcg_random_range_inclusive(1, 7))
#define d8()     ((int) pcg_random_range_inclusive(1, 8))
#define d9()     ((int) pcg_random_range_inclusive(1, 9))

#endif
