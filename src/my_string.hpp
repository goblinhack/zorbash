//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_STRING_UTILL_HPP_
#define _MY_STRING_UTILL_HPP_

#include <iostream>
#include <map>
#include <memory>
// REMOVED #include <stdarg.h>
#include <vector>
// REMOVED #include <wchar.h>

#include "my_format_str_attribute.hpp"

using shared_vector_string  = std::shared_ptr< std::vector< std::string > >;
using shared_vector_wstring = std::shared_ptr< std::vector< std::wstring > >;

extern size_t strlcpy_(char *dst, const char *src, size_t size);

extern size_t strlcat_(char *dst, const char *src, size_t size);

//
// Max long string size
//
#define MAXLONGSTR  4096
#define MAXSTR      1024
#define MAXSHORTSTR 128

char *dynprintf(const char *fmt, ...) CHECK_FORMAT_STR(printf, 1, 2);
char *dynvprintf(const char *fmt, va_list args);
char *strappend(const char *in, const char *append);
char *strcasestr_(const char *s, const char *find);
char *strprepend(const char *in, const char *prepend);

int length_without_format(const std::string &);
int length_without_format(const std::wstring &);

int snprintf_realloc(char **str, int *size, int *used, const char *fmt, ...);
int strisregexp(const char *in);

shared_vector_string  split(const char *in, int max_line_len);
shared_vector_string  split(const std::string &, int max_line_len);
shared_vector_wstring split(const std::wstring &, int max_line_len);

std::string   capitalise(std::string in);
std::string  &ltrim(std::string &s);
std::string   ltrim_ws(const std::string &s);
std::string   mybasename(const char *in, const char *who);
std::string  &rtrim(std::string &s);
std::string   rtrim_ws(const std::string &s);
std::string   strerror_to_string(const int err);
std::string  &trim(std::string &s);
std::string   trim_ws(const std::string &s);
std::string   ws_to_utf8(std::wstring const &s);
std::string   wstring_to_string(const std::wstring &s);
std::wstring &ltrim(std::wstring &s);
std::wstring  ltrim_ws(const std::wstring &s);
std::wstring &rtrim(std::wstring &s);
std::wstring  rtrim_ws(const std::wstring &s);
std::wstring  string_to_wstring(const std::string &s);
std::wstring &trim(std::wstring &s);
std::wstring  trim_ws(const std::wstring &s);
std::wstring  utf8_to_ws(std::string const &utf8);

uint32_t strcommon(const char *a, const char *b);
void     hexdump(const unsigned char *addr, size_t len);
void     hexdump(std::vector< unsigned char > &v);
void     strchop(char *s);
void     strchopc(char *s, char c);
void     strnoescape(char *uncompressed);
void     strrepc(char *s, const char *replace_set, char replace_with);

extern std::vector< std::string > split_tokens(const std::string &s, const char delimiter);
#endif
