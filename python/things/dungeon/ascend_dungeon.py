import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_shown_in_bg(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_ascend_dungeon(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_critical_to_level(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_light_color(self, "yellow")
    my.tp_set_light_power(self, 2)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "%%fg=gold$The way up.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 1000
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.open", delay_ms=delay, is_open=True)
    my.tp_set_tile(self, tile=name + ".2.open", delay_ms=delay, is_open=True)

    my.tp_update(self)


def init():
    tp_init(name="entrance", text_name="dungeon entrance", short_text_name="entrance")


init()
