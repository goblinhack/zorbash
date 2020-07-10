//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_THING_AI_H
#define _MY_THING_AI_H

//#include <unordered_map>
//#include <memory>
//#include <set>
#include "my_dmap.h"

typedef struct AgeMap_* AgeMapp;
typedef struct Dmap_* Dmapp;

//
// Higher scores are better. Score is how desirable something is.
//
class Goal
{
public:
    float score = {0};
    point at;

    Goal () {}
    Goal (float score, point at) : score(score), at(at) {}

    friend bool operator<(const class Goal & lhs, const class Goal & rhs) {
        return lhs.score > rhs.score; // Higher scores at the head
    }
};

//
// Lower costs are better. Cost is the path to the target.
//
class Next_hop
{
public:
    float cost = {0};
    point goal;
    fpoint next_hop;

    Next_hop () {}
    Next_hop (float cost, point goal, fpoint next_hop) :
        cost(cost), goal(goal), next_hop(next_hop) {}

    friend bool operator<(const class Next_hop & lhs, const class Next_hop & rhs) {
        return lhs.cost < rhs.cost; // Lower costs at the head
    }
};

class Path {
public:
    Path () {}
    Path (std::vector<point> &p, int c) : path(p), cost(c) { }

    std::vector<point> path;
    int                cost {};

    friend bool operator<(const class Path & lhs, const class Path & rhs) {
        if (lhs.cost == rhs.cost) {
            return lhs.path.size() < rhs.path.size();
        } else {
            return lhs.cost < rhs.cost; // Lower costs at the head
        }
    }
};

extern Path astar_solve(char path_debug, point s, point g, const Dmap *d);

extern void astar_dump(const Dmap *dmap,
                       const point &at,
                       const point &start,
                       const point &end);

typedef struct AgeMap_ {
    std::array<std::array<timestamp_t, MAP_HEIGHT>, MAP_WIDTH> val {};
} AgeMap;
std::ostream& operator<<(std::ostream &out, Bits<const AgeMap & > const my);
std::istream& operator>>(std::istream &in, Bits<AgeMap &> my);

#ifdef ENABLE_DEBUG_AI_ASTAR
extern std::array<std::array<char, MAP_HEIGHT>, MAP_WIDTH> astar_debug;
#endif

#endif
