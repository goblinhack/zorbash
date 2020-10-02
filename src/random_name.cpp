//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//
#include "my_main.h"
#include "my_random_name.h"

std::string random_name (int len)
{
    for (;;) {
        std::string d1(dict1_name());
        std::string d2(dict2_name());
        if ((int) (d1.size() + d2.size()) > len) {
            continue;
        }

        if (random_range(0, 100) < 50) {
            return d1 + d2;
        } else {
            return d2 + d1;
        }
    }
}
