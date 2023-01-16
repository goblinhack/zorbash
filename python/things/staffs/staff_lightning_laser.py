import my
import tp


def on_born(me, x, y):
    # my.con("me      {} {:X} {},{}".format(my.thing_name_get(me), me, x, y))

    #
    # Lightning can impact all things in the same pool
    #
    for source in my.level_get_all(me, x, y):
        if my.thing_is_water(source):
            for water in my.level_flood_fill_get_all_things(me, x, y, "is_water"):
                water_x, water_y = my.thing_coords_get(water)

                for it in my.level_get_all(water, water_x, water_y):
                    # my.con("cand    {} {:X} {},{}".format(my.thing_name_get(it), it, water_x, water_y))
                    if it != me:
                        if my.thing_possible_to_attack(me, it):
                            my.thing_hit(me, it)
                            if my.thing_is_player(it):
                                my.thing_msg(it, "Current surges through your body!")

                            my.thing_shoot_at(source, "staff_lightning_laser_fork", it)
            return

        it = source
        if my.thing_possible_to_attack(me, it):
            my.thing_hit(me, it)
            if my.thing_is_player(it):
                my.thing_msg(it, "Current surges through your body!")


#
# This is an internal only object to fire lasers from monsters
#
def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.dmg_lightning_chance_d1000(self, 0, 1000)  # for electric eel attack
    my.dmg_lightning_dice(self, "1d10+4")
    my.gfx_ascii_shown(self, True)
    my.is_able_to_attack_owner(self, True)
    my.is_laser(self, True)
    my.is_lightning(self, True)
    my.is_loggable(self, True)
    my.is_no_tile(self, True)
    my.is_usable(self, True)
    my.on_born_do(self, "me.on_born()")
    my.text_a_or_an(self, "a")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=255, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=200, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=100, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="cyan", ascii_fg_alpha=50, tile="nothing")
    my.tile(self, ascii_fg_char="block", ascii_fg_col_name="white", ascii_fg_alpha=50, tile="nothing")

    my.tp_update(self)


def init():
    tp_init(
        name="staff_lightning_laser",
        text_long_name="ray of lightning",
        text_short_name="ray of lightning",
    )


init()
