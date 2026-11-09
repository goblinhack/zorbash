//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/barrel.py
//

#include "my_native.hpp"

namespace mod_things_items_barrel {

static void explode(uint32_t me, int x, int y);
static void on_fire(uint32_t me, int x, int y);
static void on_fall(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void explode(uint32_t me, int x, int y)
{
  if (my::thing_is_dead(me)) {
    return;
  }
  my::thing_dead(me, "exploded");
  my::thing_msg(me, "The oil filled barrel explodes!");
  my::spawn_at_my_position(me, "explosion_major");
  my::spawn_set_fire_to_things_around_me(me, "fire");
  my::spawn_at_my_position(me, "fire");
}

static void on_fire(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void on_fall(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void on_death(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->chance_d1000_appearing_set(100);
  self->collision_check_set(true);
  self->collision_hit_priority_set(1);
  self->dmg_chance_d1000_crush_set(0, 1000);
  self->dmg_chance_d1000_drown_set(0, 1000);
  self->dmg_crush_dice_set("2d6");
  self->dmg_drown_dice_set("2d6");
  self->dmg_rcv_doubled_from_fire_set(true);
  self->environ_dislikes_fire_set(100);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_oversized_and_on_floor_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->is_able_to_fall_over_set(true);
  self->is_able_to_fall_set(true);
  self->is_always_hit_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_barrel_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_burnable_set(true);
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
  self->is_light_blocker_for_monst_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_obs_ai_set(true);
  self->is_obs_shoving_set(true);
  self->is_obs_spawn_monst_set(true);
  self->is_one_per_tile_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_very_combustible_set(true);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_fall_do_set("me.on_fall()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("barrels");
  self->text_apostrophize_set("barrel's");
  self->text_description_short_set("A barrel of oil. Why\? Don't ask.");
  self->thing_size_set(THING_SIZE_LARGE);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BARREL);
  my::tile(self, {.tile = name, .ascii_fg_char = "B", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown"});
}

static void init(void)
{
  tp_init("barrel", "barrel");
}

void module_init(void)
{
  native_register("barrel", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("barrel", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("barrel", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("barrel", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_barrel
