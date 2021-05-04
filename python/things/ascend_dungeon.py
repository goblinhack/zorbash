import zx
import tp


def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_collision_circle(True)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(False)
    x.set_is_described_when_hovering_over(True)
    x.set_is_critical_to_level(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_ascend_dungeon(True)
    x.set_is_interesting(True)
    x.set_light_strength(2)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("the")
    x.set_text_description("%%fg=gold$The way up.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 1000
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".1.open", delay_ms=delay, is_open=True)
    x.set_tile(tile=name + ".2.open", delay_ms=delay, is_open=True)

    x.update()

def init():
    tp_init(name="entrance", text_name="dungeon entrance", short_text_name="entrance")

init()
