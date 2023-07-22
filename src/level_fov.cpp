/*
 * Modified from libtcod, so here is their original license
 */

/* BSD 3-Clause License
 *
 * Copyright © 2008-2021, Jice and the libtcod contributors.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

//
// Changed by goblinhack@gmail.com
//

#include <math.h>

#include "my_array_bounds_check.hpp"
#include "my_level.hpp"
#include "my_thing.hpp"

// Octant transformation matrixes.
// {xx, xy, yx, yy}
static const int matrix_table[ 8 ][ 4 ] = {
    {1, 0, 0, 1},   {0, 1, 1, 0},   {0, -1, 1, 0}, {-1, 0, 0, 1},
    {-1, 0, 0, -1}, {0, -1, -1, 0}, {0, 1, -1, 0}, {1, 0, 0, -1},
};

// Cast visiblity using shadowcasting.
void Level::scan(Thingp me, FovMap *fov_curr, FovMap *fov_ever, int pov_x, int pov_y,
                 int   distance_from_origin, // Polar distance_from_origin from POV.
                 float view_slope_high, float view_slope_low, int max_radius, int octant, bool light_walls)
{
  const int xx             = matrix_table[ octant ][ 0 ];
  const int xy             = matrix_table[ octant ][ 1 ];
  const int yx             = matrix_table[ octant ][ 2 ];
  const int yy             = matrix_table[ octant ][ 3 ];
  const int radius_squared = max_radius * max_radius;

  if (view_slope_high < view_slope_low) {
    return; // View is invalid.
  }

  if (distance_from_origin > max_radius) {
    return; // Distance is out-of-range.
  }

  if (is_oob(pov_x + distance_from_origin * xy, pov_y + distance_from_origin * yy)) {
    return; // Distance is out-of-bounds.
  }

  bool prev_tile_blocked = false;

  for (int angle = distance_from_origin; angle >= 0; --angle) { // Polar angle coordinates from high to low.
    const float tile_slope_high     = (angle + 0.5f) / (distance_from_origin - 0.5f);
    const float tile_slope_low      = (angle - 0.5f) / (distance_from_origin + 0.5f);
    const float prev_tile_slope_low = (angle + 0.5f) / (distance_from_origin + 0.5f);

    if (tile_slope_low > view_slope_high) {
      continue; // Tile is not in the view yet.
    }
    if (tile_slope_high < view_slope_low) {
      break; // Tiles will no longer be in view.
    }

    // Current tile is in view.
    const int map_x = pov_x + angle * xx + distance_from_origin * xy;
    const int map_y = pov_y + angle * yx + distance_from_origin * yy;

    if (is_oob(map_x, map_y)) {
      continue; // Angle is out-of-bounds.
    }

    //
    // Treat player and monster blocking differently so the player can use cover
    //
    auto light_blocker = is_light_blocker(map_x, map_y);
    if (me->is_monst()) {
      if (! light_blocker) { light_blocker = is_light_blocker_for_monst(map_x, map_y); }
    }

    if (angle * angle + distance_from_origin * distance_from_origin <= radius_squared
        && (light_walls || ! light_blocker)) {
      set_no_check(fov_curr->can_see, map_x, map_y, true);

      if (fov_ever) { set_no_check(fov_ever->can_see, map_x, map_y, true); }

      //
      // Always call this, even for cells we can see, as a monster may have just walked onto
      // a cell that was empty that we have already seen.
      //
      me->can_see_you(point(map_x, map_y));
    }

    if (prev_tile_blocked && ! light_blocker) { // Wall -> floor.
      view_slope_high = prev_tile_slope_low;    // Reduce the view size.
    }

    if (! prev_tile_blocked && light_blocker) { // Floor -> wall.
      // Get the last sequence of floors as a view and recurse into them.
      scan(me, fov_curr, fov_ever, pov_x, pov_y, distance_from_origin + 1, view_slope_high, tile_slope_high,
           max_radius, octant, light_walls);
    }

    prev_tile_blocked = light_blocker;
  }

  if (! prev_tile_blocked) {
    // Tail-recurse into the current view.
    scan(me, fov_curr, fov_ever, pov_x, pov_y, distance_from_origin + 1, view_slope_high, view_slope_low, max_radius,
         octant, light_walls);
  }
}

bool Level::fov_calculate(Thingp me, FovMap *fov_curr, FovMap *fov_ever, int pov_x, int pov_y, int max_radius,
                          bool light_walls)
{
  if (is_oob(pov_x, pov_y)) {
    err("Point of view {%i, %i} is out of bounds.", pov_x, pov_y);
    return false;
  }

  fov_curr->can_see = {};

  if (max_radius <= 0) {
    int max_radius_x = std::max(MAP_WIDTH - pov_x, pov_x);
    int max_radius_y = std::max(MAP_HEIGHT - pov_y, pov_y);
    max_radius       = (int) (sqrt(max_radius_x * max_radius_x + max_radius_y * max_radius_y)) + 1;
  }

  /* recursive shadow casting */
  for (int octant = 0; octant < 8; ++octant) {
    scan(me, fov_curr, fov_ever, pov_x, pov_y, 1, 1.0, 0.0, max_radius, octant, light_walls);
  }

  set_no_check(fov_curr->can_see, pov_x, pov_y, true);
  set_no_check(fov_ever->can_see, pov_x, pov_y, true);
  me->can_see_you(point(pov_x, pov_y));

  return true;
}
