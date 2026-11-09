//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_repulsion.py
//

#include "my_native.hpp"

namespace mod_things_spells_spell_of_repulsion {

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  for (auto it : my::level_get_all(item, x, y)) {
    if (my::thing_is_moveable(it)) {
      my::thing_repulse(owner, it);
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
  self->is_spell_of_repulsion_set(true);
  self->is_spell_set(true);
  self->is_target_select_set(true);
  self->is_usable_set(true);
  self->on_use_do_set("me.on_use()");
  self->range_max_set(9);
  self->spell_base_name_set(name);
  self->spell_cost_set(2);
  self->text_a_or_an_set("a");
  self->text_description_long2_set("It would be a shame if there was a chasm in the way.");
  self->text_description_long_set("Repulse people even more than usual with this repellent spell");
  self->text_description_short_set("Spell, repulsion.");
  self->text_description_very_short_set("Beckon");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "spell_of_repulsion"});
  my::tile(self, {.tile = "spell_of_repulsion_activated"});
}

static void init(void)
{
  tp_init("spell_of_repulsion", "repulsion", "repulsion");
}

void module_init(void)
{
  native_register("spell_of_repulsion", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_spells_spell_of_repulsion
