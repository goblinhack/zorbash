//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::confused_tick(void)
{
  if (confused_count() > 0) {
    confused_count_decr();
  }
  confused_update();
}

void Thing::confused_update(void)
{
  if (is_player()) {
    if (confused_count()) {
      debuff_add_if_not_found(tp_find("debuff_status_confused"));
      game->set_request_to_remake_rightbar();
    } else {
      debuff_remove(tp_find("debuff_status_confused"));
      game->set_request_to_remake_rightbar();
    }
  }

  if (confused_count()) {
    clear_move_path("confusion");
    dbg("Is confused");
  }
}

int Thing::confused_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->confused_count);
  }
  return 0;
}

int Thing::confused_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  confused_update();
  return (aip()->confused_count = v);
}

int Thing::confused_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->confused_count -= v;
  if (aip()->confused_count < 0) {
    aip()->confused_count = 0;
  }
  confused_update();
  return aip()->confused_count;
}

int Thing::confused_count_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_immune_to_confusion()) {
    return 0;
  }
  new_aip();
  aip()->confused_count += v;
  if (aip()->confused_count < 0) {
    aip()->confused_count = 0;
  }
  confused_update();
  return aip()->confused_count;
}

int Thing::confused_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->confused_count--;
  if (aip()->confused_count < 0) {
    aip()->confused_count = 0;
  }
  confused_update();
  return aip()->confused_count;
}

int Thing::confused_count_incr(void)
{
  TRACE_NO_INDENT();
  if (is_immune_to_confusion()) {
    return 0;
  }
  new_aip();
  aip()->confused_count++;
  if (aip()->confused_count < 0) {
    aip()->confused_count = 0;
  }
  confused_update();
  return aip()->confused_count;
}
