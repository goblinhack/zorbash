import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_exit(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(2)
    x.set_light_color("white")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("the");
    x.set_text_description("%%fg=gold$The way down...")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 50
    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".7", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".8", is_dir_none=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="exit1", text_name="dungeon exit")

init()
