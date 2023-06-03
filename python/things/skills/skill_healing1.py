import my
import tp
import skill_healing0

self = None


def on_tick_when_activated(owner, skill, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("skill  {} {}".format(my.thing_name_get(skill), my.thing_health(skill)))

    if not owner:
        return False  # did nothing

    if my.thing_stamina(owner) < 2:
        return False  # did nothing

    if my.thing_health(owner) >= my.thing_health_max(owner):
        return False  # did nothing

    my.thing_stamina_decr(owner, 2)
    my.thing_health_incr(owner, 1)
    return False  # did nothing


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.stat_dex_bonus(self, 1)
    my.text_description_long3(self, "Conversion rate is 1 stamina per turn to 1 health.")
    my.text_description_very_short(self, "AccHeal 1")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    skill_healing0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_healing1", text_long_name="accelerated health 1", text_short_name="accelerated health 1")


init()
