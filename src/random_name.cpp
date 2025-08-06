//
// Copyright goblinhack@gmail.com
//

#include "my_random_name.hpp"

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

// https://stackoverflow.com/questions/7666509/hash-function-for-string
static unsigned long hash(const char *s)
{
  unsigned long hash = 5381;
  char          c;

  while ((c = *s++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

uint32_t string_to_hash(const std::string &str)
{
#ifdef FANCY_BUT_GIVES_DIFFERENT_RESULTS_ON_DIFFERENT_PLATFORMS
  return static_cast< uint32_t >(std::hash< std::string > {}(str));
#else
  return hash(str.c_str());
#endif
}
