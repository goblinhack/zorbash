import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_ascend_dungeon(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_critical_to_level(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_light_color(mytp, "yellow")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "%%fg=gold$The way up.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 1000
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.open", delay_ms=delay, is_open=True)
    my.tp_set_tile(mytp, tile=name + ".2.open", delay_ms=delay, is_open=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="entrance", text_name="dungeon entrance", short_text_name="entrance")


init()
