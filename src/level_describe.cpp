//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_wid_thing_info.hpp"

void Level::describe(point p)
{
  TRACE_NO_INDENT();
  bool got_one_with_long_text = false;

  dbg("Level describe @%d,%d", p.x, p.y);
  TRACE_AND_INDENT();

  if (! player) {
    dbg2("Level describe @%d,%d; no, no player", p.x, p.y);
    return;
  }

  if (player->is_dead) {
    dbg2("Level describe @%d,%d; no, dead", p.x, p.y);
    return;
  }

  if (game->robot_mode) {
    dbg2("Level describe @%d,%d; no, robot mode", p.x, p.y);
    return;
  }

  if (is_starting) {
    dbg2("Level describe @%d,%d; no, starting", p.x, p.y);
    return;
  }

  if ((game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_ENCHANTING_ITEMS) ||
      (game->state == Game::STATE_SAVE_MENU) || (game->state == Game::STATE_LOAD_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_CHOOSING_SKILLS)) {
    dbg2("Level describe @%d,%d; no wrong state", p.x, p.y);
    return;
  }

  std::vector< Thingp > hover_over_things;
  hover_over = nullptr;

  FOR_ALL_THINGS_THAT_DO_STUFF(this, t, p.x, p.y)
  {
    int x = p.x;
    int y = p.y;
    IF_DEBUG2 { t->log("Active thing cand for describe"); }
    TRACE_AND_INDENT();

    //
    // We show the player info in the inventory, so skip it here.
    //
    if (t->is_player()) {
      continue;
    }

    //
    // Don't allow snooping of monsters we cannot see
    //
    if (! get(can_see_currently.can_see, x, y) && t->is_monst()) {
      IF_DEBUG2
      {
        //
        // Allow snooping in debug mode
        //
      }
      else
      {
        continue;
      }
    }

    if (! get(can_see_currently.can_see, x, y) && ! get(can_see_ever.can_see, x, y)) {
      TRACE_AND_INDENT();
      IF_DEBUG2
      {
        //
        // Allow snooping in debug mode
        //
      }
      else
      {
        continue;
      }
    }

    if (t->immediate_owner()) {
      IF_DEBUG2 { t->log("Ignore for describe, has owner"); }
      continue;
    }

    if (t->is_described_when_hovering_over()) {
      if (! t->text_description_short().empty() || ! t->text_description_long().empty()) {
        IF_DEBUG2 { t->log("Add to describe"); }
        got_one_with_long_text |= ! t->text_description_long().empty();
        push_back_if_unique(hover_over_things, t);
      } else {
        IF_DEBUG2 { t->log("Ignore for describe, no text"); }
      }
    } else {
      IF_DEBUG2 { t->log("Ignore for describe, not described"); }
    }

    if (! hover_over) {
      hover_over = t;
    }
  }
  FOR_ALL_THINGS_END()

  FOR_ALL_THINGS_THAT_INTERACT(this, t, p.x, p.y)
  {
    int x = p.x;
    int y = p.y;
    IF_DEBUG2 { t->log("Interesting thing cand for describe"); }
    TRACE_AND_INDENT();

    //
    // We show the player info in the inventory, so skip it here.
    //
    if (t->is_player()) {
      continue;
    }

    //
    // Don't allow snooping of monsters we cannot see
    //
    if (! get(can_see_currently.can_see, x, y) && t->is_monst()) {
      IF_DEBUG2
      {
        //
        // Allow snooping in debug mode
        //
      }
      else
      {
        continue;
      }
    }

    if (! get(can_see_currently.can_see, x, y) && ! get(can_see_ever.can_see, x, y)) {
      TRACE_AND_INDENT();
      IF_DEBUG2
      {
        //
        // Allow snooping in debug mode
        //
      }
      else
      {
        continue;
      }
    }

    //
    // Dead monst clog up the screen
    //
    if (t->is_monst() && t->is_dead) {
      IF_DEBUG2 { t->log("Ignore for describe, monst or dead"); }
      continue;
    }

    if (t->immediate_owner()) {
      IF_DEBUG2 { t->log("Ignore for describe, has owner"); }
      continue;
    }

    if (t->is_described_when_hovering_over()) {
      if (! t->text_description_short().empty() || ! t->text_description_long().empty()) {
        IF_DEBUG2 { t->log("Add to describe"); }
        got_one_with_long_text |= ! t->text_description_long().empty();
        push_back_if_unique(hover_over_things, t);
      } else {
        IF_DEBUG2 { t->log("Ignore for describe, no text"); }
      }
    } else {
      IF_DEBUG2 { t->log("Ignore for describe, not described"); }
    }

    if (! hover_over) {
      hover_over = t;
    }
  }
  FOR_ALL_THINGS_END()

  FOR_ALL_NON_INTERNAL_THINGS(this, t, p.x, p.y)
  {
    int x = p.x;
    int y = p.y;
    IF_DEBUG2 { t->log("All thing cand for describe"); }
    TRACE_AND_INDENT();

    //
    // We show the player info in the inventory, so skip it here.
    //
    if (t->is_player()) {
      continue;
    }

    //
    // Don't allow snooping of monsters we cannot see
    //
    if (! get(can_see_currently.can_see, x, y) && t->is_monst()) {
      IF_DEBUG2
      {
        //
        // Allow snooping in debug mode
        //
      }
      else
      {
        continue;
      }
    }

    if (! get(can_see_currently.can_see, x, y) && ! get(can_see_ever.can_see, x, y)) {
      TRACE_AND_INDENT();
      IF_DEBUG2
      {
        //
        // Allow snooping in debug mode
        //
      }
      else
      {
        continue;
      }
    }

    if (t->immediate_owner()) {
      IF_DEBUG2 { t->log("Ignore for describe, boring"); }
      continue;
    }

    //
    // Only show the player as fallback if we have nothing else
    //
    if (hover_over_things.size()) {
      //
      // Dead monst clog up the screen. Unless we have nothing else.
      //
      if (t->is_monst() && t->is_dead) {
        IF_DEBUG2 { t->log("Ignore for describe, showing something better"); }
        continue;
      }
    }

    if (t->is_described_when_hovering_over()) {
      if (! t->text_description_short().empty() || ! t->text_description_long().empty()) {
        got_one_with_long_text |= ! t->text_description_long().empty();
        IF_DEBUG2 { t->log("Add to describe"); }
        push_back_if_unique(hover_over_things, t);
      } else {
        IF_DEBUG2 { t->log("Ignore for describe, no text"); }
      }
    } else {
      IF_DEBUG2 { t->log("Ignore for describe, not described"); }
    }

    if (! hover_over) {
      hover_over = t;
    }
  }
  FOR_ALL_THINGS_END()

  if (! got_one_with_long_text) {
    dbg2("Describe @%d,%d; found nothing with long text", p.x, p.y);
  }

  dbg2("Describe @%d,%d; found %d things", p.x, p.y, (int) hover_over_things.size());

  if (! got_one_with_long_text || ! hover_over_things.size()) {
    //
    // If we found nothing, then check to see if we are already showing
    // something of interest and if so, keep it.
    //
    auto o = game->current_wid_thing_info;
    if (o) {
      dbg2("Currently describing %s", o->to_string().c_str());
      if (o->is_hidden) {
        dbg2("Currently describing %s; prefer me over current1", o->to_string().c_str());
      }

      //
      // If showing something under the player, then prefer
      // to keep showing that if nothing else.
      //
      if (o->curr_at == player->curr_at) {
        dbg2("Describe %s; prefer me over current2", o->to_string().c_str());
        return;
      }
    }

    if (wid_thing_info_window.size()) {
      auto o = wid_thing_info_window.front()->t;
      if (o) {
        dbg2("Currently describing %s", o->to_string().c_str());
        if (o->is_hidden) {
          dbg2("Describe %s; prefer me over current3", o->to_string().c_str());
          return;
        }

        if (o->curr_at == player->curr_at) {
          dbg2("Describe %s; prefer me over current4", o->to_string().c_str());
          return;
        }
      }
    }

    wid_thing_info_fini("describe");
  }

  if (hover_over_things.size() > 1) {
    dbg("Describe @%d,%d; found %d things", p.x, p.y, (int) hover_over_things.size());
    if (game->wid_thing_info_create_list(hover_over_things)) {
      if (hover_over_things.size() > 1) {
        auto        k = ::to_string(game->config.key_wait_or_collect);
        std::string text;

        if (player->curr_at == p) {
          if (k == ".") {
            text = "Multiple things here. Press %%fg=yellow$" + k + "%%fg=reset$ to collect.";
          } else {
            text = "Multiple things here. %%fg=yellow$" + k + "%%fg=reset$ to collect.";
          }
        } else {
          text = "Multiple things here.";
        }
        BOTCON("%s", text.c_str());
      }
    }
  } else if (hover_over_things.size()) {
    dbg("Describe @%d,%d; found thing", p.x, p.y);
    if (game->wid_thing_info_create_list(hover_over_things)) {
      if (hover_over_things.size() > 1) {
        auto        k = ::to_string(game->config.key_wait_or_collect);
        std::string text;
        if (player->curr_at == p) {
          if (k == ".") {
            text = "Something is here. Press %%fg=yellow$" + k + "%%fg=reset$ to collect.";
          } else {
            text = "Something is here. %%fg=yellow$" + k + "%%fg=reset$ to collect.";
          }
        } else {
          text = "Something is here.";
        }
        BOTCON("%s", text.c_str());
      }
    }
  }
}

void Level::describe(Thingp t)
{
  TRACE_NO_INDENT();

  if (! player) {
    return;
  }

  if (player->is_dead) {
    return;
  }

  if (game->robot_mode) {
    return;
  }

  if (is_starting) {
    return;
  }

  if (unlikely(! t)) {
    err("Null thing");
    return;
  }

  if (t->is_hidden) {
    return;
  }

  if (t->is_player()) {
    return;
  }

  dbg2("Describe %s", t->to_short_string().c_str());
  TRACE_AND_INDENT();

  if ((game->state == Game::STATE_INVENTORY) || (game->state == Game::STATE_OPTIONS_FOR_ITEM_MENU) ||
      (game->state == Game::STATE_COLLECTING_ITEMS) || (game->state == Game::STATE_SAVE_MENU) ||
      (game->state == Game::STATE_LOAD_MENU) || (game->state == Game::STATE_QUIT_MENU) ||
      (game->state == Game::STATE_KEYBOARD_MENU) || (game->state == Game::STATE_ENCHANTING_ITEMS)) {
    dbg2("Describe %s; no wrong state", t->to_short_string().c_str());
    return;
  }

  if (! t->is_described_when_hovering_over()) {
    dbg2("Describe %s; no not described", t->to_short_string().c_str());
    return;
  }

  //
  // If we're trying to show the player, then don't do that
  // if we're showing something more interesting from the
  // inventory.
  //
  auto o = game->current_wid_thing_info;
  if (o) {
    dbg2("Currently Describe %s", o->to_string().c_str());
    if (o->is_hidden) {
      dbg2("Currently Describe %s; prefer me over current5", o->to_string().c_str());
    }

    //
    // If showing something under the player, then prefer
    // to keep showing that if nothing else.
    //
    if (o->curr_at == player->curr_at) {
      dbg2("Describe %s; prefer me over current6", o->to_string().c_str());
      return;
    }
  }

  if (wid_thing_info_window.size()) {
    auto o = wid_thing_info_window.front()->t;
    if (o) {
      dbg2("Describe %s", o->to_string().c_str());
      if (o->is_hidden) {
        dbg2("Describe %s; prefer me over current7", o->to_string().c_str());
        return;
      }

      if (o->curr_at == player->curr_at) {
        dbg2("Describe %s; prefer me over current8", o->to_string().c_str());
        return;
      }
    }
  }

  wid_thing_info_fini("describe2");

  dbg2("Describe %s?", t->to_short_string().c_str());
  if (! t->text_description_short().empty() || ! t->text_description_long().empty()) {
    dbg2("Describe %s; has no text", t->to_short_string().c_str());
    t->show_botcon_description();
    return;
  }

  std::vector< Thingp > hover_over_things;
  hover_over_things.push_back(t);
  game->wid_thing_info_create_list(hover_over_things);
}
