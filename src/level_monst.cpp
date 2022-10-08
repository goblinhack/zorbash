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

Tpp Level::get_random_monst(point p, biome_t biome, monst_type_t monst_type, monst_class_t monst_class)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 1000) {
      //
      // If we've tried too many times, try the next lower class
      //
      if ((int) biome == 0) {
        return nullptr;
      }

      //
      // Try the next lower class
      //
      return get_random_monst(p, biome, monst_type, (monst_class_t) (((int) monst_class) - 1));
    }

    auto tp = tp_get_with_rarity_filter(tp_monst[ biome ][ monst_type ][ monst_class ]);
    if (! tp) {
      continue;
    }

    if (tp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Got random monster '%s'", tp->text_short_capitalised().c_str());
    return tp;
  }
}

Tpp Level::get_dungeon_biome_random_monst(Dungeonp d, point p, biome_t biome, monst_type_t monst_type)
{
  monst_class_t monst_class = MONST_CLASS_ANY;

  int difficulty_offset = 0;

  if (d->is_monst_class_a(p.x, p.y)) {
    difficulty_offset = 1;
    monst_class       = MONST_CLASS_A;
  }
  if (d->is_monst_class_b(p.x, p.y)) {
    difficulty_offset = 50;
    monst_class       = MONST_CLASS_B;
  }
  if (d->is_monst_class_c(p.x, p.y)) {
    difficulty_offset = 100;
    monst_class       = MONST_CLASS_C;
  }
  if (d->is_monst_class_d(p.x, p.y)) {
    difficulty_offset = 200;
    monst_class       = MONST_CLASS_D;
  }
  if (d->is_monst_class_e(p.x, p.y)) {
    difficulty_offset = 500;
    monst_class       = MONST_CLASS_E;
  }

  Tpp tp = nullptr;

  if (d1000() < d1000_chance_of_creating_monst[ monst_type ][ monst_class ] + difficulty_offset) {
    tp = get_random_monst(p, biome, monst_type, monst_class);
    if (tp) {
      con("INF: Got level monster '%s' biome %d class %d", tp->text_short_capitalised().c_str(), biome, monst_class);
    }
  }

  return tp;
}

void tp_monst_add(Tpp tp)
{
  if (tp->is_swimmer()) {
    if (tp->is_biome_dungeon()) {
      if (tp->is_monst()) {
        tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_ANY ].push_back(tp);
      }
      if (tp->is_monst_class_a()) {
        tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_A ].push_back(tp);
      }
      if (tp->is_monst_class_b()) {
        tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_B ].push_back(tp);
      }
      if (tp->is_monst_class_c()) {
        tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_C ].push_back(tp);
      }
      if (tp->is_monst_class_d()) {
        tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_D ].push_back(tp);
      }
      if (tp->is_monst_class_e()) {
        tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_E ].push_back(tp);
      }
    }

    if (tp->is_biome_swamp()) {
      if (tp->is_monst()) {
        tp_monst[ BIOME_SWAMP ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_ANY ].push_back(tp);
      }
      if (tp->is_monst_class_a()) {
        tp_monst[ BIOME_SWAMP ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_A ].push_back(tp);
      }
      if (tp->is_monst_class_b()) {
        tp_monst[ BIOME_SWAMP ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_B ].push_back(tp);
      }
      if (tp->is_monst_class_c()) {
        tp_monst[ BIOME_SWAMP ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_C ].push_back(tp);
      }
      if (tp->is_monst_class_d()) {
        tp_monst[ BIOME_SWAMP ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_D ].push_back(tp);
      }
      if (tp->is_monst_class_e()) {
        tp_monst[ BIOME_SWAMP ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_E ].push_back(tp);
      }
    }

    if (tp->is_biome_sewer()) {
      if (tp->is_monst()) {
        tp_monst[ BIOME_SEWER ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_ANY ].push_back(tp);
      }
      if (tp->is_monst_class_a()) {
        tp_monst[ BIOME_SEWER ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_A ].push_back(tp);
      }
      if (tp->is_monst_class_b()) {
        tp_monst[ BIOME_SEWER ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_B ].push_back(tp);
      }
      if (tp->is_monst_class_c()) {
        tp_monst[ BIOME_SEWER ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_C ].push_back(tp);
      }
      if (tp->is_monst_class_d()) {
        tp_monst[ BIOME_SEWER ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_D ].push_back(tp);
      }
      if (tp->is_monst_class_e()) {
        tp_monst[ BIOME_SEWER ][ MONST_TYPE_SWIMMER ][ MONST_CLASS_E ].push_back(tp);
      }
    }
  }

  if (tp->is_biome_dungeon()) {
    if (tp->is_monst()) {
      tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_NORMAL ][ MONST_CLASS_ANY ].push_back(tp);
    }
    if (tp->is_monst_class_a()) {
      tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_NORMAL ][ MONST_CLASS_A ].push_back(tp);
    }
    if (tp->is_monst_class_b()) {
      tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_NORMAL ][ MONST_CLASS_B ].push_back(tp);
    }
    if (tp->is_monst_class_c()) {
      tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_NORMAL ][ MONST_CLASS_C ].push_back(tp);
    }
    if (tp->is_monst_class_d()) {
      tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_NORMAL ][ MONST_CLASS_D ].push_back(tp);
    }
    if (tp->is_monst_class_e()) {
      tp_monst[ BIOME_DUNGEON ][ MONST_TYPE_NORMAL ][ MONST_CLASS_E ].push_back(tp);
    }
  }

  if (tp->is_biome_swamp()) {
    if (tp->is_monst()) {
      tp_monst[ BIOME_SWAMP ][ MONST_TYPE_NORMAL ][ MONST_CLASS_ANY ].push_back(tp);
    }
    if (tp->is_monst_class_a()) {
      tp_monst[ BIOME_SWAMP ][ MONST_TYPE_NORMAL ][ MONST_CLASS_A ].push_back(tp);
    }
    if (tp->is_monst_class_b()) {
      tp_monst[ BIOME_SWAMP ][ MONST_TYPE_NORMAL ][ MONST_CLASS_B ].push_back(tp);
    }
    if (tp->is_monst_class_c()) {
      tp_monst[ BIOME_SWAMP ][ MONST_TYPE_NORMAL ][ MONST_CLASS_C ].push_back(tp);
    }
    if (tp->is_monst_class_d()) {
      tp_monst[ BIOME_SWAMP ][ MONST_TYPE_NORMAL ][ MONST_CLASS_D ].push_back(tp);
    }
    if (tp->is_monst_class_e()) {
      tp_monst[ BIOME_SWAMP ][ MONST_TYPE_NORMAL ][ MONST_CLASS_E ].push_back(tp);
    }
  }

  if (tp->is_biome_sewer()) {
    if (tp->is_monst()) {
      tp_monst[ BIOME_SEWER ][ MONST_TYPE_NORMAL ][ MONST_CLASS_ANY ].push_back(tp);
    }
    if (tp->is_monst_class_a()) {
      tp_monst[ BIOME_SEWER ][ MONST_TYPE_NORMAL ][ MONST_CLASS_A ].push_back(tp);
    }
    if (tp->is_monst_class_b()) {
      tp_monst[ BIOME_SEWER ][ MONST_TYPE_NORMAL ][ MONST_CLASS_B ].push_back(tp);
    }
    if (tp->is_monst_class_c()) {
      tp_monst[ BIOME_SEWER ][ MONST_TYPE_NORMAL ][ MONST_CLASS_C ].push_back(tp);
    }
    if (tp->is_monst_class_d()) {
      tp_monst[ BIOME_SEWER ][ MONST_TYPE_NORMAL ][ MONST_CLASS_D ].push_back(tp);
    }
    if (tp->is_monst_class_e()) {
      tp_monst[ BIOME_SEWER ][ MONST_TYPE_NORMAL ][ MONST_CLASS_E ].push_back(tp);
    }
  }
}
