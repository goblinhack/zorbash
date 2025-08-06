//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::blinded_tick(void)
{
  if (blinded_count() > 0) {
    blinded_count_decr();
  }
  blinded_update();
}

void Thing::blinded_update(void)
{
  if (is_player()) {
    if (blinded_count()) {
      debuff_add_if_not_found(tp_find("debuff_status_blinded"));
      game->set_request_to_remake_rightbar();
    } else {
      debuff_remove(tp_find("debuff_status_blinded"));
      game->set_request_to_remake_rightbar();
    }
  }

  if (blinded_count()) {
    dbg("Is blinded");
  }
}

int Thing::blinded_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->blinded_count);
  }
  return 0;
}

int Thing::blinded_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  blinded_update();
  return (aip()->blinded_count = v);
}

int Thing::blinded_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->blinded_count -= v;
  if (aip()->blinded_count < 0) {
    aip()->blinded_count = 0;
  }
  blinded_update();
  return aip()->blinded_count;
}

int Thing::blinded_count_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_immune_to_blinding()) {
    return 0;
  }
  new_aip();
  aip()->blinded_count += v;
  if (aip()->blinded_count < 0) {
    aip()->blinded_count = 0;
  }
  blinded_update();
  return aip()->blinded_count;
}

int Thing::blinded_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->blinded_count--;
  if (aip()->blinded_count < 0) {
    aip()->blinded_count = 0;
  }
  blinded_update();
  return aip()->blinded_count;
}

int Thing::blinded_count_incr(void)
{
  TRACE_NO_INDENT();
  if (is_immune_to_blinding()) {
    return 0;
  }
  new_aip();
  aip()->blinded_count++;
  if (aip()->blinded_count < 0) {
    aip()->blinded_count = 0;
  }
  blinded_update();
  return aip()->blinded_count;
}
