//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_ascii.h"
#include "my_log.h"

void putf (FILE *fp, const char *s)
{
    std::string out = ascii_strip(s);
    fputs(out.c_str(), fp);
    putc('\n', fp);
}
