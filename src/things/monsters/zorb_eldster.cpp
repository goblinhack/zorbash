//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/zorb_eldster.py
//

#include "my_native.hpp"
#include "things/monsters/zorb_all.hpp"

namespace mod_things_monsters_zorb_eldster {

static void on_born(uint32_t me, int x, int y);
static void on_death_of_a_follower(uint32_t me, uint32_t leader, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  mod_things_monsters_zorb_all::on_born(me, x, y);
}

static void on_death_of_a_follower(uint32_t me, uint32_t leader, int x, int y)
{
  if ((! my::thing_is_dead_or_dying(me))) {
    my::thing_msg(me, "The zorblin eldster cries out in rage!");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = mod_things_monsters_zorb_all::tp_init(name, text_long_name);
  self->chance_d1000_carrier_of_treasure_class_B_set(200);
  self->chance_d1000_carrier_of_weapon_class_A_set(400);
  self->health_initial_dice_set("2d5");
  self->is_able_to_freeze_set(true);
  self->is_able_to_use_weapons_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_loggable_set(true);
  self->is_monst_class_B_set(true);
  self->is_zorblin_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_death_of_a_follower_do_set("me.on_death_of_a_follower()");
  self->on_you_nat_attack_attempt_do_set("zorb_all.on_you_nat_attack_attempt()");
  self->stat_psi_set(8);
  self->stat_str_set(8);
  self->text_description_long2_set("This zorblin is world weary and longing for an early retirement. Can you help\?");
  self->text_description_short_set("A very war-weary zoblin.");
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
  tp_init("zorb_eldster", "zorblin eldster");
}

void module_init(void)
{
  native_register("zorb_eldster", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zorb_eldster", "on_death_of_a_follower", 4, [](const int64_t *a) -> NativeRet { (void) a; on_death_of_a_follower((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_zorb_eldster
