import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.appearing_chance_d1000(self, 10)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_food(self, True)
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
    my.nutrition_dice(self, "1d40")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stat_luck_mod(self, 4)
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+1 LUCK")
    my.text_long_description(self, "Nutritious and lucky!")
    my.text_short_description(self, "A four leaf clover.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="*", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="four_leaf_clover", text_long_name="four-leaf clover", text_short_name="4-clover")


init()
