import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "orange puff fungus", "orange puff fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d2")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "An enormous powder puff mushroom with fluffy flecks of orange on its cap and a pale stalk.")
    my.text_description_short(self, "An enormous orange mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="orange",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_2", tiles=["fungus_edible_2"])


init()
