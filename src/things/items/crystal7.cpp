//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/items/crystal7.py
//

#include "my_native.hpp"
#include "things/items/crystal0.hpp"

namespace mod_things_items_crystal7 {

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  mod_things_items_crystal0::tp_init(self);
  self->stat_psi_bonus_set(3);
  self->text_description_long2_set("It glows beautifully in the dark and will bestow you with much needed psi bonuses.");
  self->text_description_long_set("This magical crystal is the first to collect on your long journey towards confronting Zorbash.");
  my::tile(self, {.tile = name, .ascii_fg_char = "theta", .ascii_bg_col_name = "", .ascii_fg_col_name = "white", .delay_ms = 50});
  my::tile(self, {.tile = name, .ascii_fg_char = "theta", .ascii_bg_col_name = "", .ascii_fg_col_name = "cyan", .delay_ms = 50});
}

static void init(void)
{
  tp_init("crystal7", "crystal VII", "crystal VII");
}

void module_init(void)
{
  init();
}

} // namespace mod_things_items_crystal7
