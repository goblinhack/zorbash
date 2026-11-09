//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/debuffs/debuff_temporary_immolation.py
//

#include "my_native.hpp"

namespace mod_things_debuffs_debuff_temporary_immolation {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static bool on_tick(uint32_t owner, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You immolate yourself! One in a long series of bad decisions you've made!");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You survive and are fire proof!");
  }
  my::thing_buff_add(owner, "buff_permanent_immune_to_fire");
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
  self->is_debuff_set(true);
  self->is_loggable_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d10+10");
  self->move_speed_bonus_set(100);
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->on_tick_do_set("me.on_tick()");
  self->text_description_long_set("You are on fire! Should you survive this, you'll be tougher.");
  self->text_description_short_set("You are on fire!");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "small_fire.1"});
}

static void init(void)
{
  tp_init("debuff_temporary_immolation", "immolation", "immolation");
}

void module_init(void)
{
  native_register("debuff_temporary_immolation", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("debuff_temporary_immolation", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("debuff_temporary_immolation", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_debuffs_debuff_temporary_immolation
