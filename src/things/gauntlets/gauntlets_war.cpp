//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/gauntlets/gauntlets_war.py
//

#include "my_native.hpp"

namespace mod_things_gauntlets_gauntlets_war {

static void on_equip(uint32_t owner, uint32_t me, int x, int y);
static void on_unequip(uint32_t owner, uint32_t me, int x, int y);
static void on_enchant(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_equip(uint32_t owner, uint32_t me, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "Your fists feel full of rage!");
  }
}

static void on_unequip(uint32_t owner, uint32_t me, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "Your fists feel like normal fists again!");
  }
}

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "The gauntlets become yet more war like.");
  }
  my::thing_shove_bonus_incr(me, 1);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_runic_class_A_set(10);
  self->equip_carry_anim_set("gauntlets_war_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("1050");
  self->health_initial_dice_set("200");
  self->is_able_to_be_equipped_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_auto_equipped_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_gauntlet_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_value_defensive_set(1);
  self->is_value_offensive_set(1);
  self->item_height_set(3);
  self->item_width_set(3);
  self->noise_additional_on_jump_end_set((-50));
  self->noise_on_dropping_set((-50));
  self->noise_on_moving_set(25);
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_equip_do_set("me.on_equip()");
  self->on_unequip_do_set("me.on_unequip()");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_def_bonus_set(3);
  self->stat_str_bonus_set(5);
  self->text_description_enchant_set("+1 str, +1 def, +1 shove");
  self->text_description_long_set("Provides a hefty strength and defense bonus, these gauntlets mean business.\?");
  self->text_description_short_set("Gauntlets of war.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "[", .ascii_bg_col_name = "", .ascii_fg_col_name = "white"});
}

static void init(void)
{
  tp_init("gauntlets_war", "gauntlets of war", "gauntlets, war");
}

void module_init(void)
{
  native_register("gauntlets_war", "on_equip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_equip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("gauntlets_war", "on_unequip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_unequip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("gauntlets_war", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_gauntlets_gauntlets_war
