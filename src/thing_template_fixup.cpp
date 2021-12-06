//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_vector_bounds_check.hpp"

void tp_fixup(void)
{
  TRACE_AND_INDENT();
  for (auto &tp : tp_id_map) {
    if (tp->stamina()) {
      tp->set_is_able_to_tire(true);
    }

    if (tp->is_tickable()) {
      tp->set_is_interesting(true);
    }

    if (tp->is_very_combustible()) {
      tp->set_is_combustible(true);
    }

    if (tp->is_able_to_fire_at()) {
      if (! tp->distance_vision()) {
        DIE("Tp %s needs vision distance if it is able to fire at things", tp->name().c_str());
      }
    }

    if (tp->is_interesting()) {
      if (tp->is_tmp_thing()) {
        DIE("Tp %s cannot be both interesting and temporary", tp->name().c_str());
      }
    }
  }

  for (auto &tp : tp_name_map) {
    auto tpp = tp.second;
    if (! tpp->lifespan_dice_str().empty()) {
      if (! tpp->is_tickable()) {
        DIE("Thing template must be set to be is_tickable [%s] for lifespan tick to work", tp.first.c_str());
      }
    }
  }
}
