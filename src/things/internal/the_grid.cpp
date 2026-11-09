//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/internal/the_grid.py
//

#include "my_native.hpp"

namespace mod_things_internal_the_grid {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(false);
  self->is_internal_set(true);
  self->is_the_grid_set(true);
  self->text_a_or_an_set("the");
  self->text_description_short_set("The grid.");
  my::tile(self, {.tile = name});
}

static void init(void)
{
  tp_init("the_grid", "ground", "ground");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_internal_the_grid
