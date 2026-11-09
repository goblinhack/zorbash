//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_dominate_monst0.py
//

#include "my_native.hpp"
#include "things/spells/spell_of_dominate_monst0.hpp"

namespace mod_things_spells_spell_of_dominate_monst0 {

void on_targeted(uint32_t me, int x, int y, int bonus)
{
  int existing_mental_load = 0;
  uint32_t owner = 0;
  int roll = 0;
  owner = my::thing_top_owner_id_get(me);
  if ((! (owner != 0))) {
    return;
  }
  existing_mental_load = 0;
  for (auto f : my::thing_get_followers(me)) {
    existing_mental_load += my::thing_stat_int_bonus(f);
  }
  bonus -= existing_mental_load;
  bonus += my::thing_stat_psi_bonus(me);
  for (auto it : my::level_get_all(me, x, y)) {
    if ((! my::thing_is_monst(it))) {
      continue;
    }
    if (my::thing_is_dead(it)) {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(it) + "'s mind is beyond your powers.")).c_str());
      continue;
    }
    if (my::thing_is_ethereal(it)) {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(it) + "'s mind evades your grasp.")).c_str());
      continue;
    }
    roll = my::pcg_random_inclusive(1, 20);
    if (((roll + bonus) > [&]() { auto t1_0_ = my::thing_stat_int(it); auto t1_1_ = my::thing_stat_psi_bonus(it); return (t1_0_ + t1_1_); }())) {
      if (my::thing_set_leader(it, owner)) {
        my::thing_msg(me, ((std::string("The ") + my::thing_name_get(it) + "'s mind is beholden to you.")).c_str());
      } else {
        my::thing_msg(me, ((std::string("The ") + my::thing_name_get(it) + " cannot be possessed.")).c_str());
      }
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(it) + " fends off your mental attack.")).c_str());
    }
  }
}

void module_init(void)
{
  native_register("spell_of_dominate_monst0", "on_targeted", 4, [](const int64_t *a) -> NativeRet { (void) a; on_targeted((uint32_t) a[0], (int) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
}

} // namespace mod_things_spells_spell_of_dominate_monst0
