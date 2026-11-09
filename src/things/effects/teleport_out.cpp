//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/effects/teleport_out.py
//

#include "my_native.hpp"

namespace mod_things_effects_teleport_out {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_EXPLOSION, "teleport");
}

static void tp_init(const std::string &name)
{
  int delay = 0;
  Tpp self = my::tp_load(name, std::string("teleport_out"));
  self->dmg_chance_d1000_cold_set(0, 1000);
  self->dmg_cold_dice_set("2d6");
  self->dmg_nat_att_type_set("telefreeze");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shadow_short_set(true);
  self->is_floating_set(true);
  self->is_loggable_set(true);
  self->is_one_per_tile_set(true);
  self->light_color_set("cyan");
  self->light_dist_set(2);
  self->noise_on_born_set(100);
  self->noise_on_born_set(50);
  self->on_born_do_set("me.on_born()");
  self->text_hits_set("freezes");
  self->tick_prio_set(MAP_TICK_PRIO_VERY_HIGH);
  self->z_depth_set(MAP_DEPTH_TOP);
  self->z_prio_set(MAP_Z_PRIO_EFFECT);
  delay = 5;
  my::tile(self, {.tile = (name + ".1"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".2"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".3"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".4"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".5"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".6"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".7"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".8"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".9"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".10"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".11"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".12"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".13"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".14"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".15"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".16"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".17"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".18"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".19"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".20"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".21"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".22"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".23"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".24"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".25"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".26"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".27"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".28"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".29"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".30"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".31"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".32"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".33"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".34"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".35"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".36"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".37"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".38"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".39"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".40"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".41"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".42"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".43"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".44"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".45"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".46"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".47"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".48"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".49"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".50"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".51"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".52"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".53"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".54"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".55"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".56"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".57"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".58"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".59"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".60"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".61"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".62"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".63"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay});
  my::tile(self, {.tile = (name + ".64"), .ascii_bg_char = "block", .ascii_bg_col_name = "purple", .ascii_fg_col_name = "", .delay_ms = delay, .is_end_of_anim = true, .is_dead_on_end_of_anim = true});
}

static void init(void)
{
  tp_init("teleport_out");
}

void module_init(void)
{
  native_register("teleport_out", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_effects_teleport_out
