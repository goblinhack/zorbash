//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::initial_charge_count(void)
{
  TRACE_NO_INDENT();
  return (tp()->charge_count());
}

////////////////////////////////////////////////////////////////////////////
// charge_count
////////////////////////////////////////////////////////////////////////////
int Thing::charge_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) { return (infop()->charge_count); }
  return 0;
}

int Thing::charge_count_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  if (is_player()) { game->set_request_to_remake_rightbar(); }
  return (infop()->charge_count = v);
}

int Thing::charge_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  if (is_player()) { game->set_request_to_remake_rightbar(); }
  return (infop()->charge_count -= v);
}

int Thing::charge_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  if (is_player()) { game->set_request_to_remake_rightbar(); }
  return (infop()->charge_count += v);
}

int Thing::charge_count_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  if (is_player()) { game->set_request_to_remake_rightbar(); }
  return (infop()->charge_count--);
}

int Thing::charge_count_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  if (is_player()) { game->set_request_to_remake_rightbar(); }
  return (infop()->charge_count++);
}
