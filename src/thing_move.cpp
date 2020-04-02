//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"
#include "my_sprintf.h"

void Thing::stop (void)
{_
    target = at;
    cursor_path_stop();
}

bool Thing::move (fpoint future_pos)
{_
    bool up     = future_pos.y < at.y;
    bool down   = future_pos.y > at.y;
    bool left   = future_pos.x < at.x;
    bool right  = future_pos.x > at.x;
    bool attack = false;
    bool idle   = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, idle));
}

bool Thing::attack (fpoint future_pos)
{_
    bool up     = future_pos.y < at.y;
    bool down   = future_pos.y > at.y;
    bool left   = future_pos.x < at.x;
    bool right  = future_pos.x > at.x;
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
{_
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
    auto delta = fpoint(x, y) - at;

    if (tp_gfx_bounce_on_move(tp())) {
        bounce(0.1, 0.1, 250, 3);
    }

    move_set_dir_from_delta(delta);

    if (attack) {
        use();

        if (is_player()) {
            game->tick_begin();
        }

        if ((x == at.x) && (y == at.y)) {
            return (false);
        }
    }

    if ((x == at.x) && (y == at.y)) {
        return (false);
    }

    if (is_player()) {
        game->tick_begin();
    }

    if (is_player()) {
        if (at != future_pos) {
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

    if (tp_gfx_animated_can_hflip(tp())) {
        if (future_pos.x > at.x) {
            if (is_facing_left && !get_timestamp_flip_start()) {
                set_timestamp_flip_start(time_get_time_ms_cached());
            }
        } else if (future_pos.x < at.x) {
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

void Thing::bounce (double bounce_height,
                    double bounce_fade,
                    timestamp_t ms,
                    int bounce_count)
{_
    auto t = set_timestamp_bounce_begin(time_get_time_ms_cached());
    set_timestamp_bounce_end(t + ms);

    set_bounce_height(bounce_height);
    set_bounce_fade(bounce_fade);
    set_bounce_count(bounce_count);
    is_bouncing = true;
}

void Thing::fadeup (double fadeup_height,
                    double fadeup_fade,
                    timestamp_t ms)
{_
    auto t = set_timestamp_fadeup_begin(time_get_time_ms_cached());
    set_timestamp_fadeup_end(t + ms);

    set_fadeup_height(fadeup_height);
    set_fadeup_fade(fadeup_fade);
    is_fadeup = true;
}

void Thing::lunge (fpoint to)
{_
    auto t = set_timestamp_lunge_begin(time_get_time_ms_cached());
    set_timestamp_lunge_end(t + 200);
    set_lunge_to(to);
}

double Thing::get_bounce (void)
{_
    if (!is_bouncing) {
        return (0.0);
    }

    auto t = time_get_time_ms_cached();

    if (t >= get_timestamp_bounce_end()) {
        is_bouncing = false;

        if (get_bounce_count()) {
            bounce(
                get_bounce_height() * get_bounce_fade(),
                get_bounce_fade(),
                (double)(get_timestamp_bounce_end() -
                         get_timestamp_bounce_begin()) * get_bounce_fade(),
                get_bounce_count() - 1);
        }

        return (0);
    }

    double time_step =
        (double)(t - get_timestamp_bounce_begin()) /
        (double)(get_timestamp_bounce_end() - get_timestamp_bounce_begin());

    double height = 1.0;

    height *= sin(time_step * RAD_180);
    height *= get_bounce_height();

    return (height);
}

double Thing::get_fadeup (void)
{_
    if (!is_fadeup) {
        return (0.0);
    }

    auto t = time_get_time_ms_cached();

    if (t >= get_timestamp_fadeup_end()) {
        gl_last_color.a = 0;
        dead("fadeup finished");
        return (-1);
    }

    double time_step =
        (double)(t - get_timestamp_fadeup_begin()) /
        (double)(get_timestamp_fadeup_end() - get_timestamp_fadeup_begin());

    gl_last_color.a = (uint8_t)(255.0 - (250.0 * time_step));
    glcolor(gl_last_color);

    double height = br.y - tl.y;

    height *= sin(time_step * RAD_90);
    height *= get_fadeup_height();

    return (height);
}

double Thing::get_lunge (void)
{_
    if (!get_timestamp_lunge_begin()) {
        return (0);
    }

    auto t = time_get_time_ms_cached();

    if (t >= get_timestamp_lunge_end()) {
        return (0);
    }

    double time_step =
        (double)(t - get_timestamp_lunge_begin()) /
        (double)(get_timestamp_lunge_end() - get_timestamp_lunge_begin());

    if (time_step > 0.5) {
        return (1.0 - time_step);
    } else {
        return time_step;
    }
}

void Thing::update_pos (fpoint to, bool immediately)
{_
    auto tpp = tp();

    point new_at((int)to.x, (int)to.y);
    if (level->is_oob(new_at)) {
        return;
    }

    point old_at((int)at.x, (int)at.y);

    has_ever_moved = true;

    if (!has_ever_moved) {
        at = to;
    }

    //
    // Keep track of where this thing is on the grid
    //
    if (old_at != new_at) {
        if (is_wall()) {
            level->unset_wall(old_at.x, old_at.y);
            level->set_wall(new_at.x, new_at.y);
        }
        if (is_floor()) {
            level->unset_floor(old_at.x, old_at.y);
            level->set_floor(new_at.x, new_at.y);
        }
        if (is_hazard()) {
            level->unset_hazard(old_at.x, old_at.y);
            level->set_hazard(new_at.x, new_at.y);
        }
        if (is_secret_door()) {
            level->unset_secret_door(old_at.x, old_at.y);
            level->set_secret_door(new_at.x, new_at.y);
        }
        if (is_corpse()) {
            level->unset_corpse(old_at.x, old_at.y);
            level->set_corpse(new_at.x, new_at.y);
        }
        if (is_lava()) {
            level->unset_lava(old_at.x, old_at.y);
            level->set_lava(new_at.x, new_at.y);
        }
        if (is_blood()) {
            level->unset_blood(old_at.x, old_at.y);
            level->set_blood(new_at.x, new_at.y);
        }
        if (is_water()) {
            level->unset_water(old_at.x, old_at.y);
            level->set_water(new_at.x, new_at.y);
        }
        if (is_corridor()) {
            level->unset_corridor(old_at.x, old_at.y);
            level->set_corridor(new_at.x, new_at.y);
        }
        if (is_dirt()) {
            level->unset_dirt(old_at.x, old_at.y);
            level->set_dirt(new_at.x, new_at.y);
        }
        if (tp_gfx_large_shadow(tpp)) {
            level->unset_gfx_large_shadow(old_at.x, old_at.y);
            level->set_gfx_large_shadow(new_at.x, new_at.y);
        }

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
    } else{_
        speed = tp_stats_move_speed_ms(tpp);
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    at = to;

    if (!immediately) {
        set_timestamp_move_begin(time_get_time_ms_cached());
        set_timestamp_move_end(get_timestamp_move_begin() + speed);
    }

    move_carried_items();

    if (tp_is_loggable(tpp)) {
        dbg("moved");
    }

    fpoint blit_tl;
    fpoint blit_br;
    Tilep tile;

    get_coords(blit_tl, blit_br, tile);
}

void Thing::move_set_dir_from_delta (fpoint delta)
{_
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
{_
    auto delta = to - at;
    move_set_dir_from_delta(delta);
    update_pos(to, false);
}

void Thing::move_delta (fpoint delta)
{_
    move_set_dir_from_delta(delta);
    update_pos(at + delta, false);
}

void Thing::move_to_immediately (fpoint to)
{_
    auto delta = to - at;
    move_set_dir_from_delta(delta);
    update_pos(to, true);
}

void Thing::move_to_immediately_delta (fpoint delta)
{_
    move_set_dir_from_delta(delta);
    update_pos(at + delta, true);
}

void Thing::move_carried_items (void)
{_
    //
    // Light source follows the thing.
    //
    update_light();

    //
    // Weapons follow also.
    //
    if (get_weapon_id_carry_anim()) {
        auto w = thing_find(get_weapon_id_carry_anim());
        if (w) {
            w->move_to(at);
            w->dir = dir;
        }
    }

    if (get_weapon_id_use_anim()) {
        auto w = thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to(at);
            w->dir = dir;
        }
    }

    //
    // If something moves on the water, make bubbles?
    //
    if (is_monst() || is_player()) {
        if (level->is_water((int)at.x, (int)at.y)) {
            if (random_range(0, 1000) > 500) {
                thing_new(tp_name(tp_random_ripple()), at);
            }
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id) {
        auto w = thing_find(on_fire_anim_id);
        if (w) {
            w->move_to(at);
            w->dir = dir;
        }
    }
}
