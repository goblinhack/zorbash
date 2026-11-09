//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/zorb_pack.py
//

#include "my_native.hpp"
#include "things/monsters/zorb_all.hpp"

namespace mod_things_monsters_zorb_pack {

static void on_born(uint32_t me, int x, int y);
static void on_you_are_declared_leader(uint32_t me, int x, int y);
static void on_you_are_declared_a_follower(uint32_t me, uint32_t leader, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  mod_things_monsters_zorb_all::on_born(me, x, y);
}

static void on_you_are_declared_leader(uint32_t me, int x, int y)
{
  int r = 0;
  r = my::non_pcg_random_inclusive(1, 100);
  if ((r < 60)) {
    my::thing_polymorph(me, "zorb_captain");
  } else if ((r < 70)) {
    my::thing_polymorph(me, "zorb_priest");
  } else if ((r < 80)) {
    my::thing_polymorph(me, "zorb_wizard");
  } else if ((r < 90)) {
    my::thing_polymorph(me, "zorb_necro");
  } else {
    my::thing_polymorph(me, "zorb_pirate");
  }
}

static void on_you_are_declared_a_follower(uint32_t me, uint32_t leader, int x, int y)
{
  int r = 0;
  r = my::non_pcg_random_inclusive(1, 100);
  if ((r < 90)) {
    my::thing_polymorph(me, "zorb_soldier");
  } else {
    my::thing_polymorph(me, "zorb_eldster");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->gfx_ascii_shown_set(true);
  self->is_able_to_follow_set(true);
  self->is_allied_with_set("zorb_pack");
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_chasms_set(true);
  self->distance_recruitment_max_set(7);
  self->is_monst_class_B_set(true);
  self->is_loggable_set(true);
  self->is_monst_pack_set(true);
  self->is_loggable_set(true);
  self->on_you_are_declared_a_follower_do_set("me.on_you_are_declared_a_follower()");
  self->on_you_are_declared_leader_do_set("me.on_you_are_declared_leader()");
  self->spawn_group_radius_set(4);
  self->spawn_group_size_dice_set("1d4+3");
}

static void init(void)
{
  tp_init("zorb_pack", "zorblin pack");
}

void module_init(void)
{
  native_register("zorb_pack", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zorb_pack", "on_you_are_declared_leader", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_are_declared_leader((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("zorb_pack", "on_you_are_declared_a_follower", 4, [](const int64_t *a) -> NativeRet { (void) a; on_you_are_declared_a_follower((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_zorb_pack
