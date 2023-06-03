import my
import tp

self = None


def on_tick_when_deactivated(owner, skill, x, y):
    if owner and (my.thing_health(owner) < my.thing_health_max(owner) / 10):
        my.thing_raging_set(owner, True)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "%%fg=red$You feel primal rage coursing through your veins!%%fg=reset$")
        my.thing_skill_activate(owner, skill)
        return True  # didn't do anything

    return False  # didn't do anything


def on_tick_when_activated(owner, skill, x, y):
    if owner:
        if (my.thing_health(owner) < my.thing_health_max(owner) / 10):
            if my.pcg_randint(1, 100) < 10:
                my.thing_stamina_decr(owner, 5)
        else:
            my.thing_raging_set(owner, False)
            if my.thing_is_player(owner):
                my.thing_msg(owner, "You feel your primal rage dissipate.")
    return False  # didn't do anything


def on_use(owner, skill, target, x, y):
    my.spawn_using_items_radius_range(owner, skill, target, "skill_rage_effect")
    bonus = 2
    my.thing_dmg_current_incr(owner, bonus)
    if my.thing_is_player(owner):
        my.thing_msg(owner, f"%%fg=red$You rage hit for {bonus} additional damage.%%fg=reset$")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.on_tick_when_deactivated_do(self, "me.on_tick_when_deactivated()")
    my.on_use_do(self, "me.on_use()")
    my.skill_base_name(self, "skill_rage")
    my.stat_att_bonus(self, 2)
    my.stat_str_bonus(self, 2)
    my.text_description_long2(self, "When activated your stamina will drain rapidly.")
    my.text_description_long(self, "While raging you gain 2 damage points per attack and gain additional strength bonuses.")
    my.text_description_short(self, "Rage skill.")
    my.text_description_very_short(self, "Rage    1")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_rage_activated")
    my.tile(self, tile="skill_rage")
    my.tp_update(self)


def init():
    tp_init(name="skill_rage1", text_long_name="rage 1", text_short_name="rage 1")


init()
