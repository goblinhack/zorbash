/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_string.h"

class Dice {
private:
    int ndice {};
    int sides {};
    int modifier {};
public:
    Dice(std::string s) 
    {
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

    int roll(void)
    {
        auto n = ndice;
        auto tot = 0;
        while (n--) {
            tot += random_range(0, sides);
        }
        tot += modifier;
        return (tot);
    }
};
