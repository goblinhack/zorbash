//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

int Thing::is_reflective(void)
{
  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter && iter->is_reflective()) {
      return true;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_BUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter && iter->is_reflective()) {
      return true;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_DEBUFFS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter && iter->is_reflective()) {
      return true;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_SKILLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter && iter->is_activated) {
      if (iter && iter->is_reflective()) {
        return true;
      }
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_SPELLS(item)
  {
    auto iter = level->thing_find(item.id);
    if (iter && iter->is_reflective()) {
      return true;
    }
  }

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter && iter->is_reflective()) {
      return true;
    }
  }

  return (tp()->is_reflective());
}
