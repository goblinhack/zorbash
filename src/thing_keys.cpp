#include "my_game.hpp"
#include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
// REMOVED #include "my_python.hpp"
// REMOVED #include "my_string.hpp"
#include "my_thing.hpp"

////////////////////////////////////////////////////////////////////////////
// keys
////////////////////////////////////////////////////////////////////////////
int Thing::keys(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->keys);
  }
  return 0;
}

int Thing::keys_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys = v);
  return n;
}

int Thing::keys_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys -= v);
  if (infop()->keys < 0) {
    infop()->keys = 0;
  }
  return n;
}

int Thing::keys_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys += v);
  return n;
}

int Thing::keys_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys--);
  if (infop()->keys < 0) {
    infop()->keys = 0;
  }
  return n;
}

int Thing::keys_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->keys++);
  return n;
}
