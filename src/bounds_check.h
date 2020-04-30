#include <assert.h>
#include <iostream>

#ifdef ENABLE_ABORT
#define DOABORT abort();
#else
#define DOABORT
#endif

#ifdef DEBUG
#define DODEBUG(x) x
#else
#define DODEBUG(x)
#endif

#ifdef ENABLE_ASSERT
#define ASSERT(x) \
    if (! (x)) { \
        std::cerr << "Assert '" << #x << "' failed at line " \
                  << __LINE__ << ", file " << __FILE__ \
                  << ", function " << __FUNCTION__ << "()" << std::endl; \
        DOABORT \
    }
#else
#define ASSERT(x)
#endif

// Based on
// https://stackoverflow.com/questions/2193544/how-to-print-additional-information-when-assert-fails
#ifndef NDEBUG
#define ASSERT_EX(left, operator, right) \
    if (!((left) operator (right))) { \
        std::cerr << "ASSERT FAILED: " << #left << " " << #operator << " " << #right << " @ " << __FILE__ << ":" << __PRETTY_FUNCTION__ << " line " << __LINE__ << " " << #left << "=" << (left) << "; " << #right << "=" << (right) << std::endl; \
        ASSERT(left operator right); \
    }
#else
#define ASSERT_EX(left, operator, right) \
    ASSERT(left operator right);
#endif
