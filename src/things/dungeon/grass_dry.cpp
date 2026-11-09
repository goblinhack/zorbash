//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/grass_dry.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_grass_dry {

static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  if (my::thing_is_fire(hitter)) {
    my::spawn_at_my_position(me, "small_fire");
    my::thing_msg(me, "The dry grass burns!");
  }
  my::place_at(me, "grass_dry_dead", x, y);
}

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("dry grass"));
  self->collision_hit_priority_set(1);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_shadow_very_short_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_amplify_footsteps_set(true);
  self->is_able_to_fall_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_combustible_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_grass_dry_set(true);
  self->is_grass_set(true);
  self->is_interesting_set(true);
  self->is_one_per_tile_set(true);
  self->nutrition_dice_set("1d4");
  self->on_hit_and_now_dead_do_set("grass_dry.on_hit_and_now_dead()");
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Parched grass.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "three_dots", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkolivegreen2", .delay_ms = 300});
  }
}

static void init(void)
{
  tp_init("grass_dry", std::vector< std::string >{
      "grass_dry.1",
      "grass_dry.2",
      "grass_dry.3",
      "grass_dry.4",
      "grass_dry.5",
      "grass_dry.6",
      "grass_dry.7",
      "grass_dry.8",
      "grass_dry.9",
      "grass_dry.10",
      "grass_dry.11",
      "grass_dry.12",
      "grass_dry.13",
      "grass_dry.14",
      "grass_dry.15",
      "grass_dry.16",
      "grass_dry.17",
      "grass_dry.18",
    });
}

void module_init(void)
{
  native_register("grass_dry", "on_hit_and_now_dead", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_now_dead((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_grass_dry
