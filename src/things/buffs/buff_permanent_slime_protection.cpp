//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_slime_protection.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_slime_protection {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static int on_owner_rcv_dmg(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static int on_owner_rcv_dmg_melee(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_drown(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_bite(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_claw(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_cold(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_fire(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_heat(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_crush(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_lightning(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_energy(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_acid(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_digest(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_nat_att(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_necrosis(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_stat_str(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_stat_con(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "A protective green slimy glow surrounds you.");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The protective green slimy glow around you fades.");
  }
}

static int on_owner_rcv_dmg(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  if (my::thing_is_slime(hitter)) {
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(me, "You take half damage from the slime attack.");
    }
    return ((int) (((double) damage / (double) 2)));
  }
  return damage;
}

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_impact") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
  if (my::thing_is_slime(victim)) {
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(me, "You issue double damage slime attack.");
    }
    return ((damage + my::thing_enchant_count_get(me)) * 2);
  }
  return (damage + my::thing_enchant_count_get(me));
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
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
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
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_heat(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_crush(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_lightning(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_energy(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_acid(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_digest(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
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
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static int on_owner_rcv_dmg_stat_con(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  return on_owner_rcv_dmg(me, owner, hitter, real_hitter, x, y, damage);
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_loggable_set(true);
  self->is_runic_defensive_class_A_set(true);
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_attack_dmg_melee_do_set("me.on_owner_attack_dmg_melee()");
  self->on_owner_rcv_dmg_acid_do_set("me.on_owner_rcv_dmg_acid()");
  self->on_owner_rcv_dmg_bite_do_set("me.on_owner_rcv_dmg_bite()");
  self->on_owner_rcv_dmg_claw_do_set("me.on_owner_rcv_dmg_claw()");
  self->on_owner_rcv_dmg_cold_do_set("me.on_owner_rcv_dmg_cold()");
  self->on_owner_rcv_dmg_crush_do_set("me.on_owner_rcv_dmg_crush()");
  self->on_owner_rcv_dmg_digest_do_set("me.on_owner_rcv_dmg_digest()");
  self->on_owner_rcv_dmg_drown_do_set("me.on_owner_rcv_dmg_drown()");
  self->on_owner_rcv_dmg_energy_do_set("me.on_owner_rcv_dmg_energy()");
  self->on_owner_rcv_dmg_fire_do_set("me.on_owner_rcv_dmg_fire()");
  self->on_owner_rcv_dmg_lightning_do_set("me.on_owner_rcv_dmg_lightning()");
  self->on_owner_rcv_dmg_melee_do_set("me.on_owner_rcv_dmg_melee()");
  self->on_owner_rcv_dmg_nat_att_do_set("me.on_owner_rcv_dmg_nat_att()");
  self->on_owner_rcv_dmg_necrosis_do_set("me.on_owner_rcv_dmg_necrosis()");
  self->on_owner_rcv_dmg_poison_do_set("me.on_owner_rcv_dmg_poison()");
  self->on_owner_rcv_dmg_stat_con_do_set("me.on_owner_rcv_dmg_stat_con()");
  self->on_owner_rcv_dmg_stat_str_do_set("me.on_owner_rcv_dmg_stat_str()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->text_description_long_set("Fear slime no more. You now issue double damage on slime composed monstrosities and receive only half damage from their vile attacks.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_slime_protection"});
}

static void init(void)
{
  tp_init("buff_permanent_slime_protection", "slime protection");
}

void module_init(void)
{
  native_register("buff_permanent_slime_protection", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_permanent_slime_protection", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_melee", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_poison", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_poison((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_drown", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_drown((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_bite", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_bite((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_claw", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_claw((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_cold", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_cold((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_fire", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_fire((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_heat", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_heat((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_crush", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_crush((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_lightning", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_lightning((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_energy", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_energy((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_acid", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_acid((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_digest", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_digest((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_nat_att", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_nat_att((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_necrosis", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_necrosis((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_stat_str", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_stat_str((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_slime_protection", "on_owner_rcv_dmg_stat_con", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_stat_con((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_permanent_slime_protection
