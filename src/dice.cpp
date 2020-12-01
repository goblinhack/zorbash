//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
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
    // Allow python function after ":" so "1d1+1:fire.call_me()" is allowed
    //
    for (auto d : split_tokens(s, ':')) {
        std::size_t found = d.find("()");
        if (found != std::string::npos) {
            //
            // Parse the python function call
            //
            auto bare_func = d.replace(found, 2, "");
            auto sp = split_tokens(bare_func, '.');
            if (sp.size() == 2) {
                //
                // <module>.<func>()
                //
                python_mod = sp[0];
                python_func = sp[1];
            } else {
                //
                // <func>()
                //
                python_func = sp[0];
            }
        } else {
            //
            // 1d6+1
            //
            for (auto x : split_tokens(d, '+')) {
                auto sp = split_tokens(x, 'd');
                if (sp.size() == 2) {
                    ndice = std::stoi(sp[0]);
                    sides = std::stoi(sp[1]);
                } else {
                    modifier += std::stoi(sp[0]);
                }
                // CON("new dice %dd%d+%d", ndice, sides, modifier);
            }
        }
    }
}

int Dice::roll (void) const
{
    auto n = ndice;
    auto tot = 0;
    while (n--) {
        tot += random_range(0, sides) + 1;
    }
    tot += modifier;
    // CON("roll %dd%d+%d => %d", ndice, sides, modifier, tot);
    return (tot);
}

int Dice::max_roll (void) const
{
    return ndice * sides + modifier;
}

bool Dice::crit_roll (void) const
{
    auto r = roll();
    return r >= (ndice * sides);
}

bool Dice::crit_roll_minus_modifier (void) const
{
    auto r = roll();
    return r - modifier >= (ndice * sides);
}

int Dice::operator ()() const
{
    return (roll());
}
