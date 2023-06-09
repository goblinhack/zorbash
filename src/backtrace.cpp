//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iostream>
#include <string.h>
#ifdef _WIN32
#include <dbghelp.h>
#include <shlwapi.h>
#include <stdio.h>
#include <windows.h>
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
  size = unw_backtrace(&bt[ 0 ], bt.size());
#else
#ifndef _WIN32
  size                 = backtrace(&bt[ 0 ], bt.size());
#else
  size = 0;
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

void backtrace_dump(void)
{
  auto bt = new Backtrace();
  bt->init();
  auto s = bt->to_string();
  std::cerr << s << std::endl;
  fprintf(MY_STDERR, "%s", s.c_str());
}

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOL_LEN 1024

typedef struct CallstackEntry {
  DWORD64 offset; // if 0, we have no valid entry
  CHAR    name[ MAX_SYMBOL_LEN ];
  CHAR    undName[ MAX_SYMBOL_LEN ];
  CHAR    undFullName[ MAX_SYMBOL_LEN ];
  DWORD64 offsetFromSmybol;
  DWORD   offsetFromLine;
  DWORD   lineNumber;
  CHAR    lineFileName[ MAX_SYMBOL_LEN ];
  DWORD   symType;
  LPCSTR  symTypeString;
  CHAR    moduleName[ MAX_SYMBOL_LEN ];
  DWORD64 baseOfImage;
  CHAR    loadedImageName[ MAX_SYMBOL_LEN ];
} CallstackEntry;

typedef enum CallstackEntryType { firstEntry, nextEntry, lastEntry } CallstackEntryType;

void _backtrace(void)
{
  HANDLE process = ::GetCurrentProcess();
  HANDLE thread  = GetCurrentThread();

  if (! SymInitialize(process, 0, true)) {
    wprintf(L"SymInitialize unable to find process!! Error: %d\r\n", GetLastError());
  }

  DWORD symOptions = SymGetOptions();
  symOptions |= SYMOPT_LOAD_LINES;
  symOptions |= SYMOPT_FAIL_CRITICAL_ERRORS;
  symOptions = SymSetOptions(symOptions);

  char szSearchPath[ MAX_SYMBOL_LEN ] = {0};
  SymGetSearchPath(process, szSearchPath, MAX_SYMBOL_LEN);

  char  szUserName[ MAX_SYMBOL_LEN ] = {0};
  DWORD dwSize                       = MAX_SYMBOL_LEN;
  GetUserNameA(szUserName, &dwSize);

  CHAR   search_path_debug[ MAX_SYMBOL_LEN ];
  size_t maxLen = MAX_SYMBOL_LEN;
#if _MSC_VER >= 1400
  maxLen = _TRUNCATE;
#endif
  _snprintf_s(search_path_debug, maxLen, "SymInit: Symbol-SearchPath: '%s', symOptions: %d, UserName: '%s'\n",
              szSearchPath, symOptions, szUserName);
  search_path_debug[ MAX_SYMBOL_LEN - 1 ] = 0;
  printf(search_path_debug);

  // Initalize more memory
  CONTEXT context;
  memset(&context, 0, sizeof(CONTEXT));
  context.ContextFlags = CONTEXT_FULL;
  RtlCaptureContext(&context);

  // Initalize a few things here and there
  STACKFRAME stack;
  memset(&stack, 0, sizeof(STACKFRAME));
  stack.AddrPC.Offset    = context.Rip;
  stack.AddrPC.Mode      = AddrModeFlat;
  stack.AddrStack.Offset = context.Rsp;
  stack.AddrStack.Mode   = AddrModeFlat;
  stack.AddrFrame.Offset = context.Rbp;
  stack.AddrFrame.Mode   = AddrModeFlat;

#ifdef _M_IX86
  auto machine = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
  auto machine = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
  auto machine = IMAGE_FILE_MACHINE_IA64;
#else
#error "platform not supported!"
#endif
  for (ULONG frame = 0;; frame++) {
    BOOL result
        = StackWalk(machine, process, thread, &stack, &context, 0, SymFunctionTableAccess, SymGetModuleBase, 0);

    CallstackEntry csEntry;
    csEntry.offset               = stack.AddrPC.Offset;
    csEntry.name[ 0 ]            = 0;
    csEntry.undName[ 0 ]         = 0;
    csEntry.undFullName[ 0 ]     = 0;
    csEntry.offsetFromSmybol     = 0;
    csEntry.offsetFromLine       = 0;
    csEntry.lineFileName[ 0 ]    = 0;
    csEntry.lineNumber           = 0;
    csEntry.loadedImageName[ 0 ] = 0;
    csEntry.moduleName[ 0 ]      = 0;

    IMAGEHLP_SYMBOL64 symbol {};
    symbol.SizeOfStruct  = sizeof(IMAGEHLP_SYMBOL64);
    symbol.MaxNameLength = MAX_SYMBOL_LEN;

    // Initalize more memory and clear it out
    if (SymGetSymFromAddr64(process, stack.AddrPC.Offset, &csEntry.offsetFromSmybol, &symbol)) {
    }

    IMAGEHLP_LINE64 line {};
    line.SizeOfStruct = sizeof(line);

    if (SymGetLineFromAddr64(process, stack.AddrPC.Offset, &csEntry.offsetFromLine, &line)) {
    }

    printf(
        "Frame %lu:\n"
        "    Symbol name:    %s\n"
        "    PC address:     0x%08LX\n"
        "    Stack address:  0x%08LX\n"
        "    Frame address:  0x%08LX\n"
        "\n",
        frame, symbol.Name, (ULONG64) stack.AddrPC.Offset, (ULONG64) stack.AddrStack.Offset,
        (ULONG64) stack.AddrFrame.Offset);

    // If nothing else to do break loop
    if (! result) {
      break;
    }
  }
}
#endif
