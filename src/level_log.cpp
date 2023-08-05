//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_console.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_wid_console.hpp"

void Level::log_(const char *fmt, va_list args)
{
  verify(MTYPE_LEVEL, this);
  auto l = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon_gen) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", l->to_string().c_str(), g_callframes_indent, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void Level::log(const char *fmt, ...)
{
  verify(MTYPE_LEVEL, this);
  log_catchup_missing_indent_levels();
  auto    l = this;
  va_list args;
  va_start(args, fmt);
  l->log_(fmt, args);
  va_end(args);
}

void Level::con_(const char *fmt, va_list args)
{
  verify(MTYPE_LEVEL, this);
  auto l = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon_gen) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "Level %s: ", l->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');
  wid_console_log(buf);
  FLUSH_THE_CONSOLE();
}

void Level::con(const char *fmt, ...)
{
  verify(MTYPE_LEVEL, this);
  auto    l = this;
  va_list args;

  va_start(args, fmt);
  l->con_(fmt, args);
  va_end(args);
}

void Level::err_(const char *fmt, va_list args)
{
  static bool nested_error;
  if (nested_error) {
    return;
  }
  nested_error = true;

  verify(MTYPE_LEVEL, this);
  auto l = this;
  char buf[ MAXLONGSTR ];
  int  len = 0;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon_gen) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Level %s: ", l->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  nested_error = false;
}

void Level::err(const char *fmt, ...)
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
