import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "bluering fungus", "bluering fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d20")
    my.is_fungus_poison(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A large shiny blue mushroom with a brighter blue ring around the cap.")
    my.text_description_short(self, "A bluering mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="blue",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_8", tiles=["fungus_poison_8"])


init()
