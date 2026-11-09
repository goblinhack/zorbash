//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/fungus/fungus_edible_12.py
//

#include "my_native.hpp"
#include "things/fungus/fungus_common.hpp"

namespace mod_things_fungus_fungus_edible_12 {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("darkstar fungus"), std::string("darkstar fungus"));
  mod_things_fungus_fungus_common::tp_init(self);
  self->is_fungus_edible_set(true);
  self->nutrition_dice_set("1d12");
  self->text_a_or_an_set("the");
  self->text_description_long_set("A beautiful dark blue mushroom covered in star shaped speckles that look like stars.");
  self->text_description_short_set("A darkstar mushroom.");
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "\"", .ascii_bg_col_name = "", .ascii_fg_col_name = "darkblue"});
  }
}

static void init(void)
{
  tp_init("fungus_edible_12", std::vector< std::string >{"fungus_edible_12"});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_fungus_fungus_edible_12
