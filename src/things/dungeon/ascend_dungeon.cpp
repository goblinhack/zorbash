//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/ascend_dungeon.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_ascend_dungeon {

static std::vector< std::string > on_get_text_description_long(uint32_t owner, uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static std::vector< std::string > on_get_text_description_long(uint32_t owner, uint32_t me, int x, int y)
{
  if ((my::thing_level_get(me) == 1)) {
    return std::vector< std::string >{"This imposing doorway leads back to freedom from the terrible dungeon you find yourself in.", "Why are you here\? Good question. Something involving a bet, copious amounts of liquid, seven ferrets and an ungodly desire to rid the world of a terrible evil of some kind.", "The door will likely remain barred until you return here with the Orb of Zorb..."};
  } else {
    return std::vector< std::string >{"This imposing doorway leads up to the previous level."};
  }
  return {};
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_show_light_once_seen_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_show_square_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_ascend_dungeon_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_critical_to_level_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_one_per_tile_set(true);
  self->light_color_set("yellow");
  self->light_dist_set(3);
  self->normal_placement_rules_set(true);
  self->on_get_text_description_long_do_set("me.on_get_text_description_long()");
  self->text_a_or_an_set("the");
  self->text_description_short_set("%%fg=gold$The way up.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  delay = 1000;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "gold", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".1.open"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_open = true});
  my::tile(self, {.tile = (name + ".2.open"), .ascii_fg_char = "omega", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .is_open = true});
}

static void init(void)
{
  tp_init("ascend_dungeon", "dungeon entrance", "entrance");
}

void module_init(void)
{
  native_register("ascend_dungeon", "on_get_text_description_long", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {0, on_get_text_description_long((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3])}; });
  init();
}

} // namespace mod_things_dungeon_ascend_dungeon
