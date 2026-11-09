//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_status_full.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_status_full {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_loggable_set(true);
  self->text_description_long2_set("However, if you become hungry or starved, you will lose points on attack and defense and other abilities may also be impacted.");
  self->text_description_long3_set("Best to keep food at hand.");
  self->text_description_long_set("Hunger does not kill in this game.");
  self->text_description_short_set("You are satiated.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  my::tile(self, {.tile = "buff_status_full"});
}

static void init(void)
{
  tp_init("buff_status_full", "full and happy", "full");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_buffs_buff_status_full
