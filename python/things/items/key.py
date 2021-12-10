import my
import tp


def key_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_bounce_always(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("10")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_auto_collect_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_collect_as_keys(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_key(True)
    mytp.set_is_loggable(True)
    mytp.set_is_metal(True)
    mytp.set_is_moveable(True)
    mytp.set_light_color("yellow")
    mytp.set_light_strength(2)
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("an")
    mytp.set_text_description("A key that leadeth places undreamt, or next door.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", delay_ms=100)
    mytp.set_tile(tile=name + ".2", delay_ms=100)
    mytp.set_tile(tile=name + ".3", delay_ms=100)
    mytp.set_tile(tile=name + ".4", delay_ms=100)
    mytp.set_tile(tile=name + ".5", delay_ms=100)
    mytp.set_tile(tile=name + ".6", delay_ms=100)
    mytp.set_tile(tile=name + ".7", delay_ms=100)
    mytp.set_tile(tile=name + ".8", delay_ms=100)

    mytp.update()


def init():
    key_init(name="key", text_name="key")


init()
