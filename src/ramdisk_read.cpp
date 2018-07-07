/*
 * Copyright(C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include "my_string.h"

#define nUSE_ZLIB
#define nUSE_MINIZ
#define nUSE_STB_IMAGE

#ifdef USE_ZLIB
#endif

#ifdef USE_MINIZ
#endif

#ifdef USE_STB_IMAGE
#endif

#include "my_file.h"

#include "ramdisk_data.cpp"

extern ramdisk_t ramdisk_data[];

unsigned char *ramdisk_load (const char *filename, int32_t *outlen)
{_
    ramdisk_t *ramfile = ramdisk_data;
    unsigned char *out;
    char *alt_filename;

    alt_filename = 0;

    /*
     * If the file is on disk and is newer than the program, use that in
     * preference.
     */
    if (file_exists(filename)) {
        if (strstr(filename, "data/")) {
            if (file_exists_and_is_newer_than(filename,
                                              EXEC_FULL_PATH_AND_NAME)) {
                out = file_read_if_exists(filename, outlen);
                if (out) {
                    DBG("Locdisk %s (newer than exec)", filename);
                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(filename, ".o/ramdisk_data.o")) {
                out = file_read_if_exists(filename, outlen);
                if (out) {
                    DBG("Locdisk %s (newer than build)", filename);
                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(filename, "src/.o/ramdisk_data.o")) {
                out = file_read_if_exists(filename, outlen);
                if (out) {
                    DBG("Locdisk %s (newer than src build)", filename);
                    return (out);
                }
            }
        } else {
            out = file_read_if_exists(filename, outlen);
            if (out) {
                DBG("Locdisk %s (exists locally)", filename);
                return (out);
            }
        }
    }

    if (EXEC_DIR) {
        alt_filename = strprepend(filename, EXEC_DIR);

        if (file_exists(alt_filename)) {
            if (file_exists_and_is_newer_than(alt_filename,
                                              EXEC_FULL_PATH_AND_NAME)) {
                out = file_read_if_exists(alt_filename, outlen);
                if (out) {
                    DBG("Locdisk %s", filename);
                    myfree(alt_filename);
                    alt_filename = 0;

                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(alt_filename,
                                            ".o/ramdisk_data.o")) {
                out = file_read_if_exists(alt_filename, outlen);
                if (out) {
                    DBG("Locdisk %s", filename);
                    myfree(alt_filename);
                    alt_filename = 0;

                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(alt_filename,
                                            "src/.o/ramdisk_data.o")) {
                out = file_read_if_exists(alt_filename, outlen);
                if (out) {
                    DBG("Locdisk %s", filename);
                    myfree(alt_filename);
                    alt_filename = 0;

                    return (out);
                }
            }
        }
    }

    while (ramfile->filename) {
        if (strcmp(ramfile->filename, filename)) {
            ramfile++;
            continue;
        }

        if (outlen) {
            *outlen = (int)ramfile->len;
        }

        DBG("Ramdisk %s, %d bytes", filename, ramfile->len);

        if (alt_filename) {
            myfree(alt_filename);
            alt_filename = 0;
        }

        uint8_t *copy = (__typeof__(copy))
                        mymalloc((int)ramfile->len + 1, "ramdisk load");
        if (!copy) {
            DBG("no memory for loading ramdisk copy, %s", filename);
            return (0);
        }

        memcpy(copy, (unsigned char*)ramfile->data, (int)ramfile->len);
        *(copy + (int)ramfile->len) = 0;

        return (copy);

#ifdef USE_ZLIB
        int32_t err;

        out = mymalloc(ramfile->orig_len, "RAMDISK scratchpad");
        if (!out) {
            ERR("no memory for ramdisk, %s", filename);
        }

        outlenl = ramfile->orig_len;
        err = uncompress(out, &outlenl,
                         (unsigned char *)ramfile->data,
                         ramfile->len);
        if (err) {
            ERR("file failed to decompress from ramdisk, %s, "
                "orig len %d, compressed len %d, err %d",
                filename, ramfile->orig_len, ramfile->len, err);
        }

        if (outlen) {
            *outlen = (int)outlenl;
        }
#endif

#ifdef USE_MINIZ
        int32_t err;

        out = (__typeof__(out)) mymalloc(ramfile->orig_len, "RAMDISK scratchpad");
        if (!out) {
            ERR("no memory for ramdisk, %s", filename);
        }

        outlenl = ramfile->orig_len;
        err = mz_uncompress(out, &outlenl,
                            (unsigned char *)ramfile->data,
                            ramfile->len);
        if (err) {
            ERR("file failed to decompress from ramdisk, %s, err %d",
                filename, err);
        }

        if (outlen) {
            *outlen = (int32_t)outlenl;
        }
#endif

#ifdef USE_STB_IMAGE
        out = (__typeof__(out))
            stbi_zlib_decode_malloc((const char *)ramfile->data,
                                    ramfile->len, &outlenl);
        if (!out) {
            ERR("file failed to decompress from ramdisk, %s", filename);
        }

        if (outlen) {
            *outlen = (int)outlenl;
        }
#endif

        return (out);
    }

    /*
     * Fallback to the disk.
     */
    out = file_read_if_exists(filename, outlen);
    if (out) {
        DBG("Locdisk %s", filename);

        if (alt_filename) {
            myfree(alt_filename);
            alt_filename = 0;
        }

        return (out);
    }

    out = file_read_if_exists(alt_filename, outlen);
    if (out) {
        DBG("Locdisk %s", filename);

        if (alt_filename) {
            myfree(alt_filename);
            alt_filename = 0;
        }

        return (out);
    }

    if (alt_filename) {
        myfree(alt_filename);
        alt_filename = 0;
    }

    {
        std::string alt_filename = mybasename(filename, "strip dir");

        out = file_read_if_exists(alt_filename.c_str(), outlen);
        if (out) {
            DBG("Locdisk %s", alt_filename.c_str());

            return (out);
        }
    }

    /*
     * Fail. Caller should whinge.
     *
    char *popup_str = dynprintf("Filename was not found on ramdisk or "
                                "on the local disk, %s", filename);

    MSG_BOX("%s", popup_str);
    myfree(popup_str);
     */
    LOG("File not found \"%s\"", filename);

    if (alt_filename) {
        myfree(alt_filename);
        alt_filename = 0;
    }

    return (0);
}

ramdisk_t *ramdisk_get_data (void)
{_
    return (ramdisk_data);
}
