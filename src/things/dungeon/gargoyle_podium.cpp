//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/gargoyle_podium.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_gargoyle_podium {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_fall_set(true);
  self->is_one_per_tile_set(true);
  self->text_a_or_an_set("an");
  self->text_description_short_set("An empty podium. With claw marks.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "_", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray"});
  }
}

static void init(void)
{
  tp_init("gargoyle_podium", "empty podium", std::vector< std::string >{"gargoyle.podium"});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_gargoyle_podium
