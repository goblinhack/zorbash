//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_STRING_UTILL_H_
#define _MY_STRING_UTILL_H_

//#include <iostream>
#include <memory>
#include <vector>
#include <stdarg.h>
#include <wchar.h>
#include <map>

typedef std::shared_ptr< std::vector< std::string > > shared_vector_string;
typedef std::shared_ptr< std::vector< std::wstring > > shared_vector_wstring;

extern size_t
strlcpy_(char * dst, const char * src, size_t size);

extern size_t
strlcat_(char * dst, const char * src, size_t size);

//
// Max long string size
//
#define MAXSTR                          1024
#define MAXSHORTSTR                     256

std::wstring string_to_wstring(const std::string& s);
std::string wstring_to_string(const std::wstring& s);
std::string ws_to_utf8(std::wstring const& s);
std::wstring utf8_to_ws(std::string const& utf8);

void strrepc(char *s, const char *replace_set, char replace_with);
char *strappend(const char *in, const char *append);
char *strprepend(const char *in, const char *prepend);
uint32_t strcommon(const char *a, const char *b);
void strchop(char *s);
void strchopc(char *s, char c);
int32_t strisregexp(const char *in);
void strnoescape(char *uncompressed);
char *dynprintf(const char *fmt, ...);
char *dynvprintf(const char *fmt, va_list args);
std::string mybasename(const char *in, const char *who);
void hexdump(const unsigned char *addr, size_t len);
char *strcasestr_(const char *s, const char *find);

shared_vector_string split(const char *in, uint32_t max_line_len);
shared_vector_string split(const std::string &, uint32_t max_line_len);
shared_vector_wstring split(const std::wstring &, uint32_t max_line_len);
extern std::vector<std::string> split_tokens(const std::string &s,
                                             const char delimiter);
int32_t snprintf_realloc(char **str, int32_t *size, int32_t *used,
                         const char *fmt, ...);

std::string& ltrim(std::string& s);
std::string& rtrim(std::string& s);
std::string& trim(std::string& s);
std::string ltrim_ws(const std::string& s);
std::string rtrim_ws(const std::string& s);
std::string trim_ws(const std::string& s);

std::wstring& ltrim(std::wstring& s);
std::wstring& rtrim(std::wstring& s);
std::wstring& trim(std::wstring& s);
std::wstring ltrim_ws(const std::wstring& s);
std::wstring rtrim_ws(const std::wstring& s);
std::wstring trim_ws(const std::wstring& s);
std::string& string_timestamp(void);
#endif
