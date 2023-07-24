import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "corpse finger fungus", "corpse finger")
    fungus_common.tp_init(self)
    # begin sort marker
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d20")
    my.is_fungus_poison(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "A sickly white mushroom with green flesh visible under the cap. It is long and narrow and resembles almost a corpse like finger reach out of the ground.")
    my.text_description_short(self, "A corpse finger mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="lollipop", ascii_bg_col_name="", ascii_fg_col_name="darkgreen",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_9", tiles=["fungus_poison_9"])


init()
