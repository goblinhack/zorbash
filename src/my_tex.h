/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_TEX_H_
#define _MY_TEX_H_

uint8_t tex_init(void);
void tex_fini(void);
texp tex_load(std::string file, std::string name, int mode);
texp tex_find(std::string name);
texp tex_from_surface(SDL_Surface *surface,
                      std::string optional_file,
                      std::string name, int mode);
void tex_blit(texp tex, point at);
void blit_quad(point tl, point br);
int32_t tex_get_gl_binding(texp);
uint32_t tex_get_width(texp);
uint32_t tex_get_height(texp);
SDL_Surface *tex_get_surface(texp);
texp string2tex(const char **s);
texp string2tex(std::string &s, int *len);
texp string2tex(std::wstring &s, int *len);
#endif
