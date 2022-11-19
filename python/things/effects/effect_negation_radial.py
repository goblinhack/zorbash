import my
import tp


def on_born(me, x, y):
    item = my.thing_immediate_owner_id_get(me)
    radius = my.thing_effect_radius_get(item)
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))

    for dx in range(-radius, radius + 1):
        for dy in range(-radius, radius + 1):
            if dx == 0 and dy == 0:
                continue
            x1 = x + dx
            y1 = y + dy
            distance = (((x1 - x)**2 + (y1 - y)**2)**0.5)
            if distance > radius:
                continue

            my.place_at(me, "magical_effect", x1, y1)
            for it in my.level_get_all(item, x1, y1):
                if my.thing_possible_to_attack(item, it):
                    my.thing_hit(item, it)


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_check(self, True)
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tp_update(self)


def init():
    tp_init(
        name="effect_negation_radial",
        text_long_name="blast of negation",
        text_short_name="blast of negation",
    )


init()
