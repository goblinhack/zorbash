//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"

bool Thing::move (fpoint future_pos)
{
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = false;

    verify(this);
    if (tp_gfx_can_hflip(tp)) {
        if (future_pos.x > mid_at.x) {
            if (is_facing_left && !flip_start_ms) {
                flip_start_ms = time_get_time_ms_cached();
            }
        } else if (future_pos.x < mid_at.x) {
            if (!is_facing_left && !flip_start_ms) {
                flip_start_ms = time_get_time_ms_cached();
            }
        }
    }
    return (move(future_pos, up, down, left, right, attack));
}

bool Thing::move (fpoint future_pos,
                  const uint8_t up,
                  const uint8_t down,
                  const uint8_t left,
                  const uint8_t right,
                  const uint8_t attack)
{
    if (is_dead) {
        return (false);
    }

    auto x = future_pos.x;
    auto y = future_pos.y;

    if (attack) {
        use();
    }

    if ((x == mid_at.x) && (y == mid_at.y)) {
        return (false);
    }

    if (up || down || left || right) {
        move_delta(fpoint(x, y) - mid_at);
    }

    if (tp_gfx_bounce_on_move(tp)) {
        bounce(0.1, 0.1, 100, 3);
    }

    return (true);
}

bool Thing::update_coordinates (void)
{
    old_br = br;

    get_bounce();

    const double tile_gl_width = game.config.tile_gl_width;
    const double tile_gl_height = game.config.tile_gl_height;

    double x;
    double y;

    if (time_get_time_ms_cached() >= end_move_ms) {
        x = mid_at.x;
        y = mid_at.y;

        interpolated_mid_at = mid_at;

        if (!is_waiting_for_ai) {
            is_waiting_for_ai = true;
            auto now = time_get_time_ms_cached();
            auto delay = tp_ai_delay_after_moving_ms(tp);
            auto jitter = random_range(0, delay / 10);
            next_ai_ms = now + delay + jitter;
        }
    } else {
        double t = end_move_ms - begin_move_ms;
        double dt = time_get_time_ms_cached() - begin_move_ms;
        double step = dt / t;
        double dx = mid_at.x - last_mid_at.x;
        double dy = mid_at.y - last_mid_at.y;

        x = last_mid_at.x + dx * step;
        y = last_mid_at.y + dy * step;

        interpolated_mid_at = fpoint(x, y);
    }

    double tx = x;
    double ty = y;

    tx -= sz.w / 2;
    ty -= sz.h / 2;

    tl.x = tx * tile_gl_width;
    tl.y = ty * tile_gl_height;
    br.x = (tx+1) * tile_gl_width;
    br.y = (ty+1) * tile_gl_height;

    Tilep tile;
    if (current_tileinfo) {
        tile = current_tileinfo->tile;
    } else {
        tile = current_tile;
    }

    //
    // Scale up tiles that are larger to the same pix scale.
    //
    if (unlikely((tile->pix_width != TILE_WIDTH) ||
                 (tile->pix_height != TILE_HEIGHT))) {
        auto xtiles = (tile->pix_width / TILE_WIDTH) / 2.0;
        auto mx = (br.x + tl.x) / 2.0;
        tl.x = mx - (xtiles * tile_gl_width);
        br.x = mx + (xtiles * tile_gl_width);

        auto ytiles = (tile->pix_height / TILE_HEIGHT) / 2.0;
        auto my = (br.y + tl.y) / 2.0;
        tl.y = my - (ytiles * tile_gl_height);
        br.y = my + (ytiles * tile_gl_height);
    }

    //
    // Put larger tiles on the same y base as small ones.
    //
    if (unlikely(tp_gfx_oversized_but_sitting_on_the_ground(tp))) {
        double y_offset =
            (((tile->pix_height - TILE_HEIGHT) / TILE_HEIGHT) *
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

    if (unlikely(tp_gfx_can_hflip(tp))) {
        if (flip_start_ms) {
            auto diff = time_get_time_ms_cached() - flip_start_ms;
            uint32_t flip_time = 100;
            uint32_t flip_steps = 100;

            if (diff > flip_time) {
                flip_start_ms = 0;
                is_facing_left = !is_facing_left;
                if (is_dir_left() ||
                    is_dir_tl()   ||
                    is_dir_bl()) {
                    std::swap(tl.x, br.x);
                }
            } else {
                if (is_dir_right() ||
                    is_dir_tr()   ||
                    is_dir_br()) {
                    std::swap(tl.x, br.x);
                }
                double w = br.x - tl.x;
                double dw = w / flip_steps;
                double tlx = tl.x;
                double brx = br.x;

                tl.x = tlx + dw * diff;
                br.x = brx - dw * diff;
            }
        } else {
            if (!is_facing_left) {
                std::swap(tl.x, br.x);
            }
        }
    }

    if (unlikely(tp_gfx_animated_can_vflip(tp))) {
        if (is_dir_up()) {
            std::swap(tl.y, br.y);
        }
    }

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
                    uint32_t ms,
                    uint32_t bounce_count)
{
    timestamp_bounce_begin = time_get_time_ms_cached();
    timestamp_bounce_end = timestamp_bounce_begin + ms;

    this->bounce_height = bounce_height;
    this->bounce_fade = bounce_fade;
    this->bounce_count = bounce_count;
    is_bouncing = true;
}

double Thing::get_bounce (void)
{
    if (!is_bouncing) {
        return (0.0);
    }

    auto t = time_get_time_ms_cached();

    if (t >= timestamp_bounce_end) {
        is_bouncing = false;

        if (bounce_count) {
            bounce(
                bounce_height * bounce_fade,
                bounce_fade,
                (double)(timestamp_bounce_end -
                         timestamp_bounce_begin) * bounce_fade,
                bounce_count - 1);
        }

        return (0);
    }

    double time_step =
        (double)(t - timestamp_bounce_begin) /
        (double)(timestamp_bounce_end - timestamp_bounce_begin);

    double height = br.y - tl.y;

    height *= sin(time_step * RAD_180);
    height *= bounce_height;

    return (height);
}

void Thing::update_pos (fpoint to)
{_
    point new_at((int)to.x, (int)to.y);
    if (game.state.map.is_oob(new_at)) {
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
            game.state.map.is_wall[old_at.x][old_at.y] = false;
            game.state.map.is_wall[new_at.x][new_at.y] = true;
        }
        if (is_wall() || is_rock()) {
            game.state.map.is_solid[old_at.x][old_at.y] = false;
            game.state.map.is_solid[new_at.x][new_at.y] = true;
        }
        if (is_floor()) {
            game.state.map.is_floor[old_at.x][old_at.y] = false;
            game.state.map.is_floor[new_at.x][new_at.y] = true;
        }
        if (is_lava()) {
            game.state.map.is_lava[old_at.x][old_at.y] = false;
            game.state.map.is_lava[new_at.x][new_at.y] = true;
        }
        if (is_blood()) {
            game.state.map.is_blood[old_at.x][old_at.y] = false;
            game.state.map.is_blood[new_at.x][new_at.y] = true;
        }
        if (is_water()) {
            game.state.map.is_water[old_at.x][old_at.y] = false;
            game.state.map.is_water[new_at.x][new_at.y] = true;
        }
        if (is_deep_water()) {
            game.state.map.is_deep_water[old_at.x][old_at.y] = false;
            game.state.map.is_deep_water[new_at.x][new_at.y] = true;
        }
        if (is_corridor()) {
            game.state.map.is_corridor[old_at.x][old_at.y] = false;
            game.state.map.is_corridor[new_at.x][new_at.y] = true;
        }
        if (is_dirt()) {
            game.state.map.is_dirt[old_at.x][old_at.y] = false;
            game.state.map.is_dirt[new_at.x][new_at.y] = true;
        }
        if (is_monst()) {
            game.state.map.is_monst[old_at.x][old_at.y] = false;
            game.state.map.is_monst[new_at.x][new_at.y] = true;
        }
        if (is_key()) {
            game.state.map.is_key[old_at.x][old_at.y] = false;
            game.state.map.is_key[new_at.x][new_at.y] = true;
        }
        if (tp_gfx_large_shadow_caster(tp)) {
            game.state.map.gfx_large_shadow_caster[old_at.x][old_at.y] = false;
            game.state.map.gfx_large_shadow_caster[new_at.x][new_at.y] = true;
        }
        if (is_door()) {
            game.state.map.is_door[old_at.x][old_at.y] = false;
            game.state.map.is_door[new_at.x][new_at.y] = true;
        }
    }

    int speed;
    auto owner = get_owner();
    if (owner) {
        speed = tp_move_speed_ms(owner->tp);
    } else{
        speed = tp_move_speed_ms(tp);
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    mid_at = to;
    begin_move_ms = time_get_time_ms_cached();
    end_move_ms = begin_move_ms + speed;

    move_carried_items();
}

void Thing::move_delta (fpoint delta)
{_
    //
    // If not moving and this is the first move then break out of the
    // idle animation.
    //
    if (is_dir_none()) {
        next_frame_ms = time_get_time_ms_cached();
    }

    if (delta.x > 0) {
        set_dir_left();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.x < 0) {
        set_dir_right();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.y > 0) {
        set_dir_up();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.y < 0) {
        set_dir_down();
        is_moving = true;
        has_ever_moved = true;
    }

    update_pos(mid_at + delta);
}

void Thing::move_to (fpoint to)
{_
    move_delta(fpoint(to.x - mid_at.x, to.y - mid_at.y));
}

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
