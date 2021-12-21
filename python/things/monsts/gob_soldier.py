import my
import gob_all


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.topcon("The goblin soldier cries out in rage!")


def tp_init(name, text_name):
    mytp = gob_all.tp_init(name, text_name)
    mytp.set_long_text_description("Goblins are small, green skinned beings that lair in caves, abandoned mines, despoiled dungeons and other dismal settings, otherwise known as their homes. They spend their time defending their natural habitat from invading marauders like you. However, they usually carry some meagre amounts of gold, dug out from the depths with their bare, shaking hands. Best to find out... This particular goblin has is a battle hardened veteran of many wars.")
    mytp.set_on_death_of_my_leader_do("me.on_death_of_my_leader()")
    mytp.set_text_description("A grizzled war-weary soldier.")
    mytp.set_stat_strength(10)
    mytp.set_health_initial_dice("2d8+2")
    mytp.set_is_able_to_use_weapons(True)
    mytp.set_is_carrier_of_treasure_class_a(True)

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
    tp_init(name="gob_soldier", text_name="goblin soldier")


init()
