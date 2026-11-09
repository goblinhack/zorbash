//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_raging.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_raging {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_loggable_set(true);
  self->text_description_long2_set("Your stamina will decrease faster than normal while raging.");
  self->text_description_long_set("You are currently raging and deal more damage with more chance of hitting");
  self->text_description_short_set("You are satiated.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  my::tile(self, {.tile = "buff_raging"});
}

static void init(void)
{
  tp_init("buff_permanent_raging", "raging mad", "raging");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_buffs_buff_permanent_raging
