//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//
#pragma once

#ifndef _MY_PLAYER_H_
#define _MY_PLAYER_H_

extern void player_tick(bool left = false, bool right = false, bool up = false, bool down = false, bool attack = false,
                        bool wait = false, bool jump = false);

#endif
