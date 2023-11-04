//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_english.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_sprintf.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"

//
// Python callback upon being hit
//
void Thing::on_hit_and_still_alive(Thingp hitter,      // an arrow / monst /...
                                   Thingp real_hitter, // who fired the arrow?
                                   bool crit, int damage)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_hit_and_still_alive = tp()->on_hit_and_still_alive_do();
  if (std::empty(on_hit_and_still_alive)) {
    return;
  }

  auto t = split_tokens(on_hit_and_still_alive, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, crit=%d, damage=%d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), real_hitter->to_short_string().c_str(), crit, damage);

    //
    // Warning cannot handle negative values here for damage
    //
    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y, (unsigned int) crit, (unsigned int) damage);
  } else {
    ERR("Bad on_hit_and_still_alive call [%s] expected mod:function, got %d elems", on_hit_and_still_alive.c_str(),
        (int) on_hit_and_still_alive.size());
  }
}

void Thing::on_hit_and_now_dead(Thingp hitter,      // an arrow / monst /...
                                Thingp real_hitter, // who fired the arrow?
                                bool crit, int damage)
{
  TRACE_NO_INDENT();
  auto on_hit_and_now_dead = tp()->on_hit_and_now_dead_do();
  if (std::empty(on_hit_and_now_dead)) {
    return;
  }

  auto t = split_tokens(on_hit_and_now_dead, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s, %s, crit=%d, damage=%d)", mod.c_str(), fn.c_str(), to_short_string().c_str(),
        hitter->to_short_string().c_str(), real_hitter->to_short_string().c_str(), crit, damage);

    //
    // Warning cannot handle negative values here for damage
    //
    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, real_hitter->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y, (unsigned int) crit, (unsigned int) damage);
  } else {
    ERR("Bad on_hit_and_now_dead call [%s] expected mod:function, got %d elems", on_hit_and_now_dead.c_str(),
        (int) on_hit_and_now_dead.size());
  }
}

//
// Python callback upon being miss
//
void Thing::on_hit_dodge_do(Thingp hitter)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_hit_dodge_do = tp()->on_hit_dodge_do();
  if (std::empty(on_hit_dodge_do)) {
    return;
  }

  auto t = split_tokens(on_hit_dodge_do, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s, %s)", mod.c_str(), fn.c_str(), to_short_string().c_str(), hitter->to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, hitter->id.id, (unsigned int) curr_at.x,
                    (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_hit_dodge_do call [%s] expected mod:function, got %d elems", on_hit_dodge_do.c_str(),
        (int) on_hit_dodge_do.size());
  }
}

void Thing::on_you_nat_attack_attempt(void)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_you_nat_attack_attempt = tp()->on_you_nat_attack_attempt_do();
  if (std::empty(on_you_nat_attack_attempt)) {
    return;
  }

  auto t = split_tokens(on_you_nat_attack_attempt, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_you_nat_attack_attempt call [%s] expected mod:function, got %d elems",
        on_you_nat_attack_attempt.c_str(), (int) on_you_nat_attack_attempt.size());
  }
}

void Thing::on_you_nat_attack_success(void)
{
  if (is_dead) {
    return;
  }

  TRACE_NO_INDENT();
  auto on_you_nat_attack_success = tp()->on_you_nat_attack_success_do();
  if (std::empty(on_you_nat_attack_success)) {
    return;
  }

  auto t = split_tokens(on_you_nat_attack_success, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    dbg("Call %s.%s(%s)", mod.c_str(), fn.c_str(), to_short_string().c_str());

    py_call_void_fn(mod.c_str(), fn.c_str(), id.id, (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  } else {
    ERR("Bad on_you_nat_attack_success call [%s] expected mod:function, got %d elems",
        on_you_nat_attack_success.c_str(), (int) on_you_nat_attack_success.size());
  }
}

int Thing::ai_hit_actual(Thingp              hitter,      // an arrow / monst /...
                         Thingp              real_hitter, // who fired the arrow?
                         ThingAttackOptionsp attack_options, int damage)
{
  TRACE_NO_INDENT();

  bool is_killed = false;

  if (damage < 0) {
    err("Negative damage: %d", damage);
    return false;
  }

  if (! hitter) {
    err("No hitter");
    return false;
  }

  if (! real_hitter) {
    err("No real hitter");
    return false;
  }

  dbg("Hit actual, damage %d", damage);
  TRACE_NO_INDENT();

  auto victim = this;
  if (attack_options->attack[ THING_ATTACK_POISON ]) {
    TRACE_NO_INDENT();
    damage = real_hitter->total_dmg_for_on_attacking_dmg_poison(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_poison(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_bite(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_bite(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_claw(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_claw(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_fire(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_fire(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_crush(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_crush(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_impact(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_impact(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_lightning(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_lightning(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_energy(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_energy(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_negation(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_negation(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_acid(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_acid(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_acid(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_acid(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_WATER ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_water(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_water(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_digest(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_digest(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_necrosis(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_necrosis(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_stamina(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_stamina(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_magic_drain(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_magic_drain(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_nat_att(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_nat_att(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_cold(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_cold(hitter, real_hitter, damage);

    if (is_on_fire()) {
      if (is_player()) {
        msg("%%fg=green$The cold attack puts out the flames!%%fg=reset$");
      }
      on_fire_unset();

      auto smoke = level->thing_new("smoke", curr_at);
      if (smoke) {
        smoke->lifespan_set(pcg_random_range(1, 10));
      }
    }
  } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_drown(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_drown(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_missile(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_missile(hitter, real_hitter, damage);
  } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
    TRACE_NO_INDENT();
    real_hitter->total_dmg_for_on_attacking_dmg_heat(victim, damage);
    damage = victim->total_dmg_for_on_rcv_dmg_heat(hitter, real_hitter, damage);
  } else {
    TRACE_NO_INDENT();
    //
    // The real hitter could be a sword. The hitter, the player.
    // Use this to see if we increase the damage due to any buffs of abilities of the sword.
    //
    real_hitter->total_dmg_for_on_attacking_dmg_melee(victim, damage);
    //
    // And use this for damage reduction on the victim.
    //
    damage = victim->total_dmg_for_on_rcv_dmg_melee(hitter, real_hitter, damage);
  }

  TRACE_NO_INDENT();

  //
  // Auto rage; the player does this via a skill
  //
  if (real_hitter->is_able_to_rage()) {
    if (real_hitter->is_raging()) {
      damage += 2;
    }
  }

  std::string dmg_type;
  bool        attack_set = false;

  /////////////////////////////////////////////////////////////////////////
  // Poison damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_POISON ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_poison()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to poison damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to poison damage!", text_The().c_str());
        }
      } else {
        dbg("Is immune to poison");
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no poison damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no poison damage!", text_The().c_str());
      } else {
        dbg("Takes no poison damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack poison damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "poison ";

    if (dmg_rcv_doubled_from_poison()) {
      damage *= 2;
      dmg_type = "double " + dmg_type;
      dbg("Double damage from poison");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Drown damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (! is_air_breather()) {
    attack_options->attack[ THING_ATTACK_DROWN ] = false;
  }

  if (attack_options->attack[ THING_ATTACK_DROWN ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (! damage) {
      if (is_player()) {
        msg("You take no drowning damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no drowning damage!", text_The().c_str());
      } else {
        dbg("Takes no drowning damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack drown damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "drown ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Bite damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_BITE ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (! damage) {
      if (is_player()) {
        msg("You take no bite damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no bite damage!", text_The().c_str());
      } else {
        dbg("Takes no bite damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_bite damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "bite ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Claw damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_CLAW ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (! damage) {
      if (is_player()) {
        msg("You take no claw damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no claw damage!", text_The().c_str());
      } else {
        dbg("Takes no claw damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_claw damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "claw ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Cold damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_COLD ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_cold()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to cold damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to cold damage!", text_The().c_str());
        } else {
          dbg("Takes no cold damage");
        }
      } else {
        dbg("Is immune to cold damage");
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no cold damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no cold damage!", text_The().c_str());
      } else {
        dbg("Takes no cold damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_cold damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "cold ";

    if (temperature_sensitive()) {
      if ((temperature_get() > TEMPERATURE_THRESHOLD) || is_burnt || dmg_rcv_doubled_from_cold()) {
        dmg_type = "double " + dmg_type;
        damage *= 2;
        dbg("Double damage from cold");
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Fire damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_FIRE ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_fire()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to fire damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to fire damage!", text_The().c_str());
        } else {
          dbg("Is immune to fire damage");
        }
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no fire damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no fire damage!", text_The().c_str());
      } else {
        dbg("Takes no fire damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_fire damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "fire ";

    if (temperature_sensitive()) {
      if ((temperature_get() < -TEMPERATURE_THRESHOLD) || was_frozen || is_frozen || dmg_rcv_doubled_from_fire()) {
        dmg_type = "double " + dmg_type;
        damage *= 2;
        dbg("Double damage from fire");
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Crush damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
    TRACE_NO_INDENT();
    attack_set = true;

    if (! damage || ! is_crushable()) {
      if (is_player()) {
        msg("You take no damage due to being super uncrushable!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no crush damage!", text_The().c_str());
      } else {
        dbg("Takes no crush damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_crush damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "crush ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Impact damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
    TRACE_NO_INDENT();
    attack_set = true;

    if (! damage || is_very_hard()) {
      if (is_player()) {
        msg("You take no impact damage due to being super tough!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no impact damage!", text_The().c_str());
      } else {
        dbg("Takes no impact damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_impact damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "impact ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Lightning / electricity damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
    TRACE_NO_INDENT();
    if (is_immune_to_electricity() || is_immune_to_lightning()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to electrical damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to electrical damage!", text_The().c_str());
        } else {
          dbg("Takes no electrical damage");
        }
      } else {
        dbg("Is immune to electrical damage");
      }
      return false;
    }

    attack_set = true;
    if (! damage) {
      if (is_player()) {
        msg("You take no lightning damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no lightning damage!", text_The().c_str());
      } else {
        dbg("Takes no electrical damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_lightning damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "lightning ";

    if (was_frozen || is_frozen) {
      dmg_type = "double " + dmg_type;
      damage *= 2;
      dbg("Double damage from lightning");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Energy damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (! damage) {
      if (is_player()) {
        msg("You take no energy damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no energy damage!", text_The().c_str());
      } else {
        dbg("Takes no energy damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_energy damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "energy ";

    if (was_frozen || is_frozen) {
      dmg_type = "double " + dmg_type;
      damage *= 2;
      dbg("Double damage from energy");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Negation damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
    TRACE_NO_INDENT();
    attack_set = true;

    if (is_immune_to_negation()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to negation damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to negation damage!", text_The().c_str());
        } else {
          dbg("Takes no negation damage");
        }
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no negation damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no negation damage!", text_The().c_str());
      } else {
        dbg("Is immune to negation damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_negation damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "negation ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Acid damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_ACID ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_acid()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to acid damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to acid damage!", text_The().c_str());
        } else {
          dbg("Is immune to acid damage");
        }
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no acid damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no acid damage!", text_The().c_str());
      } else {
        dbg("Takes no acid damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_acid damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "acid ";

    if (dmg_rcv_doubled_from_acid()) {
      damage *= 2;
      dmg_type = "double " + dmg_type;
      dbg("Double damage from acid");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Water damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_WATER ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_water()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to water damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to water damage!", text_The().c_str());
        } else {
          dbg("Is immune to water damage");
        }
      } else {
        dbg("Is immune to water damage");
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no water damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no water damage!", text_The().c_str());
      } else {
        dbg("Takes no water damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_water damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "water ";

    if (dmg_rcv_doubled_from_water()) {
      damage *= 2;
      dmg_type = "double " + dmg_type;
      dbg("Double damage from water");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Digest damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (! damage) {
      if (is_player()) {
        msg("You take no digest damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no digest damage!", text_The().c_str());
      } else {
        dbg("Takes no digest damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_digest damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "digest ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Necrosis damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_necrosis()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to rotting!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to rotting!", text_The().c_str());
        } else {
          dbg("Takes no rotting damage");
        }
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no rotting damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no rotting damage!", text_The().c_str());
      } else {
        dbg("Takes no rotting damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack necrosis damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "rotting ";

    if (dmg_rcv_doubled_from_necrosis()) {
      damage *= 2;
      dmg_type = "double " + dmg_type;
      dbg("Double damage from necrosis");
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Draining damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_stamina_drain()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to physical draining!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to physical draining attacks!", text_The().c_str());
        } else {
          dbg("Is immune to physical draining damage");
        }
      } else {
        dbg("Is immune to physical draining damage");
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no physical draining damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no physical draining damage!", text_The().c_str());
      } else {
        dbg("Takes no physical draining damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack physical draining damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "physical draining ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Magical draining damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_magic_drain()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to magical draining!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to magical draining attacks!", text_The().c_str());
        } else {
          dbg("Is immune to magical draining damage");
        }
      } else {
        dbg("Is immune to magical draining damage");
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no magical draining damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no magical draining damage!", text_The().c_str());
      } else {
        dbg("Takes no draining damageal draining");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack magic damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "magical draining ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Missile damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
    TRACE_NO_INDENT();
    attack_set = true;

    if (! damage || is_very_hard()) {
      if (is_player()) {
        msg("The missile bounces off of you!");
      } else if (real_hitter->is_player()) {
        msg("The missile bounces off of %s!", text_the().c_str());
      } else {
        msg("The missile bounces off of %s!", text_the().c_str());
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack dmg_missile damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "impact ";
  }

  /////////////////////////////////////////////////////////////////////////
  // Heat damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_HEAT ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (is_immune_to_fire()) {
      if (real_hitter->is_player()) {
        if (is_player()) {
          msg("You are immune to heat damage!");
        } else if (is_mob() || is_item() || is_alive_monst()) {
          msg("%s is immune to heat damage!", text_The().c_str());
        } else {
          dbg("Is immune to heat damage");
        }
      }
      return false;
    }

    if (! damage) {
      if (is_player()) {
        msg("You take no heat damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no heat damage!", text_The().c_str());
      } else {
        dbg("Takes no heat damage");
      }
      return false;
    }

    IF_DEBUG { real_hitter->log("Attack dmg_heat damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = "heat ";

    if (temperature_sensitive()) {
      if ((temperature_get() < -TEMPERATURE_THRESHOLD) || was_frozen || is_frozen || dmg_rcv_doubled_from_fire()) {
        dmg_type = "double " + dmg_type;
        damage *= 2;
        dbg("Double damage from heat");
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Natural damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
    TRACE_NO_INDENT();
    attack_set = true;
    if (! damage) {
      dmg_type = real_hitter->dmg_nat_att_type();
      if (is_player()) {
        msg("You take no %s damage!", dmg_type.c_str());
      } else if (real_hitter->is_player()) {
        msg("%s takes no %s damage!", text_The().c_str(), dmg_type.c_str());
      } else {
        dbg("Takes no nat damage");
      }
      return false;
    }
    IF_DEBUG { real_hitter->log("Attack natural attack damage %d on %s", damage, to_short_string().c_str()); }
    dmg_type = real_hitter->dmg_nat_att_type() + " ";
  }

  TRACE_NO_INDENT();
  if (! attack_set) {
    if (! damage) {
      if (is_player()) {
        msg("You take no attack damage!");
      } else if (real_hitter->is_player()) {
        msg("%s takes no attack damage!", text_The().c_str());
      } else {
        dbg("Takes no nat damage");
      }
      return false;
    }
    if (victim->is_player() || victim->is_monst()) {
      dmg_type = "melee ";
    } else {
      dmg_type = "bashing ";
    }
    IF_DEBUG { real_hitter->log("Attack melee damage %d on %s", damage, to_short_string().c_str()); }
  }

  //
  // Allow rocks on the main level to be destroyed; but not in the border
  //
  TRACE_NO_INDENT();
  if (is_very_hard()) {
    if ((curr_at.x < MAP_BORDER_ROCK) || (curr_at.y < MAP_BORDER_ROCK) || (curr_at.x >= MAP_WIDTH - MAP_BORDER_ROCK)
        || (curr_at.y >= MAP_HEIGHT - MAP_BORDER_ROCK)) {
      IF_DEBUG { hitter->log("Cannot hit: %s is border rock", to_short_string().c_str()); }
      if (real_hitter->is_player()) {
        msg("%s is indestructable!", text_The().c_str());
      }
      if (hitter->is_weapon()) {
        weapon_check_for_dmg(hitter, this);
      }
      wobble(20);
      return false;
    }
  }

  //
  // If the thing is dead, then allow an additional eat attack.
  //
  TRACE_NO_INDENT();
  if (is_dead || is_dying) {
    if (real_hitter->can_eat(this)) {
      IF_DEBUG { hitter->log("Thing is dead, allow it to be eaten"); }
    } else {
      IF_DEBUG { hitter->log("Hit fails, it's dead"); }
      return false;
    }
  } else {
    if (! damage) {
      IF_DEBUG { hitter->log("Hit fails, no damage"); }
      return false;
    }
  }

  auto delta = curr_at - hitter->curr_at;

  TRACE_NO_INDENT();
  if (real_hitter != this) {
    if (real_hitter->tp()->gfx_pixelart_bounce_on_move()) {
      if (real_hitter->bounce(0.5, 0.1, 100, 3)) {
        real_hitter->move_set_dir_from_delta(delta);
      }
    }
  }

  TRACE_NO_INDENT();
  if (real_hitter->is_able_to_tire()) {
    TRACE_NO_INDENT();
    if (! real_hitter->stamina()) {
      if (real_hitter->is_player()) {
        msg("You are too tired to attack.");
        return false;
      }
    }

    //
    // If hitting with a weapon, tire the wielder
    //
    if (hitter->is_weapon()) {
      //
      // Different weapons have different drain on stamina.
      //
      if (d20_ge(stat_con_total(), SAVING_ROLL_HARD)) {
        //
        // Only half stamina damage if you pass con roll
        //
        if (hitter != real_hitter) {
          auto s = hitter->stamina_drain_on_attacking();
          if (s) {
            s /= 2;
            if (! s) {
              s = 1;
            }
          }
          real_hitter->stamina_decr(s);
        }
      } else {
        if (hitter != real_hitter) {
          auto s = hitter->stamina_drain_on_attacking();
          real_hitter->stamina_decr(s);
        } else {
          real_hitter->stamina_decr(1);
        }
      }
    }
  }

  //
  // Check for immunity
  //
  TRACE_NO_INDENT();
  if (is_immune_to_fire()) {
    TRACE_NO_INDENT();

    bool fire_hit = false;

    if (attack_options->attack_type_set) {
      //
      // Explosions are firey but also do impact damage.
      //
      if (attack_options->attack[ THING_ATTACK_HEAT ] || attack_options->attack[ THING_ATTACK_FIRE ]) {
        fire_hit = true;
      }
    } else {
      if (hitter->is_fire() || real_hitter->is_fire()) {
        fire_hit = true;
      }
    }

    if (fire_hit) {
      if (is_player()) {
        msg("You bask in the fire!");
      } else if (real_hitter->is_player()) {
        msg("%s basks in the fire! You do no damage!", text_The().c_str());
      }
      return false;
    }
  }

  //
  // Try to push the thing into a hazard if we can just to be sneaky
  //
  TRACE_NO_INDENT();
  if (this == hitter) {
    //
    // On fire?
    //
  } else if (hitter->is_monst()) {
    switch (hitter->try_to_shove_into_hazard(this, delta)) {
      case THING_SHOVE_TRIED_AND_FAILED : return true;
      case THING_SHOVE_TRIED_AND_PASSED : return true;
      case THING_SHOVE_NEVER_TRIED : break;
    }
  }

  //
  // Try to steal instead of attacking?
  //
  TRACE_NO_INDENT();
  if (real_hitter->is_thief()) {
    if (real_hitter->is_adjacent(this)) {
      if (real_hitter->steal_item_from(this)) {
        return true;
      }

      if (real_hitter->steal_treasure_from(this)) {
        return true;
      }
    }
  }

  //
  // Poison attack
  //
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_POISON ]) {
    TRACE_NO_INDENT();
    if (is_immune_to_poison()) {
      if (hitter->is_poisonous_danger_level() || real_hitter->is_poisonous_danger_level()) {
        if (is_player()) {
          msg("You drink in the poison!");
        } else if (real_hitter->is_player()) {
          msg("%s drinks in the poison! You do no damage!", text_The().c_str());
        }
        if (hitter->is_poisonous_danger_level()) {
          health_boost(hitter, damage);
        } else {
          health_boost(real_hitter, damage);
        }
        return false;
      }
    } else {
      poisoned_amount_incr(damage / 2);
      poisoned();
    }
  }

  //
  // Necrotic attack
  //
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
    TRACE_NO_INDENT();
    if (is_undead() || is_ethereal()) {
      if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
        if (is_player()) {
          msg("You are immune to the withering touch of %s!", text_the().c_str());
        } else if (real_hitter->is_player()) {
          msg("%s shrugs off your withering touch!", text_The().c_str());
        }
        return false;
      }
    } else {
      if (pcg_random_range(0, 100) < 50) {
        if (is_immune_to_necrosis()) {
          if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
            if (is_player()) {
              msg("You gain strength from the withering touch!");
            } else if (real_hitter->is_player()) {
              msg("%s gains strength from your withering touch!", text_The().c_str());
            }
            stat_str_incr();
            return false;
          }
        } else {
          if (real_hitter->is_necrotic_danger_level()) {
            damage = real_hitter->is_necrotic_danger_level();
          } else {
            damage = 1;
          }
          damage = total_dmg_for_on_rcv_dmg_stat_str(hitter, real_hitter, damage);
          if (! damage) {
            IF_DEBUG { real_hitter->log("No strength damage"); }
            return false;
          }
          if (real_hitter->is_necrotic_danger_level()) {
            if (damage > 1) {
              rotting();
              necrotized_amount_incr(damage - 1);
            }
          }
          stat_str_decr();
          if (is_player()) {
            msg("%%fg=limegreen$Your skin is rotting. You lose 1 permanent strength!%%fg=reset$");
          } else if (is_alive_monst() && real_hitter->is_player()) {
            msg("%%fg=limegreen$Your rotting hand touches %s for 1 permanent strength damage!%%fg=reset$",
                text_the().c_str());
          }
          return true;
        }
      } else {
        if (is_immune_to_necrosis()) {
          if (hitter->is_necrotic_danger_level() || real_hitter->is_necrotic_danger_level()) {
            if (is_player()) {
              msg("You gain constitution from the withering touch!");
            } else if (real_hitter->is_player()) {
              msg("%s gains constitution from your withering touch!", text_The().c_str());
            }
            stat_con_incr();
            return false;
          }
        } else {
          if (real_hitter->is_necrotic_danger_level()) {
            damage = real_hitter->is_necrotic_danger_level();
          } else {
            damage = 1;
          }
          damage = total_dmg_for_on_rcv_dmg_stat_con(hitter, real_hitter, damage);
          if (! damage) {
            IF_DEBUG { real_hitter->log("No con damage"); }
            return false;
          }
          if (real_hitter->is_necrotic_danger_level()) {
            if (damage > 1) {
              rotting();
              necrotized_amount_incr(damage - 1);
            }
          }
          stat_con_decr();
          if (is_player()) {
            msg("%%fg=limegreen$Your skin is rotting. You lose 1 permanent con!%%fg=reset$");
          } else if (is_alive_monst() && real_hitter->is_player()) {
            msg("%%fg=limegreen$Your rotting hand touches %s for 1 permanent con damage!%%fg=reset$",
                text_the().c_str());
          }
          return true;
        }
      }
    }
  }

  //
  // If a staff is firing a laser, then get the damage from the
  // staff so we can add in enchants.
  //
  TRACE_NO_INDENT();
  if (hitter->is_laser()) {
    TRACE_NO_INDENT();
    auto owner = hitter->immediate_owner();
    if (owner) {
      if (owner->dmg_current()) {
        damage = owner->dmg_current();
        owner->dmg_current_set(0);
      }
    }
  }

  TRACE_NO_INDENT();
  real_hitter->attack_num_set(attack_options->attack_num);

  //
  // Allow the damage to be modified for skills
  //
  if (real_hitter->is_monst() || real_hitter->is_player()) {
    TRACE_NO_INDENT();
    TRACE_NO_INDENT();
    FOR_ALL_SKILLS_FOR(real_hitter, oid)
    {
      auto iter = level->thing_find(oid);
      if (iter && iter->is_activated) {
        real_hitter->dmg_current_set(damage);
        real_hitter->on_use_skill(iter, this);
        damage = real_hitter->dmg_current();
      }
    }
  }

  TRACE_NO_INDENT();
  if (victim->is_frozen) {
    damage *= 3;
    IF_DEBUG { hitter->log("Hit %s (health %d) for shatter damage %d", text_the().c_str(), health(), damage); }
  } else if (attack_options->crit) {
    damage *= 2;
    IF_DEBUG { hitter->log("Hit %s (health %d) for CRIT damage %d", text_the().c_str(), health(), damage); }
  } else {
    IF_DEBUG { hitter->log("Hit %s (health %d) for damage %d", text_the().c_str(), health(), damage); }
  }

  //
  // If hit by something then abort following any path
  //
  TRACE_NO_INDENT();
  if (is_player()) {
    if (game->robot_mode) {
      if (infop()->monst_state == MONST_STATE_MOVING) {
        clear_move_path("robot was hit while moving");
      } else {
        //
        // Allow the robot to continue resting as it might have been trying to eat food to recover.
        //
      }
    } else {
      clear_move_path("player was hit");
    }

    //
    // Some things like eels are only seen when they hit the player.
    //
    real_hitter->has_attacked_player = true;
    hitter->has_attacked_player      = true;
  }

  real_hitter->reset_goal_penalty(this);

  //
  // If possessions are destroyed, let the player know.
  //
  TRACE_NO_INDENT();
  auto o_top = top_owner();
  if (is_dead || is_dying) {
    //
    // Limit to possessions and not things like a sword thing animation.
    //
    dbg("Dead or dying");
    TRACE_NO_INDENT();

    if (is_item()) {
      dbg("Dead or dying item");
      TRACE_NO_INDENT();

      if (o_top && o_top->is_player()) {
        dbg("Player is onwer of dead or dying thing");
        if (! o_top->is_dead && ! o_top->is_dying) {
          if (is_drained) {
            msg("Your %s is drained.", text_long_name().c_str());
          } else {
            msg("Your %s is destroyed!", text_long_name().c_str());
          }
        }
      } else if (o_top && o_top->is_monst()) {
        dbg("Monst is owner of dead or dying thing");
        if (! o_top->is_dead && ! o_top->is_dying) {
          if (is_drained) {
            msg("%s %s is drained.", apostrophise(o_top->text_The()).c_str(), text_long_name().c_str());
          } else {
            msg("%s %s is destroyed!", apostrophise(o_top->text_The()).c_str(), text_long_name().c_str());
          }
        }
      }
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Undead double damage
  /////////////////////////////////////////////////////////////////////////
  if (real_hitter->is_holy() || hitter->is_holy()) {
    if (victim->is_undead()) {
      damage *= 2;
      dmg_type += "(x2 holy smite) ";
    }
  }

  TRACE_NO_INDENT();
  if (is_player()) {
    TRACE_NO_INDENT();
    //
    // Player being hit
    //
    if (real_hitter == this) {
      //
      // You hit yourself
      //
      if (real_hitter->attack_no_msg() || hitter->attack_no_msg()) {
        //
        // Things like radiation damage from a sword of plutonium are quiet attacks
        //
      } else if (attack_options->attack[ THING_ATTACK_POISON ]) {
        if (level->is_gas_poison(curr_at.x, curr_at.y)) {
          real_hitter->msg("%%fg=yellow$Poison burns your lungs for %s%d damage!%%fg=reset$", dmg_type.c_str(),
                           damage);
        } else {
          real_hitter->msg("%%fg=yellow$Poison circulates through your veins for %d %sdamage!%%fg=reset$", damage,
                           dmg_type.c_str());
        }
      } else if (hitter->is_weapon()) {
        real_hitter->msg("%%fg=orange$You attack yourself for %d %sdamage with %s!%%fg=reset$", damage,
                         dmg_type.c_str(), hitter->text_the().c_str());
      } else if (hitter->is_laser()) {
        real_hitter->msg("%%fg=orange$You zap yourself for %d %sdamage with %s!%%fg=reset$", damage, dmg_type.c_str(),
                         hitter->text_the().c_str());
      } else if (hitter->is_magical() && hitter->is_item()) {
        real_hitter->msg("%%fg=orange$You blast yourself for %d %sdamage with %s!%%fg=reset$", damage,
                         dmg_type.c_str(), hitter->text_the().c_str());
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        real_hitter->msg("%%fg=orange$You burn for %d %sdamage!%%fg=reset$", damage, dmg_type.c_str());
      } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
        real_hitter->msg("%%fg=cyan$Your skin blisters for %d %sdamage!%%fg=reset$", damage, dmg_type.c_str());
      } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
        real_hitter->msg("%%fg=limegreen$Your skin is falling away in chunks!%%fg=reset$");
      } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
        real_hitter->msg("%%fg=limegreen$Your stamina feels drained!%%fg=reset$");
      } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
        real_hitter->msg("%%fg=limegreen$Your magical powers feel drained!%%fg=reset$");
      } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
        real_hitter->msg("%%fg=orange$You take %d %sdamage!%%fg=reset$", damage, dmg_type.c_str());
      } else {
        real_hitter->msg("%%fg=orange$You hurt yourself for %d %sdamage with %s!%%fg=reset$", damage,
                         dmg_type.c_str(), hitter->text_the().c_str());
      }
    } else {
      if (is_dead || is_dying) {
        //
        // Fatal/final hit
        //
        if (attack_options->attack[ THING_ATTACK_POISON ]) {
          msg("%%fg=red$%s's fangs suck the last sustenance from you!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
          msg("%%fg=red$%s's withering touch finishes you off!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
          msg("%%fg=red$%s's physical draining touch finishes you off!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
          msg("%%fg=red$%s's magical draining touch finishes you off!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (hitter->is_barrel()) {
          if (is_air_breather()) {
            msg("%%fg=red$You are drowned in a barrel!%%fg=reset$");
            // popup("%%fg=red$Drown!");
          } else if (is_crushable()) {
            msg("%%fg=red$You are crushed in a barrel!%%fg=reset$");
            // popup("%%fg=red$Crush!");
          } else {
            msg("%%fg=red$You are killed by a barrel!%%fg=reset$");
          }
        } else if (hitter->is_weapon()) {
          if (hitter == real_hitter) {
            msg("%%fg=red$%s cuts you down!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=red$%s cuts you down with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the(false).c_str());
          }
        } else if (hitter->is_laser()) {
          if (hitter == real_hitter) {
            msg("%%fg=red$%s zaps you apart!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=red$%s zaps you apart with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the().c_str());
          }
        } else if (hitter->is_magical() && hitter->is_item()) {
          if (hitter == real_hitter) {
            msg("%%fg=red$%s blasts you into pieces!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=red$%s blasts you into pieces with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the().c_str());
          }
        } else if (hitter->is_projectile() || hitter->is_laser()) {
          if (hitter == real_hitter) {
            msg("%%fg=red$%s blasted you into bits!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=red$%s blasted you into bits with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the().c_str());
          }
        } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
          msg("%%fg=red$%s dissolves your body!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
          msg("%%fg=red$%s %s deep!%%fg=reset$", real_hitter->text_The().c_str(),
              pluralise(real_hitter->dmg_nat_att_type()).c_str());
        } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
          msg("%%fg=red$%s blasts you apart!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
          msg("%%fg=red$%s negates you!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
          msg("%%fg=red$%s fries your body!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
          msg("%%fg=red$You are flattened by %s!%%fg=reset$", real_hitter->text_the().c_str());
        } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
          msg("%%fg=red$You are impacted by %s!%%fg=reset$", real_hitter->text_the().c_str());
        } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
          msg("%%fg=red$You are burnt to a crisp by %s!%%fg=reset$", real_hitter->text_the().c_str());
        } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
          msg("%%fg=red$You are eaten by %s!%%fg=reset$", real_hitter->text_the().c_str());
        } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
          msg("%%fg=red$You are drowned by %s!%%fg=reset$", real_hitter->text_the().c_str());
        } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
          if (hitter == real_hitter) {
            msg("%%fg=red$%s strikes you!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=red$%s strikes you with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the().c_str());
          }
        } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
          if (hitter == real_hitter) {
            msg("%%fg=red$%s burns you!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=red$%s burns you with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the().c_str());
          }
        } else {
          msg("%%fg=red$%s %s you fatally!%%fg=reset$", real_hitter->text_The().c_str(),
              real_hitter->text_hits().c_str());
        }
      } else {
        //
        // Hit when not dead yet...
        //
        if (attack_options->crit) {
          msg("%%fg=red$%s CRITS you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_POISON ]) {
          if (real_hitter->is_fungus()) {
            msg("%%fg=yellow$%s's toxins injure you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str());
          } else if (real_hitter->is_monst()) {
            msg("%%fg=yellow$%s's fangs injure you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str());
          } else {
            msg("%%fg=yellow$%s injures you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          }
        } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
          msg("%%fg=limegreen$%s's withering touch rots your skin!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
          msg("%%fg=limegreen$%s's physical draining touch weakens you!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
          msg("%%fg=limegreen$%s's magical draining touch weakens you!%%fg=reset$", real_hitter->text_The().c_str());
        } else if (hitter->is_barrel()) {
          if (is_air_breather()) {
            msg("%%fg=orange$You are drowning in a barrel!%%fg=reset$");
          } else if (is_crushable()) {
            msg("%%fg=orange$You are being crushed by a barrel!%%fg=reset$");
          }
        } else if (hitter->is_weapon()) {
          if (hitter == real_hitter) {
            msg("%%fg=orange$%s hits you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          } else {
            msg("%%fg=orange$%s hits you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str(), hitter->text_the(false).c_str());
          }
        } else if (hitter->is_laser()) {
          if (hitter == real_hitter) {
            msg("%%fg=orange$%s zaps you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          } else {
            msg("%%fg=orange$%s zaps you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str(), hitter->text_the().c_str());
          }
        } else if (hitter->is_magical() && hitter->is_item()) {
          if (hitter == real_hitter) {
            msg("%%fg=orange$%s blasts you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          } else {
            msg("%%fg=orange$%s blasts you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str(), hitter->text_the().c_str());
          }
        } else if (hitter->is_projectile() || hitter->is_laser()) {
          if (hitter == real_hitter) {
            msg("%%fg=orange$%s blasted you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          } else {
            msg("%%fg=orange$%s blasted you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str(), hitter->text_the().c_str());
          }
        } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
          msg("%%fg=orange$%s burns you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
          if (! real_hitter->dmg_nat_att_type().empty()) {
            msg("%%fg=orange$%s attacks you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          } else {
            msg("%%fg=orange$%s bites you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          }
        } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
          msg("%%fg=orange$%s blasts you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
          msg("%%fg=orange$%s negates you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
          msg("%%fg=orange$%s electrocutes you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
              dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
          msg("%%fg=orange$You are being crushed by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
              damage);
        } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
          msg("%%fg=orange$You are being hit by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
              damage);
        } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
          if (real_hitter->is_explosion()) {
            msg("%%fg=orange$You are kaboomed by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
                damage);
          } else {
            msg("%%fg=orange$You are burnt by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(), damage);
          }
          popup("%%fg=red$!");
        } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
          msg("%%fg=orange$You are being consumed by %s for %d damage!%%fg=reset$", real_hitter->text_the().c_str(),
              damage);
        } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
          msg("%%fg=orange$You are drowning!%%fg=reset$");
        } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
          if (hitter == real_hitter) {
            msg("%%fg=orange$%s strikes you!%%fg=reset$", real_hitter->text_The().c_str());
          } else {
            msg("%%fg=orange$%s strikes you with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                hitter->text_the().c_str());
          }
        } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
          if (hitter == real_hitter) {
            msg("%%fg=orange$%s burns you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(), damage,
                dmg_type.c_str());
          } else {
            msg("%%fg=orange$%s burns you for %d %sdamage with %s!%%fg=reset$", real_hitter->text_The().c_str(),
                damage, dmg_type.c_str(), hitter->text_the().c_str());
          }
        } else {
          msg("%%fg=orange$%s %s you for %d %sdamage!%%fg=reset$", real_hitter->text_The().c_str(),
              real_hitter->text_hits().c_str(), damage, dmg_type.c_str());
        }
      }
    }

    //
    // Player being hit
    //
    if (is_bloodied() || (damage > THING_DAMAGE_SHAKE_ABOVE)) {
      level->wobble_set(damage / THING_DAMAGE_SHAKE_SCALE);
    }
  } else if (real_hitter->is_player()) {
    TRACE_NO_INDENT();
    //
    // Player hitting something else
    //
    if (top_owner() == real_hitter) {
      //
      // This can be the player is on fire and that causes carried items to burn
      //
      if (d20_ge(real_hitter->stat_luck_total(), SAVING_ROLL_HARD)) {
        dbg("Avoids damage by luck");
        return false;
      }

      if (attack_options->attack[ THING_ATTACK_POISON ]) {
        msg("%%fg=yellow$Your %s is being poisoned.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
        msg("%%fg=yellow$Your %s is being bitten.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
        msg("%%fg=yellow$Your %s is being clawed.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
        msg("%%fg=yellow$Your %s is freezing.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        msg("%%fg=yellow$Your %s is burning.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
        msg("%%fg=yellow$Your %s is being crushed.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
        msg("%%fg=yellow$Your %s is being impacted.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
        msg("%%fg=yellow$Your %s is being zapped.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
        msg("%%fg=yellow$Your %s is being blasted.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
        msg("%%fg=yellow$Your %s is being negated.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
        msg("%%fg=yellow$Your %s is disintegrating.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
        msg("%%fg=yellow$Your %s is dissolving.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
        msg("%%fg=yellow$Your %s is rotting.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
        msg("%%fg=yellow$Your %s is physically drained.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
        msg("%%fg=yellow$Your %s is magically drained.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
        msg("%%fg=yellow$Your %s is being drowned.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
        msg("%%fg=yellow$Your %s is struck.%%fg=reset$", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
        msg("%%fg=yellow$Your %s burns.%%fg=reset$", text_long_name().c_str());
      } else {
        msg("%%fg=yellow$Your %s is being damaged.%%fg=reset$", text_long_name().c_str());
      }
    } else if (is_alive_monst() || is_mob()) {
      //
      // Provide some more interesting messages for when the player hits monsters...
      //
      if (attack_options->crit) {
        real_hitter->msg("%%fg=red$You CRIT hit %s for %d %sdamage!%%fg=reset$", text_the().c_str(), damage,
                         dmg_type.c_str());
      } else {
        if (hitter && (hitter != real_hitter)) {
          if (attack_options->attack[ THING_ATTACK_POISON ]) {
            real_hitter->msg("%%fg=yellow$You poison %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str(), hitter->text_the().c_str());
          } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
            real_hitter->msg("%%fg=yellow$You rot %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str(), hitter->text_the().c_str());
          } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
            real_hitter->msg("%%fg=yellow$You tire %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str(), hitter->text_the().c_str());
          } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
            real_hitter->msg("%%fg=yellow$You drain %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str(), hitter->text_the().c_str());
          } else if (hitter->is_sword()) {
            real_hitter->msg("%%fg=yellow$You slash %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str(), hitter->text_the().c_str());
          } else if (hitter->is_weapon()) {
            real_hitter->msg("%%fg=yellow$You hit %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str(), hitter->text_the().c_str());
          } else if (hitter->is_laser()) {
            real_hitter->msg("%%fg=yellow$You zap %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str(), hitter->text_the().c_str());
          } else if (hitter->is_magical() && hitter->is_item()) {
            real_hitter->msg("%%fg=yellow$You blast %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str(), hitter->text_the().c_str());
          } else {
            real_hitter->msg("%%fg=yellow$You hit %s for %d %sdamage with %s.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str(), hitter->text_the().c_str());
          }

          if (game->robot_mode) {
            BOTCON("Robot attacks %s.%%fg=reset$", text_the().c_str());
          }
        } else {
          if (attack_options->attack[ THING_ATTACK_POISON ]) {
            real_hitter->msg("%%fg=yellow$You are poisoned %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
            real_hitter->msg("%%fg=yellow$You bite %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
            real_hitter->msg("%%fg=yellow$You claw %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
            real_hitter->msg("%%fg=yellow$You freeze %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
            real_hitter->msg("%%fg=yellow$You burn %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
            real_hitter->msg("%%fg=yellow$You crush %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
            real_hitter->msg("%%fg=yellow$You are impacted %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                             damage, dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
            real_hitter->msg("%%fg=yellow$You zap %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
            real_hitter->msg("%%fg=yellow$You blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
            real_hitter->msg("%%fg=yellow$You blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
            real_hitter->msg("%%fg=yellow$You dissolve %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
            real_hitter->msg("%%fg=yellow$You digest %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
            real_hitter->msg("%%fg=yellow$You rot %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
            real_hitter->msg("%%fg=yellow$You are drained %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
            real_hitter->msg("%%fg=yellow$You are drained %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
            real_hitter->msg("%%fg=yellow$You drown %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
            real_hitter->msg("%%fg=yellow$You strike down %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
            real_hitter->msg("%%fg=yellow$You burn down %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (hitter->is_weapon()) {
            real_hitter->msg("%%fg=yellow$You hit %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (hitter->is_laser()) {
            real_hitter->msg("%%fg=yellow$You zap %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else if (hitter->is_magical()) {
            real_hitter->msg("%%fg=yellow$You blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          } else {
            real_hitter->msg("%%fg=yellow$You hit %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                             dmg_type.c_str());
          }

          if (game->robot_mode) {
            BOTCON("Robot attacks %s.", text_the().c_str());
          }
        }
      }
    } else if (is_item()) {
      //
      // Player hitting items.
      //
      if (hitter->is_weapon()) {
        real_hitter->msg("You hit %s.", text_the().c_str());
      } else if (hitter->is_laser()) {
        real_hitter->msg("You zap %s.", text_the().c_str());
      } else if (hitter->is_magical() && hitter->is_item()) {
        if (attack_options->attack[ THING_ATTACK_POISON ]) {
          real_hitter->msg("%%fg=yellow$You magically poison %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
          real_hitter->msg("%%fg=yellow$You magically bite %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
          real_hitter->msg("%%fg=yellow$You magically rake %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
          real_hitter->msg("%%fg=yellow$You magically freeze %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
          real_hitter->msg("%%fg=yellow$You magically burn %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
          real_hitter->msg("%%fg=yellow$You magically crush %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
          real_hitter->msg("%%fg=yellow$You magically blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
          real_hitter->msg("%%fg=yellow$You magically zap %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                           dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
          real_hitter->msg("%%fg=yellow$You magically blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
          real_hitter->msg("%%fg=yellow$You magically blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
          real_hitter->msg("%%fg=yellow$You magically dissolve %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
          real_hitter->msg("%%fg=yellow$You magically digest %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
          real_hitter->msg("%%fg=yellow$You magically rot %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                           dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
          real_hitter->msg("%%fg=yellow$You are drained %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                           dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
          real_hitter->msg("%%fg=yellow$You are drained %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                           dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
          real_hitter->msg("%%fg=yellow$You magically drown %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
          real_hitter->msg("%%fg=yellow$You magically strike down %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
          real_hitter->msg("%%fg=yellow$You magically burn %s for %d %sdamage.%%fg=reset$", text_the().c_str(),
                           damage, dmg_type.c_str());
        } else {
          real_hitter->msg("%%fg=yellow$You blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                           dmg_type.c_str());
        }
      } else {
        real_hitter->msg("You hit %s.", text_the().c_str());
      }

      if (game->robot_mode) {
        BOTCON("Robot attacks %s.", text_the().c_str());
      }
    } else if (is_rock() || is_wall_dungeon()) {
      //
      // Provide some more interesting messages for when hitting rocks...
      //
      if (hitter->is_weapon()) {
        if (hitter->is_weapon() && (hitter->weapon_dmgd_pct() > 50)) {
          hitter->msg("%%fg=yellow$You pointlessly hit %s with your very damaged weapon.%%fg=reset$",
                      text_the().c_str());
        } else if (hitter->is_weapon() && (hitter->weapon_dmgd_pct() > 0)) {
          hitter->msg("%%fg=yellow$You hit %s with your damaged weapon.%%fg=reset$", text_the().c_str());
        } else {
          if (pcg_random_range(1, 100) < 10) {
            hitter->msg("%%fg=yellow$You hit %s, why though?%%fg=reset$", text_the().c_str());
          } else {
            hitter->msg("%%fg=yellow$You hit %s.%%fg=reset$", text_the().c_str());
          }
        }
      } else if (hitter->is_laser()) {
        real_hitter->msg("%%fg=yellow$You zap %s.%%fg=reset$", text_the().c_str());
      } else if (hitter->is_magical() && hitter->is_item()) {
        real_hitter->msg("%%fg=yellow$You blast %s.%%fg=reset$", text_the().c_str());
      } else {
        hitter->msg("%%fg=yellow$You hit %s.%%fg=reset$", text_the().c_str());
      }

      if (game->robot_mode) {
        BOTCON("Robot attacks %s.", text_the().c_str());
      }
    } else {
      //
      // Player hitting something.
      //
      if (hitter->is_weapon()) {
        real_hitter->msg("%%fg=yellow$You hit %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                         dmg_type.c_str());
      } else if (hitter->is_laser()) {
        real_hitter->msg("%%fg=yellow$You zap %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                         dmg_type.c_str());
      } else if (hitter->is_magical() && hitter->is_item()) {
        real_hitter->msg("%%fg=yellow$You blast %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                         dmg_type.c_str());
      } else {
        real_hitter->msg("%%fg=yellow$You hit %s for %d %sdamage.%%fg=reset$", text_the().c_str(), damage,
                         dmg_type.c_str());
      }

      if (game->robot_mode) {
        BOTCON("Robot attacks %s.", text_the().c_str());
      }
    }
  } else if (hitter->is_lightning()) {
    TRACE_NO_INDENT();
    //
    // Fork lightning passes through water.
    //
    if (real_hitter->is_water()) {
      hitter->msg("%s surges through the water and electrifies %s for %d damage.", hitter->text_The().c_str(),
                  text_the().c_str(), damage);
    } else {
      hitter->msg("%s electrifies %s for %d damage.", hitter->text_The().c_str(), text_the().c_str(), damage);
    }
  } else if (real_hitter == this) {
    TRACE_NO_INDENT();
    if (o_top && o_top->is_player()) {
      if (attack_options->attack[ THING_ATTACK_POISON ]) {
        msg("Your %s is being poisoned.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
        msg("Your %s is being bitten.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
        msg("Your %s is being clawed.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
        msg("Your %s is freezing.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        msg("Your %s is burning.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
        msg("Your %s is being crushed.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
        msg("Your %s is being impacted.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
        msg("Your %s is being zapped.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
        msg("Your %s is being blasted.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
        msg("Your %s is being negated.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
        msg("Your %s is disintegrating.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
        msg("Your %s is dissolving.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
        msg("Your %s is rotting.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
        msg("Your %s is physically drained.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
        msg("Your %s is magically drained.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
        msg("Your %s is being drowned.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
        msg("Your %s is struck.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
        msg("Your %s burns.", text_long_name().c_str());
      } else {
        msg("Your %s is being damaged.", text_long_name().c_str());
      }
    } else if (o_top && o_top->is_monst()) {
      if (attack_options->attack[ THING_ATTACK_POISON ]) {
        msg("%s %s is being poisoned.", pluralise(text_The()).c_str(), text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
        msg("Your %s is being bitten.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
        msg("Your %s is being clawed.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
        msg("Your %s is freezing.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        msg("Your %s is burning.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
        msg("Your %s is being crushed.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
        msg("Your %s is being impacted.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
        msg("Your %s is being zapped.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
        msg("Your %s is being blasted.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
        msg("Your %s is being negated.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
        msg("Your %s is disintegrating.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
        msg("Your %s is dissolving.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
        msg("Your %s is rotting.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
        msg("Your %s is physically drained.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
        msg("Your %s is magically drained.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
        msg("Your %s is being drowned.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
        msg("Your %s is struck.", text_long_name().c_str());
      } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
        msg("Your %s burns.", text_long_name().c_str());
      } else {
        msg("Your %s is being damaged.", text_long_name().c_str());
      }
    } else {
      if (attack_options->attack[ THING_ATTACK_POISON ]) {
        real_hitter->msg("%s is being poisoned.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
        real_hitter->msg("%s is biting itself.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
        real_hitter->msg("%s is clawing itself.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
        real_hitter->msg("%s is freezing.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        real_hitter->msg("%s is burning.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
        real_hitter->msg("%s is being crushed.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
        real_hitter->msg("%s is being impacted.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
        real_hitter->msg("%s is being electrified.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
        real_hitter->msg("%s is being disintegrated.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
        real_hitter->msg("%s is being negated.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
        real_hitter->msg("%s is being dissolved.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
        real_hitter->msg("%s is being digested.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
        real_hitter->msg("%s is rotting.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
        real_hitter->msg("%s is being physically drained.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
        real_hitter->msg("%s is being magically drained.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
        real_hitter->msg("%s is drowning.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
        real_hitter->msg("%s is struck.", text_The().c_str());
      } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
        real_hitter->msg("%s burns.", text_The().c_str());
      } else {
        real_hitter->msg("%s is hitting itself.", text_The().c_str());
      }
    }
  } else if (real_hitter->is_monst() && (real_hitter != hitter)) {
    TRACE_NO_INDENT();
    if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
      real_hitter->msg("%s %s %s with %s.", real_hitter->text_The().c_str(), real_hitter->text_hits().c_str(),
                       text_the().c_str(), hitter->text_the().c_str());
    } else {
      real_hitter->msg("%s hits %s with %s.", real_hitter->text_The().c_str(), text_the().c_str(),
                       hitter->text_the().c_str());
    }
  } else if (real_hitter != this) {
    TRACE_NO_INDENT();
    //
    // Something else hitting something else. But don't show a message for things
    // like rocks being hit by explosions.
    //
    if (victim->is_interesting()) {
      if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
        real_hitter->msg("%s %s %s.", real_hitter->text_The().c_str(), real_hitter->text_hits().c_str(),
                         text_the().c_str());
      } else {
        real_hitter->msg("%s hits %s.", real_hitter->text_The().c_str(), text_the().c_str());
      }
    }
  }

  //
  // Trail of blood?
  //
  place_blood();

  //
  // Check for staff of fire projectiles (this is the non real hitter case)
  //
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_FIRE ] || hitter->is_fire() || hitter->is_lava() || real_hitter->is_fire()
      || real_hitter->is_lava()) {
    on_fire_set("hit by fire");
  } else if (is_on_fire()) {
    if (is_player()) {
      if (real_hitter->is_monst()) {
        if (! is_immune_to_fire()) {
          msg("%%fg=red$You burn whilst being attacked!%%fg=reset$");
        }
      }
    }
    if (hitter->on_fire_set("hit by fire due to attacking")) {
      msg("%s sets itself on fire!", hitter->text_The().c_str());
    }
  }

  //
  // In player robot mode we want to keep track of enemies also
  //
  add_attacker(real_hitter);

  //
  // Need to check this after immunity checks, so that if an explosion occurs and
  // we take no fire damage, we're still hit by impact damage.
  //
  if (maybe_aip()) {
    if (is_dead) {
      //
      // If dead, allow things to chomp on your bones
      //
    } else {
      //
      // If alive, one hit per tick
      //
      // NOTE: this needs to be before on_fire_set() as that leads to multiple hits by lava
      //
      IF_DEBUG { log("Set recently hit: %s", to_short_string().c_str()); }
      aip()->recently_hit_by[ real_hitter->id ]++;
    }
  }

  //
  // If sufficiently far away, the hitter message might be hard to associate
  //
  auto second_message_distance = 2;

  //
  // Visible hit indication
  //
  TRACE_NO_INDENT();
  if (is_player()) {
    TRACE_NO_INDENT();
    //
    // Player being hit
    //
    if (attack_options->crit) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=red$It CRITS you -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=red$-%d", damage));
      }
    } else if (hitter->is_missile()) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=orange$It strikes you -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    } else if (hitter->is_fire() || real_hitter->is_fire()) {
      TRACE_NO_INDENT();
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$Burns -%d", damage));
      }
    } else if (hitter->is_projectile()) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=orange$Hits you -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    } else if (hitter->is_staff()) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=orange$Zaps you -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    } else if (hitter->is_laser()) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=orange$Zaps you -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    } else if (hitter->is_fire() || real_hitter->is_fire()) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=red$Burns you for -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=red$-%d", damage));
      }
    } else if (hitter->is_monst() || real_hitter->is_monst()) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=orange$It %s you -%d", real_hitter->text_hits().c_str(), damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=red$Burns you for -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=red$-%d", damage));
      }
    } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=red$Chills you for -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=red$-%d", damage));
      }
    } else {
      TRACE_NO_INDENT();
      real_hitter->popup(string_sprintf("%%fg=orange$Hits you for -%d", damage));
      if (distance(real_hitter->curr_at, curr_at) > second_message_distance) {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    }
  } else if (is_monst()) {
    //
    // Thing being hit
    //
    TRACE_NO_INDENT();
    if (hitter->is_player() || real_hitter->is_player()) {
      //
      // Thing being hit by player
      //
      TRACE_NO_INDENT();
      if (attack_options->crit) {
        real_hitter->popup(string_sprintf("%%fg=red$You CRIT it -%d", damage));
      } else {
        real_hitter->popup(string_sprintf("%%fg=orange$You hit it -%d", damage));
      }
    } else {
      //
      // Monster hitting monst, or self attack damage like cold or fire
      //
      TRACE_NO_INDENT();
      if (attack_options->crit) {
        popup(string_sprintf("%%fg=red$-%d", damage));
      } else {
        popup(string_sprintf("%%fg=orange$-%d", damage));
      }
    }
  }

  TRACE_NO_INDENT();
  real_hitter->tick_last_did_something_set(game->tick_current);

  //
  // Splat graphics
  //
  if (is_monst() || is_player()) {
    //
    // If offscreen, avoid as we never see it.
    //
    TRACE_NO_INDENT();
    if (is_visible_to_player) {
      if (is_green_blooded()) {
        level->thing_new(tp_random_green_splatter()->name(), curr_at);
      } else if (is_red_blooded()) {
        level->thing_new(tp_random_red_splatter()->name(), curr_at);
      } else if (is_undead()) {
        level->thing_new(tp_random_green_splatter()->name(), curr_at);
      } else {
        //
        // Nothing for gargoyles being attacked.
        //
      }
    }
  }

  TRACE_NO_INDENT();
  if (real_hitter != this) {
    if (gfx_pixelart_wobbles_when_hit()) {
      wobble(20);
      bounce(0.5 /* height */, 0.1 /* fade */, 100, 1);
    }
  }

  //
  // Python callback. Poison looks like an attack on self, so avoid.
  //
  TRACE_NO_INDENT();
  if (real_hitter != this) {
    //
    // Are we carrying a weapon? If not, see if we can do a claw attack
    //
    if (real_hitter->is_player()) {
      //
      // We can hit this case if we have no sword and are punching.
      // We don't want to see the natural attack of the player as
      // we already displayed it during swing attacks.
      //
    } else if (attack_options->attack[ THING_ATTACK_NATURAL ] || attack_options->attack[ THING_ATTACK_POISON ]
               || attack_options->attack[ THING_ATTACK_DIGEST ]
               || ! real_hitter->equip_id_carry_anim(MONST_EQUIP_WEAPON).ok()) {
      //
      // Monster natural attack
      //
      if (real_hitter->is_visible_to_player) {
        auto claws = real_hitter->tp()->gfx_anim_use();
        if (claws != "") {
          auto nat_att_effect = level->thing_new(claws, curr_at, real_hitter);
          if (nat_att_effect) {
            if (nat_att_effect->bounce(0.1, 0.1, 100, 3)) {
              nat_att_effect->move_set_dir_from_delta(delta);
            }
          }
        }
      }

      real_hitter->on_you_nat_attack_attempt();
    }
  }

  //
  // Not sure if stamina of 0 should kill. I vote yes.
  //
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
    auto h = stamina_decr(damage);
    if (h <= 0) {
      h         = stamina_set(0);
      is_killed = true;
    }
  } else {
    auto h = health_decr(damage);
    if (h <= 0) {
      h         = health_set(0);
      is_killed = true;
    }
  }

  //
  // Magical draining has no physical effect.
  //
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
    auto h = magic_decr(damage);
    if (h <= 0) {
      h = magic_set(0);
    }
  } else {
    auto h = health_decr(damage);
    if (h <= 0) {
      h = health_set(0);
    }
  }

  /////////////////////////////////////////////////////////////////////////
  // Negation damage
  /////////////////////////////////////////////////////////////////////////
  TRACE_NO_INDENT();
  if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
    negation_dmg(damage, is_killed);
  }

  TRACE_NO_INDENT();
  if (is_killed) {
    //
    // Record who dun it.
    //
    if (is_loggable()) {
      dbg("Is killed by (%s) %u damage", real_hitter->to_short_string().c_str(), damage);
    }
    std::string defeater = real_hitter->text_a_or_an();

    //
    // If not a monst, e.g. a mob then don't include defeated by
    //
    auto reason = "by " + defeater;

    if (real_hitter->is_monst() || real_hitter->is_player()) {
      if (is_monst() || is_player()) {
        if (is_sleeping) {
          reason = "in its sleep, by " + defeater;
        } else {
          reason = "by " + defeater;
        }
      } else {
        reason = "by " + defeater;
      }
    }

    if ((real_hitter->curr_at == curr_at) && real_hitter->is_engulfer()) {
      reason = "in the bowels of " + defeater;
    }

    if (real_hitter == this) {
      if (attack_options->attack[ THING_ATTACK_POISON ]) {
        if (level->is_gas_poison(curr_at.x, curr_at.y)) {
          reason = "by poison gas";
        } else if (poison_reason_get().empty()) {
          reason = "by poisoning";
        } else {
          reason = "by poisoning by " + poison_reason_get();
        }
      } else if (attack_options->attack[ THING_ATTACK_BITE ]) {
        reason = "by biting";
      } else if (attack_options->attack[ THING_ATTACK_CLAW ]) {
        reason = "by clawing";
      } else if (attack_options->attack[ THING_ATTACK_COLD ]) {
        if (level->is_spell_of_holding_barrier(curr_at.x, curr_at.y)) {
          reason = "by magical holding";
        } else if (level->is_spell_of_sanctuary_barrier(curr_at.x, curr_at.y)) {
          reason = "by sanctuary breaking";
        } else if (level->is_block_of_ice(curr_at.x, curr_at.y)) {
          reason = "by refrigeration";
        } else {
          reason = "by cold";
        }
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        if (is_able_to_melt()) {
          reason = "by melting";
        } else {
          reason = "by fire";
        }
      } else if (attack_options->attack[ THING_ATTACK_CRUSH ]) {
        reason = "by crushing";
      } else if (attack_options->attack[ THING_ATTACK_IMPACT ]) {
        reason = "by impact";
      } else if (attack_options->attack[ THING_ATTACK_FIRE ]) {
        reason = "by burning";
      } else if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
        reason = "by a bolt of lighting";
      } else if (attack_options->attack[ THING_ATTACK_ENERGY ]) {
        reason = "by too much energy";
      } else if (attack_options->attack[ THING_ATTACK_NEGATION ]) {
        reason = "by negation";
      } else if (attack_options->attack[ THING_ATTACK_ACID ]) {
        reason = "by acid";
      } else if (attack_options->attack[ THING_ATTACK_DIGEST ]) {
        reason = "by digestion";
      } else if (attack_options->attack[ THING_ATTACK_NECROSIS ]) {
        reason = "by rotting";
      } else if (attack_options->attack[ THING_ATTACK_STAMINA_DRAIN ]) {
        reason = "by stamina draining";
      } else if (attack_options->attack[ THING_ATTACK_MAGIC_DRAIN ]) {
        reason = "by magical draining";
      } else if (attack_options->attack[ THING_ATTACK_NATURAL ]) {
        reason = "by over friendly biting";
      } else if (attack_options->attack[ THING_ATTACK_DROWN ]) {
        reason = "by drowning";
      } else if (attack_options->attack[ THING_ATTACK_MISSILE ]) {
        reason = "by a missile";
      } else if (attack_options->attack[ THING_ATTACK_HEAT ]) {
        reason = "by burning";
      } else {
        reason = "by something unknown";
      }
    }

    dead(real_hitter, reason);

    //
    // Does the attacker feast on success? This is too quick for normal
    // monsters as the body immediately vanishes into bones. But for an
    // engulfer maybe not.
    //
    if (is_engulfer()) {
      if (real_hitter->can_eat(this)) {
        real_hitter->eat(this);
      }
    }
  } else {
    dbg("Is hit by (%s) %u damage, health now %d/%d", real_hitter->to_short_string().c_str(), damage, health(),
        stamina());
  }

  //
  // Used by AI to know if we can relax
  //
  TRACE_NO_INDENT();
  tick_last_i_was_attacked_set(game->tick_current);

  //
  // So we can tell when things are attacking us
  //
  real_hitter->tick_last_i_attacked_set(game->tick_current);

  if (is_player()) {
    score_incr(damage);
  }

  //
  // This might trigger more damage. Interesting effects here, like being attacked by defrosted creature will
  // make you colder.
  //
  TRACE_NO_INDENT();
  if (real_hitter != this) {
    //
    // Only if the temperature is extreme enough.
    //
    auto hitter_temp = hitter->temperature_get();
    if (abs(hitter_temp) >= TEMPERATURE_THRESHOLD) {
      temperature_incr(hitter_temp / 10);
    }
  }

  //
  // Python callback
  //
  TRACE_NO_INDENT();
  if (is_dead || is_dying) {
    TRACE_NO_INDENT();
    on_hit_and_now_dead(hitter, real_hitter, attack_options->crit, damage);

    //
    // Set up noise, for example a door being hit
    //
    level->sound_sources_incr(curr_at.x, curr_at.y, noise_on_hit_and_still_alive());
  } else {
    TRACE_NO_INDENT();
    on_hit_and_still_alive(hitter, real_hitter, attack_options->crit, damage);

    //
    // Set up noise, for example a door being broken
    //
    level->sound_sources_incr(curr_at.x, curr_at.y, noise_on_hit_and_now_dead());

    //
    // Interrupt whatever the monster was doing.
    //
    if (is_monst() || (is_player() && game->robot_mode)) {
      if (is_sleeping) {
        if (wake("was attacked")) {
          change_state(MONST_STATE_IDLE, "was attacked and woken");
        }
      } else {
        change_state(MONST_STATE_IDLE, "was attacked");
      }
    }
  }

  //
  // Python callback. Poison looks like an attack on self, so avoid.
  //
  TRACE_NO_INDENT();
  if (real_hitter != this) {
    TRACE_NO_INDENT();
    //
    // Are we carrying a weapon? If not, see if we can do a claw attack
    //
    if (real_hitter->is_player()) {
      //
      // We can hit this case if we have no sword and are punching.
      // We don't want to see the natural attack of the player as
      // we already displayed it during swing attacks.
      //
    } else if (attack_options->attack[ THING_ATTACK_NATURAL ] || attack_options->attack[ THING_ATTACK_POISON ]
               || attack_options->attack[ THING_ATTACK_DIGEST ]
               || ! real_hitter->equip_id_carry_anim(MONST_EQUIP_WEAPON).ok()) {

      //
      // Monster natural attack
      //
      real_hitter->on_you_nat_attack_success();
    }
  }
  TRACE_NO_INDENT();

  return true;
}

//
// Returns true on the target being dead.
//
int Thing::is_hit(Thingp hitter, ThingAttackOptionsp attack_options, int damage)
{
  IF_DEBUG { hitter->log("Is hit? damage %d", damage); }
  TRACE_AND_INDENT();

  if (attack_options->attack[ THING_ATTACK_NATURAL ] || attack_options->attack[ THING_ATTACK_DIGEST ]) {
    //
    // Allow attacks when dead
    //
    IF_DEBUG { hitter->log("Possible attack on %s", to_short_string().c_str()); }
  } else if (damage) {
    //
    // Filter attacks when dead
    //
    if (is_dead || is_dying) {
      if (is_frozen) {
        IF_DEBUG { hitter->log("Already dead, allow frozen corpse hit %s", to_short_string().c_str()); }
        corpse_cleanup = true;
        dead("frozen corpse cleanup");
        return false;
      }
      IF_DEBUG { hitter->log("Already dead, no more hits %s", to_short_string().c_str()); }
      return false;
    }
    IF_DEBUG { hitter->log("Possible attack on %s", to_short_string().c_str()); }
  } else {
    //
    // Failed attack
    IF_DEBUG { hitter->log("No damage"); }
    return false;
  }
  TRACE_NO_INDENT();

  //
  // If given a real hitter, prefer that; for example a player slamming a door on a monster.
  //
  Thingp real_hitter = attack_options->real_hitter;

  //
  // If an arrow, who really fired it?
  //
  if (! real_hitter) {
    if (hitter) {
      real_hitter = hitter->top_owner();

      //
      // If on fire, the fire is owned by the player. So don't make the player the real hitter.
      //
      if (real_hitter) {
        if (real_hitter->is_fire()) {
          if (real_hitter == this) {
            real_hitter = nullptr;
          }
        }
      }

      if (! real_hitter) {
        real_hitter = hitter;
      }
    }
  }
  if (! hitter) {
    IF_DEBUG { log("No hitter"); }
    return false;
  }

  if (! real_hitter) {
    IF_DEBUG { hitter->log("No real hitter"); }
    return false;
  }

  //
  // If we are pushed into lava and then catch fire, the spawn of fire causes another location check.
  // Avoid the lava hitting twice.
  //
  if (maybe_aip()) {
    //
    // Keep track of who hit me to avoid multiple hits per tick
    // But allow special weapons to attack more than one time.
    //
    if (attack_options->attack_num == 0) {
      if (aip()->recently_hit_by.find(real_hitter->id) != aip()->recently_hit_by.end()) {
        //
        // Faster things get more moves and hits
        //
        auto speed             = move_speed_curr();
        auto real_hitter_speed = real_hitter->move_speed_curr();
        if (speed && real_hitter_speed) {
          auto hit_count     = aip()->recently_hit_by[ real_hitter->id ];
          auto max_hit_count = real_hitter_speed / speed;

          if (hit_count >= max_hit_count) {
            IF_DEBUG
            {
              real_hitter->log("No, I've already hit %s (count %d max %d)", to_short_string().c_str(), hit_count,
                               max_hit_count);
            }
            return false;
          }
        } else {
          //
          // Static things hit one time
          //
          IF_DEBUG { real_hitter->log("No, I've already hit %s", to_short_string().c_str()); }
          return false;
        }
      }
    }
  }

  //
  // Unable to hit?
  //
  if (is_floating_currently() && real_hitter->is_water()) {
    //
    // Electric eel fork lightning attack in water
    //
    if (is_player()) {
      msg("You watch the electrics going on beneath you.");
    }
    IF_DEBUG { hitter->log("Cannot hit: %s is floating above water", to_short_string().c_str()); }
    return false;
  }

  if (attack_options->attack[ THING_ATTACK_LIGHTNING ]) {
    if (is_floating_currently() && real_hitter->is_always_submerged_in_water()) {
      //
      // Electric eel first lightning hit
      //
      IF_DEBUG { hitter->log("Cannot hit: %s is floating above me", to_short_string().c_str()); }
      if (is_player()) {
        msg("You watch the electrics going on beneath you.");
      }
      return false;
    }
  }

  if (is_floating_currently() && hitter->is_always_submerged_in_water()) {
    if (thing_size() > (int) THING_SIZE_NORMAL) {
      //
      // Krakens etc... Allow large things in the water to attack though.
      //
    } else {
      //
      // Eels etc...
      //
      IF_DEBUG { hitter->log("Cannot hit: %s is floating above me", to_short_string().c_str()); }
      if (is_player()) {
        msg("You watch the water thrash beneath you.");
      }
      return false;
    }
  }

  if (is_floating_currently() && hitter->is_always_submerged_in_lava()) {
    if (thing_size() > (int) THING_SIZE_NORMAL) {
      //
      // Demon?
      //
    } else {
      //
      // Fire ant
      //
      IF_DEBUG { hitter->log("Cannot hit: %s is floating above me", to_short_string().c_str()); }
      if (is_player()) {
        msg("You watch the lava roil beneath you.");
      }
      return false;
    }
  }

  //
  // Cruel to let things keep on hitting you when you're dead
  // Even worse, to let them eat you, but better if you are dead first.
  //
  if (is_dead || is_dying) {
    if (real_hitter->can_eat(this)) {
      IF_DEBUG { hitter->log("Cannot hit dead thing, but can eat: %s", to_short_string().c_str()); }
    } else {
      IF_DEBUG { hitter->log("Cannot hit: %s is dead", to_short_string().c_str()); }
      return false;
    }
  }

  if (is_resurrecting) {
    IF_DEBUG { hitter->log("Cannot hit: %s is resurrecting", to_short_string().c_str()); }
    return false;
  }

  if (hitter && (hitter->is_dead || hitter->is_dying)) {
    //
    // This case is hit if a ghost runs into a player. The ghost takes
    // damage. We don't want the player to keep absorbing hits when
    // the ghost is dead though.
    //
    if (hitter->is_monst()) {
      IF_DEBUG { hitter->log("No, hitter %s is already dead", to_short_string().c_str()); }
      return false;
    }
  }

  //
  // Check to see if this is a thing that can be damaged by the hitter.
  //
  if (hitter) {
    //
    // Walls and doors and other solid object are not damaged by poison
    // or similar effects. Limit it to explosions and the like.
    //
    // If the player is hitting these things, then inflict some damage.
    // But we could also allow occasional improvements due to training
    // exercises.
    //
    bool training = false;

    if (is_door()) {
      if (hitter->is_player() && attack_options->attack[ THING_ATTACK_NATURAL ]) {
        auto h = hitter->health_decr(pcg_random_range(1, 2));
        if (h <= 0) {
          h = health_set(0);
          hitter->dead("by smashing yourself to death on a door");
          return false;
        }
        hitter->msg("You smash your fists against the door!");
        training = true;

        //
        // Make too much noise and you stir something...
        //
        level->create_wandering_monster();
      } else if (! hitter->is_explosion() && ! hitter->is_projectile() && ! hitter->is_laser()
                 && ! hitter->is_weapon() && ! hitter->is_magical() && ! hitter->is_fire() && ! hitter->is_lava()
                 && ! hitter->gfx_pixelart_attack_anim()) {
        //
        // Not something that typically damages walls.
        //
        IF_DEBUG { hitter->log("No, %s is immune (1)", to_short_string().c_str()); }
        return false;
      }
    }

    if (is_wall() || is_rock()) {
      if (hitter->is_player() && attack_options->attack[ THING_ATTACK_NATURAL ]) {
        auto h = hitter->health_decr(pcg_random_range(1, 4));
        if (h <= 0) {
          h = health_set(0);
          hitter->dead("by smashing yourself to death on rock");
          return false;
        }
        hitter->msg("You smash your fists against the rock!");
        training = true;
      } else if (! hitter->is_explosion() && ! hitter->is_projectile() && ! hitter->is_laser()
                 && ! hitter->is_weapon() && ! hitter->is_magical() && ! hitter->is_fire() && ! hitter->is_lava()
                 && ! hitter->gfx_pixelart_attack_anim()) {
        //
        // Not something that typically damages walls.
        //
        IF_DEBUG { hitter->log("No, %s is immune (2)", to_short_string().c_str()); }
        return false;
      }
    }

    //
    // Rocky/ninja training mode
    //
    if (training) {
      hitter->physical_training_tick();
    }
  }

  IF_DEBUG { hitter->log("Hit succeeds"); }
  TRACE_AND_INDENT();

  int hit_and_destroyed;

  hit_and_destroyed = ai_hit_actual(hitter, real_hitter, attack_options, damage);
  if (hit_and_destroyed) {
    IF_DEBUG { hitter->log("Hit and destroyed victim"); }
  }

  return (hit_and_destroyed);
}
