//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/pillar.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_pillar {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_floor_deco_set(true);
  self->is_interesting_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_jump_end_set(true);
  self->is_obs_jumping_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spawn_set(true);
  self->is_obs_spell_casting_set(true);
  self->is_obs_throwing_set(true);
  self->is_obs_wall_or_door_set(true);
  self->is_one_per_tile_set(true);
  self->is_pillar_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("An aged and moss-covered stone pillar.");
  self->thing_size_set(THING_SIZE_GIANT);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "|", .ascii_bg_col_name = "", .ascii_fg_col_name = "white"});
  }
}

static void init(void)
{
  tp_init("pillar", "stone pillar", std::vector< std::string >{
      "pillar.1",
      "pillar.2",
      "pillar.3",
      "pillar.4",
      "pillar.5",
      "pillar.6",
      "pillar.7",
      "pillar.8",
      "pillar.9",
      "pillar.10",
      "pillar.11",
      "pillar.12",
      "pillar.13",
      "pillar.14",
      "pillar.15",
      "pillar.16",
      "pillar.17",
      "pillar.18",
      "pillar.19",
      "pillar.20",
      "pillar.21",
      "pillar.22",
      "pillar.23",
      "pillar.24",
      "pillar.25",
      "pillar.26",
      "pillar.27",
      "pillar.28",
      "pillar.29",
      "pillar.30",
      "pillar.31",
      "pillar.32",
      "pillar.33",
      "pillar.34",
      "pillar.35",
      "pillar.36",
      "pillar.37",
      "pillar.38",
      "pillar.39",
      "pillar.40",
      "pillar.41",
      "pillar.42",
      "pillar.43",
      "pillar.44",
      "pillar.45",
      "pillar.46",
      "pillar.47",
      "pillar.48",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_pillar
