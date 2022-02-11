import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_critical_to_level(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_descend_dungeon(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_light_color(mytp, "white")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "%%fg=gold$The way down.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 50
    my.tp_set_tile(mytp, tile=name + ".1", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".6", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".7", is_dir_none=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".8", is_dir_none=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="exit1", text_name="dungeon exit", short_text_name="exit")


init()
