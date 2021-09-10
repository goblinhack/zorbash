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
#include "my_monst.h"
#include "my_thing_template.h"
#include "my_wid_console.h"
#include "my_wid_actionbar.h"
#include "my_array_bounds_check.h"
#include "my_random.h"

void Thing::on_move (void)
{_
    if (is_player()) {
        //
        // Update reachability for the player
        //
        level->dmap_to_player_update();
    }

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

        dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_string().c_str(), (int)mid_at.x, (int)mid_at.y);

        py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int)mid_at.x, (unsigned int)mid_at.y);
    } else {
        ERR("Bad on_move call [%s] expected mod:function, got %d elems",
            on_move.c_str(), (int)on_move.size());
    }
}

void Thing::move_finish (void)
{_
    if (!is_moving) {
        return;
    }
    is_moving = false;

    dbg("Move finish");

    //
    // Set this so that we can pick up items again at the last location.
    //
    set_where_i_dropped_an_item_last(point(-1, -1));

    if (is_player()) {
        if (check_anything_to_carry(true)) {
            BOTCON("Press %%fg=yellow$%s%%fg=reset$ or click to collect.",
                   SDL_GetScancodeName(
                        (SDL_Scancode)game->config.key_wait_or_collect));
            level->describe(mid_at);
            wid_actionbar_init();
        }
    }

    if (!is_hidden) {
        dbg("Move to %f,%f finished", mid_at.x, mid_at.y);
    }

    //
    // Make sure that things that declare they are finished moving really
    // are where they should be.
    //
    update_pos(mid_at, true);
    update_interpolated_position();

    on_move();
}

bool Thing::move (fpoint future_pos)
{_
    if (!is_hidden) {
        dbg("Move to %f,%f", future_pos.x, future_pos.y);
    }

    //
    // Don't let minions wander too far
    //
    auto master = get_top_minion_owner();
    if (master) {
        if (minion_leash_distance()) {
            if (distance(future_pos, master->mid_at) >= minion_leash_distance()) {
                dbg("Minion cannot to %f,%f; it tugs at the leash", future_pos.x, future_pos.y);
                lunge(future_pos);
                return false;
            }
        }
    }

    bool up              = future_pos.y < mid_at.y;
    bool down            = future_pos.y > mid_at.y;
    bool left            = future_pos.x < mid_at.x;
    bool right           = future_pos.x > mid_at.x;
    bool attack          = false;
    bool wait_or_collect = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, wait_or_collect, true));
}

bool Thing::move (point future_pos)
{_
    return move(make_fpoint(future_pos));
}

bool Thing::move_no_shove (fpoint future_pos)
{
    dbg("Move, without shoving to %f,%f", future_pos.x, future_pos.y);
    bool up              = future_pos.y < mid_at.y;
    bool down            = future_pos.y > mid_at.y;
    bool left            = future_pos.x < mid_at.x;
    bool right           = future_pos.x > mid_at.x;
    bool attack          = false;
    bool wait_or_collect = false;

    verify(this);
    return (move(future_pos, up, down, left, right, attack, wait_or_collect, false));
}

bool Thing::move_no_shove (point future_pos)
{
    dbg("Move, without shoving to %d,%d", future_pos.x, future_pos.y);
    bool up              = future_pos.y < mid_at.y;
    bool down            = future_pos.y > mid_at.y;
    bool left            = future_pos.x < mid_at.x;
    bool right           = future_pos.x > mid_at.x;
    bool attack          = false;
    bool wait_or_collect = false;

    verify(this);
    return (move(make_fpoint(future_pos), up, down, left, right, attack, wait_or_collect, false));
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
    dbg("Move");

    if (is_dead) {
        return false;
    }

    if (is_hidden) {
        dbg("Move; no, is hidden");
        return false;
    }
    if (is_changing_level) {
        dbg("Move; no waiting on level change");
        return false;
    }
    if (is_falling) {
        dbg("Move; no, is falling");
        return false;
    }
    if (is_jumping) {
        dbg("Move; no, is jumping");
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
            // Makes sure ghosts (or the cursor!) do not get stuck in webs.
            //
            if (!is_ethereal() &&
                !is_cursor() &&
                !is_cursor_path()) {
                if (is_player()) {
                    if (level->is_spiderweb(mid_at.x, mid_at.y)) {
                        TOPCON("You are trapped in a web!");
                        game->tick_begin("trapped in a web");
                    } else {
                        TOPCON("You cannot move!");
                        game->tick_begin("trapped in something sticky");
                    }
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

        if (!game->robot_mode) {
            dbg("Check if there is anything to carry here");
            auto items = anything_to_carry();
            if (!items.empty()) {
                //
                // In mouse mode, it really is better to open a window to allow
                // choosing
                //
#if 0
                if (items.size() > 1) {
                    game->wid_collect_create(items);
                } else {
                    try_to_carry(items);
                }
#else
                game->wid_collect_create(items);
#endif
            }
        } else {
            TOPCON("You wait...");

            rest();
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
        dbg("Move; no, is waiting to ascend dungeon");
        if (is_player()) {
            game->tick_begin("player waiting to ascend");
        }
        return false;
    }
    if (is_waiting_to_descend_sewer) {
        dbg("Move; no, is waiting to descend sewer");
        if (is_player()) {
            game->tick_begin("player waiting to descend");
        }
        return false;
    }
    if (is_waiting_to_descend_dungeon) {
        dbg("Move; no, is waiting to descend dungeon");
        if (is_player()) {
            game->tick_begin("player waiting to descend");
        }
        return false;
    }
    if (is_waiting_to_ascend_sewer) {
        dbg("Move; no, is waiting to ascend sewer");
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
        if (mid_at != future_pos) {
            if (up) {
                dbg("Try to move up; collision check");
            } else if (down) {
                dbg("Try to move down; collision check");
            } else if (left) {
                dbg("Try to move left; collision check");
            } else if (right) {
                dbg("Try to move right; collision check");
            } else if (attack) {
                dbg("Try to move (attack); collision check");
            }

            if (collision_check_only(future_pos)) {
                if (shove_allowed) {
                    game->tick_begin("player tried to shove");
                    try_to_shove(future_pos);
                } else {
                    game->tick_begin("player tried to attack");
                    use_weapon();
                }
                lunge(future_pos);
                clear_move_path("Move failed");
                return false;
            } else {
                game->tick_begin("player moved");
            }
        }

        set_where_i_failed_to_collect_last(point(-1, -1));

        if (!level->map_follow_player) {
            level->map_follow_player = true;
        }
    }

    auto t = most_dangerous_adjacent_thing_get();
    if (is_monst() && t) {
        auto free_attack =
             (((t->mid_at.x >= mid_at.x) && left) ||
              ((t->mid_at.x <= mid_at.x) && right) ||
              ((t->mid_at.y >= mid_at.y) && up) ||
              ((t->mid_at.y <= mid_at.y) && down));

        if (free_attack) {_
            dbg("Free attack by %s", t->to_string().c_str());
            if (t->attack(this)) {
                //
                // Too noisy?
                //
                if (is_player()) {
                    std::string s = t->text_The() + " free attacks as you move";
                    TOPCON("%s.", s.c_str());
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
    fpoint new_pos = mid_at;
    auto tpp = tp();
    float step = game->tick_dt;

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
        float dx = mid_at.x - last_mid_at.x;
        float dy = mid_at.y - last_mid_at.y;

        new_pos.x = last_mid_at.x + dx * step;
        new_pos.y = last_mid_at.y + dy * step;
    } else if (!is_moving) {
        if (mid_at != last_mid_at) {
            if (!is_hidden) {
                dbg("Changed position (new %f, %f, old %f,%f)",
                    mid_at.x, mid_at.y, last_mid_at.x, last_mid_at.y);
            }

            new_pos = mid_at;
            last_mid_at = mid_at;
        }
    } else if (game->tick_dt >= 1) {
        if (mid_at != last_mid_at) {
            if (!is_hidden) {
                dbg("End of move position (new %f, %f, old %f,%f)",
                    mid_at.x, mid_at.y, last_mid_at.x, last_mid_at.y);
            }

            new_pos = mid_at;
            last_mid_at = mid_at;

            move_finish();
        }
    } else {
        float dx = mid_at.x - last_mid_at.x;
        float dy = mid_at.y - last_mid_at.y;

        new_pos.x = last_mid_at.x + dx * step;
        new_pos.y = last_mid_at.y + dy * step;
    }

    level_pop();
    set_interpolated_mid_at(new_pos);
    level_push();

    //
    // For now only the player has a calculated light
    //
    update_light();
}

void Thing::update_pos (fpoint to, bool immediately)
{_
    if (!is_hidden) {
        dbg("Update pos to %f,%f", to.x, to.y);
    }

    point new_at((int)to.x, (int)to.y);
    if (level->is_oob(new_at)) {
        return;
    }

    point old_at((int)mid_at.x, (int)mid_at.y);

    last_mid_at = mid_at;
    has_ever_moved = true;

    //
    // If moving things on the non game level, move non smoothly
    //
    if (level != game->level) {
        immediately = true;
    }

    //
    // Keep track of where this thing is on the grid
    //
    if (old_at == new_at) {
        return;
    }

    if (!is_hidden) {
        dbg("Move to %f,%f", to.x, to.y);
    }

    if (is_player()) {
        if (((int)old_at.x != (int)new_at.x) ||
            ((int)old_at.y != (int)new_at.y)) {
            level->minimap_valid = false;
        }
    }

    level_pop();
    mid_at = to;
    level_push();

    if (!immediately) {
        is_moving = true;
    }

    move_carried_items();
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

bool Thing::move_to_try (const point& nh, const bool escaping, bool check_only)
{_
    if (escaping) {
        dbg("Escape to try %d,%d", nh.x, nh.y);
    } else {
        dbg("Move to try %d,%d", nh.x, nh.y);
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
        dbg("Cannot move to %d,%d will hit obstacle or monst", nh.x, nh.y);
_
        bool target_attacked = false;
        bool target_overlaps = false;
        collision_check_and_handle_nearby(fnh,
                                          &target_attacked,
                                          &target_overlaps);
        if (target_attacked) {
            dbg("Cannot move to %d,%d, must attack", nh.x, nh.y);
            return true;
        } else {
            dbg("Cannot move to %d,%d, obstacle", nh.x, nh.y);
            return false;
        }
    } else {
        dbg("Move to %d,%d is ok", nh.x, nh.y);

        if (!escaping) {
            if (get_terrain_cost(nh) >= DMAP_LESS_PREFERRED_TERRAIN) {_
                dbg("But %d,%d is less preferred terrain, avoid", nh.x, nh.y);
                return false;
            }
        }

        if (!check_only) {
            move(fnh);
        }
        return true;
    }
}

bool Thing::move_to_or_attack (const point& nh)
{_
    dbg("Move to or attack");
    return move_to_try(nh, false, false);
}

bool Thing::move_to_or_escape (const point& nh)
{_
    dbg("Move to or escape");
    return move_to_try(nh, true, false);
}

bool Thing::move_to_or_attack_check_only (const point& nh)
{_
    dbg("Move to or attack");
    return move_to_try(nh, false, true);
}

bool Thing::move_to_or_escape_check_only (const point& nh)
{_
    dbg("Move to or escape");
    return move_to_try(nh, true, true);
}

void Thing::clear_move_path (const std::string &why)
{
    if (!monstp) {
        return;
    }

    if (is_player()) {
        game->cursor_move_path.clear();
        if (level) {
            level->cursor_path_clear();
        }

        if (game->robot_mode) {
            robot_change_state(ROBOT_STATE_IDLE, why);
        }
    }

    monstp->move_path.clear();
}
