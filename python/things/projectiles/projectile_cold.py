import my
import tp


def on_born(me, x, y):
    selection_x, selection_y = my.thing_coords_get(me)
    for it in my.level_get_all(me, selection_x, selection_y):
        if my.thing_possible_to_attack(me, it):
            my.thing_hit(me, it)
    my.spawn_owned_thing_at_my_position(me, "explosion_cold")
    my.spawn_owned_thing_at_my_position(me, "block_of_ice")


#
# This is an internal only object to cold projectiles from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.collision_check(self, True)
    my.damage_cold_chance_d1000(self, 0, 1000)
    my.damage_cold_dice(self, "1d10")  # This is the damage when the monst colds
    my.gfx_ascii_shown(self, True)
    my.is_cold(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_projectile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, -100)
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")
    my.tile(self, ascii_fg_char="*", ascii_fg_col_name="cyan",  tile="nothing")

    my.tp_update(self)


def init():
    tp_init(name="projectile_cold", text_long_name="snowball", text_short_name="snowball")


init()
