//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

void Thing::on_thrown(void)
{
  TRACE_NO_INDENT();

  auto on_thrown = tp()->on_thrown_do();
  if (std::empty(on_thrown)) {
    return;
  }

  auto t = split_tokens(on_thrown, '.');
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

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_thrown call [%s] expected mod:function, got %d elems", on_thrown.c_str(), (int) on_thrown.size());
  }
}

bool Thing::throw_item_choose_target(Thingp what)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot throw null thing");
    return false;
  }

  TRACE_NO_INDENT();
  dbg("Trying to throw: %s", what->to_short_string().c_str());

  if (! what->is_throwable()) {
    if (is_player()) {
      msg("I don't know how to throw %s.", what->text_the().c_str());
      game->tick_begin("player tried to throw something they could not");
    }
    return false;
  }

  if (! is_target_select(what)) {
    return false;
  }

  game->request_to_throw_item  = what;
  game->request_destination_ok = false;

  return is_target_select(what);
}

void Thing::on_thrown_callback(void)
{
  on_thrown();
  visible();
}

void Thing::throw_at(Thingp what, Thingp target)
{
  TRACE_NO_INDENT();
  if (! what) {
    what = game->request_to_throw_item;
  }

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot throw null thing");
    return;
  }

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot throw at null target");
    return;
  }

  //
  // We don't always get to throw as far as we want.
  //
  bool need_to_choose_a_new_target = false;

  //
  // Check for obstacles in the way of the throwing.
  //
  auto throw_at             = target->curr_at;
  auto throw_was_stopped_at = in_the_way_for_throwing(curr_at, throw_at);
  if (throw_at != throw_was_stopped_at) {
    if (is_player()) {
      msg("You fail to throw %s that far, something was in the way.", what->text_the().c_str());
    }
    throw_at = throw_was_stopped_at;

    dbg("Throw %s at new point %s", what->to_short_string().c_str(), throw_at.to_string().c_str());
    need_to_choose_a_new_target = true;
  }

  //
  // If you can't throw that far, throw as far as you can.
  //
  float dist     = DISTANCE(curr_at.x, curr_at.y, throw_at.x, throw_at.y);
  float max_dist = distance_throw_get();
  if (dist > max_dist) {
    if (! need_to_choose_a_new_target) {
      if (is_player()) {
        msg("You fail to throw %s that far.", what->text_the().c_str());
      }
    }

    float dx = (float) throw_at.x - (float) curr_at.x;
    float dy = (float) throw_at.y - (float) curr_at.y;
    dx /= dist;
    dy /= dist;
    dx *= max_dist - 1;
    dy *= max_dist - 1;
    throw_at = curr_at + point(dx, dy);

    float dist = distance(curr_at, throw_at);
    dbg("Throw %s at new point %s, dist %f, max %f", what->to_short_string().c_str(), throw_at.to_string().c_str(),
        dist, max_dist);
    need_to_choose_a_new_target = true;
  }

  if (need_to_choose_a_new_target) {
    FOR_ALL_GRID_THINGS(level, t, throw_at.x, throw_at.y)
    {
      target = t;
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      msg("You throw %s.", what->text_the().c_str());
    }
  }

  dbg("Thrown %s", what->to_short_string().c_str());
  what->move_to_immediately(throw_at);

  //
  // Important to call this prior to drop, as drop() will spawn a particle. We want to spawn our own particle here,
  // which reacts when it hits the destination.
  //
  {
    auto callback = std::bind(&Thing::on_thrown_callback, what);

    auto src   = (last_blit_tl + last_blit_br) / (short) 2;
    auto dst   = (target->last_blit_tl + target->last_blit_br) / (short) 2;
    auto sz    = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);
    auto delay = PARTICLE_SPEED_MS;

    //
    // Daggers, horseshoes...
    //
    if (what->is_thrown_as_a_weapon()) {
      //
      // But it's too fast in ascii mode
      //
      if (! g_opt_ascii) {
        delay /= 2;
      }
    }

    if (! is_being_destroyed) {
      if (is_player()) {
        //
        // So the player is visible above light
        //
        level->new_external_particle(what->id, src, dst, sz, delay, tile_index_to_tile(what->tile_curr), false,
                                     callback);
      } else {
        level->new_internal_particle(what->id, src, dst, sz, delay, tile_index_to_tile(what->tile_curr), false,
                                     callback);
      }
    }
  }

  //
  // Potions for example are used when thrown. Chocolate frogs, no.
  //
  // Must come after the particle code above.
  //
  what->location_check_me();
  if (what->is_used_when_thrown()) {
    used(what, target, true /* remove_after_use */);
  } else {
    drop(what, target, false /* stolen */, true /* thrown */);
  }

  //
  // As there is no animation, no need to hide.
  //
  if (! g_opt_ascii) {
    what->hide();
  }

  if (is_player()) {
    game->tick_begin("player threw an item");
  }

  if (game->state == Game::STATE_CHOOSING_TARGET) {
    game->change_state(Game::STATE_NORMAL, "finished choosing a target");
  }
}

////////////////////////////////////////////////////////////////////////////
// distance_throw
////////////////////////////////////////////////////////////////////////////
float Thing::distance_throw_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->distance_throw);
  }
  return 0;
}

int Thing::distance_throw_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw = v);
  return n;
}

int Thing::distance_throw_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw -= v);
  return n;
}

int Thing::distance_throw_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw += v);
  return n;
}

int Thing::distance_throw_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw--);
  return n;
}

int Thing::distance_throw_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_throw++);
  return n;
}
