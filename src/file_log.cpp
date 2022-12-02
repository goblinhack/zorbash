//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_time.hpp"
#include <cstring>

static void file_log_(const char *fmt, va_list args)
{
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "FILE: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void FILE_LOG(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  file_log_(fmt, args);
  va_end(args);
}

void FILE_DBG(const char *fmt, ...)
{
  va_list args;

  IF_NODEBUG2 { return; }

  va_start(args, fmt);
  file_log_(fmt, args);
  va_end(args);
}
