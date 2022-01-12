//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
#include "my_game_dungeons.hpp"
#include "my_globals.hpp"
#include "my_globals_extra.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_random_name.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "my_world.hpp"

void Game::pre_init(void)
{
  TRACE_AND_INDENT();

  set_seed();

  current_level = point3d(0, 0, 0);
  level         = nullptr;

  world.clear();
}

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  pre_init();

  CON("Creating level, name '%s', seed %u", seed_name.c_str(), seed);

  // init_levels();
  init_jump_paths();

  // auto l = get(world.levels, current_level.x, current_level.y, current_level.z);
  // if (! l) {
  // return;
  //}
  // level = l;
}

void Game::set_seed(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  if (g_opt_seed_name != "") {
    seed_name = g_opt_seed_name;
  } else {
    seed_name = random_name(sizeof("4294967295") - 1);
  }
  seed = string_to_hash(seed_name);
  pcg_srand(seed);
}

void Game::init_level(point3d p)
{
  DBG("Game init level %d,%d,%d", p.x, p.y, p.z);
  TRACE_AND_INDENT();

  auto level_seed = seed + p.x + p.y + p.z;
  TRACE_AND_INDENT();
  auto l = get(world.levels, p.x, p.y, p.z);
  TRACE_AND_INDENT();
  if (! l) {
    DBG("Create new level at: %d,%d,%d", p.x, p.y, p.z);
    world.new_level_at(p, level_seed);
    l = get(world.levels, p.x, p.y, p.z);
    if (! l) {
      ERR("No level created at: %d,%d,%d", game->current_level.x, game->current_level.y, game->current_level.z);
    }
  } else {
    LOG("Level already exists: %d,%d,%d", p.x, p.y, p.z);
  }
}

void Game::init_levels(void)
{
  LOG("Game init levels");
  TRACE_AND_INDENT();

  //
  // Increase this to create more levels in advance
  //
  for (auto z = 0; z <= 0; z++) {
    auto level_at = current_level;
    level_at.z += z;
    init_level(level_at);
  }
}

void Game::place_player(void)
{
  //
  // Place the player if we do not have one.
  //
  if (! game->level) {
    ERR("No level for player");
    return;
  }

  LOG("DGN: Place player");

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! level->is_ascend_dungeon(x, y)) {
        continue;
      }
      auto t = level->thing_new("player2", point(x, y));
      {
        auto W = level->thing_new("wand_lightning", point(x, y));
        t->carry(W);
        t->enchant_without_stone(W);
      }
      {
        auto w3 = level->thing_new("sword1_wood", point(x, y));
        t->carry(w3);
      }
      {
        auto w3 = level->thing_new("axe", point(x, y));
        t->carry(w3);
      }
      {
        auto W = level->thing_new("torch", point(x, y));
        t->carry(W);
      }
      {
        auto b = level->thing_new("bag_s", point(x, y));
        t->carry(b);
      }

      IF_DEBUG2
      {
        level->thing_new("spiderweb", point(x + 3, y));
        level->thing_new("armor_lather", point(x, y - 2));
        level->thing_new("shield_woodon", point(x + 1, y - 3));
        level->thing_new("shield_wooden", point(x, y - 3));
        level->thing_new("fire", point(x - 1, y + 1));
        level->thing_new("food_frog", point(x, y + 1));
        // level->thing_new("thunderstone", point(x - 1, y - 1));
        // level->thing_new("treasure_map", point(x - 1, y - 2));
        // level->thing_new("beast_map", point(x + 1, y - 2));
        // level->thing_new("fire", point(x + 2, y - 2));
        // level->thing_new("zorblin", point(x + 1, y));
        // level->thing_new("zorb_pack", point(x + 2, y));
      }

      LOG("DGN: Placed player");

      //
      // Zoom the map to the player
      //
      LOG("DGN: Scroll to player");
      level->scroll_map_to_player();

      return;
    }
  }
}

void Game::start(void)
{
  TRACE_AND_INDENT();
  LOG("Start the game!");

  tick_begin_ms = time_get_time_ms();

  wid_rightbar_fini();
  wid_rightbar_init();

  wid_topcon_fini();
  wid_topcon_init();

  wid_thing_info_fini();
  wid_inventory_fini();

  wid_skillbox_fini();
  wid_skillbox_init();

  wid_actionbar_init();

  wid_visible(wid_topcon_window);
  TOPCON("Welcome to the lair of the dread monster, %%fg=red$Zorbash%%fg=reset$.");
  TOPCON("Collect the %%fg=yellow$crystals%%fg=reset$ and defeat Zorbash to win.");

  CON("%%fg=red$@@@@@@  @@@@@  @@@@@@  @@@@@@   @@@@@   @@@@  @@@ @@@%%fg=reset$");
  CON("%%fg=red$@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@@ @@@@@@ @@@ @@@%%fg=reset$");
  CON("%%fg=red$   @@! @@! @@@ @@! @@@ @@! @@@ @@! @@@ !@@    @@! @@@%%fg=reset$");
  CON("%%fg=red$   @!  !@! @!@ !@! @!@ !@  @!@ !@! @!@ !@!    !@! @!@%%fg=reset$");
  CON("%%fg=red$  @!   @!@ !@! @!@!@!  @!@@!@  @!@@!@! !!@!!  @!@!!@!%%fg=reset$");
  CON("%%fg=red$ !!    !@! !!! !!@!!   !!!!!!! !!!!!!!  !!!!! !!!@!!!%%fg=reset$");
  CON("%%fg=red$ !:    !!: !!! !!: !!  !!: !!! !!: !!!     !: !!: !!!%%fg=reset$");
  CON("%%fg=red$:!     :!: !:! :!: !:! :!: !:! :!: !:!    !:! :!: !:!%%fg=reset$");
  CON("%%fg=red$:::::: ::::::: ::  ::: ::::::: ::: ::: :::::: ::  :::%%fg=reset$");
  CON("%%fg=red$::::::  :::::  ::  ::: ::::::  ::: ::: :::::: ::  :::%%fg=reset$");
  CON("%%fg=red$::::::  :::::  ::  ::: ::::::  ::: : : :::::  ::  :::%%fg=reset$");
  CON("%%fg=red$:  :    :       :  :    :  ::   :  : : :   :   :  : :%%fg=reset$");
  CON("%%fg=red$.  .      .     .    .  :  :           .   .        :%%fg=reset$");
  CON("%%fg=red$.         .                :     . :   .            :%%fg=reset$");
  CON("%%fg=red$.  . .  : . :   .  : .  :  ::   :. : . ..  .   .  : :%%fg=reset$");
  CON("%%fg=green$Version " MYVER "%%fg=reset$");
  CON("Press %%fg=yellow$<tab>%%fg=reset$ to complete commands.");
  CON("Press %%fg=yellow$?%%fg=reset$ to show command options.");
  CON("You can also enter raw python code here.");

  wid_botcon_fini();
  wid_botcon_init();

  wid_visible(wid_botcon_window);
  BOTCON("Press 'h' for help.");

  place_player();
}
