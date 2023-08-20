import my
import tp

self = None


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel sluggish.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_unset(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel less sluggish again.")


def on_tick(owner, item, x, y):
    my.thing_stamina_incr(owner, 2)
    my.thing_health_incr(owner, 2)
    return True


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_debuff(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.move_speed_bonus(self, -50)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.lifespan_dice(self, "1d100+50")
    my.on_tick_do(self, "me.on_tick()")
    my.on_owner_unset_do(self, "me.on_owner_unset()")
    my.text_description_long(self, "You feel even more sluggish than normal.")
    my.text_description_long2(self, "One plus side is that you will heal and recover faster from this enforced rest.")
    my.text_description_short(self, "You are being slowed.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile="debuff_slowed")
    my.tp_update(self)


def init():
    tp_init(name="debuff_slowed", text_long_name="sluggishly slow", text_short_name="slowed")


init()
