/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#include "my_enum.h"
#include "my_font.h"

#ifndef _MY_TTF_H_
#define _MY_TTF_H_

fontp ttf_new(std::string name, int pointSize, int style);
void ttf_free(fontp);
void ttf2tga(void);
fontp ttf_read_tga(fontp, const char *name, int pointsize);
fontp ttf_write_tga(std::string name, int pointsize, int style);
#endif
