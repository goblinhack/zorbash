//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

point3d Thing::born_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->born);
  }
  die("No born location");
  return (point3d(-1, -1, -1));
}

void Thing::born_set(point3d v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->born = v;
}

const std::string &Thing::on_born_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_born_do());
}
