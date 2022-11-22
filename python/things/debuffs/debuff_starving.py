import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You are starving.")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)

    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_debuff(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.text_description_long(self, "You are starving and may not attack, defend or jump well. You will not die if you continue to starve, but why continue to live like this?")
    my.text_description_short(self, "You are starving.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="debuff_starving")
    my.tp_update(self)


def init():
    tp_init(name="debuff_starving", text_long_name="starving", text_short_name="starving")


init()
