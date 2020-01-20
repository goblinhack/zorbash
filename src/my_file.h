//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_FILE_H_
#define _MY_FILE_H_

unsigned char *file_read(const char *filename, int32_t *len);
int32_t file_write(const char *filename, unsigned char *buffer, int32_t len);
uint8_t file_exists(const char *filename);
unsigned char *file_read_if_exists(const char *filename, int32_t *out_len);
int32_t file_size(const char *filename);
uint8_t file_non_zero_size_exists(const char *filename);
uint8_t file_unlink(const char *filename);
double file_age(const char *filename);
uint8_t file_exists_and_is_newer_than(const char *filename,
                                      const char *filename2);

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#endif
