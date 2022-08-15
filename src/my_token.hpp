//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TOKEN_HPP_
#define _MY_TOKEN_HPP_

#include "my_string.hpp"
#include "slre.hpp"

typedef struct tokens_t_ {
  struct slre regexp[ MAXSHORTSTR ];
  char       *args[ MAXSHORTSTR ];
  char        data[ MAXSHORTSTR ];
  uint32_t    cnt;
} tokens_t;

tokens_t *tokens_tostring(const char *input, tokens_t *);
void      tokens_print_to(tokens_t *, char *output, int output_size);
void      tokens_print(tokens_t *);
void      tokens_test(void);
#endif
