import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_gas_blocker(True)
    mytp.set_is_interesting(True)
    mytp.set_is_light_blocker(True)
    mytp.set_is_secret_door(True)
    mytp.set_noise_level(20)
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A strange looking wall.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    mytp.set_tile(tile=name + ".1")
    mytp.set_tile(tile=name + ".2")
    mytp.set_tile(tile=name + ".3")
    mytp.set_tile(tile=name + ".4")
    mytp.set_tile(tile=name + ".5")
    mytp.set_tile(tile=name + ".6")
    mytp.set_tile(tile=name + ".7")
    mytp.set_tile(tile=name + ".8")
    mytp.set_tile(tile=name + ".9")
    mytp.set_tile(tile=name + ".10")
    mytp.set_tile(tile=name + ".11")
    mytp.set_tile(tile=name + ".12")
    mytp.set_tile(tile=name + ".13")
    mytp.set_tile(tile=name + ".14")
    mytp.set_tile(tile=name + ".15")
    mytp.set_tile(tile=name + ".16")

    mytp.update()


def init():
    tp_init(name="door_secret", text_name="An inconspicious dungeon wall.")


init()
