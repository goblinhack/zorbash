//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_tile.h"
#include "my_main.h"
#include "my_game.h"
#include "my_thing.h"

#undef DEBUG_COLLISION

class ThingColl {
public:
    ThingColl(void) {}
    ThingColl(Thingp      target,
              std::string reason,
              uint16_t    priority) :
        target(target),
        reason(reason),
        priority(priority)
    { }

    Thingp      target {nullptr};
    std::string reason;
    uint16_t    priority {0};
};

static std::vector<class ThingColl> thing_colls;
static const float thing_collision_tiles = 1;

#if 0
static bool
things_tile_overlap (Thingp A, Thingp B)
{
    auto A_tile = tile_index_to_tile(A->tile_curr);
    if (!A_tile) {
        return false;
    }
    auto B_tile = tile_index_to_tile(B->tile_curr);
    if (!B_tile) {
        return false;
    }

    float A_width  = (A->last_blit_br.x - A->last_blit_tl.x);
    float A_height = (A->last_blit_br.y - A->last_blit_tl.y);
    float B_width  = (B->last_blit_br.x - B->last_blit_tl.x);
    float B_height = (B->last_blit_br.y - B->last_blit_tl.y);

    float A_dw = A_width  / (float)A_tile->pix_width;
    float A_dh = A_height / (float)A_tile->pix_height;
    float B_dw = B_width  / (float)B_tile->pix_width;
    float B_dh = B_height / (float)B_tile->pix_height;

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
            float Ax = A->last_blit_tl.x + (((float)x) * A_dw);
            float Ay = A->last_blit_tl.y + (((float)y) * A_dh);
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
                return true;
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
            float Ax = A->last_blit_tl.x + (((float)x) * A_dw);
            float Ay = A->last_blit_tl.y + (((float)y) * A_dh);
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
    return false;
}

static bool
things_tile_overlap (Thingp A, fpoint A_at, Thingp B)
{
    auto A_tile = tile_index_to_tile(A->tile_curr);
    if (!A_tile) {
        return false;
    }
    auto B_tile = tile_index_to_tile(B->tile_curr);
    if (!B_tile) {
        return false;
    }

    float A_width  = (A->last_blit_br.x - A->last_blit_tl.x);
    float A_height = (A->last_blit_br.y - A->last_blit_tl.y);
    float B_width  = (B->last_blit_br.x - B->last_blit_tl.x);
    float B_height = (B->last_blit_br.y - B->last_blit_tl.y);

    float A_dw = A_width  / (float)A_tile->pix_width;
    float A_dh = A_height / (float)A_tile->pix_height;
    float B_dw = B_width  / (float)B_tile->pix_width;
    float B_dh = B_height / (float)B_tile->pix_height;

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

            auto m = A->get_interpolated_mid_at();
            float Adx = A_at.x - m.x;
            float Ady = A_at.y - m.y;
            Adx *= game->config.tile_gl_width;
            Ady *= game->config.tile_gl_height;

            float Ax = A->last_blit_tl.x + Adx + (((float)x) * A_dw);
            float Ay = A->last_blit_tl.y + Ady + (((float)y) * A_dh);
            Ax -= B->last_blit_tl.x;
            Ay -= B->last_blit_tl.y;
            Ax /= B_dw;
            Ay /= B_dh;

            int dx = (int)Ax;
            int dy = (int)Ay;

            if ((dx <=- 1) || (dx >= (int)B_tile->pix_width - 2)) {
                continue;
            }

            if ((dy <= 1) || (dy >= (int)B_tile->pix_height - 2)) {
                continue;
            }

            if (get(B_tile->pix, dx, dy)) {
                return true;
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
            float Ax = A->last_blit_tl.x + (((float)x) * A_dw);
            float Ay = A->last_blit_tl.y + (((float)y) * A_dh);
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
    return false;
}
#endif

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

    float radius = fmin((C1.x - C0.x) / 2.0, (C2.y - C0.y) / 2.0);

    //
    // Corner collisions, normal is at 45 degrees. Unless there is a wall.
    //
    if (distance(C_at, B0) < radius) {
        if (!level->is_wall(B->interpolated_mid_at.x - 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B0.x;
            normal->y = C_at.y - B0.y;
            return true;
        }
    }

    if (distance(C_at, B1) < radius) {
        if (!level->is_wall(B->interpolated_mid_at.x + 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B1.x;
            normal->y = C_at.y - B1.y;
            return true;
        }
    }

    if (distance(C_at, B2) < radius) {
        if (!level->is_wall(B->interpolated_mid_at.x + 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B2.x;
            normal->y = C_at.y - B2.y;
            return true;
        }
    }

    if (distance(C_at, B3) < radius) {
        if (!level->is_wall(B->interpolated_mid_at.x - 1,
                                       B->interpolated_mid_at.y)) {
            normal->x = C_at.x - B3.x;
            normal->y = C_at.y - B3.y;
            return true;
        }
    }

    float dist;
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

    return false;

collided:

    if (check_only) {
        return true;
    }

    fpoint delta;

    if (get_line_intersection(C_at, B_at, B0, B1, intersect)) {
        delta.x = B0.x - B1.x;
        delta.y = B0.y - B1.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return true;
    }

    if (get_line_intersection(C_at, B_at, B1, B2, intersect)) {
        delta.x = B1.x - B2.x;
        delta.y = B1.y - B2.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return true;
    }

    if (get_line_intersection(C_at, B_at, B2, B3, intersect)) {
        delta.x = B2.x - B3.x;
        delta.y = B2.y - B3.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return true;
    }

    if (get_line_intersection(C_at, B_at, B3, B0, intersect)) {
        delta.x = B3.x - B0.x;
        delta.y = B3.y - B0.y;
        normal->x = -delta.y;
        normal->y = delta.x;
        return true;
    }

    //
    // Sphere may be inside box.
    //
    return false;
}
#endif

//
// If two circles collide, the resultant direction is along the normal between
// the two center of masses of the circles.
//
static int circle_circle_collision (Thingp A,
                                    Thingp B,
                                    fpoint *intersect)
{
    fpoint A_at = A->get_interpolated_mid_at();
    fpoint B_at = B->get_interpolated_mid_at();

    //fpoint A0, A1, A2, A3;
    //A->to_coords(&A0, &A1, &A2, &A3);
    //float A_radius = fmin((A1.x - A0.x) / 2.0, (A2.y - A0.y) / 2.0);
    float A_radius = A->tp()->collision_radius();
    float B_radius = B->tp()->collision_radius();

    //fpoint B0, B1, B2, B3;
    //B->to_coords(&B0, &B1, &B2, &B3);
    //float B_radius = fmin((B1.x - B0.x) / 2.0, (B2.y - B0.y) / 2.0);

    fpoint n = B_at - A_at;
    float touching_dist = A_radius + B_radius;
    float dist_squared = n.x*n.x + n.y*n.y;

    float diff = dist_squared - touching_dist * touching_dist;
    if (diff > 0.0) {
        //
        // Circles are not touching
        //
        return false;
    }

    diff = sqrt(fabs(diff));
    diff /= 2.0;

    n = unit(n);
    n *= (A_radius - diff);
    n += A_at;

    if (intersect) {
        *intersect = n;
    }

    return true;
}

static int circle_circle_collision (Thingp A,
                                    fpoint A_at,
                                    Thingp B,
                                    fpoint B_at,
                                    fpoint *intersect)
{
    //fpoint A0, A1, A2, A3;
    //A->to_coords(&A0, &A1, &A2, &A3);
    //float A_radius = fmin((A1.x - A0.x) / 2.0, (A2.y - A0.y) / 2.0);
    float A_radius = A->tp()->collision_radius();
    float B_radius = B->tp()->collision_radius();

    //fpoint B0, B1, B2, B3;
    //B->to_coords(&B0, &B1, &B2, &B3);
    //float B_radius = fmin((B1.x - B0.x) / 2.0, (B2.y - B0.y) / 2.0);

    fpoint n = B_at - A_at;
    float touching_dist = A_radius + B_radius;
    float dist_squared = n.x*n.x + n.y*n.y;

    float diff = dist_squared - touching_dist * touching_dist;
    if (diff > 0.0) {
        //
        // Circles are not touching
        //
        return false;
    }

    diff = sqrt(fabs(diff));
    diff /= 2.0;

    n = unit(n);
    n *= (A_radius - diff);
    n += A_at;

    if (intersect) {
        *intersect = n;
    }

    return true;
}

static int circle_circle_collision_attack (Thingp A,
                                           fpoint A_at,
                                           Thingp B,
                                           fpoint B_at,
                                           fpoint *intersect)
{
    //fpoint A0, A1, A2, A3;
    //A->to_coords(&A0, &A1, &A2, &A3);
    //float A_radius = fmin((A1.x - A0.x) / 2.0, (A2.y - A0.y) / 2.0);
    float A_radius = A->tp()->collision_radius();
    float B_radius = B->tp()->collision_attack_radius();
    if (!B_radius) {
        B_radius = B->tp()->collision_radius();
    }

    //fpoint B0, B1, B2, B3;
    //B->to_coords(&B0, &B1, &B2, &B3);
    //float B_radius = fmin((B1.x - B0.x) / 2.0, (B2.y - B0.y) / 2.0);

    fpoint n = B_at - A_at;
    float touching_dist = A_radius + B_radius;
    float dist_squared = n.x*n.x + n.y*n.y;

    float diff = dist_squared - touching_dist * touching_dist;
    if (diff > 0.0) {
        //
        // Circles are not touching
        //
        return false;
    }

    diff = sqrt(fabs(diff));
    diff /= 2.0;

    n = unit(n);
    n *= (A_radius - diff);
    n += A_at;

    if (intersect) {
        *intersect = n;
    }

    return true;
}

//
// Add a thing to the list of things that could be hit on this attack.
//
static void
thing_add_ai_possible_hit (Thingp target, std::string reason)
{
    thing_colls.push_back(
      ThingColl(target,
                reason,
                target->tp()->collision_hit_priority()));
}

//
// Reset the list of things we can possibly hit.
//
static void thing_possible_init (void)
{
    thing_colls.resize(0);
}

//
// Find the thing with the highest priority to hit.
//
bool Thing::collision_find_best_target (bool *target_attacked,
                                        bool *target_overlaps)
{_
    bool ret = false;
    auto me = this;
    ThingColl *best = nullptr;

    log("Collided with or can attack or eat something, find the best");
_
    *target_attacked = false;
    *target_overlaps = false;

    for (auto& cand : thing_colls) {
        //
        // Don't be silly and hit yourself.
        //
        if (cand.target == me) {
            continue;
        }

        log("Candidate: %s", cand.target->to_string().c_str());

        //
        // Skip things that aren't really hitable.
        //
        if (cand.target->tp()->gfx_weapon_carry_anim()) {
            if (is_loggable_for_unimportant_stuff()) {
                log("Ignore %s skip, not hittable",
                    cand.target->to_string().c_str());
            }
            continue;
        }

        if (!best) {
            best = &cand;
            continue;
        }

        if (cand.priority > best->priority) {
            //
            // If this target is higher prio, prefer it.
            //
            best = &cand;
            if (is_loggable_for_unimportant_stuff()) {
                log("Add %s", cand.target->to_string().c_str());
            }
        } else if (cand.priority == best->priority) {
            //
            // If this target is closer, prefer it.
            //
            auto me_pos = mid_at;
            auto best_pos = best->target->mid_at;

            float dist_best = DISTANCE(me_pos.x,
                                       me_pos.y,
                                       best_pos.x,
                                       best_pos.y);
            float dist_cand = DISTANCE(me_pos.x,
                                       me_pos.y,
                                       best_pos.x,
                                       best_pos.y);

            if (dist_cand < dist_best) {
                best = &cand;
                if (is_loggable_for_unimportant_stuff()) {
                    log("Add %s", cand.target->to_string().c_str());
                }
            }
        } else {
            if (is_loggable_for_unimportant_stuff()) {
                log("Ignore %s", cand.target->to_string().c_str());
            }
        }
    }

    if (best) {
        *target_overlaps = true;

        auto it = best->target;

        if (is_loggable_for_unimportant_stuff()) {
            log("Best candidate %s", it->to_string().c_str());
        }

        if (attack(it)) {
            *target_attacked = true;
            ret = true;
        } else {
            if (is_loggable_for_unimportant_stuff()) {
                log("Collision: cannot hit %s", it->to_string().c_str());
            }
        }
    }

    thing_possible_init();
    return (ret);
}

bool things_overlap (const Thingp A, const Thingp B)
{
#if 0
    fpoint A_at, B_at;

    A_at = A->interpolated_mid_at;
    B_at = B->interpolated_mid_at;

    int check_only = true;
    fpoint intersect = {0,0};
    fpoint normal_A = {0,0};

    if (tp_collision_circle(A->tp) &&
        !tp_collision_circle(B->tp)) {
        if (circle_box_collision(A, // circle
                                 A_at,
                                 B, // box
                                 B_at,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (things_tile_overlap(A, B));
        }
        return false;
    }

    if (!tp_collision_circle(A->tp) &&
         tp_collision_circle(B->tp)) {
        if (circle_box_collision(B, // circle
                                 B_at,
                                 A, // box
                                 A_at,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (things_tile_overlap(A, B));
        }
        return false;
    }

#endif
    if (A->tp()->collision_circle() &&
        B->tp()->collision_circle()) {
        if (circle_circle_collision(A, // circle
                                    B, // box
                                    nullptr)) {
            LOG("%s %s (test1) overlaps", A->to_string().c_str(), B->to_string().c_str());
            return true;
        }
        LOG("%s %s (test2) no overlaps", A->to_string().c_str(), B->to_string().c_str());
        return false;
    }

#if 0
    return (things_tile_overlap(A, B));
#endif
    LOG("%s %s (test3) no overlaps", A->to_string().c_str(), B->to_string().c_str());
    return false;
}

bool things_overlap (const Thingp A, fpoint A_at, const Thingp B)
{
#if 0
    fpoint A_at, B_at;

    A_at = A->interpolated_mid_at;
    B_at = B->interpolated_mid_at;

    int check_only = true;
    fpoint intersect = {0,0};
    fpoint normal_A = {0,0};

    if (tp_collision_circle(A->tp) &&
        !tp_collision_circle(B->tp)) {
        if (circle_box_collision(A, // circle
                                 A_at,
                                 B, // box
                                 B_at,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (things_tile_overlap(A, B));
        }
        return false;
    

    if (!tp_collision_circle(A->tp) &&
         tp_collision_circle(B->tp)) {
        if (circle_box_collision(B, // circle
                                 B_at,
                                 A, // box
                                 A_at,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            return (things_tile_overlap(A, B));
        }
        return false;
    }

#endif

    //
    // FYI This path is used for monst attacks
    //
    if (A->tp()->collision_circle() &&
        B->tp()->collision_circle()) {
        if (circle_circle_collision(A, // circle
                                    A_at,
                                    B, // box
                                    B->mid_at,
                                    nullptr)) {
            LOG("%s %s (test4) overlaps", A->to_string().c_str(), B->to_string().c_str());
            return true;
        }

        //
        // This is to allow hits when a thing is in transit
        //
        if (circle_circle_collision(A, // circle
                                    A_at,
                                    B, // box
                                    B->get_interpolated_mid_at(),
                                    nullptr)) {
            LOG("%s %s (test5) overlaps", A->to_string().c_str(), B->to_string().c_str());
            return true;
        }
    }

#if 0
    return (things_tile_overlap(A, A_at, B));
#endif
    LOG("%s %s (test6) A %f %f B %f %f B interp %f %f", A->to_string().c_str(), B->to_string().c_str(),
        A_at.x, A_at.y,
        B->mid_at.x, B->mid_at.y,
        B->get_interpolated_mid_at().x, B->get_interpolated_mid_at().y);
    return false;
}

bool things_overlap_attack (const Thingp A, fpoint A_at, const Thingp B)
{
    if (A->tp()->collision_circle() &&
        B->tp()->collision_circle()) {
        if (circle_circle_collision_attack(A, // circle
                                           A_at,
                                           B, // box
                                           B->mid_at,
                                           nullptr)) {
            LOG("%s %s (test7) overlaps", A->to_string().c_str(), B->to_string().c_str());
            return true;
        }
        if (circle_circle_collision_attack(A, // circle
                                           A_at,
                                           B, // box
                                           B->get_interpolated_mid_at(),
                                           nullptr)) {
            LOG("%s %s (test8) overlaps", A->to_string().c_str(), B->to_string().c_str());
            return true;
        }
        if (circle_circle_collision_attack(A, // circle
                                           A->get_interpolated_mid_at(),
                                           B, // box
                                           B->get_interpolated_mid_at(),
                                           nullptr)) {
            LOG("%s %s (test9) overlaps", A->to_string().c_str(), B->to_string().c_str());
            return true;
        }
    }

    LOG("%s %s (test10) no overlaps", A->to_string().c_str(), B->to_string().c_str());
    return false;
}

//
// handle a single collision between two things
//
// false aborts the walk
//
bool Thing::collision_add_candidates (Thingp it, fpoint future_pos,
                                      int x, int y, int dx, int dy)
{_
    auto me = this;

    Thingp owner_it = it->get_immediate_owner();
    Thingp owner_me = me->get_immediate_owner();

    log("Collision candidate? %s", it->to_string().c_str());
_
    //
    // Need this or shields attack the player.
    //
    if ((owner_it == me) || (owner_me == it)) {
        //
        // If on fire, allow fire to burn its owner - you!
        //
        if (!is_fire()) {
            log("Yes; allow fire to burn owner");
            return true;
        }
    }

    //
    // Sword use hits?
    //
    if (is_player() && it->is_item() && !it->is_auto_collect_item()) {
        log("No; allow items to be collected manually");
        return false;
    } else if (!it->is_dead && possible_to_attack(it)) {
        if (things_overlap_attack(me, future_pos, it)) {
            log("Yes; candidate to attack");
            thing_add_ai_possible_hit(it, "battle");
        } else {
            log("No; cannot attack %s, no overlap", it->to_string().c_str());
        }
    } else if (can_eat(it)) {
        if (get_where_i_dropped_an_item_last() == make_point(it->mid_at)) {
            log("No; can eat but was seen previously");
            return true;
        }

        if (things_overlap(me, me->mid_at, it)) {
            log("Yes; overlaps and can eat");
            thing_add_ai_possible_hit(it, "eat");
        }
    } else if (it->is_dead) {
        log("No; ignore corpse");
    } else {
        log("No; ignore");
    }

    return true;
}

bool Thing::collision_obstacle (fpoint p)
{
    //
    // Avoid threats and treat them as obstacles
    //
    for (const auto& it : get(level->all_thing_ptrs_at, p.x, p.y)) {
        if (!it) {
            continue;
        }

        if (it->is_the_grid) { continue; }

        //
        // "true" on collision
        //
        if (collision_obstacle(it)) {
            return true;
        }
    }

    return false;
}

bool Thing::collision_obstacle (point p)
{
    //
    // Avoid threats and treat them as obstacles
    //
    FOR_ALL_COLLISION_THINGS(level, it, p.x, p.y) {
        //
        // "true" on collision
        //
        if (collision_obstacle(it)) {
            return true;
        }
    }
    FOR_ALL_THINGS_END();

    return false;
}

bool Thing::ai_obstacle (fpoint p)
{
    //
    // Avoid threats and treat them as obstacles
    //
    FOR_ALL_COLLISION_THINGS(level, it, p.x, p.y) {
        //
        // "true" on collision
        //
        if (ai_obstacle(it)) {
            return true;
        }
    }
    FOR_ALL_THINGS_END();

    return false;
}

//
// "true" on collision
//
bool Thing::collision_check_only (Thingp it, fpoint A_at, int x, int y)
{
    auto me = this;
    auto it_tp = it->tp();
    auto me_tp = me->tp();

    //
    // Do not include hidden as we use the sword being carried here
    // and when swinging, it is hidden
    //
    if (is_falling || is_jumping || is_changing_level) {
        log("Ignore collisions");
        return false;
    }

    if (g_opt_debug2) {
        log("Collision check only? @%f,%f with %s",
            A_at.x, A_at.y, it->to_string().c_str());
    }
_

    if (it->is_monst()) {
        if (is_torch()) {
            //
            // Torches always hit monsters
            //
        } else {
            //
            // Allow walking over the dead
            //
            if (can_eat(it)) {
                if (things_overlap(me, me->mid_at, it)) {
                    log("Yes; overlaps and can eat");
                    return true;
                }
            }

            if (it->is_dead) {
                log("No; ignore corpse");
                return false;
            }
        }
    }

    Thingp owner_it = it->get_immediate_owner();
    Thingp owner_me = me->get_immediate_owner();

    //
    // Need this or shields attack the player.
    //
    if ((owner_it == me) || (owner_me == it)) {
        log("No; collision with myself");
        return false;
    }

    //
    // Sword use hits?
    //
    if (me_tp->gfx_attack_anim()) {
        if (it_tp->is_monst()) {
            //
            // Weapon hits monster or generator.
            //
            if (things_overlap_attack(me, A_at, it)) {
                log("Yes; overlaps and can attack");
                return true;
            }
        }
    } else if (it->is_door() && !it->is_open) {
        if (things_overlap(me, A_at, it)) {
            if (!it->is_dead) {
                log("Yes; overlaps and can open");
                return !open_door(it);
            }
        }
    } else if (it->is_ethereal() && !is_player()) {
        //
        // Ignore is_ethereal to make it easier to attack ghosts
        //
        log("No; can pass through");
    } else if (it->is_exit()) {
        if (things_overlap(me, A_at, it)) {
            log("No; overlaps but can exit");
            // open_exit(it);
            return false;
        }
    } else if (is_player() && it->is_item() && !it->is_auto_collect_item()) {
        log("No; allow manual collect instead");
        return false;
    } else if (possible_to_attack(it)) {
        if (things_overlap(me, A_at, it)) {
            log("Yes; overlaps and can attack");
            return true;
        } else {
            log("No; can attack but no overlap");
        }
    } else if (can_eat(it)) {
        if (get_where_i_failed_to_collect_last() == make_point(it->mid_at)) {
            log("No; tried to collect previously");
	    set_where_i_failed_to_collect_last(point(-1, -1));
            return false;
        }

        if (get_where_i_dropped_an_item_last() == make_point(it->mid_at)) {
            log("No; can eat but was seen previously");
            return false;
        }

        if (things_overlap(me, me->mid_at, it)) {
            log("Yes; can eat and overlaps");
            return true;
        } else {
            log("Yes; can eat but no overlap");
        }
    } else {
        if (things_overlap(me, A_at, it)) {
            //
            // "true" on collision
            //
            if (collision_obstacle(it)) {
                log("Yes; overlaps and is an obstacle");
                return true;
            }
        }
    }

    return false;
}

bool Thing::collision_check_and_handle (fpoint future_pos,
                                        bool *target_attacked,
                                        bool *target_overlaps,
                                        float radius)
{_
    if (is_loggable_for_unimportant_stuff()) {
        log("Collision handle");
    }
_
    //
    // Do not include hidden as we use the sword being carried here
    // and when swinging, it is hidden
    //
    if (is_falling || is_jumping || is_changing_level) {
        log("Ignore collisions");
        return false;
    }

    int minx = future_pos.x - radius;
    while (minx < 0) {
        minx++;
    }

    int miny = future_pos.y - radius;
    while (miny < 0) {
        miny++;
    }

    int maxx = future_pos.x + radius;
    while (maxx >= MAP_WIDTH) {
        maxx--;
    }

    int maxy = future_pos.y + radius;
    while (maxy >= MAP_HEIGHT) {
        maxy--;
    }

    for (int16_t x = minx; x <= maxx; x++) {
        auto dx = x - future_pos.x;
        for (int16_t y = miny; y <= maxy; y++) {
            auto dy = y - future_pos.y;
            FOR_ALL_COLLISION_THINGS(level, it, x, y) {
                if (this == it) {
                    continue;
                }

                if (it->is_hidden ||
                    it->is_falling ||
                    it->is_jumping ||
                    it->is_changing_level) {
                    log("Ignore as hidden/falling/jumping");
                    continue;
                }

                //
                // false is used to abort the walk
                //
                if (!collision_add_candidates(it, future_pos, x, y, dx, dy)) {
                    log("Collision check, abort walk");
                    return false;
                }
            } FOR_ALL_THINGS_END()
        }
    }

    return (collision_find_best_target(target_attacked, target_overlaps));
}

//
// Have we hit anything? True on having done something at this (future?)
// position.
//
bool Thing::collision_check_and_handle_nearby (fpoint future_pos,
                                               bool *target_attacked,
                                               bool *target_overlaps)
{
    return (collision_check_and_handle(future_pos,
                                       target_attacked,
                                       target_overlaps,
                                       thing_collision_tiles));
}

bool Thing::collision_check_and_handle_at (fpoint future_pos,
                                           bool *target_attacked,
                                           bool *target_overlaps)
{
    return (collision_check_and_handle(future_pos,
                                       target_attacked,
                                       target_overlaps,
                                       0.0));
}

bool Thing::collision_check_and_handle_at (bool *target_attacked,
                                           bool *target_overlaps)
{
    return (collision_check_and_handle_at(mid_at,
                                          target_attacked, target_overlaps));
}


//
// "true" on overlap/collision at the specified position. This might be
// a speculative move on behalf of the thing.
//
bool Thing::collision_check_only (fpoint future_pos)
{
    if (is_loggable_for_unimportant_stuff()) {
        log("Collision check only");
    }
_
    int minx = future_pos.x - thing_collision_tiles;
    while (minx < 0) {
        minx++;
    }

    int miny = future_pos.y - thing_collision_tiles;
    while (miny < 0) {
        miny++;
    }

    int maxx = future_pos.x + thing_collision_tiles;
    while (maxx >= MAP_WIDTH) {
        maxx--;
    }

    int maxy = future_pos.y + thing_collision_tiles;
    while (maxy >= MAP_HEIGHT) {
        maxy--;
    }

    for (int16_t x = minx; x <= maxx; x++) {
        for (int16_t y = miny; y <= maxy; y++) {
            FOR_ALL_COLLISION_THINGS(level, it, x, y) {
                if (this == it) {
                    continue;
                }

                //
                // Skip things we cannot collide with
                //
                if (it->is_hidden ||
                    it->is_falling ||
                    it->is_jumping ||
                    it->is_changing_level) {
                    log("Ignore falling %s", it->to_string().c_str());
                    continue;
                }

                if (collision_check_only(it, future_pos, x, y)) {
                    log("Cannot move");
                    return true;
                }
            } FOR_ALL_THINGS_END()
        }
    }
    return false;
}

//
// "true" on overlap/collision at the current position
//
bool Thing::collision_check_only (void)
{
    return (collision_check_only(mid_at));
}
