//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <math.h>

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_level.h"
#include "my_thing.h"

bool Thing::throw_item_choose_target (Thingp item)
{_
  dbg("Trying to throw: %s", item->to_string().c_str());

  if (!item->is_throwable()) {
    if (is_player()) {
      TOPCON("I don't know how to throw %s.", item->text_the().c_str());
      game->tick_begin("player tried to throw something they could not");
    }
    return false;
  }

  if (!target_select(item)) {
    return false;
  }

  game->request_to_throw_item = item;

  return target_select(item);
}

void Thing::throw_at (Thingp item, Thingp target)
{_
  if (!item) {
    item = game->request_to_throw_item;
  }

  if (!item) {
    return;
  }

  if (DISTANCE(mid_at.x, mid_at.y, target->mid_at.x, target->mid_at.y) >
    get_throw_distance()) {

    if (is_player()) {
      TOPCON("You cannot throw %s that far.", item->text_the().c_str());
    }
    return;
  }

  if (is_player()) {
    TOPCON("You throw %s.", item->text_the().c_str());
  }

  dbg("Thrown %s", item->to_string().c_str());
  item->move_to_immediately(target->mid_at);

  //
  // Potions for example are used when thrown. Chocolate frogs, no.
  //
  if (level->is_lava(target->mid_at.x, target->mid_at.y) ||
    level->is_chasm(target->mid_at.x, target->mid_at.y)) {
    drop(item, target);

    item->location_check_forced();
  } else {
    if (item->is_used_when_thrown()) {
      used(item, target, true /* remove_after_use */);
    } else {
      drop(item, target);
    }
  }

  item->hide();

  {
    auto src = (last_blit_tl + last_blit_br) / 2;
    auto dst = (target->last_blit_tl + target->last_blit_br) / 2;
    auto sz = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);
    auto delay = PARTICLE_SPEED_MS;

    if (is_player()) {
      //
      // So the player is visible above light
      //
      level->new_external_particle(item->id, src, dst, sz, delay,
                     tile_index_to_tile(item->tile_curr),
                     false,
                     true /* make_visible_at_end */);
    } else {
      level->new_internal_particle(item->id, src, dst, sz, delay,
                     tile_index_to_tile(item->tile_curr),
                     false,
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
