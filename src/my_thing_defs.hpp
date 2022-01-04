//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_THING_DEFS_HPP_
#define _MY_THING_DEFS_HPP_

//
// Grid chunks are used to construct the levels and the overall dungeon
//
#define DUNGEON_GRID_CHUNK_HEIGHT  4  // Levels are split into grids. Each grid can have a room.
#define DUNGEON_GRID_CHUNK_WIDTH   4  // Rooms across and down
#define DUNGEONS_GRID_CHUNK_HEIGHT 20 // The whole underworld
#define DUNGEONS_GRID_CHUNK_WIDTH  20 //
#define MAX_GRID_CHUNK_HEIGHT      DUNGEONS_GRID_CHUNK_HEIGHT
#define MAX_GRID_CHUNK_WIDTH       DUNGEONS_GRID_CHUNK_WIDTH

#define LEVEL_FADE_IN_MS                  500  // Level start fade animation time
#define LEVEL_FADE_OUT_MS                 500  // Level end fade animation time
#define LEVELS_DEEP                       52   // NOTE: This is divided by 2 for sewer levels
#define LEVELS_MONST_COUNT                100  // Monsters max per level. Want more? You're mad...
#define LIGHT_MAX_RAYS                    180  // Max light rays cast
#define MAP_BORDER_ROCK                   3    // Map rock border; keep at 3 as jump AI looks 2 tiles adjacent
#define MAP_BORDER_ROOM                   10   // Room border padding
#define MAP_ROOM_HEIGHT                   13   // Max room dimensions
#define MAP_ROOM_WIDTH                    13   // Max room dimensions
#define MAP_SLOTS                         32   // Max things per map slot
#define MAX_BAG_HEIGHT                    20   // Biggest player bag dimensions.
#define MAX_BAG_WIDTH                     20   // Biggest player bag dimensions.
#define PARTICLE_SPEED_MS                 450  // For collection of coins etc...
#define THING_AI_CAN_SEE_SECRET_DOOR_DIST 3    // How close to a secret door can a monst see it?
#define THING_AI_ESCAPE_ATTEMPTS          4    // Quite CPU heavy
#define THING_AI_MAX_AVOID_ATTEMPT_LOC    4    // How many places to look at per attempt to avoid something
#define THING_AI_MAX_AVOID_COUNT          10   // Count to keep track of avoid attempts
#define THING_AI_MAX_GOAL_PENALTY         100  // Helps to avoid goal oscillation
#define THING_AI_MAX_RESENT_COUNT         100  // Count to keep track of resentfulness
#define THING_AI_WANDER_TRIES             4    // Quite CPU heavy
#define THING_DAMAGE_SHAKE_ABOVE          10   // Damage above this causes shakes
#define THING_DAMAGE_SHAKE_SCALE          40.0 // Smaller means more shaking
#define THING_HEALTH_BLOODIED_PCT1        35   // Some blood on the screen
#define THING_HEALTH_BLOODIED_PCT2        15   // More...
#define THING_HEALTH_BLOODIED_PCT3        15   // More...
#define THING_HEALTH_BLOODIED_PCT4        5    // Lots of blood on screen
#define THING_JUMP_HEIGHT                 40   // Height in pixels
#define THING_JUMP_SPEED_MS               450  // Jump animation speed
#define THING_MOVE_SPEED_FAST_MS          50   // When in robot mode, move things faster
#define THING_MOVE_SPEED_SLOW_MS          125  // Normal movement speed
#define THING_TICK_DURATION_TOO_LONG      10   // How many ms per thing tick we expect not to exceed
#define THING_TICK_WAIT_TOO_LONG          100  // How many ticks we wait for things to stop moving

#define LEVELS_ACROSS MAP_WIDTH // World size; no world yet...
#define LEVELS_DOWN   MAP_HEIGHT
#define MAP_HEIGHT    ((DUNGEON_GRID_CHUNK_HEIGHT * MAP_ROOM_HEIGHT) + (MAP_BORDER_ROOM * 2))
#define MAP_WIDTH     ((DUNGEON_GRID_CHUNK_WIDTH * MAP_ROOM_WIDTH) + (MAP_BORDER_ROOM * 2))

#endif
