//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_ptrcheck.hpp"
#include "my_range.hpp"
#include "my_room.hpp"
#include "my_template.hpp"
#include "my_vector_bounds_check.hpp"

std::vector< Roomp > Room::all_rooms;

Room::Room(biome_t biome)
{
  this->biome  = biome;
  this->roomno = all_rooms.size();
  newptr(MTYPE_ROOM, this, "room");
}

Room::~Room(void) { oldptr(MTYPE_ROOM, this); }

void room_init(void) { TRACE_AND_INDENT(); }

void room_fini(void)
{
  TRACE_AND_INDENT();
  for (auto &r : Room::all_rooms) {
    delete r;
  }
}

Roomp Room::room_new(biome_t biome)
{
  TRACE_AND_INDENT();
  auto r = new Room(biome);
  Room::all_rooms.push_back(r);
  return r;
}

Roomp Room::create_w_flip(void)
{
  TRACE_AND_INDENT();
  std::vector< std::string > rot[ MAP_DEPTH ];

  auto r = Room::room_new(biome);

  /*
   * Flip the room chars
   */
  for (auto z = 0; z < MAP_DEPTH; z++) {
    for (auto y = 0; y < height; y++) {
      std::string s;
      for (auto x = 0; x < width; x++) {
        set(r->data, x, y, z, get(data, width - x - 1, y, z));
      }
    }
  }

  /*
   * Flip the doors too
   */
  auto z = MAP_DEPTH_OBJ;
  {
    for (auto y = 0; y < height; y++) {
      std::string s;
      for (auto x = 0; x < width; x++) {
        auto c = get(r->data, x, y, z);
        switch (c) {
          case Charmap::CHAR_DOOR_UP : c = Charmap::CHAR_DOOR_UP; break;
          case Charmap::CHAR_DOOR_DOWN : c = Charmap::CHAR_DOOR_DOWN; break;
          case Charmap::CHAR_DOOR_LEFT : c = Charmap::CHAR_DOOR_RIGHT; break;
          case Charmap::CHAR_DOOR_RIGHT : c = Charmap::CHAR_DOOR_LEFT; break;
        }
        set(r->data, x, y, z, c);
      }
    }
  }

  r->dir_up    = dir_up;
  r->dir_down  = dir_down;
  r->dir_left  = dir_right;
  r->dir_right = dir_left;

  r->is_ascend_dungeon  = is_ascend_dungeon;
  r->is_lock            = is_lock;
  r->is_key             = is_key;
  r->is_secret          = is_secret;
  r->is_descend_dungeon = is_descend_dungeon;

  r->depth = depth;

  r->finalize();

  return r;
}

Roomp Room::rotate_clockwise(void)
{
  TRACE_AND_INDENT();
  std::vector< std::string > rot[ MAP_DEPTH ];

  auto r = Room::room_new(biome);

  /*
   * Rotate the room chars
   */
  for (auto z = 0; z < MAP_DEPTH; z++) {
    for (auto y = 0; y < height; y++) {
      std::string s;
      for (auto x = 0; x < width; x++) {
        set(r->data, width - y - 1, x, z, get(data, x, y, z));
      }
    }
  }

  /*
   * Rotate the doors too
   */
  auto z = MAP_DEPTH_OBJ;
  {
    for (auto y = 0; y < height; y++) {
      std::string s;
      for (auto x = 0; x < width; x++) {
        auto c = get(r->data, x, y, z);
        switch (c) {
          case Charmap::CHAR_DOOR_UP : c = Charmap::CHAR_DOOR_RIGHT; break;
          case Charmap::CHAR_DOOR_DOWN : c = Charmap::CHAR_DOOR_LEFT; break;
          case Charmap::CHAR_DOOR_LEFT : c = Charmap::CHAR_DOOR_UP; break;
          case Charmap::CHAR_DOOR_RIGHT : c = Charmap::CHAR_DOOR_DOWN; break;
        }

        set(r->data, x, y, z, c);
      }
    }
  }

  r->dir_up    = dir_left;
  r->dir_down  = dir_right;
  r->dir_left  = dir_down;
  r->dir_right = dir_up;

  r->is_ascend_dungeon  = is_ascend_dungeon;
  r->is_lock            = is_lock;
  r->is_key             = is_key;
  r->is_secret          = is_secret;
  r->is_descend_dungeon = is_descend_dungeon;

  r->depth = depth;

  r->finalize();

  return r;
}

//
// Find all doors from a room
//
void Room::find_doors(void)
{
  int z = MAP_DEPTH_OBJ;

  for (auto x : range< int >(0, width)) {
    for (auto y : range< int >(0, height)) {
      if (get(data, x, y, z) == Charmap::CHAR_DOOR_UP) {
        has_door    = true;
        has_door_up = true;
        doors_up.push_back(point(x, y));
        if (y == height - 1) {
          dump();
          DIE("up door is in bottom row?");
        }
        if (get(data, x, y + 1, z) == ' ') {
          dump();
          DIE("up door has space next to it?");
        }
      }
      if (get(data, x, y, z) == Charmap::CHAR_DOOR_DOWN) {
        has_door      = true;
        has_door_down = true;
        doors_down.push_back(point(x, y));
        if (y == 0) {
          dump();
          DIE("down door is in top row?");
        }
        if (get(data, x, y - 1, z) == ' ') {
          dump();
          DIE("down door has space next to it?");
        }
      }
      if (get(data, x, y, z) == Charmap::CHAR_DOOR_LEFT) {
        has_door      = true;
        has_door_left = true;
        doors_left.push_back(point(x, y));
        if (x == width - 1) {
          dump();
          DIE("left door is in right column?");
        }
        if (get(data, x + 1, y, z) == ' ') {
          dump();
          DIE("left door has space next to it?");
        }
      }
      if (get(data, x, y, z) == Charmap::CHAR_DOOR_RIGHT) {
        has_door       = true;
        has_door_right = true;
        doors_right.push_back(point(x, y));
        if (x == 0) {
          dump();
          DIE("right door is in left column?");
        }
        if (get(data, x - 1, y, z) == ' ') {
          dump();
          DIE("right door has space next to it?");
        }
      }
    }
  }

  if (! doors_up.size() && ! doors_down.size() && ! doors_left.size() && ! doors_right.size()) {
    dump();
    ERR("Room has no doors");
  }
}

//
// Erase all connected character cells in the room
//
void Room::room_flood_erase(
    std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > &room_copy, int x,
    int y)
{
  bool found_something = false;

  for (auto z = 0; z < MAP_DEPTH; z++) {
    auto m = get(room_copy, x, y, z);
    if (m && (m != ' ')) {
      found_something = true;
      set(room_copy, x, y, z, ' ');
    }
  }

  if (! found_something) {
    return;
  }

  if (x > 0) {
    room_flood_erase(room_copy, x - 1, y);
  }
  if (x < width - 1) {
    room_flood_erase(room_copy, x + 1, y);
  }
  if (y > 0) {
    room_flood_erase(room_copy, x, y - 1);
  }
  if (y < height - 1) {
    room_flood_erase(room_copy, x, y + 1);
  }
}

bool Room::room_do_any_doors_remain(
    std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > &room_copy)
{
  //
  // Erase everything that adjoins a door.
  //
  for (auto x : range< int >(0, width)) {
    for (auto y : range< int >(0, height)) {
      if (get(room_copy, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_UP) {
        return true;
      }
      if (get(room_copy, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_DOWN) {
        return true;
      }
      if (get(room_copy, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_LEFT) {
        return true;
      }
      if (get(room_copy, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_RIGHT) {
        return true;
      }
    }
  }
  return false;
}

//
// Check doors can all reach each other.
//
void Room::room_check_doors_can_reach_each_other(void)
{
  //
  // Chasms are more challenging
  //
  if (biome == BIOME_CHASMS) {
    return;
  }

  //
  // Erase everything that adjoins a door.
  //
  for (auto x : range< int >(0, width)) {
    for (auto y : range< int >(0, height)) {
      if (get(data, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_UP) {
        std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > data_copy {};
        ::std::copy(mbegin(data), mend(data), mbegin(data_copy));
        room_flood_erase(data_copy, x, y);
        if (room_do_any_doors_remain(data_copy)) {
          dump();
          DIE("found an unconnected up door");
        }
      }
      if (get(data, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_DOWN) {
        std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > data_copy {};
        ::std::copy(mbegin(data), mend(data), mbegin(data_copy));
        room_flood_erase(data_copy, x, y);
        if (room_do_any_doors_remain(data_copy)) {
          dump();
          DIE("found an unconnected down door");
        }
      }
      if (get(data, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_LEFT) {
        std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > data_copy {};
        ::std::copy(mbegin(data), mend(data), mbegin(data_copy));
        room_flood_erase(data_copy, x, y);
        if (room_do_any_doors_remain(data_copy)) {
          dump();
          DIE("found an unconnected left door");
        }
      }
      if (get(data, x, y, MAP_DEPTH_OBJ) == Charmap::CHAR_DOOR_RIGHT) {
        std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > data_copy {};
        ::std::copy(mbegin(data), mend(data), mbegin(data_copy));
        room_flood_erase(data_copy, x, y);
        if (room_do_any_doors_remain(data_copy)) {
          dump();
          DIE("found an unconnected right door");
        }
      }
    }
  }
}

void Room::finalize(void)
{
  find_doors();

  IF_DEBUG3 { dump(); }
}

void Room::dump(std::array< std::array< std::array< char, MAP_DEPTH >, MAP_ROOM_HEIGHT >, MAP_ROOM_WIDTH > &data)
{
  IF_DEBUG3
  {
    std::array< std::array< char, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > tmp {};
    for (auto y = 0; y < height; y++) {
      for (auto x = 0; x < width; x++) {
        set(tmp, x, y, ' ');
      }
    }

    for (auto y = 0; y < height; y++) {
      for (auto x = 0; x < width; x++) {
        for (auto d = MAP_DEPTH - 1; d >= 0; d--) {
          auto m = get(data, x, y, d);
          if (! m || (m == ' ')) {
            continue;
          }

          auto cr = get(Charmap::all_charmaps, m);
          auto c  = cr.c;

          set(tmp, x, y, c);
          break;
        }
      }
    }

    LOG("ROOM(%d): depth %d", roomno, depth);
    LOG("ROOM(%d): direction: Up %d down %d left %d right %d", roomno, dir_up, dir_down, dir_left, dir_right);
    LOG("ROOM(%d): doors:     up %d down %d left %d right %d", roomno, has_door_up, has_door_down, has_door_left,
        has_door_right);
    for (auto y = 0; y < height; y++) {
      std::string s;
      for (auto x = 0; x < width; x++) {
        s += get(tmp, x, y);
      }
      LOG("ROOM(%d): %s", roomno, s.c_str());
    }
    LOG("-");
  }
}

void Room::dump(void) { dump(data); }

void Room::con(void)
{
  IF_DEBUG3
  {
    std::array< std::array< char, MAP_HEIGHT_MAX >, MAP_WIDTH_MAX > tmp {};
    for (auto y = 0; y < height; y++) {
      for (auto x = 0; x < width; x++) {
        set(tmp, x, y, ' ');
      }
    }

    for (auto y = 0; y < height; y++) {
      for (auto x = 0; x < width; x++) {
        for (auto d = MAP_DEPTH - 1; d >= 0; d--) {
          auto m = get(data, x, y, d);
          if (! m || (m == ' ')) {
            continue;
          }

          auto cr = get(Charmap::all_charmaps, m);
          auto c  = cr.c;

          set(tmp, x, y, c);
          break;
        }
      }
    }

    CON("ROOM(%d): depth %d", roomno, depth);
    CON("ROOM(%d): direction: Up %d down %d left %d right %d", roomno, dir_up, dir_down, dir_left, dir_right);
    CON("ROOM(%d): doors:     up %d down %d left %d right %d", roomno, has_door_up, has_door_down, has_door_left,
        has_door_right);
    for (auto y = 0; y < height; y++) {
      std::string s;
      for (auto x = 0; x < width; x++) {
        s += get(tmp, x, y);
      }
      CON("ROOM(%d): %s", roomno, s.c_str());
    }
    CON("-");
  }
}

bool Room::contains(int depth, char what)
{
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto m = get(data, x, y, depth);
      if (m == what) {
        return true;
      }
    }
  }
  return false;
}

bool Room::contains(int depth, char what1, char what2)
{
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto m = get(data, x, y, depth);
      if ((m == what1) || (m == what2)) {
        return true;
      }
    }
  }
  return false;
}

bool Room::contains(int depth, char what1, char what2, char what3)
{
  for (auto y = 0; y < height; y++) {
    for (auto x = 0; x < width; x++) {
      auto m = get(data, x, y, depth);
      if ((m == what1) || (m == what2) || (m == what3)) {
        return true;
      }
    }
  }
  return false;
}
