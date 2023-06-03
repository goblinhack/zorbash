import my
import tp
import skill_primal_rage0

self = None


def on_tick_when_deactivated(owner, skill, x, y):
    if owner and (my.thing_health(owner) < my.thing_health_max(owner) / 20):
        my.thing_raging_set(owner, True)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "%%fg=red$You feel primal rage coursing through your veins!%%fg=reset$")
        my.thing_skill_activate(owner, skill)
        return True  # didn't do anything

    return False  # didn't do anything


def on_tick_when_activated(owner, skill, x, y):
    if owner:
        if (my.thing_health(owner) < my.thing_health_max(owner) / 25):
            if my.pcg_randint(1, 100) < 10:
                my.thing_stamina_decr(owner, )
        else:
            my.thing_raging_set(owner, False)
            if my.thing_is_player(owner):
                my.thing_msg(owner, "You feel your primal rage dissipate.")
    return False  # didn't do anything


def on_use(owner, skill, target, x, y):
    my.spawn_using_items_radius_range(owner, skill, target, "skill_primal_rage_effect")
    bonus = 6
    my.thing_dmg_current_incr(owner, bonus)
    if my.thing_is_player(owner):
        my.thing_msg(owner, f"%%fg=red$You rage hit for {bonus} additional damage.%%fg=reset$")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.stat_att_bonus(self, 3)
    my.stat_str_bonus(self, 3)
    my.skill_replaces(self, "skill_primal_rage2")
    my.text_description_long3(self, "While raging you gain 6 damage points per attack and gain additional strength bonuses. This is the maximum ability of primal raging. Beyond this, other types of rage specialization become possible.")
    my.text_description_long4(self, "Raging will auto activate at 20 percent of your health and deactivate at 25 percent.")
    my.text_description_long5(self, "With this level of skill have a 10 percent chance of draining stamina.")
    my.text_description_very_short(self, "PrimRage3")
    # end sort marker
    my.tile(self, tile="skill_primal_rage_activated")
    my.tile(self, tile="skill_primal_rage")

    skill_primal_rage0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_primal_rage3", text_long_name="primal rage 3", text_short_name="primal rage 3")


init()
