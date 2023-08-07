import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "blobbo fungus", "blobbo fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_fungus_edible(self, True)
    my.nutrition_dice(self, "1d14")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A shimering green blob like fungus. Hm tasty...")
    my.text_description_short(self, "An blobbo mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="green",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_edible_14", tiles=["fungus_edible_14"])


init()
