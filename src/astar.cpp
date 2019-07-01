//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <algorithm>
#include "my_main.h"
#include "my_thing.h"
#include "my_dmap.h"
#include "my_math.h"
#include <vector>

#ifdef ASTAR_DEBUG
static char debug[DUN_WIDTH][DUN_HEIGHT];
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

    static const int width = DUN_WIDTH;
    static const int height = DUN_HEIGHT;
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
        return (0);
//        return (abs(goal.x - at.x) + abs(goal.y - at.y));
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

    std::tuple<std::vector<point>, int > create_path (Dmap *dmap,
                                                    const Node *came_from)
    {
        std::vector<point> l;
        int cost = came_from->cost.cost;

        while (came_from) {
            if (came_from->came_from) {
                l.push_back(came_from->at);
            }
#if 0
printf(" %d(%d) ", came_from->cost.cost, dmap->val[came_from->at.x][came_from->at.y]);
#endif
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

//printf("solve %c\n", 'A' + *gi);
        while (!open_nodes.empty()) {
            auto c = open_nodes.begin();
            Node *current = c->second;

            if (current->at == goal) {
//printf("  path %c ",'A' + *gi);
                auto [path, cost] = create_path(dmap, current);
//printf("\n");

                if (cost < best.cost) {
                    best.path = path;
                    best.cost = cost;
//printf("    best %d\n", cost);
#ifdef ASTAR_DEBUG
                    for (auto p : path) {
                        debug[p.x][p.y] = 'A' + *gi;
                    }
                    (*gi)++;
#endif
                } else {
#ifdef ASTAR_DEBUG
                    for (auto p : path) {
                        debug[p.x][p.y] = 'a' + *gi;
                    }
                    (*gi)++;
#endif
//printf("    !best %d\n", cost);
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
static void dump (Dmap *dmap, point start)
{
    int x;
    int y;

    printf("astar:\n");
    for (y = 0; y < DUN_HEIGHT; y++) {
        for (x = 0; x < DUN_WIDTH; x++) {
            uint16_t e = dmap->val[x][y];

            char buf[10] = {};
            if (e == DMAP_IS_WALL) {
                sprintf(buf, "##  ");
            } else if (e == DMAP_IS_PASSABLE) {
                sprintf(buf, "_   ");
            } else if ((e > DMAP_IS_PASSABLE) && 
                        (e < DMAP_IS_PASSABLE + 100)) {
                sprintf(buf, ">%-3d", e - DMAP_IS_PASSABLE);
            } else if (e > 0) {
                sprintf(buf, "%-4d", e);
            } else {
                sprintf(buf, ".   ");
            }

            if (point(x, y) == start) {
                sprintf(buf, " @  ");
            }

            if (debug[x][y]) {
                buf[2] = debug[x][y];
            }

            printf("%s", buf);
        }
        printf("\n");
    }
    printf("\n");
}
#endif

Path astar_solve (point start, std::multiset<Goal> &goals, Dmap *dmap)
{
    auto best = Path();
    best.cost = std::numeric_limits<int>::max();
    char gi = '\0';

#ifdef ASTAR_DEBUG
    memset(debug, 0, sizeof(debug));
#endif
    for (auto g : goals) {
        auto a = Astar(start, g.at, dmap);

        auto path = a.solve(&gi);
        if (path.cost < best.cost)  {
            best = path;
        }
    }

#ifdef ASTAR_DEBUG
    for (auto p : best.path) {
        debug[p.x][p.y] = '%';
    }

    dump(dmap, start);
#endif
    return (best);
}
