import my
import gob_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(leader):
        my.topcon("The goblin wizard curses darkly in rage!")


def tp_init(name, text_name):
    mytp = gob_all.tp_init(name, text_name)
    mytp.set_long_text_description("Goblins are small, green skinned beings that lair in caves, abandoned mines, despoiled dungeons and other dismal settings, otherwise known as their homes. They spend their time defending their natural habitat from invading marauders like you. However, they usually carry some meagre amounts of gold, dug out from the depths with their bare, shaking hands. Best to find out... This particular goblin is learned in the dark gobliny arts. They worship their dark lord who lives in his dark lair. They also prefer dark chocolate.")
    mytp.set_on_death_of_a_follower_do("me.on_death_of_a_follower()")
    mytp.set_text_description("A master of the dark gobliny arts.")
    mytp.set_is_carrier_of_treasure_class_b(True)
    mytp.set_is_debug_type(True)
    mytp.set_stat_strength(8)
    mytp.set_distance_avoid(5)
    mytp.set_health_initial_dice("2d4+4")
    mytp.set_is_able_to_use_wands(True)
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
    tp_init(name="gob_wizard", text_name="goblin wizard")


init()
