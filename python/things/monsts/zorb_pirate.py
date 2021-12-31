import my
import zorb_all


def on_death_of_a_follower(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.topcon("The zorblin pirate cries out: Aaar!")


def on_born(me, x, y):
    my.thing_carry(me, "treasure_map")
    my.thing_carry(me, "gold6")
    my.thing_carry(me, "cutlass")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    mytp.set_long_text_description_extra("This particular zorblin was once a ruthless adventurer who plundered the seas in their mighty pirate ship, but due to a series of unfortunate and inexplicable events has now found themselves wandering the halls of this dungeon looking for the odd piece of eight.")
    mytp.set_on_death_of_a_follower_do("me.on_death_of_a_follower()")
    mytp.set_on_born_do("me.on_born()")
    mytp.set_text_description("A one-eyed pirate zorblin.")
    mytp.set_is_carrier_of_treasure_class_c(True)
    mytp.set_stat_strength(14)
    mytp.set_health_initial_dice("2d10+4")
    mytp.set_health_initial_dice("2d10")
    mytp.set_is_able_to_use_weapons(True)

    delay = 300
    mytp.set_tile(tile=name + ".1", delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    mytp.update()


def init():
    tp_init(name="zorb_pirate", text_name="zorblin pirate")


init()
