//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SPRINTF_HPP_
#define _MY_SPRINTF_HPP_

#include "my_format_str_attribute.hpp"

#include <string>

std::string string_sprintf(const char *format, ...) CHECK_FORMAT_STR(printf, 1, 2);
std::string string_sprintf(const char *format, va_list args);
#endif
