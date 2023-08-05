//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::move_count(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->move_count);
  }
  return 0;
}

int Thing::move_count_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_count = v);
  return n;
}

int Thing::move_count_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_count -= v);
  if (infop()->move_count < 0) {
    infop()->move_count = 0;
  }
  return n;
}

int Thing::move_count_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_count += v);
  return n;
}

int Thing::move_count_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_count--);
  if (infop()->move_count < 0) {
    infop()->move_count = 0;
  }
  return n;
}

int Thing::move_count_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_count++);
  return n;
}
