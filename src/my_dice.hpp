//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_DICE_HPP_
#define _MY_DICE_HPP_

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

bool d20roll(int stat_a, int stat_b);
bool d20roll(int stat_a, int stat_b, bool &fumble, bool &critical);
bool d20roll_under(int stat);

int stat_to_bonus(int stat);

const std::string stat_to_bonus_string(int stat);
const std::string stat_to_bonus_slash_str(int stat);
const std::string modifier_to_string(int stat);

#endif
