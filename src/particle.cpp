//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iterator>
#include <math.h>
#include <vector>

#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_particle.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

bool Thing::particle_anim_exists(void) { return has_internal_particle || has_external_particle; }

void Thing::delete_particle(void)
{
  TRACE_NO_INDENT();

  //
  // Don't remove immediately in case we are walking the particles.
  //
  if (has_internal_particle) {
    dbg3("Delete particle: Has internal particle");
    for (auto &p : level->all_internal_particles) {
      if (p.id == id) {
        dbg3("Remove particle");
        p.id      = NoThingId;
        p.removed = true;
        break;
      }
    }

    has_internal_particle = false;
  }

  if (has_external_particle) {
    dbg3("Delete particle: Has external particle");
    for (auto &p : level->all_external_particles) {
      if (p.id == id) {
        dbg3("Remove particle");
        p.id      = NoThingId;
        p.removed = true;
        break;
      }
    }

    has_external_particle = false;
  }
}
