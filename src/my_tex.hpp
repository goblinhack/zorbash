//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_TEX_HPP_
#define _MY_TEX_HPP_

#include "my_fwd.hpp"
#include <SDL.h>
#include <memory>

int tex_get_gl_binding(Texp);

SDL_Surface *tex_get_surface(Texp);

Texp string2tex(const char **s);
Texp string2tex(std::string &s, int *len);
Texp string2tex(std::wstring &s, int *len);
Texp tex_find(std::string name);
Texp tex_from_surface(SDL_Surface *surface, std::string file, std::string name, int mode);
Texp tex_load(std::string file, std::string name, int mode);

uint32_t tex_get_height(Texp);
uint32_t tex_get_width(Texp);

uint8_t tex_init(void);

void tex_fini(void);
void tex_free(Texp tex);
void tex_load(Texp *tex, Texp *tex_black_and_white, Texp *tex_mask, std::string file, std::string name, int mode);

#endif
