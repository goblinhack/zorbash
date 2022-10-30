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
  if (is_resurrectable()) {
    danger_level *= 2;
  }
  if (is_able_to_shove()) {
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
  if (is_thief()) {
    danger_level += 20;
  }
  if (is_able_to_fire_at()) {
    danger_level += 20;
  }
  if (is_always_submerged()) {
    danger_level *= 2;
  }

  danger_level += aggression_pct() / 10;

  danger_level += damage_melee_dice().max_roll();
  danger_level += damage_poison_dice().max_roll();
  danger_level += damage_drown_dice().max_roll();
  danger_level += damage_bite_dice().max_roll();
  danger_level += damage_claw_dice().max_roll();
  danger_level += damage_cold_dice().max_roll();
  danger_level += damage_fire_dice().max_roll();
  danger_level += damage_crush_dice().max_roll();
  danger_level += damage_lightning_dice().max_roll();
  danger_level += damage_energy_dice().max_roll();
  danger_level += damage_acid_dice().max_roll();
  danger_level += damage_water_dice().max_roll();
  danger_level += damage_digest_dice().max_roll();
  danger_level += damage_digest_dice().max_roll();
  danger_level += damage_nat_att_dice().max_roll();

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
  if (is_resurrectable()) {
    danger_level *= 2;
  }
  if (is_able_to_shove()) {
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
  if (is_thief()) {
    danger_level += 20;
  }
  if (is_able_to_fire_at()) {
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
  if (is_always_submerged()) {
    danger_level *= 2;
  }

  danger_level += damage_max();

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
  if (is_resurrectable()) {
    danger_level *= 2;
  }
  if (is_able_to_shove()) {
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
  if (is_thief()) {
    danger_level += 20;
  }
  if (is_able_to_fire_at()) {
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

  danger_level += damage_max();

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
  if (is_dead || is_dying) {
    return false;
  }

  if (! it->is_mob() && ! it->is_monst() && ! it->is_player()) {
    return false;
  }

  if (is_fearless()) {
    return false;
  }

  if (same_leader_or_owner(it)) {
    return false;
  }

  if (same_mob(it)) {
    return false;
  }

  int a = danger_current_level();
  int b = it->danger_current_level();

  //
  // If it's really close, then it's more dangerous
  //
  if (distance(curr_at, it->curr_at) < 2) {
    b += 10;
  }

  if (distance(curr_at, it->curr_at) == 0) {
    b += 20;
  }

  //
  // If I'm low on health then consider it more dangereous
  //
  if (health() < health_max() / 5) {
    b++;
  } else if (health() < health_max() / 10) {
    b += 2;
  }

  if (is_cowardly()) {
    b *= 10;
  }

  // dbg("My danger level %d, its %d, %s", a, b, it->to_short_string().c_str());

  //
  // So giant rats will attack each other if at the same danger level
  //
  return b > a;
}

const std::string Thing::danger_level_str(Thingp it)
{
  auto a     = danger_current_level();
  auto b     = it->danger_current_level();
  auto delta = b - a;

  if (delta > 20) {
    return "%%fg=red$Deadly. Avoid!";
  }
  if (delta > 10) {
    return "%%fg=red$Dangerous";
  }
  if (delta >= 0) {
    return "%%fg=orange$Caution advised";
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
  int a = danger_current_level();
  int b = it->danger_current_level();
  return b - a;
}

int Thing::danger_initial_level(Thingp it)
{
  int a = danger_initial_level();
  int b = it->danger_initial_level();
  // con("danger level %d vs %s %d", a, it->to_short_string().c_str(), b);
  return b - a;
}
