//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/fungus/fungus_poison_11.py
//

#include "my_native.hpp"
#include "things/fungus/fungus_common.hpp"

namespace mod_things_fungus_fungus_poison_11 {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("toblerungus"), std::string("toblerungus"));
  mod_things_fungus_fungus_common::tp_init(self);
  self->dmg_chance_d1000_poison_set(0, 1000);
  self->dmg_poison_dice_set("1d3");
  self->is_fungus_poison_set(true);
  self->nutrition_dice_set("1d20");
  self->text_a_or_an_set("the");
  self->text_description_long_set("Looks like a pyramid shaped chunk of chocolate in mushroom form");
  self->text_description_short_set("An enormous dark chocolate mushroom.");
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "\"", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown"});
  }
}

static void init(void)
{
  tp_init("fungus_poison_11", std::vector< std::string >{"fungus_poison_11"});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_fungus_fungus_poison_11
