//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_main.h"
#include "my_globals.h"
#include "my_tile.h"
#include "my_thing.h"

void Thing::stamina_boost(int v)
{
  TRACE_AND_INDENT();
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
