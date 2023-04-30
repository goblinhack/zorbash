import my
import tp


def key_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.chance_d1000_appearing(self, 1000)
    my.chance_d1000_melting(self, 10)
    my.collision_hit_priority(self, 6)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_always(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gold_value_dice(self, "10")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_melt(self, True)
    my.is_auto_collect_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_collectable(self, True)
    my.is_collected_as_keys(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_key(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "an")
    my.text_description_long(self, "A key that leadeth places undreamed of, or next door.")
    my.text_description_short(self, "A key.")
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
    key_init(name="key", text_long_name="key")


init()
