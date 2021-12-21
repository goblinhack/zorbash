//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_backtrace.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_math.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include <algorithm>

bool Thing::possible_to_attack(const Thingp victim)
{
  TRACE_NO_INDENT();
  auto me = tp();

  if (victim == this) {
    return false;
  }

  auto my_owner  = get_top_owner();
  auto its_owner = victim->get_top_owner();
  if (my_owner && (my_owner == its_owner)) {
    return false;
  }

  auto my_manifestor  = get_top_manifestor();
  auto its_manifestor = victim->get_top_manifestor();
  if (my_manifestor && (my_manifestor == its_manifestor)) {
    return false;
  }

  auto my_spawned_owner  = get_top_spawned_owner();
  auto its_spawned_owner = victim->get_top_spawned_owner();
  if (my_spawned_owner && (my_spawned_owner == its_spawned_owner)) {
    return false;
  }

  if (same_leader(victim)) {
    return false;
  }

  //
  // Weapons can't attack all by themselves. That would be nuts.
  //
  if (is_weapon() || is_wand() || is_ring()) {
    if (! my_owner) {
      return false;
    }
  }

  dbg("Is it possible to attack %s?", victim->to_string().c_str());
  TRACE_AND_INDENT();

  //
  // Fire attacks via tick so it can get you when you fall or jump into it.
  //
  if (is_fire()) {
    if (! is_monst() && ! is_laser() && ! is_projectile() && ! is_weapon()) {
      dbg("Cannot attack %s, I am fire", victim->to_string().c_str());
      return false;
    }
  }

  if (is_meat_eater() || attack_meat()) {
    //
    // Meat eaters eat you when you are dead!
    //
  } else {
    if (victim->is_dead) {
      dbg("Cannot attack %s, it's dead", victim->to_string().c_str());
      return false;
    }
  }

  //
  // No attacking of open doors!
  //
  if (victim->is_open) {
    dbg("Cannot attack %s, it's open", victim->to_string().c_str());
    return false;
  }

  //
  // Attacking of closed doors?
  //
  if (victim->is_door()) {
    if (me->is_able_to_break_down_doors()) {
      dbg("Can break down door %s", victim->to_string().c_str());
      return true;
    }
  }

  //
  // Don't attadk thy leader or follower
  //
  if (same_leader(victim)) {
    return false;
  }

  if (is_alive_monst() || is_resurrected) {
    if (me->is_jelly_baby_eater()) {
      if (victim->is_jelly_baby()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_treasure_eater()) {
      if (victim->is_treasure_type()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
      if (victim->is_carrying_treasure()) {
        dbg("Can steal from %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_potion_eater()) {
      if (victim->is_potion()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_item_magical_eater()) {
      if (victim->is_item_magical()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    //
    // Cleaners can attack cleaners?
    //
    if (me->is_item_magical_eater()) {
      if (victim->is_item_magical_eater()) {
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }

    //
    // Can we eats it?
    //
    if (me->is_meat_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by meat eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_meat()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead meat: %s", victim->to_string().c_str());
          return true;
        }

        dbg("Can attack meat or blood: %s", victim->to_string().c_str());
        return true;
      }
    }

    //
    // Can we attack the meat? Only if it is alive.
    //
    if (me->attack_meat()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("no, cannot attack %s, not is_attackable by meat eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_meat()) {
        if (victim->is_dead) {
          dbg("Can not attack dead meat: %s", victim->to_string().c_str());
          return false;
        }
        if (victim->is_dead) {
          dbg("Can not attack dead meat: %s", victim->to_string().c_str());
          return false;
        }

        dbg("Can attack living meat: %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->is_blood_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by blood eating monst", victim->to_string().c_str());
        return false;
      }

      if (victim->is_blood()) {
        //
        // Doesn't matter if dead, if it can eat you...
        //
        if (victim->is_dead) {
          dbg("Can eat dead blood: %s", victim->to_string().c_str());
          return true;
        }

        dbg("Can attack blood or blood: %s", victim->to_string().c_str());
        return true;
      }
    }

    if (me->attack_humanoid()) {
      if (victim->is_humanoid()) {
        if (! victim->is_dead) {
          dbg("Can attack humanoid: %s", victim->to_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_living()) {
      if (victim->is_living()) {
        if (! victim->is_dead) {
          dbg("Can attack living: %s", victim->to_string().c_str());
          return true;
        }
      }
    }

    if (me->attack_undead()) {
      if (victim->is_undead()) {
        if (! victim->is_dead) {
          dbg("Can attack undead: %s", victim->to_string().c_str());
          return true;
        }
      }
    }

    if (me->is_food_eater()) {
      if (! victim->is_attackable_by_monst()) {
        dbg("No, cannot attack %s, not is_attackable by food eating monst", victim->to_string().c_str());
        return false;
      }
      if (victim->is_food()) {
        dbg("Can attack food: %s", victim->to_string().c_str());
        return true;
      }
    }
  }

  if (is_player()) {
    if (victim->is_attackable_by_player()) {
      if (game->robot_mode) {
        if (victim->is_barrel()) {
          dbg("No, do not attack %s, is explosive barrel", victim->to_string().c_str());
          return false;
        }
      }
      if (victim->is_foilage()) {
        dbg("No, do not attack %s", victim->to_string().c_str());
        return false;
      }
      dbg("Can attack %s", victim->to_string().c_str());
      return true;
    }
    dbg("No, cannot attack %s, not is_attackable", victim->to_string().c_str());
    return false;
  }

  if (is_weapon()) {
    auto o = get_immediate_owner();
    if (o) {
      if (o->is_monst()) {
        if (! victim->is_attackable_by_monst()) {
          // Too noisy
          // dbg("Cannot weapon attack %s, not is_attackable by monst",
          //     victim->to_string().c_str());
          return false;
        }
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      } else {
        if (! victim->is_attackable_by_player()) {
          dbg("Cannot weapon attack %s, not is_attackable by player", victim->to_string().c_str());
          return false;
        }
        dbg("Can attack %s", victim->to_string().c_str());
        return true;
      }
    }
  }

  if (me->is_fire() || me->is_lava()) {
    if (me->is_monst()) {
      //
      // Fire monsters do not attack always
      //
    } else if (victim->is_burnable() || victim->is_very_combustible() || victim->is_combustible()) {
      if (! victim->is_fire() && ! victim->is_lava()) {
        dbg("Can attack as I am firey %s", victim->to_string().c_str());
        return true;
      }
    }
  }

  if (is_enemy(victim)) {
    dbg("Can attack enemy %s", victim->to_string().c_str());
    return true;
  }

  if (is_weapon()) {
    if (victim->is_foilage() || victim->is_sticky() || victim->is_spiderweb()) {
      dbg("Can attack scenery %s", victim->to_string().c_str());
      return true;
    }
  }

  if (victim->is_alive_monst() || victim->is_combustible() || victim->is_very_combustible() ||
      victim->is_burnable() || victim->is_wall() || victim->is_rock() || victim->is_door() || victim->is_bridge() ||
      victim->is_dry_grass() || victim->is_treasure_type() || victim->is_enchantstone() || victim->is_skillstone() ||
      victim->is_foilage() || victim->is_spiderweb() || victim->is_sticky() || victim->is_brazier() ||
      victim->is_barrel() || victim->is_player() || victim->is_food() || victim->is_bag_item()) {

    if (is_laser()) {
      dbg("Can attack as laser %s", victim->to_string().c_str());
      return true;
    }

    if (is_projectile()) {
      dbg("Can attack as projectile %s", victim->to_string().c_str());
      return true;
    }

    if (is_wand()) {
      dbg("Can attack as wand %s", victim->to_string().c_str());
      return true;
    }

    if (is_ring()) {
      dbg("Can attack as ring %s", victim->to_string().c_str());
      return true;
    }

    if (is_explosion()) {
      dbg("Can attack as explosion %s", victim->to_string().c_str());
      return true;
    }
  }

  dbg("Cannot attack %s, ignore", victim->to_string().c_str());

  return false;
}

bool Thing::possible_to_attack_at(point at)
{
  bool ret = false;

  dbg("Possible to attack? at %s", at.to_string().c_str());
  TRACE_AND_INDENT();

  FOR_ALL_COLLISION_THINGS(level, victim, at.x, at.y)
  {
    if (! possible_to_attack(victim)) {
      continue;
    }
    dbg("Yes; %s", victim->to_string().c_str());
    ret = true;
  }

  if (! ret) {
    dbg("No");
  }

  FOR_ALL_THINGS_END()

  return ret;
}

bool Thing::attack(point future_pos)
{
  bool up     = future_pos.y < curr_at.y;
  bool down   = future_pos.y > curr_at.y;
  bool left   = future_pos.x < curr_at.x;
  bool right  = future_pos.x > curr_at.x;
  bool attack = true;
  bool idle   = false;

  verify(MTYPE_THING, this);
  bool shove_allowed  = true;
  bool attack_allowed = true;
  return (move(future_pos, up, down, left, right, attack, idle, shove_allowed, attack_allowed));
}

bool Thing::attack(Thingp victim, bool prefer_attack_with_jaws)
{
  dbg("Attack %s", victim->to_string().c_str());
  TRACE_AND_INDENT();

  set_idle_count(0);

  auto owner = get_top_owner();

  if (! possible_to_attack(victim)) {
    dbg("Attack failed, not possible to attack %s", victim->to_string().c_str());
    return false;
  }

  if (is_able_to_tire()) {
    if (! get_stamina()) {
      if (is_player()) {
        TOPCON("You are too tired to attack. You need to rest.");
      }
      return false;
    }
  }

  //
  // attack modifier: strength + attack bonus
  //
  auto attack_total = get_stat_strength() + get_stat_attack_bonus();
  if (owner) {
    attack_total += owner->get_stat_strength();
    attack_total += owner->get_stat_attack_bonus();
  }

  attack_total -= get_idle_count();
  attack_total -= get_stuck_count();

  //
  // defence modifier: armor class + dexterity
  //
  auto defence_total = victim->get_stat_armor_class();
  defence_total += victim->get_stat_dexterity();

  auto victim_owner = get_top_owner();
  if (victim_owner) {
    defence_total = victim_owner->get_stat_armor_class();
    defence_total = victim_owner->get_stat_dexterity();
  }

  defence_total -= victim->get_idle_count();
  defence_total -= victim->get_stuck_count();

  //
  // Terrain penalties
  //
  if (! is_aquatic()) {
    if (level->is_water(curr_at)) {
      attack_total /= 2;
    }
    if (level->is_deep_water(curr_at)) {
      attack_total /= 2;
    }
  }

  if (! victim->is_aquatic()) {
    if (level->is_water(victim->curr_at)) {
      defence_total /= 2;
    }
    if (level->is_deep_water(victim->curr_at)) {
      defence_total /= 2;
    }
  }

  bool damage_set       = false;
  bool attack_poison    = false;
  bool attack_future1   = false;
  bool attack_future2   = false;
  bool attack_future3   = false;
  bool attack_future4   = false;
  bool attack_fire      = false;
  bool attack_crush     = false;
  bool attack_lightning = false;
  bool attack_energy    = false;
  bool attack_acid      = false;
  bool attack_digest    = false;
  bool attack_necrosis  = false;
  bool attack_bite      = false;
  int  damage           = 0;

  //
  // Chance of poison damage?
  //
  if (! damage_set || prefer_attack_with_jaws) {
    if ((int) pcg_random_range(0, 1000) < damage_poison_chance_d1000()) {
      int damage_poison = get_damage_poison();
      if (damage_poison > 0) {
        damage        = damage_poison;
        damage_set    = true;
        attack_poison = true;
      }
    }
  }
  //
  // Chance of attack_future1 damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_future1_chance_d1000()) {
      int attack_future1 = get_damage_future1();
      if (attack_future1 > 0) {
        damage         = attack_future1;
        damage_set     = true;
        attack_future1 = true;
      }
    }
  }

  //
  // Chance of attack_future2 damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_future2_chance_d1000()) {
      int attack_future2 = get_damage_future2();
      if (attack_future2 > 0) {
        damage         = attack_future2;
        damage_set     = true;
        attack_future2 = true;
      }
    }
  }

  //
  // Chance of attack_future3 damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_future3_chance_d1000()) {
      int attack_future3 = get_damage_future3();
      if (attack_future3 > 0) {
        damage         = attack_future3;
        damage_set     = true;
        attack_future3 = true;
      }
    }
  }

  //
  // Chance of attack_future4 damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_future4_chance_d1000()) {
      int attack_future4 = get_damage_future4();
      if (attack_future4 > 0) {
        damage         = attack_future4;
        damage_set     = true;
        attack_future4 = true;
      }
    }
  }

  //
  // Chance of attack_fire damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_fire_chance_d1000()) {
      int attack_fire = get_damage_fire();
      if (attack_fire > 0) {
        damage      = attack_fire;
        damage_set  = true;
        attack_fire = true;
      }
    }
  }

  //
  // Chance of attack_crush damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_crush_chance_d1000()) {
      int attack_crush = get_damage_crush();
      if (attack_crush > 0) {
        damage       = attack_crush;
        damage_set   = true;
        attack_crush = true;
      }
    }
  }

  //
  // Chance of attack_lightning damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_lightning_chance_d1000()) {
      int attack_lightning = get_damage_lightning();
      if (attack_lightning > 0) {
        damage           = attack_lightning;
        damage_set       = true;
        attack_lightning = true;
      }
    }
  }

  //
  // Chance of attack_energy damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_energy_chance_d1000()) {
      int attack_energy = get_damage_energy();
      if (attack_energy > 0) {
        damage        = attack_energy;
        damage_set    = true;
        attack_energy = true;
      }
    }
  }

  //
  // Chance of attack_acid damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_acid_chance_d1000()) {
      int attack_acid = get_damage_acid();
      if (attack_acid > 0) {
        damage      = attack_acid;
        damage_set  = true;
        attack_acid = true;
      }
    }
  }

  //
  // Chance of attack_digest damage?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_digest_chance_d1000()) {
      int attack_digest = get_damage_digest();
      if (attack_digest > 0) {
        damage        = attack_digest;
        damage_set    = true;
        attack_digest = true;
      }
    }
  }

  //
  // Chance of necrosis damage?
  //
  if (! damage_set || prefer_attack_with_jaws) {
    if ((int) pcg_random_range(0, 1000) < damage_necrosis_chance_d1000()) {
      int damage_necrosis = get_damage_necrosis();
      if (damage_necrosis > 0) {
        damage          = damage_necrosis;
        damage_set      = true;
        attack_necrosis = true;
      }
    }
  }

  //
  // Bite?
  //
  if (! damage_set || prefer_attack_with_jaws) {
    if ((int) pcg_random_range(0, 1000) < damage_bite_chance_d1000()) {
      int damage_bite = get_damage_bite();
      if (damage_bite > 0) {
        damage      = damage_bite + stat_to_bonus(attack_total);
        damage_set  = true;
        attack_bite = true;
      }
    }
  }

  //
  // Melee?
  //
  if (! damage_set) {
    if ((int) pcg_random_range(0, 1000) < damage_melee_chance_d1000()) {
      damage = get_damage_melee() + stat_to_bonus(attack_total);
      if (damage > 0) {
        damage_set = true;
      }
    }
  }
  if (! damage_set) {
    if (owner) {
      if ((int) pcg_random_range(0, 1000) < owner->damage_melee_chance_d1000()) {
        damage = get_damage_melee() + stat_to_bonus(attack_total);
        if (damage > 0) {
          damage_set = true;
        }
      }
    }
  }

  //
  // This overrides other damage types. For when we are stuck inside a cleaner
  //
  if (is_engulfer()) {
    if (victim->curr_at == curr_at) {
      damage           = get_damage_digest();
      attack_poison    = false;
      attack_future1   = false;
      attack_future2   = false;
      attack_future3   = false;
      attack_future4   = false;
      attack_fire      = false;
      attack_crush     = false;
      attack_lightning = false;
      attack_energy    = false;
      attack_acid      = false;
      attack_digest    = true;
      attack_necrosis  = false;
      attack_bite      = false;
      damage_set       = true;
    }
  }

  //
  // If some attack type worked, then make sure we have some damage
  //
  if (damage_set) {
    if (damage < 1) {
      damage = 1;
    }
  }

  if (damage <= 0) {
    if (is_player() || (owner && owner->is_player())) {
      TOPCON("You inflict no damage on %s.", victim->text_the().c_str());
    }
    dbg("Attack failed, no damage");
    return false;
  }

  if (is_player()) {
    //
    // Player always uses their weapon
    //
    if (get_equip(MONST_EQUIP_WEAPON)) {
      auto delta = victim->curr_at - curr_at;
      move_set_dir_from_delta(delta);
      equip_use_may_attack(MONST_EQUIP_WEAPON);
      return true;
    }
  } else if (is_monst()) {
    //
    // Don't swing weapons at pools of blood.
    //
    if (victim->is_alive_monst() || victim->is_door() || victim->is_player() || victim->is_mob()) {
      if (get_equip(MONST_EQUIP_WEAPON)) {
        auto delta = victim->curr_at - curr_at;
        move_set_dir_from_delta(delta);
        equip_use_may_attack(MONST_EQUIP_WEAPON);
        return true;
      }
    } else if (is_monst()) {
      attack_bite = true;
    }
  }

  bool crit   = false;
  bool fumble = false;

  //
  // See if we can bypass its defences
  //
  if (is_player() || is_alive_monst()) {
    if (victim->is_dead) {
      //
      // It's hard to miss a corpse.
      //
    } else if (victim->is_always_hit()) {
      //
      // You just cannot miss this.
      //
    } else {
      dbg("attack_total %d %s defence_total %d", attack_total, victim->to_string().c_str(), defence_total);
      auto hit = d20roll(attack_total, defence_total, fumble, crit);

      //
      // Cannot miss (if engulfing?)
      //
      if (victim->curr_at == curr_at) {
        hit = true;
      }

      if (! hit) {
        if (is_player() || (owner && owner->is_player())) {
          TOPCON("You miss %s.", victim->text_the().c_str());
          msg("!");
        } else if (victim->is_player()) {
          if (owner) {
            TOPCON("%s misses with %s.", owner->text_the().c_str(), text_The().c_str());
          } else {
            TOPCON("%s misses.", text_The().c_str());
          }
        } else {
          dbg("The attack missed (att %d, def %d) on %s", attack_total, defence_total, victim->to_string().c_str());
        }

        if (attack_lunge()) {
          lunge(victim->curr_at);
        }

        //
        // An attempt at an attack counts
        //
        victim->add_enemy(this);

        //
        // We tried to attack, so do not move
        //
        return true;
      }
    }
  }

  if (victim->is_hit(this, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                     attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                     attack_acid, attack_digest, damage)) {
    dbg("The attack succeeded");

    if (attack_lunge()) {
      lunge(victim->curr_at);
    }
    if (attack_eater()) {
      health_boost(victim->get_nutrition());
    }
    if (is_destroyed_on_hitting() || is_destroyed_on_hit_or_miss()) {
      dead("by foolishness");
    }
    decr_stamina();
    return true;
  }

  victim->on_you_miss_do(this);

  //
  // Missiles?
  //
  if (is_destroyed_on_hit_or_miss()) {
    if (is_loggable()) {
      dbg("Attack missed %s", victim->to_string().c_str());
    }
    if (attack_lunge()) {
      lunge(victim->curr_at);
    }
    dead("by foolishness");
    return true;
  }

  return false;
}
bool Thing::bite(Thingp victim) { return attack(victim, true); }

int Thing::is_attacked_with_damage_melee(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_bite(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = true;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_poison(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = true;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_necrosis(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = true;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_future1(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = true;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_future2(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = true;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_future3(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = true;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_future4(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = true;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_fire(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = true;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_crush(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = true;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_lightning(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = true;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_energy(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = true;
  const bool attack_acid      = false;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_acid(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = true;
  const bool attack_digest    = false;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}

int Thing::is_attacked_with_damage_digest(Thingp hitter, int damage)
{
  TRACE_NO_INDENT();
  const bool crit             = false;
  const bool attack_bite      = false;
  const bool attack_poison    = false;
  const bool attack_necrosis  = false;
  const bool attack_future1   = false;
  const bool attack_future2   = false;
  const bool attack_future3   = false;
  const bool attack_future4   = false;
  const bool attack_fire      = false;
  const bool attack_crush     = false;
  const bool attack_lightning = false;
  const bool attack_energy    = false;
  const bool attack_acid      = false;
  const bool attack_digest    = true;
  return (is_hit(hitter, crit, attack_bite, attack_poison, attack_necrosis, attack_future1, attack_future2,
                 attack_future3, attack_future4, attack_fire, attack_crush, attack_lightning, attack_energy,
                 attack_acid, attack_digest, damage));
}
