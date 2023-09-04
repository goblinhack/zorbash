//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

////////////////////////////////////////////////////////////////////////////
// runic_name
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::runic_name_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->runic_name);
  }
  static std::string empty;
  return empty;
}

void Thing::runic_name_set(const std::string &v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->runic_name = v;
}
