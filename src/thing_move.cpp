//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_thing.h"

//
// This is movement on the client of the player initiated by the player.
//
bool Thing::move (fpoint future_pos)
{
    bool up     = future_pos.y < at.y;
    bool down   = future_pos.y > at.y;
    bool left   = future_pos.x < at.x;
    bool right  = future_pos.x > at.x;
    bool attack = false;

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

    if ((x == at.x) && (y == at.y)) {
        return (false);
    }

    if (up || down || left || right) {
        move_delta(fpoint(x, y) - at);
    }

    bounce(0.1, 0.1, 100, 3);

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
        x = at.x;
        y = at.y;

        interpolated_at = at;
    } else {
        double t = end_move_ms - begin_move_ms;
        double dt = time_get_time_ms_cached() - begin_move_ms;
        double step = dt / t;
        double dx = at.x - last_at.x;
        double dy = at.y - last_at.y;

        x = last_at.x + dx * step;
        y = last_at.y + dy * step;

        interpolated_at = fpoint(x, y);
    }

    double tx = x;
    double ty = y;

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
    if (unlikely(tp_is_blitted_as_sitting_on_the_ground(tp))) {
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

#if 0
    //
    // So the player floats a bit over the ground
    //
    if (tp_is_blit_y_offset(tp)) {
        tl.y -= 0.01;
        br.y -= 0.01;
    }
#endif

    if (unlikely(tp_is_animated_can_hflip(tp))) {
        if (flip_start_ms) {
            auto diff = time_get_time_ms_cached() - flip_start_ms;
            uint32_t flip_time = 100;
            uint32_t flip_steps = 100;

            if (diff > flip_time) {
                flip_start_ms = 0;
                if (is_dir_left()) {
                    std::swap(tl.x, br.x);
                }
            } else {
                if (is_dir_right()) {
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
            if (is_dir_left()) {
                std::swap(tl.x, br.x);
            }
        }
    }

    if (unlikely(tp_is_animated_can_vflip(tp))) {
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

    point old_at((int)at.x, (int)at.y);

    has_ever_moved = true;

    if (!has_ever_moved) {
        last_at = to;
    } else {
        last_at = at;
    }

    //
    // Keep track of where this thing is on the grid
    //
    if (old_at != new_at) {
        if (tp_is_wall(tp)) {
            game.state.map.is_wall[old_at.x][old_at.y] = false;
            game.state.map.is_wall[new_at.x][new_at.y] = true;
        }
        if (tp_is_rock(tp)) {
            game.state.map.is_rock[old_at.x][old_at.y] = false;
            game.state.map.is_rock[new_at.x][new_at.y] = true;
        }
        if (tp_is_wall(tp) || tp_is_rock(tp)) {
            game.state.map.is_solid[old_at.x][old_at.y] = false;
            game.state.map.is_solid[new_at.x][new_at.y] = true;
        }
        if (tp_is_floor(tp)) {
            game.state.map.is_floor[old_at.x][old_at.y] = false;
            game.state.map.is_floor[new_at.x][new_at.y] = true;
        }
        if (tp_is_lava(tp)) {
            game.state.map.is_lava[old_at.x][old_at.y] = false;
            game.state.map.is_lava[new_at.x][new_at.y] = true;
        }
        if (tp_is_blood(tp)) {
            game.state.map.is_blood[old_at.x][old_at.y] = false;
            game.state.map.is_blood[new_at.x][new_at.y] = true;
        }
        if (tp_is_water(tp)) {
            game.state.map.is_water[old_at.x][old_at.y] = false;
            game.state.map.is_water[new_at.x][new_at.y] = true;
        }
        if (tp_is_deep_water(tp)) {
            game.state.map.is_deep_water[old_at.x][old_at.y] = false;
            game.state.map.is_deep_water[new_at.x][new_at.y] = true;
        }
        if (tp_is_corridor(tp)) {
            game.state.map.is_corridor[old_at.x][old_at.y] = false;
            game.state.map.is_corridor[new_at.x][new_at.y] = true;
        }
        if (tp_is_dirt(tp)) {
            game.state.map.is_dirt[old_at.x][old_at.y] = false;
            game.state.map.is_dirt[new_at.x][new_at.y] = true;
        }
        if (tp_is_monst(tp)) {
            game.state.map.is_monst[old_at.x][old_at.y] = false;
            game.state.map.is_monst[new_at.x][new_at.y] = true;
        }
        if (tp_is_key(tp)) {
            game.state.map.is_key[old_at.x][old_at.y] = false;
            game.state.map.is_key[new_at.x][new_at.y] = true;
        }
        if (tp_is_shadow_caster(tp)) {
            game.state.map.is_shadow_caster[old_at.x][old_at.y] = false;
            game.state.map.is_shadow_caster[new_at.x][new_at.y] = true;
        }
        if (tp_is_door(tp)) {
            game.state.map.is_door[old_at.x][old_at.y] = false;
            game.state.map.is_door[new_at.x][new_at.y] = true;
        }
    }

    //
    // Moves are immediate, but we render the move in steps, hence keep
    // track of when we moved.
    //
    at = to;
    begin_move_ms = time_get_time_ms_cached();
    end_move_ms = begin_move_ms + ONESEC / 10;

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

    update_pos(at + delta);
}

void Thing::move_to (fpoint to)
{_
    move_delta(fpoint(to.x - at.x, to.y - at.y));
}
