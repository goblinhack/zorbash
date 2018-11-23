/*
 * Copyright (C) 2018 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include "my_game.h"
#include "my_thing.h"

fpoint Thing::get_velocity (void)
{
    fpoint v;

    v.x = momentum;                    
    v.y = fall_speed;

    return (v);
}

void Thing::set_velocity (double x, double y)
{
    momentum = x;
    fall_speed = y;
}

void Thing::set_velocity (fpoint v)
{
    momentum = v.x;
    fall_speed = v.y;
}

/*
 * This is movement on the client of the player initiated by the player.
 */
bool Thing::move (fpoint future_pos,
                  const uint8_t up,
                  const uint8_t down,
                  const uint8_t left,
                  const uint8_t right,
                  const uint8_t fire)
{
    if (is_dead) {
        return (false);
    }

    auto x = future_pos.x;
    auto y = future_pos.y;

    if (check_if_will_hit_solid_obstacle(future_pos)) {
        if (!check_if_will_hit_solid_obstacle(fpoint(x, at.y))) {
            y = at.y;
        } else if (!check_if_will_hit_solid_obstacle(fpoint(at.x, y))) {
            x = at.x;
        } else {
            return (false);
        }
    } else if ((x != 0) && (y != 0)) {
        /*
         * Avoid diagonal shortcuts through obstacles.
         */
        if (check_if_will_hit_solid_obstacle(fpoint(x, at.y))) {
            x = at.x;
        } 

        if (check_if_will_hit_solid_obstacle(fpoint(at.x, y))) {
            y = at.y;
        }
    }

    if ((x == at.x) && (y == at.y)) {
        return (false);
    }

    if (up || down || left || right) {
        move_delta(fpoint(x, y) - at);
    }

#if 0
    if (fire) {
        thing_fire(level, t, up, down, left, right);
    }
#endif

    handle_collisions();

    return (true);
}

/*
 * Try to keep moving with momentum
 */
bool Thing::slide (void)
{
    double x;
    double y = at.y;

    auto m = fabs(momentum);

    if (m > game.config.movement_max_speed) {
        if (momentum > game.config.movement_max_speed) {
            momentum = game.config.movement_max_speed;
        } else {
            momentum = -game.config.movement_max_speed;
        }
    }

    if (m < game.config.movement_min_speed) {
        momentum = 0;
        return (false);
    }

    rot += momentum;

    x = at.x + momentum;
    auto future_pos = fpoint(x, y);
    if (check_if_will_hit_solid_obstacle(future_pos)) {
        momentum /= 2;

        x = at.x + momentum;
        future_pos = fpoint(x, y);
        if (check_if_will_hit_solid_obstacle(future_pos)) {
            momentum /= 2;

            x = at.x + momentum;
            future_pos = fpoint(x, y);
            if (check_if_will_hit_solid_obstacle(future_pos)) {
                momentum /= 2;

                x = at.x + momentum;
                future_pos = fpoint(x, y);
                if (check_if_will_hit_solid_obstacle(future_pos)) {
                    momentum = 0;
                    return (false);
                }
            }
        }
    }

    momentum *= game.config.movement_friction;

    move_to(future_pos);

    handle_collisions();

    return (true);
}

#if 0
void thing_wid_move (levelp level,
                     thingp t, 
                     double x, 
                     double y, 
                     uint8_t smooth)
{
    double dist = DISTANCE(t->x, t->y, x, y);

    if (smooth) {
        if (dist == 0.0) {
            return;
        }
    }

    widp w = t->wid;

    thing_move_to(t, x, y);

    x *= game.tile_width;
    y *= game.tile_height;
    x += game.tile_width / 2;
    y += game.tile_height / 2;

    fpoint tl = { x, y };
    fpoint br = { x, y };

    if (!w) {
        /*
         * Player has left the level?
         */
        THING_LOG(t, "Trying to move but has no widget");
        DIE("bug");
        return;
    }

    tilep tile = wid_get_tile(w);
    if (tile) {
        double tw = tile_get_width(tile);
        double th = tile_get_height(tile);
        double scale_x = tw / TILE_WIDTH; 
        double scale_y = th / TILE_HEIGHT; 

        double tile_width = game.tile_width;
        double tile_height = game.tile_height;

        if (scale_x > 1) {
            tile_width *= scale_x;
            tile_height *= scale_y;
        }

        br.x += tile_width / 2.0;
        br.y += tile_height / 2.0;
        tl.x -= tile_width / 2.0;
        tl.y -= tile_height / 2.0;
    }

    /*
     * Now the tile itself has a shadow that is 1/4 of the pixels.
     * The center is 24x24 and with shadow it is 32x32. We need to
     * stretch the tile so it overlaps so the inner 24x24 if seamless.
     */
#if 0
    double tile_width = ((br.x - tl.x) / 
                         (double)TILE_PIX_WIDTH) * 
                            (double)TILE_PIX_WITH_SHADOW_WIDTH;

    double tile_height = ((br.y - tl.y) / 
                         (double)TILE_PIX_HEIGHT) * 
                            (double)TILE_PIX_WITH_SHADOW_HEIGHT;
    double tile_width = (br.x - tl.x);
    double tile_height = (br.y - tl.y);

    tile_width *= 0.50;
    tile_height *= 0.50;
#endif

#if 0
    double tile_width = (br.x - tl.x);
    double tile_height = (br.y - tl.y);
#endif

#if 0
    if (thing_is_wall(t) || thing_is_door(t)) {
        tl.y -= game.tile_height / 3.0;
        br.x += game.tile_width / 3.0;
    }
#endif

#if 0
    if (scale_x == 1) {
        tl.y -= tile_height / 4.0;
        br.x += tile_width / 4.0;
    }
#endif

#if 0
    /*
     * Stretch vertically a bit and then recented. Don't do this. Overlapping 
     * wall pixels with shadows mess up.
     */
    tl.y -= tile_height / 8.0;
    tl.y += tile_height / 16.0;
    br.y += tile_height / 16.0;
#endif

    /*
     * Off the map? Perhaps between levels.
     */
    if (!w) {
        return;
    }

    /*
     * For teleporting things, no smooth move!
     */
    if (dist > 2.0) {
        wid_move_end(w);
        smooth = false;
    }

    /*
     * Player moves better in small increments.
     */
    if (thing_is_player_or_owned_by_player(level, t)) {
        smooth = false;
    }

    /*
     * Breaks boulder bounce if not
     */
    if (thing_can_roll(t)) {
        smooth = false;
    }

    double ms = 1000;
    ms = ms / (1.0 / dist);

    /*
     * Add a bit of jumpiness to confuse the player.
     */
    if (thing_is_monst(t)) {
        ms -= 10.0 * gauss(tp_get_speed(thing_tp(t)), 10);
    }

    if (smooth) {
        if (t->is_jumping) {
            if (wid_is_moving(w)) {
                wid_move_end(w);
            }
        }

        wid_move_to_abs_poffset_in(w, tl, ms);
    } else {
        wid_set_tl_br(w, tl, br);
    }

    double bounce_ms = 300;

    /*
     * Make the player bounce about as they walk
     */
    if (thing_is_bomb(t)) {
        wid_bounce_to_pct_in(w, 0.1, 0.9, bounce_ms, 4);
    }

    if (thing_is_player(t) || 
        thing_is_monst(t)) {

        if (thing_is_player(t)) {
            if (t->is_submerged) {
                if (thing_is_dir_left(t) ||
                    thing_is_dir_tl(t) ||
                    thing_is_dir_bl(t)) {

                    wid_rotate_to_pct_in(w, 65, 70, ONESEC, 999);
                } else {
                    wid_rotate_to_pct_in(w, -65, -70, ONESEC, 999);
                }
            } else {
                if (time_have_x_tenths_passed_since(5, t->timestamp_last_submerged)) {
                    wid_rotate_to_pct_in(w, 0, 0, ONESEC, 999);

                    t->timestamp_last_submerged = time_get_time_ms();
                }
            }

            wid_effect_sways(t->wid);
            wid_set_animate(t->wid, false);
            wid_set_no_shape(t->wid);
        }

        if (!t->fall_speed && !t->jump_speed) {
            if (!w->bouncing) {
                wid_bounce_to_pct_in(w, 0.1, 0.9, bounce_ms, 0);
            }

            /*
             * And their little weapon too.
             */
            widp weapon_wid = thing_get_weapon_carry_anim_wid(level, t);
            if (weapon_wid) {
                wid_bounce_to_pct_in(weapon_wid, 0.15, 0.9, bounce_ms, 0);
            }
        }
    }
}

void thing_wid_update (levelp level,
                       thingp t, 
                       double x, double y, 
                       uint8_t smooth,
                       uint8_t is_new)
{
    verify(t);

    thing_wid_move(level, t, x, y, smooth);

    /*
     * Update the weapon being carried.
     */
    thingp weapon_carry_anim = thing_weapon_carry_anim(level, t);
    if (weapon_carry_anim) {
        weapon_carry_anim->dir = t->dir;
        if (thing_is_dir_left(t)) {
            thing_wid_move(level, weapon_carry_anim, x - 0.2, y - 0.3, smooth);
        } else {
            thing_wid_move(level, weapon_carry_anim, x + 0.2, y - 0.3, smooth);
        }
    }

    /*
     * Update the weapon being swung.
     */
    thingp weapon_swing_anim = thing_weapon_swing_anim(level, t);
    if (weapon_swing_anim) {
        double dx = 0;
        double dy = 0;

        weapon_swing_anim->dir = t->dir;
        thing_weapon_swing_offset(level, t, &dx, &dy);
        thing_wid_move(level, weapon_swing_anim, x + dx, y + dy, smooth);
    }
}

/*
 * Throw things in the vicinity around.
 */
thingp things_throw (levelp level, thingp t)
{
    thingp it;
    thingp me;
    widp wid_next;
    widp wid_me;
    widp wid_it;

    verify(t);
    wid_me = thing_wid(t);
    verify(wid_me);

    int32_t dx, dy;

    me = wid_get_thing(wid_me);

    uint8_t z;

    widp grid = game.wid_grid;

    int32_t collision_radius = thing_collision_radius(me);
    if (!collision_radius) {
        collision_radius = 2;
    }

    collision_radius *= 3;

    for (dx = -collision_radius; dx <= collision_radius; dx++) 
    for (dy = -collision_radius; dy <= collision_radius; dy++)
    for (z = MAP_DEPTH_OBJ; z < MAP_DEPTH; z++) {
        int32_t x = (int32_t)me->x + dx;
        int32_t y = (int32_t)me->y + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        wid_it = wid_grid_find_first(grid, x, y, z);
        while (wid_it) {
            verify(wid_it);

            wid_next = wid_grid_find_next(grid, wid_it, x, y, z);
            if (wid_me == wid_it) {
                wid_it = wid_next;
                continue;
            }

            it = wid_get_thing(wid_it);
            if (!it) {
                wid_it = wid_next;
                continue;
            }

            if (!thing_is_throwable(it)) {
                wid_it = wid_next;
                continue;
            }

            THING_LOG(it, "is thrown by the explosion");

            double scale = 8;

            it->momentum = (it->x - me->x) / scale;
            it->jump_speed = (it->y - me->y) / scale;

            wid_it = wid_next;
            continue;
        }
    }

    return (0);
}

thingp collision_ignore;
int things_handle_impact (levelp level, 
                          const thingp A, 
                          double nx,
                          double ny,
                          const thingp B)
{
    int check_only = false;
    int collided = false;
    fpoint intersect = {0,0};
    fpoint normal_A = {0,0};
    fpoint normal_B = {0,0};
    fpoint A_at = { A->x, A->y };
    fpoint B_at = { B->x, B->y };
    int circle_circle = false;

    if (thing_can_roll(A) && !thing_can_roll(B)) {
        if (circle_box_collision(level,
                                 A, /* circle */
                                 nx,
                                 ny,
                                 B, /* box */
                                 B->x,
                                 B->y,
                                 &normal_A,
                                 &intersect,
                                 check_only)) {
            normal_B = normal_A;
            collided = true;
        }
    } else if (thing_can_roll(A) && thing_can_roll(B)) {
        if (circle_circle_collision(A, /* circle */
                                    B, /* circle */
                                    nx,
                                    ny,
                                    &intersect)) {
            normal_A = fsub(B_at, A_at);
            normal_B = normal_A;
            collided = true;
            circle_circle = true;
        }
    } else{
        return (false);
    }

    if (!collided) {
        return (false);
    }

    /*
     * Normal vector is a line between the two center of masses.
     * Tangent vector is at 90 degrees to this.
     */
    fpoint normal_A_unit = funit(normal_A);
    fpoint tangent_A_unit = { -normal_A_unit.y, normal_A_unit.x };

    fpoint normal_B_unit = funit(normal_B);
    fpoint tangent_B_unit = { -normal_B_unit.y, normal_B_unit.x };

    double mA = 1;
    double mB = 1;

    fpoint vA = thing_velocity(A);
    fpoint vB = thing_velocity(B);

    if (thing_is_stationary(B)) {
        mB = mA;
        vB = fmul(-1, vA);
    }

    /*
     * Project the velocity onto the normal vectors.
     */
    double normal_A_len = fdot(normal_A_unit, vA);
    double normal_B_len = fdot(normal_B_unit, vB);

    double tangent_A_len = fdot(tangent_A_unit, vA);
    double tangent_B_len = fdot(tangent_B_unit, vB);
    
    /*
     * Tangent velocity doesn't change.after collision.
     */
    double tangent_A_velocity = tangent_A_len;
    double tangent_B_velocity = tangent_B_len;
    
    /*
     * Do one dimensional elastic collision.
     */
    double normal_A_velocity =
        (normal_A_len*(mA - mB) + 2.0 * mB*normal_B_len) / (mA + mB);

    double normal_B_velocity =
        (normal_B_len*(mB - mA) + 2.0 * mA*normal_B_len) / (mA + mB);

    fpoint normal_velocity_A  = fmul(normal_A_velocity, normal_A_unit);
    fpoint tangent_velocity_A = fmul(tangent_A_velocity, tangent_A_unit);

    A->normal_velocity  = normal_velocity_A;
    A->tangent_velocity = tangent_velocity_A;

    fpoint normal_velocity_B  = fmul(normal_B_velocity, normal_B_unit);
    fpoint tangent_velocity_B = fmul(tangent_B_velocity, tangent_B_unit);

    static double COLLISION_ELASTICITY      = 0.4;
    static double TANGENT_ELASTICITY        = 0.4;

    normal_velocity_A = fmul(COLLISION_ELASTICITY, normal_velocity_A);
    normal_velocity_B = fmul(COLLISION_ELASTICITY, normal_velocity_B);
    tangent_velocity_A = fmul(TANGENT_ELASTICITY, tangent_velocity_A);
    tangent_velocity_B = fmul(TANGENT_ELASTICITY, tangent_velocity_B);

    thing_set_velocity(A,
        normal_velocity_A.x + tangent_velocity_A.x,
        normal_velocity_A.y + tangent_velocity_A.y);

    if (thing_is_stationary(B)) {
        return (true);
    }

    thing_set_velocity(B,
        normal_velocity_B.x + tangent_velocity_B.x,
        normal_velocity_B.y + tangent_velocity_B.y);

    return (true);
}
#endif
