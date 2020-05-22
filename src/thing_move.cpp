//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"
#include "my_gl.h"

void Thing::stop (void)
{
    mid_at = get_interpolated_mid_at();
    set_timestamp_move_begin(0);
    set_timestamp_move_end(0);
    update_interpolated_position();
    cursor_path_stop();
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
    return (move(future_pos, up, down, left, right, attack, idle));
}

bool Thing::attack (fpoint future_pos)
{
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = true;
    bool idle   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, idle));
}

bool Thing::move (fpoint future_pos,
                  uint8_t up,
                  uint8_t down,
                  uint8_t left,
                  uint8_t right,
                  uint8_t attack,
                  uint8_t idle)
{
    if (is_dead) {
        return (false);
    }

    if (idle) {
        if (is_player()) {
            game->tick_begin();
        }
        return (false);
    }

    auto x = future_pos.x;
    auto y = future_pos.y;
    auto delta = fpoint(x, y) - mid_at;

    if (tp_is_gfx_bounce_on_move(tp())) {
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
    }

    if (is_player()) {
        if (mid_at != future_pos) {
            if (collision_check_only(future_pos)) {
                try_to_shove(future_pos);
                lunge(future_pos);
                return (false);
            }
        }
    }

    if (is_player()) {
        if (!level->map_follow_player) {
            level->map_follow_player = true;
            level->cursor_needs_update = true;
        }
    }

    if (tp_is_gfx_animated_can_hflip(tp())) {
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

    get_bounce();
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        if (mid_at != last_mid_at) {
            update_pos = true;
            new_pos = mid_at;
            is_waiting_to_move = true;
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
        detach();
        set_interpolated_mid_at(new_pos);
        attach();
        update_light();
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

    has_ever_moved = true;

    if (!has_ever_moved) {
        last_mid_at = to;
    } else {
        last_mid_at = mid_at;
    }

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
        speed = tp_stats_move_speed_ms(owner->tp());
    } else{
        speed = tp_stats_move_speed_ms(tpp);
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    detach();
    mid_at = to;
    attach();

    if (!immediately) {
        set_timestamp_move_begin(time_get_time_ms_cached());
        set_timestamp_move_end(get_timestamp_move_begin() + speed);
    }

    move_carried_items();

    if (tp_is_loggable(tpp)) {
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
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);
    update_pos(to, false);
}

void Thing::move_delta (fpoint delta)
{
    move_set_dir_from_delta(delta);
    update_pos(mid_at + delta, false);
}

void Thing::move_to_immediately (fpoint to)
{
    auto delta = to - mid_at;
    move_set_dir_from_delta(delta);
    update_pos(to, true);
}

void Thing::move_to_immediately_delta (fpoint delta)
{
    move_set_dir_from_delta(delta);
    update_pos(mid_at + delta, true);
}
