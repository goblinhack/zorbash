import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_coords_get(me)
    for thing in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, thing):
            my.thing_hit(me, thing)
    my.level_spawn_owned_thing_at(me, "green_splatter")


#
# This is an internal only object to acid projectiles from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.collision_check(self, True)
    my.damage_acid_chance_d1000(self, 0, 1000)
    my.damage_acid_dice(self, "1d10")  # This is the damage when the monst acids
    my.gfx_ascii_shown(self, True)
    my.is_acid(self, True)
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

    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="lime",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="green",  tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="projectile_acid", text_long_name="acidball", text_short_name="acidball")


init()
