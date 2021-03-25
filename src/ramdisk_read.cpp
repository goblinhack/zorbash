//
// Copyright(C) 2011-2020 goblinhack@gmail.com
//
// See the README file for license info for license.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_string.h"
#include "my_ramdisk.h"
#include "my_ptrcheck.h"

std::map<std::string, ramdisk_t_> ramdisk_data;

unsigned char *ramdisk_load (const std::string &filename, int *outlen)
{_
    auto f = ramdisk_data.find(filename);
    if (f == ramdisk_data.end()) {
        return nullptr;
    }

    auto ramfile = f->second;

    uint8_t *out = (__typeof__(out))
                    mymalloc(ramfile.len + 1, "ramdisk load");
    if (!out) {
        ERR("No memory for loading ramdisk out, %s", filename.c_str());
        return (nullptr);
    }

    memcpy(out, (unsigned char*)ramfile.data, (int)ramfile.len);
    *(out + (int)ramfile.len) = 0;

    return (out);
}
