//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.h"
#include "my_globals.h"
#include "my_level.h"
#include "my_main.h"
#include "my_sys.h"
#include "my_thing.h"
#include "my_tile.h"

bool Thing::projectile_choose_target(Thingp item)
{
  TRACE_AND_INDENT();
  dbg("Trying to target a projectile with: %s", item->to_string().c_str());

  if (! target_select(item)) {
    return false;
  }

  game->request_to_fire_item = item;

  return target_select(item);
}

Thingp Thing::projectile_fire_at(const std::string &projectile_name, Thingp target)
{
  TRACE_AND_INDENT();
  if (projectile_name == "") {
    die("No projectile name");
  }

  auto start = last_blit_at;
  auto end   = target->last_blit_at;

  if (! start.x && ! start.y) {
    return nullptr;
  }

  if (! end.x && ! end.y) {
    return nullptr;
  }

  auto projectile = level->thing_new(projectile_name, mid_at);
  if (! projectile) {
    return nullptr;
  }

  projectile->set_owner(this);
  projectile->move_to_immediately(target->mid_at);

  dbg("Firing named projectile with: %s at %s", projectile->to_string().c_str(), target->to_string().c_str());

  if (! projectile->is_projectile()) {
    if (is_player()) {
      TOPCON("I don't know how to fire %s.", projectile->text_the().c_str());
      game->tick_begin("player tried to use something they could not");
    }
    return nullptr;
  }

  if (is_player()) {
    game->tick_begin("player fired " + projectile->text_the());
    game->change_state(Game::STATE_NORMAL);
  }

  level->new_projectile(projectile->id, start, end, 200);

  on_use(projectile, target);

  return projectile;
}
