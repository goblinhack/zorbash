//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/containers/bag_small.py
//

#include "my_native.hpp"

namespace mod_things_containers_bag_small {

static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->capacity_height_set(10);
  self->capacity_width_set(10);
  self->chance_d10000_set_on_fire_set(2000);
  self->chance_d1000_carrier_of_treasure_class_A_set(1000);
  self->chance_d1000_carrier_of_treasure_class_B_set(200);
  self->chance_d1000_carrier_of_treasure_class_C_set(50);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->health_initial_dice_set("20");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_container_set(true);
  self->is_bag_item_not_stackable_set(true);
  self->is_bag_item_set(true);
  self->is_bag_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_interesting_set(true);
  self->is_item_carrier_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_organic_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_A_set(true);
  self->is_treasure_set(true);
  self->item_height_set(3);
  self->item_width_set(3);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->on_death_drop_all_items_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("small bag");
  self->text_apostrophize_set("small bag's");
  self->text_description_long_set("A small leathery brown bag.");
  self->text_description_short_set("A small brown bag.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "bag_small", .ascii_fg_char = "down_triangle", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = 1000});
}

static void init(void)
{
  tp_init("bag_small", "small bag");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_containers_bag_small
