//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_dungeon.hpp"
#include "my_game.hpp"

static Tpidmap tp_monst[ BIOME_MAX ][ MONST_ENVIRON_MAX ][ MONST_CLASS_MAX ];

Tpp Level::get_random_monst(point p, monst_environ_t monst_environ, monst_class_t monst_class, int difficulty_offset)
{
  TRACE_NO_INDENT();

  auto roll = d1000();

  //
  // Should be set to -1 if this is intentional
  //
  if (! d1000_chance_of_creating_monst[ monst_environ ][ monst_class ]) {
    DIE("No chance of creating monster for biome %d type %d class %d", biome, monst_environ, monst_class);
  }

  //
  // Roll the dice and see if we get to place a monster.
  //
  dbg("roll %d -- biome %d type %d class %d -- %d", roll, biome, monst_environ, monst_class,
      d1000_chance_of_creating_monst[ monst_environ ][ monst_class ] + difficulty_offset);

  if (roll < d1000_chance_of_creating_monst[ monst_environ ][ monst_class ] + difficulty_offset) {
    auto tries = 0U;
    for (;;) {
      //
      // Try the next lower class
      //
      if (tries++ > 100) {
        //
        // If we've tried too many times, try the next lower class
        //
        if (monst_class == MONST_CLASS_A) {
          return get_random_monst(p, monst_environ, monst_class);
        }

        tries = 0;
        dbg("INF: Try the next lowest class for -- biome %d type %d class %d -- %d", biome, monst_environ,
            monst_class, d1000_chance_of_creating_monst[ monst_environ ][ monst_class ] + difficulty_offset);
        return get_random_monst(p, monst_environ, (monst_class_t) (((int) monst_class) - 1), difficulty_offset);
      }

      //
      // Filter according to monster rarity
      //
      auto tp = tp_get_with_rarity_filter(tp_monst[ biome ][ monst_environ ][ monst_class ]);
      if (! tp) {
        continue;
      }

      //
      // Filter locations that are not appropriate
      //
      if (tp->is_disliked_by_me(this, p)) {
        dbg("INF: skip '%s' at %s", tp->text_short_capitalised().c_str(), p.to_string().c_str());
        continue;
      }

      dbg("INF: Monster '%s' at %s", tp->text_short_capitalised().c_str(), p.to_string().c_str());
      return tp;
    }
  } else {
    if (monst_class == MONST_CLASS_A) {
      return get_random_monst(p, monst_environ, monst_class);
    }
    return get_random_monst(p, monst_environ, (monst_class_t) (((int) monst_class) - 1), difficulty_offset);
  }
}

Tpp Level::get_random_monst(point p, monst_environ_t monst_environ, int difficulty_offset)
{
  for (int monst_class = MONST_CLASS_A; monst_class < MONST_CLASS_MAX; monst_class++) {
    auto roll = d1000();
    if (roll < d1000_chance_of_creating_monst[ monst_environ ][ monst_class ]) {
      return get_random_monst(p, monst_environ, (monst_class_t) monst_class, difficulty_offset);
    }
  }
  return nullptr;
}

Tpp Level::get_biome_dungeon_random_monst(Dungeonp d, point p, monst_environ_t monst_environ)
{
  monst_class_t monst_class       = MONST_CLASS_ANY;
  int           difficulty_offset = 0;

  if (d->is_monst_class_A(p.x, p.y)) {
    difficulty_offset = 1;
    monst_class       = MONST_CLASS_A;
  } else if (d->is_monst_class_B(p.x, p.y)) {
    difficulty_offset = 50;
    monst_class       = MONST_CLASS_B;
  } else if (d->is_monst_class_C(p.x, p.y)) {
    difficulty_offset = 100;
    monst_class       = MONST_CLASS_C;
  } else if (d->is_monst_class_D(p.x, p.y)) {
    difficulty_offset = 200;
    monst_class       = MONST_CLASS_D;
  } else if (d->is_monst_class_E(p.x, p.y)) {
    difficulty_offset = 500;
    monst_class       = MONST_CLASS_E;
  } else {
    return nullptr;
  }

  return get_random_monst(p, monst_environ, monst_class, difficulty_offset);
}

Tpp Level::get_biome_swamp_random_monst(Dungeonp d, point p, monst_environ_t monst_environ)
{
  monst_class_t monst_class = MONST_CLASS_ANY;

  if (d->is_monst_class_A(p.x, p.y)) {
    monst_class = MONST_CLASS_A;
  } else if (d->is_monst_class_B(p.x, p.y)) {
    monst_class = MONST_CLASS_B;
  } else if (d->is_monst_class_C(p.x, p.y)) {
    monst_class = MONST_CLASS_C;
  } else if (d->is_monst_class_D(p.x, p.y)) {
    monst_class = MONST_CLASS_D;
  } else if (d->is_monst_class_E(p.x, p.y)) {
    monst_class = MONST_CLASS_E;
  } else {
    return nullptr;
  }

  return get_random_monst(p, monst_environ, monst_class);
}

Tpp Level::get_biome_sewer_random_monst(point p, monst_environ_t monst_environ)
{
  monst_class_t monst_class = MONST_CLASS_ANY;
  return get_random_monst(p, monst_environ, monst_class);
}

void tp_monst_add(Tpp tp)
{
  // CON("INF: Add monster '%s'", tp->text_short_capitalised().c_str());

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

  if (tp->is_swimmer()) {
    if (! tp->environ_likes_shallow_water() && ! tp->environ_likes_deep_water()) {
      CON("INF: Swimming monster '%s' needs to set shallow and or deep water preferences",
          tp->text_short_capitalised().c_str());
    }
  }

  if (tp->environ_likes_shallow_water()) {
    monst_types.push_back(MONST_ENVIRON_SHALLOW_WATER);
  }

  if (tp->environ_likes_deep_water()) {
    monst_types.push_back(MONST_ENVIRON_DEEP_WATER);
  }

  if (! tp->environ_likes_shallow_water() && ! tp->environ_likes_deep_water()) {
    monst_types.push_back(MONST_ENVIRON_NORMAL);
  }

  for (auto biome : biomes) {
    for (auto monst_environ : monst_types) {
      if (tp->is_monst()) {
        tp_monst[ biome ][ monst_environ ][ MONST_CLASS_ANY ].push_back(tp);
      }
      if (tp->is_monst_class_A()) {
        tp_monst[ biome ][ monst_environ ][ MONST_CLASS_A ].push_back(tp);
      }
      if (tp->is_monst_class_B()) {
        tp_monst[ biome ][ monst_environ ][ MONST_CLASS_B ].push_back(tp);
      }
      if (tp->is_monst_class_C()) {
        tp_monst[ biome ][ monst_environ ][ MONST_CLASS_C ].push_back(tp);
      }
      if (tp->is_monst_class_D()) {
        tp_monst[ biome ][ monst_environ ][ MONST_CLASS_D ].push_back(tp);
      }
      if (tp->is_monst_class_E()) {
        tp_monst[ biome ][ monst_environ ][ MONST_CLASS_E ].push_back(tp);
      }
    }
  }
}
