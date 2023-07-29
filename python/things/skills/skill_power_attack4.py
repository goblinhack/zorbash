import my
import tp
import skill_power_attack0

self = None


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.skill_replaces(self, "skill_power_attack3")
    my.stat_att_bonus(self, 8)
    my.stat_def_bonus(self, -8)
    my.text_description_very_short(self, "IronDef4")
    # end sort marker
    skill_power_attack0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_power_attack4", text_long_name="power attack 4", text_short_name="power attack 4")


init()
