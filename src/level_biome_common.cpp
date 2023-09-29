//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_room.hpp"
#include "my_thing.hpp"

void Level::place_objects_with_normal_placement_rules(Dungeonp d)
{
  TRACE_AND_INDENT();

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      Tpp tp {};

      //
      // Reset the seed for each cell to increase the chances
      // of repeatability if other small things change in the
      // game
      //
      pcg_srand(seed + x + (y * MAP_WIDTH));

      point p(x, y);

      if (d->is_red_blood(x, y)) {
        tp = tp_random_red_blood();
      }
      if (d->is_door(x, y)) {
        tp = tp_random_door();
      }
      if (d->is_ascend_dungeon(x, y)) {
        tp = tp_random_ascend_dungeon();
      }
      if (d->is_descend_dungeon(x, y)) {
        tp = tp_random_descend_dungeon();
      }
      if (d->is_food(x, y)) {
        if (d1000() < 500) {
          tp = tp_random_food();
        }
      }
      if (d->is_gold(x, y)) {
        if (d1000() < 500) {
          tp = tp_random_gold();
        }
      }
      if (d->is_key(x, y)) {
        tp = tp_random_key();
      }
      if (d->is_potion(x, y)) {
        if (d1000() < 500) {
          tp = tp_random_potion();
        }
      }
      if (d->is_staff(x, y)) {
        if (d1000() < 500) {
          tp = tp_random_staff();
        }
      }
      if (d->is_ring(x, y)) {
        if (d1000() < 500) {
          tp = tp_random_ring();
        }
      }
      if (d->is_secret_door(x, y)) {
        if (biome == BIOME_CHASMS) {
          tp = tp_random_door();
        } else {
          tp = tp_random_secret_door();
        }
      }

      Tpp tp_monst = nullptr;
      switch (biome) {
        case BIOME_UNKNOWN : break;
        case BIOME_DUNGEON : tp_monst = get_biome_dungeon_random_monst(d, p, MONST_ENVIRON_NORMAL); break;
        case BIOME_FLOODED : tp_monst = get_biome_flooded_random_monst(d, p, MONST_ENVIRON_NORMAL); break;
        case BIOME_SWAMP : tp_monst = get_biome_swamp_random_monst(d, p, MONST_ENVIRON_NORMAL); break;
        case BIOME_SEWER : tp_monst = get_biome_sewer_random_monst(p, MONST_ENVIRON_NORMAL); break;
        case BIOME_ICE : tp_monst = get_biome_ice_random_monst(d, p, MONST_ENVIRON_NORMAL); break;
        case BIOME_CHASMS : tp_monst = get_biome_chasms_random_monst(d, p, MONST_ENVIRON_NORMAL); break;
        case BIOME_LAVA : tp_monst = get_biome_lava_random_monst(d, p, MONST_ENVIRON_NORMAL); break;
        default : break;
      }

      if (tp_monst) {
        tp = tp_monst;
      }

      //
      // If a hard monst room then always give treasure
      //
      auto r                     = d->getr(x, y);
      bool is_more_generous_room = false;
      if (r) {
        if (r->is_more_generous_room_set) {
          is_more_generous_room = r->is_more_generous_room;
        } else {
          is_more_generous_room        = r->contains(MAP_DEPTH_OBJ, Charmap::CHAR_DOOR);
          r->is_more_generous_room_set = true;
          r->is_more_generous_room     = is_more_generous_room;
        }
      }

      if (d->is_mob_class_A(x, y) || d->is_mob_class_B(x, y) || d->is_mob_class_C(x, y)) {
        //
        // If surrounded by hazards then choose an ethereal mob
        //
        if (d->is_hazard(x - 1, y) && d->is_hazard(x + 1, y) && d->is_hazard(x, y - 1) && d->is_hazard(x, y + 1)
            && d->is_hazard(x - 1, y - 1) && d->is_hazard(x + 1, y - 1) && d->is_hazard(x - 1, y + 1)
            && d->is_hazard(x + 1, y + 1)) {

          if (d1000() < d1000_chance_creating_mob_class_A) {
            tp = tp_random_ethereal_mob();
          }
        } else {
          //
          // Else choose a normal mob
          //
          if (d->is_mob_class_A(x, y)) {
            if (d1000() < d1000_chance_creating_mob_class_A) {
              tp = tp_random_mob_class_A(p);
            }
          }
          if (d->is_mob_class_B(x, y)) {
            if (d1000() < d1000_chance_creating_mob_class_B) {
              tp = tp_random_mob_class_B(p);
            }
          }
          if (d->is_mob_class_C(x, y)) {
            if (d1000() < d1000_chance_creating_mob_class_C) {
              tp = tp_random_mob_class_C(p);
            }
          }
        }
      }

      if (d->is_trap(x, y)) {
        if (d1000() < 50) {
          tp = tp_random_trap();
        }
      }

      if (d->is_barrel(x, y)) {
        if (d1000() < 200) {
          tp = tp_random_barrel();
        }
      }

      if (r && r->is_secret) {
        //
        // For secret rooms, be generous and place the good stuff first.
        // We enchant this later after placing.
        //
        if (d->is_treasure_class_A(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_A * 3) {
            tp = tp_random_treasure_class_A(p);
          }
        }
        if (d->is_treasure_class_B(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_B * 3) {
            tp = tp_random_treasure_class_B(p);
          }
        }
        if (d->is_treasure_class_C(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_C * 3) {
            tp = tp_random_treasure_class_C(p);
          }
        }
      } else if (is_more_generous_room) {
        if (d->is_treasure_class_A(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_A * 2) {
            tp = tp_random_treasure_class_A(p);
          }
        }
        if (d->is_treasure_class_B(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_B * 2) {
            tp = tp_random_treasure_class_B(p);
          }
        }
        if (d->is_treasure_class_C(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_C * 2) {
            tp = tp_random_treasure_class_C(p);
          }
        }
      } else {
        if (d->is_treasure_class_A(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_A) {
            tp = tp_random_treasure_class_A(p);
          }
        }
        if (d->is_treasure_class_B(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_B) {
            tp = tp_random_treasure_class_B(p);
          }
        }
        if (d->is_treasure_class_C(x, y)) {
          if (d1000() < d1000_chance_creating_treasure_class_C) {
            tp = tp_random_treasure_class_C(p);
          }
        }
      }

      if (r && r->is_secret) {
        //
        // For secret rooms, be generous and place the good stuff first.
        // We enchant this later after placing.
        //
        if (d->is_weapon_class_A(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_A * 3) {
            tp = tp_random_weapon_class_A(p);
          }
        }
        if (d->is_weapon_class_B(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_B * 3) {
            tp = tp_random_weapon_class_B(p);
          }
        }
        if (d->is_weapon_class_C(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_C * 3) {
            tp = tp_random_weapon_class_C(p);
          }
        }
      } else if (is_more_generous_room) {
        if (d->is_weapon_class_A(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_A * 2) {
            tp = tp_random_weapon_class_A(p);
          }
        }
        if (d->is_weapon_class_B(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_B * 2) {
            tp = tp_random_weapon_class_B(p);
          }
        }
        if (d->is_weapon_class_C(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_C * 2) {
            tp = tp_random_weapon_class_C(p);
          }
        }
      } else {
        if (d->is_weapon_class_A(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_A) {
            tp = tp_random_weapon_class_A(p);
          }
        }
        if (d->is_weapon_class_B(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_B) {
            tp = tp_random_weapon_class_B(p);
          }
        }
        if (d->is_weapon_class_C(x, y)) {
          if (d1000() < d1000_chance_creating_weapon_class_C) {
            tp = tp_random_weapon_class_C(p);
          }
        }
      }

      if (d->is_magic_stone(x, y)) {
        tp = tp_random_magic_stone();
      }

      //
      // Make sure we have a floor under a portal for example
      //
      if (! is_bridge(x, y) && ! is_chasm(x, y) && ! is_floor(x, y) && ! is_dirt(x, y) && ! is_corridor(x, y)) {
        if (biome == BIOME_CHASMS) {
          //
          // The void.
          //
        } else if (biome == BIOME_ICE) {
          static auto tp = tp_find("floor_ice1");
          if (tp) {
            (void) thing_new(tp->name(), point(x, y));
          }
        } else if (biome == BIOME_LAVA) {
          static auto tp = tp_find("floor_lava1");
          if (tp) {
            (void) thing_new(tp->name(), point(x, y));
          }
        } else {
          auto tp = tp_random_dirt();
          if (tp) {
            (void) thing_new(tp->name(), point(x, y));
          }
        }
      }

      if (d->is_portal(x, y)) {
        //
        // If the map has a portal, we must place it as place_portals will try
        // to enssure we have at least 2 portals.
        //
        tp = tp_random_portal();
      }

      if (unlikely(! tp)) {
        continue;
      }

      if (tp->environ_likes_deep_water()) {
        if (! is_deep_water(x, y)) {
          log("INF: Dropping %s for deep water", tp->name().c_str());
          continue;
        }
      }

      if (tp->is_swimmer()) {
        if (! is_water(x, y)) {
          log("INF: Dropping %s for deep water", tp->name().c_str());
          continue;
        }
      }

      if (! tp->is_critical_to_level()) {
        if (biome == BIOME_DUNGEON) {
          if (! tp->is_biome_dungeon()) {
            log("INF: Dropping %s for biome dungeon", tp->name().c_str());
            continue;
          }
        } else if (biome == BIOME_FLOODED) {
          if (! tp->is_biome_flooded()) {
            log("INF: Dropping %s for biome flooded", tp->name().c_str());
            continue;
          }
        } else if (biome == BIOME_SWAMP) {
          if (! tp->is_biome_swamp()) {
            log("INF: Dropping %s for biome swamp", tp->name().c_str());
            continue;
          }
        } else if (biome == BIOME_SEWER) {
          if (! tp->is_biome_sewer()) {
            log("INF: Dropping %s for biome sewer", tp->name().c_str());
            continue;
          }
        } else if (biome == BIOME_ICE) {
          if (! tp->is_biome_ice()) {
            log("INF: Dropping %s for biome ice", tp->name().c_str());
            continue;
          }
        } else if (biome == BIOME_CHASMS) {
          if (! tp->is_biome_chasms()) {
            log("INF: Dropping %s for biome chasms", tp->name().c_str());
            continue;
          }
        } else if (biome == BIOME_LAVA) {
          if (! tp->is_biome_lava()) {
            log("INF: Dropping %s for biome lava", tp->name().c_str());
            continue;
          }
        } else {
          continue;
        }
      }

      //
      // Don't place items where they would catch fire immediately.
      //
      if (heatmap(x, y)) {
        if (tp->is_very_combustible()) {
          continue;
        }
      }

      if (heatmap(x, y) > 2) {
        if (tp->is_combustible()) {
          continue;
        }
      }

      dbg("INF: Creating %s", tp->name().c_str());
      auto t = thing_new(tp->name(), point(x, y));
      if (t) {
        if (t->is_ascend_dungeon()) {
          if (prev_levels.size()) {
            t->open();
          }
        } else if (t->is_weapon()) {
          if (r && r->is_secret) {
            t->enchant_randomly();
          }
          dbg("INF: Placed weapon '%s'", t->text_short_capitalised().c_str());
        } else if (t->is_treasure_type()) {
          if (r && r->is_secret) {
            t->enchant_randomly();
          }
          dbg("INF: Placed treasure '%s'", t->text_short_capitalised().c_str());
        } else if (t->is_bag()) {
          dbg("INF: Placed '%s'", t->text_short_capitalised().c_str());
        } else if (t->is_monst()) {
          dbg("INF: Placed monster '%s'", t->text_short_capitalised().c_str());
        } else {
          //
          // Doors etc... don't log, not as interesting
          //
        }
      }
    }
  }
}

void Level::place_spiderweb(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_spiderweb(x, y)) {
        auto tp = tp_random_spiderweb();
        if (unlikely(! tp)) {
          return;
        }

        if (! tp->normal_placement_rules()) {
          continue;
        }

        if (heatmap(x, y)) {
          continue;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

//
// If we only have one portal, place another.
//
void Level::place_portals(Dungeonp d)
{
  TRACE_AND_INDENT();

  int portal_count = 0;

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (d->is_portal(x, y)) {
        if (++portal_count > 1) {
          return;
        }
      }
    }
  }

  //
  // Sometimes add portals if none exist
  //
  if (portal_count == 0) {
    if (pcg_random_range(0, 100) < 90) {
      return;
    }
  }

  //
  // Place an additional portal.
  //
  auto tries = 10000;

  while (tries-- > 0) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK + 1);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK + 1);

    if (d->is_oob(x, y)) {
      continue;
    }
    if (d->is_hazard(x, y)) {
      continue;
    }
    if (! d->is_floor(x, y)) {
      continue;
    }
    if (d->is_floor_deco_at(x, y)) {
      continue;
    }

    if (d->is_food(x, y) || d->is_red_blood(x, y) || d->is_door(x, y) || d->is_ascend_dungeon(x, y)
        || d->is_descend_dungeon(x, y) || d->is_mob_any(x, y) || d->is_key(x, y) || d->is_potion(x, y)
        || d->is_trap(x, y) || d->is_barrel(x, y) || d->is_staff(x, y) || d->is_ring(x, y) || d->is_secret_door(x, y)
        || d->is_portal(x, y) || d->is_weapon_class_A(x, y) || d->is_weapon_class_B(x, y) || d->is_treasure_type(x, y)
        || d->is_treasure_class_A(x, y) || d->is_treasure_class_B(x, y) || d->is_treasure_class_C(x, y)
        || d->is_monst_any(x, y)) {
      continue;
    }

    //
    // No portals next to the entrance which obscures the player.
    //
    bool skip              = false;
    int  entrance_distance = MAP_BORDER_ROCK - 1;
    for (auto dx = -entrance_distance; dx <= entrance_distance; dx++) {
      for (auto dy = -entrance_distance; dy <= entrance_distance; dy++) {
        if (d->is_ascend_dungeon(x + dx, y + dy)) {
          skip = true;
          break;
        }
        if (d->is_descend_dungeon(x + dx, y + dy)) {
          skip = true;
          break;
        }
      }
      if (skip) {
        break;
      }
    }

    if (skip) {
      continue;
    }

    auto tp = tp_random_portal();

    thing_new(tp->name(), point(x, y));

    if (++portal_count > 1) {
      return;
    }
  }
}

void Level::place_dirt(Dungeonp d)
{
  TRACE_AND_INDENT();
  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {
      if (! d->is_anything_at(x, y) || d->is_dirt(x, y)) {
        auto tp = tp_random_dirt();
        if (unlikely(! tp)) {
          return;
        }

        (void) thing_new(tp->name(), point(x, y));
      }
    }
  }
}

void Level::place_random_treasure(Dungeonp d)
{
  TRACE_AND_INDENT();
  int tries        = 1000;
  int treasure_max = pcg_random_range(1, 10);

  while (tries-- > 0) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK + 1);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK + 1);

    if (d->is_door(x, y) || d->is_rock(x, y) || d->is_wall(x, y) || d->is_chasm(x, y) || d->is_lava(x, y)) {
      continue;
    }

    if (d->is_dirt(x, y) || d->is_weapon_class_A(x, y) || d->is_weapon_class_B(x, y) || d->is_weapon_class_C(x, y)
        || d->is_treasure_class_A(x, y) || d->is_treasure_class_B(x, y) || d->is_treasure_class_C(x, y)) {

      auto tp = tp_random_treasure();
      if (unlikely(! tp)) {
        return;
      }

      if (tp->is_torch()) {
        if (d->is_deep_water(x, y) || d->is_foliage(x, y)) {
          continue;
        }
      }

      //
      // Be nice and enchant this lost treasure.
      //
      auto t = thing_new(tp->name(), point(x, y));
      if (! t) {
        continue;
      }

      if (pcg_random_range(0, 100) < 20) {
        t->enchant_randomly();
      }

      if (t->is_sword()) {
        //
        // Double enchant swords in lakes :)
        //
        if (d->is_shallow_water(x, y)) {
          t->enchant_randomly();
        }

        if (d->is_deep_water(x, y)) {
          t->enchant_randomly();
        }
      } else {
        //
        // Further enchant deep water items?
        //
        if (pcg_random_range(0, 100) < 20) {
          if (d->is_deep_water(x, y)) {
            t->enchant_randomly();
          }
        }
      }

      dbg("INF: Placed random item '%s'", t->text_short_capitalised().c_str());

      if (treasure_max-- < 0) {
        return;
      }
    }
  }
}

bool Level::place_random_named(Dungeonp d, const std::string &what)
{
  TRACE_AND_INDENT();
  int tries = 1000;

  auto tp = tp_find(what);
  if (unlikely(! tp)) {
    return false;
  }

  while (tries-- > 0) {
    auto x = pcg_random_range(MAP_BORDER_ROCK, MAP_WIDTH - MAP_BORDER_ROCK + 1);
    auto y = pcg_random_range(MAP_BORDER_ROCK, MAP_HEIGHT - MAP_BORDER_ROCK + 1);

    if (d->is_door(x, y) || d->is_rock(x, y) || d->is_wall(x, y) || d->is_chasm(x, y) || d->is_lava(x, y)) {
      continue;
    }

    if (d->is_dirt(x, y) || d->is_weapon_class_A(x, y) || d->is_weapon_class_B(x, y) || d->is_weapon_class_C(x, y)
        || d->is_treasure_class_A(x, y) || d->is_treasure_class_B(x, y) || d->is_treasure_class_C(x, y)) {

      if (tp->is_torch()) {
        if (d->is_deep_water(x, y) || d->is_foliage(x, y)) {
          continue;
        }
      }

      //
      // Be nice and enchant this lost treasure.
      //
      auto t = thing_new(tp->name(), point(x, y));
      if (! t) {
        continue;
      }

      if (pcg_random_range(0, 100) < 20) {
        t->enchant_randomly();
      }

      if (t->is_sword()) {
        //
        // Double enchant swords in lakes :)
        //
        if (d->is_shallow_water(x, y)) {
          t->enchant_randomly();
        }

        if (d->is_deep_water(x, y)) {
          t->enchant_randomly();
        }
      } else {
        //
        // Further enchant deep water items?
        //
        if (pcg_random_range(0, 100) < 20) {
          if (d->is_deep_water(x, y)) {
            t->enchant_randomly();
          }
        }
      }

      dbg("INF: Placed random item '%s'", t->text_short_capitalised().c_str());

      return true;
    }
  }

  return false;
}
