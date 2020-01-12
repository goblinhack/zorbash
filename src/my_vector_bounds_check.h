#include <vector>

//
// Single dimension vector check
//
template<class TYPE>
static inline
void set(std::vector<TYPE>& vec, std::size_t X, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    vec[X] = v;
}

template<class TYPE>
static inline
TYPE get(std::vector<TYPE> const &vec, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    return (vec[X]);
}

template<class TYPE>
static inline
TYPE& getref(std::vector<TYPE> &vec, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    return (vec[X]);
}

//
// Two dimension vector check
//
template<class TYPE>
static inline
void set(std::vector<std::vector<TYPE>>& vec,
         std::size_t X, std::size_t Y, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    ASSERT(Y >= 0)
    ASSERT(Y < vec[X].size())
    vec[X][Y] = v;
}

template<class TYPE>
static inline
TYPE& get(std::vector<std::vector<TYPE>> const &vec,
          std::size_t X, std::size_t Y){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    ASSERT(Y >= 0)
    ASSERT(Y < vec[X].size())
    return (vec[X][Y]);
}

template<class TYPE>
static inline
TYPE& getref(std::vector<std::vector<TYPE>> &vec,
             std::size_t X, std::size_t Y){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    ASSERT(Y >= 0)
    ASSERT(Y < vec[X].size())
    return (vec[X][Y]);
}

//
// Three dimension vector check
//
template<class TYPE>
static inline
void set(std::vector<std::vector<std::vector<TYPE>>>& vec,
         std::size_t X, std::size_t Y, std::size_t Z, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    ASSERT(Y >= 0)
    ASSERT(Y < vec[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < vec[X][Y].size())
    vec[X][Y][Z] = v;
}

template<class TYPE>
static inline
TYPE get(std::vector<std::vector<std::vector<TYPE>>> const &vec,
         std::size_t X, std::size_t Y, std::size_t Z){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    ASSERT(Y >= 0)
    ASSERT(Y < vec[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < vec[X][Y].size())
    return (vec[X][Y][Z]);
}

template<class TYPE>
static inline
TYPE& getref(std::vector<std::vector<std::vector<TYPE>>> & vec,
             std::size_t X, std::size_t Y, std::size_t Z){_
    ASSERT(X >= 0)
    ASSERT(X < vec.size())
    ASSERT(Y >= 0)
    ASSERT(Y < vec[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < vec[X][Y].size())
    return (vec[X][Y][Z]);
}
