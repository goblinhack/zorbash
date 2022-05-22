import my
import tp


def key_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.collision_hit_priority(self, 6)
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
    my.is_key(self, 5)
    my.is_loggable(self, True)
    my.is_meltable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.light_color(self, "red")
    my.light_dist(self, 1)
    my.long_text_description(self, "An evil looking set of keys. Probably still works just fine though. Translates into five keys when carried.")
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "an")
    my.text_description(self, "An evil looking key.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name)

    my.tp_update(self)


def init():
    key_init(name="key_penta", text_name="evil looking key")


init()
