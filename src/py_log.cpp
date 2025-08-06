//
// Copyright goblinhack@gmail.com
//

#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_time.hpp"

static void py_log_(const char *fmt, va_list args)
{
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "PYC: ");
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DBG("%s", buf);
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

  IF_NODEBUG { return; }

  va_start(args, fmt);
  py_log_(fmt, args);
  va_end(args);
}
