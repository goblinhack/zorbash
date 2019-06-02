/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#pragma once

#include <string>
#include <sstream>

#include "my_string.h"

class Dice {
private:
    int ndice {};
    int sides {};
    int modifier {};
    std::string hd;

public:
    Dice (void)
    {
    }

    std::string to_string (void) const
    {
        return (hd);
    }

    const char * to_cstring (void)
    {
        return (to_string().c_str());
    }

    Dice (std::string s)
    {
        hd = s;

        for (auto x : split_tokens(s, '+')) {
            auto d = split_tokens(x, 'd');
            if (d.size() == 2) {
                ndice = std::stoi(d[0]);
                sides = std::stoi(d[1]);
            } else {
                modifier += std::stoi(d[0]);
            }
        }
    }

    int roll(void) const
    {
        auto n = ndice;
        auto tot = 0;
        while (n--) {
            tot += random_range(0, sides) + 1;
        }
        tot += modifier;
        return (tot);
    }

    int operator ()() const
    {
        return (roll());
    }
};
