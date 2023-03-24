import my
import tp


def on_get_text_description_long(owner, me, x, y):
    if my.thing_level_get(me) == 1:
        return ["This imposing doorway leads back to freedom from the terrible dungeon you find yourself in.",
                "Why are you here? Good question. Something involving a bet, copious amounts of liquid, seven ferrets and an ungodly desire to rid the world of a terrible evil of some kind.",
                "The door will likely remain barred until you return here with the Orb of Zorb..."]
    else:
        return ["This imposing doorway leads up to the previous level."]


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_show_square_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_ascend_dungeon(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_critical_to_level(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 3)
    my.normal_placement_rules(self, True)
    my.on_get_text_description_long_do(self, "me.on_get_text_description_long()")
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "%%fg=gold$The way up.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 1000
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1.open", delay_ms=delay, is_open=True)
    my.tile(self,
            ascii_fg_char="omega", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2.open", delay_ms=delay, is_open=True)

    my.tp_update(self)


def init():
    tp_init(name="ascend_dungeon", text_long_name="dungeon entrance", text_short_name="entrance")


init()
