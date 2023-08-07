import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "anemone fungus", "anemone fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d7")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A peculiar mushroom that looks like an orange sea anemone.")
    my.text_description_short(self, "An enormous orange anemone mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="orange",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_7", tiles=["fungus_edible_7"])


init()
