import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(leader):
        my.topcon("The zorblin necromancer begins muttering some unknown words!")


def on_born(me, x, y):
    my.thing_carry(me, "wand_energy")


def on_tick(me, x, y):
    # my.con("me   {} {:X}".format(my.thing_get_name(me), me))
    if my.thing_get_constitution(me) > 1:
        for follower in my.thing_get_all_followers(me):
            if my.thing_is_dead_or_dying(follower):
                my.thing_resurrect(follower, "arise")
                my.thing_decr_constitution(me, 1)
                my.thing_msg(me, "Arise!")
                return True

    return False


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    mytp.set_long_text_description_extra("This particular zorblin is learned in the dark arts. Withered of body, but sharp of mind, beware the abilities of this zorblin.")
    mytp.set_on_death_of_a_follower_do("me.on_death_of_a_follower()")
    mytp.set_on_born_do("me.on_born()")
    mytp.set_text_description("A master of the darkest arts.")
    mytp.set_is_carrier_of_treasure_class_b(True)
    mytp.set_strength(6)
    mytp.set_distance_avoid(5)
    mytp.set_health_initial_dice("2d3+4")
    mytp.set_is_able_to_use_wands(True)
    mytp.set_on_tick_do("me.on_tick()")
    mytp.set_is_intelligent(True)
    mytp.set_is_able_to_use_rings(True)

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
    tp_init(name="zorb_necro", text_name="zorblin necromancer")


init()
