/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MUSIC_HPP_
#define _MY_MUSIC_HPP_

class music;
using musicp = class music *;

bool music_init(void);
void music_fini(void);
bool music_load(uint32_t rate, const std::string &file, const std::string &name);
bool music_find(const std::string &name);
bool music_play(const std::string &name);
bool music_halt(void);
void music_update_volume(void);

#endif
