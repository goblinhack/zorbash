//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::on_stuck(void)
{
  TRACE_NO_INDENT();

  auto on_stuck = tp()->on_stuck_do();
  if (std::empty(on_stuck)) {
    return;
  }

  auto t = split_tokens(on_stuck, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %d, %d)", mod.c_str(), fn.c_str(), to_short_string().c_str(), (int) curr_at.x,
        (int) curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_stuck call [%s] expected mod:function, got %d elems", on_stuck.c_str(), (int) on_stuck.size());
  }
}

void Thing::stuck(const std::string &why)
{
  dbg("Stuck: %s", why.c_str());
  TRACE_AND_INDENT();

  stuck_count_incr();

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_stuck_do().empty()) {
        iter->stuck(why);
      }
    }
  }
}

void Thing::unstuck(void)
{
  dbg("Unstuck");
  TRACE_AND_INDENT();

  stuck_count_set(0);

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (! iter->on_stuck_do().empty()) {
        iter->unstuck();
      }
    }
  }
}

//
// Are we stuck at the current location?
//
bool Thing::is_stuck_check(void)
{
  TRACE_NO_INDENT();

  bool stuck = false;

  //
  // Makes sure ghosts (or the cursor!) do not get stuck in webs.
  //
  if (is_ethereal()) {
    return false;
  }

  //
  // If things are dead should they remain stuck ? It can cause resurrecting things to be stuck,
  // so I say no.
  //
  if (is_dead_or_dying()) {
    return false;
  }

  //
  // Don't block resurrection as the anim will never end.
  //
  if (is_resurrecting) {
    return false;
  }

  //
  // Paralysed
  //
  if (paralysis_count() > 0) {
    dbg("Stuck, yes: paralysed");
    return true;
  }

  if (! is_monst() && ! is_player()) {
    return false;
  }

  //
  // Slowed so much it cannot move?
  //
  if (tp()->move_speed()) {
    if (move_speed_curr() == 0) {
      dbg("Stuck, yes: no move speed");
      return true;
    }

    //
    // So slow that your body stops functioning?
    //
    if (move_speed_curr() < 0) {
      if (is_player()) {
        //
        // Body shutdown due to being too slow
        //
        msg("You became so slow, you're body just stopped...");
        dead("by extreme slowing");
        dbg("Stuck, yes: too slow");
        return true;
      } else if (is_magical() || is_undead() || is_ethereal()) {
        //
        // The undead really don't care if their body stops working.
        //
        return true;
      } else if (is_flying()) {
        //
        // Body shutdown due to being too slow
        //
        dead("bu falling to the ground dead");
        dbg("Stuck, yes: falling down dead");
        return true;
      } else if (is_humanoid()) {
        //
        // Body shutdown due to being too slow
        //
        dbg("Stuck, yes: extreme slowing");
        dead("by extreme slowing");
        return true;
      } else {
        //
        // Stuck
        //
        dbg("Stuck, yes: too slow");
        return true;
      }
    }
  }

  if (is_frozen) {
    dbg("Stuck, yes: frozen");
    return true;
  }

  if (level->is_spiderweb(curr_at.x, curr_at.y)) {
    if (is_immune_to_spiderwebs()) {
      //
      // ok
      //
    } else if (is_able_to_walk_through_walls()) {
      //
      // ok
      //
    } else if (is_ethereal()) {
      //
      // ok
      //
    } else if (buff_slippery() && (d20() < stat_str())) {
      //
      // Give a better chance to escape if slippery.
      //
    } else if (10 + d20() < stat_str()) {
      //
      // Give a chance to escape.
      //
    } else {
      dbg("Stuck, yes: caught in a web");
      stuck = true;
    }
  } else if (level->is_spell_of_holding_barrier(curr_at.x, curr_at.y)) {
    if (is_immune_to_spell_of_holding()) {
      //
      // ok
      //
    } else {
      dbg("Stuck, yes: caught in a spell of holding");
      stuck = true;
    }
  } else if (level->is_block_of_ice(curr_at.x, curr_at.y)) {
    if (is_able_to_walk_through_walls()) {
      //
      // ok
      //
    } else if (is_ethereal()) {
      //
      // ok
      //
    } else {
      dbg("Stuck, yes: caught in a ice");
      stuck = true;
    }
  } else if (level->is_sticky(curr_at.x, curr_at.y)) {
    if (is_sticky()) {
      //
      // ok
      //
    } else if (is_able_to_walk_through_walls()) {
      //
      // ok
      //
    } else if (is_ethereal()) {
      //
      // ok
      //
    } else if (buff_slippery()) {
      //
      // ok
      //
    } else {
      dbg("Stuck, yes: caught in sticky stuff");
      stuck = true;
    }
  } else if (level->is_tentacle(curr_at.x, curr_at.y)) {
    if (is_tentacle()) {
      //
      // ok
      //
    } else if (is_able_to_walk_through_walls()) {
      //
      // ok
      //
    } else if (is_ethereal()) {
      //
      // ok
      //
    } else if (buff_slippery()) {
      //
      // ok
      //
    } else {
      dbg("Stuck, yes: caught in a tentacle");
      stuck = true;
    }
  }

  if (level->is_rock(curr_at.x, curr_at.y) || level->is_wall(curr_at.x, curr_at.y)
      || level->is_barrel(curr_at.x, curr_at.y)) {
    if (is_flying()) {
      //
      // ok
      //
    } else if (is_able_to_walk_through_walls()) {
      //
      // ok
      //
    } else if (is_ethereal()) {
      //
      // ok
      //
    } else if (15 + d20() < stat_str()) {
      //
      // Give a chance to escape.
      //
    } else {
      dbg("Stuck, yes: caught in a rock, wall or barrel");
      stuck = true;
    }
  }

  //
  // Stuck under an alive heavy monster?
  //
  if (level->is_monst(curr_at.x, curr_at.y)) {
    if (level->is_heavy(curr_at.x, curr_at.y)) {
      if (is_flying()) {
        //
        // ok
        //
      } else if (is_able_to_walk_through_walls()) {
        //
        // ok
        //
      } else if (is_ethereal()) {
        //
        // ok
        //
      } else if (is_heavy()) {
        //
        // ok
        //
      } else {
        dbg("Stuck, yes: caught under a heavy monster");
        stuck = true;
      }
    }
  }

  //
  // Blocked from moving by something stronger?
  //
  TRACE_NO_INDENT();
  FOR_ALL_NON_INTERNAL_THINGS(level, it, curr_at.x, curr_at.y)
  {
    if (it == this) {
      continue;
    }

    if (! it->is_alive_monst()) {
      continue;
    }

    //
    // Don't get stuck under your fellow minion or mob spawner
    //
    if (is_friend(it) || same_mob(it)) {
      continue;
    }

    if (it->is_engulfer() || it->is_heavy()) {
      if (is_engulfer()) {
        //
        // Fellow engulfer
        //
      } else if (is_heavy()) {
        //
        // Fellow heavy thing
        //
      } else if (! d20_ge(stat_str_total(), it->stat_str_total())) {
        dbg("Stuck, yes: caught in an engulfer");
        stuck = true;
      }
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()

  return stuck;
}

void Thing::is_stuck_update(void)
{
  //
  // Don't do silly things like have stuck skills.
  //
  auto owner = top_owner();
  if (owner) {
    return;
  }

  //
  // Plants, grass etc...
  //
  if (! is_moveable()) {
    return;
  }

  dbg2("Stuck check");
  TRACE_AND_INDENT();

  //
  // Check if we are still stuck
  //

  if (stuck_count()) {
    if (! is_stuck_check()) {
      if (is_player()) {
        msg("You are no longer stuck!");
        debuff_remove(tp_find("debuff_status_stuck"));
        game->set_request_to_remake_rightbar();
      } else if (is_monst()) {
        msg("%s is no longer stuck.", text_The().c_str());
      }
      unstuck();
      return;
    }

    //
    // Yes.
    //
    stuck("still stuck");
  } else {
    //
    // Are we newly stuck?
    //
    if (! is_stuck_check()) {
      return;
    }

    //
    // Yes.
    //
    stuck("newly stuck at location");

    if (is_player()) {
      debuff_add_if_not_found(tp_find("debuff_status_stuck"));
      game->set_request_to_remake_rightbar();

      if (level->is_spiderweb(curr_at.x, curr_at.y)) {
        msg("You are trapped in a web!");
      } else if (level->is_spell_of_holding_barrier(curr_at.x, curr_at.y) && ! is_immune_to_spell_of_holding()) {
        msg("You are trapped in a magical hold!");
      } else if (level->is_block_of_ice(curr_at.x, curr_at.y)) {
        msg("You are trapped in ice!");
      } else if (level->is_barrel(curr_at.x, curr_at.y)) {
        msg("You are trapped inside a barrel!");
      } else if (is_frozen) {
        msg("You are frozen to the bone and cannot move!");
      } else {
        msg("You are stuck!");
      }
    } else if (is_monst()) {
      if (level->is_spiderweb(curr_at.x, curr_at.y)) {
        msg("%s is trapped in a web!", text_The().c_str());
      } else if (level->is_spell_of_holding_barrier(curr_at.x, curr_at.y) && ! is_immune_to_spell_of_holding()) {
        msg("%s is trapped in a magical hold!", text_The().c_str());
      } else if (level->is_block_of_ice(curr_at.x, curr_at.y)) {
        msg("%s is trapped in ice!", text_The().c_str());
      } else if (level->is_barrel(curr_at.x, curr_at.y)) {
        msg("%s is trapped inside a barrel!", text_The().c_str());
      } else if (is_frozen) {
        msg("%s is frozen stiff!", text_The().c_str());
      } else {
        msg("%s is stuck!", text_The().c_str());
      }
    }

    if (is_frozen) {
      popup(string_sprintf("%%fg=lightblue$Frozen!%%fg=reset$"));
    } else {
      popup(string_sprintf("Stuck!"));
    }
  }

  //
  // Shake the web or block of ice or barrel...
  //
  wobble(pcg_random_range(5, 20));
  TRACE_NO_INDENT();
  FOR_ALL_NON_INTERNAL_THINGS(level, t, curr_at.x, curr_at.y)
  {
    if (t->is_spiderweb()) {
      t->wobble(5);
    }
    if (t->is_spell_of_holding_barrier()) {
      t->wobble(5);
    }
    if (t->is_block_of_ice()) {
      t->wobble(5);
    }
    if (t->is_barrel()) {
      t->wobble(5);
    }
  }
  TRACE_NO_INDENT();
  FOR_ALL_THINGS_END()
}

bool Thing::is_stuck_currently(void) { return stuck_count() > 0; }

int Thing::stuck_count(void)
{
  TRACE_NO_INDENT();

  if (! is_monst() && ! is_player()) {
    return 0;
  }

  if (maybe_aip()) {
    return (aip()->stuck_count);
  }
  return 0;
}

int Thing::stuck_count_set(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count = v);
}

int Thing::stuck_count_decr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count -= v);
}

int Thing::stuck_count_incr(int v)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count += v);
}

int Thing::stuck_count_decr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count--);
}

int Thing::stuck_count_incr(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (aip()->stuck_count++);
}
