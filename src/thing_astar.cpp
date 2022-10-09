//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_main.hpp"
#include "my_sprintf.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

#include <limits>
#include <vector>

std::array< std::array< char, MAP_HEIGHT >, MAP_WIDTH > astar_debug {};

class Nodecost
{
public:
  Nodecost(void) = default;
  Nodecost(int c) : cost(c)
  {
    static int tiebreak_;
    tiebreak = tiebreak_++;
  }

  bool operator<(const Nodecost &rhs) const
  {
    if (cost < rhs.cost) {
      return true;
    }
    if (cost > rhs.cost) {
      return false;
    }
    return (tiebreak < rhs.tiebreak);
  }

  int cost {};
  int tiebreak {};
};

class Node
{
public:
  Node(void) = default;
  Node(Thingp me, point p, Nodecost c) : cost(c), at(p) { is_disliked = me->is_disliked_by_me(p); }

  class Node *came_from {};
  Nodecost    cost;
  point       at;
  bool        is_disliked;
};

typedef std::map< Nodecost, Node * > Nodemap;

class Astar
{
public:
  Astar(point s, point g, const Dmap *d) : start(s), goal(g), dmap(d) {}

  static const int                                  width  = MAP_WIDTH;
  static const int                                  height = MAP_HEIGHT;
  std::array< std::array< Node *, height >, width > open   = {};
  std::array< std::array< Node *, height >, width > closed = {};
  Nodemap                                           open_nodes;
  Nodemap                                           closed_nodes;
  point                                             start;
  point                                             goal;
  const Dmap                                       *dmap {};

  void add_to_open(Node *n)
  {
    auto p = n->at;
    auto o = &getref(open, p.x, p.y);
    if (*o) {
      ERR("Already in open");
      return;
    }
    *o          = n;
    auto result = open_nodes.insert(std::make_pair(n->cost, n));
    if (! result.second) {
      ERR("Open insert fail");
      return;
    }
  }

  void add_to_closed(Node *n)
  {
    auto p = n->at;
    auto o = &getref(closed, p.x, p.y);
    if (*o) {
      ERR("Already in closed");
      return;
    }
    *o          = n;
    auto result = closed_nodes.insert(std::make_pair(n->cost, n));
    if (! result.second) {
      ERR("Closed insert fail");
      return;
    }
  }

  void remove_from_open(Node *n)
  {
    auto p = n->at;
    auto o = &getref(open, p.x, p.y);
    if (! *o) {
      ERR("Not in open");
      return;
    }
    *o = nullptr;
    open_nodes.erase(n->cost);
  }

  // Manhattan distance.
  int heuristic(const point at)
  {
    // return (abs(goal.x - at.x) + abs(goal.y - at.y));
    return 1;
  }

  // Evaluate a neighbor for adding to the open set
  void eval_neighbor(Thingp me, Node *current, point delta)
  {
    auto next_hop = current->at + delta;

    if ((next_hop.x < 0) || (next_hop.y < 0) || (next_hop.x > width - 1) || (next_hop.y > height - 1)) {
      return;
    }

    // Ignore walls.
    if (get(dmap->val, next_hop.x, next_hop.y) == DMAP_IS_WALL) {
      return;
    }

    // If in the closed set already, ignore.
    if (closed[ next_hop.x ][ next_hop.y ]) {
      return;
    }

    int distance_to_next_hop = get(dmap->val, next_hop.x, next_hop.y);
    if (distance_to_next_hop == DMAP_IS_PASSABLE) {
      distance_to_next_hop = 0;
    }

    int  cost     = current->cost.cost + distance_to_next_hop + heuristic(next_hop);
    auto neighbor = get(open, next_hop.x, next_hop.y);
    if (! neighbor) {
      auto ncost          = Nodecost(cost + heuristic(next_hop));
      neighbor            = new Node(me, next_hop, ncost);
      neighbor->came_from = current;
      add_to_open(neighbor);
      return;
    }

    if (cost < neighbor->cost.cost) {
      remove_from_open(neighbor);
      neighbor->came_from = current;
      neighbor->cost      = cost;
      add_to_open(neighbor);
    }
  }

  void cleanup(void)
  {
    for (auto y = 0; y < height; y++) {
      for (auto x = 0; x < width; x++) {
        if (open[ x ][ y ]) {
          delete (open[ x ][ y ]);
        }
        if (closed[ x ][ y ]) {
          delete (closed[ x ][ y ]);
        }
      }
    }
  }

  std::tuple< std::vector< point >, int > create_path(const Dmap *dmap, const Node *came_from)
  {
    std::vector< point > l;
    int                  cost               = came_from->cost.cost;
    int                  consecutive_hazard = 0;

    while (came_from) {
      if (came_from->came_from) {
        l.push_back(came_from->at);

        //
        // If we pass over too many consecutive things we do not like, like chasms
        // then we cannot use this path.
        //
        if (came_from->is_disliked) {
          consecutive_hazard++;
          if (consecutive_hazard > 2) {
            l.clear();
            return {l, std::numeric_limits< int >::max()};
          }
        } else {
          consecutive_hazard = 0;
        }
      }
      came_from = came_from->came_from;
    }

    return {l, cost};
  }

  std::pair< Path, Path > solve(Thingp me, const Goal *goalp, char *path_debug)
  {
    auto distance_to_next_hop = 0;
    auto ncost                = Nodecost(distance_to_next_hop + heuristic(start));
    auto neighbor             = new Node(me, start, ncost);
    add_to_open(neighbor);
    Path best;
    best.cost = std::numeric_limits< int >::max();
    Path fallback;
    fallback.cost = std::numeric_limits< int >::max();

    float fallback_dist = distance(start, goal);

    while (! open_nodes.empty()) {
      auto  c       = open_nodes.begin();
      Node *current = c->second;

      auto at = current->at;
      set(astar_debug, at.x, at.y, (char) ('?'));
      if (at == goal) {
        auto [ path, cost ] = create_path(dmap, current);

        if (cost < best.cost) {
          if (goalp) {
            best.goal = *goalp;
          }
          best.path = path;
          best.cost = cost;
#ifdef ENABLE_DEBUG_AI_ASTAR
          for (const auto &p : path) {
            set(astar_debug, p.x, p.y, (char) ('A' + *path_debug));
          }
          (*path_debug)++;
#endif
        } else {
#ifdef ENABLE_DEBUG_AI_ASTAR
          for (const auto &p : path) {
            set(astar_debug, p.x, p.y, (char) ('a' + *path_debug));
          }
          (*path_debug)++;
#endif
        }
        remove_from_open(current);
        add_to_closed(current);
        continue;
      } else {
        //
        // Create any old path in case we cannot reach the goal
        //
        float dist = distance(goal, current->at);
        if (dist < fallback_dist) {
          fallback_dist       = dist;
          auto [ path, cost ] = create_path(dmap, current);
          if (goalp) {
            fallback.goal = *goalp;
          }
          fallback.path = path;
          fallback.cost = cost;
        }
      }

      remove_from_open(current);
      add_to_closed(current);

      eval_neighbor(me, current, point(-1, 0));
      eval_neighbor(me, current, point(1, 0));
      eval_neighbor(me, current, point(0, -1));
      eval_neighbor(me, current, point(0, 1));

      //
      // This leads to the robot taking diagonals across lava which looks
      // like cheating.
      //
      // Also leads to zig zag paths over chasms that would need
      // optimized.
      //
      if (me->is_able_to_move_diagonally()) {
        if ((get(dmap->val, at.x - 1, at.y) == DMAP_IS_WALL) || (get(dmap->val, at.x, at.y - 1) == DMAP_IS_WALL)) {
          eval_neighbor(me, current, point(-1, -1));
        }
        if ((get(dmap->val, at.x - 1, at.y) == DMAP_IS_WALL) || (get(dmap->val, at.x, at.y + 1) == DMAP_IS_WALL)) {
          eval_neighbor(me, current, point(-1, 1));
        }
        if ((get(dmap->val, at.x + 1, at.y) == DMAP_IS_WALL) || (get(dmap->val, at.x, at.y - 1) == DMAP_IS_WALL)) {
          eval_neighbor(me, current, point(1, -1));
        }
        if ((get(dmap->val, at.x + 1, at.y) == DMAP_IS_WALL) || (get(dmap->val, at.x, at.y + 1) == DMAP_IS_WALL)) {
          eval_neighbor(me, current, point(1, 1));
        }
      }
    }

    cleanup();

    return (std::pair(best, fallback));
  }
};

void astar_dump(const Dmap *dmap, const point at, const point start, const point end)
{
  int x;
  int y;

  LOG("ASTAR:");
  for (y = start.y; y < end.y; y++) {
    std::string s;
    for (x = start.x; x < end.x; x++) {
      uint16_t e = get(dmap->val, x, y);

      std::string buf;
      if (e == DMAP_IS_WALL) {
        buf = "## ";
      } else if (e == DMAP_IS_PASSABLE) {
        buf = ".  ";
      } else if (e > 0) {
        buf = string_sprintf("%-3X", e);
      } else {
        buf = "*  ";
      }

      if (point(x, y) == at) {
        buf = " @ ";
      }

#ifdef ENABLE_DEBUG_AI_ASTAR
      if (get(astar_debug, x, y)) {
        buf[ 2 ] = get(astar_debug, x, y);
      }
#endif
      s += buf;
    }
    LOG("ASTAR:%s", s.c_str());
  }
}

std::pair< Path, Path > Thing::astar_solve(const Goal *goal, char path_debug, point s, point g, const Dmap *d)
{
  char tmp = path_debug;
  auto a   = Astar(s, g, d);
  return (a.solve(this, goal, &tmp));
}
