import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "skullpuff fungus", "skullpuff fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_short(self, "An enormous skullpuff mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="white",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_5", tiles=["fungus_edible_5"])


init()
