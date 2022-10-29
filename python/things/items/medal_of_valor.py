import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.appearing_chance_d1000(self, 10)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gold_value_dice(self, "10")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 2)
    my.item_width(self, 2)
    my.noise_on_dropping(self, 25)
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stat_def_mod(self, 2)
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+1 DEF")
    my.text_long_description(self, "Even just looking at this medal of valor, you feel more brave. Whomever left it here, probably felt the same...")
    my.text_short_description(self, "A medal of valor.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="*", ascii_bg_col_name="", ascii_fg_col_name="magenta",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="medal_of_valor", text_long_name="medal of valor", text_short_name="medal valor")


init()
