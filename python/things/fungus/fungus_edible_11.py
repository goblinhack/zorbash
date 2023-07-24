import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "lemon fungus", "lemon fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d11")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A lemon sherbet mushroom, covered in a dusting of fine white specks, like sugar.")
    my.text_description_short(self, "An enormous mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="lollipop", ascii_bg_col_name="", ascii_fg_col_name="red",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_11", tiles=["fungus_edible_11"])


init()
