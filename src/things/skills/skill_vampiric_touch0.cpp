//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_vampiric_touch0.py
//

#include "my_native.hpp"
#include "things/skills/skill_vampiric_touch0.hpp"

namespace mod_things_skills_skill_vampiric_touch0 {

int do_vampiric_touch(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage, int damage_reduction_percent)
{
  int dmg_reduction = 0;
  int health_boost = 0;
  std::string real_hitter_name;
  int stamina_boost = 0;
  uint32_t target = 0;
  if ((real_hitter == me)) {
    return damage;
  }
  if (my::thing_is_undead(real_hitter)) {
    return damage;
  }
  dmg_reduction = 0;
  if (my::thing_is_monst(real_hitter)) {
    dmg_reduction = ((int) ((((double) ((double) (damage)) / (double) 100.0) * damage_reduction_percent)));
    if ((dmg_reduction == 0)) {
      dmg_reduction = 1;
    }
  }
  if ((dmg_reduction > 0)) {
    if (((owner != 0) && [&]() { auto t1_0_ = my::thing_health(owner); auto t1_1_ = my::thing_health_max(owner); return (t1_0_ < t1_1_); }())) {
      health_boost = ((int) (((double) ((double) (dmg_reduction)) / (double) 2.0)));
      my::thing_health_incr(owner, health_boost);
      stamina_boost = dmg_reduction;
      my::thing_stamina_incr(owner, stamina_boost);
      if (((owner != 0) && my::thing_is_player(owner))) {
        if ((health_boost > 0)) {
          real_hitter_name = my::thing_name_get(real_hitter);
          my::thing_msg(owner, ((std::string("Vampiric touch heals you for ") + std::to_string(health_boost) + " and drains the " + real_hitter_name + " for " + std::to_string(dmg_reduction) + " stamina.")).c_str());
        } else if ((stamina_boost > 0)) {
          real_hitter_name = my::thing_name_get(real_hitter);
          my::thing_msg(owner, ((std::string("Vampiric touch replenishes you for ") + std::to_string(stamina_boost) + " and drains the " + real_hitter_name + " for " + std::to_string(dmg_reduction) + " stamina.")).c_str());
        }
      }
    }
    target = real_hitter;
    my::thing_hit_dmg_stamina(me, me, target, dmg_reduction);
  }
  return (damage - dmg_reduction);
}

void tp_init(Tpp self)
{
  self->gfx_ascii_shown_set(true);
  self->is_loggable_set(true);
  self->is_skill_set(true);
  self->is_tickable_set(true);
  self->on_owner_rcv_dmg_acid_do_set("me.on_owner_rcv_dmg_acid()");
  self->on_owner_rcv_dmg_bite_do_set("me.on_owner_rcv_dmg_bite()");
  self->on_owner_rcv_dmg_claw_do_set("me.on_owner_rcv_dmg_claw()");
  self->on_owner_rcv_dmg_cold_do_set("me.on_owner_rcv_dmg_cold()");
  self->on_owner_rcv_dmg_crush_do_set("me.on_owner_rcv_dmg_crush()");
  self->on_owner_rcv_dmg_digest_do_set("me.on_owner_rcv_dmg_digest()");
  self->on_owner_rcv_dmg_drown_do_set("me.on_owner_rcv_dmg_drown()");
  self->on_owner_rcv_dmg_energy_do_set("me.on_owner_rcv_dmg_energy()");
  self->on_owner_rcv_dmg_fire_do_set("me.on_owner_rcv_dmg_fire()");
  self->on_owner_rcv_dmg_heat_do_set("me.on_owner_rcv_dmg_heat()");
  self->on_owner_rcv_dmg_lightning_do_set("me.on_owner_rcv_dmg_lightning()");
  self->on_owner_rcv_dmg_melee_do_set("me.on_owner_rcv_dmg_melee()");
  self->on_owner_rcv_dmg_missile_do_set("me.on_owner_rcv_dmg_missile()");
  self->on_owner_rcv_dmg_nat_att_do_set("me.on_owner_rcv_dmg_nat_att()");
  self->on_owner_rcv_dmg_necrosis_do_set("me.on_owner_rcv_dmg_necrosis()");
  self->on_owner_rcv_dmg_poison_do_set("me.on_owner_rcv_dmg_poison()");
  self->on_owner_rcv_dmg_stat_con_do_set("me.on_owner_rcv_dmg_stat_con()");
  self->on_owner_rcv_dmg_stat_str_do_set("me.on_owner_rcv_dmg_stat_str()");
  self->skill_base_name_set("skill_vampiric_touch");
  self->text_description_long2_set("This is a powerful skill and whilst active, you will experience a powerful constitution and luck drain. Do vampires need luck anyway\?");
  self->text_description_long3_set("This skill is not effective against the undead. Also beware that certain types of damage, such as heat fire, lightning and drowning will be more potent whilst this skill is active.");
  self->text_description_long_set("With this dark skill you are able to gain stamina and some health from the creature that attacked you, draining it for the same amount you recover");
  self->text_description_short_set("vampiric touch.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "skill_vampiric_touch"});
  my::tile(self, {.tile = "skill_vampiric_touch_activated"});
}

void module_init(void)
{
  native_register("skill_vampiric_touch0", "do_vampiric_touch", 8, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) do_vampiric_touch((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6], (int) a[7]), {}}; });
}

} // namespace mod_things_skills_skill_vampiric_touch0
