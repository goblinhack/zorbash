/*
 * Copyright (C) 2011-2017 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_main.h"
#include "my_thing.h"
#include "my_tile.h"
#include "my_math_util.h"

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
                             double nx,
                             double ny,
                             fpoint *intersect)
{
    double Ax = A->at.x;
    double Ay = A->at.y;
    Ax += (nx - A->at.x);
    Ay += (ny - A->at.y);

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

#if 0
typedef struct {
    Thingp target;
    const char *reason;
    uint16_t priority;
    uint8_t hitter_killed_on_hitting:1;
    uint8_t hitter_killed_on_hit_or_miss:1;
} thing_possible_hit;

#define MAX_THING_POSSIBLE_HIT 16

static thing_possible_hit thing_possible_hits[MAX_THING_POSSIBLE_HIT];
static uint32_t thing_possible_hit_size;
static const int def_collision_radius = 4;
static int collision_radius = def_collision_radius;

/*
 * Add a thing to the list of things that could be hit on this attack.
 */
static void 
thing_possible_hit_add_hitter_killed_on_hitting_ (Thingp target,
                                                  const char *reason,
                                                  int hitter_killed_on_hitting,
                                                  int hitter_killed_on_hit_or_miss)
{
    if (thing_possible_hit_size >= MAX_THING_POSSIBLE_HIT) {
        return;
    }

    thing_possible_hit *h = &thing_possible_hits[thing_possible_hit_size++];
    memset(h, 0, sizeof(*h));
    h->target = target;
    h->priority = tp_get_weapon_hit_priority(thing_tp(target));
    h->hitter_killed_on_hitting = hitter_killed_on_hitting;
    h->hitter_killed_on_hit_or_miss = hitter_killed_on_hit_or_miss;
}

static void 
thing_possible_hit_add (Thingp target, const char *reason)
{
    thing_possible_hit_add_hitter_killed_on_hitting_(target,
                                                     reason,
                                                     false,
                                                     false);
}

static void 
thing_possible_hit_add_hitter_killed_on_hitting (Thingp target,
                                                 const char *reason)
{
    thing_possible_hit_add_hitter_killed_on_hitting_(target,
                                                     reason,
                                                     true,
                                                     false);
}

static void 
thing_possible_hit_add_hitter_killed_on_hit_or_miss (Thingp target,
                                                 const char *reason)
{
    thing_possible_hit_add_hitter_killed_on_hitting_(target,
                                                     reason,
                                                     false,
                                                     true);
}

/*
 * Reset the list of things we can possibly hit.
 */
static void thing_possible_init (void)
{
    thing_possible_hit_size = 0;
}

/*
 * Find the thing with the highest priority to hit.
 */
static void thing_possible_hit_do (levelp level, Thingp hitter)
{
    thing_possible_hit *best = 0;
    uint32_t i;

    for (i = 0; i < thing_possible_hit_size; i++) {
        thing_possible_hit *cand = &thing_possible_hits[i];

        /*
         * Don't be silly and hit yourself.
         */
        if (cand->target == hitter) {
            continue;
        }

        /*
         * Skip things that aren't really hitable.
         */
        if (thing_is_animation(cand->target)            ||
            thing_is_cloud_effect(cand->target)         ||
            thing_is_weapon_carry_anim(cand->target)) {
            continue;
        }

        /*
         * If you fall and land behind something, it's safe.
         */
        if (cand->target->fall_speed) {
            if (hitter->dx > 0) {
                if (cand->target->x < hitter->x) {
                    continue;
                }
            }

            if (hitter->dx < 0) {
                if (cand->target->x > hitter->x) {
                    continue;
                }
            }
        }

        if (!best) {
            best = cand;
            continue;
        }

        if (cand->priority > best->priority) {
            /*
             * If this target is higher prio, prefer it.
             */
            best = cand;
        } else if (cand->priority == best->priority) {
            /*
             * If this target is closer, prefer it.
             */
            double dist_best = DISTANCE(hitter->x, hitter->y,
                                        best->target->x, best->target->y);
            double dist_cand = DISTANCE(hitter->x, hitter->y,
                                        cand->target->x, cand->target->y);

            if (dist_cand < dist_best) {
                best = cand;
            }
        }
if (0) {
CON("hitter %s dx %f x %f target %s x %f",
    thing_logname(hitter),
    hitter->dx, hitter->x,
    thing_logname(cand->target),
    cand->target->x);
}
    }

    if (best) {
if (0) {
CON("hitter %s best %s and hitter_killed_on_hitting %d",thing_logname(hitter),thing_logname(best->target), best->hitter_killed_on_hitting);
}
        if (thing_hit(level, best->target, hitter, 0)) {
            if (best->hitter_killed_on_hitting) {
                thing_dead(level, hitter, 0, "hitter killed on hitting");
            }
        } else if (best->hitter_killed_on_hit_or_miss) {
            thing_dead(level, hitter, 0, "hitter killed on hitting");
        }
    }

    thing_possible_init();
}

/*
 * Things move in jumps. Find the real position the client
 * will see so collisions look more accurate.
 */
void 
thingp_get_interpolated_position (const Thingp t, double *x, double *y)
{
    widp w = thing_wid(t);

    if (!wid_is_moving(w)) {
        *x = t->x;
        *y = t->y;
        return;
    }

    double wdx, wdy;
    double dx = t->x - t->last_x;
    double dy = t->y - t->last_y;

    wid_get_move_interpolated_progress(thing_wid(t), &wdx, &wdy);

    *x = t->last_x + (dx * wdx);
    *y = t->last_y + (dy * wdy);
}

static uint8_t things_overlap (levelp level,
                               const Thingp A, 
                               double nx,
                               double ny,
                               const Thingp B)
{
    static tilep wall;
    static double collision_map_large_x1;
    static double collision_map_large_x2;
    static double collision_map_large_y1;
    static double collision_map_large_y2;
    static double collision_map_medium_x1;
    static double collision_map_medium_x2;
    static double collision_map_medium_y1;
    static double collision_map_medium_y2;
    static double collision_map_small_x1;
    static double collision_map_small_x2;
    static double collision_map_small_y1;
    static double collision_map_small_y2;
    static double collision_map_tiny_x1;
    static double collision_map_tiny_x2;
    static double collision_map_tiny_y1;
    static double collision_map_tiny_y2;

    double Ax, Ay;
    double Bx, By;

    /*
     * If -1, -1 then we are looking at the current position.
     *
     * If not then we are just checking out a future position.
     */
    if ((nx == -1.0) && (ny == -1.0)) {
        thingp_get_interpolated_position(A, &Ax, &Ay);
        thingp_get_interpolated_position(B, &Bx, &By);
    } else {
        Ax = nx;
        Ay = ny;
        Bx = B->x;
        By = B->y;
    }

    /*
     * The tiles are considered to be 1 unit wide. However the actual pixels
     * of each tile include shadows. px1/px2 are the bounds and exclude the
     * shadows. So we need to scale up the px1/px2 bounds to 1 as if the 
     * shadow pixels were not there.
     */
    if (!wall) {
        wall = tile_find("wall1_0_0");
        if (!wall) {
            ERR("no wall for collisions");
        }

        tilep tile = tile_find("large-collision-map");
        if (!tile) {
            ERR("no tile for collisions");
        }

        collision_map_large_x1 = tile->px1;
        collision_map_large_x2 = tile->px2;
        collision_map_large_y1 = tile->py1;
        collision_map_large_y2 = tile->py2;

        tile = tile_find("medium-collision-map");
        if (!tile) {
            ERR("no tile for collisions");
        }

        collision_map_medium_x1 = tile->px1;
        collision_map_medium_x2 = tile->px2;
        collision_map_medium_y1 = tile->py1;
        collision_map_medium_y2 = tile->py2;

        tile = tile_find("small-collision-map");
        if (!tile) {
            ERR("no tile for collisions");
        }

        collision_map_small_x1 = tile->px1;
        collision_map_small_x2 = tile->px2;
        collision_map_small_y1 = tile->py1;
        collision_map_small_y2 = tile->py2;

        tile = tile_find("small-collision-map");
        if (!tile) {
            ERR("no tile for collisions");
        }

        collision_map_small_x1 = tile->px1;
        collision_map_small_x2 = tile->px2;
        collision_map_small_y1 = tile->py1;
        collision_map_small_y2 = tile->py2;
    }

    double Apx1;
    double Apx2;
    double Apy1;
    double Apy2;

    double Bpx1;
    double Bpx2;
    double Bpy1;
    double Bpy2;

    widp Aw = thing_wid(A);
    widp Bw = thing_wid(B);

    if (0 &&
        ((thing_is_player(A) && thing_is_monst(B)) ||
         (thing_is_player(B) && thing_is_monst(A)))) {

        tilep tileA = wid_get_tile(Aw);
        if (!tileA) {
            DIE("no tile for thing A %s", thing_logname(A));
            return (false);
        }

        Apx1 = tileA->px1;
        Apx2 = tileA->px2;
        Apy1 = tileA->py1;
        Apy2 = tileA->py2;

        tilep tileB = wid_get_tile(Bw);
        if (!tileB) {
            DIE("no tile for thing B %s", thing_logname(B));
            return (false);
        }

        Bpx1 = tileB->px1;
        Bpx2 = tileB->px2;
        Bpy1 = tileB->py1;
        Bpy2 = tileB->py2;

    } else {
        if (thing_is_wall(A) || thing_is_door(A)) {
            tilep tileA = wid_get_tile(Aw);
            if (!tileA) {
                DIE("no tile for thing A %s", thing_logname(A));
                return (false);
            }

            Apx1 = tileA->px1;
            Apx2 = tileA->px2;
            Apy1 = tileA->py1;
            Apy2 = tileA->py2;

#if 0
            double tile_width = (Apx2 - Apx1);
            double tile_height = (Apy2 - Apy1);

            Apy1 -= tile_height / 3.0;
            Apx2 += tile_width / 3.0;
#endif

        } else if (thing_is_collision_map_large(A)) {
            Apx1 = collision_map_large_x1;
            Apx2 = collision_map_large_x2;
            Apy1 = collision_map_large_y1;
            Apy2 = collision_map_large_y2;
        } else if (thing_is_collision_map_medium(A)) {
            Apx1 = collision_map_medium_x1;
            Apx2 = collision_map_medium_x2;
            Apy1 = collision_map_medium_y1;
            Apy2 = collision_map_medium_y2;
        } else if (thing_is_collision_map_small(A)) {
            Apx1 = collision_map_small_x1;
            Apx2 = collision_map_small_x2;
            Apy1 = collision_map_small_y1;
            Apy2 = collision_map_small_y2;
        } else if (thing_is_collision_map_tiny(A)) {
            Apx1 = collision_map_tiny_x1;
            Apx2 = collision_map_tiny_x2;
            Apy1 = collision_map_tiny_y1;
            Apy2 = collision_map_tiny_y2;
        } else {
            /*
            * Just use pixel and alpha values.
            */
            tilep tileA = wid_get_tile(Aw);
            if (!tileA) {
                DIE("no tile for thing A %s", thing_logname(A));
                return (false);
            }

            Apx1 = tileA->px1;
            Apx2 = tileA->px2;
            Apy1 = tileA->py1;
            Apy2 = tileA->py2;
        }

        if (thing_is_wall(B) || thing_is_door(B)) {
            tilep tileB = wid_get_tile(Bw);
            if (!tileB) {
                DIE("no tile for thing B %s", thing_logname(B));
                return (false);
            }

            Bpx1 = tileB->px1;
            Bpx2 = tileB->px2;
            Bpy1 = tileB->py1;
            Bpy2 = tileB->py2;

#if 0
            double tile_width = (Bpx2 - Bpx1);
            double tile_height = (Bpy2 - Bpy1);

            Bpy1 -= tile_height / 3.0;
            Bpx2 += tile_width / 3.0;
#endif

        } else if (thing_is_collision_map_large(B)) {
            Bpx1 = collision_map_large_x1;
            Bpx2 = collision_map_large_x2;
            Bpy1 = collision_map_large_y1;
            Bpy2 = collision_map_large_y2;
        } else if (thing_is_collision_map_medium(B)) {
            Bpx1 = collision_map_medium_x1;
            Bpx2 = collision_map_medium_x2;
            Bpy1 = collision_map_medium_y1;
            Bpy2 = collision_map_medium_y2;
        } else if (thing_is_collision_map_small(B)) {
            Bpx1 = collision_map_small_x1;
            Bpx2 = collision_map_small_x2;
            Bpy1 = collision_map_small_y1;
            Bpy2 = collision_map_small_y2;
        } else if (thing_is_collision_map_medium(B)) {
            Bpx1 = collision_map_medium_x1;
            Bpx2 = collision_map_medium_x2;
            Bpy1 = collision_map_medium_y1;
            Bpy2 = collision_map_medium_y2;
        } else {
            /*
            * Just use pixel and alpha values.
            */
            tilep tileB = wid_get_tile(Bw);
            if (!tileB) {
                DIE("no tile for thing B %s", thing_logname(B));
                return (false);
            }

            Bpx1 = tileB->px1;
            Bpx2 = tileB->px2;
            Bpy1 = tileB->py1;
            Bpy2 = tileB->py2;
        }
    }

    /*
     * Bit of a hack. We need bonepiles to be passable by ghosts, but easy to 
     * hit by missiles.
     */
    if (thing_is_projectile(A) &&
        (thing_is_monst(B)          ||
         thing_is_trap(B)           ||
         thing_is_mob_spawner(B))) {

        Bpx1 = collision_map_large_x1;
        Bpx2 = collision_map_large_x2;
        Bpy1 = collision_map_large_y1;
        Bpy2 = collision_map_large_y2;
    }

    /*
     * Similar thing for sword things, we want them to hit targets easily.
     */
    if (thing_is_weapon_swing_effect(A) &&
        (thing_is_monst(B)          ||
         thing_is_player(B)         ||
         thing_is_mob_spawner(B))) {

        Bpx1 = collision_map_large_x1;
        Bpx2 = collision_map_large_x2;
        Bpy1 = collision_map_large_y1;
        Bpy2 = collision_map_large_y2;
    }

    int check_only = true;
    fpoint intersect = {0,0};
    fpoint normal_A = {0,0};

    if (thing_can_roll(A) && !thing_can_roll(B)) {
        if (circle_box_collision(level,
                                 A, /* circle */
                                 Ax,
                                 Ay,
                                 B, /* box */
                                 Bx,
                                 By,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (true);
        }
        return (false);
    }

    if (!thing_can_roll(A) && thing_can_roll(B)) {
        if (circle_box_collision(level,
                                 B, /* circle */
                                 Bx,
                                 By,
                                 A, /* box */
                                 Ax,
                                 Ay,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (true);
        }
        return (false);
    }

    if (thing_can_roll(A) && thing_can_roll(B)) {
        if (circle_circle_collision(A, /* circle */
                                    B, /* box */
                                    Ax,
                                    Ay,
                                    &intersect)) {
            return (true);
        }
        return (false);
    }

    /*
     * We really only care about collision radius for large objects like 
     * sawblades. If we use walls here then because of the granularity of
     * movement of one block at a time, the blade detects a collision too
     * far from the wall. The solution would be to use smaller next hop
     * walks but that might cause problems in the client with speed 
     * calculations. Easier just to save radial collisions for monsters and 
     * the like.
     */
    if ((thing_collision_radius(A) > 0.0) || (thing_collision_radius(B) > 0.0)) {

        if (!thing_is_action(A) && !thing_is_action_trigger(A) &&
            !thing_is_action(B) && !thing_is_action_trigger(B)) { 

            if (Aw->first_tile) {
                Ax += ((Aw->first_tile->px1 + Aw->first_tile->px2) / 2.0);
                Ay += ((Aw->first_tile->py1 + Aw->first_tile->py2) / 2.0);
            }

            if (Bw->first_tile) {
                Bx += ((Bw->first_tile->px1 + Bw->first_tile->px2) / 2.0);
                By += ((Bw->first_tile->py1 + Bw->first_tile->py2) / 2.0);
            }

            double dist = DISTANCE(Ax, Ay, Bx, By);
            if (dist < max(thing_collision_radius(A), thing_collision_radius(B))) {
                return (true);
            } else {
                return (false);
            }
        }
    }

    /*
     * Find the start of pixels in the tile.
     */
    double Atlx = Ax + Apx1;
    double Abrx = Ax + Apx2;
    double Atly = Ay + Apy1;
    double Abry = Ay + Apy2;

    double Btlx = Bx + Bpx1;
    double Bbrx = Bx + Bpx2;
    double Btly = By + Bpy1;
    double Bbry = By + Bpy2;

    /*
     * The rectangles don't overlap if one rectangle's minimum in some 
     * dimension is greater than the other's maximum in that dimension.
     */
    if ((Atlx < Bbrx) && 
        (Abrx > Btlx) &&
        (Atly < Bbry) && 
        (Abry > Btly)) {

#if 0
    if ((thing_is_rope(A) &&
         thing_is_rope(B))) {
CON("    A %s %f %f %f %f",thing_logname(A),Atlx,Atly,Abrx,Abry);
CON("      %f %f",Ax,Ay);
CON("      %f %f %f %f",Apx1,Apy1,Apx2,Apy2);
CON("    B %s %f %f %f %f",thing_logname(B),Btlx,Btly,Bbrx,Bbry);
CON("      %f %f",Bx,By);
CON("      %f %f %f %f",Bpx1,Bpy1,Bpx2,Bpy2);
    }
#endif

        return (true);
    }

    return (false);
}

/*
 * handle a single collision between two things
 */
static int thing_handle_collision (levelp level,
                                   Thingp me, Thingp it, 
                                   int32_t x, int32_t y,
                                   int32_t dx, int32_t dy)
{
    if (thing_is_hidden(it) ||
        thing_is_wall_deco(it) ||
        thing_is_ladder_deco(it)) {
        return (true);
    }

    /*
     * Filter out boring things.
     */
    if (thing_is_dungeon_floor(it)          ||
        thing_is_ladder(it)                 ||
        thing_is_weapon_carry_anim(it)      ||
        thing_is_animation(it)) {

        if ((dx == 0) && (dy == 0)) {
            if (thing_is_player(me)) {
                if (thing_is_shop_floor(it)) {
                    /*
                     * Going into a shop.
                     */
                    shop_enter(level, me, it);
                } else if (me->in_shop_owned_by_thing_id) {
                    /*
                     * Still inside the shop?
                     */
                    if (!shop_inside(level, me)) {
                        shop_leave(level, me, it);
                    }
                }
            }
        }

        return (true);
    }

    /*
     * Weapon swing of monster should not hit other monsters.
     */
    Thingp owner_it = thing_owner(level, it);
    Thingp owner_me = thing_owner(level, me);

    if (owner_me) {
        if (thing_is_monst(owner_me) && thing_is_monst(it)) {
            if (!thing_is_shop_floor(owner_me)) {
                /*
                 * Allow shopkeepers to shoot monsters.
                 */
                return (true);
            }
        }
    }

    if (thing_is_dead(it)) {
#if 0
if (debug) {
LOG("  dead");
}
#endif
        return (true);
    }

    /*
     * Need this or shields attack the player.
     */
    if ((owner_it == me) || (owner_me == it)) {
#if 0
if (debug) {
LOG("  owner");
}
#endif
        return (true);
    }

    /*
     * Do we overlap with something?
     */
    if (!things_overlap(level, me, -1.0, -1.0, it)) {
#if 0
CON("  no overlap %s vs %s",thing_logname(me), thing_logname(it));
#endif
        return (true);
    }

#if 0
CON("  overlap %s vs %s",thing_logname(me), thing_logname(it));
#endif

    if (!thing_is_teleport(me)        &&
        !thing_is_ladder(me)          &&
        !thing_is_dungeon_floor(me)) {

        if (thing_is_teleport(it)) {
            thing_reached_teleport(level, me, it);
            return (true);
        }
    }

    /*
     * Lava does not attack lava
     */
    if (thing_is_lava(me) || thing_is_acid(me)) {
        if (thing_is_lava(it) || thing_is_acid(it)) {
            return (true);
        }

        /*
         * Allow weapon blasts to sail over lava
         */
        if (thing_is_projectile(it)) {
            return (true);
        }

        if (thing_is_levitating(it)) {
            return (true);
        }

        if (thing_is_fragile(it)         ||
            thing_is_combustable(it)) {
//CON("  %d",__LINE__);
            thing_possible_hit_add(it, "monst hit thing");
            return (true);
        }
//CON("%s vs %s",thing_logname(me), thing_logname(it));

        if (thing_is_player(it) ||
            thing_is_monst(it)) {
            thing_possible_hit_add(it, "burn attack");
            return (true);
        }

        return (true);
    }

    /*
     * Monster friendly fire?
     */
    if (thing_is_monst(me) && thing_is_monst(it)) {
        if (!thing_is_shop_floor(me)) {
            /*
             * Allow shopkeepers to shoot monsters.
             */
            return (true);
        }
    }

    if (thing_is_player(me)) {
        /*
         * Player collects keys and other items
         */
        if (thing_is_treasure(it)               ||
            thing_is_weapon(it)                 ||
            thing_is_carryable(it)              ||
            thing_is_food(it)) {

            if (thing_is_bomb(it) && thing_is_awake(it)) {
                /*
                 * Don't collect ticking bombs.
                 */
            } else {
                thing_set_is_collected(it, true);

                if (thing_is_bomb(it)) {
                    thing_collect_bomb(level, me, it);
                    return (true);
                }

                if (thing_is_ropepile(it)) {
                    thing_collect_rope(level, me, it);
                    return (true);
                }

                if (thing_is_key(it)) {
                    thing_collect_key(level, me, it);
                    return (true);
                }

                if (thing_is_torch(it)) {
                    thing_collect_torch(level, me, it);
                    return (true);
                }

                thing_collect(level, me, it);
                return (true);
            }
        }

        /*
         * Open doors if you have a key.
         */
        if (thing_is_door(it)) {
            thing_use_key(level, it, x, y);
            return (true);
        }

        /*
         * Player bumped into something.
         */
        if (thing_is_explosion(it) ||
            thing_is_cloud_effect(it)) {
            /*
             * I'm hit!
             */
#if 0
if (debug) {
LOG("add poss me %s hitter %s",thing_logname(me), thing_logname(it));
}
#endif
//CON("  %d",__LINE__);
            thing_possible_hit_add(it, "player hit thing");
            return (true);
        }

        if (thing_is_exit(it)) {
            level->reached_exit = true;
            return (false);
        }

        /*
         * An action trigger is only ever used to start an object off as the 
         * initiator of a collision.
         */
        if (thing_is_action_trigger_on_hero(it)) {
            /*
             * Giant sawblades should only activate on the center tile of 
             * collisions.
             */
            level_trigger_activate(level, it->data.col);
        }
    }

    if (thing_is_monst(me)) {
        /*
         * Monster bumped into something.
         */
        if (thing_is_player(it)                ||
            thing_is_cloud_effect(it)) {
            /*
             * I'm hit!
             */
#if 0
if (debug) {
LOG("add poss me %s hitter %s",thing_logname(me), thing_logname(it));
}
#endif
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
//CON("  %d",__LINE__);
            thing_possible_hit_add(it, "monst hit thing");
            return (true);
        }

        if (thing_is_action_trigger_on_monst(it)) {
            /*
             * Giant sawblades should only activate on the center tile of 
             * collisions.
             */
            if ((dx == 0) && (dy == 0)) {
                level_trigger_activate(level, it->data.col);
            }
        }
    }

    if (thing_is_boulder(me) &&
        ((fabs(me->momentum) > THING_FALL_SPEED_BOULDER_HURTS) || 
         (me->fall_speed > THING_FALL_SPEED_BOULDER_HURTS))) {

        /*
         * Rock bumped into something.
         */
        if (thing_is_player(it)                ||
            thing_is_monst(it)                 ||
            thing_is_bomb(it)                  ||
            thing_is_cloud_effect(it)) {
            /*
             * I'm hit!
             */
#if 0
if (debug) {
LOG("add poss me %s hitter %s",thing_logname(me), thing_logname(it));
}
#endif
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
//CON("  %d",__LINE__);
            thing_possible_hit_add(it, "rock hit thing");
            return (true);
        }
    }

    if (thing_is_smallrock(me) && 
        ((fabs(me->momentum) > THING_PUSH_SPEED_OBJ) || 
         (me->fall_speed >  THING_PUSH_SPEED_OBJ))) {

        /*
         * Rock bumped into something.
         */
        if (thing_is_player(it)                ||
            thing_is_monst(it)                 ||
            thing_is_bomb(it)                  ||
            thing_is_cloud_effect(it)) {
            /*
             * I'm hit!
             */
#if 0
if (debug) {
LOG("add poss me %s hitter %s",thing_logname(me), thing_logname(it));
}
#endif
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
//CON("  %d",__LINE__);
            thing_possible_hit_add(it, "rock hit thing");
            return (true);
        }
    }

    /*
     * If spinning blades or moving wall hit something?
     */
#if 0
    if ((thing_is_wall(me) || thing_is_sawblade(me))) {
#else
    if (thing_is_wall(me)) {
#endif

#if 0
        if (thing_is_sawblade(me)) {
            /*
             * Sawblades are tricky. We want them to be covered in blood and 
             * to do that they need to polymorph and essentially die on the 
             * first hit.
             */
            if (thing_is_warm_blooded(it)) {
                uint32_t id = me->tp_id;
                switch (id) {
                case THING_SAWBLADE1:
                case THING_SAWBLADE2:
                case THING_SAWBLADE3:
                case THING_SAWBLADE4:
                    thing_possible_hit_add_hitter_killed_on_hitting(
                                                    it, "projection hit thing");
                    return (true);

                default:
                    break;
                }
            }
        }
#endif

        /*
         * Allow things to walk unharmed through walls.
         */
        if (thing_is_ethereal(it)) {
            return (true);
        }

        /*
         * Wall is crushing something
         */
        if (thing_is_player(it)                 ||
            thing_is_treasure(it)               ||
            thing_is_food(it)                   ||
            thing_is_door(it)                   ||
            thing_is_cobweb(it)                 ||
            thing_is_mob_spawner(it)            ||
            thing_is_monst(it)) {
            /*
             * I'm hit!
             */
#if 0
if (debug) {
LOG("add poss me %s hitter %s",thing_logname(me), thing_logname(it));
}
#endif
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
//CON("  %d",__LINE__);
            thing_possible_hit_add(it, "object hit thing");
            return (true);
        }

        if (thing_is_action_trigger_on_wall(it)) {
            /*
             * Giant sawblades should only activate on the center tile of 
             * collisions.
             */
            level_trigger_activate(level, it->data.col);
        }

        /*
         * Initially we have a wall sitting on a trigger. The wall is inactive
         * and doesn't do collision tests. The trigger might no be active 
         * either and so we n
         */
        if (thing_is_action_left(it)                ||
            thing_is_action_right(it)               ||
            thing_is_action_up(it)                  ||
            thing_is_action_down(it)) {

            if (level_trigger_is_activated(level, it->data.col)) {
                level_trigger_move_thing(level, thing_tp(it), me);
            }
        }
    }

    /*
     * Explosion hit something?
     */
    if (thing_is_projectile(me)                 || 
        thing_is_explosion(me)) {

        /*
         * Don't let shopkeepers shoot their own wares when defending a shop
         */
        Thingp owner_proj = thing_owner(level, me);
        if (owner_it && (owner_it == owner_proj)) {
            return (true);
        }

        if (owner_proj) {
            /*
             * Don't let monsters shoot their own mob spawners.
             */
            if (thing_is_mob_spawner(it) ||
                thing_is_cobweb(it)) {
                if (thing_is_monst(me)) {
                    return (true);
                }
            }
        }

        if (thing_is_lava(it) || 
            thing_is_water(it) ||
            thing_is_acid(it)) {
            /*
             * No hitting this.
             */
            return (true);
        } else if (thing_is_monst(it)           || 
                   thing_is_fragile(it)         ||
                   thing_is_trap(it)            ||
                   thing_is_combustable(it)     ||
                   thing_is_cobweb(it)          ||
                   thing_is_mob_spawner(it)) {
            /*
             * Can projectiles hit these?
             */
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
            if (owner_me == it) {
                /*
                 * Don't hit your owner.
                 */
            } else {
                /*
                 * Weapon hits monster or generator
                 */
                if (it->hp < thing_stats_get_total_damage(me)) {
                    me->hp -= it->hp;

//CON("  %d",__LINE__);
                    thing_possible_hit_add(it, "projectile hit");
                } else {
//CON("  %d",__LINE__);
                    thing_possible_hit_add_hitter_killed_on_hit_or_miss(
                                                    it, "projectile hit");
                }
                return (true);
            }
        }

        if (thing_is_door(it)                   ||
            thing_is_rock(it)                   ||
            thing_is_wall(it)) {
            thing_possible_hit_add(it, "explosion hit wall");
            return (true);
        }

        if (thing_is_door(it)                   ||
            thing_is_player(it)                 ||
            thing_is_sawblade(it)) {
            if (owner_me == it) {
                /*
                 * Don't hit your owner.
                 */
                return (true);
            } else {
                /*
                 * Weapon hits monster or generator
                 */
//CON("  %d",__LINE__);
                thing_possible_hit_add_hitter_killed_on_hit_or_miss(
                                                it, "projectile hit");
                return (true);
            }
        }
    }

    /*
     * Poison cloud hit something?
     */
    if (thing_is_non_explosive_gas_cloud(me)) {

        if (thing_is_monst(it)                  || 
            thing_is_player(it)                 ||
            thing_is_mob_spawner(it)) {
            /*
             * Weapon hits monster or generator
             */
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
//CON("  %d",__LINE__);
            thing_possible_hit_add_hitter_killed_on_hit_or_miss(
                                            it, "projection hit thing");
            return (true);
        }
    }

    /*
     * Sword swing hits?
     */
    if (thing_is_weapon_swing_effect(me)) {

        if (thing_is_monst(it)                  || 
            thing_is_door(it)                   ||
            thing_is_bomb(it)                   ||
            thing_is_player(it)                 ||
            thing_is_rock(it)                   ||
            thing_is_wall(it)                   ||
            /*
             * Don't hit walls. It's daft.
             */
            thing_is_cobweb(it)                 ||
            thing_is_mob_spawner(it)) {
            /*
             * Weapon hits monster or generator.
             */
//CON("%d %s %s",__LINE__,thing_logname(me), thing_logname(it));
//CON("  %d",__LINE__);
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
int thing_handle_collisions (levelp level, Thingp me)
{
    int32_t dx, dy;

#if 0
if (thing_is_powerup(me)) {
debug = 1;
LOG("  ");
LOG("  ");
LOG("--");
LOG("  ");
LOG("shield coll");
}
#endif
    thing_map_t *map = level_map(level);

    collision_radius = thing_collision_radius(me);
    if (!collision_radius) {
        collision_radius = def_collision_radius;
    }

    for (dx = -collision_radius; dx <= collision_radius; dx++) 
    for (dy = -collision_radius; dy <= collision_radius; dy++) {
        int32_t x = (int32_t)me->x + dx;
        int32_t y = (int32_t)me->y + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        thing_map_cell *cell = &map->cells[x][y];

        uint32_t i;
        for (i = 0; i < cell->count; i++) {
            Thingp it;
            
            it = id_to_thing(cell->id[i]);
#if 0
if (debug) {
LOG("%d %d [%d] %s",x,y,i, thing_logname(it));
}
#endif

            if (me == it) {
                continue;
            }

            if (!thing_handle_collision(level, me, it, x, y, dx, dy)) {
                return (false);
            }
        }
    }

    thing_possible_hit_do(level, me);

    return (true);
}

/*
 * Have we hit anything?
 *
 * No opening of doors in here or other actions. This is just a check.
 */
Thingp thing_hit_solid_obstacle (levelp level,
                                 Thingp t, 
                                 double nx, 
                                 double ny)
{
    Thingp me;
    widp wid_me;

    verify(t);
    wid_me = thing_wid(t);
    verify(wid_me);

    int32_t dx, dy;
    me = wid_get_thing(wid_me);
    thing_map_t *map = level_map(level);

    /*
     * Allow things to walk unharmed through walls.
     */
    if (thing_is_ethereal(t)) {
        return (0);
    }

    collision_radius = thing_collision_radius(me);
    if (!collision_radius) {
        collision_radius = def_collision_radius;
    }

    for (dx = -collision_radius; dx <= collision_radius; dx++) 
    for (dy = -collision_radius; dy <= collision_radius; dy++) {
        int32_t x = (int32_t)nx + dx;
        int32_t y = (int32_t)ny + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        thing_map_cell *cell = &map->cells[x][y];

        uint32_t i;
        for (i = 0; i < cell->count; i++) {
            Thingp it;
            
            it = id_to_thing(cell->id[i]);
            if (it == t) {
                continue;
            }

            verify(it);

            /*
             * Light embers and other junky effects to ignore.
             */
            if (thing_is_hidden(it) ||
                thing_is_wall_deco(it) ||
                thing_is_ladder_deco(it)) {
                continue;
            }

            /*
             * No collisions with the floor!
             */
            if (thing_is_dungeon_floor(it)  ||
                thing_is_action(it)         ||
                thing_is_ladder(it)         ||
                thing_is_animation(it)) {
                continue;
            }

            /*
             * Allowed to pass through small rocks.
             */
            if (!thing_is_smallrock(me)) {
                if (thing_is_smallrock(it)) {
                    continue;
                }
            }

            if (thing_is_spikes(it)) {
                continue;
            }

            /*
             * Bombs
             */
            if (thing_is_carryable(it)) {
                continue;
            }

            /*
             * Allow things to walk unharmed through walls.
             */
            if (thing_is_ethereal(it)) {
                continue;
            }

            /*
             * Allow dead ghosts to walk over each other!
             */
            if (thing_is_monst(it)) {
                if (thing_is_dead(it)) {
                    continue;
                }
            }

            if (thing_is_monst(me)) {
                if (thing_is_monst(it)) {
                    /*
                     * Allow them to walk apart.
                     */
                    if ((me->x < it->x) && (me->dx < 0) && (it->dx > 0)) {
                        continue;
                    }

                    if ((me->x < it->x) && (me->dx < 0) && (it->dx < 0)) {
                        continue;
                    }

                    if ((me->x > it->x) && (me->dx > 0) && (it->dx < 0)) {
                        continue;
                    }

                    if ((me->x > it->x) && (me->dx > 0) && (it->dx > 0)) {
                        continue;
                    }
                }

                if (thing_is_player(it) &&
                    thing_get_weapon_carry_anim_wid(level, me)) {
                    /*
                     * If the monst has a weapon do not walk into the player 
                     * like a bite attack.
                     */
                    double dist = DISTANCE(me->x, me->y, it->x, it->y);
                    if (dist > 0.5) {
                        /*
                         * Get close, enough to hit but not too close.
                         */
                        continue;
                    }

                } else if (thing_is_player(it)                 ||
                           thing_can_walk_through(it)          ||
                           thing_is_carryable(it)              ||
                           thing_is_weapon_swing_effect(it)    ||
                           thing_is_explosion(it)              ||
                           thing_is_non_explosive_gas_cloud(it)||
                           thing_is_projectile(it)             ||
                           thing_is_treasure(it)               ||
                           thing_is_weapon(it)                 ||
                           thing_is_sawblade(it)               ||
                           thing_is_teleport(it)               ||
                           thing_is_rope(it)                   ||
                           thing_is_corpse(it)                 ||
                           thing_is_food(it)) {
                    /*
                     * Allow monsters to walk into these things:
                     */
                    continue;
                }

                if (thing_is_levitating(me)) {
                    if (thing_is_acid(it)    ||
                        thing_is_cobweb(it)  ||
                        thing_is_lava(it)    ||
                        thing_is_water(it)   ||
                        thing_is_acid(it)) {
                        /*
                         * Allow monsters to glide over these things:
                         */
                        continue;
                    }
                }
            }

            if (thing_is_projectile(me)                 ||
                thing_is_cloud_effect(me)               ||
                thing_is_weapon_swing_effect(me)) {
                /*
                 * Allow these to pass through anything.
                 */
                continue;
            }

            if (thing_is_player(me)) {
                /*
                 * Allow to walk through doors so we can open them later.
                 */
                if (thing_is_door(it)) {
                    if (me->keys) {
                        continue;
                    } else {
                        if (!me->message_open_door_need_key) {
                            me->message_open_door_need_key = 1;
                            MSG_SHOUT_AT(INFO, me,
                                         0, 0,
                                         "Collect keys to open doors");
                        }
                    }
                }

                /*
                 * Allow player to collect keys and other junk.
                 */
                if (thing_is_carryable(it)              ||
                    thing_can_walk_through(it)          ||
                    thing_is_food(it)                   ||
                    thing_is_treasure(it)               ||
                    thing_is_weapon(it)                 ||
                    thing_is_exit(it)                   ||
                    thing_is_rope(it)                   ||
                    thing_is_teleport(it)               ||
                    thing_is_lava(it)                   ||
                    thing_is_water(it)                  ||
                    thing_is_acid(it)                   ||
                    thing_is_trap(it)                   ||
                    thing_is_monst(it)                  ||
                    /*
                     * Walk through friendly fire.
                     */
                    thing_is_projectile(it)             ||
                    thing_is_weapon_swing_effect(it)    ||
                    thing_is_weapon_carry_anim(it)      ||
                    thing_is_explosion(it)              ||
                    thing_is_sawblade(it)               ||
                    thing_is_cloud_effect(it)) {
                    continue;
                }

                /*
                 * Allow player to walk through other player. Else thay
                 * can spawn on top of each other and get stuck.
                 */
                if (thing_is_player(it)) {
                    continue;
                }
            }

            if (thing_is_wall(me)     || 
                thing_is_rope(me)     ||
                thing_is_sawblade(me)) {
                /*
                 * Allow moving walls to crush most things except walls and 
                 * doors.
                 */
                if (!thing_is_wall(it) && 
                    !thing_is_rock(it) && 
                    !thing_is_door(it)) {
                    continue;
                }
            }

            if (!things_overlap(level, me, nx, ny, it)) {
                continue;
            }

            /*
             * Push obstacles?
             */
            if (thing_is_obstacle(it)) {
                double dist_now = DISTANCE(t->x, t->y, it->x, it->y);
                double dist_then = DISTANCE(nx, ny, it->x, it->y);

                /*
                 * If inside the obstacle, no pushing!
                 */
                if (dist_then > dist_now) {
                    continue;
                } else {
                    /*
                     * If moving towards it; crimes against physics.
                     */
                    it->momentum += t->momentum / 2;
                    t->momentum = 0;
                }
            }

            /*
             * You can walk away from a boulder, but not closer...
             */
            if (thing_is_boulder(it)) {
                double dist_now = DISTANCE(t->x, t->y, it->x, it->y);
                double dist_then = DISTANCE(nx, ny, it->x, it->y);

                /*
                 * Else be sticky
                 */
                if (dist_then > dist_now) {
                    continue;
                } else {
                    return (it);
                }
            }

            /*
             * You can walk closer to a cobweb, but not back out...
             */
            if (thing_is_cobweb(it)) {
                double dist_now = DISTANCE(t->x, t->y, it->x, it->y);
                double dist_then = DISTANCE(nx, ny, it->x, it->y);

                /*
                 * No spiders stuck in their own web
                 */
                if ((tp_to_id(thing_tp(t)) == THING_SPIDER1) ||
                    (tp_to_id(thing_tp(t)) == THING_SPIDER2)) {
                    continue;
                }

                /*
                 * Allow floating things to glide over
                 */
                if (thing_is_levitating(t)) {
                    continue;
                }

                /*
                 * Else be sticky
                 */
                if (dist_then < dist_now) {
                    continue;
                } else {
                    return (it);
                }
            }

            return (it);
        }
    }

    return (0);
}

/*
 * Have we hit anything?
 *
 * No opening of doors in here or other actions. This is just a check.
 */
Thingp thing_hit_fall_obstacle (levelp level,
                                Thingp t, 
                                double nx, 
                                double ny)
{
    Thingp candidate = 0;
    Thingp me;
    widp wid_me;

    verify(t);
    wid_me = thing_wid(t);
    verify(wid_me);

    int32_t dx, dy;
    me = wid_get_thing(wid_me);
    thing_map_t *map = level_map(level);

    collision_radius = thing_collision_radius(me);
    if (!collision_radius) {
        collision_radius = def_collision_radius;
    }

    for (dx = -collision_radius; dx <= collision_radius; dx++) 
    for (dy = -collision_radius; dy <= collision_radius; dy++) {
        int32_t x = (int32_t)nx + dx;
        int32_t y = (int32_t)ny + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        thing_map_cell *cell = &map->cells[x][y];

        uint32_t i;
        for (i = 0; i < cell->count; i++) {
            Thingp it;
            
            it = id_to_thing(cell->id[i]);
            if (it == t) {
                continue;
            }

            verify(it);

            /*
             * Light embers and other junky effects to ignore.
             */
            if (thing_is_hidden(it) ||
                thing_is_wall_deco(it) ||
                thing_is_ladder_deco(it)) {
                continue;
            }

            if (thing_is_spikes(it)) {
                continue;
            }

            if (thing_is_dungeon_floor(it)) {
                continue;
            }

            if (thing_is_player(me)) {
                /*
                 * Allow players to land on small rocks and monsters.
                 */
                if (!thing_is_wall(it) && 
                    !thing_is_rock(it) && 
                    !thing_is_monst(it) && 
                    !thing_is_smallrock(it) && 
                    !thing_is_rope(it) && 
                    !thing_is_ladder(it) && 
                    !thing_is_obstacle(it) && 
                    !thing_is_cobweb(it) && 
                    !thing_is_door(it)) {
                    continue;
                }

                if (t->fall_speed < THING_FALL_SPEED_HIT_MONST) {
                    if (thing_is_monst(it)) {
                        continue;
                    }
                }
            } else if (thing_is_monst(me) ||
                       thing_is_rope(me)) {

                /*
                 * Allow monsters to land on small rocks.
                 */
                if (!thing_is_wall(it) && 
                    !thing_is_rock(it) && 
                    !thing_is_smallrock(it) && 
                    !thing_is_obstacle(it) && 
                    !thing_is_rope(it) && 
                    !thing_is_ladder(it) && 
                    !thing_is_cobweb(it) && 
                    !thing_is_spikes(it) && 
                    !thing_is_door(it)) {
                    continue;
                }
            } else if (thing_is_obstacle(me)) {
                if (!thing_is_wall(it) && 
                    !thing_is_rock(it) && 
                    !thing_is_obstacle(it) && 
                    !thing_is_door(it)) {
                    continue;
                }
            } else if (thing_is_smallrock(me)) {
                if (thing_is_smallrock(it)) {
                    if (me->y > it->y) {
                        continue;
                    }
                    if (me->y == it->y) {
                        if ((int)(uintptr_t) me < (int)(uintptr_t) it) {
                            continue;
                        }
                    }
                }

                if (!thing_is_wall(it) && 
                    !thing_is_rock(it) && 
                    !thing_is_smallrock(it) && 
                    !thing_is_door(it)) {
                    continue;
                }
            } else {
                /*
                 * Larger obstacles are only stopped by large obstacles.
                 */
                if (!thing_is_wall(it) && 
                    !thing_is_rock(it) && 
                    !thing_is_boulder(it) && 
                    !thing_is_door(it)) {
                    continue;
                }
            }

            if (!things_overlap(level, me, nx, ny, it)) {
                continue;
            }

            /*
             * You can walk closer to a cobweb, but not back out...
             */
            if (thing_is_cobweb(it)) {
                double dist_now = DISTANCE(t->x, t->y, it->x, it->y);
                double dist_then = DISTANCE(nx, ny, it->x, it->y);

                /*
                 * No spiders stuck in their own web
                 */
                if ((tp_to_id(thing_tp(t)) == THING_SPIDER1) ||
                    (tp_to_id(thing_tp(t)) == THING_SPIDER2)) {
                    continue;
                }

                /*
                 * Else be sticky
                 */
                if (dist_then < dist_now) {
                    continue;
                } else {
                    return (it);
                }
            }

            /*
             * To allow you to land on dead monsters, but prefer live ones.
             */
            if (thing_is_dead(it)) {
                candidate = it;
                continue;
            }

            return (it);
        }
    }

    return (candidate);
}

/*
 * Have we hit anything?
 *
 * Is there anything other than floor here
 */
Thingp thing_hit_any_obstacle (levelp level, 
                               Thingp t, 
                               double nx, 
                               double ny)
{
    Thingp me;
    widp wid_me;

    verify(t);
    wid_me = thing_wid(t);
    verify(wid_me);

    int32_t dx, dy;

    me = wid_get_thing(wid_me);

    thing_map_t *map = level_map(level);

    collision_radius = thing_collision_radius(me);
    if (!collision_radius) {
        collision_radius = def_collision_radius;
    }

    for (dx = -collision_radius; dx <= collision_radius; dx++) 
    for (dy = -collision_radius; dy <= collision_radius; dy++) {
        int32_t x = (int32_t)me->x + dx;
        int32_t y = (int32_t)me->y + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        thing_map_cell *cell = &map->cells[x][y];

        uint32_t i;
        for (i = 0; i < cell->count; i++) {
            Thingp it;
            
            it = id_to_thing(cell->id[i]);
            if (me == it) {
                continue;
            }

            /*
             * Light embers and other junky effects to ignore.
             */
            if (thing_is_hidden(it) ||
                thing_is_wall_deco(it) ||
                thing_is_ladder_deco(it)) {
                continue;
            }

            /*
             * No collisions with the floor!
             */
            if (thing_is_dungeon_floor(it) ||
                thing_is_ladder(it)) {
                continue;
            }

            /*
             * Allow dead ghosts to walk over each other!
             */
            if (thing_is_dead(it)) {
                continue;
            }

            if (!things_overlap(level, me, nx, ny, it)) {
                continue;
            }

            /*
             * You can walk closer to a cobweb, but not back out...
             */
            if (thing_is_cobweb(it)) {
                continue;
            }

            return (it);
        }
    }

    return (0);
}

/*
 * Have we hit anything?
 *
 * Is there anything other than floor here
 */
Thingp thing_overlaps (levelp level, 
                       Thingp t, 
                       double nx, 
                       double ny,
                       thing_is_fn fn)
{
    Thingp me;
    widp wid_me;

    verify(t);
    wid_me = thing_wid(t);
    verify(wid_me);

    int32_t dx, dy;

    me = wid_get_thing(wid_me);

    thing_map_t *map = level_map(level);

    collision_radius = thing_collision_radius(me);
    if (!collision_radius) {
        collision_radius = def_collision_radius;
    }

    for (dx = -collision_radius; dx <= collision_radius; dx++) 
    for (dy = -collision_radius; dy <= collision_radius; dy++) {
        int32_t x = (int32_t)me->x + dx;
        int32_t y = (int32_t)me->y + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        thing_map_cell *cell = &map->cells[x][y];

        uint32_t i;
        for (i = 0; i < cell->count; i++) {
            Thingp it;
            
            it = id_to_thing(cell->id[i]);
            if (me == it) {
                continue;
            }

            if (thing_is_hidden(it) ||
                thing_is_wall_deco(it) ||
                thing_is_ladder_deco(it)) {
                continue;
            }

            if (!things_overlap(level, me, nx, ny, it)) {
                continue;
            }

            if (fn(it)) {
                return (it);
            }

            continue;
        }
    }

    return (0);
}
#endif
