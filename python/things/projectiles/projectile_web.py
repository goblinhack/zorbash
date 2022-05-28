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
    # start sort marker
    my.collision_check(self, True)
    my.gfx_ascii_mode_shown(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_projectile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tp_update(self)


def init():
    tp_init(name="projectile_web", text_name="web ball", short_text_name="web ball")


init()
