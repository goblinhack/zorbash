import my
import gob_all


def on_you_are_declared_leader(me, x, y):
    my.thing_polymorph(me, "gob_pirate")
    # my.thing_polymorph(me, "gob_wizard")
    # my.thing_polymorph(me, "gob_captain")


def on_you_are_declared_a_follower(me, leader, x, y):
    my.thing_polymorph(me, "gob_soldier")


def tp_init(name, text_name):
    mytp = gob_all.tp_init(name, text_name)
    mytp.set_spawn_group_radius(4)
    mytp.set_spawn_group_size_dice("1d8")
    mytp.set_is_allied_with("gob_pack")
    mytp.set_on_you_are_declared_a_follower_do("me.on_you_are_declared_a_follower()")
    mytp.set_on_you_are_declared_leader_do("me.on_you_are_declared_leader()")
    mytp.update()


def init():
    tp_init(name="gob_pack", text_name="goblin pack")


init()
