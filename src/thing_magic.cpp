//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::magic_boost(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return;
  }

  auto max_magic = magic_max();
  if (! max_magic) {
    return;
  }

  auto old_magic = magic();
  auto new_magic = old_magic + v;
  new_magic      = std::min(new_magic, max_magic);
  magic_set(new_magic);

  if (new_magic >= max_magic) {
    dbg("Magic boost not possible, maxxed at %d", new_magic);
  } else {
    dbg("Magic boost by %d from %d to %d", v, old_magic, new_magic);
  }
}

////////////////////////////////////////////////////////////////////////////
// magic
////////////////////////////////////////////////////////////////////////////
int Thing::magic(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->magic;
  }
  /*
   * Why do we do this? It makes looking at weapon health hard
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->magic();
  }
  */
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->magic();
    }
  }
  return v;
}

int Thing::magic_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic = v);
  return n;
}

int Thing::magic_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();

  v = total_dmg_for_on_receiving_dmg_stamina(this, this, v);

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_tireless()) {
        return true;
      }
    }
  }

  auto n = (infop()->magic -= v);
  if (infop()->magic < 0) {
    infop()->magic = 0;
  }
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  return n;
}

int Thing::magic_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic += v);
  if (n > magic_max()) {
    n              = magic_max();
    infop()->magic = n;
  }
  return n;
}

int Thing::magic_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic--);
  if (infop()->magic < 0) {
    infop()->magic = 0;
  }
  return n;
}

int Thing::magic_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic++);
  if (n > magic_max()) {
    n              = magic_max();
    infop()->magic = n;
  }
  return n;
}

////////////////////////////////////////////////////////////////////////////
// magic_max
////////////////////////////////////////////////////////////////////////////
int Thing::magic_max(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->magic_max);
  }
  return 0;
}

int Thing::magic_max_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic_max = v);
  return n;
}

int Thing::magic_max_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic_max -= v);
  return n;
}

int Thing::magic_max_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic_max += v);
  return n;
}

int Thing::magic_max_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic_max--);
  return n;
}

int Thing::magic_max_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->magic_max++);
  return n;
}

int Thing::magic_drain_on_using(void)
{
  TRACE_NO_INDENT();
  return (tp()->magic_drain_on_using());
}
