/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include <strstream>
#include "minilzo.h"

#define HEAP_ALLOC(var,size) \
    void *var; \
    posix_memalign(&var, sizeof(lzo_align_t), size + size / 16 + 64 + 3);

// binary mode is only for switching off newline translation
// ios::ate, open at end
std::vector<char> read_file (const std::string filename)
{_
    std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
    ifs.unsetf(std::ios::skipws);

    std::ifstream::pos_type sz = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> bytes(sz);
    ifs.read(bytes.data(), sz);

    return bytes;
}

static std::vector<char> read_lzo_file (const std::string filename,
                                        lzo_uint *uncompressed_sz)
{_
    std::ifstream ifs(filename, std::ios::in | std::ios::binary | std::ios::ate);
    // tellg is not ideal, look into <filesystem> post mojave
    std::ifstream::pos_type sz = ifs.tellg();

    ifs.seekg(0, std::ios::beg);
    ifs.unsetf(std::ios::skipws);
    ifs.read((char*) uncompressed_sz, sizeof(lzo_uint));

    sz -= (int) sizeof(lzo_uint);
    std::vector<char> bytes(sz);
    ifs.read(bytes.data(), sz);

    return (bytes);
}

void
Game::save (void)
{_
    CON("%s: save", saved_file.c_str());

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

//    std::cout << "before compression ";
//    (void) hexdump((const unsigned char*)uncompressed, uncompressed_len);

    if (lzo_init() != LZO_E_OK) {
        DIE("LZO init fail: enable '-DLZO_DEBUG' for diagnostics)");
    }

    HEAP_ALLOC(wrkmem, LZO1X_1_MEM_COMPRESS);

    lzo_uint compressed_len = 0;
    int r = lzo1x_1_compress((lzo_bytep)uncompressed, uncompressed_len,
                             (lzo_bytep)compressed, &compressed_len, wrkmem);
    if (r == LZO_E_OK) {
        CON("%s: compressed %lu to %lu bytes",
            saved_file.c_str(),
            (unsigned long) uncompressed_len, 
            (unsigned long) compressed_len);
    } else {
        DIE("LZO internal error - compression failed: %d", r);
    }

    //
    // Dump the post compress buffer
    //
//    std::cout << "after compression ";
//    (void) hexdump((const unsigned char *)compressed, compressed_len);

    //
    // Save the post compress buffer
    //
    auto ofile = fopen(saved_file.c_str(), "wb");
    fwrite((char*) &uncompressed_len, sizeof(uncompressed_len), 1, ofile);
    fwrite(compressed, compressed_len, 1, ofile);
    fclose(ofile);

    free(uncompressed);
    free(compressed);
    free(wrkmem);

    CON("%s: saved", saved_file.c_str());
}

void
Game::load (void)
{_
    CON("%s: load", saved_file.c_str());

    //
    // Read to a vector and then copy to a C buffer for LZO to use
    //
    lzo_uint uncompressed_len;
    auto vec = read_lzo_file(saved_file, &uncompressed_len);
    auto data = vec.data();
    lzo_uint compressed_len = vec.size();

    HEAP_ALLOC(compressed, compressed_len);
    HEAP_ALLOC(uncompressed, uncompressed_len);
    memcpy(compressed, data, compressed_len);

    lzo_uint new_len = 0;
    int r = lzo1x_decompress((lzo_bytep)compressed, compressed_len, (lzo_bytep)uncompressed, &new_len, NULL);
    if (r == LZO_E_OK && new_len == uncompressed_len) {
        CON("%s: decompressed %lu to %lu bytes",
            saved_file.c_str(),
            (unsigned long) compressed_len, 
            (unsigned long) uncompressed_len);
    } else {
        /* this should NEVER happen */
        DIE("LZO internal error - decompression failed: %d", r);
    }

//    std::cout << "decompressed as ";
//    hexdump((const unsigned char *)uncompressed, uncompressed_len);

    std::istrstream in((const char *)uncompressed, uncompressed_len);
    class Game &c = *this;
    in >> bits(c);
//    this->dump("", std::cout);

    free(uncompressed);
    free(compressed);

    CON("%s: loaded", saved_file.c_str());
}
