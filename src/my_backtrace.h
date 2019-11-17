//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#ifndef _MY_BACKTRACE_H_
#define _MY_BACKTRACE_H_

#define MAX_TRACEBACK 63

struct traceback_;
typedef struct traceback_ * tracebackp;

tracebackp traceback_alloc(void);
void traceback_free(tracebackp);
void traceback_stdout(tracebackp);
void traceback_stderr(tracebackp);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include <cxxabi.h>

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

inline void backtrace_print(FILE *out,
                            void *addrlist[MAX_TRACEBACK+1],
                            int addrlen)
{
    fprintf(out, "stack trace:\n");

    if (addrlen == 0) {
	fprintf(out, "  <empty, possibly corrupt>\n");
	return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char ** symbollist = backtrace_symbols(addrlist, addrlen);
    const char *prefix = "> ";

    // address of this function.
    for (int i = 1; i < addrlen; i++) {

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
                fprintf(out, "%s%u %s\n", prefix, i, demangled);
                free(demangled);
                done = true;
                break;
            }

            cur[n_sym] = tmp;
            cur += n_sym;
        }

        if (!done) {
            fprintf(out, "%s%s\n", prefix, p);
        }
    }

    free(symbollist);
}

inline void backtrace_print (void)
{
    // storage array for stack trace address data
    void* addrlist[MAX_TRACEBACK+1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

    backtrace_print(MY_STDERR, addrlist, addrlen);
}

#endif
