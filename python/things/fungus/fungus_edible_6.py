import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "blueberry fungus", "blueberry fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d6")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An strange mushroom composed of enormous berries that look like blueberries.")
    my.text_description_short(self, "An enormous blueberry mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="blue",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_6", tiles=["fungus_edible_6"])


init()
