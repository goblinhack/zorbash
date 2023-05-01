//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <algorithm> // do not remove
#include <iostream>  // do not remove
#include <libgen.h>  // do not remove
#include <sstream>   // do not remove
#include <string>    // do not remove

#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_tex.hpp"
#include "my_thing_template.hpp"

std::wstring string_to_wstring(const std::string &s);
std::string  wstring_to_string(const std::wstring &s);

std::wstring string_to_wstring(const std::string &s)
{
  std::wstring temp(s.length(), L' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

std::string wstring_to_string(const std::wstring &s)
{
  std::string temp(s.length(), ' ');
  std::copy(s.begin(), s.end(), temp.begin());
  return temp;
}

/*
 * Replace chars in replace_set with replace_with.
 */
void strrepc(char *s, const char *replace_set, char replace_with)
{
  TRACE_NO_INDENT();
  char *c;

  for (c = s; *c; c++) {
    if (strchr(replace_set, *c)) {
      *c = replace_with;
    }
  }
}

/*
 * return a part of a string.
 *
 * substr("foo.zip", -4, 4) -> "zip"
 */
#if 0
static char *substr (const char *in, int pos, int len)
{ TRACE_NO_INDENT();
  int slen;
  char *out;

  if (!in) {
    return 0;
  }

  slen = (uint32_t)strlen(in);

  /*
   * Negative positions from the end.
   */
  if (pos < 0) {
    pos = slen + pos;
  }

  if (pos < 0) {
    pos = 0;
  }

  if (len < 0) {
    len = 0;
  }

  if (pos > slen) {
    pos = slen;
  }

  if (len > slen - pos) {
    len = slen - pos;
  }

  out = (__typeof__(out)) mymalloc(len + sizeof((char)'\0'), "substr");
  if (!out) {
    return 0;
  }

  memcpy(out, &(in[pos]), len);
  out[len] = '\0';

  return out;
}
#endif

//
// Recursively replace part of a string with another.
//
// strsub("foo.zip", ".zip", ""); -> "foo"
//
char *strsub_(const char *in, const char *look_for, const char *replace_with, const char *what, const char *file,
              const char *func, int line)
{
  TRACE_NO_INDENT();
  char       *buf;
  const char *at;
  int         newlen;
  int         oldlen;
  int         len;

  if (! in || ! look_for || ! replace_with) {
    return nullptr;
  }

  // printf("in %s\n", in);
  // printf("  look for %s\n", look_for);
  // printf("  replace  %s\n", replace_with);
  at = strstr(in, look_for);
  if (! at) {
    buf = dupstr(in, what);
    return buf;
  }

  oldlen = (uint32_t) strlen(look_for);
  newlen = (uint32_t) strlen(replace_with);

  len = (uint32_t) strlen(in) - oldlen + newlen;
  buf = (__typeof__(buf)) myzalloc_(len + sizeof((char) '\0'), what, file, func, line);
  if (! buf) {
    return nullptr;
  }

  *buf = '\0';
  strlcpy_(buf, in, at - in + 1);
  strcat(buf, replace_with);
  strcat(buf, at + oldlen);

  if (! strcmp(buf, in)) {
    return buf;
  }

  auto out = strsub_(buf, look_for, replace_with, what, file, func, line);
  myfree(buf);
  return out;
}

/*
 * Add onto the end of a string.
 *
 * strappend("foo", ".zip"); -> "foo.zip"
 */
char *strappend(const char *in, const char *append)
{
  TRACE_NO_INDENT();
  char *buf;
  int   newlen;
  int   len;

  if (! in || ! append) {
    return nullptr;
  }

  newlen = (uint32_t) strlen(append);
  len    = (uint32_t) strlen(in) + newlen;
  buf    = (__typeof__(buf)) myzalloc(len + sizeof((char) '\0'), "strappend");
  if (! buf) {
    return nullptr;
  }

  strcpy(buf, in);
  strcat(buf, append);

  return buf;
}

/*
 * Add onto the start of a string.
 *
 * strprepend("foo", "bar"); -> "barfoo"
 */
char *strprepend(const char *in, const char *prepend)
{
  TRACE_NO_INDENT();
  char *buf;
  int   newlen;
  int   len;

  if (! in || ! prepend) {
    return nullptr;
  }

  newlen = (uint32_t) strlen(prepend);
  len    = (uint32_t) strlen(in) + newlen;
  buf    = (__typeof__(buf)) myzalloc(len + sizeof((char) '\0'), "strprepend");
  if (! buf) {
    return nullptr;
  }

  strcpy(buf, prepend);
  strcat(buf, in);

  return buf;
}

/*
 * Return the common matching length of two strings.
 */
uint32_t strcommon(const char *a, const char *b)
{
  TRACE_NO_INDENT();
  const char *o;

  o = a;

  while ((*a == *b) && *a) {
    a++;
    b++;
  }

  return (uint32_t) (a - o);
}

/*
 * Removes trailing whitespace.
 */
void strchop(char *s)
{
  TRACE_NO_INDENT();
  uint32_t size;
  char    *end;

  size = (uint32_t) strlen(s);
  if (! size) {
    return;
  }

  end = s + size - 1;
  while ((end >= s) && (*end == ' ')) {
    end--;
  }

  *(end + 1) = '\0';
}

/*
 * Removes trailing characters.
 */
void strchopc(char *s, char c)
{
  TRACE_NO_INDENT();
  uint32_t size;
  char    *end;

  size = (uint32_t) strlen(s);
  if (! size) {
    return;
  }

  end = s + size - 1;
  while ((end >= s) && (*end == c)) {
    end--;
  }

  *(end + 1) = '\0';
}

int strisregexp(const char *in)
{
  TRACE_NO_INDENT();
  const char *a = in;
  char        c;

  while ((c = *a++)) {
    switch (c) {
      case '[' : return 1;
      case ']' : return 1;
      case '{' : return 1;
      case '}' : return 1;
      case '+' : return 1;
      case '$' : return 1;
      case '^' : return 1;
      case '-' : return 1;
      case '*' : return 1;
    }
  }

  return false;
}

size_t strlcpy_(char *dst, const char *src, size_t max_len)
{
  TRACE_NO_INDENT();
  size_t srclen = strlen(src);
  if (max_len > 0) {
    uint32_t len = std::min(srclen, max_len - 1);
    memcpy(dst, src, len);
    dst[ len ] = '\0';
  }
  return srclen;
}

size_t strlcat_(char *dst, const char *src, size_t max_len)
{
  TRACE_NO_INDENT();
  uint32_t dstlen = strlen(dst);
  uint32_t srclen = strlen(src);
  if (dstlen < max_len) {
    strlcpy_(dst + dstlen, src, max_len - dstlen);
  }
  return (dstlen + srclen);
}

/*
 * Shrink a string by the space needed for its escape characters.
 */
void strnoescape(char *uncompressed)
{
  TRACE_NO_INDENT();
  char *t = uncompressed;
  char *s = uncompressed;
  char  c;

  while ((c = *s++)) {
    if (c != '\\') {
      *t++ = c;
      continue;
    }

    switch (*s++) {
      case 'n' : *t++ = '\n'; break;
      case 't' : *t++ = '\t'; break;
      case '%' : *t++ = '%'; break;
      case '#' : *t++ = '@'; break;
      case '\"' : *t++ = '\"'; break;
      case '\'' : *t++ = '\''; break;
      case '\\' : *t++ = '\\'; break;
      default :
        {
          char *o = s - 1;
          char  orig;

          while (isdigit(*s)) {
            s++;
          }

          orig = *s;
          *s   = '\0';
          *t++ = atoi(o);
          *s   = orig;
          break;
        }
    }
  }
  *t = '\0';
}

static const char *dynvprintf_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  static char buf[ MAXSTR ];

  buf[ 0 ] = '\0';
  vsnprintf(buf, MAXSTR, fmt, args);

  return buf;
}

/*
 * dynamically allocate a printf formatted string. e.g.
 * dynprintf("%sbar", "foo"); => "foobar"
 */
char *dynprintf(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  const char *ret;
  va_list     args;

  va_start(args, fmt);
  ret = dynvprintf_(fmt, args);
  va_end(args);

  return (dupstr(ret, __FUNCTION__));
}

char *dynvprintf(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  static char buf[ MAXSTR ];

  buf[ 0 ] = '\0';
  vsnprintf(buf, MAXSTR, fmt, args);

  return (dupstr(buf, __FUNCTION__));
}

/*
 * mybasename
 *
 * A safe wrapper for basename to avoid modifications to the input string.
 */
std::string mybasename(const char *in, const char *who)
{
  TRACE_NO_INDENT();
  char       *tmp = dupstr(in, who);
  std::string tmp2(basename(tmp));
  myfree(tmp);

  return (tmp2);
}

/*-
 * Copyright (c) 1990, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Find the first occurrence of find in s, ignore case.
 */
char *strcasestr_(const char *s, const char *find)
{
  TRACE_NO_INDENT();
  char   c, sc;
  size_t len;

  if ((c = *find++) != 0) {
    c   = tolower((unsigned char) c);
    len = strlen(find);
    do {
      do {
        if ((sc = *s++) == 0)
          return nullptr;
      } while ((char) tolower((unsigned char) sc) != c);
    } while (strncasecmp(s, find, len) != 0);
    s--;
  }
  return ((char *) s);
}

/*
 * Split a string "like\nthis" into "like" and "this".
 */
shared_vector_string split(const char *text, int max_line_len)
{
  TRACE_NO_INDENT();
  uint8_t           found_format_string;
  const char       *line_start;
  const char       *line_end;
  int               line_len;
  char              c;
  const char *const text_start = text;

  if (! text) {
    return nullptr;
  }

  auto result = std::make_shared< std::vector< std::string > >();

  for (; /*ever*/;) {
    line_len   = 0;
    line_start = text;

    /*
     * The first newline is used as a split char. Two newlines means one
     * of them is forced.
     */
    if (text != text_start) {
      if (*text == '\n') {
        text++;
      }
    }

    while (*text == ' ') {
      text++;
    }

    /*
     * Read in as much of the line we can up to the line length.
     */
    found_format_string = false;

    while (line_len < max_line_len) {
      c = *text;
      if ((c == '\n') || (c == '\0')) {
        break;
      }
      line_len++;

      if (! found_format_string) {
        if (c == '%') {
          found_format_string = true;
        }
      } else if (found_format_string) {
        if (! strncmp(text, "fg=", 3)) {
          text += 3;
          line_len -= 2; /* for the %% */
          (void) string2color(&text);
          found_format_string = false;
          continue;
        }
        if (! strncmp(text, "tp=", 3)) {
          text += 3;
          line_len -= 2; /* for the %% */
          (void) string2tp(&text);
          found_format_string = false;
          continue;
        }
        if (! strncmp(text, "tex=", 4)) {
          text += 4;
          line_len -= 2; /* for the %% */
          (void) string2tex(&text);
          found_format_string = false;
          continue;
        }
        if (! strncmp(text, "tile=", 5)) {
          text += 5;
          line_len -= 2; /* for the %% */
          (void) string2tile(&text);
          found_format_string = false;
          continue;
        }
        if (c == '%') {
          line_len -= 1;
        } else {
          found_format_string = false;
          text--;
        }
      }

      text++;
    }

    line_end = text;

    /*
     * Step back looking for a word break.
     */
    if (line_len >= max_line_len) {
      while ((line_end > line_start) && ((*line_end != ' ') && (*line_end != '\0') && (*line_end != '\n'))) {
        line_end--;
      }
    }

    while (line_end > line_start) {
      if (*(line_end - 1) == ' ') {
        line_end--;
        continue;
      }
      break;
    }

    if (line_end == line_start) {
      line_end = text;
    }

    /*
     * Skip leading junk.
     */
    while (line_start < line_end) {
      if ((*line_start == '\n')) {
        line_start++;
        continue;
      }

      if (*line_start == ' ') {
        line_start++;
        continue;
      }
      break;
    }

    line_len = (int) (line_end - line_start);
    char tmp[ line_len + 1 ];
    strlcpy_(tmp, line_start, line_len + 1);

    result->push_back(tmp);

    text = line_end;
    if (! *text) {
      break;
    }

    if (text == text_start) {
      if (line_len == 0) {
        text++;
      }
    }
  }

  return result;
}

shared_vector_string split(const std::string &text, int max_line_len)
{
  TRACE_NO_INDENT();
  uint8_t found_format_string;
  int     line_len;
  char    c;
  auto    text_start = text.begin();
  auto    text_iter  = text_start;
  auto    line_start = text_start;
  auto    line_end   = text_start;

  if (max_line_len < 0) {
    DIE("bad max line len");
  }

  if (! text.length()) {
    return nullptr;
  }

  // printf("SPLIT1 [%s] max_line_len %d\n", text.c_str(), max_line_len);

  auto result = std::make_shared< std::vector< std::string > >();

  for (; /*ever*/;) {
    line_len   = 0;
    line_start = text_iter;

    /*
     * The first newline is used as a split char. Two newlines means one
     * of them is forced.
     */
    if (text_iter != text_start) {
      if (*text_iter == '\n') {
        text_iter++;
      }
    }

    while (*text_iter == ' ') {
      text_iter++;
    }

    /*
     * Read in as much of the line we can up to the line length.
     */
    found_format_string = false;

    while (line_len < max_line_len) {
      c = *text_iter;
      if ((c == '\n') || (c == '\0')) {
        break;
      }
      line_len++;

      if (! found_format_string) {
        if (c == '%') {
          found_format_string = true;
        }
      } else if (found_format_string) {
        if (std::string(text_iter, text_iter + 3) == "fg=") {
          text_iter += 3;
          line_len -= 2; /* for the %% */
          auto tmp = std::string(text_iter, text.end());

          int len = 0;
          (void) string2color(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (std::string(text_iter, text_iter + 3) == "tp=") {
          text_iter += 3;
          line_len -= 2; /* for the %% */

          auto tmp = std::string(text_iter, text.end());

          int len = 0;
          (void) string2tp(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (std::string(text_iter, text_iter + 4) == "tex=") {
          text_iter += 4;
          line_len -= 2; /* for the %% */
          auto tmp = std::string(text_iter, text.end());

          int len = 0;
          (void) string2tex(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (std::string(text_iter, text_iter + 5) == "tile=") {
          text_iter += 5;
          line_len -= 2; /* for the %% */
          auto tmp = std::string(text_iter, text.end());

          int len = 0;
          (void) string2tile(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (c == '%') {
          line_len -= 1;
        } else {
          found_format_string = false;
          text_iter--;
        }
      }

      text_iter++;
      // printf("LEN %d [%c]\n", line_len, c);
    }
    // printf("END line_len %d\n", line_len);

    line_end = text_iter;

    /*
     * Step back looking for a word break.
     */
    if (line_len >= max_line_len) {
      while ((line_end > line_start) && ((*line_end != ' ') && (*line_end != '\0') && (*line_end != '\n'))) {
        line_end--;
      }
    }

    while (line_end > line_start) {
      if (*(line_end - 1) == ' ') {
        line_end--;
        continue;
      }
      break;
    }

    if (line_end == line_start) {
      line_end = text_iter;
    }

    /*
     * Skip leading junk.
     */
    while (line_start < line_end) {
      if (*line_start == '\n') {
        line_start++;
        continue;
      }

      if (*line_start == ' ') {
        line_start++;
        continue;
      }
      break;
    }

    line_len = (int) (line_end - line_start);
    auto tmp = std::string(line_start, line_start + line_len);

    // printf("OUT [%s] max_line_len %d\n", tmp.c_str(), line_len);
    result->push_back(tmp);

    text_iter = line_end;
    if (! *text_iter) {
      break;
    }

    if (text_iter == text_start) {
      if (line_len == 0) {
        text_iter++;
      }
    }
  }

  return result;
}

shared_vector_wstring split(const std::wstring &text, int max_line_len)
{
  TRACE_NO_INDENT();
  uint8_t found_format_string;
  int     line_len;
  char    c;
  auto    text_start = text.begin();
  auto    text_iter  = text_start;
  auto    line_start = text_start;
  auto    line_end   = text_start;

  if (! text.length()) {
    return nullptr;
  }
  // printf("SPLIT2 [%s] max_line_len %d\n", wstring_to_string(text).c_str(),
  // max_line_len);

  auto result = std::make_shared< std::vector< std::wstring > >();

  for (; /*ever*/;) {
    line_len   = 0;
    line_start = text_iter;

    /*
     * The first newline is used as a split char. Two newlines means one
     * of them is forced.
     */
    if (text_iter != text_start) {
      if (*text_iter == '\n') {
        text_iter++;
      }
    }

    while (*text_iter == ' ') {
      text_iter++;
    }

    /*
     * Read in as much of the line we can up to the line length.
     */
    found_format_string = false;

    while (line_len < max_line_len) {
      c = *text_iter;
      if ((c == '\n') || (c == '\0')) {
        break;
      }
      line_len++;

      if (! found_format_string) {
        if (c == '%') {
          found_format_string = true;
        }
      } else if (found_format_string) {
        if (std::wstring(text_iter, text_iter + 3) == L"fg=") {
          text_iter += 3;
          line_len -= 2; /* for the %% */
          auto tmp = std::wstring(text_iter, text.end());

          int len = 0;
          (void) string2color(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (std::wstring(text_iter, text_iter + 3) == L"tp=") {
          text_iter += 3;
          line_len -= 2; /* for the %% */
          auto tmp = std::wstring(text_iter, text.end());

          int len = 0;
          (void) string2tp(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (std::wstring(text_iter, text_iter + 4) == L"tex=") {
          text_iter += 4;
          line_len -= 2; /* for the %% */
          auto tmp = std::wstring(text_iter, text.end());

          int len = 0;
          (void) string2tex(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (std::wstring(text_iter, text_iter + 5) == L"tile=") {
          text_iter += 5;
          line_len -= 2; /* for the %% */
          auto tmp = std::wstring(text_iter, text.end());

          int len = 0;
          (void) string2tile(tmp, &len);
          text_iter += len + 1;

          found_format_string = false;
          continue;
        }
        if (c == '%') {
          line_len -= 1;
        } else {
          found_format_string = false;
          text_iter--;
        }
      }

      text_iter++;
    }

    line_end = text_iter;

    /*
     * Step back looking for a word break.
     */
    if (line_len >= max_line_len) {
      while ((line_end > line_start) && ((*line_end != ' ') && (*line_end != '\0') && (*line_end != '\n'))) {
        line_end--;
      }
    }

    while (line_end > line_start) {
      if (*(line_end - 1) == ' ') {
        line_end--;
        continue;
      }
      break;
    }

    if (line_end == line_start) {
      line_end = text_iter;
    }

    /*
     * Skip leading junk.
     */
    while (line_start < line_end) {
      if (*line_start == '\n') {
        line_start++;
        continue;
      }

      if (*line_start == ' ') {
        line_start++;
        continue;
      }
      break;
    }

    line_len = (int) (line_end - line_start);
    auto tmp = std::wstring(line_start, line_start + line_len);

    // printf("OUT [%s] max_line_len %d\n", wstring_to_string(tmp).c_str(),
    // line_len);
    result->push_back(tmp);

    text_iter = line_end;
    if (! *text_iter) {
      break;
    }

    if (text_iter == text_start) {
      if (line_len == 0) {
        text_iter++;
      }
    }
  }

  return result;
}

int length_without_format(const std::string &text)
{
  TRACE_NO_INDENT();
  uint8_t found_format_string;
  char    c;
  auto    text_start = text.begin();
  auto    text_iter  = text_start;
  int     line_len   = 0;

  found_format_string = false;

  for (;;) {
    c = *text_iter;
    if (! c) {
      break;
    }
    line_len++;

    if (! found_format_string) {
      if (c == '%') {
        found_format_string = true;
      }
    } else if (found_format_string) {
      if (std::string(text_iter, text_iter + 3) == "fg=") {
        text_iter += 3;
        line_len -= 2; /* for the %% */
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2color(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "tp=") {
        text_iter += 3;
        line_len -= 2; /* for the %% */

        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tp(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 4) == "tex=") {
        text_iter += 4;
        line_len -= 2; /* for the %% */
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tex(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 5) == "tile=") {
        text_iter += 5;
        line_len -= 2; /* for the %% */
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tile(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (c == '%') {
        line_len -= 1;
      } else {
        found_format_string = false;
        text_iter--;
      }
    }

    text_iter++;
    // printf("LEN %d [%c]\n", line_len, c);
  }
  // printf("END line_len %d\n", line_len);

  return line_len;
}

int length_without_format(const std::wstring &text)
{
  TRACE_NO_INDENT();
  uint8_t found_format_string;
  char    c;
  auto    text_start = text.begin();
  auto    text_iter  = text_start;
  int     line_len   = 0;

  found_format_string = false;

  for (;;) {
    c = *text_iter;
    if (! c) {
      break;
    }
    line_len++;

    if (! found_format_string) {
      if (c == '%') {
        found_format_string = true;
      }
    } else if (found_format_string) {
      if (std::string(text_iter, text_iter + 3) == "fg=") {
        text_iter += 3;
        line_len -= 2; /* for the %% */
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2color(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 3) == "tp=") {
        text_iter += 3;
        line_len -= 2; /* for the %% */

        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tp(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 4) == "tex=") {
        text_iter += 4;
        line_len -= 2; /* for the %% */
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tex(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (std::string(text_iter, text_iter + 5) == "tile=") {
        text_iter += 5;
        line_len -= 2; /* for the %% */
        auto tmp = std::string(text_iter, text.end());

        int len = 0;
        (void) string2tile(tmp, &len);
        text_iter += len + 1;

        found_format_string = false;
        continue;
      }
      if (c == '%') {
        line_len -= 1;
      } else {
        found_format_string = false;
        text_iter--;
      }
    }

    text_iter++;
    // printf("LEN %d [%c]\n", line_len, c);
  }
  // printf("END line_len %d\n", line_len);

  return line_len;
}

Tpp string2tp(const char **s)
{
  TRACE_NO_INDENT();
  static char        tmp[ MAXSHORTSTR ];
  static const char *eo_tmp = tmp + MAXSHORTSTR;
  const char        *c      = *s;
  char              *t      = tmp;

  while (t < eo_tmp) {
    if ((*c == '\0') || (*c == '$')) {
      break;
    }

    *t++ = *c++;
  }

  if (c == eo_tmp) {
    ERR("Tp name %s is too long", tmp);
    return nullptr;
  }

  *t++ = '\0';
  *s += (t - tmp);

  Tpp tp = tp_find(tmp);
  if (unlikely(! tp)) {
    ERR("Tp name [%s] not found", tmp);
  }

  return tp;
}

Tpp string2tp(const std::string &s, int *len)
{
  TRACE_NO_INDENT();
  auto        iter = s.begin();
  std::string out;

  while (iter != s.end()) {
    auto c = *iter;

    if ((c == '\0') || (c == '$')) {
      break;
    }

    out += c;
    iter++;
  }

  if (len) {
    *len = iter - s.begin();
  }

  if (iter == s.end()) {
    ERR("Tp name %s is too long", out.c_str());
    return nullptr;
  }

  Tpp tp = tp_find(out);
  if (unlikely(! tp)) {
    ERR("Tp name [%s] not found", out.c_str());
  }

  return tp;
}

Tpp string2tp(const std::wstring &s, int *len)
{
  TRACE_NO_INDENT();
  auto v = wstring_to_string(s);
  return (string2tp(v, len));
}

/*
 * size, the returned size of the buffer. Can be given initially to force
 * alloc of a given buffer size. Else a default size is used.
 *
 * used, optional pointer to avoid the need to do strlen when appending to the
 * string.
 *
 * str, returned pointer for the new string
 *
 * returns 0 on success
 */
int snprintf_realloc(char **str, int *size, int *used, const char *fmt, ...)
{
  TRACE_NO_INDENT();
  int     freespace;
  int     needspace;
  int     usedspace;
  va_list ap;
  char   *tmp;

  if (! str) {
    return (-1);
  }

  if (! size) {
    return (-1);
  }

  if (! *str) {
    if (! *size) {
      *size = 128;
    }

    if (used) {
      *used = 0;
    }

    *str = (char *) mymalloc(*size, "snprintf alloc");
    if (! *str) {
      *size = 0;
      return (-1);
    }

    *str[ 0 ] = '\0';
  }

  if (! used || ! *used) {
    usedspace = (uint32_t) strlen(*str);
  } else {
    usedspace = *used;
  }

  char add[ MAXSTR ];
  va_start(ap, fmt);
  vsnprintf(add, sizeof(add) - 1, fmt, ap);
  va_end(ap);
  add[ MAXSHORTSTR - 1 ] = '\0';

  needspace = strlen(add);

  for (; /*ever*/;) {
    freespace = *size - usedspace;

    if (needspace < freespace) {
      if (used) {
        *used += needspace;
      }
      strcat(*str, add);

      return 0;
    }

    (*size) *= 2;

    tmp = (char *) myrealloc(*str, *size, "snprintf realloc");
    if (! tmp) {
      free(*str);
      *str  = nullptr;
      *size = 0;
      return (-1);
    }

    *str = tmp;
  }
}

std::vector< std::string > split_tokens(const std::string &s, const char delimiter)
{
  std::string                token;
  std::istringstream         s_stream(s);
  std::vector< std::string > tokens;
  while (std::getline(s_stream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
std::string &ltrim(std::string &s)
{
  auto it
      = std::find_if(s.begin(), s.end(), [](char c) { return ! std::isspace< char >(c, std::locale::classic()); });
  s.erase(s.begin(), it);
  return s;
}

std::string &rtrim(std::string &s)
{
  auto it
      = std::find_if(s.rbegin(), s.rend(), [](char c) { return ! std::isspace< char >(c, std::locale::classic()); });
  s.erase(it.base(), s.end());
  return s;
}

std::string &trim(std::string &s) { return ltrim(rtrim(s)); }

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim_ws(const std::string &s)
{
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim_ws(const std::string &s)
{
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim_ws(const std::string &s) { return rtrim_ws(ltrim_ws(s)); }

std::wstring &ltrim(std::wstring &s)
{
  auto it
      = std::find_if(s.begin(), s.end(), [](char c) { return ! std::isspace< char >(c, std::locale::classic()); });
  s.erase(s.begin(), it);
  return s;
}

std::wstring &rtrim(std::wstring &s)
{
  auto it
      = std::find_if(s.rbegin(), s.rend(), [](char c) { return ! std::isspace< char >(c, std::locale::classic()); });
  s.erase(it.base(), s.end());
  return s;
}

std::wstring &trim(std::wstring &s) { return ltrim(rtrim(s)); }

const std::wstring LWHITESPACE = L" \n\r\t\f\v";

std::wstring ltrim_ws(const std::wstring &s)
{
  size_t start = s.find_first_not_of(LWHITESPACE);
  return (start == std::wstring::npos) ? L"" : s.substr(start);
}

std::wstring rtrim_ws(const std::wstring &s)
{
  size_t end = s.find_last_not_of(LWHITESPACE);
  return (end == std::wstring::npos) ? L"" : s.substr(0, end + 1);
}

std::wstring trim_ws(const std::wstring &s) { return rtrim_ws(ltrim_ws(s)); }

//
// Concert errno to a std::string
//
std::string strerror_to_string(const int err)
{
  static const auto MAX_ERRNO_BUF_SIZE = 1024U;
  char              err_out[ MAX_ERRNO_BUF_SIZE ];
  err_out[ 0 ] = '\0';

  //
  // Choose the correct strerror
  //
#if defined(__GLIBC__) && (_GNU_SOURCE || (_POSIX_C_SOURCE < 200112L && _XOPEN_SOURCE < 600))
  //
  // GNU version returns a string pointer
  //
  const char *str = strerror_r(errno, err_out, MAX_ERRNO_BUF_SIZE);
  if (str) {
    return std::string(str);
  }
#else
  //
  // XSI version returns 0 on success
  //
  if (! strerror_r(err, err_out, sizeof(err_out))) {
    return std::string(err_out);
  }
#endif
  return "Could not decode errno: " + std::to_string(err) + " strerror_r errno=" + std::to_string(errno);
}

//
// foo bar -> Foo Bar
//
std::string capitalise(std::string in)
{
  TRACE_NO_INDENT();
  std::string out = in;

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}

//
// Modify the input string with and change "pattern" to "replace_with" repeatedly.
//
void replace(std::string &input, const std::string &pattern, const std::string &replace_with)
{
  size_t pos = 0;
  for (;;) {
    pos = input.find(pattern, pos);
    if (pos == std::string::npos) {
      return;
    }
    input.replace(pos, pattern.length(), replace_with);
    pos += replace_with.length();
  }
}
