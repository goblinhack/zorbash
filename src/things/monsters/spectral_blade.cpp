//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/spectral_blade.py
//

#include "my_native.hpp"

namespace mod_things_monsters_spectral_blade {

static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  my::thing_msg(me, "The spectral blade vanishes!");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(100);
  self->ai_wanderer_set(true);
  self->attack_humanoid_set(true);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->distance_vision_set(8);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_nat_att_dice_set("1d4");
  self->dmg_nat_att_type_set("slash");
  self->dmg_num_of_attacks_set(1);
  self->dmg_rcv_doubled_from_fire_set(true);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_centered_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_shoot_at_close_range_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_buffable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_ethereal_set(true);
  self->is_fearless_set(true);
  self->is_floating_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_blinding_set(true);
  self->is_immune_to_confusion_set(true);
  self->is_immune_to_entrancement_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_paralysis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_vorpal_weapons_set(true);
  self->is_interesting_set(true);
  self->is_lifeless_set(true);
  self->is_loggable_set(true);
  self->is_magical_set(true);
  self->is_monst_class_B_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_not_shown_as_a_pet_set(true);
  self->is_shootable_set(true);
  self->is_tickable_set(true);
  self->is_vanquished_on_negation_set(true);
  self->light_color_set("white");
  self->light_dist_set(1);
  self->move_speed_set(200);
  self->noise_decibels_hearing_set(0);
  self->noise_on_moving_set(0);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->rarity_set(THING_RARITY_UNIQUE);
  self->stat_con_set(10);
  self->stat_def_set(10);
  self->stat_dex_set(10);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(10);
  self->temperature_max_set(50);
  self->temperature_min_set((-50));
  self->temperature_set(0);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("spectral blades");
  self->text_apostrophize_set("spectral blade's");
  self->text_description_long_set("A phantom blade that just wants to play.");
  self->text_description_short_set("A spectral blde.");
  self->text_hits_set("slash");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 25;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "/", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "|", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "\\", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "-", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "/", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "|", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "\\", .ascii_fg_col_name = "white", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "-", .ascii_fg_col_name = "white", .delay_ms = delay});
}

static void init(void)
{
  tp_init("spectral_blade", "spectral blade", "spectral blade");
}

void module_init(void)
{
  native_register("spectral_blade", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_spectral_blade
