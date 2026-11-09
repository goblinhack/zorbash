//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_magic_missile.py
//

#include "my_native.hpp"

namespace mod_things_spells_spell_of_magic_missile {

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  int damage = 0;
  int enchant = 0;
  damage = my::thing_dmg_energy(item);
  enchant = my::thing_enchant_count_get(item);
  my::thing_dmg_current_set(owner, (damage + enchant));
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->dmg_chance_d1000_energy_set(0, 1000);
  self->dmg_energy_dice_set("1d6");
  self->gfx_targeted_projectile_set("projectile_magic_missile");
  self->is_loggable_set(true);
  self->is_spell_always_succeeds_set(true);
  self->is_spell_set(true);
  self->is_target_select_set(true);
  self->is_usable_set(true);
  self->on_use_do_set("me.on_use()");
  self->range_max_set(7);
  self->spell_base_name_set(name);
  self->spell_cost_set(2);
  self->text_a_or_an_set("a");
  self->text_description_long_set("Send a message to your enemies with a flash of directed energy.");
  self->text_description_short_set("Spell, magic missile.");
  self->text_description_very_short_set("MagicMiss");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "spell_of_magic_missile"});
  my::tile(self, {.tile = "spell_of_magic_missile_activated"});
}

static void init(void)
{
  tp_init("spell_of_magic_missile", "magic missile", "magic missile");
}

void module_init(void)
{
  native_register("spell_of_magic_missile", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_spells_spell_of_magic_missile
