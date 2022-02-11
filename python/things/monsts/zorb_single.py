import zorb_all
import my


def tp_init(name, text_name):
    self = zorb_all.tp_init(name, text_name)
    my.tp_set_text_description(self, "A very lesser and a bit insecure zorblin.")
    my.tp_set_is_able_to_use_weapons(self, True)
    my.tp_set_is_monst_class_b(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_carrier_of_treasure_class_a(self, True)
    my.tp_set_is_carrier_of_weapon_class_a(self, True)

    delay = 300
    my.tp_set_tile(self, tile=name + ".1", delay_ms=delay, frame=1)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=delay, frame=2)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=delay, frame=3)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=delay, frame=4)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=delay, frame=5)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=delay, frame=6)
    my.tp_set_tile(self, tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tp_set_tile(self, tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tp_set_tile(self, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_single", text_name="lesser zorblin")


init()
