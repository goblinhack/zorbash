//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_SERIALIZE_HPP_
#define _MY_SERIALIZE_HPP_

#include "c_plus_plus_serializer.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"

std::istream &operator>>(std::istream &in, Bits< point & > my);
std::ostream &operator<<(std::ostream &out, Bits< const point & > const my);
std::istream &operator>>(std::istream &in, Bits< fpoint & > my);
std::ostream &operator<<(std::ostream &out, Bits< const fpoint & > const my);
std::ostream &operator<<(std::ostream &out, Bits< const point3d & > const my);
std::istream &operator>>(std::istream &in, Bits< point3d & > my);
std::ostream &operator<<(std::ostream &out, Bits< const Config & > const my);
std::istream &operator>>(std::istream &in, Bits< Config & > my);
std::ostream &operator<<(std::ostream &out, Bits< const class Game & > const my);
std::istream &operator>>(std::istream &in, Bits< class Game & > my);
std::ostream &operator<<(std::ostream &out, Bits< const HiScore & > const my);  // save
std::istream &operator>>(std::istream &in, Bits< HiScore & > my);               // load
std::ostream &operator<<(std::ostream &out, Bits< const HiScores & > const my); // save
std::istream &operator>>(std::istream &in, Bits< HiScores & > my);              // load
std::istream &operator>>(std::istream &in, Bits< Levelp & > my);
std::ostream &operator<<(std::ostream &out, Bits< Levelp & > const my);
std::ostream &operator<<(std::ostream &out, Bits< const ThingInfop & > const my);
std::istream &operator>>(std::istream &in, Bits< ThingInfop & > my);
std::ostream &operator<<(std::ostream &out, Bits< const ThingItemsp & > const my);
std::istream &operator>>(std::istream &in, Bits< ThingItemsp & > my);
std::ostream &operator<<(std::ostream &out, Bits< const ThingAip & > const my);
std::istream &operator>>(std::istream &in, Bits< ThingAip & > my);
std::istream &operator>>(std::istream &in, Bits< SDL_Keysym & > my);
std::ostream &operator<<(std::ostream &out, Bits< const SDL_Keysym & > const my);
std::ostream &operator<<(std::ostream &out, Bits< const AgeMap & > const my);
std::istream &operator>>(std::istream &in, Bits< AgeMap & > my);
std::ostream &operator<<(std::ostream &out, Bits< const Thingp & > const my);
std::istream &operator>>(std::istream &in, Bits< Thingp & > my);
std::ostream &operator<<(std::ostream &out, Bits< const World & > const my);
std::istream &operator>>(std::istream &in, Bits< World & > my);

#endif
