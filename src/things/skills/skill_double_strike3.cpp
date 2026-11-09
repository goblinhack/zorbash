//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_double_strike3.py
//

#include "my_native.hpp"
#include "things/skills/skill_double_strike0.hpp"

namespace mod_things_skills_skill_double_strike3 {

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
  int attack = 0;
  int dmg = 0;
  attack = my::thing_attack_num_get(owner);
  if ((attack == 0)) {
    return;
  }
  if ((! (target != 0))) {
    return;
  }
  my::spawn_using_items_radius_range(owner, skill, target, "skill_double_strike_effect");
  dmg = my::thing_dmg_current(owner);
  dmg = ((int) ((((double) ((double) (dmg)) / (double) 100.0) * 50.0)));
  if ((dmg == 0)) {
    dmg = 1;
  }
  my::thing_dmg_current_set(owner, dmg);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->dmg_num_of_attacks_set(2);
  self->skill_replaces_set("skill_double_strike2");
  self->stat_def_bonus_set((-1));
  self->stat_str_bonus_set(2);
  self->text_description_long2_set("The additional attack will be 50 percent of the initial attack.");
  self->text_description_long3_set("When activated, 10 percent chance of draining stamina by 1 per move.");
  self->text_description_short_set("Double strike skill.");
  self->text_description_very_short_set("DbStrike3");
  mod_things_skills_skill_double_strike0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_double_strike3", "double strike 3", "double attack 3");
}

void module_init(void)
{
  native_register("skill_double_strike3", "on_tick_when_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("skill_double_strike3", "on_use_skill", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use_skill((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_skills_skill_double_strike3
