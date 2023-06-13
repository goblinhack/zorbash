import my
import tp


def spawn(me, x, y):
    my.spawn_set_fire_to_things_around_me(me, "fire")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.collision_check(self, True)
    my.dmg_chance_d1000_fire(self, 0, 1000)
    my.dmg_fire_dice(self, "1d3+1")
    my.dmg_nat_att_type(self, "burn")
    my.environ_dislikes_water(self, 100)
    my.gfx_ascii_shown(self, True)
    my.gfx_on_fire_anim(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_flickers(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.health_initial_dice(self, "5")
    my.is_able_to_fall(self, True)
    my.is_dead_on_falling(self, True)
    my.is_fire(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_tickable(self, True)
    my.lifespan_dice(self, "1d10+10")
    my.light_color(self, "orange")
    my.light_dist(self, 3)
    my.on_idle_tick_freq_dice(self, "1d10+10:me.spawn()")
    my.temperature_min(self, 0)
    my.temperature(self, 100)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "")
    my.text_description_short(self, "Fire embers.")
    my.text_hits(self, "burns")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_FIRE)
    # end sort marker

    delay = 75
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="darkred",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="darkred",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="darkred",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="darkred",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="darkred",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="darkred",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="^", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".16", delay_ms=delay)
    my.tp_update(self)


def init():
    tp_init(name="small_fire", text_long_name="burning fire")


init()
