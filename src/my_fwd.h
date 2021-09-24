//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#pragma once
#ifndef _MY_FWD_H_
#define _MY_FWD_H_

class Charmap;
class Font;
class Level;
class Light;
class Room;
class LevelStatic;
class Tex;
class Tile;
class Tp;
class World;
class Wid;
struct AgeMap_;
struct Dmap_;
struct Monst_;
struct SDL_Surface;
struct Thing_;
struct ascii_;
struct Dmap_;
using Fontp        = class Font *;
using Dmapp        = struct Dmap_ *;
using Levelp       = class Level *;
using LevelStaticp = class LevelStatic *;
using Lightp       = class Light *;
using Monstp       = struct Monst_ *;
using Roomp        = class Room *;
using Texp         = class Tex *;
using Thingp       = struct Thing_ *;
using Tilep        = class Tile *;
using Tpp          = class Tp *;
using Widp         = class Wid *;
using Worldp       = class World *;

#endif
