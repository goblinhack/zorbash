//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing_template.hpp"

bool Tp::has_temperature(void) { return _has_temperature; }

void Tp::temperature_set(int v)
{
  _temperature = v;
  if (! _initial_temperature_set) {
    _initial_temperature_set = true;
    _initial_temperature     = v;
  }
  _has_temperature = true;
}

void Tp::temperature_max_set(int v)
{
  _temperature_max_set = true;
  _temperature_max     = v;
}
void Tp::temperature_min_set(int v)
{
  _temperature_min_set = true;
  _temperature_min     = v;
}

bool Tp::initial_temperature_is_set(void) const { return _initial_temperature_set; }
bool Tp::temperature_min_is_set(void) const { return _temperature_min_set; }
bool Tp::temperature_max_is_set(void) const { return _temperature_max_set; }

// begin sort marker1 {
const std::string &Tp::dmg_nat_att_type(void) const { return _dmg_nat_att_type; }
const std::string &Tp::equip_carry_anim(void) const { return _equip_carry_anim; }
const std::string &Tp::gfx_anim_use(void) const { return _gfx_anim_use; }
const std::string &Tp::gfx_targetted_laser(void) const { return _gfx_targetted_laser; }
const std::string &Tp::gfx_targetted_radial(void) const { return _gfx_targetted_radial; }
const std::string &Tp::is_allied_with(void) const { return _is_allied_with; }
const std::string &Tp::light_color(void) const { return _light_color; }
const std::string &Tp::name(void) const { return _name; }
const std::string &Tp::on_attacking_dmg_acid_do(void) const { return _on_attacking_dmg_acid_do; }
const std::string &Tp::on_attacking_dmg_bite_do(void) const { return _on_attacking_dmg_bite_do; }
const std::string &Tp::on_attacking_dmg_claw_do(void) const { return _on_attacking_dmg_claw_do; }
const std::string &Tp::on_attacking_dmg_cold_do(void) const { return _on_attacking_dmg_cold_do; }
const std::string &Tp::on_attacking_dmg_crush_do(void) const { return _on_attacking_dmg_crush_do; }
const std::string &Tp::on_attacking_dmg_digest_do(void) const { return _on_attacking_dmg_digest_do; }
const std::string &Tp::on_attacking_dmg_draining_do(void) const { return _on_attacking_dmg_draining_do; }
const std::string &Tp::on_attacking_dmg_drown_do(void) const { return _on_attacking_dmg_drown_do; }
const std::string &Tp::on_attacking_dmg_energy_do(void) const { return _on_attacking_dmg_energy_do; }
const std::string &Tp::on_attacking_dmg_fire_do(void) const { return _on_attacking_dmg_fire_do; }
const std::string &Tp::on_attacking_dmg_heat_do(void) const { return _on_attacking_dmg_heat_do; }
const std::string &Tp::on_attacking_dmg_lightning_do(void) const { return _on_attacking_dmg_lightning_do; }
const std::string &Tp::on_attacking_dmg_melee_do(void) const { return _on_attacking_dmg_melee_do; }
const std::string &Tp::on_attacking_dmg_nat_att_do(void) const { return _on_attacking_dmg_nat_att_do; }
const std::string &Tp::on_attacking_dmg_necrosis_do(void) const { return _on_attacking_dmg_necrosis_do; }
const std::string &Tp::on_attacking_dmg_negation_do(void) const { return _on_attacking_dmg_negation_do; }
const std::string &Tp::on_attacking_dmg_poison_do(void) const { return _on_attacking_dmg_poison_do; }
const std::string &Tp::on_attacking_dmg_stat_att_do(void) const { return _on_attacking_dmg_stat_att_do; }
const std::string &Tp::on_attacking_dmg_stat_con_do(void) const { return _on_attacking_dmg_stat_con_do; }
const std::string &Tp::on_attacking_dmg_stat_str_do(void) const { return _on_attacking_dmg_stat_str_do; }
const std::string &Tp::on_attacking_dmg_water_do(void) const { return _on_attacking_dmg_water_do; }
const std::string &Tp::on_awake_do(void) const { return _on_awake_do; }
const std::string &Tp::on_born_do(void) const { return _on_born_do; }
const std::string &Tp::on_death_do(void) const { return _on_death_do; }
const std::string &Tp::on_death_of_a_follower_do(void) const { return _on_death_of_a_follower_do; }
const std::string &Tp::on_death_of_my_leader_do(void) const { return _on_death_of_my_leader_do; }
const std::string &Tp::on_dropped_do(void) const { return _on_dropped_do; }
const std::string &Tp::on_enchant_do(void) const { return _on_enchant_do; }
const std::string &Tp::on_equip_do(void) const { return _on_equip_do; }
const std::string &Tp::on_fall_begin_do(void) const { return _on_fall_begin_do; }
const std::string &Tp::on_fall_do(void) const { return _on_fall_do; }
const std::string &Tp::on_final_use_do(void) const { return _on_final_use_do; }
const std::string &Tp::on_get_text_description_long_do(void) const { return _on_get_text_description_long_do; }
const std::string &Tp::on_jump_do(void) const { return _on_jump_do; }
const std::string &Tp::on_lifespan_tick_do(void) const { return _on_lifespan_tick_do; }
const std::string &Tp::on_move_do(void) const { return _on_move_do; }
const std::string &Tp::on_open_do(void) const { return _on_open_do; }
const std::string &Tp::on_owner_add_do(void) const { return _on_owner_add_do; }
const std::string &Tp::on_owner_attack_dmg_acid_do(void) const { return _on_owner_attack_dmg_acid_do; }
const std::string &Tp::on_owner_attack_dmg_bite_do(void) const { return _on_owner_attack_dmg_bite_do; }
const std::string &Tp::on_owner_attack_dmg_claw_do(void) const { return _on_owner_attack_dmg_claw_do; }
const std::string &Tp::on_owner_attack_dmg_cold_do(void) const { return _on_owner_attack_dmg_cold_do; }
const std::string &Tp::on_owner_attack_dmg_crush_do(void) const { return _on_owner_attack_dmg_crush_do; }
const std::string &Tp::on_owner_attack_dmg_digest_do(void) const { return _on_owner_attack_dmg_digest_do; }
const std::string &Tp::on_owner_attack_dmg_draining_do(void) const { return _on_owner_attack_dmg_draining_do; }
const std::string &Tp::on_owner_attack_dmg_drown_do(void) const { return _on_owner_attack_dmg_drown_do; }
const std::string &Tp::on_owner_attack_dmg_energy_do(void) const { return _on_owner_attack_dmg_energy_do; }
const std::string &Tp::on_owner_attack_dmg_fire_do(void) const { return _on_owner_attack_dmg_fire_do; }
const std::string &Tp::on_owner_attack_dmg_heat_do(void) const { return _on_owner_attack_dmg_heat_do; }
const std::string &Tp::on_owner_attack_dmg_lightning_do(void) const { return _on_owner_attack_dmg_lightning_do; }
const std::string &Tp::on_owner_attack_dmg_melee_do(void) const { return _on_owner_attack_dmg_melee_do; }
const std::string &Tp::on_owner_attack_dmg_nat_att_do(void) const { return _on_owner_attack_dmg_nat_att_do; }
const std::string &Tp::on_owner_attack_dmg_necrosis_do(void) const { return _on_owner_attack_dmg_necrosis_do; }
const std::string &Tp::on_owner_attack_dmg_negation_do(void) const { return _on_owner_attack_dmg_negation_do; }
const std::string &Tp::on_owner_attack_dmg_poison_do(void) const { return _on_owner_attack_dmg_poison_do; }
const std::string &Tp::on_owner_attack_dmg_stat_att_do(void) const { return _on_owner_attack_dmg_stat_att_do; }
const std::string &Tp::on_owner_attack_dmg_stat_con_do(void) const { return _on_owner_attack_dmg_stat_con_do; }
const std::string &Tp::on_owner_attack_dmg_stat_str_do(void) const { return _on_owner_attack_dmg_stat_str_do; }
const std::string &Tp::on_owner_attack_dmg_water_do(void) const { return _on_owner_attack_dmg_water_do; }
const std::string &Tp::on_owner_receive_dmg_acid_do(void) const { return _on_owner_receive_dmg_acid_do; }
const std::string &Tp::on_owner_receive_dmg_bite_do(void) const { return _on_owner_receive_dmg_bite_do; }
const std::string &Tp::on_owner_receive_dmg_claw_do(void) const { return _on_owner_receive_dmg_claw_do; }
const std::string &Tp::on_owner_receive_dmg_cold_do(void) const { return _on_owner_receive_dmg_cold_do; }
const std::string &Tp::on_owner_receive_dmg_crush_do(void) const { return _on_owner_receive_dmg_crush_do; }
const std::string &Tp::on_owner_receive_dmg_digest_do(void) const { return _on_owner_receive_dmg_digest_do; }
const std::string &Tp::on_owner_receive_dmg_draining_do(void) const { return _on_owner_receive_dmg_draining_do; }
const std::string &Tp::on_owner_receive_dmg_drown_do(void) const { return _on_owner_receive_dmg_drown_do; }
const std::string &Tp::on_owner_receive_dmg_energy_do(void) const { return _on_owner_receive_dmg_energy_do; }
const std::string &Tp::on_owner_receive_dmg_fire_do(void) const { return _on_owner_receive_dmg_fire_do; }
const std::string &Tp::on_owner_receive_dmg_heat_do(void) const { return _on_owner_receive_dmg_heat_do; }
const std::string &Tp::on_owner_receive_dmg_lightning_do(void) const { return _on_owner_receive_dmg_lightning_do; }
const std::string &Tp::on_owner_receive_dmg_melee_do(void) const { return _on_owner_receive_dmg_melee_do; }
const std::string &Tp::on_owner_receive_dmg_nat_att_do(void) const { return _on_owner_receive_dmg_nat_att_do; }
const std::string &Tp::on_owner_receive_dmg_necrosis_do(void) const { return _on_owner_receive_dmg_necrosis_do; }
const std::string &Tp::on_owner_receive_dmg_negation_do(void) const { return _on_owner_receive_dmg_negation_do; }
const std::string &Tp::on_owner_receive_dmg_poison_do(void) const { return _on_owner_receive_dmg_poison_do; }
const std::string &Tp::on_owner_receive_dmg_stat_att_do(void) const { return _on_owner_receive_dmg_stat_att_do; }
const std::string &Tp::on_owner_receive_dmg_stat_con_do(void) const { return _on_owner_receive_dmg_stat_con_do; }
const std::string &Tp::on_owner_receive_dmg_stat_str_do(void) const { return _on_owner_receive_dmg_stat_str_do; }
const std::string &Tp::on_owner_receive_dmg_water_do(void) const { return _on_owner_receive_dmg_water_do; }
const std::string &Tp::on_owner_remove_do(void) const { return _on_owner_remove_do; }
const std::string &Tp::on_polymorphed_do(void) const { return _on_polymorphed_do; }
const std::string &Tp::on_receiving_dmg_acid_do(void) const { return _on_receiving_dmg_acid_do; }
const std::string &Tp::on_receiving_dmg_bite_do(void) const { return _on_receiving_dmg_bite_do; }
const std::string &Tp::on_receiving_dmg_claw_do(void) const { return _on_receiving_dmg_claw_do; }
const std::string &Tp::on_receiving_dmg_cold_do(void) const { return _on_receiving_dmg_cold_do; }
const std::string &Tp::on_receiving_dmg_crush_do(void) const { return _on_receiving_dmg_crush_do; }
const std::string &Tp::on_receiving_dmg_digest_do(void) const { return _on_receiving_dmg_digest_do; }
const std::string &Tp::on_receiving_dmg_draining_do(void) const { return _on_receiving_dmg_draining_do; }
const std::string &Tp::on_receiving_dmg_drown_do(void) const { return _on_receiving_dmg_drown_do; }
const std::string &Tp::on_receiving_dmg_energy_do(void) const { return _on_receiving_dmg_energy_do; }
const std::string &Tp::on_receiving_dmg_fire_do(void) const { return _on_receiving_dmg_fire_do; }
const std::string &Tp::on_receiving_dmg_heat_do(void) const { return _on_receiving_dmg_heat_do; }
const std::string &Tp::on_receiving_dmg_lightning_do(void) const { return _on_receiving_dmg_lightning_do; }
const std::string &Tp::on_receiving_dmg_melee_do(void) const { return _on_receiving_dmg_melee_do; }
const std::string &Tp::on_receiving_dmg_nat_att_do(void) const { return _on_receiving_dmg_nat_att_do; }
const std::string &Tp::on_receiving_dmg_necrosis_do(void) const { return _on_receiving_dmg_necrosis_do; }
const std::string &Tp::on_receiving_dmg_negation_do(void) const { return _on_receiving_dmg_negation_do; }
const std::string &Tp::on_receiving_dmg_poison_do(void) const { return _on_receiving_dmg_poison_do; }
const std::string &Tp::on_receiving_dmg_stat_att_do(void) const { return _on_receiving_dmg_stat_att_do; }
const std::string &Tp::on_receiving_dmg_stat_con_do(void) const { return _on_receiving_dmg_stat_con_do; }
const std::string &Tp::on_receiving_dmg_stat_str_do(void) const { return _on_receiving_dmg_stat_str_do; }
const std::string &Tp::on_receiving_dmg_water_do(void) const { return _on_receiving_dmg_water_do; }
const std::string &Tp::on_resting_do(void) const { return _on_resting_do; }
const std::string &Tp::on_stuck_do(void) const { return _on_stuck_do; }
const std::string &Tp::on_swing_do(void) const { return _on_swing_do; }
const std::string &Tp::on_targetted_do(void) const { return _on_targetted_do; }
const std::string &Tp::on_targetted_radially_do(void) const { return _on_targetted_radially_do; }
const std::string &Tp::on_teleport_do(void) const { return _on_teleport_do; }
const std::string &Tp::on_thrown_do(void) const { return _on_thrown_do; }
const std::string &Tp::on_tick_do(void) const { return _on_tick_do; }
const std::string &Tp::on_unequip_do(void) const { return _on_unequip_do; }
const std::string &Tp::on_use_do(void) const { return _on_use_do; }
const std::string &Tp::on_waiting_do(void) const { return _on_waiting_do; }
const std::string &Tp::on_want_to_fire_at_something_do(void) const { return _on_want_to_fire_at_something_do; }
const std::string &Tp::on_you_are_declared_a_follower_do(void) const { return _on_you_are_declared_a_follower_do; }
const std::string &Tp::on_you_are_declared_leader_do(void) const { return _on_you_are_declared_leader_do; }
const std::string &Tp::on_you_are_hit_and_now_dead_do(void) const { return _on_you_are_hit_and_now_dead_do; }
const std::string &Tp::on_you_are_hit_but_dodge_it_do(void) const { return _on_you_are_hit_but_dodge_it_do; }
const std::string &Tp::on_you_are_hit_but_still_alive_do(void) const { return _on_you_are_hit_but_still_alive_do; }
const std::string &Tp::on_you_are_on_fire_do(void) const { return _on_you_are_on_fire_do; }
const std::string &Tp::on_you_nat_att_do(void) const { return _on_you_nat_att_do; }
const std::string &Tp::spawn_on_shoved(void) const { return _spawn_on_shoved; }
const std::string &Tp::str1(void) const { return _str1; }
const std::string &Tp::str2(void) const { return _str2; }
const std::string &Tp::str4(void) const { return _str4; }
const std::string &Tp::target_name_projectile(void) const { return _target_name_projectile; }
const std::string &Tp::text_debuff(void) const { return _text_debuff; }
const std::string &Tp::text_description_enchant(void) const { return _text_description_enchant; }
const std::string &Tp::text_description_long2(void) const { return _text_description_long2; }
const std::string &Tp::text_description_long3(void) const { return _text_description_long3; }
const std::string &Tp::text_description_long(void) const { return _text_description_long; }
const std::string &Tp::text_description_short(void) const { return _text_description_short; }
const std::string &Tp::text_hits(void) const { return _text_hits; }
const std::string &Tp::text_long_name(void) const { return _text_long_name; }
const std::string &Tp::text_short_name(void) const { return _text_short_name; }
const std::string &Tp::text_skill(void) const { return _text_skill; }
const std::string &Tp::text_title(void) const { return _text_title; }
const std::string &Tp::text_unused1(void) const { return _text_unused1; }
const std::string &Tp::text_unused2(void) const { return _text_unused2; }
const std::string &Tp::text_unused3(void) const { return _text_unused3; }
const std::string &Tp::text_unused(void) const { return _text_unused; }
// end sort marker1 }

// begin sort marker2 {
int Tp::aggression_pct(void) const { return _aggression_pct; }
int Tp::ai_detect_secret_doors(void) const { return _ai_detect_secret_doors; }
int Tp::ai_resent_count(void) const { return _ai_resent_count; }
int Tp::ai_wanderer(void) const { return _ai_wanderer; }
int Tp::appearing_chance_d1000(void) const { return _appearing_chance_d1000; }
int Tp::attack_eater(void) const { return _attack_eater; }
int Tp::attack_engulf_chance_d1000(void) const { return _attack_engulf_chance_d1000; }
int Tp::attack_humanoid(void) const { return _attack_humanoid; }
int Tp::attack_living(void) const { return _attack_living; }
int Tp::attack_lunge(void) const { return _attack_lunge; }
int Tp::attack_meat(void) const { return _attack_meat; }
int Tp::attack_no_msg(void) const { return _attack_no_msg; }
int Tp::attacks_per_round(void) const { return _attacks_per_round; }
int Tp::attack_undead(void) const { return _attack_undead; }
int Tp::blast_min_radius(void) const { return _blast_min_radius; }
int Tp::blit_bot_off(void) const { return _blit_bot_off; }
int Tp::blit_left_off(void) const { return _blit_left_off; }
int Tp::blit_right_off(void) const { return _blit_right_off; }
int Tp::blit_top_off(void) const { return _blit_top_off; }
int Tp::capacity_height(void) const { return _capacity_height; }
int Tp::capacity_width(void) const { return _capacity_width; }
int Tp::charge_count(void) const { return _charge_count; }
int Tp::collateral_dmg_pct(void) const { return _collateral_dmg_pct; }
int Tp::collision_check(void) const { return _collision_check; }
int Tp::collision_hit_180(void) const { return _collision_hit_180; }
int Tp::collision_hit_360(void) const { return _collision_hit_360; }
int Tp::collision_hit_adj(void) const { return _collision_hit_adj; }
int Tp::collision_hit_priority(void) const { return _collision_hit_priority; }
int Tp::collision_hit_two_tiles_ahead(void) const { return _collision_hit_two_tiles_ahead; }
int Tp::consume_per_bite_amount(void) const { return _consume_per_bite_amount; }
int Tp::crit_chance_d10000(void) const { return _crit_chance_d10000; }
int Tp::damaged_chance_d10000(void) const { return _dmgd_chance_d10000; }
int Tp::distance_avoid(void) const { return _distance_avoid; }
int Tp::distance_leader_max(void) const { return _distance_leader_max; }
int Tp::distance_minion_vision_shared(void) const { return _distance_minion_vision_shared; }
int Tp::distance_mob_max(void) const { return _distance_mob_max; }
int Tp::distance_recruitment_max(void) const { return _distance_recruitment_max; }
int Tp::distance_throw(void) const { return _distance_throw; }
int Tp::distance_vision(void) const { return _distance_vision; }
int Tp::dmg_received_doubled_from_acid(void) const { return _dmg_received_doubled_from_acid; }
int Tp::dmg_received_doubled_from_cold(void) const { return _dmg_received_doubled_from_cold; }
int Tp::dmg_received_doubled_from_fire(void) const { return _dmg_received_doubled_from_fire; }
int Tp::dmg_received_doubled_from_necrosis(void) const { return _dmg_received_doubled_from_necrosis; }
int Tp::dmg_received_doubled_from_poison(void) const { return _dmg_received_doubled_from_poison; }
int Tp::dmg_received_doubled_from_water(void) const { return _dmg_received_doubled_from_water; }
int Tp::effect_radius(void) const { return _effect_radius; }
int Tp::enchant_max(void) const { return _enchant_max; }
int Tp::environ_avoids_acid(void) const { return _environ_avoids_acid; }
int Tp::environ_avoids_cold(void) const { return _environ_avoids_cold; }
int Tp::environ_avoids_fire(void) const { return _environ_avoids_fire; }
int Tp::environ_avoids_necrosis(void) const { return _environ_avoids_necrosis; }
int Tp::environ_avoids_poison(void) const { return _environ_avoids_poison; }
int Tp::environ_avoids_water(void) const { return _environ_avoids_water; }
int Tp::gfx_ascii_animated(void) const { return _gfx_ascii_animated; }
int Tp::gfx_ascii_bg_color_spread_alpha(void) const { return _gfx_ascii_bg_color_spread_alpha; }
int Tp::gfx_ascii_bg_color_spread_blue(void) const { return _gfx_ascii_bg_color_spread_blue; }
int Tp::gfx_ascii_bg_color_spread_green(void) const { return _gfx_ascii_bg_color_spread_green; }
int Tp::gfx_ascii_bg_color_spread_hue(void) const { return _gfx_ascii_bg_color_spread_hue; }
int Tp::gfx_ascii_bg_color_spread_red(void) const { return _gfx_ascii_bg_color_spread_red; }
int Tp::gfx_ascii_color_bg_unchanged_by_lights(void) const { return _gfx_ascii_color_bg_unchanged_by_lights; }
int Tp::gfx_ascii_color_fg_unchanged_by_lights(void) const { return _gfx_ascii_color_fg_unchanged_by_lights; }
int Tp::gfx_ascii_color_is_animated(void) const { return _gfx_ascii_color_is_animated; }
int Tp::gfx_ascii_fade_with_dist(void) const { return _gfx_ascii_fade_with_dist; }
int Tp::gfx_ascii_fg_color_spread_alpha(void) const { return _gfx_ascii_fg_color_spread_alpha; }
int Tp::gfx_ascii_fg_color_spread_blue(void) const { return _gfx_ascii_fg_color_spread_blue; }
int Tp::gfx_ascii_fg_color_spread_green(void) const { return _gfx_ascii_fg_color_spread_green; }
int Tp::gfx_ascii_fg_color_spread_hue(void) const { return _gfx_ascii_fg_color_spread_hue; }
int Tp::gfx_ascii_fg_color_spread_red(void) const { return _gfx_ascii_fg_color_spread_red; }
int Tp::gfx_ascii_shown_as_gray_in_shadow(void) const { return _gfx_ascii_shown_as_gray_in_shadow; }
int Tp::gfx_ascii_shown_in_bg(void) const { return _gfx_ascii_shown_in_bg; }
int Tp::gfx_ascii_shown(void) const { return _gfx_ascii_shown; }
int Tp::gfx_glows(void) const { return _gfx_glows; }
int Tp::gfx_on_fire_anim(void) const { return _gfx_on_fire_anim; }
int Tp::gfx_pixelart_animated_can_hflip(void) const { return _gfx_pixelart_animated_can_hflip; }
int Tp::gfx_pixelart_animated_can_vflip(void) const { return _gfx_pixelart_animated_can_vflip; }
int Tp::gfx_pixelart_animated_no_dir(void) const { return _gfx_pixelart_animated_no_dir; }
int Tp::gfx_pixelart_anim_synced_with_owner(void) const { return _gfx_pixelart_anim_synced_with_owner; }
int Tp::gfx_pixelart_attack_anim(void) const { return _gfx_pixelart_attack_anim; }
int Tp::gfx_pixelart_bounce_always(void) const { return _gfx_pixelart_bounce_always; }
int Tp::gfx_pixelart_bounce_on_move(void) const { return _gfx_pixelart_bounce_on_move; }
int Tp::gfx_pixelart_equip_carry_anim(void) const { return _gfx_pixelart_equip_carry_anim; }
int Tp::gfx_pixelart_flickers(void) const { return _gfx_pixelart_flickers; }
int Tp::gfx_pixelart_health_bar_autohide(void) const { return _gfx_pixelart_health_bar_autohide; }
int Tp::gfx_pixelart_health_bar_only_when_awake(void) const { return _gfx_pixelart_health_bar_only_when_awake; }
int Tp::gfx_pixelart_health_bar_shown(void) const { return _gfx_pixelart_health_bar_shown; }
int Tp::gfx_pixelart_oversized_and_centered(void) const { return _gfx_pixelart_oversized_and_centered; }
int Tp::gfx_pixelart_oversized_and_on_floor(void) const { return _gfx_pixelart_oversized_and_on_floor; }
int Tp::gfx_pixelart_reflection(void) const { return _gfx_pixelart_reflection; }
int Tp::gfx_pixelart_shadow_long(void) const { return _gfx_pixelart_shadow_long; }
int Tp::gfx_pixelart_shadow_short(void) const { return _gfx_pixelart_shadow_short; }
int Tp::gfx_pixelart_shadow_solid(void) const { return _gfx_pixelart_shadow_solid; }
int Tp::gfx_pixelart_shadow_very_short(void) const { return _gfx_pixelart_shadow_very_short; }
int Tp::gfx_pixelart_shadow(void) const { return _gfx_pixelart_shadow; }
int Tp::gfx_pixelart_show_asleep_anim(void) const { return _gfx_pixelart_show_asleep_anim; }
int Tp::gfx_pixelart_show_highlighted(void) const { return _gfx_pixelart_show_highlighted; }
int Tp::gfx_pixelart_shown_in_bg(void) const { return _gfx_pixelart_shown_in_bg; }
int Tp::gfx_pixelart_show_outlined(void) const { return _gfx_pixelart_show_outlined; }
int Tp::gfx_pixelart_show_square_outlined(void) const { return _gfx_pixelart_show_square_outlined; }
int Tp::gfx_pixelart_submergable(void) const { return _gfx_pixelart_submergable; }
int Tp::gfx_pixelart_wobbles_when_hit(void) const { return _gfx_pixelart_wobbles_when_hit; }
int Tp::gfx_water(void) const { return _gfx_water; }
int Tp::hunger_clock_tick_freq(void) const { return _hunger_clock_tick_freq; }
int Tp::hunger_is_hunger_level_hungry_at_pct(void) const { return _hunger_is_hunger_level_hungry_at_pct; }
int Tp::hunger_is_hunger_level_starving_at_pct(void) const { return _hunger_is_hunger_level_starving_at_pct; }
int Tp::hunger_is_insatiable(void) const { return _hunger_is_insatiable; }
int Tp::initial_temperature(void) const { return _initial_temperature; }
int Tp::internal_has_dir_anim(void) const { return _internal_has_dir_anim; }
int Tp::internal_has_hp_anim(void) const { return _internal_has_hp_anim; }
int Tp::is_able_to_attack_mobs(void) const { return _is_able_to_attack_mobs; }
int Tp::is_able_to_attack_owner(void) const { return _is_able_to_attack_owner; }
int Tp::is_able_to_be_surprised(void) const { return _is_able_to_be_surprised; }
int Tp::is_able_to_break_down_doors(void) const { return _is_able_to_break_down_doors; }
int Tp::is_able_to_break_out_of_ice(void) const { return _is_able_to_break_out_of_ice; }
int Tp::is_able_to_break_out_of_webs(void) const { return _is_able_to_break_out_of_webs; }
int Tp::is_able_to_burn(void) const { return _is_able_to_burn; }
int Tp::is_able_to_change_levels(void) const { return _is_able_to_change_levels; }
int Tp::is_able_to_collect_keys(void) const { return _is_able_to_collect_keys; }
int Tp::is_able_to_enchant_items(void) const { return _is_able_to_enchant_items; }
int Tp::is_able_to_fall(void) const { return _is_able_to_fall; }
int Tp::is_able_to_fire_at_close_range(void) const { return _is_able_to_fire_at_close_range; }
int Tp::is_able_to_fire_at(void) const { return _is_able_to_fire_at; }
int Tp::is_able_to_follow(void) const { return _is_able_to_follow; }
int Tp::is_able_to_freeze(void) const { return _is_able_to_freeze; }
int Tp::is_able_to_grapple_chance_d1000(void) const { return _is_able_to_grapple_chance_d1000; }
int Tp::is_able_to_grapple(void) const { return _is_able_to_grapple; }
int Tp::is_able_to_jump_attack_chance_d1000(void) const { return _is_able_to_jump_attack_chance_d1000; }
int Tp::is_able_to_jump_attack(void) const { return _is_able_to_jump_attack; }
int Tp::is_able_to_jump_escape(void) const { return _is_able_to_jump_escape; }
int Tp::is_able_to_jump_on_low_hp_chance_d1000(void) const { return _is_able_to_jump_on_low_hp_chance_d1000; }
int Tp::is_able_to_jump_onto_chance_d1000(void) const { return _is_able_to_jump_onto_chance_d1000; }
int Tp::is_able_to_jump_onto(void) const { return _is_able_to_jump_onto; }
int Tp::is_able_to_jump_randomly_chance_d1000(void) const { return _is_able_to_jump_randomly_chance_d1000; }
int Tp::is_able_to_jump(void) const { return _is_able_to_jump; }
int Tp::is_able_to_jump_without_tiring(void) const { return _is_able_to_jump_without_tiring; }
int Tp::is_able_to_learn_skills(void) const { return _is_able_to_learn_skills; }
int Tp::is_able_to_live_out_of_water(void) const { return _is_able_to_live_out_of_water; }
int Tp::is_able_to_melt(void) const { return _is_able_to_melt; }
int Tp::is_able_to_move_diagonally(void) const { return _is_able_to_move_diagonally; }
int Tp::is_able_to_open_doors(void) const { return _is_able_to_open_doors; }
int Tp::is_able_to_rest(void) const { return _is_able_to_rest; }
int Tp::is_able_to_see_in_the_dark(void) const { return _is_able_to_see_in_the_dark; }
int Tp::is_able_to_see_invisible(void) const { return _is_able_to_see_invisible; }
int Tp::is_able_to_see_through_doors(void) const { return _is_able_to_see_through_doors; }
int Tp::is_able_to_shove_chance_d1000(void) const { return _is_able_to_shove_chance_d1000; }
int Tp::is_able_to_shove(void) const { return _is_able_to_shove; }
int Tp::is_able_to_sleep(void) const { return _is_able_to_sleep; }
int Tp::is_able_to_spawn_things(void) const { return _is_able_to_spawn_things; }
int Tp::is_able_to_swim(void) const { return _is_able_to_swim; }
int Tp::is_able_to_teleport_attack_chance_d1000(void) const { return _is_able_to_teleport_attack_chance_d1000; }
int Tp::is_able_to_teleport_attack(void) const { return _is_able_to_teleport_attack; }
int Tp::is_able_to_teleport_escape(void) const { return _is_able_to_teleport_escape; }
int Tp::is_able_to_teleport_without_tiring(void) const { return _is_able_to_teleport_without_tiring; }
int Tp::is_able_to_tire(void) const { return _is_able_to_tire; }
int Tp::is_able_to_use_amulet(void) const { return _is_able_to_use_amulet; }
int Tp::is_able_to_use_armor(void) const { return _is_able_to_use_armor; }
int Tp::is_able_to_use_boots(void) const { return _is_able_to_use_boots; }
int Tp::is_able_to_use_cloak(void) const { return _is_able_to_use_cloak; }
int Tp::is_able_to_use_gauntlet(void) const { return _is_able_to_use_gauntlet; }
int Tp::is_able_to_use_helmet(void) const { return _is_able_to_use_helmet; }
int Tp::is_able_to_use_rings(void) const { return _is_able_to_use_rings; }
int Tp::is_able_to_use_shield(void) const { return _is_able_to_use_shield; }
int Tp::is_able_to_use_staffs(void) const { return _is_able_to_use_staffs; }
int Tp::is_able_to_use_weapons(void) const { return _is_able_to_use_weapons; }
int Tp::is_able_to_walk_through_walls(void) const { return _is_able_to_walk_through_walls; }
int Tp::is_acid(void) const { return _is_acid; }
int Tp::is_air_breather(void) const { return _is_air_breather; }
int Tp::is_alive_on_end_of_anim(void) const { return _is_alive_on_end_of_anim; }
int Tp::is_always_hit(void) const { return _is_always_hit; }
int Tp::is_always_submerged(void) const { return _is_always_submerged; }
int Tp::is_amulet(void) const { return _is_amulet; }
int Tp::is_aquatic(void) const { return _is_aquatic; }
int Tp::is_armor(void) const { return _is_armor; }
int Tp::is_ascend_dungeon(void) const { return _is_ascend_dungeon; }
int Tp::is_ascend_sewer(void) const { return _is_ascend_sewer; }
int Tp::is_asleep_initially(void) const { return _is_asleep_initially; }
int Tp::is_attackable_by_monst(void) const { return _is_attackable_by_monst; }
int Tp::is_attackable_by_player(void) const { return _is_attackable_by_player; }
int Tp::is_auto_collect_item(void) const { return _is_auto_collect_item; }
int Tp::is_auto_equipped(void) const { return _is_auto_equipped; }
int Tp::is_auto_throw(void) const { return _is_auto_throw; }
int Tp::is_auto_use(void) const { return _is_auto_use; }
int Tp::is_bag_item_container(void) const { return _is_bag_item_container; }
int Tp::is_bag_item_not_stackable(void) const { return _is_bag_item_not_stackable; }
int Tp::is_bag_item(void) const { return _is_bag_item; }
int Tp::is_bag(void) const { return _is_bag; }
int Tp::is_barrel(void) const { return _is_barrel; }
int Tp::is_basalt(void) const { return _is_basalt; }
int Tp::is_biome_dungeon(void) const { return _is_biome_dungeon; }
int Tp::is_biome_sewer(void) const { return _is_biome_sewer; }
int Tp::is_biome_swamp(void) const { return _is_biome_swamp; }
int Tp::is_biome_unused(void) const { return _is_biome_unused; }
int Tp::is_bleeder(void) const { return _is_bleeder; }
int Tp::is_block_of_ice(void) const { return _is_block_of_ice; }
int Tp::is_bones(void) const { return _is_bones; }
int Tp::is_boots(void) const { return _is_boots; }
int Tp::is_brazier(void) const { return _is_brazier; }
int Tp::is_bridge(void) const { return _is_bridge; }
int Tp::is_brittle(void) const { return _is_brittle; }
int Tp::is_buff(void) const { return _is_buff; }
int Tp::is_carnivorous_plant(void) const { return _is_carnivorous_plant; }
int Tp::is_carrier_of_treasure_class_a_d1000(void) const { return _is_carrier_of_treasure_class_a_d1000; }
int Tp::is_carrier_of_treasure_class_b_d1000(void) const { return _is_carrier_of_treasure_class_b_d1000; }
int Tp::is_carrier_of_treasure_class_c_d1000(void) const { return _is_carrier_of_treasure_class_c_d1000; }
int Tp::is_carrier_of_weapon_class_a_d1000(void) const { return _is_carrier_of_weapon_class_a_d1000; }
int Tp::is_carrier_of_weapon_class_b_d1000(void) const { return _is_carrier_of_weapon_class_b_d1000; }
int Tp::is_carrier_of_weapon_class_c_d1000(void) const { return _is_carrier_of_weapon_class_c_d1000; }
int Tp::is_chasm(void) const { return _is_chasm; }
int Tp::is_cloak(void) const { return _is_cloak; }
int Tp::is_cold(void) const { return _is_cold; }
int Tp::is_collectable(void) const { return _is_collectable; }
int Tp::is_collected_as_gold(void) const { return _is_collected_as_gold; }
int Tp::is_collected_as_keys(void) const { return _is_collected_as_keys; }
int Tp::is_combustible(void) const { return _is_combustible; }
int Tp::is_corpse_on_death(void) const { return _is_corpse_on_death; }
int Tp::is_corpse_with_bones(void) const { return _is_corpse_with_bones; }
int Tp::is_corridor(void) const { return _is_corridor; }
int Tp::is_cowardly(void) const { return _is_cowardly; }
int Tp::is_critical_to_level(void) const { return _is_critical_to_level; }
int Tp::is_crushable(void) const { return _is_crushable; }
int Tp::is_crystal(void) const { return _is_crystal; }
int Tp::is_cursor_can_hover_over(void) const { return _is_cursor_can_hover_over; }
int Tp::is_cursor_can_hover_over_x2_click(void) const { return _is_cursor_can_hover_over_x2_click; }
int Tp::is_cursor_path_blocker(void) const { return _is_cursor_path_blocker; }
int Tp::is_cursor_path_hazard(void) const { return _is_cursor_path_hazard; }
int Tp::is_cursor_path(void) const { return _is_cursor_path; }
int Tp::is_cursor(void) const { return _is_cursor; }
int Tp::is_dagger(void) const { return _is_dagger; }
int Tp::is_dead_on_end_of_anim(void) const { return _is_dead_on_end_of_anim; }
int Tp::is_dead_on_falling(void) const { return _is_dead_on_falling; }
int Tp::is_dead_on_shove(void) const { return _is_dead_on_shove; }
int Tp::is_debuff(void) const { return _is_debuff; }
int Tp::is_debug_path(void) const { return _is_debug_path; }
int Tp::is_debug_type(void) const { return _is_debug_type; }
int Tp::is_deep_water_swimmer(void) const { return _is_deep_water_swimmer; }
int Tp::is_deep_water(void) const { return _is_deep_water; }
int Tp::is_descend_dungeon(void) const { return _is_descend_dungeon; }
int Tp::is_descend_sewer(void) const { return _is_descend_sewer; }
int Tp::is_described_when_hovering_over(void) const { return _is_described_when_hovering_over; }
int Tp::is_destroyed_on_hit_or_miss(void) const { return _is_destroyed_on_hit_or_miss; }
int Tp::is_destroyed_on_hitting(void) const { return _is_destroyed_on_hitting; }
int Tp::is_dirt(void) const { return _is_dirt; }
int Tp::is_door(void) const { return _is_door; }
int Tp::is_droppable(void) const { return _is_droppable; }
int Tp::is_dry_grass_trampled(void) const { return _is_dry_grass_trampled; }
int Tp::is_dry_grass(void) const { return _is_dry_grass; }
int Tp::is_eater_of_amulets(void) const { return _is_eater_of_amulets; }
int Tp::is_eater_of_armor(void) const { return _is_eater_of_armor; }
int Tp::is_eater_of_boots(void) const { return _is_eater_of_boots; }
int Tp::is_eater_of_cloaks(void) const { return _is_eater_of_cloaks; }
int Tp::is_eater_of_food(void) const { return _is_eater_of_food; }
int Tp::is_eater_of_gauntlets(void) const { return _is_eater_of_gauntlets; }
int Tp::is_eater_of_green_blood(void) const { return _is_eater_of_green_blood; }
int Tp::is_eater_of_helmets(void) const { return _is_eater_of_helmets; }
int Tp::is_eater_of_jelly(void) const { return _is_eater_of_jelly; }
int Tp::is_eater_of_magical_items(void) const { return _is_eater_of_magical_items; }
int Tp::is_eater_of_meat(void) const { return _is_eater_of_meat; }
int Tp::is_eater_of_potions(void) const { return _is_eater_of_potions; }
int Tp::is_eater_of_red_blood(void) const { return _is_eater_of_red_blood; }
int Tp::is_eater_of_rings(void) const { return _is_eater_of_rings; }
int Tp::is_eater_of_shields(void) const { return _is_eater_of_shields; }
int Tp::is_eater_of_staffs(void) const { return _is_eater_of_staffs; }
int Tp::is_eater_of_treasure(void) const { return _is_eater_of_treasure; }
int Tp::is_eater_of_weapons(void) const { return _is_eater_of_weapons; }
int Tp::is_enchantable(void) const { return _is_enchantable; }
int Tp::is_enchantstone(void) const { return _is_enchantstone; }
int Tp::is_engulfer(void) const { return _is_engulfer; }
int Tp::is_ethereal_mob(void) const { return _is_ethereal_mob; }
int Tp::is_ethereal(void) const { return _is_ethereal; }
int Tp::is_exit_finder(void) const { return _is_exit_finder; }
int Tp::is_explorer(void) const { return _is_explorer; }
int Tp::is_explosion(void) const { return _is_explosion; }
int Tp::is_fearless(void) const { return _is_fearless; }
int Tp::is_fire(void) const { return _is_fire; }
int Tp::is_flat(void) const { return _is_flat; }
int Tp::is_floating(void) const { return _is_floating; }
int Tp::is_floor_deco(void) const { return _is_floor_deco; }
int Tp::is_floor(void) const { return _is_floor; }
int Tp::is_flying(void) const { return _is_flying; }
int Tp::is_foliage(void) const { return _is_foliage; }
int Tp::is_food(void) const { return _is_food; }
int Tp::is_gas_blocker(void) const { return _is_gas_blocker; }
int Tp::is_gauntlet(void) const { return _is_gauntlet; }
int Tp::is_gelatinous(void) const { return _is_gelatinous; }
int Tp::is_glass(void) const { return _is_glass; }
int Tp::is_gold(void) const { return _is_gold; }
int Tp::is_green_blooded(void) const { return _is_green_blooded; }
int Tp::is_green_blood(void) const { return _is_green_blood; }
int Tp::is_green_splatter(void) const { return _is_green_splatter; }
int Tp::is_hard(void) const { return _is_hard; }
int Tp::is_hazard(void) const { return _is_hazard; }
int Tp::is_health_booster(void) const { return _is_health_booster; }
int Tp::is_heavy(void) const { return _is_heavy; }
int Tp::is_helmet(void) const { return _is_helmet; }
int Tp::is_hittable(void) const { return _is_hittable; }
int Tp::is_humanoid(void) const { return _is_humanoid; }
int Tp::is_immune_to_acid(void) const { return _is_immune_to_acid; }
int Tp::is_immune_to_cold(void) const { return _is_immune_to_cold; }
int Tp::is_immune_to_draining(void) const { return _is_immune_to_draining; }
int Tp::is_immune_to_electricity(void) const { return _is_immune_to_electricity; }
int Tp::is_immune_to_fire(void) const { return _is_immune_to_fire; }
int Tp::is_immune_to_necrosis(void) const { return _is_immune_to_necrosis; }
int Tp::is_immune_to_negation(void) const { return _is_immune_to_negation; }
int Tp::is_immune_to_poison(void) const { return _is_immune_to_poison; }
int Tp::is_immune_to_spiderwebs(void) const { return _is_immune_to_spiderwebs; }
int Tp::is_immune_to_water(void) const { return _is_immune_to_water; }
int Tp::is_intelligent(void) const { return _is_intelligent; }
int Tp::is_interesting(void) const { return _is_interesting; }
int Tp::is_internal(void) const { return _is_internal; }
int Tp::is_invisible(void) const { return _is_invisible; }
int Tp::is_item_carrier(void) const { return _is_item_carrier; }
int Tp::is_item_collector(void) const { return _is_item_collector; }
int Tp::is_item_organic(void) const { return _is_item_organic; }
int Tp::is_item_targetted(void) const { return _is_item_targetted; }
int Tp::is_item(void) const { return _is_item; }
int Tp::is_jelly(void) const { return _is_jelly; }
int Tp::is_key_special(void) const { return _is_key_special; }
int Tp::is_key(void) const { return _is_key; }
int Tp::is_laser(void) const { return _is_laser; }
int Tp::is_lava(void) const { return _is_lava; }
int Tp::is_lifeless(void) const { return _is_lifeless; }
int Tp::is_light_blocker_for_monst(void) const { return _is_light_blocker_for_monst; }
int Tp::is_light_blocker(void) const { return _is_light_blocker; }
int Tp::is_lightning(void) const { return _is_lightning; }
int Tp::is_limb(void) const { return _is_limb; }
int Tp::is_living(void) const { return _is_living; }
int Tp::is_loggable(void) const { return _is_loggable; }
int Tp::is_magical(void) const { return _is_magical; }
int Tp::is_map_beast(void) const { return _is_map_beast; }
int Tp::is_map_treasure(void) const { return _is_map_treasure; }
int Tp::is_meat(void) const { return _is_meat; }
int Tp::is_metal(void) const { return _is_metal; }
int Tp::is_minion(void) const { return _is_minion; }
int Tp::is_mob_challenge_class_a(void) const { return _is_mob_challenge_class_a; }
int Tp::is_mob_challenge_class_b(void) const { return _is_mob_challenge_class_b; }
int Tp::is_mob(void) const { return _is_mob; }
int Tp::is_monst_class_a(void) const { return _is_monst_class_a; }
int Tp::is_monst_class_b(void) const { return _is_monst_class_b; }
int Tp::is_monst_class_c(void) const { return _is_monst_class_c; }
int Tp::is_monst_class_d(void) const { return _is_monst_class_d; }
int Tp::is_monst_class_e(void) const { return _is_monst_class_e; }
int Tp::is_monst_pack(void) const { return _is_monst_pack; }
int Tp::is_monst(void) const { return _is_monst; }
int Tp::is_moveable(void) const { return _is_moveable; }
int Tp::is_msg_allowed_hears_something(void) const { return _is_msg_allowed_hears_something; }
int Tp::is_msg_allowed_is_dead(void) const { return _is_msg_allowed_is_dead; }
int Tp::is_msg_allowed_is_seen(void) const { return _is_msg_allowed_is_seen; }
int Tp::is_msg_allowed_is_surprised(void) const { return _is_msg_allowed_is_surprised; }
int Tp::is_msg_allowed_is_wounded(void) const { return _is_msg_allowed_is_wounded; }
int Tp::is_msg_allowed_senses_danger(void) const { return _is_msg_allowed_senses_danger; }
int Tp::is_msg(void) const { return _is_msg; }
int Tp::is_necrotic_danger_level(void) const { return _is_necrotic_danger_level; }
int Tp::is_no_tile(void) const { return _is_no_tile; }
int Tp::is_obs_destructable(void) const { return _is_obs_destructable; }
int Tp::is_obs_for_ai(void) const { return _is_obs_for_ai; }
int Tp::is_obs_for_jump_landing(void) const { return _is_obs_for_jump_landing; }
int Tp::is_obs_for_shoving(void) const { return _is_obs_for_shoving; }
int Tp::is_obs_in_the_way_for_firing(void) const { return _is_obs_in_the_way_for_firing; }
int Tp::is_obs_in_the_way_for_jumping(void) const { return _is_obs_in_the_way_for_jumping; }
int Tp::is_obs_in_the_way_for_throwing(void) const { return _is_obs_in_the_way_for_throwing; }
int Tp::is_obs_wall_or_door(void) const { return _is_obs_wall_or_door; }
int Tp::is_obs_when_dead(void) const { return _is_obs_when_dead; }
int Tp::is_openable(void) const { return _is_openable; }
int Tp::is_organic(void) const { return _is_organic; }
int Tp::is_pillar(void) const { return _is_pillar; }
int Tp::is_plant(void) const { return _is_plant; }
int Tp::is_player(void) const { return _is_player; }
int Tp::is_poisonous_danger_level(void) const { return _is_poisonous_danger_level; }
int Tp::is_potion(void) const { return _is_potion; }
int Tp::is_projectile(void) const { return _is_projectile; }
int Tp::is_red_blooded(void) const { return _is_red_blooded; }
int Tp::is_red_blood(void) const { return _is_red_blood; }
int Tp::is_red_splatter(void) const { return _is_red_splatter; }
int Tp::is_removable_if_out_of_slots(void) const { return _is_removable_if_out_of_slots; }
int Tp::is_resurrectable(void) const { return _is_resurrectable; }
int Tp::is_ring(void) const { return _is_ring; }
int Tp::is_ripple(void) const { return _is_ripple; }
int Tp::is_rock(void) const { return _is_rock; }
int Tp::is_rusty(void) const { return _is_rusty; }
int Tp::is_secret_door(void) const { return _is_secret_door; }
int Tp::is_sewer_wall(void) const { return _is_sewer_wall; }
int Tp::is_shallow_water_swimmer(void) const { return _is_shallow_water_swimmer; }
int Tp::is_shallow_water(void) const { return _is_shallow_water; }
int Tp::is_shield(void) const { return _is_shield; }
int Tp::is_shovable_and_sticky(void) const { return _is_shovable_and_sticky; }
int Tp::is_shovable(void) const { return _is_shovable; }
int Tp::is_skillstone(void) const { return _is_skillstone; }
int Tp::is_skill(void) const { return _is_skill; }
int Tp::is_slippery(void) const { return _is_slippery; }
int Tp::is_smoke(void) const { return _is_smoke; }
int Tp::is_snake(void) const { return _is_snake; }
int Tp::is_soft(void) const { return _is_soft; }
int Tp::is_spider(void) const { return _is_spider; }
int Tp::is_spiderweb(void) const { return _is_spiderweb; }
int Tp::is_staff(void) const { return _is_staff; }
int Tp::is_steal_item_chance_d1000(void) const { return _is_steal_item_chance_d1000; }
int Tp::is_steam(void) const { return _is_steam; }
int Tp::is_sticky(void) const { return _is_sticky; }
int Tp::is_stone(void) const { return _is_stone; }
int Tp::is_swimmer(void) const { return _is_swimmer; }
int Tp::is_sword(void) const { return _is_sword; }
int Tp::is_target_radial(void) const { return _is_target_radial; }
int Tp::is_target_select(void) const { return _is_target_select; }
int Tp::is_tentacle(void) const { return _is_tentacle; }
int Tp::is_the_grid(void) const { return _is_the_grid; }
int Tp::is_thief(void) const { return _is_thief; }
int Tp::is_throwable(void) const { return _is_throwable; }
int Tp::is_tickable(void) const { return _is_tickable; }
int Tp::is_tireless(void) const { return _is_tireless; }
int Tp::is_tmp_thing(void) const { return _is_tmp_thing; }
int Tp::is_torch(void) const { return _is_torch; }
int Tp::is_treasure_chest(void) const { return _is_treasure_chest; }
int Tp::is_treasure_class_a(void) const { return _is_treasure_class_a; }
int Tp::is_treasure_class_b(void) const { return _is_treasure_class_b; }
int Tp::is_treasure_class_c(void) const { return _is_treasure_class_c; }
int Tp::is_treasure_type(void) const { return _is_treasure_type; }
int Tp::is_treasure(void) const { return _is_treasure; }
int Tp::is_undead(void) const { return _is_undead; }
int Tp::is_usable(void) const { return _is_usable; }
int Tp::is_used_when_thrown(void) const { return _is_used_when_thrown; }
int Tp::is_very_combustible(void) const { return _is_very_combustible; }
int Tp::is_very_hard(void) const { return _is_very_hard; }
int Tp::is_very_heavy(void) const { return _is_very_heavy; }
int Tp::is_wall_dungeon(void) const { return _is_wall_dungeon; }
int Tp::is_wall(void) const { return _is_wall; }
int Tp::is_weapon_class_a(void) const { return _is_weapon_class_a; }
int Tp::is_weapon_class_b(void) const { return _is_weapon_class_b; }
int Tp::is_weapon_class_c(void) const { return _is_weapon_class_c; }
int Tp::is_weapon(void) const { return _is_weapon; }
int Tp::is_wet_grass(void) const { return _is_wet_grass; }
int Tp::is_wooden(void) const { return _is_wooden; }
int Tp::item_height(void) const { return _item_height ? _item_height : 1; }
int Tp::item_width(void) const { return _item_width ? _item_width : 1; }
int Tp::jump_distance_mod(void) const { return _jump_distance_mod; }
int Tp::jump_distance(void) const { return _jump_distance; }
int Tp::light_dist(void) const { return _light_dist; }
int Tp::melting_chance_d1000(void) const { return _melting_chance_d1000; }
int Tp::minion_limit(void) const { return _minion_limit; }
int Tp::move_speed_mod(void) const { return _move_speed_mod; }
int Tp::move_speed(void) const { return _move_speed; }
int Tp::noise_additional_on_jump_end(void) const { return _noise_additional_on_jump_end; }
int Tp::noise_additional_on_teleporting(void) const { return _noise_additional_on_teleporting; }
int Tp::noise_blocker(void) const { return _noise_blocker; }
int Tp::noise_decibels_hearing(void) const { return _noise_decibels_hearing; }
int Tp::noise_on_born(void) const { return _noise_on_born; }
int Tp::noise_on_dropping(void) const { return _noise_on_dropping; }
int Tp::noise_on_moving(void) const { return _noise_on_moving; }
int Tp::noise_on_open(void) const { return _noise_on_open; }
int Tp::noise_on_you_are_hit_and_now_dead(void) const { return _noise_on_you_are_hit_and_now_dead; }
int Tp::noise_on_you_are_hit_but_still_alive(void) const { return _noise_on_you_are_hit_but_still_alive; }
int Tp::normal_placement_rules(void) const { return _normal_placement_rules; }
int Tp::on_death_drop_all_items(void) const { return _on_death_drop_all_items; }
int Tp::on_death_is_open(void) const { return _on_death_is_open; }
int Tp::range_max(void) const { return _range_max; }
int Tp::rarity(void) const { return _rarity; }
int Tp::shove_strength_mod(void) const { return _shove_strength_mod; }
int Tp::shove_strength(void) const { return _shove_strength; }
int Tp::spawn_group_radius(void) const { return _spawn_group_radius; }
int Tp::stamina_drain_on_attacking(void) const { return _stamina_drain_on_attacking; }
int Tp::stamina_drain_on_using(void) const { return _stamina_drain_on_using; }
int Tp::stamina(void) const { return _stamina; }
int Tp::stat_att_mod(void) const { return _stat_att_mod; }
int Tp::stat_att_penalty_when_idle_max(void) const { return _stat_att_penalty_when_idle_max; }
int Tp::stat_att_penalty_when_idle(void) const { return _stat_att_penalty_when_idle; }
int Tp::stat_att_penalty_when_in_deep_water(void) const { return _stat_att_penalty_when_in_deep_water; }
int Tp::stat_att_penalty_when_in_shallow_water(void) const { return _stat_att_penalty_when_in_shallow_water; }
int Tp::stat_att_penalty_when_stuck_max(void) const { return _stat_att_penalty_when_stuck_max; }
int Tp::stat_att_penalty_when_stuck(void) const { return _stat_att_penalty_when_stuck; }
int Tp::stat_att(void) const { return _stat_att; }
int Tp::stat_con_mod(void) const { return _stat_con_mod; }
int Tp::stat_con(void) const { return _stat_con; }
int Tp::stat_def_mod(void) const { return _stat_def_mod; }
int Tp::stat_def_penalty_when_idle_max(void) const { return _stat_def_penalty_when_idle_max; }
int Tp::stat_def_penalty_when_idle(void) const { return _stat_def_penalty_when_idle; }
int Tp::stat_def_penalty_when_in_deep_water(void) const { return _stat_def_penalty_when_in_deep_water; }
int Tp::stat_def_penalty_when_in_shallow_water(void) const { return _stat_def_penalty_when_in_shallow_water; }
int Tp::stat_def_penalty_when_stuck_max(void) const { return _stat_def_penalty_when_stuck_max; }
int Tp::stat_def_penalty_when_stuck(void) const { return _stat_def_penalty_when_stuck; }
int Tp::stat_def(void) const { return _stat_def; }
int Tp::stat_dex_mod(void) const { return _stat_dex_mod; }
int Tp::stat_dex(void) const { return _stat_dex; }
int Tp::stat_luck_mod(void) const { return _stat_luck_mod; }
int Tp::stat_luck(void) const { return _stat_luck; }
int Tp::stats02(void) const { return _stats02; }
int Tp::stats03(void) const { return _stats03; }
int Tp::stats04(void) const { return _stats04; }
int Tp::stats05(void) const { return _stats05; }
int Tp::stats06(void) const { return _stats06; }
int Tp::stats07(void) const { return _stats07; }
int Tp::stats09(void) const { return _stats09; }
int Tp::stat_str_mod(void) const { return _stat_str_mod; }
int Tp::stat_str(void) const { return _stat_str; }
int Tp::teleport_distance(void) const { return _teleport_distance; }
int Tp::temperature_max(void) const { return _temperature_max; }
int Tp::temperature_min(void) const { return _temperature_min; }
int Tp::temperature_sensitive_to_sudden_changes(void) const { return _temperature_sensitive_to_sudden_changes; }
int Tp::temperature_sensitive(void) const { return _temperature_sensitive; }
int Tp::temperature(void) const { return _temperature; }
int Tp::thing_size(void) const { return _thing_size; }
int Tp::tick_prio(void) const { return _tick_prio; }
int Tp::unused_chance1_d1000(void) const { return _unused_chance1_d1000; }
int Tp::unused_chance2_d1000(void) const { return _unused_chance2_d1000; }
int Tp::unused_chance3_d1000(void) const { return _unused_chance3_d1000; }
int Tp::unused_chance4_d1000(void) const { return _unused_chance4_d1000; }
int Tp::unused_chance5_d1000(void) const { return _unused_chance5_d1000; }
int Tp::unused_chance6_d1000(void) const { return _unused_chance6_d1000; }
int Tp::unused_flag103(void) const { return _unused_flag103; }
int Tp::unused_flag10(void) const { return _unused_flag10; }
int Tp::unused_flag11(void) const { return _unused_flag11; }
int Tp::unused_flag123(void) const { return _unused_flag123; }
int Tp::unused_flag12(void) const { return _unused_flag12; }
int Tp::unused_flag13(void) const { return _unused_flag13; }
int Tp::unused_flag14(void) const { return _unused_flag14; }
int Tp::unused_flag15(void) const { return _unused_flag15; }
int Tp::unused_flag16(void) const { return _unused_flag16; }
int Tp::unused_flag17(void) const { return _unused_flag17; }
int Tp::unused_flag18(void) const { return _unused_flag18; }
int Tp::unused_flag19(void) const { return _unused_flag19; }
int Tp::unused_flag1(void) const { return _unused_flag1; }
int Tp::unused_flag20(void) const { return _unused_flag20; }
int Tp::unused_flag27(void) const { return _unused_flag27; }
int Tp::unused_flag2(void) const { return _unused_flag2; }
int Tp::unused_flag3(void) const { return _unused_flag3; }
int Tp::unused_flag40(void) const { return _unused_flag40; }
int Tp::unused_flag48(void) const { return _unused_flag48; }
int Tp::unused_flag4(void) const { return _unused_flag4; }
int Tp::unused_flag5(void) const { return _unused_flag5; }
int Tp::unused_flag6(void) const { return _unused_flag6; }
int Tp::unused_flag7(void) const { return _unused_flag7; }
int Tp::unused_flag8(void) const { return _unused_flag8; }
int Tp::unused_flag9(void) const { return _unused_flag9; }
int Tp::weapon_dmg(void) const { return _weapon_dmg; }
// end sort marker2 }

// begin sort marker3 {
void Tp::aggression_pct_set(int v) { _aggression_pct = v; }
void Tp::ai_detect_secret_doors_set(int v) { _ai_detect_secret_doors = v; }
void Tp::ai_resent_count_set(int v) { _ai_resent_count = v; }
void Tp::ai_wanderer_set(int v) { _ai_wanderer = v; }
void Tp::appearing_chance_d1000_set(int v) { _appearing_chance_d1000 = v; }
void Tp::attack_eater_set(int v) { _attack_eater = v; }
void Tp::attack_engulf_chance_d1000_set(int v) { _attack_engulf_chance_d1000 = v; }
void Tp::attack_humanoid_set(int v) { _attack_humanoid = v; }
void Tp::attack_living_set(int v) { _attack_living = v; }
void Tp::attack_lunge_set(int v) { _attack_lunge = v; }
void Tp::attack_meat_set(int v) { _attack_meat = v; }
void Tp::attack_no_msg_set(int v) { _attack_no_msg = v; }
void Tp::attacks_per_round_set(int v) { _attacks_per_round = v; }
void Tp::attack_undead_set(int v) { _attack_undead = v; }
void Tp::blast_min_radius_set(int v) { _blast_min_radius = v; }
void Tp::blit_bot_off_set(int v) { _blit_bot_off = v; }
void Tp::blit_left_off_set(int v) { _blit_left_off = v; }
void Tp::blit_right_off_set(int v) { _blit_right_off = v; }
void Tp::blit_top_off_set(int v) { _blit_top_off = v; }
void Tp::capacity_height_set(int v) { _capacity_height = v; }
void Tp::capacity_width_set(int v) { _capacity_width = v; }
void Tp::charge_count_set(int v) { _charge_count = v; }
void Tp::collateral_dmg_pct_set(int v) { _collateral_dmg_pct = v; }
void Tp::collision_attack_set(int v) { _collision_attack = v; }
void Tp::collision_check_set(int v) { _collision_check = v; }
void Tp::collision_hit_180_set(int v) { _collision_hit_180 = v; }
void Tp::collision_hit_360_set(int v) { _collision_hit_360 = v; }
void Tp::collision_hit_adj_set(int v) { _collision_hit_adj = v; }
void Tp::collision_hit_priority_set(int v) { _collision_hit_priority = v; }
void Tp::collision_hit_two_tiles_ahead_set(int v) { _collision_hit_two_tiles_ahead = v; }
void Tp::consume_per_bite_amount_set(int v) { _consume_per_bite_amount = v; }
void Tp::crit_chance_d10000_set(int v) { _crit_chance_d10000 = v; }
void Tp::damaged_chance_d10000_set(int v) { _dmgd_chance_d10000 = v; }
void Tp::distance_avoid_set(int v) { _distance_avoid = v; }
void Tp::distance_leader_max_set(int v) { _distance_leader_max = v; }
void Tp::distance_minion_vision_shared_set(int v) { _distance_minion_vision_shared = v; }
void Tp::distance_mob_max_set(int v) { _distance_mob_max = v; }
void Tp::distance_recruitment_max_set(int v) { _distance_recruitment_max = v; }
void Tp::distance_throw_set(int v) { _distance_throw = v; }
void Tp::distance_vision_set(int v) { _distance_vision = v; }
void Tp::dmg_received_doubled_from_acid_set(int v) { _dmg_received_doubled_from_acid = v; }
void Tp::dmg_received_doubled_from_cold_set(int v) { _dmg_received_doubled_from_cold = v; }
void Tp::dmg_received_doubled_from_fire_set(int v) { _dmg_received_doubled_from_fire = v; }
void Tp::dmg_received_doubled_from_necrosis_set(int v) { _dmg_received_doubled_from_necrosis = v; }
void Tp::dmg_received_doubled_from_poison_set(int v) { _dmg_received_doubled_from_poison = v; }
void Tp::dmg_received_doubled_from_water_set(int v) { _dmg_received_doubled_from_water = v; }
void Tp::effect_radius_set(int v) { _effect_radius = v; }
void Tp::enchant_level_set(int v) { _enchant_level = v; }
void Tp::enchant_max_set(int v) { _enchant_max = v; }
void Tp::environ_avoids_acid_set(int v) { _environ_avoids_acid = v; }
void Tp::environ_avoids_cold_set(int v) { _environ_avoids_cold = v; }
void Tp::environ_avoids_fire_set(int v) { _environ_avoids_fire = v; }
void Tp::environ_avoids_necrosis_set(int v) { _environ_avoids_necrosis = v; }
void Tp::environ_avoids_poison_set(int v) { _environ_avoids_poison = v; }
void Tp::environ_avoids_water_set(int v) { _environ_avoids_water = v; }
void Tp::equip_carry_anim_set(const std::string &v) { _equip_carry_anim = v; }
void Tp::gfx_anim_use_set(const std::string &v) { _gfx_anim_use = v; }
void Tp::gfx_ascii_animated_set(int v) { _gfx_ascii_animated = v; }
void Tp::gfx_ascii_bg_color_spread_alpha_set(int v) { _gfx_ascii_bg_color_spread_alpha = v; }
void Tp::gfx_ascii_bg_color_spread_blue_set(int v) { _gfx_ascii_bg_color_spread_blue = v; }
void Tp::gfx_ascii_bg_color_spread_green_set(int v) { _gfx_ascii_bg_color_spread_green = v; }
void Tp::gfx_ascii_bg_color_spread_hue_set(int v) { _gfx_ascii_bg_color_spread_hue = v; }
void Tp::gfx_ascii_bg_color_spread_red_set(int v) { _gfx_ascii_bg_color_spread_red = v; }
void Tp::gfx_ascii_color_bg_unchanged_by_lights_set(int v) { _gfx_ascii_color_bg_unchanged_by_lights = v; }
void Tp::gfx_ascii_color_fg_unchanged_by_lights_set(int v) { _gfx_ascii_color_fg_unchanged_by_lights = v; }
void Tp::gfx_ascii_color_is_animated_set(int v) { _gfx_ascii_color_is_animated = v; }
void Tp::gfx_ascii_fade_with_dist_set(int v) { _gfx_ascii_fade_with_dist = v; }
void Tp::gfx_ascii_fg_color_spread_alpha_set(int v) { _gfx_ascii_fg_color_spread_alpha = v; }
void Tp::gfx_ascii_fg_color_spread_blue_set(int v) { _gfx_ascii_fg_color_spread_blue = v; }
void Tp::gfx_ascii_fg_color_spread_green_set(int v) { _gfx_ascii_fg_color_spread_green = v; }
void Tp::gfx_ascii_fg_color_spread_hue_set(int v) { _gfx_ascii_fg_color_spread_hue = v; }
void Tp::gfx_ascii_fg_color_spread_red_set(int v) { _gfx_ascii_fg_color_spread_red = v; }
void Tp::gfx_ascii_shown_as_gray_in_shadow_set(int v) { _gfx_ascii_shown_as_gray_in_shadow = v; }
void Tp::gfx_ascii_shown_in_bg_set(int v) { _gfx_ascii_shown_in_bg = v; }
void Tp::gfx_ascii_shown_set(int v) { _gfx_ascii_shown = v; }
void Tp::gfx_glows_set(int v) { _gfx_glows = v; }
void Tp::gfx_on_fire_anim_set(int v) { _gfx_on_fire_anim = v; }
void Tp::gfx_pixelart_animated_can_hflip_set(int v) { _gfx_pixelart_animated_can_hflip = v; }
void Tp::gfx_pixelart_animated_can_vflip_set(int v) { _gfx_pixelart_animated_can_vflip = v; }
void Tp::gfx_pixelart_animated_no_dir_set(int v) { _gfx_pixelart_animated_no_dir = v; }
void Tp::gfx_pixelart_animated_set(int v) { _gfx_pixelart_animated = v; }
void Tp::gfx_pixelart_anim_synced_with_owner_set(int v) { _gfx_pixelart_anim_synced_with_owner = v; }
void Tp::gfx_pixelart_attack_anim_set(int v) { _gfx_pixelart_attack_anim = v; }
void Tp::gfx_pixelart_bounce_always_set(int v) { _gfx_pixelart_bounce_always = v; }
void Tp::gfx_pixelart_bounce_on_move_set(int v) { _gfx_pixelart_bounce_on_move = v; }
void Tp::gfx_pixelart_equip_carry_anim_set(int v) { _gfx_pixelart_equip_carry_anim = v; }
void Tp::gfx_pixelart_flickers_set(int v) { _gfx_pixelart_flickers = v; }
void Tp::gfx_pixelart_health_bar_autohide_set(int v) { _gfx_pixelart_health_bar_autohide = v; }
void Tp::gfx_pixelart_health_bar_only_when_awake_set(int v) { _gfx_pixelart_health_bar_only_when_awake = v; }
void Tp::gfx_pixelart_health_bar_shown_set(int v) { _gfx_pixelart_health_bar_shown = v; }
void Tp::gfx_pixelart_oversized_and_centered_set(int v) { _gfx_pixelart_oversized_and_centered = v; }
void Tp::gfx_pixelart_oversized_and_on_floor_set(int v) { _gfx_pixelart_oversized_and_on_floor = v; }
void Tp::gfx_pixelart_reflection_set(int v) { _gfx_pixelart_reflection = v; }
void Tp::gfx_pixelart_shadow_long_set(int v) { _gfx_pixelart_shadow_long = v; }
void Tp::gfx_pixelart_shadow_set(int v) { _gfx_pixelart_shadow = v; }
void Tp::gfx_pixelart_shadow_short_set(int v) { _gfx_pixelart_shadow_short = v; }
void Tp::gfx_pixelart_shadow_solid_set(int v) { _gfx_pixelart_shadow_solid = v; }
void Tp::gfx_pixelart_shadow_very_short_set(int v) { _gfx_pixelart_shadow_very_short = v; }
void Tp::gfx_pixelart_show_asleep_anim_set(int v) { _gfx_pixelart_show_asleep_anim = v; }
void Tp::gfx_pixelart_show_highlighted_set(int v) { _gfx_pixelart_show_highlighted = v; }
void Tp::gfx_pixelart_shown_in_bg_set(int v) { _gfx_pixelart_shown_in_bg = v; }
void Tp::gfx_pixelart_show_outlined_set(int v) { _gfx_pixelart_show_outlined = v; }
void Tp::gfx_pixelart_show_square_outlined_set(int v) { _gfx_pixelart_show_square_outlined = v; }
void Tp::gfx_pixelart_submergable_set(int v) { _gfx_pixelart_submergable = v; }
void Tp::gfx_pixelart_wobbles_when_hit_set(int v) { _gfx_pixelart_wobbles_when_hit = v; }
void Tp::gfx_targetted_laser_set(const std::string &v) { _gfx_targetted_laser = v; }
void Tp::gfx_targetted_radial_set(const std::string &v) { _gfx_targetted_radial = v; }
void Tp::gfx_water_set(int v) { _gfx_water = v; }
void Tp::hunger_clock_tick_freq_set(int v) { _hunger_clock_tick_freq = v; }
void Tp::hunger_is_hunger_level_hungry_at_pct_set(int v) { _hunger_is_hunger_level_hungry_at_pct = v; }
void Tp::hunger_is_hunger_level_starving_at_pct_set(int v) { _hunger_is_hunger_level_starving_at_pct = v; }
void Tp::hunger_is_insatiable_set(int v) { _hunger_is_insatiable = v; }
void Tp::internal_has_dir_anim_set(int v) { _internal_has_dir_anim = v; }
void Tp::internal_has_hp_anim_set(int v) { _internal_has_hp_anim = v; }
void Tp::is_able_to_attack_mobs_set(int v) { _is_able_to_attack_mobs = v; }
void Tp::is_able_to_attack_owner_set(int v) { _is_able_to_attack_owner = v; }
void Tp::is_able_to_be_surprised_set(int v) { _is_able_to_be_surprised = v; }
void Tp::is_able_to_break_down_doors_set(int v) { _is_able_to_break_down_doors = v; }
void Tp::is_able_to_break_out_of_ice_set(int v) { _is_able_to_break_out_of_ice = v; }
void Tp::is_able_to_break_out_of_webs_set(int v) { _is_able_to_break_out_of_webs = v; }
void Tp::is_able_to_burn_set(int v) { _is_able_to_burn = v; }
void Tp::is_able_to_change_levels_set(int v) { _is_able_to_change_levels = v; }
void Tp::is_able_to_collect_keys_set(int v) { _is_able_to_collect_keys = v; }
void Tp::is_able_to_enchant_items_set(int v) { _is_able_to_enchant_items = v; }
void Tp::is_able_to_fall_set(int v) { _is_able_to_fall = v; }
void Tp::is_able_to_fire_at_close_range_set(int v) { _is_able_to_fire_at_close_range = v; }
void Tp::is_able_to_fire_at_set(int v) { _is_able_to_fire_at = v; }
void Tp::is_able_to_follow_set(int v) { _is_able_to_follow = v; }
void Tp::is_able_to_freeze_set(int v) { _is_able_to_freeze = v; }
void Tp::is_able_to_grapple_chance_d1000_set(int v) { _is_able_to_grapple_chance_d1000 = v; }
void Tp::is_able_to_grapple_set(int v) { _is_able_to_grapple = v; }
void Tp::is_able_to_jump_attack_chance_d1000_set(int v) { _is_able_to_jump_attack_chance_d1000 = v; }
void Tp::is_able_to_jump_attack_set(int v) { _is_able_to_jump_attack = v; }
void Tp::is_able_to_jump_escape_set(int v) { _is_able_to_jump_escape = v; }
void Tp::is_able_to_jump_on_low_hp_chance_d1000_set(int v) { _is_able_to_jump_on_low_hp_chance_d1000 = v; }
void Tp::is_able_to_jump_onto_chance_d1000_set(int v) { _is_able_to_jump_onto_chance_d1000 = v; }
void Tp::is_able_to_jump_onto_set(int v) { _is_able_to_jump_onto = v; }
void Tp::is_able_to_jump_randomly_chance_d1000_set(int v) { _is_able_to_jump_randomly_chance_d1000 = v; }
void Tp::is_able_to_jump_set(int v) { _is_able_to_jump = v; }
void Tp::is_able_to_jump_without_tiring_set(int v) { _is_able_to_jump_without_tiring = v; }
void Tp::is_able_to_learn_skills_set(int v) { _is_able_to_learn_skills = v; }
void Tp::is_able_to_live_out_of_water_set(int v) { _is_able_to_live_out_of_water = v; }
void Tp::is_able_to_melt_set(int v) { _is_able_to_melt = v; }
void Tp::is_able_to_move_diagonally_set(int v) { _is_able_to_move_diagonally = v; }
void Tp::is_able_to_open_doors_set(int v) { _is_able_to_open_doors = v; }
void Tp::is_able_to_rest_set(int v) { _is_able_to_rest = v; }
void Tp::is_able_to_see_in_the_dark_set(int v) { _is_able_to_see_in_the_dark = v; }
void Tp::is_able_to_see_invisible_set(int v) { _is_able_to_see_invisible = v; }
void Tp::is_able_to_see_through_doors_set(int v) { _is_able_to_see_through_doors = v; }
void Tp::is_able_to_shove_chance_d1000_set(int v) { _is_able_to_shove_chance_d1000 = v; }
void Tp::is_able_to_shove_set(int v) { _is_able_to_shove = v; }
void Tp::is_able_to_sleep_set(int v) { _is_able_to_sleep = v; }
void Tp::is_able_to_spawn_things_set(int v) { _is_able_to_spawn_things = v; }
void Tp::is_able_to_swim_set(int v) { _is_able_to_swim = v; }
void Tp::is_able_to_teleport_attack_chance_d1000_set(int v) { _is_able_to_teleport_attack_chance_d1000 = v; }
void Tp::is_able_to_teleport_attack_set(int v) { _is_able_to_teleport_attack = v; }
void Tp::is_able_to_teleport_escape_set(int v) { _is_able_to_teleport_escape = v; }
void Tp::is_able_to_teleport_without_tiring_set(int v) { _is_able_to_teleport_without_tiring = v; }
void Tp::is_able_to_tire_set(int v) { _is_able_to_tire = v; }
void Tp::is_able_to_use_amulet_set(int v) { _is_able_to_use_amulet = v; }
void Tp::is_able_to_use_armor_set(int v) { _is_able_to_use_armor = v; }
void Tp::is_able_to_use_boots_set(int v) { _is_able_to_use_boots = v; }
void Tp::is_able_to_use_cloak_set(int v) { _is_able_to_use_cloak = v; }
void Tp::is_able_to_use_gauntlet_set(int v) { _is_able_to_use_gauntlet = v; }
void Tp::is_able_to_use_helmet_set(int v) { _is_able_to_use_helmet = v; }
void Tp::is_able_to_use_rings_set(int v) { _is_able_to_use_rings = v; }
void Tp::is_able_to_use_shield_set(int v) { _is_able_to_use_shield = v; }
void Tp::is_able_to_use_staffs_set(int v) { _is_able_to_use_staffs = v; }
void Tp::is_able_to_use_weapons_set(int v) { _is_able_to_use_weapons = v; }
void Tp::is_able_to_walk_through_walls_set(int v) { _is_able_to_walk_through_walls = v; }
void Tp::is_acid_set(int v) { _is_acid = v; }
void Tp::is_air_breather_set(int v) { _is_air_breather = v; }
void Tp::is_alive_on_end_of_anim_set(int v) { _is_alive_on_end_of_anim = v; }
void Tp::is_allied_with_set(const std::string &v) { _is_allied_with = v; }
void Tp::is_always_hit_set(int v) { _is_always_hit = v; }
void Tp::is_always_submerged_set(int v) { _is_always_submerged = v; }
void Tp::is_amulet_set(int v) { _is_amulet = v; }
void Tp::is_aquatic_set(int v) { _is_aquatic = v; }
void Tp::is_armor_set(int v) { _is_armor = v; }
void Tp::is_ascend_dungeon_set(int v) { _is_ascend_dungeon = v; }
void Tp::is_ascend_sewer_set(int v) { _is_ascend_sewer = v; }
void Tp::is_asleep_initially_set(int v) { _is_asleep_initially = v; }
void Tp::is_attackable_by_monst_set(int v) { _is_attackable_by_monst = v; }
void Tp::is_attackable_by_player_set(int v) { _is_attackable_by_player = v; }
void Tp::is_auto_collect_item_set(int v) { _is_auto_collect_item = v; }
void Tp::is_auto_equipped_set(int v) { _is_auto_equipped = v; }
void Tp::is_auto_throw_set(int v) { _is_auto_throw = v; }
void Tp::is_auto_use_set(int v) { _is_auto_use = v; }
void Tp::is_bag_item_container_set(int v) { _is_bag_item_container = v; }
void Tp::is_bag_item_not_stackable_set(int v) { _is_bag_item_not_stackable = v; }
void Tp::is_bag_item_set(int v) { _is_bag_item = v; }
void Tp::is_bag_set(int v) { _is_bag = v; }
void Tp::is_barrel_set(int v) { _is_barrel = v; }
void Tp::is_basalt_set(int v) { _is_basalt = v; }
void Tp::is_biome_dungeon_set(int v) { _is_biome_dungeon = v; }
void Tp::is_biome_sewer_set(int v) { _is_biome_sewer = v; }
void Tp::is_biome_swamp_set(int v) { _is_biome_swamp = v; }
void Tp::is_biome_unused_set(int v) { _is_biome_unused = v; }
void Tp::is_bleeder_set(int v) { _is_bleeder = v; }
void Tp::is_block_of_ice_set(int v) { _is_block_of_ice = v; }
void Tp::is_bones_set(int v) { _is_bones = v; }
void Tp::is_boots_set(int v) { _is_boots = v; }
void Tp::is_brazier_set(int v) { _is_brazier = v; }
void Tp::is_bridge_set(int v) { _is_bridge = v; }
void Tp::is_brittle_set(int v) { _is_brittle = v; }
void Tp::is_buff_set(int v) { _is_buff = v; }
void Tp::is_carnivorous_plant_set(int v) { _is_carnivorous_plant = v; }
void Tp::is_carrier_of_treasure_class_a_d1000_set(int v) { _is_carrier_of_treasure_class_a_d1000 = v; }
void Tp::is_carrier_of_treasure_class_b_d1000_set(int v) { _is_carrier_of_treasure_class_b_d1000 = v; }
void Tp::is_carrier_of_treasure_class_c_d1000_set(int v) { _is_carrier_of_treasure_class_c_d1000 = v; }
void Tp::is_carrier_of_weapon_class_a_d1000_set(int v) { _is_carrier_of_weapon_class_a_d1000 = v; }
void Tp::is_carrier_of_weapon_class_b_d1000_set(int v) { _is_carrier_of_weapon_class_b_d1000 = v; }
void Tp::is_carrier_of_weapon_class_c_d1000_set(int v) { _is_carrier_of_weapon_class_c_d1000 = v; }
void Tp::is_chasm_set(int v) { _is_chasm = v; }
void Tp::is_cloak_set(int v) { _is_cloak = v; }
void Tp::is_cold_set(int v) { _is_cold = v; }
void Tp::is_collectable_set(int v) { _is_collectable = v; }
void Tp::is_collected_as_gold_set(int v) { _is_collected_as_gold = v; }
void Tp::is_collected_as_keys_set(int v) { _is_collected_as_keys = v; }
void Tp::is_combustible_set(int v) { _is_combustible = v; }
void Tp::is_corpse_on_death_set(int v) { _is_corpse_on_death = v; }
void Tp::is_corpse_with_bones_set(int v) { _is_corpse_with_bones = v; }
void Tp::is_corridor_set(int v) { _is_corridor = v; }
void Tp::is_cowardly_set(int v) { _is_cowardly = v; }
void Tp::is_critical_to_level_set(int v) { _is_critical_to_level = v; }
void Tp::is_crushable_set(int v) { _is_crushable = v; }
void Tp::is_crystal_set(int v) { _is_crystal = v; }
void Tp::is_cursor_can_hover_over_set(int v) { _is_cursor_can_hover_over = v; }
void Tp::is_cursor_can_hover_over_x2_click_set(int v) { _is_cursor_can_hover_over_x2_click = v; }
void Tp::is_cursor_path_blocker_set(int v) { _is_cursor_path_blocker = v; }
void Tp::is_cursor_path_hazard_set(int v) { _is_cursor_path_hazard = v; }
void Tp::is_cursor_path_set(int v) { _is_cursor_path = v; }
void Tp::is_cursor_set(int v) { _is_cursor = v; }
void Tp::is_dagger_set(int v) { _is_dagger = v; }
void Tp::is_dead_on_end_of_anim_set(int v) { _is_dead_on_end_of_anim = v; }
void Tp::is_dead_on_falling_set(int v) { _is_dead_on_falling = v; }
void Tp::is_dead_on_shove_set(int v) { _is_dead_on_shove = v; }
void Tp::is_debuff_set(int v) { _is_debuff = v; }
void Tp::is_debug_path_set(int v) { _is_debug_path = v; }
void Tp::is_debug_type_set(int v) { _is_debug_type = v; }
void Tp::is_deep_water_set(int v) { _is_deep_water = v; }
void Tp::is_deep_water_swimmer_set(int v) { _is_deep_water_swimmer = v; }
void Tp::is_descend_dungeon_set(int v) { _is_descend_dungeon = v; }
void Tp::is_descend_sewer_set(int v) { _is_descend_sewer = v; }
void Tp::is_described_when_hovering_over_set(int v) { _is_described_when_hovering_over = v; }
void Tp::is_destroyed_on_hit_or_miss_set(int v) { _is_destroyed_on_hit_or_miss = v; }
void Tp::is_destroyed_on_hitting_set(int v) { _is_destroyed_on_hitting = v; }
void Tp::is_dirt_set(int v) { _is_dirt = v; }
void Tp::is_door_set(int v) { _is_door = v; }
void Tp::is_droppable_set(int v) { _is_droppable = v; }
void Tp::is_dry_grass_set(int v) { _is_dry_grass = v; }
void Tp::is_dry_grass_trampled_set(int v) { _is_dry_grass_trampled = v; }
void Tp::is_eater_of_amulets_set(int v) { _is_eater_of_amulets = v; }
void Tp::is_eater_of_armor_set(int v) { _is_eater_of_armor = v; }
void Tp::is_eater_of_boots_set(int v) { _is_eater_of_boots = v; }
void Tp::is_eater_of_cloaks_set(int v) { _is_eater_of_cloaks = v; }
void Tp::is_eater_of_food_set(int v) { _is_eater_of_food = v; }
void Tp::is_eater_of_gauntlets_set(int v) { _is_eater_of_gauntlets = v; }
void Tp::is_eater_of_green_blood_set(int v) { _is_eater_of_green_blood = v; }
void Tp::is_eater_of_helmets_set(int v) { _is_eater_of_helmets = v; }
void Tp::is_eater_of_jelly_set(int v) { _is_eater_of_jelly = v; }
void Tp::is_eater_of_magical_items_set(int v) { _is_eater_of_magical_items = v; }
void Tp::is_eater_of_meat_set(int v) { _is_eater_of_meat = v; }
void Tp::is_eater_of_potions_set(int v) { _is_eater_of_potions = v; }
void Tp::is_eater_of_red_blood_set(int v) { _is_eater_of_red_blood = v; }
void Tp::is_eater_of_rings_set(int v) { _is_eater_of_rings = v; }
void Tp::is_eater_of_shields_set(int v) { _is_eater_of_shields = v; }
void Tp::is_eater_of_staffs_set(int v) { _is_eater_of_staffs = v; }
void Tp::is_eater_of_treasure_set(int v) { _is_eater_of_treasure = v; }
void Tp::is_eater_of_weapons_set(int v) { _is_eater_of_weapons = v; }
void Tp::is_enchantable_set(int v) { _is_enchantable = v; }
void Tp::is_enchantstone_set(int v) { _is_enchantstone = v; }
void Tp::is_engulfer_set(int v) { _is_engulfer = v; }
void Tp::is_ethereal_mob_set(int v) { _is_ethereal_mob = v; }
void Tp::is_ethereal_set(int v) { _is_ethereal = v; }
void Tp::is_exit_finder_set(int v) { _is_exit_finder = v; }
void Tp::is_explorer_set(int v) { _is_explorer = v; }
void Tp::is_explosion_set(int v) { _is_explosion = v; }
void Tp::is_fearless_set(int v) { _is_fearless = v; }
void Tp::is_fire_set(int v) { _is_fire = v; }
void Tp::is_flat_set(int v) { _is_flat = v; }
void Tp::is_floating_set(int v) { _is_floating = v; }
void Tp::is_floor_deco_set(int v) { _is_floor_deco = v; }
void Tp::is_floor_set(int v) { _is_floor = v; }
void Tp::is_flying_set(int v) { _is_flying = v; }
void Tp::is_foliage_set(int v) { _is_foliage = v; }
void Tp::is_food_set(int v) { _is_food = v; }
void Tp::is_gas_blocker_set(int v) { _is_gas_blocker = v; }
void Tp::is_gauntlet_set(int v) { _is_gauntlet = v; }
void Tp::is_gelatinous_set(int v) { _is_gelatinous = v; }
void Tp::is_glass_set(int v) { _is_glass = v; }
void Tp::is_gold_set(int v) { _is_gold = v; }
void Tp::is_green_blooded_set(int v) { _is_green_blooded = v; }
void Tp::is_green_blood_set(int v) { _is_green_blood = v; }
void Tp::is_green_splatter_set(int v) { _is_green_splatter = v; }
void Tp::is_hard_set(int v) { _is_hard = v; }
void Tp::is_hazard_set(int v) { _is_hazard = v; }
void Tp::is_health_booster_set(int v) { _is_health_booster = v; }
void Tp::is_heavy_set(int v) { _is_heavy = v; }
void Tp::is_helmet_set(int v) { _is_helmet = v; }
void Tp::is_hittable_set(int v) { _is_hittable = v; }
void Tp::is_humanoid_set(int v) { _is_humanoid = v; }
void Tp::is_immune_to_acid_set(int v) { _is_immune_to_acid = v; }
void Tp::is_immune_to_cold_set(int v) { _is_immune_to_cold = v; }
void Tp::is_immune_to_draining_set(int v) { _is_immune_to_draining = v; }
void Tp::is_immune_to_electricity_set(int v) { _is_immune_to_electricity = v; }
void Tp::is_immune_to_fire_set(int v) { _is_immune_to_fire = v; }
void Tp::is_immune_to_necrosis_set(int v) { _is_immune_to_necrosis = v; }
void Tp::is_immune_to_negation_set(int v) { _is_immune_to_negation = v; }
void Tp::is_immune_to_poison_set(int v) { _is_immune_to_poison = v; }
void Tp::is_immune_to_spiderwebs_set(int v) { _is_immune_to_spiderwebs = v; }
void Tp::is_immune_to_water_set(int v) { _is_immune_to_water = v; }
void Tp::is_intelligent_set(int v) { _is_intelligent = v; }
void Tp::is_interesting_set(int v) { _is_interesting = v; }
void Tp::is_internal_set(int v) { _is_internal = v; }
void Tp::is_invisible_set(int v) { _is_invisible = v; }
void Tp::is_item_carrier_set(int v) { _is_item_carrier = v; }
void Tp::is_item_collector_set(int v) { _is_item_collector = v; }
void Tp::is_item_organic_set(int v) { _is_item_organic = v; }
void Tp::is_item_set(int v) { _is_item = v; }
void Tp::is_item_targetted_set(int v) { _is_item_targetted = v; }
void Tp::is_jelly_set(int v) { _is_jelly = v; }
void Tp::is_key_set(int v) { _is_key = v; }
void Tp::is_key_special_set(int v) { _is_key_special = v; }
void Tp::is_laser_set(int v) { _is_laser = v; }
void Tp::is_lava_set(int v) { _is_lava = v; }
void Tp::is_lifeless_set(int v) { _is_lifeless = v; }
void Tp::is_light_blocker_for_monst_set(int v) { _is_light_blocker_for_monst = v; }
void Tp::is_light_blocker_set(int v) { _is_light_blocker = v; }
void Tp::is_lightning_set(int v) { _is_lightning = v; }
void Tp::is_limb_set(int v) { _is_limb = v; }
void Tp::is_living_set(int v) { _is_living = v; }
void Tp::is_loggable_set(int v) { _is_loggable = v; }
void Tp::is_magical_set(int v) { _is_magical = v; }
void Tp::is_map_beast_set(int v) { _is_map_beast = v; }
void Tp::is_map_treasure_set(int v) { _is_map_treasure = v; }
void Tp::is_meat_set(int v) { _is_meat = v; }
void Tp::is_metal_set(int v) { _is_metal = v; }
void Tp::is_minion_set(int v) { _is_minion = v; }
void Tp::is_mob_challenge_class_a_set(int v) { _is_mob_challenge_class_a = v; }
void Tp::is_mob_challenge_class_b_set(int v) { _is_mob_challenge_class_b = v; }
void Tp::is_mob_set(int v) { _is_mob = v; }
void Tp::is_monst_class_a_set(int v) { _is_monst_class_a = v; }
void Tp::is_monst_class_b_set(int v) { _is_monst_class_b = v; }
void Tp::is_monst_class_c_set(int v) { _is_monst_class_c = v; }
void Tp::is_monst_class_d_set(int v) { _is_monst_class_d = v; }
void Tp::is_monst_class_e_set(int v) { _is_monst_class_e = v; }
void Tp::is_monst_pack_set(int v) { _is_monst_pack = v; }
void Tp::is_monst_set(int v) { _is_monst = v; }
void Tp::is_moveable_set(int v) { _is_moveable = v; }
void Tp::is_msg_allowed_hears_something_set(int v) { _is_msg_allowed_hears_something = v; }
void Tp::is_msg_allowed_is_dead_set(int v) { _is_msg_allowed_is_dead = v; }
void Tp::is_msg_allowed_is_seen_set(int v) { _is_msg_allowed_is_seen = v; }
void Tp::is_msg_allowed_is_surprised_set(int v) { _is_msg_allowed_is_surprised = v; }
void Tp::is_msg_allowed_is_wounded_set(int v) { _is_msg_allowed_is_wounded = v; }
void Tp::is_msg_allowed_senses_danger_set(int v) { _is_msg_allowed_senses_danger = v; }
void Tp::is_msg_set(int v) { _is_msg = v; }
void Tp::is_necrotic_danger_level_set(int v) { _is_necrotic_danger_level = v; }
void Tp::is_no_tile_set(int v) { _is_no_tile = v; }
void Tp::is_obs_destructable_set(int v) { _is_obs_destructable = v; }
void Tp::is_obs_for_ai_set(int v) { _is_obs_for_ai = v; }
void Tp::is_obs_for_jump_landing_set(int v) { _is_obs_for_jump_landing = v; }
void Tp::is_obs_for_shoving_set(int v) { _is_obs_for_shoving = v; }
void Tp::is_obs_in_the_way_for_firing_set(int v) { _is_obs_in_the_way_for_firing = v; }
void Tp::is_obs_in_the_way_for_jumping_set(int v) { _is_obs_in_the_way_for_jumping = v; }
void Tp::is_obs_in_the_way_for_throwing_set(int v) { _is_obs_in_the_way_for_throwing = v; }
void Tp::is_obs_wall_or_door_set(int v) { _is_obs_wall_or_door = v; }
void Tp::is_obs_when_dead_set(int v) { _is_obs_when_dead = v; }
void Tp::is_openable_set(int v) { _is_openable = v; }
void Tp::is_organic_set(int v) { _is_organic = v; }
void Tp::is_pillar_set(int v) { _is_pillar = v; }
void Tp::is_plant_set(int v) { _is_plant = v; }
void Tp::is_player_set(int v) { _is_player = v; }
void Tp::is_poisonous_danger_level_set(int v) { _is_poisonous_danger_level = v; }
void Tp::is_potion_set(int v) { _is_potion = v; }
void Tp::is_projectile_set(int v) { _is_projectile = v; }
void Tp::is_red_blooded_set(int v) { _is_red_blooded = v; }
void Tp::is_red_blood_set(int v) { _is_red_blood = v; }
void Tp::is_red_splatter_set(int v) { _is_red_splatter = v; }
void Tp::is_removable_if_out_of_slots_set(int v) { _is_removable_if_out_of_slots = v; }
void Tp::is_resurrectable_set(int v) { _is_resurrectable = v; }
void Tp::is_ring_set(int v) { _is_ring = v; }
void Tp::is_ripple_set(int v) { _is_ripple = v; }
void Tp::is_rock_set(int v) { _is_rock = v; }
void Tp::is_rusty_set(int v) { _is_rusty = v; }
void Tp::is_secret_door_set(int v) { _is_secret_door = v; }
void Tp::is_sewer_wall_set(int v) { _is_sewer_wall = v; }
void Tp::is_shallow_water_set(int v) { _is_shallow_water = v; }
void Tp::is_shallow_water_swimmer_set(int v) { _is_shallow_water_swimmer = v; }
void Tp::is_shield_set(int v) { _is_shield = v; }
void Tp::is_shovable_and_sticky_set(int v) { _is_shovable_and_sticky = v; }
void Tp::is_shovable_set(int v) { _is_shovable = v; }
void Tp::is_skill_set(int v) { _is_skill = v; }
void Tp::is_skillstone_set(int v) { _is_skillstone = v; }
void Tp::is_slippery_set(int v) { _is_slippery = v; }
void Tp::is_smoke_set(int v) { _is_smoke = v; }
void Tp::is_snake_set(int v) { _is_snake = v; }
void Tp::is_soft_set(int v) { _is_soft = v; }
void Tp::is_spider_set(int v) { _is_spider = v; }
void Tp::is_spiderweb_set(int v) { _is_spiderweb = v; }
void Tp::is_staff_set(int v) { _is_staff = v; }
void Tp::is_steal_item_chance_d1000_set(int v) { _is_steal_item_chance_d1000 = v; }
void Tp::is_steam_set(int v) { _is_steam = v; }
void Tp::is_sticky_set(int v) { _is_sticky = v; }
void Tp::is_stone_set(int v) { _is_stone = v; }
void Tp::is_swimmer_set(int v) { _is_swimmer = v; }
void Tp::is_sword_set(int v) { _is_sword = v; }
void Tp::is_target_radial_set(int v) { _is_target_radial = v; }
void Tp::is_target_select_set(int v) { _is_target_select = v; }
void Tp::is_tentacle_set(int v) { _is_tentacle = v; }
void Tp::is_the_grid_set(int v) { _is_the_grid = v; }
void Tp::is_thief_set(int v) { _is_thief = v; }
void Tp::is_throwable_set(int v) { _is_throwable = v; }
void Tp::is_tickable_set(int v) { _is_tickable = v; }
void Tp::is_tireless_set(int v) { _is_tireless = v; }
void Tp::is_tmp_thing_set(int v) { _is_tmp_thing = v; }
void Tp::is_torch_set(int v) { _is_torch = v; }
void Tp::is_treasure_chest_set(int v) { _is_treasure_chest = v; }
void Tp::is_treasure_class_a_set(int v) { _is_treasure_class_a = v; }
void Tp::is_treasure_class_b_set(int v) { _is_treasure_class_b = v; }
void Tp::is_treasure_class_c_set(int v) { _is_treasure_class_c = v; }
void Tp::is_treasure_set(int v) { _is_treasure = v; }
void Tp::is_treasure_type_set(int v) { _is_treasure_type = v; }
void Tp::is_undead_set(int v) { _is_undead = v; }
void Tp::is_usable_set(int v) { _is_usable = v; }
void Tp::is_used_when_thrown_set(int v) { _is_used_when_thrown = v; }
void Tp::is_very_combustible_set(int v) { _is_very_combustible = v; }
void Tp::is_very_hard_set(int v) { _is_very_hard = v; }
void Tp::is_very_heavy_set(int v) { _is_very_heavy = v; }
void Tp::is_wall_dungeon_set(int v) { _is_wall_dungeon = v; }
void Tp::is_wall_set(int v) { _is_wall = v; }
void Tp::is_weapon_class_a_set(int v) { _is_weapon_class_a = v; }
void Tp::is_weapon_class_b_set(int v) { _is_weapon_class_b = v; }
void Tp::is_weapon_class_c_set(int v) { _is_weapon_class_c = v; }
void Tp::is_weapon_set(int v) { _is_weapon = v; }
void Tp::is_wet_grass_set(int v) { _is_wet_grass = v; }
void Tp::is_wooden_set(int v) { _is_wooden = v; }
void Tp::item_height_set(int v) { _item_height = v; }
void Tp::item_width_set(int v) { _item_width = v; }
void Tp::jump_distance_mod_set(int v) { _jump_distance_mod = v; }
void Tp::jump_distance_set(int v) { _jump_distance = v; }
void Tp::light_color_set(const std::string &v) { _light_color = v; }
void Tp::light_dist_set(int v) { _light_dist = v; }
void Tp::melting_chance_d1000_set(int v) { _melting_chance_d1000 = v; }
void Tp::minion_limit_set(int v) { _minion_limit = v; }
void Tp::move_speed_mod_set(int v) { _move_speed_mod = v; }
void Tp::move_speed_set(int v) { _move_speed = v; }
void Tp::name_set(const std::string &v) { _name = v; }
void Tp::noise_additional_on_jump_end_set(int v) { _noise_additional_on_jump_end = v; }
void Tp::noise_additional_on_teleporting_set(int v) { _noise_additional_on_teleporting = v; }
void Tp::noise_blocker_set(int v) { _noise_blocker = v; }
void Tp::noise_decibels_hearing_set(int v) { _noise_decibels_hearing = v; }
void Tp::noise_on_born_set(int v) { _noise_on_born = v; }
void Tp::noise_on_dropping_set(int v) { _noise_on_dropping = v; }
void Tp::noise_on_moving_set(int v) { _noise_on_moving = v; }
void Tp::noise_on_open_set(int v) { _noise_on_open = v; }
void Tp::noise_on_you_are_hit_and_now_dead_set(int v) { _noise_on_you_are_hit_and_now_dead = v; }
void Tp::noise_on_you_are_hit_but_still_alive_set(int v) { _noise_on_you_are_hit_but_still_alive = v; }
void Tp::normal_placement_rules_set(int v) { _normal_placement_rules = v; }
void Tp::on_attacking_dmg_acid_do_set(const std::string &v) { _on_attacking_dmg_acid_do = v; }
void Tp::on_attacking_dmg_bite_do_set(const std::string &v) { _on_attacking_dmg_bite_do = v; }
void Tp::on_attacking_dmg_claw_do_set(const std::string &v) { _on_attacking_dmg_claw_do = v; }
void Tp::on_attacking_dmg_cold_do_set(const std::string &v) { _on_attacking_dmg_cold_do = v; }
void Tp::on_attacking_dmg_crush_do_set(const std::string &v) { _on_attacking_dmg_crush_do = v; }
void Tp::on_attacking_dmg_digest_do_set(const std::string &v) { _on_attacking_dmg_digest_do = v; }
void Tp::on_attacking_dmg_draining_do_set(const std::string &v) { _on_attacking_dmg_draining_do = v; }
void Tp::on_attacking_dmg_drown_do_set(const std::string &v) { _on_attacking_dmg_drown_do = v; }
void Tp::on_attacking_dmg_energy_do_set(const std::string &v) { _on_attacking_dmg_energy_do = v; }
void Tp::on_attacking_dmg_fire_do_set(const std::string &v) { _on_attacking_dmg_fire_do = v; }
void Tp::on_attacking_dmg_heat_do_set(const std::string &v) { _on_attacking_dmg_heat_do = v; }
void Tp::on_attacking_dmg_lightning_do_set(const std::string &v) { _on_attacking_dmg_lightning_do = v; }
void Tp::on_attacking_dmg_melee_do_set(const std::string &v) { _on_attacking_dmg_melee_do = v; }
void Tp::on_attacking_dmg_nat_att_do_set(const std::string &v) { _on_attacking_dmg_nat_att_do = v; }
void Tp::on_attacking_dmg_necrosis_do_set(const std::string &v) { _on_attacking_dmg_necrosis_do = v; }
void Tp::on_attacking_dmg_negation_do_set(const std::string &v) { _on_attacking_dmg_negation_do = v; }
void Tp::on_attacking_dmg_poison_do_set(const std::string &v) { _on_attacking_dmg_poison_do = v; }
void Tp::on_attacking_dmg_stat_att_do_set(const std::string &v) { _on_attacking_dmg_stat_att_do = v; }
void Tp::on_attacking_dmg_stat_con_do_set(const std::string &v) { _on_attacking_dmg_stat_con_do = v; }
void Tp::on_attacking_dmg_stat_str_do_set(const std::string &v) { _on_attacking_dmg_stat_str_do = v; }
void Tp::on_attacking_dmg_water_do_set(const std::string &v) { _on_attacking_dmg_water_do = v; }
void Tp::on_awake_do_set(const std::string &v) { _on_awake_do = v; }
void Tp::on_born_do_set(const std::string &v) { _on_born_do = v; }
void Tp::on_death_do_set(const std::string &v) { _on_death_do = v; }
void Tp::on_death_drop_all_items_set(int v) { _on_death_drop_all_items = v; }
void Tp::on_death_is_open_set(int v) { _on_death_is_open = v; }
void Tp::on_death_of_a_follower_do_set(const std::string &v) { _on_death_of_a_follower_do = v; }
void Tp::on_death_of_my_leader_do_set(const std::string &v) { _on_death_of_my_leader_do = v; }
void Tp::on_dropped_do_set(const std::string &v) { _on_dropped_do = v; }
void Tp::on_enchant_do_set(const std::string &v) { _on_enchant_do = v; }
void Tp::on_equip_do_set(const std::string &v) { _on_equip_do = v; }
void Tp::on_fall_begin_do_set(const std::string &v) { _on_fall_begin_do = v; }
void Tp::on_fall_do_set(const std::string &v) { _on_fall_do = v; }
void Tp::on_final_use_do_set(const std::string &v) { _on_final_use_do = v; }
void Tp::on_get_text_description_long_do_set(const std::string &v) { _on_get_text_description_long_do = v; }
void Tp::on_jump_do_set(const std::string &v) { _on_jump_do = v; }
void Tp::on_lifespan_tick_do_set(const std::string &v) { _on_lifespan_tick_do = v; }
void Tp::on_move_do_set(const std::string &v) { _on_move_do = v; }
void Tp::on_open_do_set(const std::string &v) { _on_open_do = v; }
void Tp::on_owner_add_do_set(const std::string &v) { _on_owner_add_do = v; }
void Tp::on_owner_attack_dmg_acid_do_set(const std::string &v) { _on_owner_attack_dmg_acid_do = v; }
void Tp::on_owner_attack_dmg_bite_do_set(const std::string &v) { _on_owner_attack_dmg_bite_do = v; }
void Tp::on_owner_attack_dmg_claw_do_set(const std::string &v) { _on_owner_attack_dmg_claw_do = v; }
void Tp::on_owner_attack_dmg_cold_do_set(const std::string &v) { _on_owner_attack_dmg_cold_do = v; }
void Tp::on_owner_attack_dmg_crush_do_set(const std::string &v) { _on_owner_attack_dmg_crush_do = v; }
void Tp::on_owner_attack_dmg_digest_do_set(const std::string &v) { _on_owner_attack_dmg_digest_do = v; }
void Tp::on_owner_attack_dmg_draining_do_set(const std::string &v) { _on_owner_attack_dmg_draining_do = v; }
void Tp::on_owner_attack_dmg_drown_do_set(const std::string &v) { _on_owner_attack_dmg_drown_do = v; }
void Tp::on_owner_attack_dmg_energy_do_set(const std::string &v) { _on_owner_attack_dmg_energy_do = v; }
void Tp::on_owner_attack_dmg_fire_do_set(const std::string &v) { _on_owner_attack_dmg_fire_do = v; }
void Tp::on_owner_attack_dmg_heat_do_set(const std::string &v) { _on_owner_attack_dmg_heat_do = v; }
void Tp::on_owner_attack_dmg_lightning_do_set(const std::string &v) { _on_owner_attack_dmg_lightning_do = v; }
void Tp::on_owner_attack_dmg_melee_do_set(const std::string &v) { _on_owner_attack_dmg_melee_do = v; }
void Tp::on_owner_attack_dmg_nat_att_do_set(const std::string &v) { _on_owner_attack_dmg_nat_att_do = v; }
void Tp::on_owner_attack_dmg_necrosis_do_set(const std::string &v) { _on_owner_attack_dmg_necrosis_do = v; }
void Tp::on_owner_attack_dmg_negation_do_set(const std::string &v) { _on_owner_attack_dmg_negation_do = v; }
void Tp::on_owner_attack_dmg_poison_do_set(const std::string &v) { _on_owner_attack_dmg_poison_do = v; }
void Tp::on_owner_attack_dmg_stat_att_do_set(const std::string &v) { _on_owner_attack_dmg_stat_att_do = v; }
void Tp::on_owner_attack_dmg_stat_con_do_set(const std::string &v) { _on_owner_attack_dmg_stat_con_do = v; }
void Tp::on_owner_attack_dmg_stat_str_do_set(const std::string &v) { _on_owner_attack_dmg_stat_str_do = v; }
void Tp::on_owner_attack_dmg_water_do_set(const std::string &v) { _on_owner_attack_dmg_water_do = v; }
void Tp::on_owner_receive_dmg_acid_do_set(const std::string &v) { _on_owner_receive_dmg_acid_do = v; }
void Tp::on_owner_receive_dmg_bite_do_set(const std::string &v) { _on_owner_receive_dmg_bite_do = v; }
void Tp::on_owner_receive_dmg_claw_do_set(const std::string &v) { _on_owner_receive_dmg_claw_do = v; }
void Tp::on_owner_receive_dmg_cold_do_set(const std::string &v) { _on_owner_receive_dmg_cold_do = v; }
void Tp::on_owner_receive_dmg_crush_do_set(const std::string &v) { _on_owner_receive_dmg_crush_do = v; }
void Tp::on_owner_receive_dmg_digest_do_set(const std::string &v) { _on_owner_receive_dmg_digest_do = v; }
void Tp::on_owner_receive_dmg_draining_do_set(const std::string &v) { _on_owner_receive_dmg_draining_do = v; }
void Tp::on_owner_receive_dmg_drown_do_set(const std::string &v) { _on_owner_receive_dmg_drown_do = v; }
void Tp::on_owner_receive_dmg_energy_do_set(const std::string &v) { _on_owner_receive_dmg_energy_do = v; }
void Tp::on_owner_receive_dmg_fire_do_set(const std::string &v) { _on_owner_receive_dmg_fire_do = v; }
void Tp::on_owner_receive_dmg_heat_do_set(const std::string &v) { _on_owner_receive_dmg_heat_do = v; }
void Tp::on_owner_receive_dmg_lightning_do_set(const std::string &v) { _on_owner_receive_dmg_lightning_do = v; }
void Tp::on_owner_receive_dmg_melee_do_set(const std::string &v) { _on_owner_receive_dmg_melee_do = v; }
void Tp::on_owner_receive_dmg_nat_att_do_set(const std::string &v) { _on_owner_receive_dmg_nat_att_do = v; }
void Tp::on_owner_receive_dmg_necrosis_do_set(const std::string &v) { _on_owner_receive_dmg_necrosis_do = v; }
void Tp::on_owner_receive_dmg_negation_do_set(const std::string &v) { _on_owner_receive_dmg_negation_do = v; }
void Tp::on_owner_receive_dmg_poison_do_set(const std::string &v) { _on_owner_receive_dmg_poison_do = v; }
void Tp::on_owner_receive_dmg_stat_att_do_set(const std::string &v) { _on_owner_receive_dmg_stat_att_do = v; }
void Tp::on_owner_receive_dmg_stat_con_do_set(const std::string &v) { _on_owner_receive_dmg_stat_con_do = v; }
void Tp::on_owner_receive_dmg_stat_str_do_set(const std::string &v) { _on_owner_receive_dmg_stat_str_do = v; }
void Tp::on_owner_receive_dmg_water_do_set(const std::string &v) { _on_owner_receive_dmg_water_do = v; }
void Tp::on_owner_remove_do_set(const std::string &v) { _on_owner_remove_do = v; }
void Tp::on_polymorphed_do_set(const std::string &v) { _on_polymorphed_do = v; }
void Tp::on_receiving_dmg_acid_do_set(const std::string &v) { _on_receiving_dmg_acid_do = v; }
void Tp::on_receiving_dmg_bite_do_set(const std::string &v) { _on_receiving_dmg_bite_do = v; }
void Tp::on_receiving_dmg_claw_do_set(const std::string &v) { _on_receiving_dmg_claw_do = v; }
void Tp::on_receiving_dmg_cold_do_set(const std::string &v) { _on_receiving_dmg_cold_do = v; }
void Tp::on_receiving_dmg_crush_do_set(const std::string &v) { _on_receiving_dmg_crush_do = v; }
void Tp::on_receiving_dmg_digest_do_set(const std::string &v) { _on_receiving_dmg_digest_do = v; }
void Tp::on_receiving_dmg_draining_do_set(const std::string &v) { _on_receiving_dmg_draining_do = v; }
void Tp::on_receiving_dmg_drown_do_set(const std::string &v) { _on_receiving_dmg_drown_do = v; }
void Tp::on_receiving_dmg_energy_do_set(const std::string &v) { _on_receiving_dmg_energy_do = v; }
void Tp::on_receiving_dmg_fire_do_set(const std::string &v) { _on_receiving_dmg_fire_do = v; }
void Tp::on_receiving_dmg_heat_do_set(const std::string &v) { _on_receiving_dmg_heat_do = v; }
void Tp::on_receiving_dmg_lightning_do_set(const std::string &v) { _on_receiving_dmg_lightning_do = v; }
void Tp::on_receiving_dmg_melee_do_set(const std::string &v) { _on_receiving_dmg_melee_do = v; }
void Tp::on_receiving_dmg_nat_att_do_set(const std::string &v) { _on_receiving_dmg_nat_att_do = v; }
void Tp::on_receiving_dmg_necrosis_do_set(const std::string &v) { _on_receiving_dmg_necrosis_do = v; }
void Tp::on_receiving_dmg_negation_do_set(const std::string &v) { _on_receiving_dmg_negation_do = v; }
void Tp::on_receiving_dmg_poison_do_set(const std::string &v) { _on_receiving_dmg_poison_do = v; }
void Tp::on_receiving_dmg_stat_att_do_set(const std::string &v) { _on_receiving_dmg_stat_att_do = v; }
void Tp::on_receiving_dmg_stat_con_do_set(const std::string &v) { _on_receiving_dmg_stat_con_do = v; }
void Tp::on_receiving_dmg_stat_str_do_set(const std::string &v) { _on_receiving_dmg_stat_str_do = v; }
void Tp::on_receiving_dmg_water_do_set(const std::string &v) { _on_receiving_dmg_water_do = v; }
void Tp::on_resting_do_set(const std::string &v) { _on_resting_do = v; }
void Tp::on_stuck_do_set(const std::string &v) { _on_stuck_do = v; }
void Tp::on_swing_do_set(const std::string &v) { _on_swing_do = v; }
void Tp::on_targetted_do_set(const std::string &v) { _on_targetted_do = v; }
void Tp::on_targetted_radially_do_set(const std::string &v) { _on_targetted_radially_do = v; }
void Tp::on_teleport_do_set(const std::string &v) { _on_teleport_do = v; }
void Tp::on_thrown_do_set(const std::string &v) { _on_thrown_do = v; }
void Tp::on_tick_do_set(const std::string &v) { _on_tick_do = v; }
void Tp::on_unequip_do_set(const std::string &v) { _on_unequip_do = v; }
void Tp::on_use_do_set(const std::string &v) { _on_use_do = v; }
void Tp::on_waiting_do_set(const std::string &v) { _on_waiting_do = v; }
void Tp::on_want_to_fire_at_something_do_set(const std::string &v) { _on_want_to_fire_at_something_do = v; }
void Tp::on_you_are_declared_a_follower_do_set(const std::string &v) { _on_you_are_declared_a_follower_do = v; }
void Tp::on_you_are_declared_leader_do_set(const std::string &v) { _on_you_are_declared_leader_do = v; }
void Tp::on_you_are_hit_and_now_dead_do_set(const std::string &v) { _on_you_are_hit_and_now_dead_do = v; }
void Tp::on_you_are_hit_but_dodge_it_do_set(const std::string &v) { _on_you_are_hit_but_dodge_it_do = v; }
void Tp::on_you_are_hit_but_still_alive_do_set(const std::string &v) { _on_you_are_hit_but_still_alive_do = v; }
void Tp::on_you_are_on_fire_do_set(const std::string &v) { _on_you_are_on_fire_do = v; }
void Tp::on_you_nat_att_do_set(const std::string &v) { _on_you_nat_att_do = v; }
void Tp::range_max_set(int v) { _range_max = v; }
void Tp::rarity_set(int v) { _rarity = v; }
void Tp::shove_strength_mod_set(int v) { _shove_strength_mod = v; }
void Tp::shove_strength_set(int v) { _shove_strength = v; }
void Tp::spawn_group_radius_set(int v) { _spawn_group_radius = v; }
void Tp::spawn_on_shoved_set(const std::string &v) { _spawn_on_shoved = v; }
void Tp::stamina_drain_on_attacking_set(int v) { _stamina_drain_on_attacking = v; }
void Tp::stamina_drain_on_using_set(int v) { _stamina_drain_on_using = v; }
void Tp::stamina_set(int v) { _stamina = v; }
void Tp::stat_att_mod_set(int v) { _stat_att_mod = v; }
void Tp::stat_att_penalty_when_idle_max_set(int v) { _stat_att_penalty_when_idle_max = v; }
void Tp::stat_att_penalty_when_idle_set(int v) { _stat_att_penalty_when_idle = v; }
void Tp::stat_att_penalty_when_in_deep_water_set(int v) { _stat_att_penalty_when_in_deep_water = v; }
void Tp::stat_att_penalty_when_in_shallow_water_set(int v) { _stat_att_penalty_when_in_shallow_water = v; }
void Tp::stat_att_penalty_when_stuck_max_set(int v) { _stat_att_penalty_when_stuck_max = v; }
void Tp::stat_att_penalty_when_stuck_set(int v) { _stat_att_penalty_when_stuck = v; }
void Tp::stat_att_set(int v) { _stat_att = v; }
void Tp::stat_con_mod_set(int v) { _stat_con_mod = v; }
void Tp::stat_con_set(int v) { _stat_con = v; }
void Tp::stat_def_mod_set(int v) { _stat_def_mod = v; }
void Tp::stat_def_penalty_when_idle_max_set(int v) { _stat_def_penalty_when_idle_max = v; }
void Tp::stat_def_penalty_when_idle_set(int v) { _stat_def_penalty_when_idle = v; }
void Tp::stat_def_penalty_when_in_deep_water_set(int v) { _stat_def_penalty_when_in_deep_water = v; }
void Tp::stat_def_penalty_when_in_shallow_water_set(int v) { _stat_def_penalty_when_in_shallow_water = v; }
void Tp::stat_def_penalty_when_stuck_max_set(int v) { _stat_def_penalty_when_stuck_max = v; }
void Tp::stat_def_penalty_when_stuck_set(int v) { _stat_def_penalty_when_stuck = v; }
void Tp::stat_def_set(int v) { _stat_def = v; }
void Tp::stat_dex_mod_set(int v) { _stat_dex_mod = v; }
void Tp::stat_dex_set(int v) { _stat_dex = v; }
void Tp::stat_luck_mod_set(int v) { _stat_luck_mod = v; }
void Tp::stat_luck_set(int v) { _stat_luck = v; }
void Tp::stats02_set(int v) { _stats02 = v; }
void Tp::stats03_set(int v) { _stats03 = v; }
void Tp::stats04_set(int v) { _stats04 = v; }
void Tp::stats05_set(int v) { _stats05 = v; }
void Tp::stats06_set(int v) { _stats06 = v; }
void Tp::stats07_set(int v) { _stats07 = v; }
void Tp::stats09_set(int v) { _stats09 = v; }
void Tp::stat_str_mod_set(int v) { _stat_str_mod = v; }
void Tp::stat_str_set(int v) { _stat_str = v; }
void Tp::str1_set(const std::string &v) { _str1 = v; }
void Tp::str2_set(const std::string &v) { _str2 = v; }
void Tp::str4_set(const std::string &v) { _str4 = v; }
void Tp::target_name_projectile_set(const std::string &v) { _target_name_projectile = v; }
void Tp::teleport_distance_set(int v) { _teleport_distance = v; }
void Tp::temperature_sensitive_set(int v) { _temperature_sensitive = v; }
void Tp::temperature_sensitive_to_sudden_changes_set(int v) { _temperature_sensitive_to_sudden_changes = v; }
void Tp::text_a_or_an_set(const std::string &v) { _text_a_or_an = v; }
void Tp::text_debuff_set(const std::string &v) { _text_debuff = v; }
void Tp::text_description_enchant_set(const std::string &v) { _text_description_enchant = v; }
void Tp::text_description_long2_set(const std::string &v) { _text_description_long2 = v; }
void Tp::text_description_long3_set(const std::string &v) { _text_description_long3 = v; }
void Tp::text_description_long_set(const std::string &v) { _text_description_long = v; }
void Tp::text_description_short_set(const std::string &v) { _text_description_short = v; }
void Tp::text_hits_set(const std::string &v) { _text_hits = v; }
void Tp::text_long_name_set(const std::string &v) { _text_long_name = v; }
void Tp::text_short_name_set(const std::string &v) { _text_short_name = v; }
void Tp::text_skill_set(const std::string &v) { _text_skill = v; }
void Tp::text_title_set(const std::string &v) { _text_title = v; }
void Tp::text_unused1_set(const std::string &v) { _text_unused1 = v; }
void Tp::text_unused2_set(const std::string &v) { _text_unused2 = v; }
void Tp::text_unused3_set(const std::string &v) { _text_unused3 = v; }
void Tp::text_unused_set(const std::string &v) { _text_unused = v; }
void Tp::thing_size_set(int v) { _thing_size = v; }
void Tp::tick_prio_set(int v) { _tick_prio = v; }
void Tp::unused_chance1_d1000_set(int v) { _unused_chance1_d1000 = v; }
void Tp::unused_chance2_d1000_set(int v) { _unused_chance2_d1000 = v; }
void Tp::unused_chance3_d1000_set(int v) { _unused_chance3_d1000 = v; }
void Tp::unused_chance4_d1000_set(int v) { _unused_chance4_d1000 = v; }
void Tp::unused_chance5_d1000_set(int v) { _unused_chance5_d1000 = v; }
void Tp::unused_chance6_d1000_set(int v) { _unused_chance6_d1000 = v; }
void Tp::unused_flag103_set(int v) { _unused_flag103 = v; }
void Tp::unused_flag10_set(int v) { _unused_flag10 = v; }
void Tp::unused_flag11_set(int v) { _unused_flag11 = v; }
void Tp::unused_flag123_set(int v) { _unused_flag123 = v; }
void Tp::unused_flag12_set(int v) { _unused_flag12 = v; }
void Tp::unused_flag13_set(int v) { _unused_flag13 = v; }
void Tp::unused_flag14_set(int v) { _unused_flag14 = v; }
void Tp::unused_flag15_set(int v) { _unused_flag15 = v; }
void Tp::unused_flag16_set(int v) { _unused_flag16 = v; }
void Tp::unused_flag17_set(int v) { _unused_flag17 = v; }
void Tp::unused_flag18_set(int v) { _unused_flag18 = v; }
void Tp::unused_flag19_set(int v) { _unused_flag19 = v; }
void Tp::unused_flag1_set(int v) { _unused_flag1 = v; }
void Tp::unused_flag20_set(int v) { _unused_flag20 = v; }
void Tp::unused_flag27_set(int v) { _unused_flag27 = v; }
void Tp::unused_flag2_set(int v) { _unused_flag2 = v; }
void Tp::unused_flag3_set(int v) { _unused_flag3 = v; }
void Tp::unused_flag40_set(int v) { _unused_flag40 = v; }
void Tp::unused_flag48_set(int v) { _unused_flag48 = v; }
void Tp::unused_flag4_set(int v) { _unused_flag4 = v; }
void Tp::unused_flag5_set(int v) { _unused_flag5 = v; }
void Tp::unused_flag6_set(int v) { _unused_flag6 = v; }
void Tp::unused_flag7_set(int v) { _unused_flag7 = v; }
void Tp::unused_flag8_set(int v) { _unused_flag8 = v; }
void Tp::unused_flag9_set(int v) { _unused_flag9 = v; }
void Tp::weapon_dmg_set(int v) { _weapon_dmg = v; }
void Tp::weapon_use_distance_set(int v) { _weapon_use_distance = v; }
void Tp::z_depth_set(int v) { z_depth = v; }
void Tp::z_prio_set(int v) { z_prio = v; }
// end sort marker3 }
