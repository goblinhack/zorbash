//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/cloaks/cloak_stone.py
//

#include "my_native.hpp"

namespace mod_things_cloaks_cloak_stone {

static void on_enchant(uint32_t me, int x, int y);
static void on_waiting(uint32_t me, int x, int y);
static void on_move(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The stone cloak glistens.");
  }
  my::thing_stat_def_bonus_incr(me, 2);
}

static void on_waiting(uint32_t me, int x, int y)
{
  int new_stamina = 0;
  uint32_t owner = 0;
  int stamina = 0;
  owner = my::thing_top_owner_id_get(me);
  if ((! (owner != 0))) {
    return;
  }
  if (my::level_is_wall_at(owner, x, y)) {
    stamina = my::thing_stamina(owner);
    new_stamina = ((int) ((((double) ((double) (stamina)) / (double) 100.0) * 90.0)));
    my::thing_stamina_set(owner, new_stamina);
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, "You wait inside the wall and feel drained.");
    }
    return;
  }
  if (my::level_is_rock_at(owner, x, y)) {
    stamina = my::thing_stamina(owner);
    new_stamina = ((int) ((((double) ((double) (stamina)) / (double) 100.0) * 80.0)));
    my::thing_stamina_set(owner, new_stamina);
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, "You wait inside solid rock and feel very drained.");
    }
    return;
  }
  return;
}

static void on_move(uint32_t me, int x, int y)
{
  int new_stamina = 0;
  uint32_t owner = 0;
  int stamina = 0;
  owner = my::thing_top_owner_id_get(me);
  if ((! (owner != 0))) {
    return;
  }
  if (my::level_is_wall_at(owner, x, y)) {
    stamina = my::thing_stamina(owner);
    new_stamina = ((int) ((((double) ((double) (stamina)) / (double) 100.0) * 80.0)));
    my::thing_stamina_set(owner, new_stamina);
    if (my::thing_is_player(owner)) {
      my::thing_msg(owner, "You pass into the wall, but feel drained.");
    }
    return;
  }
  if (my::level_is_rock_at(owner, x, y)) {
    stamina = my::thing_stamina(owner);
    new_stamina = ((int) ((((double) ((double) (stamina)) / (double) 100.0) * 50.0)));
    my::thing_stamina_set(owner, new_stamina);
    if (my::thing_is_player(owner)) {
      my::thing_msg(owner, "You pass into solid rock, but feel very drained.");
    }
    return;
  }
  return;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_damaged_set(100);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_set_on_fire_set(2000);
  self->collision_hit_priority_set(6);
  self->enchant_max_set(10);
  self->equip_carry_anim_set("cloak_stone_carry");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gold_value_dice_set("500");
  self->is_able_to_be_equipped_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_walk_through_walls_set(true);
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
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_value_defensive_set(1);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set((-20));
  self->normal_placement_rules_set(true);
  self->on_enchant_do_set("me.on_enchant()");
  self->on_move_do_set("me.on_move()");
  self->on_waiting_do_set("me.on_waiting()");
  self->rarity_set(THING_RARITY_VERY_RARE);
  self->stat_dex_bonus_set((-4));
  self->text_a_or_an_set("a");
  self->text_pluralize_set("stone cloaks");
  self->text_apostrophize_set("stone cloak's");
  self->text_description_enchant_set("+1 DEF");
  self->text_description_long_set("A strange, almost black, cloak that looks to be covered in shimmering stone dust... It glistens in your torch light as you examine it. It seems magical... but what does it do\?");
  self->text_description_short_set("Stone cloak.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_ITEM);
  my::tile(self, {.tile = name, .ascii_fg_char = "[", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray50"});
}

static void init(void)
{
  tp_init("cloak_stone", "cloak of stone", "cloak, stone");
}

void module_init(void)
{
  native_register("cloak_stone", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cloak_stone", "on_waiting", 3, [](const int64_t *a) -> NativeRet { (void) a; on_waiting((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("cloak_stone", "on_move", 3, [](const int64_t *a) -> NativeRet { (void) a; on_move((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_cloaks_cloak_stone
