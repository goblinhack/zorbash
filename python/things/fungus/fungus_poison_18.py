import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "reincarnation fungus", "reincarn. fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d100")
    my.is_fungus_poison(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "Eat this dazzling mushroom once and get to live again...")
    my.text_description_short(self, "An enormous reincarnation mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="F", ascii_bg_col_name="", ascii_fg_col_name="lightblue",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_18", tiles=["fungus_poison_17"])


init()
