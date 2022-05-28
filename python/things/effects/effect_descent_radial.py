import my
import tp


def on_born(me, x, y):
    item = my.thing_immediate_owner_id_get(me)
    my.level_spawn_using_items_radius_range(id=me, parent_id=item, victim_id=me, what="explosion_destroy_floor", min=1)
    my.thing_popup(me, "You shall not pass!")
    my.thing_dead(me, "used")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.gfx_ascii_mode_shown(self, True)
    my.blast_max_radius(self, 2)
    my.collision_check(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)

    my.tp_update(self)


def init():
    tp_init(
        name="effect_descent_radial",
        text_name="blast of destruction",
        short_text_name="blast of descent",
    )


init()
