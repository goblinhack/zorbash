/*
 * Copyright(C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#pragma once

unsigned char *ramdisk_load(const char *filename, int32_t *outlen);

typedef struct ramdisk_t_ {
    const char *filename;
    const unsigned char *data;
    int32_t len;
} ramdisk_t;

void ramdisk_init(void);

extern ramdisk_t *ramdisk_get_data(void);
