import my
import zorb_all


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin soldier cries out in rage!")


def tp_init(name, text_name):
    self = zorb_all.tp_init(name, text_name)
    my.long_text_description_extra(self, "This particular zorblin has is a battle hardened veteran of many wars.")
    my.on_death_of_my_leader_do(self, "me.on_death_of_my_leader()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.text_description(self, "A grizzled war-weary soldier.")
    my.is_able_to_use_armor(self, True)
    my.is_monst_class_b(self, True)
    my.is_biome_dungeon(self, True)
    my.stat_str(self, 10)
    my.health_initial_dice(self, "2d8+2")
    my.is_able_to_use_weapons(self, True)
    my.is_carrier_of_treasure_class_a(self, True)
    my.is_carrier_of_weapon_class_a(self, True)

    delay = 300
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".6", delay_ms=delay, frame=6)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".dead.4", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".dead.5", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_soldier", text_name="zorblin soldier")


init()
