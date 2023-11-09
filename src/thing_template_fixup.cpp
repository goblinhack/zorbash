//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_string.hpp"
#include "my_template.hpp"
#include "my_ui.hpp"

void tp_fixup(void)
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_id_map) {

    if (tp->thing_size() == THING_SIZE_NOT_SET) {
      tp->thing_size_set(THING_SIZE_NORMAL);
    }

    if (tp->is_living()) {
      if (tp->is_lifeless()) {
        DIE("Tp %s is living and lifeless?", tp->name().c_str());
      }
    }

    if (tp->is_able_to_freeze()) {
      if (tp->is_fire()) {
        DIE("Tp %s is fire and can freeze?", tp->name().c_str());
      }
    }

    if (tp->stamina()) {
      tp->is_able_to_tire_set(true);
    }

    if (tp->is_able_to_tire()) {
      if (tp->is_tireless()) {
        DIE("Tp %s is tireless and can tire? or has stamina set", tp->name().c_str());
      }
    }

    if (tp->is_fearless()) {
      if (tp->is_cautious()) {
        DIE("Tp %s is fearless and cautious?", tp->name().c_str());
      }
    }

    if (tp->is_fearless()) {
      if (tp->is_daring()) {
        DIE("Tp %s is fearless and daring?", tp->name().c_str());
      }
    }

    if (tp->is_item_collector()) {
      if (! tp->capacity_height() || ! tp->capacity_width()) {
        DIE("Tp %s needs bag capacity", tp->name().c_str());
      }
    }

    if (tp->is_enchantable()) {
      if (tp->text_description_enchant().empty()) {
        DIE("Tp %s needs enchant description", tp->name().c_str());
      }
    }

    if (tp->is_monst() || tp->is_monst_pack()) {
      tp->is_tickable_set(true);
    }

    if (tp->is_item()) {
      if (! tp->is_collected_as_keys() && ! tp->is_collected_as_gold()) {
        if (tp->text_short_name().size() > UI_LEFTBAR_WIDTH) {
          DIE("Tp %s short name [%s] long name [%s] is too long and will be truncated (max %d)?", tp->name().c_str(),
              tp->text_short_name().c_str(), tp->text_long_name().c_str(), UI_LEFTBAR_WIDTH);
        }
      }
    }

    if (tp->is_described_in_leftbar()) {
      if (tp->text_short_name().size() > UI_LEFTBAR_WIDTH) {
        DIE("Tp %s short name [%s] long name [%s] is too long and will be truncated (max %d)?", tp->name().c_str(),
            tp->text_short_name().c_str(), tp->text_long_name().c_str(), UI_LEFTBAR_WIDTH);
      }
    }

    if (tp->environ_likes_shallow_water()) {
      tp->is_swimmer_set(true);
    }

    if (tp->environ_likes_deep_water()) {
      tp->is_swimmer_set(true);
    }

    if (tp->is_tickable()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_able_to_melt()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_burnable()) {
      tp->is_interesting_set(true);
    }

    if (tp->temperature_sensitive()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_able_to_teleport_escape() || tp->is_able_to_teleport_self()
        || tp->is_able_to_teleport_without_tiring()) {
      tp->is_immune_to_cold_set(true);
    }

    if (tp->is_ethereal()) {
      if (tp->is_air_breather()) {
        DIE("Tp %s is ethereal set and breathes air?", tp->name().c_str());
      }
      if (tp->is_crushable()) {
        DIE("Tp %s is ethereal and crushable?", tp->name().c_str());
      }

      tp->is_immune_to_paralysis_set(true);
      tp->is_immune_to_blinding_set(true);
      tp->is_immune_to_poison_set(true);
      tp->is_immune_to_spiderwebs_set(true);
      tp->is_immune_to_necrosis_set(true);
      tp->is_immune_to_stamina_drain_set(true);
      tp->is_immune_to_fire_set(true);
      tp->is_immune_to_cold_set(true);
      tp->temperature_never_changes_set(true);
    }

    if (tp->environ_hates_acid()) {
      tp->environ_dislikes_acid_set(true);
    }

    if (tp->environ_hates_cold()) {
      if (tp->is_biome_ice()) {
        DIE("Tp %s hates water and is in biome ice?", tp->name().c_str());
      }
      tp->environ_dislikes_cold_set(true);
    }

    if (tp->environ_hates_fire()) {
      if (tp->is_biome_lava()) {
        DIE("Tp %s hates water and is in biome lava?", tp->name().c_str());
      }
      tp->environ_dislikes_fire_set(true);
    }

    if (tp->environ_hates_necrosis()) {
      tp->environ_dislikes_necrosis_set(true);
    }

    if (tp->environ_hates_poison()) {
      tp->environ_dislikes_poison_set(true);
    }

    if (tp->environ_hates_water()) {
      if (tp->is_biome_flooded()) {
        DIE("Tp %s hates water and is in biome flooded?", tp->name().c_str());
      }
      tp->environ_dislikes_water_set(true);
    }

    if (tp->is_fire_elemental()) {
      if (tp->environ_hates_fire()) {
        DIE("Tp %s hates fire and is a cold elemental ?", tp->name().c_str());
      }
      tp->is_immune_to_fire_set(true);
      tp->dmg_rcv_doubled_from_cold_set(true);
    }

    if (tp->is_cold_elemental()) {
      if (tp->environ_hates_cold()) {
        DIE("Tp %s hates cold and is a cold elemental ?", tp->name().c_str());
      }
      tp->is_immune_to_cold_set(true);
      tp->dmg_rcv_doubled_from_fire_set(true);
    }

    if (tp->is_undead()) {
      if (tp->is_air_breather()) {
        DIE("Tp %s has undead set and breathes air?", tp->name().c_str());
      }

      tp->is_immune_to_poison_set(true);
      tp->is_immune_to_necrosis_set(true);
      tp->is_immune_to_stamina_drain_set(true);
      tp->is_immune_to_cold_set(true);
      tp->dmg_rcv_doubled_from_fire_set(true);
    }

    if (! tp->on_tick_do().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has on tick action but is not tickable?", tp->name().c_str());
      }
    }

    if (! tp->on_tick_when_deactivated_do().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has on tick_when_deactivated action but is not tickable?", tp->name().c_str());
      }
    }

    if (! tp->on_tick_when_activated_do().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has on tick_when_activated action but is not tickable?", tp->name().c_str());
      }
    }

    if (! tp->on_idle_tick_freq_dice_str().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has idle tick action but is not tickable?", tp->name().c_str());
      }
    }

    if (! tp->resurrect_dice_str().empty()) {
      if (! tp->is_able_to_be_resurrected()) {
        DIE("Tp %s has resurrect diced but is not resurrectable?", tp->name().c_str());
      }
    }

    if (! tp->on_want_to_shoot_at_do().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has shoot at action but is not tickable?", tp->name().c_str());
      }
      tp->is_able_to_shoot_at_set(true);
    }

    if (tp->is_very_combustible()) {
      tp->is_combustible_set(true);
    }

    if (tp->is_obsidian()) {
      tp->is_very_hard_set(true);
    }

    if (tp->is_metal()) {
      tp->is_hard_set(true);
    }

    if (tp->is_very_hard()) {
      tp->is_hard_set(true);
    }

    if (tp->is_very_heavy()) {
      tp->is_heavy_set(true);
    }

    if (tp->is_very_intelligent()) {
      tp->is_intelligent_set(true);
    }

    if (tp->is_burnable() || tp->is_combustible() || tp->is_very_combustible()) {
      tp->is_tickable_set(true);
      tp->temperature_sensitive_set(true);
    }

    if (tp->is_able_to_freeze()) {
      tp->is_tickable_set(true);
      tp->temperature_sensitive_set(true);
    }

    if (tp->chance_d1000_shove()) {
      tp->is_able_to_shove_set(true);
    }

    if (tp->chance_d1000_tameable()) {
      tp->is_tameable_set(true);
    }

    if (tp->chance_d10000_runic_class_A()) {
      tp->is_able_to_have_a_runic_inscribed_set(true);
    }

    if (tp->chance_d10000_runic_class_B()) {
      tp->is_able_to_have_a_runic_inscribed_set(true);
    }

    if (tp->chance_d1000_shooting()) {
      tp->is_able_to_shoot_at_set(true);
    }

    if (tp->chance_d1000_shooting_avoid_friends()) {
      tp->is_able_to_shoot_at_set(true);
    }

    if (tp->chance_d1000_jump_attack()) {
      tp->is_able_to_jump_set(true);
    }

    if (tp->chance_d1000_jump_on_low_hp()) {
      tp->is_able_to_jump_set(true);
    }

    if (tp->chance_d1000_jump_onto()) {
      tp->is_able_to_jump_set(true);
    }

    if (tp->chance_d1000_jump_randomly()) {
      tp->is_able_to_jump_set(true);
    }

    if (tp->chance_d1000_steal_item() && ! tp->is_thief()) {
      DIE("Tp %s needs is_thief set", tp->name().c_str());
    }

    if (tp->is_able_to_melt()) {
      tp->is_tickable_set(true);
      tp->temperature_sensitive_set(true);
      if (! tp->chance_d1000_melting()) {
        DIE("Tp %s needs melting chance set as it can melt", tp->name().c_str());
      }
    }

    if (tp->temperature_sensitive()) {
      if (! tp->initial_temperature_is_set()) {
        tp->temperature_set(TEMPERATURE_ROOM);
      }
    }

    if (tp->chance_d1000_grapple()) {
      tp->is_able_to_grapple_set(true);
    }

    if (tp->is_stone()) {
      tp->temperature_sensitive_to_sudden_changes_set(true);
    }

    if (tp->is_poisonous_danger_level()) {
      if (tp->dmg_poison_dice_str().empty()) {
        DIE("Tp %s needs a poison danger level set?", tp->name().c_str());
      }
    }

    if (tp->is_flying()) {
      if (tp->is_shovable()) {
        DIE("Tp %s a flying thing that can be shoved, are you sure?", tp->name().c_str());
      }
    }

    if (tp->is_wooden()) {
      if (! tp->is_burnable()) {
        DIE("Tp %s needs to be set as is_burnable if wooden", tp->name().c_str());
      }
    }

    if (tp->is_able_to_shoot_at()) {
      if (! tp->distance_vision()) {
        DIE("Tp %s needs vision distance if it is able to shoot at things", tp->name().c_str());
      }
    }

    if (tp->is_able_to_use_ranged_weapons()) {
      if (! tp->distance_throw()) {
        DIE("Tp %s needs vision distance_throw if it is_able_to_use_ranged_weapons", tp->name().c_str());
      }
    }

    if (tp->is_able_to_spell_cast()) {
      if (! tp->distance_spell_cast()) {
        DIE("Tp %s needs vision distance_spell_cast if it is_able_to_spell_cast", tp->name().c_str());
      }
    }

    if (tp->is_interesting()) {
      if (tp->is_tmp_thing()) {
        DIE("Tp %s cannot be both interesting and temporary", tp->name().c_str());
      }
    }

    if (tp->is_floor() || tp->is_corridor()) {
      if (tp->is_interesting()) {
        DIE("Tp %s interesting floor?", tp->name().c_str());
      }
    }

    if (tp->is_monst()) {
      if (! tp->collision_hit_priority()) {
        DIE("Tp %s is a monst that cannot be hit?", tp->name().c_str());
      }

      tp->hunger_is_hunger_level_hungry_at_pct_set(50);
      tp->hunger_is_hunger_level_starving_at_pct_set(10);
    }

    if (tp->is_skill() || tp->is_spell() || tp->is_buff() || tp->is_debuff() || tp->is_item() || tp->is_monst()
        || tp->is_player()) {
      if (! tp->stat_att()) {
        tp->stat_att_set(10);
      }
      if (! tp->stat_str()) {
        tp->stat_str_set(10);
      }
      if (! tp->stat_def()) {
        tp->stat_def_set(10);
      }
      if (! tp->stat_con()) {
        tp->stat_con_set(10);
      }
      if (! tp->stat_dex()) {
        tp->stat_dex_set(10);
      }
      if (! tp->stat_luck()) {
        tp->stat_luck_set(10);
      }
      if (! tp->stat_thv()) {
        tp->stat_thv_set(10);
      }
      if (! tp->stat_psi()) {
        tp->stat_psi_set(10);
      }
      if (! tp->stat_int()) {
        tp->stat_int_set(10);
      }
    }

    //
    // If only a single attack type then make sure it is 1000%
    //
    int num_attack_types = 0;

    num_attack_types += tp->dmg_melee() ? 1 : 0;
    num_attack_types += tp->dmg_nat_att() ? 1 : 0;
    num_attack_types += tp->dmg_poison() ? 1 : 0;
    num_attack_types += tp->dmg_drown() ? 1 : 0;
    num_attack_types += tp->dmg_bite() ? 1 : 0;
    num_attack_types += tp->dmg_claw() ? 1 : 0;
    num_attack_types += tp->dmg_cold() ? 1 : 0;
    num_attack_types += tp->dmg_fire() ? 1 : 0;
    num_attack_types += tp->dmg_heat() ? 1 : 0;
    num_attack_types += tp->dmg_crush() ? 1 : 0;
    num_attack_types += tp->dmg_impact() ? 1 : 0;
    num_attack_types += tp->dmg_missile() ? 1 : 0;
    num_attack_types += tp->dmg_lightning() ? 1 : 0;
    num_attack_types += tp->dmg_energy() ? 1 : 0;
    num_attack_types += tp->dmg_negation() ? 1 : 0;
    num_attack_types += tp->dmg_acid() ? 1 : 0;
    num_attack_types += tp->dmg_water() ? 1 : 0;
    num_attack_types += tp->dmg_digest() ? 1 : 0;
    num_attack_types += tp->dmg_necrosis() ? 1 : 0;
    num_attack_types += tp->dmg_stamina() ? 1 : 0;
    num_attack_types += tp->dmg_magic_drain() ? 1 : 0;
    num_attack_types += tp->dmg_holy() ? 1 : 0;

    //
    // If only a single attack type then make sure it is 1000%
    //
    if (tp->dmg_num_of_attacks() <= 1) {
      if (num_attack_types == 1) {
        int attack_index = 0;

        if (tp->dmg_acid() > 0) {
          tp->dmg_chance_d1000_acid_set(attack_index, 1000);
        }
        if (tp->dmg_water() > 0) {
          tp->dmg_chance_d1000_water_set(attack_index, 1000);
        }
        if (tp->dmg_nat_att() > 0) {
          tp->dmg_chance_d1000_nat_att_set(attack_index, 1000);
        }
        if (tp->dmg_crush() > 0) {
          tp->dmg_chance_d1000_crush_set(attack_index, 1000);
        }
        if (tp->dmg_impact() > 0) {
          tp->dmg_chance_d1000_impact_set(attack_index, 1000);
        }
        if (tp->dmg_missile() > 0) {
          tp->dmg_chance_d1000_missile_set(attack_index, 1000);
        }
        if (tp->dmg_digest() > 0) {
          tp->dmg_chance_d1000_digest_set(attack_index, 1000);
        }
        if (tp->dmg_energy() > 0) {
          tp->dmg_chance_d1000_energy_set(attack_index, 1000);
        }
        if (tp->dmg_negation() > 0) {
          tp->dmg_chance_d1000_negation_set(attack_index, 1000);
        }
        if (tp->dmg_fire() > 0) {
          tp->dmg_chance_d1000_fire_set(attack_index, 1000);
        }
        if (tp->dmg_heat() > 0) {
          tp->dmg_chance_d1000_heat_set(attack_index, 1000);
        }
        if (tp->dmg_drown() > 0) {
          tp->dmg_chance_d1000_drown_set(attack_index, 1000);
        }
        if (tp->dmg_bite() > 0) {
          tp->dmg_chance_d1000_bite_set(attack_index, 1000);
        }
        if (tp->dmg_claw() > 0) {
          tp->dmg_chance_d1000_claw_set(attack_index, 1000);
        }
        if (tp->dmg_cold() > 0) {
          tp->dmg_chance_d1000_cold_set(attack_index, 1000);
        }
        if (tp->dmg_lightning() > 0) {
          tp->dmg_chance_d1000_lightning_set(attack_index, 1000);
        }
        if (tp->dmg_melee() > 0) {
          tp->dmg_chance_d1000_melee_set(attack_index, 1000);
        }
        if (tp->dmg_necrosis() > 0) {
          tp->dmg_chance_d1000_necrosis_set(attack_index, 1000);
        }
        if (tp->dmg_stamina() > 0) {
          tp->dmg_chance_d1000_stamina_drain_set(attack_index, 1000);
        }
        if (tp->dmg_magic_drain() > 0) {
          tp->dmg_chance_d1000_magic_drain_set(attack_index, 1000);
        }
        if (tp->dmg_holy() > 0) {
          tp->dmg_chance_d1000_holy_set(attack_index, 1000);
        }
        if (tp->dmg_poison() > 0) {
          tp->dmg_chance_d1000_poison_set(attack_index, 1000);
        }
      }
    }

    //
    // Check some damage has been set if we have multiple attacks
    //
    if (tp->is_monst() || tp->is_weapon() || tp->is_staff()) {
      for (auto i = 0; i < tp->dmg_num_of_attacks(); i++) {
        auto total_damange_for_this_attack_round
            = tp->dmg_chance_d1000_acid(i) + tp->dmg_chance_d1000_water(i) + tp->dmg_chance_d1000_cold(i)
            + tp->dmg_chance_d1000_crush(i) + tp->dmg_chance_d1000_impact(i) + tp->dmg_chance_d1000_missile(i)
            + tp->dmg_chance_d1000_digest(i) + tp->dmg_chance_d1000_energy(i) + tp->dmg_chance_d1000_negation(i)
            + tp->dmg_chance_d1000_fire(i) + tp->dmg_chance_d1000_heat(i) + tp->dmg_chance_d1000_drown(i)
            + tp->dmg_chance_d1000_bite(i) + tp->dmg_chance_d1000_claw(i) + tp->dmg_chance_d1000_lightning(i)
            + tp->dmg_chance_d1000_melee(i) + tp->dmg_chance_d1000_nat_att(i) + tp->dmg_chance_d1000_necrosis(i)
            + tp->dmg_chance_d1000_stamina_drain(i) + tp->dmg_chance_d1000_magic_drain(i)
            + tp->dmg_chance_d1000_holy(i) + tp->dmg_chance_d1000_poison(i);

        if (! total_damange_for_this_attack_round) {
          DIE("Thing template [%s] has no damage set for att # %d", tp->name().c_str(), i);
        }
      }
    }

    if ((num_attack_types > 0) && ! tp->dmg_num_of_attacks()) {
      tp->dmg_num_of_attacks_set(1);
    }
  }

  for (auto &tp : tp_name_map) {
    auto tpp = tp.second;
    if (! tpp->lifespan_dice_str().empty()) {
      if (! tpp->is_tickable()) {
        DIE("Thing template must be set to be is_tickable [%s] for lifespan tick to work", tp.first.c_str());
      }
    }
  }
}

void tp_assign_allies(void)
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_id_map) {
    auto allies = tp->is_allied_with();
    for (auto ally : split_tokens(allies, ',')) {
      auto tp_cands = tp_find_wildcard(ally);
      if (! tp_cands.size()) {
        DIE("Tp no %s ally not found: %s", tp->name().c_str(), ally.c_str());
      }
      auto tp2 = pcg_one_of(tp_cands);
      if (! tp2) {
        DIE("Tp %s ally not found: %s", tp->name().c_str(), ally.c_str());
      }
      tp->allies.insert(tp2);
    }
  }
}
