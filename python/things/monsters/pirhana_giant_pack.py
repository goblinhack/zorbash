import my
import tp


def on_you_are_declared_leader(me, x, y):
    my.thing_polymorph(me, "pirhana_giant")


def on_you_are_declared_a_follower(me, leader, x, y):
    my.thing_polymorph(me, "pirhana_giant")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.distance_recruitment_max(self, 7)
    my.is_able_to_follow(self, True)
    my.is_allied_with(self, "pirhana_giant_pack")
    my.is_biome_dungeon(self, True)
    my.is_monst_class_c(self, True)
    my.is_loggable(self, True)
    my.rarity(self, my.RARITY_COMMON)
    my.on_you_are_declared_a_follower_do(self, "me.on_you_are_declared_a_follower()")
    my.is_deep_water_swimmer(self, True)
    my.is_shallow_water_swimmer(self, True)
    my.on_you_are_declared_leader_do(self, "me.on_you_are_declared_leader()")
    my.is_swimmer(self, True)
    my.is_monst_pack(self, True)
    my.is_loggable(self, True)
    my.spawn_group_radius(self, 5)
    my.spawn_group_size_dice(self, "1d4+3")
    my.tp_update(self)


def init():
    tp_init(name="pirhana_giant_pack", text_long_name="pirhana_giant pack")


init()
