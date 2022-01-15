import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin leader cries out in rage!")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    mytp.set_long_text_description_extra("This particular zorblin has risen through the ranks. As tough as stone nails in a stone coffin, this zorblin is not prepared to take any of your cheek.")
    mytp.set_health_initial_dice("2d10")
    mytp.set_health_initial_dice("2d10+4")
    mytp.set_is_able_to_use_weapons(True)
    mytp.set_is_able_to_use_armor(True)
    mytp.set_is_carrier_of_treasure_class_b(True)
    mytp.set_is_monst_class_b(True)
    mytp.set_is_carrier_of_weapon_class_b(True)
    mytp.set_on_death_of_a_follower_do("me.on_death_of_a_follower()")
    mytp.set_stat_str(12)
    mytp.set_text_description("A grizzled war-weary zorblin.")

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
    tp_init(name="zorb_captain", text_name="zorblin leader")


init()
