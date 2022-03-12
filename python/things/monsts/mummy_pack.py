import my
import tp


def on_you_are_declared_leader(me, x, y):
    my.thing_polymorph(me, "mummy_necro")


def on_you_are_declared_a_follower(me, leader, x, y):
    my.thing_polymorph(me, "mummy")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.distance_leader_max(self, 5)
    my.distance_recruitment_max(self, 7)
    my.is_able_to_follow(self, True)
    my.is_allied_with(self, "mummy_pack")
    my.is_biome_dungeon(self, True)
    my.is_monst_class_c(self, True)
    my.is_pack(self, True)
    my.on_you_are_declared_a_follower_do(self, "me.on_you_are_declared_a_follower()")
    my.on_you_are_declared_leader_do(self, "me.on_you_are_declared_leader()")
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d4+1")
    my.tp_update(self)


def init():
    tp_init(name="mummy_pack", text_name="mummy pack")


init()
