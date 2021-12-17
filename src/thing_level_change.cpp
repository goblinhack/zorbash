//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_level.hpp"
#include "my_light.hpp"
#include "my_monst.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_world.hpp"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::level_change(Levelp l)
{
  TRACE_AND_INDENT();
  if (level == l) {
    dbg("Change level; no, same level");
    return;
  }

  auto old_level = level;

  dbg("Change level");
  level_leave();
  level = l;
  level_enter();

  if (maybe_aip()) {
    get_aip()->move_path = {};
    clear_age_map();
    clear_seen_map();
    clear_interrupt_map();
    clear_dmap_can_see();
    clear_can_see_currently();
    clear_can_see_ever();
  }

  move_finish();

  if (is_player()) {
    old_level->player = nullptr;
    level->player     = this;
  }

  {
    auto it = get_immediate_owner();
    if (it) {
      it->level_change(l);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto it = get_equip(e);
    if (it) {
      it->level_change(l);
    }

    it = get_equip_carry_anim(e);
    if (it) {
      it->level_change(l);
    }

    it = get_equip_use_anim(e);
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

  if (maybe_itemp()) {
    for (const auto it : get_item_vector()) {
      it->level_change(l);
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

  //
  // For auto and normal save
  //
  if (is_player()) {
    game->set_meta_data(l);
  }

  game->request_snapshot = true;
}
