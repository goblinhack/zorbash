//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include "my_main.h"
#include "my_thing.h"
#include "my_dmap.h"
#include "my_math.h"
#include <list>

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
    Node *open[width][height] = {{}};
    Node *closed[width][height] = {{}};
    Nodemap open_nodes;
    Nodemap closed_nodes;
    point start;
    point goal;
    Dmap *dmap {};

    void add_to_open (Node *n)
    {
        auto p = n->at;
        auto o = &open[p.x][p.y];
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
        auto o = &closed[p.x][p.y];
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
        auto o = &open[p.x][p.y];
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
        if (dmap->val[nexthop.x][nexthop.y] == DMAP_IS_WALL) {
            return;
        }

        // If in the closed set already, ignore.
        if (closed[nexthop.x][nexthop.y]) {
            return;
        }

        auto distance_to_nexthop = dmap->val[nexthop.x][nexthop.y];
        auto cost = current->cost.cost + 
                    distance_to_nexthop + heuristic(nexthop);
        auto neighbor = open[nexthop.x][nexthop.y];
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

    std::tuple<std::list<point>, int > create_path (const Node *came_from)
    {
        std::list<point> l;
        int cost = 0;

        while (came_from) {
            l.push_back(came_from->at);
printf("    %d %d cost %d\n", came_from->at.x, came_from->at.y, came_from->cost.cost);
            cost += came_from->cost.cost;
            came_from = came_from->came_from;
        }
        return {l, cost};
    }

    void dump (const Node *came_from)
    {
        auto [l, cost] = create_path(came_from);
        int x;
        int y;

        printf("astar:\n");
        for (y = 0; y < MAP_HEIGHT; y++) {
            for (x = 0; x < MAP_WIDTH; x++) {
                uint16_t e = dmap->val[x][y];

                bool best = false;
                for (auto n : l) {
                    if (n == point(x, y)) {
                        best = true;
                        break;
                    }
                }

                char buf[10] = {};
                if (e == DMAP_IS_WALL) {
                    sprintf(buf, "## ");
                } else if (e == DMAP_IS_PASSABLE) {
                    sprintf(buf, "_  ");
                } else if ((e > DMAP_IS_PASSABLE) && 
                           (e < DMAP_IS_PASSABLE + 100)) {
                    sprintf(buf, ">%-2d", e - DMAP_IS_PASSABLE);
                } else if (e > 0) {
                    sprintf(buf, "%-3d", e);
                } else {
                    sprintf(buf, ".  ");
                }

                if (point(x, y) == start) {
                    sprintf(buf, " @ ");
                }

                if (best) {
                    buf[2] = '%';
                }

                printf("%s", buf);
            }
            printf("\n");
        }
        printf("\n");
    }

    std::list<point> solve (void)
    {
        auto distance_to_nexthop = 0;
        auto ncost = Nodecost(distance_to_nexthop + heuristic(start));
        auto neighbor = new Node(start, ncost);
        add_to_open(neighbor);
        std::list<point> l;
        int best = 0;

printf("search\n");
        while (!open_nodes.empty()) {
            auto c = open_nodes.begin();
            Node *current = c->second;

            if (current->at == goal) {
                auto [n, cost] = create_path(current);

                if ((cost < best) || l.empty()) {
                    best = cost;
                    l = n;
printf("   goal found best cost %d\n", cost);
                } else {
printf("   goal found cost %d\n", cost);
                }
//                dump(current);
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

        return (l);
    }
};

std::list<point> astar_solve (point s, point g, Dmap *d)
{
    auto a = Astar(s, g, d);
    return (a.solve());
}
