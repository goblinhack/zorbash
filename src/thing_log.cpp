//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_console.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_log.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_time.hpp"
#include "my_traceback.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

void Thing::log_(const char *fmt, va_list args)
{
  verify(this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);

  snprintf(buf + len, MAXLONGSTR - len, "%60s: %*s", t->to_string().c_str(), g_callframes_depth, "");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void Thing::log(const char *fmt, ...)
{
  verify(this);
  log_catchup_missing_indent_levels();

  auto    t = this;
  va_list args;
  va_start(args, fmt);
  t->log_(fmt, args);
  va_end(args);
}

void Thing::die_(const char *fmt, va_list args)
{
  verify(this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  DIE("%s", buf);
}

void Thing::die(const char *fmt, ...)
{
  g_errored = true;

  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->die_(fmt, args);
  va_end(args);
}

void Thing::con_(const char *fmt, va_list args)
{
  verify(this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
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
  verify(this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
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
  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->con_(fmt, args);
  va_end(args);
}

void Thing::topcon(const char *fmt, ...)
{
  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->topcon_(fmt, args);
  va_end(args);
}

void Thing::err_(const char *fmt, va_list args)
{
  static bool nested_error;
  if (nested_error) {
    return;
  }
  nested_error = true;

  verify(this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "ERROR: Thing %s: ", t->to_string().c_str());

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  putf(MY_STDERR, buf);

  fprintf(stderr, "%s\n", buf);

  callstack_dump();
  traceback_dump();

  wid_console_log(buf);
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  nested_error = false;
}

void Thing::err(const char *fmt, ...)
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

void Thing::botcon_(const char *fmt, va_list args)
{
  verify(this);
  auto t = this;
  char buf[ MAXLONGSTR ];
  int  len;

  buf[ 0 ] = '\0';
  get_timestamp(buf, MAXLONGSTR);
  len = (int) strlen(buf);
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
  verify(this);
  auto    t = this;
  va_list args;

  va_start(args, fmt);
  t->botcon_(fmt, args);
  va_end(args);
}
