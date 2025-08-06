//
// Copyright goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_AI_H
#define _MY_THING_AI_H

#include "my_dmap.hpp"
#include <set>

typedef struct AgeMap_ *AgeMapp;
typedef struct Dmap_   *Dmapp;

//
// Higher scores are better. Score is how desirable something is.
//
class Goal
{
public:
  int         prio  = {0};
  int         score = {0};
  point       at;
  std::string msg;
  Thingp      what {};
  bool        avoid {};

  Goal() = default;
  Goal(int prio, int score, point at, const std::string &msg) : prio(prio), score(score), at(at), msg(msg) {}
  Goal(int prio, int score, point at, const std::string &msg, bool avoid)
      : prio(prio), score(score), at(at), msg(msg), avoid(avoid)
  {
  }
  Goal(int prio, int score, point at, const std::string &msg, Thingp what)
      : prio(prio), score(score), at(at), msg(msg), what(what)
  {
  }
  Goal(int prio, int score, point at, const std::string &msg, Thingp what, bool avoid)
      : prio(prio), score(score), at(at), msg(msg), what(what), avoid(avoid)
  {
  }
};

//
// Lower costs are better. Cost is the path to the target.
//
class Next_hop
{
public:
  float  cost = {0};
  point  goal;
  fpoint next_hop;

  Next_hop() = default;
  Next_hop(float cost, point goal, fpoint next_hop) : cost(cost), goal(goal), next_hop(next_hop) {}
};

class Path
{
public:
  Path() = default;
  Path(std::vector< point > &p, int c, const Goal &g) : path(p), cost(c), goal(g) {}

  std::vector< point > path;
  int                  cost {};
  Goal                 goal;
};

extern void astar_dump(const Dmap *dmap, const point at, const point start, const point end);

class GoalMap
{
public:
  std::multiset< class Goal > goals;
  Dmap                       *dmap;
};

typedef struct AgeMap_ {
  std::array< std::array< int, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > val {};
} AgeMap;

extern std::array< std::array< char, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > astar_debug;

#endif
