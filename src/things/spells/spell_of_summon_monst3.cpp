//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_summon_monst3.py
//

#include "my_native.hpp"

namespace mod_things_spells_spell_of_summon_monst3 {

static void on_targeted(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_targeted(uint32_t me, int x, int y)
{
  my::place_at(me, "random_monst_class_C", x, y);
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
  self->on_targeted_do_set("me.on_targeted()");
  self->range_max_set(7);
  self->spell_base_name_set(name);
  self->spell_cost_set(6);
  self->spell_replaces_set("spell_of_summon_monst2");
  self->text_a_or_an_set("a");
  self->text_description_long_set("Summon a very challenging monster, class C.");
  self->text_description_short_set("Spell, summon monst III.");
  self->text_description_very_short_set("SumMonstA");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "spell_of_summon_monst3"});
  my::tile(self, {.tile = "spell_of_summon_monst3_activated"});
}

static void init(void)
{
  tp_init("spell_of_summon_monst3", "summon monst III", "summon monst III");
}

void module_init(void)
{
  native_register("spell_of_summon_monst3", "on_targeted", 3, [](const int64_t *a) -> NativeRet { (void) a; on_targeted((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_spells_spell_of_summon_monst3
