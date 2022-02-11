import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_gas_blocker(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_light_blocker(mytp, True)
    my.tp_set_is_secret_door(mytp, True)
    my.tp_set_noise_blocker(mytp, True)
    my.tp_set_noise_on_open(mytp, 10)
    my.tp_set_noise_on_you_are_hit_and_now_dead(mytp, 10)
    my.tp_set_noise_on_you_are_hit_but_still_alive(mytp, 10)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A strange looking wall.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    my.tp_set_tile(mytp, tile=name + ".1")
    my.tp_set_tile(mytp, tile=name + ".2")
    my.tp_set_tile(mytp, tile=name + ".3")
    my.tp_set_tile(mytp, tile=name + ".4")
    my.tp_set_tile(mytp, tile=name + ".5")
    my.tp_set_tile(mytp, tile=name + ".6")
    my.tp_set_tile(mytp, tile=name + ".7")
    my.tp_set_tile(mytp, tile=name + ".8")
    my.tp_set_tile(mytp, tile=name + ".9")
    my.tp_set_tile(mytp, tile=name + ".10")
    my.tp_set_tile(mytp, tile=name + ".11")
    my.tp_set_tile(mytp, tile=name + ".12")
    my.tp_set_tile(mytp, tile=name + ".13")
    my.tp_set_tile(mytp, tile=name + ".14")
    my.tp_set_tile(mytp, tile=name + ".15")
    my.tp_set_tile(mytp, tile=name + ".16")

    my.tp_update(mytp, )


def init():
    tp_init(name="door_secret", text_name="An inconspicious dungeon wall.")


init()
