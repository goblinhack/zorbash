//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SPRINTF_HPP_
#define _MY_SPRINTF_HPP_

#include <string>

std::string string_sprintf(const char *format, ...) __attribute__((format(printf, 1, 2)));
std::string string_sprintf(const char *format, va_list args);
#endif
