//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

////////////////////////////////////////////////////////////////////////////
// runic_name
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::runic_name_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->runic_name);
  }
  static std::string empty;
  return empty;
}

void Thing::runic_name_set(const std::string &v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->runic_name = v;
}

void Thing::add_random_runic(void)
{
  TRACE_NO_INDENT();

  if (! is_enchantable()) {
    return;
  }

  //
  // If enchanted, it can have a runic
  //
  if (! enchant_count_get()) {
    return;
  }

  //
  // Able to have a runic?
  //
  if (! is_able_to_have_a_runic_inscribed()) {
    return;
  }

  //
  // Make it more likely, the more enchants
  //
  if (d10000() + (500 * enchant_count_get()) < chance_d10000_runic()) {
    //
    // Success
    //
    if (is_weapon()) {
      auto tp = tp_random_runic_offensive();
      if (tp) {
        new_infop();
        runic_name_set(tp->name());
      }
    } else {
      auto tp = tp_random_runic_defensive();
      if (tp) {
        new_infop();
        runic_name_set(tp->name());
      }
    }
  }
}
