import my
import tp
import fungus_common


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "bloodcrawler fungus", "b.crawler fungus")
    fungus_common.tp_init(self)
    # begin sort marker
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d30")
    my.is_fungus_poison(self, True)
    my.nutrition_dice(self, "1d5")
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "This mushroom has long red tendril like legs and a bloated hideous cap. Need I say more?")
    my.text_description_short(self, "An bloodcrawler mushroom.")
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="lollipop", ascii_bg_col_name="", ascii_fg_col_name="red",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_16", tiles=["fungus_poison_15"])


init()
