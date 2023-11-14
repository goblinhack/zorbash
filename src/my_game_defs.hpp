//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_GAME_DEFS_HPP_
#define _MY_GAME_DEFS_HPP_

//
// Grid chunks are used to construct the levels and the overall dungeon
//
#define DUNGEON_GRID_CHUNK_HEIGHT_MAX 3  // Levels are split into grids. Each grid can have a room.
#define DUNGEON_GRID_CHUNK_WIDTH_MAX  7  // Rooms across and down
#define DUNGEONS_GRID_CHUNK_HEIGHT    10 // The whole underworld
#define DUNGEONS_GRID_CHUNK_WIDTH     10 //
#define DUNGEON_MAX_DEPTH             3  // Max difficulty level
#define DUNGEONS_MAX_DIFFICULTY_LEVEL 8  // Max difficulty level
#define MAX_GRID_CHUNK_HEIGHT         DUNGEONS_GRID_CHUNK_HEIGHT
#define MAX_GRID_CHUNK_WIDTH          DUNGEONS_GRID_CHUNK_WIDTH

//
// How granular gas is. This divides up a single tile.
//
#define DUNGEON_GAS_RESOLUTION 4

#define LEVEL_LOUDEST_SOUND        100 // Decibels
#define LEVEL_SOUND_DAMPENING      4   // The higher this is, the less sounds travels
#define LEVEL_FADE_IN_MS           500 // Level start fade animation time
#define LEVEL_FADE_OUT_MS          500 // Level end fade animation time
#define LEVEL_MONST_COUNT_INIT_MAX 25  // Monsters max per level at creation. Want more? You're mad...
#define LEVEL_MONST_COUNT_ABS_MAX  50  // Monsters max per level period.
#define LEVEL_REDRAW_BG_DELAY_MS   50  // Frequency to redraw the entire background when things change

//
// The border needs to be big enough so that the player is not
// obscured by the left bar. This is about this many tiles:
//
#define MAP_BORDER_ROCK                6               // Map rock border
#define MAP_BORDER_AROUND_STAIRS_WIDE  MAP_BORDER_ROCK // Avoid placing big things too close to the entrance
#define MAP_BORDER_AROUND_STAIRS_SMALL 3               // Avoid placing small things too close to the entrance
#define MAP_BORDER_ROOM                1               // Room border padding
#define MAP_ROOM_HEIGHT                11              // Max room dimensions
#define MAP_ROOM_WIDTH                 11              // Max room dimensions

#define MAP_BORDER_ASCII_AUTO_SCROLL 8 // Ascii map scroll threshold

extern int MAP_HEIGHT;
extern int MAP_WIDTH;
extern int DUNGEON_GRID_CHUNK_HEIGHT;
extern int DUNGEON_GRID_CHUNK_WIDTH;

#define MAP_HEIGHT_MAX ((DUNGEON_GRID_CHUNK_HEIGHT_MAX * (MAP_ROOM_HEIGHT + MAP_BORDER_ROOM)) + (MAP_BORDER_ROCK * 2))
#define MAP_WIDTH_MAX  ((DUNGEON_GRID_CHUNK_WIDTH_MAX * (MAP_ROOM_WIDTH + MAP_BORDER_ROOM)) + (MAP_BORDER_ROCK * 2))

#define LEVELS_ACROSS MAP_WIDTH_MAX // World size; no world yet...
#define LEVELS_DOWN   MAP_HEIGHT_MAX
#define LEVELS_DEEP   (DUNGEONS_GRID_CHUNK_HEIGHT * 2)

#define SKILL_TREE_ACROSS 8
#define SKILL_TREE_DOWN   8

#define SPELL_TREE_ACROSS 8
#define SPELL_TREE_DOWN   8

#define GAME_MONST_HEALTH_BAR_STEPS 16
#define GAME_MOST_ZOOMED_IN         5
#define GAME_MOST_ZOOMED_OUT        1
#define GAME_DEFAULT_UI_ZOOM        1
#define GAME_DEFAULT_PIX_ZOOM       GAME_MOST_ZOOMED_IN

//
// So the mini map looks square even though the map is not
//
#define MAP_MINI_HEIGHT (MAP_HEIGHT * (MAP_WIDTH / MAP_HEIGHT))

#define LIGHT_MAX_RAYS      180 // Max light rays cast
#define LIGHT_FLICKER_SPEED 10  // Max light rays cast
//
// Max things per map slot. This also includes carried items, as they really do
// exist in the same place as the player; and might catch fire for example. Hence
// the slot count has to be large enough for all carried items and whatever is
// at this tile.
//
#define MAP_SLOTS 256

#endif
