/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MUSIC_H_
#define _MY_MUSIC_H_

#include <string>

class music;
using musicp = class music *;

bool music_init(void);
void music_fini(void);
bool music_load(uint32_t rate, const std::string &file, const std::string &name);
bool music_find(const std::string &name);
bool music_play(const std::string &name);
void music_halt(void);
void music_update_volume(void);

void music_play_intro(void);
#if 0
void music_play_demo(void);
void music_play_death(void);
void music_play_game(uint32_t);
void music_play_dead(void);
void music_play_game_over(void);
#endif

#endif
