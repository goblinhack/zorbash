import my
import tp


def attack(me, thing):
    if my.thing_possible_to_attack(me, thing):
        if thing != me:
            my.thing_hit(me, thing)


def on_born(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_d")

    selection_x, selection_y = my.thing_coords_get(me)
    my.spawn_radius_range(me, "explosion_fire", min=0, max=3)

    #
    # Blast damage
    #
    for dx in range(-2, 3):
        for dy in range(-2, 3):
            if my.pcg_randint(1, 100) < 20:
                my.spawn_at(me, "small_fire", x + dx, y + dy)
            if my.pcg_randint(1, 100) < 10:
                my.spawn_at(me, "fire", x + dx, y + dy)
            for thing in my.level_get_all(me, selection_x + dx, selection_y + dy):
                attack(me, thing)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.damage_fire_chance_d1000(self, 0, 1000)
    my.damage_fire_dice(self, "6d6")
    my.damage_nat_att_type(self, "blast")
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_explosion(self, True)
    my.is_fire(self, True)
    my.is_floating(self, True)
    my.is_loggable(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 4)
    my.noise_on_born(self, 100)
    my.on_born_do(self, "me.on_born()")
    my.temperature(self, 100)
    my.text_hits(self, "blasts")
    my.tick_prio(self, my.MAP_TICK_PRIO_VERY_HIGH)
    my.z_depth(self, my.MAP_DEPTH_TOP)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_bg_col_name="orange", ascii_fg_col_name="",
            tile=name + ".16",
            delay_ms=delay,
            is_end_of_anim=True,
            is_dead_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="explosion_major",
            text_long_name="huge explosion",
            text_short_name="huge explosion")


init()
