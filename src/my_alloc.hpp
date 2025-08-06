//
// Copyright goblinhack@gmail.com
//
#pragma once

#ifndef _MY_ALLOC_H
#define _MY_ALLOC_H

#if defined(__MINGW32__)
#define HEAP_ALLOC(var, size)                                                                                        \
  void *var;                                                                                                         \
  var = malloc(size + size / 16 + 64 + 3);                                                                           \
  if (! var) {                                                                                                       \
    ERR("malloc failed for size %" PRIu32, (uint32_t) size);                                                         \
  }
#else
#define HEAP_ALLOC(var, size)                                                                                        \
  void *var;                                                                                                         \
  if (posix_memalign(&var, sizeof(lzo_align_t), size + size / 16 + 64 + 3)) {                                        \
    ERR("posix_memalign failed for size %" PRIu32, (uint32_t) size);                                                 \
  }
#endif

#endif
