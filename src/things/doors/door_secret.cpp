//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/doors/door_secret.py
//

#include "my_native.hpp"

namespace mod_things_doors_door_secret {

static void on_death(uint32_t me, int x, int y);
static void on_open(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "door_stone");
}

static void on_open(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "door_stone");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_gas_blocker_set(true);
  self->is_interesting_set(true);
  self->is_light_blocker_set(true);
  self->is_loggable_set(true);
  self->is_obs_jumping_set(true);
  self->is_openable_set(true);
  self->is_secret_door_set(true);
  self->noise_blocker_set(true);
  self->noise_on_hit_and_now_dead_set(10);
  self->noise_on_hit_and_still_alive_set(10);
  self->noise_on_open_or_close_set(10);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_death_is_open_set(true);
  self->on_open_do_set("me.on_open()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("uneven dungeon walls");
  self->text_apostrophize_set("uneven dungeon wall's");
  self->text_description_short_set("A strange looking wall.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".9"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".10"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".11"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".12"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".13"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".14"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".15"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
  my::tile(self, {.tile = (name + ".16"), .ascii_fg_char = "#", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "white"});
}

static void init(void)
{
  tp_init("door_secret", "uneven dungeon wall", "dungeon wall");
}

void module_init(void)
{
  native_register("door_secret", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("door_secret", "on_open", 3, [](const int64_t *a) -> NativeRet { (void) a; on_open((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_doors_door_secret
