//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/kraken_tentacle.py
//

#include "my_native.hpp"

namespace mod_things_monsters_kraken_tentacle {

static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->ai_resent_count_set(100);
  self->ai_wanderer_set(true);
  self->attack_eater_set(true);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->chance_d1000_grapple_set(200);
  self->chance_d1000_tameable_set(0);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->consume_per_bite_amount_set(1);
  self->distance_minion_from_mob_max_set(3);
  self->distance_minion_vision_shared_set(true);
  self->distance_vision_set(3);
  self->dmg_chance_d1000_nat_att_set(0, 900);
  self->dmg_chance_d1000_poison_set(0, 500);
  self->dmg_nat_att_dice_set("1d3+1");
  self->dmg_nat_att_type_set("lash");
  self->dmg_poison_dice_set("1d8+1");
  self->environ_likes_deep_water_set(true);
  self->environ_likes_shallow_water_set(true);
  self->gfx_anim_use_set("attack_green");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("1d10");
  self->hunger_clock_tick_freq_set(50);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_always_submerged_in_water_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_meat_set(true);
  self->is_green_blooded_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_water_set(true);
  self->is_interesting_set(true);
  self->is_limb_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_minion_set(true);
  self->is_monst_class_A_set(true);
  self->is_monst_set(true);
  self->is_moveable_set(true);
  self->is_shootable_set(true);
  self->is_soft_set(true);
  self->is_tentacle_set(true);
  self->is_tickable_set(true);
  self->move_speed_set(50);
  self->rarity_set(THING_RARITY_COMMON);
  self->stamina_set(100);
  self->stat_con_set(10);
  self->stat_def_set(4);
  self->stat_dex_set(5);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(18);
  self->temperature_max_set(50);
  self->temperature_min_set((-20));
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("kraken tentacles");
  self->text_apostrophize_set("kraken tentacle's");
  self->text_description_long_set("A deadly kraken tentacle. Beware its grapple attack and watch out for it's poisonous ink.");
  self->text_description_short_set("A slimy tentacle.");
  self->text_hits_set("bites");
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MONST);
  delay = 800;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "t", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("kraken_tentacle", "kraken tentacle");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_monsters_kraken_tentacle
