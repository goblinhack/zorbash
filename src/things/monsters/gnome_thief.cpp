//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/gnome_thief.py
//

#include "my_native.hpp"
#include "things/monsters/gnome_all.hpp"

namespace mod_things_monsters_gnome_thief {

static void on_born(uint32_t me, int x, int y);
static void on_death_of_my_leader(uint32_t me, int x, int y);
static void on_stealing(uint32_t me, uint32_t victim, uint32_t what, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  mod_things_monsters_gnome_all::on_born(me, x, y);
  my::thing_carry(me, "dagger");
  my::thing_carry(me, "dart");
  my::thing_carry(me, "dart");
  my::thing_carry(me, "dart");
  my::thing_carry(me, "dart");
  my::thing_carry(me, "gold3");
}

static void on_death_of_my_leader(uint32_t me, int x, int y)
{
  if ((! my::thing_is_dead_or_dying(me))) {
    my::thing_msg(me, "The gnome thief cries out in tiny impotent rage!");
  }
}

static void on_stealing(uint32_t me, uint32_t victim, uint32_t what, int x, int y)
{
  if ((my::pcg_random_inclusive(1, 100) < 100)) {
    if ((! my::thing_is_dead_or_dying(me))) {
      my::thing_msg(me, "The gnome thief cackles with glee and vanishes!");
    }
    my::thing_teleport_randomly(me);
  } else if ((! my::thing_is_dead_or_dying(me))) {
    my::thing_msg(me, "The gnome thief cackles with glee!");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  int delay = 0;
  Tpp self = mod_things_monsters_gnome_all::tp_init(name, text_long_name);
  self->chance_d1000_carrier_of_treasure_class_B_set(20);
  self->chance_d1000_steal_item_set(500);
  self->health_initial_dice_set("1d4+2");
  self->is_able_to_run_away_after_stealing_set(true);
  self->is_able_to_teleport_escape_set(true);
  self->is_biome_dungeon_set(true);
  self->is_cowardly_set(true);
  self->is_monst_class_A_set(true);
  self->on_born_do_set("me.on_born()");
  self->on_stealing_do_set("me.on_stealing()");
  self->on_you_nat_attack_attempt_do_set("gnome_all.on_you_nat_attack_attempt()");
  self->teleport_distance_set(20);
  self->text_description_long2_set("This particular gnome is very adept at liberating items from their owners.");
  self->text_description_short_set("A sneaky gnome thief.");
  delay = 300;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "g", .ascii_bg_col_name = "", .ascii_fg_col_name = "gray30", .delay_ms = delay, .is_dead = true});
}

static void init(void)
{
  tp_init("gnome_thief", "gnome thief");
}

void module_init(void)
{
  native_register("gnome_thief", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gnome_thief", "on_death_of_my_leader", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death_of_my_leader((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("gnome_thief", "on_stealing", 5, [](const int64_t *a) -> NativeRet { (void) a; on_stealing((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_gnome_thief
