//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/cloaks/cloak_protection.py
//

#include "my_native.hpp"

namespace mod_things_cloaks_cloak_protection {

static void on_enchant(uint32_t me, int x, int y);
static bool on_tick(uint32_t owner, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The cloak of protection shimmers.");
  }
  my::thing_stat_def_bonus_incr(me, 2);
}

static bool on_tick(uint32_t owner, uint32_t item, int x, int y)
{
  if ((! (owner != 0))) {
    return false;
  }
  my::thing_stamina_decr(owner, 2);
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_set_on_fire_set(2000);
  self->collision_hit_priority_set(6);
  self->enchant_max_set(10);
  self->equip_carry_anim_set("cloak_protection_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("250");
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
  self->is_burnable_set(true);
  self->is_cloak_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_tickable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_value_defensive_set(1);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set((-20));
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_tick_do_set("me.on_tick()");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_def_bonus_set(2);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("cloaks of protection");
  self->text_apostrophize_set("cloak of protection's");
  self->text_description_enchant_set("+2 DEF");
  self->text_description_long_set("A finely embroidered cloak that offers modest protection against attack.");
  self->text_description_short_set("Cloak of protection.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "[", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink"});
}

static void init(void)
{
  tp_init("cloak_protection", "cloak of modest protection", "cloak, protection");
}

void module_init(void)
{
  native_register("cloak_protection", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cloak_protection", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_cloaks_cloak_protection
