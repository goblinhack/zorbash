import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "You are hungry.")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)

    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_debuff(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.text_description_long(self, "You are hungry and may not attack, defend or jump as well as you did.")
    my.text_description_short(self, "You are hungry.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="debuff_status_hungry")
    my.tp_update(self)


def init():
    tp_init(name="debuff_status_hungry",
            text_long_name="hungry",
            text_short_name="hungry")


init()
