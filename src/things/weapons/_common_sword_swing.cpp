//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/weapons/_common_sword_swing.py
//

#include "my_native.hpp"
#include "things/weapons/_common_sword_swing.hpp"

namespace mod_things_weapons__common_sword_swing {

void init(Tpp self, const std::string &name)
{
  int delay = 0;
  self->gfx_pixelart_show_outlined_set(true);
  self->is_loggable_set(true);
  self->is_moveable_set(true);
  self->is_removable_if_out_of_slots_set(true);
  self->text_a_or_an_set("a");
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_SWING);
  delay = 20;
  my::tile(self, {.tile = (name + "_left.1"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + "_left.2"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + "_left.3"), .ascii_fg_char = "\\", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + "_left.4"), .ascii_fg_char = "-", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + "_left.5"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_none = true});
  my::tile(self, {.tile = (name + "_left.6"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_none = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  delay = 20;
  my::tile(self, {.tile = (name + "_left.1"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + "_left.2"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + "_left.3"), .ascii_fg_char = "\\", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + "_left.4"), .ascii_fg_char = "-", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + "_left.5"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_left = true});
  my::tile(self, {.tile = (name + "_left.6"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_left = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + "_left.1"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + "_left.2"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + "_left.3"), .ascii_fg_char = "\\", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + "_left.4"), .ascii_fg_char = "-", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + "_left.5"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_right = true});
  my::tile(self, {.tile = (name + "_left.6"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_right = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + "_up.1"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + "_up.2"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + "_up.3"), .ascii_fg_char = "\\", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + "_up.4"), .ascii_fg_char = "-", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + "_up.5"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_up = true});
  my::tile(self, {.tile = (name + "_up.6"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_up = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
  my::tile(self, {.tile = (name + "_up.1"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + "_up.2"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + "_up.3"), .ascii_fg_char = "\\", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + "_up.4"), .ascii_fg_char = "-", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + "_up.5"), .ascii_fg_char = "/", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_down = true});
  my::tile(self, {.tile = (name + "_up.6"), .ascii_fg_char = "|", .ascii_fg_col_name = "cyan", .delay_ms = delay, .is_dir_down = true, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

void module_init(void)
{
}

} // namespace mod_things_weapons__common_sword_swing
