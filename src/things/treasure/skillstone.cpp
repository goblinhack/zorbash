//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/treasure/skillstone.py
//

#include "my_native.hpp"

namespace mod_things_treasure_skillstone {

static void explode(uint32_t me, int x, int y);
static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_fire(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void explode(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  if (my::thing_is_dead(me)) {
    return;
  }
  owner = my::thing_top_owner_id_get(me);
  if ((owner != 0)) {
    if (my::thing_is_player(owner)) {
      my::thing_msg(me, "Your skillstone explodes.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s skillstone explodes.")).c_str());
    }
  } else {
    my::thing_msg(me, "The skillstone explodes.");
  }
  my::spawn_at_my_position(me, "explosion_major");
  my::spawn_set_fire_to_things_around_me(me, "fire");
  my::spawn_at_my_position(me, "fire");
  my::thing_dead(me, "exploded");
}

static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  explode(me, x, y);
}

static void on_fire(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_hit_priority_set(5);
  self->environ_dislikes_fire_set(10);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gold_value_dice_set("500");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
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
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_magic_stone_set(true);
  self->is_moveable_set(true);
  self->is_skillstone_set(true);
  self->is_stone_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(10);
  self->normal_placement_rules_set(true);
  self->on_hit_and_now_dead_do_set("me.on_hit_and_now_dead()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("skillstones");
  self->text_apostrophize_set("skillstone's");
  self->text_description_long_set("Use this magical stone to learn some new skills into your brain matter thing.");
  self->text_description_short_set("A glowing skillstone.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "diamond_solid", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = 100});
}

static void init(void)
{
  tp_init("skillstone", "skillstone", "skillstone");
}

void module_init(void)
{
  native_register("skillstone", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("skillstone", "on_hit_and_now_dead", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_now_dead((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("skillstone", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_treasure_skillstone
