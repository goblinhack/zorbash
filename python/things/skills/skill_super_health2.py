import my
import tp
import skill_super_health0

self = None


def on_tick_when_activated(owner, skill, x, y):
    if not owner:
        return False  # did nothing

    if my.pcg_randint(1, 100) < 50:
        my.thing_stamina_incr(owner, 3)
        my.thing_health_incr(owner, 2)

    return False  # did nothing


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.stat_con_bonus(self, 3)
    my.text_description_long3(self, "You will gain 3 stamina and 2 health at a 50 percent chance per turn.")
    my.text_description_very_short(self, "SupHealt2")
    my.skill_replaces(self, "skill_super_health1")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    skill_super_health0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_super_health2", text_long_name="super health 2", text_short_name="super health 2")


init()
