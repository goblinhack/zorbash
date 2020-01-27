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
#ifndef _WIN32
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
#endif

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

#ifdef _WIN32
#include <windows.h>
#include <excpt.h>
#include <imagehlp.h>
#include <binutils/bfd.h>
#include <psapi.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <psapi.h>
#include <dbghelp.h>

#define STACKWALK_MAX_NAMELEN 1024

typedef struct CallstackEntry
{
    DWORD64 offset; // if 0, we have no valid entry
    CHAR    name[STACKWALK_MAX_NAMELEN];
    CHAR    undName[STACKWALK_MAX_NAMELEN];
    CHAR    undFullName[STACKWALK_MAX_NAMELEN];
    DWORD64 offsetFromSmybol;
    DWORD   offsetFromLine;
    DWORD   lineNumber;
    CHAR    lineFileName[STACKWALK_MAX_NAMELEN];
    DWORD   symType;
    LPCSTR  symTypeString;
    CHAR    moduleName[STACKWALK_MAX_NAMELEN];
    DWORD64 baseOfImage;
    CHAR    loadedImageName[STACKWALK_MAX_NAMELEN];
} CallstackEntry;

typedef enum CallstackEntryType
{
    firstEntry,
    nextEntry,
    lastEntry
} CallstackEntryType;

//
// Needs .pdb filea to work and clang is not creating them for some reason
//
void _backtrace (void)
{
    HANDLE process = ::GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    // Randomly saw this was supposed to be called prior to StackWalk so tried
    // it
    if (!SymInitialize(process, 0, true)) {
        wprintf(L"SymInitialize unable to find process!! Error: %d\r\n", 
            GetLastError());
    }

    DWORD symOptions = SymGetOptions();
    symOptions |= SYMOPT_LOAD_LINES;
    symOptions |= SYMOPT_FAIL_CRITICAL_ERRORS;
    symOptions = SymSetOptions(symOptions);

    char szSearchPath[STACKWALK_MAX_NAMELEN] = {0};
    SymGetSearchPath(process, szSearchPath, STACKWALK_MAX_NAMELEN);

    char  szUserName[STACKWALK_MAX_NAMELEN] = {0};
    DWORD dwSize = STACKWALK_MAX_NAMELEN;
    GetUserNameA(szUserName, &dwSize);

    CHAR   search_path_debug[STACKWALK_MAX_NAMELEN];
    size_t maxLen = STACKWALK_MAX_NAMELEN;
#if _MSC_VER >= 1400
    maxLen = _TRUNCATE;
#endif
    _snprintf_s(search_path_debug, maxLen, "SymInit: Symbol-SearchPath: '%s', symOptions: %d, UserName: '%s'\n",
            szSearchPath, symOptions, szUserName);
    search_path_debug[STACKWALK_MAX_NAMELEN - 1] = 0;
    printf(search_path_debug);

    // Initalize more memory
    CONTEXT context;
    memset(&context, 0, sizeof(CONTEXT));
    context.ContextFlags = CONTEXT_FULL;
    RtlCaptureContext(&context);

    // Initalize a few things here and there
    STACKFRAME stack;
    memset(&stack, 0, sizeof(STACKFRAME));
    stack.AddrPC.Offset       = context.Rip;
    stack.AddrPC.Mode         = AddrModeFlat;
    stack.AddrStack.Offset    = context.Rsp;
    stack.AddrStack.Mode      = AddrModeFlat;
    stack.AddrFrame.Offset    = context.Rbp;
    stack.AddrFrame.Mode      = AddrModeFlat;

//    IMAGEHLP_MODULE64_V3 Module;
//    memset(&Module, 0, sizeof(Module));
//    Module.SizeOfStruct = sizeof(Module);

#ifdef _M_IX86
    auto machine = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
    auto machine = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
    auto machine = IMAGE_FILE_MACHINE_IA64;
#else
#error "platform not supported!"
#endif

    for (ULONG frame = 0; ; frame++)
    {
        // Check for frames
        BOOL result = StackWalk(machine, 
                                process, 
                                thread, 
                                &stack,
                                &context,
                                0,
                                SymFunctionTableAccess, 
                                SymGetModuleBase, 
                                0);

        CallstackEntry csEntry;
        csEntry.offset = stack.AddrPC.Offset;
        csEntry.name[0] = 0;
        csEntry.undName[0] = 0;
        csEntry.undFullName[0] = 0;
        csEntry.offsetFromSmybol = 0;
        csEntry.offsetFromLine = 0;
        csEntry.lineFileName[0] = 0;
        csEntry.lineNumber = 0;
        csEntry.loadedImageName[0] = 0;
        csEntry.moduleName[0] = 0;

        // Initalize more memory
        MODULEINFO                  module_info;
        SecureZeroMemory(&module_info, sizeof(MODULEINFO));

        IMAGEHLP_SYMBOL64 symbol {};
        symbol.SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
        symbol.MaxNameLength = STACKWALK_MAX_NAMELEN;

        // Initalize more memory and clear it out
        if (SymGetSymFromAddr64(process, 
                                stack.AddrPC.Offset,
                                &csEntry.offsetFromSmybol, 
                                &symbol)) {
            printf("got sym\n");
        }

        char name[STACKWALK_MAX_NAMELEN];
        UnDecorateSymbolName(symbol.Name, (PSTR)name, sizeof(name), 
                             UNDNAME_COMPLETE );

        IMAGEHLP_LINE64 line {};
        line.SizeOfStruct = sizeof(line);

        if (SymGetLineFromAddr64(process, 
                                 stack.AddrPC.Offset,
                                 &csEntry.offsetFromLine, 
                                 &line)) {
            printf("got line\n");
        }

        printf("Frame %lu:\n"
               "    Symbol name:    %s\n"
               "    PC address:     0x%08LX\n"
               "    Stack address:  0x%08LX\n"
               "    Frame address:  0x%08LX\n"
               "\n",
               frame,
               symbol.Name,
               (ULONG64)stack.AddrPC.Offset,
               (ULONG64)stack.AddrStack.Offset,
               (ULONG64)stack.AddrFrame.Offset
           );

#if 0
        // Initalize memory
        LPWSTR console_message = (LPWSTR) new TCHAR[MaxMsgLength];
        LPWSTR file_message = (LPWSTR) new TCHAR[MaxMsgLength];

        // Set some strings
        swprintf(console_message, MaxMsgLength, L">> Frame %02lu: called from: %016X Stack: %016X Frame: %016X Address return: %016X\r\n",
            frame, s.AddrPC.Offset, s.AddrStack.Offset, s.AddrFrame.Offset, s.AddrReturn.Offset);
        swprintf(file_message, MaxMsgLength, L"Frame %02lu: called from: %016X Stack: %016X Frame: %016X Address return: %016X\r\n",
            frame, s.AddrPC.Offset, s.AddrStack.Offset, s.AddrFrame.Offset, s.AddrReturn.Offset);

        /* When the symbol can yield the name, line and file name the above strings
        will also include that information */
        // To go here . . .

        // Write some strings
        wprintf(L"CONSOLE: %s\n", console_message);
        wprintf(L"FILE: %s\n", file_message);

        // Delete some memory
        if (console_message) {
            delete[] console_message;   console_message = nullptr;
        }
        if (file_message) {
            delete[] file_message;  file_message = nullptr;
        }

#endif
        // If nothing else to do break loop
        if (!result) {
            break;
        }
    }
}

void does_not_work (void)
{
    printf("test2\n");
    _backtrace2();
    printf("\n\n");
    DIE("test");
}
#endif
