//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/debuffs/debuff_status_confused.py
//

#include "my_native.hpp"

namespace mod_things_debuffs_debuff_status_confused {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_debuff_set(true);
  self->is_loggable_set(true);
  self->text_description_long_set("You are confused and may be unable to walk in a straight line!");
  self->text_description_short_set("You are confused. More so.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  my::tile(self, {.tile = "debuff_status_confused"});
}

static void init(void)
{
  tp_init("debuff_status_confused", "confusion", "confusion");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_debuffs_debuff_status_confused
