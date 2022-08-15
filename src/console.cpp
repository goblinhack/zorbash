//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_console.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing_template.hpp"
#include <string.h>

static inline void term_puts_fg(unsigned char a)
{
  TRACE_AND_INDENT();
  static const char *data[] = {
      "[30m", "[31m", "[32m", "[33m", "[34m", "[35m", "[36m", "[37m", "\033[m",
  };

  if (a >= ARRAY_SIZE(data)) {
    ERR("Overflow");
  }

  fputs(data[ a ], stdout);
}

static void term_puts_fgbg(unsigned char fg, unsigned char bg)
{
  TRACE_AND_INDENT();
  static const char *data[] = {
      "[40;30m", "[40;31m", "[40;32m", "[40;33m", "[40;34m", "[40;35m", "[40;36m", "[40;37m",
      "[41;30m", "[41;31m", "[41;32m", "[41;33m", "[41;34m", "[41;35m", "[41;36m", "[41;37m",
      "[42;30m", "[42;31m", "[42;32m", "[42;33m", "[42;34m", "[42;35m", "[42;36m", "[42;37m",
      "[43;30m", "[43;31m", "[43;32m", "[43;33m", "[43;34m", "[43;35m", "[43;36m", "[43;37m",
      "[44;30m", "[44;31m", "[44;32m", "[44;33m", "[44;34m", "[44;35m", "[44;36m", "[44;37m",
      "[45;30m", "[45;31m", "[45;32m", "[45;33m", "[45;34m", "[45;35m", "[45;36m", "[45;37m",
      "[46;30m", "[46;31m", "[46;32m", "[46;33m", "[46;34m", "[46;35m", "[46;36m", "[46;37m",
      "[47;30m", "[47;31m", "[47;32m", "[47;33m", "[47;34m", "[47;35m", "[47;36m", "[47;37m",
  };

  if (bg == 0) {
    /*
     * Allow the default color to be 0, that of the terminal.
     */
    term_puts_fg(fg);
    return;
  }

  fputs((char *) data[ (bg & 7) * 8 + (fg & 7) ], stdout);
}

static term_color term_color_string_to_index(const wchar_t **s)
{
  TRACE_AND_INDENT();
  if (! wcsncmp(*s, L"black$", sizeof("black$") - 1)) {
    *s += sizeof("black$") - 1;
    return (TERM_COLOR_BLACK);
  }
  if (! wcsncmp(*s, L"red$", sizeof("red$") - 1)) {
    *s += sizeof("red$") - 1;
    return (TERM_COLOR_RED);
  }
  if (! wcsncmp(*s, L"green$", sizeof("green$") - 1)) {
    *s += sizeof("green$") - 1;
    return (TERM_COLOR_GREEN);
  }
  if (! wcsncmp(*s, L"yellow$", sizeof("yellow$") - 1)) {
    *s += sizeof("yellow$") - 1;
    return (TERM_COLOR_YELLOW);
  }
  if (! wcsncmp(*s, L"blue$", sizeof("blue$") - 1)) {
    *s += sizeof("blue$") - 1;
    return (TERM_COLOR_BLUE);
  }
  if (! wcsncmp(*s, L"pink$", sizeof("pink$") - 1)) {
    *s += sizeof("pink$") - 1;
    return (TERM_COLOR_PINK);
  }
  if (! wcsncmp(*s, L"cyan$", sizeof("cyan$") - 1)) {
    *s += sizeof("cyan$") - 1;
    return (TERM_COLOR_CYAN);
  }
  if (! wcsncmp(*s, L"white$", sizeof("white$") - 1)) {
    *s += sizeof("white$") - 1;
    return (TERM_COLOR_WHITE);
  }
  if (! wcsncmp(*s, L"reset$", sizeof("reset$") - 1)) {
    *s += sizeof("reset$") - 1;
    return (TERM_COLOR_RESET);
  }

  (void) string2color(s);

  return (TERM_COLOR_WHITE);
}

static term_color term_color_string_to_index(const char **s)
{
  TRACE_AND_INDENT();
  if (! strncmp(*s, "black$", sizeof("black$") - 1)) {
    *s += sizeof("black$") - 1;
    return (TERM_COLOR_BLACK);
  }
  if (! strncmp(*s, "red$", sizeof("red$") - 1)) {
    *s += sizeof("red$") - 1;
    return (TERM_COLOR_RED);
  }
  if (! strncmp(*s, "green$", sizeof("green$") - 1)) {
    *s += sizeof("green$") - 1;
    return (TERM_COLOR_GREEN);
  }
  if (! strncmp(*s, "yellow$", sizeof("yellow$") - 1)) {
    *s += sizeof("yellow$") - 1;
    return (TERM_COLOR_YELLOW);
  }
  if (! strncmp(*s, "blue$", sizeof("blue$") - 1)) {
    *s += sizeof("blue$") - 1;
    return (TERM_COLOR_BLUE);
  }
  if (! strncmp(*s, "pink$", sizeof("pink$") - 1)) {
    *s += sizeof("pink$") - 1;
    return (TERM_COLOR_PINK);
  }
  if (! strncmp(*s, "cyan$", sizeof("cyan$") - 1)) {
    *s += sizeof("cyan$") - 1;
    return (TERM_COLOR_CYAN);
  }
  if (! strncmp(*s, "white$", sizeof("white$") - 1)) {
    *s += sizeof("white$") - 1;
    return (TERM_COLOR_WHITE);
  }
  if (! strncmp(*s, "reset$", sizeof("reset$") - 1)) {
    *s += sizeof("reset$") - 1;
    return (TERM_COLOR_RESET);
  }

  (void) string2color(s);

  return (TERM_COLOR_WHITE);
}

void term_log(const wchar_t *s)
{
  TRACE_AND_INDENT();
  wchar_t c;

  int fg = TERM_COLOR_WHITE;
  int bg = TERM_COLOR_BLACK;

  while ((c = *s++) != '\0') {

    if (c == '%') {
      if (! wcsncmp(s, L"fg=", 3)) {
        s += 3;
        term_puts_fg(fg = term_color_string_to_index(&s));
        continue;
      }

      if (! wcsncmp(s, L"bg=", 3)) {
        s += 3;
        bg = term_color_string_to_index(&s);
        term_puts_fgbg(fg, bg);
        continue;
      }
      continue;
    }

    putwchar(c);
  }
}

void term_log(const char *s)
{
  TRACE_AND_INDENT();
  char c;

  int fg = TERM_COLOR_WHITE;
  int bg = TERM_COLOR_BLACK;

  while ((c = *s++) != '\0') {

    if (c == '%') {
      if (! strncmp(s, "fg=", 3)) {
        s += 3;
        term_puts_fg(fg = term_color_string_to_index(&s));
        continue;
      }

      if (! strncmp(s, "bg=", 3)) {
        s += 3;
        bg = term_color_string_to_index(&s);
        term_puts_fgbg(fg, bg);
        continue;
      }
      continue;
    }

    putchar(c);
  }
}
