/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"

void
Game::save (void)
{_
    CON("save %s", appdata.c_str());
}

void
Game::load (void)
{_
    CON("load %s", appdata.c_str());
}

#if 0
//struct to hold the value:
template<typename T> struct bits_t { T t; }; //no constructor necessary
//functions to infer type, construct bits_t with a member initialization list
//use a reference to avoid copying. The non-const version lets us extract too
template<typename T> bits_t<T&> bits(T &t) { return bits_t<T&>{t}; }
template<typename T> bits_t<const T&> bits(const T& t) { 
return bits_t<const T&>{t}; }
//insertion operator to call ::write() on whatever type of stream
template<typename S, typename T>
S& operator<<(S &s, bits_t<T> b) {
    return s.write((char*)&b.t, sizeof(T));
}
//extraction operator to call ::read(), require a non-const reference here
template<typename S, typename T>
S& operator>>(S& s, bits_t<T&> b) {
    return s.read((char*)&b.t, sizeof(T));
}

i
//writing
std::ofstream f = /*open a file*/;
int a = 5, b = -1, c = 123456;
f << bits(a) << bits(b) << bits(c);

//reading
std::ifstream f2 = /*open a file*/;
int a, b, c;
f >> bits(a) >> bits(b) >> bits(c);


void test (void)
{
  std::ofstream output( "C:\\myfile.gif", std::ios::binary );
}
#endif
