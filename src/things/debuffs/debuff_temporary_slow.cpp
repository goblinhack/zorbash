//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/debuffs/debuff_temporary_slow.py
//

#include "my_native.hpp"

namespace mod_things_debuffs_debuff_temporary_slow {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static bool on_tick(uint32_t owner, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You feel sluggish.");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You feel less sluggish again.");
  }
}

static bool on_tick(uint32_t owner, uint32_t item, int x, int y)
{
  my::thing_stamina_incr(owner, 2);
  my::thing_health_incr(owner, 2);
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_debuff_set(true);
  self->is_loggable_set(true);
  self->is_tickable_set(true);
  self->lifespan_dice_set("1d30+10");
  self->move_speed_bonus_set((-50));
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->on_tick_do_set("me.on_tick()");
  self->text_description_long2_set("One plus side is that you will heal and recover faster from this enforced rest.");
  self->text_description_long_set("You feel even more sluggish than normal.");
  self->text_description_short_set("You are being slowed.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "debuff_slow"});
}

static void init(void)
{
  tp_init("debuff_temporary_slow", "sluggishly slow", "slowed");
}

void module_init(void)
{
  native_register("debuff_temporary_slow", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("debuff_temporary_slow", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("debuff_temporary_slow", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_debuffs_debuff_temporary_slow
