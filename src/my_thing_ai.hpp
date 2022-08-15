//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_AI_H
#define _MY_THING_AI_H

#include "my_dmap.hpp"
#include "my_fwd.hpp"
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

  Goal() {}
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

  friend bool operator<(const class Goal &lhs, const class Goal &rhs)
  {
    // Lower priorities at the head
    if (lhs.prio < rhs.prio) {
      return true;
    }
    return lhs.score > rhs.score; // Higher scores at the head
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

  Next_hop() {}
  Next_hop(float cost, point goal, fpoint next_hop) : cost(cost), goal(goal), next_hop(next_hop) {}

  friend bool operator<(const class Next_hop &lhs, const class Next_hop &rhs)
  {
    return lhs.cost < rhs.cost; // Lower costs at the head
  }
};

class Path
{
public:
  Path() {}
  Path(std::vector< point > &p, int c, const Goal &g) : path(p), cost(c), goal(g) {}

  std::vector< point > path;
  int                  cost {};
  Goal                 goal;

  friend bool operator<(const class Path &lhs, const class Path &rhs)
  {
    if (lhs.cost == rhs.cost) {
      return lhs.path.size() < rhs.path.size();
    } else {
      return lhs.cost < rhs.cost; // Lower costs at the head
    }
  }
};

extern void astar_dump(const Dmap *dmap, const point at, const point start, const point end);

class GoalMap
{
public:
  std::multiset< class Goal > goals;
  Dmap                       *dmap;
};

typedef struct AgeMap_ {
  std::array< std::array< uint32_t, MAP_HEIGHT >, MAP_WIDTH > val {};
} AgeMap;
std::ostream &operator<<(std::ostream &out, Bits< const AgeMap & > const my);
std::istream &operator>>(std::istream &in, Bits< AgeMap & > my);

extern std::array< std::array< char, MAP_HEIGHT >, MAP_WIDTH > astar_debug;

#endif
