//
// Copyright goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_console.hpp"
#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

void Thing::log_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", t->to_string().c_str(), g_callframes_indent, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void Thing::log(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  log_catchup_missing_indent_levels();

  auto    t = this;
  va_list args;
  va_start(args, fmt);
  t->log_(fmt, args);
  va_end(args);
}

void Thing::dbg_(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  IF_NODEBUG { return; }

  verify(MTYPE_THING, this);
  log_catchup_missing_indent_levels();

  auto    t = this;
  va_list args;
  va_start(args, fmt);
  t->log_(fmt, args);
  va_end(args);
}

void Thing::die_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DIE("%s", buf);
}

void Thing::die(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  g_errored = true;

  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->die_(fmt, args);
  va_end(args);
}

void Thing::con_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_console_log(buf);
  FLUSH_THE_CONSOLE();
}

void Thing::topcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_topcon_log(buf);
  wid_console_log(buf);
  FLUSH_THE_CONSOLE();
}

void Thing::con(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->con_(fmt, args);
  va_end(args);
}

void Thing::topcon(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->topcon_(fmt, args);
  va_end(args);
}

void Thing::err_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  static bool nested_error;
  if (nested_error) {
    return;
  }
  nested_error = true;

  callstack_dump();
  backtrace_dump();

  char error_buf[ MAXLONGSTR ];
  {
    int len;

    error_buf[ 0 ] = '\0';
    len            = (int) strlen(error_buf);
    vsnprintf(error_buf + len, MAXLONGSTR - len, fmt, args);
  }

  verify(MTYPE_THING, this);
  auto t = this;
  char buf[ MAXLONGSTR * 2 ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Thing %s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: %%%%fg=red$%s%%%%fg=reset$", error_buf);
  putf(MY_STDOUT, buf);
  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);
  TRACE_NO_INDENT();
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  error_handler(error_buf);

  nested_error = false;
}

void Thing::err(const char *fmt, ...)
{
  TRACE_NO_INDENT();
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

void Thing::botcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_botcon_log(buf);
  wid_console_log(buf);
  FLUSH_THE_CONSOLE();
}

void Thing::botcon(const char *fmt, ...)
{
  TRACE_NO_INDENT();
  verify(MTYPE_THING, this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->botcon_(fmt, args);
  va_end(args);
}
