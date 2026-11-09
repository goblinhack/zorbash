//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/dungeon/bridge.py
//

#include "my_native.hpp"

namespace mod_things_dungeon_bridge
{

static bool collapsing = false;

static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::vector< std::string > &tiles,
                    const std::vector< std::string > &bot3_tiles);
static void init(void);

static void on_death(uint32_t me, int x, int y)
{
  my::spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor");
  if (collapsing) {
    return;
  }
  my::thing_msg(me, "The bridge collapses!");
  collapsing = true;
  for (auto bridge : my::level_flood_fill_get_all_things(me, x, y, "is_bridge")) {
    if ((bridge != me)) {
      if ((! my::thing_is_dead_or_dying(bridge))) {
        my::thing_dead(bridge, "dead");
      }
    }
  }
  collapsing = false;
}

static void tp_init(const std::string &name, const std::vector< std::string > &tiles,
                    const std::vector< std::string > &bot3_tiles)
{
  Tpp self = my::tp_load(name, std::string("bridge"));
  self->gfx_ascii_bg_color_spread_hue_set(30);
  self->gfx_ascii_shown_as_gray_in_shadow_set(true);
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_shadow_set(true);
  self->gfx_pixelart_shown_in_bg_set(true);
  self->health_initial_dice_set("20+1d10");
  self->is_able_to_fall_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_bridge_set(true);
  self->is_burnable_set(true);
  self->is_combustible_set(true);
  self->is_cursor_can_hover_over_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_flat_set(true);
  self->is_interesting_set(true);
  self->is_one_per_tile_set(true);
  self->on_death_do_set("bridge.on_death()");
  self->text_a_or_an_set("the");
  self->text_description_short_set("Shaky bridge.");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_depth_set(MAP_DEPTH_FLOOR);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  for (const auto &t : tiles) {
    my::tile(self, {.tile = t, .ascii_fg_char = "-", .ascii_bg_col_name = "brown", .ascii_fg_col_name = "black"});
  }

  for (const auto &t : bot3_tiles) {
    my::bot3_tile(self, {.tile = t});
  }
}

static void init(void)
{
  tp_init("bridge_x", std::vector< std::string > {"bridge_x"}, std::vector< std::string > {"chasm_under_bridge.1"});
  tp_init("bridge_lr",
          std::vector< std::string > {
              "bridge_lr.1",
              "bridge_lr.2",
              "bridge_lr.3",
              "bridge_lr.4",
              "bridge_lr.5",
              "bridge_lr.6",
              "bridge_lr.7",
              "bridge_lr.8",
              "bridge_lr.9",
              "bridge_lr.10",
              "bridge_lr.11",
              "bridge_lr.12",
              "bridge_lr.13",
              "bridge_lr.14",
              "bridge_lr.15",
              "bridge_lr.16",
              "bridge_lr.17",
              "bridge_lr.18",
          },
          std::vector< std::string > {
              "chasm_under_bridge.1",  "chasm_under_bridge.2",  "chasm_under_bridge.3",  "chasm_under_bridge.4",
              "chasm_under_bridge.5",  "chasm_under_bridge.6",  "chasm_under_bridge.7",  "chasm_under_bridge.8",
              "chasm_under_bridge.9",  "chasm_under_bridge.10", "chasm_under_bridge.11", "chasm_under_bridge.12",
              "chasm_under_bridge.13", "chasm_under_bridge.14", "chasm_under_bridge.15", "chasm_under_bridge.16",
              "chasm_under_bridge.17", "chasm_under_bridge.18", "chasm_under_bridge.19",
          });
  tp_init("bridge_ud",
          std::vector< std::string > {
              "bridge_ud.1",  "bridge_ud.2",  "bridge_ud.3",  "bridge_ud.4",  "bridge_ud.5",
              "bridge_ud.6",  "bridge_ud.7",  "bridge_ud.8",  "bridge_ud.9",  "bridge_ud.10",
              "bridge_ud.11", "bridge_ud.12", "bridge_ud.13", "bridge_ud.14", "bridge_ud.15",
              "bridge_ud.16", "bridge_ud.17", "bridge_ud.18", "bridge_ud.19",
          },
          std::vector< std::string > {
              "chasm_under_bridge.1",  "chasm_under_bridge.2",  "chasm_under_bridge.3",  "chasm_under_bridge.4",
              "chasm_under_bridge.5",  "chasm_under_bridge.6",  "chasm_under_bridge.7",  "chasm_under_bridge.8",
              "chasm_under_bridge.9",  "chasm_under_bridge.10", "chasm_under_bridge.11", "chasm_under_bridge.12",
              "chasm_under_bridge.13", "chasm_under_bridge.14", "chasm_under_bridge.15", "chasm_under_bridge.16",
              "chasm_under_bridge.17", "chasm_under_bridge.18", "chasm_under_bridge.19",
          });
}

void module_init(void)
{
  native_register("bridge", "on_death", 3, [](const int64_t *a) -> NativeRet {
    (void) a;
    on_death((uint32_t) a[ 0 ], (int) a[ 1 ], (int) a[ 2 ]);
    return NativeRet {};
  });
  init();
}

} // namespace mod_things_dungeon_bridge
