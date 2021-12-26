//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Level::create(point3d at, int seed)
{
  TRACE_AND_INDENT();
  pcg_srand(game->seed + at.z);

  is_starting = true;
  clear();

  is_level_type_dungeon = false;
  is_level_type_sewer   = false;

  this->seed = seed;
  world_at   = at;

  log("-");
  log("Creating, seed %u", seed);
  log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  log("v v v v v v v v v v v v v v v v v v v v v v v v v v v");

  //
  // Must set the level pointer so for e.g. spiders can spawn webs when born
  //
  game->level_being_created = this;

  bool ret;
  if (at.z & 1) {
    ret = create_dungeon(at, seed);
  } else {
    ret = create_sewer(at, seed);
  }

  game->level_being_created = nullptr;

  log("^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^");
  log("| | | | | | | | | | | | | | | | | | | | | | | | | | |");
  log("Created, seed %u", seed);
  log("-");

  if (! ret) {
    err("Failed to create level");
  }

  update_map();

  game->started = true;
  is_starting   = false;

  ts_fade_in_begin = time_get_time_ms_cached();

  things_gc_force();

  if (! cursor && player) {
    cursor = thing_new("cursor", player->curr_at);
    cursor->hide();
  }

  created();
}

void Level::created(void)
{
  TRACE_AND_INDENT();

  std::list< Thingp > cands;

  //
  // Fist get all candidate followers
  //
  FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL(this, t)
  {
    if (t->is_able_to_follow()) {
      cands.push_back(t);
    }
  }
  FOR_ALL_THINGS_THAT_DO_STUFF_ON_LEVEL_END(this)

  if (! cands.size()) {
    return;
  }

  std::map< Thingp, std::list< Thingp > > groups;

  //
  // Assign members to groups
  //
  for (auto t : cands) {
    Thingp group_cand = nullptr;
    con("Cand %s", t->to_short_string().c_str());
    for (const auto &g : groups) {
      for (const auto &m : g.second) {
        //
        // Filter to allies only
        //
        if (t->tp()->allies.find(m->tp()) == t->tp()->allies.end()) {
          continue;
        }
        //
        // That are close enough
        //
        if (distance(t->curr_at, m->curr_at) <= m->get_distance_recruitment_max()) {
          group_cand = g.first;
        }
      }
    }
    if (group_cand) {
      groups[ group_cand ].push_back(t);
    } else {
      groups[ t ].push_back(t);
    }
  }

  //
  // Ok now we have everyone in their groups
  //
  if (0) {
    for (const auto &g : groups) {
      con("Group %p", g.first);
      for (const auto &m : g.second) {
        con("- Member %s", m->to_short_string().c_str());
      }
    }
  }

  //
  // Now choose the leader
  //
  for (const auto &g : groups) {
    con("Group %p", g.first);

    Thingp leader = nullptr;
    for (const auto &m : g.second) {
      if (! leader) {
        leader = m;
      } else {
        if (m->get_danger_current_level() > leader->get_danger_current_level()) {
          leader = m;
        }
      }
    }

    //
    // Now choose the leader
    //
    for (const auto &m : g.second) {
      if (m == leader) {
        con("- Leader %s", m->to_short_string().c_str());
      } else {
        con("- Member %s", m->to_short_string().c_str());
      }
    }

    for (const auto &m : g.second) {
      m->set_leader(leader);
    }
  }
}

void Level::place_the_grid(void)
{
  TRACE_AND_INDENT();
  for (auto x = 0; x < MAP_WIDTH; x++) {
    for (auto y = 0; y < MAP_HEIGHT; y++) {
      (void) thing_new("the_grid", point(x, y));
      if (g_errored) {
        ERR("Could not create level");
        return;
      }
    }
  }
}
