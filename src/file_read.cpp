//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <string.h>

#include "my_main.h"
#include "my_ramdisk.h"
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

unsigned char *file_load (const char *filename, int32_t *outlen)
{_
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
                    DBG("file %s (newer than exec)", filename);
                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(filename, ".o/file_data.o")) {
                out = file_read_if_exists(filename, outlen);
                if (out) {
                    DBG("file %s (newer than build)", filename);
                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(filename, "src/.o/file_data.o")) {
                out = file_read_if_exists(filename, outlen);
                if (out) {
                    DBG("file %s (newer than src build)", filename);
                    return (out);
                }
            }
        } else {
            out = file_read_if_exists(filename, outlen);
            if (out) {
                DBG("file %s (exists locally)", filename);
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
                    DBG("file %s", filename);
                    myfree(alt_filename);
                    alt_filename = 0;

                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(alt_filename,
                                            ".o/file_data.o")) {
                out = file_read_if_exists(alt_filename, outlen);
                if (out) {
                    DBG("file %s", filename);
                    myfree(alt_filename);
                    alt_filename = 0;

                    return (out);
                }
            }

            if (file_exists_and_is_newer_than(alt_filename,
                                            "src/.o/file_data.o")) {
                out = file_read_if_exists(alt_filename, outlen);
                if (out) {
                    DBG("file %s", filename);
                    myfree(alt_filename);
                    alt_filename = 0;

                    return (out);
                }
            }
        }
    }

    /*
     * Fallback to the disk.
     */
    out = file_read_if_exists(filename, outlen);
    if (out) {
        DBG("file %s", filename);

        if (alt_filename) {
            myfree(alt_filename);
            alt_filename = 0;
        }

        return (out);
    }

    out = file_read_if_exists(alt_filename, outlen);
    if (out) {
        DBG("file %s", filename);

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
            DBG("file %s", alt_filename.c_str());

            return (out);
        }
    }

    /*
     * Fail. Caller should whinge.

    char *popup_str = dynprintf("Filename was not found on ramdisk or "
                                "on the local disk, %s", filename);

    GAME_UI_MSG_BOX("%s", popup_str);
    myfree(popup_str);
     */
    LOG("File not found \"%s\"", filename);

    if (alt_filename) {
        myfree(alt_filename);
        alt_filename = 0;
    }

    return (0);
}
