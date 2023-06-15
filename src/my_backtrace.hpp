//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TRACEBACK_HPP_
#define _MY_TRACEBACK_HPP_

#include <array>
#include <string> // no not remove

class Backtrace
{
  static const int                    max_backtrace = 63;
  std::array< void *, max_backtrace > bt {};
  int                                 size {};

public:
  Backtrace(void) = default;
  void        init(void);
  std::string to_string(void);
  void        log(void);
  Backtrace(const Backtrace *const other)
  {
    bt   = other->bt;
    size = other->size;
  }
};

void        backtrace_dump(void);
void        backtrace_unwind();
std::string backtrace_string(void);
#endif
