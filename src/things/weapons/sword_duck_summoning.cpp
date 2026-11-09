//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/weapons/sword_duck_summoning.py
//

#include "my_native.hpp"

namespace mod_things_weapons_sword_duck_summoning {

static void on_swing(uint32_t owner, uint32_t item, int x, int y);
static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void on_equip(uint32_t owner, uint32_t me, int x, int y);
static void on_unequip(uint32_t owner, uint32_t me, int x, int y);
static void on_enchant(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_swing(uint32_t owner, uint32_t item, int x, int y)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_swing") + std::to_string(my::non_pcg_random_inclusive(1, 3)))).c_str());
}

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_impact") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
  return (damage + my::thing_enchant_count_get(me));
}

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  int damage = 0;
  uint32_t duck = 0;
  uint32_t hitter = 0;
  int nducks = 0;
  if ((! (target != 0))) {
    return;
  }
  nducks = my::pcg_random_inclusive(1, 6);
  for (int n = 0, n_end_ = nducks; n < n_end_; n += 1) {
    duck = my::spawn_at_my_position(target, "duck1");
    if ((duck != 0)) {
      my::thing_friend_add(duck, owner);
    }
  }
  hitter = item;
  target = owner;
  damage = (d6() * nducks);
  my::thing_hit_dmg_stamina(owner, hitter, target, damage);
  my::spawn_at_my_position(target, "magical_effect");
  if (my::thing_is_player(owner)) {
    my::topcon("Your sword drains your stamina!");
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

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "The sword quacks.");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->attack_no_msg_set(true);
  self->chance_d10000_damaged_set(1);
  self->chance_d10000_enchanted_set(200);
  self->chance_d10000_runic_class_A_set(1000);
  self->charge_count_set(5);
  self->dmg_chance_d1000_melee_set(0, 1000);
  self->dmg_melee_dice_set("1d10+2");
  self->dmg_num_of_attacks_set(1);
  self->equip_carry_anim_set("sword_duck_summoning_carry");
  self->gfx_anim_use_set("sword_duck_summoning_swing");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_show_light_once_seen_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("1500");
  self->health_initial_dice_set("1d1000+500");
  self->is_able_to_attack_owner_set(true);
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
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_immune_to_acid_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_item_targeted_set(true);
  self->is_kept_after_final_use_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_pointy_set(true);
  self->is_sword_set(true);
  self->is_target_select_set(true);
  self->is_tickable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_very_hard_set(true);
  self->is_weapon_class_C_set(true);
  self->is_weapon_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->light_color_set("yellow");
  self->light_dist_set(1);
  self->noise_on_dropping_set(5);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_equip_do_set("me.on_equip()");
  self->on_owner_attack_dmg_melee_do_set("me.on_owner_attack_dmg_melee()");
  self->on_swing_do_set("me.on_swing()");
  self->on_unequip_do_set("me.on_unequip()");
  self->on_use_do_set("me.on_use()");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_att_bonus_set(2);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("swords of duck summoning");
  self->text_apostrophize_set("sword of duck summoning's");
  self->text_description_enchant_set("+1 DMG, +1 ATT");
  self->text_description_long_set("This powerful sword additionally grants you the ability to summon a duck at any given location within range. Said duck will be friendly towards you and may or may not be an assist in battle.");
  self->text_description_short_set("Thy ducky powered means of justice.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "up_arrow", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow"});
}

static void init(void)
{
  tp_init("sword_duck_summoning", "sword of duck summoning", "sword, duck");
}

void module_init(void)
{
  native_register("sword_duck_summoning", "on_swing", 4, [](const int64_t *a) -> NativeRet { (void) a; on_swing((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("sword_duck_summoning", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  native_register("sword_duck_summoning", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("sword_duck_summoning", "on_equip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_equip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("sword_duck_summoning", "on_unequip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_unequip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("sword_duck_summoning", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_weapons_sword_duck_summoning
