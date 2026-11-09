//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/treasure/thunderstone.py
//

#include "my_native.hpp"

namespace mod_things_treasure_thunderstone {

static void explode(uint32_t me, int x, int y);
static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_fire(uint32_t me, int x, int y);
static void on_fall(uint32_t me, int x, int y);
static void on_use(uint32_t owner, uint32_t me, uint32_t target, int x, int y);
static void on_dropped(uint32_t me, int x, int y);
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
      my::thing_msg(me, "Your thunderstone explodes.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s thunderstone explodes.")).c_str());
    }
  } else {
    my::thing_msg(me, "The thunderstone explodes.");
  }
  my::spawn_at_my_position(me, "explosion_major");
  my::spawn_set_fire_to_things_around_me(me, "fire");
  my::spawn_at_my_position(me, "fire");
  my::spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor");
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

static void on_fall(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void on_use(uint32_t owner, uint32_t me, uint32_t target, int x, int y)
{
  if ((! (target != 0))) {
    return;
  }
  my::spawn_at_my_position(target, "explosion_major");
  my::spawn_using_items_radius_range(owner, me, target, "explosion_destroy_floor");
}

static void on_dropped(uint32_t me, int x, int y)
{
  my::spawn_at_my_position(me, "explosion_major");
  my::spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor");
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->collision_hit_priority_set(5);
  self->effect_has_blast_radius_set(true);
  self->effect_radius_set(4);
  self->environ_dislikes_fire_set(20);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_auto_throw_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_collectable_set(true);
  self->is_combustible_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_stone_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_C_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_used_when_thrown_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(10);
  self->normal_placement_rules_set(true);
  self->on_dropped_do_set("me.on_dropped()");
  self->on_fall_do_set("me.on_fall()");
  self->on_hit_and_now_dead_do_set("me.on_hit_and_now_dead()");
  self->on_use_do_set("me.on_use()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("thunderstones");
  self->text_apostrophize_set("thunderstone's");
  self->text_description_long_set("This most dangerous stone can devastate any are where it is thrown. Be careful where you drop it...");
  self->text_description_short_set("A harmless looking brownish stone.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "diamond_solid", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = 100});
}

static void init(void)
{
  tp_init("thunderstone", "thunderstone", "thunderstone");
}

void module_init(void)
{
  native_register("thunderstone", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("thunderstone", "on_hit_and_now_dead", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_now_dead((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("thunderstone", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("thunderstone", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("thunderstone", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("thunderstone", "on_dropped", 3, [](const int64_t *a) -> NativeRet { (void) a; on_dropped((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_treasure_thunderstone
