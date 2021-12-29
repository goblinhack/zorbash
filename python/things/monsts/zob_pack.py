import my
import zob_all


def on_you_are_declared_leader(me, x, y):
    r = my.non_pcg_randint(1, 100)
    if r < 90:
        my.thing_polymorph(me, "zob_captain")
    elif r < 95:
        my.thing_polymorph(me, "zob_wizard")
    else:
        my.thing_polymorph(me, "zob_pirate")


def on_you_are_declared_a_follower(me, leader, x, y):
    r = my.non_pcg_randint(1, 100)
    if r < 90:
        my.thing_polymorph(me, "zob_soldier")
    else:
        my.thing_polymorph(me, "zob_eldster")


def tp_init(name, text_name):
    mytp = zob_all.tp_init(name, text_name)
    mytp.set_spawn_group_radius(4)
    mytp.set_spawn_group_size_dice("1d8")
    mytp.set_is_allied_with("zob_pack")
    mytp.set_on_you_are_declared_a_follower_do("me.on_you_are_declared_a_follower()")
    mytp.set_on_you_are_declared_leader_do("me.on_you_are_declared_leader()")
    mytp.update()


def init():
    tp_init(name="zob_pack", text_name="zoblin pack")


init()
