//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_immune_to_poison.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_immune_to_poison {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static bool on_tick(uint32_t owner, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "A green glow surrounds you.");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The green glow around you fades.");
  }
}

static int on_owner_rcv_dmg_poison(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You take half damage from the poison.");
  }
  return ((int) (((double) damage / (double) 2)));
}

static bool on_tick(uint32_t owner, uint32_t item, int x, int y)
{
  int new_poison = 0;
  int poison = 0;
  poison = my::thing_poisoned_amount_get(item);
  if ((poison == 0)) {
    return false;
  }
  new_poison = ((int) (((double) poison / (double) 2)));
  if (((owner != 0) && my::thing_is_player(owner))) {
    if ((new_poison == 0)) {
      my::thing_msg(owner, "%%fg=green$The poison has little effect on you!%%fg=reset$");
    } else {
      my::thing_msg(owner, "%%fg=green$The poison fades from your system!%%fg=reset$");
    }
  }
  my::thing_poisoned_amount_set(owner, new_poison);
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_immune_to_poison_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_runic_defensive_class_A_set(true);
  self->is_tickable_set(true);
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_rcv_dmg_poison_do_set("me.on_owner_rcv_dmg_poison()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->on_tick_do_set("me.on_tick()");
  self->text_description_long_set("Poison causes you 50 percent less damage.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_immune_to_poison"});
}

static void init(void)
{
  tp_init("buff_permanent_immune_to_poison", "poison immunity");
}

void module_init(void)
{
  native_register("buff_permanent_immune_to_poison", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_permanent_immune_to_poison", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_permanent_immune_to_poison", "on_owner_rcv_dmg_poison", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_poison((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  native_register("buff_permanent_immune_to_poison", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_permanent_immune_to_poison
