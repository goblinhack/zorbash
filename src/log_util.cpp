//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_ascii.hpp"
#include "my_log.hpp"

void putf(FILE *fp, const char *s)
{
  auto sp = s;
  while (*sp) {
    if (*sp == '%') {
      std::string out = ascii_strip(s);
      fputs(out.c_str(), fp);
      putc('\n', fp);
      return;
    }
    sp++;
  }

  fputs(s, fp);
  putc('\n', fp);
}
