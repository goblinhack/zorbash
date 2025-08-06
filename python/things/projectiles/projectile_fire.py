import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_coords_get(me)
    for it in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, it):
            my.spawn_at_my_position(it, "explosion_fire")
            return


#
# This is an internal only object to fire projectiles from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_check(self, True)
    my.dmg_acid_dice(self, "1d6")  # This is the damage when the monst acids
    my.dmg_chance_d1000_acid(self, 0, 1000)
    my.gfx_ascii_shown(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_dead_on_falling(self, True)
    my.is_fire(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_projectile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, 100)
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="orange",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="red",  tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="projectile_fire",
            text_long_name="fireball",
            text_short_name="fireball")


init()
