import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "black reaper fungus", "reaper fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d8")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An ominous and dark capped mushroom. Black frills that dangle from its cap make this mushroom look like it is wearing the cape of a reaper.")
    my.text_description_short(self, "A reaper mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="gray10",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_8", tiles=["fungus_edible_8"])


init()
