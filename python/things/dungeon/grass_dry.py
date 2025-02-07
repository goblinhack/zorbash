import my
import tp


def on_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    if my.thing_is_fire(hitter):
        my.spawn_at_my_position(me, "small_fire")
        my.thing_msg(me, "The dry grass burns!")
    my.place_at(me, "grass_dry_dead", x, y)


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "dry grass")
    # begin sort marker
    my.collision_hit_priority(self, 1)
    my.gfx_ascii_shown(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shadow_very_short(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_amplify_footsteps(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_grass(self, True)
    my.is_grass_dry(self, True)
    my.is_interesting(self, True)
    my.is_one_per_tile(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_hit_and_now_dead_do(self, "grass_dry.on_hit_and_now_dead()")
    my.temperature(self, 20)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "Parched grass.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)  # if you change this, change grass_tick
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self, delay_ms=300,
                ascii_fg_char="three_dots", ascii_bg_col_name="", ascii_fg_col_name="darkolivegreen2",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="grass_dry",
        tiles=[
            "grass_dry.1",
            "grass_dry.2",
            "grass_dry.3",
            "grass_dry.4",
            "grass_dry.5",
            "grass_dry.6",
            "grass_dry.7",
            "grass_dry.8",
            "grass_dry.9",
            "grass_dry.10",
            "grass_dry.11",
            "grass_dry.12",
            "grass_dry.13",
            "grass_dry.14",
            "grass_dry.15",
            "grass_dry.16",
            "grass_dry.17",
            "grass_dry.18",
        ],
    )


init()
