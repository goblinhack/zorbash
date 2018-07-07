/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_STRING_UTILL_H_
#define _MY_STRING_UTILL_H_

#include "my_main.h"
#include "my_enum.h"

#include <stdarg.h>
#include <wchar.h>

std::wstring string_to_wstring(const std::string& s);
std::string wstring_to_string(const std::wstring& s);

void strrepc(char *s, const char *replace_set, char replace_with);
char *substr(const char *in, int32_t pos, int32_t len);
char *strappend(const char *in, const char *append);
char *strprepend(const char *in, const char *prepend);
char *strsub(const char *in, const char *remove, const char *replace_with);
uint32_t strcommon(const char *a, const char *b);
void strchop(char *s);
void strchopc(char *s, char c);
int32_t strisregexp(const char *in);
void strnoescape(char *uncompressed);
char *dynprintf(const char *fmt, ...);
char *dynvprintf(const char *fmt, va_list args);
std::string mybasename(const char *in, const char *who);
uint8_t hex_dump(void *addr, uint64_t offset, uint64_t len);
uint8_t hex_dump_log(void *addr, uint64_t offset, uint64_t len);
char *strcasestr_(const char *s, const char *find);
void itoa05(char *string, unsigned int value);

shared_vector_string split(const char *in, uint32_t max_line_len);
shared_vector_string split(const std::string &, uint32_t max_line_len);
shared_vector_wstring split(const std::wstring &, uint32_t max_line_len);
tpp string2tp(const char **s);
tpp string2tp(std::string &s, int *len);
tpp string2tp(std::wstring &s, int *len);
int32_t snprintf_realloc(char **str, int32_t *size, int32_t *used,
                         const char *fmt, ...);

std::string string_sprintf(const char *format, ...) __attribute__ ((format (printf, 1, 2)));
#endif
