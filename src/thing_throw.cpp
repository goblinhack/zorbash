//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <math.h>

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

bool Thing::throw_item_choose_target(Thingp what)
{
  verify(what);
  if (! what) {
    err("Cannot throw null thing");
    return false;
  }

  TRACE_AND_INDENT();
  dbg("Trying to throw: %s", what->to_string().c_str());

  if (! what->is_throwable()) {
    if (is_player()) {
      TOPCON("I don't know how to throw %s.", what->text_the().c_str());
      game->tick_begin("player tried to throw something they could not");
    }
    return false;
  }

  if (! target_select(what)) {
    return false;
  }

  game->request_to_throw_item = what;

  return target_select(what);
}

void Thing::throw_at(Thingp what, Thingp target)
{
  TRACE_AND_INDENT();
  if (! what) {
    what = game->request_to_throw_item;
  }

  verify(what);
  if (! what) {
    err("Cannot throw null thing");
    return;
  }

  verify(what);
  if (! what) {
    err("Cannot throw at null target");
    return;
  }

  if (DISTANCE(mid_at.x, mid_at.y, target->mid_at.x, target->mid_at.y) > get_throw_distance()) {
    if (is_player()) {
      TOPCON("You cannot throw %s that far.", what->text_the().c_str());
    }
    return;
  }

  if (is_player()) {
    TOPCON("You throw %s.", what->text_the().c_str());
  }

  dbg("Thrown %s", what->to_string().c_str());
  what->move_to_immediately(target->mid_at);

  //
  // Potions for example are used when thrown. Chocolate frogs, no.
  //
  if (level->is_lava(target->mid_at.x, target->mid_at.y) || level->is_chasm(target->mid_at.x, target->mid_at.y)) {
    drop(what, target);

    what->location_check_forced();
  } else {
    if (what->is_used_when_thrown()) {
      used(what, target, true /* remove_after_use */);
    } else {
      drop(what, target);
    }
  }

  what->hide();

  {
    auto src   = (last_blit_tl + last_blit_br) / 2;
    auto dst   = (target->last_blit_tl + target->last_blit_br) / 2;
    auto sz    = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);
    auto delay = PARTICLE_SPEED_MS;

    if (is_player()) {
      //
      // So the player is visible above light
      //
      level->new_external_particle(what->id, src, dst, sz, delay, tile_index_to_tile(what->tile_curr), false,
                                   true /* make_visible_at_end */);
    } else {
      level->new_internal_particle(what->id, src, dst, sz, delay, tile_index_to_tile(what->tile_curr), false,
                                   true /* make_visible_at_end */);
    }
  }

  if (is_player()) {
    game->tick_begin("player threw an item");
  }

  if (game->state == Game::STATE_CHOOSING_TARGET) {
    game->change_state(Game::STATE_NORMAL);
  }
}
