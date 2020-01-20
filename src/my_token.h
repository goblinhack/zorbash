//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_TOKEN_H_
#define _MY_TOKEN_H_

#include "my_string.h"
#include "my_slre.h"

typedef struct tokens_t_ {
    struct slre regexp[MAXSHORTSTR];
    char *args[MAXSHORTSTR];
    char data[MAXSHORTSTR];
    uint32_t cnt;
} tokens_t;

tokens_t *tokens_tostring(const char *input, tokens_t *);
void tokens_print_to(tokens_t *, char *output, int32_t output_size);
void tokens_print(tokens_t *);
void tokens_test(void);
#endif
