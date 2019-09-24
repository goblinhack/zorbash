//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_game.h"

#undef DEBUG_COLLISION

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
static const double thing_collision_tiles = 1;

static bool
things_tile_overlap (Thingp A, Thingp B)
{_
    auto A_tile = tile_index_to_tile(A->tile_curr);
    if (!A_tile) {
        return (false);
    }
    auto B_tile = tile_index_to_tile(B->tile_curr);
    if (!B_tile) {
        return (false);
    }

    double A_width  = (A->last_blit_br.x - A->last_blit_tl.x);
    double A_height = (A->last_blit_br.y - A->last_blit_tl.y);
    double B_width  = (B->last_blit_br.x - B->last_blit_tl.x);
    double B_height = (B->last_blit_br.y - B->last_blit_tl.y);

    double A_dw = A_width  / (double)A_tile->pix_width;
    double A_dh = A_height / (double)A_tile->pix_height;
    double B_dw = B_width  / (double)B_tile->pix_width;
    double B_dh = B_height / (double)B_tile->pix_height;

    for (int y = 0; y < (int)A_tile->pix_height; y++) {
        for (int x = 0; x < (int)A_tile->pix_width; x++) {
            if (!get(A_tile->pix, x, y)) {
#ifdef DEBUG_COLLISION
                printf(" ");
#endif
                continue;
            }
#ifdef DEBUG_COLLISION
            printf("A");
#endif
            double Ax = A->last_blit_tl.x + (((double)x) * A_dw);
            double Ay = A->last_blit_tl.y + (((double)y) * A_dh);
            Ax -= B->last_blit_tl.x;
            Ay -= B->last_blit_tl.y;
            Ax /= B_dw;
            Ay /= B_dh;

            int dx = (int)Ax;
            int dy = (int)Ay;

            if ((dx < 0) || (dx >= (int)B_tile->pix_width)) {
                continue;
            }

            if ((dy < 0) || (dy >= (int)B_tile->pix_height)) {
                continue;
            }

            if (get(B_tile->pix, dx, dy)) {
                return (true);
            }
        }
#ifdef DEBUG_COLLISION
        printf("\n");
#endif
    }
#ifdef DEBUG_COLLISION
    printf("\n");
#endif

#ifdef DEBUG_COLLISION
    for (int y = 0; y < (int)A_tile->pix_height; y++) {
        for (int x = 0; x < (int)A_tile->pix_width; x++) {
            double Ax = A->last_blit_tl.x + (((double)x) * A_dw);
            double Ay = A->last_blit_tl.y + (((double)y) * A_dh);
            Ax -= B->last_blit_tl.x;
            Ay -= B->last_blit_tl.y;
            Ax /= B_dw;
            Ay /= B_dh;

            int dx = (int)Ax;
            int dy = (int)Ay;

            if ((dx < 0) || (dx >= (int)B_tile->pix_width)) {
                printf("-");
                continue;
            }

            if ((dy < 0) || (dy >= (int)B_tile->pix_height)) {
                printf("-");
                continue;
            }

            if (get(B_tile->pix, dx, dy)) {
                printf("B");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
#endif
    return (false);
}

#if 0
static int circle_box_collision (Thingp C,
                                 fpoint C_at,
                                 Thingp B,
                                 fpoint B_at,
                                 fpoint *normal,
                                 fpoint *intersect,
                                 int check_only)
{
    fpoint C0, C1, C2, C3;
    C->to_coords(&C0, &C1, &C2, &C3);
    auto C_offset = C_at - C->interpolated_mid_at;
    C0 += C_offset;
    C1 += C_offset;
    C2 += C_offset;
    C3 += C_offset;

    fpoint B0, B1, B2, B3;
    B->to_coords(&B0, &B1, &B2, &B3);
    auto B_offset = B_at - B->interpolated_mid_at;
    B0 += B_offset;
    B1 += B_offset;
    B2 += B_offset;
    B3 += B_offset;

    double radius = fmin((C1.x - C0.x) / 2.0, (C2.y - C0.y) / 2.0);

    /*
     * Corner collisions, normal is at 45 degrees. Unless there is a wall.
     */
    if (distance(C_at, B0) < radius) {
        if (!world->is_wall(B->interpolated_mid_at.x - 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B0.x;
            normal->y = C_at.y - B0.y;
            return (true);
        }
    }

    if (distance(C_at, B1) < radius) {
        if (!world->is_wall(B->interpolated_mid_at.x + 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B1.x;
            normal->y = C_at.y - B1.y;
            return (true);
        }
    }

    if (distance(C_at, B2) < radius) {
        if (!world->is_wall(B->interpolated_mid_at.x + 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B2.x;
            normal->y = C_at.y - B2.y;
            return (true);
        }
    }

    if (distance(C_at, B3) < radius) {
        if (!world->is_wall(B->interpolated_mid_at.x - 1,
                                       B->interpolated_mid_at.y)) {
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
static int circle_circle_collision (Thingp A,
                                    Thingp B,
                                    fpoint at,
                                    fpoint *intersect)
{
    double Ax = A->interpolated_mid_at.x;
    double Ay = A->interpolated_mid_at.y;
    Ax += (at.x - A->interpolated_mid_at.x);
    Ay += (at.y - A->interpolated_mid_at.y);

    fpoint A_at = { Ax, Ay };
    //fpoint A0, A1, A2, A3;
    //A->to_coords(&A0, &A1, &A2, &A3);
    //double A_radius = fmin((A1.x - A0.x) / 2.0, (A2.y - A0.y) / 2.0);
    double A_radius = tp_collision_radius(A->tp);

    double Bx = B->interpolated_mid_at.x;
    double By = B->interpolated_mid_at.y;

    fpoint B_at = { Bx, By };
    //fpoint B0, B1, B2, B3;
    //B->to_coords(&B0, &B1, &B2, &B3);
    //double B_radius = fmin((B1.x - B0.x) / 2.0, (B2.y - B0.y) / 2.0);
    double B_radius = tp_collision_radius(B->tp);

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
#endif

/*
 * Add a thing to the list of things that could be hit on this attack.
 */
static void
thing_add_ai_possible_hit (Thingp target,
                           std::string reason,
                           int hitter_killed_on_hitting,
                           int hitter_killed_on_hit_or_miss)
{_
    thing_colls.push_back(
      ThingColl(target,
                reason,
                tp_collision_hit_priority(target->tp()),
                hitter_killed_on_hitting,
                hitter_killed_on_hit_or_miss));
}

static void
thing_ai_possible_hit_add (Thingp target, std::string reason)
{
    thing_add_ai_possible_hit(target, reason, false, false);
}

static void
thing_ai_possible_hit_add_hitter_killed_on_hitting (Thingp target,
                                                 std::string reason)
{
    thing_add_ai_possible_hit(target, reason, true, false);
}

#if 0
static void
thing_ai_possible_hit_add_hitter_killed_on_hit_or_miss (Thingp target,
                                                     std::string reason)
{
    thing_add_ai_possible_hit(target, reason, false, true);
}
#endif

/*
 * Reset the list of things we can possibly hit.
 */
static void thing_possible_init (void)
{
    thing_colls.resize(0);
}

/*
 * Find the thing with the highest priority to hit.
 */
void Thing::ai_possible_hits_find_best (void)
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
        if (tp_gfx_is_weapon_carry_anim(cand.target->tp())) {
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
            auto me_pos = get_interpolated_mid_at();
            auto best_pos = best->target->get_interpolated_mid_at();

            double dist_best = DISTANCE(me_pos.x,
                                        me_pos.y,
                                        best_pos.x,
                                        best_pos.y);
            double dist_cand = DISTANCE(me_pos.x,
                                        me_pos.y,
                                        best_pos.x,
                                        best_pos.y);

            if (dist_cand < dist_best) {
                best = &cand;
            }
        }
    }

    if (best) {
        int damage = 0;

        auto it = best->target;
        if (will_eat(it)) {
            damage = bite_damage();
            health_boost(it->is_nutrition());
        }

        if (it->ai_ai_hit_if_possible(me, damage)) {
            if (best->hitter_killed_on_hitting) {
                me->dead("self killed on hitting");
            }
        } else if (best->hitter_killed_on_hit_or_miss) {
            me->dead("self killed on hitting");
        }
    }

    thing_possible_init();
}

bool things_overlap (const Thingp A, const Thingp B)
{_
#if 0
    fpoint A_at, B_at;

    A_at = A->interpolated_mid_at;
    B_at = B->interpolated_mid_at;

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
            return (things_tile_overlap(A, B));
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
            return (things_tile_overlap(A, B));
        }
        return (false);
    }

    if (tp_collision_circle(A->tp) &&
        tp_collision_circle(B->tp)) {
        if (circle_circle_collision(A, /* circle */
                                    B, /* box */
                                    A_at,
                                    &intersect)) {
            return (things_tile_overlap(A, B));
        }
        return (false);
    }
#endif

    return (things_tile_overlap(A, B));
}

//
// handle a single collision between two things
//
// false aborts the walk
//
bool Thing::ai_possible_hit (Thingp it, int x, int y, int dx, int dy)
{_
    auto me = this;
    auto it_tp = it->tp();
    auto me_tp = me->tp();

    if (it->is_dead) {
        return (true);
    }

    Thingp owner_it = it->owner_get();
    Thingp owner_me = me->owner_get();

    /*
     * Need this or shields attack the player.
     */
    if ((owner_it == me) || (owner_me == it)) {
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
            if (things_overlap(me, it)) {
                thing_ai_possible_hit_add_hitter_killed_on_hitting(
                        it, "sword hit thing");
            }
        }
    } else if (will_attack(it)) {
        if (tp_collision_attack(me_tp)) {
            if (things_overlap(me, it)) {
                thing_ai_possible_hit_add(it, "battle");
            }
        }
    } else if (will_eat(it)) {
        if (things_overlap(me, it)) {
            thing_ai_possible_hit_add(it, "eat");
        }
    }

    return (true);
}

/*
 * Have we hit anything?
 */
bool Thing::ai_collisions_handle (void)
{_
    int minx = mid_at.x - thing_collision_tiles;
    while (minx < 0) {
        minx++;
    }

    int miny = mid_at.y - thing_collision_tiles;
    while (miny < 0) {
        miny++;
    }

    int maxx = mid_at.x + thing_collision_tiles;
    while (maxx >= MAP_WIDTH) {
        maxx--;
    }

    int maxy = mid_at.y + thing_collision_tiles;
    while (maxy >= MAP_HEIGHT) {
        maxy--;
    }

    for (int16_t x = minx; x <= maxx; x++) {
        auto dx = x - mid_at.x;
        for (int16_t y = miny; y <= maxy; y++) {
            auto dy = y - mid_at.y;
            FOR_ALL_INTERESTING_THINGS(world, it, x, y) {
                if (this == it) {
                    continue;
                }

                if (it->is_hidden) {
                    continue;
                }

                if (!ai_possible_hit(it, x, y, dx, dy)) {
                    return (false);
                }
            }
        }
    }

    ai_possible_hits_find_best();

    return (true);
}
