#ifndef _MY__PTRCHECK_H__
#define _MY__PTRCHECK_H__

//
// __FUNCTION__ is not a preprocessor directive so we can't convert it into a
// string
//
#define PTRCHECK_AT \
  std::string(__FILE__), std::string(__PRETTY_FUNCTION__), __LINE__

//
// util.c
//
void *myzalloc_(int size, std::string what, std::string func, std::string file, int line);
void *mymalloc_(int size, std::string what, std::string func, std::string file, int line);
void *myrealloc_(void *ptr, int size, std::string what, std::string func, std::string file, int line);
void myfree_(void *ptr, std::string func, std::string file, int line);
char *dupstr_(const char *in, std::string what, std::string func, std::string file, int line);
char *strsub_(const char *in, const char *old, const char *replace_with, std::string what, std::string file, std::string func, int line);

#define myzalloc(__size__, __what__) \
    myzalloc_((__size__), (__what__), PTRCHECK_AT)

#define mymalloc(__size__, __what__) \
    mymalloc_((__size__), (__what__), PTRCHECK_AT)

#define myrealloc(__ptr__, __size__, __what__) \
    myrealloc_((__ptr__), (__size__), (__what__), PTRCHECK_AT)

#define myfree(__ptr__)             \
    myfree_((__ptr__), PTRCHECK_AT)

#define dupstr(__ptr__, __what__)   \
    dupstr_((__ptr__), (__what__), PTRCHECK_AT)

#define strsub(a, b, c, __what__) \
    strsub_(a, b, c, (__what__), PTRCHECK_AT)

void *ptrcheck_alloc(const void *ptr, std::string what, int size, std::string file, std::string func, int line);
int ptrcheck_verify(const void *ptr, std::string &file, std::string &func, int line);
int ptrcheck_free(void *ptr, std::string file, std::string func, int line);
void ptrcheck_leak_print(void);

#ifdef ENABLE_PTRCHECK
#define newptr(__ptr__, __what__) \
    (ptrcheck_alloc((__ptr__), (__what__), sizeof(*(__ptr__)), PTRCHECK_AT))
#define oldptr(__ptr__) (ptrcheck_free((__ptr__), PTRCHECK_AT))
#define verify(__ptr__)                                      \
{                                                            \
    static std::string a = std::string(__FILE__);            \
    static std::string b = std::string(__PRETTY_FUNCTION__); \
    ptrcheck_verify((__ptr__), a, b, __LINE__);              \
}
#else
#define newptr(__ptr__, __what__)
#define oldptr(__ptr__)
#define verify(__ptr__)
#endif

#endif // __PTRCHECK_H__
