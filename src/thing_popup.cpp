//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::popup(std::string const &m)
{
  if (! is_visible_to_player) {
    dbg("Popup: %s not visible to player", m.c_str());
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

  //
  // Stop msgs piling up in the same tick
  //
  // con("POPUP: %s", m.c_str());

  //
  // Make sure only one popup per thing
  //
  for (auto k : game->popups) {
    auto p = k.first;
    if (p->infop()->popup_owner_id == id) {
      p->dead("too many popups");
    }
  }

  // dbg("Popup: %s delta %d,%d", m.c_str(), dx, dy);
  auto msg = level->thing_new("msg", curr_at);
  msg->msg_set(m);
  msg->fadeup(6.0, 0.01, 2500);
  msg->infop()->popup_owner_id = id;
  game->popups[ msg ]          = true;
}
