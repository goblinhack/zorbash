//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/bones.py
//

#include "my_native.hpp"

namespace mod_things_items_bones {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  Tpp self = my::tp_load(name, std::string("bones and skin and stuff"));
  self->chance_d1000_appearing_set(100);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_able_to_fall_set(true);
  self->is_bones_set(true);
  self->is_loggable_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->normal_placement_rules_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("Some poor creature's remnants.");
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = ",", .ascii_bg_col_name = "", .ascii_fg_col_name = "white"});
}

static void init(void)
{
  tp_init("bones.1");
  tp_init("bones.2");
  tp_init("bones.3");
  tp_init("bones.4");
  tp_init("bones.5");
  tp_init("bones.6");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_items_bones
