/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include <strstream>
#include "quicklz.h"

static std::vector<char> read_binary_file (const std::string filename)
{_
    // binary mode is only for switching off newline translation
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios::skipws);

    std::streampos file_size;
    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> vec(file_size);
    vec.insert(vec.begin(),
               std::istream_iterator<char>(file),
               std::istream_iterator<char>());
    return (vec);
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
}

void
Game::load (void)
{_
    //
    // Read to a vector and then copy to a C buffer for qlz to use
    //
    auto vec = read_binary_file(saved_file);
    auto src = vec.data();

    //
    // Decompress
    //
    auto dstlen = qlz_size_decompressed(src);
    auto dst = new char[dstlen];
    qlz_state_decompress *state_decompress = 
      (qlz_state_decompress *)new char[sizeof(qlz_state_decompress)];
    auto newlen = qlz_decompress(src, dst, state_decompress);

    std::cout << "decompressed as ";
    hexdump(dst, newlen);

    std::istrstream in(dst, newlen);

    class Game &c = *this;
    in >> bits(c);

    delete state_decompress;
    delete []dst;

    this->dump("", std::cout);
}
