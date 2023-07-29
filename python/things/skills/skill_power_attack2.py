import my
import tp
import skill_power_attack0

self = None


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.skill_replaces(self, "skill_power_attack1")
    my.stat_def_bonus(self, -4)
    my.stat_dex_bonus(self, 4)
    my.text_description_very_short(self, "IronDef2")
    # end sort marker
    skill_power_attack0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_power_attack2", text_long_name="power attack 2", text_short_name="power attack 2")


init()
