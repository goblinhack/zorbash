//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//


#ifndef _MY_COMMAND_H_
#define _MY_COMMAND_H_

typedef struct tokens_t_ *tokenp;
typedef struct tokens_t_ *tokensp;

typedef uint8_t(*command_fn_t)(tokenp, void *context);

#include "my_token.h"

void command_fini(void);
uint8_t command_init(void);
void command_add(command_fn_t callback,
                 std::string input,
                 std::string readable_input);
uint8_t command_handle(const char *input,
                       char *expandedtext,
                       uint8_t show_ambiguous,
                       uint8_t show_complete,
                       uint8_t execute_command,
                       void *context);
uint8_t command_handle(std::string input,
                       std::string *expanded_text,
                       uint8_t show_ambiguous,
                       uint8_t show_complete,
                       uint8_t execute_command,
                       void *context);
uint8_t command_handle(std::wstring input,
                       std::wstring *expanded_text,
                       uint8_t show_ambiguous,
                       uint8_t show_complete,
                       uint8_t execute_command,
                       void *context);
void commands_test(void);
#endif
