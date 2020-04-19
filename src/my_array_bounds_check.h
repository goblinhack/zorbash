#include <array>

//
// Single dimension array check
//
template<class TYPE, std::size_t XDIM>
static inline
void set(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    arr[X] = v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    arr[X] += v;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    arr[X] -= v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr(std::array<TYPE,XDIM>& arr, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    arr[X] ++;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr(std::array<TYPE,XDIM>& arr, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    arr[X] --;
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE get(std::array<TYPE,XDIM> const &arr, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    return (arr[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE& getref(std::array<TYPE,XDIM> &arr, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    return (arr[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE* getptr(std::array<TYPE,XDIM> &arr, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    return (&arr[X]);
}

//
// Two dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void set(std::array<std::array<TYPE,YDIM>,XDIM>& arr,
         std::size_t X, std::size_t Y, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    arr[X][Y] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void incr(std::array<std::array<TYPE,YDIM>,XDIM>& arr,
          std::size_t X, std::size_t Y, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    arr[X][Y] += v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void decr(std::array<std::array<TYPE,YDIM>,XDIM>& arr,
          std::size_t X, std::size_t Y, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    arr[X][Y] -= v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE& getref(std::array<std::array<TYPE,YDIM>,XDIM> &arr,
             std::size_t X, std::size_t Y){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    return (arr[X][Y]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE get(std::array<std::array<TYPE,YDIM>,XDIM> const &arr,
         std::size_t X, std::size_t Y){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    return (arr[X][Y]);
}

//
// Three dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
void set(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM>& arr,
         std::size_t X, std::size_t Y, std::size_t Z, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    arr[X][Y][Z] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE get(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> const &arr,
          std::size_t X, std::size_t Y, std::size_t Z){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    return (arr[X][Y][Z]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE& getref(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> &arr,
             std::size_t X, std::size_t Y, std::size_t Z){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    return (arr[X][Y][Z]);
}

//
// Four dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
void set(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM>& arr,
         std::size_t X, std::size_t Y, std::size_t Z, std::size_t I, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < arr[X][Y][Z].size())
    arr[X][Y][Z][I] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE get(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> const &arr,
          std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < arr[X][Y][Z].size())
    return (arr[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE& getref(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> &arr,
             std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    ASSERT(I >= 0)
    ASSERT(I < arr[X][Y][Z].size())
    return (arr[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM>
static inline
void set_unsafe(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    arr[X] = v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr_unsafe(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    arr[X] += v;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr_unsafe(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    arr[X] -= v;
}

template<class TYPE, std::size_t XDIM>
static inline
void incr_unsafe(std::array<TYPE,XDIM>& arr, std::size_t X){_
    arr[X] ++;
}

template<class TYPE, std::size_t XDIM>
static inline
void decr_unsafe(std::array<TYPE,XDIM>& arr, std::size_t X){_
    arr[X] --;
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE get_unsafe(std::array<TYPE,XDIM> const &arr, std::size_t X){_
    return (arr[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE& getref_unsafe(std::array<TYPE,XDIM> &arr, std::size_t X){_
    return (arr[X]);
}

template<class TYPE, std::size_t XDIM>
static inline
TYPE* getptr_unsafe(std::array<TYPE,XDIM> &arr, std::size_t X){_
    return (&arr[X]);
}

//
// Two dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void set_unsafe(std::array<std::array<TYPE,YDIM>,XDIM>& arr,
                std::size_t X, std::size_t Y, TYPE v){_
    arr[X][Y] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void incr_unsafe(std::array<std::array<TYPE,YDIM>,XDIM>& arr,
                 std::size_t X, std::size_t Y, TYPE v){_
    arr[X][Y] += v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
void decr_unsafe(std::array<std::array<TYPE,YDIM>,XDIM>& arr,
                 std::size_t X, std::size_t Y, TYPE v){_
    arr[X][Y] -= v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE& getref_unsafe(std::array<std::array<TYPE,YDIM>,XDIM> &arr,
                    std::size_t X, std::size_t Y){_
    return (arr[X][Y]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
static inline
TYPE get_unsafe(std::array<std::array<TYPE,YDIM>,XDIM> const &arr,
                std::size_t X, std::size_t Y){_
    return (arr[X][Y]);
}

//
// Three dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
void set_unsafe(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM>& arr,
                std::size_t X, std::size_t Y, std::size_t Z, TYPE v){_
    arr[X][Y][Z] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE get_unsafe(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> const &arr,
                std::size_t X, std::size_t Y, std::size_t Z){_
    return (arr[X][Y][Z]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM>
static inline
TYPE& getref_unsafe(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> &arr,
                    std::size_t X, std::size_t Y, std::size_t Z){_
    return (arr[X][Y][Z]);
}

//
// Four dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
void set_unsafe(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM>& arr,
                std::size_t X, std::size_t Y, std::size_t Z, std::size_t I, TYPE v){_
    arr[X][Y][Z][I] = v;
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE get_unsafe(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> const &arr,
                std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    return (arr[X][Y][Z][I]);
}

template<class TYPE, std::size_t XDIM, std::size_t YDIM, std::size_t ZDIM, std::size_t IDIM>
static inline
TYPE& getref_unsafe(std::array<std::array<std::array<std::array<TYPE,IDIM>,ZDIM>,YDIM>,XDIM> &arr,
                    std::size_t X, std::size_t Y, std::size_t Z, std::size_t I){_
    return (arr[X][Y][Z][I]);
}
