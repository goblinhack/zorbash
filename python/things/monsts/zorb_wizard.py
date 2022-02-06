import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin wizard curses darkly in rage!")


def on_born(me, x, y):
    my.thing_carry(me, "wand_fire")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    mytp.set_long_text_description_extra("This particular zorblin is learned in the dark zorbliny arts. They worship their dark lord who lives in his dark lair. They also prefer dark chocolate.")
    mytp.set_on_death_of_a_follower_do("me.on_death_of_a_follower()")
    mytp.set_on_born_do("me.on_born()")
    mytp.set_text_description("A master of the dark zorbliny arts.")
    mytp.set_is_carrier_of_treasure_class_b(True)
    mytp.set_stat_str(8)
    mytp.set_is_monst_class_c(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_distance_avoid(5)
    mytp.set_health_initial_dice("2d4+4")
    mytp.set_is_able_to_use_wands(True)
    mytp.set_is_intelligent(True)
    mytp.set_is_able_to_use_rings(True)

    delay = 300
    mytp.set_tile(tile=name + ".1", delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, frame=6)
    mytp.set_tile(tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    mytp.update()


def init():
    tp_init(name="zorb_wizard", text_name="zorblin wizard")


init()
