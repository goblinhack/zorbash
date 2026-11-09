//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_artful_dodging3.py
//

#include "my_native.hpp"
#include "things/skills/skill_artful_dodging0.hpp"

namespace mod_things_skills_skill_artful_dodging3 {

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y)
{
  if ((! (owner != 0))) {
    return false;
  }
  if ([&]() { auto t1_0_ = my::thing_stamina(owner); auto t1_1_ = my::thing_stamina_max(owner); return (t1_0_ >= t1_1_); }()) {
    return false;
  }
  if (((owner != 0) && (my::pcg_random_inclusive(1, 100) < 30))) {
    my::thing_stamina_incr(owner, 1);
    return false;
  }
  return false;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->skill_replaces_set("skill_artful_dodging2");
  self->stat_def_bonus_set(2);
  self->stat_dex_bonus_set(3);
  self->stat_thv_bonus_set(5);
  self->text_description_long3_set("Stamina will be recovered at a rate of 1 with a 30 percent chance per move.");
  self->text_description_very_short_set("ArtDodge3");
  mod_things_skills_skill_artful_dodging0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_artful_dodging3", "artful dodging 3", "artful dodging 3");
}

void module_init(void)
{
  native_register("skill_artful_dodging3", "on_tick_when_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_skills_skill_artful_dodging3
