//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_random_name.hpp"
#include "my_sys.hpp"

#include <functional> // for std::hash
#include <iostream>
#include <string>

std::string random_name(int len)
{
  for (;;) {
    std::string d1(dict1_name());
    std::string d2(dict2_name());
    if ((int) (d1.size() + d2.size()) > len) {
      continue;
    }

    return d1 + d2;
  }
}

uint32_t string_to_hash(const std::string &str) { return static_cast< uint32_t >(std::hash< std::string > {}(str)); }
