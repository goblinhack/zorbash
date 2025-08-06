import my
import tp
import skill_devoted_thrust0

self = None


def on_tick_when_activated(owner, skill, x, y):
    if owner and my.py_pcg_random_range_inclusive(1, 100) < 10:
        my.thing_stamina_decr(owner, 1)
    return False  # didn't do anything


def on_use_skill(owner, skill, target, x, y):
    if not target:
        return
    my.spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    bonus = int(float(my.thing_stamina(owner) / 100.0) * 75.0)

    if bonus > 1:
        if owner and my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=yellow$You strike with a mighty thrust of {bonus} additional damage.%%fg=reset$")
        my.thing_dmg_current_incr(owner, bonus)
        my.thing_stamina_decr(owner, bonus)
    else:
        if owner and my.thing_is_player(owner):
            my.thing_msg(owner, "You run out of devotion.")
        my.thing_skill_deactivate(owner, skill)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.skill_replaces(self, "skill_devoted_thrust3")
    my.stat_def_bonus(self, -3)
    my.stat_str_bonus(self, 3)
    my.text_description_long4(self, "When activated, 75 percent of your stamina will be converted to damage.")
    my.text_description_long5(self, "When activated, 10 percent chance of draining stamina by 1.")
    my.text_description_very_short(self, "InsThrst1")
    # end sort marker
    skill_devoted_thrust0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_devoted_thrust4",
            text_long_name="insane devotion 1",
            text_short_name="insane devotion 1")


init()
