//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_depth.h"
#include "my_game.h"
#include "my_gl.h"
#include "my_level.h"
#include "my_player.h"
#include "my_ptrcheck.h"
#include "my_python.h"
#include "my_sprintf.h"
#include "my_string.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_wid_console.h"
#include "my_wid_collect.h"
#include "my_array_bounds_check.h"

void Thing::on_move (void)
{_
    auto on_move = tp()->on_move_do();
    if (std::empty(on_move)) {
        return;
    }

    auto t = split_tokens(on_move, '.');
    if (t.size() == 2) {
        auto mod = t[0];
        auto fn = t[1];
        std::size_t found = fn.find("()");
        if (found != std::string::npos) {
            fn = fn.replace(found, 2, "");
        }

        log("call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), (int)mid_at.x, (int)mid_at.y);

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    } else {
        ERR("Bad on_move call [%s] expected mod:function, got %d elems",
            on_move.c_str(), (int)on_move.size());
    }
}

void Thing::move_reset_timestamps (void)
{_
    if (is_player()) {
        if (check_anything_to_carry()) {
            BOTCON("Press %%fg=yellow$%s%%fg=reset$ to collect items.",
                   SDL_GetScancodeName(
                        (SDL_Scancode)game->config.key_wait_or_collect));
            level->describe(mid_at);
        }
    }
    set_timestamp_move_begin(0);
    set_timestamp_move_end(0);
}

void Thing::move_finish (void)
{_
    if (get_timestamp_move_begin() == 0) {
        return;
    }

    //
    // Set this so that we can pick up items again at the last location.
    //
    set_where_i_dropped_an_item_last(point(-1, -1));
    move_reset_timestamps();

    if (!is_hidden) {
        log("Move to %f,%f finished", mid_at.x, mid_at.y);
    }

    update_interpolated_position();
}

bool Thing::move (fpoint future_pos)
{_
    if (!is_hidden) {
        log("Move to %f,%f", future_pos.x, future_pos.y);
    }

    //
    // Don't let minions wander too far
    //
    auto master = get_top_minion_owner();
    if (master) {
        if (minion_leash_distance()) {
            if (distance(future_pos, master->mid_at) >= minion_leash_distance()) {
                log("Minion cannot to %f,%f; it tugs at the leash", future_pos.x, future_pos.y);
                lunge(future_pos);
                return false;
            }
        }
    }

    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = false;
    bool wait_or_collect   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, wait_or_collect, true));
}

bool Thing::move_no_shove (fpoint future_pos)
{
    log("Move, without shoving to %f,%f", future_pos.x, future_pos.y);
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = false;
    bool wait_or_collect   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, wait_or_collect, false));
}

bool Thing::move (fpoint future_pos,
                  uint8_t up,
                  uint8_t down,
                  uint8_t left,
                  uint8_t right,
                  uint8_t attack,
                  uint8_t wait_or_collect,
                  bool shove_allowed)
{_
    log("Move");

    if (is_dead) {
        return false;
    }

    if (is_hidden) {
        log("Move; no, is hidden");
        return false;
    }
    if (is_changing_level) {
        log("Move; no waiting on level change");
        return false;
    }
    if (is_falling) {
        log("Move; no, is falling");
        return false;
    }
    if (is_jumping) { 
        log("Move; no, is jumping");
        return false;
    }

    //
    // Check for being stuck in webs or something else sticky
    //
    if (up || down || left || right) {
        if (loves_spiderwebs() && 
            level->is_spiderweb(mid_at.x, mid_at.y)) {
            //
            // No getting stuck in webs
            //
        } else if (level->is_sticky(mid_at.x, mid_at.y)) {
            //
            // Makes sure ghosts do not get stuck in webs.
            //
            if (!is_ethereal()) {
                if (is_player()) {
                    TOPCON("You cannot move!");
                }
                lunge(future_pos);
                return false;
            }
        }
    }

    //
    // No rest for the undead.
    //
    if (!attack) {
        if (!is_undead() && !is_ethereal()) {
            rest();
        }
    }

    //
    // Set this so that we can pick up items again at the last location.
    //
    set_where_i_dropped_an_item_last(point(-1, -1));

    if (wait_or_collect) {
        if (is_player()) {
            game->tick_begin("player idled");
        }

        log("Check if there is anything to carry here");
        auto items = anything_to_carry();
        if (!items.empty()) {
            if (items.size() > 1) {
                game->wid_collect_create(items);
            } else {
                try_to_carry(items);
            }
        } else {
            TOPCON("You wait...");
        }

#if 0
        location_check();
#endif
        return false;
    }

    //
    // Do this after wait checks, so the player can bump the tick
    // if stuck.
    //
    if (is_waiting_to_ascend_dungeon) {
        log("Move; no, is waiting to ascend dungeon");
        if (is_player()) {
            game->tick_begin("player waiting to ascend");
        }
        return false;
    }
    if (is_waiting_to_descend_sewer) {
        log("Move; no, is waiting to descend sewer");
        if (is_player()) {
            game->tick_begin("player waiting to descend");
        }
        return false;
    }
    if (is_waiting_to_descend_dungeon) {
        log("Move; no, is waiting to descend dungeon");
        if (is_player()) {
            game->tick_begin("player waiting to descend");
        }
        return false;
    }
    if (is_waiting_to_ascend_sewer) {
        log("Move; no, is waiting to ascend sewer");
        if (is_player()) {
            game->tick_begin("player waiting to ascend");
        }
        return false;
    }

    auto x = future_pos.x;
    auto y = future_pos.y;
    auto delta = fpoint(x, y) - mid_at;

    if (tp()->gfx_bounce_on_move()) {
        if (get_bounce() == 0) {
            bounce(0.2 /* height */, 0.1 /* fade */, 200, 3);
        }
    }

    move_set_dir_from_delta(delta);

    if (attack) {
        if (is_player()) {
            game->tick_begin("player attacked");
        }

        use_weapon();
        return false;
    }

    if ((x == mid_at.x) && (y == mid_at.y)) {
        return false;
    }

    if (is_player()) {
        game->tick_begin("player moved");
        log("Player move");
        _

        if (mid_at != future_pos) {
            log("Try to move; collision check");
            if (collision_check_only(future_pos)) {
                log("Cannot move; try to shove");
                if (shove_allowed) {
                    try_to_shove(future_pos);
                }
                lunge(future_pos);
                log("Move failed");
                return false;
            }
        }

        set_where_i_failed_to_collect_last(point(-1, -1));

        if (!level->map_follow_player) {
            level->map_follow_player = true;
        }
    }

    auto t = nearby_most_dangerous_thing_get();
    if (t) {
        auto free_attack =
             (t->get_tick() < game->tick_current) &&
             (((t->mid_at.x >= mid_at.x) && left) ||
              ((t->mid_at.x <= mid_at.x) && right) ||
              ((t->mid_at.y >= mid_at.y) && up) ||
              ((t->mid_at.y <= mid_at.y) && down));

        if (free_attack) {_
            log("Free attack by %s", t->to_string().c_str());
            if (t->attack(this)) {
                //
                // Too noisy?
                //
                if ((0)) {
                    if (is_player()) {
                        std::string s = t->text_The() + " attacks as you run";
                        TOPCON("%s.", s.c_str());
                    }
                }
            }

            //
            // Even if it misses, it counts
            //
            t->update_tick();
        }
    }

    if (tp()->gfx_animated_can_hflip()) {
        if (future_pos.x > mid_at.x) {
            if (is_facing_left && !get_timestamp_flip_start()) {
                set_timestamp_flip_start(time_get_time_ms_cached());
            }
        } else if (future_pos.x < mid_at.x) {
            if (!is_facing_left && !get_timestamp_flip_start()) {
                set_timestamp_flip_start(time_get_time_ms_cached());
            }
        }
    }

    if (up || down || left || right) {
        move_delta(delta);
    }

    return true;
}

void Thing::update_interpolated_position (void)
{_
    bool update_pos = false;
    fpoint new_pos;
    auto tpp = tp();

    auto p = get_top_owner();
    if ((p && p->is_falling) || is_falling) {
        if (z_depth == MAP_DEPTH_LAVA) {
            //
            // If we change the depth, it is displayed as white
            //
        } else if (z_depth == MAP_DEPTH_WATER) {
            //
            // If we change the depth, it is displayed as white
            //
        } else {
            //
            // Stops monsts falling over the floor tiles
            //
            z_depth = MAP_DEPTH_FLOOR;
        }
    } else {
        z_depth = tpp->z_depth;
    }

    if (is_jumping) {
        float t = get_timestamp_jump_end() - get_timestamp_jump_begin();
        float dt = time_get_time_ms_cached() - get_timestamp_jump_begin();

        float step;
        if (!t) {
            step = 1.0;
        } else {
            step = dt / t;
        }

        float dx = mid_at.x - last_mid_at.x;
        float dy = mid_at.y - last_mid_at.y;

        update_pos = true;
        new_pos.x = last_mid_at.x + dx * step;
        new_pos.y = last_mid_at.y + dy * step;
    } else if (!get_timestamp_move_end()) {
        if (mid_at != last_mid_at) {
            if (!is_hidden) {
                log("Changed position (new %f, %f, old %f,%f)",
                    mid_at.x, mid_at.y, last_mid_at.x, last_mid_at.y);
            }

            update_pos = true;
            new_pos = mid_at;
            last_mid_at = mid_at;
            set_timestamp_move_end(time_get_time_ms_cached());
            on_move();
        }
    } else if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        if (mid_at != last_mid_at) {
            if (!is_hidden) {
                log("End of move position (new %f, %f, old %f,%f)",
                    mid_at.x, mid_at.y, last_mid_at.x, last_mid_at.y);
            }

            update_pos = true;
            new_pos = mid_at;
            last_mid_at = mid_at;

            //
            // In case we changed level, update these
            //
            new_pos = mid_at;
            last_mid_at = mid_at;

            move_finish();
        }

        //
        // If the dead widget popped up, it waited for our move to end
        //
        if (is_player() && is_dead) {
            game->soft_pause();
        }
    } else {
        float t = get_timestamp_move_end() - get_timestamp_move_begin();
        float dt = time_get_time_ms_cached() - get_timestamp_move_begin();

        float step;
        if (!t) {
            step = 1.0;
        } else {
            step = dt / t;
        }

        float dx = mid_at.x - last_mid_at.x;
        float dy = mid_at.y - last_mid_at.y;

        new_pos.x = last_mid_at.x + dx * step;
        new_pos.y = last_mid_at.y + dy * step;
        update_pos = true;
    }

    if (update_pos) {
        if (g_opt_debug4) {
            log("Update interpolated pos");
        }

        level_pop();
        set_interpolated_mid_at(new_pos);
        level_push();

        //
        // For now only the player has a calculated light
        //
        update_light();
    }
}

void Thing::update_pos (fpoint to, bool immediately, uint32_t speed)
{_
    if (!is_hidden) {
        log("Update pos to %f,%f", to.x, to.y);
    }

    auto tpp = tp();
    point new_at((int)to.x, (int)to.y);
    if (level->is_oob(new_at)) {
        return;
    }

    point old_at((int)mid_at.x, (int)mid_at.y);

    if (!has_ever_moved) {
        last_mid_at = to;
    }

    has_ever_moved = true;

    //
    // Keep track of where this thing is on the grid
    //
    if (old_at != new_at) {
        if (is_player()) {
            if (((int)old_at.x != (int)new_at.x) ||
                ((int)old_at.y != (int)new_at.y)) {
                level->minimap_valid = false;
            }
        }
    }

    int move_speed;
    if (speed) {
        move_speed = speed;
    } else {
        auto owner = get_top_owner();
        if (owner) {
            move_speed = owner->tp()->move_speed_ms();
        } else{
            move_speed = tpp->move_speed_ms();
        }
    }

    //
    // If moving things on the non game level, move non smoothly
    //
    if (level != game->level) {
        immediately = true;
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    if (to == mid_at) {
        return;
    }

    if (!is_hidden) {
        log("Move to %f,%f speed %d", to.x, to.y, move_speed);
    }
    level_pop();
    mid_at = to;
    level_push();

    if (!immediately) {
        set_timestamp_move_begin(time_get_time_ms_cached());
        set_timestamp_move_end(get_timestamp_move_begin() + move_speed);
        on_move();
    }

    move_carried_items();

    if (!is_hidden) {
        if (tpp->is_loggable_for_unimportant_stuff()) {
            log("Moved");
        }
    }
}

void Thing::move_set_dir_from_delta (fpoint delta)
{
    //
    // If not moving and this is the first move then break out of the
    // idle animation.
    //
    if (is_dir_none()) {
        timestamp_next_frame = time_get_time_ms_cached();
    }

    if (delta.x < 0) {
        if (delta.y > 0) {
            dir_set_bl();
        } else if (delta.y < 0) {
            dir_set_tl();
        } else {
            dir_set_left();
        }
        is_moving = true;
        has_ever_moved = true;
        return;
    }

    if (delta.x > 0) {
        if (delta.y > 0) {
            dir_set_br();
        } else if (delta.y < 0) {
            dir_set_tr();
        } else {
            dir_set_right();
        }
        is_moving = true;
        has_ever_moved = true;
        return;
    }

    if (delta.y > 0) {
        if (delta.x > 0) {
            dir_set_br();
        } else if (delta.x < 0) {
            dir_set_bl();
        } else {
            dir_set_down();
        }
        is_moving = true;
        has_ever_moved = true;
        return;
    }

    if (delta.y < 0) {
        if (delta.x > 0) {
            dir_set_tr();
        } else if (delta.x < 0) {
            dir_set_tl();
        } else {
            dir_set_up();
        }
        is_moving = true;
        has_ever_moved = true;
        return;
    }
}

void Thing::move_to (fpoint to)
{_
    move_finish();
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);

    update_pos(to, false);
}

void Thing::move_to (fpoint to, uint32_t speed)
{_
    move_finish();
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);

    update_pos(to, false, speed);
}

void Thing::move_delta (fpoint delta)
{_
    move_finish();
    move_set_dir_from_delta(delta);

    //
    // If the move finish ended up doing something like moving into
    // a sewer, then we need to abort the delta move
    //
    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_ascend_sewer || 
        is_jumping) { 
        return;
    }

    update_pos(mid_at + delta, false);
}

void Thing::move_to_immediately (fpoint to)
{_
    move_finish();
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);

    //
    // Don't check for descending here as that check will be set when falling
    //
 
    update_pos(to, true);
    move_finish();

    if (is_changing_level ||
        is_hidden || 
        is_falling || 
        is_waiting_to_ascend_dungeon || 
        is_waiting_to_descend_sewer || 
        is_waiting_to_descend_dungeon || 
        is_waiting_to_ascend_sewer || 
        is_jumping) { 
        //
        // Things like changing level, don't look at the location until
        // the interpolated position is updated else we can look at the
        // old level coords on the new level and collide with the wrong
        // things
        //
    } else {
        location_check_forced();
    }

    if (is_player()) {
        if (!level->map_follow_player) {
            level->map_follow_player = true;
        }
    }

    update_interpolated_position();
}

bool Thing::move_to_check (const point& nh, const bool escaping)
{_
    if (escaping) {
        log("Escape to check %d,%d", nh.x, nh.y);
    } else {
        log("Move to check %d,%d", nh.x, nh.y);
    }

    //
    // Check to see if moving to this new location will hit something
    //
    // We need to look at the next-hop at the current time which may
    // be vacant, but also to the future if a thing is moving to that
    // spot; in which case we get an attack of opportunity.
    //
    auto fnh = fpoint(nh.x, nh.y);
    if (collision_check_only(fnh)) {
        //
        // We would hit something and cannot do this move. However,
        // see if we can hit the thing that is in the way.
        //
        log("Cannot move to %d,%d will hit obstacle or monst", nh.x, nh.y);
_
        bool target_attacked = false;
        bool target_overlaps = false;
        collision_check_and_handle_nearby(fnh,
                                          &target_attacked,
                                          &target_overlaps);
        if (target_attacked) {
            log("Cannot move to %d,%d, must attack", nh.x, nh.y);
            return true;
        } else {
            log("Cannot move to %d,%d, obstacle", nh.x, nh.y);
            return false;
        }
    } else {
        log("Move to %d,%d is ok", nh.x, nh.y);

        if (!escaping) {
            if (is_less_preferred_terrain(nh)) {_
                log("But %d,%d is less preferred terrain, avoid", nh.x, nh.y);
                return false;
            }
        }

        move(fnh);
        return true;
    }
}

bool Thing::move_to_or_attack (const point& nh)
{_
    log("Move to or attack");
    return move_to_check(nh, false);
}

bool Thing::move_to_or_escape (const point& nh)
{_
    log("Move to or escape");
    return move_to_check(nh, true);
}
