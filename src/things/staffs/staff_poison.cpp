//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/staffs/staff_poison.py
//

#include "my_native.hpp"

namespace mod_things_staffs_staff_poison {

static void on_targeted(uint32_t me, int x, int y);
static void on_targeted_radially(uint32_t me, int x, int y);
static void on_idle(uint32_t me, int x, int y);
static void explode(uint32_t me, int x, int y);
static void on_thrown(uint32_t owner, uint32_t me, int x, int y);
static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_fall(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_targeted(uint32_t me, int x, int y)
{
  double distance = 0.0;
  bool got_one = false;
  uint32_t owner = 0;
  int radius = 0;
  int roll = 0;
  int x1 = 0;
  int y1_ = 0;
  radius = my::thing_effect_radius_get(me);
  owner = my::thing_top_owner_id_get(me);
  roll = d20();
  for (int dx = (-radius), dx_end_ = (radius + 1); dx < dx_end_; dx += 1) {
    for (int dy = (-radius), dy_end_ = (radius + 1); dy < dy_end_; dy += 1) {
      x1 = (x + dx);
      y1_ = (y + dy);
      distance = std::pow((double) (my::ipow2((x1 - x)) + my::ipow2((y1_ - y))), (double) 0.5);
      if ((distance > (radius + 0.5))) {
        continue;
      }
      got_one = false;
      for (auto it : my::level_get_all(me, x1, y1_)) {
        if (my::thing_possible_to_attack(me, it)) {
          my::spawn_gas_poison_around_thing(it, 1);
          my::thing_hit_dmg_poison(owner, me, it, roll);
          got_one = true;
          break;
        }
      }
      if ((! got_one)) {
        for (auto it : my::level_get_all(me, x1, y1_)) {
          my::spawn_gas_poison_around_thing(it, 1);
          my::thing_hit_dmg_poison(owner, me, it, roll);
          break;
        }
      }
    }
  }
  my::thing_sound_play_channel(me, CHANNEL_EXPLOSION, "explosion_b");
}

static void on_targeted_radially(uint32_t me, int x, int y)
{
  double distance = 0.0;
  uint32_t owner = 0;
  int radius = 0;
  int roll = 0;
  int x1 = 0;
  int y1_ = 0;
  radius = my::thing_effect_radius_get(me);
  radius += 1;
  owner = my::thing_top_owner_id_get(me);
  roll = d20();
  for (int dx = (-radius), dx_end_ = (radius + 1); dx < dx_end_; dx += 1) {
    for (int dy = (-radius), dy_end_ = (radius + 1); dy < dy_end_; dy += 1) {
      if (((dx == 0) && (dy == 0))) {
        continue;
      }
      x1 = (x + dx);
      y1_ = (y + dy);
      distance = std::pow((double) (my::ipow2((x1 - x)) + my::ipow2((y1_ - y))), (double) 0.5);
      if ((distance > (radius + 0.5))) {
        continue;
      }
      for (auto it : my::level_get_all(me, x1, y1_)) {
        if (my::thing_possible_to_attack(me, it)) {
          my::spawn_gas_poison_around_thing(it, 1);
          my::thing_hit_dmg_poison(owner, me, it, roll);
        }
      }
    }
  }
  my::thing_sound_play_channel(me, CHANNEL_EXPLOSION, "explosion_b");
}

static void on_idle(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  if ([&]() { auto t1_0_ = my::thing_charge_count(me); auto t1_1_ = my::thing_initial_charge_count(me); return (t1_0_ < t1_1_); }()) {
    my::thing_charge_count_incr(me, 1);
    owner = my::thing_top_owner_id_get(me);
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(me, ((std::string("%%fg=orange$The ") + my::thing_name_get(me) + " pulses.%%fg=reset$")).c_str());
    }
  }
}

static void explode(uint32_t me, int x, int y)
{
  uint32_t owner = 0;
  if ((my::thing_charge_count(me) == 0)) {
    return;
  }
  if (my::thing_is_dead(me)) {
    return;
  }
  owner = my::thing_top_owner_id_get(me);
  if ((owner != 0)) {
    if (my::thing_is_player(owner)) {
      my::thing_msg(me, "Your staff of poison explodes.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s staff of poison explodes.")).c_str());
    }
  } else {
    my::thing_msg(me, "The staff of poison explodes.");
  }
  my::spawn_at_my_position(me, "explosion_major");
  on_targeted(me, x, y);
  my::thing_dead(me, "exploded");
}

static void on_thrown(uint32_t owner, uint32_t me, int x, int y)
{
  if ((my::thing_charge_count(me) == 0)) {
    return;
  }
  if (my::level_is_chasm_at(me, x, y)) {
    return;
  }
  if (my::level_is_water_at(me, x, y)) {
    return;
  }
  explode(me, x, y);
}

static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  explode(me, x, y);
}

static void on_fall(uint32_t me, int x, int y)
{
  explode(me, x, y);
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->chance_d10000_enchanted_set(20);
  self->charge_count_set(5);
  self->collision_hit_priority_set(6);
  self->effect_has_blast_radius_set(true);
  self->equip_carry_anim_set("staff_poison_carry");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_targeted_projectile_set("staff_projectile_poison");
  self->gold_value_dice_set("300");
  self->health_initial_dice_set("20+1d10");
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_fall_set(true);
  self->is_bag_item_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_swamp_set(true);
  self->is_burnable_set(true);
  self->is_collectable_set(true);
  self->is_combustible_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_droppable_set(true);
  self->is_enchantable_set(true);
  self->is_immune_to_poison_set(true);
  self->is_interesting_set(true);
  self->is_item_set(true);
  self->is_loggable_set(true);
  self->is_magical_set(true);
  self->is_staff_set(true);
  self->is_target_radial_set(true);
  self->is_target_select_set(true);
  self->is_throwable_set(true);
  self->is_tickable_set(true);
  self->is_treasure_class_B_set(true);
  self->is_treasure_set(true);
  self->is_treasure_type_set(true);
  self->is_usable_set(true);
  self->is_value_offensive_set(1);
  self->is_wooden_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(5);
  self->normal_placement_rules_set(true);
  self->on_fall_do_set("me.on_fall()");
  self->on_hit_and_now_dead_do_set("me.on_hit_and_now_dead()");
  self->on_idle_tick_freq_dice_set("1d200+200:me.on_idle()");
  self->on_targeted_do_set("me.on_targeted()");
  self->on_targeted_radially_do_set("me.on_targeted_radially()");
  self->on_thrown_do_set("me.on_thrown()");
  self->range_max_set(7);
  self->temperature_set((-10));
  self->text_a_or_an_set("a");
  self->text_pluralize_set("staffs of poison");
  self->text_apostrophize_set("staff of poison's");
  self->text_description_enchant_set("+1 radius");
  self->text_description_long_set("Discharges a blast of intense poison at an ungrateful recipient...");
  self->text_description_short_set("A staff of poison.");
  self->tick_prio_set(MAP_TICK_PRIO_LOW);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "limegreen", .delay_ms = 100});
}

static void init(void)
{
  tp_init("staff_poison", "staff of poison", "staff, poison");
}

void module_init(void)
{
  native_register("staff_poison", "on_targeted", 3, [](const int64_t *a) -> NativeRet { (void) a; on_targeted((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_poison", "on_targeted_radially", 3, [](const int64_t *a) -> NativeRet { (void) a; on_targeted_radially((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_poison", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_poison", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_poison", "on_thrown", 4, [](const int64_t *a) -> NativeRet { (void) a; on_thrown((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("staff_poison", "on_hit_and_now_dead", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_now_dead((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("staff_poison", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_staffs_staff_poison
