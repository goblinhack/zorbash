//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"

static Tpidmap tp_monst[ BIOME_MAX ][ MONST_TYPE_MAX ][ MONST_CLASS_MAX ];

Tpp Level::get_random_monst(point p, biome_t biome, monst_type_t monst_type, monst_class_t monst_class,
                            int difficulty_offset)
{
  TRACE_NO_INDENT();

  auto roll = d1000();

  //
  // Should be set to -1 if this is intentional
  //
  if (! d1000_chance_of_creating_monst[ monst_type ][ monst_class ]) {
    DIE("No chance of creating monster for biome %d type %d class %d", biome, monst_type, monst_class);
  }

  //
  // Roll the dice and see if we get to place a monster.
  //
  if (0) {
    CON("roll %d -- biome %d type %d class %d -- %d", roll, biome, monst_type, monst_class,
        d1000_chance_of_creating_monst[ monst_type ][ monst_class ] + difficulty_offset);
  }

  if (roll < d1000_chance_of_creating_monst[ monst_type ][ monst_class ] + difficulty_offset) {
    auto tries = 0U;
    for (;;) {
      //
      // Try the next lower class
      //
      if (tries++ > 100) {
        //
        // If we've tried too many times, try the next lower class
        //
        if ((int) biome == 0) {
          return nullptr;
        }

        return get_random_monst(p, biome, monst_type, (monst_class_t) (((int) monst_class) - 1), difficulty_offset);
      }

      //
      // Filter according to monster rarity
      //
      auto tp = tp_get_with_rarity_filter(tp_monst[ biome ][ monst_type ][ monst_class ]);
      if (! tp) {
        continue;
      }

      //
      // Filter locations that are not appropriate
      //
      if (tp->is_disliked_by_me(this, p)) {
        continue;
      }

      con("INF: Got random monster '%s'", tp->text_short_capitalised().c_str());
      return tp;
    }
  }
  return nullptr;
}

Tpp Level::get_dungeon_biome_random_monst(Dungeonp d, point p, biome_t biome, monst_type_t monst_type)
{
  monst_class_t monst_class       = MONST_CLASS_ANY;
  int           difficulty_offset = 0;

  if (d->is_monst_class_a(p.x, p.y)) {
    difficulty_offset = 1;
    monst_class       = MONST_CLASS_A;
  } else if (d->is_monst_class_b(p.x, p.y)) {
    difficulty_offset = 50;
    monst_class       = MONST_CLASS_B;
  } else if (d->is_monst_class_c(p.x, p.y)) {
    difficulty_offset = 100;
    monst_class       = MONST_CLASS_C;
  } else if (d->is_monst_class_d(p.x, p.y)) {
    difficulty_offset = 200;
    monst_class       = MONST_CLASS_D;
  } else if (d->is_monst_class_e(p.x, p.y)) {
    difficulty_offset = 500;
    monst_class       = MONST_CLASS_E;
  } else {
    return nullptr;
  }

  return get_random_monst(p, biome, monst_type, monst_class, difficulty_offset);
}

Tpp Level::get_sewer_biome_random_monst(point p, biome_t biome, monst_type_t monst_type)
{
  for (int monst_class = MONST_CLASS_A; monst_class < MONST_CLASS_MAX; monst_class++) {
    auto roll = d1000();
    if (roll < d1000_chance_of_creating_monst[ monst_type ][ monst_class ]) {
      return get_random_monst(p, biome, monst_type, (monst_class_t) monst_class, 1000);
    }
  }
  return nullptr;
}

void tp_monst_add(Tpp tp)
{
  std::vector< int > biomes;
  std::vector< int > monst_types;

  if (tp->is_biome_dungeon()) {
    biomes.push_back(BIOME_DUNGEON);
  }
  if (tp->is_biome_sewer()) {
    biomes.push_back(BIOME_SEWER);
  }
  if (tp->is_biome_swamp()) {
    biomes.push_back(BIOME_SWAMP);
  }
  if (tp->is_shallow_water_swimmer()) {
    monst_types.push_back(MONST_TYPE_SHALLOW_WATER);
  } else if (tp->is_deep_water_swimmer()) {
    monst_types.push_back(MONST_TYPE_DEEP_WATER);
  } else {
    monst_types.push_back(MONST_TYPE_NORMAL);
  }

  for (auto biome : biomes) {
    for (auto monst_type : monst_types) {
      if (tp->is_monst()) {
        tp_monst[ biome ][ monst_type ][ MONST_CLASS_ANY ].push_back(tp);
      }
      if (tp->is_monst_class_a()) {
        tp_monst[ biome ][ monst_type ][ MONST_CLASS_A ].push_back(tp);
      }
      if (tp->is_monst_class_b()) {
        tp_monst[ biome ][ monst_type ][ MONST_CLASS_B ].push_back(tp);
      }
      if (tp->is_monst_class_c()) {
        tp_monst[ biome ][ monst_type ][ MONST_CLASS_C ].push_back(tp);
      }
      if (tp->is_monst_class_d()) {
        tp_monst[ biome ][ monst_type ][ MONST_CLASS_D ].push_back(tp);
      }
      if (tp->is_monst_class_e()) {
        tp_monst[ biome ][ monst_type ][ MONST_CLASS_E ].push_back(tp);
      }
    }
  }
}
