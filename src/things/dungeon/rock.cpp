//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/rock.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_rock {

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
  self->health_initial_dice_set("1d30+60");
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
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
  self->text_a_or_an_set("the");
  self->text_description_short_set("Rocky the rock.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "#", .ascii_bg_col_name = "burlywood", .ascii_fg_col_name = "black"});
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
  tp_init("rock1", std::vector< std::string >{
      "rock1.1",
      "rock1.2",
      "rock1.3",
      "rock1.4",
      "rock1.5",
      "rock1.6",
      "rock1.7",
      "rock1.8",
      "rock1.9",
      "rock1.10",
      "rock1.11",
      "rock1.12",
      "rock1.13",
      "rock1.14",
      "rock1.15",
      "rock1.16",
      "rock1.17",
      "rock1.18",
      "rock1.19",
    }, std::vector< std::string >{
      "wall_deco1.left.1",
      "wall_deco2.left.1",
      "wall_deco1.left.2",
      "wall_deco2.left.2",
      "wall_deco1.left.3",
      "wall_deco2.left.3",
      "wall_deco1.left.4",
      "wall_deco2.left.4",
      "wall_deco1.left.5",
      "wall_deco2.left.5",
      "wall_deco1.left.6",
      "wall_deco2.left.6",
    }, std::vector< std::string >{
      "wall_deco1.right.1",
      "wall_deco2.right.1",
      "wall_deco1.right.2",
      "wall_deco2.right.2",
      "wall_deco1.right.3",
      "wall_deco2.right.3",
      "wall_deco1.right.4",
      "wall_deco2.right.4",
      "wall_deco1.right.5",
      "wall_deco2.right.5",
      "wall_deco1.right.6",
      "wall_deco2.right.6",
    }, std::vector< std::string >{
      "wall_deco1.top.1",
      "wall_deco2.top.1",
      "wall_deco1.top.2",
      "wall_deco2.top.2",
      "wall_deco1.top.3",
      "wall_deco2.top.3",
      "wall_deco1.top.4",
      "wall_deco2.top.4",
      "wall_deco1.top.5",
      "wall_deco2.top.5",
      "wall_deco1.top.6",
      "wall_deco2.top.6",
      "wall_deco1.top.7",
      "wall_deco2.top.7",
    }, std::vector< std::string >{
      "wall_deco1.bot.1",
      "wall_deco2.bot.1",
      "wall_deco1.bot.2",
      "wall_deco2.bot.2",
      "wall_deco1.bot.3",
      "wall_deco2.bot.3",
      "wall_deco1.bot.4",
      "wall_deco2.bot.4",
      "wall_deco1.bot.5",
      "wall_deco2.bot.5",
      "wall_deco1.bot.6",
      "wall_deco2.bot.6",
      "wall_deco1.bot.7",
      "wall_deco2.bot.7",
    }, std::vector< std::string >{
      "wall_deco1.tl.1",
      "wall_deco2.tl.1",
      "wall_deco1.tl.2",
      "wall_deco2.tl.2",
      "wall_deco1.tl.3",
      "wall_deco2.tl.3",
      "wall_deco1.tl.4",
      "wall_deco2.tl.4",
      "wall_deco1.tl.5",
      "wall_deco2.tl.5",
      "wall_deco1.tl.6",
      "wall_deco2.tl.6",
    }, std::vector< std::string >{
      "wall_deco1.tr.1",
      "wall_deco2.tr.1",
      "wall_deco1.tr.2",
      "wall_deco2.tr.2",
      "wall_deco1.tr.3",
      "wall_deco2.tr.3",
      "wall_deco1.tr.4",
      "wall_deco2.tr.4",
      "wall_deco1.tr.5",
      "wall_deco2.tr.5",
      "wall_deco1.tr.6",
      "wall_deco2.tr.6",
    }, std::vector< std::string >{
      "wall_deco1.bl.1",
      "wall_deco2.bl.1",
      "wall_deco1.bl.2",
      "wall_deco2.bl.2",
      "wall_deco1.bl.3",
      "wall_deco2.bl.3",
      "wall_deco1.bl.4",
      "wall_deco2.bl.4",
      "wall_deco1.bl.5",
      "wall_deco2.bl.5",
      "wall_deco1.bl.6",
      "wall_deco2.bl.6",
    }, std::vector< std::string >{
      "wall_deco1.br.1",
      "wall_deco2.br.1",
      "wall_deco1.br.2",
      "wall_deco2.br.2",
      "wall_deco1.br.3",
      "wall_deco2.br.3",
      "wall_deco1.br.4",
      "wall_deco2.br.4",
      "wall_deco1.br.5",
      "wall_deco2.br.5",
      "wall_deco1.br.6",
      "wall_deco2.br.6",
    }, std::vector< std::string >{
      "wall_shadow_deco1.left.1",
      "wall_shadow_deco2.left.1",
      "wall_shadow_deco1.left.2",
      "wall_shadow_deco2.left.2",
      "wall_shadow_deco1.left.3",
      "wall_shadow_deco2.left.3",
      "wall_shadow_deco1.left.4",
      "wall_shadow_deco2.left.4",
      "wall_shadow_deco1.left.5",
      "wall_shadow_deco2.left.5",
      "wall_shadow_deco1.left.6",
      "wall_shadow_deco2.left.6",
    }, std::vector< std::string >{
      "wall_shadow_deco1.right.1",
      "wall_shadow_deco2.right.1",
      "wall_shadow_deco1.right.2",
      "wall_shadow_deco2.right.2",
      "wall_shadow_deco1.right.3",
      "wall_shadow_deco2.right.3",
      "wall_shadow_deco1.right.4",
      "wall_shadow_deco2.right.4",
      "wall_shadow_deco1.right.5",
      "wall_shadow_deco2.right.5",
      "wall_shadow_deco1.right.6",
      "wall_shadow_deco2.right.6",
    }, std::vector< std::string >{
      "wall_shadow_deco1.top.1",
      "wall_shadow_deco2.top.1",
      "wall_shadow_deco1.top.2",
      "wall_shadow_deco2.top.2",
      "wall_shadow_deco1.top.3",
      "wall_shadow_deco2.top.3",
      "wall_shadow_deco1.top.4",
      "wall_shadow_deco2.top.4",
      "wall_shadow_deco1.top.5",
      "wall_shadow_deco2.top.5",
      "wall_shadow_deco1.top.6",
      "wall_shadow_deco2.top.6",
      "wall_shadow_deco1.top.7",
      "wall_shadow_deco2.top.7",
    }, std::vector< std::string >{
      "wall_shadow_deco1.bot.1",
      "wall_shadow_deco2.bot.1",
      "wall_shadow_deco1.bot.2",
      "wall_shadow_deco2.bot.2",
      "wall_shadow_deco1.bot.3",
      "wall_shadow_deco2.bot.3",
      "wall_shadow_deco1.bot.4",
      "wall_shadow_deco2.bot.4",
      "wall_shadow_deco1.bot.5",
      "wall_shadow_deco2.bot.5",
      "wall_shadow_deco1.bot.6",
      "wall_shadow_deco2.bot.6",
      "wall_shadow_deco1.bot.7",
      "wall_shadow_deco2.bot.7",
    }, std::vector< std::string >{
      "wall_shadow_deco1.tl.1",
      "wall_shadow_deco2.tl.1",
      "wall_shadow_deco1.tl.2",
      "wall_shadow_deco2.tl.2",
      "wall_shadow_deco1.tl.3",
      "wall_shadow_deco2.tl.3",
      "wall_shadow_deco1.tl.4",
      "wall_shadow_deco2.tl.4",
      "wall_shadow_deco1.tl.5",
      "wall_shadow_deco2.tl.5",
      "wall_shadow_deco1.tl.6",
      "wall_shadow_deco2.tl.6",
    }, std::vector< std::string >{
      "wall_shadow_deco1.tr.1",
      "wall_shadow_deco2.tr.1",
      "wall_shadow_deco1.tr.2",
      "wall_shadow_deco2.tr.2",
      "wall_shadow_deco1.tr.3",
      "wall_shadow_deco2.tr.3",
      "wall_shadow_deco1.tr.4",
      "wall_shadow_deco2.tr.4",
      "wall_shadow_deco1.tr.5",
      "wall_shadow_deco2.tr.5",
      "wall_shadow_deco1.tr.6",
      "wall_shadow_deco2.tr.6",
    }, std::vector< std::string >{
      "wall_shadow_deco1.bl.1",
      "wall_shadow_deco2.bl.1",
      "wall_shadow_deco1.bl.2",
      "wall_shadow_deco2.bl.2",
      "wall_shadow_deco1.bl.3",
      "wall_shadow_deco2.bl.3",
      "wall_shadow_deco1.bl.4",
      "wall_shadow_deco2.bl.4",
      "wall_shadow_deco1.bl.5",
      "wall_shadow_deco2.bl.5",
      "wall_shadow_deco1.bl.6",
      "wall_shadow_deco2.bl.6",
    }, std::vector< std::string >{
      "wall_shadow_deco1.br.1",
      "wall_shadow_deco2.br.1",
      "wall_shadow_deco1.br.2",
      "wall_shadow_deco2.br.2",
      "wall_shadow_deco1.br.3",
      "wall_shadow_deco2.br.3",
      "wall_shadow_deco1.br.4",
      "wall_shadow_deco2.br.4",
      "wall_shadow_deco1.br.5",
      "wall_shadow_deco2.br.5",
      "wall_shadow_deco1.br.6",
      "wall_shadow_deco2.br.6",
    });
}

void module_init(void)
{
  init();
}

} // namespace mod_things_dungeon_rock
