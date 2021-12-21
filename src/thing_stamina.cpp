//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_tile.hpp"

void Thing::stamina_boost(int v)
{
  TRACE_NO_INDENT();
  if (! v) {
    return;
  }

  auto max_stamina = get_stamina_max();
  if (! max_stamina) {
    return;
  }

  auto old_stamina = get_stamina();
  auto new_stamina = old_stamina + v;
  new_stamina      = std::min(new_stamina, max_stamina);
  set_stamina(new_stamina);

  if (new_stamina >= max_stamina) {
    dbg("Stamina boost not possible, maxxed at %d", new_stamina);
  } else {
    dbg("Stamina boost by %d from %d to %d", v, old_stamina, new_stamina);
  }
}
