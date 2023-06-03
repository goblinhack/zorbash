import my
import tp
import skill_devoted_thrust0

self = None


def on_tick_when_activated(owner, skill, x, y):
    if owner and my.pcg_randint(1, 100) < 10:
        my.thing_stamina_decr(owner, 1)
    return False  # didn't do anything


def on_use(owner, skill, target, x, y):
    my.spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    bonus = int(my.thing_stamina(owner) / 100) * 90

    if bonus > 1:
        if my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=yellow$You strike with a mighty thrust of {bonus} additional damage.%%fg=reset$")
        my.thing_dmg_current_incr(owner, bonus)
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You run out of devotion.")
        my.thing_skill_deactivate(owner, skill)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.skill_replaces(self, "skill_devoted_thrust4")
    my.stat_def_bonus(self, -4)
    my.stat_str_bonus(self, 4)
    my.text_description_long4(self, "When activated, 90 percent of your stamina will be converted to damage.")
    my.text_description_long5(self, "When activated, 10 percent chance of draining stamina by 1.")
    my.text_description_very_short(self, "InsThrst2")
    # end sort marker
    skill_devoted_thrust0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_devoted_thrust5", text_long_name="insane devotion 2", text_short_name="insane devotion 2")


init()
