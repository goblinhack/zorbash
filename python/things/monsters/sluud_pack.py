import my
import tp


def on_you_are_declared_leader(me, x, y):
    my.thing_polymorph(me, "sluud_dark")


def on_you_are_declared_a_follower(me, leader, x, y):
    r = my.py_non_pcg_random_range_inclusive(1, 100)
    if r < 90:
        my.thing_polymorph(me, "sluud")
    else:
        my.thing_polymorph(me, "sluud")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.is_able_to_follow(self, True)
    my.is_allied_with(self, "sluud_pack")
    my.is_biome_dungeon(self, True)
    my.on_you_are_declared_a_follower_do(self, "me.on_you_are_declared_a_follower()")
    my.on_you_are_declared_leader_do(self, "me.on_you_are_declared_leader()")
    my.is_biome_swamp(self, True)
    my.distance_recruitment_max(self, 7)
    my.is_monst_class_B(self, True)
    my.is_loggable(self, True)
    my.is_monst_pack(self, True)
    my.is_loggable(self, True)
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d6+3")
    # end sort marker
    my.tp_update(self)


def init():
    tp_init(name="sluud_pack",
            text_long_name="sluud pack")


init()
