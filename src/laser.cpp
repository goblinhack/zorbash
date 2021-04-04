//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include <vector>
#include <iterator>
#include "my_sys.h"
#include "my_game.h"
#include "my_laser.h"
#include "my_level.h"
#include "my_tile.h"
#include "my_point.h"
#include "my_gl.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_random.h"

void Level::new_laser (ThingId id, point start, point stop, uint32_t dur)
{
    if (id.ok()) {
        auto t = thing_find(id);
        if (t) {
            if (t->has_laser) {
                return;
            }
            t->has_laser = true;
            t->log("new internal laser");
        }
    }

    uint32_t now = time_update_time_milli();
    new_lasers.push_back(Laser(id, start, stop, pixel_map_at, now, now + dur));
}

void Level::display_lasers (void)
{_
#if 0
    CON("-");
    for (auto p : all_lasers) {
        CON("all int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
    for (auto p : new_lasers) {
        CON("new int p %d,%d to %d,%d %s", p.start.x, p.start.y, p.stop.x, p.stop.y, p.tile->name.c_str());
    }
#endif

    all_lasers.insert(std::end(all_lasers), 
                      std::begin(new_lasers), 
                      std::end(new_lasers));
    new_lasers.clear();

    if (all_lasers.empty()) {
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
    auto e = std::remove_if(all_lasers.begin(),
                            all_lasers.end(),
        [=, this] (Laser &p) {
            float t = p.timestamp_stop - p.timestamp_start;
            float dt = ((float)(now - p.timestamp_start)) / t;
            if (dt > 1) {
                if (p.id.id) {
                    auto t = thing_find(p.id);
                    if (t) {
                        t->log("End of laser");
                        t->has_laser = false;
                    }
                }
                return true;
            }

            auto start = p.start - p.pixel_map_at;
            auto stop = p.stop - p.pixel_map_at;

            auto tile_start = tile_find_mand("laser_green_start");
            std::vector<Tilep> tile_mid;
            tile_mid.push_back(tile_find_mand("laser_green_mid1"));
            tile_mid.push_back(tile_find_mand("laser_green_mid2"));
            tile_mid.push_back(tile_find_mand("laser_green_mid3"));
            tile_mid.push_back(tile_find_mand("laser_green_mid4"));
            tile_mid.push_back(tile_find_mand("laser_green_mid5"));
            tile_mid.push_back(tile_find_mand("laser_green_mid6"));
            auto tile_end = tile_find_mand("laser_green_end");

            auto dist = distance(start, stop);
            auto steps = (int)ceil(dist) / TILE_WIDTH;
            dpoint diff(stop.x - start.x, stop.y - start.y);
            dpoint step = diff / steps;
            double ninety_deg = RAD_360 / 4;

            dpoint perp = step;
            perp = perp.rotate_radians(ninety_deg);
            perp /= 2;

            point p1;
            point p2;
            point op1;
            point op2;

            static int i; 
            i++;
            for (int t = 0; t <= steps; t++) {
                fpoint mid(start.x + step.x * t, start.y + step.y * t);

                op1 = p1;
                op2 = p2;

                p1.x = mid.x - perp.x;
                p1.y = mid.y - perp.y;
                p2.x = mid.x + perp.x;
                p2.y = mid.y + perp.y;

                if (t == 0) {
                    continue;
                }

                if (t == 1) {
                    tile_blit(tile_start, op1, op2, p1, p2);
                } else if (t == steps) {
                    tile_blit(tile_end, op1, op2, p1, p2);
                } else {
                    tile_blit(tile_mid[(t + i) % tile_mid.size()],
                              op1, op2, p1, p2);
                }
            }

            return false;
        });
    all_lasers.erase(e, all_lasers.end());

    blit_flush();
}

bool Thing::laser_anim_exists (void)
{_
    return has_laser;
}

void Thing::delete_laser (void)
{_
    auto e = std::remove_if(level->all_lasers.begin(),
                            level->all_lasers.end(),
        [=, this] (Laser &p) { 
            if (p.id == id) {
                log("Remove laser");
                return true;
            } else {
                return false;
            }
        }
    );

    level->all_lasers.erase(e, level->all_lasers.end());
    has_laser = false;
}
