//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

////////////////////////////////////////////////////////////////////////////
// tick_last_did_something
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_did_something(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) {
    return (infop()->tick_last_did_something);
  }
  return 0;
}

uint32_t Thing::tick_last_did_something_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something = v);
}

uint32_t Thing::tick_last_did_something_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something -= v);
}

uint32_t Thing::tick_last_did_something_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something += v);
}

uint32_t Thing::tick_last_did_something_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something--);
}

uint32_t Thing::tick_last_did_something_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_dropped
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_dropped(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) {
    return (infop()->tick_last_dropped);
  }
  return 0;
}

uint32_t Thing::tick_last_dropped_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped = v);
}

uint32_t Thing::tick_last_dropped_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped -= v);
}

uint32_t Thing::tick_last_dropped_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped += v);
}

uint32_t Thing::tick_last_dropped_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped--);
}

uint32_t Thing::tick_last_dropped_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_location_check
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_location_check(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_location_check);
  }
  return 0;
}

uint32_t Thing::tick_last_location_check_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check = v);
}

uint32_t Thing::tick_last_location_check_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check -= v);
}

uint32_t Thing::tick_last_location_check_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check += v);
}

uint32_t Thing::tick_last_location_check_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check--);
}

uint32_t Thing::tick_last_location_check_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_escape
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_escape(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_escape);
  }
  return 0;
}

uint32_t Thing::tick_last_escape_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape = v);
}

uint32_t Thing::tick_last_escape_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape -= v);
}

uint32_t Thing::tick_last_escape_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape += v);
}

uint32_t Thing::tick_last_escape_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape--);
}

uint32_t Thing::tick_last_escape_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_level_change
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_level_change(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_level_change);
  }
  return 0;
}

uint32_t Thing::tick_last_level_change_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change = v);
}

uint32_t Thing::tick_last_level_change_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change -= v);
}

uint32_t Thing::tick_last_level_change_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change += v);
}

uint32_t Thing::tick_last_level_change_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change--);
}

uint32_t Thing::tick_last_level_change_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_was_attacked
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_i_was_attacked(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_i_was_attacked);
  }
  return 0;
}

uint32_t Thing::tick_last_i_was_attacked_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked = v);
}

uint32_t Thing::tick_last_i_was_attacked_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked -= v);
}

uint32_t Thing::tick_last_i_was_attacked_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked += v);
}

uint32_t Thing::tick_last_i_was_attacked_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked--);
}

uint32_t Thing::tick_last_i_was_attacked_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_attacked
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_i_attacked(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_i_attacked);
  }
  return 0;
}

uint32_t Thing::tick_last_i_attacked_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked = v);
}

uint32_t Thing::tick_last_i_attacked_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked -= v);
}

uint32_t Thing::tick_last_i_attacked_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked += v);
}

uint32_t Thing::tick_last_i_attacked_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked--);
}

uint32_t Thing::tick_last_i_attacked_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_tried_to_attack
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::tick_last_i_tried_to_attack(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->tick_last_i_tried_to_attack);
  }
  return 0;
}

uint32_t Thing::tick_last_i_tried_to_attack_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack = v);
}

uint32_t Thing::tick_last_i_tried_to_attack_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack -= v);
}

uint32_t Thing::tick_last_i_tried_to_attack_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack += v);
}

uint32_t Thing::tick_last_i_tried_to_attack_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack--);
}

uint32_t Thing::tick_last_i_tried_to_attack_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack++);
}

////////////////////////////////////////////////////////////////////////////
// where_i_dropped_an_item_last
////////////////////////////////////////////////////////////////////////////
point Thing::where_i_dropped_an_item_last_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (itemsp()->where_i_dropped_an_item_last);
  }
  return (point(-1, -1));
}

point Thing::where_i_dropped_an_item_last_set(point v)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    new_itemsp();
    return (itemsp()->where_i_dropped_an_item_last = v);
  }
  return (point(-1, -1));
}

////////////////////////////////////////////////////////////////////////////
// where_i_failed_to_collect_last
////////////////////////////////////////////////////////////////////////////
point Thing::where_i_failed_to_collect_last_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (itemsp()->where_i_failed_to_collect_last);
  }
  return (point(-1, -1));
}

point Thing::where_i_failed_to_collect_last_set(point v)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    new_itemsp();
    return (itemsp()->where_i_failed_to_collect_last = v);
  }
  return (point(-1, -1));
}
