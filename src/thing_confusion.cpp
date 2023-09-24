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

void Thing::confusion_tick(void)
{
  if (confusion_count() > 0) {
    confusion_count_decr();
  }
  confusion_update();
}

void Thing::confusion_update(void)
{
  if (is_player()) {
    if (confusion_count()) {
      debuff_add_if_not_found(tp_find("debuff_status_confusion"));
      game->set_request_to_remake_rightbar();
    } else {
      debuff_remove(tp_find("debuff_status_confusion"));
      game->set_request_to_remake_rightbar();
    }
  }

  if (confusion_count()) {
    clear_move_path("confusion");
    dbg("Is confused");
  }
}

int Thing::confusion_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->confusion_count);
  }
  return 0;
}

int Thing::confusion_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  confusion_update();
  return (aip()->confusion_count = v);
}

int Thing::confusion_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->confusion_count -= v;
  if (aip()->confusion_count < 0) {
    aip()->confusion_count = 0;
  }
  confusion_update();
  return aip()->confusion_count;
}

int Thing::confusion_count_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_immune_to_confusion()) {
    return 0;
  }
  new_aip();
  aip()->confusion_count += v;
  if (aip()->confusion_count < 0) {
    aip()->confusion_count = 0;
  }
  confusion_update();
  return aip()->confusion_count;
}

int Thing::confusion_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->confusion_count--;
  if (aip()->confusion_count < 0) {
    aip()->confusion_count = 0;
  }
  confusion_update();
  return aip()->confusion_count;
}

int Thing::confusion_count_incr(void)
{
  TRACE_NO_INDENT();
  if (is_immune_to_confusion()) {
    return 0;
  }
  new_aip();
  aip()->confusion_count++;
  if (aip()->confusion_count < 0) {
    aip()->confusion_count = 0;
  }
  confusion_update();
  return aip()->confusion_count;
}
