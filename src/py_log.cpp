//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_time.h"
#include "my_string.h"
#include "my_file.h"
#include "my_log.h"
#include "my_python.h"
#include "my_main.h"
#include "my_globals.h"

static void py_log_(const char *fmt, va_list args)
{
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "PYC: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void PY_LOG(const char *fmt, ...)
{
  va_list args;

  va_start(args, fmt);
  py_log_(fmt, args);
  va_end(args);
}

void PY_DBG(const char *fmt, ...)
{
  va_list args;

  IF_NODEBUG4 { return; }

  va_start(args, fmt);
  py_log_(fmt, args);
  va_end(args);
}
