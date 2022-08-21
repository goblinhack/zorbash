import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.collision_hit_priority(self, 6)
    my.environ_avoids_fire(self, 100)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_food(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_organic(self, True)
    my.is_throwable(self, True)
    my.is_usable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 25)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "10+1d20")
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "A bottle of imported Gobweiser beer. A local favorite.")
    my.text_short_description(self, "Imported beer.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char=";", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name, is_hp_100_percent=True)
    my.tp_update(self)


def init():
    tp_init(name="food_beer1", text_long_name="imported beer", text_short_name="beer")


init()
