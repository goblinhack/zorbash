//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/fungus/fungus_common_withered.py
//

#include "my_native.hpp"
#include "things/fungus/fungus_common_withered.hpp"

namespace mod_things_fungus_fungus_common_withered {

void tp_init(Tpp self)
{
  self->collision_check_set(true);
  self->collision_hit_priority_set(3);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_bag_item_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_combustible_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(false);
  self->is_described_when_hovering_over_set(true);
  self->is_fungus_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_light_blocker_for_monst_set(true);
  self->is_one_per_tile_set(true);
  self->is_organic_set(true);
  self->is_shootable_set(true);
  self->is_throwable_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_description_long2_set("Some withered fungus that looks dry enough to burst into flames at the smallest spark.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
}

void module_init(void)
{
}

} // namespace mod_things_fungus_fungus_common_withered
