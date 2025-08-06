//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_COMMAND_HISTORY_HPP_
#define _MY_COMMAND_HISTORY_HPP_

//
// History for all text widgets.
//
#define HISTORY_MAX 16
extern std::array< std::wstring, HISTORY_MAX > history;
extern uint32_t                                g_history_at;
extern uint32_t                                g_history_walk;

#endif
