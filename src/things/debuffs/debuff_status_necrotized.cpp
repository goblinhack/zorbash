//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/debuffs/debuff_status_necrotized.py
//

#include "my_native.hpp"

namespace mod_things_debuffs_debuff_status_necrotized {

static bool on_tick(uint32_t owner, uint32_t item, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static bool on_tick(uint32_t owner, uint32_t item, int x, int y)
{
  int necrosis = 0;
  necrosis = my::thing_necrotized_amount_get(owner);
  if ((necrosis == 0)) {
    if (((owner != 0) && my::thing_is_player(owner))) {
      my::thing_msg(owner, "You are no longer unpleasant any more than usual..");
    }
    my::thing_dead(item, "end of debuff");
    return true;
  }
  return true;
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->is_debuff_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_tickable_set(true);
  self->on_tick_do_set("me.on_tick()");
  self->text_debuff_set("You are unpleasant!");
  self->text_description_long_set("Your skin is peeling off!");
  self->text_description_short_set("Rotting debuff.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "debuff_status_necrotized"});
}

static void init(void)
{
  tp_init("debuff_status_necrotized", "rotting");
}

void module_init(void)
{
  native_register("debuff_status_necrotized", "on_tick", 4, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_tick((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]), {}}; });
  init();
}

} // namespace mod_things_debuffs_debuff_status_necrotized
