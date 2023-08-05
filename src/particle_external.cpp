//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Level::new_external_particle(ThingId id, point start, point stop, isize sz, uint32_t dur, const Tilep tile,
                                  bool hflip, MyCallback callback)
{
  TRACE_NO_INDENT();

  if (unlikely(! tile)) {
    err("No external particle tile");
    return;
  }

  //
  // We hit here for player jumps
  //
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

      if (t->has_external_particle) {
        return;
      }

      t->has_external_particle = true;
    }
  }

  if (g_opt_ascii) {
    callback();
    return;
  }

  uint32_t now = time_game_ms();
  new_external_particles.push_back(
      Particle(id, start, stop, pixel_map_at, sz, now, now + dur, tile, hflip, callback));
}

void Level::handle_external_particles(void)
{
  TRACE_NO_INDENT();

  if (all_external_particles.empty()) {
    return;
  }

  auto now = time_game_ms();
  auto e   = std::remove_if(all_external_particles.begin(), all_external_particles.end(), [ =, this ](Particle &p) {
    if (p.removed) {
      return true;
    }

    float t  = p.ts_stop - p.ts_start;
    float dt = (((float) (now) -p.ts_start)) / t;

    //
    // We need reliable durations when testing
    //
    if (g_opt_test_dungeon_gen) {
      dt = 1;
    }

    // con("dt %f", dt);
    if (dt >= 1) {
      if (p.id.id) {
        auto t = thing_find(p.id);
        if (t) {
          p.callback();
          IF_DEBUG3
          t->log("Particle end");
          t->is_scheduled_for_jump_end = true;
          t->has_external_particle     = false;
        }
      }
      return true;
    }

    return false;
  });

  all_external_particles.erase(e, all_external_particles.end());
}
