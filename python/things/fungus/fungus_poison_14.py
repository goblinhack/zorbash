import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "green jelly fungus", "green jelly fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d30")
    my.is_fungus_poison(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "Green, translucent and succulent looking. This green mushroom is a site to die for.")
    my.text_description_short(self, "An enormous green jelly mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="green",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_14", tiles=["fungus_poison_14"])


init()
