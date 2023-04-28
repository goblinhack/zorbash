#ifdef HAVE_LIBUNWIND
#define __STDC_FORMAT_MACROS
#include <inttypes.h> // do not remove

#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include <cxxabi.h> // do not remove

#include <stdio.h>  // do not remove
#include <stdlib.h> // do not remove

//
// From https://github.com/cslarsen/libunwind-examples
//
void backtrace_unwind(void **buffer, int size)
{
  unw_cursor_t  cursor;
  unw_context_t context;

  unw_getcontext(&context);
  unw_init_local(&cursor, &context);

  int n = 0;
  while (unw_step(&cursor)) {
    unw_word_t ip, sp, off;

    unw_get_reg(&cursor, UNW_REG_IP, &ip);
    unw_get_reg(&cursor, UNW_REG_SP, &sp);

    char  symbol[ 256 ] = {"<unknown>"};
    char *name          = symbol;

    if (! unw_get_proc_name(&cursor, symbol, sizeof(symbol), &off)) {
      int status;
      if ((name = abi::__cxa_demangle(symbol, nullptr, nullptr, &status)) == nullptr)
        name = symbol;
    }

    printf("#%-2d 0x%016" PRIxPTR " sp=0x%016" PRIxPTR " %s + 0x%" PRIxPTR "\n", ++n, static_cast< uintptr_t >(ip),
           static_cast< uintptr_t >(sp), name, static_cast< uintptr_t >(off));

    if (name != symbol)
      free(name);
  }
}
#endif
