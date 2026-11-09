//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_devoted_thrust3.py
//

#include "my_native.hpp"
#include "things/skills/skill_devoted_thrust0.hpp"

namespace mod_things_skills_skill_devoted_thrust3 {

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y);
static void on_use_skill(uint32_t owner, uint32_t skill, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y)
{
  if (((owner != 0) && (my::pcg_random_inclusive(1, 100) < 10))) {
    my::thing_stamina_decr(owner, 1);
  }
  return false;
}

static void on_use_skill(uint32_t owner, uint32_t skill, uint32_t target, int x, int y)
{
  int bonus = 0;
  if ((! (target != 0))) {
    return;
  }
  my::spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect");
  bonus = ((int) ((((double) (((double) my::thing_stamina(owner) / (double) 100.0))) * 50.0)));
  if ((bonus > 1)) {
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, ((std::string("%%fg=yellow$You strike with a mighty thrust of ") + std::to_string(bonus) + " additional damage.%%fg=reset$")).c_str());
    }
    my::thing_dmg_current_incr(owner, bonus);
    my::thing_stamina_decr(owner, bonus);
  } else {
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, "You run out of devotion.");
    }
    my::thing_skill_deactivate(owner, skill);
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->skill_replaces_set("skill_devoted_thrust2");
  self->stat_def_bonus_set((-2));
  self->stat_str_bonus_set(2);
  self->text_description_long4_set("When activated, 50 percent of your stamina will be converted to damage.");
  self->text_description_long5_set("When activated, 10 percent chance of draining stamina by 1.");
  self->text_description_very_short_set("DevThrst3");
  mod_things_skills_skill_devoted_thrust0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_devoted_thrust3", "devoted thrust 3", "devoted thrust 3");
}

void module_init(void)
{
  native_register("skill_devoted_thrust3", "on_tick_when_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("skill_devoted_thrust3", "on_use_skill", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use_skill((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_skills_skill_devoted_thrust3
