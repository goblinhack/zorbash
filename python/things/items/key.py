import my
import tp


def key_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_bounce_always(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_gold_value_dice(mytp, "10")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_auto_collect_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_collect_as_keys(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_key(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_metal(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_light_color(mytp, "yellow")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_noise_on_moving_or_being_carried(mytp, 5)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_text_a_or_an(mytp, "an")
    my.tp_set_text_description(mytp, "A key that leadeth places undreamt, or next door.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".7", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".8", delay_ms=100)

    my.tp_update(mytp, )


def init():
    key_init(name="key", text_name="key")


init()
