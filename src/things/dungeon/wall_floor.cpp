//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/wall_floor.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_wall_floor {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles, const std::vector< std::string > &bot3_tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles, const std::vector< std::string > &bot3_tiles)
{
  Tpp self = my::tp_load(name, std::string("dungeon wall"), std::string("dungeon wall"));
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(false);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_floor_set(true);
  self->is_one_per_tile_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("The unwashed dungeon foundation.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t});
  }
  {
    for (const auto &t : bot3_tiles) {
      my::bot3_tile(self, {.tile = t, .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "white"});
    }
  }
}

static void init(void)
{
  tp_init("wall_floor1", std::vector< std::string >{
      "floor1.1",
      "floor1.2",
      "floor1.3",
      "floor1.4",
      "floor1.5",
      "floor1.6",
      "floor1.7",
      "floor1.8",
      "floor1.9",
      "floor1.10",
      "floor1.11",
      "floor1.12",
      "floor1.13",
      "floor1.14",
      "floor1.15",
      "floor1.16",
      "floor1.17",
      "floor1.18",
      "floor1.19",
    }, {}, std::vector< std::string >{
      "chasm2.1",
      "chasm2.2",
      "chasm2.3",
      "chasm2.4",
      "chasm2.5",
      "chasm2.6",
      "chasm2.7",
      "chasm2.8",
      "chasm2.9",
      "chasm2.10",
      "chasm2.11",
      "chasm2.12",
      "chasm2.13",
      "chasm2.14",
      "chasm2.15",
      "chasm2.16",
      "chasm2.17",
      "chasm2.18",
      "chasm2.19",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_wall_floor
