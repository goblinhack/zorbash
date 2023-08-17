import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "withered fungus", "withered fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.is_combustible(self, True)
    my.is_fungus_withered(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_long2(self, "When even the mushrooms die, you know this is not the place to be...")
    my.text_description_long(self, "A dry husk of a mushroom.")
    my.text_description_short(self, "A withered mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="brown",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_withered_8", tiles=["fungus_withered_8"])


init()
