//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_thing_template.hpp"
#include "my_ui.hpp"

void tp_fixup(void)
{
  TRACE_NO_INDENT();

  for (auto &tp : tp_id_map) {
    if (tp->stamina()) {
      tp->is_able_to_tire_set(true);
    }

    if (tp->is_monst() || tp->is_monst_pack()) {
      tp->is_tickable_set(true);
    }

    if (tp->is_item()) {
      if (! tp->is_collected_as_keys() && ! tp->is_collected_as_gold()) {
        if (tp->text_short_name().size() > UI_LEFTBAR_WIDTH) {
          DIE("Tp %s short name is too long and will be truncated (max %d)?", tp->name().c_str(), UI_LEFTBAR_WIDTH);
        }
      }
    }

    if (tp->is_shallow_water_swimmer()) {
      tp->is_swimmer_set(true);
    }

    if (tp->is_deep_water_swimmer()) {
      tp->is_swimmer_set(true);
    }

    if (tp->is_tickable()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_able_to_melt()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_able_to_burn()) {
      tp->is_interesting_set(true);
    }

    if (tp->temperature_sensitive()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_ethereal()) {
      tp->is_immune_to_spiderwebs_set(true);
    }

    if (tp->is_undead()) {
      tp->is_immune_to_necrosis_set(true);
      tp->is_immune_to_draining_set(true);
    }

    if (! tp->on_tick_do().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has on tick action but is not tickable?", tp->name().c_str());
      }
    }

    if (! tp->on_idle_tick_freq_dice_str().empty()) {
      if (! tp->is_tickable()) {
        DIE("Tp %s has idle tick action but is not tickable?", tp->name().c_str());
      }
    }

    if (tp->is_very_combustible()) {
      tp->is_combustible_set(true);
    }

    if (tp->is_very_hard()) {
      tp->is_hard_set(true);
    }

    if (tp->is_very_heavy()) {
      tp->is_heavy_set(true);
    }

    if (tp->is_able_to_burn() || tp->is_combustible() || tp->is_very_combustible()) {
      tp->temperature_sensitive_set(true);
    }

    if (tp->is_able_to_freeze()) {
      tp->temperature_sensitive_set(true);
    }

    if (tp->is_able_to_shove_chance_d1000()) {
      tp->is_able_to_shove_set(true);
    }

    if (tp->is_able_to_grapple_chance_d1000()) {
      tp->is_able_to_grapple_set(true);
    }

    if (tp->is_able_to_melt()) {
      tp->temperature_sensitive_set(true);
      if (! tp->melting_chance_d1000()) {
        DIE("Tp %s needs melting chance set as it can melt", tp->name().c_str());
      }
    }

    if (tp->is_stone()) {
      tp->temperature_sensitive_to_sudden_changes_set(true);
    }

    if (tp->is_poisonous_danger_level()) {
      if (tp->damage_poison_dice_str().empty()) {
        DIE("Tp %s needs a poison danger level set?", tp->name().c_str());
      }
    }

    if (tp->is_flying()) {
      if (tp->is_shovable()) {
        DIE("Tp %s a flying thing that can be shoved, are you sure?", tp->name().c_str());
      }
    }

    if (tp->is_wooden()) {
      if (! tp->is_able_to_burn()) {
        DIE("Tp %s needs to be set as burnable if wooden", tp->name().c_str());
      }
    }

    if (tp->is_able_to_fire_at()) {
      if (! tp->distance_vision()) {
        DIE("Tp %s needs vision distance if it is able to fire at things", tp->name().c_str());
      }
    }

    if (tp->is_interesting()) {
      if (tp->is_tmp_thing()) {
        DIE("Tp %s cannot be both interesting and temporary", tp->name().c_str());
      }
    }

    if (tp->is_floor()) {
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

    if (tp->is_monst() || tp->is_player()) {
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
    }

    //
    // If only a single attack type then make sure it is 1000%
    //
    int num_attack_types = 0;

    num_attack_types += tp->damage_melee() ? 1 : 0;
    num_attack_types += tp->damage_nat_att() ? 1 : 0;
    num_attack_types += tp->damage_poison() ? 1 : 0;
    num_attack_types += tp->damage_drown() ? 1 : 0;
    num_attack_types += tp->damage_bite() ? 1 : 0;
    num_attack_types += tp->damage_claw() ? 1 : 0;
    num_attack_types += tp->damage_cold() ? 1 : 0;
    num_attack_types += tp->damage_fire() ? 1 : 0;
    num_attack_types += tp->damage_crush() ? 1 : 0;
    num_attack_types += tp->damage_lightning() ? 1 : 0;
    num_attack_types += tp->damage_energy() ? 1 : 0;
    num_attack_types += tp->damage_acid() ? 1 : 0;
    num_attack_types += tp->damage_water() ? 1 : 0;
    num_attack_types += tp->damage_digest() ? 1 : 0;
    num_attack_types += tp->damage_necrosis() ? 1 : 0;
    num_attack_types += tp->damage_draining() ? 1 : 0;

    //
    // If only a single attack type then make sure it is 1000%
    //
    if (tp->attacks_per_round() <= 1) {
      if (num_attack_types == 1) {
        int attack_index = 0;

        if (tp->damage_acid() > 0) {
          tp->damage_acid_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_water() > 0) {
          tp->damage_water_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_nat_att() > 0) {
          tp->damage_nat_att_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_crush() > 0) {
          tp->damage_crush_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_digest() > 0) {
          tp->damage_digest_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_energy() > 0) {
          tp->damage_energy_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_fire() > 0) {
          tp->damage_fire_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_drown() > 0) {
          tp->damage_drown_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_bite() > 0) {
          tp->damage_bite_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_claw() > 0) {
          tp->damage_claw_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_cold() > 0) {
          tp->damage_cold_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_lightning() > 0) {
          tp->damage_lightning_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_melee() > 0) {
          tp->damage_melee_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_necrosis() > 0) {
          tp->damage_necrosis_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_draining() > 0) {
          tp->damage_draining_chance_d1000_set(attack_index, 1000);
        }
        if (tp->damage_poison() > 0) {
          tp->damage_poison_chance_d1000_set(attack_index, 1000);
        }
      }
    }

    if ((num_attack_types > 0) && ! tp->attacks_per_round()) {
      tp->attacks_per_round_set(1);
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
      auto tp2 = tp_find(ally);
      if (! tp2) {
        DIE("Tp %s ally not found: %s", tp->name().c_str(), ally.c_str());
      }
      tp->allies.insert(tp2);
    }
  }
}
