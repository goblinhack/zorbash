//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::move_penalty(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->move_penalty);
  }
  return 0;
}

int Thing::move_penalty_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_penalty = v);
  return n;
}

int Thing::move_penalty_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_penalty -= v);
  if (infop()->move_penalty < 0) {
    infop()->move_penalty = 0;
  }
  return n;
}

int Thing::move_penalty_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_penalty += v);
  return n;
}

int Thing::move_penalty_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_penalty--);
  if (infop()->move_penalty < 0) {
    infop()->move_penalty = 0;
  }
  return n;
}

int Thing::move_penalty_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->move_penalty++);
  return n;
}
