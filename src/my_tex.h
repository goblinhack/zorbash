//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once

#ifndef _MY_TEX_H_
#define _MY_TEX_H_

#include <SDL.h>
#include <memory>

typedef class Tex * Texp;

uint8_t tex_init(void);
void tex_fini(void);
void tex_free(Texp tex);
Texp tex_load(std::string file, std::string name, int mode);
Texp tex_find(std::string name);
Texp tex_from_surface(SDL_Surface *surface,
                      std::string file,
                      std::string name, int mode);
int32_t tex_get_gl_binding(Texp);
uint32_t tex_get_width(Texp);
uint32_t tex_get_height(Texp);
SDL_Surface *tex_get_surface(Texp);
Texp string2tex(const char **s);
Texp string2tex(std::string &s, int *len);
Texp string2tex(std::wstring &s, int *len);
#endif
