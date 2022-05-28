import my
import tp


def key_init(name, text_name):
    self = tp.Tp(name, text_name)
    # start sort marker
    my.collision_hit_priority(self, 6)
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_always(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gold_value_dice(self, "10")
    my.is_able_to_fall(self, True)
    my.is_auto_collect_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_collect_as_keys(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_key(self, True)
    my.is_loggable(self, True)
    my.is_meltable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 2)
    my.long_text_description(self, "A key that leadeth places undreamt of, or next door.")
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "an")
    my.text_description(self, "A key.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".1", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".6", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".7", delay_ms=100)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".8", delay_ms=100)

    my.tp_update(self)


def init():
    key_init(name="key", text_name="key")


init()
