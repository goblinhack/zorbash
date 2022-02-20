//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon_grid.hpp"
#include "my_game.hpp"
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

void Game::place_player(void)
{
  //
  // Place the player if we do not have one.
  //
  if (! game->level) {
    ERR("No level for player");
    return;
  }

  LOG("INF: Place player");

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! level->is_ascend_dungeon(x, y)) {
        continue;
      }
      auto t = level->thing_new("player2", point(x, y));
      {
        auto W = level->thing_new("wand_descent", point(x, y));
        t->carry(W);
        t->enchant_without_stone(W);
      }
      if (0) {
        auto w3 = level->thing_new("sword1_wood", point(x, y));
        t->carry(w3);
      }
      {
        auto w3 = level->thing_new("shovel", point(x, y));
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
        {
          auto W = level->thing_new("wand_fire", point(x, y));
          t->carry(W);
          t->enchant_without_stone(W);
        }
        {
          auto W = level->thing_new("wand_cold", point(x, y));
          t->carry(W);
          t->enchant_without_stone(W);
        }
        // level->thing_new("belcher", point(x + 3, y));
        // level->thing_new("gargoyle_moving", point(x + 2, y - 5));
        // level->thing_new("rat_giant", point(x + 1, y - 1));
        // level->thing_new("rat_giant", point(x + 1, y + 1));
        // level->thing_new("rat_giant", point(x - 1, y + 1));
        // level->thing_new("gargoyle_static", point(x + 2, y - 2));
        // level->thing_new("lava", point(x, y));
        level->thing_new("food_frog", point(x + 3, y - 1));
        level->thing_new("fire", point(x + 3, y - 1));
        // level->thing_new("enchantstone", point(x + 1, y - 1));
        // level->thing_new("horseshoe", point(x + 2, y - 1));
        // level->thing_new("four_leaf_clover", point(x + 2, y - 1));
        // level->thing_new("medal_of_valor", point(x + 2, y - 1));
        // level->thing_new("wooden_cross", point(x + 2, y - 1));
        // level->thing_new("spiderweb", point(x + 3, y));
        // level->thing_new("armor_lather", point(x, y - 2));
        // level->thing_new("boots_fluffy", point(x, y - 2));
        // level->thing_new("shield_woodon", point(x, y - 2));
        // level->thing_new("fire", point(x, y - 2));
        // level->thing_new("food_frog", point(x, y - 2));
        // level->thing_new("thunderstone", point(x, y - 2));
        // level->thing_new("map_treasure", point(x, y - 2));
        // level->thing_new("map_beast", point(x, y - 2));
        // level->thing_new("zorblin", point(x + 1, y));
        // level->thing_new("zorb_pack", point(x + 2, y));
        // level->assign_leaders_and_followers();
        // level->thing_new("key_pair", point(x - 1, y - 2));
        // level->thing_new("key_golden", point(x - 1, y + 2));
        // level->thing_new("key_penta", point(x, y + 12));
      }

      LOG("INF: Placed player");

      //
      // Zoom the map to the player
      //
      LOG("INF: Scroll to player");
      level->scroll_map_to_player();
    }
  }

  level->ts_fade_in_begin = time_get_time_ms_cached();
  level->ts_redraw_bg     = 1; // Force redraw
}
