import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_shown_in_bg(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_critical_to_level(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_descend_dungeon(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_light_color(self, "white")
    my.tp_set_light_power(self, 2)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "%%fg=gold$The way down.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 50
    my.tp_set_tile(self, tile=name + ".1", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".7", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".8", is_dir_none=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="exit1", text_name="dungeon exit", short_text_name="exit")


init()
