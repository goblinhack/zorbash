//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_primal_rage5.py
//

#include "my_native.hpp"
#include "things/skills/skill_primal_rage0.hpp"

namespace mod_things_skills_skill_primal_rage5 {

static bool on_tick_when_deactivated(uint32_t owner, uint32_t skill, int x, int y);
static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y);
static void on_use_skill(uint32_t owner, uint32_t skill, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static bool on_tick_when_deactivated(uint32_t owner, uint32_t skill, int x, int y)
{
  if (((owner != 0) && [&]() { auto t1_0_ = my::thing_health(owner); auto t1_1_ = ((double) my::thing_health_max(owner) / (double) 20); return (t1_0_ < t1_1_); }())) {
    my::thing_raging_set(owner, true);
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, "%%fg=red$You feel primal rage coursing through your veins!%%fg=reset$");
    }
    my::thing_skill_activate(owner, skill);
    return true;
  }
  return false;
}

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y)
{
  if ((owner != 0)) {
    if ([&]() { auto t1_0_ = my::thing_health(owner); auto t1_1_ = ((double) my::thing_health_max(owner) / (double) 25); return (t1_0_ < t1_1_); }()) {
      if ((my::pcg_random_inclusive(1, 100) < 5)) {
        my::thing_stamina_decr(owner, 1);
      }
    } else {
      my::thing_raging_set(owner, false);
      if (((owner != 0) && my::thing_is_player(owner))) {
        my::thing_msg(owner, "You feel your primal rage dissipate.");
      }
    }
  }
  return false;
}

static void on_use_skill(uint32_t owner, uint32_t skill, uint32_t target, int x, int y)
{
  int bonus = 0;
  if ((! (target != 0))) {
    return;
  }
  my::spawn_using_items_radius_range(owner, skill, target, "skill_primal_rage_effect");
  bonus = 6;
  my::thing_dmg_current_incr(owner, bonus);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(owner, ((std::string("%%fg=red$You rage hit for ") + std::to_string(bonus) + " additional damage.%%fg=reset$")).c_str());
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->skill_replaces_set("skill_primal_rage4");
  self->stat_att_bonus_set(3);
  self->stat_def_bonus_set(1);
  self->stat_str_bonus_set(3);
  self->text_description_long3_set("While raging you gain 6 damage points per attack and gain additional strength bonuses.");
  self->text_description_long4_set("Raging will auto activate at 20 percent of your health and deactivate at 25 percent.");
  self->text_description_long5_set("With this level of skill you only have a 1 percent chance of draining stamina giving you with a true tireless rage.");
  self->text_description_very_short_set("TireRage2");
  mod_things_skills_skill_primal_rage0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_primal_rage5", "tireless rage 2", "tireless rage 2");
}

void module_init(void)
{
  native_register("skill_primal_rage5", "on_tick_when_deactivated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_deactivated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("skill_primal_rage5", "on_tick_when_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("skill_primal_rage5", "on_use_skill", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use_skill((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_skills_skill_primal_rage5
