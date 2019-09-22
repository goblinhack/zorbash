#include <array>

//
// Single dimension array check
//
template<class TYPE, std::size_t XDIM>
void set(std::array<TYPE,XDIM>& arr, std::size_t X, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    arr[X] = v;
}    

template<class TYPE, std::size_t XDIM>
TYPE& get(std::array<TYPE,XDIM> & arr, std::size_t X){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    return (arr[X]);
}    

//
// Two dimension array check
//
template<class TYPE, std::size_t XDIM, std::size_t YDIM>
void set(std::array<std::array<TYPE,YDIM>,XDIM>& arr, 
         std::size_t X, std::size_t Y, TYPE v){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    arr[X][Y] = v;
}    

template<class TYPE, std::size_t XDIM, std::size_t YDIM>
TYPE& get(std::array<std::array<TYPE,YDIM>,XDIM> & arr, 
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
TYPE& get(std::array<std::array<std::array<TYPE,ZDIM>,YDIM>,XDIM> & arr, 
          std::size_t X, std::size_t Y, std::size_t Z){_
    ASSERT(X >= 0)
    ASSERT(X < arr.size())
    ASSERT(Y >= 0)
    ASSERT(Y < arr[X].size())
    ASSERT(Z >= 0)
    ASSERT(Z < arr[X][Y].size())
    return (arr[X][Y][Z]);
}    
