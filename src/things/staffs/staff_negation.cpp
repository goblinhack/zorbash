//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/staffs/staff_negation.py
//

#include "my_native.hpp"

namespace mod_things_staffs_staff_negation {

static void on_targeted(uint32_t me, int x, int y);
static void on_targeted_radially(uint32_t me, int x, int y);
static void on_idle(uint32_t me, int x, int y);
static void explode(uint32_t me, int x, int y);
static int on_rcv_dmg_negation(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void on_hit_and_now_dead(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_fall(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_targeted(uint32_t me, int x, int y)
{
  double distance = 0.0;
  int radius = 0;
  int x1 = 0;
  int y1_ = 0;
  radius = my::thing_effect_radius_get(me);
  for (int dx = (-radius), dx_end_ = (radius + 1); dx < dx_end_; dx += 1) {
    for (int dy = (-radius), dy_end_ = (radius + 1); dy < dy_end_; dy += 1) {
      x1 = (x + dx);
      y1_ = (y + dy);
      distance = std::pow((double) (my::ipow2((x1 - x)) + my::ipow2((y1_ - y))), (double) 0.5);
      if ((distance > (radius + 0.5))) {
        continue;
      }
      my::place_at(me, "magical_effect", x1, y1_);
      for (auto it : my::level_get_all(me, x1, y1_)) {
        if (my::thing_possible_to_attack(me, it)) {
          my::thing_hit(0, me, it);
        }
      }
    }
  }
}

static void on_targeted_radially(uint32_t me, int x, int y)
{
  double distance = 0.0;
  int radius = 0;
  int x1 = 0;
  int y1_ = 0;
  radius = my::thing_effect_radius_get(me);
  radius += 1;
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
      my::place_at(me, "magical_effect", x1, y1_);
      for (auto it : my::level_get_all(me, x1, y1_)) {
        if (my::thing_possible_to_attack(me, it)) {
          my::thing_hit(0, me, it);
        }
      }
    }
  }
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
      my::thing_msg(me, "Your staff of negation explodes.");
    } else {
      my::thing_msg(me, ((std::string("The ") + my::thing_name_get(owner) + "'s staff of negation explodes.")).c_str());
    }
  } else {
    my::thing_msg(me, "The staff of negation explodes.");
  }
  my::spawn_at_my_position(me, "explosion_major");
  my::spawn_set_fire_to_things_around_me(me, "fire");
  my::spawn_at_my_position(me, "fire");
  my::thing_dead(me, "exploded");
}

static int on_rcv_dmg_negation(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  explode(me, x, y);
  return damage;
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
  self->chance_d10000_set_on_fire_set(5000);
  self->charge_count_set(5);
  self->collision_hit_priority_set(6);
  self->dmg_chance_d1000_energy_set(1, 1000);
  self->dmg_chance_d1000_negation_set(0, 1000);
  self->dmg_energy_dice_set("1d10+10");
  self->dmg_negation_dice_set("1");
  self->dmg_num_of_attacks_set(2);
  self->effect_has_blast_radius_set(true);
  self->equip_carry_anim_set("staff_negation_carry");
  self->gfx_ascii_fade_with_dist_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->gfx_pixelart_show_highlighted_set(true);
  self->gfx_targeted_laser_set("laser_negation");
  self->gold_value_dice_set("300");
  self->health_initial_dice_set("20+1d10");
  self->is_able_to_be_reflected_set(true);
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
  self->is_value_defensive_set(1);
  self->is_value_offensive_set(1);
  self->is_wooden_set(true);
  self->item_height_set(4);
  self->item_width_set(4);
  self->noise_on_dropping_set(5);
  self->normal_placement_rules_set(true);
  self->on_fall_do_set("me.on_fall()");
  self->on_hit_and_now_dead_do_set("me.on_hit_and_now_dead()");
  self->on_idle_tick_freq_dice_set("1d200+200:me.on_idle()");
  self->on_rcv_dmg_negation_do_set("me.on_rcv_dmg_negation()");
  self->on_targeted_do_set("me.on_targeted()");
  self->on_targeted_radially_do_set("me.on_targeted_radially()");
  self->range_max_set(7);
  self->temperature_set(30);
  self->text_a_or_an_set("a");
  self->text_pluralize_set("staffs of negation");
  self->text_apostrophize_set("staff of negation's");
  self->text_description_enchant_set("+1 radius");
  self->text_description_long_set("Discharges a single blast of negation at an ungrateful recipient and their equipment...");
  self->text_description_short_set("A staff of negation.");
  self->tick_prio_set(MAP_TICK_PRIO_LOW);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_BEHIND);
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = 100});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "/", .ascii_bg_col_name = "", .ascii_fg_col_name = "purple", .delay_ms = 100});
}

static void init(void)
{
  tp_init("staff_negation", "staff of negation", "staff, negation");
}

void module_init(void)
{
  native_register("staff_negation", "on_targeted", 3, [](const int64_t *a) -> NativeRet { (void) a; on_targeted((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_negation", "on_targeted_radially", 3, [](const int64_t *a) -> NativeRet { (void) a; on_targeted_radially((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_negation", "on_idle", 3, [](const int64_t *a) -> NativeRet { (void) a; on_idle((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_negation", "explode", 3, [](const int64_t *a) -> NativeRet { (void) a; explode((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("staff_negation", "on_rcv_dmg_negation", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_rcv_dmg_negation((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  native_register("staff_negation", "on_hit_and_now_dead", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_now_dead((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("staff_negation", "on_fall", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_staffs_staff_negation
