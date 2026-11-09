//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/weapons/axe.py
//

#include "my_native.hpp"

namespace mod_things_weapons_axe {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void on_swing(uint32_t owner, uint32_t item, int x, int y);
static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static void on_enchant(uint32_t me, int x, int y);
static void on_equip(uint32_t owner, uint32_t me, int x, int y);
static void on_unequip(uint32_t owner, uint32_t me, int x, int y);
static void init_weapon(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  for (auto it : my::level_get_all(me, x, y)) {
    if (my::thing_is_interesting(it)) {
      if ((it == me)) {
        continue;
      }
      if ((it == owner)) {
        continue;
      }
      my::thing_hit_dmg_missile(owner, me, it, 0, 0, true);
    }
  }
  if ((my::pcg_random_inclusive(1, 100) < 5)) {
    my::thing_dead(me, "broken");
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::topcon("Your axe shatters on impact!");
    }
  }
}

static void on_swing(uint32_t owner, uint32_t item, int x, int y)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_swing") + std::to_string(my::non_pcg_random_inclusive(1, 3)))).c_str());
}

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_impact") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
  return (damage + my::thing_enchant_count_get(me));
}

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "The axe glows.");
  }
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

static void init_weapon(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_crit_set(500);
  self->chance_d10000_damaged_set(5);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_runic_class_A_set(500);
  self->collision_hit_360_set(true);
  self->dmg_chance_d1000_melee_set(0, 1000);
  self->dmg_melee_dice_set("1d6");
  self->equip_carry_anim_set("axe_carry");
  self->gfx_anim_use_set("axe_swing");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("150");
  self->health_initial_dice_set("1d200+150");
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
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_metal_set(true);
  self->is_moveable_set(true);
  self->is_throwable_set(true);
  self->is_thrown_as_a_weapon_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_weapon_class_B_set(true);
  self->is_weapon_set(true);
  self->is_wooden_set(true);
  self->item_height_set(6);
  self->item_width_set(6);
  self->noise_on_dropping_set(15);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_equip_do_set("me.on_equip()");
  self->on_owner_attack_dmg_melee_do_set("me.on_owner_attack_dmg_melee()");
  self->on_swing_do_set("me.on_swing()");
  self->on_thrown_do_set("me.on_thrown()");
  self->on_unequip_do_set("me.on_unequip()");
  self->rarity_set(THING_RARITY_UNCOMMON);
  self->stamina_drain_on_attacking_set(2);
  self->stat_att_bonus_set(1);
  self->text_pluralize_set("short axes");
  self->text_apostrophize_set("short axe's");
  self->text_a_or_an_set("a");
  self->text_description_enchant_set("+1 DMG, +1 ATT");
  self->text_description_long_set("A gleaming wooden handled axe. It's a bit short and extra hungry for vengeance. Against what, who can say. Take care, as your mighty swing can hit all monsters adjacent to you.");
  self->text_description_short_set("Thy choppy means of justice.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "up_arrow", .ascii_bg_col_name = "", .ascii_fg_col_name = "white"});
}

static void init(void)
{
  init_weapon("axe", "short axe", "short axe");
}

void module_init(void)
{
  native_register("axe", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("axe", "on_swing", 4, [](const int64_t *a) -> NativeRet { (void) a; on_swing((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("axe", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  native_register("axe", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("axe", "on_equip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_equip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("axe", "on_unequip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_unequip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_weapons_axe
