//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/internal/msg.py
//

#include "my_native.hpp"

namespace mod_things_internal_msg {

static void tp_init(const std::string &name);
static void init(void);

static void tp_init(const std::string &name)
{
  Tpp self = my::tp_load(name);
  self->gfx_ascii_shown_set(true);
  self->is_internal_set(true);
  self->is_loggable_set(false);
  self->is_moveable_set(true);
  self->is_msg_set(true);
  self->is_no_tile_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->is_tmp_thing_set(true);
  self->text_a_or_an_set("a");
  self->text_description_short_set("A message.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_TOP);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
}

static void init(void)
{
  tp_init("msg");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_internal_msg
