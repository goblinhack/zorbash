//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/fungus/fungus_healing.py
//

#include "my_native.hpp"

namespace mod_things_fungus_fungus_healing {

static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_gas_healing_around_thing(me, 1);
}

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("divine fungus"), std::string("divine fungus"));
  self->collision_check_set(true);
  self->collision_hit_priority_set(3);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_long_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_shadow_solid_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->health_initial_dice_set("1");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_combustible_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(false);
  self->is_described_when_hovering_over_set(true);
  self->is_fungus_healing_set(true);
  self->is_fungus_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_light_blocker_for_monst_set(true);
  self->is_one_per_tile_set(true);
  self->is_organic_set(true);
  self->is_shootable_set(true);
  self->light_color_set("pink");
  self->light_dist_set(1);
  self->on_death_do_set("me.on_death()");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_description_long_set("This beautiful glowing fungus is well known for its healing properties and will release a gas of helpful spores upon its death.");
  self->text_description_short_set("A divine fungus.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "\"", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink"});
  }
}

static void init(void)
{
  tp_init("fungus_healing", std::vector< std::string >{"fungus_healing"});
}

void module_init(void)
{
  native_register("fungus_healing", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_fungus_fungus_healing
