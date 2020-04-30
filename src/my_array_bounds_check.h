#pragma once
#include <array>
#include "bounds_check.h"

//
// Single dimension array check
//
template<class TYPE, std::size_t XDIM>
static inline
void set(std::array<TYPE,XDIM>& container, std::size_t X, TYPE v){_
    DODEBUG(std::cerr << "set [" << X << "] = " << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    container[X] = v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr(std::array<TYPE,XDIM>& container, std::size_t X, TYPE v){_
    DODEBUG(std::cerr << "incr [" << X << "] = " << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    container[X] += v;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr(std::array<TYPE,XDIM>& container, std::size_t X, TYPE v){_
    DODEBUG(std::cerr << "decr [" << X << "] = " << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    container[X] -= v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr(std::array<TYPE,XDIM>& container, std::size_t X){_
    DODEBUG(std::cerr << "incr [" << X << "]" << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    container[X] ++;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr(std::array<TYPE,XDIM>& container, std::size_t X){_
    DODEBUG(std::cerr << "decr [" << X << "]" << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    container[X] --;
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE get(std::array<TYPE,XDIM> const &container, std::size_t X){_
    DODEBUG(std::cerr << "get [" << X << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    DODEBUG(std::cerr << container[X] << std::endl);
    return (container[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE& getref(std::array<TYPE,XDIM> &container, std::size_t X){_
    DODEBUG(std::cerr << "getref [" << X << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    return (container[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE* getptr(std::array<TYPE,XDIM> &container, std::size_t X){_
    DODEBUG(std::cerr << "getptr [" << X << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    return (&container[X]);
}

//
// Two dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void set(std::array<std::array<TYPE,YDIM>,XDIM>& container,
         std::size_t X, std::size_t Y, TYPE v){_
    DODEBUG(std::cerr << "set [" << X << "][" << Y << "] = " << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    container[X][Y] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void incr(std::array<std::array<TYPE,YDIM>,XDIM>& container,
          std::size_t X, std::size_t Y, TYPE v){_
    DODEBUG(std::cerr << "incr [" << X << "][" << Y << "]" << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    container[X][Y] += v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void decr(std::array<std::array<TYPE,YDIM>,XDIM>& container,
          std::size_t X, std::size_t Y, TYPE v){_
    DODEBUG(std::cerr << "decr [" << X << "][" << Y << "]" << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    container[X][Y] -= v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE& getref(std::array<std::array<TYPE,YDIM>,XDIM> &container,
             std::size_t X, std::size_t Y){_
    DODEBUG(std::cerr << "getref [" << X << "][" << Y << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    return (container[X][Y]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE* getptr(std::array<std::array<TYPE,YDIM>,XDIM> &container,
             std::size_t X, std::size_t Y){_
    DODEBUG(std::cerr << "getptr [" << X << "][" << Y << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    return (&container[X][Y]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE get(std::array<std::array<TYPE,YDIM>,XDIM> const &container,
         std::size_t X, std::size_t Y){_
    DODEBUG(std::cerr << "get [" << X << "][" << Y << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    DODEBUG(std::cerr << container[X][Y] << std::endl);
    return (container[X][Y]);
}

//
// Three dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
void set(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM>& container,
         std::size_t X, std::size_t Y, std::size_t Z, TYPE v){_
    DODEBUG(std::cerr << "set [" << X << "][" << Y << "][" << Z << "] = " << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    container[X][Y][Z] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE get(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> const &container,
         std::size_t X, std::size_t Y, std::size_t Z){_
    DODEBUG(std::cerr << "get [" << X << "][" << Y << "][" << Z << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    DODEBUG(std::cerr << container[X][Y][Z] << std::endl);
    return (container[X][Y][Z]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE& getref(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> &container,
             std::size_t X, std::size_t Y, std::size_t Z){_
    DODEBUG(std::cerr << "getref [" << X << "][" << Y << "][" << Z << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    return (container[X][Y][Z]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE* getptr(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> &container,
             std::size_t X, std::size_t Y, std::size_t Z){_
    DODEBUG(std::cerr << "getptr [" << X << "][" << Y << "][" << Z << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    return (&container[X][Y][Z]);
}

//
// Four dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
void set(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM>& container,
         std::size_t X, std::size_t Y, std::size_t Z, std::size_t I, TYPE v){_
    DODEBUG(std::cerr << "set [" << X << "][" << Y << "][" << Z << "][" << I << "] = " << v << std::endl);
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < container[X][Y][Z].size())
    container[X][Y][Z][I] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE get(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> const &container,
          std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    DODEBUG(std::cerr << "getptr [" << X << "][" << Y << "][" << Z << "][" << I << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < container[X][Y][Z].size())
    DODEBUG(std::cerr << container[X][Y][Z][I] << std::endl);
    return (container[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE& getref(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> &container,
             std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    DODEBUG(std::cerr << "getref [" << X << "][" << Y << "][" << Z << "][" << I << "] = ");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < container[X][Y][Z].size())
    return (container[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE* getptr(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> &container,
             std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    DODEBUG(std::cerr << "getref [" << X << "][" << Y << "][" << Z << "][" << I << "] = )");
    ASSERT_EX(X,>=,0)
    ASSERT_EX(X,<,container.size())
    ASSERT_EX(Y,>=,0)
    ASSERT_EX(Y,<,container[X].size())
    ASSERT_EX(Z,>=,0)
    ASSERT_EX(Z,<,container[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < container[X][Y][Z].size())
    return (&container[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM>
static inline
void set_unsafe(std::array<TYPE,XDIM>& container, std::size_t X, TYPE v){_
    container[X] = v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr_unsafe(std::array<TYPE,XDIM>& container, std::size_t X, TYPE v){_
    container[X] += v;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr_unsafe(std::array<TYPE,XDIM>& container, std::size_t X, TYPE v){_
    container[X] -= v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr_unsafe(std::array<TYPE,XDIM>& container, std::size_t X){_
    container[X] ++;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr_unsafe(std::array<TYPE,XDIM>& container, std::size_t X){_
    container[X] --;
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE get_unsafe(std::array<TYPE,XDIM> const &container, std::size_t X){_
    return (container[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE& getref_unsafe(std::array<TYPE,XDIM> &container, std::size_t X){_
    return (container[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE* getptr_unsafe(std::array<TYPE,XDIM> &container, std::size_t X){_
    return (&container[X]);
}

//
// Two dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void set_unsafe(std::array<std::array<TYPE,YDIM>,XDIM>& container,
                std::size_t X, std::size_t Y, TYPE v){_
    container[X][Y] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void incr_unsafe(std::array<std::array<TYPE,YDIM>,XDIM>& container,
                 std::size_t X, std::size_t Y, TYPE v){_
    container[X][Y] += v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void decr_unsafe(std::array<std::array<TYPE,YDIM>,XDIM>& container,
                 std::size_t X, std::size_t Y, TYPE v){_
    container[X][Y] -= v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE& getref_unsafe(std::array<std::array<TYPE,YDIM>,XDIM> &container,
                    std::size_t X, std::size_t Y){_
    return (container[X][Y]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE get_unsafe(std::array<std::array<TYPE,YDIM>,XDIM> const &container,
                std::size_t X, std::size_t Y){_
    return (container[X][Y]);
}

//
// Three dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
void set_unsafe(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM>& container,
                std::size_t X, std::size_t Y, std::size_t Z, TYPE v){_
    container[X][Y][Z] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE get_unsafe(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> const &container,
                std::size_t X, std::size_t Y, std::size_t Z){_
    return (container[X][Y][Z]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE& getref_unsafe(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> &container,
                    std::size_t X, std::size_t Y, std::size_t Z){_
    return (container[X][Y][Z]);
}

//
// Four dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
void set_unsafe(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM>& container,
                std::size_t X, std::size_t Y, std::size_t Z, std::size_t I, TYPE v){_
    container[X][Y][Z][I] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE get_unsafe(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> const &container,
                std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    return (container[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE& getref_unsafe(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> &container,
                    std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    return (container[X][Y][Z][I]);
}
