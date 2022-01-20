//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_thing_template.hpp"

std::string Tp::to_string(void) { return text_name().c_str(); }

std::string Tp::to_short_string(void) { return short_text_name().c_str(); }
