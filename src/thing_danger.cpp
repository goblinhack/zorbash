//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_thing.hpp"
#include "my_thing_template.hpp"

int Tp::get_danger_level(void)
{
  TRACE_NO_INDENT();
  int danger_level = 0;

  danger_level = health_initial_max_roll() / 10;

  if (is_undead()) {
    danger_level++;
  }
  if (is_lifeless()) {
    danger_level++;
  }
  if (is_sticky()) {
    danger_level++;
  }
  if (is_spiderweb()) {
    danger_level += 5;
  }
  if (is_able_to_be_resurrected()) {
    danger_level *= 2;
  }
  if (is_able_to_regenerate()) {
    danger_level *= 2;
  }
  if (is_able_to_shove()) {
    danger_level++;
  }
  if (is_able_to_grapple()) {
    danger_level++;
  }
  if (is_acid()) {
    danger_level++;
  }
  if (hunger_is_insatiable()) {
    danger_level++;
  }
  if (is_fire()) {
    danger_level++;
  }
  if (is_lava()) {
    danger_level++;
  }
  if (is_poisonous_danger_level()) {
    danger_level += is_poisonous_danger_level();
  }
  if (is_necrotic_danger_level()) {
    danger_level += is_necrotic_danger_level() * 20;
  }
  if (is_floating()) {
    danger_level += 2;
  }
  if (is_flying()) {
    danger_level += 2;
  }
  if (is_able_to_jump()) {
    danger_level += 5;
  }
  if (is_able_to_shoot_at()) {
    danger_level += 20;
  }
  if (is_always_submerged()) {
    danger_level *= 2;
  }
  if (is_able_to_teleport_attack()) {
    danger_level *= 2;
  }

  danger_level += aggression_pct() / 10;

  danger_level += dmg_melee_dice().max_roll();
  danger_level += dmg_poison_dice().max_roll();
  danger_level += dmg_drown_dice().max_roll();
  danger_level += dmg_bite_dice().max_roll();
  danger_level += dmg_claw_dice().max_roll();
  danger_level += dmg_cold_dice().max_roll();
  danger_level += dmg_fire_dice().max_roll();
  danger_level += dmg_heat_dice().max_roll();
  danger_level += dmg_crush_dice().max_roll();
  danger_level += dmg_missile_dice().max_roll();
  danger_level += dmg_lightning_dice().max_roll();
  danger_level += dmg_energy_dice().max_roll();
  danger_level += dmg_negation_dice().max_roll();
  danger_level += dmg_acid_dice().max_roll();
  danger_level += dmg_water_dice().max_roll();
  danger_level += dmg_digest_dice().max_roll();
  danger_level += dmg_digest_dice().max_roll();
  danger_level += dmg_nat_att_dice().max_roll();

  //
  // Don't include crush damage as it is non typical
  //

  // CON("level %d", danger_level);
  return danger_level;
}

int Thing::danger_initial_level(void)
{
  TRACE_NO_INDENT();
  int danger_level = 0;

  danger_level = health_max() / 10;

  if (is_undead()) {
    danger_level++;
  }
  if (is_lifeless()) {
    danger_level++;
  }
  if (is_sticky()) {
    danger_level++;
  }
  if (is_spiderweb()) {
    danger_level += 5;
  }
  if (is_able_to_be_resurrected()) {
    danger_level *= 2;
  }
  if (is_able_to_regenerate()) {
    danger_level *= 2;
  }
  if (is_able_to_shove()) {
    danger_level++;
  }
  if (is_able_to_grapple()) {
    danger_level++;
  }
  if (is_carrying_an_item()) {
    danger_level++;
  }
  if (is_acid()) {
    danger_level++;
  }
  if (hunger_is_insatiable()) {
    danger_level++;
  }
  if (is_fire()) {
    danger_level++;
  }
  if (is_lava()) {
    danger_level++;
  }
  if (is_poisonous_danger_level()) {
    danger_level += is_poisonous_danger_level();
  }
  if (is_necrotic_danger_level()) {
    danger_level += is_necrotic_danger_level() * 20;
  }
  if (is_floating()) {
    danger_level += 2;
  }
  if (is_flying()) {
    danger_level += 2;
  }
  if (is_able_to_jump()) {
    danger_level += 5;
  }
  if (is_able_to_shoot_at()) {
    danger_level += 20;
  }
  if (idle_count() > 5) {
    danger_level /= 2;
  }
  if (stuck_count() > 5) {
    danger_level /= 2;
  }
  if (is_always_submerged()) {
    danger_level *= 2;
  }
  if (is_able_to_teleport_attack()) {
    danger_level *= 2;
  }

  danger_level += dmg_max();

  danger_level += aggression_pct() / 10;

  //
  // Low on health, reduce the level
  //
  if (health() < health_max() / 5) {
    danger_level /= 5;
  }

  if (health() < health_max() / 10) {
    danger_level /= 10;
  }

  //
  // Don't include crush damage as it is non typical
  //

  return danger_level;
}

int Thing::danger_current_level(void)
{
  TRACE_NO_INDENT();

  if (is_dead || is_dying) {
    return 0;
  }

  int danger_level = 0;

  danger_level = health() / 10;

  if (is_undead()) {
    danger_level++;
  }
  if (is_lifeless()) {
    danger_level++;
  }
  if (is_sticky()) {
    danger_level++;
  }
  if (is_spiderweb()) {
    danger_level += 5;
  }
  if (is_able_to_be_resurrected()) {
    danger_level *= 2;
  }
  if (is_able_to_regenerate()) {
    danger_level *= 2;
  }
  if (is_able_to_shove()) {
    danger_level++;
  }
  if (is_able_to_grapple()) {
    danger_level++;
  }
  if (is_carrying_an_item()) {
    danger_level++;
  }
  if (is_acid()) {
    danger_level++;
  }
  if (hunger_is_insatiable()) {
    danger_level++;
  }
  if (is_fire()) {
    danger_level++;
  }
  if (is_lava()) {
    danger_level++;
  }
  if (is_poisonous_danger_level()) {
    danger_level += is_poisonous_danger_level();
  }
  if (is_necrotic_danger_level()) {
    danger_level += is_necrotic_danger_level() * 20;
  }
  if (is_floating()) {
    danger_level += 2;
  }
  if (is_flying()) {
    danger_level += 2;
  }
  if (is_able_to_jump()) {
    danger_level += 5;
  }
  if (is_able_to_shoot_at()) {
    danger_level += 20;
  }
  if (idle_count() > 5) {
    danger_level /= 2;
  }
  if (stuck_count() > 5) {
    danger_level /= 2;
  }
  if (is_always_submerged()) {
    danger_level *= 2;
  }
  if (is_able_to_teleport_attack()) {
    danger_level *= 2;
  }

  danger_level += dmg_max();

  danger_level += aggression_pct() / 10;

  //
  // Leaders are stronger with more followers
  //
  if (is_able_to_follow()) {
    if (follower_count()) {
      danger_level *= follower_count();
    }
  }

  //
  // Low on health, reduce the level
  //
  if (health() < health_max() / 5) {
    danger_level /= 2;
  }

  if (health() < health_max() / 10) {
    danger_level /= 10;
  }

  return danger_level;
}

int Thing::is_dangerous(Thingp it)
{
  if (! it->is_mob() && ! it->is_monst() && ! it->is_player()) {
    return false;
  }

  dbg2("Is dangerous %s?", it->to_short_string().c_str());

  if (is_dead || is_dying) {
    dbg2("Is dangerous %s? no is dead or dying", it->to_short_string().c_str());
    return false;
  }

  if (is_fearless()) {
    dbg2("Is dangerous %s? no as I am fearless", it->to_short_string().c_str());
    return false;
  }

  if (is_friend(it) || same_mob(it)) {
    dbg2("Is dangerous %s? no as it is a friend", it->to_short_string().c_str());
    return false;
  }

  int my_danger_level  = danger_current_level();
  int its_danger_level = it->danger_current_level();

  //
  // If it's really close, then it's more dangerous
  //
  if (distance(curr_at, it->curr_at) < 2) {
    its_danger_level += 10;
  }

  if (distance(curr_at, it->curr_at) == 0) {
    its_danger_level += 20;
  }

  //
  // If I'm low on health then consider it more dangereous
  //
  if (health() < health_max() / 5) {
    its_danger_level++;
  } else if (health() < health_max() / 10) {
    its_danger_level += 2;
  }

  if (is_cowardly()) {
    its_danger_level *= 10;
  }

  dbg2("My danger level %d, its %d, %s", my_danger_level, its_danger_level, it->to_short_string().c_str());

  //
  // Will consider more dangerous things even more dangerous
  //
  if (is_cautious()) {
    its_danger_level *= 2;
  }

  //
  // Will consider more dangerous things less dangerous
  //
  if (is_daring()) {
    its_danger_level /= 2;
  }

  //
  // So giant rats will attack each other if at the same danger level
  //
  return its_danger_level > my_danger_level;
}

const std::string Thing::danger_level_str(Thingp it)
{
  auto my_danger_level  = danger_current_level();
  auto its_danger_level = it->danger_current_level();
  auto delta            = its_danger_level - my_danger_level;

  if (delta > 20) {
    return "%%fg=red$Deadly. Avoid!";
  }
  if (delta > 10) {
    return "%%fg=red$Dangerous";
  }
  if (delta >= 5) {
    return "%%fg=orange$Caution advised";
  }
  if (delta >= 0) {
    return "%%fg=orange$Some caution advised";
  }
  if (delta >= -10) {
    return "%%fg=yellow$Slight caution needed";
  }
  if (delta >= -20) {
    return "%%fg=green$Mostly harmless";
  } else if (delta >= -30) {
    return "%%fg=green$Harmless";
  } else {
    return "%%fg=green$Walkover";
  }
}

int Thing::danger_current_level(Thingp it)
{
  int my_danger_level  = danger_current_level();
  int its_danger_level = it->danger_current_level();
  return its_danger_level - my_danger_level;
}

int Thing::danger_initial_level(Thingp it)
{
  int my_danger_level  = danger_initial_level();
  int its_danger_level = it->danger_initial_level();
  // con("danger level %d vs %s %d", my_danger_level, it->to_short_string().c_str(), its_danger_level);
  return its_danger_level - my_danger_level;
}
