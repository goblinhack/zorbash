import my
import zorb_all


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin soldier cries out in rage!")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init( name, text_name)
    my.tp_set_long_text_description_extra(mytp, "This particular zorblin has is a battle hardened veteran of many wars.")
    my.tp_set_on_death_of_my_leader_do(mytp, "me.on_death_of_my_leader()")
    my.tp_set_text_description(mytp, "A grizzled war-weary soldier.")
    my.tp_set_is_able_to_use_armor(mytp, True)
    my.tp_set_is_monst_class_b(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_stat_str(mytp, 10)
    my.tp_set_health_initial_dice(mytp, "2d8+2")
    my.tp_set_is_able_to_use_weapons(mytp, True)
    my.tp_set_is_carrier_of_treasure_class_a(mytp, True)
    my.tp_set_is_carrier_of_weapon_class_a(mytp, True)

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
    tp_init(name="zorb_soldier", text_name="zorblin soldier")


init()
