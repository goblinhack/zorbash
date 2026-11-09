//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_double_damage.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_double_damage {

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_impact") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
  damage = ((damage * 2) + my::thing_enchant_count_get(me));
  return damage;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_loggable_set(true);
  self->is_runic_offensive_class_A_set(true);
  self->on_owner_attack_dmg_melee_do_set("me.on_owner_attack_dmg_melee()");
  self->text_description_long_set("Wield twice the amount of normal melee damage with no stamina loss!");
  self->text_description_short_set("Double damage");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_double_damage"});
}

static void init(void)
{
  tp_init("buff_permanent_double_damage", "double damage", "double damage");
}

void module_init(void)
{
  native_register("buff_permanent_double_damage", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_permanent_double_damage
