//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_DICE_H_
#define _MY_DICE_H_

#include <string>

class Dice {
private:
    int ndice {};
    int sides {};
    int modifier {};
    std::string hd;
public:
    std::string python_func;
    std::string python_mod;
    Dice (void);
    std::string to_string (void) const;
    const char *to_cstring(void);
    Dice (std::string s);
    int roll(void) const;
    int max_roll(void) const;
    int min_roll(void) const;
    bool crit_roll(void) const;
    bool crit_roll_minus_modifier(void) const;
    int operator ()() const;
};

bool d20roll(int modifier_a, int modifier_b);
bool d20roll(int modifier_a, int modifier_b, bool &fumble, bool &critical);
int modifier_to_bonus(int modifier);
const std::string modifier_to_bonus_str(int modifier);
const std::string modifier_to_bonus_slash_str(int modifier);

#endif
