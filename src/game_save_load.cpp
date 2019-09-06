/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_dungeon.h"
#include <fstream>

std::istream& operator>>(std::istream& in, Bits<std::string &> v)
{
    std::cout << "read string" << std::endl;
    size_t sz = 0;
    in >> bits(sz);
    if (in && sz) {
        std::vector<char> tmp(sz);
        in.read(tmp.data(), sz);
        v.t.assign(tmp.data(), sz);
    }

    return in;
}

std::ostream& operator<<(std::ostream &out, Bits<const std::string &> const v)
{
    std::cout << "write non const string" << std::endl;
    size_t sz = v.t.size();
    return out << bits(sz) << v.t;
}

std::ostream& operator<<(std::ostream &out, Bits<std::string &> const v)
{
    std::cout << "write string" << std::endl;
    size_t sz = v.t.size();
    return out << bits(sz) << v.t;
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<std::vector<std::string> &> const v)
{
    std::cout << "write vector string " << v.t.size() << " elems" << std::endl;
    size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

std::ostream& operator<<(std::ostream &out, 
                         Bits<const std::vector<std::string> &> const v)
{
    std::cout << "write vector const string " << v.t.size() << " elems" << std::endl;
    size_t sz = v.t.size();
    out << bits(sz);
    for (auto i : v.t) { out << bits(i); }
    return (out);
}

std::istream& operator>>(std::istream &in, 
                         Bits<std::vector<std::string> &> v)
{
    size_t sz = 0;
    in >> bits(sz);
    std::cout << "read vector string " << sz << " elems" << std::endl;
    if (in && sz) {
        while (sz--) {
            std::string s;
            in >> bits(s);
            v.t.push_back(s);
        }
    }

    return in;
}

void
Game::save (void)
{_
    CON("save %s", saved_file.c_str());
    {
        std::ofstream f(saved_file, std::ios::binary );
        int a = 5, b = -1, c = 123456;

        std::string d("hello");
        std::initializer_list<std::string> data = {"there", "you"};
        std::vector<std::string> e(data);

        f << bits(a) << bits(b) << bits(c) << bits(d) << bits(e);
    }

    {
        std::ifstream f(saved_file);
        int a, b, c;
        std::string d;
        std::vector<std::string> e;

        f >> bits(a) >> bits(b) >> bits(c) >> bits(d) >> bits(e);

        std::cout << "a " << a << std::endl;
        std::cout << "b " << b << std::endl;
        std::cout << "c " << c << std::endl;
        std::cout << "d " << d << std::endl;
        std::cout << "e " << e.size() << " elems: ";
        for (auto i : e) {
            std::cout << "[" << i << "] ";
        }
        std::cout << std::endl;
    }
    DIE("X");
}

void
Game::load (void)
{_
    CON("load %s", saved_file.c_str());
}
