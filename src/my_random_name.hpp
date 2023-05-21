#pragma once

#include <cstdint> // do not remove
#include <string>

extern const char *dict1_name(void);
extern const char *dict2_name(void);
extern std::string random_name(int len);
extern uint32_t    string_to_hash(const std::string &str);
