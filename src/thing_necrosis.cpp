//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::necrosis_tick(void)
{
  TRACE_NO_INDENT();

  if ((is_alive_monst() || is_player()) && ! is_ethereal() && ! is_undead()) {
    auto old_necrosis = necrotized_amount();
    if (! old_necrosis) {
      return;
    }

    dbg("Necrosis tick");
    TRACE_AND_INDENT();

    rotting();

    Thingp hitter   = this;
    int    necrosis = old_necrosis;

    if (necrosis) {
      necrotized_amount_decr();
      is_attacked_with_dmg_necrosis(hitter, hitter, 1);
    }
  }
}

void Thing::rotting(void)
{
  if (is_player()) {
    debuff_add_if_not_found(tp_find("debuff_necrotized"));
  }
}

////////////////////////////////////////////////////////////////////////////
// necrosis
////////////////////////////////////////////////////////////////////////////
int Thing::necrotized_amount(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->necrosis;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->necrotized_amount();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->necrotized_amount();
    }
  }
  return v;
}

int Thing::necrotized_amount_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis = v);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return n;
}

int Thing::necrotized_amount_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis -= v);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return n;
}

int Thing::necrotized_amount_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis += v);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return n;
}

int Thing::necrotized_amount_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis--);
  if (infop()->necrosis < 0) {
    infop()->necrosis = 0;
  }
  return n;
}

int Thing::necrotized_amount_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->necrosis++);
  return n;
}
