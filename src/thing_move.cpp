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

    if (tp_gfx_bounce_on_move(tp())) {
        bounce(0.1, 0.1, 250, 3);
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

    if (tp_gfx_animated_can_hflip(tp())) {
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
    get_bounce();
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        detach();
        set_interpolated_mid_at(mid_at);
        attach();
        update_light();
    } else {
        double t = get_timestamp_move_end() - get_timestamp_move_begin();
        double dt = time_get_time_ms_cached() - get_timestamp_move_begin();
        double step = dt / t;
        double dx = mid_at.x - last_mid_at.x;
        double dy = mid_at.y - last_mid_at.y;

        auto x = last_mid_at.x + dx * step;
        auto y = last_mid_at.y + dy * step;

        detach();
        fpoint new_pos(x, y);
        set_interpolated_mid_at(new_pos);
        attach();
        update_light();
    }
}

bool Thing::update_coordinates (void)
{
    auto old_br = br;
    auto tpp = tp();

    get_bounce();

    double x;
    double y;

    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        x = mid_at.x;
        y = mid_at.y;

        if (is_active()) {
            if (!is_waiting_to_move) {
                is_waiting_to_move = true;
                auto now = time_get_time_ms_cached();
                auto delay = tp_ai_delay_after_moving_ms(tpp);
                auto jitter = random_range(0, delay / 10);
                set_timestamp_ai_next(now + delay + jitter);
            }
        }
    } else {
        double t = get_timestamp_move_end() - get_timestamp_move_begin();
        double dt = time_get_time_ms_cached() - get_timestamp_move_begin();
        double step = dt / t;
        double dx = mid_at.x - last_mid_at.x;
        double dy = mid_at.y - last_mid_at.y;

        x = last_mid_at.x + dx * step;
        y = last_mid_at.y + dy * step;
    }

#if 0
    //
    // Some things (like messages) have no tiles and so use the default.
    //
    float tile_pix_width = TILE_WIDTH;
    float tile_pix_height = TILE_HEIGHT;
    if (!is_no_tile()) {
        auto tile = tile_index_to_tile(tile_curr);
        if (!tile) {
            err("has no tile, index %d", tile_curr);
            return (false);
        }
        tile_pix_width = tile->pix_width;
        tile_pix_height = tile->pix_height;
    }

    //
    // Scale up tiles that are larger to the same pix scale.
    //
    if (unlikely((tile_pix_width != TILE_WIDTH) ||
                 (tile_pix_height != TILE_HEIGHT))) {
        auto xtiles = (tile_pix_width / TILE_WIDTH) / 2.0;
        auto mx = (br.x + tl.x) / 2.0;
        tl.x = mx - (xtiles * tile_gl_width);
        br.x = mx + (xtiles * tile_gl_width);

        auto ytiles = (tile_pix_height / TILE_HEIGHT) / 2.0;
        auto my = (br.y + tl.y) / 2.0;
        tl.y = my - (ytiles * tile_gl_height);
        br.y = my + (ytiles * tile_gl_height);
    }

    //
    // Put larger tiles on the same y base as small ones.
    //
    if (unlikely(tp_gfx_oversized_but_sitting_on_the_ground(tpp))) {
        double y_offset =
            (((tile_pix_height - TILE_HEIGHT) / TILE_HEIGHT) *
                tile_gl_height) / 2.0;
        tl.y -= y_offset;
        br.y -= y_offset;
    }

    //
    // Boing.
    //
    if (unlikely(is_bouncing)) {
        double height = get_bounce();

        tl.y -= height;
        br.y -= height;
    }

    //
    // Lunge to attack.
    //
    {
        auto lunge = get_lunge();
        if (lunge) {
            auto delta = get_lunge_to() - get_interpolated_mid_at();
            auto dx = -delta.x * lunge;
            auto dy = -delta.y * lunge;
            dx = -delta.x * lunge * tile_gl_width;
            dy = delta.y * lunge * tile_gl_height;
            tl.x -= dx;
            br.x -= dx;
            tl.y += dy;
            br.y += dy;
        }
    }
#endif

    //
    // If we've moved, need to update the display sort order.
    //
    if (br != old_br) {
        return (true);
    }

    return (false);
}

void Thing::bounce (double bounce_height,
                    double bounce_fade,
                    timestamp_t ms,
                    int bounce_count)
{
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
{
    auto t = set_timestamp_fadeup_begin(time_get_time_ms_cached());
    set_timestamp_fadeup_end(t + ms);

    set_fadeup_height(fadeup_height);
    set_fadeup_fade(fadeup_fade);
    is_fadeup = true;
}

void Thing::lunge (fpoint to)
{
    auto t = set_timestamp_lunge_begin(time_get_time_ms_cached());
    set_timestamp_lunge_end(t + 200);
    set_lunge_to(to);
}

double Thing::get_bounce (void)
{
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
{
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
{
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
        if (is_chasm()) {
            level->unset_chasm(old_at.x, old_at.y);
            level->set_chasm(new_at.x, new_at.y);
        }
        if (is_blood()) {
            level->unset_blood(old_at.x, old_at.y);
            level->set_blood(new_at.x, new_at.y);
        }
        if (is_water()) {
            level->unset_water(old_at.x, old_at.y);
            level->set_water(new_at.x, new_at.y);
        }
        if (is_deep_water()) {
            level->unset_deep_water(old_at.x, old_at.y);
            level->set_deep_water(new_at.x, new_at.y);
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
    } else{
        speed = tp_stats_move_speed_ms(tpp);
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    mid_at = to;

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

#if 0
void Thing::to_coords (fpoint *P0, fpoint *P1, fpoint *P2, fpoint *P3)
{
    P0->x = tl.x;
    P0->y = tl.y;
    P1->x = br.x;
    P1->y = tl.y;
    P2->x = br.x;
    P2->y = br.y;
    P3->x = tl.x;
    P3->y = br.y;
}
#endif

void Thing::move_carried_items (void)
{
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
            w->move_to(mid_at);
            w->dir = dir;
        }
    }

    if (get_weapon_id_use_anim()) {
        auto w = thing_find(get_weapon_id_use_anim());
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        }
    }

    //
    // If something moves on the water, make a ripple
    //
    if (is_monst() || is_player()) {
        if (level->is_water((int)mid_at.x, (int)mid_at.y)) {
            fpoint at(mid_at.x - 0.5, mid_at.y - 0.5);
            if (random_range(0, 1000) > 500) {
                thing_new(tp_name(tp_random_ripple()), at);
            }
        }
    }

    auto on_fire_anim_id = get_on_fire_anim_id();
    if (on_fire_anim_id) {
        auto w = thing_find(on_fire_anim_id);
        if (w) {
            w->move_to(mid_at);
            w->dir = dir;
        } else {
        }
    }
}
