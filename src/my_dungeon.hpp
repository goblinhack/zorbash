//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once

#include <array>
#include <vector>

#include "my_depth.hpp"
#include "my_dungeon_grid.hpp"
// REMOVED #include "my_fwd.hpp"
#include "my_game_defs.hpp"
// REMOVED #include "my_point.hpp"

#define STRINGIFY(x) #x
#define TOSTRING(x)  STRINGIFY(x)
#define AT           __FILE__ ":" TOSTRING(__LINE__)

class Grid
{
public:
  std::array< std::array< Roomp, DUNGEON_GRID_CHUNK_HEIGHT >, DUNGEON_GRID_CHUNK_WIDTH > node_rooms {};
};

using Dungeonp = class Dungeon *;

class Dungeon
{
public:
  //
  // Set on create fail
  //
  bool failed {};
  //
  // The. World.
  //
  std::vector< char > cells;
  //
  // For rollback when moving rooms around.
  //
  std::vector< char > cells_saved;
  //
  // Pointers from map position to room
  //
  std::vector< Roomp >                                   cells_room;
  int                                                    map_width {MAP_WIDTH};
  int                                                    map_height {MAP_HEIGHT};
  int                                                    map_depth {MAP_DEPTH};
  std::array< std::array< int, MAP_HEIGHT >, MAP_WIDTH > map_jigsaw_buffer_water_depth {};
  //
  // High level view of the map.
  //
  int    grid_width {0};
  int    grid_height {0};
  Nodes *nodes {};
  //
  // Root seed for the dungeon
  //
  uint32_t seed;
  //
  // Room pointers on the above nodes map
  //
  Grid grid {};
  //
  // Placed rooms
  //
  std::vector< Roomp > all_placed_rooms;

  Dungeon(int map_width, int map_height, int grid_width, int grid_height, uint32_t seed);
  Dungeon(int level);
  ~Dungeon();

  Roomp *cell_rooms_addr(const int x, const int y);
  Roomp *cell_rooms_addr_no_check(const int x, const int y);

  Roomp getr(const int x, const int y);
  Roomp getr_no_check(const int x, const int y);

  bool can_place_room(Roomp r, int x, int y);
  bool create_cyclic_rooms(Grid *g);
  bool is_anything_at(const int x, const int y);
  bool is_anything_at(const int x, const int y, const int z);
  bool is_anything_at_no_check(const int x, const int y);
  bool is_anything_at_no_check(const int x, const int y, const int z);
  bool is_ascend_dungeon(const int x, const int y);
  bool is_ascend_dungeon_no_check(const int x, const int y);
  bool is_barrel(const int x, const int y);
  bool is_brazier(const int x, const int y);
  bool is_bridge(const int x, const int y);
  bool is_bridge_no_check(const int x, const int y);
  bool is_chasm(const int x, const int y);
  bool is_chasm_no_check(const int x, const int y);
  bool is_corridor(const int x, const int y);
  bool is_corridor_no_check(const int x, const int y);
  bool is_deep_water(const int x, const int y);
  bool is_deep_water_no_check(const int x, const int y);
  bool is_descend_dungeon(const int x, const int y);
  bool is_descend_dungeon_no_check(const int x, const int y);
  bool is_descend_sewer_at(const int x, const int y);
  bool is_descend_sewer(const int x, const int y);
  bool is_descend_sewer_no_check(const int x, const int y);
  bool is_dirt(const int x, const int y);
  bool is_dirt_no_check(const int x, const int y);
  bool is_door(const int x, const int y);
  bool is_door_no_check(const int x, const int y);
  bool is_dry_grass(const int x, const int y);
  bool is_enchantstone(const int x, const int y);
  bool is_floor(const int x, const int y);
  bool is_floor_deco_at(const int x, const int y);
  bool is_floor_no_check(const int x, const int y);
  bool is_foilage(const int x, const int y);
  bool is_food(const int x, const int y);
  bool is_gold(const int x, const int y);
  bool is_hazard(const int x, const int y);
  bool is_key(const int x, const int y);
  bool is_lava(const int x, const int y);
  bool is_lava_no_check(const int x, const int y);
  bool is_mob_any(const int x, const int y);
  bool is_mob_challenge_class_a(const int x, const int y);
  bool is_mob_challenge_class_b(const int x, const int y);
  bool is_monst_any(const int x, const int y);
  bool is_monst_class_a(const int x, const int y);
  bool is_monst_class_b(const int x, const int y);
  bool is_monst_class_c(const int x, const int y);
  bool is_monst_class_d(const int x, const int y);
  bool is_monst_class_e(const int x, const int y);
  bool is_oob(const int x, const int y);
  bool is_oob(const int x, const int y, const int z);
  bool is_potion(const int x, const int y);
  bool is_red_blood(const int x, const int y);
  bool is_ring(const int x, const int y);
  bool is_rock(const int x, const int y);
  bool is_secret_corridor_at(const int x, const int y);
  bool is_secret_door(const int x, const int y);
  bool is_shallow_water(const int x, const int y);
  bool is_shallow_water_no_check(const int x, const int y);
  bool is_skillstone(const int x, const int y);
  bool is_spiderweb(const int x, const int y);
  bool is_treasure_class_a(const int x, const int y);
  bool is_treasure_class_b(const int x, const int y);
  bool is_treasure_class_c(const int x, const int y);
  bool is_treasure_type(const int x, const int y);
  bool is_wall(const int x, const int y);
  bool is_wall_no_check(const int x, const int y);
  bool is_staff(const int x, const int y);
  bool is_weapon_class_a(const int x, const int y);
  bool is_weapon_class_b(const int x, const int y);
  bool is_weapon_class_c(const int x, const int y);
  bool is_wet_grass(const int x, const int y);
  bool room_is_a_candidate(int x, int y, const DungeonNode *n, Roomp r);
  bool room_is_a_candidate_less_restrictive(const DungeonNode *n, Roomp r);
  bool rooms_move_closer_together(void);
  bool solve(int x, int y, Grid *g);

  char getc(const int x, const int y, const int z);
  char getc_no_check(const int x, const int y, const int z);

  int draw_corridor(point start, point end, char w);
  int draw_corridors(void);
  int get_grid_depth_at(const int x, const int y);
  int offset(const int x, const int y);
  int offset(const int x, const int y, const int z);

  void add_border(void);
  void add_corridor_walls(void);
  void add_foilage_around_water(void);
  void add_remaining(void);
  void add_room_walls(void);
  void add_spiderweb(void);
  void assign_rooms_to_tiles(void);
  void block_secret_doors(void);
  void cave_generation(void);
  void cave_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations);
  void center_room_layout(void);
  void choose_room_doors(void);
  void create_node_map(void);
  void debug(const std::string s);
  void dirt_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations);
  void dmap_set_is_walls(Dmapp d);
  void dry_grass_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations);
  void dump(void);
  void foilage_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations);
  void make_dungeon(void);
  void map_place_room_ptr(Roomp r, int x, int y);
  void place_doors_between_depth_changes(void);
  void place_level(LevelStaticp l);
  void place_room(Roomp r, int x, int y);
  void putc(const int x, const int y, const int z, const char c);
  void putc_no_check(const int x, const int y, const int z, const char c);
  void putr(const int x, const int y, Roomp r);
  void remove_all_doors(void);
  void reset_possible_rooms(void);
  void restore_level(void);
  void room_print_at(Roomp r, int x, int y);
  void room_print_only_doors_at(Roomp r, int x, int y);
  void room_print_only_doors(Grid *g);
  void rooms_print_all(Grid *g);
  void save_level(void);
  void water_fixup_shallows(void);
  void water_fixup(void);
  void water_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations);
  void wet_grass_gen(unsigned int map_fill_prob, int map_r1, int map_r2, int map_generations);

  unsigned int MAP_FILL_PROB   = 10;
  unsigned int MAP_R1          = 5;
  unsigned int MAP_R2          = 2;
  int          MAP_GENERATIONS = 5;

  //
  // Used temporarily during level generation.
  //
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > map_save {};
  std::array< std::array< uint8_t, MAP_HEIGHT >, MAP_WIDTH > map_curr {};

  char *cell_addr(const int x, const int y, const int z);
  char *cell_addr_no_check(const int x, const int y, const int z);
};

extern class Dungeon *dungeon_test(void);
