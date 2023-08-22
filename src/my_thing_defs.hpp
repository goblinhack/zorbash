//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_DEFS_HPP_
#define _MY_THING_DEFS_HPP_

#define MAX_BAG_HEIGHT                            20   // Biggest player bag dimensions.
#define MAX_BAG_WIDTH                             20   // Biggest player bag dimensions.
#define PARTICLE_SPEED_DROPPED_ITEM_ASCII_MS      500  // Not used yet, if ever
#define PARTICLE_SPEED_DROPPED_ITEM_PIXELART_MS   500  // For dropping potions etc...
#define PARTICLE_SPEED_INVENTORY_ITEM_ASCII_MS    500  // Not used yet, if ever
#define PARTICLE_SPEED_INVENTORY_ITEM_PIXELART_MS 500  // For dropping items from the inventory to the sidebat
#define PARTICLE_SPEED_THROWN_ITEM_ASCII_MS       500  // Not used yet, if ever
#define PARTICLE_SPEED_THROWN_ITEM_PIXELART_MS    500  // For dropping potions etc...
#define PARTICLE_SPEED_THROWN_WEAPON_ASCII_MS     400  // Is used for throwing darts etc...
#define PARTICLE_SPEED_THROWN_WEAPON_PIXELART_MS  200  // For throwing darts etc...
#define PARTICLE_SPEED_SPELL_CAST_ASCII_MS        400  // Casting spells
#define PARTICLE_SPEED_SPELL_CAST_PIXELART_MS     200  // Casting spells
#define TEMPERATURE_MAX                           1000 // Celcius
#define TEMPERATURE_MIN                           -273 // Celcius
#define TEMPERATURE_ROOM                          20   // Celcius
#define TEMPERATURE_THRESHOLD                     50   // Consider things cold or hot when outside this range (-X..X)
#define THING_AI_CAN_SEE_SECRET_DOOR_DIST         3    // How close to a secret door can a monst see it?
#define THING_AI_ESCAPE_ATTEMPTS                  4    // Quite CPU heavy
#define THING_AI_MAX_AVOID_ATTEMPT_LOC            100  // How many places to look at per attempt to avoid something
#define THING_AI_MAX_WANDER_LOC                   10   // How many places to look at per wander attempt
#define THING_AI_MAX_AVOID_COUNT                  10   // Count to keep track of avoid attempts
#define THING_AI_MAX_GOAL_PENALTY                 100  // Helps to avoid goal oscillation
#define THING_AI_MAX_RESENT_COUNT                 100  // Count to keep track of resentfulness
#define THING_AI_WANDER_TRIES                     1    // Quite CPU heavy
#define THING_DAMAGE_SHAKE_ABOVE                  10   // Damage above this causes shakes
#define THING_DAMAGE_SHAKE_SCALE                  40.0 // Smaller means more shaking
#define THING_FALL_SPEED_MS                       1000 // Fall animation speed
#define THING_HEALTH_BLOODIED_PCT1                35   // Some blood on the screen
#define THING_HEALTH_BLOODIED_PCT2                25   // More...
#define THING_HEALTH_BLOODIED_PCT3                15   // More...
#define THING_HEALTH_BLOODIED_PCT4                5    // Lots of blood on screen
#define THING_HUNGER_FULL                         100  // Creature is full but not satiated
#define THING_HUNGER_MAX                          150  // Creature is the most full it can ever be.
#define THING_HUNGER_PENALTY_WHEN_HUNGRY          1    // Attack and defence penalties
#define THING_HUNGER_PENALTY_WHEN_STARVING        2    // Penalties when in dire straits.
#define THING_HUNGER_SATIATED                     80   // Satiated hunger level.
#define THING_JUMP_HEIGHT                         20   // Height in pixels
#define THING_JUMP_SPEED_MS                       450  // Jump animation speed
#define THING_MOVE_SPEED_FAST_MS                  25   // Movement when we have a cursor path
#define THING_MOVE_SPEED_SLOW_MS                  150  // Normal movement speed
#define THING_TICK_DURATION_TOO_LONG              20   // How many ms per thing tick we expect not to exceed
#define THING_TICK_WAIT_TOO_LONG                  100  // How many ticks we wait for things to stop moving
#define THING_CAN_SEE_INTO_SHADOWS_DISTANCE       2    // Allows the cursor to find paths just out of view
#define TELEPORT_DISTANCE_MAX                     (MAP_WIDTH / 2) // How far can things teleport

#endif
