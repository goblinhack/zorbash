//
// Copyright goblinhack@gmail.com
//

#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"
#include <algorithm>

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

    //
    // We need reliable durations when testing
    //
    if (g_opt_test_dungeon) {
      dt = 1;
    }

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
