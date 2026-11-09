//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/fire.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_fire {

static void spawn(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void spawn(uint32_t me, int x, int y)
{
  my::spawn_set_fire_to_things_around_me(me, "small_fire");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->collision_check_set(true);
  self->dmg_chance_d1000_fire_set(0, 1000);
  self->dmg_fire_dice_set("1d20+6");
  self->dmg_nat_att_type_set("fire");
  self->environ_dislikes_water_set(100);
  self->gfx_ascii_shown_set(true);
  self->gfx_on_fire_anim_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_flickers_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->health_initial_dice_set("10");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_dead_on_falling_set(true);
  self->is_fire_set(true);
  self->is_hazard_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_one_per_tile_set(false);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d20+20");
  self->light_color_set("orange");
  self->light_dist_set(4);
  self->on_idle_tick_freq_dice_set("1d10+10:me.spawn()");
  self->temperature_min_set(0);
  self->temperature_set(100);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("");
  self->text_description_short_set("Fire.");
  self->text_hits_set("burns");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_FIRE);
  delay = 75;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkred", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkred", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkred", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".9"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".10"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkred", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".11"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkred", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".12"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".13"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkred", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".14"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".15"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".16"), .ascii_fg_char = "inverted_v", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
}

static void init(void)
{
  tp_init("fire", "fire");
}

void module_init(void)
{
  native_register("fire", "spawn", 3, [](const int64_t *a) -> NativeRet { (void) a; spawn((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_fire
