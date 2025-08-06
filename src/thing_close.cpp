//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::on_close(void)
{
  auto on_close = tp()->on_close_do();
  if (std::empty(on_close)) {
    return;
  }

  auto t = split_tokens(on_close, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_close call [%s] expected mod:function, got %d elems", on_close.c_str(), (int) on_close.size());
  }
}

bool Thing::close(Thingp it)
{
  TRACE_NO_INDENT();

  if (it->is_door()) {
    return close_door(it);
  }

  if (! is_monst() && ! is_player()) {
    return false;
  }

  if (! it->is_openable()) {
    return false;
  }

  if (! it->is_open) {
    return false;
  }

  if (it->is_dead) {
    return false;
  }

  IF_DEBUG1 { it->log("Close"); }

  it->level_pop();
  it->is_open = false;
  it->level_push();

  it->on_close();
  update_light();
  level->request_dmap_to_player_update = true;

  level->sound_sources_incr(it->curr_at.x, it->curr_at.y, it->noise_on_open_or_close());

  return true;
}

bool Thing::close(void)
{
  TRACE_NO_INDENT();

  if (is_door()) {
    return close_door(this);
  }

  if (! is_openable()) {
    return false;
  }

  if (! is_open) {
    return false;
  }

  if (is_dead) {
    return false;
  }

  IF_DEBUG1 { log("Close"); }

  level_pop();
  is_open = false;
  level_push();

  on_close();
  update_light();
  level->request_dmap_to_player_update = true;

  level->sound_sources_incr(curr_at.x, curr_at.y, noise_on_open_or_close());

  return true;
}
