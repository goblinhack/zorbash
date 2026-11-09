//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/torch.py
//

#include "my_native.hpp"

namespace mod_things_items_torch {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void on_lifespan_tick(uint32_t owner, uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name, const std::vector< std::string > &tiles);
static void init(void);

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  if (my::level_is_chasm_at(me, x, y)) {
    return;
  }
  if (my::level_is_water_at(me, x, y)) {
    return;
  }
  for (auto it : my::level_get_all(me, x, y)) {
    if (my::thing_is_combustible(it)) {
      my::spawn_at_my_position(me, "fire");
      return;
    }
  }
}

static void on_lifespan_tick(uint32_t owner, uint32_t me, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "One of your torches fizzles out.");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name, const std::vector< std::string > &tiles)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_set_on_fire_set(2000);
  self->chance_d1000_appearing_set(100);
  self->charge_count_set(10);
  self->collision_hit_priority_set(1);
  self->collision_hit_priority_set(6);
  self->gfx_ascii_show_light_once_seen_set(true);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_in_bg_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_glows_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_flickers_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->health_initial_dice_set("30");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_hittable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_throwable_set(true);
  self->is_tickable_set(true);
  self->is_torch_set(true);
  self->is_treasure_class_A_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_wooden_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->lifespan_dice_set("1d300+100");
  self->light_color_set("orange");
  self->light_dist_set(1);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->on_lifespan_tick_do_set("me.on_lifespan_tick()");
  self->on_thrown_do_set("me.on_thrown()");
  self->temperature_set(50);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("torches");
  self->text_apostrophize_set("torch's");
  self->text_description_long_set("A bundle of torches to light the way. Be warned, they do burn out slowly. Don't find yourself lost in the dark...");
  self->text_description_short_set("A small beacon of light in this blighted place.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  delay = 100;
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "(", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange", .delay_ms = delay});
  }
}

static void init(void)
{
  tp_init("torch", "torch", "torch", std::vector< std::string >{"torch.1", "torch.2", "torch.3", "torch.4", "torch.5", "torch.6"});
}

void module_init(void)
{
  native_register("torch", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("torch", "on_lifespan_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; on_lifespan_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_torch
