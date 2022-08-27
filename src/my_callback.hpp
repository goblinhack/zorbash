//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_CALLBACK_HPP_
#define _MY_CALLBACK_HPP_

#include <functional> // for _1, _2
using MyCallback = std::function< void(void) >;
extern MyCallback NoCallback;

#endif
