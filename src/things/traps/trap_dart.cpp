//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/traps/trap_dart.py
//

#include "my_native.hpp"

namespace mod_things_traps_trap_dart
{

static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static bool on_want_to_shoot_at(uint32_t me, uint32_t target, int target_x, int target_y)
{
  int roll = 0;
  for (auto it : my::level_get_all(me, target_x, target_y)) {
    if ((it == me)) {
      continue;
    }
    if (my::thing_is_interesting(it)) {
      if (my::thing_possible_to_attack(me, it)) {
        roll = d100();
        if ((roll < 5)) {
          my::thing_throw_at(me, "dart_paralysis", it);
        } else if ((roll < 10)) {
          my::thing_throw_at(me, "dart_poison", it);
        } else {
          my::thing_throw_at(me, "dart", it);
        }
      }
    }
  }
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self  = my::tp_load(name, text_long_name);
  self->aggression_pct_set(100);
  self->attack_humanoid_set(true);
  self->chance_d1000_appearing_set(100);
  self->chance_d1000_shooting_set(300);
  self->collision_hit_priority_set(20);
  self->distance_throw_set(5);
  self->distance_vision_set(8);
  self->dmg_chance_d1000_crush_set(0, 1000);
  self->dmg_crush_dice_set("4d6");
  self->dmg_num_of_attacks_set(0);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("20+1d20");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_see_in_the_dark_set(true);
  self->is_able_to_shoot_at_close_range_set(true);
  self->is_able_to_shoot_at_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_corpse_on_death_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_cursor_path_blocker_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_heavy_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_interesting_set(true);
  self->is_lifeless_set(true);
  self->is_light_blocker_for_monst_set(true);
  self->is_loggable_set(true);
  self->is_mob_class_B_set(true);
  self->is_mob_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_jump_end_set(true);
  self->is_obs_jumping_set(true);
  self->is_obs_shooting_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spell_casting_set(true);
  self->is_obs_throwing_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_stone_set(true);
  self->is_tickable_set(true);
  self->is_trap_set(true);
  self->is_turret_set(true);
  self->normal_placement_rules_set(true);
  self->on_want_to_shoot_at_do_set("me.on_want_to_shoot_at()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("dart turrets");
  self->text_apostrophize_set("dart turret's");
  self->text_description_long_set(
      "A menacing stone turret with a roaming target-like eye atop it. It's either the entrance to a certain brand "
      "of shop, or something nasty. Which can it be...\?");
  self->text_description_short_set("A dart turret");
  self->thing_size_set(THING_SIZE_LARGE);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_MOB);
  delay = 100;
  my::tile(self, {.tile              = (name + ".1"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".2"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".1"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".2"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".1"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".2"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".1"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".2"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".1"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".2"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".1"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".2"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".3"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".4"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".3"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".4"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".3"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".4"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".3"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".4"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".3"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".4"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".3"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "red",
                  .ascii_fg_col_name = "white",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".4"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "white",
                  .ascii_fg_col_name = "red",
                  .delay_ms          = delay});
  my::tile(self, {.tile              = (name + ".dead"),
                  .ascii_fg_char     = "^",
                  .ascii_bg_col_name = "gray",
                  .ascii_fg_col_name = "black",
                  .delay_ms          = delay,
                  .is_dead           = true,
                  .is_end_of_anim    = true});
}

static void init(void) { tp_init("trap_dart", "dart turret"); }

void module_init(void)
{
  native_register("trap_dart", "on_want_to_shoot_at", 4, [](const int64_t *a) -> NativeRet {
    (void) a;
    return NativeRet {(int) on_want_to_shoot_at((uint32_t) a[ 0 ], (uint32_t) a[ 1 ], (int) a[ 2 ], (int) a[ 3 ]),
                      {}};
  });
  init();
}

} // namespace mod_things_traps_trap_dart
