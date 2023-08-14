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
  int ndice {};    // 1d6+2 (1)
  int sides {};    // 1d6+2 (6)
  int modifier {}; // 1d6+2 (6)

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

  int operator()() const;
};

#define SAVING_ROLL_MODERATE 10
#define SAVING_ROLL_HARD     19

bool d20_ge(int stat_total, const int dice_roll_to_exceed);
bool d20_ge(int stat_total, const int dice_roll_to_exceed, bool &fumble, bool &critical);

int stat_to_bonus(int stat);

const std::string stat_to_bonus_string(int stat);
const std::string stat_to_bonus_slash_str(int stat);
const std::string bonus_to_string(int stat);

extern int d10000(void);
extern int d1000(void);
extern int d100(void);
extern int d10(void);
extern int d11(void);
extern int d12(void);
extern int d13(void);
extern int d14(void);
extern int d15(void);
extern int d16(void);
extern int d17(void);
extern int d18(void);
extern int d19(void);
extern int d20(void);
extern int d2(void);
extern int d3(void);
extern int d4(void);
extern int d50(void);
extern int d5(void);
extern int d6(void);
extern int d7(void);
extern int d8(void);
extern int d9(void);

#endif
