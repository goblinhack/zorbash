//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_random.hpp"
#include "my_string.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

void tp_fixup(void)
{
  TRACE_AND_INDENT();
  for (auto &tp : tp_id_map) {
    if (tp->stamina()) {
      tp->is_able_to_tire_set(true);
    }

    if (tp->is_tickable()) {
      tp->is_interesting_set(true);
    }

    if (tp->is_very_combustible()) {
      tp->is_combustible_set(true);
    }

    if (tp->is_very_heavy()) {
      tp->is_heavy_set(true);
    }

    if (tp->is_stone()) {
      tp->temperature_change_sensitive_set(true);
    }

    if (tp->is_flying()) {
      if (tp->is_shovable()) {
        DIE("Tp %s a flying thing that can be shoved, are you sure?", tp->name().c_str());
      }
    }

    if (tp->is_wooden()) {
      if (! tp->is_burnable()) {
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
    }

    if (tp->is_buff() || tp->is_debuff() || tp->is_skill() || tp->is_monst() || tp->is_item() || tp->is_player()) {
      if (! tp->stat_str_get()) {
        tp->stat_str_set(10);
      }
      if (! tp->stat_def_get()) {
        tp->stat_def_set(10);
      }
      if (! tp->stat_con_get()) {
        tp->stat_con_set(10);
      }
      if (! tp->stat_dex_get()) {
        tp->stat_dex_set(10);
      }
      if (! tp->stat_luck_get()) {
        tp->stat_luck_set(10);
      }
    }

    //
    // If only a single attack type then make sure it is 1000%
    //
    int num_attack_types = 0;

    num_attack_types += tp->damage_melee_get() ? 1 : 0;
    num_attack_types += tp->damage_natural_attack_get() ? 1 : 0;
    num_attack_types += tp->damage_poison_get() ? 1 : 0;
    num_attack_types += tp->damage_future1_get() ? 1 : 0;
    num_attack_types += tp->damage_future2_get() ? 1 : 0;
    num_attack_types += tp->damage_future3_get() ? 1 : 0;
    num_attack_types += tp->damage_cold_get() ? 1 : 0;
    num_attack_types += tp->damage_fire_get() ? 1 : 0;
    num_attack_types += tp->damage_crush_get() ? 1 : 0;
    num_attack_types += tp->damage_lightning_get() ? 1 : 0;
    num_attack_types += tp->damage_energy_get() ? 1 : 0;
    num_attack_types += tp->damage_acid_get() ? 1 : 0;
    num_attack_types += tp->damage_digest_get() ? 1 : 0;
    num_attack_types += tp->damage_necrosis_get() ? 1 : 0;

    if (num_attack_types == 1) {
      if (tp->damage_acid_get() > 0) {
        tp->damage_acid_chance_d1000_set(1000);
      }
      if (tp->damage_natural_attack_get() > 0) {
        tp->damage_natural_attack_chance_d1000_set(1000);
      }
      if (tp->damage_crush_get() > 0) {
        tp->damage_crush_chance_d1000_set(1000);
      }
      if (tp->damage_digest_get() > 0) {
        tp->damage_digest_chance_d1000_set(1000);
      }
      if (tp->damage_energy_get() > 0) {
        tp->damage_energy_chance_d1000_set(1000);
      }
      if (tp->damage_fire_get() > 0) {
        tp->damage_fire_chance_d1000_set(1000);
      }
      if (tp->damage_future1_get() > 0) {
        tp->damage_future1_chance_d1000_set(1000);
      }
      if (tp->damage_future2_get() > 0) {
        tp->damage_future2_chance_d1000_set(1000);
      }
      if (tp->damage_future3_get() > 0) {
        tp->damage_future3_chance_d1000_set(1000);
      }
      if (tp->damage_cold_get() > 0) {
        tp->damage_cold_chance_d1000_set(1000);
      }
      if (tp->damage_lightning_get() > 0) {
        tp->damage_lightning_chance_d1000_set(1000);
      }
      if (tp->damage_melee_get() > 0) {
        tp->damage_melee_chance_d1000_set(1000);
      }
      if (tp->damage_necrosis_get() > 0) {
        tp->damage_necrosis_chance_d1000_set(1000);
      }
      if (tp->damage_poison_get() > 0) {
        tp->damage_poison_chance_d1000_set(1000);
      }
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
  TRACE_AND_INDENT();
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
