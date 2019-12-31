//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_string.h"
#include "my_main.h"
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
