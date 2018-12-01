/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include "my_game.h"
#include "my_thing.h"

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

    bounce(0.1, 0.1, 100, 3);

    return (true);
}

void Thing::update_coordinates (void)
{
    const double tile_gl_width = game.config.tile_gl_width;
    const double tile_gl_height = game.config.tile_gl_height;

    double x;
    double y;

    if (time_get_time_ms() >= end_move_ms) {
        x = at.x;
        y = at.y;
    } else {
        double t = end_move_ms - begin_move_ms;
        double dt = time_get_time_ms() - begin_move_ms;
        double step = dt / t;
        double dx = at.x - last_at.x;
        double dy = at.y - last_at.y;

        x = last_at.x + dx * step;
        y = last_at.y + dy * step;
    }

    double tx = x - game.state.map_at.x;
    double ty = y - game.state.map_at.y;

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

    /*
     * Scale up tiles that are larger to the same pix scale.
     */
    if (unlikely(tile->pix_width != TILE_WIDTH)) {
        auto xtiles = (tile->pix_width / TILE_WIDTH) / 2.0;
        auto mx = (br.x + tl.x) / 2.0;
        tl.x = mx - (xtiles * tile_gl_width);
        br.x = mx + (xtiles * tile_gl_width);

        auto ytiles = (tile->pix_height / TILE_HEIGHT) / 2.0;
        auto my = (br.y + tl.y) / 2.0;
        tl.y = my - (ytiles * tile_gl_height);
        br.y = my + (ytiles * tile_gl_height);
    }

    /*
     * Put larger tiles on the same y base as small ones.
     */
    if (unlikely(tp_is_blit_off_center(tp))) {
        double y_offset = 
            (((tile->pix_height - TILE_HEIGHT) / TILE_HEIGHT) * 
                tile_gl_height) / 2.0;
        tl.y -= y_offset;
        br.y -= y_offset;
    }

    /*
     * Boing.
     */
    if (unlikely(is_bouncing)) {
        double height = get_bounce();

        tl.y -= height;
        br.y -= height;
    }

    /*
     * So the player floats a bit over the ground
     */
    if (tp_is_blit_y_offset(tp)) {
        tl.y -= 0.01;
        br.y -= 0.01;
    }

    if (unlikely(tp_is_animated_walk_flip(tp))) {
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
}

void thing_update_all_coordinates (void)
{
    for (auto p : game.state.map.all_things) {
        auto t = p.second;

        t->update_coordinates();
    }
}

void Thing::bounce (double bounce_height,
                    double bounce_fade,
                    uint32_t ms,
                    uint32_t bounce_count)
{
    timestamp_bounce_begin = time_get_time_ms();
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

    auto t = time_get_time_ms();

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
