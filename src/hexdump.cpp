//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_string.hpp"
#include <iomanip>
#include <string.h>  // do not remove
#include <strings.h> // do not remove

#define HEX_DUMP_WIDTH (16)

//
// e.g.
// 00000000  02 00 00 00 09 00 00 00  76 65 63 2D 65 6C 65 6D |........vec-elem|
// 00000010  31 09 00 00 00 76 65 63  2D 65 6C 65 6D 32 02 00 |1....vec-elem2..|
// 00000020  00 00 0A 00 00 00 6C 69  73 74 2D 65 6C 65 6D 31 |......list-elem1|
// 00000030  0A 00 00 00 6C 69 73 74  2D 65 6C 65 6D 32 12 61 |....list-elem2.a|
// 00000040  72 72 2D 65 6C 65 6D 31  00 00 00 00 00 00 00 00 |rr-elem1........|
// 00000050  00 00 00 00 00 00 12 61  72 72 2D 65 6C 65 6D 32 |.......arr-elem2|
// 00000060  00 00 00 00 00 00 00 00  00 00 00 00 00 00 30 31 |..............01|
// 00000070  32 33 34 35 61 62 63 64  65 66 67 68 69 6A 6B 6C |2345abcdefghi
//
void hexdump(const unsigned char *addr, size_t len)
{
  int           skipping_blanks         = false;
  unsigned char empty[ HEX_DUMP_WIDTH ] = {0};
  unsigned char buf[ HEX_DUMP_WIDTH + 1 ];
  auto         *pc = (unsigned char *) addr;
  size_t        i;
  unsigned int  x;

  std::cout << std::dec << len << " bytes:" << std::endl;

  if (! len) {
    return;
  }

  for (i = 0, x = 0; i < len; i++, x++) {
    if ((i % HEX_DUMP_WIDTH) == 0) {
      if (! skipping_blanks) {
        if (i != 0) {
          std::cout << " |" << std::setw(HEX_DUMP_WIDTH) << buf << "|" << std::endl;
        }
      }

      /*
       * Skip blank blocks.
       */
      if (! memcmp(pc + i, empty, sizeof(empty))) {
        i += HEX_DUMP_WIDTH - 1;
        skipping_blanks = true;
        buf[ 0 ]        = '\0';
        continue;
      }

      std::cout << "  " << std::setfill('0') << std::setw(4) << std::hex << i;

      x = 0;
    }

    if (x && (((i % (HEX_DUMP_WIDTH / 2))) == 0)) {
      std::cout << " ";
    }

    skipping_blanks = false;

    std::cout << " " << std::setfill('0') << std::setw(2) << std::hex << (int) pc[ i ];

    if ((pc[ i ] < ' ') || (pc[ i ] > '~')) {
      buf[ i % HEX_DUMP_WIDTH ] = '.';
    } else {
      buf[ i % HEX_DUMP_WIDTH ] = pc[ i ];
    }

    buf[ (i % HEX_DUMP_WIDTH) + 1 ] = '\0';
  }

  if (! buf[ 0 ]) {
    if (skipping_blanks) {
      std::cout << "  *\n";
    }

    return;
  }

  while ((i % HEX_DUMP_WIDTH) != 0) {
    std::cout << "   ";
    if (i && (((i % (HEX_DUMP_WIDTH / 2))) == 0)) {
      std::cout << " ";
    }

    i++;
  }

  std::cout << " |" << std::setw(-HEX_DUMP_WIDTH) << buf << "|" << std::endl;
}

void hexdump(std::vector< unsigned char > &v) { hexdump(v.data(), v.size()); }
