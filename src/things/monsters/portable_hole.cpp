//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/portable_hole.py
//

#include "my_native.hpp"

namespace mod_things_monsters_portable_hole {

static void on_pre_teleport(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_pre_teleport(uint32_t me, int x, int y)
{
  if (my::thing_is_dead_or_dying(me)) {
    return;
  }
  my::thing_dead(me, "by a dimensional rift");
  my::thing_msg(me, "The portable hole explodes violently!");
  my::spawn_at_my_position(me, "explosion_major");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(100);
  self->ai_wanderer_set(true);
  self->attack_humanoid_set(true);
  self->chance_d1000_tameable_set(0);
  self->chance_d1000_teleport_attack_set(1000);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_vision_set(8);
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_type_set("touches");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_health_bar_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_teleport_attack_set(true);
  self->is_able_to_walk_through_walls_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_buffable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_ethereal_set(true);
  self->is_immune_to_acid_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_fire_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_vorpal_weapons_set(true);
  self->is_interesting_set(true);
  self->is_lifeless_set(true);
  self->is_loggable_set(true);
  self->is_magical_set(true);
  self->is_monst_class_B_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_tickable_set(true);
  self->is_vanquished_on_negation_set(true);
  self->light_color_set("purple");
  self->light_dist_set(1);
  self->move_speed_set(50);
  self->noise_decibels_hearing_set(5);
  self->noise_on_moving_set(1);
  self->normal_placement_rules_set(true);
  self->on_pre_teleport_do_set("me.on_pre_teleport()");
  self->rarity_set(THING_RARITY_UNCOMMON);
  self->stat_con_set(10);
  self->stat_def_set(10);
  self->stat_dex_set(10);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(10);
  self->teleport_distance_set(20);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("portable holes");
  self->text_apostrophize_set("portable hole's");
  self->text_description_long2_set("Originally used to get rid of detritus from the dungeon floor, they also work well for getting rid of annoying dungeoneers.");
  self->text_description_long_set("Portable holes are a one way ticket to other parts of the dungeon, which may or may not be a good thing.");
  self->text_description_short_set("A portable hole.");
  self->text_hits_set("burns");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_CONSUMER);
  delay = 200;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "O", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "o", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = ".", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "o", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = delay});
}

static void init(void)
{
  tp_init("portable_hole", "portable hole", "portable hole");
}

void module_init(void)
{
  native_register("portable_hole", "on_pre_teleport", 3, [](const int64_t *a) -> NativeRet { (void) a; on_pre_teleport((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_portable_hole
