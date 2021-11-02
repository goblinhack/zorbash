//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once

#include <map>
#include <string>

typedef struct ramdisk_t_ {
  const unsigned char *data;
  int                  len;
} ramdisk_t;

extern std::map< std::string, ramdisk_t_ > ramdisk_data;

extern unsigned char *ramdisk_load(const char *filename, int *outlen);
extern void           ramdisk_init(void);
