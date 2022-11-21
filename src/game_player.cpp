//
// Copyright Neil McGill, goblinhack@gmail.com
//

// REMOVED #include "my_array_bounds_check.hpp"
// REMOVED #include "my_dungeon_grid.hpp"
#include "my_game.hpp"
// REMOVED #include "my_globals.hpp"
// REMOVED #include "my_globals_extra.hpp"
// REMOVED #include "my_level.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_random_name.hpp"
// REMOVED #include "my_sys.hpp"
#include "my_thing.hpp"
// REMOVED #include "my_wid_actionbar.hpp"
// REMOVED #include "my_wid_botcon.hpp"
// REMOVED #include "my_wid_inventory.hpp"
// REMOVED #include "my_wid_popup.hpp"
// REMOVED #include "my_wid_rightbar.hpp"
// REMOVED #include "my_wid_skillbox.hpp"
// REMOVED #include "my_wid_thing_info.hpp"
// REMOVED #include "my_wid_topcon.hpp"
// REMOVED #include "my_world.hpp"

void Game::place_player(void)
{
  //
  // Place the player if we do not have one.
  //
  if (! level) {
    ERR("No level for player");
    return;
  }

  DBG("INF: Place player");

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! level->is_ascend_dungeon(x, y)) {
        continue;
      }
      auto t = level->thing_new("player2", point(x, y));
      if (0) {
        auto k = level->thing_new("key", point(x, y));
        t->carry(k);
      }
      if (1) {
        auto w = level->thing_new("sword_wood", point(x, y));
        t->carry(w);
      }
      if (1) {
        auto w = level->thing_new("food_pottedmeat", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("armor_lather", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("sword_plutonium", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("potion_health", point(x - 1, y + 1));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("staff_descent", point(x, y));
        t->carry(w);
        // t->enchant_without_stone(w);
        // t->enchant_without_stone(w);
        // t->enchant_without_stone(w);
        // t->enchant_without_stone(w);
      }
      if (0) {
        level->thing_new("wall_dungeon.1", point(x + 1, y));
        level->thing_new("wall_dungeon.1", point(x, y + 2));
        level->thing_new("descend_sewer1", point(x + 4, y + 4));
      }
      if (0) {
        level->thing_new("boots_jumping", point(x + 1, y - 2));
        level->thing_new("boots_teleport", point(x + 1, y - 1));
      }
      if (0) {
        auto w = level->thing_new("gauntlets_lion", point(x, y - 2));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("buff_undead_resist", point(x, y));
        t->buff_add(w);
      }
      if (0) {
        level->thing_new("zorb_necro", point(x + 2, y));
        level->thing_new("zorb_pirate", point(x + 2, y + 1));
        level->thing_new("fire", point(x + 1, y));
        level->thing_new("fire", point(x + 1, y - 1));
        level->thing_new("fire", point(x + 1, y + 1));
        level->thing_new("small_fire", point(x + 3, y + 3));
      }
      if (0) {
        auto w = level->thing_new("skill_devoted_thrust", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("amulet_endurance", point(x, y - 2));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("staff_lightning", point(x, y));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("pike", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("scythe", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("double_shovel", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("shovel", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto r1 = level->thing_new("ring_shield", point(x, y));
        t->carry(r1);
        auto r2 = level->thing_new("ring_poison_resist", point(x, y));
        t->carry(r2);
      }
      if (0) {
        auto w = level->thing_new("very_broadsword", point(x, y));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("sword_draining", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("axe", point(x, y));
        t->carry(w);
      }
      if (1) {
        auto w = level->thing_new("torch", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("wooden_cross", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("cloak_stone", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("cloak_fire", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("cloak_protection", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("torch", point(x, y));
        t->carry(w);
      }
      if (1) {
        auto b = level->thing_new("bag_s", point(x, y));
        t->carry(b);
      }
      if (0) {
        auto b = level->thing_new("enchantstone", point(x, y));
        t->carry(b);
      }
      if (0) {
        auto b = level->thing_new("skillstone", point(x, y));
        t->carry(b);
      }
      if (0) {
        auto b = level->thing_new("thunderstone", point(x, y));
        t->carry(b);
      }
      if (0) {
        auto b = level->thing_new("chest1", point(x, y));
        auto w = level->thing_new("wooden_cross", point(x, y));
        b->carry(w);
      }
      if (0) {
        auto w = level->thing_new("staff_energy", point(x, y));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("map_treasure", point(x, y));
        t->carry(w);
      }
      if (0) {
        auto w = level->thing_new("map_beast", point(x, y));
        t->carry(w);
      }
      if (1) {
        level->thing_new("zorb_eldster", point(x + 1, y));
        level->thing_new("cement_man", point(x + 4, y + 3));
        // auto w = level->thing_new("staff_negation", point(x, y));
        // auto w = level->thing_new("staff_lightning", point(x, y));
        auto w = level->thing_new("staff_descent", point(x, y));
        // auto w = level->thing_new("staff_fire", point(x, y));
        t->carry(w);
        // t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("staff_fire", point(x, y));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("staff_descent", point(x, y));
        t->carry(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        level->thing_new("water", point(x + 1, y));
        level->thing_new("deep_water", point(x + 2, y));
        level->thing_new("deep_water", point(x + 3, y));
        level->thing_new("water", point(x + 4, y));

        level->thing_new("water", point(x + 1, y + 1));
        level->thing_new("deep_water", point(x + 2, y + 1));
        level->thing_new("deep_water", point(x + 3, y + 1));
        level->thing_new("water", point(x + 4, y + 1));

        level->thing_new("water", point(x + 1, y + 2));
        level->thing_new("deep_water", point(x + 2, y + 2));
        level->thing_new("deep_water", point(x + 3, y + 2));
        level->thing_new("water", point(x + 4, y + 2));

        level->thing_new("water", point(x + 1, y + 3));
        level->thing_new("deep_water", point(x + 2, y + 3));
        level->thing_new("deep_water", point(x + 3, y + 3));
        level->thing_new("water", point(x + 4, y + 3));

        level->thing_new("water", point(x + 1, y + 4));
        level->thing_new("deep_water", point(x + 2, y + 4));
        level->thing_new("deep_water", point(x + 3, y + 4));
        level->thing_new("water", point(x + 4, y + 4));

        level->thing_new("water", point(x + 1, y + 5));
        level->thing_new("deep_water", point(x + 2, y + 5));
        level->thing_new("deep_water", point(x + 3, y + 5));
        level->thing_new("water", point(x + 4, y + 5));

        // level->thing_new("kraken", point(x + 2, y + 2));

        // level->thing_new("cleaner", point(x + 2, y - 2));
      }

      IF_DEBUG2
      {
        if (0) {
          level->thing_new("lava", point(x + 1, y));
          level->thing_new("lava", point(x + 2, y));
          level->thing_new("lava", point(x + 3, y));
        }
        if (0) {
          level->thing_new("coffin_mob", point(x + 2, y + 1));
        }
        if (0) {
          level->thing_new("barrel", point(x + 2, y + 1));
          level->thing_new("rat_giant", point(x + 3, y + 1));
        }
        if (0) {
          level->thing_new("staff_energy", point(x, y + 1));
        }
        // level->thing_new("gargoyle_moving", point(x + 2, y - 5));
        // level->thing_new("rat_giant", point(x - 1, y));
        // level->thing_new("rat_giant", point(x + 1, y));
        // level->thing_new("rat_giant", point(x, y - 1));
        // level->thing_new("door_metal", point(x + 2, y));
        // level->thing_new("rock1", point(x + 1, y));
        // level->thing_new("rock1", point(x + 3, y));
        // level->thing_new("gargoyle_static", point(x + 2, y - 2));
        // level->thing_new("food_frog", point(x + 3, y - 1));
        // level->thing_new("fire", point(x + 1, y - 1));
        // level->thing_new("enchantstone", point(x + 1, y - 1));
        // level->thing_new("skillstone", point(x + 1, y - 1));
        // level->thing_new("horseshoe", point(x, y));
        // level->thing_new("four_leaf_clover", point(x, y));
        // level->thing_new("medal_of_valor", point(x, y));
        // level->thing_new("wooden_cross", point(x, y));
        // level->thing_new("armor_lather", point(x, y));
        // level->thing_new("boots_fluffy", point(x, y - 2));
        // level->thing_new("boots_silence", point(x, y - 2));
        // level->thing_new("boots_teleport", point(x, y - 2));
        // level->thing_new("mummy_necro", point(x + 5, y + 1));
        // level->thing_new("shield_woodon", point(x, y - 2));
        // level->thing_new("fire", point(x, y - 2));
        // level->thing_new("food_frog", point(x, y - 2));
        // level->thing_new("cleaner", point(x + 1, y + 3));
        // level->thing_new("thunderstone", point(x, y - 2));
        // level->thing_new("zorb_eldster", point(x + 5, y));
        // level->thing_new("key", point(x + 5, y));
        // level->thing_new("key_pair", point(x - 1, y - 2));
        // level->thing_new("key_golden", point(x - 1, y + 2));
        // level->thing_new("key_penta", point(x, y + 12));
        // level->thing_new("snake_viper", point(x, y + 2));
        // level->thing_new("zorb_pack", point(x + 2, y));
        // level->thing_new("mummy_pack", point(x + 2, y + 12));
        // level->thing_new("barrel", point(x - 2, y));
        // level->thing_new("floor_red_blood1", point(x + 2, y + 1));
        // level->thing_new("teleport", point(x + 2, y + 2));
        // level->thing_new("teletoad", point(x + 2, y + 2));
        // level->thing_new("flesh_golem", point(x, y + 1));
        level->assign_leaders_and_followers();
      }
      if (0) {
        level->thing_new("cleaner", point(x, y));
        level->thing_new("gargoyle_static", point(x, y + 1));
      }
      if (0) {
        level->thing_new("foilage", point(x, y + 1));
        level->thing_new("mummy", point(x - 1, y + 1));
      }
      // level->thing_new("lizardkin", point(x - 2, y + 1));
      // level->thing_new("vampire_rose", point(x - 2, y + 1));
      // level->thing_new("blob", point(x - 2, y + 1));
      // level->thing_new("belcher", point(x - 3, y + 1));
      // level->thing_new("cleaner", point(x - 3, y + 2));
      if (0) {
        auto d = level->thing_new("bat_lesser", point(x + 2, y + 2));
        d->wake("");
        d->is_burnt = true;
        d->dead("x");
      }
      if (0) {
        level->thing_new("lava", point(x + 2, y + 1));
        level->thing_new("block_of_ice", point(x + 2, y + 1));
      }
      // level->thing_new("vampire_rose_stem", point(x, y + 1));
      // level->thing_new("fire", point(x - 4, y + 5));
      // level->thing_new("foilage", point(x - 4, y + 5));
      // level->thing_new("foilage", point(x, y + 5));
      // level->player->on_fire_set("");
      // level->thing_new("block_of_ice", point(x, y + 1));
      // level->thing_new("block_of_ice", point(x, y + 2));
      if (0) {
        level->thing_new("vampire_rose_stem1", point(x - 1, y + 2));
        level->thing_new("vampire_rose_stem2", point(x + 1, y + 2));
        level->thing_new("vampire_rose_stem1", point(x - 1, y + 1));
        level->thing_new("vampire_rose_stem2", point(x + 1, y + 1));
        level->thing_new("vampire_rose_stem1", point(x, y + 1));
        level->thing_new("vampire_rose_stem2", point(x - 1, y + 3));
        level->thing_new("vampire_rose_stem1", point(x + 1, y + 3));
        level->thing_new("vampire_rose_stem2", point(x, y + 3));
        level->thing_new("vampire_rose_stem1", point(x - 1, y + 4));
        level->thing_new("vampire_rose_stem2", point(x + 1, y + 4));
        level->thing_new("vampire_rose_stem1", point(x, y + 4));
      }
      if (0) {
        level->thing_new("jelly_parent", point(x, y + 4));
      }
      if (0) {
        auto d = level->thing_new("dogman", point(x + 1, y + 2));
        d->dead("x");
        // level->thing_new("potion_health", point(x + 3, y + 4));
      }

      // level->thing_new("staff_descent", point(x + 5, y + 2));
      // level->thing_new("fire", point(x + 5, y + 2));
      // level->thing_new("spiderweb", point(x, y));
      // level->thing_new("spider_giant", point(x + 2, y));
      if (0) {
        level->thing_new("bat_lesser", point(x + 2, y + 1));
      }
      // level->thing_new("flesh_golem", point(x, y + 3));
      // level->thing_new("lava", point(x, y + 5));
      // level->thing_new("lava", point(x, y + 6));
      // level->thing_new("lava", point(x, y + 7));
      // level->thing_new("lava", point(x + 1, y + 5));
      // level->thing_new("lava", point(x + 1, y + 6));
      // level->thing_new("lava", point(x + 1, y + 7));
      // level->thing_new("lava", point(x + 1, y + 7));
      //
      if (0) {
        auto m = level->thing_new("coffin_mob", point(x, y + 4));
        m->frozen_set();
      }
      // level->thing_new("flameskull", point(x, y + 4));

      if (0) {
        auto m = level->thing_new("jelly_parent", point(x, y + 4));
        m->frozen_set();
      }
      // level->thing_new("jelly_baby", point(x, y + 2));
      //
      // Zoom the map to the player
      //
      level->scroll_map_to_player();

      DBG("INF: Placed player");
    }
  }

  level->ts_fade_in_begin = time_ms_cached();
  level->ts_redraw_bg     = 1; // Force redraw

  auto player = level->player;
  if (player) {
    level->request_player_light_update = true;

    if (0) {
      level->thing_new("water", point(player->curr_at.x, player->curr_at.y));
      level->thing_new("water", point(player->curr_at.x + 1, player->curr_at.y));
      level->thing_new("water", point(player->curr_at.x + 1, player->curr_at.y + 1));
      level->thing_new("water", point(player->curr_at.x + 2, player->curr_at.y + 1));
      level->thing_new("block_of_ice", point(player->curr_at.x, player->curr_at.y));
      player->frozen_set();
      level->thing_new("lava", point(player->curr_at.x, player->curr_at.y));
    }

    if (0) {
      IF_DEBUG2
      {
        player->health_max_incr(200);
        // player->health_decr(90);
      }
    }
  }
}
