import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_gas_blocker(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_light_blocker(self, True)
    my.tp_set_is_secret_door(self, True)
    my.tp_set_noise_blocker(self, True)
    my.tp_set_noise_on_open(self, 10)
    my.tp_set_noise_on_you_are_hit_and_now_dead(self, 10)
    my.tp_set_noise_on_you_are_hit_but_still_alive(self, 10)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A strange looking wall.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    my.tp_set_tile(self, tile=name + ".1")
    my.tp_set_tile(self, tile=name + ".2")
    my.tp_set_tile(self, tile=name + ".3")
    my.tp_set_tile(self, tile=name + ".4")
    my.tp_set_tile(self, tile=name + ".5")
    my.tp_set_tile(self, tile=name + ".6")
    my.tp_set_tile(self, tile=name + ".7")
    my.tp_set_tile(self, tile=name + ".8")
    my.tp_set_tile(self, tile=name + ".9")
    my.tp_set_tile(self, tile=name + ".10")
    my.tp_set_tile(self, tile=name + ".11")
    my.tp_set_tile(self, tile=name + ".12")
    my.tp_set_tile(self, tile=name + ".13")
    my.tp_set_tile(self, tile=name + ".14")
    my.tp_set_tile(self, tile=name + ".15")
    my.tp_set_tile(self, tile=name + ".16")

    my.tp_update(self)


def init():
    tp_init(name="door_secret", text_name="An inconspicious dungeon wall.")


init()
