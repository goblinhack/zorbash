//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_haste.py
//

#include "my_native.hpp"

namespace mod_things_spells_spell_of_haste {

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  for (auto it : my::level_get_all(item, x, y)) {
    if ((my::thing_is_alive_monst(it) || my::thing_is_player(it))) {
      my::thing_buff_add(it, "buff_temporary_hasted");
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
  self->is_spell_set(true);
  self->is_target_select_set(true);
  self->is_usable_set(true);
  self->on_use_do_set("me.on_use()");
  self->range_max_set(7);
  self->spell_base_name_set(name);
  self->spell_cost_set(2);
  self->text_a_or_an_set("a");
  self->text_description_long_set("The target of this spell will be able to zip around the dungeon with extraordinary speed.");
  self->text_description_short_set("Spell, hasted.");
  self->text_description_very_short_set("Hasted");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "spell_of_haste"});
  my::tile(self, {.tile = "spell_of_haste_activated"});
}

static void init(void)
{
  tp_init("spell_of_haste", "hasted", "hasted");
}

void module_init(void)
{
  native_register("spell_of_haste", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_spells_spell_of_haste
