//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include "my_main.h"
#include "my_game.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_sprintf.h"
#include <vector>

#define ASTAR_DEBUG
#ifdef ASTAR_DEBUG
static std::array<std::array<char, MAP_HEIGHT>, MAP_WIDTH> debug {};
#endif

class Nodecost {
public:
    Nodecost (void) { }
    Nodecost (int c) : cost(c)
    {
        static int tiebreak_;
        tiebreak = tiebreak_++;
    }

    bool operator <(const Nodecost& rhs) const
    {
        if (cost < rhs.cost) {
            return (true);
        } else if (cost > rhs.cost) {
            return (false);
        } else {
            return (tiebreak < rhs.tiebreak);
        }
    }

    int cost {};
    int tiebreak {};
};

class Node {
public:
    Node (void) { }
    Node (point p, Nodecost c) : cost(c), at(p) { }

    class Node *came_from {};
    Nodecost    cost;
    point       at;
};

typedef std::map< Nodecost, Node * > Nodemap;

class Astar {
public:
    Astar (point s, point g, Dmap *d) : start(s), goal(g), dmap(d) { }

    static const int width = MAP_WIDTH;
    static const int height = MAP_HEIGHT;
    std::array<std::array<Node *, height>, width> open = {};
    std::array<std::array<Node *, height>, width> closed = {};
    Nodemap open_nodes;
    Nodemap closed_nodes;
    point start;
    point goal;
    Dmap *dmap {};

    void add_to_open (Node *n)
    {
        auto p = n->at;
        auto o = &getref(open, p.x, p.y);
        if (*o) {
            DIE("already in open");
        }
        *o = n;
        auto result = open_nodes.insert(std::make_pair(n->cost, n));
        if (result.second == false) {
            DIE("open insert fail");
        }
    }

    void add_to_closed (Node *n)
    {
        auto p = n->at;
        auto o = &getref(closed, p.x, p.y);
        if (*o) {
            DIE("already in closed");
        }
        *o = n;
        auto result = closed_nodes.insert(std::make_pair(n->cost, n));
        if (result.second == false) {
            DIE("closed insert fail");
        }
    }

    void remove_from_open (Node *n)
    {
        auto p = n->at;
        auto o = &getref(open, p.x, p.y);
        if (!*o) {
            DIE("not in open");
        }
        *o = nullptr;
        open_nodes.erase(n->cost);
    }

    // Manhattan distance.
    int heuristic (const point at)
    {
        return (abs(goal.x - at.x) + abs(goal.y - at.y));
    }

    // Evaluate a neighbor for adding to the open set
    void eval_neighbor (Node *current, point delta)
    {
        auto nexthop = current->at + delta;

        if ((nexthop.x <= 0) ||
            (nexthop.y <= 0) ||
            (nexthop.x >= width - 1) ||
            (nexthop.y >= height - 1)) {
            return;
        }

        // Ignore walls.
        if (get(dmap->val, nexthop.x, nexthop.y) == DMAP_IS_WALL) {
            return;
        }

        // If in the closed set already, ignore.
        if (closed[nexthop.x][nexthop.y]) {
            return;
        }

        int distance_to_nexthop = get(dmap->val, nexthop.x, nexthop.y);
        if (distance_to_nexthop == DMAP_IS_PASSABLE) {
            distance_to_nexthop = 0;
        }

        int cost = current->cost.cost +
                   distance_to_nexthop + heuristic(nexthop);
        auto neighbor = get(open, nexthop.x, nexthop.y);
        if (!neighbor) {
            auto ncost = Nodecost(cost + heuristic(nexthop));
            neighbor = new Node(nexthop, ncost);
            neighbor->came_from = current;
            add_to_open(neighbor);
            return;
        }

        if (cost < neighbor->cost.cost) {
            remove_from_open(neighbor);
            neighbor->came_from = current;
            neighbor->cost = cost;;
            add_to_open(neighbor);
        }
    }

    void cleanup (void)
    {
        for (auto y = 0; y < height; y++) {
            for (auto x = 0; x < width; x++) {
                if (open[x][y]) {
                    delete(open[x][y]);
                }
                if (closed[x][y]) {
                    delete(closed[x][y]);
                }
            }
        }
    }

    std::tuple<std::vector<point>, int > create_path (Dmap *dmap,
                                                      const Node *came_from)
    {
        std::vector<point> l;
        int cost = came_from->cost.cost;

        while (came_from) {
            if (came_from->came_from) {
                l.push_back(came_from->at);
            }
            came_from = came_from->came_from;
        }

        return {l, cost};
    }

    Path solve (char *gi)
    {
        auto distance_to_nexthop = 0;
        auto ncost = Nodecost(distance_to_nexthop + heuristic(start));
        auto neighbor = new Node(start, ncost);
        add_to_open(neighbor);
        Path best;
        best.cost = std::numeric_limits<int>::max();

        while (!open_nodes.empty()) {
            auto c = open_nodes.begin();
            Node *current = c->second;

            if (current->at == goal) {
                auto [path, cost] = create_path(dmap, current);

                if (cost < best.cost) {
                    best.path = path;
                    best.cost = cost;
#ifdef ASTAR_DEBUG
                    for (auto p : path) {
                        set(debug, p.x, p.y, (char)('A' + *gi));
                    }
                    (*gi)++;
#endif
                } else {
#ifdef ASTAR_DEBUG
                    for (auto p : path) {
                        set(debug, p.x, p.y, (char)('a' + *gi));
                    }
                    (*gi)++;
#endif
                }
                remove_from_open(current);
                continue;
            }

            remove_from_open(current);
            add_to_closed(current);

            eval_neighbor(current, point(-1,  0));
            eval_neighbor(current, point( 1,  0));
            eval_neighbor(current, point( 0, -1));
            eval_neighbor(current, point( 0,  1));
        }

        cleanup();

        return (best);
    }
};

#ifdef ASTAR_DEBUG
static void dump (Dmap *dmap,
                  const point &at,
                  const point &start,
                  const point &end)
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

            if (get(debug, x, y)) {
                buf[2] = get(debug, x, y);
            }
            s += buf;
        }
        LOG("ASTAR:%s", s.c_str());
    }
}
#endif

Path astar_solve (const point &at,
                  std::multiset<Goal> &goals,
                  Dmap *dmap,
                  const point &start,
                  const point &end)
{
    auto best = Path();
    best.cost = std::numeric_limits<int>::max();
    char gi = '\0';

#ifdef ASTAR_DEBUG
    debug = {};
#endif
    for (auto g : goals) {
        auto a = Astar(at, g.at, dmap);

        auto path = a.solve(&gi);
        if (path.cost < best.cost)  {
            best = path;
        }
    }

#ifdef ASTAR_DEBUG
    for (auto p : best.path) {
        set(debug, p.x, p.y, 'X');
    }

    dump(dmap, at, start, end);
#endif
    return (best);
}
