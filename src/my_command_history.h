//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#pragma once
#ifndef _MY_COMMAND_HISTORY_H_
#define _MY_COMMAND_HISTORY_H_

//
// History for all text widgets.
//
#define HISTORY_MAX 16
extern std::array< std::wstring, HISTORY_MAX > history;
extern uint32_t                                g_history_at;
extern uint32_t                                g_history_walk;

#endif
