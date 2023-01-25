//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_wid.hpp"

static void wid_log_(Widp w, const char *fmt, va_list args)
{
  char buf[ MAXLONGSTR ];
  int  len;

  verify(MTYPE_WID, w);
  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "WID [%p/%s]: ", w, to_string(w).c_str());
  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void WID_LOG(Widp w, const char *fmt, ...)
{
  va_list args;

  verify(MTYPE_WID, w);

  va_start(args, fmt);
  wid_log_(w, fmt, args);
  va_end(args);
}

void WID_DBG(Widp w, const char *fmt, ...)
{
  va_list args;

  IF_NODEBUG3 { return; }

  verify(MTYPE_WID, w);

  va_start(args, fmt);
  wid_log_(w, fmt, args);
  va_end(args);
}
