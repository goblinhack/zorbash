//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/cloaks/cloak_fire.py
//

#include "my_native.hpp"

namespace mod_things_cloaks_cloak_fire {

static void on_equip(uint32_t owner, uint32_t me, int x, int y);
static void on_unequip(uint32_t owner, uint32_t me, int x, int y);
static void on_enchant(uint32_t me, int x, int y);
static void on_waiting(uint32_t me, int x, int y);
static void on_move(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_equip(uint32_t owner, uint32_t me, int x, int y)
{
  my::thing_buff_add(owner, "buff_permanent_immune_to_fire");
}

static void on_unequip(uint32_t owner, uint32_t me, int x, int y)
{
  my::thing_buff_remove(owner, "buff_permanent_immune_to_fire");
}

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg_if_not_dead_or_dying(me, "The fire cloak burns brighter.");
  }
}

static void on_waiting(uint32_t me, int x, int y)
{
  int enchant = 0;
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if ((! (owner != 0))) {
    return;
  }
  enchant = my::thing_enchant_count_get(me);
  if ((enchant == 0)) {
    enchant = 1;
  }
  if (my::level_is_lava_at(owner, x, y)) {
    my::thing_stamina_incr(owner, (10 * enchant));
    my::thing_health_incr(owner, (10 * enchant));
    if (my::thing_is_player(owner)) {
      my::thing_msg_if_not_dead_or_dying(owner, "You wait inside the lava and feel invigorated.");
    }
    return;
  }
  if ((my::level_is_fire_at(owner, x, y) || my::level_is_lava_at(owner, x, y))) {
    my::thing_stamina_incr(owner, (5 * enchant));
    my::thing_health_incr(owner, (5 * enchant));
    if (my::thing_is_player(owner)) {
      my::thing_msg_if_not_dead_or_dying(owner, "You wait inside the fire and feel invigorated.");
    }
    return;
  }
  return;
}

static void on_move(uint32_t me, int x, int y)
{
  (void) on_waiting(me, x, y);
  return;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->collision_hit_priority_set(6);
  self->enchant_max_set(10);
  self->equip_carry_anim_set("cloak_fire_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("666");
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
  self->is_cloak_set(true);
  self->is_collectable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_value_defensive_set(1);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set((-20));
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_equip_do_set("me.on_equip()");
  self->on_move_do_set("me.on_move()");
  self->on_unequip_do_set("me.on_unequip()");
  self->on_waiting_do_set("me.on_waiting()");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_def_bonus_set(1);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("cloaks of fires");
  self->text_apostrophize_set("cloak of fire's");
  self->text_description_enchant_set("+1 DEF");
  self->text_description_long_set("A brilliant fiery red cloak.");
  self->text_description_short_set("Cloak of fire protection.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "[", .ascii_bg_col_name = "", .ascii_fg_col_name = "orange"});
}

static void init(void)
{
  tp_init("cloak_fire", "cloak of fire protection", "cloak, fire");
}

void module_init(void)
{
  native_register("cloak_fire", "on_equip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_equip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("cloak_fire", "on_unequip", 4, [](const int64_t *a) -> NativeRet { (void) a; on_unequip((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("cloak_fire", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cloak_fire", "on_waiting", 3, [](const int64_t *a) -> NativeRet { (void) a; on_waiting((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cloak_fire", "on_move", 3, [](const int64_t *a) -> NativeRet { (void) a; on_move((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_cloaks_cloak_fire
