/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include <strstream>
#include <stdlib.h>
#include "minilzo.h"

#define HEAP_ALLOC(var,size) \
    void *var; \
    posix_memalign(&var, sizeof(lzo_align_t), size + size / 16 + 64 + 3);


static std::vector<char> read_lzo (const std::string filename,
                                   lzo_uint *uncompressed_file_size)
{_
    // binary mode is only for switching off newline translation
    std::ifstream file(filename, std::ios::binary);
    file.unsetf(std::ios::skipws);

    std::streampos file_size;
    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    lzo_uint sz;
    file >> bits(sz);
    *uncompressed_file_size = sz;
    file_size -= sizeof(sz);

    std::vector<char> vec;
    vec.reserve(file_size);
    vec.insert(vec.begin(),
               std::istream_iterator<char>(file),
               std::istream_iterator<char>());

    return (vec);
}

void
Game::save (void)
{_
    std::stringstream s(std::ios::in | std::ios::out | std::ios::binary);

    const class Game &c = *this;
    s << bits(c);

    //
    // Get the pre compress buffer
    //
    auto data = s.str().c_str();
    s.seekg(0, std::ios::end);
    lzo_uint uncompressed_len = s.tellg();
    s.seekg(0, std::ios::beg);

    HEAP_ALLOC(uncompressed, uncompressed_len);
    HEAP_ALLOC(compressed, uncompressed_len);
    memcpy(uncompressed, data, uncompressed_len);

    std::cout << "before compression ";
    (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);

    if (lzo_init() != LZO_E_OK) {
        ERR("internal error - lzo_init() failed !!!\n");
        DIE("(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
    }

    HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

    lzo_uint compressed_len = 0;
    int r = lzo1x_1_compress((lzo_bytep)uncompressed, uncompressed_len,
                             (lzo_bytep)compressed, &compressed_len, wrkmem);
    if (r == LZO_E_OK) {
        printf("compressed %lu bytes into %lu bytes\n",
            (unsigned long) uncompressed_len, (unsigned long) compressed_len);
    } else {
        DIE("internal error - compression failed: %d", r);
    }

    //
    // Dump the post compress buffer
    //
    std::cout << "after compression ";
    (void) hexdump((const unsigned char *)compressed, compressed_len);

    //
    // Save the post compress buffer
    //
    auto ofile = fopen(saved_file.c_str(), "wb");
    fwrite((char*) &uncompressed_len, sizeof(uncompressed_len), 1, ofile);
    fwrite(compressed, compressed_len, 1, ofile);
    fclose(ofile);
}

void
Game::load (void)
{_
    //
    // Read to a vector and then copy to a C buffer for qlz to use
    //
    lzo_uint uncompressed_len;
    auto vec = read_lzo(saved_file, &uncompressed_len);
    auto data = vec.data();
    lzo_uint compressed_len = vec.size();

    printf("read compressed %lu bytes back into %lu bytes\n",
        (unsigned long) compressed_len, (unsigned long) uncompressed_len);

    HEAP_ALLOC(compressed, compressed_len);
    HEAP_ALLOC(uncompressed, uncompressed_len);
    memcpy(compressed, data, compressed_len);


    lzo_uint new_len = 0;
    int r = lzo1x_decompress((lzo_bytep)compressed, compressed_len, (lzo_bytep)uncompressed, &new_len, NULL);
    if (r == LZO_E_OK && new_len == uncompressed_len) {
        CON("decompressed %lu bytes back into %lu bytes",
            (unsigned long) compressed_len, (unsigned long) uncompressed_len);
    } else {
        /* this should NEVER happen */
        DIE("internal error - decompression failed: %d\n", r);
    }

    std::cout << "decompressed as ";
    hexdump((const unsigned char *)uncompressed, uncompressed_len);

    std::istrstream in((const char *)uncompressed, uncompressed_len);
    class Game &c = *this;
    in >> bits(c);
    this->dump("", std::cout);
}
