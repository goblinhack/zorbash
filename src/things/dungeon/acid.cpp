//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/acid.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_acid {

static void acid_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name, const std::vector< std::string > &tiles, const std::vector< std::string > &left_tiles);
static void init(void);

static void acid_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name, const std::vector< std::string > &tiles, const std::vector< std::string > &left_tiles)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->dmg_acid_dice_set("1d3+1");
  self->dmg_chance_d1000_acid_set(0, 1000);
  self->dmg_nat_att_type_set("burn");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->is_able_to_fall_set(true);
  self->is_acid_set(true);
  self->is_eater_of_meat_set(true);
  self->is_hazard_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_obs_ai_set(true);
  self->is_one_per_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d20+20");
  self->light_color_set("green");
  self->light_dist_set(2);
  self->text_a_or_an_set("");
  self->text_description_short_set("A pool of hissing acid.");
  self->text_hits_set("burns");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "middle_dot", .ascii_bg_col_name = "", .ascii_fg_col_name = "green"});
  }
}

static void init(void)
{
  acid_init("acid1", "hissing acid", "acid", std::vector< std::string >{
      "acid1.1",
      "acid1.2",
      "acid1.3",
      "acid1.4",
      "acid1.5",
      "acid1.6",
      "acid1.7",
      "acid1.8",
      "acid1.9",
      "acid1.10",
      "acid1.11",
      "acid1.12",
      "acid1.13",
      "acid1.14",
      "acid1.15",
      "acid1.16",
      "acid1.17",
      "acid1.18",
      "acid1.19",
    }, {});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_acid
