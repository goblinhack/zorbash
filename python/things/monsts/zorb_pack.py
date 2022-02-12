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
    self = zorb_all.tp_init(name, text_name)
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d8")
    my.is_allied_with(self, "zorb_pack")
    my.on_you_are_declared_a_follower_do(self, "me.on_you_are_declared_a_follower()")
    my.is_monst_class_b(self, True)
    my.is_biome_dungeon(self, True)
    my.on_you_are_declared_leader_do(self, "me.on_you_are_declared_leader()")
    my.tp_update(self)


def init():
    tp_init(name="zorb_pack", text_name="zorblin pack")


init()
