//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"

//
// Get rid of all the hooks to other things that this thing has. e.g. the
// weapons it carries etc.
//
void Thing::level_change(Levelp l)
{
  TRACE_NO_INDENT();

  if (level == l) {
    return;
  }

  auto old_level = level;

  dbg("Change level");
  TRACE_AND_INDENT();

  level_leave();
  level = l;
  level_enter();

  if (maybe_aip()) {
    aip()->move_path = {};
    clear_age_map();
    clear_dmap_can_see_old();
    clear_interrupt_map();
    clear_dmap_can_see();
    clear_can_see_currently();
    clear_can_see_ever();
  }

  move_finish();

  //
  // Move the monster a bit - this fakes movement, so if the player follows, the monster
  // is not just sitting on the entrance.
  //
  if (is_monst()) {
    move_away_from_entrance();
  }

  if (is_player()) {
    //
    // I think we need to clean up the interesting_things_pending_remove list before leaving this level.
    //
    old_level->things_gc_if_possible();
    old_level->player = nullptr;
    level->player     = this;
  }

  {
    auto it = immediate_owner();
    if (it) {
      it->level_change(l);
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto it = equip_get(e);
    if (it) {
      it->level_change(l);
    }

    it = equip_carry_anim(e);
    if (it) {
      it->level_change(l);
    }

    it = equip_use_anim(e);
    if (it) {
      it->level_change(l);
    }
  }

  {
    auto id = on_fire_anim_id();
    if (id.ok()) {
      auto it = level->thing_find(id);
      if (it) {
        it->level_change(l);
      }
    }
  }

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      iter->level_change(l);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->level_change(l);
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->level_change(l);
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->level_change(l);
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        iter->level_change(l);
      }
    }
  }

  for (auto l : light_get()) {
    l->level = level;
    l->reset();
  }

  dbg("Changed level");
  TRACE_AND_INDENT();

  if (is_player()) {
    l->scroll_map_to_player();

    //
    // Update the cursor position.
    //
    l->cursor_recreate();
    l->cursor_path_clear();

    //
    // For auto and normal save
    //
    game->set_meta_data(l);
  }

  if (is_player()) {
    py_call_void_fn("events", "on_level_change", level->dungeon_walk_order_level_no, level->is_shop_level,
                    level->is_crystal_level, level->is_boss_level, level->is_final_boss_level);
  }

  //
  // Recreate as we might need to show location specific icons, like aacend ot descend
  //
  wid_actionbar_init();
}

//
// Move the monster a bit - this fakes movement, so if the player follows, the monster
// is not just sitting on the entrance.
//
bool Thing::move_away_from_entrance(void)
{
  if (! level) {
    return false;
  }

  if (! level->player) {
    return false;
  }

  dbg("Try to move away from entrance");
  TRACE_AND_INDENT();

  auto d = distance_to_player_on_different_level();
  d *= 2;
  if (d < 2) {
    d = 2;
  }

  auto tries = 1000;
  while (tries-- > 0) {
    int   x = curr_at.x + pcg_random_range(-d, d);
    int   y = curr_at.y + pcg_random_range(-d, d);
    point p(x, y);

    if (x < MAP_BORDER_ROCK) {
      continue;
    }

    if (y < MAP_BORDER_ROCK) {
      continue;
    }

    if (x >= MAP_WIDTH - MAP_BORDER_ROCK) {
      continue;
    }

    if (y >= MAP_HEIGHT - MAP_BORDER_ROCK) {
      continue;
    }

    if (level->is_oob(p)) {
      continue;
    }

    if (is_hated_by_me(p)) {
      continue;
    }

    dbg("Move away from entrance, to %d,%d", x, y);
    TRACE_AND_INDENT();
    move_to_immediately(point(x, y));

    return true;
  }

  dbg("Cold not move away from entrance");
  return false;
}
