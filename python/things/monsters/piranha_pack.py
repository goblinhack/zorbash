import my
import tp


def on_you_are_declared_leader(me, x, y):
    my.thing_polymorph(me, "piranha_giant")


def on_you_are_declared_a_follower(me, leader, x, y):
    my.thing_polymorph(me, "piranha")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.distance_recruitment_max(self, 7)
    my.is_able_to_follow(self, True)
    my.is_allied_with(self, "piranha_pack")
    my.is_biome_dungeon(self, True)
    my.is_monst_class_A(self, True)
    my.is_loggable(self, True)
    my.rarity(self, my.RARITY_RARE)  # how rare within this monster class
    my.on_you_are_declared_a_follower_do(self, "me.on_you_are_declared_a_follower()")
    my.environ_likes_deep_water(self, True)
    my.on_you_are_declared_leader_do(self, "me.on_you_are_declared_leader()")
    my.is_swimmer(self, True)
    my.is_monst_pack(self, True)
    my.is_loggable(self, True)
    my.spawn_group_radius(self, 5)
    my.spawn_group_size_dice(self, "1d4+3")
    # end sort marker
    my.tp_update(self)


def init():
    tp_init(name="piranha_pack", text_long_name="piranha pack")


init()
