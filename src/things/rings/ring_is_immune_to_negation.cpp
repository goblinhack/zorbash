//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/rings/ring_is_immune_to_negation.py
//

#include "my_native.hpp"

namespace mod_things_rings_ring_is_immune_to_negation {

static void on_equip(uint32_t owner, uint32_t me, int x, int y);
static void on_unequip(uint32_t owner, uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_equip(uint32_t owner, uint32_t me, int x, int y)
{
  my::thing_buff_add(owner, "buff_permanent_immune_to_negation");
}

static void on_unequip(uint32_t owner, uint32_t me, int x, int y)
{
  my::thing_buff_remove(owner, "buff_permanent_immune_to_negation");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->collision_hit_priority_set(5);
  self->collision_hit_priority_set(6);
  self->equip_carry_anim_set("ring_is_immune_to_negation_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("500");
  self->health_initial_dice_set("1d20");
  self->health_initial_dice_set("200");
  self->is_able_to_be_equipped_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_spawn_things_set(true);
  self->is_auto_equipped_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_collectable_set(true);
  self->is_combustible_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_immune_to_negation_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_magical_set(true);
  self->is_ring_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_value_defensive_set(1);
  self->is_very_combustible_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->normal_placement_rules_set(true);
  self->on_equip_do_set("me.on_equip()");
  self->on_unequip_do_set("me.on_unequip()");
  self->stat_con_bonus_set((-1));
  self->text_a_or_an_set("a");
  self->text_pluralize_set("rings of negation immunities");
  self->text_apostrophize_set("ring of negation immunity's");
  self->text_description_enchant_set("+1 CON");
  self->text_description_long_set("Negate your negative qualities with this ring of mega nega negativity. Attacks of negation will have no impact on you.");
  self->text_description_short_set("A ring of negation immunity.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "circle", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = 100});
}

static void init(void)
{
  tp_init("ring_is_immune_to_negation", "ring of negation immunity", "ring, negation");
}

void module_init(void)
{
  native_register("ring_is_immune_to_negation", "on_equip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_equip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("ring_is_immune_to_negation", "on_unequip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_unequip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_rings_ring_is_immune_to_negation
