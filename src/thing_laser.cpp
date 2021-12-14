//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_level.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

bool Thing::laser_choose_target(Thingp item)
{
  TRACE_AND_INDENT();
  dbg("Trying to target a laser with: %s", item->to_string().c_str());

  if (! target_select(item)) {
    return false;
  }

  game->request_to_fire_item = item;

  return target_select(item);
}

Thingp Thing::laser_fire_at(const std::string &laser_name, Thingp target)
{
  TRACE_AND_INDENT();
  if (laser_name == "") {
    die("No laser name");
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    return nullptr;
  }

  if (! end.x && ! end.y) {
    return nullptr;
  }

  auto laser = level->thing_new(laser_name, target->curr_at, this);
  if (! laser) {
    return nullptr;
  }

  dbg("Firing named laser with: %s at %s", laser->to_string().c_str(), target->to_string().c_str());

  if (! laser->is_laser()) {
    if (is_player()) {
      TOPCON("I don't know how to zap %s.", laser->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
    return nullptr;
  }

  if (is_player()) {
    game->tick_begin("player zapped " + laser->text_the());
    game->change_state(Game::STATE_NORMAL);
  }

  level->new_laser(laser->id, start, end, game->current_move_speed);

  on_use(laser, target);

  return laser;
}
