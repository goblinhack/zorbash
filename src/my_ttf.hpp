//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#include "my_font.hpp"

#ifndef _MY_TTF_HPP_
#define _MY_TTF_HPP_

Fontp ttf_new(std::string name, int pointSize, int style);
void  ttf_free(Fontp);
void  ttf2tga(void);
Fontp ttf_read_tga(Fontp, const char *name, int pointsize);
Fontp ttf_write_tga(std::string name, int pointsize, int style);
#endif
