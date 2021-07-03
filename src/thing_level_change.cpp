//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_game.h"
#include "my_world.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_gl.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"
#include "my_light.h"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::level_change (Levelp l)
{_
    if (level == l) {
        dbg("Change level; no, same level");
        return;
    }

    auto old_level = level;

    dbg("Change level");
    level_leave();
    level = l;
    level_enter();

    if (monstp) {
        monstp->move_path = {};
        clear_age_map();
        clear_dmap_scent();
        move_finish();
    }

    if (is_player()) {
        old_level->player = nullptr;
        level->player = this;
    }

    {
        auto it = get_immediate_owner();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto it = weapon_get();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto it = weapon_get_carry_anim();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto it = weapon_get_use_anim();
        if (it) {
            it->level_change(l);
        }
    }

    {
        auto id = get_on_fire_anim_id();
        if (id.ok()) {
            auto it = level->thing_find(id);
            if (it) {
                it->level_change(l);
            }
        }
    }

    if (monstp) {
        for (auto id : monstp->carrying) {
            auto it = level->thing_find(id);
            if (it) {
                it->level_change(l);
            }
        }
    }

    for (auto l : get_light()) {
        l->level = level;
        l->reset();
    }

    dbg("Changed level");

    if (is_player()) {
        l->scroll_map_to_player();
    }

    //
    // Update the cursor position.
    //
    l->cursor_recreate();
    l->cursor_path_clear();
}
