//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/gnome_dwarf.py
//

#include "my_native.hpp"
#include "things/monsters/gnome_all.hpp"

namespace mod_things_monsters_gnome_dwarf {

static void on_born(uint32_t me, int x, int y);
static void on_death_of_my_leader(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  mod_things_monsters_gnome_all::on_born(me, x, y);
  my::thing_carry(me, "gold4");
}

static void on_death_of_my_leader(uint32_t me, int x, int y)
{
  if ((! my::thing_is_dead_or_dying(me))) {
    my::thing_msg(me, "The gnorf cries out in tiny impotent rage!");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = mod_things_monsters_gnome_all::tp_init(name, text_long_name);
  self->chance_d1000_carrier_of_treasure_class_B_set(20);
  self->dmg_nat_att_dice_set("1d4+1");
  self->dmg_nat_att_type_set("chop");
  self->health_initial_dice_set("1d6+4");
  self->is_able_to_run_away_after_stealing_set(true);
  self->is_able_to_teleport_escape_set(true);
  self->is_biome_dungeon_set(true);
  self->is_daring_set(true);
  self->is_monst_class_A_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_you_nat_attack_attempt_do_set("gnome_all.on_you_nat_attack_attempt()");
  self->stat_def_set(12);
  self->stat_dex_set(8);
  self->stat_luck_set(10);
  self->stat_psi_set(12);
  self->stat_str_set(8);
  self->stat_thv_set(14);
  self->text_description_long2_set("This particular gnome is a dwarfish gnome hybrid. How did this come about\? Best not to ask. As a result, this gnome prefers the use of a small axe.");
  self->text_description_long3_set("Gnorfs are stouter and far stronger than normal gnomes with excellent defensive and offensive abilities. Do not underestimate them and definitely do not laugh at their red hats. The red is blood.");
  self->text_description_short_set("A stalwart gnorf.");
  delay = 300;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "red", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("gnome_dwarf", "gnorf");
}

void module_init(void)
{
  native_register("gnome_dwarf", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gnome_dwarf", "on_death_of_my_leader", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death_of_my_leader((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_gnome_dwarf
