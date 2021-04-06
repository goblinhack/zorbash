/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_SOUND_H_
#define _MY_SOUND_H_

#include <string>

class sound;
using soundp = class sound *;

bool sound_init(void);
void sound_fini(void);
bool sound_load(float volume, const std::string &file, const std::string &alias);
bool sound_load(float volume, const char *file, const char *alias);
bool sound_find(const std::string &alias);
bool sound_play(const std::string &alias);
void sound_halt(void);

#endif
