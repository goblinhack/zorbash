//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/vampire_rose_stem.py
//

#include "my_native.hpp"

namespace mod_things_monsters_vampire_rose_stem {

static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void try_to_grow(uint32_t me, int x, int y, int dx, int dy);
static void on_idle(uint32_t me, int x, int y);
static void tp_init(std::string name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_MONST, "squelch");
}

static void try_to_grow(uint32_t me, int x, int y, int dx, int dy)
{
  if ((my::level_is_carnivorous_plant_at(me, (x + dx), (y + dy)) || my::level_is_lava_at(me, (x + dx), (y + dy)) || my::level_is_chasm_at(me, (x + dx), (y + dy)) || my::level_is_brazier_at(me, (x + dx), (y + dy)) || my::level_is_fire_at(me, (x + dx), (y + dy)) || my::level_is_wall_at(me, (x + dx), (y + dy)) || my::level_is_water_at(me, (x + dx), (y + dy)))) {
    return;
  }
  if ((my::level_is_floor_at(me, (x + dx), (y + dy)) || my::level_is_corridor_at(me, (x + dx), (y + dy)))) {
    if ((my::pcg_random_inclusive(1, 100) < 10)) {
      my::spawn_at(me, "vampire_rose_stem1", (x + dx), (y + dy));
      return;
    }
    if ((my::pcg_random_inclusive(1, 100) < 10)) {
      my::spawn_at(me, "vampire_rose_stem2", (x + dx), (y + dy));
      return;
    }
    if ((my::level_is_monst_at(me, (x + dx), (y + dy)) || my::level_is_player_at(me, (x + dx), (y + dy)))) {
      return;
    }
    if ((my::pcg_random_inclusive(1, 100) < 5)) {
      my::spawn_at(me, "vampire_rose", (x + dx), (y + dy));
    }
  }
}

static void on_idle(uint32_t me, int x, int y)
{
  try_to_grow(me, x, y, (-1), 0);
  try_to_grow(me, x, y, 1, 0);
  try_to_grow(me, x, y, 0, (-1));
  try_to_grow(me, x, y, 0, 1);
}

static void tp_init(std::string name, const std::string &text_long_name, const std::string &text_short_name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(100);
  self->attack_humanoid_set(true);
  self->attack_meat_set(true);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->dmg_chance_d1000_nat_att_set(0, 1000);
  self->dmg_chance_d1000_poison_set(0, 100);
  self->dmg_nat_att_dice_set("1d3");
  self->dmg_nat_att_type_set("prick");
  self->dmg_poison_dice_set("1d4+1");
  self->dmg_rcv_doubled_from_fire_set(true);
  self->environ_hates_acid_set(true);
  self->environ_hates_fire_set(100);
  self->gfx_anim_use_set("red_splatter");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->health_initial_dice_set("1d3");
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_carnivorous_plant_set(true);
  self->is_combustible_set(true);
  self->is_corpse_on_death_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_meat_set(true);
  self->is_flat_set(true);
  self->is_green_blooded_set(true);
  self->is_hittable_set(true);
  self->is_immune_to_confusion_set(true);
  self->is_immune_to_entrancement_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_plant_set(true);
  self->is_shootable_set(true);
  self->is_soft_set(true);
  self->is_tickable_set(true);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d4");
  self->on_idle_tick_freq_dice_set("1d20:vampire_rose_stem.on_idle()");
  self->on_you_nat_attack_attempt_do_set("vampire_rose_stem.on_you_nat_attack_attempt()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stat_con_set(20);
  self->stat_def_set(0);
  self->stat_dex_set(0);
  self->stat_luck_set(10);
  self->stat_psi_set(0);
  self->stat_str_set(10);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_sensitive_set(true);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("vampire rose stems");
  self->text_apostrophize_set("vampire rose stem's");
  self->text_description_long_set("Vampire rose stems grow rapidly and rapidly spawn roses of a most deadly type.");
  self->text_description_short_set("A thorny vampire rose stem.");
  self->text_hits_set("pricks");
  self->thing_size_set(THING_SIZE_SMALL);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  delay = 5000;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay});
  name = std::string("vampire_rose_stem");
  my::tile(self, {.tile = (name + ".1.dead"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_dead = true});
  my::tile(self, {.tile = (name + ".2.dead"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_dead = true, .is_end_of_anim = true});
  my::tile(self, {.tile = (name + ".3.dead"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_dead = true, .is_end_of_anim = true});
  my::tile(self, {.tile = (name + ".4.dead"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_dead = true, .is_end_of_anim = true});
  my::tile(self, {.tile = (name + ".5.dead"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_dead = true, .is_end_of_anim = true});
  my::tile(self, {.tile = (name + ".6.dead"), .ascii_fg_char = "~", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown", .is_dead = true, .is_end_of_anim = true});
}

static void init(void)
{
  tp_init("vampire_rose_stem1", "vampire rose stem", "vampire rose stem");
  tp_init("vampire_rose_stem2", "vampire rose stem", "vampire rose stem");
}

void module_init(void)
{
  native_register("vampire_rose_stem", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("vampire_rose_stem", "try_to_grow", 5, [](const int64_t *a) -> NativeRet { (void) a; try_to_grow((uint32_t) a[0], (int) a[1], (int) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("vampire_rose_stem", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_vampire_rose_stem
