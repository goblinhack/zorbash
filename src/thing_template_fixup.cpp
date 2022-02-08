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
      tp->set_is_able_to_tire(true);
    }

    if (tp->is_tickable()) {
      tp->set_is_interesting(true);
    }

    if (tp->is_very_combustible()) {
      tp->set_is_combustible(true);
    }

    if (tp->is_very_heavy()) {
      tp->set_is_heavy(true);
    }

    if (tp->is_stone()) {
      tp->set_is_temperature_change_sensitive(true);
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
      if (! tp->get_stat_str()) {
        tp->set_stat_str(10);
      }
      if (! tp->get_stat_def()) {
        tp->set_stat_def(10);
      }
      if (! tp->get_stat_con()) {
        tp->set_stat_con(10);
      }
      if (! tp->get_stat_dex()) {
        tp->set_stat_dex(10);
      }
    }

    //
    // If only a single attack type then make sure it is 1000%
    //
    int num_attack_types = 0;

    num_attack_types += tp->get_damage_melee() ? 1 : 0;
    num_attack_types += tp->get_damage_natural_attack() ? 1 : 0;
    num_attack_types += tp->get_damage_poison() ? 1 : 0;
    num_attack_types += tp->get_damage_future1() ? 1 : 0;
    num_attack_types += tp->get_damage_future2() ? 1 : 0;
    num_attack_types += tp->get_damage_future3() ? 1 : 0;
    num_attack_types += tp->get_damage_cold() ? 1 : 0;
    num_attack_types += tp->get_damage_fire() ? 1 : 0;
    num_attack_types += tp->get_damage_crush() ? 1 : 0;
    num_attack_types += tp->get_damage_lightning() ? 1 : 0;
    num_attack_types += tp->get_damage_energy() ? 1 : 0;
    num_attack_types += tp->get_damage_acid() ? 1 : 0;
    num_attack_types += tp->get_damage_digest() ? 1 : 0;
    num_attack_types += tp->get_damage_necrosis() ? 1 : 0;

    if (num_attack_types == 1) {
      if (tp->get_damage_acid() > 0) {
        tp->set_damage_acid_chance_d1000(1000);
      }
      if (tp->get_damage_natural_attack() > 0) {
        tp->set_damage_natural_attack_chance_d1000(1000);
      }
      if (tp->get_damage_crush() > 0) {
        tp->set_damage_crush_chance_d1000(1000);
      }
      if (tp->get_damage_digest() > 0) {
        tp->set_damage_digest_chance_d1000(1000);
      }
      if (tp->get_damage_energy() > 0) {
        tp->set_damage_energy_chance_d1000(1000);
      }
      if (tp->get_damage_fire() > 0) {
        tp->set_damage_fire_chance_d1000(1000);
      }
      if (tp->get_damage_future1() > 0) {
        tp->set_damage_future1_chance_d1000(1000);
      }
      if (tp->get_damage_future2() > 0) {
        tp->set_damage_future2_chance_d1000(1000);
      }
      if (tp->get_damage_future3() > 0) {
        tp->set_damage_future3_chance_d1000(1000);
      }
      if (tp->get_damage_cold() > 0) {
        tp->set_damage_cold_chance_d1000(1000);
      }
      if (tp->get_damage_lightning() > 0) {
        tp->set_damage_lightning_chance_d1000(1000);
      }
      if (tp->get_damage_melee() > 0) {
        tp->set_damage_melee_chance_d1000(1000);
      }
      if (tp->get_damage_necrosis() > 0) {
        tp->set_damage_necrosis_chance_d1000(1000);
      }
      if (tp->get_damage_poison() > 0) {
        tp->set_damage_poison_chance_d1000(1000);
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
