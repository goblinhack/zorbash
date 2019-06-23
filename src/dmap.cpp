/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_main.h"
#include "my_dmap.h"

void dmap_print_walls (Dmap *d)
{
    uint16_t x;
    uint16_t y;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            uint16_t e = d->val[x][y];
            if (e == DMAP_IS_WALL) {
                printf("#");
                continue;
            }
            if (e == DMAP_IS_PASSABLE) {
                printf(" ");
                continue;
            }

            if (e > 0) {
                printf("%d", e % 100);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void dmap_print (Dmap *d, point start)
{
    uint16_t x;
    uint16_t y;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            uint16_t e = d->val[x][y];
            if (point(x, y) == start) {
                printf(" @  ");
                continue;
            }

            if (e == DMAP_IS_WALL) {
                printf("##  ");
                continue;
            }
            if (e == DMAP_IS_PASSABLE) {
                printf("_   ");
                continue;
            }

            if ((e > DMAP_IS_PASSABLE) && (e < DMAP_IS_PASSABLE + 100)) {
                printf(">%-3d", e - DMAP_IS_PASSABLE);
                continue;
            }

            if (e > 0) {
                printf("%-4d", e);
            } else {
                printf(".   ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void dmap_scale_and_recenter (Dmap *d, const fpoint start, const int scale)
{
    uint16_t x;
    uint16_t y;
    const float offx = start.x - ((MAP_WIDTH / scale) / 2);
    const float offy = start.y - ((MAP_HEIGHT / scale) / 2);
    uint16_t new_val[MAP_WIDTH][MAP_HEIGHT];
    const float fscale = scale;

    for (y = 0; y < MAP_HEIGHT; y++) {
        for (x = 0; x < MAP_WIDTH; x++) {
            float X = ((float)x / fscale) + offx;
            float Y = ((float)y / fscale) + offy;

            if ((X < 0) || (X >= MAP_WIDTH) ||
                (Y < 0) || (Y >= MAP_HEIGHT)) {
                new_val[x][y] = DMAP_IS_WALL;
                continue;
            }
            new_val[x][y] = d->val[(int)X][(int)Y];
        }
    }
    memcpy(d->val, new_val, sizeof(d->val));
}

uint64_t dmap_hash (Dmap *d)
{
    uint64_t hash = 0;

    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            uint16_t e = d->val[x][y];
            hash += e * x * y;
            hash --;
        }
    }
    return (hash);
}

void dmap_process (Dmap *D, point tl, point br)
{
    uint16_t x;
    uint16_t y;
    uint16_t a;
    uint16_t b;
    uint16_t c;
    uint16_t d;
    uint16_t *e;
    uint16_t f;
    uint16_t g;
    uint16_t h;
    uint16_t i;
    uint16_t lowest;
    uint16_t changed;
    static uint16_t valid[MAP_WIDTH][MAP_HEIGHT];
    static uint16_t orig_valid[MAP_WIDTH][MAP_HEIGHT];
    static uint16_t orig[MAP_WIDTH][MAP_HEIGHT];

    memcpy(orig, D->val, sizeof(D->val));

    int minx, miny, maxx, maxy;
    if (tl.x < br.x) {
        minx = tl.x;
        maxx = br.x;
    } else {
        minx = br.x;
        maxx = tl.x;
    }
    if (tl.y < br.y) {
        miny = tl.y;
        maxy = br.y;
    } else {
        miny = br.y;
        maxy = tl.y;
    }

    if (minx < 0) {
        minx = 0;
    }
    if (miny < 0) {
        miny = 0;
    }
    if (maxx >= MAP_WIDTH) {
        maxx = MAP_WIDTH - 1;
    }
    if (maxy >= MAP_HEIGHT) {
        maxy = MAP_HEIGHT - 1;
    }

    //
    // Need a wall around the dmap or the search will sort of
    // trickle off the map
    //
    for (y = miny; y < MAP_HEIGHT; y++) {
        D->val[minx][y] = DMAP_IS_WALL;
        D->val[maxx][y] = DMAP_IS_WALL;
    }
    for (x = 0; x < MAP_WIDTH; x++) {
        D->val[x][miny] = DMAP_IS_WALL;
        D->val[x][maxy] = DMAP_IS_WALL;
    }

#if 0
    CON("dmap bounds %d,%d to %d,%d", minx, miny, maxx, maxy);
    dmap_print(D);
#endif

    memset(valid, 1, sizeof(valid));
    memset(orig_valid, 1, sizeof(valid));

    for (y = miny + 1; y < maxy; y++) {
        for (x = minx + 1; x < maxx; x++) {
            e = &D->val[x ][y];
            if (*e != DMAP_IS_WALL) {
                continue;
            }

            valid[x][y] = 0;
            orig_valid[x][y] = 0;
        }
    }

#if 0
    dmap_print(D);

    uint16_t count = 1;
#endif

    do {
        changed = false;

#if 0
        printf("run %d %d %d\n", count, x, y);
        count++;
#endif
        for (y = miny + 1; y < maxy - 1; y++) {
            for (x = minx + 1; x < maxx - 1; x++) {
                if (!orig_valid[x][y]) {
                    continue;
                }

                if (!valid[x][y]) {
                    continue;
                }

                e = &D->val[x  ][y];

                /*
                 * Avoid diagonal moves.
                 */
                if ((D->val[x-1][y] == DMAP_IS_WALL) ||
                    (D->val[x][y-1] == DMAP_IS_WALL)) {
                    a = DMAP_IS_WALL;
                } else {
                    a = D->val[x-1][y-1];
                }

                b = D->val[x  ][y-1];

                if ((D->val[x+1][y] == DMAP_IS_WALL) ||
                    (D->val[x][y-1] == DMAP_IS_WALL)) {
                    c = DMAP_IS_WALL;
                } else {
                    c = D->val[x+1][y-1];
                }

                d = D->val[x-1][y];
                f = D->val[x+1][y];

                if ((D->val[x-1][y] == DMAP_IS_WALL) ||
                    (D->val[x][y+1] == DMAP_IS_WALL)) {
                    g = DMAP_IS_WALL;
                } else {
                    g = D->val[x-1][y+1];
                }

                h = D->val[x  ][y+1];

                if ((D->val[x+1][y] == DMAP_IS_WALL) ||
                    (D->val[x][y+1] == DMAP_IS_WALL)) {
                    i = DMAP_IS_WALL;
                } else {
                    i = D->val[x+1][y+1];
                }

                if (a < b) {
                    lowest = a;
                } else {
                    lowest = b;
                }

                if (c < lowest) { lowest = c; }
                if (d < lowest) { lowest = d; }
                if (f < lowest) { lowest = f; }
                if (g < lowest) { lowest = g; }
                if (h < lowest) { lowest = h; }
                if (i < lowest) { lowest = i; }

                if (*e - lowest >= 2) {
                    *e = lowest + 1;
                    changed = true;
                }
            }
        }
#if 0
        dmap_print(D);
#endif
    } while (changed);

    //
    // Mix in any original depth modifiers
    //
    for (y = miny + 1; y < maxy - 1; y++) {
        for (x = minx + 1; x < maxx - 1; x++) {
            int o = orig[x][y];
            if (o != DMAP_IS_WALL) {
                if (o > DMAP_IS_PASSABLE) {
                    o = o - DMAP_IS_PASSABLE;
                    int n = D->val[x][y];
                    if (o + n < DMAP_IS_PASSABLE) {
                        D->val[x][y] += o;
                    }
                }
            }
        }
    }
}

static bool is_movement_blocking_at (const Dmap *D, int x, int y)
{
    if ((x >= MAP_WIDTH) || (y >= MAP_HEIGHT) || (x < 0) || (y < 0)) {
        return (true);
    }

    if (D->val[x][y] == DMAP_IS_WALL) {
        return (true);
    }

    return (false);
}

/*
 * Make L shaped moves into diagonal ones
 */
void dmap_l_shaped_path_to_diag (const Dmap *D, std::vector<point> &path)
{
    for (;/*ever*/;) {
        auto modified = false;
        size_t i = 0;

        for (;/*ever*/;) {
            if (i + 2 >= path.size()) {
                break;
            }

            auto p = path[i];
            auto px = p.x;
            auto py = p.y;

            auto n = path[i + 1];
            auto nx = n.x;
            auto ny = n.y;

            auto m = path[i + 2];
            auto mx = m.x;
            auto my = m.y;

            if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny &&
                ! is_movement_blocking_at(D, px - 1, py)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny &&
                ! is_movement_blocking_at(D, px, py + 1)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny &&
                ! is_movement_blocking_at(D, px + 1, py)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny &&
                ! is_movement_blocking_at(D, px, py + 1)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny &&
                ! is_movement_blocking_at(D, px - 1, py)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny &&
                ! is_movement_blocking_at(D, px, py - 1)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny &&
                ! is_movement_blocking_at(D, px + 1, py)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && \
                ! is_movement_blocking_at(D, px, py - 1)) {
                path.erase(path.begin() + i);
                modified = true;
                break;
            }

            i++;
        }

        if (! modified) {
            break;
        }
    }
}

//
// Given 3 points, can we do a shortcut diagonal move?
//
bool dmap_can_i_move_diagonally (const Dmap *D, point a, point b, point c)
{
    auto px = a.x;
    auto py = a.y;

    auto nx = b.x;
    auto ny = b.y;

    auto mx = c.x;
    auto my = c.y;

    if (px - 1 == mx && py + 1 == my && px == nx && py + 1 == ny &&
        ! is_movement_blocking_at(D, px - 1, py)) {
        return (true);
    }

    if (px - 1 == mx && py + 1 == my && px - 1 == nx && py == ny &&
        ! is_movement_blocking_at(D, px, py + 1)) {
        return (true);
    }

    if (px + 1 == mx && py + 1 == my && px == nx && py + 1 == ny &&
        ! is_movement_blocking_at(D, px + 1, py)) {
        return (true);
    }

    if (px + 1 == mx && py + 1 == my && px + 1 == nx && py == ny &&
        ! is_movement_blocking_at(D, px, py + 1)) {
        return (true);
    }

    if (px - 1 == mx && py - 1 == my && px == nx && py - 1 == ny &&
        ! is_movement_blocking_at(D, px - 1, py)) {
        return (true);
    }

    if (px - 1 == mx && py - 1 == my && px - 1 == nx && py == ny &&
        ! is_movement_blocking_at(D, px, py - 1)) {
        return (true);
    }

    if (px + 1 == mx && py - 1 == my && px == nx && py - 1 == ny &&
        ! is_movement_blocking_at(D, px + 1, py)) {
        return (true);
    }

    if (px + 1 == mx && py - 1 == my && px + 1 == nx && py == ny && \
        ! is_movement_blocking_at(D, px, py - 1)) {
        return (true);
    }
    return (false);
}

std::vector<point> dmap_solve (const Dmap *D, const point start)
{
    static const std::vector<point> all_deltas = {
        point(0, -1),
        point(-1, 0),
        point(1, 0),
        point(0, 1),
    };

    static uint8_t walked[MAP_WIDTH][MAP_HEIGHT];
    memset(walked, 0, sizeof(walked));

    auto at = start;
    std::vector<point> out = { };

    for (;/*ever*/;) {
        auto x = at.x;
        auto y = at.y;

        if ((x >= MAP_WIDTH) || (y >= MAP_HEIGHT) || (x < 0) || (y < 0)) {
            return out;
        }

        int lowest = D->val[x][y];
        bool got = false;
        point best;

        if (D->val[x][y] == DMAP_IS_WALL) {
            return out;
        }

        for (auto d : all_deltas) {
            auto t = at + d;
            auto tx = t.x;
            auto ty = t.y;

            if ((tx >= MAP_WIDTH) || (ty >= MAP_HEIGHT) || (tx < 0) || (ty < 0)) {
                continue;
            }

            if (walked[tx][ty]) {
                continue;
            }

            if (D->val[tx][ty] == DMAP_IS_WALL) {
                continue;
            }

            if (D->val[tx][ty] == DMAP_IS_PASSABLE) {
                continue;
            }
            int c = D->val[tx][ty];
            if (c <= lowest) {
                got = true;
                best = t;
                lowest = c;
            }
        }

        if (!got) {
            return (out);
        }

        out.push_back(best);
        at = best;
        walked[best.x][best.y] = true;
    }
    return (out);
}
