import zx
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_oversized_but_sitting_on_the_ground(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_small_shadow_caster(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_critical_to_level(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_descend_dungeon(True)
    mytp.set_is_interesting(True)
    mytp.set_light_strength(2)
    mytp.set_light_color("white")
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("%%fg=gold$The way down.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 50
    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".7", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".8", is_dir_none=True, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="exit1", text_name="dungeon exit", short_text_name="exit")

init()
