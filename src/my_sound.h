/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once
#ifndef _MY_SOUND_H_
#define _MY_SOUND_H_

uint8_t sound_init(void);
void sound_fini(void);
soundp sound_find(std::string name);
void sound_play(std::string name);
void sound_play_global_at(std::string name, double x, double y);
void sound_play_at(std::string name, double x, double y);
void sound_play_n(std::string name, int32_t n);
void sound_play_dead(void);
void sound_play_slime(void);
void sound_play_level_end(void);
void sound_play_click(void);
void sound_load_all(void);
#endif
