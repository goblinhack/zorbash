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
    mytp = zorb_all.tp_init( name, text_name)
    my.tp_set_spawn_group_radius(mytp, 4)
    my.tp_set_spawn_group_size_dice(mytp, "1d8")
    my.tp_set_is_allied_with(mytp, "zorb_pack")
    my.tp_set_on_you_are_declared_a_follower_do(mytp, "me.on_you_are_declared_a_follower()")
    my.tp_set_is_monst_class_b(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_on_you_are_declared_leader_do(mytp, "me.on_you_are_declared_leader()")
    my.tp_update(mytp, )


def init():
    tp_init(name="zorb_pack", text_name="zorblin pack")


init()
