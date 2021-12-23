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

bool Thing::projectile_choose_target(Thingp item)
{
  TRACE_AND_INDENT();
  dbg("Trying to target a projectile with: %s", item->to_short_string().c_str());

  if (is_monst() || (game->robot_mode && is_player())) {
    auto victim = get_best_visible_target();
    if (! victim) {
      dbg("No victim found");
      return false;
    }

    log("Chosen target: %s", victim->to_short_string().c_str());
    TRACE_AND_INDENT();

    used(item, victim, true);

    if (! item->projectile_name().empty()) {
      projectile_fire_at(item->projectile_name(), victim);
    } else {
      err("Unknown projectile: %s.", item->text_the().c_str());
      return false;
    }

    //
    // Get the damage from the enchanted wand, so the blast inflicts that damage.
    //
    set_current_damage(item->get_current_damage());
    return true;
  }

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

  auto projectile = level->thing_new(projectile_name, curr_at);
  if (! projectile) {
    return nullptr;
  }

  projectile->set_owner(this);
  projectile->move_to_immediately(target->curr_at);

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
