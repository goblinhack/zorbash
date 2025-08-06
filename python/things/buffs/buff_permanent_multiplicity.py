import my
import tp

self = None


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("x,y     {},{}".format(x, y))
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    vx, vy = my.thing_coords_get(victim)
    if not my.level_is_spectral_blade_at(me, vx, vy):
        if my.level_is_alive_monst_at(me, vx, vy) or my.level_is_monst_at(me, vx, vy):
            roll = my.py_d100()
            if roll < 100 + my.thing_enchant_count_get(me) * 5:
                it = my.spawn_at_my_position(victim, "spectral_blade_companion")
                if it != 0:
                    my.thing_set_leader(it, owner)
    return damage


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker

    my.gfx_ascii_shown(self, True)
    my.is_buff(self, True)
    my.is_loggable(self, True)
    my.is_runic_offensive_class_A(self, True)
    my.on_owner_attack_dmg_melee_do(self, "me.on_owner_attack_dmg_melee()")
    my.text_description_long(self, "This weapon has a chance of spawning a spectral blade every attack upon a monster")
    my.text_description_short(self, "Multiplicity weapon")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="buff_multiplicity")
    my.tp_update(self)


def init():
    tp_init(name="buff_permanent_multiplicity",
            text_long_name="multiplicity",
            text_short_name="multiplicity")


init()
