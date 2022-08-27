//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void Thing::on_lifespan_tick(Thingp what)
{
  auto on_lifespan_tick = what->tp()->on_lifespan_tick_do();
  if (std::empty(on_lifespan_tick)) {
    return;
  }

  auto t = split_tokens(on_lifespan_tick, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = what->name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), what->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, what->id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_lifespan_tick call [%s] expected mod:function, got %d elems", on_lifespan_tick.c_str(),
        (int) on_lifespan_tick.size());
  }
}

void Thing::lifespan_tick(void)
{
  TRACE_NO_INDENT();

  //
  // Torches only tick when carried
  //
  auto owner = immediate_owner();
  if (is_torch() && ! owner) {
    return;
  }

  if (! lifespan_get()) {
    return;
  }

  lifespan_decr();

  if (lifespan_get()) {
    return;
  }

  auto o = top_owner();
  if (o) {
    o->on_lifespan_tick(this);

    //
    // If the onwer if on first and this is fire, remove the flames!
    //
    if (is_fire()) {
      if (o->is_player()) {
        o->msg("The flames go out.");
      }
      o->on_fire_unset();
    }
  }

  //
  // This is for torches
  //
  if (charge_count()) {
    charge_count_decr();
    if (charge_count()) {
      dbg("Lifespan expired (but has %d charges left)", charge_count());
      game->request_remake_rightbar = true;
      LOG("Request to remake rightbar at %s %d", __FUNCTION__, __LINE__);
      lifespan_set(tp()->lifespan());
      return;
    }
  }

  dead("by ran out of life");
}

int Thing::lifespan_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->lifespan);
  } else {
    return 0;
  }
}

int Thing::lifespan_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan = v);
}

int Thing::lifespan_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan -= v);
}

int Thing::lifespan_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan += v);
}

int Thing::lifespan_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan--);
}

int Thing::lifespan_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  return (infop()->lifespan++);
}
