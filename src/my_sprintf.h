//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_SPRINTF_H_
#define _MY_SPRINTF_H_

#include <string>

std::string string_sprintf (const char *format, ...);
std::string string_sprintf (const char *format, va_list args);
#endif
