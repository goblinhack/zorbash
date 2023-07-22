//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include <stdlib.h>
#include <string.h>

void *myzalloc_(int size, const char *what, const char *file, const char *func, int line)
{
  TRACE_AND_INDENT();
  void *ptr = calloc(1, size);

  if (! ptr) { DIE("No memory, %s:%s():%u", file, func, line); }

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  return ptr;
}

void *mymalloc_(int size, const char *what, const char *file, const char *func, int line)
{
  TRACE_AND_INDENT();
  void *ptr = malloc(size);

  if (! ptr) { DIE("No memory, %s:%s():%u", file, func, line); }

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  return ptr;
}

void *myrealloc_(void *ptr, int size, const char *what, const char *file, const char *func, int line)
{
  TRACE_AND_INDENT();
  IF_DEBUG2 { ptrcheck_free(MTYPE_MISC, ptr, file, func, line); }

  ptr = realloc(ptr, size);
  if (! ptr) { DIE("No memory, %s:%s():%u", file, func, line); }

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  return ptr;
}

void myfree_(void *ptr, const char *file, const char *func, int line)
{
  TRACE_AND_INDENT();
  IF_DEBUG2 { ptrcheck_free(MTYPE_MISC, ptr, file, func, line); }

  free(ptr);
}

char *dupstr_(const char *in, const char *what, const char *file, const char *func, int line)
{
  TRACE_AND_INDENT();
  if (! in) {
    ERR("No string to duplicate");
    return nullptr;
  }

  char *ptr = strdup(in);
  if (! ptr) { DIE("No memory, %s:%s():%u", file, func, line); }

  int size = (__typeof__(size)) strlen(in);

  IF_DEBUG2 { ptrcheck_alloc(MTYPE_MISC, ptr, what, size, file, func, line); }

  return ptr;
}
