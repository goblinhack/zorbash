//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/weapons/warhammer.py
//

#include "my_native.hpp"

namespace mod_things_weapons_warhammer {

static void on_swing(uint32_t owner, uint32_t item, int x, int y);
static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static void on_equip(uint32_t owner, uint32_t me, int x, int y);
static void on_unequip(uint32_t owner, uint32_t me, int x, int y);
static void on_enchant(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_swing(uint32_t owner, uint32_t item, int x, int y)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_swing") + std::to_string(my::non_pcg_random_inclusive(1, 3)))).c_str());
  my::thing_move_penalty_incr(owner, 1);
}

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_impact") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
  if (my::thing_is_moveable(victim)) {
    my::thing_repulse(owner, victim);
  }
  return (damage + my::thing_enchant_count_get(me));
}

static void on_equip(uint32_t owner, uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, "sword_equip");
  return;
}

static void on_unequip(uint32_t owner, uint32_t me, int x, int y)
{
  return;
}

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "The warhammer glows.");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_damaged_set(1);
  self->chance_d10000_enchanted_set(200);
  self->chance_d10000_runic_class_A_set(1000);
  self->chance_d10000_set_on_fire_set(5);
  self->collision_hit_360_set(true);
  self->dmg_chance_d1000_melee_set(0, 1000);
  self->dmg_melee_dice_set("4d8");
  self->equip_carry_anim_set("warhammer_carry");
  self->gfx_anim_use_set("warhammer_swing");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("450");
  self->health_initial_dice_set("1d200+10");
  self->is_able_to_be_equipped_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_aerodynamic_set(true);
  self->is_auto_equipped_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_blunt_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_warhammer_set(true);
  self->is_weapon_class_C_set(true);
  self->is_weapon_set(true);
  self->item_height_set(5);
  self->item_width_set(5);
  self->noise_on_dropping_set(30);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_equip_do_set("me.on_equip()");
  self->on_owner_attack_dmg_melee_do_set("me.on_owner_attack_dmg_melee()");
  self->on_swing_do_set("me.on_swing()");
  self->on_unequip_do_set("me.on_unequip()");
  self->rarity_set(THING_RARITY_COMMON);
  self->stamina_drain_on_attacking_set(3);
  self->stat_str_min_set(14);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("warhammers");
  self->text_apostrophize_set("warhammer's");
  self->text_description_enchant_set("+1 DMG");
  self->text_description_long2_set("Also useful for pruning and general gardening activities.");
  self->text_description_long3_set("Blunt weapons are very effective against soft slimy enemies.");
  self->text_description_long_set("Dealing massive damage and driving the victim back one tile, the only disadvantage of the mighty warhammer is that each swing has a move penalty. Hopefully the extra damage dealt compensates!");
  self->text_description_short_set("Mighty warhammer");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "up_arrow", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray50"});
}

static void init(void)
{
  tp_init("warhammer", "warhammer", "warhammer");
}

void module_init(void)
{
  native_register("warhammer", "on_swing", 4, [](const int64_t *a) -> NativeRet { (void) a; on_swing((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("warhammer", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  native_register("warhammer", "on_equip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_equip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("warhammer", "on_unequip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_unequip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("warhammer", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_weapons_warhammer
