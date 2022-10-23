//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include <iterator>
#include <math.h>
#include <vector>

#include "my_backtrace.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_particle.hpp"
#include "my_point.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

void Level::new_internal_particle(ThingId id, point start, point stop, isize sz, uint32_t dur, const Tilep tile,
                                  bool hflip, MyCallback callback)
{
  TRACE_NO_INDENT();

  if (unlikely(! tile)) {
    err("No internal particle tile");
    return;
  }

  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      if (t->is_being_destroyed) {
        return;
      }

      if (g_opt_ascii) {
        callback();
        return;
      }

      if (t->has_internal_particle) {
        return;
      }

      t->has_internal_particle = true;
    }
  }

  if (g_opt_ascii) {
    callback();
    return;
  }

  uint32_t now = time_game_ms();
  new_internal_particles.push_back(
      Particle(id, start, stop, pixel_map_at, sz, now, now + dur, tile, hflip, callback));
}

void Level::handle_internal_particles(void)
{
  TRACE_NO_INDENT();

  if (all_internal_particles.empty()) {
    return;
  }

  //
  // std::remove_if iterates over the whole vector and moves all "selected"
  // entries "to the end". std::erase resizes the container.
  //
  // Future: std::erase_if();
  //
  glcolor(WHITE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  blit_init();
  auto now = time_game_ms();
  auto e   = std::remove_if(all_internal_particles.begin(), all_internal_particles.end(), [ =, this ](Particle &p) {
    if (p.removed) {
      return true;
    }

    float t  = p.ts_stop - p.ts_start;
    float dt = (((float) (now) -p.ts_start)) / t;
    if (dt >= 1) {
      if (p.id.id) {
        auto t = thing_find(p.id);
        if (t) {
          (p.callback)();
          // t->con("end jump");
          t->is_scheduled_for_jump_end = true;
          t->has_internal_particle     = false;
        }
      }
      return true;
    }
    return false;
  });

  all_internal_particles.erase(e, all_internal_particles.end());
}
