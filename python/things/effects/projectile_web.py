import my
import tp


def on_born(me, x, y):
    it = my.level_spawn_at_thing(me, "webball")
    if it != 0:
        my.thing_set_manifestor(me, it)


#
# This is an internal only object to fire webs
#
def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_check(True)
    mytp.set_is_interesting(True)
    mytp.set_is_loggable(True)
    mytp.set_is_no_tile(True)
    mytp.set_is_projectile(True)
    mytp.set_is_usable(True)
    mytp.set_on_born_do("me.on_born()")
    mytp.set_text_a_or_an("a")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.update()


def init():
    tp_init(name="projectile_web", text_name="web ball", short_text_name="web ball")


init()
