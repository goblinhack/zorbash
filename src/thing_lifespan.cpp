//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

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
  }

  //
  // This is for torches
  //
  if (charge_count()) {
    charge_count_decr();
    if (charge_count()) {
      dbg("Lifespan expired (but has %d charges left)", charge_count());
      game->set_request_to_remake_rightbar();
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
  }
  return 0;
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

const Dice &Thing::lifespan_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->lifespan_dice());
}

const std::string &Thing::lifespan_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->lifespan_dice_str());
}

int Thing::lifespan_initial(void)
{
  TRACE_NO_INDENT();
  return (tp()->lifespan_dice().roll());
}

const std::string &Thing::on_lifespan_tick_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_lifespan_tick_do());
}
