//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_english.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::negation_dmg(int dmg, bool &is_killed)
{
  TRACE_NO_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      iter->negation_dmg(dmg, is_killed);
    }
  }

  if (maybe_itemsp()) {
    FOR_ALL_CARRYING(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->negation_dmg(dmg, is_killed);
      }
    }

    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->negation_dmg(dmg, is_killed);
      }
    }

    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->negation_dmg(dmg, is_killed);
      }
    }

    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->negation_dmg(dmg, is_killed);
      }
    }
  }

  //
  // If a magical monster, kill them
  //
  if (is_monst()) {
    if (is_magical()) {
      is_killed = true;
      return;
    }
  }

  //
  // The magical check avoids torches being drained
  //
  if (is_magical()) {
    if (enchant_count_get()) {
      //
      // If an enchanted item, remove one charge (or more)
      //
      enchant_count_decr(dmg);

      auto owner = top_owner();

      //
      // Still enchanted?
      //
      if (enchant_count_get()) {
        if (owner && owner->is_player()) {
          if (! owner->is_dying && ! owner->is_dying) {
            owner->msg("Your %s loses enchantment!", text_long_name().c_str());
          }
        } else if (owner && owner->is_monst()) {
          if (! owner->is_dying && ! owner->is_dying) {
            owner->msg("%s %s loses enchantment!", apostrophise(owner->text_The()).c_str(), text_long_name().c_str());
          }
        }
      } else {
        if (owner && owner->is_player()) {
          if (! owner->is_dying && ! owner->is_dying) {
            owner->msg("Your %s is no longer enchanted!", text_long_name().c_str());
          }
        } else if (owner && owner->is_monst()) {
          if (! owner->is_dying && ! owner->is_dying) {
            owner->msg("%s %s is no longer enchanted!", apostrophise(owner->text_The()).c_str(),
                       text_long_name().c_str());
          }
        }
      }
    } else if (charge_count()) {
      charge_count_set(0);

      auto owner = top_owner();

      //
      // Still enchanted?
      //
      if (owner && owner->is_player()) {
        if (! owner->is_dying && ! owner->is_dying) {
          owner->msg("Your %s loses all charges!", text_long_name().c_str());
        }
      } else if (owner && owner->is_monst()) {
        if (! owner->is_dying && ! owner->is_dying) {
          owner->msg("%s %s has no more charges!", apostrophise(owner->text_The()).c_str(), text_long_name().c_str());
          owner->drop(this);
        }
      }
    }
  }
}
