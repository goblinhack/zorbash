//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::stamina_boost(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return;
  }

  auto max_stamina = stamina_max();
  if (! max_stamina) {
    return;
  }

  auto old_stamina = stamina();
  auto new_stamina = old_stamina + v;
  new_stamina      = std::min(new_stamina, max_stamina);
  stamina_set(new_stamina);

  if (new_stamina >= max_stamina) {
    dbg("Stamina boost not possible, maxxed at %d", new_stamina);
  } else {
    dbg("Stamina boost by %d from %d to %d", v, old_stamina, new_stamina);
  }
}

////////////////////////////////////////////////////////////////////////////
// stamina
////////////////////////////////////////////////////////////////////////////
int Thing::stamina(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->stamina;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->stamina();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->stamina();
    }
  }
  return v;
}

int Thing::stamina_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina = v);
  return n;
}

int Thing::stamina_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();

  v = total_on_damage_stamina(this, this, v);

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_tireless()) {
        return true;
      }
    }
  }

  auto n = (infop()->stamina -= v);
  if (infop()->stamina < 0) {
    infop()->stamina = 0;
  }
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  return n;
}

int Thing::stamina_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina += v);
  if (n > stamina_max()) {
    n                = stamina_max();
    infop()->stamina = n;
  }
  return n;
}

int Thing::stamina_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina--);
  if (infop()->stamina < 0) {
    infop()->stamina = 0;
  }
  return n;
}

int Thing::stamina_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina++);
  if (n > stamina_max()) {
    n                = stamina_max();
    infop()->stamina = n;
  }
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stamina_max
////////////////////////////////////////////////////////////////////////////
int Thing::stamina_max(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stamina_max);
  } else {
    return 0;
  }
}

int Thing::stamina_max_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max = v);
  return n;
}

int Thing::stamina_max_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max -= v);
  return n;
}

int Thing::stamina_max_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max += v);
  return n;
}

int Thing::stamina_max_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max--);
  return n;
}

int Thing::stamina_max_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->request_update_rightbar = true;
  }
  new_infop();
  auto n = (infop()->stamina_max++);
  return n;
}
