import zx
import tp

def on_use(owner, item, target, x, y):
    #zx.con("owner   {} {:08X} {}".format(zx.thing_get_name(owner), owner, owner))
    #zx.con("item    {} {:08X} {}".format(zx.thing_get_name(item), item, item))
    #zx.con("target  {} {:08X} {}".format(zx.thing_get_name(target), target, target))
    zx.tp_spawn_at(target, "explosion_major")
    zx.tp_spawn_radius_range(owner, item, target, "explosion_destroy_floor")

    target_x, target_y = zx.thing_get_coords(target)
    for thing in zx.level_get_all(target_x, target_y):
        if zx.thing_is_monst(thing) or \
                zx.thing_is_item(thing) or \
                zx.thing_is_door(thing) or \
                zx.thing_is_wall(thing) or \
                zx.thing_is_player(thing) or \
                zx.thing_is_minion_generator(thing) or \
                zx.thing_is_brazier(thing):
            zx.thing_hit(owner, item, thing)

    zx.sound_play_channel_at(zx.CHANNEL_WEAPON, "lightning_b", x, y)

#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_blast_max_radius(0)
    x.set_blast_min_radius(0)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_is_interesting(True)
    x.set_is_laser(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_no_tile(True)
    x.set_is_usable(True)
    x.set_is_spawner(True)
    x.set_laser_name("laser_descent")
    x.set_on_use_do("laser_descent.on_use()")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.update()

def init():
    tp_init(name="laser_descent", text_name="laser beam of descent", short_text_name="laser.descent")

init()
