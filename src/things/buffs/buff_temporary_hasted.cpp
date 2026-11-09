//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_temporary_hasted.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_temporary_hasted {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static bool on_tick(uint32_t owner, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You feel speedy.");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You feel sluggish again.");
  }
}

static bool on_tick(uint32_t owner, uint32_t item, int x, int y)
{
  int roll = 0;
  roll = d100();
  if ((roll < 25)) {
    my::thing_stamina_decr(owner, 1);
  }
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_loggable_set(true);
  self->is_runic_defensive_class_A_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d100+50");
  self->move_speed_bonus_set(100);
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->on_tick_do_set("me.on_tick()");
  self->text_description_long2_set("Watch out, your stamina will drop fast with this.");
  self->text_description_long_set("With this ability you can zip around the dungeon and die even quicker!");
  self->text_description_short_set("You are as fast as lightning. Slow lightning that is.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_hasted"});
}

static void init(void)
{
  tp_init("buff_temporary_hasted", "quicksilver", "hasted");
}

void module_init(void)
{
  native_register("buff_temporary_hasted", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_temporary_hasted", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_temporary_hasted", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_temporary_hasted
