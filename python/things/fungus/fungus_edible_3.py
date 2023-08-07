import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "redwood cap fungus", "redwood cap fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d3")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An enormous mushroom with a deep red hue cap.")
    my.text_description_short(self, "An enormous redwood mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="red",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_3", tiles=["fungus_edible_3"])


init()
