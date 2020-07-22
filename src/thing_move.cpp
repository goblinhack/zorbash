//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::move_finish (void)
{
    // why?
    // mid_at = get_interpolated_mid_at();
    set_timestamp_move_begin(0);
    set_timestamp_move_end(0);
    update_interpolated_position();
}

bool Thing::move (fpoint future_pos)
{
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = false;
    bool idle   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, idle, true));
}

bool Thing::move_no_shove (fpoint future_pos)
{
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = false;
    bool idle   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, idle, false));
}

bool Thing::move (fpoint future_pos,
                  uint8_t up,
                  uint8_t down,
                  uint8_t left,
                  uint8_t right,
                  uint8_t attack,
                  uint8_t idle,
                  bool shove_allowed)
{
    if (is_dead) {
        return (false);
    }

    if (is_falling) {
        return (false);
    }

    if (idle) {
        if (is_player()) {
            game->tick_begin();
        }
        location_check();
        return (false);
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
        use();

        if (is_player()) {
            game->tick_begin();
        }

        if ((x == mid_at.x) && (y == mid_at.y)) {
            return (false);
        }
    }

    if ((x == mid_at.x) && (y == mid_at.y)) {
        return (false);
    }

    if (is_player()) {
        game->tick_begin();
        g_thing_callframes_depth = callframes_depth - 1;
        log("player tick");

        if (mid_at != future_pos) {
            if (collision_check_only(future_pos)) {
                if (shove_allowed) {
                    try_to_shove(future_pos);
                }
                lunge(future_pos);
                return (false);
            }
        }

        if (!level->map_follow_player) {
            level->map_follow_player = true;
            level->cursor_needs_update = true;
        }
    }
_
    auto t = nearby_most_dangerous_thing_get();
    if (t) {_
        auto free_attack =
             ((t->mid_at.x >= mid_at.x) && left) ||
             ((t->mid_at.x <= mid_at.x) && right) ||
             ((t->mid_at.y >= mid_at.y) && up) ||
             ((t->mid_at.y <= mid_at.y) && down);

        if (free_attack) {_
            if (t->attack(this)) {_
                if (is_player()) {
                    std::string s = t->text_The() + " attacks as you run";
                    MINICON("%s", s.c_str());
                }
            }
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

    return (true);
}

void Thing::update_interpolated_position (void)
{
    bool update_pos = false;
    fpoint new_pos;

    if (!get_timestamp_move_end()) {
        update_pos = true;
        new_pos = mid_at;
        last_mid_at = mid_at;
        set_timestamp_move_end(time_get_time_ms_cached());
    } else if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        if (mid_at != last_mid_at) {
            update_pos = true;
            new_pos = mid_at;
            last_mid_at = mid_at;
            location_check();

            //
            // In case we changed level, update these
            //
            new_pos = mid_at;
            last_mid_at = mid_at;

            if (is_player()) {
                level->cursor_needs_update = true;
            }
        }
    } else {
        float t = get_timestamp_move_end() - get_timestamp_move_begin();
        float dt = time_get_time_ms_cached() - get_timestamp_move_begin();
        float step = dt / t;
        float dx = mid_at.x - last_mid_at.x;
        float dy = mid_at.y - last_mid_at.y;

        new_pos.x = last_mid_at.x + dx * step;
        new_pos.y = last_mid_at.y + dy * step;
        update_pos = true;
    }

    if (update_pos) {
        level_pop();
        set_interpolated_mid_at(new_pos);
        level_push();

        if (get_light_count()) {
            update_light();
        }
    }
}

void Thing::update_pos (fpoint to, bool immediately)
{
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

    int speed;
    auto owner = owner_get();
    if (owner) {
        speed = owner->tp()->stats_move_speed_ms();
    } else{
        speed = tpp->stats_move_speed_ms();
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    level_pop();
    mid_at = to;
    level_push();

    if (!immediately) {
        set_timestamp_move_begin(time_get_time_ms_cached());
        set_timestamp_move_end(get_timestamp_move_begin() + speed);
    }

    move_carried_items();

    if (tpp->is_loggable_for_unimportant_stuff()) {
        dbg("moved");
    }
}

void Thing::move_set_dir_from_delta (fpoint delta)
{
    //
    // If not moving and this is the first move then break out of the
    // idle animati.
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
{
    move_finish();
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);
    update_pos(to, false);
}

void Thing::move_delta (fpoint delta)
{
    move_finish();
    move_set_dir_from_delta(delta);
    update_pos(mid_at + delta, false);
}

void Thing::move_to_immediately (fpoint to)
{
    move_finish();
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);
    update_pos(to, true);
    move_finish();

    //
    // End of jump handles this
    //
    if (!is_jumping) {
        location_check();
    }
}

void Thing::move_to_immediately_delta (fpoint delta)
{
    move_finish();
    move_set_dir_from_delta(delta);
    update_pos(mid_at + delta, true);
    move_finish();

    //
    // End of jump handles this
    //
    if (!is_jumping) {
        location_check();
    }
}

bool Thing::move_to_check (const point& nh, const bool escaping)
{_
    if (escaping) {
        log("escape to check %d,%d", nh.x, nh.y);
    } else {
        log("move to check %d,%d", nh.x, nh.y);
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
        log("move to %d,%d will hit obstacle or monst", nh.x, nh.y);
_
        bool target_attacked = false;
        bool target_overlaps = false;
        collision_check_and_handle_nearby(fnh,
                                          &target_attacked,
                                          &target_overlaps);
        if (target_attacked) {
            is_tick_done = true;
            log("cannot move to %d,%d, must attack", nh.x, nh.y);
            return (true);
        } else {
            log("cannot move to %d,%d, obstacle", nh.x, nh.y);
            return (false);
        }
    } else {
        log("move to %d,%d is ok", nh.x, nh.y);

        if (!escaping) {
            if (is_less_preferred_terrain(nh)) {_
                log("but %d,%d is less preferred terrain, avoid", nh.x, nh.y);
                return (false);
            }
        }

        is_tick_done = true;
        move(fnh);
        return (true);
    }
}

bool Thing::move_to_or_attack (const point& nh)
{_
    log("move to or attack");
    return move_to_check(nh, false);
}

bool Thing::move_to_or_escape (const point& nh)
{_
    log("move to or escape");
    return move_to_check(nh, true);
}
