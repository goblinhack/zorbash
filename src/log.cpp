//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_backtrace.hpp"
#include "my_console.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_log.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_topcon.hpp"

//
// Whan a log appears, if some indent levels are missing, then pull them
// out of the callstack - it's like a mini backtrace
//
void log_catchup_missing_indent_levels(void)
{
  //
  // Seems to need more work - not reliable
  //
#if 0
  IF_NODEBUG2 {
    return;
  }

  if (!g_log_stdout) {
    g_last_logged_callframes_depth = 0;
  }

  if (g_callframes_depth > 0) {
    if (g_last_logged_callframes_depth > g_callframes_depth) {
      g_last_logged_callframes_depth = g_callframes_depth - 1;
      return;
    }
  }

  while (g_last_logged_callframes_depth < g_callframes_depth - 1) {
    auto func = callframes[g_last_logged_callframes_depth].func;
    g_last_logged_callframes_depth++;
    LOG_MISSING("%s", func);
  }
  g_last_logged_callframes_depth = g_callframes_depth;
#endif
}

static void log_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  if (! g_log_stdout) {
    // No indent
  } else {
    snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", "", g_callframes_indent, "");
  }

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

static void log_missing_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  if (! g_log_stdout) {
    // No indent
  } else {
    snprintf(buf + len, MAXLONGSTR - len, "%100s: %*s", "", g_last_logged_callframes_depth, "");
  }

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
}

void LOG(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  log_catchup_missing_indent_levels();
  va_list args;
  va_start(args, fmt);
  log_(fmt, args);
  va_end(args);
}

void LOG_MISSING(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;
  va_start(args, fmt);
  log_missing_(fmt, args);
  va_end(args);
}

static void warn_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);
  FLUSH_THE_CONSOLE();

  wid_console_log(buf);
}

void WARN(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  warn_(fmt, args);
  va_end(args);
}

static void con_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);
  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');

  wid_console_log(buf);

  FLUSH_THE_CONSOLE();
}

static void con_(const wchar_t *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (! g_opt_test_dungeon) {
    char buf[ MAXLONGSTR ];

    buf[ 0 ] = '\0';
    get_timestamp(buf, MAXLONGSTR);
    fprintf(MY_STDOUT, "%s", buf);
    term_log(buf);
  }

  {
    wchar_t buf[ MAXLONGSTR ];
    auto    wrote = vswprintf(buf, MAXLONGSTR, fmt, args);

    //
    // Only a single nul is written, but as we read 2 at a time...
    //
    if (wrote && (wrote < MAXLONGSTR - 1)) {
      buf[ wrote + 1 ] = '\0';
    } else {
      fprintf(stderr, "Failed to console log: [%S]\n", fmt);
    }

    fprintf(MY_STDOUT, "%s\n", wstring_to_string(buf).c_str());
    term_log(buf);
    wid_console_log(buf);
  }

  putchar('\n');
  FLUSH_THE_CONSOLE();
}

void con(const wchar_t *fmt)
{
  TRACE_NO_INDENT();

  if (! g_opt_test_dungeon) {
    char buf[ MAXLONGSTR ];

    buf[ 0 ] = '\0';
    get_timestamp(buf, MAXLONGSTR);
    fprintf(MY_STDOUT, "%s", buf);
    term_log(buf);
  }

  {
    fprintf(MY_STDOUT, "%s\n", wstring_to_string(fmt).c_str());
    term_log(fmt);
    wid_console_log(fmt);
  }

  putchar('\n');
  FLUSH_THE_CONSOLE();
}

void topcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  char ts[ MAXLONGSTR / 2 ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(ts, MAXLONGSTR);
    snprintf(buf, sizeof(buf) - 1, "%s", ts);
    len = (int) strlen(buf);
  }
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  putf(MY_STDOUT, buf);

  term_log(buf);
  putchar('\n');

  wid_topcon_log(buf + len);
  wid_console_log(buf + len);
  FLUSH_THE_CONSOLE();
}

void topcon_(const wchar_t *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (! g_opt_test_dungeon) {
    char ts[ MAXLONGSTR ];
    ts[ 0 ] = '\0';
    get_timestamp(ts, MAXLONGSTR);
    fprintf(MY_STDOUT, "%s", ts);
    term_log(ts);
  }

  {
    wchar_t buf[ MAXLONGSTR ];
    auto    wrote = vswprintf(buf, MAXLONGSTR, fmt, args);

    //
    // Only a single nul is written, but as we read 2 at a time...
    //
    if (wrote && (wrote < MAXLONGSTR - 1)) {
      buf[ wrote + 1 ] = '\0';
    } else {
      fprintf(stderr, "Failed to topcon log: [%S]\n", fmt);
    }

    fprintf(MY_STDOUT, "%s\n", wstring_to_string(buf).c_str());
    term_log(buf);
    wid_topcon_log(buf);
    // wid_console_log(buf);
  }

  putchar('\n');
  FLUSH_THE_CONSOLE();
}

void topcon(const wchar_t *fmt)
{
  TRACE_NO_INDENT();

  if (! g_opt_test_dungeon) {
    char ts[ MAXLONGSTR ];
    ts[ 0 ] = '\0';
    get_timestamp(ts, MAXLONGSTR);
    fprintf(MY_STDOUT, "%sPY TOPCON: ", ts);
    term_log(ts);
  }

  {
    fprintf(MY_STDOUT, "%s\n", wstring_to_string(fmt).c_str());
    term_log(fmt);
    wid_topcon_log(fmt);
    wid_console_log(fmt);
    // wid_console_log(fmt);
  }
  putchar('\n');
  FLUSH_THE_CONSOLE();
}

void CON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  log_catchup_missing_indent_levels();
  va_list args;
  va_start(args, fmt);
  con_(fmt, args);
  va_end(args);
}

void CON(const wchar_t *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  con_(fmt, args);
  va_end(args);
}

void TOPCON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  topcon_(fmt, args);
  va_end(args);
}

void TOPCON(const wchar_t *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  topcon_(fmt, args);
  va_end(args);
}

static void dying_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  snprintf(buf + len, MAXLONGSTR - len, "DIE: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  fprintf(stderr, "%s\n", buf);
  putf(MY_STDOUT, buf);

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

static void err_(const char *fmt, va_list args)
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

    error_handler(error_buf);
  }

  {
    char buf[ MAXLONGSTR ];
    int  len = 0;

    buf[ 0 ] = '\0';
    if (! g_opt_test_dungeon) {
      get_timestamp(buf, MAXLONGSTR);
      len = (int) strlen(buf);
    }

    snprintf(buf + len, MAXLONGSTR - len, "ERROR: %%%%fg=red$%s%%%%fg=reset$", error_buf);
    putf(MY_STDERR, buf);
    putf(MY_STDOUT, buf);

    term_log(buf);
    putchar('\n');

    wid_console_log(buf);
  }

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
  nested_error = false;
}

static void py_err_(const char *fmt, va_list args)
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

    error_handler(error_buf);
  }

  {
    char buf[ MAXLONGSTR ];
    int  len = 0;

    buf[ 0 ] = '\0';
    if (! g_opt_test_dungeon) {
      get_timestamp(buf, MAXLONGSTR);
      len = (int) strlen(buf);
    }

    snprintf(buf + len, MAXLONGSTR - len, "ERROR: %%%%fg=red$%s%%%%fg=reset$", error_buf);
    putf(MY_STDERR, buf);
    putf(MY_STDOUT, buf);

    PyErr_SetString(PyExc_RuntimeError, buf);
    term_log(buf);
    putchar('\n');

    wid_console_log(buf);
  }

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
  nested_error = false;
}

static void croak_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (g_die_occurred) {
    fprintf(stderr, "\nNESTED FATAL ERROR %s %s %d ", __FILE__, __FUNCTION__, __LINE__);
    exit(1);
  }
  g_die_occurred = true;

  char buf[ MAXLONGSTR ];
  int  len   = 0;
  int  tslen = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    tslen = len = (int) strlen(buf);
  }

  snprintf(buf + len, MAXLONGSTR - len, "FATAL ERROR: ");

  len = (int) strlen(buf);
  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  fprintf(stderr, "%s\n", buf);

  ERR("%s", buf + tslen);
  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  //
  // Seems to hang on crashes. Is it useful?
  //
  py_trace();

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  die();
}

void CROAK(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  croak_(fmt, args);
  va_end(args);
}

static void croak_clean_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (g_die_occurred) {
    fprintf(stderr, "\nNESTED FATAL ERROR %s %s %d ", __FILE__, __FUNCTION__, __LINE__);
    exit(1);
  }
  g_die_occurred = true;

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();

  die();
}

void CROAK_CLEAN(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  croak_clean_(fmt, args);
  va_end(args);
}

void DYING(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  dying_(fmt, args);
  va_end(args);
}

void myerr(const char *fmt, ...)
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

  wid_unset_focus();
  wid_unset_focus_lock();

  wid_hide(wid_topcon_window);
  nested_error = false;

  if (g_quitting) {
    DIE("Error while quitting");
  }
}

void py_myerr(const char *fmt, ...)
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
    py_err_(fmt, args);
    va_end(args);
  }

  wid_unset_focus();
  wid_unset_focus_lock();

  wid_hide(wid_topcon_window);
  nested_error = false;

  if (g_quitting) {
    DIE("Error while quitting");
  }
}

static void msgerr_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  int  len = 0;

  callstack_dump();
  backtrace_dump();

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(buf, MAXLONGSTR);
    len = (int) strlen(buf);
  }

  snprintf(buf + len, MAXLONGSTR - len, "ERROR: %%%%fg=red$");

  len = (int) strlen(buf);

  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  len = (int) strlen(buf);
  snprintf(buf + len, MAXLONGSTR - len, "%%%%fg=reset$");

  putf(MY_STDERR, buf);

  putf(MY_STDOUT, buf);

  fprintf(stderr, "%s\n", buf);

  wid_console_log(buf);

  FLUSH_THE_CONSOLE_FOR_ALL_PLATFORMS();
}

void GAME_UI_MSG_BOX(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  msgerr_(fmt, args);
  va_end(args);
}

static void sdl_msgerr_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];

  vsnprintf(buf, MAXLONGSTR, fmt, args);

#if SDL_MAJOR_VERSION >= 2
  CON("INF: Show SDL message box");
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "zorbash", buf, nullptr);
  CON("INF: Finished SDL message box");
#endif
}

void SDL_MSG_BOX(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  sdl_msgerr_(fmt, args);
  va_end(args);
}

static void botcon_(const char *fmt, va_list args)
{
  TRACE_NO_INDENT();

  char buf[ MAXLONGSTR ];
  char ts[ MAXLONGSTR / 2 ];
  int  len = 0;

  buf[ 0 ] = '\0';
  if (! g_opt_test_dungeon) {
    get_timestamp(ts, MAXLONGSTR);
    snprintf(buf, sizeof(buf) - 1, "%sBOTCON: ", ts);
    len = (int) strlen(buf);
  }

  vsnprintf(buf + len, MAXLONGSTR - len, fmt, args);

  // putf(MY_STDOUT, buf);
  // term_log(buf);
  // putchar('\n');

  wid_botcon_log(buf + len);
  // wid_console_log(buf + len);
  // FLUSH_THE_CONSOLE();
}

static void botcon_(const wchar_t *fmt, va_list args)
{
  TRACE_NO_INDENT();

  if (! g_opt_test_dungeon) {
    char ts[ MAXLONGSTR ];
    ts[ 0 ] = '\0';
    get_timestamp(ts, MAXLONGSTR);
    fprintf(MY_STDOUT, "%sBOTCON: ", ts);
    term_log(ts);
  }

  {
    wchar_t buf[ MAXLONGSTR ];
    auto    wrote = vswprintf(buf, MAXLONGSTR, fmt, args);

    //
    // Only a single nul is written, but as we read 2 at a time...
    //
    if (wrote && (wrote < MAXLONGSTR - 1)) {
      buf[ wrote + 1 ] = '\0';
    } else {
      fprintf(stderr, "Failed to botcon log: [%S]\n", fmt);
    }

    // fwprintf(MY_STDOUT, L"%S\n", buf);
    // term_log(buf);
    wid_botcon_log(buf);
    // wid_console_log(buf);
  }

  // putchar('\n');
  // FLUSH_THE_CONSOLE();
}

void botcon(const wchar_t *fmt)
{
  TRACE_NO_INDENT();

  {
    // fwprintf(MY_STDOUT, L"%S\n", fmt);
    // term_log(fmt);
    wid_botcon_log(fmt);
    // wid_console_log(fmt);
  }

  // putchar('\n');
  // FLUSH_THE_CONSOLE();
}

void BOTCON(const char *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  botcon_(fmt, args);
  va_end(args);
}

void BOTCON(const wchar_t *fmt, ...)
{
  TRACE_NO_INDENT();

  va_list args;

  va_start(args, fmt);
  botcon_(fmt, args);
  va_end(args);
}
