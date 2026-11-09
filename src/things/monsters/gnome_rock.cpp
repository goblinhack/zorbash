//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/gnome_rock.py
//

#include "my_native.hpp"
#include "things/monsters/gnome_all.hpp"

namespace mod_things_monsters_gnome_rock {

static void on_born(uint32_t me, int x, int y);
static void on_death_of_my_leader(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  mod_things_monsters_gnome_all::on_born(me, x, y);
  my::thing_carry(me, "gold4");
  my::thing_carry(me, "rock");
  my::thing_carry(me, "rock");
  my::thing_carry(me, "rock");
}

static void on_death_of_my_leader(uint32_t me, int x, int y)
{
  if ((! my::thing_is_dead_or_dying(me))) {
    my::thing_msg(me, "The rock gnome cries out in tiny impotent rage!");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = mod_things_monsters_gnome_all::tp_init(name, text_long_name);
  self->chance_d1000_carrier_of_treasure_class_B_set(20);
  self->dmg_nat_att_dice_set("1d6+1");
  self->dmg_nat_att_type_set("gravel");
  self->health_initial_dice_set("1d6+4");
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_daring_set(true);
  self->is_hard_set(true);
  self->is_heavy_set(true);
  self->is_made_of_rock_set(true);
  self->is_monst_class_B_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_you_nat_attack_attempt_do_set("gnome_all.on_you_nat_attack_attempt()");
  self->stat_def_set(14);
  self->stat_dex_set(6);
  self->stat_psi_set(12);
  self->stat_str_set(12);
  self->text_description_long2_set("This particular gnome is a rock gnome. Having spent so long underground, these gnomes have developed a dusty, rock like skin and a personality to match. This all makes them exceptionally tough to hit.");
  self->text_description_short_set("An granite complexioned rock gnome.");
  delay = 300;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray60", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("gnome_rock", "rock gnome");
}

void module_init(void)
{
  native_register("gnome_rock", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gnome_rock", "on_death_of_my_leader", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death_of_my_leader((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_gnome_rock
