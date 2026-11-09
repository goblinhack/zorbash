//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/holy_water.py
//

#include "my_native.hpp"

namespace mod_things_items_holy_water {

static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y);
static void shatters(uint32_t me, int x, int y);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_fire(uint32_t me, int x, int y);
static void on_fall(uint32_t me, int x, int y);
static void on_enchant(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  shatters(me, x, y);
}

static void on_use(uint32_t owner, uint32_t item, uint32_t target, int x, int y)
{
  bool did_something = false;
  int enchant = 0;
  int health = 0;
  int new_health = 0;
  int new_stamina = 0;
  int stamina = 0;
  did_something = false;
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, "potion");
  enchant = my::thing_enchant_count_get(item);
  health = my::thing_health(owner);
  new_health = ((int) (((((double) ((double) (my::thing_health_max(owner))) / (double) 100.0) * 10.0) + (enchant * 10.0))));
  if ((new_health > health)) {
    did_something = true;
    my::thing_health_set(owner, new_health);
  }
  stamina = my::thing_stamina(owner);
  new_stamina = ((int) (((((double) ((double) (my::thing_stamina_max(owner))) / (double) 100.0) * 10.0) + (enchant * 10.0))));
  if ((new_stamina > stamina)) {
    did_something = true;
    my::thing_stamina_set(owner, new_stamina);
  }
  if ((my::thing_poisoned_amount_get(owner) != 0)) {
    did_something = true;
    my::thing_poisoned_amount_set(owner, 0);
  }
  if (did_something) {
    my::spawn_using_items_radius_range(owner, item, target, "potion_effect");
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, "%%fg=pink$You glow with holiness, however you define that.%%fg=reset$");
    }
  } else if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(owner, "Hmm. The holy water didn't seem to do anything.");
  }
}

static void shatters(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  int selection_x = 0;
  int selection_y = 0;
  if (my::thing_is_dead(me)) {
    return;
  }
  owner = my::thing_top_owner_id_get(me);
  if ((owner != 0)) {
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(me, "Your beaker of holy water shatters.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s beaker of holy water shatters.")).c_str());
    }
  } else {
    my::thing_msg(me, "The beaker of holy water shatters.");
  }
  { auto pair61_ = my::thing_coords_get(me); selection_x = pair61_.first; selection_y = pair61_.second; }
  for (auto it : my::level_get_all(me, selection_x, selection_y)) {
    if (my::thing_is_undead(it)) {
      my::thing_hit_dmg_energy(owner, me, it, my::pcg_random_inclusive(10, 20));
      my::spawn_at_my_position(me, "explosion_fire");
    }
  }
  my::spawn_at_my_position(me, "water");
  my::thing_dead(me, "broken");
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  shatters(me, x, y);
}

static void on_fire(uint32_t me, int x, int y)
{
  shatters(me, x, y);
}

static void on_fall(uint32_t me, int x, int y)
{
  shatters(me, x, y);
}

static void on_enchant(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  owner = my::thing_top_owner_id_get(me);
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The holy water shimmers.");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->chance_d10000_set_on_fire_set(5000);
  self->chance_d1000_appearing_set(10);
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_pixelart_submergible_set(true);
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
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_food_set(true);
  self->is_holy_set(true);
  self->is_holy_water_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_throwable_set(true);
  self->is_treasure_class_A_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->item_height_set(3);
  self->item_width_set(3);
  self->noise_on_dropping_set(55);
  self->normal_placement_rules_set(true);
  self->nutrition_dice_set("1d1");
  self->on_enchant_do_set("me.on_enchant()");
  self->on_fall_do_set("me.on_fall()");
  self->on_hit_and_still_alive_do_set("me.on_hit_and_still_alive()");
  self->on_thrown_do_set("me.on_thrown()");
  self->on_use_do_set("me.on_use()");
  self->on_you_are_on_fire_do_set("me.on_fire()");
  self->rarity_set(THING_RARITY_RARE);
  self->stat_luck_bonus_set(2);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("beakers of holy water");
  self->text_apostrophize_set("beaker of holy water's");
  self->text_description_enchant_set("+1 LUCK");
  self->text_description_long2_set("Ideal for those undead visitors that refuse to go away.");
  self->text_description_long_set("A beaker of holy water. Quite how it got here and managed to be blessed in this accursed place is beyond me.");
  self->text_description_short_set("A beaker of holy water.");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = name, .ascii_fg_char = "halo", .ascii_bg_col_name = "", .ascii_fg_col_name = "yellow", .delay_ms = 100});
}

static void init(void)
{
  tp_init("holy_water", "beaker of holy water", "holy water");
}

void module_init(void)
{
  native_register("holy_water", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("holy_water", "on_use", 5, [](const int64_t *a) -> NativeRet { (void) a; on_use((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  native_register("holy_water", "shatters", 3, [](const int64_t *a) -> NativeRet { (void) a; shatters((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("holy_water", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("holy_water", "on_fire", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fire((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("holy_water", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("holy_water", "on_enchant", 3, [](const int64_t *a) -> NativeRet { (void) a; on_enchant((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_items_holy_water
