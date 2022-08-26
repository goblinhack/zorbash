//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_DEFS_HPP_
#define _MY_THING_DEFS_HPP_

#define MAX_BAG_HEIGHT                    20   // Biggest player bag dimensions.
#define MAX_BAG_WIDTH                     20   // Biggest player bag dimensions.
#define PARTICLE_SPEED_MS                 450  // For collection of coins etc...
#define THING_AI_CAN_SEE_SECRET_DOOR_DIST 3    // How close to a secret door can a monst see it?
#define THING_AI_ESCAPE_ATTEMPTS          4    // Quite CPU heavy
#define THING_AI_MAX_AVOID_ATTEMPT_LOC    4    // How many places to look at per attempt to avoid something
#define THING_AI_MAX_AVOID_COUNT          10   // Count to keep track of avoid attempts
#define THING_AI_MAX_GOAL_PENALTY         100  // Helps to avoid goal oscillation
#define THING_AI_MAX_RESENT_COUNT         100  // Count to keep track of resentfulness
#define THING_AI_WANDER_TRIES             2    // Quite CPU heavy
#define THING_DAMAGE_SHAKE_ABOVE          10   // Damage above this causes shakes
#define THING_DAMAGE_SHAKE_SCALE          40.0 // Smaller means more shaking
#define THING_HEALTH_BLOODIED_PCT1        35   // Some blood on the screen
#define THING_HEALTH_BLOODIED_PCT2        15   // More...
#define THING_HEALTH_BLOODIED_PCT3        15   // More...
#define THING_HEALTH_BLOODIED_PCT4        5    // Lots of blood on screen
#define THING_JUMP_HEIGHT                 20   // Height in pixels
#define THING_JUMP_SPEED_MS               450  // Jump animation speed
#define THING_FALL_SPEED_MS               1000 // Fall animation speed
#define THING_MOVE_SPEED_FAST_MS          50   // Movement when we have a cursor path
#define THING_MOVE_SPEED_SLOW_MS          125  // Normal movement speed
#define THING_TICK_DURATION_TOO_LONG      10   // How many ms per thing tick we expect not to exceed
#define THING_TICK_WAIT_TOO_LONG          100  // How many ticks we wait for things to stop moving
#define TEMPERATURE_ROOM                  20   // Celcius
#define TEMPERATURE_MIN                   -273 // Celcius
#define TEMPERATURE_MAX                   1000 // Celcius

#endif
