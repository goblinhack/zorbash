//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_immune_to_negation.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_immune_to_negation {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y);
static int on_owner_rcv_dmg_negation(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "A protective negative glow surrounds you.");
  }
}

static void on_owner_unset(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "The protective negative glow around you fades.");
  }
}

static int on_owner_rcv_dmg_negation(uint32_t me, uint32_t owner, uint32_t hitter, uint32_t real_hitter, int x, int y, int damage)
{
  if (my::thing_is_player(me)) {
    my::thing_msg(me, "You take no damage from the negation.");
  }
  return 0;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_immune_to_negation_set(true);
  self->is_loggable_set(true);
  self->is_runic_defensive_class_A_set(true);
  self->on_owner_add_do_set("me.on_owner_add()");
  self->on_owner_rcv_dmg_negation_do_set("me.on_owner_rcv_dmg_negation()");
  self->on_owner_unset_do_set("me.on_owner_unset()");
  self->text_description_long_set("You cannot be negated.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_immune_to_negation"});
}

static void init(void)
{
  tp_init("buff_permanent_immune_to_negation", "negation proof");
}

void module_init(void)
{
  native_register("buff_permanent_immune_to_negation", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_permanent_immune_to_negation", "on_owner_unset", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_unset((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  native_register("buff_permanent_immune_to_negation", "on_owner_rcv_dmg_negation", 7, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_rcv_dmg_negation((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (uint32_t) a[3], (int) a[4], (int) a[5], (int) a[6]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_permanent_immune_to_negation
