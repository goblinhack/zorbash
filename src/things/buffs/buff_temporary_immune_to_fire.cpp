//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_temporary_immune_to_fire.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_temporary_immune_to_fire {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static int on_owner_rcv_dmg_fire(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static int on_owner_rcv_dmg_heat(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "A protective blue glow surrounds you.");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The protective blue glow around you fades.");
  }
}

static int on_owner_rcv_dmg_fire(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You take no fire damage.");
  }
  return 0;
}

static int on_owner_rcv_dmg_heat(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You take no heat damage.");
  }
  return 0;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_immune_to_fire_set(true);
  self->is_loggable_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d100+50");
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_rcv_dmg_fire_do_set("me.on_owner_rcv_dmg_fire()");
  self->on_owner_rcv_dmg_heat_do_set("me.on_owner_rcv_dmg_heat()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->text_description_long_set("You bask in the fire.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_immune_to_fire"});
}

static void init(void)
{
  tp_init("buff_temporary_immune_to_fire", "fire proof");
}

void module_init(void)
{
  native_register("buff_temporary_immune_to_fire", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_temporary_immune_to_fire", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_temporary_immune_to_fire", "on_owner_rcv_dmg_fire", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_fire((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_temporary_immune_to_fire", "on_owner_rcv_dmg_heat", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_heat((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_temporary_immune_to_fire
