import my
import tp
import skill_artful_dodging0

self = None


def on_tick_when_activated(owner, skill, x, y):
    if not owner:
        return False  # did nothing

    if my.thing_stamina(owner) >= my.thing_stamina_max(owner):
        return False  # did nothing

    if owner and my.pcg_randint(1, 100) < 30:
        my.thing_stamina_incr(owner, 1)
        return False  # did nothing

    return False  # did nothing


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.stat_def_bonus(self, 2)
    my.stat_dex_bonus(self, 3)
    my.skill_replaces(self, "skill_artful_dodging2")
    my.text_description_long3(self, "Stamina will be recovered at a rate of 1 with a 30 percent chance per move.")
    my.text_description_very_short(self, "ArtDodge3")
    # end sort marker
    skill_artful_dodging0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_artful_dodging3", text_long_name="artful dodging 3", text_short_name="artful dodging 3")


init()
