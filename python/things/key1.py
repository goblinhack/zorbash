import zx
import tp


def key_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_bounce_always(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_collect_as_keys(True)
    x.set_is_collectable(True)
    x.set_is_interesting(True)
    x.set_is_item(False)
    x.set_is_key(True)
    x.set_is_light_strength(2)
    x.set_is_movable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_treasure_class_a(False)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("an");
    x.set_text_description("A key that leadeth places undreamt, or next door")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", delay_ms=100)
    x.set_tile(tile=name + ".2", delay_ms=100)
    x.set_tile(tile=name + ".3", delay_ms=100)
    x.set_tile(tile=name + ".4", delay_ms=100)
    x.set_tile(tile=name + ".5", delay_ms=100)
    x.set_tile(tile=name + ".6", delay_ms=100)
    x.set_tile(tile=name + ".7", delay_ms=100)
    x.set_tile(tile=name + ".8", delay_ms=100)

    x.update()

def init():
    key_init(name="key1", text_name="key")

init()
