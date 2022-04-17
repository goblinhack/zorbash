import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.gfx_animated(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_shown_in_bg(self, True)
    my.gfx_show_outlined(self, True)
    my.is_ascend_dungeon(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_critical_to_level(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "the")
    my.text_description(self, "%%fg=gold$The way up.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 1000
    my.tile(self, tile=name + ".1", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)
    my.tile(self, tile=name + ".3", delay_ms=delay)
    my.tile(self, tile=name + ".4", delay_ms=delay)
    my.tile(self, tile=name + ".5", delay_ms=delay)
    my.tile(self, tile=name + ".6", delay_ms=delay)
    my.tile(self, tile=name + ".3", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)
    my.tile(self, tile=name + ".3", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)
    my.tile(self, tile=name + ".3", delay_ms=delay)
    my.tile(self, tile=name + ".1.open", delay_ms=delay, is_open=True)
    my.tile(self, tile=name + ".2.open", delay_ms=delay, is_open=True)

    my.tp_update(self)


def init():
    tp_init(name="entrance", text_name="dungeon entrance", short_text_name="entrance")


init()
