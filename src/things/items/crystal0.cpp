//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/crystal0.py
//

#include "my_native.hpp"
#include "things/items/crystal0.hpp"

namespace mod_things_items_crystal0 {

void tp_init(Tpp self)
{
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_flickers_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_magic_crystal_set(true);
  self->is_moveable_set(true);
  self->item_height_set(3);
  self->item_width_set(3);
  self->light_color_set("white");
  self->light_dist_set(1);
  self->noise_on_dropping_set(25);
  self->temperature_never_changes_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("magic crystal");
  self->text_apostrophize_set("magic crystal's");
  self->text_description_long3_set("Collecting all 7 crystals will unlock the final door that leads back to the surface world.");
  self->text_description_long4_set("Each crystal will bestow different ability bonuses. Collect them all for maximum power!");
  self->text_description_short_set("Magical crystal I.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
}

void module_init(void)
{
}

} // namespace mod_things_items_crystal0
