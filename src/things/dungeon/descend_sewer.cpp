//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/descend_sewer.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_descend_sewer {

static void spawn(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles);
static void init(void);

static void spawn(uint32_t me, int x, int y)
{
  my::spawn_next_to(me, "slime_baby");
}

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles)
{
  int delay = 0;
  Tpp self = my::tp_load(name, std::string("sewer pipe"), std::string("sewer"));
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_biome_dungeon_set(true);
  self->is_descend_sewer_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->is_tickable_set(true);
  self->light_color_set("lime");
  self->light_dist_set(1);
  self->minion_limit_set(5);
  self->on_idle_tick_freq_dice_set("1d50+50:descend_sewer.spawn()");
  self->text_a_or_an_set("a");
  self->text_description_long_set("A filthy sewer pipe. Watch out, they can spawn surprises. Don't fall in!");
  self->text_description_short_set("A slime coated sewer pipe.");
  self->tick_prio_set(MAP_TICK_PRIO_LOW);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 150;
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = ">", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  }
}

static void init(void)
{
  tp_init("descend_sewer1", std::vector< std::string >{
      "descend_sewer1.1",
      "descend_sewer1.2",
      "descend_sewer1.3",
      "descend_sewer1.4",
      "descend_sewer1.5",
      "descend_sewer1.6",
      "descend_sewer1.7",
      "descend_sewer1.8",
      "descend_sewer1.9",
      "descend_sewer1.10",
    }, {});
}

void module_init(void)
{
  native_register("descend_sewer", "spawn", 3, [](const int64_t *a) -> NativeRet { (void) a; spawn((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_dungeon_descend_sewer
