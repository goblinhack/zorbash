//
// Copyright goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_ui.hpp"
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

  if (! new_spell) {
    return false;
  }

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

  TRACE_NO_INDENT();
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
      msg("You cannot add any more skills!");
      new_spell->dead("too many spells");
      return false;
    }
  }

  itemsp()->spells.push_back(new_spell->id);
  new_spell->owner_set(this);
  new_spell->hide("spell added");

  dbg("Add spell %s", new_spell->to_short_string().c_str());

  if (is_player()) {
    wid_spellbox_init();
    sound_play("powerup");
  }

redo:
  //
  // If this new spell supersedes another spell(s), then remove them.
  //
  TRACE_NO_INDENT();
  FOR_ALL_SPELLS(item)
  {
    auto learned_spell = level->thing_find(item);
    if (learned_spell) {
      std::list< Tpp > preceding_spells;
      spell_get_replace_list(learned_spell->tp(), preceding_spells);

      TRACE_NO_INDENT();
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

  auto items = itemsp();
  auto found = std::find(items->spells.begin(), items->spells.end(), what->id);
  if (found != items->spells.end()) {
    items->spells.erase(found);
  }

  dbg("Removed %s", what->to_short_string().c_str());
  what->dead("removed");

  game->set_request_to_remake_skillbox();

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

bool Thing::spell_can_use(Thingp what)
{
  TRACE_NO_INDENT();

  //
  // Have enough points?
  //
  if (what->spell_cost() > magic()) {
    if (is_player()) {
      msg("%%fg=orange$You do not have enough magic points to cast %s. You need %d.%%fg=reset$",
          what->text_the().c_str(), what->spell_cost());
      spell_deactivate(what);
      sound_play("bonk");
    }
    return false;
  }
  return true;
}

bool Thing::spell_cast(Thingp what)
{
  TRACE_NO_INDENT();

  //
  // Have enough points?
  //
  if (! spell_can_use(what)) {
    return false;
  }

  if (what->is_target_select()) {
    return item_choose_target(what);
  }

  msg("You cast %s spell.", what->text_the().c_str());

  UseOptions use_options;
  used(what, this, use_options);

  return true;
}

bool Thing::spell_cast_at(Thingp what, Thingp target)
{
  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot cast spell null thing");
    return false;
  }

  verify(MTYPE_THING, what);
  if (! what) {
    err("Cannot cast spell at null target");
    return false;
  }

  //
  // We don't always get to spell_cast as far as we want.
  //
  bool need_to_choose_a_new_target = false;

  //
  // Check for obstacles in the way of the spell_casting.
  //
  auto target_at                 = target->curr_at;
  auto spell_cast_was_stopped_at = in_the_way_for_casting(curr_at, target_at);

  auto in_the_way = in_the_way_for_casting(curr_at, target_at, 1);
  if (in_the_way.size()) {
    target = in_the_way[ 0 ];

    //
    // Something was in the way.
    //
    if (is_player()) {
      msg("You fail to cast %s that far, something was in the way.", what->text_the().c_str());
    } else {
      dbg("Fail to cast %s that far, something was in the way", what->text_the().c_str());
    }

    need_to_choose_a_new_target = true;

    target_at = target->curr_at;
    dbg("Casts %s at new in-the-way thing at: %s", what->to_short_string().c_str(), target_at.to_string().c_str());
  }

  //
  // If you can't cast that far, cast as far as you can.
  //
  float dist     = DISTANCE(curr_at.x, curr_at.y, target_at.x, target_at.y);
  float max_dist = distance_spell_cast_get();
  if (! max_dist) {
    err("Cannot cast spell, no distance set");
    return false;
  }

  if (dist > max_dist) {
    if (! need_to_choose_a_new_target) {
      if (is_player()) {
        msg("You fail to cast %s that far.", what->text_the().c_str());
      }
    }

    float dx = (float) target_at.x - (float) curr_at.x;
    float dy = (float) target_at.y - (float) curr_at.y;
    dx /= dist;
    dy /= dist;
    dx *= max_dist - 1;
    dy *= max_dist - 1;
    target_at = curr_at + point(dx, dy);

    float dist = distance(curr_at, target_at);
    dbg("Cast %s at new point %s, dist %f, max dist %f", what->to_short_string().c_str(),
        target_at.to_string().c_str(), dist, max_dist);
    need_to_choose_a_new_target = true;
  }

  if (need_to_choose_a_new_target) {
    TRACE_NO_INDENT();
    FOR_ALL_GRID_THINGS(level, t, target_at.x, target_at.y)
    {
      target = t;
      break;
    }
    TRACE_NO_INDENT();
    FOR_ALL_THINGS_END()
  }

  dbg("Cast %s at %s", what->to_short_string().c_str(), target->to_string().c_str());
  TRACE_AND_INDENT();

  //
  // Particle or laser effect for the spell?
  //
  if (what->gfx_targeted_laser().empty()) {
    target = projectile_shoot_at(what, what->gfx_targeted_projectile(), target_at);
  } else {
    UseOptions use_options;
    target = laser_shoot_at(what, what->gfx_targeted_laser(), target_at, use_options);
  }

  dbg("Spell is used");
  TRACE_AND_INDENT();

  if (! target) {
    //
    // Failed
    //
  } else if ((target->is_immune_to_spell_of_slowness() && what->is_spell_of_slowness())
             || (target->is_immune_to_spell_of_holding() && what->is_spell_of_holding())
             || (target->is_immune_to_spell_of_sanctuary() && what->is_spell_of_sanctuary())
             || (target->is_immune_to_spell_of_beckoning() && what->is_spell_of_beckoning())
             || (target->is_immune_to_spell_of_repulsion() && what->is_spell_of_repulsion())) {
    //
    // Immune. Spell fails.
    //
    dbg("Spell fails on immune target: %s", target->to_string().c_str());
    TRACE_AND_INDENT();

    if (target->is_player()) {
      target->msg("%%fg=green$You are immune to %s %s spell.%%fg=reset$", text_the(TEXT_APOSTROPHIZE).c_str(),
                  what->text_long_name().c_str());
    } else if (target->is_monst() && is_player()) {
      msg("%%fg=yellow$%s is immune to your %s spell.%%fg=reset$", capitalize_first(target->text_the()).c_str(),
          what->text_long_name().c_str());
    }
  } else if (this == target) {
    //
    // Allow the ability to cast spells on yourself
    //
    dbg("Spell is used on self");
    TRACE_AND_INDENT();
  } else if (target->is_alive_monst() || target->is_player()) {
    //
    // Casting upon another
    //
    dbg("Spell is used on target: %s", target->to_string().c_str());
    TRACE_AND_INDENT();

    //
    // Spells of protection always succeed
    //
    if (what->is_spell_always_succeeds() || (d20() + stat_psi_bonus() > target->stat_psi())) {
      //
      // Spell succeeds
      //
      dbg("Spell succeeds on target: %s", target->to_string().c_str());
      TRACE_AND_INDENT();

      if (target->is_player()) {
        target->msg("%%fg=yellow$You are hit by %s %s spell.%%fg=reset$", text_the(TEXT_APOSTROPHIZE).c_str(),
                    what->text_long_name().c_str());
      } else if (target->is_monst() && is_player()) {
        msg("%%fg=green$Your spell succeeds.%%fg=reset$");
      }

      UseOptions use_options;
      used(what, target, use_options);

      //
      // Prevent the thing from moving due to shock
      //
      target->move_penalty_incr();
    } else {
      //
      // Spell fails
      //
      dbg("Spell fails on target: %s", target->to_string().c_str());
      TRACE_AND_INDENT();

      if (target->is_player()) {
        target->msg("%%fg=green$You resist %s %s spell.%%fg=reset$", text_the(TEXT_APOSTROPHIZE).c_str(),
                    what->text_long_name().c_str());
      } else if (target->is_monst() && is_player()) {
        msg("%%fg=yellow$%s resists your %s spell.%%fg=reset$", capitalize_first(target->text_the()).c_str(),
            what->text_long_name().c_str());
      }
    }
  } else {
    //
    // Could be the grid, the cursor, a door etc.. etc...
    //
    UseOptions use_options;
    used(what, target, use_options);
  }

  if (is_player()) {
    game->tick_begin("player cast a spell");

    if (game->state == Game::STATE_CHOOSING_TARGET) {
      game->change_state(Game::STATE_NORMAL, "finished choosing a target");
    }
  }

  return target;
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

  //
  // Have enough points?
  //
  if (! spell_can_use(what)) {
    return;
  }

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
  for (const auto spellbook : carried_item_only_vector()) {
    if (spellbook->is_spellbook()) {
      if (spellbook->charge_count()) {
        spellbook->charge_count_decr();
      }
      if (! spellbook->charge_count()) {
        spellbook->is_drained = true;
        spellbook->dead("drained and used");
      }
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
    TRACE_NO_INDENT();
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

static Tpp spell_alias_set_tpp(Spellp spell)
{
  if (spell->spell_alias.empty()) {
    return nullptr;
  }

  //
  // Check the alias to spell mapping exists
  //
  if (game->spell_aliases.find(spell->spell_alias) == game->spell_aliases.end()) {
    ERR("Spell alias %s not found", spell->spell_alias.c_str());
    return nullptr;
  }

  //
  // Find the spell template
  //
  auto spell_name = game->spell_aliases[ spell->spell_alias ];
  if (spell_name.empty()) {
    ERR("Spell name %s not found", spell->spell_alias.c_str());
    return nullptr;
  }

  auto tpp = tp_find(spell_name);
  if (tpp) {
    spell->tpp = tpp;
  }

  return tpp;
}

//
// Learn a random spell out of the available ones
//
bool Thing::learn_random_spell(void)
{
  TRACE_AND_INDENT();

  std::vector< Tpp > cands;

  for (auto iter : game->spell_tree) {
    auto tree_name = iter.first;
    for (auto y = 0; y < SPELL_TREE_DOWN; y++) {
      for (auto x = 0; x < SPELL_TREE_ACROSS; x++) {
        TRACE_NO_INDENT();

        auto new_spell = get(game->spell_tree[ tree_name ], x, y);
        if (! new_spell) {
          continue;
        }

        //
        // If the widget has not been opened yet, we need to set the spell tpp
        //
        spell_alias_set_tpp(new_spell);

        if (! new_spell->tpp) {
          ERR("Spell %s has no template", new_spell->spell_alias.c_str());
          continue;
        }

        dbg("Possible spell: %s", new_spell->tpp->name().c_str());
        TRACE_AND_INDENT();

        if (! spell_has_precursor(new_spell) || spell_is_available(new_spell)) {
          //
          // Available
          //
          TRACE_AND_INDENT();
          dbg("Candidate spell: %s", new_spell->tpp->name().c_str());
        } else {
          //
          // Not available
          //
          TRACE_AND_INDENT();
          dbg("Unavailable spell: %s", new_spell->tpp->name().c_str());
          continue;
        }

        //
        // Check this spell is not already known
        //
        bool spell_cand = true;
        TRACE_NO_INDENT();
        FOR_ALL_SPELLS(oid)
        {
          auto current_spell = game->level->thing_find(oid);
          if (! current_spell) {
            continue;
          }

          if (current_spell->tp() == new_spell->tpp) {
            //
            // Already known
            //
            TRACE_AND_INDENT();
            dbg("Add candidate spell: %s", new_spell->tpp->name().c_str());
            spell_cand = false;
            break;
          }
        }

        if (spell_cand) {
          cands.push_back(new_spell->tpp);
        }
      }
    }
  }

  if (cands.empty()) {
    return false;
  }

  auto chosen = cands[ pcg_random_range(0, cands.size()) ];
  dbg("Add this spell: %s", chosen->name().c_str());
  return spell_add(chosen);
}

////////////////////////////////////////////////////////////////////////////
// distance_spell_cast
////////////////////////////////////////////////////////////////////////////
float Thing::distance_spell_cast_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->distance_spell_cast);
  }
  return 0;
}

int Thing::distance_spell_cast_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_spell_cast = v);
  return n;
}

int Thing::distance_spell_cast_decr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_spell_cast -= v);
  return n;
}

int Thing::distance_spell_cast_incr(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_spell_cast += v);
  return n;
}

int Thing::distance_spell_cast_decr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_spell_cast--);
  return n;
}

int Thing::distance_spell_cast_incr(void)
{
  TRACE_NO_INDENT();
  new_infop();
  auto n = (infop()->distance_spell_cast++);
  return n;
}
