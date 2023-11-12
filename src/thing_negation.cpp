//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_english.hpp"
#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

void Thing::negation_dmg(int dmg, bool &is_killed)
{
  TRACE_NO_INDENT();

  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      verify(MTYPE_THING, iter);
      iter->negation_dmg(dmg, is_killed);
    }
  }

  if (maybe_itemsp()) {
    TRACE_NO_INDENT();
    FOR_ALL_CARRYING(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        iter->negation_dmg(dmg, is_killed);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_BUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        verify(MTYPE_THING, iter);
        iter->negation_dmg(dmg, is_killed);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_DEBUFFS(id)
    {
      auto iter = level->thing_find(id);
      if (iter) {
        verify(MTYPE_THING, iter);
        iter->negation_dmg(dmg, is_killed);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SKILLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        verify(MTYPE_THING, iter);
        iter->negation_dmg(dmg, is_killed);
      }
    }

    TRACE_NO_INDENT();
    FOR_ALL_SPELLS(id)
    {
      auto iter = level->thing_find(id);
      if (iter && iter->is_activated) {
        verify(MTYPE_THING, iter);
        iter->negation_dmg(dmg, is_killed);
      }
    }
  }

  if (is_monst()) {
    //
    // If a magical monster, kill them
    //
    if (is_magical()) {
      is_killed = true;
      return;
    }

    //
    // Else remove immunity. Just one ?
    //
    if (! _is_immune_to_negation) {
      if (_is_able_to_regenerate) {
        msg("%s loses the ability to regenerate!", text_The().c_str());
        _is_able_to_regenerate = false;
      } else if (_is_immune_to_cold) {
        msg("%s loses natural immunity to cold!", text_The().c_str());
        _is_immune_to_cold = false;
      } else if (_is_immune_to_fire) {
        msg("%s loses natural immunity to fire!", text_The().c_str());
        _is_immune_to_fire = false;
      } else if (_is_immune_to_acid) {
        msg("%s loses natural immunity to acid!", text_The().c_str());
        _is_immune_to_acid = false;
      } else if (_is_immune_to_poison) {
        msg("%s loses natural immunity to poison!", text_The().c_str());
        _is_immune_to_poison = false;
      } else if (_is_immune_to_electricity) {
        msg("%s loses natural immunity to electricity!", text_The().c_str());
        _is_immune_to_electricity = false;
      } else if (_is_immune_to_lightning) {
        msg("%s loses natural immunity to lightning!", text_The().c_str());
        _is_immune_to_lightning = false;
      } else if (_is_immune_to_magic_drain) {
        msg("%s loses natural immunity to magical draining!", text_The().c_str());
        _is_immune_to_magic_drain = false;
      } else if (_is_immune_to_stamina_drain) {
        msg("%s loses natural immunity to stamina drain!", text_The().c_str());
        _is_immune_to_stamina_drain = false;
      } else if (_is_immune_to_necrosis) {
        msg("%s loses natural immunity to necrosis!", text_The().c_str());
        _is_immune_to_necrosis = false;
      } else if (_is_immune_to_blinding) {
        msg("%s loses natural immunity to blinding!", text_The().c_str());
        _is_immune_to_blinding = false;
      } else if (_is_immune_to_confusion) {
        msg("%s loses natural immunity to confusion!", text_The().c_str());
        _is_immune_to_confusion = false;
      } else if (_is_immune_to_entrancement) {
        msg("%s loses natural immunity to entrancement!", text_The().c_str());
        _is_immune_to_entrancement = false;
      } else if (_is_immune_to_non_magical_weapons) {
        msg("%s loses natural immunity to non-magical-weapons!", text_The().c_str());
        _is_immune_to_non_magical_weapons = false;
      } else if (_is_immune_to_paralysis) {
        msg("%s loses natural immunity to paralysis!", text_The().c_str());
        _is_immune_to_paralysis = false;
      } else if (_is_immune_to_spell_of_beckoning) {
        msg("%s loses natural immunity to spell-of-beckoning!", text_The().c_str());
        _is_immune_to_spell_of_beckoning = false;
      } else if (_is_immune_to_spell_of_holding) {
        msg("%s loses natural immunity to spell-of-holding!", text_The().c_str());
        _is_immune_to_spell_of_holding = false;
      } else if (_is_immune_to_spell_of_repulsion) {
        msg("%s loses natural immunity to spell-of-repulsion!", text_The().c_str());
        _is_immune_to_spell_of_repulsion = false;
      } else if (_is_immune_to_spell_of_sanctuary) {
        msg("%s loses natural immunity to spell-of-sanctuary!", text_The().c_str());
        _is_immune_to_spell_of_sanctuary = false;
      } else if (_is_immune_to_spell_of_slowness) {
        msg("%s loses natural immunity to spell-of-slowness!", text_The().c_str());
        _is_immune_to_spell_of_slowness = false;
      } else if (_is_immune_to_teleport_attack) {
        msg("%s loses natural immunity to teleport-attack!", text_The().c_str());
        _is_immune_to_teleport_attack = false;
      } else if (_is_immune_to_vorpal_weapons) {
        msg("%s loses natural immunity to vorpal weapons!", text_The().c_str());
        _is_immune_to_vorpal_weapons = false;
      } else if (_is_immune_to_holy_damage) {
        msg("%s loses natural immunity to holy damage!", text_The().c_str());
        _is_immune_to_holy_damage = false;
      }
    }
  }

  //
  // The magical check avoids torches being drained
  //
  if (is_magical() || is_weapon() || is_ring() || is_staff()) {
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
        } else if (is_item()) {
          msg("%s loses enchantment!", text_The().c_str());
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
        } else if (is_item()) {
          msg("%s is no longer enchanted!", text_The().c_str());
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
      } else if (is_item()) {
        msg("%s shakes!", text_The().c_str());
      }
    }
  }
}
