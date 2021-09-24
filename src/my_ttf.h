//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#include "my_font.h"

#ifndef _MY_TTF_H_
#define _MY_TTF_H_

Fontp ttf_new(std::string name, int pointSize, int style);
void  ttf_free(Fontp);
void  ttf2tga(void);
Fontp ttf_read_tga(Fontp, const char *name, int pointsize);
Fontp ttf_write_tga(std::string name, int pointsize, int style);
#endif
