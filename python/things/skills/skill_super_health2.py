import my
import tp
import skill_super_health0

self = None


def on_tick_when_activated(owner, skill, x, y):
    if not owner:
        return False  # did nothing

    if my.py_pcg_random_range_inclusive(1, 100) < 50:
        my.thing_stamina_incr(owner, 3)
        my.thing_health_incr(owner, 2)

    return False  # did nothing


def on_owner_receive_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    new_damage = int(damage / 3)
    if owner and my.thing_is_player(owner):
        my.thing_msg(owner, f"Your superior health reduces the poison damage to {new_damage}.")
    return new_damage


def on_owner_receive_dmg_cold(me, owner, hitter, real_hitter, x, y, damage):
    new_damage = int(damage / 3)
    if owner and my.thing_is_player(owner):
        my.thing_msg(owner, f"Your superior health reduces the cold damage to {new_damage}.")
    return new_damage


def on_owner_receive_dmg_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    new_damage = int(damage / 3)
    if owner and my.thing_is_player(owner):
        my.thing_msg(owner, f"Your superior health reduces the necrosis damage to {new_damage}.")
    return new_damage


def on_owner_receive_dmg_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    new_damage = int(damage / 3)
    if owner and my.thing_is_player(owner):
        my.thing_msg(owner, f"Your superior health reduces the constitution damage to {new_damage}.")
    return new_damage


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.skill_replaces(self, "skill_super_health1")
    my.stat_con_bonus(self, 3)
    my.text_description_long4(self, "You will gain 3 stamina and 2 health at a 50 percent chance per turn.")
    my.text_description_long5(self, "Cold, poison, necrosis and constitution damage will be reduced by 30 percent.")
    my.text_description_very_short(self, "SupHealt2")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    skill_super_health0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_super_health2", text_long_name="super health 2", text_short_name="super health 2")


init()
