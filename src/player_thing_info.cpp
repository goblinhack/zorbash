//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"
#include "my_sdl_event.hpp"
#include "my_thing.hpp"

bool Thing::player_is_ready_for_popups(void)
{
  verify(MTYPE_THING, this);

  if (! level) {
    dbg("Not ready for thing info; no level");
    return false;
  }

  //
  // While fading in out, we don't want popups.
  //
  if (! g_opt_ascii && level->ts_fade_out_begin) {
    dbg("Not ready for thing info; fading out");
    return false;
  }

  if (! g_opt_ascii && level->ts_fade_in_begin) {
    dbg("Not ready for thing info; fading in");
    return false;
  }

  //
  // If the player has done something like moved the mouse, or pressed an inventory shortcut, then allow the thing
  // info.
  //
  if (! sdl.event_count) {
    //
    // This is really for ascii mode, as there is no fade in/out.
    //
    if (level->ts_entered && ! time_have_x_tenths_passed_since(10, level->ts_entered)) {
      dbg("Not ready for thing info; changing level");
      return false;
    }

    //
    // While changing level, popups are confusing
    //
    if (is_changing_level) {
      dbg("Not ready for thing info; changing level");
      return false;
    }

    //
    // No popups before the first tick
    //
    if (game->tick_current <= 1) {
      if (game->tick_requested.empty()) {
        if ((time_ms() - game->tick_begin_ms) < 50) {
          if (! game->cursor_moved) {
            dbg("Not ready for thing info: too soon %ums", time_ms() - game->tick_begin_ms);
            return false;
          }
        }
      }
    }

    if (! level->player) {
      dbg("Not ready for thing info; no level");
      return false;
    }

    if (! is_player()) {
      if (level->player->is_dead || level->player->is_dying) {
        dbg("Not ready for thing info; dead");
        return false;
      }
    }

    if (level->is_starting || level->is_being_destroyed) {
      dbg("Not ready for thing info; level starting");
      return false;
    }
  }

  return true;
}
