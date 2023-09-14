//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::paralysis_tick(void)
{
  if (paralysis_count() > 0) {
    paralysis_count_decr();
  }
  paralysis_update();
}

void Thing::paralysis_update(void)
{
  if (is_player()) {
    if (paralysis_count()) {
      debuff_add_if_not_found(tp_find("debuff_status_paralysis"));
      game->set_request_to_remake_rightbar();
    } else {
      debuff_remove(tp_find("debuff_status_paralysis"));
      game->set_request_to_remake_rightbar();
    }
  }

  if (paralysis_count()) {
    clear_move_path("paralysis");
    dbg("Is paralysed");
  }
}

int Thing::paralysis_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->paralysis_count);
  }
  return 0;
}

int Thing::paralysis_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  paralysis_update();
  return (aip()->paralysis_count = v);
}

int Thing::paralysis_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->paralysis_count -= v;
  if (aip()->paralysis_count < 0) {
    aip()->paralysis_count = 0;
  }
  paralysis_update();
  return aip()->paralysis_count;
}

int Thing::paralysis_count_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_immune_to_paralysis()) {
    return 0;
  }
  new_aip();
  aip()->paralysis_count += v;
  if (aip()->paralysis_count < 0) {
    aip()->paralysis_count = 0;
  }
  paralysis_update();
  return aip()->paralysis_count;
}

int Thing::paralysis_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->paralysis_count--;
  if (aip()->paralysis_count < 0) {
    aip()->paralysis_count = 0;
  }
  paralysis_update();
  return aip()->paralysis_count;
}

int Thing::paralysis_count_incr(void)
{
  TRACE_NO_INDENT();
  if (is_immune_to_paralysis()) {
    return 0;
  }
  new_aip();
  aip()->paralysis_count++;
  if (aip()->paralysis_count < 0) {
    aip()->paralysis_count = 0;
  }
  paralysis_update();
  return aip()->paralysis_count;
}
