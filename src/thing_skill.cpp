//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
#include "my_vector_bounds_check.hpp"
#include "my_wid_skillbox.hpp"
#include <algorithm>

//
// Get the list of all other skills this skill replaces. This is done
// recursively, so skill X level 3 replaces X levels 1, 2
//
static void skill_get_replace_list(Tpp tp, std::list< Tpp > &out)
{
  TRACE_NO_INDENT();
  auto replaces = tp->skill_replaces();
  if (! replaces.empty()) {
    auto tppo = tp_find(replaces);
    if (tppo) {
      TRACE_NO_INDENT();
      out.push_back(tppo);
      skill_get_replace_list(tppo, out);
    }
  }
}

bool Thing::skill_add(Thingp new_skill)
{
  TRACE_NO_INDENT();

  if (! new_skill) {
    return false;
  }

  dbg("Try to add skill %s", new_skill->to_short_string().c_str());
  TRACE_AND_INDENT();

  if (! maybe_itemsp()) {
    dbg("No; not a monst");
    return false;
  }

  auto existing_owner = new_skill->immediate_owner();
  if (existing_owner) {
    if (existing_owner == this) {
      dbg("No; same owner");
      return false;
    }
    existing_owner->drop(new_skill);
  }

  TRACE_NO_INDENT();
  FOR_ALL_SKILLS(item)
  {
    //
    // Already carried?
    //
    if (item == new_skill->id) {
      dbg("No; already carried");
      return false;
    }
  }

  if (is_player()) {
    if (! skillbox_id_insert(new_skill)) {
      msg("You cannot receive any more skills!");
      new_skill->dead("too many skills");
      return false;
    }
  }

  itemsp()->skills.push_back(new_skill->id);
  new_skill->owner_set(this);
  new_skill->hide("skill add");

  dbg("Add skill %s", new_skill->to_short_string().c_str());

  if (is_player()) {
    wid_skillbox_init();
    sound_play("powerup");
  }

  if (new_skill->is_always_activated()) {
    skill_activate(new_skill);
  }

redo:
  //
  // If this new skill supersedes another skill(s), then remove them.
  //
  TRACE_NO_INDENT();
  FOR_ALL_SKILLS(item)
  {
    auto learned_skill = level->thing_find(item);
    if (learned_skill) {
      std::list< Tpp > preceding_skills;
      skill_get_replace_list(learned_skill->tp(), preceding_skills);

      TRACE_NO_INDENT();
      FOR_ALL_SKILLS(item)
      {
        auto other_skill = level->thing_find(item);
        for (auto preceding_skill : preceding_skills) {
          if (preceding_skill == other_skill->tp()) {
            skill_remove(other_skill);
            goto redo;
          }
        }
      }
    }
  }

  return true;
}

bool Thing::skill_remove(Thingp what)
{
  TRACE_NO_INDENT();

  dbg("Removing skill %s", what->to_short_string().c_str());
  TRACE_AND_INDENT();

  auto existing_owner = what->immediate_owner();
  if (existing_owner != this) {
    err("Attempt to remove skill %s which is not owned", what->to_short_string().c_str());
    return false;
  }

  Thingp o = what->top_owner();
  if (o) {
    if (o->is_player()) {
      o->skillbox_id_remove(what);
    }
  }

  what->owner_unset();

  auto items = itemsp();
  auto found = std::find(items->skills.begin(), items->skills.end(), what->id);
  if (found != items->skills.end()) {
    items->skills.erase(found);
  }

  dbg("Removed %s", what->to_short_string().c_str());
  what->dead("removed");

  game->set_request_to_remake_skillbox();

  return true;
}

void Thing::skill_remove_all(void)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return;
  }

  while (! itemsp()->skills.empty()) {
    auto id = *itemsp()->skills.begin();
    auto t  = level->thing_find(id);
    if (unlikely(! t)) {
      return;
    }
    skill_remove(t);
  }
}

bool Thing::skill_use(Thingp what)
{
  TRACE_NO_INDENT();
  msg("You use %s.", what->text_the().c_str());

  UseOptions use_options;
  used(what, this, use_options);

  if (what->is_target_select()) {
    return item_choose_target(what);
  }

  return true;
}

void Thing::skill_deactivate(Thingp what)
{
  TRACE_NO_INDENT();
  what->is_activated = false;
  game->set_request_to_remake_skillbox();
  if (is_player()) {
    msg("You deactivate %s.", what->text_the().c_str());
    sound_play("coin");
  }
}

void Thing::skill_activate(Thingp what)
{
  TRACE_NO_INDENT();
  what->is_activated = true;
  game->set_request_to_remake_skillbox();
  if (is_player()) {
    msg("You activate %s.", what->text_the().c_str());
    sound_play("coin");
  }
}

bool Thing::has_skill(Tpp skill)
{
  TRACE_NO_INDENT();
  if (! maybe_itemsp()) {
    return 0;
  }

  if (! skill) {
    return false;
  }

  TRACE_NO_INDENT();
  FOR_ALL_SKILLS(oid)
  {
    auto learned_skill_iter = game->level->thing_find(oid);
    auto learned_skill      = learned_skill_iter->tp();
    if (learned_skill == skill) {
      return true;
    }

    //
    // Check if this skill has been acquired via a superseding skill
    //
    TRACE_NO_INDENT();
    std::list< Tpp > preceding_skills;
    skill_get_replace_list(learned_skill, preceding_skills);
    for (auto preceding_skill : preceding_skills) {
      if (preceding_skill == skill) {
        return true;
      }
    }
  }

  return false;
}

bool Thing::skill_add(Tpp what)
{
  TRACE_NO_INDENT();
  auto t = level->thing_new(what, curr_at);
  if (unlikely(! t)) {
    err("Cannot learn skill");
    return false;
  }

  if (is_player()) {
    msg("You learn %s.", t->text_the().c_str());
  }

  skill_add(t);

  //
  // Drop a skillstone
  //
  auto found = false;
  for (const auto skillstone : carried_item_only_vector()) {
    if (skillstone->is_skillstone()) {
      if (skillstone->charge_count()) {
        skillstone->charge_count_decr();
      }
      if (! skillstone->charge_count()) {
        skillstone->is_drained = true;
        skillstone->dead("drained and used");
      }
      found = true;
      break;
    }
  }
  if (! found) {
    err("no skillstone found");
  }

  return true;
}

int Thing::skillstone_count(void)
{
  TRACE_NO_INDENT();
  int v = 0;
  for (const auto t : carried_item_only_vector()) {
    if (! t->is_skillstone()) {
      continue;
    }
    dbg("Found a skillstone: %s", t->to_short_string().c_str());
    v++;
  }
  return v;
}

bool Thing::can_learn_a_skill(void)
{
  TRACE_NO_INDENT();

  //
  // Once skills are maxxed out, that's it
  //
  if (itemsp()->skills.size() >= UI_INVENTORY_QUICK_ITEMS_MAX) {
    return false;
  }

  //
  // Look at the list of skills this thing knows. If we find
  // something that is not present, then we have something to learn.
  //
  for (auto tpp : tp_get_skills()) {
    bool already_learned = false;
    TRACE_NO_INDENT();
    FOR_ALL_SKILLS(oid)
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

static Tpp skill_alias_set_tpp(Skillp skill)
{
  if (skill->skill_alias.empty()) {
    return nullptr;
  }

  //
  // Check the alias to skill mapping exists
  //
  if (game->skill_aliases.find(skill->skill_alias) == game->skill_aliases.end()) {
    ERR("Skill alias %s not found", skill->skill_alias.c_str());
    return nullptr;
  }

  //
  // Find the skill template
  //
  auto skill_name = game->skill_aliases[ skill->skill_alias ];
  if (skill_name.empty()) {
    ERR("Skill name %s not found", skill->skill_alias.c_str());
    return nullptr;
  }

  auto tpp = tp_find(skill_name);
  if (tpp) {
    skill->tpp = tpp;
  }

  return tpp;
}

//
// Learn a random skill out of the available ones
//
bool Thing::learn_random_skill(void)
{
  TRACE_AND_INDENT();

  std::vector< Tpp > cands;

  for (auto iter : game->skill_tree) {
    auto tree_name = iter.first;
    for (auto y = 0; y < SKILL_TREE_DOWN; y++) {
      for (auto x = 0; x < SKILL_TREE_ACROSS; x++) {
        TRACE_NO_INDENT();

        auto new_skill = get(game->skill_tree[ tree_name ], x, y);
        if (! new_skill) {
          continue;
        }

        //
        // If the widget has not been opened yet, we need to set the skill tpp
        //
        skill_alias_set_tpp(new_skill);

        if (! new_skill->tpp) {
          ERR("Skill %s has no template", new_skill->skill_alias.c_str());
          continue;
        }

        dbg("Possible skill: %s", new_skill->tpp->name().c_str());
        TRACE_AND_INDENT();

        if (! skill_has_precursor(new_skill) || skill_is_available(new_skill)) {
          //
          // Available
          //
          TRACE_AND_INDENT();
          dbg("Candidate skill: %s", new_skill->tpp->name().c_str());
        } else {
          //
          // Not available
          //
          TRACE_AND_INDENT();
          dbg("Unavailable skill: %s", new_skill->tpp->name().c_str());
          continue;
        }

        //
        // Check this skill is not already known
        //
        bool skill_cand = true;
        TRACE_NO_INDENT();
        FOR_ALL_SKILLS(oid)
        {
          auto current_skill = game->level->thing_find(oid);
          if (! current_skill) {
            continue;
          }

          if (current_skill->tp() == new_skill->tpp) {
            //
            // Already known
            //
            TRACE_AND_INDENT();
            dbg("Add candidate skill: %s", new_skill->tpp->name().c_str());
            skill_cand = false;
            break;
          }
        }

        if (skill_cand) {
          cands.push_back(new_skill->tpp);
        }
      }
    }
  }

  if (cands.empty()) {
    return false;
  }

  auto chosen = cands[ pcg_random_range(0, cands.size()) ];
  dbg("Add this skill: %s", chosen->name().c_str());
  return skill_add(chosen);
}
