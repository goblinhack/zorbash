//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/shield/shield_eagle.py
//

#include "my_native.hpp"

namespace mod_things_shield_shield_eagle {

static void on_enchant(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The eagle shield flaps its wings.");
  }
  my::thing_stat_def_bonus_incr(me, 1);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_damaged_set(10);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_runic_class_A_set(100);
  self->collision_hit_priority_set(6);
  self->enchant_max_set(10);
  self->equip_carry_anim_set("shield_eagle_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("1000");
  self->health_initial_dice_set("1000");
  self->is_able_to_be_equipped_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_auto_equipped_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_immune_to_acid_set(true);
  self->is_immune_to_cold_set(true);
  self->is_immune_to_fire_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_shield_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_value_defensive_set(1);
  self->is_very_hard_set(true);
  self->item_height_set(6);
  self->item_width_set(4);
  self->jump_distance_bonus_set(2);
  self->noise_on_dropping_set(50);
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->shove_bonus_set(1);
  self->stat_def_bonus_set(5);
  self->stat_dex_bonus_set((-2));
  self->stat_str_bonus_set(1);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("eagle shields");
  self->text_apostrophize_set("eagle shield's");
  self->text_description_enchant_set("+1 DEF");
  self->text_description_long_set("Fight and glide like the eagle with this dazzling lightweight shield.");
  self->text_description_short_set("Eagle shield.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "[", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray5"});
}

static void init(void)
{
  tp_init("shield_eagle", "eagle shield", "shield, eagle");
}

void module_init(void)
{
  native_register("shield_eagle", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_shield_shield_eagle
