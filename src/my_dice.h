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
    bool crit_roll(void) const;
    bool crit_roll_minus_modifier(void) const;
    int operator ()() const;
};
#endif
