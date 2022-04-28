//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <iterator>
#include <math.h>
#include <vector>

#include "my_game.hpp"
#include "my_gl.hpp"
#include "my_point.hpp"
#include "my_projectile.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_vector_bounds_check.hpp"

Projectile_::Projectile_(Levelp level, ThingId thing_id, ThingId victim_id, point start, point stop,
                         point pixel_map_at, uint32_t ts_start, uint32_t ts_stop, bool follow_moving_target)
    : id(thing_id), victim_id(victim_id), start(start), stop(stop), pixel_map_at(pixel_map_at), ts_start(ts_start),
      ts_stop(ts_stop), follow_moving_target(follow_moving_target)
{
  TRACE_AND_INDENT();
  auto t = level->thing_find(id);
  if (unlikely(! t)) {
    ERR("no projectile");
    return;
  }

  //
  // Can be either a wand or the projectile itself being fired
  //
  std::string name;
  if (t->is_projectile()) {
    name = t->tp()->name();
  } else {
    name = t->target_name_projectile();
    if (name.empty()) {
      t->err("no projectile name");
      return;
    }
  }

  //
  // Find all projectile animation tiles. Names look like this:
  //
  // "projectile_green.{frame}.1",
  // "projectile_green.{frame}.2",
  // "projectile_green.{frame}.3",
  // "projectile_green.{frame}.4",
  // "projectile_green.{frame}.5",
  // "projectile_green.{frame}.6",
  // "projectile_green.{frame}.7",
  // "projectile_green.{frame}.8",
  // "projectile_green.{frame}.9",
  // "projectile_green.{frame}.10",
  // "projectile_green.{frame}.11",
  // "projectile_green.{frame}.12",
  // "projectile_green.{frame}.13",
  // "projectile_green.{frame}.14",
  // "projectile_green.{frame}.15",
  // "projectile_green.{frame}.16",
  //
  for (int frame = 0; frame < max_frames; frame++) {
    tiles.push_back(tile_find_mand(name + "." + std::to_string(frame + 1)));
  }
}

void Level::new_projectile(ThingId id, ThingId victim_id, point start, point stop, uint32_t dur,
                           bool follow_moving_target)
{
  TRACE_AND_INDENT();
  if (id.ok()) {
    auto t = thing_find(id);
    if (t) {
      if (t->has_projectile) {
        return;
      }
      t->has_projectile = true;
      t->log("New internal projectile");
    }
  }

  uint32_t now = time_game_ms();
  new_projectiles.push_back(
      Projectile(this, id, victim_id, start, stop, pixel_map_at, now, now + dur, follow_moving_target));
}

void Level::display_pixelart_projectiles(void)
{
  TRACE_NO_INDENT();
#if 0
  CON("-");
  for (auto p : all_projectiles) {
    CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
  for (auto p : new_projectiles) {
    CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
  }
#endif

  all_projectiles.insert(std::end(all_projectiles), std::begin(new_projectiles), std::end(new_projectiles));
  new_projectiles.clear();

  if (all_projectiles.empty()) {
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
  auto e   = std::remove_if(all_projectiles.begin(), all_projectiles.end(), [ =, this ](Projectile &p) {
    float timestep = p.ts_stop - p.ts_start;
    float dt       = ((float) (now - p.ts_start)) / timestep;

    Thingp t;

    t = thing_find(p.id);
    if (unlikely(! t)) {
      return true;
    }

    if (dt > 1) {
      if (t) {
        t->dead("End of projectile");
        t->has_projectile = false;
      }
      return true;
    }

    if (p.follow_moving_target) {
      auto t = thing_find_optional(p.victim_id);
      if (t) {
        p.stop = t->last_blit_at;
      }
    }

    auto start = p.start - p.pixel_map_at;
    auto stop  = p.stop - p.pixel_map_at;

    auto   dist  = distance(start, stop);
    auto   steps = (int) ceil(dist) / TILE_WIDTH;
    fpoint diff(stop.x - start.x, stop.y - start.y);
    fpoint step       = diff / steps;
    float  ninety_deg = RAD_360 / 4;

    fpoint perp = step;
    perp        = rotate_radians(perp, ninety_deg);
    perp /= 2;

    int frame = (int) ((float) Projectile::max_frames * dt);
    if (frame >= Projectile::max_frames) {
      frame = Projectile::max_frames - 1;
    }

    fpoint mid(start.x + (diff.x * dt), start.y + (diff.y * dt));

    point tl = make_point(mid - perp - step / 2);
    point tr = make_point(mid - perp + step / 2);
    point bl = make_point(mid + perp - step / 2);
    point br = make_point(mid + perp + step / 2);

    if (! g_opt_ascii) {
      tile_blit(get(p.tiles, frame), tl, tr, bl, br);
    }
#if 0
      //
      // Debug
      //
      gl_blitline(tl.x, tl.y, tr.x, tr.y);
      gl_blitline(tr.x, tr.y, br.x, br.y);
      gl_blitline(br.x, br.y, bl.x, bl.y);
      gl_blitline(bl.x, bl.y, tl.x, tl.y);
#endif

    return false;
  });
  all_projectiles.erase(e, all_projectiles.end());

  blit_flush();
}

bool Thing::projectile_anim_exists(void)
{
  TRACE_AND_INDENT();
  return has_projectile;
}

void Thing::delete_projectile(void)
{
  TRACE_AND_INDENT();
  auto e = std::remove_if(level->all_projectiles.begin(), level->all_projectiles.end(), [ =, this ](Projectile &p) {
    if (p.id == id) {
      log("Remove projectile");
      return true;
    } else {
      return false;
    }
  });

  level->all_projectiles.erase(e, level->all_projectiles.end());
  has_projectile = false;
}
