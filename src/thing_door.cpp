//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_globals.h"
#include "my_game.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_string.h"
#include "my_thing_template.h"
#include "my_python.h"

bool Thing::open_door (Thingp it)
{_
  if (!is_monst() && !is_player()) {
    return false;
  }

  if (is_on_fire()) {
    if (!it->is_on_fire()) {
      if (is_player()) {
        TOPCON("The door is ablaze!");
      }
      it->set_on_fire("opened flaming door");
    }
  }

  if (!it->is_door()) {
    return false;
  }

  if (it->is_open) {
    return false;
  }

  if (it->is_dead) {
    return false;
  }

  if (get_keys()) {
    decr_keys();
    IF_DEBUG1 {
      it->log("Open");
    }
    it->level_pop();
    it->is_open = true;
    it->level_push();

    if (is_player()) {
      TOPCON("The door creaks open.");
    }

    it->on_open();
    update_light();
    level->dmap_to_player_update();
    return true;
  }

  if (is_player()) {
    static uint32_t last_told_when;
    if (!last_told_when || (game->tick_current >= last_told_when + 10)) {
      TOPCON("You need a key.");
    }
    last_told_when = game->tick_current;
  }

  return false;
}

bool Thing::close_door (Thingp it)
{_
  if (is_on_fire()) {
    if (!it->is_on_fire()) {
      if (is_player()) {
        TOPCON("The door is ablaze!");
      }
      it->set_on_fire("closed flaming door");
    }
  }

  if (!it->is_door()) {
    return false;
  }

  if (!it->is_open) {
    return false;
  }

  if (it->is_dead) {
    return false;
  }

  IF_DEBUG1 {
    it->log("Close");
  }
  it->level_pop();
  it->is_open = false;
  it->level_push();

  if (is_player()) {
    TOPCON("The door creaks open.");
  }

  update_light();
  level->dmap_to_player_update();
  return true;
}
