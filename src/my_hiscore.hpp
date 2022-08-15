//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_HISCORE_HPP_
#define _MY_HISCORE_HPP_

#include "c_plus_plus_serializer.hpp"
#include <string>

class HiScore
{
public:
  HiScore(void) {}
  HiScore(std::string name, std::string when, int score, int level_reached, std::string defeated_by)
  {
    this->name          = name;
    this->when          = when;
    this->score         = score;
    this->level_reached = level_reached;
    this->defeated_by   = defeated_by;
  }

  ~HiScore(void) {}

  //
  // Who made the score?
  //
  std::string name;
  std::string when;
  std::string defeated_by;
  int         score;
  int         level_reached;

  //
  // The number of scores in the table.
  //
  static const int max           = 20;
  static const int max_displayed = 20;
};
std::ostream &operator<<(std::ostream &out, Bits< const HiScore & > const my); // save
std::istream &operator>>(std::istream &in, Bits< HiScore & > my);              // load

class HiScores
{
public:
  HiScores(void);
  ~HiScores(void);

  //
  // All the hiscores held in the file.
  //
  std::vector< HiScore > hiscores;

  void        add_new_hiscore(class Thing_ *player, const std::string &name, const std::string &defeated_by);
  bool        is_new_hiscore(class Thing_ *player);
  bool        is_new_highest_hiscore(class Thing_ *player);
  const char *place_str(class Thing_ *player);
};
std::ostream &operator<<(std::ostream &out, Bits< const HiScores & > const my); // save
std::istream &operator>>(std::istream &in, Bits< HiScores & > my);              // load

#endif // _MY_THING_HPP_
