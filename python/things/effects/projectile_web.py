import my
import tp


def on_born(me, x, y):
    it = my.level_spawn_at_thing(me, "webball")
    if it != 0:
        my.thing_set_mob(me, it)


#
# This is an internal only object to fire webs
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_check(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_no_tile(self, True)
    my.tp_set_is_projectile(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_on_born_do(self, "me.on_born()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(name="projectile_web", text_name="web ball", short_text_name="web ball")


init()
