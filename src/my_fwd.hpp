//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FWD_HPP_
#define _MY_FWD_HPP_

#include <vector>

class ThingAttackOptions_;
class Charmap;
class Font;
class Level;
class LevelStatic;
class Light;
class Particle_;
class Projectile_;
class Room;
class Tex;
class Skill;
class Spell;
class Thing_;
class Tile;
class Tp;
class Wid;
class WidBag;
class WidPopup;
class World;

struct AgeMap_;
struct ascii_;
struct Dmap_;
struct FovMap_;
struct SDL_Surface;
struct ThingAi_;
struct ThingInfo_;

using Dmapp               = struct Dmap_ *;
using Dungeonp            = class Dungeon *;
using Fontp               = class Font *;
using Levelp              = class Level *;
using LevelStaticp        = class LevelStatic *;
using Lightp              = class Light *;
using Particlep           = class Particle_ *;
using Projectilep         = class Projectile_ *;
using Roomp               = class Room *;
using Texp                = class Tex *;
using Skillp              = class Skill *;
using Spellp              = class Spell *;
using ThingAip            = struct ThingAi_ *;
using ThingInfop          = struct ThingInfo_ *;
using ThingItemsp         = struct ThingItem_ *;
using Thingp              = class Thing_ *;
using ThingAttackOptionsp = class ThingAttackOptions_ *;
using Tilemap             = std::vector< class Tile * >;
using Tilep               = class Tile *;
using TpId                = unsigned short;
using Tpp                 = class Tp *;
using Widp                = class Wid *;
using Worldp              = class World *;

#endif
