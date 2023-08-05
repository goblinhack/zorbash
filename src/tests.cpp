//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"

void run_tests()
{
  TRACE_NO_INDENT();

  if (g_opt_test_save_load) {
    CON("save load test");
    CON("==============");
    game->init();
    game->load();
    game->init();
    game->fini();
    game->init();
    game->fini();
    game->init();
    game->save();
    game->fini();
    game->load();
    DIE("end of save load test");
  }

  if (g_opt_test_dungeon_gen) {
    dungeon_test();
  }
}
