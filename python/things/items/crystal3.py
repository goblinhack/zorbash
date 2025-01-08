import my
import tp
import crystal0


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    crystal0.tp_init(self)
    my.stat_con_bonus(self, 3)
    my.text_description_long(self, "This magical crystal is the next to collect on your long journey towards confronting Zorbash.")
    my.text_description_long2(self, "It glows beautifully in the dark and will bestow you with much needed constitution bonuses.")
    # end sort marker

    my.tile(self,
            ascii_fg_char="theta", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name, delay_ms=50)
    my.tile(self,
            ascii_fg_char="theta", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name, delay_ms=50)

    my.tp_update(self)


def init():
    tp_init(name="crystal3", text_long_name="crystal III", text_short_name="crystal III")


init()
