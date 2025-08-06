//
// Copyright goblinhack@gmail.com
//

#include "my_thing_template.hpp"

std::string Tp::to_string(void) { return text_long_name().c_str(); }

std::string Tp::to_short_string(void) { return text_short_name().c_str(); }
