//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/fungus/fungus_withered_10.py
//

#include "my_native.hpp"
#include "things/fungus/fungus_common_withered.hpp"

namespace mod_things_fungus_fungus_withered_10 {

static void tp_init(const std::string &name, const std::vector< std::string > &tiles);
static void init(void);

static void tp_init(const std::string &name, const std::vector< std::string > &tiles)
{
  Tpp self = my::tp_load(name, std::string("withered fungus"), std::string("withered fungus"));
  mod_things_fungus_fungus_common_withered::tp_init(self);
  self->is_fungus_withered_set(true);
  self->text_a_or_an_set("the");
  self->text_description_long2_set("When even the mushrooms die, you know this is not the place to be...");
  self->text_description_long_set("A dry husk of a mushroom.");
  self->text_description_short_set("A withered mushroom.");
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "\"", .ascii_bg_col_name = "", .ascii_fg_col_name = "brown"});
  }
}

static void init(void)
{
  tp_init("fungus_withered_10", std::vector< std::string >{"fungus_withered_10"});
}

void module_init(void)
{
  init();
}

} // namespace mod_things_fungus_fungus_withered_10
