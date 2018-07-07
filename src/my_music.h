/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info.
 */

#pragma once

#ifndef _MY_MUSIC_H_
#define _MY_MUSIC_H_

uint8_t music_init(void);
void music_fini(void);
musicp music_load(std::string file, std::string name);
musicp music_find(std::string name);
void music_play(std::string file, std::string alias, uint32_t rate);
void music_play_demo(void);
void music_play_death(void);
void music_play_intro(void);
void music_play_game(uint32_t);
void music_play_dead(void);
void music_play_game_over(void);
void music_halt(void);
void music_update_volume(void);

extern uint8_t music_init_done;
#endif
