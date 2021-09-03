//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_THING_DEFS_H_
#define _MY_THING_DEFS_H_

#define LEVEL_FADE_IN_MS                   500
#define LEVEL_FADE_OUT_MS                  500
#define LEVELS_ACROSS                      MAP_WIDTH // World size
#define LEVELS_DEEP                        52  // Divided by 2 for sewer levels
#define LEVELS_DOWN                        MAP_HEIGHT
#define LEVELS_MONST_COUNT                 100
#define LEVEL_TICK_DURATION_TOO_LONG       20  // How many ms per level tick we expect
#define LIGHT_MAX_RAYS                     180 // Max light rays cast
#define MAP_BORDER_ROCK                    3   // Map rock border; keep at 3 as jump AI looks 2 tiles adjacent
#define MAP_BORDER_ROOM                    10  // Room border padding
#define MAP_GRID_HEIGHT                    4
#define MAP_GRID_WIDTH                     4   // Rooms across and down
#define MAP_HEIGHT                         ((MAP_GRID_HEIGHT*MAP_ROOM_HEIGHT) + (MAP_BORDER_ROOM*2))
#define MAP_ROOM_HEIGHT                    13
#define MAP_ROOM_WIDTH                     13
#define MAP_SLOTS                          32   // Max things per map slot
#define MAP_WIDTH                          ((MAP_GRID_WIDTH*MAP_ROOM_WIDTH) + (MAP_BORDER_ROOM*2))
#define MAX_BAG_HEIGHT                     20
#define MAX_BAG_WIDTH                      20
#define PARTICLE_SPEED_MS                  450
#define THING_JUMP_SPEED                   450
#define MONST_JUMP_SPEED                   150
#define ROBOT_CAN_SEE_SECRET_DOOR_DISTANCE 3
#define THING_DAMAGE_SHAKE_ABOVE           10   // Damage above this causes shakes
#define THING_DAMAGE_SHAKE_SCALE           40.0 // Smaller means more shaking
#define THING_FAST_MOVE_SPEED_MS           50
#define THING_HEALTH_BLOODIED_PCT1         35   // Some blood on the screen
#define THING_HEALTH_BLOODIED_PCT2         15   // More...
#define THING_HEALTH_BLOODIED_PCT3         15   // More...
#define THING_HEALTH_BLOODIED_PCT4         5    // Lots of blood on screen
#define THING_SLOW_MOVE_SPEED_MS           125
#define THING_TICK_DURATION_TOO_LONG       10   // How many ms per thing tick we expect not to exceed
#define THING_AI_ESCAPE_ATTEMPTS           4    // Quite CPU heavy
#define THING_AI_WANDER_TRIES              1    // Quite CPU heavy

#endif
