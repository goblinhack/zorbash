//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/floor_ice.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_floor_ice {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &bot3_tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &bot3_tiles)
{
  Tpp self = my::tp_load(name, std::string("dirty floor"), std::string("dirty floor"));
  self->gfx_ascii_fg_color_spread_blue_set(20);
  self->gfx_ascii_fg_color_spread_green_set(20);
  self->gfx_ascii_fg_color_spread_red_set(20);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_floor_set(true);
  self->is_one_per_tile_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("The icy dungeon floor.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "black", .ascii_fg_col_name = "white"});
  }
  {
    for (const auto &t : bot3_tiles) {
      my::bot3_tile(self, {.tile = t});
    }
  }
}

static void init(void)
{
  tp_init("floor_ice1", std::vector< std::string >{
      "floor_ice1.1",
      "floor_ice1.2",
      "floor_ice1.3",
      "floor_ice1.4",
      "floor_ice1.5",
      "floor_ice1.6",
      "floor_ice1.7",
      "floor_ice1.8",
      "floor_ice1.9",
      "floor_ice1.10",
      "floor_ice1.11",
      "floor_ice1.12",
      "floor_ice1.13",
      "floor_ice1.14",
      "floor_ice1.15",
      "floor_ice1.16",
      "floor_ice1.17",
      "floor_ice1.18",
      "floor_ice1.19",
      "floor_ice1.20",
      "floor_ice1.21",
      "floor_ice1.22",
      "floor_ice1.23",
      "floor_ice1.24",
      "floor_ice1.25",
      "floor_ice1.26",
      "floor_ice1.27",
      "floor_ice1.28",
      "floor_ice1.29",
      "floor_ice1.30",
      "floor_ice1.31",
      "floor_ice1.32",
      "floor_ice1.33",
      "floor_ice1.34",
      "floor_ice1.35",
      "floor_ice1.36",
      "floor_ice1.37",
      "floor_ice1.38",
    }, std::vector< std::string >{
      "chasm1.1",
      "chasm1.2",
      "chasm1.3",
      "chasm1.4",
      "chasm1.5",
      "chasm1.6",
      "chasm1.7",
      "chasm1.8",
      "chasm1.9",
      "chasm1.10",
      "chasm1.11",
      "chasm1.12",
      "chasm1.13",
      "chasm1.14",
      "chasm1.15",
      "chasm1.16",
      "chasm1.17",
      "chasm1.18",
      "chasm1.19",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_floor_ice
