//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_console.hpp"
#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_thing_template.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

void Tp::log_(const char *fmt, va_list args)
{
  verify(MTYPE_TP, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", t->to_short_string().c_str(), g_callframes_indent, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void Tp::log(const char *fmt, ...)
{
  verify(MTYPE_TP, this);

  auto    t = this;
  va_list args;
  va_start(args, fmt);
  t->log_(fmt, args);
  va_end(args);
}

void Tp::dbg_(const char *fmt, ...)
{
  IF_NODEBUG { return; }

  verify(MTYPE_TP, this);

  auto    t = this;
  va_list args;
  va_start(args, fmt);
  t->log_(fmt, args);
  va_end(args);
}

void Tp::die_(const char *fmt, va_list args)
{
  verify(MTYPE_TP, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_short_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DIE("%s", buf);
}

void Tp::die(const char *fmt, ...)
{
  g_errored = true;

  verify(MTYPE_TP, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->die_(fmt, args);
  va_end(args);
}

void Tp::con_(const char *fmt, va_list args)
{
  verify(MTYPE_TP, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_short_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_console_log(buf);
  FLUSH_THE_CONSOLE();
}

void Tp::topcon_(const char *fmt, va_list args)
{
  verify(MTYPE_TP, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_short_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_topcon_log(buf);
  wid_console_log(buf);
  FLUSH_THE_CONSOLE();
}

void Tp::con(const char *fmt, ...)
{
  verify(MTYPE_TP, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->con_(fmt, args);
  va_end(args);
}

void Tp::topcon(const char *fmt, ...)
{
  verify(MTYPE_TP, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->topcon_(fmt, args);
  va_end(args);
}

void Tp::err_(const char *fmt, va_list args)
{
  static bool nested_error;
  if (nested_error) {
    return;
  }
  nested_error = true;

  verify(MTYPE_TP, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Thing %s: ", t->to_short_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);
  TRACE_NO_INDENT();
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  nested_error = false;
}

void Tp::err(const char *fmt, ...)
{
  static bool nested_error;
  if (nested_error) {
    return;
  }
  bool old_nested_error = nested_error;
  nested_error          = true;

  if (old_nested_error) {
    //
    // Subsequent errors on quitting, avoid error logging
    //
    va_list args;
    va_start(args, fmt);
    log_(fmt, args);
    va_end(args);
  } else {
    g_errored = true;
    va_list args;
    va_start(args, fmt);
    err_(fmt, args);
    va_end(args);
  }

  nested_error = false;
}
