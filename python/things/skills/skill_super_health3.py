import my
import tp
import skill_super_health0

self = None


def on_tick_when_activated(owner, skill, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("skill  {} {}".format(my.thing_name_get(skill), my.thing_health(skill)))

    if not owner:
        return False  # did nothing

    if my.pcg_randint(1, 100) < 50:
        my.thing_stamina_incr(owner, 4)
        my.thing_health_incr(owner, 3)

    return False  # did nothing


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.stat_con_bonus(self, 4)
    my.text_description_long3(self, "You will gain 4 stamina and 3 health at a 50 percent chance per turn.")
    my.text_description_very_short(self, "SupHealt3")
    my.skill_replaces(self, "skill_super_health2")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    skill_super_health0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_super_health3", text_long_name="super health 3", text_short_name="super health 3")


init()
