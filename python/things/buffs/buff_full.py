import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You are satiated.")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)

    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.text_long_description(self, "Hunger does not kill in this game. However, if you become hungry or starved, you will lose points on attack and defense and other abilities may also be impacted. Best to keep food at hand.")
    my.text_short_description(self, "You are satiated.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    # end sort marker

    my.tile(self,
            tile="buff_full")
    my.tp_update(self)


def init():
    tp_init(name="buff_full", text_long_name="full and happy", text_short_name="full")


init()
