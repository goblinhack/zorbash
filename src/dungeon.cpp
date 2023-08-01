//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_ascii.hpp"
#include "my_dmap.hpp"
#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_level_static.hpp"
#include "my_player.hpp"
#include "my_room.hpp"
#include "my_sdl_proto.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_console.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"

//
// The algorithm
//
// - Create a cyclic dungeon map. Different 'levels' of the dungeon can be
// cycles with a door of some kind to the next level.
//
//    K         S    D    K
//    1____1____1____2____2    -
//    |    |    |         |
//    |    |    |         |
//    |    |    |         |
//    |    |    |        D|   D
//    1    1____1    -    3____4
//    ?                   |    |
//    ?                   |    |
//    ?                   |    |
//    ?                  K|   E|
//    1____1____2    -    3    4
//
//  - Place initial small rooms
//
//  - Now we know we have a possible level, replace some of the small rooms
//  with larger rooms, so it looks more interesting.
//
//  xDxxxxx                                                         xDxxx
// xx.....D               xDx      xDxxDx                           D...xxx
// D......x               D.xx     x.xx.x      xxDxxx               x.....x
// x......x               x..xx    x....x      x..$.D               x.....x
// xxxxDxxx               x...x    x....x      D....x              xx..x..x
//                        x...xx   xx...x      x....x              x......D
//                        xxx..x    xxx.D      xxxDxx              x...xxxx
//                          xDxx      xDx                          xDxxx
//                                 xDx              xxxxx
//                                 x.x              D...D         xxxxx
//                                xx.xx             x...x         D...D
//   xxxxDxxxxx                  xx...xDx           x...xxxxDxxxx x...xxxxxxxxx
//   x........D                  x......x           x...........D x...........D
//   xxxx..xxxx          xDxxxx  x......xx          x...........x xxxx...xxxxxx
//      D..D             D....D  D.......x          x...........x    D...x
//   xxxx..xxxx          x....xx xDxxxxxxx          x...........x xxxx...x
//   D........x          xx....D                    xxxDxxxxxxxxx x......x
//   xxxxxDxxxx           xx...x                                  xxxDxxxx
//                         xx..x
//           xxxxDx         xxDx  xDxx
//           D....x               D..xx                             xxxxxDx
//           x....D  xxDxx        x...xx                xxxxDxx     x.xx..D
//           x...xx xx...D        x....D                x.....D     x.....x
//           D.xxx  D....x        x.xDxx                D.....x     x.....x
//           xDx    xx..xx        xDx                   x.....x     xxxxxxx
//                   xx.x                               xxxDxxx
//                    xDx
//
//
//  - Drag all the rooms to the center of the map, making sure to keep enough
//  of a gap for corridors
//
//                                                   xDxxx
//                                  xDxxDx           D...xxx
//                  xDxxxxx         x.xx.x           x.....x
//                 xx.....D  xDx    x....x  xxDxxx   x.....x
//                 D......x  D.xx   x....x  x..$.D  xx..x..x
//                 x......x  x..xx  xx...x  D....x  x......D  xxxxx
//                 xxxxDxxx  x...x   xxx.D  x....x  x...xxxx  D...D
//                           x...xx    xDx  xxxDxx  xDxxx     x...xxxxxxxxx
//                           xxx..x                           x...........D
//              xxxxDxxxxx     xDxx    xDx                    xxxx...xxxxxx
//              x........D             x.x      xxxxx            D...x
//              xxxx..xxxx            xx.xx     D...D         xxxx...x
//                 D..D     xDxxxx   xx...xDx   x...x         x......x
//              xxxx..xxxx  D....D   x......x   x...xxxxDxxxx xxxDxxxx
//              D........x  x....xx  x......xx  x...........D
//              xxxxxDxxxx  xx....D  D.......x  x...........x
//                           xx...x  xDxxxxxxx  x...........x
//                            xx..x             x...........x
//                     xxxxDx  xxDx             xxxDxxxxxxxxx
//                     D....x         xDxx
//                     x....D         D..xx            xxxxxDx
//                     x...xx  xxDxx  x...xx  xxxxDxx  x.xx..D
//                     D.xxx  xx...D  x....D  x.....D  x.....x
//                     xDx    D....x  x.xDxx  D.....x  x.....x
//                            xx..xx  xDx     x.....x  xxxxxxx
//                             xx.x           xxxDxxx
//                              xDx
//
//  - Now draw corridors, according to the original node layout. Make sure no
//  corridors overlap or touch.
//
//                                                   xxxxx
//                                  xxxxxx          #D...xxx
//                  xxxxxxx         x.xx.x         ##x.....x
//                 xx.....D# xxx    x....x  xxxxxx## x.....x
//                 x......x##D.xx   x....x  x..$.D# xx..x..x
//                 x......x  x..xx  xx...x #D....x  x......x  xxxxx
//                 xxxxDxxx  x...x   xxx.D##x....x  x...xxxx  x...x
//                   ###     x...xx    xDx  xxxxxx  xDxxx     x...xxxxxxxxx
//                  ##       xxx..x     #            #        x...........x
//              xxxxDxxxxx     xDxx    xDx           #        xxxx...xxxxxx
//              x........x    ###      x.x      xxxxx##      ####D...x
//              xxxx..xxxx   ##       xx.xx     x...x ##     #xxxx...x
//                 x..x     xDxxxx   xx...xxx   x...x  ##    #x......x
//              xxxx..xxxx  x....x   x......x   x...xxxxDxxxx#xxxDxxxx
//              x........x  x....xx  x......xx  x...........D#   #
//              xxxxxDxxxx  xx....D##D.......x  x...........x    #
//                   ??????  xx...x  xxxxxxxxx  x...........x   ##
//                        ??  xx..x             x...........x  ##
//                     xxxxDx  xxxx             xxxDxxxxxxxxx ##
//                     x....x         xxxx         #        ###
//                     x....D#       #D..xx       ##   xxxxxDx
//                     x...xx# xxxxx##x...xx  xxxxDxx  x.xx..x
//                     x.xxx #xx...D# x....x  x.....x  x.....x
//                     xxx   #D....x  x.xxxx  x.....x  x.....x
//                            xx..xx  xxx     x.....x  xxxxxxx
//                             xx.x           xxxxxxx
//                              xxx
//
//

void Dungeon::make_dungeon(void)
{
  TRACE_NO_INDENT();

  //
  // Create the high level blueprint of the level layout
  //
  DBG2("INF: Created node map");
  create_node_map();

  for (;;) {
    //
    // Reset the list of rooms we can place. We only place one of
    // each possible room once per level
    //
    DBG2("INF: Try to create");
    reset_possible_rooms();

    //
    // Create a cyclic dungeon map.
    //
    DBG2("INF: Create cyclic rooms");
    if (! create_cyclic_rooms(&grid)) { continue; }
    TRACE_NO_INDENT();
    debug("create cyclic rooms");

    //
    // Choose how rooms are linked
    //
    DBG2("INF: Choose room doors");
    choose_room_doors();
    TRACE_NO_INDENT();
    debug("choose room doors");

    //
    // Drag rooms closer together
    //
    DBG2("INF: Move rooms closer");

    if (rooms_move_closer_together()) { break; }

    DBG2("INF: Failed, retry");
    debug("failed to place dungeon");
    failed = true;
    return;
  }

  //
  // Keep track of which tile has which room
  //
  DBG2("INF: Assign rooms to tiles");
  assign_rooms_to_tiles();
  TRACE_NO_INDENT();
  debug("assigned rooms to tiles");

  //
  // Wall off secret doors
  //
  DBG2("INF: Block secret doors");
  block_secret_doors();
  TRACE_NO_INDENT();
  debug("blocked secret doors");

  //
  // Remove all doors and then add them back in, but only between
  // depth changes
  //
  DBG2("INF: Remove all rooms");
  remove_all_doors();
  TRACE_NO_INDENT();
  debug("remove all doors");

  //
  // Place the rooms back on the map, so if there were any intentional
  // doors removed above then they will reappear.
  //
  DBG2("INF: Place rooms with doors");
  room_print_only_doors(&grid);
  TRACE_NO_INDENT();
  debug("only doors");

  if (biome != BIOME_CHASMS) {
    //
    // Not sure we want this as rooms
    //
    DBG2("INF: Place doors between room depth changes");
    place_doors_between_depth_changes();
    TRACE_NO_INDENT();
    debug("add doors between depth changes");

    //
    // Add a perimeter to the level. Helps avoid off by one bugs.
    //
    DBG2("INF: Add corridor walls");
    add_corridor_walls();
    TRACE_NO_INDENT();
    debug("add corridor walls");

    DBG2("INF: Add room walls");
    add_room_walls();
    TRACE_NO_INDENT();
    debug("add room walls");
  }

  IF_DEBUG2
  {
    LOG("Created basic layout:");
    dump();
  }

  //
  // Add a cave as the under-dungeon
  //
  if (biome == BIOME_LAVA) {
    DBG2("INF: Generate lava");

    lava_gen(2000, // fill prob
             10,   // R1
             5,    // R2
             4 /* generations */);
  }

  if (biome == BIOME_ICE) {
    DBG2("INF: Generate ice");

    ice_gen(2000, // fill prob
            10,   // R1
            5,    // R2
            4 /* generations */);
  }

  if ((biome != BIOME_CHASMS) && (biome != BIOME_LAVA) && (biome != BIOME_ICE)) {
    DBG2("INF: Generate water");

    water_gen(2000, // fill prob
              10,   // R1
              5,    // R2
              4 /* generations */);

    if (biome == BIOME_SWAMP) {
      water_gen(2000, // fill prob
                10,   // R1
                5,    // R2
                4 /* generations */);
    }

    DBG2("INF: Generate caves");
    cave_gen(2000, // fill prob
             10,   // R1
             5,    // R2
             3 /* generations */);

    DBG2("INF: Generate dirt");
    dirt_gen(2000, // fill prob
             10,   // R1
             5,    // R2
             4 /* generations */);

    DBG2("INF: Add deepwater and islands of safety");
    water_fixup();
  }

  DBG2("INF: Add border");
  add_border();

  DBG2("INF: Add remaining items");
  add_remaining();

  //
  // Add a cave as the under-dungeon
  //
  if (biome == BIOME_SWAMP) {
    foliage_gen(2000, // fill prob
                10,   // R1
                5,    // R2
                2 /* generations */);
  }

  if (biome != BIOME_CHASMS) {
    DBG2("INF: Add spiderwebs");
    add_spiderweb();
  }

  if (biome != BIOME_CHASMS) {
    DBG2("INF: Generate dry grass");
    grass_dry_gen(1500, // fill prob
                  10,   // R1
                  5,    // R2
                  2 /* generations */);
  }

  if (biome == BIOME_SWAMP) {
    DBG2("INF: Generate dry grass");
    grass_dry_gen(1500, // fill prob
                  10,   // R1
                  5,    // R2
                  2 /* generations */);

    DBG2("INF: Generate fungus");
    fungus_withered_gen(100, // fill prob
                        3,   // R1
                        1,   // R2
                        2 /* generations */);
    fungus_healing_gen(100, // fill prob
                       3,   // R1
                       1,   // R2
                       2 /* generations */);
    fungus_poison_gen(100, // fill prob
                      10,  // R1
                      1,   // R2
                      2 /* generations */);
    fungus_edible_gen(100, // fill prob
                      10,  // R1
                      1,   // R2
                      2 /* generations */);
  }

  if (biome == BIOME_DUNGEON) {
    DBG2("INF: Generate fungus");
    fungus_withered_gen(50, // fill prob
                        3,  // R1
                        1,  // R2
                        2 /* generations */);
    fungus_healing_gen(50, // fill prob
                       3,  // R1
                       1,  // R2
                       2 /* generations */);
    fungus_poison_gen(30, // fill prob
                      10, // R1
                      1,  // R2
                      2 /* generations */);
    fungus_edible_gen(20, // fill prob
                      10, // R1
                      1,  // R2
                      2 /* generations */);
  }

  DBG2("INF: Generate wet grass");
  grass_wet_gen(1000, // fill prob
                10,   // R1
                5,    // R2
                2 /* generations */);

  DBG2("INF: Generate foliage");
  foliage_gen(10, // fill prob
              10, // R1
              5,  // R2
              2 /* generations */);

  DBG2("INF: Add foliage around water");
  add_foliage_around_water();

  dump();
}

char *Dungeon::cell_addr(const int x, const int y, const int z)
{
  if (unlikely(is_oob(x, y, z))) { return nullptr; }

  return (getptr(cells, offset(x, y, z)));
}

char *Dungeon::cell_addr_no_check(const int x, const int y, const int z) { return (getptr(cells, offset(x, y, z))); }

bool Dungeon::is_oob(const int x, const int y, const int z)
{
  return ((x < 0) || (x >= map_width) || (y < 0) || (y >= map_height) || (z < 0) || (z >= map_depth));
}

bool Dungeon::is_oob(const int x, const int y)
{
  return ((x < 0) || (x >= map_width) || (y < 0) || (y >= map_height));
}

void Dungeon::debug(const std::string s)
{
  IF_DEBUG2
  {
    LOG("DUNGEON (%u) %s", seed, s.c_str());
    LOG("===========================================================");
    dump();
  }
}

//
// Make a dungeon from rooms
//
Dungeon::Dungeon(biome_t biome, int map_width, int map_height, int grid_width, int grid_height, uint32_t seed)
    : map_width(map_width), map_height(map_height), grid_width(grid_width), grid_height(grid_height), seed(seed)
{
  TRACE_NO_INDENT();
  this->biome = biome;
  make_dungeon();
}

Dungeon::~Dungeon() { delete nodes; }

//
// Make a dungeon from a single level
//
Dungeon::Dungeon(biome_t biome, int level)
{
  TRACE_NO_INDENT();
  if (level >= (int) LevelStatic::all_static_levels.size()) {
    ERR("Out of range level %d", level);
    return;
  }

  this->biome = biome;
  auto l      = get(LevelStatic::all_static_levels, level);

  cells.resize(l->width * l->height * MAP_DEPTH, Charmap::SPACE);
  std::fill(cells.begin(), cells.end(), Charmap::SPACE);

  place_level(l);
  IF_DEBUG2 { dump(); }
}

int Dungeon::offset(const int x, const int y, const int z)
{
  auto offset = (map_width * map_height) * z;
  offset += (map_width) *y;
  offset += x;

  return offset;
}

int Dungeon::offset(const int x, const int y)
{
  auto offset = (map_width) *y;
  offset += x;

  return offset;
}

//
// Puts a tile on the map
//
void Dungeon::putc(const int x, const int y, const int z, const char c)
{
  if (! c) { ERR("Putting nul char at %d,%d,%d", x, y, z); }
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }
  auto p = cell_addr(x, y, z);
  if (p != nullptr) { *p = c; }
}

//
// Puts a tile on the map
//
void Dungeon::putc_no_check(const int x, const int y, const int z, const char c)
{
  auto p = cell_addr_no_check(x, y, z);
  if (p != nullptr) { *p = c; }
}

//
// Gets a tile of the map or None
//
char Dungeon::getc(const int x, const int y, const int z)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }
  auto p = cell_addr(x, y, z);
  if (p != nullptr) { return (*p); }
  return (Charmap::NONE);
}

//
// Gets a tile of the map or None
//
char Dungeon::getc_no_check(const int x, const int y, const int z)
{
  auto p = cell_addr_no_check(x, y, z);
  if (p != nullptr) { return (*p); }
  return (Charmap::NONE);
}

Roomp *Dungeon::cell_rooms_addr(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { return nullptr; }

  return (getptr(cells_room, offset(x, y)));
}

Roomp *Dungeon::cell_rooms_addr_no_check(const int x, const int y) { return (getptr(cells_room, offset(x, y))); }

void Dungeon::putr(const int x, const int y, Roomp r)
{
  auto p = cell_rooms_addr(x, y);
  if (p != nullptr) { *p = r; }
}

Roomp Dungeon::getr(const int x, const int y)
{
  auto p = cell_rooms_addr(x, y);
  if (p != nullptr) { return (*p); }
  return nullptr;
}

Roomp Dungeon::getr_no_check(const int x, const int y)
{
  auto p = cell_rooms_addr_no_check(x, y);
  if (p != nullptr) { return (*p); }
  return nullptr;
}

bool Dungeon::is_anything_at(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    if ((c != Charmap::NONE) && (c != Charmap::SPACE)) { return true; }
  }
  return false;
}

bool Dungeon::is_anything_at(const int x, const int y, const int z)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  auto c = getc(x, y, z);
  return (c != Charmap::NONE) && (c != Charmap::SPACE);
}

int Dungeon::get_grid_depth_at(const int x, const int y)
{
  if (! nodes) { return 0; }

  auto r = getr(x, y);
  if (r) { return (r->depth); }
  return 0;
}

bool Dungeon::is_floor(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_floor) { return true; }
  }
  return false;
}

bool Dungeon::is_corridor(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_corridor) { return true; }
  }
  return false;
}

bool Dungeon::is_bridge(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_bridge) { return true; }
  }
  return false;
}

bool Dungeon::is_corridor_no_check(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc_no_check(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_corridor) { return true; }
  }
  return false;
}

bool Dungeon::is_dirt(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_dirt) { return true; }
  }
  return false;
}

bool Dungeon::is_dirt_no_check(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc_no_check(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_dirt) { return true; }
  }
  return false;
}

bool Dungeon::is_grass_dry(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_grass_dry) { return true; }
  }
  return false;
}

bool Dungeon::is_grass_wet(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_grass_wet) { return true; }
  }
  return false;
}

bool Dungeon::is_fungus_withered(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_fungus_withered) { return true; }
  }
  return false;
}

bool Dungeon::is_fungus_healing(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_fungus_healing) { return true; }
  }
  return false;
}

bool Dungeon::is_fungus_poison(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_fungus_poison) { return true; }
  }
  return false;
}

bool Dungeon::is_fungus_edible(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_fungus_edible) { return true; }
  }
  return false;
}

bool Dungeon::is_magic_stone(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_magic_stone) { return true; }
  }
  return false;
}

bool Dungeon::is_foliage(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_foliage) { return true; }
  }
  return false;
}

bool Dungeon::is_spiderweb(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_spiderweb) { return true; }
  }
  return false;
}

bool Dungeon::is_portal(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_portal) { return true; }
  }
  return false;
}

bool Dungeon::is_secret_corridor_at(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_secret_corridor) { return true; }
  }
  return false;
}

bool Dungeon::is_wall(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  auto d = MAP_DEPTH_OBJ;
  auto c = getc(x, y, d);
  auto v = get(Charmap::all_charmaps, c);
  return (v.is_wall);
}

bool Dungeon::is_monst_class_A(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_monst_class_A) { return true; }
  }
  return false;
}

bool Dungeon::is_monst_any(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_monst_class_A) { return true; }
    if (v.is_monst_class_B) { return true; }
    if (v.is_monst_class_C) { return true; }
    if (v.is_monst_class_D) { return true; }
    if (v.is_monst_class_E) { return true; }
  }
  return false;
}

bool Dungeon::is_monst_class_B(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_monst_class_B) { return true; }
  }
  return false;
}

bool Dungeon::is_monst_class_C(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_monst_class_C) { return true; }
  }
  return false;
}

bool Dungeon::is_monst_class_D(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_monst_class_D) { return true; }
  }
  return false;
}

bool Dungeon::is_monst_class_E(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_monst_class_E) { return true; }
  }
  return false;
}

bool Dungeon::is_mob_any(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_mob_challenge_class_A) { return true; }
    if (v.is_mob_challenge_class_B) { return true; }
  }
  return false;
}

bool Dungeon::is_mob_challenge_class_A(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_mob_challenge_class_A) { return true; }
  }
  return false;
}

bool Dungeon::is_mob_challenge_class_B(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_mob_challenge_class_B) { return true; }
  }
  return false;
}

bool Dungeon::is_food(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_food) { return true; }
  }
  return false;
}

bool Dungeon::is_brazier(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_brazier) { return true; }
  }
  return false;
}

bool Dungeon::is_barrel(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_barrel) { return true; }
  }
  return false;
}

bool Dungeon::is_fungus(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_fungus) { return true; }
  }
  return false;
}

bool Dungeon::is_trap(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_trap) { return true; }
  }
  return false;
}

bool Dungeon::is_red_blood(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_red_blood) { return true; }
  }
  return false;
}

bool Dungeon::is_rock(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_rock) { return true; }
  }
  return false;
}

bool Dungeon::is_door(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_door) { return true; }
  }
  return false;
}

bool Dungeon::is_secret_door(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_secret_door) { return true; }
  }
  return false;
}

bool Dungeon::is_ascend_dungeon(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_ascend_dungeon) { return true; }
  }
  return false;
}

bool Dungeon::is_floor_deco_at(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_floor_deco) { return true; }
  }
  return false;
}

bool Dungeon::is_descend_sewer_at(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_descend_sewer) { return true; }
  }
  return false;
}

bool Dungeon::is_descend_dungeon(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_descend_dungeon) { return true; }
  }
  return false;
}

bool Dungeon::is_descend_sewer(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_descend_sewer) { return true; }
  }
  return false;
}

bool Dungeon::is_lava(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_lava) { return true; }
  }
  return false;
}

bool Dungeon::is_block_of_ice(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_block_of_ice) { return true; }
  }
  return false;
}

bool Dungeon::is_chasm(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_chasm) { return true; }
  }
  return false;
}

bool Dungeon::is_shallow_water(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_shallow_water) { return true; }
  }
  return false;
}

bool Dungeon::is_deep_water(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_deep_water) { return true; }
  }
  return false;
}

bool Dungeon::is_hazard(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_deep_water) { return true; }
    if (v.is_shallow_water) { return true; }
    if (v.is_chasm) { return true; }
    if (v.is_lava) { return true; }
    if (v.is_block_of_ice) { return true; }
  }
  return false;
}

bool Dungeon::is_treasure_type(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if ((v.is_treasure_class_A) || (v.is_treasure_class_B) || (v.is_treasure_class_C)) { return true; }
  }
  return false;
}

bool Dungeon::is_treasure_class_A(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_treasure_class_A) { return true; }
  }
  return false;
}

bool Dungeon::is_treasure_class_B(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_treasure_class_B) { return true; }
  }
  return false;
}

bool Dungeon::is_treasure_class_C(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_treasure_class_C) { return true; }
  }
  return false;
}

bool Dungeon::is_weapon_class_A(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_weapon_class_A) { return true; }
  }
  return false;
}

bool Dungeon::is_weapon_class_B(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_weapon_class_B) { return true; }
  }
  return false;
}

bool Dungeon::is_weapon_class_C(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_weapon_class_C) { return true; }
  }
  return false;
}

bool Dungeon::is_gold(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_gold) { return true; }
  }
  return false;
}

bool Dungeon::is_key(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_key) { return true; }
  }
  return false;
}

bool Dungeon::is_potion(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_potion) { return true; }
  }
  return false;
}

bool Dungeon::is_staff(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_staff) { return true; }
  }
  return false;
}

bool Dungeon::is_ring(const int x, const int y)
{
  if (unlikely(is_oob(x, y))) { DIE("Out of bounds %s at map (%d,%d)", __FUNCTION__, x, y); }

  for (auto d = 0; d < map_depth; d++) {
    auto c = getc(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_ring) { return true; }
  }
  return false;
}

bool Dungeon::is_anything_at_no_check(const int x, const int y)
{
  for (auto d = 0; d < map_depth; d++) {
    auto c = getc_no_check(x, y, d);
    if ((c != Charmap::NONE) && (c != Charmap::SPACE)) { return true; }
  }
  return false;
}

bool Dungeon::is_anything_at_no_check(const int x, const int y, const int z)
{
  auto c = getc_no_check(x, y, z);
  return (c != Charmap::NONE) && (c != Charmap::SPACE);
}

bool Dungeon::is_floor_no_check(const int x, const int y)
{
  const auto d = MAP_DEPTH_FLOOR;
  auto       c = getc_no_check(x, y, d);
  auto       v = get(Charmap::all_charmaps, c);

  return (v.is_floor);
}

bool Dungeon::is_wall_no_check(const int x, const int y)
{
  auto d = MAP_DEPTH_OBJ;
  auto c = getc_no_check(x, y, d);
  auto v = get(Charmap::all_charmaps, c);
  return (v.is_wall);
}

bool Dungeon::is_chasm_no_check(const int x, const int y)
{
  for (auto d = 0; d < map_depth; d++) {
    auto c = getc_no_check(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_chasm) { return true; }
  }
  return false;
}

bool Dungeon::is_shallow_water_no_check(const int x, const int y)
{
  for (auto d = 0; d < map_depth; d++) {
    auto c = getc_no_check(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_shallow_water) { return true; }
  }
  return false;
}

bool Dungeon::is_deep_water_no_check(const int x, const int y)
{
  for (auto d = 0; d < map_depth; d++) {
    auto c = getc_no_check(x, y, d);
    auto v = get(Charmap::all_charmaps, c);

    if (v.is_deep_water) { return true; }
  }
  return false;
}

void Dungeon::create_node_map(void)
{
  if (grid_width > DUNGEON_GRID_CHUNK_WIDTH) {
    ERR("Nodes width overflow. got %d, max %d", grid_width, DUNGEON_GRID_CHUNK_WIDTH);
  }

  if (grid_height > DUNGEON_GRID_CHUNK_HEIGHT) {
    ERR("Nodes height overflow. got %d, max %d", grid_height, DUNGEON_GRID_CHUNK_HEIGHT);
  }

  nodes = new Nodes(biome, grid_width, grid_height, true);
}

void Dungeon::dump(void)
{
  TRACE_NO_INDENT();
  IF_DEBUG2
  {
    LOG("INF: Seed %u (with room depth)", seed);
    for (auto y = 0; y < map_height; y++) {
      std::string s;
      for (auto x = 0; x < map_width; x++) {
        bool got_one = false;
        for (auto d = map_depth - 1; d >= 0; d--) {
          if (! is_anything_at(x, y, d)) { continue; }

          auto m  = getc(x, y, d);
          auto cr = get(Charmap::all_charmaps, m);
          auto c  = cr.c;

          if (! c) { ERR("Unknown map char 0x%X/%c at x %d, y %d, depth %d", m, m, x, y, d); }

          if (is_wall(x, y)) { c = 'X'; }

          s += c;
          got_one = true;
          break;
        }
        if (! got_one) { s += " "; }
      }
      if (s != "") {
        LOG("[%s]", s.c_str());
        // printf("[%s]\n", s.c_str());
      }
    }
  }

  //
  // Pass 2 without room depths
  //
  LOG("INF: Seed %u", seed);
  // printf("INF: Seed %u\n", seed);
  for (auto y = 0; y < map_height; y++) {
    std::string s;
    for (auto x = 0; x < map_width; x++) {
      bool got_one = false;
      for (auto d = map_depth - 1; d >= 0; d--) {
        if (! is_anything_at(x, y, d)) { continue; }

        auto m  = getc(x, y, d);
        auto cr = get(Charmap::all_charmaps, m);
        auto c  = cr.c;

        if (! c) { ERR("Unknown map char %c at x %d, y %d, depth %d", m, x, y, d); }

        s += c;
        got_one = true;
        break;
      }
      if (! got_one) { s += " "; }
    }
    if (s != "") {
      LOG("[%s]", s.c_str());
      // printf("[%s]\n", s.c_str());
    }
  }
}

void Dungeon::reset_possible_rooms(void)
{
  cells.resize(map_width * map_height * MAP_DEPTH, Charmap::SPACE);
  cells_room.resize(map_width * map_height, nullptr);

  std::fill(cells.begin(), cells.end(), Charmap::SPACE);
  std::fill(cells_room.begin(), cells_room.end(), nullptr);

  for (auto &r : Room::all_rooms) {
    r->placed = false;
    r->skip   = false;

    r->which_secret_door_up    = 0;
    r->which_secret_door_down  = 0;
    r->which_secret_door_left  = 0;
    r->which_secret_door_right = 0;
    r->which_door_up           = 0;
    r->which_door_down         = 0;
    r->which_door_left         = 0;
    r->which_door_right        = 0;

    r->left_room  = nullptr;
    r->right_room = nullptr;
    r->up_room    = nullptr;
    r->down_room  = nullptr;

    r->secret_left_room  = nullptr;
    r->secret_right_room = nullptr;
    r->secret_up_room    = nullptr;
    r->secret_down_room  = nullptr;
  }
}

void Dungeon::room_print_at(Roomp r, int x, int y)
{
  TRACE_NO_INDENT();
  r->at.x = x;
  r->at.y = y;
  for (auto z = 0; z < MAP_DEPTH; z++) {
    for (auto dy = 0; dy < r->height; dy++) {
      for (auto dx = 0; dx < r->width; dx++) {
        auto c = get(r->data, dx, dy, z);
        if (c && (c != Charmap::SPACE)) { putc(x + dx, y + dy, z, c); }
      }
    }
  }
}

void Dungeon::room_print_only_doors_at(Roomp r, int x, int y)
{
  TRACE_NO_INDENT();
  for (auto z = 0; z < MAP_DEPTH; z++) {
    for (auto dy = 0; dy < r->height; dy++) {
      for (auto dx = 0; dx < r->width; dx++) {
        auto c = get(r->data, dx, dy, z);
        if (c == Charmap::DOOR) { putc(x + dx, y + dy, z, c); }
      }
    }
  }
}

void Dungeon::room_print_only_doors(Grid *g)
{
  TRACE_NO_INDENT();
  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      Roomp r = get(g->node_rooms, x, y);
      if (r) { room_print_only_doors_at(r, r->at.x, r->at.y); }
    }
  }
}

bool Dungeon::rooms_print_all(Grid *g)
{
  TRACE_NO_INDENT();

  //
  // Try to juggle the rooms around a bit so the don't all line up due
  // to the grid placement approach we use.
  //
  if (pcg_random_range(0, 10) < 5) { return rooms_print_all_with_no_jiggle(g); }
  return rooms_print_all_with_jiggle(g);
}

bool Dungeon::rooms_print_all_with_no_jiggle(Grid *g)
{
  TRACE_NO_INDENT();

  std::fill(cells.begin(), cells.end(), Charmap::SPACE);

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      Roomp r = get(g->node_rooms, x, y);
      if (! r) { return false; }

      auto rx = (x * (MAP_ROOM_WIDTH + MAP_BORDER_ROOM)) + MAP_BORDER_ROCK;
      auto ry = (y * (MAP_ROOM_HEIGHT + MAP_BORDER_ROOM)) + MAP_BORDER_ROCK;
      room_print_at(r, rx, ry);
    }
  }
  return true;
}

bool Dungeon::rooms_print_all_with_jiggle(Grid *g)
{
  TRACE_NO_INDENT();

  //
  // Try to juggle the rooms around a bit so the don't all line up due
  // to the grid placement approach we use.
  //
  int attempts           = 100;
  int room_jiggle_offset = 2;
  while (attempts--) {
    //
    // Try to place all rooms. Clear th map.
    //
    std::fill(cells.begin(), cells.end(), Charmap::SPACE);

    for (auto x = 0; x < grid_width; x++) {
      for (auto y = 0; y < grid_height; y++) {
        auto n = nodes->getn(x, y);
        if (n->depth <= 0) { continue; }

        Roomp r = get(g->node_rooms, x, y);
        if (! r) { return false; }

        auto rx = (x * (MAP_ROOM_WIDTH + MAP_BORDER_ROOM)) + MAP_BORDER_ROCK;
        auto ry = (y * (MAP_ROOM_HEIGHT + MAP_BORDER_ROOM)) + MAP_BORDER_ROCK;

        bool placed = false;
        int  tries  = 100;

        //
        // Jiggle a single room around. Make sure it does not overlap.
        //
        if (pcg_random_range(0, 10) < 3) {
          while (tries--) {
            int nx = rx + pcg_random_range(-room_jiggle_offset, room_jiggle_offset);
            int ny = ry + pcg_random_range(-room_jiggle_offset, room_jiggle_offset);

            if (can_place_room(r, nx, ny)) {
              room_print_at(r, nx, ny);
              placed = true;
              break;
            }
          }
        }

        if (! placed) {
          //
          // Failed to place this room. Try to place it with no jigggle.
          //
          if (can_place_room(r, rx, ry)) {
            room_print_at(r, rx, ry);
            placed = true;
          }

          //
          // Still failed. Try the whole process over again.
          //
          if (! placed) { goto next; }
        }
      }
    }

    //
    // Managed to place all rooms
    //
    return true;

    //
    // Try again
    //
  next:
    continue;
  }

  //
  // Failed all attempts
  //
  return false;
}

bool Dungeon::room_is_a_candidate(int x, int y, const DungeonNode *n, Roomp r)
{
  if (n->biome == BIOME_UNKNOWN) { DIE("No biome set for DungeonNode"); }

  if (n->biome != r->biome) { return false; }

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto o = get(grid.node_rooms, x, y);
      if (o == r) { return false; }
    }
  }

  if ((n->has_door_down || n->has_secret_exit_down) && ! r->doors_down.size()) { return false; }
  if ((n->has_door_up || n->has_secret_exit_up) && ! r->doors_up.size()) { return false; }
  if ((n->has_door_left || n->has_secret_exit_left) && ! r->doors_left.size()) { return false; }
  if ((n->has_door_right || n->has_secret_exit_right) && ! r->doors_right.size()) { return false; }
  if (n->dir_left != r->dir_left) { return false; }
  if (n->dir_right != r->dir_right) { return false; }
  if (n->dir_up != r->dir_up) { return false; }
  if (n->dir_down != r->dir_down) { return false; }
  if (n->is_descend_dungeon) { return (n->is_descend_dungeon == r->is_descend_dungeon); }
  if (n->is_ascend_dungeon) { return (n->is_ascend_dungeon == r->is_ascend_dungeon); }
  if (n->is_lock) { return (n->is_lock == r->is_lock); }
  if (n->is_key) { return (n->is_key == r->is_key); }
  if (n->is_secret) { return (n->is_secret == r->is_secret); }
  if (n->depth != r->depth) { return false; }
  return true;
}

bool Dungeon::room_is_a_candidate_less_restrictive(const DungeonNode *n, Roomp r)
{
  if (n->biome != r->biome) { return false; }

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto o = get(grid.node_rooms, x, y);
      if (o == r) { return false; }
    }
  }

  if ((n->has_door_down || n->has_secret_exit_down) && ! r->doors_down.size()) { return false; }
  if ((n->has_door_up || n->has_secret_exit_up) && ! r->doors_up.size()) { return false; }
  if ((n->has_door_left || n->has_secret_exit_left) && ! r->doors_left.size()) { return false; }
  if ((n->has_door_right || n->has_secret_exit_right) && ! r->doors_right.size()) { return false; }
  if (r->dir_left) { return false; }
  if (r->dir_right) { return false; }
  if (r->dir_up) { return false; }
  if (r->dir_down) { return false; }
  if (n->is_descend_dungeon) { return (n->is_descend_dungeon == r->is_descend_dungeon); }
  if (n->is_ascend_dungeon) { return (n->is_ascend_dungeon == r->is_ascend_dungeon); }
  if (n->is_lock) { return (n->is_lock == r->is_lock); }
  if (n->is_key) { return (n->is_key == r->is_key); }
  if (n->is_secret) { return (n->is_secret == r->is_secret); }
  if (n->depth > r->depth) { return false; }
  return true;
}

bool Dungeon::room_is_a_candidate_any_depth(const DungeonNode *n, Roomp r)
{
  if (n->biome != r->biome) { return false; }

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto o = get(grid.node_rooms, x, y);
      if (o == r) { return false; }
    }
  }

  if ((n->has_door_down || n->has_secret_exit_down) && ! r->doors_down.size()) { return false; }
  if ((n->has_door_up || n->has_secret_exit_up) && ! r->doors_up.size()) { return false; }
  if ((n->has_door_left || n->has_secret_exit_left) && ! r->doors_left.size()) { return false; }
  if ((n->has_door_right || n->has_secret_exit_right) && ! r->doors_right.size()) { return false; }
  if (r->dir_left) { return false; }
  if (r->dir_right) { return false; }
  if (r->dir_up) { return false; }
  if (r->dir_down) { return false; }
  if (n->is_descend_dungeon) { return (n->is_descend_dungeon == r->is_descend_dungeon); }
  if (n->is_ascend_dungeon) { return (n->is_ascend_dungeon == r->is_ascend_dungeon); }
  if (n->is_lock) { return (n->is_lock == r->is_lock); }
  if (n->is_key) { return (n->is_key == r->is_key); }
  if (n->is_secret) { return (n->is_secret == r->is_secret); }
  return true;
}

bool Dungeon::solve(int x, int y, Grid *g)
{
  auto n = nodes->getn(x, y);

  if (! nodes->node_is_a_room(n)) { return true; }

  if (get(g->node_rooms, x, y)) { return true; }

  std::vector< Roomp > candidates;

  if (! Room::all_rooms.size()) { DIE("Failed to load any rooms. Initialization error?"); }

  for (auto r : Room::all_rooms) {
    if (! room_is_a_candidate(x, y, n, r)) { continue; }

    candidates.push_back(r);
  }

  auto ncandidates = candidates.size();
  if (! ncandidates) {
    for (auto r : Room::all_rooms) {
      if (! room_is_a_candidate_less_restrictive(n, r)) { continue; }

      candidates.push_back(r);
    }

    ncandidates = candidates.size();
    if (! ncandidates) {
      for (auto r : Room::all_rooms) {
        if (! room_is_a_candidate_any_depth(n, r)) { continue; }

        candidates.push_back(r);
      }
    }

    ncandidates = candidates.size();
    if (! ncandidates) {
      rooms_print_all(g);
      dump();
      DIE("No grid room candidates at map (%d,%d)", x, y);
      return false;
    }
  }

  auto ri = pcg_random_range(0, ncandidates);
  auto r  = get(candidates, ri);
  set(g->node_rooms, x, y, r);

  if (n->has_door_down) {
    Grid old;
    std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
    if (! solve(x, y + 1, g)) { std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms)); }
  }
  if (n->has_door_up) {
    Grid old;
    std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
    if (! solve(x, y - 1, g)) { std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms)); }
  }
  if (n->has_door_right) {
    Grid old;
    std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
    if (! solve(x + 1, y, g)) { std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms)); }
  }
  if (n->has_door_left) {
    Grid old;
    std::copy(mbegin(g->node_rooms), mend(g->node_rooms), mbegin(old.node_rooms));
    if (! solve(x - 1, y, g)) { std::copy(mbegin(old.node_rooms), mend(old.node_rooms), mbegin(g->node_rooms)); }
  }
  return true;
}

bool Dungeon::create_cyclic_rooms(Grid *g)
{
  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (! n->is_ascend_dungeon) { continue; }
      if (! solve(x, y, g)) {
        dump();
        DIE("Could not solve level at %d,%d", x, y);
      }
      break;
    }
  }

  for (auto x = 0; x < grid_width; x++) {
    for (auto y = 0; y < grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (! n->is_secret) { continue; }
      solve(x, y, g);
    }
  }

  return rooms_print_all(g);
}

void Dungeon::add_border(void)
{
  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_BORDER_ROCK; x++) {
      if (! is_anything_at_no_check(x, y)) { putc(x, y, MAP_DEPTH_OBJ, Charmap::ROCK); }
      if (! is_anything_at_no_check(MAP_WIDTH - (x + 1), y)) {
        putc(MAP_WIDTH - (x + 1), y, MAP_DEPTH_OBJ, Charmap::ROCK);
      }
    }
  }
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_BORDER_ROCK; y++) {
      if (! is_anything_at_no_check(x, y)) { putc(x, y, MAP_DEPTH_OBJ, Charmap::ROCK); }
      if (! is_anything_at_no_check(x, MAP_HEIGHT - (y + 1))) {
        putc(x, MAP_HEIGHT - (y + 1), MAP_DEPTH_OBJ, Charmap::ROCK);
      }
    }
  }

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_BORDER_ROCK; x++) {
      putc(x, y, MAP_DEPTH_OBJ, Charmap::ROCK);
      putc(MAP_WIDTH - (x + 1), y, MAP_DEPTH_OBJ, Charmap::ROCK);
    }
  }
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_BORDER_ROCK; y++) {
      putc(x, y, MAP_DEPTH_OBJ, Charmap::ROCK);
      putc(x, MAP_HEIGHT - (y + 1), MAP_DEPTH_OBJ, Charmap::ROCK);
    }
  }
}

void Dungeon::add_corridor_walls(void)
{
  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      if (is_wall_no_check(x, y)) { continue; }
      if (is_corridor_no_check(x, y)) {
        if (! is_anything_at_no_check(x - 1, y - 1)) { putc(x - 1, y - 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x, y - 1)) { putc(x, y - 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x + 1, y - 1)) { putc(x + 1, y - 1, MAP_DEPTH_OBJ, Charmap::WALL); }

        if (! is_anything_at_no_check(x - 1, y)) { putc(x - 1, y, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x + 1, y)) { putc(x + 1, y, MAP_DEPTH_OBJ, Charmap::WALL); }

        if (! is_anything_at_no_check(x - 1, y + 1)) { putc(x - 1, y + 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x, y + 1)) { putc(x, y + 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x + 1, y + 1)) { putc(x + 1, y + 1, MAP_DEPTH_OBJ, Charmap::WALL); }
      }
    }
  }
}

void Dungeon::add_room_walls(void)
{
  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      if (is_wall_no_check(x, y)) { continue; }
      if (is_floor_no_check(x, y) || is_chasm_no_check(x, y)) {
        if (! is_anything_at_no_check(x - 1, y - 1)) { putc(x - 1, y - 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x, y - 1)) { putc(x, y - 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x + 1, y - 1)) { putc(x + 1, y - 1, MAP_DEPTH_OBJ, Charmap::WALL); }

        if (! is_anything_at_no_check(x - 1, y)) { putc(x - 1, y, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x + 1, y)) { putc(x + 1, y, MAP_DEPTH_OBJ, Charmap::WALL); }

        if (! is_anything_at_no_check(x - 1, y + 1)) { putc(x - 1, y + 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x, y + 1)) { putc(x, y + 1, MAP_DEPTH_OBJ, Charmap::WALL); }
        if (! is_anything_at_no_check(x + 1, y + 1)) { putc(x + 1, y + 1, MAP_DEPTH_OBJ, Charmap::WALL); }
      }
    }
  }
}

//
// Find which doors we want to use for a room
//
void Dungeon::choose_room_doors(void)
{
  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      if (n->depth == nodes->depth_obstacle) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (! r) { continue; }

      if (n->has_door_down) {
        auto o = get(grid.node_rooms, x, y + 1);
        if (! o) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Had exit down at %d,%d, but no node exists", x, y);
        }
        auto rdoori = pcg_random_range(0, r->doors_down.size());
        auto odoori = pcg_random_range(0, o->doors_up.size());
        if (rdoori >= r->doors_down.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug");
        }
        if (odoori >= o->doors_up.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug");
        }

        r->which_door_down = rdoori;
        o->which_door_up   = odoori;

        r->down_room = o;
        o->up_room   = r;
      }

      if (n->has_door_right) {
        auto o = get(grid.node_rooms, x + 1, y);
        if (! o) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Had exit right at %d,%d, but no node exists", x, y);
        }
        auto rdoori = pcg_random_range(0, r->doors_right.size());
        auto odoori = pcg_random_range(0, o->doors_left.size());
        if (rdoori >= r->doors_right.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug");
        }
        if (odoori >= o->doors_left.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug");
        }

        r->which_door_right = rdoori;
        o->which_door_left  = odoori;

        r->right_room = o;
        o->left_room  = r;
      }

      if (n->has_secret_exit_down) {
        auto o = get(grid.node_rooms, x, y + 1);
        if (! o) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Had secret exit down at %d,%d, but no node exists", x, y);
        }
        auto rdoori = pcg_random_range(0, r->doors_down.size());
        auto odoori = pcg_random_range(0, o->doors_up.size());
        if (rdoori >= r->doors_down.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug, room %d, down door index %d size %d", r->roomno, (int) rdoori, (int) r->doors_down.size());
        }
        if (odoori >= o->doors_up.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug, room %d, up door index %d size %d", r->roomno, (int) odoori, (int) r->doors_up.size());
        }

        r->which_secret_door_down = rdoori;
        o->which_secret_door_up   = odoori;

        r->secret_down_room = o;
        o->secret_up_room   = r;
      }

      if (n->has_secret_exit_right) {
        auto o = get(grid.node_rooms, x + 1, y);
        if (! o) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Had secret exit right at %d,%d, but no node exists", x, y);
        }
        auto rdoori = pcg_random_range(0, r->doors_right.size());
        auto odoori = pcg_random_range(0, o->doors_left.size());
        if (rdoori >= r->doors_right.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug, room %d, right door index %d size %d", r->roomno, (int) rdoori, (int) r->doors_right.size());
        }
        if (odoori >= o->doors_left.size()) {
          TRACE_NO_INDENT();
          debug("bug");
          ERR("Bug, room %d, left door index %d size %d", r->roomno, (int) odoori, (int) r->doors_left.size());
        }

        r->which_secret_door_right = rdoori;
        o->which_secret_door_left  = odoori;

        r->secret_right_room = o;
        o->secret_left_room  = r;
      }
    }
  }
}

void Dungeon::save_level(void)
{
  TRACE_NO_INDENT();
  std::copy(mbegin(cells), mend(cells), mbegin(cells_saved));

  for (unsigned int rs = 0; rs < (unsigned int) all_placed_rooms.size(); rs++) {
    auto r = get(all_placed_rooms, rs);
    if (r) { r->rollback_at = r->at; }
  }
}

void Dungeon::restore_level(void)
{
  TRACE_NO_INDENT();
  std::copy(mbegin(cells_saved), mend(cells_saved), mbegin(cells));

  for (unsigned int rs = 0; rs < (unsigned int) all_placed_rooms.size(); rs++) {
    auto r = get(all_placed_rooms, rs);
    if (r) { r->at = r->rollback_at; }
  }
}

int Dungeon::draw_corridor(point start, point end, char w)
{
  TRACE_NO_INDENT();
  Dmap d {};

  DBG("draw corridor from %d,%d to %d,%d", start.x, start.y, end.x, end.y);

  if ((start.x <= 0) || (start.y <= 0) || (start.x >= map_width - 1) || (start.y >= map_height - 1)) { return 0; }
  if ((end.x <= 0) || (end.y <= 0) || (end.x >= map_width - 1) || (end.y >= map_height - 1)) { return 0; }

  //
  // Very close corridors we cannot use dmap as that will be len 0
  //
  if (start + point(1, 1) == end) {
    if (! is_anything_at_no_check(start.x + 1, start.y)) {
      putc(start.x + 1, start.y, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
    if (! is_anything_at_no_check(start.x, start.y + 1)) {
      putc(start.x, start.y + 1, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
  }
  TRACE_NO_INDENT();
  if (start + point(1, -1) == end) {
    if (! is_anything_at_no_check(start.x + 1, start.y)) {
      putc(start.x + 1, start.y, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
    if (! is_anything_at_no_check(start.x, start.y - 1)) {
      putc(start.x, start.y - 1, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
  }
  TRACE_NO_INDENT();
  if (start + point(-1, 1) == end) {
    if (! is_anything_at_no_check(start.x - 1, start.y)) {
      putc(start.x - 1, start.y, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
    if (! is_anything_at_no_check(start.x, start.y + 1)) {
      putc(start.x, start.y + 1, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
  }
  TRACE_NO_INDENT();
  if (start + point(-1, -1) == end) {
    if (! is_anything_at_no_check(start.x - 1, start.y)) {
      putc(start.x - 1, start.y, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
    if (! is_anything_at_no_check(start.x, start.y - 1)) {
      putc(start.x, start.y - 1, MAP_DEPTH_FLOOR, w);
      putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
      return 3;
    }
  }

  //
  // If close, try a direct walk
  //
  TRACE_NO_INDENT();
  if (distance(start, end) < 4) {
    std::vector< point > p;

    auto at = start;

    for (;;) {
      if (at == end) {
        for (auto i : p) {
          putc(i.x, i.y, MAP_DEPTH_FLOOR, w);
        }
        putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
        putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);
        return p.size();
      }

      if (end.x > at.x) {
        point cand = at + point(1, 0);
        if ((cand == end) || ! is_anything_at_no_check(cand.x, cand.y)) {
          p.push_back(cand);
          at = cand;
          continue;
        }
      }
      if (end.x < at.x) {
        point cand = at + point(-1, 0);
        if ((cand == end) || ! is_anything_at_no_check(cand.x, cand.y)) {
          p.push_back(cand);
          at = cand;
          continue;
        }
      }
      if (end.y > at.y) {
        point cand = at + point(0, 1);
        if ((cand == end) || ! is_anything_at_no_check(cand.x, cand.y)) {
          p.push_back(cand);
          at = cand;
          continue;
        }
      }
      if (end.y < at.y) {
        point cand = at + point(0, -1);
        if ((cand == end) || ! is_anything_at_no_check(cand.x, cand.y)) {
          p.push_back(cand);
          at = cand;
          continue;
        }
      }
      break;
    }
  }

#if 0
  if (w == Charmap::CORRIDOR) {
    LOG("Create corridor, between %d,%d and %d,%d", start.x, start.y, end.x, end.y);
  } else {
    LOG("Create secret corridor, between %d,%d and %d,%d", start.x, start.y, end.x, end.y);
  }
#endif

  TRACE_NO_INDENT();
  point dmap_start = start;
  point dmap_end   = end;

  int minx, miny, maxx, maxy;
  if (dmap_start.x < dmap_end.x) {
    minx = dmap_start.x;
    maxx = dmap_end.x;
  } else {
    minx = dmap_end.x;
    maxx = dmap_start.x;
  }
  if (dmap_start.y < dmap_end.y) {
    miny = dmap_start.y;
    maxy = dmap_end.y;
  } else {
    miny = dmap_end.y;
    maxy = dmap_start.y;
  }

  auto border = 2;
  minx -= border;
  miny -= border;
  maxx += border;
  maxy += border;

  if (minx < 0) { minx = 0; }
  if (miny < 0) { miny = 0; }
  if (maxx >= map_width) { maxx = map_width - 1; }
  if (maxy >= map_height) { maxy = map_height - 1; }

  //
  // Set up obstacles for the corridor search
  //
  TRACE_NO_INDENT();
  for (auto y = miny; y < maxy; y++) {
    for (auto x = minx; x < maxx; x++) {
      if (is_anything_at_no_check(x, y)) {
        set(d.val, x, y, DMAP_IS_WALL);
      } else {
        set(d.val, x, y, DMAP_IS_PASSABLE);
      }
    }
  }

  if (biome != BIOME_CHASMS) {
    //
    // Avoid this pattern as it would need a long door
    //
    // D
    // ##
    //  #D
    // ...
    //
    TRACE_NO_INDENT();
    {
      auto x = start.x;
      auto y = start.y;
      if (is_anything_at_no_check(x, y + 1)) {
        set(d.val, x - 1, y, DMAP_IS_WALL);
        set(d.val, x + 1, y, DMAP_IS_WALL);
      }
      if (is_anything_at_no_check(x, y - 1)) {
        set(d.val, x - 1, y, DMAP_IS_WALL);
        set(d.val, x + 1, y, DMAP_IS_WALL);
      }
      if (is_anything_at_no_check(x + 1, y)) {
        set(d.val, x, y - 1, DMAP_IS_WALL);
        set(d.val, x, y + 1, DMAP_IS_WALL);
      }
      if (is_anything_at_no_check(x - 1, y)) {
        set(d.val, x, y - 1, DMAP_IS_WALL);
        set(d.val, x, y + 1, DMAP_IS_WALL);
      }
    }

    TRACE_NO_INDENT();
    {
      auto x = end.x;
      auto y = end.y;
      if (is_anything_at_no_check(x, y + 1)) {
        set(d.val, x - 1, y, DMAP_IS_WALL);
        set(d.val, x + 1, y, DMAP_IS_WALL);
      }
      if (is_anything_at_no_check(x, y - 1)) {
        set(d.val, x - 1, y, DMAP_IS_WALL);
        set(d.val, x + 1, y, DMAP_IS_WALL);
      }
      if (is_anything_at_no_check(x + 1, y)) {
        set(d.val, x, y - 1, DMAP_IS_WALL);
        set(d.val, x, y + 1, DMAP_IS_WALL);
      }
      if (is_anything_at_no_check(x - 1, y)) {
        set(d.val, x, y - 1, DMAP_IS_WALL);
        set(d.val, x, y + 1, DMAP_IS_WALL);
      }
    }

    //
    // Ensure adjoining corridors are not possible
    //
    TRACE_NO_INDENT();
    for (auto y = miny + 1; y < maxy - 1; y++) {
      for (auto x = minx + 1; x < maxx - 1; x++) {
        if (is_corridor_no_check(x, y)) {
          set(d.val, x - 1, y, DMAP_IS_WALL);
          set(d.val, x, y - 1, DMAP_IS_WALL);
          set(d.val, x, y, DMAP_IS_WALL);
          set(d.val, x, y + 1, DMAP_IS_WALL);
          set(d.val, x + 1, y, DMAP_IS_WALL);
        }
      }
    }
  }

  TRACE_NO_INDENT();
  dmap_start = point(minx, miny);
  dmap_end   = point(maxx, maxy);

  set(d.val, end.x, end.y, DMAP_IS_GOAL);
  set(d.val, start.x, start.y, DMAP_IS_PASSABLE);

  dmap_process(&d, dmap_start, dmap_end, false, false);
  auto dmap_mid = dmap_start + dmap_end;
  dmap_mid /= 2;
  IF_DEBUG2 { dmap_print(&d, dmap_mid, dmap_start, dmap_end); }

  auto p = dmap_solve_manhattan(&d, start);

  //
  // Too long a corridor?
  //
  if (p.size() > 25) {
    for (auto c : p) {
      putc(c.x, c.y, MAP_DEPTH_FLOOR, Charmap::DEBUG);
    }
    DBG("cannot create corridor, too long a corridor");
    return 0;
  }

  //
  // Check we can reach the end point
  //
  TRACE_NO_INDENT();
  bool got_goal = false;
  for (auto c : p) {
    if (c == end) {
      got_goal = true;
      break;
    }
  }

  TRACE_NO_INDENT();
  if (! got_goal) {
    for (auto c : p) {
      putc(c.x, c.y, MAP_DEPTH_FLOOR, Charmap::DEBUG);
    }
    putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DEBUG);
    putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DEBUG);

#if 0
    DNG("INF: cannot create corridor, end not found between %d,%d and %d,%d", start.x, start.y, end.x, end.y);
    dump();
#endif
    return 0;
  }

  TRACE_NO_INDENT();
  for (auto c : p) {
    putc(c.x, c.y, MAP_DEPTH_FLOOR, w);
  }

  TRACE_NO_INDENT();
  putc(start.x, start.y, MAP_DEPTH_OBJ, Charmap::DOOR);
  TRACE_NO_INDENT();
  putc(end.x, end.y, MAP_DEPTH_OBJ, Charmap::DOOR);

#if 0
  DBG("INF: placed corridor len %d", (int) p.size());
  dump();
#endif

  return (p.size());
}

//
// Join the corridors of each room, return the total lenght of all corridors
//
int Dungeon::draw_corridors(void)
{
  TRACE_NO_INDENT();
#if 1
  LOG("Draw corridors");
  dump();
#endif

  for (auto x = 0; x < map_width; x++) {
    for (auto y = 0; y < map_height; y++) {
      auto c = getc(x, y, MAP_DEPTH_OBJ);
      if ((c == Charmap::DOOR_UP) || (c == Charmap::DOOR_DOWN) || (c == Charmap::DOOR_LEFT)
          || (c == Charmap::DOOR_RIGHT)) {
        putc(x, y, MAP_DEPTH_OBJ, Charmap::WALL);
      }
    }
  }

  auto total_len = 0;

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {

      auto n = nodes->getn(x, y);
      if (! n->depth) { continue; }

      if (n->depth == nodes->depth_obstacle) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (! r) { continue; }

      if (n->has_door_down) {
        auto o = get(grid.node_rooms, x, y + 1);

        auto rdoori = r->which_door_down;
        auto odoori = o->which_door_up;

        auto rdoor = get(r->doors_down, rdoori);
        auto odoor = get(o->doors_up, odoori);

        auto start = r->at + rdoor;
        auto end   = o->at + odoor;

        r->down_door_at = start;
        o->up_door_at   = end;

        auto len = draw_corridor(start, end, Charmap::CORRIDOR);
        if (! len) { return 0; }
        total_len += len;
      }

      if (n->has_door_right) {
        auto o = get(grid.node_rooms, x + 1, y);

        auto rdoori = r->which_door_right;
        auto odoori = o->which_door_left;

        auto rdoor = get(r->doors_right, rdoori);
        auto odoor = get(o->doors_left, odoori);

        auto start = r->at + rdoor;
        auto end   = o->at + odoor;

        r->right_door_at = start;
        o->left_door_at  = end;

        auto len = draw_corridor(start, end, Charmap::CORRIDOR);
        if (! len) { return 0; }
        total_len += len;
      }

      if (n->has_secret_exit_down) {
        auto o = get(grid.node_rooms, x, y + 1);

        auto rdoori = r->which_secret_door_down;
        auto odoori = o->which_secret_door_up;

        auto rdoor = get(r->doors_down, rdoori);
        auto odoor = get(o->doors_up, odoori);

        auto start = r->at + rdoor;
        auto end   = o->at + odoor;

        r->down_secret_door_at = start;
        o->up_secret_door_at   = end;

        auto len = draw_corridor(start, end, Charmap::SECRET_CORRIDOR);
        if (! len) { return 0; }
        total_len += len;
      }

      if (n->has_secret_exit_right) {
        auto o = get(grid.node_rooms, x + 1, y);

        auto rdoori = r->which_secret_door_right;
        auto odoori = o->which_secret_door_left;

        auto rdoor = get(r->doors_right, rdoori);
        auto odoor = get(o->doors_left, odoori);

        auto start = r->at + rdoor;
        auto end   = o->at + odoor;

        r->right_secret_door_at = start;
        o->left_secret_door_at  = end;

        auto len = draw_corridor(start, end, Charmap::SECRET_CORRIDOR);
        if (! len) { return 0; }
        total_len += len;
      }
    }
  }

  return total_len;
}

void Dungeon::center_room_layout(void)
{
  auto minx = map_width;
  auto miny = map_height;
  auto maxx = 0;
  auto maxy = 0;

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (! r) { continue; }

      if (r->at.x < minx) { minx = r->at.x; }
      if (r->at.y < miny) { miny = r->at.y; }
      if (r->at.x + r->width > maxx) { maxx = r->at.x + r->width; }
      if (r->at.y + r->height > maxy) { maxy = r->at.y + r->height; }
    }
  }

  auto dx = (map_width - (maxx - minx)) / 2;
  auto dy = (map_height - (maxy - miny)) / 2;

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (! r) { continue; }

      r->at.x -= minx;
      r->at.y -= miny;

      r->at.x += dx;
      r->at.y += dy;
    }
  }
}

//
// Dump a room onto the level. No checks
//
void Dungeon::place_room(Roomp r, int x, int y)
{
  //
  // Place the room tiles
  //
  for (auto dz = 0; dz < MAP_DEPTH; dz++) {
    for (auto dy = 0; dy < r->height; dy++) {
      for (auto dx = 0; dx < r->width; dx++) {
        auto c = get(r->data, dx, dy, dz);
        if ((c != Charmap::SPACE) && (c != Charmap::NONE)) { putc_no_check(x + dx, y + dy, dz, c); }
      }
    }
  }

  //
  // Place a border around the room
  //
  for (auto dy = 0; dy < r->height; dy++) {
    for (auto dx = 0; dx < r->width; dx++) {
      auto f = get(r->data, dx, dy, MAP_DEPTH_FLOOR);
      auto c = get(r->data, dx, dy, MAP_DEPTH_CHASM);
      auto d = get(r->data, dx, dy, MAP_DEPTH_OBJ);
      if ((d == Charmap::DOOR_UP) || (d == Charmap::DOOR_DOWN) || (d == Charmap::DOOR_LEFT)
          || (d == Charmap::DOOR_RIGHT)) {
        //
        // Do not wrap doors in walls so we can move the rooms closer
        //
      } else if ((f != Charmap::SPACE) || (c != Charmap::SPACE)) {
        if (! is_anything_at_no_check(x + dx - 1, y + dy - 1)) {
          putc_no_check(x + dx - 1, y + dy - 1, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx, y + dy - 1)) {
          putc_no_check(x + dx, y + dy - 1, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx + 1, y + dy - 1)) {
          putc_no_check(x + dx + 1, y + dy - 1, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx - 1, y + dy)) {
          putc_no_check(x + dx - 1, y + dy, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx + 1, y + dy)) {
          putc_no_check(x + dx + 1, y + dy, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx - 1, y + dy + 1)) {
          putc_no_check(x + dx - 1, y + dy + 1, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx, y + dy + 1)) {
          putc_no_check(x + dx, y + dy + 1, MAP_DEPTH_OBJ, Charmap::WALL);
        }
        if (! is_anything_at_no_check(x + dx + 1, y + dy + 1)) {
          putc_no_check(x + dx + 1, y + dy + 1, MAP_DEPTH_OBJ, Charmap::WALL);
        }
      }
    }
  }
}

void Dungeon::place_level(LevelStaticp l)
{
  if ((l->width > MAP_WIDTH) || (l->height > MAP_HEIGHT)) { ERR("Level has bad size %d,%d", l->width, l->height); }

  for (auto z = 0; z < MAP_DEPTH; z++) {
    for (auto y = 0; y < l->height; y++) {
      for (auto x = 0; x < l->width; x++) {
        auto c = get(l->data, x, y, z);
        if (c && (c != Charmap::SPACE)) { putc(x, y, z, c); }
      }
    }
  }
}

//
// Dump a room onto the level along with its roomno. Done when we
// have finalized positions of rooms.
//
void Dungeon::map_place_room_ptr(Roomp r, int x, int y)
{
  if (! r) { ERR("No room to place"); }

  for (auto dz = 0; dz < MAP_DEPTH; dz++) {
    for (auto dy = 0; dy < r->height; dy++) {
      for (auto dx = 0; dx < r->width; dx++) {
        auto c = get(r->data, dx, dy, dz);
        if (c != Charmap::SPACE) { putr(x + dx, y + dy, r); }
      }
    }
  }
}

//
// Check for room overlaps
//
bool Dungeon::can_place_room(Roomp r, int x, int y)
{
  if (x < MAP_BORDER_ROCK) { return false; }
  if (y < MAP_BORDER_ROCK) { return false; }
  if (x + r->width >= map_width - MAP_BORDER_ROCK) { return false; }
  if (y + r->height >= map_height - MAP_BORDER_ROCK) { return false; }

  for (auto dz = 0; dz < MAP_DEPTH; dz++) {
    for (auto dy = 0; dy < r->height; dy++) {
      for (auto dx = 0; dx < r->width; dx++) {
        if (is_oob(x + dx, y + dy)) { return false; }
        auto c = get(r->data, dx, dy, dz);
        if (c != Charmap::SPACE) {
          if (is_anything_at_no_check(x + dx, y + dy)) { return false; }

          if (is_wall_no_check(x + dx - 1, y + dy) || is_wall_no_check(x + dx + 1, y + dy)
              || is_wall_no_check(x + dx, y + dy - 1) || is_wall_no_check(x + dx, y + dy + 1)) {
            return false;
          }
        }
      }
    }
  }

  return true;
}

bool Dungeon::rooms_move_closer_together(void)
{
#if 0
  LOG("Rooms_move_closer_together");
  dump();
#endif

  auto delta = 1;

  all_placed_rooms.resize(0);

  for (auto r : Room::all_rooms) {
    r->placed = false;
  }

  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (! r) { continue; }

      all_placed_rooms.push_back(r);
      r->placed = true;
    }
  }

  //
  // Make sure we start with a solvable room
  //
  save_level();

  auto corridor_count = draw_corridors();

  if (! corridor_count) {
    TRACE_NO_INDENT();
#if 0
    DBG("level before adding corridors is NOT solvable:");
    dump();
#endif
    return false;
  }

  TRACE_NO_INDENT();
#if 0
  DBG("level before adding shorter corridors is solvable");
#endif
  restore_level();

  auto failed_to_place_all_corridors    = 0;
  auto failed_to_make_shorter_corridors = 0;

  //
  // This is slow and causes jitter in the game when a monst falls into a chasm.
  //
  int attempts_to_move_rooms_closer = 0; /* pcg_random_range(0, 30); */

  choose_room_doors();

  while (attempts_to_move_rooms_closer-- > 0) {
    center_room_layout();

    for (unsigned int rs = 0; rs < (unsigned int) all_placed_rooms.size(); rs++) {

      std::fill(cells.begin(), cells.end(), Charmap::SPACE);

      //
      // which rooms shall we move?
      //
      for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
          auto n = nodes->getn(x, y);
          if (n->depth <= 0) { continue; }

          auto r = get(grid.node_rooms, x, y);
          if (r) { r->skip = (pcg_random_range(0, 100) < 50); }
        }
      }

      //
      // Place all rooms that are not going to move
      //
      for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
          auto n = nodes->getn(x, y);
          if (n->depth <= 0) { continue; }

          auto r = get(grid.node_rooms, x, y);
          if (! r) { continue; }
          if (! r->skip) { place_room(r, r->at.x, r->at.y); }
        }
      }

      //
      // Place the rooms we want to move
      //
      auto moved = false;
      for (auto x = 0; x < nodes->grid_width; x++) {
        for (auto y = 0; y < nodes->grid_height; y++) {
          auto n = nodes->getn(x, y);
          if (n->depth <= 0) { continue; }

          auto r = get(grid.node_rooms, x, y);
          if (! r) { continue; }

          if (! r->skip) { continue; }

          delta = 1 + pcg_random_range(0, 2);

          auto moved_one = false;
          switch (pcg_random_range(0, 4)) {
            case 0 :
              if (can_place_room(r, r->at.x - delta, r->at.y)) {
                r->at.x -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x + delta, r->at.y)) {
                r->at.x += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x, r->at.y - delta)) {
                r->at.y -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x, r->at.y + delta)) {
                r->at.y += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              break;

            case 1 :
              if (can_place_room(r, r->at.x + delta, r->at.y)) {
                r->at.x += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x - delta, r->at.y)) {
                r->at.x -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x, r->at.y + delta)) {
                r->at.y += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x, r->at.y - delta)) {
                r->at.y -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              break;

            case 2 :
              if (can_place_room(r, r->at.x, r->at.y - delta)) {
                r->at.y -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x - delta, r->at.y)) {
                r->at.x -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x + delta, r->at.y)) {
                r->at.x += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x, r->at.y + delta)) {
                r->at.y += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              break;

            case 3 :
              if (can_place_room(r, r->at.x, r->at.y + delta)) {
                r->at.y += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x, r->at.y - delta)) {
                r->at.y -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x - delta, r->at.y)) {
                r->at.x -= delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              if (can_place_room(r, r->at.x + delta, r->at.y)) {
                r->at.x += delta;
                place_room(r, r->at.x, r->at.y);
                moved_one = true;
                break;
              }
              break;
            case 4 : ERR("Wtf");
          }

          if (moved_one) {
            moved = true;
          } else {
            place_room(r, r->at.x, r->at.y);
          }
        }
      }

      if (! moved) {
        restore_level();
        continue;
      }

      //
      // Ok we've moved one room. If we can still place corridors
      // then we can keep going. If not, rollback the room to the
      // last that was solvable.
      //
      std::vector< char > cells_ok;
      std::copy(mbegin(cells), mend(cells), mbegin(cells_ok));

      auto new_total_corridor_len = draw_corridors();
      if (new_total_corridor_len >= corridor_count) {
        restore_level();
        if (! draw_corridors()) { ERR("Rolled back level was not solvable"); }

        if (failed_to_make_shorter_corridors++ > 1000) {
          TRACE_NO_INDENT();
          debug("cannot place shorter corridor layout");
          return true;
        }

        restore_level();
      } else if (! new_total_corridor_len) {
        restore_level();
        if (! draw_corridors()) { ERR("Rolled back level was not solvable"); }

        if (failed_to_place_all_corridors++ > 1000) {
          TRACE_NO_INDENT();
          debug("cannot place shorter corridor layout");
          return true;
        }

        restore_level();
      } else {
        corridor_count = new_total_corridor_len;
        DBG("moved rooms closer, new_total_corridor_len now %d", new_total_corridor_len);
        failed_to_place_all_corridors    = 0;
        failed_to_make_shorter_corridors = 0;
        std::copy(mbegin(cells_ok), mend(cells_ok), mbegin(cells));
        save_level();
      }
    }
  }

  auto ret = draw_corridors();
  TRACE_NO_INDENT();
  debug("success, placed shorter corridor layout");
  return ret;
}

void Dungeon::assign_rooms_to_tiles(void)
{
  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (r) { map_place_room_ptr(r, r->at.x, r->at.y); }
    }
  }
}

void Dungeon::block_secret_doors(void)
{
  for (auto x = 1; x < map_width - 1; x++) {
    for (auto y = 1; y < map_height - 1; y++) {
      if (getc(x, y, MAP_DEPTH_OBJ) == Charmap::DOOR) {
        for (auto dy = -1; dy <= 1; dy++) {
          for (auto dx = -1; dx <= 1; dx++) {
            if (getc(x + dx, y + dy, MAP_DEPTH_FLOOR) == Charmap::SECRET_CORRIDOR) {
              putc(x, y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
              goto next;
            }
          }
        }
      }
    next:;
    }
  }
}

void Dungeon::remove_all_doors(void)
{
  for (auto x = 0; x < map_width; x++) {
    for (auto y = 0; y < map_height; y++) {
      if (getc(x, y, MAP_DEPTH_OBJ) == Charmap::DOOR) {
        putc(x, y, MAP_DEPTH_OBJ, Charmap::SPACE);
        putc(x, y, MAP_DEPTH_FLOOR, Charmap::FLOOR);
      }
    }
  }
}

void Dungeon::place_doors_between_depth_changes(void)
{
  for (auto x = 0; x < nodes->grid_width; x++) {
    for (auto y = 0; y < nodes->grid_height; y++) {
      auto n = nodes->getn(x, y);
      if (n->depth <= 0) { continue; }

      auto r = get(grid.node_rooms, x, y);
      if (! r) { continue; }

      if (r->down_room) {
        auto o = r->down_room;
        if (! o) { ERR("Room linkage bug"); }

        if (o->depth && (r->depth > o->depth)) {
          putc(r->down_door_at.x, r->down_door_at.y, MAP_DEPTH_OBJ, Charmap::DOOR);
        }
      }

      if (r->up_room) {
        auto o = r->up_room;
        if (! o) { ERR("Room linkage bug"); }

        if (o->depth && (r->depth > o->depth)) {
          putc(r->up_door_at.x, r->up_door_at.y, MAP_DEPTH_OBJ, Charmap::DOOR);
        }
      }

      if (r->right_room) {
        auto o = r->right_room;
        if (! o) { ERR("Room linkage bug"); }

        if (o->depth && (r->depth > o->depth)) {
          putc(r->right_door_at.x, r->right_door_at.y, MAP_DEPTH_OBJ, Charmap::DOOR);
        }
      }

      if (r->left_room) {
        auto o = r->left_room;
        if (! o) { ERR("Room linkage bug"); }

        if (o->depth && (r->depth > o->depth)) {
          putc(r->left_door_at.x, r->left_door_at.y, MAP_DEPTH_OBJ, Charmap::DOOR);
        }
      }

      if (r->secret_down_room) {
        auto o = r->secret_down_room;
        if (! o) { ERR("Room linkage bug"); }

        putc(r->down_secret_door_at.x, r->down_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
        putc(o->up_secret_door_at.x, o->up_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
      }

      if (r->secret_up_room) {
        auto o = r->secret_up_room;
        if (! o) { ERR("Room linkage bug"); }

        putc(r->up_secret_door_at.x, r->up_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
        putc(o->down_secret_door_at.x, o->down_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
      }

      if (r->secret_right_room) {
        auto o = r->secret_right_room;
        if (! o) { ERR("Room linkage bug"); }

        putc(r->right_secret_door_at.x, r->right_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
        putc(o->left_secret_door_at.x, o->left_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
      }

      if (r->secret_left_room) {
        auto o = r->secret_left_room;
        if (! o) { ERR("Room linkage bug"); }

        putc(r->left_secret_door_at.x, r->left_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
        putc(o->right_secret_door_at.x, o->right_secret_door_at.y, MAP_DEPTH_OBJ, Charmap::SECRET_DOOR);
      }
    }
  }
}

void Dungeon::dmap_set_is_walls(Dmap *d)
{
  int x, y;

  for (x = 0; x < MAP_WIDTH; x++) {
    for (y = 0; y < MAP_HEIGHT; y++) {

      if (is_anything_at(x, y)) {
        set(d->val, x, y, DMAP_IS_WALL);
      } else {
        set(d->val, x, y, DMAP_IS_PASSABLE);
      }
    }
  }
}

/*
Cellular Automata Method for Generating Random Cave-Like LevelsStatic


  From RogueBasin

Jump to: Navigation < #column-one>, search < #searchInput>

By Jim Babcock < /index.php?title=Jim_Babcock&action=edit>

It is an old and fairly well documented trick to use cellular automata
< /index.php?title=Cellular_automata > to generate cave-like structures.
The basic idea is to fill the map randomly, then repeatedly apply the
4-5 rule: A tile is a wall if it is a wall and has 4 neighbors that are
walls, or if it is not a wall and has 5 neighbors that are. This rule
can be stated more simply: A tile becomes or remains a wall if the 3x3
region centered on it contains at least 5 walls. (/Note: It is important
to do this for each tile simultaneously. If you update one, then use its
value when you update the next, your results won't look as good, and the
tricks described later won't work./)

If the map initially contains 45% walls, and the process above is
repeated 5 times, the output looks like (for example)

############################################################
###....####################################.....############
##......######################..#########.........##########
##......#####################....#######...........####.####
##......###################.........................##...###
##......##################..........................###...##
#........##############.............................###...##
#........#############...............................#....##
##.......##############..................................###
##.......###..############..............................####
##.......##....############.............................####
#..............############...###........................###
#...............###########..#####...............##.......##
#................#################...............##.......##
##.....#####..........###########....#..........###.......##
##....#######...........########....###.........####......##
##....#######............######....####........#####......##
##....#######.............####....#####.......#####......###
#......######..............###....####........####......####
#.......######.............###...####.........###.......####
#........#####.............###..####.....................###
##........####..............#...####.....................###
#####......##...................####.....................###
######...........................##.....................####
######..................................................####
######.........###.....................####.............####
######......#########.................######............####
#######....#############.......##############.....###..#####
##############################################..############
############################################################

The problem is, the results of the algorithm are very inconsistent. Not
only is it prone to generating disjoint (not connected) maps, like in
this example, with the same parameters:

############################################################
#####################################################..#####
#####.....##################...###############............##
#####......###########.####....########.#####..............#
#####.......#########..###.....###############.............#
####.............#####.###....###################.........##
###...............########...####################........###
##.................#######...####################........###
##.......##.........#####.....##################.........###
##......####.........###.......################...........##
##.....########.................#######..######...........##
##...###########................######...#######..........##
#########..######..............######....########........###
########....######..#####......#####.....##########......###
#######......#############.....#####.....###########.....###
#######.......############......###.......###########.....##
#######.......###########.......###.......###########.....##
######.......####..######.......####.......#########......##
#####.......####....#####.......####..........######.....###
####........####......####......####...........#####.....###
####.........###.......###......####...##......######.....##
####...##.....###.......#......###########.....#######.....#
#####.####.....#####...........############....########....#
##########.....######..........############....#########..##
#########.......#####...........##########.....#############
#########.......####...............#####........############
##########......####................###...........##########
###########....#####.....######.....####...........#########
################################...##########.....##########
############################################################

it also sometimes generates maps which consist of basically one huge
open space, like this one:

############################################################
############################################################
#################.####.######..######........###############
########...#####...##...####....####..........######...#####
###.####...####....###..####....####..........#####.....####
##...###....##.....###...##.....###............###......####
###.####...........###..........###.....###.........########
########...........###...........#.......#.........#########
#######.............#..............................#########
######.....##..........................................#####
###.......###...........................................####
##.......####...........................................####
##......................................................####
##.....................................................#####
##.....................................................#####
#.....................................##...............#####
#.....................................##................####
#...........................###......###................####
##...........###............###.....#####...............####
###...........#..............##.....######............######
######.......................##......######........#########
##########..................##.........#####......##########
###########................###..........####......##########
############................#...........####......##########
###.....#####.........##...............#####.......####..###
###.....#####.......#####.............#####..............###
###.....####.......#####..............#####.....##.......###
####...#####.......#####.....#####...######....####.....####
#############.##########....################..##############
############################################################

We can fix the disjoint segments problem in one of three ways. Either
throw away maps that have disjoint segments in them, connect up the
segments after the fact, or fill in all but the biggest segment. We
can't just retry when we get a disjoint map, because if the map is big
then, statistically, that will be almost 100% of the time. Filling in
all but the biggest segment will tend to produce a small area in a map
that was supposed to be big. Connecting up the regions works, but it
tends to look unnatural, as in the example from above, now connected:

############################################################
#####################################################..#####
#####.....##################...###############............##
#####......###########.####....########....................#
#####.......#########..###.....###############.............#
####.............####..###....###################.........##
###...............###.####...####################........###
##.................##.####...####################........###
##.......##.........#.###.....##################.........###
##......####..........##.......################...........##
##.....########.................#######..######...........##
##...###########................######...#######..........##
#########..######..............######....########........###
########............#####......#####.....##########......###
#######......#############...............###########.....###
#######.......############......###.......###########.....##
#######.......###########.......###.......###########.....##
######.......####..######.......####.......#########......##
#####.......####....#####.......####.....................###
####........####......####......####...........#####.....###
####.........###.......###......####...##......######.....##
####...##.....###.......#......###########.....#######.....#
#####.####.....#####...........############....########....#
##########.....######..........############....#########..##
#########.......#####...........##########.....#############
#########.......####...............#####........############
##########......####................###...........##########
###########....#####.....######.....####...........#########
################################...##########.....##########
############################################################

The solution to both problems, as it turns out, is to revisit the
original cellular automata rules. Recall that the original rule was

   // There is a wall initially at P with 45% probability
   // In the next generation, there is a wall at spot P if the number of
  tiles around P which are walls is at least 5

Or, in more compact notation:

   // Winit (p) = rand[0,100) <  45
   // R (p) = the number of tiles within 1 step of p which are walls
   // W? (p) = R (p) ? 5

Now, one of the problems was that we tend to get big, open areas. So why
not try filling those areas in? Change the rule to

   // W? (p) = R (p) ? 5 or p is in the middle of an open space

Or more formally,

   // Rn (p) = the number of tiles within n steps of p which are walls
   // W? (p) = R1 (p)?5 || R2 (p)=0

So how does it look?

Winit (p) = rand[0,100) <  45
Repeat 5: W? (p) = R1 (p) ? 5 || R2 (p) ? 1

############################################################
##....######################################################
#.......###..#####..####....###########################..###
#...#.........###.............##########..############....##
##...###...#..###..............########....######..###....##
###...######...#..##...........######.....######....###..###
####..######......##..##........####...#..######....########
####..###.#.......#...##...#.....##...###..######...########
#####.........##...........##........####.....##.....#######
#####.........##...........#.......##.....#.............####
####...###...##................#...##......###...........###
####...###..##...###....##.....##..##..##..###....##.....###
#########..###..####...###.............###..##..####.....###
########...##..#####...##...............#...#...####....####
#######........######......###...##....................#####
#######..##.....######....##########...................#####
######..####.......####...#########...................######
####....####..##....##.....#######...##..............#######
###.....###..#####......#...####....##................######
##..##..###..###........##.........#....#......##......#####
#..####..##...##.................###...##.....####......####
#.....#..###..#..##..........#..###..###.....#####......####
##.......####.....#...##........##..###....#######......####
######....###.......................###...#######....#######
#######......................##.....###...#######...########
########.................#######....####...#####....########
########..............###########..######...........########
#########....####....######################........#########
###################.########################################
############################################################

This is more interesting - it doesn't have any big open areas, it has a
decent layout. It's almost fully connected. Still, it has some new
problems: There are isolated single-tile walls in places, and in general
it's not very smooth. But with a little tweaking:

Winit (p) = rand[0,100) <  40
Repeat 4: W? (p) = R1 (p) ? 5 || R2 (p) ? 2
Repeat 3: W? (p) = R1 (p) ? 5

############################################################
###...###########..#############################.....#######
##..........####....################..#########.........####
##...........##.....####..#########.......####..######...###
##.......#..........###....###.................########..###
##......###........###........................#########..###
##.......##.........#........................##########...##
##.......###...........##.............###....#########.....#
##.......######.......####...........#####....#####........#
###.....#########....#####...........######...#####........#
###########################...........#####...#######.....##
#############...###########.............##....########....##
############.........#######...................#######....##
###########...........########......###............##....###
###..#####.............#########...##########............###
##....###...............######################..........####
###..........................######..#########..........####
####..........................###.....#######...........####
####.................##................##................###
####...###..........####...............#..................##
###...#####.........####..............##......##...........#
##....########......#####............####....####..........#
##....#########.....#####............####....####..........#
##.....######.......#####.............##.....####...##.....#
##......##..........#####....................####..####....#
###.................####.........###........############..##
###............##..######.###...############################
####..........##############################################
######..####################################################
############################################################

Notice that the initial fill percentage is a little lower, the cutoffs
are different, and we switch rules after a few generations. This is more
like the desired result. So, with these parameters, I give you some more
samples, at various sizes.

##############################
##..###....###.....###########
#...........................##
#.................##.........#
##..###..........#######.....#
########.........#######.....#
############......####......##
#############...............##
###..########...............##
##....#######...###..#......##
##.....######...#######.....##
##......#####...######......##
##...#...###....#####.......##
##..##.........######.......##
##..........##########......##
###........#####..####.....###
###........####....###.....###
###....##...##.....###.....###
###...####........####......##
###...#####......#####......##
##....#####.....#####.......##
##.....###.....####.........##
##..............##..........##
###.........................##
####........................##
####.......................###
####..........##...........###
#####...###..####.........####
####################.....#####
##############################

############################################################
#########......###...##........####...####.....#############
####............................##.....##............#######
###................###.....##..........................#####
###...............#####...####..........................####
###...............#####....####............#............####
####...###.........####.......##.......................#####
##########..........###........##.....................######
##########...........#..........##...................#######
#########.......................#####..............#########
######.........................#######...#......############
#####..........................############....#############
####...........................###########......######..####
###..........##.................#########................###
##.......#######........#..........######...###.........####
##......########.......##............###...######.....######
###.....#######...............#####........########..#######
###......#####...##...........######........################
###......#####..####...........#####.........###############
#######..#####..####............###...........#######....###
########..###...#####......###.................#####......##
########.......######......####.................###.......##
########.......######.......##....##..................##..##
#######.......######....##.......####................####..#
######.......#######....###......####..........###..#####..#
#####........######.....######....##..........##########...#
######........###........######...............########.....#
##########...............#######.............########.....##
#############...#######..###########...#####################
############################################################

################################################################
#######..#####............####..####...###....###########...####
###......####..................................#########.....###
##.......###.......................................####......###
##......####.............##.........................##......####
##......#####......##...####................##..............####
##......##############..#####...............###.............####
##.....###############...#####...............##........##...####
##.....################..######.........#.............####...###
##.....################...#####........###............####....##
###.....#####..##...##....####.........###.............###....##
####....####..............###..........###...................###
####....####.............####..........##....................###
###.....####...........#####.........................##.....####
##.......##............#####....................##..####...#####
##.....................######................###########...#####
###..##........##......###############.....############....#####
########......####....#################..###############..######
#########...####################################################
################################################################

############################################################
#########......###...##........####...####.....#############
####............................##.....##............#######
###................###.....##..........................#####
###...............#####...####..........................####
###...............#####....####............#............####
####...###.........####.......##.......................#####
##########..........###........##.....................######
##########...........#..........##...................#######
#########.......................#####..............#########
######.........................#######...#......############
#####..........................############....#############
####...........................###########......######..####
###..........##.................#########................###
##.......#######........#..........######...###.........####
##......########.......##............###...######.....######
###.....#######...............#####........########..#######
###......#####...##...........######........################
###......#####..####...........#####.........###############
#######..#####..####............###...........#######....###
########..###...#####......###.................#####......##
########.......######......####.................###.......##
########.......######.......##....##..................##..##
#######.......######....##.......####.........##.....####..#
#####........#######....###......####........#####..#####..#
####........#######.....######...#####.......############..#
####.......######..........####..#########..#############..#
###........#####............###..########################.##
##.........####.............###..################.######..##
#....###...####......####....#...######..#######...#####..##
#.....#.....##......######.......#####....#####....#####..##
#...................######........####....###.....#####...##
#....................#####........#####..###......##......##
#....................######........########................#
##......#............########.......#######................#
##......##...........#########......#######...............##
###.....#............####...##.....#######..##...........###
###..........#......####...........######..####..........###
##..........####....####...........#####..######.........###
##...........####..#####............##....######.........###
##............###..######......#...........####..........###
##............###..#######.....##........................###
##.......###...#....#######....#..........................##
###......###.........######.........................##.....#
###.......#..........######........#####...........####....#
###............###...######......########.........#####....#
###...........#####..######.....#########.........####.....#
###...........#####.#######.....########...........###.....#
###...........####..########...#########......##...###....##
###...........####...##################......####..###....##
###...........####......##############.......####..###....##
###...........####..........##########........##...###....##
###............####..........#########.............####..###
###...........#####...........#######..............#########
###.....##########............######.......##......#########
##.....###########.....###.....####.......####......########
##.....############....###......##.......#####........######
###...##############..#####.............#######.......######
################################...##..#####################
############################################################

There's still no guarantee of connectedness, though. However, it's now
consistently almost-connected, so that you can reasonably just drop the
isolated chunks.

Finally, here is the C program I used to try out different parameters.
Before putting this into an actual game, handling of disconnected
regions is needed.

*/

//
// Grow our cells
//
void Dungeon::cave_generation(void)
{
  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;
  int16_t       x, y;

  for (x = 2; x < maze_w; x++) {
    for (y = 2; y < maze_h; y++) {

      uint8_t adjcount = 0;

#define ADJ(i, j) adjcount += get(map_curr, x + i, y + j);

      ADJ(-1, -1);
      ADJ(-1, 0);
      ADJ(-1, 1);

      ADJ(0, -1);
      ADJ(0, 0);
      ADJ(0, 1);

      ADJ(1, -1);
      ADJ(1, 0);
      ADJ(1, 1);

      if (adjcount >= MAP_R1) { continue; }

      ADJ(-2, -1);
      ADJ(-2, 0);
      ADJ(-2, 1);

      ADJ(-1, -2);
      ADJ(-1, 2);

      ADJ(0, -2);
      ADJ(0, 2);

      ADJ(1, -2);
      ADJ(1, 2);

      ADJ(2, -1);
      ADJ(2, 0);
      ADJ(2, 1);

      //
      // Adjust for the grow threshold for rock or flow.
      //
      if (adjcount <= MAP_R2) {
        //
        // map_save set to 0 already.
        //
      } else {
        set(map_save, x, y, (uint8_t) 1);
      }
    }
  }
}

//
// Any water next to cave walls make it shallow
//
void Dungeon::water_fixup_shallows(void)
{
  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      if (! is_deep_water_no_check(x, y)) { continue; }

      if (is_wall(x - 1, y - 1) || is_wall(x, y - 1) || is_wall(x + 1, y - 1) || is_wall(x - 1, y) || is_wall(x, y)
          || is_wall(x + 1, y) || is_wall(x - 1, y + 1) || is_wall(x, y + 1) || is_wall(x + 1, y + 1)
          || is_rock(x - 1, y - 1) || is_rock(x, y - 1) || is_rock(x + 1, y - 1) || is_rock(x - 1, y) || is_rock(x, y)
          || is_rock(x + 1, y) || is_rock(x - 1, y + 1) || is_rock(x, y + 1) || is_rock(x + 1, y + 1)) {
        putc(x, y, MAP_DEPTH_LIQUID, Charmap::SHALLOW_WATER);
      }
    }
  }
}

//
// Add deepwater and islands of safety.
//
void Dungeon::water_fixup(void)
{
  std::array< std::array< bool, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > cand {};

  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      if (is_shallow_water(x - 1, y - 1) && is_shallow_water(x, y - 1) && is_shallow_water(x + 1, y - 1)
          && is_shallow_water(x - 1, y) && is_shallow_water(x, y) && is_shallow_water(x + 1, y)
          && is_shallow_water(x - 1, y + 1) && is_shallow_water(x, y + 1) && is_shallow_water(x + 1, y + 1)) {
        set(cand, x, y, true);
      }
    }
  }
  for (auto y = 1; y < MAP_HEIGHT - 1; y++) {
    for (auto x = 1; x < MAP_WIDTH - 1; x++) {
      if (get(cand, x, y)) {
        if (pcg_random_range(0, 100) < 95) {
          putc(x, y, MAP_DEPTH_LIQUID, Charmap::DEEP_WATER);
        } else {
          putc(x, y, MAP_DEPTH_LIQUID, Charmap::SPACE);
          putc(x, y, MAP_DEPTH_FLOOR, Charmap::DIRT);
        }
      }
    }
  }
}

void Dungeon::add_remaining(void)
{
  for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
    for (auto x = 2; x < MAP_WIDTH - 2; x++) {
      if (is_anything_at(x, y)) { continue; }

      if (biome == BIOME_CHASMS) {
        if (pcg_random_range(0, 1000) < 20) {
          putc(x, y, MAP_DEPTH_FLOOR, Charmap::FLOOR);
          continue;
        }
        if (pcg_random_range(0, 10000) < 100) {
          putc(x, y, MAP_DEPTH_OBJ, Charmap::TREASURE_CLASS_B);
          putc(x, y, MAP_DEPTH_FLOOR, Charmap::FLOOR);
          continue;
        }
        if (pcg_random_range(0, 10000) < 50) {
          putc(x, y, MAP_DEPTH_OBJ, Charmap::TREASURE_CLASS_B);
          putc(x, y, MAP_DEPTH_FLOOR, Charmap::FLOOR);
          continue;
        }
        if (pcg_random_range(0, 10000) < 10) {
          putc(x, y, MAP_DEPTH_OBJ, Charmap::TREASURE_CLASS_C);
          putc(x, y, MAP_DEPTH_FLOOR, Charmap::FLOOR);
          continue;
        }
        putc(x, y, MAP_DEPTH_OBJ, Charmap::CHASM);
        continue;
      }

      if (pcg_random_range(0, 100) < 95) { putc(x, y, MAP_DEPTH_OBJ, Charmap::ROCK); }

      putc(x, y, MAP_DEPTH_LIQUID, Charmap::SPACE);
      putc(x, y, MAP_DEPTH_FLOOR, Charmap::DIRT);

      if (pcg_random_range(0, 100) < 20) {
        putc(x, y, MAP_DEPTH_FLOOR2, Charmap::GRASS_DRY);
      } else if (pcg_random_range(0, 100) < 20) {
        putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FOLIAGE);
      } else if (is_dirt(x, y)) {
        if (pcg_random_range(0, 100) < 20) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FOLIAGE); }
      } else if (is_corridor(x, y)) {
        if (pcg_random_range(0, 100) < 20) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::SPIDERWEB); }
      }
    }
  }
}

void Dungeon::add_foliage_around_water(void)
{
  bool foliage_ok_next_to_walls = pcg_random_range(0, 100) > 50;

  for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
    for (auto x = 2; x < MAP_WIDTH - 2; x++) {

      if (is_chasm(x, y) || is_wall(x, y) || is_rock(x, y) || is_bridge(x, y) || is_chasm(x, y)
          || is_block_of_ice(x, y) || is_lava(x, y) || is_brazier(x, y) || is_deep_water(x, y)
          || is_shallow_water(x, y)) {
        continue;
      }

      if (is_dirt(x, y)) {
        if (pcg_random_range(0, 100) > 95) { continue; }
      }

      if (is_floor(x, y)) {
        if (pcg_random_range(0, 100) > 10) { continue; }
      }

      int foliage_ok = 0;
      for (auto dx = -2; dx <= 2; dx++) {
        if (foliage_ok < 0) { break; }
        for (auto dy = -2; dy <= 2; dy++) {
          if (is_block_of_ice(x + dx, y + dy) || is_bridge(x + dx, y + dy) || is_lava(x + dx, y + dy)
              || is_brazier(x + dx, y + dy) || is_chasm(x + dx, y + dy)) {
            foliage_ok = -1;
            goto next;
          }

          if (! foliage_ok_next_to_walls) {
            if (is_wall(x + dx, y + dy)) {
              foliage_ok = -1;
              goto next;
            }
          }
          if (is_shallow_water(x + dx, y + dy) || is_foliage(x + dx, y + dy) || is_deep_water(x + dx, y + dy)) {
            foliage_ok = 1;
          }
        }
      }
    next:
      if (foliage_ok == 1) {
        if (pcg_random_range(0, 100) > 80) {
          putc(x, y, MAP_DEPTH_FLOOR2, Charmap::GRASS_WET);
        } else if (pcg_random_range(0, 100) > 20) {
          putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FOLIAGE);
        }
      }
    }
  }
}

void Dungeon::add_spiderweb(void)
{
  if (pcg_random_range(0, 10) > 1) { return; }

  for (auto y = 2; y < MAP_HEIGHT - 2; y++) {
    for (auto x = 2; x < MAP_WIDTH - 2; x++) {

      if (is_block_of_ice(x, y) || is_lava(x, y) || is_wall(x, y) || is_rock(x, y) || is_deep_water(x, y)
          || is_brazier(x, y) || is_shallow_water(x, y)) {
        continue;
      }

      if (is_corridor(x, y)) {
        if (pcg_random_range(0, 1000) > 400) { continue; }
      } else if (is_floor(x, y)) {
        if (pcg_random_range(0, 1000) > 1) { continue; }
      } else {
        continue;
      }

      int spiderweb_ok = 0;
      for (auto dx = -2; dx <= 2; dx++) {
        if (spiderweb_ok == -1) { break; }
        for (auto dy = -1; dy <= 1; dy++) {
          if (is_block_of_ice(x + dx, y + dy) || is_lava(x + dx, y + dy) || is_shallow_water(x + dx, y + dy)
              || is_deep_water(x + dx, y + dy) || is_brazier(x + dx, y + dy)) {
            spiderweb_ok = -1;
            goto next;
          }

          if (is_chasm(x + dx, y + dy) || is_bridge(x + dx, y + dy) || is_spiderweb(x + dx, y + dy)
              || is_rock(x + dx, y + dy) || is_wall(x + dx, y + dy)) {
            spiderweb_ok = 1;
            goto next;
          }
        }
      }
    next:
      if (spiderweb_ok == 1) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::SPIDERWEB); }
    }
  }
}

//
// Generate a cave!
//
void Dungeon::cave_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (is_anything_at(x, y)) { continue; }

        bool chasm_ok = true;
        for (auto dx = -1; dx <= 1; dx++) {
          if (! chasm_ok) { break; }
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) {
              chasm_ok = false;
              break;
            }
            if (is_shallow_water(x + dx, y + dy)) {
              chasm_ok = false;
              break;
            }
            if (is_deep_water(x + dx, y + dy)) {
              chasm_ok = false;
              break;
            }
          }
        }

        if (chasm_ok) {
          putc(x, y, MAP_DEPTH_OBJ, Charmap::CHASM);
        } else {
          putc(x, y, MAP_DEPTH_OBJ, Charmap::ROCK);
        }
      }
    }
  }
}

void Dungeon::dirt_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (! is_anything_at(x, y)) { putc(x, y, MAP_DEPTH_FLOOR, Charmap::DIRT); }
      }
    }
  }
}

void Dungeon::grass_dry_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  if (0) {
    printf("initial grass\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  if (0) {
    printf("final grass\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }

        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) { goto next; }
            if (is_brazier(x + dx, y + dy)) { goto next; }
            if (is_shallow_water(x + dx, y + dy)) { goto next; }
            if (is_deep_water(x + dx, y + dy)) { goto next; }
          }
        }

        putc(x, y, MAP_DEPTH_FLOOR2, Charmap::GRASS_DRY);
      }
    next:
      continue;
    }
  }
}

void Dungeon::grass_wet_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  if (0) {
    printf("initial grass\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  if (0) {
    printf("final grass\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (y = 2; y < maze_h - 2; y++) {
    for (x = 2; x < maze_w - 2; x++) {
      if (get(map_curr, x, y)) {
        if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }
        if (is_deep_water(x, y)) { continue; }

        bool ok_to_place = false;
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) { goto next; }
            if (is_dirt(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_shallow_water(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_deep_water(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
          }
        }

        if (ok_to_place) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::GRASS_WET); }
      }
    next:
      continue;
    }
  }
}

void Dungeon::fungus_edible_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  if (0) {
    printf("initial fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  if (0) {
    printf("final fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (y = 2; y < maze_h - 2; y++) {
    for (x = 2; x < maze_w - 2; x++) {
      if (get(map_curr, x, y)) {
        if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }
        if (is_deep_water(x, y)) { continue; }
        if (is_floor(x, y)) {
          if (d100() < 90) { continue; }
        }
        if (is_corridor(x, y)) {
          if (d100() < 80) { continue; }
        }

        bool ok_to_place = false;
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) { goto next; }
            if (is_deep_water(x + dx, y + dy)) { goto next; }
            if (is_floor(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_dirt(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_shallow_water(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
          }
        }

        if (ok_to_place) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FUNGUS_EDIBLE); }
      }
    next:
      continue;
    }
  }
}

void Dungeon::fungus_poison_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  if (0) {
    printf("initial fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  if (0) {
    printf("final fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (y = 2; y < maze_h - 2; y++) {
    for (x = 2; x < maze_w - 2; x++) {
      if (get(map_curr, x, y)) {
        if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }
        if (is_deep_water(x, y)) { continue; }
        if (is_floor(x, y)) {
          if (d100() < 90) { continue; }
        }
        if (is_corridor(x, y)) {
          if (d100() < 80) { continue; }
        }

        bool ok_to_place = false;
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) { goto next; }
            if (is_deep_water(x + dx, y + dy)) { goto next; }
            if (is_floor(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_dirt(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_shallow_water(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
          }
        }

        if (ok_to_place) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FUNGUS_POISON); }
      }
    next:
      continue;
    }
  }
}

void Dungeon::fungus_withered_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  if (0) {
    printf("initial fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  if (0) {
    printf("final fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (y = 2; y < maze_h - 2; y++) {
    for (x = 2; x < maze_w - 2; x++) {
      if (get(map_curr, x, y)) {
        if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }
        if (is_shallow_water(x, y)) { continue; }
        if (is_deep_water(x, y)) { continue; }

        bool ok_to_place = false;
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) { goto next; }
            if (is_shallow_water(x + dx, y + dy)) { goto next; }
            if (is_deep_water(x + dx, y + dy)) { goto next; }
            if (is_floor(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_dirt(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
          }
        }

        if (ok_to_place) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FUNGUS_WITHERED); }
      }
    next:
      continue;
    }
  }
}

void Dungeon::fungus_healing_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  if (0) {
    printf("initial fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  if (0) {
    printf("final fungus\n");
    for (y = 2; y < maze_h - 2; y++) {
      for (x = 2; x < maze_w - 2; x++) {
        if (get(map_curr, x, y)) {
          printf(".");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  for (y = 2; y < maze_h - 2; y++) {
    for (x = 2; x < maze_w - 2; x++) {
      if (get(map_curr, x, y)) {
        if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }
        if (is_shallow_water(x, y)) { continue; }

        bool ok_to_place = false;
        for (auto dx = -1; dx <= 1; dx++) {
          for (auto dy = -1; dy <= 1; dy++) {
            if (is_lava(x + dx, y + dy)) { goto next; }
            if (is_shallow_water(x + dx, y + dy)) { goto next; }
            if (is_floor(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
            if (is_dirt(x + dx, y + dy)) {
              ok_to_place = true;
              break;
            }
          }
        }

        if (ok_to_place) { putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FUNGUS_HEALING); }
      }
    next:
      continue;
    }
  }
}

void Dungeon::foliage_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)

{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (biome == BIOME_DUNGEON) {
          if (is_wall(x, y) || is_rock(x, y) || is_chasm(x, y)) { continue; }

          for (auto dx = -1; dx <= 1; dx++) {
            for (auto dy = -1; dy <= 1; dy++) {
              if (is_lava(x + dx, y + dy)) { goto next; }
              if (is_brazier(x + dx, y + dy)) { goto next; }
              if (is_deep_water(x + dx, y + dy)) { goto next; }
            }
          }
        }

        putc(x, y, MAP_DEPTH_FLOOR2, Charmap::FOLIAGE);
      }
    next:
      continue;
    }
  }
}

void Dungeon::water_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (! is_anything_at(x, y)) { putc(x, y, MAP_DEPTH_LIQUID, Charmap::SHALLOW_WATER); }
      }
    }
  }
}

void Dungeon::lava_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (! is_anything_at(x, y)) { putc(x, y, MAP_DEPTH_LIQUID, Charmap::LAVA); }
      }
    }
  }
}

void Dungeon::ice_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations)
{
  map_save = {};
  map_curr = {};

  const int16_t maze_w = MAP_WIDTH - 2;
  const int16_t maze_h = MAP_HEIGHT - 2;

  if (map_r1) { MAP_R1 = map_r1; }

  if (map_r2) { MAP_R2 = map_r2; }

  if (map_generations) { MAP_GENERATIONS = map_generations; }

  int16_t x, y, i;

  map_curr = {};

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (pcg_random_range(0, 10000) < map_fill_prob) { set(map_curr, x, y, (uint8_t) 1); }
    }
  }

  for (i = 0; i < MAP_GENERATIONS; i++) {
    cave_generation();
    std::copy(mbegin(map_save), mend(map_save), mbegin(map_curr));
    map_save = {};
  }

  for (x = 2; x < maze_w - 2; x++) {
    for (y = 2; y < maze_h - 2; y++) {
      if (get(map_curr, x, y)) {
        if (! is_anything_at(x, y)) { putc(x, y, MAP_DEPTH_LIQUID, Charmap::ICE); }
      }
    }
  }
}

void dungeon_test(void)
{
  static int dungeon_seed = 10000;

  CON("Test dungeon seed: %d", dungeon_seed);

  //
  // smaller node numbers mean larger rooms
  //
  auto    biome = get_biome(0);
  point3d world_at;
  point   grid_at;

  g_opt_ascii = true;
  sdl_display_reset();

  //
  // Create the new level
  //
  game->init();

  auto new_level                   = new Level(biome);
  auto difficulty_depth            = 0;
  auto dungeon_walk_order_level_no = 0;

  new_level->create(world_at, grid_at, dungeon_seed, difficulty_depth, dungeon_walk_order_level_no);
  game->level = new_level;

  pcg_random_allowed++;
  game->place_player();
  game->robot_mode_requested = true;
  game->start();
  game->tick_begin_now();
  game->tick_end();
  game->tick_begin_now();
  pcg_random_allowed--;

  while (game->tick_current < 100) {
    SDL_Delay(5);
    game->level->tick();
    wid_gc_all();
    wid_display_all();
    ascii_dump();
  }
  delete new_level;

  game->fini();

  if (! dungeon_seed--) { DIE("end of test"); }
}
