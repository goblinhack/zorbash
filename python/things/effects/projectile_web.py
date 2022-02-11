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
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_no_tile(mytp, True)
    my.tp_set_is_projectile(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_on_born_do(mytp, "me.on_born()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_update(mytp, )


def init():
    tp_init(name="projectile_web", text_name="web ball", short_text_name="web ball")


init()
