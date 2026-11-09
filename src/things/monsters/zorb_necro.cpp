//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/zorb_necro.py
//

#include "my_native.hpp"
#include "things/monsters/zorb_all.hpp"

namespace mod_things_monsters_zorb_necro {

static void on_born(uint32_t me, int x, int y);
static void on_death_of_a_follower(uint32_t me, uint32_t leader, int x, int y);
static bool on_tick(uint32_t owner, uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_msg(me, "Hello mortal!");
  my::thing_carry(me, "staff_energy");
  mod_things_monsters_zorb_all::on_born(me, x, y);
}

static void on_death_of_a_follower(uint32_t me, uint32_t leader, int x, int y)
{
  if ((! my::thing_is_dead_or_dying(leader))) {
    my::thing_msg(me, "The zorblin necromancer begins muttering some unknown words!");
  }
}

static bool on_tick(uint32_t owner, uint32_t me, int x, int y)
{
  std::vector< uint32_t > followers;
  int risen = 0;
  if ((my::pcg_random_inclusive(1, 100) < 90)) {
    return false;
  }
  risen = 0;
  if ((my::thing_stat_con(me) > 1)) {
    followers = my::thing_all_followers_get(me);
    if ((followers.empty())) {
      return false;
    }
    for (auto follower : followers) {
      if (my::thing_is_dead_or_dying(follower)) {
        if (my::thing_resurrect(follower, "arise")) {
          my::thing_stat_con_decr(me, 1);
          my::thing_msg(me, "Arise my minion!");
          my::thing_msg(follower, "Groan!");
          if ((my::thing_stat_con(me) <= 1)) {
            return true;
          }
          risen += 1;
        }
      }
    }
  }
  if ((risen > 0)) {
    return true;
  }
  return false;
}

static void on_death(uint32_t me, int x, int y)
{
  std::vector< uint32_t > followers;
  followers = my::thing_all_followers_get(me);
  if ((followers.empty())) {
    return;
  }
  for (auto follower : followers) {
    if (my::thing_is_resurrected_or_resurrecting(follower)) {
      my::thing_speaks(follower, "Free at last!");
      my::thing_perma_death(follower, "Leader died!");
    }
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = mod_things_monsters_zorb_all::tp_init(name, text_long_name);
  self->chance_d1000_carrier_of_treasure_class_C_set(1000);
  self->chance_d1000_shooting_set(500);
  self->distance_avoid_set(5);
  self->environ_hates_fire_set(100);
  self->environ_hates_water_set(100);
  self->health_initial_dice_set("2d3+4");
  self->is_able_to_use_rings_set(true);
  self->is_able_to_use_staffs_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_cowardly_set(true);
  self->is_intelligent_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_B_set(true);
  self->is_zorblin_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_death_do_set("me.on_death()");
  self->on_death_of_a_follower_do_set("me.on_death_of_a_follower()");
  self->on_tick_do_set("me.on_tick()");
  self->on_you_nat_attack_attempt_do_set("zorb_all.on_you_nat_attack_attempt()");
  self->stat_dex_set(6);
  self->stat_int_set(14);
  self->stat_luck_set(6);
  self->stat_psi_set(14);
  self->stat_str_set(6);
  self->text_description_long2_set("This particular zorblin is learned in the dark arts. Withered of body, but sharp of mind, beware the abilities of this zorblin.");
  self->text_description_short_set("A master of the darkest arts.");
  delay = 300;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 1});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 2});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 3});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 4});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 5});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 6});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "Z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 1, .is_sleeping = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "green", .delay_ms = delay, .frame = 2, .is_sleeping = true});
  my::tile(self, {.tile = (name + ".dead.1"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.2"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.3"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.4"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
  my::tile(self, {.tile = (name + ".dead.5"), .ascii_fg_char = "z", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .is_dead = true, .is_end_of_anim = true});
}

static void init(void)
{
  tp_init("zorb_necro", "zorblomancer");
}

void module_init(void)
{
  native_register("zorb_necro", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zorb_necro", "on_death_of_a_follower", 4, [](const int64_t *a) -> NativeRet { (void) a; on_death_of_a_follower((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("zorb_necro", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  native_register("zorb_necro", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_zorb_necro
