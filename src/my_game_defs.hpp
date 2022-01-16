//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

//
// Grid chunks are used to construct the levels and the overall dungeon
//
#define DUNGEON_GRID_CHUNK_HEIGHT  4  // Levels are split into grids. Each grid can have a room.
#define DUNGEON_GRID_CHUNK_WIDTH   4  // Rooms across and down
#define DUNGEONS_GRID_CHUNK_HEIGHT 10 // The whole underworld
#define DUNGEONS_GRID_CHUNK_WIDTH  10 //
#define DUNGEONS_MAX_DEPTH         8  // Max difficulty level
#define MAX_GRID_CHUNK_HEIGHT      DUNGEONS_GRID_CHUNK_HEIGHT
#define MAX_GRID_CHUNK_WIDTH       DUNGEONS_GRID_CHUNK_WIDTH

#define LEVEL_FADE_IN_MS   500 // Level start fade animation time
#define LEVEL_FADE_OUT_MS  500 // Level end fade animation time
#define LEVELS_MONST_COUNT 100 // Monsters max per level. Want more? You're mad...

#define MAP_BORDER_ROCK 3  // Map rock border; keep at 3 as jump AI looks 2 tiles adjacent
#define MAP_BORDER_ROOM 10 // Room border padding
#define MAP_ROOM_HEIGHT 13 // Max room dimensions
#define MAP_ROOM_WIDTH  13 // Max room dimensions

#define LEVELS_ACROSS MAP_WIDTH // World size; no world yet...
#define LEVELS_DOWN   MAP_HEIGHT
#define LEVELS_DEEP   DUNGEONS_GRID_CHUNK_HEIGHT * 2

#define MAP_HEIGHT ((DUNGEON_GRID_CHUNK_HEIGHT * MAP_ROOM_HEIGHT) + (MAP_BORDER_ROOM * 2))
#define MAP_WIDTH  ((DUNGEON_GRID_CHUNK_WIDTH * MAP_ROOM_WIDTH) + (MAP_BORDER_ROOM * 2))

#define LIGHT_MAX_RAYS 180 // Max light rays cast
#define MAP_SLOTS      32  // Max things per map slot

#endif
