//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"

bool Thing::move (fpoint future_pos)
{
    bool up     = future_pos.y < mid_at.y;
    bool down   = future_pos.y > mid_at.y;
    bool left   = future_pos.x < mid_at.x;
    bool right  = future_pos.x > mid_at.x;
    bool attack = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack));
}

bool Thing::move (fpoint future_pos,
                  uint8_t up,
                  uint8_t down,
                  uint8_t left,
                  uint8_t right,
                  uint8_t attack)
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

    if (tp_gfx_can_hflip(tp())) {
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
        move_delta(fpoint(x, y) - mid_at, false);
    }

    if (tp_gfx_bounce_on_move(tp())) {
        bounce(0.1, 0.1, 100, 3);
    }

    return (true);
}
    
void Thing::update_interpolated_position (void)
{
    get_bounce();
    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        set_interpolated_mid_at(mid_at);
    } else {
        double t = get_timestamp_move_end() - get_timestamp_move_begin();
        double dt = time_get_time_ms_cached() - get_timestamp_move_begin();
        double step = dt / t;
        double dx = mid_at.x - last_mid_at.x;
        double dy = mid_at.y - last_mid_at.y;

        auto x = last_mid_at.x + dx * step;
        auto y = last_mid_at.y + dy * step;
        set_interpolated_mid_at(fpoint(x, y));
    }
}

bool Thing::update_coordinates (void)
{
    auto old_br = br;
    auto tpp = tp();

    get_bounce();

    const double tile_gl_width = game->config.tile_gl_width;
    const double tile_gl_height = game->config.tile_gl_height;

    double x;
    double y;

    if (time_get_time_ms_cached() >= get_timestamp_move_end()) {
        x = mid_at.x;
        y = mid_at.y;

        if (is_active()) {
            if (!is_waiting_for_ai) {
                is_waiting_for_ai = true;
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

    double tx = x;
    double ty = y;

    auto sz = tpp->sz;
    tx -= sz.w / 2;
    ty -= sz.h / 2;

    tl.x = tx * tile_gl_width;
    tl.y = ty * tile_gl_height;

    br.x = (tx+1) * tile_gl_width;
    br.y = (ty+1) * tile_gl_height;

    //
    // To account for rounding errors in the display
    //
CON("XXX fix this");
    if (z_depth() <= MAP_DEPTH_LAST_FLOOR_TYPE) {
        br.x += tile_gl_width / (TILE_WIDTH * 4);
        br.y += tile_gl_height / (TILE_WIDTH * 4);
    }

    auto tile = tile_index_to_tile(tile_curr);
    if (!tile) {
        die("has no tile, index %d", tile_curr);
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
    if (unlikely(tp_gfx_oversized_but_sitting_on_the_ground(tpp))) {
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

    if (unlikely(tp_gfx_can_hflip(tpp))) {
        if (get_timestamp_flip_start()) {
            //
            // Slow flip
            //
            auto diff = time_get_time_ms_cached() - get_timestamp_flip_start();
            uint32_t flip_time = 100;
            uint32_t flip_steps = flip_time;

            if (diff > flip_time) {
                set_timestamp_flip_start(0);
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
                std::swap(tl.x, br.x);
            }
        } else {
            //
            // Fast flip
            //
            if (is_dir_right()) {
                std::swap(tl.x, br.x);
            }
        }
    }

    if (unlikely(tp_gfx_animated_can_vflip(tpp))) {
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
    auto t = set_timestamp_bounce_begin(time_get_time_ms_cached());
    set_timestamp_bounce_end(t + ms);

    set_bounce_height(bounce_height);
    set_bounce_fade(bounce_fade);
    set_bounce_count(bounce_count);
    is_bouncing = true;
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

    double height = br.y - tl.y;

    height *= sin(time_step * RAD_180);
    height *= get_bounce_height();

    return (height);
}

void Thing::update_pos (fpoint to, bool immediately)
{_
    auto tpp = tp();

    point new_at((int)to.x, (int)to.y);
    if (world->is_oob(new_at)) {
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
            world->unset_wall(old_at.x, old_at.y);
            world->set_wall(new_at.x, new_at.y);
        }
        if (is_floor()) {
            world->unset_floor(old_at.x, old_at.y);
            world->set_floor(new_at.x, new_at.y);
        }
        if (is_lava()) {
            world->unset_lava(old_at.x, old_at.y);
            world->set_lava(new_at.x, new_at.y);
        }
        if (is_blood()) {
            world->unset_blood(old_at.x, old_at.y);
            world->set_blood(new_at.x, new_at.y);
        }
        if (is_water()) {
            world->unset_water(old_at.x, old_at.y);
            world->set_water(new_at.x, new_at.y);
        }
        if (is_deep_water()) {
            world->unset_deep_water(old_at.x, old_at.y);
            world->set_deep_water(new_at.x, new_at.y);
        }
        if (is_corridor()) {
            world->unset_corridor(old_at.x, old_at.y);
            world->set_corridor(new_at.x, new_at.y);
        }
        if (is_dirt()) {
            world->unset_dirt(old_at.x, old_at.y);
            world->set_dirt(new_at.x, new_at.y);
        }
        if (tp_gfx_large_shadow_caster(tpp)) {
            world->unset_gfx_large_shadow_caster(old_at.x, old_at.y);
            world->set_gfx_large_shadow_caster(new_at.x, new_at.y);
        }
    }

    int speed;
    auto owner = owner_get();
    if (owner) {
        speed = tp_move_speed_ms(owner->tp());
    } else{
        speed = tp_move_speed_ms(tpp);
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
}

void Thing::move_delta (fpoint delta, bool immediately)
{_
    //
    // If not moving and this is the first move then break out of the
    // idle animation.
    //
    if (is_dir_none()) {
        timestamp_next_frame = time_get_time_ms_cached();
    }

    if (delta.x < 0) {
        dir_set_left();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.x > 0) {
        dir_set_right();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.y > 0) {
        dir_set_up();
        is_moving = true;
        has_ever_moved = true;
    }

    if (delta.y < 0) {
        dir_set_down();
        is_moving = true;
        has_ever_moved = true;
    }

    update_pos(mid_at + delta, immediately);
}

void Thing::move_to (fpoint to)
{_
    move_delta(fpoint(to.x - mid_at.x, to.y - mid_at.y), false);
}

void Thing::move_to_immediately (fpoint to)
{_
    move_delta(fpoint(to.x - mid_at.x, to.y - mid_at.y), true);
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
