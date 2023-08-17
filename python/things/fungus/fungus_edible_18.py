import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "golden fungus", "golden fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d25")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A shimmering golden mushroom. It's not made of actual gold, merely gold flavour.")
    my.text_description_short(self, "A golden mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="gold",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_18", tiles=["fungus_edible_18"])


init()
