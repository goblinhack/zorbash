//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_ui.hpp"
#include "my_wid_topcon.hpp"

void Thing::necrosis_tick(void)
{
  TRACE_NO_INDENT();

  if ((is_alive_monst() || is_player()) && ! is_ethereal() && ! is_undead()) {
    auto old_necrosis = necrotized_amount_get();
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
      is_attacked_with_damage_necrosis(hitter, 1);
    }
  }
}

void Thing::rotting(void)
{
  if (is_player()) {
    debuff_add_if_not_found(tp_find("debuff_necrotized"));
  }
}
