//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/skills/skill_vampiric_touch1.py
//

#include "my_native.hpp"
#include "things/skills/skill_vampiric_touch0.hpp"

namespace mod_things_skills_skill_vampiric_touch1 {

static int on_owner_rcv_dmg(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_melee(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_drown(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_bite(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_claw(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_cold(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_fire(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_heat(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_crush(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_missile(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_lightning(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_energy(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_acid(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_digest(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_nat_att(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_necrosis(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_stat_str(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_stat_con(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static int on_owner_rcv_dmg(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return mod_things_skills_skill_vampiric_touch0::do_vampiric_touch(me, owner, hitter, real_hitter, x, y, damage, 10);
}

static int on_owner_rcv_dmg_melee(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_drown(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, (damage * 2));
}

static int on_owner_rcv_dmg_bite(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_claw(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_cold(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_fire(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, (damage * 2));
}

static int on_owner_rcv_dmg_heat(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, (damage * 2));
}

static int on_owner_rcv_dmg_crush(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static int on_owner_rcv_dmg_missile(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static int on_owner_rcv_dmg_lightning(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, (damage * 2));
}

static int on_owner_rcv_dmg_energy(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static int on_owner_rcv_dmg_acid(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static int on_owner_rcv_dmg_digest(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static int on_owner_rcv_dmg_nat_att(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_necrosis(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_stat_str(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static int on_owner_rcv_dmg_stat_con(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return damage;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->stat_con_bonus_set((-4));
  self->stat_luck_bonus_set((-4));
  self->stat_psi_bonus_set(1);
  self->text_description_long4_set("Damage reduction is 10 percent of damage dealt. Of that, the damage reduction will be applied to your stamina, and conversely will drain the attacker for the same amount. Health will improve at 50 percent of the damage reduction");
  self->text_description_very_short_set("VamTouch1");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  mod_things_skills_skill_vampiric_touch0::tp_init(self);
}

static void init(void)
{
  tp_init("skill_vampiric_touch1", "vampiric touch 1", "vampiric touch 1");
}

void module_init(void)
{
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_melee", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_poison", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_poison((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_drown", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_drown((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_bite", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_bite((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_claw", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_claw((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_cold", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_cold((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_fire", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_fire((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_heat", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_heat((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_crush", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_crush((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_missile", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_missile((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_lightning", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_lightning((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_energy", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_energy((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_acid", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_acid((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_digest", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_digest((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_nat_att", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_nat_att((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_necrosis", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_necrosis((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_stat_str", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_stat_str((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("skill_vampiric_touch1", "on_owner_rcv_dmg_stat_con", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_stat_con((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  init();
}

} // namespace mod_things_skills_skill_vampiric_touch1
