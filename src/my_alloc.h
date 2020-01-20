//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//
#ifndef _MY_ALLOC_H
#define _MY_ALLOC_H

#if defined(__MINGW32__)
// https://stackoverflow.com/questions/10862121/undefined-reference-to-posix-memalign-using-mingw32
#define HEAP_ALLOC(var,size) \
    void *var; \
    var = _aligned_malloc(sizeof(lzo_align_t), size + size / 16 + 64 + 3);
#else
#define HEAP_ALLOC(var,size) \
    void *var; \
    posix_memalign(&var, sizeof(lzo_align_t), size + size / 16 + 64 + 3);
#endif

#endif
