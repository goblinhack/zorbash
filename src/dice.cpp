//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_string.h"
#include "my_dice.h"

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

    //
    // Allow python function after ":" so "1d1+1:call_me()" is allowed
    //
    for (auto d : split_tokens(s, ':')) {
        std::size_t found = d.find("()");
        if (found != std::string::npos) {
            python_func = d.replace(found, 2, "");
        } else {
            for (auto x : split_tokens(d, '+')) {
                auto d = split_tokens(x, 'd');
                if (d.size() == 2) {
                    ndice = std::stoi(d[0]);
                    sides = std::stoi(d[1]);
                } else {
                    modifier += std::stoi(d[0]);
                }
            }
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
