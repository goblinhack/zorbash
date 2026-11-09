//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_protection.py
//

#include "my_native.hpp"

namespace mod_things_spells_spell_of_protection {

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  uint32_t spell = 0;
  spell = my::place_at(target, "spell_of_protection_barrier", x, y);
  if ((spell != 0)) {
    if (my::thing_is_the_grid(target)) {
      my::thing_set_leader(spell, owner);
    } else {
      my::thing_set_leader(spell, target);
    }
  }
  my::place_at(target, "magical_effect", x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_targeted_laser_set("laser_magic_effect");
  self->is_able_to_be_reflected_set(true);
  self->is_loggable_set(true);
  self->is_spell_always_succeeds_set(true);
  self->is_spell_of_protection_set(true);
  self->is_spell_set(true);
  self->is_target_select_set(true);
  self->is_usable_set(true);
  self->on_use_do_set("me.on_use()");
  self->range_max_set(7);
  self->spell_base_name_set(name);
  self->spell_cost_set(5);
  self->text_a_or_an_set("a");
  self->text_description_long_set("Use this spell to place a magical barrier around a monster to protect it, or yourself, from harm");
  self->text_description_short_set("Spell of protection.");
  self->text_description_very_short_set("Holding");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "spell_of_protection"});
  my::tile(self, {.tile = "spell_of_protection_activated"});
}

static void init(void)
{
  tp_init("spell_of_protection", "protection", "protection");
}

void module_init(void)
{
  native_register("spell_of_protection", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_spells_spell_of_protection
