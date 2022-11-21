//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_array_bounds_check.hpp"
// REMOVED #include "my_dungeon_grid.hpp"
#include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
#include "my_globals_extra.hpp"
// REMOVED #include "my_level.hpp"
// REMOVED #include "my_random.hpp"
#include "my_random_name.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_thing.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
// REMOVED #include "my_wid_popup.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
// REMOVED #include "my_world.hpp"

void Game::pre_init(void)
{
  TRACE_AND_INDENT();

  pcg_random_allowed++;
  set_seed();

  current_level = point3d(0, 0, 0);
  level         = nullptr;

  world.clear();
  pcg_random_allowed--;
}

void Game::init(void)
{
  LOG("Game init");
  TRACE_AND_INDENT();

  pre_init();

  CON("Creating level, name '%s', seed %u", seed_name.c_str(), seed);

  init_jump_paths();
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

void Game::start(void)
{
  TRACE_AND_INDENT();
  LOG("Start the game!");

  pcg_random_allowed++;
  tick_begin_ms      = 0;
  tick_begin_game_ms = 0;

  wid_rightbar_fini();
  wid_rightbar_init();

  wid_leftbar_fini();
  wid_leftbar_init();

  wid_topcon_fini();
  wid_topcon_init();

  wid_thing_info_fini("start the game");
  wid_inventory_fini();

  wid_skillbox_fini();
  wid_skillbox_init();

  wid_actionbar_init();
  wid_asciimap_init();

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
  CON("%%fg=green$Version: " MYVER "%%fg=reset$");
  CON("Press %%fg=yellow$<tab>%%fg=reset$ to complete commands.");
  CON("Press %%fg=yellow$?%%fg=reset$ to show command options.");
  CON("You can also enter python code here.");

  wid_botcon_fini();
  wid_botcon_init();
  wid_visible(wid_botcon_window);

  BOTCON("Press 'h' to see key bindings.");

  place_player();
  pcg_random_allowed--;
}
