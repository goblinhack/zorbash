//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_string.h"
#include "my_ramdisk.h"
#include "my_ptrcheck.h"

std::map<std::string, ramdisk_t_> ramdisk_data;

unsigned char *ramdisk_load (const char *filename, int *outlen)
{_
    auto f = ramdisk_data.find(filename);
    if (f == ramdisk_data.end()) {
        return nullptr;
    }

    auto ramfile = f->second;

    uint8_t *out = (__typeof__(out))
                    mymalloc(ramfile.len + 1, "ramdisk load");
    if (!out) {
        ERR("No memory for loading ramdisk out, %s", filename);
        return (nullptr);
    }

    memcpy(out, (unsigned char*)ramfile.data, ramfile.len);
    *(out + ramfile.len) = 0;
    *outlen = ramfile.len;

    return (out);
}
