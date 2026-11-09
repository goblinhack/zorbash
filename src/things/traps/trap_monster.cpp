//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/traps/trap_monster.py
//

#include "my_native.hpp"

namespace mod_things_traps_trap_monster {

static void on_death(uint32_t me, int x, int y);
static void on_activated(uint32_t me, uint32_t victim, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "pressure_plate");
  my::spawn_things_around_me(me, "random_monst_class_A", 1);
}

static void on_activated(uint32_t me, uint32_t victim, int x, int y)
{
  if (my::thing_is_player(victim)) {
    my::thing_msg(victim, "You hear a pressure plate click beneath you...");
    my::thing_msg(victim, "%%fg=red$Surprise!%%fg=reset$");
  } else {
    my::thing_msg(victim, "The pressure plate clicks...");
  }
  my::thing_popup(victim, "!!!");
  my::thing_dead(me, "activated");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->gfx_ascii_shown_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_interesting_set(true);
  self->is_loggable_set(true);
  self->is_pressure_plate_set(true);
  self->is_trap_set(true);
  self->noise_on_hit_and_now_dead_set(50);
  self->noise_on_hit_and_still_alive_set(50);
  self->normal_placement_rules_set(true);
  self->on_activated_do_set("me.on_activated()");
  self->on_death_do_set("me.on_death()");
  self->text_a_or_an_set("a");
  self->text_pluralize_set("howling floor tiles");
  self->text_apostrophize_set("howling floor tile's");
  self->text_description_short_set("A strange looking floor tile.");
  self->z_depth_set(MAP_DEPTH_FLOOR2);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "trap.1", .ascii_fg_char = "middle_dot", .ascii_fg_col_name = "darkgreen"});
  my::tile(self, {.tile = "trap.2", .ascii_fg_char = "middle_dot", .ascii_fg_col_name = "darkgreen"});
  my::tile(self, {.tile = "trap.3", .ascii_fg_char = "middle_dot", .ascii_fg_col_name = "darkgreen"});
}

static void init(void)
{
  tp_init("trap_monster", "uneven floor tile");
}

void module_init(void)
{
  native_register("trap_monster", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("trap_monster", "on_activated", 4, [](const int64_t *a) -> NativeRet { (void) a; on_activated((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_traps_trap_monster
