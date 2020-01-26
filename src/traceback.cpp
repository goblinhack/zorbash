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
/*
    Copyright (c) 2010 ,
        Cloud Wu . All rights reserved.

        http://www.codingnow.com

    Use, modification and distribution are subject to the "New BSD License"
    as listed at <url: http://www.opensource.org/licenses/bsd-license.php >.

filename: backtrace.c
compiler: gcc 3.4.5 (mingw-win32)
build command: gcc -O2 -shared -Wall -o backtrace.dll backtrace.c -lbfd -liberty -limagehlp
how to use: Call LoadLibraryA("backtrace.dll"); at beginning of your program .
*/

#define PACKAGE "your-program-name"
#define PACKAGE_VERSION "0.1"

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

#define BUFFER_MAX (16*1024)

#define BFD_ERR_OK          (0)
#define BFD_ERR_OPEN_FAIL   (1)
#define BFD_ERR_BAD_FORMAT  (2)
#define BFD_ERR_NO_SYMBOLS  (3)
#define BFD_ERR_READ_SYMBOL (4)

static const char *const bfd_errors[] = {
    "",
    "(Failed to open bfd)",
    "(Bad format)",
    "(No symbols)",
    "(Failed to read symbols)",
};

struct bfd_ctx {
    bfd * handle;
    asymbol ** symbol;
};

struct bfd_set {
    char * name;
    struct bfd_ctx * bc;
    struct bfd_set *next;
};

struct find_info {
    asymbol **symbol;
    bfd_vma counter;
    const char *file;
    const char *func;
    unsigned line;
};

static void
lookup_section(bfd *abfd, asection *sec, void *opaque_data)
{
    struct find_info *data = static_cast<struct find_info *>(opaque_data);

    if (data->func)
        return;

    if (!(bfd_get_section_flags(abfd, sec) & SEC_ALLOC))
        return;

    bfd_vma vma = bfd_get_section_vma(abfd, sec);
    if (data->counter < vma || vma + bfd_get_section_size(sec) <= data->counter)
        return;

    bfd_find_nearest_line(abfd, sec, data->symbol, data->counter - vma, &(data->file), &(data->func), &(data->line));
}

static void
find(struct bfd_ctx * b, DWORD offset, const char **file, const char **func, unsigned *line)
{
    struct find_info data;
    data.func = NULL;
    data.symbol = b->symbol;
    data.counter = offset;
    data.file = NULL;
    data.func = NULL;
    data.line = 0;

    bfd_map_over_sections(b->handle, &lookup_section, &data);
    if (file) {
        *file = data.file;
    }
    if (func) {
        *func = data.func;
    }
    if (line) {
        *line = data.line;
    }
}

static int
init_bfd_ctx(struct bfd_ctx *bc, const char * procname, int *err)
{
    bc->handle = NULL;
    bc->symbol = NULL;

    bfd *b = bfd_openr(procname, 0);
    if (!b) {
        if(err) { *err = BFD_ERR_OPEN_FAIL; }
        return 1;
    }

    if(!bfd_check_format(b, bfd_object)) {
        bfd_close(b);
        if(err) { *err = BFD_ERR_BAD_FORMAT; }
        return 1;
    }

    if(!(bfd_get_file_flags(b) & HAS_SYMS)) {
        bfd_close(b);
        if(err) { *err = BFD_ERR_NO_SYMBOLS; }
        return 1;
    }

    void *symbol_table;

    unsigned dummy = 0;
    if (bfd_read_minisymbols(b, FALSE, &symbol_table, &dummy) == 0) {
        if (bfd_read_minisymbols(b, TRUE, &symbol_table, &dummy) < 0) {
            free(symbol_table);
            bfd_close(b);
            if(err) { *err = BFD_ERR_READ_SYMBOL; }
            return 1;
        }
    }

    bc->handle = b;
    bc->symbol = static_cast<asymbol **>(symbol_table);

    if(err) { *err = BFD_ERR_OK; }
    return 0;
}

static struct bfd_ctx *
get_bc(struct bfd_set *set , const char *procname, int *err)
{
    while(set->name) {
        if (strcmp(set->name , procname) == 0) {
            return set->bc;
        }
        set = set->next;
    }
    struct bfd_ctx bc;
    if (init_bfd_ctx(&bc, procname, err)) {
        return NULL;
    }
    set->next = (struct bfd_set *) calloc(1, sizeof(*set));
    set->bc = (struct bfd_ctx *) malloc(sizeof(struct bfd_ctx));
    memcpy(set->bc, &bc, sizeof(bc));
    set->name = strdup(procname);

    return set->bc;
}

static void
_backtrace(struct bfd_set *set, int depth , LPCONTEXT context)
{
    char procname[MAX_PATH];
    GetModuleFileNameA(NULL, procname, sizeof procname);

    struct bfd_ctx *bc = NULL;
    int err = BFD_ERR_OK;

    STACKFRAME frame;
    memset(&frame,0,sizeof(frame));

    frame.AddrPC.Offset = context->Rip;
    frame.AddrPC.Mode = AddrModeFlat;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Offset = context->Rbp;
    frame.AddrFrame.Mode = AddrModeFlat;

    HANDLE process = GetCurrentProcess();
    HANDLE thread = GetCurrentThread();

    SymInitialize(process, 0, false);

    char symbol_buffer[sizeof(IMAGEHLP_SYMBOL) + 255];
    char module_name_raw[MAX_PATH];

#ifdef _M_IX86
    auto platform = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
    auto platform = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
    auto platform = IMAGE_FILE_MACHINE_IA64;
#else
#error "platform not supported!"
#endif

    while(StackWalk64(platform,
        process,
        thread,
        &frame,
        context,
        0,
        SymFunctionTableAccess,
        SymGetModuleBase, 0)) {

        --depth;
        if (depth < 0)
            break;

        IMAGEHLP_SYMBOL *symbol = (IMAGEHLP_SYMBOL *)symbol_buffer;
        symbol->SizeOfStruct = (sizeof *symbol) + 255;
        symbol->MaxNameLength = 254;

        DWORD64 module_base = SymGetModuleBase(process, frame.AddrPC.Offset);
        printf("module_base %p\n", (void*)process);

        const char * module_name = "[unknown module]";
        if (module_base &&
            GetModuleFileNameA((HINSTANCE)module_base, module_name_raw, MAX_PATH)) {
            module_name = module_name_raw;
        printf("module_name %s\n", module_name);
            bc = get_bc(set, module_name, &err);
        }

        const char * file = NULL;
        const char * func = NULL;
        unsigned line = 0;

        if (bc) {
            find(bc,frame.AddrPC.Offset,&file,&func,&line);
        }

        if (file == NULL) {
            DWORD64 dummy = 0;
            if (SymGetSymFromAddr(process, frame.AddrPC.Offset, &dummy, symbol)) {
                file = symbol->Name;
            }
            else {
                file = "[unknown file]";
            }
        }
        if (func == NULL) {
            printf("%p : %s : %s %s \n",
                (void*) frame.AddrPC.Offset,
                module_name,
                file,
                bfd_errors[err]);
        }
        else {
            printf("%p : %s : %s (%d) : in function (%s) \n",
                (void*) frame.AddrPC.Offset,
                module_name,
                file,
                line,
                func);
        }
    }
}

#include <psapi.h>
#include <dbghelp.h>
#define STACKWALK_MAX_NAMELEN 1024

void _backtrace2(void)
{
#ifdef _M_IX86
    auto machine = IMAGE_FILE_MACHINE_I386;
#elif _M_X64
    auto machine = IMAGE_FILE_MACHINE_AMD64;
#elif _M_IA64
    auto machine = IMAGE_FILE_MACHINE_IA64;
#else
#error "platform not supported!"
#endif

    // Initalize some memory
    HANDLE                          process = ::GetCurrentProcess();
    HANDLE                          thread = GetCurrentThread();

    // Initalize more memory
    CONTEXT                         context;
    STACKFRAME                      stack_frame;

    // Set some memory
    memset(&context, 0, sizeof(CONTEXT));
    memset(&stack_frame, 0, sizeof(STACKFRAME));

    RtlCaptureContext(&context);

    // Initalize a few things here and there
    stack_frame.AddrPC.Offset       = context.Rip;
    stack_frame.AddrPC.Mode         = AddrModeFlat;
    stack_frame.AddrStack.Offset    = context.Rsp;
    stack_frame.AddrStack.Mode      = AddrModeFlat;
    stack_frame.AddrFrame.Offset    = context.Rbp;
    stack_frame.AddrFrame.Mode      = AddrModeFlat;

    IMAGEHLP_SYMBOL64 *pSym =
      (IMAGEHLP_SYMBOL64*)malloc(sizeof(IMAGEHLP_SYMBOL64) + STACKWALK_MAX_NAMELEN);
    memset(pSym, 0, sizeof(IMAGEHLP_SYMBOL64) + STACKWALK_MAX_NAMELEN);
    pSym->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
    pSym->MaxNameLength = STACKWALK_MAX_NAMELEN;

    // Randomly saw this was supposed to be called prior to StackWalk so tried 
    // it
    if (!SymInitialize(process, 0, false)) {
        wprintf(L"SymInitialize unable to find process!! Error: %d\r\n", GetLastError());
    }

    CallstackEntry csEntry;

    for (ULONG frame = 0; ; frame++)
    {
printf("frame %d\n", (int)frame);
        // Check for frames
        BOOL result = StackWalk(machine, process, thread, &stack_frame, &context, 0,
            SymFunctionTableAccess, SymGetModuleBase, 0);

        csEntry.offset = s.AddrPC.Offset;
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

        // Get the file name of the file containing the function
//        TCHAR module_buffer[MaxPath];
//        DWORD mod_file = GetModuleFileName((HINSTANCE)module_base, 
//        module_buffer, MaxPath);
//        if ((module_base != 0) && (mod_file != 0)) {
//            module_info.module_name = module_buffer;
//        }

        // Initalize more memory and clear it out
        printf("offset %ld\n", stack_frame.AddrPC.Offset);
        if (SymGetSymFromAddr64(process, stack_frame.AddrPC.Offset, 
                                &csEntry.offsetFromSmybol, pSym)) {
            printf("got sym\n");
//            name_buffer = symbol->Name;
        }
        if (SymGetLineFromAddr64(process, stack_frame.AddrPC.Offset, 
                                 &csEntry.offsetFromLine, &line)) {
            printf("got line\n");
//            name_buffer = symbol->Name;
        }

#if 0
        // Initalize memory
        LPWSTR console_message = (LPWSTR) new TCHAR[MaxMsgLength];
        LPWSTR file_message = (LPWSTR) new TCHAR[MaxMsgLength];

        // Set some strings
        swprintf(console_message, MaxMsgLength, L">> Frame %02lu: called from: %016X Stack: %016X Frame: %016X Address return: %016X\r\n",
            frame, stack_frame.AddrPC.Offset, stack_frame.AddrStack.Offset, stack_frame.AddrFrame.Offset, stack_frame.AddrReturn.Offset);
        swprintf(file_message, MaxMsgLength, L"Frame %02lu: called from: %016X Stack: %016X Frame: %016X Address return: %016X\r\n",
            frame, stack_frame.AddrPC.Offset, stack_frame.AddrStack.Offset, stack_frame.AddrFrame.Offset, stack_frame.AddrReturn.Offset);

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

void testn (void)
{
    CONTEXT             context;
    STACKFRAME64        stack;

    RtlCaptureContext( &context );
    memset( &stack, 0, sizeof( STACKFRAME64 ) );

    struct bfd_set *set = (struct bfd_set *) calloc(1,sizeof(*set));
    printf("test1\n");
    _backtrace(set, 12, &context);
    printf("\n\n");

    printf("test2\n");
    _backtrace2();
    printf("\n\n");
    DIE("test");
}

void test1 (void) { testn(); }
void test2 (void) { test1(); }
void test3 (void) { test2(); }
void test4 (void) { test3(); }
void test5 (void) { test4(); }
void test (void) { test5(); }

#endif
