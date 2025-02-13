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

void Thing::on_thrown(ThingId owner_id_when_thrown)
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

    dbg("Call %s.%s(%s, %u, %u)", mod.c_str(), fn.c_str(), to_short_string().c_str(), curr_at.x, curr_at.y);

    py_call_void_fn(mod.c_str(), fn.c_str(), owner_id_when_thrown.id, id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_thrown call [%s] expected mod:function, got %d elems", on_thrown.c_str(), (int) on_thrown.size());
  }

  //
  // So thrown potions make a noise
  //
  level->sound_sources_incr(curr_at.x, curr_at.y, noise_on_dropping());
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

void Thing::on_thrown_callback(ThingId owner_id_when_thrown)
{
  dbg("Thrown callback");

  //
  // Bit of a hack, but it avoids attacking the monster you just tamed
  //
  if (! is_being_used_to_tame) {
    is_being_used_to_tame = false;
    on_thrown(owner_id_when_thrown);
  }

  visible("thrown");
  dbg("Thrown callback done");
}

bool Thing::throw_at(Thingp what, Thingp target)
{
  TRACE_NO_INDENT();
  if (! what) {
    what = game->request_to_throw_item;
  }

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot throw null thing");
    return false;
  }

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot throw at null target");
    return false;
  }

  //
  // We don't always get to throw as far as we want.
  //
  bool need_to_choose_a_new_target = false;

  //
  // Check for obstacles in the way of the throwing.
  //
  auto target_at            = target->curr_at;
  auto throw_was_stopped_at = in_the_way_for_throwing(curr_at, target_at);

  auto in_the_way = in_the_way_for_throwing(curr_at, target_at, 1);
  if (in_the_way.size()) {
    target = in_the_way[ 0 ];

    if (target && target->is_portal()) {
      //
      // Throwing into a portal?
      // Will teleport the item later after the particle move.
      //
      if (is_player()) {
        msg("You throw %s into a portal.", what->text_the().c_str());
      } else {
        msg("%s throws %s into a portal.", text_The().c_str(), what->text_the().c_str());
      }
    } else {
      //
      // Something was in the way.
      //
      if (is_player()) {
        msg("You fail to throw %s that far, something was in the way.", what->text_the().c_str());
      } else {
        dbg("Fail to throw %s that far, something was in the way", what->text_the().c_str());
      }

      need_to_choose_a_new_target = true;
    }

    if (target) {
      target_at = target->curr_at;
      dbg("Throw %s at new in-the-way thing at: %s", what->to_short_string().c_str(), target_at.to_string().c_str());
    }
  }

  //
  // If you can't throw that far, throw as far as you can.
  //
  float dist     = DISTANCE(curr_at.x, curr_at.y, target_at.x, target_at.y);
  float max_dist = distance_throw_get();
  if (! max_dist) {
    err("Cannot throw, no distance set");
    return false;
  }

  //
  // Allow darts to be thrown further
  //
  if (what) {
    if (what->is_missile()) {
      max_dist *= 2;
    }
    if (what->is_heavy()) {
      max_dist /= 2;
    }
    if (what->is_light()) {
      max_dist *= 2;
    }
    if (what->is_aerodynamic()) {
      max_dist *= 2;
    }
  }

  what->is_being_thrown = true;

  if (dist > max_dist) {
    if (! need_to_choose_a_new_target) {
      if (is_player()) {
        msg("You fail to throw %s that far.", what->text_the().c_str());
      }
    }

    float dx = (float) target_at.x - (float) curr_at.x;
    float dy = (float) target_at.y - (float) curr_at.y;
    dx /= dist;
    dy /= dist;
    dx *= max_dist - 1;
    dy *= max_dist - 1;
    target_at = curr_at + point(dx, dy);

    float dist = distance(curr_at, target_at);
    dbg("Throw %s at new point %s, dist %f, max dist %f", what->to_short_string().c_str(),
        target_at.to_string().c_str(), dist, max_dist);
    need_to_choose_a_new_target = true;
  }

  //
  // Adjust throwing distance for size.
  //
  switch (what->thing_size()) {
    case THING_SIZE_NOT_SET : break;
    case THING_SIZE_TINY : dist *= 3; break;
    case THING_SIZE_SMALL : dist *= 2; break;
    case THING_SIZE_NORMAL : break;
    case THING_SIZE_LARGE : dist /= 2; break;
    case THING_SIZE_GIANT : dist /= 3; break;
    case THING_SIZE_GARGANTUAN : dist /= 4; break;
  }

  if (need_to_choose_a_new_target) {
    TRACE_NO_INDENT();
    FOR_ALL_GRID_THINGS(level, t, target_at.x, target_at.y)
    {
      target = t;
      break;
    }
    FOR_ALL_THINGS_END()
  } else {
    if (is_player()) {
      //
      // No need for a message if it has a projectile as we will log "You shoot..." later.
      //
      if (what->gfx_targeted_projectile().empty()) {
        if (target->is_cursor()) {
          msg("You throw %s at the ground.", what->text_the().c_str());
        } else {
          msg("You throw %s at %s", what->text_the().c_str(), target->text_the().c_str());
        }
      }
    }
  }

  TRACE_AND_INDENT();
  dbg("Throw item %s at %s", what->to_short_string().c_str(), target->to_string().c_str());

  if (target && target->is_portal()) {
    //
    // The portal will move the item.
    //
    TRACE_AND_INDENT();
    dbg("Throw item %s at %s into portal", what->to_short_string().c_str(), target->to_string().c_str());
    what->move_to_immediately(target_at);
  } else {
    //
    // Move to the new location.
    //
    what->move_to_immediately(target_at);
  }

  //
  // Important to call this prior to drop, as drop() will spawn a particle. We want to spawn our own particle here,
  // which reacts when it hits the destination.
  //
  dbg("Throw particle");
  TRACE_AND_INDENT();

  {
    auto o        = what->top_owner();
    auto callback = std::bind(&Thing::on_thrown_callback, what, o ? o->id : NoThingId);

    auto src = (last_blit_tl + last_blit_br) / (short) 2;
    auto dst = (target->last_blit_tl + target->last_blit_br) / (short) 2;
    auto sz  = isize(last_blit_br.x - last_blit_tl.x, last_blit_br.y - last_blit_tl.y);

    //
    // Default thrown particle speed
    //
    auto delay = 0;

    if (g_opt_ascii) {
      delay = PARTICLE_SPEED_THROWN_ITEM_ASCII_MS;
    } else {
      delay = PARTICLE_SPEED_THROWN_ITEM_PIXELART_MS;
    }

    //
    // Daggers, horseshoes...
    //
    if (what->is_thrown_as_a_weapon()) {
      //
      // But it's too fast in ascii mode
      //
      if (g_opt_ascii) {
        delay = PARTICLE_SPEED_THROWN_WEAPON_ASCII_MS;
      } else {
        delay = PARTICLE_SPEED_THROWN_WEAPON_PIXELART_MS;
      }
    }

    if (! is_being_destroyed) {
      if (g_opt_ascii) {
        //
        // Ascii animations happen inside the level as projectiles
        //
        if (! what->gfx_targeted_projectile().empty()) {
          //
          // Fire the ascii projectile which should not really interact.
          //
          projectile_shoot_at(what, what->gfx_targeted_projectile(), target_at);

          //
          // Make sure the thrown item appears.
          //
          callback();
        } else {
          //
          // Make sure the thrown item appears.
          //
          callback();
        }
      } else if (what->is_thrown_as_a_weapon()) {
        //
        // Ascii animations happen inside the level as projectiles
        //
        if (! what->gfx_targeted_projectile().empty()) {
          //
          // Fire the ascii projectile which should not really interact.
          //
          projectile_shoot_at(what, what->gfx_targeted_projectile(), target_at);

          //
          // Make sure the thrown item appears.
          //
          callback();
        } else {
          //
          // Pixelart animations happen above the level as particles
          //
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
      } else {
        //
        // Pixelart animations happen above the level as particles
        //
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
  }

  if (what->is_dead_or_dying()) {
    //
    // Callback could still be running so make sure we drop it.
    //
    dbg("Post particle throw, item is dead");
    TRACE_AND_INDENT();
    if (what->top_owner()) {
      DropOptions drop_options;
      drop_options.is_being_thrown = true;
      drop(what, target, drop_options);
      dbg("Post used, dropped item is dead");
    }
  } else {
    dbg("Post particle throw, use or drop");
    TRACE_AND_INDENT();

    //
    // Potions for example are used when thrown. Chocolate frogs, no.
    //
    // Must come after the particle code above.
    //
    if (what->is_used_when_thrown()) {
      dbg("Use thrown item");
      TRACE_AND_INDENT();

      UseOptions use_options;
      use_options.remove_after_use = true;
      used(what, target, use_options);
    } else {
      DropOptions drop_options;
      drop_options.is_being_thrown = true;

      //
      // Previous bugs allowed you to throw a rock at yourself and hence by
      // this point there would be no owner. Double check the item is still owned.
      //
      if (what->top_owner()) {
        if (attempt_to_tame_with(target->curr_at, what)) {
          dbg("Tamed with thrown item");
          what->is_being_used_to_tame = true;
          TRACE_AND_INDENT();
          drop(what, target, drop_options);
        } else if (target && target->is_portal()) {
          dbg("Drop into portal");
          TRACE_AND_INDENT();
          drop(what, target, drop_options);
        } else {
          dbg("Drop thrown item");
          TRACE_AND_INDENT();
          drop(what, target, drop_options);
        }
      } else {
        dbg("Thrown item is no longer owned");
      }
    }
  }

  dbg("Post drop");
  TRACE_AND_INDENT();

  //
  // Location check must be after drop as this could thrown into a teleport.
  //
  what->location_check_me();

  dbg("Post location check");
  TRACE_AND_INDENT();

  //
  // As there is no animation, no need to hide.
  //
  if (what->has_external_particle || what->has_internal_particle) {
    what->hide("thrown");
  }

  if (is_player()) {
    game->tick_begin("player threw an item");

    if (game->state == Game::STATE_CHOOSING_TARGET) {
      game->change_state(Game::STATE_NORMAL, "finished choosing a target for throwing");
    }
  }

  return true;
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
