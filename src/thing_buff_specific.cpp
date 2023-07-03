//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

bool Thing::buff_is_slippery(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_slippery()) {
        return true;
      }
    }
  }
  return false;
}

bool Thing::buff_is_aquatic(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_aquatic()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_aquatic()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_fire(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_fire()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_fire()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_cold(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_cold()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_cold()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_poison(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_poison()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_poison()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_negation(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_negation()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_negation()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_teleport_attack(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_teleport_attack()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_teleport_attack()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_water(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_water()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_water()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_stamina_drain(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_stamina_drain()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_stamina_drain()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_magic_drain(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_magic_drain()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_magic_drain()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_immune_to_necrosis(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_immune_to_necrosis()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_immune_to_necrosis()) {
          return true;
        }
      }
    }
  }

  return false;
}

bool Thing::buff_is_invisible(void)
{
  TRACE_NO_INDENT();

  if (! maybe_itemsp()) {
    return false;
  }

  FOR_ALL_BUFFS(id)
  {
    auto t = level->thing_find(id);
    if (t) {
      if (t->is_invisible()) {
        return true;
      }
    }
  }

  auto owner = top_owner();
  if (owner) {
    FOR_ALL_BUFFS_FOR(owner, item)
    {
      auto iter = level->thing_find(item.id);
      if (iter) {
        if (iter->is_invisible()) {
          return true;
        }
      }
    }
  }

  return false;
}
