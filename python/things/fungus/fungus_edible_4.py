import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "fancy cap fungus", "fancy cap fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d4")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An enormous mushroom with brown cap ringed with translucent yellow frills.")
    my.text_description_short(self, "An enormous fancy cap mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="lollipop", ascii_bg_col_name="", ascii_fg_col_name="yellow",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_4", tiles=["fungus_edible_4"])


init()
