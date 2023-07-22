//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"

////////////////////////////////////////////////////////////////////////////
// tick_last_did_something
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_did_something(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) { return (infop()->tick_last_did_something); }
  return 0;
}

int Thing::tick_last_did_something_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something = v);
}

int Thing::tick_last_did_something_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something -= v);
}

int Thing::tick_last_did_something_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something += v);
}

int Thing::tick_last_did_something_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something--);
}

int Thing::tick_last_did_something_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_did_something++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_seen_by_player
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_seen_by_player(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) { return (infop()->tick_last_seen_by_player); }
  return 0;
}

int Thing::tick_last_seen_by_player_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_seen_by_player = v);
}

int Thing::tick_last_seen_by_player_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_seen_by_player -= v);
}

int Thing::tick_last_seen_by_player_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_seen_by_player += v);
}

int Thing::tick_last_seen_by_player_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_seen_by_player--);
}

int Thing::tick_last_seen_by_player_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_seen_by_player++);
}

////////////////////////////////////////////////////////////////////////////
// tick_born
////////////////////////////////////////////////////////////////////////////
int Thing::tick_born(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) { return (infop()->tick_born); }
  return 0;
}

int Thing::tick_born_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_born = v);
}

int Thing::tick_born_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_born -= v);
}

int Thing::tick_born_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_born += v);
}

int Thing::tick_born_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_born--);
}

int Thing::tick_born_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_born++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_dropped
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_dropped(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) { return (infop()->tick_last_dropped); }
  return 0;
}

int Thing::tick_last_dropped_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped = v);
}

int Thing::tick_last_dropped_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped -= v);
}

int Thing::tick_last_dropped_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped += v);
}

int Thing::tick_last_dropped_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped--);
}

int Thing::tick_last_dropped_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_dropped++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_teleported
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_teleported(void)
{
  TRACE_NO_INDENT();

  if (maybe_infop()) { return (infop()->tick_last_teleported); }
  return 0;
}

int Thing::tick_last_teleported_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_teleported = v);
}

int Thing::tick_last_teleported_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_teleported -= v);
}

int Thing::tick_last_teleported_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_teleported += v);
}

int Thing::tick_last_teleported_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_teleported--);
}

int Thing::tick_last_teleported_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_teleported++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_location_check
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_location_check(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_location_check); }
  return 0;
}

int Thing::tick_last_location_check_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check = v);
}

int Thing::tick_last_location_check_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check -= v);
}

int Thing::tick_last_location_check_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check += v);
}

int Thing::tick_last_location_check_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check--);
}

int Thing::tick_last_location_check_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_location_check++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_escape
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_escape(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_escape); }
  return 0;
}

int Thing::tick_last_escape_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape = v);
}

int Thing::tick_last_escape_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape -= v);
}

int Thing::tick_last_escape_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape += v);
}

int Thing::tick_last_escape_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape--);
}

int Thing::tick_last_escape_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_escape++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_level_change
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_level_change(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_level_change); }
  return 0;
}

int Thing::tick_last_level_change_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change = v);
}

int Thing::tick_last_level_change_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change -= v);
}

int Thing::tick_last_level_change_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change += v);
}

int Thing::tick_last_level_change_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change--);
}

int Thing::tick_last_level_change_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_level_change++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_was_attacked
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_i_was_attacked(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_i_was_attacked); }
  return 0;
}

int Thing::tick_last_i_was_attacked_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked = v);
}

int Thing::tick_last_i_was_attacked_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked -= v);
}

int Thing::tick_last_i_was_attacked_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked += v);
}

int Thing::tick_last_i_was_attacked_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked--);
}

int Thing::tick_last_i_was_attacked_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_was_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_attacked
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_i_attacked(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_i_attacked); }
  return 0;
}

int Thing::tick_last_i_attacked_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked = v);
}

int Thing::tick_last_i_attacked_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked -= v);
}

int Thing::tick_last_i_attacked_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked += v);
}

int Thing::tick_last_i_attacked_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked--);
}

int Thing::tick_last_i_attacked_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_i_tried_to_attack
////////////////////////////////////////////////////////////////////////////
int Thing::tick_last_i_tried_to_attack(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->tick_last_i_tried_to_attack); }
  return 0;
}

int Thing::tick_last_i_tried_to_attack_set(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack = v);
}

int Thing::tick_last_i_tried_to_attack_decr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack -= v);
}

int Thing::tick_last_i_tried_to_attack_incr(uint32_t v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack += v);
}

int Thing::tick_last_i_tried_to_attack_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->tick_last_i_tried_to_attack--);
}

int Thing::tick_last_i_tried_to_attack_incr(void)
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
  if (maybe_itemsp()) { return (itemsp()->where_i_dropped_an_item_last); }
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
  if (maybe_itemsp()) { return (itemsp()->where_i_failed_to_collect_last); }
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
