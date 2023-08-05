//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"

void Thing::popup(std::string const &m)
{
  if (! is_visible_to_player) {
    dbg("Popup: %s not visible to player", m.c_str());
    return;
  }

  if (! game->level) {
    return;
  }

  auto player = game->level->player;
  if (! player) {
    return;
  }

  //
  // Check we're on the same level
  //
  if (player->level != level) {
    return;
  }

  if (level->is_starting) {
    return;
  }

  //
  // Get the top owner as that will be the popup owner. We keep track
  // of who created the popup so we can avoid > 1 popup per thing which
  // just makes things hard to read.
  //
  auto top_o = top_owner();
  if (top_o) {
    top_o->popup(m);
    return;
  }

  auto msg = level->thing_new("msg", curr_at);
  if (! msg) {
    return;
  }

  msg->msg_set(m);
  msg->fadeup(8.0, 0.02, 3000);
  msg->infop()->popup_owner_id = id;

  //
  // Walk all current popups and place this new popup so it does not overlap
  // any other in the vertical plane
  //
  while (true) {
    Tilep tile = {};
    point blit_tl, blit_br;

    if (! msg->map_offset_coords_get(blit_tl, blit_br, tile, false)) {
      break;
    }

    bool overlaps = {};
    for (auto existing_msg : game->popups) {

      last_blit_tl = existing_msg->last_blit_tl;
      last_blit_br = existing_msg->last_blit_tl + point(0, UI_FONT_SMALL_HEIGHT);

      if (last_blit_tl == point(0, 0) && (last_blit_br == point(0, 0))) {
        existing_msg->map_offset_coords_get(last_blit_tl, last_blit_br, tile, false);
        last_blit_br = existing_msg->last_blit_tl + point(0, UI_FONT_SMALL_HEIGHT);
      }

      if ((last_blit_tl.y >= blit_tl.y) && (last_blit_tl.y <= blit_br.y)) {
        overlaps = true;
        break;
      }
      if ((last_blit_br.y >= blit_tl.y) && (last_blit_br.y <= blit_br.y)) {
        overlaps = true;
        break;
      }
    }

    if (! overlaps) {
      //
      // No overlap with existing messages
      //
      break;
    }

    //
    // Try again, but with a bit of an offset to hopefully not overlap
    //
    msg->blit_offset.y += UI_FONT_SMALL_HEIGHT;
  }

  game->popups.push_front(msg);

  log("POPUP: %s", m.c_str());
}
