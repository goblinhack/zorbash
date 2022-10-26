//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FILE_HPP_
#define _MY_FILE_HPP_

#include <stdint.h>

#include "my_format_str_attribute.hpp"

int            file_write(const char *filename, unsigned char *buffer, int len);
uint8_t        file_exists(const char *filename);
int            file_size(const char *filename);
uint8_t        file_non_zero_size_exists(const char *filename);
uint8_t        file_unlink(const char *filename);
double         file_age(const char *filename);
uint8_t        file_exists_and_is_newer_than(const char *filename, const char *filename2);
unsigned char *file_load(const char *filename, int *outlen);

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#include <fcntl.h>
#include <io.h>
#define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#define SET_BINARY_MODE(file)
#endif

void FILE_LOG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
void FILE_DBG(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);

#endif
