//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/boots/boots_teleport_emer.py
//

#include "my_native.hpp"

namespace mod_things_boots_boots_teleport_emer {

static void on_enchant(uint32_t me, int x, int y);
static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The boots become a bit less squeaky.");
  }
  my::thing_noise_incr(me, (-10));
}

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  my::thing_teleport_randomly(owner);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->equip_carry_anim_set("boots_teleport_emer_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("250");
  self->health_initial_dice_set("20");
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
  self->is_boots_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_value_defensive_set(1);
  self->item_height_set(5);
  self->item_width_set(5);
  self->noise_additional_on_jump_end_set(50);
  self->noise_additional_on_teleporting_set(50);
  self->noise_on_dropping_set(50);
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_use_do_set("me.on_use()");
  self->rarity_set(THING_RARITY_RARE);
  self->stat_dex_bonus_set((-1));
  self->teleport_distance_set(20);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("boots of teleport");
  self->text_apostrophize_set("boots of teleport's");
  self->text_description_enchant_set("-10 decibels");
  self->text_description_long_set("Boots of uncontrolled emergency teleport. Useful in moments of desperation, these squeaky boots will randomly teleport you up to 20 tiles away when used. This may be good or bad depending on your situation.");
  self->text_description_short_set("Boots of emergency teleport.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "[", .ascii_bg_col_name = "", .ascii_fg_col_name = "white"});
}

static void init(void)
{
  tp_init("boots_teleport_emer", "boots of emergency teleport", "boots emtele");
}

void module_init(void)
{
  native_register("boots_teleport_emer", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("boots_teleport_emer", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_boots_boots_teleport_emer
