//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/rock_lava.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_rock_lava {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles, const std::vector< std::string > &right1_tiles, const std::vector< std::string > &top1_tiles, const std::vector< std::string > &bot1_tiles, const std::vector< std::string > &tl1_tiles, const std::vector< std::string > &tr1_tiles, const std::vector< std::string > &bl1_tiles, const std::vector< std::string > &br1_tiles, const std::vector< std::string > &left2_tiles, const std::vector< std::string > &right2_tiles, const std::vector< std::string > &top2_tiles, const std::vector< std::string > &bot2_tiles, const std::vector< std::string > &tl2_tiles, const std::vector< std::string > &tr2_tiles, const std::vector< std::string > &bl2_tiles, const std::vector< std::string > &br2_tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles, const std::vector< std::string > &left1_tiles, const std::vector< std::string > &right1_tiles, const std::vector< std::string > &top1_tiles, const std::vector< std::string > &bot1_tiles, const std::vector< std::string > &tl1_tiles, const std::vector< std::string > &tr1_tiles, const std::vector< std::string > &bl1_tiles, const std::vector< std::string > &br1_tiles, const std::vector< std::string > &left2_tiles, const std::vector< std::string > &right2_tiles, const std::vector< std::string > &top2_tiles, const std::vector< std::string > &bot2_tiles, const std::vector< std::string > &tl2_tiles, const std::vector< std::string > &tr2_tiles, const std::vector< std::string > &bl2_tiles, const std::vector< std::string > &br2_tiles)
{
  Tpp self = my::tp_load(name, std::string("rock"));
  self->collision_hit_priority_set(1);
  self->gfx_ascii_bg_color_spread_hue_set(10);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("999");
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_lava_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_gas_blocker_set(true);
  self->is_hittable_set(true);
  self->is_light_blocker_set(true);
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
  self->is_rock_set(true);
  self->is_shootable_set(true);
  self->is_stone_set(true);
  self->is_very_hard_set(true);
  self->is_wall_set(true);
  self->noise_blocker_set(true);
  self->temperature_set(100);
  self->text_a_or_an_set("the");
  self->text_description_short_set("Melting rock.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "L", .ascii_bg_col_name = "gray20", .ascii_fg_col_name = "orange"});
  }
  {
    for (const auto &t : left1_tiles) {
      my::left1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : right1_tiles) {
      my::right1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : top1_tiles) {
      my::top1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : bot1_tiles) {
      my::bot1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : tl1_tiles) {
      my::tl1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : tr1_tiles) {
      my::tr1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : bl1_tiles) {
      my::bl1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : br1_tiles) {
      my::br1_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : left2_tiles) {
      my::left2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : right2_tiles) {
      my::right2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : top2_tiles) {
      my::top2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : bot2_tiles) {
      my::bot2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : tl2_tiles) {
      my::tl2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : tr2_tiles) {
      my::tr2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : bl2_tiles) {
      my::bl2_tile(self, {.tile = t});
    }
  }
  {
    for (const auto &t : br2_tiles) {
      my::br2_tile(self, {.tile = t});
    }
  }
}

static void init(void)
{
  tp_init("rock_lava1", std::vector< std::string >{
      "rock_lava1.1",
      "rock_lava1.2",
      "rock_lava1.3",
      "rock_lava1.4",
      "rock_lava1.5",
      "rock_lava1.6",
      "rock_lava1.7",
      "rock_lava1.8",
      "rock_lava1.9",
      "rock_lava1.10",
      "rock_lava1.11",
      "rock_lava1.12",
      "rock_lava1.13",
      "rock_lava1.14",
      "rock_lava1.15",
      "rock_lava1.16",
      "rock_lava1.17",
      "rock_lava1.18",
      "rock_lava1.19",
    }, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_rock_lava
