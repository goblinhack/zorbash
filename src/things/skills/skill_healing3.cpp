//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_healing3.py
//

#include "my_native.hpp"
#include "things/skills/skill_healing0.hpp"

namespace mod_things_skills_skill_healing3 {

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y)
{
  if ((! (owner != 0))) {
    return false;
  }
  if ((my::thing_stamina(owner) < 6)) {
    return false;
  }
  if ([&]() { auto t1_0_ = my::thing_health(owner); auto t1_1_ = my::thing_health_max(owner); return (t1_0_ >= t1_1_); }()) {
    return false;
  }
  my::thing_stamina_decr(owner, 6);
  my::thing_health_incr(owner, 3);
  return false;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->skill_replaces_set("skill_healing2");
  self->stat_con_bonus_set(3);
  self->text_description_long2_set("Conversion rate is 6 stamina per turn to 3 health.");
  self->text_description_very_short_set("AccHeal 3");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  mod_things_skills_skill_healing0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_healing3", "accelerated health 3", "accelerated health 3");
}

void module_init(void)
{
  native_register("skill_healing3", "on_tick_when_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_skills_skill_healing3
