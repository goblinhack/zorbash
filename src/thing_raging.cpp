//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::is_raging(void)
{
  TRACE_NO_INDENT();
  return is_raging_currently;
}

int Thing::is_able_to_rage(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_rage());
}

bool Thing::raging_set(bool val)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }

  if (is_player()) {
    if (val) {
      buff_add_if_not_found(tp_find("buff_permanent_raging"));
    } else {
      buff_remove(tp_find("buff_permanent_raging"));
    }
  }

  is_raging_currently = val;

  return is_raging_currently;
}

void Thing::rage_tick(void)
{
  TRACE_NO_INDENT();

  if (! is_able_to_rage()) {
    return;
  }

  bool was_raging = is_raging();
  raging_set(health() < (health_max() / 4));
  bool am_raging = is_raging();

  if (! was_raging && am_raging) {
    msg("%%fg=red$%s enters into a primal rage!%%fg=reset$", text_The().c_str());
  }
}
