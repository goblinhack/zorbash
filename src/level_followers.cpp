//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing.hpp"

void Level::assign_leaders_and_followers(void)
{
  dbg("Assign leaders and followers");
  TRACE_AND_INDENT();

  std::list< Thingp > cands;

  //
  // Fist get all candidate followers
  //
  TRACE_NO_INDENT();
  FOR_ALL_TICKABLE_THINGS_ON_LEVEL(this, t)
  {
    if (t->is_able_to_follow()) {
      cands.push_back(t);
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_TICKABLE_THINGS_ON_LEVEL_END(this)

  if (! cands.size()) {
    dbg("Assign leaders and followers: none found");
    return;
  }

  std::map< Thingp, std::list< Thingp > > groups;

  //
  // Assign members to groups
  //
  dbg("Choose followers");
  for (auto t : cands) {
    Thingp group_cand = nullptr;
    for (const auto &g : groups) {
      for (const auto &m : g.second) {
        //
        // Filter to allies only
        //
        if (t->tp()->allies.find(m->tp()) != t->tp()->allies.end()) {
          //
          // ok
          //
        } else if (t->is_friend(m)) {
          //
          // ok
          //
        } else {
          continue;
        }

        //
        // That are close enough
        //
        if (distance(t->curr_at, m->curr_at) <= m->distance_recruitment_max_float()) {
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
  // Now choose the leader
  //
  dbg("Choose the leaders");
  for (const auto &g : groups) {
    Thingp leader = nullptr;
    for (const auto &m : g.second) {
      if (! leader) {
        leader = m;
      } else {
        if (m->danger_current_level() > leader->danger_current_level()) {
          leader = m;
        }
      }
    }

    for (const auto &m : g.second) {
      if (m) {
        if (m == leader) {
          dbg("- Leader %s", m->to_short_string().c_str());
        } else {
          dbg("- Member %s", m->to_short_string().c_str());
        }
      }
    }

    for (const auto &m : g.second) {
      if (m) {
        m->leader_set(leader);
      }
    }
  }
}
