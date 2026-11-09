//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/spiderweb.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_spiderweb {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("spiderweb"));
  self->collision_check_set(true);
  self->collision_hit_priority_set(3);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_centered_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1d20");
  self->is_able_to_fall_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_combustible_set(true);
  self->is_crushable_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_hazard_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_cold_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->is_spiderweb_set(true);
  self->is_sticky_set(true);
  self->normal_placement_rules_set(true);
  self->text_a_or_an_set("a");
  self->text_description_long2_set("Best to try and jump over such obstacles.");
  self->text_description_long_set("Free real estate. All welcome, says a small sign next to this web.");
  self->text_description_short_set("Thick and sticky spiderweb.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_WEB);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "cross", .ascii_fg_col_name = "white"});
  }
}

static void init(void)
{
  tp_init("spiderweb", std::vector< std::string >{"spiderweb.1", "spiderweb.2", "spiderweb.3", "spiderweb.4", "spiderweb.5", "spiderweb.6"});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_spiderweb
