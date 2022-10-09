//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Thing::health_boost(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return false;
  }

  auto old_health = health();
  auto new_health = old_health + v;
  auto max_health = health_max();

  if (old_health >= max_health) {
    dbg("Health boost not possible, maxxed out already");
    return false;
  }

  new_health = std::min(new_health, max_health);
  health_set(new_health);

  if (new_health >= max_health) {
    dbg("Health boost not possible, maxxed at %d", new_health);
  } else {
    dbg("Health boost by %d from %d to %d", v, old_health, new_health);
  }
  return new_health - old_health;
}

bool Thing::health_boost_would_occur(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return false;
  }

  auto old_health = health();
  auto max_health = health_max();

  return old_health < max_health;
}

bool Thing::is_bloodied(void)
{
  TRACE_NO_INDENT();
  return health_pct() <= THING_HEALTH_BLOODIED_PCT1;
}

float Thing::health_pct(void)
{
  TRACE_NO_INDENT();
  float pct = (((float) health()) / ((float) health_max())) * 100;
  return pct;
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::health(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->health;
  }
  /*
   * Why do we do this? It makes looking at weapon health hard
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->health();
  }
   */
  return v;
}

int Thing::health_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health = v);
  return n;
}

int Thing::health_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health -= v);
  return n;
}

int Thing::health_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health += v);
  if (n > health_max()) {
    n               = health_max();
    infop()->health = n;
  }
  return n;
}

int Thing::health_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health--);
  return n;
}

int Thing::health_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health++);
  if (n > health_max()) {
    n               = health_max();
    infop()->health = n;
  }
  return n;
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::health_max(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->health_max);
  }
  return 0;
}

int Thing::health_max_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health_max = v);
  return n;
}

int Thing::health_max_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health_max -= v);
  return n;
}

int Thing::health_max_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health_max += v);
  return n;
}

int Thing::health_max_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health_max--);
  return n;
}

int Thing::health_max_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->health_max++);
  return n;
}

const Dice &Thing::health_initial_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_initial_dice());
}

const std::string &Thing::health_initial_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_initial_dice_str());
}

int Thing::health_initial(void)
{
  TRACE_NO_INDENT();
  return (tp()->health_initial_dice().roll());
}
