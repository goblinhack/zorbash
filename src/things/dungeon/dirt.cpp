//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/dirt.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_dirt {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles, const std::vector< std::string > &bot3_tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles, const std::vector< std::string > &bot3_tiles)
{
  Tpp self = my::tp_load(name, std::string("some dirt"), std::string("some dirt"));
  self->gfx_ascii_fg_color_spread_blue_set(20);
  self->gfx_ascii_fg_color_spread_green_set(20);
  self->gfx_ascii_fg_color_spread_red_set(20);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->is_able_to_dampen_footsteps_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_dirt_set(true);
  self->is_flat_set(true);
  self->is_one_per_tile_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Some exciting dirt");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "middle_dot", .ascii_fg_col_name = "saddlebrown"});
  }
  {
    for (const auto &t : bot3_tiles) {
      my::bot3_tile(self, {.tile = t});
    }
  }
}

static void init(void)
{
  tp_init("dirt1", std::vector< std::string >{
      "dirt1.1",
      "dirt1.2",
      "dirt1.3",
      "dirt1.4",
      "dirt1.5",
      "dirt1.6",
      "dirt1.7",
      "dirt1.8",
      "dirt1.9",
      "dirt1.10",
      "dirt1.11",
      "dirt1.12",
      "dirt1.13",
      "dirt1.14",
      "dirt1.15",
      "dirt1.16",
      "dirt1.17",
      "dirt1.18",
      "dirt1.19",
    }, {}, std::vector< std::string >{
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
  tp_init("dirt2", std::vector< std::string >{
      "dirt2.1",
      "dirt2.2",
      "dirt2.3",
      "dirt2.4",
      "dirt2.5",
      "dirt2.6",
      "dirt2.7",
      "dirt2.8",
      "dirt2.9",
      "dirt2.10",
      "dirt2.11",
      "dirt2.12",
      "dirt2.13",
      "dirt2.14",
      "dirt2.15",
      "dirt2.16",
      "dirt2.17",
      "dirt2.18",
      "dirt2.19",
    }, {}, std::vector< std::string >{
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
  tp_init("dirt3", std::vector< std::string >{
      "dirt3.1",
      "dirt3.2",
      "dirt3.3",
      "dirt3.4",
      "dirt3.5",
      "dirt3.6",
      "dirt3.7",
      "dirt3.8",
      "dirt3.9",
      "dirt3.10",
      "dirt3.11",
      "dirt3.12",
      "dirt3.13",
      "dirt3.14",
      "dirt3.15",
      "dirt3.16",
      "dirt3.17",
      "dirt3.18",
      "dirt3.19",
    }, {}, std::vector< std::string >{
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

} // namespace mod_things_dungeon_dirt
