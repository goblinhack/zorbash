//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_sprintf.hpp"
#include <stdarg.h>

// https://stackoverflow.com/questions/40159892/using-asprintf-on-windows
#include <stdarg.h> /* needed for va_list */
#include <stdio.h>  /* needed for vsnprintf */
#include <stdlib.h> /* needed for malloc-free */

#ifndef _vscprintf
/* For some reason, MSVC fails to honour this #ifndef. */
/* Hence function renamed to _vscprintf_so(). */
static int _vscprintf_so(const char *format, va_list pargs)
{
  int     retval;
  va_list argcopy;
  va_copy(argcopy, pargs);
  retval = vsnprintf(nullptr, 0, format, argcopy);
  va_end(argcopy);
  return retval;
}
#endif // _vscprintf

#ifndef vasprintf
int vasprintf(char **strp, const char *fmt, va_list ap)
{
  int len = _vscprintf_so(fmt, ap);
  if (len == -1)
    return -1;
  char *str = (char *) malloc((size_t) len + 1);
  if (! str)
    return -1;
  int r = vsnprintf(str, len + 1, fmt, ap); /* "secure" version of vsprintf */
  if (r == -1)
    return free(str), -1;
  *strp = str;
  return r;
}
#endif // vasprintf

#ifndef asprintf
int asprintf(char *strp[], const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int r = vasprintf(strp, fmt, ap);
  va_end(ap);
  return r;
}
#endif // asprintf

std::string string_sprintf(const char *format, ...)
{
  va_list args;
  char   *buf;

  va_start(args, format);

  if (vasprintf(&buf, format, args) == -1) {
    throw std::bad_alloc();
  }

  std::string ret = buf;
  free(buf);

  va_end(args);

  return ret;
}

std::string string_sprintf(const char *format, va_list args)
{
  char *buf;

  if (asprintf(&buf, format, args) == -1) {
    throw std::bad_alloc();
  }

  std::string ret = buf;
  free(buf);

  return ret;
}
