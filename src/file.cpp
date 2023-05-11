//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_file.hpp"
#include "my_globals_extra.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_ramdisk.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include <string.h>  // do not remove
#include <strings.h> // do not remove
#include <sys/stat.h>
#include <unistd.h>

static unsigned char *file_io_read_if_exists(const char *filename, int *out_len);
static unsigned char *file_io_read(const char *filename, int *len);

unsigned char *file_load(const char *filename, int *outlen)
{
  TRACE_AND_INDENT();
  unsigned char *out;
  char          *alt_filename;

  alt_filename = nullptr;

  /*
   * If the file is on disk and is newer than the program, use that in
   * preference.
   */
  if (file_exists(filename)) {
    if (strstr(filename, "data/")) {
      if (file_exists_and_is_newer_than(filename, EXEC_FULL_PATH_AND_NAME)) {
        out = file_io_read_if_exists(filename, outlen);
        if (out) {
          FILE_LOG("Read file %s (newer than exec)", filename);
          return out;
        }
      }

      if (file_exists_and_is_newer_than(filename, ".build/file.o")) {
        out = file_io_read_if_exists(filename, outlen);
        if (out) {
          FILE_LOG("Read file %s (newer than build)", filename);
          return out;
        }
      }

      if (file_exists_and_is_newer_than(filename, "src/.build/file.o")) {
        out = file_io_read_if_exists(filename, outlen);
        if (out) {
          FILE_LOG("Read file %s (newer than src build)", filename);
          return out;
        }
      }
    } else {
      out = file_io_read_if_exists(filename, outlen);
      if (out) {
        FILE_LOG("Read file %s (exists locally)", filename);
        return out;
      }
    }
  }

  if (EXEC_DIR) {
    alt_filename = strprepend(filename, EXEC_DIR);

    if (file_exists(alt_filename)) {
      if (file_exists_and_is_newer_than(alt_filename, EXEC_FULL_PATH_AND_NAME)) {
        out = file_io_read_if_exists(alt_filename, outlen);
        if (out) {
          myfree(alt_filename);
          alt_filename = nullptr;

          return out;
        }
      }

      if (file_exists_and_is_newer_than(alt_filename, ".build/file.o")) {
        out = file_io_read_if_exists(alt_filename, outlen);
        if (out) {
          myfree(alt_filename);
          alt_filename = nullptr;

          return out;
        }
      }

      if (file_exists_and_is_newer_than(alt_filename, "src/.build/file.o")) {
        out = file_io_read_if_exists(alt_filename, outlen);
        if (out) {
          myfree(alt_filename);
          alt_filename = nullptr;

          return out;
        }
      }
    }
  }

  auto r = ramdisk_load(filename, outlen);
  if (r) {
    FILE_LOG("Read (ramdisk) %s, %dMb, %d bytes", filename, *outlen / (1024 * 1024), *outlen);

    if (alt_filename) {
      myfree(alt_filename);
      alt_filename = nullptr;
    }

    return r;
  }

  /*
   * Fallback to the disk.
   */
  out = file_io_read_if_exists(filename, outlen);
  if (out) {
    if (alt_filename) {
      myfree(alt_filename);
      alt_filename = nullptr;
    }

    return out;
  }

  out = file_io_read_if_exists(alt_filename, outlen);
  if (out) {
    if (alt_filename) {
      myfree(alt_filename);
      alt_filename = nullptr;
    }

    return out;
  }

  if (alt_filename) {
    myfree(alt_filename);
    alt_filename = nullptr;
  }

  {
    std::string alt_filename = mybasename(filename, "strip dir");

    out = file_io_read_if_exists(alt_filename.c_str(), outlen);
    if (out) {
      return out;
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
    alt_filename = nullptr;
  }

  return nullptr;
}

unsigned char *file_io_read(const char *filename, int *out_len)
{
  TRACE_AND_INDENT();
  unsigned char *buffer;
  FILE          *file;
  int            len;

  file = fopen(filename, "rb");
  if (! file) {
    fprintf(MY_STDERR, "Failed to open file \"%s\" for reading: %s\n", filename, strerror(errno));
    return nullptr;
  }

  /*
   * Get the file size.
   */
  if (fseek(file, 0, SEEK_END)) {
    fprintf(MY_STDERR, "Failed to seek end of file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return nullptr;
  }

  len = (uint) ftell(file);
  if (len == -1) {
    fprintf(MY_STDERR, "Failed to get size of file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return nullptr;
  }

  if (fseek(file, 0, SEEK_SET)) {
    fprintf(MY_STDERR, "Failed to seek begin of file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return nullptr;
  }

  buffer = (unsigned char *) mymalloc(len + sizeof((char) '\0'), "file read");
  if (! buffer) {
    fprintf(MY_STDERR, "Failed to alloc mem for file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return nullptr;
  }

  if (! fread(buffer, len, 1, file)) {
    fprintf(MY_STDERR, "Failed to read file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return nullptr;
  }

  if (out_len) {
    *out_len = len;
  }

  FILE_LOG("Read %s, %dMb, %d bytes", filename, len / (1024 * 1024), len);

  fclose(file);

  return buffer;
}

int file_write(const char *filename, unsigned char *buffer, int len)
{
  TRACE_AND_INDENT();
  FILE   *file;
  uint8_t rc;

  file = fopen(filename, "w");
  if (! file) {
    fprintf(MY_STDERR, "Failed to open file \"%s\" for writing: %s\n", filename, strerror(errno));
    return (-1);
  }

  rc = fwrite(buffer, len, 1, file);

  FILE_LOG("Saved %s, %d bytes", filename, len);

  /*
   * Check written one object.
   */
  if (! rc) {
    fprintf(MY_STDERR, "Failed to write file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return (-1);
  }

  if (ferror(file)) {
    fprintf(MY_STDERR, "Error writing to write file \"%s\": %s\n", filename, strerror(errno));
    fclose(file);
    return (-1);
  }

  fclose(file);
  return 0;
}

/*
 * Does the requested file exist?
 */
uint8_t file_exists(const char *filename)
{
  TRACE_AND_INDENT();
  struct stat buf;

  if (stat(filename, &buf) >= 0) {
    if (S_ISDIR(buf.st_mode)) {
      return 0;
    }

    return 1;
  }
  return 0;
}

unsigned char *file_io_read_if_exists(const char *filename, int *out_len)
{
  TRACE_AND_INDENT();
#if 0
  unsigned char *ret;
  char *mz_filename;

  if (!filename) {
    return 0;
  }

  if (strstr(filename, ".mz")) {
    ret = mzip_file_read(filename, out_len);
    return ret;
  }

  mz_filename = strappend(filename, ".mz");
  if (!mz_filename) {
    return 0;
  }

  if (file_exists(mz_filename)) {
    ret = mzip_file_read(mz_filename, out_len);
    myfree(mz_filename);
    return ret;
  }

  myfree(mz_filename);
#endif

  if (file_exists(filename)) {
    return (file_io_read(filename, out_len));
  }

  return nullptr;
}

/*
 * How large is the file?
 */
int file_size(const char *filename)
{
  TRACE_AND_INDENT();
  struct stat buf;

  if (stat(filename, &buf) >= 0) {
    return int(buf.st_size);
  }

  return (-1);
}

/*
 * Does the requested file exist?
 */
uint8_t file_non_zero_size_exists(const char *filename)
{
  TRACE_AND_INDENT();
  if (! file_exists(filename)) {
    return 0;
  }

  if (! file_size(filename)) {
    return 0;
  }

  return 1;
}

/*
 * Remove the file if it exists.
 */
uint8_t file_unlink(const char *filename)
{
  TRACE_AND_INDENT();
  if (! file_exists(filename)) {
    return 0;
  }

  unlink(filename);

  return 1;
}

/*
 * Modification time.
 */
double file_age(const char *filename)
{
  TRACE_AND_INDENT();
  struct stat buf;

  if (stat(filename, &buf) < 0) {
    return (-1);
  }

  time_t now = time(nullptr);

  return (difftime(now, buf.st_mtime));
}

/*
 * If the first filename newer than the second ?
 */
uint8_t file_exists_and_is_newer_than(const char *filename1, const char *filename2)
{
  TRACE_AND_INDENT();
  struct stat buf1;
  struct stat buf2;
  double      delta;

  if (stat(filename1, &buf1) < 0) {
    return false;
  }

  if (stat(filename2, &buf2) < 0) {
    return false;
  }

  delta = difftime(buf1.st_mtime, buf2.st_mtime);

  return (delta > 0);
}
