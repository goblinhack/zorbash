//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_super_health1.py
//

#include "my_native.hpp"
#include "things/skills/skill_super_health0.hpp"

namespace mod_things_skills_skill_super_health1 {

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y);
static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_cold(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_necrosis(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_stat_con(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static bool on_tick_when_activated(uint32_t owner, uint32_t skill, int x, int y)
{
  if ((! (owner != 0))) {
    return false;
  }
  if ((my::pcg_random_inclusive(1, 100) < 50)) {
    my::thing_stamina_incr(owner, 2);
    my::thing_health_incr(owner, 1);
  }
  return false;
}

static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  int new_damage = 0;
  new_damage = ((int) (((double) damage / (double) 2)));
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(owner, ((std::string("Your superior health reduces the poison damage to ") + std::to_string(new_damage) + ".")).c_str());
  }
  return new_damage;
}

static int on_owner_rcv_dmg_cold(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  int new_damage = 0;
  new_damage = ((int) (((double) damage / (double) 2)));
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(owner, ((std::string("Your superior health reduces the cold damage to ") + std::to_string(new_damage) + ".")).c_str());
  }
  return new_damage;
}

static int on_owner_rcv_dmg_necrosis(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  int new_damage = 0;
  new_damage = ((int) (((double) damage / (double) 2)));
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(owner, ((std::string("Your superior health reduces the necrosis damage to ") + std::to_string(new_damage) + ".")).c_str());
  }
  return new_damage;
}

static int on_owner_rcv_dmg_stat_con(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  int new_damage = 0;
  new_damage = ((int) (((double) damage / (double) 2)));
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(owner, ((std::string("Your superior health reduces the constitution damage to ") + std::to_string(new_damage) + ".")).c_str());
  }
  return new_damage;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->stat_con_bonus_set(2);
  self->text_description_long4_set("You will gain 2 stamina and 1 health at a 50 percent chance per turn.");
  self->text_description_long5_set("Cold, poison, necrosis and constitution damage will be reduced by 50 percent.");
  self->text_description_very_short_set("SupHealt1");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  mod_things_skills_skill_super_health0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_super_health1", "super health 1", "super health 1");
}

void module_init(void)
{
  native_register("skill_super_health1", "on_tick_when_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick_when_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("skill_super_health1", "on_owner_rcv_dmg_poison", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_poison((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_super_health1", "on_owner_rcv_dmg_cold", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_cold((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_super_health1", "on_owner_rcv_dmg_necrosis", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_necrosis((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_super_health1", "on_owner_rcv_dmg_stat_con", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_stat_con((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  init();
}

} // namespace mod_things_skills_skill_super_health1
