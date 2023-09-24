import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You are confused and unable to move!")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)

    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_debuff(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.text_description_long(self, "You are confused and may be unable to walk in a straight line!")
    my.text_description_short(self, "You are confused. More so.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="debuff_status_confusion")
    my.tp_update(self)


def init():
    tp_init(name="debuff_status_confusion", text_long_name="confusion", text_short_name="confusion")


init()
