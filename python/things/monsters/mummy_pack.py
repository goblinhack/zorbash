import my
import tp


def on_you_are_declared_leader(me, x, y):
    my.thing_polymorph(me, "mummy_necro")


def on_you_are_declared_a_follower(me, leader, x, y):
    r = my.py_non_pcg_random_range_inclusive(1, 100)
    if r < 80:
        my.thing_polymorph(me, "snake_asp")
        return
    my.thing_polymorph(me, "mummy")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.distance_recruitment_max(self, 7)
    my.is_able_to_follow(self, True)
    my.is_allied_with(self, "mummy_pack")
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_chasms(self, True)
    my.is_monst_class_C(self, True)
    my.is_loggable(self, True)
    my.is_monst_pack(self, True)
    my.is_loggable(self, True)
    my.on_you_are_declared_a_follower_do(self, "me.on_you_are_declared_a_follower()")
    my.on_you_are_declared_leader_do(self, "me.on_you_are_declared_leader()")
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d4+3")
    # end sort marker
    my.tp_update(self)


def init():
    tp_init(name="mummy_pack", text_long_name="mummy pack")


init()
