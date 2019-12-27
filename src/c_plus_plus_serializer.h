#ifndef C_PLUS_PLUS_SERIALIZER
#define C_PLUS_PLUS_SERIALIZER
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//
// 64 bits for serializing is a bit overkill for serializing, so use int
//
#ifdef USE_SIZE_T
typedef size_t my_size_t;
#else
typedef int my_size_t;
#endif

template<typename TYPE> struct Bits { TYPE t; };

template<typename TYPE>
static inline Bits<TYPE&> bits(TYPE &t)
{
    return Bits<TYPE&>{t};
}

template<typename TYPE>
static inline Bits<const TYPE&> bits(const TYPE& t)
{
    return Bits<const TYPE&>{t};
}

////////////////////////////////////////////////////////////////////////////
// Read/write POD types
////////////////////////////////////////////////////////////////////////////
template<typename TYPE>
static inline std::istream& operator>>(std::istream& in, Bits<TYPE&> b)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read " << sizeof(TYPE) << " bytes" << std::endl;
#endif
    return in.read(reinterpret_cast<char*>(&b.t), sizeof(TYPE));
}

template<typename TYPE>
static inline std::ostream& operator<<(std::ostream &out, Bits<TYPE&> const b)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write " << sizeof(TYPE) << " bytes" << std::endl;
#endif
    // reinterpret_cast is for pointer conversion
    // static_cast is for compatible pointer conversion
    return out.write(reinterpret_cast<const char*>(&(b.t)), sizeof(TYPE));
}

////////////////////////////////////////////////////////////////////////////
// Read/write std::string
////////////////////////////////////////////////////////////////////////////
static inline std::istream& operator>>(std::istream& in, Bits<std::string &> v)
{
    my_size_t sz = 0;
    in >> bits(sz);
    if (in && sz) {
        std::vector<char> tmp(sz);
        in.read(tmp.data(), sz);
        v.t.assign(tmp.data(), sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "read '" << v.t << "'" << std::endl;
#endif
    }

    return in;
}

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const std::string &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write const '" << v.t << "'" << std::endl;
#endif
    my_size_t sz = v.t.size();
    return out << bits(sz) << v.t;
}

static inline
std::ostream& operator<<(std::ostream &out, Bits<std::string &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write '" << v.t << "'" << std::endl;
#endif
    my_size_t sz = v.t.size();
    return out << bits(sz) << v.t;
}

////////////////////////////////////////////////////////////////////////////
// Read/write std::wstring
////////////////////////////////////////////////////////////////////////////
static inline std::istream& operator>>(std::istream& in, Bits<std::wstring &> v)
{
    my_size_t sz = 0;
    in >> bits(sz);
    if (in && sz) {
        std::vector<wchar_t> tmp(sz);
        while (sz--) {
            wchar_t tmp;
            in >> bits(tmp);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
            std::cout << "read '" << tmp << "'" << std::endl;
#endif
            v.t += tmp;
        }
    }

    return in;
}

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const std::wstring &> const v)
{
    my_size_t sz = v.t.size();
    out << bits(sz);
    for (auto tmp : v.t) {
        out << bits(tmp);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "write const '" << tmp << "'" << std::endl;
#endif
    }
    return out;
}

static inline
std::ostream& operator<<(std::ostream &out, Bits<std::wstring &> const v)
{
    my_size_t sz = v.t.size();
    out << bits(sz);
    for (auto tmp : v.t) {
        out << bits(tmp);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "write '" << tmp << "'" << std::endl;
#endif
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////
// Read/write wchar_t
////////////////////////////////////////////////////////////////////////////
static inline std::istream& operator>>(std::istream& in, Bits<wchar_t &> v)
{
    if (sizeof(wchar_t) == 4) {
        unsigned char _a, _b, _c, _d;
        in >> bits(_a);
        in >> bits(_b);
        in >> bits(_c);
        in >> bits(_d);
        v.t = (_a << 24) | (_b << 16) | (_c << 8) | _d;
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "read '" << _a << "'" << std::endl;
        std::cout << "read '" << _b << "'" << std::endl;
        std::cout << "read '" << _c << "'" << std::endl;
        std::cout << "read '" << _d << "'" << std::endl;
#endif
    } else if (sizeof(wchar_t) == 2) {
        unsigned char _a, _b;
        in >> bits(_a);
        in >> bits(_b);
        v.t = (_a << 8) | _b;
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "read '" << _a << "'" << std::endl;
        std::cout << "read '" << _b << "'" << std::endl;
#endif
    } else {
        static_assert(sizeof(wchar_t) <= 4, "wchar_t is greater that 32 bit");
    }

    return in;
}

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const wchar_t &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write const '" << v.t << "'" << std::endl;
#endif
    if (sizeof(wchar_t) == 4) {
        unsigned char _a, _b, _c, _d;
        _a = (v.t & (0xff000000)) >> 24; out << bits(_a);
        _b = (v.t & (0x00ff0000)) >> 16; out << bits(_b);
        _c = (v.t & (0x0000ff00)) >> 8;  out << bits(_c);
        _d = (v.t & (0x000000ff)) >> 0;  out << bits(_d);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "write '" << _a << "'" << std::endl;
        std::cout << "write '" << _b << "'" << std::endl;
        std::cout << "write '" << _c << "'" << std::endl;
        std::cout << "write '" << _d << "'" << std::endl;
#endif
    } else if (sizeof(wchar_t) == 2) {
        unsigned char _a, _b;
        _a = (v.t & (0xff00)) >> 8;  out << bits(_a);
        _b = (v.t & (0x00ff)) >> 0;  out << bits(_b);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "write '" << _a << "'" << std::endl;
        std::cout << "write '" << _b << "'" << std::endl;
#endif
    } else {
        static_assert(sizeof(wchar_t) <= 4, "wchar_t is greater that 32 bit");
    }
    return (out);
}

static inline
std::ostream& operator<<(std::ostream &out, Bits<wchar_t &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write const '" << v.t << "'" << std::endl;
#endif
    if (sizeof(wchar_t) == 4) {
        unsigned char _a, _b, _c, _d;
        _a = (v.t & (0xff000000)) >> 24; out << bits(_a);
        _b = (v.t & (0x00ff0000)) >> 16; out << bits(_b);
        _c = (v.t & (0x0000ff00)) >> 8;  out << bits(_c);
        _d = (v.t & (0x000000ff)) >> 0;  out << bits(_d);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "write '" << _a << "'" << std::endl;
        std::cout << "write '" << _b << "'" << std::endl;
        std::cout << "write '" << _c << "'" << std::endl;
        std::cout << "write '" << _d << "'" << std::endl;
#endif
    } else if (sizeof(wchar_t) == 2) {
        unsigned char _a, _b;
        _a = (v.t & (0xff00)) >> 8;  out << bits(_a);
        _b = (v.t & (0x00ff)) >> 0;  out << bits(_b);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
        std::cout << "write '" << _a << "'" << std::endl;
        std::cout << "write '" << _b << "'" << std::endl;
#endif
    } else {
        static_assert(sizeof(wchar_t) <= 4, "wchar_t is greater that 32 bit");
    }
    return (out);
}

////////////////////////////////////////////////////////////////////////////
// Read/write simple container
////////////////////////////////////////////////////////////////////////////
template <
  class T, 
  template <typename ELEM, typename ALLOC = std::allocator<ELEM> > class C>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<C<T> &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write container<T> " << v.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

template <
  class T, 
  template <typename ELEM, typename ALLOC = std::allocator<ELEM> > class C>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const C<T> &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write container<const T> " << v.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

template <
  class T, 
  template <typename ELEM, typename ALLOC = std::allocator<ELEM> > class C>
static inline std::istream& operator>>(std::istream &in, Bits<C<T> &> v)
{
    my_size_t sz = 0;
    in >> bits(sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read container<T> " << sz << " elems" << std::endl;
#endif
    if (in && sz) {
        while (sz--) {
            T s;
            in >> bits(s);
            v.t.push_back(s);
        }
    }

    return in;
}

////////////////////////////////////////////////////////////////////////////
// Read/write std::array
////////////////////////////////////////////////////////////////////////////
template <
  class T, 
  std::size_t N,
  template <typename ELEM, std::size_t > class C>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<C<T, N> &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write array container<T> " << v.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

template <
  class T, 
  std::size_t N,
  template <typename ELEM, std::size_t > class C>
static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<const C<T, N> &> const v)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write array container<const T> " << v.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

template <
  class T, 
  std::size_t N,
  template <typename ELEM, std::size_t > class C>
static inline std::istream& operator>>(std::istream &in, Bits<C<T, N> &> v)
{
    my_size_t sz = 0;
    in >> bits(sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read array container<T> " << sz << " elems" << std::endl;
#endif
    if (in && sz) {
        for (auto n = 0; n < sz; n++) {
            T s;
            in >> bits(s);
            v.t[n] = s;
        }
    }

    return in;
}

////////////////////////////////////////////////////////////////////////////
// Read/write map
////////////////////////////////////////////////////////////////////////////

template <
    template < class K,
               class V,
               class Compare = std::less<K>,
               class Alloc = std::allocator<std::pair<const K,V> >
               > class M,
    class K, class V >

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<M<K,V> &> const m)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write map<K,V> " << m.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = m.t.size();
    out << bits(sz);
    for (auto i : m.t) { out << bits(i.first) << bits(i.second); }
    return (out);
}

template <
    template < class K,
               class V,
               class Compare = std::less<K>,
               class Alloc = std::allocator<std::pair<const K,V> >
               > class M,
    class K, class V >

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<M<K,const V> &> const m)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write map<K,const V> " << m.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = m.t.size();
    out << bits(sz);
    for (auto i : m.t) { out << bits(i.first) << bits(i.second); }
    return (out);
}

template <
    template < class K,
               class V,
               class Compare = std::less<K>,
               class Alloc = std::allocator<std::pair<const K,V> >
               > class M,
    class K, class V >

static inline std::istream& operator>>(std::istream &in, 
                                       Bits<M<K,V> &> m)
{
    my_size_t sz = 0;
    in >> bits(sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read map<K,V> " << sz << " elems" << std::endl;
#endif
    if (in && sz) {
        while (sz--) {
            K k;
            V v;
            in >> bits(k) >> bits(v);
            m.t.insert(std::make_pair(k, v));
        }
    }

    return in;
}

////////////////////////////////////////////////////////////////////////////
// Read/write unordered_map
////////////////////////////////////////////////////////////////////////////

template <
    template < class K,
               class T,
               class Hash = std::hash<K>,
               class Pred = std::equal_to<K>,
               class Alloc = std::allocator< std::pair<const K,T> >
               > class M,
    class K, class V >

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<M<K,V> &> const m)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write unordered_map<K,V> " << m.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = m.t.size();
    out << bits(sz);
    for (auto i : m.t) { out << bits(i.first) << bits(i.second); }
    return (out);
}

template <
    template < class K,
               class T,
               class Hash = std::hash<K>,
               class Pred = std::equal_to<K>,
               class Alloc = std::allocator< std::pair<const K,T> >
               > class M,
    class K, class V >

static inline std::ostream& operator<<(std::ostream &out, 
                                       Bits<M<K,const V> &> const m)
{
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "write unordered_map<K,const V> " << m.t.size() << " elems" << std::endl;
#endif
    my_size_t sz = m.t.size();
    out << bits(sz);
    for (auto i : m.t) { out << bits(i.first) << bits(i.second); }
    return (out);
}

template <
    template < class K,
               class T,
               class Hash = std::hash<K>,
               class Pred = std::equal_to<K>,
               class Alloc = std::allocator< std::pair<const K,T> >
               > class M,
    class K, class V >

static inline std::istream& operator>>(std::istream &in, 
                                       Bits<M<K,V> &> m)
{
    my_size_t sz = 0;
    in >> bits(sz);
#ifdef DEBUG_C_PLUS_PLUS_SERIALIZER
    std::cout << "read unordered_map<K,V> " << sz << " elems" << std::endl;
#endif
    if (in && sz) {
        while (sz--) {
            K k;
            V v;
            in >> bits(k) >> bits(v);
            m.t.insert(std::make_pair(k, v));
        }
    }

    return in;
}
#endif /* C_PLUS_PLUS_SERIALIZER */
