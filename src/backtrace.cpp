//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iostream>
#include <string.h>
#ifdef _WIN32
// clang-format off
#include <stdio.h>   // do not remove
#include <windows.h> // do not remove
#include <shlwapi.h> // do not remove
#include <winbase.h> // do not remove
#include <dbghelp.h> // do not remove
// clang-format on
#else
#include <execinfo.h> // do not remove
#endif
#include <cxxabi.h>
#ifdef HAVE_LIBUNWIND
#include <libunwind.h> // do not remove
#endif
#include <memory>

#include "my_backtrace.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"

void Backtrace::init(void)
{
#ifdef HAVE_LIBUNWIND
#ifdef _WIN32
  //
  // Just did not seem to work on mingw
  //
  size = 0;
#else
  size = unw_backtrace(&bt[ 0 ], bt.size());
#endif
#else
#ifdef _WIN32
  size = 0;
#else
  size = backtrace(&bt[ 0 ], bt.size());
#endif
#endif
}

//
// Inspired from https://github.com/nico/demumble/issues
//
#ifndef _WIN32
static bool starts_with(const char *s, const char *prefix) { return strncmp(s, prefix, strlen(prefix)) == 0; }

static bool is_mangle_char_posix(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_';
}

static bool is_mangle_char_win(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || strchr("?_@$", c);
}

static bool is_plausible_itanium_prefix(char *s)
{
  // Itanium symbols start with 1-4 underscores followed by Z.
  // strnstr() is BSD, so use a small local buffer and strstr().
  const int N = 5; // == strlen("____Z")
  char      prefix[ N + 1 ];
  strncpy(prefix, s, N);
  prefix[ N ] = '\0';
  return strstr(prefix, "_Z");
}
#endif

//
// See
// https://stackoverflow.com/questions/4939636/function-to-mangle-demangle-functions
//
// See also c++filt e.g.:
//
// c++filt -n _ZNK3MapI10StringName3RefI8GDScriptE10ComparatorIS0_E16DefaultAllocatorE3hasERKS0_
// Map<StringName, Ref<GDScript>, Comparator<StringName>, DefaultAllocator>::has(StringName const&) const
//
#ifndef _WIN32
static auto cppDemangle(const char *abiName)
{
  //
  // This function allocates and returns storage in ret
  //
  int   status;
  char *ret = abi::__cxa_demangle(abiName, nullptr /* output buffer */, nullptr /* length */, &status);

  auto deallocator = ([](char *mem) {
    if (mem)
      free((void *) mem);
  });

  if (status) {
    // 0: The demangling operation succeeded.
    // -1: A memory allocation failure occurred.
    // -2: mangled_name is not a valid name under the C++ ABI mangling rules.
    // -3: One of the arguments is invalid.
    std::unique_ptr< char, decltype(deallocator) > retval(nullptr, deallocator);
    return retval;
  }

  //
  // Create a unique pointer to take ownership of the returned string so it
  // is freed when that pointers goes out of scope
  //
  std::unique_ptr< char, decltype(deallocator) > retval(ret, deallocator);
  return retval;
}
#endif

std::string Backtrace::to_string(void)
{
#ifdef _WIN32
  return "";
#else
  auto        addrlist = &bt[ 0 ];
  std::string sout     = "stack trace\n===========\n";

  if (size == 0) {
    sout += "  <empty, possibly corrupt>\n";
    return sout;
  }

  // resolve addresses into strings containing "filename(function+address)",
  // this array must be free()-ed
  char      **symbollist = backtrace_symbols(addrlist, size);
  const char *prefix     = " >";

  // address of this function.
  for (int i = size - 1; i >= 0; i--) {

    char *p    = symbollist[ i ];
    char *cur  = p;
    char *end  = p + strlen(cur);
    bool  done = false;

    while (cur < end) {
      size_t special = strcspn(cur, "_?");
      cur += special;

      if (cur >= end) {
        break;
      }

      size_t n_sym = 0;
      if (*cur == '?') {
        while (cur + n_sym != end && is_mangle_char_win(cur[ n_sym ])) {
          ++n_sym;
        }
      } else if (is_plausible_itanium_prefix(cur)) {
        while (cur + n_sym != end && is_mangle_char_posix(cur[ n_sym ])) {
          ++n_sym;
        }
      } else {
        ++cur;
        continue;
      }

      char tmp     = cur[ n_sym ];
      cur[ n_sym ] = '\0';

      if (starts_with(cur, "__Z")) {
        cur++;
      }

      auto demangled = cppDemangle(cur);
      if (demangled) {
        sout += string_sprintf("%s %s\n", prefix, demangled.get());
        done = true;
        break;
      }

      cur[ n_sym ] = tmp;
      cur += n_sym;
    }

    if (! done) {
      sout += string_sprintf("%s%s\n", prefix, p);
    }
  }

  sout += string_sprintf("end-of-stack\n");

  free(symbollist);

  return sout;
#endif
}

void Backtrace::log(void)
{
#ifdef _WIN32
  return;
#else
  auto addrlist = &bt[ 0 ];

  LOG("stack trace");
  LOG("===========");

  if (size == 0) {
    LOG("  <empty, possibly corrupt>");
    return;
  }

  // resolve addresses into strings containing "filename(function+address)",
  // this array must be free()-ed
  char      **symbollist = backtrace_symbols(addrlist, size);
  const char *prefix     = " >";

  // address of this function.
  for (int i = 1; i < size; i++) {

    char *p    = symbollist[ i ];
    char *cur  = p;
    char *end  = p + strlen(cur);
    bool  done = false;

    while (cur < end) {
      size_t special = strcspn(cur, "_?");
      cur += special;

      if (cur >= end) {
        break;
      }

      size_t n_sym = 0;
      if (*cur == '?') {
        while (cur + n_sym != end && is_mangle_char_win(cur[ n_sym ])) {
          ++n_sym;
        }
      } else if (is_plausible_itanium_prefix(cur)) {
        while (cur + n_sym != end && is_mangle_char_posix(cur[ n_sym ])) {
          ++n_sym;
        }
      } else {
        ++cur;
        continue;
      }

      char tmp     = cur[ n_sym ];
      cur[ n_sym ] = '\0';

      if (starts_with(cur, "__Z")) {
        cur++;
      }

      auto demangled = cppDemangle(cur);
      if (demangled) {
        LOG("%s%u %s", prefix, i, demangled.get());
        done = true;
        break;
      }

      cur[ n_sym ] = tmp;
      cur += n_sym;
    }

    if (! done) {
      LOG("%s%s", prefix, p);
    }
  }

  LOG("end-of-stack");

  free(symbollist);
#endif
}

#ifdef _WIN32
#include <errno.h>
#include <windows.h>

void backtrace_dump() { fprintf(MY_STDERR, "%s", backtrace_string().c_str()); }

std::string backtrace_string(void)
{
  char tmp[ 10000 ];

  *tmp = '\0';

  {
    int error = errno;
    snprintf(tmp + strlen(tmp), sizeof(tmp) - strlen(tmp), "errno = %d: %s\n", error, strerror(error));
  }

  {
    DWORD error = GetLastError();
    char  buf[ 1024 ];
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf,
                   sizeof(buf), NULL);
    snprintf(tmp + strlen(tmp), sizeof(tmp) - strlen(tmp), "GetLastError = %d: %s", error, buf);
  }

  const int max_symbol_len = 1024;

  HANDLE process = GetCurrentProcess();
  SymInitialize(process, NULL, TRUE);

  void *stack[ 128 ];
  WORD  num_frames = CaptureStackBackTrace(0, 128, stack, NULL);

  for (WORD i = 0; i < num_frames; i++) {
    char         symbol_mem[ sizeof(SYMBOL_INFO) + max_symbol_len * sizeof(TCHAR) ];
    SYMBOL_INFO *symbol  = (SYMBOL_INFO *) symbol_mem;
    symbol->MaxNameLen   = max_symbol_len;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    DWORD64 addr64 = DWORD64(stack[ i ]);
    SymFromAddr(process, addr64, NULL, symbol);

    IMAGEHLP_LINE64 line;
    DWORD           col;
    line.SizeOfStruct  = sizeof(line);
    BOOL has_file_info = SymGetLineFromAddr64(process, addr64, &col, &line);

    if (has_file_info) {
      snprintf(tmp + strlen(tmp), sizeof(tmp) - strlen(tmp), "(%s:%d - 0x%08I64x)\n", symbol->Name, line.FileName,
               line.LineNumber, symbol->Address);
    } else {
      snprintf(tmp + strlen(tmp), sizeof(tmp) - strlen(tmp), "(%s, 0x%08I64x)\n", symbol->Name, symbol->Address);
    }
  }

  // __debugbreak();

  std::string ret(tmp);
  return tmp;
}

#else
std::string backtrace_string(void)
{
  auto bt = new Backtrace();
  bt->init();
  return bt->to_string();
}

void backtrace_dump(void)
{
  auto bt = backtrace_string();
  fprintf(MY_STDERR, "%s", bt.c_str());
}
#endif
