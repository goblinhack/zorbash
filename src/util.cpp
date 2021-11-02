//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include <string.h>

void *myzalloc_(int size, std::string what, std::string file, std::string func, int line)
{
  TRACE_AND_INDENT();
  void *ptr = calloc(1, size);

  if (! ptr) {
    DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
  }

  IF_DEBUG2 { ptrcheck_alloc(ptr, what, size, file, func, line); }

  return (ptr);
}

void *mymalloc_(int size, std::string what, std::string file, std::string func, int line)
{
  TRACE_AND_INDENT();
  void *ptr = malloc(size);

  if (! ptr) {
    DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
  }

  IF_DEBUG2 { ptrcheck_alloc(ptr, what, size, file, func, line); }

  return (ptr);
}

void *myrealloc_(void *ptr, int size, std::string what, std::string file, std::string func, int line)
{
  TRACE_AND_INDENT();
  IF_DEBUG2 { ptrcheck_free(ptr, file, func, line); }

  ptr = realloc(ptr, size);
  if (! ptr) {
    DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
  }

  IF_DEBUG2 { ptrcheck_alloc(ptr, what, size, file, func, line); }

  return (ptr);
}

void myfree_(void *ptr, std::string file, std::string func, int line)
{
  TRACE_AND_INDENT();
  IF_DEBUG2 { ptrcheck_free(ptr, file, func, line); }

  free(ptr);
}

char *dupstr_(const char *in, std::string what, std::string file, std::string func, int line)
{
  TRACE_AND_INDENT();
  if (! in) {
    ERR("No string to duplicate");
    return 0;
  }

  char *ptr = strdup(in);
  if (! ptr) {
    DIE("No memory, %s:%s():%u", file.c_str(), func.c_str(), line);
  }

  int size = (__typeof__(size)) strlen(in);

  IF_DEBUG2 { ptrcheck_alloc(ptr, what, size, file, func, line); }

  return (ptr);
}
