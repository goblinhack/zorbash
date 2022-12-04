//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#include <iostream>
#include <sstream>

//
// Single dimension array check
//
template < class TYPE > static inline void set(std::vector< TYPE > &container, std::size_t X, TYPE v)
{
  DODEBUG(std::cerr << "set [" << X << "] = " << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  container[ X ] = v;
}

template < class TYPE > static inline void incr(std::vector< TYPE > &container, std::size_t X, TYPE v)
{
  DODEBUG(std::cerr << "incr [" << X << "] = " << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  container[ X ] += v;
}

template < class TYPE > static inline void decr(std::vector< TYPE > &container, std::size_t X, TYPE v)
{
  DODEBUG(std::cerr << "decr [" << X << "] = " << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  container[ X ] -= v;
}

template < class TYPE > static inline void incr(std::vector< TYPE > &container, std::size_t X)
{
  DODEBUG(std::cerr << "incr [" << X << "]" << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  container[ X ]++;
}

template < class TYPE > static inline void decr(std::vector< TYPE > &container, std::size_t X)
{
  DODEBUG(std::cerr << "decr [" << X << "]" << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  container[ X ]--;
}

template < class TYPE > static inline TYPE get(std::vector< TYPE > const &container, std::size_t X)
{
  DODEBUG(std::cerr << "get [" << X << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  DODEBUG(std::cerr << container[ X ] << std::endl);
  return (container[ X ]);
}

template < class TYPE > static inline TYPE &getref(std::vector< TYPE > &container, std::size_t X)
{
  DODEBUG(std::cerr << "getref [" << X << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  return (container[ X ]);
}

template < class TYPE > static inline TYPE *getptr(std::vector< TYPE > &container, std::size_t X)
{
  DODEBUG(std::cerr << "getptr [" << X << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
  }
  return (&container[ X ]);
}

//
// Two dimension array check
//
template < class TYPE >
static inline void set(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y, TYPE v)
{
  DODEBUG(std::cerr << "set [" << X << "][" << Y << "] = " << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
  }
  container[ X ][ Y ] = v;
}

template < class TYPE >
static inline void incr(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y, TYPE v)
{
  DODEBUG(std::cerr << "incr [" << X << "][" << Y << "]" << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
  }
  container[ X ][ Y ] += v;
}

template < class TYPE >
static inline void decr(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y, TYPE v)
{
  DODEBUG(std::cerr << "decr [" << X << "][" << Y << "]" << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
  }
  container[ X ][ Y ] -= v;
}

template < class TYPE >
static inline TYPE &getref(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y)
{
  DODEBUG(std::cerr << "getref [" << X << "][" << Y << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
  }
  return (container[ X ][ Y ]);
}

template < class TYPE >
static inline TYPE *getptr(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y)
{
  DODEBUG(std::cerr << "getptr [" << X << "][" << Y << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
  }
  return (&container[ X ][ Y ]);
}

template < class TYPE >
static inline TYPE get(std::vector< std::vector< TYPE > > const &container, std::size_t X, std::size_t Y)
{
  DODEBUG(std::cerr << "get [" << X << "][" << Y << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
  }
  DODEBUG(std::cerr << container[ X ][ Y ] << std::endl);
  return (container[ X ][ Y ]);
}

//
// Three dimension array check
//
template < class TYPE >
static inline void set(std::vector< std::vector< std::vector< TYPE > > > &container, std::size_t X, std::size_t Y,
                       std::size_t Z, TYPE v)
{
  DODEBUG(std::cerr << "set [" << X << "][" << Y << "][" << Z << "] = " << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
  }
  container[ X ][ Y ][ Z ] = v;
}

template < class TYPE >
static inline TYPE get(std::vector< std::vector< std::vector< TYPE > > > const &container, std::size_t X,
                       std::size_t Y, std::size_t Z)
{
  DODEBUG(std::cerr << "get [" << X << "][" << Y << "][" << Z << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
  }
  DODEBUG(std::cerr << container[ X ][ Y ][ Z ] << std::endl);
  return (container[ X ][ Y ][ Z ]);
}

template < class TYPE >
static inline TYPE &getref(std::vector< std::vector< std::vector< TYPE > > > &container, std::size_t X, std::size_t Y,
                           std::size_t Z)
{
  DODEBUG(std::cerr << "getref [" << X << "][" << Y << "][" << Z << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
  }
  return (container[ X ][ Y ][ Z ]);
}

template < class TYPE >
static inline TYPE *getptr(std::vector< std::vector< std::vector< TYPE > > > &container, std::size_t X, std::size_t Y,
                           std::size_t Z)
{
  DODEBUG(std::cerr << "getptr [" << X << "][" << Y << "][" << Z << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
  }
  return (&container[ X ][ Y ][ Z ]);
}

//
// Four dimension array check
//
template < class TYPE >
static inline void set(std::vector< std::vector< std::vector< std::vector< TYPE > > > > &container, std::size_t X,
                       std::size_t Y, std::size_t Z, std::size_t I, TYPE v)
{
  DODEBUG(std::cerr << "set [" << X << "][" << Y << "][" << Z << "][" << I << "] = " << v << std::endl);
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
    ASSERT(I >= 0)
    ASSERT(I < container[ X ][ Y ][ Z ].size())
  }
  container[ X ][ Y ][ Z ][ I ] = v;
}

template < class TYPE >
static inline TYPE get(std::vector< std::vector< std::vector< std::vector< TYPE > > > > const &container,
                       std::size_t X, std::size_t Y, std::size_t Z, std::size_t I)
{
  DODEBUG(std::cerr << "getptr [" << X << "][" << Y << "][" << Z << "][" << I << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
    ASSERT(I >= 0)
    ASSERT(I < container[ X ][ Y ][ Z ].size())
  }
  DODEBUG(std::cerr << container[ X ][ Y ][ Z ][ I ] << std::endl);
  return (container[ X ][ Y ][ Z ][ I ]);
}

template < class TYPE >
static inline TYPE &getref(std::vector< std::vector< std::vector< std::vector< TYPE > > > > &container, std::size_t X,
                           std::size_t Y, std::size_t Z, std::size_t I)
{
  DODEBUG(std::cerr << "getref [" << X << "][" << Y << "][" << Z << "][" << I << "] = ");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
    ASSERT(I >= 0)
    ASSERT(I < container[ X ][ Y ][ Z ].size())
  }
  return (container[ X ][ Y ][ Z ][ I ]);
}

template < class TYPE >
static inline TYPE *getptr(std::vector< std::vector< std::vector< std::vector< TYPE > > > > &container, std::size_t X,
                           std::size_t Y, std::size_t Z, std::size_t I)
{
  DODEBUG(std::cerr << "getref [" << X << "][" << Y << "][" << Z << "][" << I << "] = )");
  if (DEBUG2) {
    ASSERT_EX(X, >=, 0)
    ASSERT_EX(X, <, container.size())
    ASSERT_EX(Y, >=, 0)
    ASSERT_EX(Y, <, container[ X ].size())
    ASSERT_EX(Z, >=, 0)
    ASSERT_EX(Z, <, container[ X ][ Y ].size())
    ASSERT(I >= 0)
    ASSERT(I < container[ X ][ Y ][ Z ].size())
  }
  return (&container[ X ][ Y ][ Z ][ I ]);
}

#ifndef ENABLE_DEBUG_EXTRA_BOUNDS_CHECKS
template < class TYPE > static inline void set_no_check(std::vector< TYPE > &container, std::size_t X, TYPE v)
{
  container[ X ] = v;
}

template < class TYPE > static inline void no_check_incr(std::vector< TYPE > &container, std::size_t X, TYPE v)
{
  container[ X ] += v;
}

template < class TYPE > static inline void no_check_decr(std::vector< TYPE > &container, std::size_t X, TYPE v)
{
  container[ X ] -= v;
}

template < class TYPE > static inline void no_check_incr(std::vector< TYPE > &container, std::size_t X)
{
  container[ X ]++;
}

template < class TYPE > static inline void no_check_decr(std::vector< TYPE > &container, std::size_t X)
{
  container[ X ]--;
}

template < class TYPE > static inline TYPE get_no_check(std::vector< TYPE > const &container, std::size_t X)
{
  return (container[ X ]);
}

template < class TYPE > static inline TYPE &getref_no_check(std::vector< TYPE > &container, std::size_t X)
{
  return (container[ X ]);
}

template < class TYPE > static inline TYPE *getptr_no_check(std::vector< TYPE > &container, std::size_t X)
{
  return (&container[ X ]);
}

//
// Two dimension array check
//
template < class TYPE >
static inline void set_no_check(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y, TYPE v)
{
  container[ X ][ Y ] = v;
}

template < class TYPE >
static inline void no_check_incr(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y, TYPE v)
{
  container[ X ][ Y ] += v;
}

template < class TYPE >
static inline void no_check_decr(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y, TYPE v)
{
  container[ X ][ Y ] -= v;
}

template < class TYPE >
static inline TYPE &getref_no_check(std::vector< std::vector< TYPE > > &container, std::size_t X, std::size_t Y)
{
  return (container[ X ][ Y ]);
}

template < class TYPE >
static inline TYPE get_no_check(std::vector< std::vector< TYPE > > const &container, std::size_t X, std::size_t Y)
{
  return (container[ X ][ Y ]);
}

//
// Three dimension array check
//
template < class TYPE >
static inline void set_no_check(std::vector< std::vector< std::vector< TYPE > > > &container, std::size_t X,
                                std::size_t Y, std::size_t Z, TYPE v)
{
  container[ X ][ Y ][ Z ] = v;
}

template < class TYPE >
static inline TYPE get_no_check(std::vector< std::vector< std::vector< TYPE > > > const &container, std::size_t X,
                                std::size_t Y, std::size_t Z)
{
  return (container[ X ][ Y ][ Z ]);
}

template < class TYPE >
static inline TYPE &getref_no_check(std::vector< std::vector< std::vector< TYPE > > > &container, std::size_t X,
                                    std::size_t Y, std::size_t Z)
{
  return (container[ X ][ Y ][ Z ]);
}

//
// Four dimension array check
//
template < class TYPE >
static inline void set_no_check(std::vector< std::vector< std::vector< std::vector< TYPE > > > > &container,
                                std::size_t X, std::size_t Y, std::size_t Z, std::size_t I, TYPE v)
{
  container[ X ][ Y ][ Z ][ I ] = v;
}

template < class TYPE >
static inline TYPE get_no_check(std::vector< std::vector< std::vector< std::vector< TYPE > > > > const &container,
                                std::size_t X, std::size_t Y, std::size_t Z, std::size_t I)
{
  return (container[ X ][ Y ][ Z ][ I ]);
}

template < class TYPE >
static inline TYPE &getref_no_check(std::vector< std::vector< std::vector< std::vector< TYPE > > > > &container,
                                    std::size_t X, std::size_t Y, std::size_t Z, std::size_t I)
{
  return (container[ X ][ Y ][ Z ][ I ]);
}
#endif

#ifdef ENABLE_DEBUG_EXTRA_BOUNDS_CHECKS
#undef getptr_no_check
#define getptr_no_check getptr
#undef getref_no_check
#define getref_no_check getref
#undef set_no_check
#define set_no_check set
#undef get_no_check
#define get_no_check get
#undef no_check_incr
#define no_check_incr incr
#undef no_check_decr
#define no_check_decr decr
#endif
