//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FWD_HPP_
#define _MY_FWD_HPP_

class Charmap;
class Font;
class Level;
class LevelStatic;
class Light;
class Room;
class Tex;
class Tile;
class Tp;
class Wid;
class World;
class Thing_;
class WidPopup;
class WidBag;
struct AgeMap_;
struct Dmap_;
struct FovMap_;
struct ThingInfo_;
struct ThingAi_;
struct SDL_Surface;
struct ascii_;

using Dmapp        = struct Dmap_ *;
using Fontp        = class Font *;
using LevelStaticp = class LevelStatic *;
using Levelp       = class Level *;
using Lightp       = class Light *;
using ThingInfop   = struct ThingInfo_ *;
using ThingItemsp  = struct ThingItem_ *;
using ThingAip     = struct ThingAi_ *;

using Dungeonp = class Dungeon *;
using Roomp    = class Room *;
using Texp     = class Tex *;
using Thingp   = class Thing_ *;
using Tilep    = class Tile *;
using Tpp      = class Tp *;
using Widp     = class Wid *;
using Worldp   = class World *;

#endif
