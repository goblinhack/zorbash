import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "gnoll")
    my.thing_enemy(me, "dogman")
    my.thing_carry(me, "dagger")
    my.thing_carry(me, "dart")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.is_able_to_follow(self, True)
    my.is_allied_with(self, "gnoll_pack")
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.distance_recruitment_max(self, 7)
    my.is_monst_class_B(self, True)
    my.is_loggable(self, True)
    my.is_monst_pack(self, True)
    my.is_loggable(self, True)
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d4+3")
    # end sort marker
    my.tp_update(self)


def init():
    tp_init(name="gnoll_pack", text_long_name="gnoll pack")


init()
