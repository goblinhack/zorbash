//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/spells/spell_of_sanctuary_barrier.py
//

#include "my_native.hpp"

namespace mod_things_spells_spell_of_sanctuary_barrier {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  for (auto it : my::level_get_all(me, x, y)) {
    if (my::thing_is_portal(it)) {
      my::spawn_at_my_position(it, "explosion_major");
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_check_set(true);
  self->collision_hit_priority_set(100);
  self->dmg_chance_d1000_magic_drain_set(0, 1000);
  self->dmg_chance_d1000_negation_set(0, 1000);
  self->dmg_magic_drain_dice_set("1");
  self->dmg_negation_dice_set("1");
  self->dmg_num_of_attacks_set(2);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_oversized_and_centered_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->health_initial_dice_set("100+1d100");
  self->is_attackable_by_monst_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_necrosis_set(true);
  self->is_immune_to_poison_set(true);
  self->is_immune_to_stamina_drain_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_not_shown_as_a_pet_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_obs_spawn_set(true);
  self->is_one_per_tile_set(true);
  self->is_spell_of_sanctuary_barrier_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("20+1d20");
  self->normal_placement_rules_set(true);
  self->on_born_do_set("me.on_born()");
  self->text_a_or_an_set("a");
  self->text_description_short_set("A scrawled mark on the floor that repels all of evil intent. Hopefully that does not include you!");
  self->text_hits_set("burns");
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 250;
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.1", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.2", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 255, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.3", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 200, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.4", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 150, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.1", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 150, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.2", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 100, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.3", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 150, .delay_ms = delay});
  my::tile(self, {.tile = "spell_of_sanctuary_barrier.4", .ascii_fg_char = "*", .ascii_bg_char = "block", .ascii_bg_col_name = "red", .ascii_bg_alpha = 150, .delay_ms = delay});
}

static void init(void)
{
  tp_init("spell_of_sanctuary_barrier", "magic barrier", "magic barrier");
}

void module_init(void)
{
  native_register("spell_of_sanctuary_barrier", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_spells_spell_of_sanctuary_barrier
