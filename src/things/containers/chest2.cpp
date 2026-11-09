//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/containers/chest2.py
//

#include "my_native.hpp"

namespace mod_things_containers_chest2 {

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_death(uint32_t me, int x, int y);
static void on_open(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, ((std::string("door_hit") + std::to_string(my::non_pcg_random_inclusive(1, 2)))).c_str());
}

static void on_death(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "door_break");
}

static void on_open(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "door_open");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->capacity_height_set(8);
  self->capacity_width_set(8);
  self->chance_d1000_carrier_of_treasure_class_A_set(100);
  self->chance_d1000_carrier_of_treasure_class_B_set(200);
  self->chance_d1000_carrier_of_treasure_class_C_set(1000);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->health_initial_dice_set("200");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_attackable_by_player_set(true);
  self->is_bag_item_container_set(true);
  self->is_bag_item_not_stackable_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_collectable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_crushable_set(true);
  self->is_crystalline_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_item_carrier_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_metal_set(true);
  self->is_moveable_set(true);
  self->is_openable_set(true);
  self->is_shootable_set(true);
  self->is_treasure_chest_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->item_height_set(5);
  self->item_width_set(5);
  self->noise_on_dropping_set(100);
  self->normal_placement_rules_set(true);
  self->on_death_do_set("me.on_death()");
  self->on_death_drop_all_items_set(true);
  self->on_death_is_open_set(true);
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_open_do_set("me.on_open()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("crystal treasure chests");
  self->text_apostrophize_set("crystal treasure chest's");
  self->text_description_long_set("A fancy treasure crystal chest.");
  self->text_description_short_set("A fancy treasure crystal chest.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = "chest2", .ascii_fg_char = "up_triangle", .ascii_bg_col_name = "", .ascii_fg_col_name = "silver", .delay_ms = 1000});
  my::tile(self, {.tile = (name + ".open"), .ascii_fg_char = "up_triangle", .ascii_bg_col_name = "", .ascii_fg_col_name = "silver", .is_open = true});
  my::tile(self, {.tile = (name + ".open"), .ascii_fg_char = "up_triangle", .ascii_bg_col_name = "", .ascii_fg_col_name = "silver", .is_dead = true});
}

static void init(void)
{
  tp_init("chest2", "fancy crystal treasure chest", "chest, crystal");
}

void module_init(void)
{
  native_register("chest2", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("chest2", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("chest2", "on_open", 3, [](const int64_t *a) -> NativeRet { (void) a; on_open((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_containers_chest2
