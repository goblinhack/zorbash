//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/fungus/fungus_poison_16.py
//

#include "my_native.hpp"
#include "things/fungus/fungus_common.hpp"

namespace mod_things_fungus_fungus_poison_16 {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("bloodcrawler fungus"), std::string("b.crawler fungus"));
  mod_things_fungus_fungus_common::tp_init(self);
  self->dmg_chance_d1000_poison_set(0, 1000);
  self->dmg_poison_dice_set("1d30");
  self->is_fungus_poison_set(true);
  self->nutrition_dice_set("1d5");
  self->text_a_or_an_set("the");
  self->text_description_long_set("This mushroom has long red tendril like legs and a bloated hideous cap. Need I say more\?");
  self->text_description_short_set("An bloodcrawler mushroom.");
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "\"", .ascii_bg_col_name = "", .ascii_fg_col_name = "red"});
  }
}

static void init(void)
{
  tp_init("fungus_poison_16", std::vector< std::string >{"fungus_poison_15"});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_fungus_fungus_poison_16
