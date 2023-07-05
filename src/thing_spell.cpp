//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_spellbox.hpp"

//
// Get the list of all other spells this spell replaces. This is done
// recursively, so spell X level 3 replaces X levels 1, 2
//
static void spell_get_replace_list(Tpp tp, std::list< Tpp > &out)
{
  TRACE_NO_INDENT();
  auto replaces = tp->spell_replaces();
  if (! replaces.empty()) {
    auto tppo = tp_find(replaces);
    if (tppo) {
      TRACE_NO_INDENT();
      out.push_back(tppo);
      spell_get_replace_list(tppo, out);
    }
  }
}

bool Thing::spell_add(Thingp new_spell)
{
  TRACE_NO_INDENT();

  dbg("Try to add spell %s", new_spell->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    dbg("No; not a monst");
    return false;
  }

  auto existing_owner = new_spell->immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      dbg("No; same owner");
      return false;
    }
    existing_owner->drop(new_spell);
  }

  FOR_ALL_SPELLS(item)
  {
    //
    // Already carried?
    //
    if (item == new_spell->id) {
      dbg("No; already carried");
      return false;
    }
  }

  if (is_player()) {
    if (! spellbox_id_insert(new_spell)) {
      dbg("No; no space in spellbox");
      return false;
    }
  }

  itemsp()->spells.push_front(new_spell->id);
  new_spell->owner_set(this);
  new_spell->hide();

  dbg("Add spell %s", new_spell->to_short_string().c_str());

  if (is_player()) {
    wid_spellbox_init();
    sound_play("powerup");
  }

redo:
  //
  // If this new spell supersedes another spell(s), then remove them.
  //
  FOR_ALL_SPELLS(item)
  {
    auto learned_spell = level->thing_find(item);
    if (learned_spell) {
      std::list< Tpp > preceding_spells;
      spell_get_replace_list(learned_spell->tp(), preceding_spells);

      FOR_ALL_SPELLS(item)
      {
        auto other_spell = level->thing_find(item);
        for (auto preceding_spell : preceding_spells) {
          if (preceding_spell == other_spell->tp()) {
            spell_remove(other_spell);
            goto redo;
          }
        }
      }
    }
  }

  return true;
}

bool Thing::spell_remove(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Removing spell %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = what->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove spell %s which is not owned", what->to_short_string().c_str());
    return false;
  }

  Thingp o = what->top_owner();
  if (o) {
    if (o->is_player()) {
      o->spellbox_id_remove(what);
    }
  }

  what->owner_unset();
  itemsp()->spells.remove(what->id);
  game->set_request_to_remake_spellbox();

  dbg("Removed %s", what->to_short_string().c_str());
  return true;
}

void Thing::spell_remove_all(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return;
  }

  while (! itemsp()->spells.empty()) {
    auto id = *itemsp()->spells.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    spell_remove(t);
  }
}

bool Thing::spell_use(Thingp what)
{
  TRACE_NO_INDENT();

  if (what->spell_cost() > magic()) {
    if (is_player()) {
      msg("You do not have enough magic points to cast %s. You need %d.", what->text_the().c_str(),
          what->spell_cost());
    }
    return false;
  }

  magic_decr(what->spell_cost());
  msg("You cast %s.", what->text_the().c_str());
  used(what, this, false /* remove after use */);

  if (what->is_target_select()) {
    return item_choose_target(what);
  }

  return true;
}

void Thing::spell_deactivate(Thingp what)
{
  TRACE_NO_INDENT();
  what->is_activated = false;
  game->set_request_to_remake_spellbox();
  if (is_player()) {
    sound_play("coin");
  }
}

void Thing::spell_activate(Thingp what)
{
  TRACE_NO_INDENT();
  what->is_activated = true;
  game->set_request_to_remake_spellbox();
  if (is_player()) {
    sound_play("coin");
  }
}

bool Thing::has_spell(Tpp spell)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return 0;
  }

  if (! spell) {
    return false;
  }

  TRACE_NO_INDENT();
  FOR_ALL_SPELLS(oid)
  {
    auto learned_spell_iter = game->level->thing_find(oid);
    auto learned_spell      = learned_spell_iter->tp();
    if (learned_spell == spell) {
      return true;
    }

    //
    // Check if this spell has been acquired via a superseding spell
    //
    TRACE_NO_INDENT();
    std::list< Tpp > preceding_spells;
    spell_get_replace_list(learned_spell, preceding_spells);
    for (auto preceding_spell : preceding_spells) {
      if (preceding_spell == spell) {
        return true;
      }
    }
  }

  return false;
}

bool Thing::spell_add(Tpp what)
{
  TRACE_NO_INDENT();
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    err("Cannot learn spell");
    return false;
  }

  if (is_player()) {
    msg("You learn %s.", t->text_the().c_str());
  }

  spell_add(t);

  //
  // Drop a spellbook
  //
  auto found = false;
  for (const auto t : carried_item_only_vector()) {
    if (t->is_spellbook()) {
      t->is_drained = true;
      t->dead("drained and used");
      found = true;
      break;
    }
  }
  if (! found) {
    err("no spellbook found");
  }

  return true;
}

int Thing::spellbook_count(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  for (const auto t : carried_item_only_vector()) {
    if (! t->is_spellbook()) {
      continue;
    }
    dbg("Found a spellbook: %s", t->to_short_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_learn_a_spell(void)
{
  TRACE_NO_INDENT();

  //
  // Once spells are maxxed out, that's it
  //
  if (itemsp()->spells.size() >= UI_INVENTORY_QUICK_ITEMS_MAX) {
    return false;
  }

  //
  // Look at the list of spells this thing knows. If we find
  // something that is not present, then we have something to learn.
  //
  for (auto tpp : tp_get_spells()) {
    bool already_learned = false;
    FOR_ALL_SPELLS(oid)
    {
      auto o = game->level->thing_find(oid);
      if (o) {
        if (o->tp() == tpp) {
          already_learned = true;
          break;
        }
      }
    }
    if (already_learned) {
      continue;
    }
    return true;
  }
  return false;
}

bool Thing::learn_random_spell(void)
{
  TRACE_NO_INDENT();

  std::vector< Tpp > cands;
  for (auto tpp : tp_get_spells()) {
    bool add = true;
    FOR_ALL_SPELLS(oid)
    {
      auto o = game->level->thing_find(oid);
      if (o) {
        if (o->tp() == tpp) {
          add = false;
          break;
        }
      }
    }
    if (add) {
      cands.push_back(tpp);
    }
  }

  if (cands.empty()) {
    return false;
  }

  auto chosen = cands[ pcg_random_range(0, cands.size()) ];
  dbg("Add this spell: %s", chosen->name().c_str());
  return spell_add(chosen);
}
