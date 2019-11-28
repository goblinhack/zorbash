//
// Copyright goblinhack@gmail.com
//
#ifndef _MY_TRACEBACK_H_
#define _MY_TRACEBACK_H_

#include <array>
#include <iostream>
#include <string>

class Traceback {
    static const int max_traceback = 63;
    std::array<void *, max_traceback> tb;
    int size {};
public:
    Traceback(void) {}
    void init(void);
    std::string to_string(void);
    Traceback(const Traceback* const other) {
        tb = other->tb;
        size = other->size;
    }
};

void traceback_dump(void);
#endif
