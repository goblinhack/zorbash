//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::on_open(void)
{
  auto on_open = tp()->on_open_do();
  if (std::empty(on_open)) {
    return;
  }

  auto t = split_tokens(on_open, '.');
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
    ERR("Bad on_open call [%s] expected mod:function, got %d elems", on_open.c_str(), (int) on_open.size());
  }
}

bool Thing::open(Thingp it)
{
  TRACE_NO_INDENT();

  if (it->is_door()) {
    return open_door(it);
  }

  if (! is_monst() && ! is_player()) {
    return false;
  }

  if (! it->is_openable()) {
    return false;
  }

  if (it->is_open) {
    return false;
  }

  if (it->is_dead) {
    return false;
  }

  IF_DEBUG1 { it->log("Open"); }

  it->level_pop();
  it->is_open = true;
  it->level_push();

  it->on_open();
  update_light();
  level->request_dmap_to_player_update = true;

  level->sound_sources_incr(it->curr_at.x, it->curr_at.y, it->noise_on_open_or_close());

  return true;
}

bool Thing::open(void)
{
  TRACE_NO_INDENT();

  if (is_door()) {
    return open_door(this);
  }

  if (! is_openable()) {
    return false;
  }

  if (is_open) {
    return false;
  }

  if (is_dead) {
    return false;
  }

  IF_DEBUG1 { log("Open"); }

  level_pop();
  is_open = true;
  level_push();

  on_open();
  update_light();
  level->request_dmap_to_player_update = true;

  level->sound_sources_incr(curr_at.x, curr_at.y, noise_on_open_or_close());

  return true;
}

const std::string &Thing::on_open_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_open_do());
}
