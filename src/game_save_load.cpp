/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include <strstream>
#include "quicklz.h"

std::ostream& operator<<(std::ostream &out, 
                         Bits<const class Game & > const my)
{
    out << bits(my.t.appdata);
    out << bits(my.t.saved_dir);
    out << bits(my.t.saved_file);
    return (out);
}

std::istream& operator>>(std::istream &in, Bits<class Game &> my)
{
    in >> bits(my.t.appdata);
    in >> bits(my.t.saved_dir);
    in >> bits(my.t.saved_file);
    return (in);
}

void
Game::save (void)
{_
    std::stringstream out(std::ios::in | std::ios::out | std::ios::binary);

    const class Game &c = *this;
    out << bits(c);

    //
    // Get the pre compress buffer
    //
    auto src = out.str().c_str();
    out.seekg(0, std::ios::end);
    int srclen = out.tellg();
    out.seekg(0, std::ios::beg);

    std::cout << "before compression ";
    (void) hexdump(src, srclen);

    //
    // Compress
    //
    qlz_state_compress *state_compress = 
      (qlz_state_compress *)new char[sizeof(qlz_state_compress)];

    //
    // http://www.quicklz.com/manual.html
    //
    // The destination buffer must be at least size + 400 bytes large because 
    // incompressible data may increase in size.
    // 
    auto dst = new char[srclen + 400 /* qlz header */];
    auto dstlen = qlz_compress(src, dst, srclen, state_compress);

    //
    // Dump the post compress buffer
    //
    std::cout << "after compression ";
    (void) hexdump(dst, dstlen);

    //
    // Save the post compress buffer
    //
    auto ofile = fopen(saved_file.c_str(), "wb");
    fwrite(dst, dstlen, 1, ofile);
    fclose(ofile);
    delete []dst;
    delete state_compress;
    DIE("xx");
}

void
Game::load (void)
{_
//    std::ifstream in(saved_file);

//    auto g = new Game;
//    in >> bits(g);
}
