import my
import tp
import crystal0


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    crystal0.tp_init(self)
    my.stat_def_bonus(self, 3)
    my.text_description_long2(self, "It glows beautifully in the dark and will bestow you with much needed defense bonuses.")
    my.text_description_long(self, "This magical crystal is the second to collect on your long journey towards confronting Zorbash.")
    # end sort marker

    my.tile(self,
            ascii_fg_char="theta", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name, delay_ms=50)
    my.tile(self,
            ascii_fg_char="theta", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name, delay_ms=50)

    my.tp_update(self)


def init():
    tp_init(name="crystal2", text_long_name="crystal II", text_short_name="crystal II")


init()
