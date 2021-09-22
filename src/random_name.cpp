//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_random_name.h"

#include <iostream>
#include <functional> // for std::hash
#include <string>

std::string random_name(int len) {
  for (;;) {
    std::string d1(dict1_name());
    std::string d2(dict2_name());
    if ((int) (d1.size() + d2.size()) > len) {
      continue;
    }

    return d1 + d2;
  }
}

uint32_t string_to_hash(const std::string &str) {
  std::hash<std::string> hasher;
  uint32_t               hashed = static_cast<uint32_t>(hasher(str) % 0xffffffff); // returns std::size_t
  return hashed;
}
