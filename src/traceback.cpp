//
// Copyright goblinhack@gmail.com
//
#include "my_main.h"
#include "my_traceback.h"
#include "my_sprintf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#include <execinfo.h>
#endif
#include <cxxabi.h>

void Traceback::init (void) {
#ifndef _WIN32
    size = backtrace(&tb[0], tb.size());
#else
    size = 0;
#endif
}

//
// Inspired from https://github.com/nico/demumble/issues
//
static bool starts_with(const char* s, const char* prefix) {
    return strncmp(s, prefix, strlen(prefix)) == 0;
}

static bool is_mangle_char_posix(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '_';
}

static bool is_mangle_char_win(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || strchr("?_@$", c);
}

static bool is_plausible_itanium_prefix(char* s) {
    // Itanium symbols start with 1-4 underscores followed by Z.
    // strnstr() is BSD, so use a small local buffer and strstr().
    const int N = 5;  // == strlen("____Z")
    char prefix[N + 1];
    strncpy(prefix, s, N); prefix[N] = '\0';
    return strstr(prefix, "_Z");
}

std::string Traceback::to_string (void)
{
#ifdef _WIN32
    return ("<no backtrace on win32, sorry>");
#else
    auto addrlist = &tb[0];
    std::string sout = "stack trace:\n===========\n";

    if (size == 0) {
        sout +="  <empty, possibly corrupt>\n";
        return (sout);
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char **symbollist = backtrace_symbols(addrlist, size);
    const char *prefix = " >";

    // address of this function.
    for (int i = 1; i < size; i++) {

        char *p = symbollist[i];
        char *cur = p;
        char *end = p + strlen(cur);
        bool done = false;

        while (cur < end) {
            size_t special = strcspn(cur, "_?");
            cur += special;

            if (cur >= end) {
                break;
            }

            size_t n_sym = 0;
            if (*cur == '?') {
                while (cur + n_sym != end && is_mangle_char_win(cur[n_sym])) {
                    ++n_sym;
                }
            } else if (is_plausible_itanium_prefix(cur)) {
                while (cur + n_sym != end && is_mangle_char_posix(cur[n_sym])) {
                    ++n_sym;
                }
            } else {
                ++cur;
                continue;
            }

            char tmp = cur[n_sym];
            cur[n_sym] = '\0';

            if (starts_with(cur, "__Z")) {
                cur += 1;
            }

            int status = 0;
            if (char *demangled = abi::__cxa_demangle(cur, 0, 0, &status)) {
                sout += string_sprintf("%s%u %s\n", prefix, i, demangled);
                free(demangled);
                done = true;
                break;
            }

            cur[n_sym] = tmp;
            cur += n_sym;
        }

        if (!done) {
            sout += string_sprintf("%s%s\n", prefix, p);
        }
    }

    sout += string_sprintf("end-of-stack\n");

    free(symbollist);

    return (sout);
#endif
}

void traceback_dump (void)
{
    auto tb = new Traceback();
    tb->init();
    auto s = tb->to_string();
    std::cerr << s << std::endl;
    fprintf(MY_STDERR, "%s", s.c_str());
}
