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

void Thing::entranced_tick(void)
{
  if (entranced_count() > 0) {
    entranced_count_decr();
  }
  entranced_update();
}

void Thing::entranced_update(void)
{
  if (is_player()) {
    if (entranced_count()) {
      debuff_add_if_not_found(tp_find("debuff_status_entranced"));
      game->set_request_to_remake_rightbar();
    } else {
      debuff_remove(tp_find("debuff_status_entranced"));
      game->set_request_to_remake_rightbar();
    }
  }

  if (entranced_count()) {
    clear_move_path("entranced");
    dbg("Is entranced");
  }
}

int Thing::entranced_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->entranced_count);
  }
  return 0;
}

int Thing::entranced_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  entranced_update();
  return (aip()->entranced_count = v);
}

int Thing::entranced_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->entranced_count -= v;
  if (aip()->entranced_count < 0) {
    aip()->entranced_count = 0;
  }
  entranced_update();
  return aip()->entranced_count;
}

int Thing::entranced_count_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_immune_to_entrancement()) {
    return 0;
  }
  new_aip();
  aip()->entranced_count += v;
  if (aip()->entranced_count < 0) {
    aip()->entranced_count = 0;
  }
  entranced_update();
  return aip()->entranced_count;
}

int Thing::entranced_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->entranced_count--;
  if (aip()->entranced_count < 0) {
    aip()->entranced_count = 0;
  }
  entranced_update();
  return aip()->entranced_count;
}

int Thing::entranced_count_incr(void)
{
  TRACE_NO_INDENT();
  if (is_immune_to_entrancement()) {
    return 0;
  }
  new_aip();
  aip()->entranced_count++;
  if (aip()->entranced_count < 0) {
    aip()->entranced_count = 0;
  }
  entranced_update();
  return aip()->entranced_count;
}
