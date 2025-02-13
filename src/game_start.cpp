//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_wid_actionbar.hpp"
#include "my_wid_asciimap.hpp"
#include "my_wid_botcon.hpp"
#include "my_wid_inventory.hpp"
#include "my_wid_leftbar.hpp"
#include "my_wid_rightbar.hpp"
#include "my_wid_skillbox.hpp"
#include "my_wid_spellbox.hpp"
#include "my_wid_thing_info.hpp"
#include "my_wid_topcon.hpp"
#include "my_wid_tp_info.hpp"

void Game::start(void)
{
  TRACE_AND_INDENT();
  CON("Start the game!");

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
  wid_tp_info_fini("start the game");
  wid_inventory_fini();

  wid_skillbox_fini();
  wid_skillbox_init();

  wid_spellbox_fini();
  wid_spellbox_init();

  wid_actionbar_init();
  wid_asciimap_init();

  wid_visible(wid_topcon_window);
  TOPCON("Welcome to the lair of the dread monster, %%fg=red$Zorbash%%fg=reset$.");
  TOPCON("Collect the %%fg=yellow$crystals%%fg=reset$ and defeat Zorbash to win.");

  CON("%%fg=red$OOOOOO  OOOOO  OOOOOO  OOOOOO   OOOOO   OOOO  OOO OOO%%fg=reset$");
  CON("%%fg=red$OOOOOO OOOOOOO OOOOOOO OOOOOOO OOOOOOO OOOOOO OOO OOO%%fg=reset$");
  CON("%%fg=red$   OO! OO! OOO OO! OOO OO! OOO OO! OOO !OO    OO! OOO%%fg=reset$");
  CON("%%fg=red$   O!  !O! O!O !O! O!O !O  O!O !O! O!O !O!    !O! O!O%%fg=reset$");
  CON("%%fg=red$  O!   O!O !O! O!O!O!  O!OO!O  O!OO!O! !!O!!  O!O!!O!%%fg=reset$");
  CON("%%fg=red$ !!    !O! !!! !!O!!   !!!!!!! !!!!!!!  !!!!! !!!O!!!%%fg=reset$");
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
  CON("You can also enter python code here.%%fg=reset$");

  wid_botcon_fini();
  wid_botcon_init();
  wid_visible(wid_botcon_window);

  BOTCON("Press 'h' to see key bindings.");

  place_player();
  pcg_random_allowed--;
}
