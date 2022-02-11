import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin wizard curses darkly in rage!")


def on_born(me, x, y):
    my.thing_carry(me, "wand_fire")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    my.tp_set_long_text_description_extra(mytp, "This particular zorblin is learned in the dark zorbliny arts. They worship their dark lord who lives in his dark lair. They also prefer dark chocolate.")
    my.tp_set_on_death_of_a_follower_do(mytp, "me.on_death_of_a_follower()")
    my.tp_set_on_born_do(mytp, "me.on_born()")
    my.tp_set_text_description(mytp, "A master of the dark zorbliny arts.")
    my.tp_set_is_carrier_of_treasure_class_b(mytp, True)
    my.tp_set_stat_str(mytp, 8)
    my.tp_set_is_monst_class_c(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_distance_avoid(mytp, 5)
    my.tp_set_health_initial_dice(mytp, "2d4+4")
    my.tp_set_is_able_to_use_wands(mytp, True)
    my.tp_set_is_intelligent(mytp, True)
    my.tp_set_is_able_to_use_rings(mytp, True)

    delay = 300
    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=delay, frame=1)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=delay, frame=2)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=delay, frame=3)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=delay, frame=4)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=delay, frame=5)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=delay, frame=6)
    my.tp_set_tile(mytp, tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tp_set_tile(mytp, tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tp_set_tile(mytp, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="zorb_wizard", text_name="zorblin wizard")


init()
