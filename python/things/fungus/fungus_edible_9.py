import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "salami fungus", "salami fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d9")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An odd mushroom that looks like a piece of salami on a stem.")
    my.text_description_short(self, "A salami mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="pink",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_9", tiles=["fungus_edible_9"])


init()
