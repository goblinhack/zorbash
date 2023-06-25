//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_python.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

bool Thing::is_bodypart(Thingp item)
{
  FOR_ALL_BODYPART(iter)
  {
    if (item == bodypart_get(iter)) {
      return true;
    }
  }
  return false;
}

Thingp Thing::bodypart_get(int which)
{
  TRACE_NO_INDENT();

  switch (which) {
    case BODYPART_HAT : break;
    case BODYPART_HAIR : break;
    case BODYPART_FACE : break;
    case BODYPART_TORSO : break;
    case BODYPART_LEGS : break;
    case BODYPART_EYES : break;
    default : err("Unknown bodypart type %d", which); return nullptr;
  }

  auto id = bodypart_id_get(which);
  if (id.ok()) {
    return (level->thing_find(id));
  }

  return nullptr;
}

//
// Returns true on change
//
bool Thing::bodypart_add(Thingp bodypart, int which)
{
  dbg("Try to add bodypart: %s", bodypart->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (bodypart_get(which) == bodypart) {
    return false;
  }

  bodypart_remove(which);
  bodypart_id_set(bodypart->id, which);
  bodypart->owner_set(this);

  return true;
}

void Thing::bodypart_remove(int which)
{
  TRACE_NO_INDENT();
  auto bodypart = bodypart_get(which);
  if (! bodypart) {
    return;
  }

  dbg("Remove bodypart %s", bodypart->to_short_string().c_str());
  TRACE_AND_INDENT();

  //
  // If this thing has its own thing id for animations then destroy that.
  //
  auto id = bodypart_id_get(which);
  if (id.ok()) {
    auto bodypart = level->thing_find(id);
    if (bodypart) {
      bodypart->dead("removed bodypart");
      bodypart->owner_set(nullptr);
    }
    bodypart_id_set(NoThingId, which);
  }
}

std::string bodypart_name(int which)
{
  switch (which) {
    case BODYPART_HAT : return "bling";
    case BODYPART_HAIR : return "hair";
    case BODYPART_FACE : return "face";
    case BODYPART_TORSO : return "torso";
    case BODYPART_LEGS : return "legs";
    case BODYPART_EYES : return "eyes";
  }
  DIE("unknown bodypart enum");
}

ThingId Thing::bodypart_id_get(int which)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    auto id = get(itemsp()->bodypart_id, which);
    if (id != NoThingId) {
      verify(MTYPE_THING, level->thing_find(id));
    }
    return id;
  }
  return NoThingId;
}

void Thing::bodypart_id_set(ThingId v, int which)
{
  TRACE_NO_INDENT();
  new_itemsp();
  itemsp()->bodypart_id[ which ] = v;
}
