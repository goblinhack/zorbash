import my
import zorb_all


def on_you_are_declared_leader(me, x, y):
    r = my.non_pcg_randint(1, 100)
    if r < 60:
        my.thing_polymorph(me, "zorb_captain")
    elif r < 70:
        my.thing_polymorph(me, "zorb_priest")
    elif r < 80:
        my.thing_polymorph(me, "zorb_wizard")
    elif r < 90:
        my.thing_polymorph(me, "zorb_necro")
    else:
        my.thing_polymorph(me, "zorb_pirate")


def on_you_are_declared_a_follower(me, leader, x, y):
    r = my.non_pcg_randint(1, 100)
    if r < 90:
        my.thing_polymorph(me, "zorb_soldier")
    else:
        my.thing_polymorph(me, "zorb_eldster")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    mytp.set_spawn_group_radius(4)
    mytp.set_spawn_group_size_dice("1d8")
    mytp.set_is_allied_with("zorb_pack")
    mytp.set_on_you_are_declared_a_follower_do("me.on_you_are_declared_a_follower()")
    mytp.set_on_you_are_declared_leader_do("me.on_you_are_declared_leader()")
    mytp.update()


def init():
    tp_init(name="zorb_pack", text_name="zorblin pack")


init()
