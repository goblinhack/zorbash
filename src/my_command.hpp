//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_COMMAND_HPP_
#define _MY_COMMAND_HPP_

#include <stdint.h>

typedef uint8_t (*command_fn_t)(class Tokens *, void *context);

#include "my_token.hpp"

void    command_fini(void);
uint8_t command_init(void);
void    command_add(command_fn_t callback, std::string input, std::string readable_input);
uint8_t command_handle(const char *input, char *expandedtext, uint8_t show_ambiguous, uint8_t show_complete,
                       uint8_t execute_command, void *context);
uint8_t command_handle(std::string input, std::string *expanded_text, uint8_t show_ambiguous, uint8_t show_complete,
                       uint8_t execute_command, void *context);
uint8_t command_handle(std::wstring input, std::wstring *expanded_text, uint8_t show_ambiguous, uint8_t show_complete,
                       uint8_t execute_command, void *context);
void    commands_test(void);
#endif
