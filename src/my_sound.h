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

uint8_t sound_init(void);
void sound_fini(void);
bool sound_load(const std::string &file, std::string &name);
bool sound_find(const std::string &name);
bool sound_play(const std::string &file, std::string &alias, uint32_t rate);
void sound_halt(void);
void sound_update_volume(void);

#if 0
void sound_play_intro(void);
void sound_play_demo(void);
void sound_play_death(void);
void sound_play_game(uint32_t);
void sound_play_dead(void);
void sound_play_game_over(void);
#endif

#endif
