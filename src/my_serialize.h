//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#ifndef _MY_SERIALIZE_H_
#define _MY_SERIALIZE_H_
#include <iostream>

template<typename TYPE> struct Bits { TYPE t; };

template<typename TYPE>
Bits<TYPE&> bits(TYPE &t)
{
    return Bits<TYPE&>{t};
}

template<typename TYPE>
Bits<const TYPE&> bits(const TYPE& t)
{
    return Bits<const TYPE&>{t};
}

template<typename TYPE>
std::istream& operator>>(std::istream& s, Bits<TYPE&> b)
{
    std::cout << "read " << sizeof(TYPE) << " bytes" << std::endl;
    return s.read((char*)(&b.t), sizeof(TYPE));
}

template<typename TYPE>
std::ostream& operator<<(std::ostream &s, Bits<TYPE&> const b)
{
    std::cout << "write " << sizeof(TYPE) << " bytes" << std::endl;
    // reinterpret_cast is for pointer conversion
    // static_cast is for compatible pointer conversion
    return s.write(reinterpret_cast<const char*>(&(b.t)), sizeof(TYPE));
}
#endif
