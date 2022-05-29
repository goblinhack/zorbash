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
    my.gold_value_dice(self, "100")
    my.is_able_to_fall(self, True)
    my.is_auto_collect_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_collect_as_keys(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_key(self, 2)
    my.is_loggable(self, True)
    my.is_meltable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 2)
    my.long_text_description(self, "A pair of keys. What more can you say.")
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "an")
    my.text_description(self, "A pair of keys.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name)

    my.tp_update(self)


def init():
    key_init(name="key_pair", text_name="pair of keys")


init()
