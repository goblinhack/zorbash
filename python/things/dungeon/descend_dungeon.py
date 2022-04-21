import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.gfx_animated(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_shown_in_bg(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_critical_to_level(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_descend_dungeon(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.light_color(self, "white")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "%%fg=gold$The way down.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 50
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".1", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".2", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".3", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".4", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".5", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".6", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".7", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".8", is_dir_none=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="exit1", text_name="dungeon exit", short_text_name="exit")


init()
