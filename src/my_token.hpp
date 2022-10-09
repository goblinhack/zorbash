//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TOKEN_HPP_
#define _MY_TOKEN_HPP_

#include "my_string.hpp"
#include "slre.hpp"

class Tokens
{
public:
  struct slre regexp[ MAXSHORTSTR ];
  char       *args[ MAXSHORTSTR ];
  char        data[ MAXSHORTSTR ];
  uint32_t    cnt;
};

class Tokens *tokens_tostring(const char *input, class Tokens *);
void          tokens_print_to(class Tokens *, char *output, int output_size);
void          tokens_print(class Tokens *);
void          tokens_test(void);
#endif
