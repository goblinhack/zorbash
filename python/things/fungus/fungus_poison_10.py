import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "cheesespire fungus", "cheesespire fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d20")
    my.is_fungus_poison(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An enormous cheddar yellow mushroom. Looks like cheese. Smells like it too.")
    my.text_description_short(self, "n cheesespire mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="yellow",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_10", tiles=["fungus_poison_10"])


init()
