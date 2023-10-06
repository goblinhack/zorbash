import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "You feel at one with the dungeon.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "The world seems more empty somehow.")


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.lifespan_dice(self, "1d100+50")
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_unset_do(self, "me.on_owner_unset()")
    my.stat_psi_bonus(self, 10)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="buff_telepathy")
    my.tp_update(self)


def init():
    tp_init(name="buff_temporary_telepathy", text_long_name="telepathy")


init()
