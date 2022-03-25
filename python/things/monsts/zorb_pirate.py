import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_topcon(me, "The zorblin pirate cries out: Aaar!")


def on_born(me, x, y):
    my.thing_carry(me, "map_treasure")
    my.thing_carry(me, "gold6")
    my.thing_carry(me, "cutlass")


def tp_init(name, text_name):
    self = zorb_all.tp_init(name, text_name)
    my.long_text_description_extra(self, "This particular zorblin was once a ruthless adventurer who plundered the seas in their mighty pirate ship, but due to a series of unfortunate and inexplicable events has now found themselves wandering the halls of this dungeon looking for the odd piece of eight.")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.on_born_do(self, "me.on_born()")
    my.text_description(self, "A one-eyed pirate zorblin.")
    my.is_carrier_of_treasure_class_c(self, True)
    my.stat_str(self, 14)
    my.health_initial_dice(self, "2d10+4")
    my.health_initial_dice(self, "2d10")
    my.is_able_to_use_weapons(self, True)
    my.is_monst_class_b(self, True)
    my.is_biome_dungeon(self, True)

    delay = 300
    my.tile(self, tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self, tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self, tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self, tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self, tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self, tile=name + ".6", delay_ms=delay, frame=6)
    my.tile(self, tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tile(self, tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tile(self, tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.4", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.5", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_pirate", text_name="zorblin pirate")


init()
