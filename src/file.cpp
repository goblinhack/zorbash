//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#if defined(__linux__)
#include <sys/errno.h>
#endif
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "my_main.h"
#include "my_file.h"

unsigned char *file_read (const char *filename, int32_t *out_len)
{_
    unsigned char *buffer;
    FILE *file;
    int32_t len;

    file = fopen(filename, "rb");
    if (!file) {
        fprintf(MY_STDERR, "Failed to open file \"%s\" for reading: %s\n",
                filename, strerror(errno));
        return (0);
    }

    /*
     * Get the file size.
     */
    if (fseek(file, 0, SEEK_END)) {
        fprintf(MY_STDERR, "Failed to seek end of file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (0);
    }

    len = (uint32_t)ftell(file);
    if (len == -1) {
        fprintf(MY_STDERR, "Failed to get size of file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (0);
    }

    if (fseek(file, 0, SEEK_SET)) {
        fprintf(MY_STDERR, "Failed to seek begin of file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (0);
    }

    buffer = (unsigned char *)mymalloc(len + sizeof((char)'\0'),
                                       "file read");
    if (!buffer) {
        fprintf(MY_STDERR, "Failed to alloc mem for file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (0);
    }

    if (!fread(buffer, len, 1, file)) {
        fprintf(MY_STDERR, "Failed to read file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (0);
    }

    if (out_len) {
        *out_len = len;
    }

    LOG("- read %s, %dMb, %d bytes", filename, len / (1024 * 1024), len);

    fclose(file);

    return (buffer);
}

int32_t file_write (const char *filename, unsigned char *buffer, int32_t len)
{_
    FILE *file;
    uint8_t rc;

    file = fopen(filename, "w");
    if (!file) {
        fprintf(MY_STDERR, "Failed to open file \"%s\" for writing: %s\n",
                filename, strerror(errno));
        return (-1);
    }

    rc = fwrite(buffer, len, 1, file);

    LOG("Saved %s, %d bytes", filename, len);

    /*
     * Check written one object.
     */
    if (!rc) {
        fprintf(MY_STDERR, "Failed to write file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (-1);
    }

    if (ferror(file)) {
        fprintf(MY_STDERR, "Error writing to write file \"%s\": %s\n",
                filename, strerror(errno));
        fclose(file);
        return (-1);
    }

    fclose(file);
    return (0);
}

/*
 * Does the requested file exist?
 */
uint8_t file_exists (const char *filename)
{_
    struct stat buf;

    if (stat(filename, &buf) >= 0) {
        if (S_ISDIR(buf. st_mode)) {
            return (0);
        }

        return (1);
    }
    return (0);
}

unsigned char *file_read_if_exists (const char *filename, int32_t *out_len)
{_
#if 0
    unsigned char *ret;
    char *mz_filename;

    if (!filename) {
        return (0);
    }

    if (strstr(filename, ".mz")) {
        ret = mzip_file_read(filename, out_len);
        return (ret);
    }

    mz_filename = strappend(filename, ".mz");
    if (!mz_filename) {
        return (0);
    }

    if (file_exists(mz_filename)) {
        ret = mzip_file_read(mz_filename, out_len);
        myfree(mz_filename);
        return (ret);
    }

    myfree(mz_filename);
#endif

    if (file_exists(filename)) {
        return (file_read(filename, out_len));
    }

    return (0);
}

/*
 * How large is the file?
 */
int32_t file_size (const char *filename)
{_
    struct stat buf;

    if (stat(filename, &buf) >= 0) {
        return (int32_t)(buf.st_size);
    }

    return (-1);
}

/*
 * Does the requested file exist?
 */
uint8_t file_non_zero_size_exists (const char *filename)
{_
    if (!file_exists(filename)) {
        return (0);
    }

    if (!file_size(filename)) {
        return (0);
    }

    return (1);
}

/*
 * Remove the file if it exists.
 */
uint8_t file_unlink (const char *filename)
{_
    if (!file_exists(filename)) {
        return (0);
    }

    unlink(filename);

    return (1);
}

/*
 * Modification time.
 */
double file_age (const char *filename)
{_
    struct stat buf;

    if (stat(filename, &buf) < 0) {
        return (-1);
    }

    time_t now = time(0);

    return (difftime(now, buf.st_mtime));
}

/*
 * If the first filename newer than the second ?
 */
uint8_t file_exists_and_is_newer_than (const char *filename1,
                                       const char *filename2)
{_
    struct stat buf1;
    struct stat buf2;
    double delta;

    if (stat(filename1, &buf1) < 0) {
        return (false);
    }

    if (stat(filename2, &buf2) < 0) {
        return (false);
    }

    delta = difftime(buf1.st_mtime, buf2.st_mtime);

    return (delta > 0);
}
