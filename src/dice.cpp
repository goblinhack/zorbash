//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <sstream>
#include "my_main.h"
#include "my_string.h"
#include "my_dice.h"

int dice_roll (const std::string &s)
{
    auto tot = 0;
    for (auto x : split_tokens(s, '+')) {
        auto d = split_tokens(x, 'd');
        if (d.size() == 2) {
            auto n = std::stoi(d[0]);
            auto hd = std::stoi(d[1]);
            while (n--) {
                tot += random_range(0, hd);
            }
        } else {
            tot += std::stoi(d[0]);
        }
    }
    return (tot);
}

Dice::Dice (void)
{
}

std::string Dice::to_string (void) const
{
    return (hd);
}

const char * Dice::to_cstring (void)
{
    return (to_string().c_str());
}

Dice::Dice (std::string s)
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

int Dice::roll(void) const
{
    auto n = ndice;
    auto tot = 0;
    while (n--) {
        tot += random_range(0, sides) + 1;
    }
    tot += modifier;
    return (tot);
}

int Dice::operator ()() const
{
    return (roll());
}
