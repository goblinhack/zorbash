import my
import tp


def gold_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.collision_hit_priority(self, 6)
    my.gfx_animated(self, True)
    my.gfx_bounce_always(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.gfx_very_short_shadow_caster(self, True)
    my.gold_value_dice(self, "1")
    my.is_able_to_fall(self, True)
    my.is_auto_collect_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_collected_as_gold(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gold(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_a(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 1)
    my.normal_placement_rules(self, True)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A gold goin.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".1", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".2", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".3", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".4", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".5", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".6", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".7", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".8", is_dir_none=True, delay_ms=50)

    my.tp_update(self)


def init():
    gold_init(name="gold1", text_name="lone gold coin")


init()
