//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_thing.h"

class ThingColl {
public:
    ThingColl(void) {}
    ThingColl(Thingp      target,
              std::string reason,
              uint16_t    priority,
              uint8_t     hitter_killed_on_hitting,
              uint8_t     hitter_killed_on_hit_or_miss) :
        target(target),
        reason(reason),
        priority(priority),
        hitter_killed_on_hitting(hitter_killed_on_hitting),
        hitter_killed_on_hit_or_miss(hitter_killed_on_hit_or_miss)
    { }

    Thingp      target {nullptr};
    std::string reason;
    uint16_t    priority {0};
    uint8_t     hitter_killed_on_hitting { false };
    uint8_t     hitter_killed_on_hit_or_miss { false };
};

static std::vector<class ThingColl> thing_colls;
static const int def_collision_radius = 1;
static int collision_radius = def_collision_radius;

bool 
thing_overlaps_border (Thingp t)
{_
    auto tile = t->current_tile;
    if (!tile) {
        return (false);
    }

    for (int y = 0; y < (int)tile->pix_height; y++) {
        for (int x = 0; x < (int)tile->pix_width; x++) {
            if (!tile->pix[x][y]) {
                continue;
            }
            
            int px = t->at.x * TILE_WIDTH + x;
            int py = t->at.y * TILE_HEIGHT + y;

            if (px < MAP_BORDER * TILE_WIDTH) {
                return (true);
            }

            if (py < MAP_BORDER * TILE_HEIGHT) {
                return (true);
            }

            if (px >= (MAP_WIDTH - MAP_BORDER) * TILE_WIDTH) {
                return (true);
            }

            if (py >= (MAP_HEIGHT - MAP_BORDER) * TILE_HEIGHT) {
                return (true);
            }
        }
    }
    return (false);
}

bool 
things_tile_overlap (Thingp t, fpoint t_at, Thingp o)
{_
    auto tile1 = t->current_tile;
    if (!tile1) {
        return (false);
    }
    auto tile2 = o->current_tile;
    if (!tile2) {
        return (false);
    }

    for (int y = 0; y < (int)tile1->pix_height; y++) {
        for (int x = 0; x < (int)tile1->pix_width; x++) {
            if (!tile1->pix[x][y]) {
                continue;
            }
            
            int px = t_at.x * TILE_WIDTH + x;
            int py = t_at.y * TILE_HEIGHT + y;

            int ox = o->at.x * TILE_WIDTH;
            int oy = o->at.y * TILE_HEIGHT;

            int dx = px - ox;
            int dy = py - oy;

            if ((dx < 0) || (dx >= (int)tile2->pix_width)) {
#if 0
if (first) {
first = 0; CON("         pix %3d,%3d %s:%3d,%3d  dx %d,%d  <>x", px, py, thing_logname(o).c_str(), ox, oy, dx, dy);
}
#endif
                continue;
            }

            if ((dy < 0) || (dy >= (int)tile2->pix_height)) {
#if 0
if (first) {
first = 0; CON("         pix %3d,%3d %s:%3d,%3d  dx %d,%d  <>y", px, py, thing_logname(o).c_str(), ox, oy, dx, dy);
}
#endif
                continue;
            }

            if (tile2->pix[dx][dy]) {
#if 0
first = 0; CON("         pix %3d,%3d %s:%3d,%3d  dx %d,%d  overlap", px, py, thing_logname(o).c_str(), ox, oy, dx, dy);
#endif
                return (true);
            }
        }
    }
    return (false);
}

bool 
things_tile_overlap (Thingp t, Thingp o)
{_
    return (things_tile_overlap(t, t->at, o));
}


int circle_box_collision (Thingp C, 
                          fpoint C_at,
                          Thingp B,
                          fpoint B_at,
                          fpoint *normal,
                          fpoint *intersect,
                          int check_only)
{
    fpoint C0, C1, C2, C3;
    C->to_coords(&C0, &C1, &C2, &C3);
    auto C_offset = C_at - C->at;
    C0 += C_offset;
    C1 += C_offset;
    C2 += C_offset;
    C3 += C_offset;

    fpoint B0, B1, B2, B3;
    B->to_coords(&B0, &B1, &B2, &B3);
    auto B_offset = B_at - B->at;
    B0 += B_offset;
    B1 += B_offset;
    B2 += B_offset;
    B3 += B_offset;

    double radius = fmin((C1.x - C0.x) / 2.0, (C2.y - C0.y) / 2.0);

    /*
     * Corner collisions, normal is at 45 degrees. Unless there is a wall.
     */
    if (distance(C_at, B0) < radius) {
        if (!game.state.map.is_wall_at(B->at.x - 1, B->at.y)) {
            normal->x = C_at.x - B0.x;
            normal->y = C_at.y - B0.y;
            return (true);
        }
    }

    if (distance(C_at, B1) < radius) {
        if (!game.state.map.is_wall_at(B->at.x + 1, B->at.y)) {
            normal->x = C_at.x - B1.x;
            normal->y = C_at.y - B1.y;
            return (true);
        }
    }

    if (distance(C_at, B2) < radius) {
        if (!game.state.map.is_wall_at(B->at.x + 1, B->at.y)) {
            normal->x = C_at.x - B2.x;
            normal->y = C_at.y - B2.y;
            return (true);
        }
    }

    if (distance(C_at, B3) < radius) {
        if (!game.state.map.is_wall_at(B->at.x - 1, B->at.y)) {
            normal->x = C_at.x - B3.x;
            normal->y = C_at.y - B3.y;
            return (true);
        }
    }

    double dist;
    if (distance_to_line(C_at, B0, B1, &dist, 0)) {
        if (dist < radius) {
            goto collided;
        }
    }

    if (distance_to_line(C_at, B1, B2, &dist, 0)) {
        if (dist < radius) {
            goto collided;
        }
    }

    if (distance_to_line(C_at, B2, B3, &dist, 0)) {
        if (dist < radius) {
            goto collided;
        }
    }

    if (distance_to_line(C_at, B3, B0, &dist, 0)) {
        if (dist < radius) {
            goto collided;
        }
    }

    return (false);

collided:

    if (check_only) {
        return (true);
    }

    fpoint delta;

    if (get_line_intersection(C_at, B_at, B0, B1, intersect)) {
        delta.x = B0.x - B1.x;
        delta.y = B0.y - B1.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    if (get_line_intersection(C_at, B_at, B1, B2, intersect)) {
        delta.x = B1.x - B2.x;
        delta.y = B1.y - B2.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    if (get_line_intersection(C_at, B_at, B2, B3, intersect)) {
        delta.x = B2.x - B3.x;
        delta.y = B2.y - B3.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    if (get_line_intersection(C_at, B_at, B3, B0, intersect)) {
        delta.x = B3.x - B0.x;
        delta.y = B3.y - B0.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return (true);
    }

    /*
     * Sphere may be inside box.
     */
    return (false);
}

/*
 * If two circles collide, the resultant direction is along the normal between
 * the two center of masses of the circles.
 */
int circle_circle_collision (Thingp A, 
                             Thingp B,
                             fpoint at,
                             fpoint *intersect)
{
    double Ax = A->at.x;
    double Ay = A->at.y;
    Ax += (at.x - A->at.x);
    Ay += (at.y - A->at.y);

    fpoint A_at = { Ax, Ay };
    fpoint A0, A1, A2, A3;
    A->to_coords(&A0, &A1, &A2, &A3);
    double A_radius = fmin((A1.x - A0.x) / 2.0, (A2.y - A0.y) / 2.0);

    double Bx = B->at.x;
    double By = B->at.y;

    fpoint B_at = { Bx, By };
    fpoint B0, B1, B2, B3;
    B->to_coords(&B0, &B1, &B2, &B3);
    double B_radius = fmin((B1.x - B0.x) / 2.0, (B2.y - B0.y) / 2.0);

    fpoint n = B_at - A_at;
    double touching_dist = A_radius + B_radius;
    double dist_squared = n.x*n.x + n.y*n.y;

    double diff = dist_squared - touching_dist * touching_dist;
    if (diff > 0.0) {
        /*
         * Circles are not touching
         */
        return (false);
    }

    diff = sqrt(fabs(diff));
    diff /= 2.0;

    n = unit(n);
    n *= (A_radius - diff);
    n += A_at;
    *intersect = n;

    return (true);
}

/*
 * Add a thing to the list of things that could be hit on this attack.
 */
static void 
thing_add_possible_hit (Thingp target,
                        std::string reason,
                        int hitter_killed_on_hitting,
                        int hitter_killed_on_hit_or_miss)
{_
    thing_colls.push_back(
      ThingColl::ThingColl(target,
                reason,
                tp_collision_hit_priority(target->tp),
                hitter_killed_on_hitting,
                hitter_killed_on_hit_or_miss));
}

void 
thing_possible_hit_add (Thingp target, std::string reason)
{
    thing_add_possible_hit(target, reason, false, false);
}

void 
thing_possible_hit_add_hitter_killed_on_hitting (Thingp target,
                                                 std::string reason)
{
    thing_add_possible_hit(target, reason, true, false);
}

void 
thing_possible_hit_add_hitter_killed_on_hit_or_miss (Thingp target,
                                                     std::string reason)
{
    thing_add_possible_hit(target, reason, false, true);
}

/*
 * Reset the list of things we can possibly hit.
 */
void thing_possible_init (void)
{
    thing_colls.resize(0);
}

/*
 * Find the thing with the highest priority to hit.
 */
void Thing::possible_hits_find_best (void)
{_
    auto me = this;
    ThingColl *best = nullptr;

    for (auto cand : thing_colls) {
        /*
         * Don't be silly and hit yourself.
         */
        if (cand.target == me) {
            continue;
        }

        /*
         * Skip things that aren't really hitable.
         */
        if (tp_gfx_is_weapon_carry_anim_only(cand.target->tp)) {
            continue;
        }

        if (!best) {
            best = &cand;
            continue;
        }

        if (cand.priority > best->priority) {
            /*
             * If this target is higher prio, prefer it.
             */
            best = &cand;
        } else if (cand.priority == best->priority) {
            /*
             * If this target is closer, prefer it.
             */
            double dist_best = DISTANCE(me->at.x, me->at.y,
                                        best->target->at.x, 
                                        best->target->at.y);
            double dist_cand = DISTANCE(me->at.x, me->at.y,
                                        cand.target->at.x, 
                                        cand.target->at.y);

            if (dist_cand < dist_best) {
                best = &cand;
            }
        }
    }

    if (best) {
con("hit %s", best->target->logname().c_str());
        if (best->target->hit_possible(me, 0)) {
            if (best->hitter_killed_on_hitting) {
                me->dead("self killed on hitting");
            }
        } else if (best->hitter_killed_on_hit_or_miss) {
            me->dead("self killed on hitting");
        }
    }

    thing_possible_init();
}

bool things_overlap (const Thingp A, fpoint future_pos, const Thingp B)
{_
    fpoint A_at, B_at;

    /*
     * If -1, -1 then we are looking at the current position.
     *
     * If not then we are just checking out a future_pos position.
     */
    if (future_pos == fpoint(-1, -1)) {
        A_at = A->at;
        B_at = B->at;
    } else {
        A_at = future_pos;
        B_at = B->at;
    }

    int check_only = true;
    fpoint intersect = {0,0};
    fpoint normal_A = {0,0};

    if (tp_collision_circle(A->tp) && 
        !tp_collision_circle(B->tp)) {
        if (circle_box_collision(A, /* circle */
                                 A_at,
                                 B, /* box */
                                 B_at,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (things_tile_overlap(A, future_pos, B));
        }
        return (false);
    }

    if (!tp_collision_circle(A->tp) && 
         tp_collision_circle(B->tp)) {
        if (circle_box_collision(B, /* circle */
                                 B_at,
                                 A, /* box */
                                 A_at,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (things_tile_overlap(A, future_pos, B));
        }
        return (false);
    }

    if (tp_collision_circle(A->tp) &&
        tp_collision_circle(B->tp)) {
CON("no circl overlap %s %s", A->logname().c_str(), B->logname().c_str());
        if (circle_circle_collision(A, /* circle */
                                    B, /* box */
                                    A_at,
                                    &intersect)) {
            return (things_tile_overlap(A, future_pos, B));
        }
DIE("circl overlap %s %s", A->logname().c_str(), B->logname().c_str());
        return (false);
    }

    return (things_tile_overlap(A, future_pos, B));
}

bool things_overlap (const Thingp A, const Thingp B)
{_
    return (things_overlap (A, fpoint(-1, -1), B));
}

//
// handle a single collision between two things
//
// false aborts the walk
//
bool Thing::possible_hit (Thingp it, int x, int y, int dx, int dy)
{_
    auto me = this;
    auto it_tp = it->tp;
    auto me_tp = me->tp;

    /*
     * Filter out boring things.
     */
    if (tp_gfx_is_weapon_carry_anim_only(it_tp)) {
#if 0
        if ((dx == 0) && (dy == 0)) {
            if (tp_is_player(me)) {
                if (tp_is_shop_floor(it_tp)) {
                    /*
                     * Going into a shop.
                     */
                    shop_enter(level, me, it_tp);
                } else if (me->in_shop_owned_by_thing_id) {
                    /*
                     * Still inside the shop?
                     */
                    if (!shop_inside(level, me)) {
                        shop_leave(level, me, it_tp);
                    }
                }
            }
        }
#endif

        return (true);
    }

    if (it->is_dead) {
        return (true);
    }

    Thingp owner_it = it->get_owner();
    Thingp owner_me = me->get_owner();

    /*
     * Need this or shields attack the player.
     */
    if ((owner_it == me) || (owner_me == it)) {
        return (true);
    }

    /*
     * Do we overlap with something?
     */
    if (!things_overlap(me, it)) {
        return (true);
    }

    /*
     * Sword use hits?
     */
    if (tp_gfx_is_weapon_use_anim(me_tp)) {
        if (tp_is_monst(it_tp)) {
            /*
             * Weapon hits monster or generator.
             */
            thing_possible_hit_add_hitter_killed_on_hitting(
                    it, "sword hit thing");
            return (true);
        }
    }

    return (true);
}

/*
 * Have we hit anything?
 */
bool Thing::handle_collisions (void)
{_
    int minx = at.x - collision_radius;
    while (minx < 0) {
        minx++;
    }

    int miny = at.y - collision_radius;
    while (miny < 0) {
        miny++;
    }

    int maxx = at.x - collision_radius;
    while (maxx >= MAP_WIDTH) {
        maxx++;
    }

    int maxy = at.y - collision_radius;
    while (maxy >= MAP_HEIGHT) {
        maxy++;
    }

    for (int16_t x = minx; x <= maxx; x++) {
        auto dx = x - at.x;
        for (int16_t y = miny; y <= maxy; y++) {
            auto dy = y - at.y;
            for (auto p : game.state.map.all_non_boring_things_at[x][y]) {
                auto it = p.second;
                if (this == it) {
                    continue;
                }

                if (!possible_hit(it, x, y, dx, dy)) {
                    return (false);
                }
            }
        }
    }

    possible_hits_find_best();

    return (true);
}

/*
 * Will we hit anything?
 */
bool Thing::check_if_will_hit_solid_obstacle (fpoint future_pos)
{_
    verify(this);

    int minx = at.x - collision_radius;
    while (minx < 0) {
        minx++;
    }

    int miny = at.y - collision_radius;
    while (miny < 0) {
        miny++;
    }

    int maxx = at.x - collision_radius;
    while (maxx >= MAP_WIDTH) {
        maxx--;
    }

    int maxy = at.y - collision_radius;
    while (maxy >= MAP_HEIGHT) {
        maxy--;
    }

    for (uint8_t z = MAP_DEPTH_ITEM; z < MAP_DEPTH; z++) {
        for (int16_t x = minx; x <= maxx; x++) {
            for (int16_t y = miny; y <= maxy; y++) {
                //
                // Walk things like monsters and walls, but skip stuff like
                // floor tiles and decorations
                //
                for (auto p : game.state.map.all_non_boring_things_at[x][y]) {
                    auto it = p.second;
                    verify(it);

                    if (this == it) {
                        continue;
                    }

                    if (!things_overlap(this, future_pos, it)) {
                        continue;
                    }

                    auto it_tp = it->tp;
                    if (tp_is_wall(it_tp)) {
                        return (true);
                    }
                }
            }
        }
    }

    return (false);
}
