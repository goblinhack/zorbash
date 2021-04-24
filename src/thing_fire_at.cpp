//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_thing.h"
#include "my_math_util.h"
#include "wid_game_map_server.h"
#include "vision.h"

typedef struct {
    thingp target;
    const char *reason;
    uint16_t priority;
} thing_possible_hit;

#define MAX_THING_POSSIBLE_HIT 256

static thing_possible_hit thing_possible_hits[MAX_THING_POSSIBLE_HIT];
static uint32_t thing_possible_hit_size;

/*
 * Used for monsters firing intrinsic weapons
 */
static void thing_fire_at_target_xy_ (thingp t, 
                                      double target_x, 
                                      double target_y, 
                                      int line_of_fire)
{
    /*
     * Cannot fire until we're on a level.
     */
    if (!t->wid) {
        THING_LOG(t, "cannot fire yet, not on the level");
        return;
    }

    double dx, dy;

    /*
     * Any smaller than this and diagonal shots collide with adjoining walls.
     */
    double dist_from_player = 0.7;

    double distance = DISTANCE(t->x, t->y, target_x, target_y);
    double sx = (target_x - t->x) / distance;
    double sy = (target_y - t->y) / distance;

    dx = sx * dist_from_player;
    dy = sy * dist_from_player;

    /*
     * Fire from the player position plus the initial delta so it looks like 
     * it comes from outside of the body.
     */
    double x = t->x;
    double y = t->y;

    tpp projectile = 0;

    tpp weapon = thing_weapon(t);
    if (weapon) {
        projectile = tp_fires(weapon);
    }

    if (!projectile) {
        projectile = tp_fires(t->tp);
    }

    if (!projectile) {
        ERR("nothing to fire");
        return;
    }

    widp w = wid_game_map_server_replace_tile(
                                    wid_game_map_server_grid_container,
                                    x,
                                    y,
                                    0, /* thing */
                                    projectile,
                                    0, /* tpp data */
                                    0, /* item */
                                    0 /* stats */);
    if (!w) {
        return;
    }

    thingp p = wid_get_thing(w);

    /*
     * Make sure we keep track of who fired so we can award scores.
     */
    thing_set_owner(p, t);

    /*
     * Set up the modifier damage if this is say a fireball or bow for ex.
     */
    p->damage = thing_stats_get_total_damage(t);

    /*
     * If firing a component of an explosion, make sure the server sends it to 
     * the client. As we don't send explosion fragments, only the center.
     */
    p->is_epicenter = true;

    /*
     * Round up say -0.7 to -1.0
     */
    dx *= 10.0;
    dy *= 10.0;
    dx /= (dist_from_player * 10.0);
    dy /= (dist_from_player * 10.0);

    p->dx = sx;
    p->dy = sy;
    p->dir = thing_angle_to_dir(p->dx, p->dy);

    /*
     * Check for immediate collision with a wall
     */
    thing_handle_collisions(wid_game_map_server_grid_container, p);
    if (thing_is_dead_or_dying(p)) {
        return;
    }

    double fnexthop_x = p->x + p->dx;
    double fnexthop_y = p->y + p->dy;

    thing_server_move(p,
                      fnexthop_x,
                      fnexthop_y,
                      fnexthop_y < p->y,
                      fnexthop_y > p->y,
                      fnexthop_x < p->x,
                      fnexthop_x > p->x,
                      false, /* fire */
                      false  /* magic */);

    /*
     * Point the shooter at the target.
     */
    if (line_of_fire) {
        t->dir = thing_angle_to_dir(p->dx, p->dy);
        thing_update(t);
    }
}

/*
 * Used for monster and players firing.
 */
static void thing_fire_at_target_xy (thingp t, double target_x, double target_y)
{
    /*
     * Cannot fire until we're on a level.
     */
    if (!t->wid) {
        THING_LOG(t, "cannot fire yet, not on the level");
        return;
    }

    fpoint p1;

    double x, y;

    thing_real_to_fmap(t, &x, &y);

    p1.x = target_x - x;
    p1.y = target_y - y;

    double d = 10.0;
    double angle = anglerot(p1);

    if (thing_has_ability_burst_shot(t)) {
        double spread = RAD_360 / 20.0;
        double density = 3.0;

        double a;
        for (a = -spread; a <= spread; a += spread / density) {
            double x = t->x + fcos(a + angle) * d;
            double y = t->y + fsin(a + angle) * d;

            if (a != 0) {
                thing_fire_at_target_xy_(t, x, y, false);
            }
        }

        double x = t->x + fcos(angle) * d;
        double y = t->y + fsin(angle) * d;
        thing_fire_at_target_xy_(t, x, y, true);

    } else if (thing_has_ability_triple_shot(t)) {
        double spread = RAD_360 / 40;

        double x = t->x + fcos(angle + spread) * d;
        double y = t->y + fsin(angle + spread) * d;
        thing_fire_at_target_xy_(t, x, y, false);

        x = t->x + fcos(angle - spread) * d;
        y = t->y + fsin(angle - spread) * d;
        thing_fire_at_target_xy_(t, x, y, false);

        x = t->x + fcos(angle) * d;
        y = t->y + fsin(angle) * d;
        thing_fire_at_target_xy_(t, x, y, true);

    } else if (thing_has_ability_double_shot(t)) {
        double spread = RAD_360 / 60;

        double x = t->x + fcos(angle - spread) * d;
        double y = t->y + fsin(angle - spread) * d;
        thing_fire_at_target_xy_(t, x, y, false);

        x = t->x + fcos(angle + spread) * d;
        y = t->y + fsin(angle + spread) * d;
        thing_fire_at_target_xy_(t, x, y, true);

    } else if (thing_has_ability_reverse_shot(t)) {
        double spread = RAD_360 / 2;

        double x = t->x + fcos(angle - spread) * d;
        double y = t->y + fsin(angle - spread) * d;
        thing_fire_at_target_xy_(t, x, y, false);

        x = t->x + fcos(angle) * d;
        y = t->y + fsin(angle) * d;
        thing_fire_at_target_xy_(t, x, y, true);
    } else {
        double x = t->x + fcos(angle) * d;
        double y = t->y + fsin(angle) * d;

        thing_fire_at_target_xy_(t, x, y, true);
    }
}

/*
 * Used for players firing.
 */
void thing_server_fire (thingp t,
                        const uint8_t up,
                        const uint8_t down,
                        const uint8_t left,
                        const uint8_t right)
{
    /*
     * Cannot fire until we're on a level.
     */
    if (!t->wid) {
        THING_LOG(t, "cannot fire yet, not on the level");
        return;
    }

    /*
     * Never do this. All server things are hidden.
     *
    if (wid_is_hidden(t->wid)) {
        return;
    }
     */

    /*
     * Use the currently wielded weapon.
     */
    tpp weapon = thing_weapon(t);
    if (!weapon) {
        THING_LOG(t, "has no weapon, cannot fire");
        return;
    }

    /*
     * Does it potentially break each use?
     */
    thing_weapon_check_for_damage_on_firing(t, weapon);

    double dx, dy;

    /*
     * Any smaller than this and diagonal shots collide with adjoining walls.
     */
    double dist_from_player = 0.7;

    /*
     * Try current direction.
     */
    dx = 0.0;
    dy = 0.0;

    /*
     * If the player is moving too then the weapon has a bit more
     * speed than if thrown when stationary.
     */
    if (down) {
        dy = dist_from_player;
    }

    if (up) {
        dy = -dist_from_player;
    }

    if (right) {
        dx = dist_from_player;
    }

    if (left) {
        dx = -dist_from_player;
    }

    /*
     * If no dir, then try the last thing dir.
     */
    if ((dx == 0) && (dy == 0)) {
        if (thing_is_dir_down(t)) {
            dy = dist_from_player;
        }

        if (thing_is_dir_up(t)) {
            dy = -dist_from_player;
        }

        if (thing_is_dir_right(t)) {
            dx = dist_from_player;
        }

        if (thing_is_dir_left(t)) {
            dx = -dist_from_player;
        }

        if (thing_is_dir_tl(t)) {
            dx = -dist_from_player;
            dy = -dist_from_player;
        }

        if (thing_is_dir_tr(t)) {
            dx = dist_from_player;
            dy = -dist_from_player;
        }

        if (thing_is_dir_bl(t)) {
            dx = -dist_from_player;
            dy = dist_from_player;
        }

        if (thing_is_dir_br(t)) {
            dx = dist_from_player;
            dy = dist_from_player;
        }
    }

    /*
     * Fire from the player position plus the initial delta so it looks like 
     * it comes from outside of the body.
     */
    double x;
    double y;

    thing_real_to_fmap(t, &x, &y);
    x += dx;
    y += dy;

    double target_x = x + dx * 10;
    double target_y = y + dy * 10;

    tpp projectile = tp_fires(weapon);
    if (!projectile) {
        /*
         * Might be a sword.
         */
        thing_swing(t);
        return;
    } else {
        /*
         * Wand or shotgun etc...
         */
    }

    thing_fire_at_target_xy(t, target_x, target_y);
}

static void thing_fire_conical_at (thingp t, thingp target)
{
    double target_x, target_y;
    thing_real_to_fmap(target, &target_x, &target_y);

    double distance = DISTANCE(t->x, t->y, target_x, target_y);

    fpoint p1;

    p1.x = target_x - t->x;
    p1.y = target_y - t->y;

    double angle = anglerot(p1);
    double spread = RAD_360 / 360.0;
    double density = 1.0;

    double d;

    if (thing_is_dragon(t)) {
        for (d = 3.0; d < distance * 1.5; d += 1.0) {

            double a;

            spread += RAD_360 / 360.0;
            density += 1.0;

            for (a = -spread; a <= spread; a += spread / density) {
                double x = t->x + fcos(a + angle) * d;
                double y = t->y + fsin(a + angle) * d;

                level_place_explosion(server_level, t, 
                                    tp_fires(t->tp),
                                    t->x, t->y,
                                    x, y);
            }
        }
    } else {
        for (d = 1.0; d < distance; d += 1.0) {

            double a;

            spread += RAD_360 / 360.0;
            density += 1.0;

            for (a = -spread; a <= spread; a += spread / density) {
                double x = t->x + fcos(a + angle) * d;
                double y = t->y + fsin(a + angle) * d;

                level_place_explosion(server_level, t, 
                                    tp_fires(t->tp),
                                    t->x, t->y,
                                    x, y);
            }
        }
    }
}

/*
 * Used for monsters firing intrinsic weapons
 */
static void thing_fire_at (thingp t, thingp target)
{
    /*
     * Cannot fire until we're on a level.
     */
    if (!t->wid) {
        THING_LOG(t, "cannot fire yet, not on the level");
        return;
    }

    if (thing_is_conical_breath_attack(t)) {
        thing_fire_conical_at(t, target);
        return;
    }

    tpp projectile = 0;

    tpp weapon = thing_weapon(t);
    if (weapon) {
        projectile = tp_fires(weapon);
    }

    if (!projectile) {
        projectile = tp_fires(t->tp);
    }

    double target_x, target_y;
    thing_real_to_fmap(target, &target_x, &target_y);

    if (!projectile) {
        /*
         * Might be a sword, so don't swing if too far from the target else it 
         * just looks daft.
         */

        double distance = DISTANCE(t->x, t->y, target_x, target_y);
        double dx = (target_x - t->x) / distance;
        double dy = (target_y - t->y) / distance;

        if (distance > 2.0) {
            return;
        }

        t->dir = thing_angle_to_dir(dx, dy);
        thing_update(t);

        thing_swing(t);
        return;
    }

    thing_fire_at_target_xy(t, target_x, target_y);
}

/*
 * Add a thing to the list of things that could be hit on this attack.
 */
static void 
thing_possible_hit_add (thingp me, thingp target)
{
    double target_x, target_y;
    thing_real_to_fmap(target, &target_x, &target_y);

    if (!can_see(server_level, me->x, me->y, target_x, target_y)) {
        return;
    }

    if (thing_possible_hit_size >= MAX_THING_POSSIBLE_HIT) {
        return;
    }

    thing_possible_hit *h = &thing_possible_hits[thing_possible_hit_size++];
    memset(h, 0, sizeof(*h));
    h->target = target;
    h->priority = tp_get_hit_priority(target->tp);
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
static void thing_fire_at_best_target (thingp hitter)
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
        if (thing_is_animation(cand->target) ||
            thing_is_cloud_effect(cand->target) ||
            thing_is_weapon_swing_effect(cand->target)) {
            continue;
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
    }

    if (best) {
        thing_fire_at(hitter, best->target);
    }

    thing_possible_init();
}

/*
 * handle a single collision between two things
 */
static void thing_consider_target (thingp me, thingp it, 
                                    int32_t x, int32_t y)
{
    /*
     * Filter out boring things.
     */
    if (thing_is_dungeon_floor(it)  ||
        thing_is_world_floor(it)    ||
        thing_is_animation(it)) {
        return;
    }

    if (thing_is_dead_or_dying(it)) {
#if 0
if (debug) {
LOG("  dead or dying");
}
#endif
        return;
    }

    if (thing_has_left_level(it)) {
#if 0
if (debug) {
LOG("  no on lev");
}
#endif
        return;
    }

    /*
     * Need this or shields attack the player.
     */
    if (thing_owner(it) == me) {
#if 0
if (debug) {
LOG("  owner");
}
#endif
        return;
    }


    if (thing_is_shopkeeper(me)) {
        if (thing_is_monst(it)) {
            if (!thing_is_shopkeeper(it)) {
                thing_possible_hit_add(me, it);
                return;
            }
        }

        if (thing_is_angry(me)) {
            if (thing_is_player(it)) {
                thing_possible_hit_add(me, it);
                return;
            }
        }

        return;
    }

    if (thing_is_jesus(me)) {
        if (thing_is_monst(it)) {
            thing_possible_hit_add(me, it);
            return;
        }

        return;
    }

    if (thing_is_monst(me) || thing_is_trap(me)) {
        if (thing_is_player(it)) {
            thing_possible_hit_add(me, it);
            return;
        }
    }
}

/*
 * Try to find something to fire at.
 */
void thing_fire_at_target (thingp me)
{
    int32_t dx, dy;

    if (thing_has_left_level(me)) {
        return;
    }

    thing_map *map = thing_get_map(me);

    int distance = tp_get_vision_distance(me->tp);

    for (dx = -distance; dx <= distance; dx++) 
    for (dy = -distance; dy <= distance; dy++) {

        int32_t x = (int32_t)me->x + dx;
        int32_t y = (int32_t)me->y + dy;

        if ((x < 0) || (y < 0) || (x >= MAP_WIDTH) || (y >= MAP_HEIGHT)) {
            continue;
        }

        thing_map_cell *cell = &map->cells[x][y];

        uint32_t i;
        for (i = 0; i < cell->count; i++) {
            thingp it;
            
            if (me->on_server) {
                it = thing_server_id(cell->id[i]);
            } else {
                it = thing_client_id(cell->id[i]);
            }
#if 0
if (debug) {
LOG("%d %d [%d] %s",x,y,i, thing_logname(it));
}
#endif

            if (me == it) {
                continue;
            }

            thing_consider_target(me, it, x, y);
        }
    }

    thing_fire_at_best_target(me);
}
