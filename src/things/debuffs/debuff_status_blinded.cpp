//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/debuffs/debuff_status_blinded.py
//

#include "my_native.hpp"

namespace mod_things_debuffs_debuff_status_blinded {

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void on_owner_add(uint32_t me, uint32_t owner, int x, int y)
{
  if (((owner != 0) && my::thing_is_player(owner))) {
    my::thing_msg(me, "You are blinded!");
  }
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_debuff_set(true);
  self->is_loggable_set(true);
  self->on_owner_add_do_set("me.on_owner_add()");
  self->text_description_long_set("You are blinded!");
  self->text_description_short_set("You are blinded.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  my::tile(self, {.tile = "debuff_status_blinded"});
}

static void init(void)
{
  tp_init("debuff_status_blinded", "blinded", "blinded");
}

void module_init(void)
{
  native_register("debuff_status_blinded", "on_owner_add", 4, [](const int64_t *a) -> NativeRet { (void) a; on_owner_add((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_debuffs_debuff_status_blinded
