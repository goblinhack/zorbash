//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/treasure/map_treasure.py
//

#include "my_native.hpp"

namespace mod_things_treasure_map_treasure {

static void on_enchant(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The map glows. It seems full of knowledge.");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->collision_hit_priority_set(6);
  self->enchant_max_set(1);
  self->environ_dislikes_fire_set(100);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("300");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_flat_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_map_treasure_set(true);
  self->is_moveable_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(1);
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("treasure maps");
  self->text_apostrophize_set("treasure map's");
  self->text_description_enchant_set("all levels");
  self->text_description_long_set("When carrying this magical map you are able to see all the treasure, food and keys on the current level.");
  self->text_description_short_set("An aged treasure map.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "cross", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = 100});
}

static void init(void)
{
  tp_init("map_treasure", "treasure map", "treasure map");
}

void module_init(void)
{
  native_register("map_treasure", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_treasure_map_treasure
