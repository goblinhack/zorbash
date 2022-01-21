//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::create(point3d at, uint32_t seed, int difficulty_depth, int dungeon_walk_order_level_no)
{
  TRACE_AND_INDENT();

  if (difficulty_depth > DUNGEONS_MAX_DEPTH) {
    difficulty_depth = DUNGEONS_MAX_DEPTH;
  }

  uint32_t seedval;

  if (dungeon_walk_order_level_no <= 1) {
    seedval = game->seed + 1; // +1 is a temporary hack
  } else {
    seedval = (at.z * DUNGEONS_GRID_CHUNK_HEIGHT * DUNGEONS_GRID_CHUNK_WIDTH) + (at.y * DUNGEONS_GRID_CHUNK_HEIGHT) +
              at.x + dungeon_walk_order_level_no;
  }

  game->seed = seedval;

  pcg_srand(seedval);

  is_starting = true;
  clear();

  is_level_type_dungeon = false;
  is_level_type_sewer   = false;

  this->seed                        = seedval;
  this->difficulty_depth            = difficulty_depth;
  this->dungeon_walk_order_level_no = dungeon_walk_order_level_no;
  world_at                          = at;

  //
  // Setup the various chances of things appearing.
  //
  set_chances_of_creating();

  IF_DEBUG2
  {
    log("-");
    log("Creating, seed %u", seedval);
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
    log("v v v v v v v v v v v v v v v v v v v v v v v v v v v");
  }

  //
  // Must set the level pointer so for e.g. spiders can spawn webs when born
  //
  game->level_being_created = this;

  bool ret;
  if (at.z & 1) {
    ret = create_dungeon(at, seed);
  } else {
    ret = create_sewer(at, seed);
  }

  game->level_being_created = nullptr;

  IF_DEBUG2
  {
    log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
    log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
    log("Created, seed %u", seed);
    log("-");
  }

  if (! ret) {
    err("Failed to create level");
  }

  update_map();

  game->started = true;
  is_starting   = false;

  ts_fade_in_begin = time_get_time_ms_cached();

  things_gc_force();

  if (! cursor && player) {
    cursor = thing_new("cursor", player->curr_at);
    cursor->hide();
  }

  created();
}

void Level::created(void)
{
  TRACE_AND_INDENT();

  assign_leaders_and_followers();
}

void Level::place_the_grid(void)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      (void) thing_new("the_grid", point(x, y));
      if (g_errored) {
        ERR("Could not create level");
        return;
      }
    }
  }
}

int Level::get_total_monst_hp_level(void)
{
  int hp = 0;
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    if (t->is_monst()) {
      hp += t->get_health_initial();
    }

    if (t->is_mob()) {
      hp += t->get_health_initial() * t->minion_limit();
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)
  return hp;
}

int Level::get_total_monst_damage_level(void)
{
  int damage = 0;
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    if (t->is_mob() || t->is_monst()) {
      damage += t->get_damage_melee_dice().max_roll();
      damage += t->get_damage_poison_dice().max_roll();
      damage += t->get_damage_future1_dice().max_roll();
      damage += t->get_damage_future2_dice().max_roll();
      damage += t->get_damage_future3_dice().max_roll();
      damage += t->get_damage_cold_dice().max_roll();
      damage += t->get_damage_fire_dice().max_roll();
      damage += t->get_damage_crush_dice().max_roll();
      damage += t->get_damage_lightning_dice().max_roll();
      damage += t->get_damage_energy_dice().max_roll();
      damage += t->get_damage_acid_dice().max_roll();
      damage += t->get_damage_digest_dice().max_roll();
      damage += t->get_damage_digest_dice().max_roll();
      damage += t->get_damage_natural_dice().max_roll();
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)
  return damage;
}

int Level::get_total_loot_level(void)
{
  int value = 0;
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    if (t->is_treasure() || t->is_weapon() || t->is_wand()) {
      value += t->get_gold_value();
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)
  return value;
}

int Level::get_total_food_level(void)
{
  int value = 0;
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL(this, t)
  {
    if (t->is_food()) {
      value += t->get_nutrition();
    }
  }
  FOR_ALL_THINGS_THAT_INTERACT_ON_LEVEL_END(this)
  return value;
}
