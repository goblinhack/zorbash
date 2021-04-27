//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include "my_sys.h"
#include "my_game.h"
#include "my_projectile.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_vector_bounds_check.h"
#include "my_random.h"

Projectile_::Projectile_(
        Levelp level,
        ThingId thing_id,
        point start, point stop,
        point pixel_map_at,
        uint32_t timestamp_start, uint32_t timestamp_stop) :
    id(thing_id),
    start(start),
    stop(stop),
    pixel_map_at(pixel_map_at),
    timestamp_start(timestamp_start),
    timestamp_stop(timestamp_stop) 
{_
    auto t = level->thing_find(id);
    if (!t) {
        ERR("no projectile");
        return;
    }

    auto name = t->projectile_name();
    if (name.empty()) {
        ERR("no projectile name");
        return;
    }

    //
    // Find all projectile animation tiles. Names look like this:
    //
    // "projectile_green.{frame}.start",
    // "projectile_green.{frame}.{mid}.1",
    // "projectile_green.{frame}.{mid}.2",
    // "projectile_green.{frame}.{mid}.3",
    // "projectile_green.{frame}.{mid}.4",
    // "projectile_green.{frame}.{mid}.5",
    // "projectile_green.{frame}.{mid}.6",
    // "projectile_green.{frame}.{mid}.7",
    // "projectile_green.{frame}.{mid}.8",
    // "projectile_green.{frame}.{mid}.9",
    // "projectile_green.{frame}.{mid}.10",
    // "projectile_green.{frame}.{mid}.11",
    // "projectile_green.{frame}.{mid}.12",
    // "projectile_green.{frame}.{mid}.13",
    // "projectile_green.{frame}.{mid}.14",
    // "projectile_green.{frame}.end",
    //
    tiles.resize(max_frames);

    for (int frame = 0; frame < max_frames; frame++) {
        tiles[frame].push_back(
            tile_find_mand(name + "." + std::to_string(frame + 1) + ".start"));
        for (int mid = 0; mid < max_frames - 2; mid++) {
            tiles[frame].push_back(
                tile_find_mand(name + "." + std::to_string(frame + 1) + 
                               ".mid." + std::to_string(mid + 1)));
        }
        tiles[frame].push_back(
            tile_find_mand(name + "." + std::to_string(frame + 1) + ".end"));
    }
}

void Level::new_projectile (ThingId id, point start, point stop, uint32_t dur)
{_
    if (id.ok()) {
        auto t = thing_find(id);
        if (t) {
            if (t->has_projectile) {
                return;
            }
            t->has_projectile = true;
            t->log("new internal projectile");
        }
    }

    uint32_t now = time_update_time_milli();
    new_projectiles.push_back(Projectile(this, id, 
                               start, stop, pixel_map_at, now, now + dur));
}

void Level::display_projectiles (void)
{_
#if 0
    CON("-");
    for (auto p : all_projectiles) {
        CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
    for (auto p : new_projectiles) {
        CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
#endif

    all_projectiles.insert(std::end(all_projectiles), 
                      std::begin(new_projectiles), 
                      std::end(new_projectiles));
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
    auto now = time_update_time_milli();
    auto e = std::remove_if(all_projectiles.begin(),
                            all_projectiles.end(),
        [=, this] (Projectile &p) {
            float timestep = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / timestep;

            Thingp t;

            t = thing_find(p.id);
            if (!t) {
                return true;
            }

            if (dt > 1) {
                if (t) {
                    t->log("End of projectile");
                    t->has_projectile = false;
                }
                return true;
            }

            auto start = p.start - p.pixel_map_at;
            auto stop = p.stop - p.pixel_map_at;

            auto dist = distance(start, stop);
            auto steps = (int)ceil(dist) / TILE_WIDTH;
            fpoint diff(stop.x - start.x, stop.y - start.y);
            fpoint step = diff / steps;
            float ninety_deg = RAD_360 / 4;

            fpoint perp = step;
            perp = perp.rotate_radians(ninety_deg);
            perp /= 2;

            point p1;
            point p2;
            point old_p1;
            point old_p2;

            int frame = (int)((float)Projectile::max_frames * dt);
            if (frame >= Projectile::max_frames) {
                frame = Projectile::max_frames - 1;
            }

            for (int animstep = 0; animstep <= steps; animstep++) {
                fpoint mid(start.x + step.x * animstep, 
                           start.y + step.y * animstep);

                old_p1 = p1;
                old_p2 = p2;

                p1.x = mid.x - perp.x;
                p1.y = mid.y - perp.y;
                p2.x = mid.x + perp.x;
                p2.y = mid.y + perp.y;

                if (animstep == 0) {
                    continue;
                }

                if (animstep == 1) {
                    tile_blit(get(p.tiles, frame, 0),
                              old_p1, p1, old_p2, p2);
                } else if (animstep == steps) {
                    tile_blit(get(p.tiles, frame, Projectile::max_frames - 1), 
                              old_p1, p1, old_p2, p2);
                } else {
                    tile_blit(get(p.tiles, frame, animstep), 
                              old_p1, p1, old_p2, p2);
                }
            }

            return false;
        });
    all_projectiles.erase(e, all_projectiles.end());

    blit_flush();
}

bool Thing::projectile_anim_exists (void)
{_
    return has_projectile;
}

void Thing::delete_projectile (void)
{_
    auto e = std::remove_if(level->all_projectiles.begin(),
                            level->all_projectiles.end(),
        [=, this] (Projectile &p) { 
            if (p.id == id) {
                log("Remove projectile");
                return true;
            } else {
                return false;
            }
        }
    );

    level->all_projectiles.erase(e, level->all_projectiles.end());
    has_projectile = false;
}
