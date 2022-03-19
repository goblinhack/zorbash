//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::poison_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return;
  }

  auto old_poison = poisoned_amount();
  if (! old_poison) {
    return;
  }

  dbg("Poison tick");
  TRACE_AND_INDENT();

  poisoned();

  Thingp hitter = this;
  int    poison = old_poison;

  if (poison) {
    auto new_poison = poison / 2;

    if (poison) {
      if (d20() < stat_con()) {
        if (is_player()) {
          msg("You take half damage fron poison due to your sturdy constitution.");
        }
        new_poison = poison / 2;
      }
    }

    //
    // Do not let poison go to zero if still in the gas. This stops messages that
    // look like you have recovered.
    //
    if (is_breather()) {
      auto intensity = level->is_gas_poison(curr_at.x, curr_at.y) / 10;
      if (intensity) {
        if (! new_poison) {
          new_poison = 1;
        }
      }
    }

    poisoned_amount_set(new_poison);

    if (! new_poison) {
      poison_reason_set("");
    }

    if (poison) {
      is_attacked_with_damage_poison(hitter, hitter, poison);
    }
  }
}

void Thing::poisoned(void)
{
  if (is_player()) {
    debuff_add_if_not_found(tp_find("debuff_poisoned"));
  }
}

////////////////////////////////////////////////////////////////////////////
// poison
////////////////////////////////////////////////////////////////////////////
int Thing::poisoned_amount(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  if (maybe_infop()) {
    v = infop()->poison;
  }
  auto owner = immediate_owner();
  if (owner && (owner != this)) {
    v += owner->poisoned_amount();
  }
  if (is_minion()) {
    auto mob = immediate_mob();
    if (mob) {
      auto mob = immediate_mob();
      v += mob->poisoned_amount();
    }
  }
  return v;
}

int Thing::poisoned_amount_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison = v);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return n;
}

int Thing::poisoned_amount_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison -= v);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return n;
}

int Thing::poisoned_amount_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison += v);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return n;
}

int Thing::poisoned_amount_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison--);
  if (infop()->poison < 0) {
    infop()->poison = 0;
  }
  return n;
}

int Thing::poisoned_amount_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->poison++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// poison_reason
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::poison_reason_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->poison_reason);
  } else {
    static std::string empty;
    return (empty);
  }
}

void Thing::poison_reason_set(const std::string &v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->poison_reason = v;
}
