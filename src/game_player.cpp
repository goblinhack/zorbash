//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Game::place_player(void)
{
  //
  // Place the player if we do not have one.
  //
  if (! level) {
    ERR("No level for player");
    return;
  }

  if (game->level->player) {
    return;
  }

  DBG("Place player");

  for (auto x = MAP_BORDER_ROCK; x < MAP_WIDTH - MAP_BORDER_ROCK; x++) {
    for (auto y = MAP_BORDER_ROCK; y < MAP_HEIGHT - MAP_BORDER_ROCK; y++) {

      //
      // Place the player at the ascend exit
      //
      if (! level->is_ascend_dungeon(x, y)) {
        continue;
      }

      CarryOptions carry_options;
      carry_options.is_able_to_be_equipped = true;

      auto t = level->thing_new("player1", point(x, y));
      if (! t) {
        DIE("Failed to create player");
      }

      TRACE_NO_INDENT();
      FOR_ALL_BODYPART(iter)
      {
        TRACE_NO_INDENT();
        auto preferred_bodypart = get(game->config.player_bodyparts, iter);
        auto my_bodypart        = level->thing_new(preferred_bodypart, point(x, y));
        t->bodypart_add(my_bodypart, iter);
      }

      if (0) {
        level->thing_new("potion_poison", point(x + 1, y));
        level->thing_new("fire", point(x + 1, y));
      }
      if (0) {
        auto w = level->thing_new("potion_levitation", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("trap_blinded", point(x + 2, y));
      }
      if (0) {
        level->thing_new("spectral_blade", point(x + 1, y));
        level->thing_new("trap_blinded", point(x + 2, y + 2));
        level->thing_new("spell_of_holding_barrier", point(x, y));
        level->thing_new("spell_of_protection_barrier", point(x, y));
        level->thing_new("ogre_totem", point(x + 2, y + 2));
        level->thing_new("trap_dart", point(x + 2, y + 2));
        level->thing_new("zorb_totem", point(x + 2, y + 2));
        level->thing_new("sentry_orb_energy", point(x - 3, y));
        level->thing_new("crystal1", point(x, y + 1));
        level->thing_new("crystal2", point(x, y + 2));
        level->thing_new("crystal3", point(x, y + 3));
        level->thing_new("crystal4", point(x, y + 4));
        level->thing_new("crystal5", point(x, y + 5));
        level->thing_new("crystal6", point(x, y + 6));
        level->thing_new("crystal7", point(x, y + 7));
      }
      if (0) {
        auto k = level->thing_new("key", point(x, y));
        t->carry(k, carry_options);
      }
      if (1) {
        auto w = level->thing_new("sword_wood", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("warhammer", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("tentacleye", point(x + 1, y));
      }
      if (0) {
        level->thing_new("skeleton", point(x, y + 3));
        auto w = level->thing_new("sword_holy", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("sword_duck_summoning", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("dagger", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("debuff_status_necrotized", point(x, y));
        t->debuff_add(w);
      }
      if (0) {
        auto w = level->thing_new("debuff_temporary_slow", point(x, y));
        t->debuff_add(w);
      }
      if (0) {
        auto w = level->thing_new("potion_fire_immunity", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("lava", point(x + 1, y - 1));
        level->thing_new("lava", point(x + 1, y + 1));
        level->player->on_fire_set("");
      }
      if (0) {
        auto w = level->thing_new("potion_levitation", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("electric_eel", point(x + 2, y + 1));
        level->thing_new("water", point(x + 1, y));
        level->thing_new("water", point(x + 2, y));
        level->thing_new("water", point(x + 3, y));
        level->thing_new("water", point(x + 4, y));
        level->thing_new("water", point(x + 1, y + 1));
        level->thing_new("water", point(x + 2, y + 1));
        level->thing_new("water", point(x + 3, y + 1));
        level->thing_new("water", point(x + 4, y + 1));
        level->thing_new("water", point(x + 1, y + 2));
        level->thing_new("water", point(x + 2, y + 2));
        level->thing_new("water", point(x + 3, y + 2));
        level->thing_new("water", point(x + 4, y + 2));
      }
      if (0) {
        auto w = level->thing_new("potion_ooze", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("potion_descent", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("potion_immolation", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
        level->thing_new("water", point(x + 1, y));
      }
      if (0) {
        auto w = level->thing_new("potion_confusion", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("potion_telepathy", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("potion_haste", point(x, y));
        level->thing_new("dogman", point(x + 2, y));
        t->carry(w, carry_options);
      }
      if (0) {
        level->thing_new("potion_darkness", point(x + 2, y));
        auto w = level->thing_new("potion_darkness", point(x, y));
        level->thing_new("dogman", point(x + 2, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("potion_poison", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("potion_strength", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("potion_life", point(x, y));
        t->carry(w, carry_options);
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("potion_invigoration", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("potion_invisibility", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      {
        //
        // Darts
        //
        for (auto d = 0; d < 2; d++) {
          auto w = level->thing_new("dart", point(x, y));
          t->carry(w, carry_options);
        }
        if (0) {
          auto w = level->thing_new("dart_metal", point(x, y));
          t->carry(w, carry_options);
        }
        if (0) {
          auto w = level->thing_new("dart_poison", point(x, y));
          t->carry(w, carry_options);
        }
        if (0) {
          auto w = level->thing_new("dart_confusion", point(x, y));
          t->carry(w, carry_options);
          level->thing_new("dogman", point(x + 2, y));
        }
        if (0) {
          auto w = level->thing_new("dart_paralysis", point(x, y));
          t->carry(w, carry_options);
        }
      }
      if (1) {
        auto w = level->thing_new("potato", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("bacon", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("pottedmeat", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("horseshoe", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("armor_lather", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("sword_plutonium", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_holding", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("staff_protection", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("staff_poison", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x + 2, y));
      }
      if (0) {
        auto w = level->thing_new("staff_discord", point(x, y));
        t->carry(w, carry_options);
        // level->thing_new("spectral_mob", point(x + 2, y + 1));
        level->thing_new("zob_mob", point(x + 2, y - 1));
      }
      if (0) {
        auto w = level->thing_new("staff_entrancement", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("dogman", point(x - 6, y - 2));
      }
      if (0) {
        level->thing_new("trap_pressure_plate_gas4", point(x - 1, y));
        level->thing_new("brazier", point(x + 1, y));
        level->thing_new("pudding_parent", point(x, y + 1));
        level->thing_new("pudding_baby", point(x + 1, y + 1));
        // level->thing_new("trap_pressure_plate_gas3", point(x - 1, y));
        // level->thing_new("exit1", point(x - 1, y + 1));
        // level->thing_new("dogman", point(x + 2, y));
        level->thing_new("slime_parent", point(x, y + 1));
        level->thing_new("slime_baby", point(x + 1, y + 1));
        auto w = level->thing_new("staff_conjuration", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_descent", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("gauntlets_lion", point(x, y - 2));
        t->carry(w, carry_options);
        t->enchant_without_stone(w);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("buff_permanent_slime_protection", point(x, y));
        level->thing_new("slime_parent", point(x, y + 1));
        level->thing_new("slime_baby", point(x + 1, y + 1));
        t->buff_add(w);
      }
      if (0) {
        auto w = level->thing_new("buff_permanent_undead_protection", point(x, y));
        t->buff_add(w);
      }
      if (0) {
        auto w = level->thing_new("debuff_status_necrotized", point(x, y));
        t->debuff_add(w);
      }
      if (0) {
        level->thing_new("zorb_wizard", point(x - 4, y));
        level->thing_new("zorb_necro", point(x + 2, y));
        level->thing_new("zorb_pirate", point(x + 2, y + 1));
        level->thing_new("fire", point(x + 1, y - 1));
        level->thing_new("fire", point(x + 1, y + 1));
        level->thing_new("small_fire", point(x + 3, y + 3));
      }
      if (0) {
        level->thing_new("portal", point(x, y + 4));
      }
      if (0) {
        level->thing_new("dogman", point(x + 1, y));
        t->spell_add(level->thing_new("spell_of_holding", point(x, y)));
        t->spell_add(level->thing_new("spell_of_protection", point(x, y)));
        t->spell_add(level->thing_new("spell_of_repulsion", point(x, y)));
        t->spell_add(level->thing_new("spell_of_beckoning", point(x, y)));
        t->spell_add(level->thing_new("spell_of_magic_missile", point(x, y)));
        level->thing_new("barrel", point(x + 3, y - 3));
        level->thing_new("brazier", point(x + 2, y));
      }
      if (0) {
        level->thing_new("barrel", point(x + 1, y));
        level->thing_new("dogman", point(x + 2, y));
        // level->thing_new("spell_of_holding_barrier", point(x + 1, y + 1));
        // level->thing_new("spell_of_holding_barrier", point(x, y));
        auto w = level->thing_new("spell_of_holding", point(x, y));
        t->spell_add(w);
      }
      if (0) {
        level->thing_new("barrel", point(x + 1, y));
        level->thing_new("dogman", point(x + 2, y));
        // level->thing_new("spell_of_protection_barrier", point(x + 1, y + 1));
        // level->thing_new("spell_of_protection_barrier", point(x, y));
        auto w = level->thing_new("spell_of_holding", point(x, y));
        t->spell_add(w);
      }
      if (0) {
        auto w = level->thing_new("spell_of_hasted", point(x, y));
        t->spell_add(w);
      }
      if (0) {
        auto w = level->thing_new("spell_of_slowing", point(x, y));
        t->spell_add(w);
      }
      if (0) {
        auto w = level->thing_new("spell_of_summon_rock", point(x, y));
        t->spell_add(w);
      }
      if (0) {
        auto w = level->thing_new("spell_of_dominate_monst1", point(x, y));
        t->spell_add(w);
      }
      if (0) {
        level->thing_new("tentacleye", point(x + 4, y));
      }
      if (0) {
        auto w = level->thing_new("skill_iron_defense1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_power_attack1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_primal_rage1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_intimidating_strength1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_devoted_thrust1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_double_strike1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_super_health5", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_vampiric_touch5", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_healing1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        auto w = level->thing_new("skill_artful_dodging1", point(x, y));
        t->skill_add(w);
      }
      if (0) {
        level->thing_new("gold6", point(x + 1, y));
        auto w = level->thing_new("skill_gold_to_health1", point(x, y));
        t->skill_add(w);
      }

      if (0) {
        level->thing_new("trap_pressure_plate_gas3", point(x - 1, y));
        level->thing_new("trap_pressure_plate_gas2", point(x - 2, y));
        level->thing_new("trap_paralysis", point(x - 2, y));
        level->thing_new("wall_dungeon.1", point(x - 2, y + 2));
        level->thing_new("wall_dungeon.1", point(x - 1, y + 2));
        level->thing_new("wall_dungeon.1", point(x, y + 2));
        level->thing_new("wall_dungeon.1", point(x + 1, y + 2));
        level->thing_new("wall_dungeon.1", point(x + 2, y + 2));
        level->thing_new("trap_pressure_plate_gas1", point(x - 2, y));
        level->thing_new("rat_large", point(x + 1, y + 3));
        level->thing_new("trap_monster", point(x - 2, y));
      }
      if (0) {
        auto d = level->thing_new("belcher", point(x - 1, y));
        d->wake("");
      }
      if (0) {
        level->thing_new("fungus_healing", point(x + 3, y));
        level->thing_new("lava", point(x + 3, y));
      }
      if (0) {
        level->thing_new("fungus_poison_18", point(x - 1, y));
        level->thing_new("fungus_edible_1", point(x - 1, y));
        level->thing_new("fungus_withered_1", point(x + 3, y));
        level->thing_new("fungus_withered_1", point(x + 3, y + 1));
        level->thing_new("fungus_withered_1", point(x + 3, y + 2));
        level->thing_new("fungus_withered_1", point(x + 2, y));
        level->thing_new("fungus_withered_1", point(x + 2, y + 1));
        level->thing_new("fungus_withered_1", point(x + 2, y + 2));
        level->thing_new("fungus_withered_1", point(x + 1, y));
        level->thing_new("fungus_withered_1", point(x + 1, y + 1));
        level->thing_new("fungus_withered_1", point(x + 1, y + 2));
        auto f = level->thing_new("fungus_poison_1", point(x - 2, y));
        t->carry(f, carry_options);
      }
      if (0) {
        level->thing_new("dogman", point(x + 1, y + 3));
        level->thing_new("lava_ant", point(x - 2, y));
        level->thing_new("grass_wet1", point(x + 1, y));
        level->thing_new("grass_wet2", point(x + 2, y));
        level->thing_new("grass_wet4", point(x + 3, y));
        level->thing_new("grass_wet1", point(x + 1, y + 2));
        level->thing_new("grass_wet2", point(x + 2, y + 2));
        level->thing_new("grass_wet4", point(x + 3, y + 2));
        level->thing_new("grass_dry", point(x + 1, y + 1));
        level->thing_new("grass_dry", point(x + 2, y + 1));
        level->thing_new("grass_dry", point(x + 3, y + 1));
      }

      if (0) {
        auto w = level->thing_new("amulet_endurance", point(x, y - 2));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("amulet_mindseeing", point(x, y - 2));
        t->carry(w, carry_options);
      }
      if (0) {
        level->thing_new("portal", point(x - 2, y));
        level->thing_new("portable_hole", point(x - 3, y));
        auto w = level->thing_new("amulet_teleport_attack", point(x, y - 2));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_lightning", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_fire", point(x, y));
        // w->enchant_randomly();
        // w->enchant_randomly();
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_cold", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_energy", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_descent", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("pike", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("scythe", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("double_shovel", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("shovel", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto r1 = level->thing_new("ring_is_immune_to_negation", point(x, y));
        t->carry(r1, carry_options);
        auto r2 = level->thing_new("ring_is_immune_to_poison", point(x, y));
        t->carry(r2, carry_options);
      }
      if (0) {
        auto r1 = level->thing_new("ring_shield", point(x, y));
        t->carry(r1, carry_options);
      }
      if (0) {
        auto r1 = level->thing_new("shield_eagle", point(x, y));
        t->carry(r1, carry_options);
      }
      if (0) {
        auto r2 = level->thing_new("ring_is_immune_to_poison", point(x, y));
        t->carry(r2, carry_options);
      }
      if (0) {
        auto r3 = level->thing_new("ring_is_immune_to_fire", point(x, y));
        t->carry(r3, carry_options);
        auto r4 = level->thing_new("ring_is_immune_to_cold", point(x, y));
        t->carry(r4, carry_options);
      }
      if (0) {
        auto w = level->thing_new("very_broadsword", point(x + 3, y));
        w->enchant_randomly();
        // t->carry(w,carry_options);
        // t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("sword_draining", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("axe", point(x, y));
        t->carry(w, carry_options);
      }
      if (1) {
        auto w = level->thing_new("torch", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("wooden_cross", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("boots_fluffy", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("cloak_stone", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("cloak_slime", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("cloak_fire", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("cloak_protection", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("torch", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto b = level->thing_new("bag_small", point(x, y));
        t->carry(b, carry_options);
      }
      if (0) {
        level->thing_new("bag_large", point(x + 1, y));
      }
      if (0) {
        auto b = level->thing_new("enchantstone", point(x, y));
        t->carry(b, carry_options);
      }
      if (0) {
        auto b = level->thing_new("enchantstone", point(x, y));
        t->carry(b, carry_options);
      }
      if (0) {
        {
          for (auto sk = 0; sk < 1; sk++) {
            auto b = level->thing_new("skillstone", point(x, y));
            t->carry(b, carry_options);
          }
        }
      }
      if (0) {
        level->thing_new("spellbook1", point(x + 1, y));
      }
      if (0) {
        level->thing_new("spellbook2", point(x + 2, y));
      }
      if (0) {
        level->thing_new("spellbook3", point(x + 3, y));
      }
      if (0) {
        level->thing_new("spellbook4", point(x + 1, y + 1));
      }
      if (0) {
        level->thing_new("spellbook5", point(x + 1, y + 2));
      }
      if (0) {
        auto b = level->thing_new("thunderstone", point(x, y));
        t->carry(b, carry_options);
      }
      if (0) {
        auto b = level->thing_new("chest1", point(x, y));
        auto w = level->thing_new("wooden_cross", point(x, y));
        b->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_energy", point(x, y));
        t->carry(w, carry_options);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("map_treasure", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("map_beast", point(x, y));
        t->carry(w, carry_options);
      }
      if (0) {
        auto w = level->thing_new("staff_negation", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("skeleton", point(x, y + 2));
      }
      if (0) {
        auto d = level->thing_new("dogman", point(x + 2, y));
        d->wake("");
      }
      if (0) {
        level->thing_new("thylacine", point(x + 1, y + 2));
        level->thing_new("hellpup", point(x + 2, y + 2));
        level->thing_new("firefox", point(x + 3, y + 2));
        level->thing_new("exit1", point(x - 1, y + 1));
      }
      if (0) {
        level->thing_new("mimic_sleeping", point(x - 2, y + 2));
        level->thing_new("rat_large", point(x + 1, y + 3));
        level->thing_new("troll_stone", point(x + 2, y));
        level->thing_new("troll_fire", point(x + 2, y + 2));
        level->thing_new("gnome_rock", point(x + 2, y + 1));
        level->thing_new("tentacleye", point(x + 1, y + 1));
        level->thing_new("scorpion_death", point(x + 2, y + 1));
        level->thing_new("yeti", point(x + 2, y + 1));
        level->thing_new("mantisman", point(x + 2, y + 1));
        level->thing_new("iceman", point(x + 2, y + 1));
        level->thing_new("molekin", point(x + 2, y + 1));
        level->thing_new("gnome_rock", point(x + 2, y + 1));
        level->thing_new("bloodbug", point(x + 2, y + 1));
        level->thing_new("death_hornet", point(x + 2, y + 1));
        level->thing_new("bear_undead", point(x + 2, y + 1));
        level->thing_new("meatfairy", point(x + 2, y + 1));
        level->thing_new("bearowl", point(x + 2, y + 1));
        level->thing_new("carcas_creeper", point(x + 2, y + 1));
        level->thing_new("centipede", point(x - 2, y + 1));
        level->thing_new("demon_fire", point(x + 4, y));
        level->thing_new("ogre", point(x + 4, y));
        level->thing_new("ettin", point(x + 2, y));
        level->thing_new("cthulite", point(x + 2, y));
        level->thing_new("cyclops", point(x + 2, y));
        level->thing_new("gargoyle_baby", point(x + 2, y + 2));
        level->thing_new("chest1", point(x + 2, y + 2));
        level->thing_new("chest2", point(x + 3, y + 2));
        level->thing_new("scorpion_colossal", point(x + 3, y + 2));
        level->thing_new("cthulite", point(x + 3, y + 2));
        level->thing_new("blinkcat", point(x + 2, y + 1));
        level->thing_new("gnome_thief", point(x + 2, y + 1));
        level->thing_new("gnome_rock", point(x + 2, y + 1));
        level->thing_new("gnome_knight", point(x + 2, y + 1));
        level->thing_new("goat_battle", point(x + 2, y + 1));
        level->thing_new("goat_demon", point(x + 2, y + 1));
        level->thing_new("gnome_dwarf", point(x + 2, y + 1));
        level->thing_new("dogman", point(x + 1, y + 3));
        level->thing_new("golem_cement", point(x + 4, y + 2));
        level->thing_new("amulet_healing", point(x + 1, y - 3));
        level->thing_new("amulet_peeking", point(x + 2, y - 3));
        level->thing_new("amulet_endurance", point(x, y - 3));
        level->thing_new("shield_eagle", point(x, y - 2));
        level->thing_new("zorb_priest", point(x + 1, y + 3));
        level->thing_new("mummy_necro", point(x + 1, y));
        level->thing_new("reaper", point(x + 3, y));
        level->thing_new("zorb_eldster", point(x + 1, y + 3));
        level->thing_new("flameskull", point(x + 1, y + 4));
        level->thing_new("pyrolizard", point(x + 2, y + 3));
        level->thing_new("cleaner", point(x + 3, y + 1));
        level->thing_new("zorb_eldster", point(x + 3, y + 2));
        level->thing_new("snake_dreadfire", point(x + 3, y + 3));
        level->thing_new("zorb_eldster", point(x + 3, y + 4));
        // auto w = level->thing_new("staff_lightning", point(x, y));
        // auto w = level->thing_new("staff_descent", point(x, y));
        auto w1 = level->thing_new("staff_cold", point(x, y));
        t->carry(w1, carry_options);
        auto w2 = level->thing_new("staff_fire", point(x, y));
        t->carry(w2, carry_options);
        // t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("rock", point(x, y));
        t->carry(w, carry_options);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("staff_fire", point(x, y));
        t->carry(w, carry_options);
        t->enchant_without_stone(w);
      }
      if (0) {
        auto w = level->thing_new("staff_descent", point(x, y));
        t->carry(w, carry_options);
        t->enchant_without_stone(w);
      }

      if (0) {
        level->thing_new("acid1", point(x - 1, y - 2));
        level->thing_new("acid1", point(x - 1, y - 3));
        level->thing_new("ooze", point(x + 1, y));
        level->thing_new("ooze", point(x + 2, y));
        level->thing_new("ooze", point(x + 3, y));
        level->thing_new("ooze", point(x + 4, y));
        level->thing_new("ooze", point(x + 1, y + 1));
        level->thing_new("ooze", point(x + 2, y + 2));
        level->thing_new("ooze", point(x + 3, y + 3));
        level->thing_new("ooze", point(x + 4, y + 4));
        level->thing_new("ooze", point(x + 1, y - 1));
        level->thing_new("ooze", point(x + 2, y - 1));
        level->thing_new("ooze", point(x + 3, y - 1));
        level->thing_new("ooze", point(x + 4, y - 1));
        level->thing_new("ooze", point(x + 1, y - 2));
        level->thing_new("ooze", point(x + 2, y - 2));
        level->thing_new("ooze", point(x + 3, y - 2));
        level->thing_new("ooze", point(x + 4, y - 2));
      }
      if (0) {
        // level->thing_new("belcher", point(x - 1, y));
        // level->thing_new("spider_flux", point(x - 1, y - 1));
        // level->thing_new("spider_bone", point(x + 2, y + 3));
        // level->thing_new("crab_sewer", point(x + 3, y + 3));
        // level->thing_new("sheep", point(x + 1, y + 3));
        // level->thing_new("goat_battle", point(x + 2, y + 1));
        // level->thing_new("moresquito", point(x + 2, y + 3));
        // level->thing_new("fleshbee", point(x + 1, y + 3));
        // level->thing_new("narhornet", point(x + 0, y + 3));
        // level->thing_new("spider_para", point(x + 2, y + 4));
        // level->thing_new("spider_brown", point(x + 2, y + 4));
        // level->thing_new("leech_giant", point(x + 2, y));
        level->thing_new("water", point(x + 1, y));
        level->thing_new("water", point(x + 2, y));
        level->thing_new("water", point(x + 3, y));
        level->thing_new("water", point(x + 4, y));

        level->thing_new("water", point(x + 1, y + 1));
        level->thing_new("water", point(x + 2, y + 1));
        level->thing_new("water", point(x + 3, y + 1));
        level->thing_new("water", point(x + 4, y + 1));

        level->thing_new("water", point(x + 1, y + 2));
        level->thing_new("water", point(x + 2, y + 2));
        level->thing_new("water", point(x + 3, y + 2));
        level->thing_new("water", point(x + 4, y + 2));

        level->thing_new("water", point(x + 1, y + 3));
        level->thing_new("water", point(x + 2, y + 3));
        level->thing_new("water", point(x + 3, y + 3));
        level->thing_new("water", point(x + 4, y + 3));

        level->thing_new("water", point(x + 1, y + 4));
        level->thing_new("water", point(x + 2, y + 4));
        level->thing_new("water", point(x + 3, y + 4));
        level->thing_new("water", point(x + 4, y + 4));

        level->thing_new("water", point(x + 1, y + 5));
        level->thing_new("water", point(x + 2, y + 5));
        level->thing_new("water", point(x + 3, y + 5));
        level->thing_new("water", point(x + 4, y + 5));

        level->thing_new("electric_eel", point(x + 3, y + 2));
        level->thing_new("eel", point(x + 3, y + 4));
        // level->thing_new("teletoad", point(x + 3, y + 3));
        // level->thing_new("kraken", point(x + 2, y + 2));

        // level->thing_new("cleaner", point(x + 2, y - 2));
      }

      if (0) {
        level->thing_new("wall_dungeon.1", point(x, y - 2));
        level->thing_new("wall_dungeon.1", point(x - 1, y - 2));
        level->thing_new("wall_dungeon.1", point(x + 1, y - 2));
        level->thing_new("door_metal", point(x + 2, y - 2));
        level->thing_new("wall_dungeon.1", point(x + 3, y - 2));
        level->thing_new("wall_dungeon.1", point(x + 4, y - 2));
        level->thing_new("wall_dungeon.1", point(x + 4, y - 2));
        level->thing_new("key", point(x + 5, y));
        // d->dead("killed");
      }
      // level->thing_new("golem_flesh", point(x + 1, y + 3));
      if (0) {
        level->thing_new("skeleton", point(x, y + 3));
        auto h = level->thing_new("holy_water", point(x, y + 2));
        t->carry(h, carry_options);
      }
      if (0) {
        auto w = level->thing_new("potion_levitation", point(x, y));
        t->carry(w, carry_options);
        level->thing_new("demon_fire", point(x + 2, y));
        level->thing_new("lava", point(x + 1, y));
        level->thing_new("lava", point(x + 2, y));
        level->thing_new("lava", point(x + 3, y));
        level->thing_new("lava", point(x + 4, y));
        level->thing_new("lava", point(x + 1, y + 1));
        level->thing_new("lava", point(x + 2, y + 1));
        level->thing_new("lava", point(x + 3, y + 1));
        level->thing_new("lava", point(x + 4, y + 1));
        level->thing_new("lava", point(x + 1, y + 2));
        level->thing_new("lava", point(x + 2, y + 2));
        level->thing_new("lava", point(x + 3, y + 2));
        level->thing_new("lava", point(x + 4, y + 2));
      }
      IF_DEBUG2
      {
        if (0) {
          level->thing_new("staff_blinking", point(x, y + 1));
          level->thing_new("boots_teleport", point(x, y - 1));
          level->thing_new("zob_mob", point(x + 2, y + 1));
        }
        if (0) {
          level->thing_new("coffin_mob", point(x + 2, y + 1));
        }
        if (0) {
          level->thing_new("barrel", point(x + 2, y + 1));
          level->thing_new("rat_giant", point(x + 3, y + 1));
        }
        if (0) {
          level->thing_new("staff_energy", point(x, y + 1));
        }
        // level->thing_new("murder_bunny", point(x + 2, y + 2));
        // level->thing_new("jackalope", point(x + 3, y + 2));
        // level->thing_new("duck2", point(x + 3, y + 2));
        // level->thing_new("gargoyle_moving", point(x + 2, y - 5));
        // level->thing_new("rat_giant", point(x - 1, y));
        // level->thing_new("rat_giant", point(x + 1, y));
        // level->thing_new("rat_giant", point(x, y - 1));
        // level->thing_new("rock1", point(x + 1, y));
        // level->thing_new("rock1", point(x + 3, y));
        // level->thing_new("gargoyle_static", point(x + 2, y - 2));
        // level->thing_new("frog", point(x + 3, y - 1));
        // level->thing_new("fire", point(x + 1, y - 1));
        // level->thing_new("enchantstone", point(x + 1, y - 1));
        // level->thing_new("skillstone", point(x + 1, y - 1));
        // level->thing_new("horseshoe", point(x, y));
        // level->thing_new("four_leaf_clover", point(x, y));
        // level->thing_new("medal_of_valor", point(x, y));
        // level->thing_new("wooden_cross", point(x, y));
        // level->thing_new("armor_lather", point(x, y));
        // level->thing_new("boots_fluffy", point(x, y - 2));
        // level->thing_new("boots_silence", point(x, y - 2));
        // level->thing_new("mummy_necro", point(x + 5, y + 1));
        // level->thing_new("shield_woodon", point(x, y - 2));
        // level->thing_new("fire", point(x, y - 2));
        // level->thing_new("frog", point(x, y - 2));
        // level->thing_new("cleaner", point(x + 1, y + 3));
        // level->thing_new("thunderstone", point(x, y - 2));
        // level->thing_new("zorb_eldster", point(x + 5, y));
        // level->thing_new("key", point(x + 5, y));
        // level->thing_new("key_pair", point(x - 1, y - 2));
        // level->thing_new("key_golden", point(x - 1, y + 2));
        // level->thing_new("key_penta", point(x, y + 12));
        // level->thing_new("snake_viper", point(x, y + 2));
        // level->thing_new("zorb_pack", point(x + 2, y));
        // level->thing_new("mummy_pack", point(x + 2, y + 12));
        // level->thing_new("barrel", point(x - 2, y));
        // level->thing_new("floor_red_blood1", point(x + 2, y + 1));
        // level->thing_new("teleport", point(x + 2, y + 2));
        // level->thing_new("scorpion", point(x + 2, y + 2));
        level->assign_leaders_and_followers();
      }
      // level->thing_new("sentry_orb_energy", point(x - 3, y));
      if (0) {
        level->thing_new("portable_hole", point(x - 3, y));
        level->thing_new("cleaner", point(x, y));
        level->thing_new("gargoyle_static", point(x, y + 1));
      }
      if (0) {
        level->thing_new("foliage", point(x, y + 1));
        level->thing_new("mummy", point(x - 1, y + 1));
      }
      // level->thing_new("pyrolizard", point(x - 2, y + 1));
      // level->thing_new("vampire_rose", point(x - 2, y + 1));
      // level->thing_new("blob", point(x - 2, y + 1));
      if (0) {
        auto d = level->thing_new("belcher", point(x - 3, y + 1));
        d->wake("");
      }
      // level->thing_new("cleaner", point(x - 3, y + 2));
      if (0) {
        auto d = level->thing_new("dogman", point(x + 1, y + 2));
        d->wake("");
        d->is_burnt = true;
        d->dead("x");
      }
      if (0) {
        level->thing_new("fire", point(x + 1, y));
        level->thing_new("door_wood", point(x + 1, y));
        level->thing_new("lava", point(x + 2, y + 1));
        level->thing_new("block_of_ice", point(x + 2, y + 1));
      }
      // level->thing_new("vampire_rose_stem", point(x, y + 1));
      // level->thing_new("fire", point(x - 4, y + 5));
      // level->thing_new("foliage", point(x - 4, y + 5));
      // level->thing_new("foliage", point(x, y + 5));
      // level->thing_new("block_of_ice", point(x, y + 1));
      // level->thing_new("block_of_ice", point(x, y + 2));
      if (0) {
        level->thing_new("vampire_rose_stem1", point(x - 1, y + 2));
        level->thing_new("vampire_rose_stem2", point(x + 1, y + 2));
        level->thing_new("vampire_rose_stem1", point(x - 1, y + 1));
        level->thing_new("vampire_rose_stem2", point(x + 1, y + 1));
        level->thing_new("vampire_rose_stem1", point(x, y + 1));
        level->thing_new("vampire_rose_stem2", point(x - 1, y + 3));
        level->thing_new("vampire_rose_stem1", point(x + 1, y + 3));
        level->thing_new("vampire_rose_stem2", point(x, y + 3));
        level->thing_new("vampire_rose_stem1", point(x - 1, y + 4));
        level->thing_new("vampire_rose_stem2", point(x + 1, y + 4));
        level->thing_new("vampire_rose_stem1", point(x, y + 4));
      }
      if (0) {
        level->thing_new("slime_parent", point(x, y + 4));
        level->thing_new("slime_baby", point(x, y + 4));
      }
      if (0) {
        auto d = level->thing_new("dogman", point(x + 1, y + 2));
        d->dead("x");
      }

      // level->thing_new("staff_descent", point(x + 5, y + 2));
      // level->thing_new("fire", point(x + 5, y + 2));
      // level->thing_new("spiderweb", point(x, y));
      // level->thing_new("spider_onyx_widow", point(x + 2, y));
      // level->thing_new("spider_giant", point(x + 2, y));
      if (0) {
        level->thing_new("bat_lesser", point(x + 2, y + 1));
      }
      // level->thing_new("golem_flesh", point(x, y + 3));
      // level->thing_new("lava", point(x, y + 5));
      // level->thing_new("lava", point(x, y + 6));
      // level->thing_new("lava", point(x, y + 7));
      // level->thing_new("lava", point(x + 1, y + 5));
      // level->thing_new("lava", point(x + 1, y + 6));
      // level->thing_new("lava", point(x + 1, y + 7));
      // level->thing_new("lava", point(x + 1, y + 7));
      //
      if (0) {
        auto m = level->thing_new("coffin_mob", point(x, y + 4));
        m->frozen_set();
      }
      // level->thing_new("flameskull", point(x, y + 4));

      if (0) {
        auto m = level->thing_new("slime_parent", point(x, y + 4));
        m->frozen_set();
      }
      // level->thing_new("slime_baby", point(x, y + 2));
      //
      // Zoom the map to the player
      //
      level->scroll_map_to_player();

      DBG("INF: Placed player");

      goto done;
    }
  }

done:
  level->ts_fade_in_begin = time_ms_cached();
  level->ts_redraw_bg     = 1; // Force redraw

  auto player = level->player;
  if (player) {
    level->request_player_light_update = true;
    game->player_is_ready_for_messages = true;
    IF_DEBUG { player->log("Placed"); }
  }
}
