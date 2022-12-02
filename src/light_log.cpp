//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_console.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_light.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_wid_console.hpp"

void Light::log_(const char *fmt, va_list args)
{
  verify(MTYPE_LIGHT, this);
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "light: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void Light::log(const char *fmt, ...)
{
  verify(MTYPE_LIGHT, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->log_(fmt, args);
  va_end(args);
}

void Light::die_(const char *fmt, va_list args)
{
  verify(MTYPE_LIGHT, this);
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "light: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DIE("%s", buf);
}

void Light::die(const char *fmt, ...)
{
  g_errored = true;

  verify(MTYPE_LIGHT, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->die_(fmt, args);
  va_end(args);
}

void Light::con_(const char *fmt, va_list args)
{
  verify(MTYPE_LIGHT, this);
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "light: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_console_log(buf);
}

void Light::con(const char *fmt, ...)
{
  verify(MTYPE_LIGHT, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->con_(fmt, args);
  va_end(args);
}

void Light::err_(const char *fmt, va_list args)
{
  verify(MTYPE_LIGHT, this);
  char buf[ MAXLONGSTR ];
  int  len;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Light: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

void Light::err(const char *fmt, ...)
{
  g_errored = true;

  verify(MTYPE_LIGHT, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->err_(fmt, args);
  va_end(args);
}
